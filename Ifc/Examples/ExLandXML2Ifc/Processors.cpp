/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#include "IfcCore.h"
#include "IfcEntity.h"

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"

#include "ExPrintConsole.h"

#include "ExLandXML2IfcConverter.h"
#include "ElementProcessor.h"

#include "AlignmentGeometryBuilder.h"
#include "Entities/IfcCurve.h"
// #define FIRST_REALIZATION

#define RAILS_TOL 1.e-1

#ifdef FIRST_REALIZATION

OdGePoint2d lineLineInt(
  const OdGePoint2d &p1, const OdGeVector2d &v1, const OdGePoint2d &p2, const OdGeVector2d &v2,
  double *t1 = nullptr, double *t2 = nullptr)
{
  double x1 = p1.x;
  double y1 = p1.y;
  double x1Dir = v1.x;
  double y1Dir = v1.y;

  double x2 = p2.x;
  double y2 = p2.y;
  double x2Dir = v2.x;
  double y2Dir = v2.y;

  // t1 = (x2 + t2 * x2Dir - x1) / x1Dir
  // t1 = (y2 + t2 * y2Dir - y1) / y1Dir
  // (x2 + t2 * x2Dir - x1) / x1Dir = (y2 + t2 * y2Dir - y1) / y1Dir
  // y1Dir * (x2 + t2 * x2Dir - x1) = x1Dir * (y2 + t2 * y2Dir - y1)

  // t2 * x2Dir * y1Dir + y1Dir * (x2 - x1) = t2 * y2Dir * x1Dir + x1Dir * (y2 - y1)
  // t2 * (x2Dir * y1Dir - y2Dir * x1Dir) = x1Dir * (y2 - y1) - y1Dir * (x2 - x1)

  // t2 * (x2Dir * y1Dir - y2Dir * x1Dir) = x1Dir * (y2 - y1) - y1Dir * (x2 - x1)
  // t2 = (x1Dir * (y2 - y1) - y1Dir * (x2 - x1)) / (x2Dir * y1Dir - y2Dir * x1Dir)

  double d = (x2Dir * y1Dir - y2Dir * x1Dir);
  if (OdZero(d))
  {
    // Incorrect
    return p1;
  }

  // Output
  double _t2 = (x1Dir * (y2 - y1) - y1Dir * (x2 - x1)) / d;
  double _t1 = OdZero(y1Dir) ? (x2 + _t2 * x2Dir - x1) / x1Dir
    : (y2 + _t2 * y2Dir - y1) / y1Dir;

  // Fillet circle center point
  OdGePoint2d resPt = p1 + v1 * _t1;
  OdGePoint2d resPt2 = p2 + v2 * _t2;
  ODA_ASSERT(resPt.isEqualTo(resPt2, OdGeTol(1e-7)));

  if (t1)
    *t1 = _t1;
  if (t2)
    *t2 = _t2;

  return resPt;
}
#endif //FIRST_REALIZATION

OdIfc::OdIfcEntityPtr ElementProcessor::processCartesianPoint(const xmlChar **attrs)
{
  OdIfc::OdIfcEntityPtr cartesianPoint = m_converter->model()->createEntityInstance("ifccartesianpoint");
  m_converter->model()->appendEntityInstance(cartesianPoint);
  return cartesianPoint;
}

/* \details
Vertical alignment processor.
*/
void ProfileProcessor::onStart(const xmlChar *name, const xmlChar **attrs)
{
  const xmlChar *profileName = m_converter->getAttr("name", attrs);
  if (profileName)
  {
    m_name = ((const char *)profileName);
  }
}

void ProfileProcessor::onEnd(const xmlChar *elementName)
{
  if (m_pvis.size() == 0)
    return;

  ODA_ASSERT(m_pvis.size() > 1);

  AlignmentProcessor *alignment = dynamic_cast<AlignmentProcessor*>(parent());
  ODA_ASSERT(alignment);

  if (alignment)
  {
    // Starts from zero in IFC
    double staDist = alignment->staStart();
    if (!OdZero(staDist))
      for (auto &it : m_pvis)
        it.station -= staDist;
  }

  enum SegmentType
  {
    kLine,
    kArc
  };

  struct Segment
  {
    ProfAlignProcessor::PVI pvi;

    SegmentType type;
    OdIfc::OdIfcEntityPtr inst;
    OdDAIObjectId id;

    OdGePoint2d startStation;
    OdGePoint2d endStation;

    // IfcAlignment2DSegment
    OdAnsiString startTag;

    // IfcAlignmentVerticalSegment
    double startDistAlong;
    double horizontalLength;
    double startHeight;
    double startGradient;
    double endGradient;
    double radius = OdDAI::Consts::OdNan;
  };
  typedef OdArray<Segment> SegmentArr;

  SegmentArr segments;

  ProfAlignProcessor::PVI *prev = nullptr;
  ProfAlignProcessor::PVI *cur = nullptr;

  prev = &m_pvis.at(0);
  for (unsigned int i = 1; i < m_pvis.size(); ++i)
  {
    cur = &m_pvis.at(i);

    if (cur->type == ProfAlignProcessor::kStation)
    {
      if (prev->type == ProfAlignProcessor::kStation)
      {
        Segment lineSegm;
        lineSegm.type = kLine;
        lineSegm.startTag = prev->desc;
        lineSegm.startDistAlong = prev->station;
        lineSegm.horizontalLength = cur->station - prev->station;
        lineSegm.startHeight = prev->elevation;
        lineSegm.startGradient = (cur->elevation - prev->elevation) / lineSegm.horizontalLength;
        lineSegm.endGradient = lineSegm.startGradient;
        lineSegm.radius = 0.; // arc attribute
        lineSegm.startStation = OdGePoint2d(prev->station, prev->elevation);
        lineSegm.endStation = OdGePoint2d(cur->station, cur->elevation);
        segments.append(lineSegm);

        prev = cur;
      }
      else
        if (prev->type == ProfAlignProcessor::kCircCurve)
        {
          Segment *prevSegment = &segments.at(segments.size() - 1);

          OdGePoint2d endStation(cur->station, cur->elevation);
          if (prevSegment->endStation != endStation)
          {
            // append following linear segment if needed
            Segment lineSegm;
            lineSegm.type = kLine;
            lineSegm.startTag = prev->desc;
            lineSegm.startDistAlong = prevSegment->endStation.x;
            lineSegm.horizontalLength = endStation.x - prevSegment->endStation.x;
            lineSegm.startHeight = prevSegment->endStation.y;
            lineSegm.startGradient = (endStation.y - prevSegment->endStation.y) / lineSegm.horizontalLength;
            lineSegm.endGradient = lineSegm.startGradient;
            lineSegm.radius = 0.; // arc attribute
            segments.append(lineSegm);
          }

          prev = cur;
        }
    }
    else
    if (cur->type == ProfAlignProcessor::kCircCurve)
    {
      ProfAlignProcessor::PVI *next = &m_pvis.at(i + 1);

      OdGePoint2d prevPVI(prev->station, prev->elevation);
      OdGePoint2d curPVI(cur->station, cur->elevation);
      OdGePoint2d nextPVI(next->station, next->elevation);

      //
      // Directions of linear segments
      //
      OdGeVector2d prevCur = (curPVI - prevPVI).normalize();
      OdGeVector2d nextCur = (nextPVI - curPVI).normalize();

      Segment arcSegm;
      arcSegm.type = kArc;
      arcSegm.startTag = prev->desc;
      arcSegm.startGradient = tan(prevCur.angle()); // -1 < gradient < 1 or -45deg < gradient_in_deg < 45deg
      arcSegm.endGradient = tan(nextCur.angle()); // -1 < gradient < 1 or -45deg < gradient_in_deg < 45deg


#ifdef FIRST_REALIZATION
      double prevLen = prevCur.length();
      double nextLen = nextCur.length();

      ODA_ASSERT(OdEqual(prevLen, 1.) && OdEqual(prevLen, nextLen));

      if (prevCur.isParallelTo(nextCur))
      {
        // Just linear segment, arc can not be calculated,
        // use next PVI
        continue;
      }

      //
      // Offset directions for fillet calculation
      //
      OdGeVector2d prevOffsetDir = prevCur.perpVector() * cur->radius;
      double prevOffsetLen = prevOffsetDir.length();

      OdGeVector2d nextOffsetDir = nextCur.perpVector() * cur->radius;
      double nextOffsetLen = nextOffsetDir.length();

      ODA_ASSERT(OdEqual(nextOffsetLen, fabs(cur->radius)));
      ODA_ASSERT(OdEqual(prevOffsetLen, nextOffsetLen));

      //
      // Offset PVI
      //
      OdGePoint2d prevPVIOffseted = curPVI + prevOffsetDir;
      OdGePoint2d nextPVIOffseted = curPVI + nextOffsetDir;

      //
      // Find fillet arc center point (intersect directions)
      //
      double t1 = 0., t2 = 0.;
      OdGePoint2d arcCenter = lineLineInt(prevPVIOffseted, prevCur, nextPVIOffseted, nextCur, &t1, &t2);

      OdGePoint2d arcStartPt = lineLineInt(arcCenter, -prevOffsetDir, prevPVI, prevCur);
      OdGePoint2d arcEndPt = lineLineInt(arcCenter, -nextOffsetDir, curPVI, nextCur);

      double arcStartAngle = 0.;
      double arcEndAngle = 0.;

      if (cur->radius < 0.)
      {
        // crest
        arcStartAngle = prevCur.perpVector().angle();
        arcEndAngle = nextCur.perpVector().angle();
      }
      else
      {
        // sag
        arcStartAngle = (-prevCur.perpVector()).angle();
        arcEndAngle = (-nextCur.perpVector()).angle();
      }

      double degStart = arcStartAngle * 180. / OdaPI;
      double degEnd = arcEndAngle * 180. / OdaPI;

      double arcAngle = (arcEndAngle - arcStartAngle);
      double degrees = arcAngle * 180. / OdaPI;
      double arcLen = arcAngle * cur->radius;


      arcSegm.startDistAlong = arcStartPt.x;
      arcSegm.horizontalLength = arcEndPt.x - arcStartPt.x;
      arcSegm.startHeight = arcStartPt.y;
      arcSegm.startStation = arcStartPt;
      arcSegm.endStation = arcEndPt;
      arcSegm.radius = cur->radius * -1.;
#else
      double radius = cur->radius;
      double arcAngle = cur->arcLength / radius;
      double halfAngle = arcAngle * .5;
      double distToArcCenter = radius / cos(halfAngle);
      double distToStart = distToArcCenter * sin(halfAngle);
      OdGePoint2d startPoint = curPVI - prevCur * distToStart;
      OdGePoint2d endPoint = curPVI + nextCur * distToStart;
      OdGeVector2d chord = endPoint - startPoint;
      arcSegm.startDistAlong = startPoint.x;
      arcSegm.horizontalLength = chord.dotProduct(OdGeVector2d::kXAxis);
      arcSegm.radius = radius;
      arcSegm.startHeight = startPoint.y;
      arcSegm.startStation = startPoint;
      arcSegm.endStation = endPoint;
#endif //FIRST_REALIZATION
      if (segments.size() > 0)
      {
        Segment *prevSegment = &segments.at(segments.size() - 1);

        if (prevSegment->endStation != arcSegm.startStation)
        {
          // append previous linear segment if needed
          Segment lineSegm;
          lineSegm.type = kLine;
          lineSegm.startTag = prev->desc;
          lineSegm.startDistAlong = prevSegment->endStation.x;
          lineSegm.horizontalLength = arcSegm.startStation.x - prevSegment->endStation.x;
          lineSegm.startHeight = prevSegment->endStation.y;
          lineSegm.startGradient = (arcSegm.startStation.y - prevSegment->endStation.y) / lineSegm.horizontalLength;
          lineSegm.endGradient = lineSegm.startGradient;
          lineSegm.radius = 0.; // arc attribute
          segments.append(lineSegm);
        }
      }
      else
      {
        if (prevPVI != arcSegm.startStation)
        {
          // append previous linear segment if needed
          Segment lineSegm;
          lineSegm.type = kLine;
          lineSegm.startTag = prev->desc;
          lineSegm.startDistAlong = prevPVI.x;
          lineSegm.horizontalLength = arcSegm.startStation.x - prevPVI.x;
          lineSegm.startHeight = prevPVI.y;
          lineSegm.startGradient = (arcSegm.startStation.y - prevPVI.y) / lineSegm.horizontalLength;
          lineSegm.endGradient = lineSegm.startGradient;
          lineSegm.radius = 0.; // arc attribute
          segments.append(lineSegm);
        }
      }

      segments.append(arcSegm);

      /*if (prevPVI != arcEndPt)
      {
        // append following linear segment if needed
        Segment lineSegm;
        lineSegm.type = kLine;
        lineSegm.tangentialContinuity = true;
        lineSegm.startTag = prev->desc;
        lineSegm.startDistAlong = arcEndPt.x;
        lineSegm.horizontalLength = nextPVI.x - arcEndPt.x;
        lineSegm.startHeight = arcEndPt.y;
        lineSegm.startGradient = (nextPVI.y - arcEndPt.y) / lineSegm.horizontalLength;
        lineSegm.radius = 0.; // arc attribute
        lineSegm.isConvex = false; // arc attribute
        segments.append(lineSegm);
      }*/

      prev = cur;
    }
  }

  double checkLength = 0;
  for (auto &segment : segments)
  {
    checkLength += segment.horizontalLength;
  }
  double totalHorizontalLength = alignment->length();
  ODA_ASSERT(OdEqual(checkLength, totalHorizontalLength, 1e-5));

  //
  // Fill IFC Model with segments
  //
  OdDAIObjectIds idsSegments, nested;
  for (auto &segment : segments)
  {
    OdIfc::OdIfcEntityPtr pEnt = m_converter->model()->createEntityInstance("ifcalignmentverticalsegment");
    segment.inst = pEnt;
    segment.id = m_converter->model()->appendEntityInstance(pEnt);
    idsSegments.append(segment.id);

    OdAnsiString segType;
    if (segment.type == kLine)
      segType = "CONSTANTGRADIENT";
    else if (segment.type == kArc)
      segType = "CIRCULARARC";
    else
    {
      ODA_FAIL_M("Unsupported segment type");
    }

    //
    // Put attribute values
    //
    pEnt->putAttr("startdistalong", segment.startDistAlong);
    pEnt->putAttr("horizontallength", segment.horizontalLength);
    pEnt->putAttr("startheight", segment.startHeight);
    pEnt->putAttr("startgradient", segment.startGradient);
    pEnt->putAttr("endgradient", segment.endGradient);
    if (segment.type != kLine)
      pEnt->putAttr("radiusofcurvature", fabs(segment.radius)); // IfcPositiveLengthMeasure
    pEnt->putAttr("predefinedtype", segType);
    
    nested.append(m_converter->createAlignmentSegment(segment.id)->id());
  }

  if (idsSegments.size() > 0)
  {
    m_alignmentVertical = m_converter->createRooted("ifcalignmentvertical");
    m_alignmentVertical->putAttr("name", m_name);
    OdDAI::ApplicationInstancePtr relNests = m_converter->addRelNests(m_alignmentVertical, nested);
    relNests->setInverseCounterParts();
  }
}

//
// CantStation
//
void CantStationProcessor::onStart(const xmlChar *name, const xmlChar **attrs)
{
  m_transitionType = (const char *)m_converter->getAttr("transitiontype", attrs);

  //
  // Station
  //
  const char *strStation = (const char *)m_converter->getAttr("station", attrs);
  ODA_ASSERT(strStation);
  if (strStation)
    m_station = atof(strStation);

  //
  // Applied cant
  //
  const char *strAppliedCant = (const char *)m_converter->getAttr("appliedcant", attrs);
  ODA_ASSERT(strAppliedCant);
  m_appliedCant = atof(strAppliedCant);

  //
  // Curvature
  //
  const char *strCurvature = (const char *)m_converter->getAttr("curvature", attrs);
  ODA_ASSERT(strCurvature);
  m_curvature = strCurvature;

  //
  // Cant Gradient
  //
  const char *strCantGradient = (const char *)m_converter->getAttr("cantgradient", attrs);
  if (strCantGradient)
    m_cantGradient = atof(strCantGradient);

  //
  // Speed
  //
  const char *strSpeed = (const char *)m_converter->getAttr("speed", attrs);
  if (strSpeed)
    m_speed = atof(strSpeed);
}

//
// Cant
//
OdAnsiString CantProcessor::transitionName2Ifc(const char *landXMLName)
{
  OdAnsiString transitionType = landXMLName;
  transitionType.makeLower();

  if (transitionType == "bloss")
    transitionType = "BLOSSCURVE";
  else
    if (transitionType == "biquadraticParabola")
      transitionType = "BIQUADRATICPARABOLA";
    else
      if (transitionType == "clothoid")
        transitionType = "CLOTHOIDCURVE";
      else
        if (transitionType == "cosine")
          transitionType = "COSINECURVE";
        else
          if (transitionType == "cubicParabola")
            transitionType = "CUBICPARABOLA";
          else
            if (transitionType == "sinusoid")
              transitionType = "SINECURVE";
            else
            {
              ODA_ASSERT(0 && "Unsupported transitional curve type");
              /*biquadratic, cubic, revBiquadratic, revBloss, revCosine, revSinusoid,
              sineHalfWave, japaneseCubic, radioid, weinerBogen */
            }

  return transitionType;
}

void CantProcessor::onEnd(const xmlChar *elementName)
{
  AlignmentProcessor *alignmentCurve = dynamic_cast<AlignmentProcessor*>(m_parent);
  ODA_ASSERT_ONCE(alignmentCurve);

  OdDAIObjectIds idsSegments, nested;
  if (m_segments.size() == 0)
  {
    // Create straight dummy segment with gauge information
    OdIfc::OdIfcEntityPtr pSegment = m_converter->model()->createEntityInstance("ifcalignmentcantsegment");
    pSegment->putAttr("startdistalong", 0.);
    pSegment->putAttr("horizontallength", alignmentCurve->length());
    pSegment->putAttr("startcantleft", 0.);
    pSegment->putAttr("endcantleft", 0.);
    pSegment->putAttr("startcantright", 0.);
    pSegment->putAttr("endcantright", 0.);
    pSegment->putAttr("predefinedtype", OdAnsiString("CONSTANTCANT"));
    OdDAIObjectId id = m_converter->model()->appendEntityInstance(pSegment);
    idsSegments.append(id);
    nested.append(m_converter->createAlignmentSegment(id)->id());
  }
  else
  {
    CantSegment &segment = m_segments[0];
    if (OdGreater(segment.station, 0.))
    {
      // First segment is starting from zero without cant
      CantSegment firstLinear;
      m_segments.insertAt(0, firstLinear);
    }

    double scale = 1e-3;
    double alignmentHorizontalLength = alignmentCurve->length();
    //segment = m_segments[m_segments.size()-1];

    ODA_ASSERT_ONCE(m_segments.size() > 1);

    OdIfc::OdIfcEntityPtr pSegment;
    CantSegment *prev = m_segments.begin();
    CantSegment *cur = prev + 1;
    while (cur < m_segments.end())
    {
      pSegment = m_converter->model()->createEntityInstance("ifcalignmentcantsegment");
      pSegment->putAttr("startdistalong", prev->station);

      double segmentHorizontalLength = cur != m_segments.end() ?
        cur->station - prev->station : alignmentHorizontalLength - prev->station;
      pSegment->putAttr("horizontallength", segmentHorizontalLength);

      // Start cant values
      double startCantLeft = 0.;
      double startCantRight = 0.;
      if (prev != nullptr)
      {
        if (prev->curvature == "ccw")
        {
          startCantRight = prev->appliedCant;
        }
        else
        {
          startCantLeft = prev->appliedCant;
        }

        // Have files where appliedCant in meters * 1e-3 (0.125)
        // and files where applied cant is in millimeters (80)
        if (startCantLeft > 1) // TODO: Units conversion?
          startCantLeft *= scale; // to mm
      }
      pSegment->putAttr("startcantleft", startCantLeft);
      pSegment->putAttr("startcantright", startCantRight);

      // End cant values
      double endCantLeft = 0.;
      double endCantRight = 0.;
      if (cur != m_segments.end())
      {
        if (cur->curvature == "ccw")
        {
          endCantRight = cur->appliedCant;
        }
        else
        {
          endCantLeft = cur->appliedCant;
        }
        
        // Have files where appliedCant in meters * 1e-3 (0.125)
        // and files where applied cant is in millimeters (80)
        if (endCantLeft > 1.) // TODO: Units conversion?
          endCantLeft *= scale; // to mm
      }
      pSegment->putAttr("endcantleft", endCantLeft);
      pSegment->putAttr("endcantright", endCantRight);

      OdAnsiString cantType;
      if (OdEqual(startCantLeft, endCantLeft) && OdEqual(startCantRight, endCantRight))
        cantType = "CONSTANTCANT";
      else
        cantType = "LINEARTRANSITION";
      pSegment->putAttr("predefinedtype", cantType);

      prev->m_alignmentCantSegment = pSegment;

      prev->id = m_converter->model()->appendEntityInstance(prev->m_alignmentCantSegment);
      idsSegments.append(prev->id);
      nested.append(m_converter->createAlignmentSegment(prev->id)->id());

      prev = cur;
      ++cur;
    }
  }

  ODA_ASSERT(idsSegments.size());

  m_alignmentCant = m_converter->createRooted("ifcalignmentcant");
  m_alignmentCant->putAttr("name", m_name);
  m_alignmentCant->putAttr("railheaddistance", m_gauge);
  OdDAI::ApplicationInstancePtr relNests = m_converter->addRelNests(m_alignmentCant, nested);
  relNests->setInverseCounterParts();
}

void CantProcessor::onSubElementEnd(ElementProcessor *subProcessor)
{
  CantStationProcessor *cantStation = dynamic_cast<CantStationProcessor*>(subProcessor);
  if (cantStation)
  {
    CantSegment segment;
    segment.station = cantStation->station();
    segment.appliedCant = cantStation->appliedCant();
    segment.curvature = cantStation->curvature();
    segment.transitionType = cantStation->transitionType();
    segment.cantGradient = cantStation->cantGradient();
    segment.speed = cantStation->speed();
    m_segments.append(segment);
  }
}

//
// AlignmentProcessor
//
void AlignmentProcessor::onStart(const xmlChar *name, const xmlChar **attrs)
{
  OdDAI::ModelPtr model = m_converter->model();
  m_inst = model->createEntityInstance("ifcalignment");
  OdIfc::Utils::assignGlobalId(m_inst);
  m_inst->putAttr("predefinedtype", (const char *)"NOTDEFINED");

  const xmlChar *alignmentName = m_converter->getAttr("name", attrs);
  if (alignmentName)
  {
    OdAnsiString name((const char *)alignmentName);
    m_inst->putAttr("name", name);
  }

  const xmlChar *staStart = m_converter->getAttr("staStart", attrs);
  if (staStart)
  {
    m_staStart = atof((const char *)staStart);
  }

  const xmlChar *length = m_converter->getAttr("length", attrs);
  if (length)
  {
    m_length = atof((const char *)length);
  }

  OdIfc::OdIfcEntityPtr site = m_converter->site();
  if (!site.isNull())
    m_converter->appendRelContainedInSpatialStructure(site, m_inst);
}

void AlignmentProcessor::onSubElement(const xmlChar *name, const xmlChar **attrs)
{
  OdString subElementName = (const char *)name;
  subElementName.makeLower();
  //if (subElementName == "start")
  //  processCartesianPoint(attrs);
}

namespace
{
  OdDAIObjectId findGeometricRepresentationContext(OdDAI::Model *model, const OdAnsiString &contextType)
  {
    OdDAI::Set<OdDAIObjectId> *contexts = model->getEntityExtent("ifcgeometricrepresentationcontext");
    if (contexts == nullptr || contexts->isNil())
      return OdDAIObjectId::kNull;

    const OdDAIObjectIds &arr = contexts->getArray();
    for (const auto &id : arr)
    {
      OdDAI::ApplicationInstancePtr inst = id.openObject();
      OdAnsiString _contextType;
      inst->getAttr("contexttype") >> _contextType;
      if (_contextType == contextType)
        return id;
    }
    return OdDAIObjectId::kNull;
  }

  OdIfc::OdIfcEntityPtr createSSHCantProfile(IfcProfileBuilder* profileBuilder, const OdDAIObjectId& profileDefId, double railHeadDistance, double cant)
  {
    return profileBuilder->createDerivedProfileDef("Cross section",
      profileDefId,
      OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(0. , cant / 2.), OdGeVector2d(1., cant / railHeadDistance).normalize(), OdGeVector2d(-cant / railHeadDistance,1.).normalize())->id()));
  }

  OdIfc::OdIfcEntityPtr createSSHCantAxis2Placement(OdDAI::Model* model, const OdDAIObjectId& basisCurveId, const OdDAIObjectId& axisZId,double distance)
  {
    OdDAI::ApplicationInstancePtr axis2PlacementLinear = model->createEntityInstance("ifcaxis2placementlinear");
    OdDAI::ApplicationInstancePtr pointByDistanceExpression = model->createEntityInstance("ifcpointbydistanceexpression");
    OdDAI::Select* select;
    pointByDistanceExpression->getAttr("distancealong") >> select;
    select->setDouble(distance);
    pointByDistanceExpression->putAttr("basiscurve", OdDAIObjectId(basisCurveId));

    axis2PlacementLinear->putAttr("location", model->appendEntityInstance(pointByDistanceExpression));
    axis2PlacementLinear->putAttr("axis", axisZId);

    model->appendEntityInstance(axis2PlacementLinear);

    return axis2PlacementLinear;
  }
}

void AlignmentProcessor::generateGeometry(const OdDAIObjectIds &alignmentNests)
{
  OdDAI::ModelPtr model = m_inst->owningModel();

  OdDAI::ApplicationInstancePtr representationCurve;
  OdAlignmentGeometryBuilder geometryBuilder(model);
  bool res = geometryBuilder.process(m_inst, representationCurve, 
    (m_converter->options().generateSweeps == tSectionedSolidHorizontalWithGradientCurve) ? false : true);

  if (res && !representationCurve.isNull())
  {
    switch (m_converter->options().generateSweeps)
    {
    case tFixedReferenceSweptAreaSolid:
      generateFixedReferenceSweptAreaSolid(representationCurve);
      break;
    case tSectionedSolidHorizontalWithGradientCurve:
      generateSectionSolidHorizontalGeometryWithGradientCurve(representationCurve);
      break;
    case tSectionedSolidHorizontalWithSegmentedReferenceCurve:
      generateSectionSolidHorizontalGeometryWithSegmentedReferenceCurve(representationCurve);
      break;
    default:
      break;
    }
  }
}

void AlignmentProcessor::generateFixedReferenceSweptAreaSolid(OdDAI::ApplicationInstance* representationCurve)
{
  OdDAI::ModelPtr model = representationCurve->owningModel();
  IfcProfileBuilderPtr profileBuilder = m_converter->createRepresentationBuilder(m_inst)->createProfileBuilder();

  OdDAIObjectIds items;
  OdIfc::OdIfcEntityPtr profileDef;

  OdDAI::ApplicationInstancePtr fixedReferenceSweptAreaSolid = model->createEntityInstance("ifcfixedreferencesweptareasolid");
  OdDAIObjectId fixedReferenceId = m_converter->dirX();

  if (!m_ifcAlignmentCant.isNull())
  {
    double railHeadDistance = OdDAI::Consts::OdNan;
    m_ifcAlignmentCant->getAttr("railheaddistance") >> railHeadDistance;

    profileDef = createRailsProfile(profileBuilder, railHeadDistance);
  }
  else
  {
    profileDef = profileBuilder->createRectangleProfileDef(IfcProfileBuilder::kAREA, "Pavement", 1., .2);
  }

  OdIfc::OdIfcEntityPtr curve = representationCurve;

  OdIfc::OdIfcCurvePtr pIfcCurve = OdIfc::OdIfcCurve::cast(OdIfc::OdIfcEntity::asCompound(m_converter->getIfcFile()->get(curve->id())));

  if (!pIfcCurve.isNull())
  {
    const OdGeCurve3d* pGeCurve = pIfcCurve->getGeCurve();
    OdGeInterval interval;

    pGeCurve->getInterval(interval);
    //      OdGeVector3d fixedReferenceVector = *OdIfc::OdIfcEntity::asVector3d(m_converter->getIfcFile()->get(fixedReferenceId));
    double distanceAlong = interval.lowerBound();
    const double upperBound = interval.upperBound();
    const OdUInt32 numOfSegs = odmax(50000, interval.length());
    const double step = interval.length() / numOfSegs;

    OdGePoint3dArray samplePoints;
    pGeCurve->getSamplePoints(numOfSegs, samplePoints);
    OdGeVector3d derivative = samplePoints.at(1) - samplePoints.at(0);
    derivative.normalize();

    //      OdGeVector3d v;
    OdGeVector3d fixedReferenceVector = -derivative.perpVector();
    //  v.x = derivatives.at(0).y;
    //  v.y = -derivatives.at(0).x;
    fixedReferenceVector.normalize();

    fixedReferenceId = m_converter->createDirection(fixedReferenceVector)->id();


    //      for (double dist = distanceAlong + step; OdLess(dist, upperBound); dist += step)
    for (int i = 2; i < numOfSegs; ++i)
    {
      OdGeVector3d derivative = samplePoints.at(i) - samplePoints.at(i - 1);
      derivative.normalize();
      if (fixedReferenceVector.isParallelTo(derivative, 1.e-1))
      {
        OdDAI::ApplicationInstancePtr fixedReferenceSweptAreaSolid = model->createEntityInstance("ifcfixedreferencesweptareasolid");
        fixedReferenceSweptAreaSolid->putAttr("sweptarea", OdDAIObjectId(profileDef->id()));
        fixedReferenceSweptAreaSolid->putAttr("directrix", OdDAIObjectId(representationCurve->id()));
        fixedReferenceSweptAreaSolid->putAttr("fixedreference", fixedReferenceId);

        OdDAI::Select* selectParam;
        fixedReferenceSweptAreaSolid->getAttr("startparam") >> selectParam;
        selectParam->setDouble(distanceAlong);

        distanceAlong = interval.lowerBound() + i * (interval.length() - 1) / numOfSegs;
        fixedReferenceSweptAreaSolid->getAttr("endparam") >> selectParam;
        selectParam->setDouble(distanceAlong);

        items.append(model->appendEntityInstance(fixedReferenceSweptAreaSolid));

        fixedReferenceVector = -derivative.perpVector();
        //      v.x = derivatives.at(0).y;
        //      v.y = -derivatives.at(0).x;
        fixedReferenceVector.normalize();
        fixedReferenceId = m_converter->createDirection(fixedReferenceVector)->id();
        //          fixedReferenceVector = *OdIfc::OdIfcEntity::asVector3d(m_converter->getIfcFile()->get(fixedReferenceId));
      }
    }
    if (distanceAlong != interval.lowerBound())
    {
      OdDAI::Select* selectParam;
      fixedReferenceSweptAreaSolid->getAttr("startparam") >> selectParam;
      selectParam->setDouble(distanceAlong);
    }
  }

  fixedReferenceSweptAreaSolid->putAttr("sweptarea", OdDAIObjectId(profileDef->id()));
  fixedReferenceSweptAreaSolid->putAttr("directrix", OdDAIObjectId(representationCurve->id()));
  fixedReferenceSweptAreaSolid->putAttr("fixedreference", fixedReferenceId);

  items.append(model->appendEntityInstance(fixedReferenceSweptAreaSolid));
  OdDAI::ApplicationInstancePtr shapeRepresentation = m_converter->createShapeRepresentation("Model", "Body", "SweptSolid");
  shapeRepresentation->putAttr("items", items);
  OdDAIObjectId idShapeRepresentation = model->appendEntityInstance(shapeRepresentation);

  OdDAI::ApplicationInstancePtr productDefinitionShape = model->createEntityInstance("ifcproductdefinitionshape");
  OdDAI::List<OdDAIObjectId>* representations = nullptr;
  productDefinitionShape->getAttr("representations") >> representations;
  representations->createEmpty();
  representations->putByIndex(0, idShapeRepresentation);
  OdDAIObjectId idProductDefinitionShape = model->appendEntityInstance(productDefinitionShape);

  m_inst->putAttr("representation", idProductDefinitionShape);
}

void AlignmentProcessor::generateSectionSolidHorizontalGeometryWithSegmentedReferenceCurve(OdDAI::ApplicationInstance* representationCurve)
{
  OdDAI::ModelPtr model = representationCurve->owningModel();
  IfcProfileBuilderPtr profileBuilder = m_converter->createRepresentationBuilder(m_inst)->createProfileBuilder();

  OdDAIObjectIds items;
  OdIfc::OdIfcEntityPtr profileDef;

  OdDAI::ApplicationInstancePtr sectionedSolidHorizontal = model->createEntityInstance("ifcsectionedsolidhorizontal");

  sectionedSolidHorizontal->putAttr("directrix", OdDAIObjectId(representationCurve->id()));
  sectionedSolidHorizontal->putAttr("fixedaxisvertical", true);
  OdDAI::OdDAIObjectIdList* crossSections = nullptr;
  OdDAI::OdDAIObjectIdList* crossSectionPositions = nullptr;
  sectionedSolidHorizontal->getAttr("crosssections") >> crossSections;
  sectionedSolidHorizontal->getAttr("crosssectionpositions") >> crossSectionPositions;
  crossSections->createEmpty();
  crossSectionPositions->createEmpty();

  OdIfc::OdIfcCurvePtr curveGeom = OdIfc::OdIfcCurve::cast(OdIfc::OdIfcEntity::asCompound(m_converter->getIfcFile()->get(representationCurve->id())));

  if (curveGeom.isNull())
  {
    ODA_ASSERT_ONCE(!"No geometry, so aborted!");
    return;
  }

  OdGeInterval curveInterval;
  curveGeom->getGeCurveCopy()->getInterval(curveInterval);

  if (!m_ifcAlignmentCant.isNull())
  {
    double railHeadDistance = OdDAI::Consts::OdNan;
    m_ifcAlignmentCant->getAttr("railheaddistance") >> railHeadDistance;

    profileDef = createRailsProfile(profileBuilder, railHeadDistance);


  }
  else
  {
    profileDef = profileBuilder->createRectangleProfileDef(IfcProfileBuilder::kAREA, "Pavement", 1., .2);
  }
  crossSections->addByIndex(crossSections->getMemberCount(), profileDef->id());
  crossSections->addByIndex(crossSections->getMemberCount(), profileDef->id());

  crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
    createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), curveInterval.lowerBound())->id());
  crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
    createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), curveInterval.upperBound())->id());

  items.append(model->appendEntityInstance(sectionedSolidHorizontal));
  OdDAI::ApplicationInstancePtr shapeRepresentation = m_converter->createShapeRepresentation("Model", "Body", "SweptSolid");
  shapeRepresentation->putAttr("items", items);
  OdDAIObjectId idShapeRepresentation = model->appendEntityInstance(shapeRepresentation);

  OdDAI::ApplicationInstancePtr productDefinitionShape = model->createEntityInstance("ifcproductdefinitionshape");
  OdDAI::List<OdDAIObjectId>* representations = nullptr;
  productDefinitionShape->getAttr("representations") >> representations;
  representations->createEmpty();
  representations->putByIndex(0, idShapeRepresentation);
  OdDAIObjectId idProductDefinitionShape = model->appendEntityInstance(productDefinitionShape);

  m_inst->putAttr("representation", idProductDefinitionShape);
}

void AlignmentProcessor::generateSectionSolidHorizontalGeometryWithGradientCurve(OdDAI::ApplicationInstance* representationCurve)
{
  OdDAI::ModelPtr model = representationCurve->owningModel();
  IfcProfileBuilderPtr profileBuilder = m_converter->createRepresentationBuilder(m_inst)->createProfileBuilder();

  OdDAIObjectIds items;
  OdIfc::OdIfcEntityPtr profileDef;

  OdIfc::OdIfcEntityPtr curve = representationCurve;

  OdDAI::ApplicationInstancePtr sectionedSolidHorizontal = model->createEntityInstance("ifcsectionedsolidhorizontal");
  sectionedSolidHorizontal->putAttr("directrix", OdDAIObjectId(representationCurve->id()));
  sectionedSolidHorizontal->putAttr("fixedaxisvertical", true);
  OdDAI::OdDAIObjectIdList* crossSections = nullptr;
  OdDAI::OdDAIObjectIdList* crossSectionPositions = nullptr;
  sectionedSolidHorizontal->getAttr("crosssections") >> crossSections;
  sectionedSolidHorizontal->getAttr("crosssectionpositions") >> crossSectionPositions;
  crossSections->createEmpty();
  crossSectionPositions->createEmpty();

  OdIfc::OdIfcCurvePtr curveGeom = OdIfc::OdIfcCurve::cast(OdIfc::OdIfcEntity::asCompound(m_converter->getIfcFile()->get(curve->id())));

  if (curveGeom.isNull())
  {
    ODA_ASSERT_ONCE(!"No geometry, so aborted!");
    return;
  }

  OdGeInterval curveInterval;
  curveGeom->getGeCurveCopy()->getInterval(curveInterval);

  if (!m_ifcAlignmentCant.isNull())
  {
    double railHeadDistance = OdDAI::Consts::OdNan;
    m_ifcAlignmentCant->getAttr("railheaddistance") >> railHeadDistance;

    profileDef = createRailsProfile(profileBuilder, railHeadDistance);

    OdDAIObjectIds segments;

    OdDAIObjectIds isNestedBy;
    if (m_ifcAlignmentCant->getAttr("isnestedby") >> isNestedBy && !isNestedBy.isEmpty())
    {
      OdDAI::ApplicationInstancePtr relNests = isNestedBy[0].openObject();
      if (!relNests.isNull())
      {
        relNests->getAttr("relatedobjects") >> segments;
      }
    }

    if (!segments.isEmpty())
    {
      OdIfc::OdIfcEntityPtr curve = representationCurve;

      for (const auto& idSegment : segments)
      {
        if (idSegment.isValid())
        {
          OdDAI::ApplicationInstancePtr alignmentSegment = idSegment.openObject();

          OdDAIObjectId idAlignmentCantSegment;
          alignmentSegment->getAttr("designparameters") >> idAlignmentCantSegment;
          if (idAlignmentCantSegment.isValid())
          {
            OdDAI::ApplicationInstancePtr alignmentCantSegment = idAlignmentCantSegment.openObject();
            //
            // Get semantic values
            //
            double startDistAlong;
            alignmentCantSegment->getAttr("startdistalong") >> startDistAlong;

            double horizontalLength;
            alignmentCantSegment->getAttr("horizontallength") >> horizontalLength;

            double startCantLeft;
            alignmentCantSegment->getAttr("startcantleft") >> startCantLeft;

            double endCantLeft;
            alignmentCantSegment->getAttr("endcantleft") >> endCantLeft;

            double startCantRight;
            alignmentCantSegment->getAttr("startcantright") >> startCantRight;

            double endCantRight;
            alignmentCantSegment->getAttr("endcantright") >> endCantRight;

            double smoothingLength;
            alignmentCantSegment->getAttr("smoothinglength") >> smoothingLength;

            OdAnsiString predefinedType;
            alignmentCantSegment->getAttr("predefinedtype") >> predefinedType;

            if (OdLess(startDistAlong, curveInterval.lowerBound(), RAILS_TOL))
              continue;

            if (crossSections->getMemberCount() == 0 && OdGreater(startDistAlong, curveInterval.lowerBound(), RAILS_TOL))
            {
              crossSections->addByIndex(crossSections->getMemberCount(),
                createSSHCantProfile(profileBuilder, profileDef->id(), railHeadDistance, 0)->id());

              crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
                createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), curveInterval.lowerBound())->id());
            }

            crossSections->addByIndex(crossSections->getMemberCount(),
              createSSHCantProfile(profileBuilder, profileDef->id(), railHeadDistance, startCantLeft + startCantRight)->id());

            crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
              createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), startDistAlong)->id());

            if (idSegment == segments.last())
            {
              crossSections->addByIndex(crossSections->getMemberCount(),
                createSSHCantProfile(profileBuilder, profileDef->id(), railHeadDistance, endCantLeft + endCantRight)->id());

              crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
                createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), startDistAlong + horizontalLength)->id());

              if (OdLess(startDistAlong + horizontalLength,curveInterval.upperBound(), RAILS_TOL))
              {
                crossSections->addByIndex(crossSections->getMemberCount(),
                  createSSHCantProfile(profileBuilder, profileDef->id(), railHeadDistance, 0)->id());

                crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
                  createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), curveInterval.upperBound())->id());
              }
            }
          }
          else
          {
            ODA_ASSERT_ONCE(idAlignmentCantSegment.isValid());
          }
        }
        else
        {
          ODA_ASSERT_ONCE(idSegment.isValid());
        }
      }
    }
    else
    {
      ODA_ASSERT(!segments.isEmpty());
      //        return OdDAI::ApplicationInstancePtr();
    }
  }
  else
  {
     profileDef = profileBuilder->createRectangleProfileDef(IfcProfileBuilder::kAREA, "Pavement", 1., .2);

     crossSections->addByIndex(crossSections->getMemberCount(), profileDef->id());
     crossSections->addByIndex(crossSections->getMemberCount(), profileDef->id());

     crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
       createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), curveInterval.lowerBound())->id());
     crossSectionPositions->addByIndex(crossSectionPositions->getMemberCount(),
       createSSHCantAxis2Placement(model, representationCurve->id(), m_converter->dirZ(), curveInterval.upperBound())->id());
  }

  items.append(model->appendEntityInstance(sectionedSolidHorizontal));
  OdDAI::ApplicationInstancePtr shapeRepresentation = m_converter->createShapeRepresentation("Model", "Body", "SweptSolid");
  shapeRepresentation->putAttr("items", items);
  OdDAIObjectId idShapeRepresentation = model->appendEntityInstance(shapeRepresentation);

  OdDAI::ApplicationInstancePtr productDefinitionShape = model->createEntityInstance("ifcproductdefinitionshape");
  OdDAI::List<OdDAIObjectId>* representations = nullptr;
  productDefinitionShape->getAttr("representations") >> representations;
  representations->createEmpty();
  representations->putByIndex(0, idShapeRepresentation);
  OdDAIObjectId idProductDefinitionShape = model->appendEntityInstance(productDefinitionShape);

  m_inst->putAttr("representation", idProductDefinitionShape);
}

OdIfc::OdIfcEntityPtr AlignmentProcessor::createRailsProfile(IfcProfileBuilder* profileBuilder, double railHeadDistance)
{
  double scale = 1e-3; // To meters
  OdIfc::OdIfcEntityPtr railProfile = profileBuilder->createAsymmetricIShapeProfileDef(
    IfcProfileBuilder::kAREA,
    "Rail Profile",
    m_converter->identity2D(),

    //
    // For R65/RP65 rail type:
    //

    // EXPLICIT
    /* bottomFlangeWidth */ 150. * scale,
    /* overallDepth */ 180. * scale,
    /* webThickness */ 20. * scale,
    /* bottomFlangeThickness */ 11.2 * scale,
    /* topFlangeWidth */ 75. * scale,

    // OPTIONAL
    /* bottomFlangeFilletRadius */ 25. * scale,
    /* topFlangeThickness */ 35.6 * scale,
    /* topFlangeFilletRadius */ 15. * scale,

    // Not used OPTIONAL
    /* bottomFlangeEdgeRadius */ 4. * scale,
    /* bottomFlangeSlope */ OdDAI::Consts::OdNan,
    /* topFlangeEdgeRadius */ 3. * scale
    /* topFlangeSlope */
  );

  OdIfc::OdIfcEntityPtr leftRailProfile = profileBuilder->createDerivedProfileDef("Left rail",
    OdDAIObjectId(railProfile->id()),
    OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(-railHeadDistance * 0.5, 0.))->id()));
  OdIfc::OdIfcEntityPtr rightRailProfile = profileBuilder->createDerivedProfileDef("Right rail",
    OdDAIObjectId(railProfile->id()),
    OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(railHeadDistance * 0.5, 0.))->id()));
  OdDAIObjectIds profiles;
  profiles.append(OdDAIObjectId(leftRailProfile->id()));
  profiles.append(OdDAIObjectId(rightRailProfile->id()));
  return profileBuilder->createCompositeProfileDef(IfcProfileBuilder::kAREA, "Rails", profiles);
}

void AlignmentProcessor::onEnd(const xmlChar *elementName)
{
  OdDAIObjectIds alignmentNests;
  ODA_ASSERT(!m_ifcAlignmentHorizontal.isNull());
  if (!m_ifcAlignmentHorizontal.isNull())
    alignmentNests.append(OdDAIObjectId(m_ifcAlignmentHorizontal->id()));
  if (!m_ifcAlignmentVertical.isNull())
    alignmentNests.append(OdDAIObjectId(m_ifcAlignmentVertical->id()));
  if (!m_ifcAlignmentCant.isNull())
    alignmentNests.append(OdDAIObjectId(m_ifcAlignmentCant->id()));

  OdDAI::ApplicationInstancePtr relNests = m_converter->addRelNests(m_inst, alignmentNests);
  relNests->setInverseCounterParts();

  if (m_converter->options().generateGeometry)
    generateGeometry(alignmentNests);
}

void AlignmentProcessor::onSubElementEnd(ElementProcessor *subProcessor)
{
  CoordGeomProcessor *coordGeom = dynamic_cast<CoordGeomProcessor*>(subProcessor);
  if (coordGeom)
  {
    m_ifcAlignmentHorizontal = coordGeom->alignmentHorizontal();
    //m_ifcAlignmentHorizontal->putAttr("startdistalong", m_staStart);
  }

  ProfileProcessor *profile = dynamic_cast<ProfileProcessor*>(subProcessor);
  if (profile)
  {
    m_ifcAlignmentVertical = profile->alignmentVertical();
  }

  CantProcessor *cant = dynamic_cast<CantProcessor*>(subProcessor);
  if (cant)
  {
    m_ifcAlignmentCant = cant->alignment2DCant();
  }
};

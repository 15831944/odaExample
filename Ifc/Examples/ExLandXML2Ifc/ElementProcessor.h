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

#ifndef _ELEMENTPROCESSOR_H_
#define _ELEMENTPROCESSOR_H_

#include "IfcExamplesCommon.h"
#include "IfcCore.h"

#include "OdaCommon.h"
#include "StaticRxObject.h"

#include <stack>

#include "libxml.h"
#include "include/libxml/xmlreader.h"
#include <libxml/parser.h>

/** \details
A base class for all elements of LandXML processors.
*/
class ElementProcessor
{
  friend class OdLandXML2IfcConverter;

protected:

  bool m_processed = false;
  OdLandXML2IfcConverter *m_converter;
  OdIfc::OdIfcEntityPtr m_inst;
  ElementProcessor *m_parent = nullptr;

public:

  ElementProcessor()
  {}

  OdIfc::OdIfcEntityPtr processCartesianPoint(const xmlChar **attrs);

  virtual ~ElementProcessor() {};

  void setParent(ElementProcessor *parent)
  {
    ODA_ASSERT(m_parent == nullptr);
    m_parent = parent;
  }

  ElementProcessor* parent() { return m_parent; }

  virtual const xmlChar* name() = 0;

  virtual void onStart(const xmlChar *name, const xmlChar **attrs) = 0;

  virtual void onEnd(const xmlChar *elementName)
  {
    //ODA_ASSERT(odStrICmpA((const char *)elementName, (const char *)name()) == 0);
  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs) {};
  virtual void onSubElementEnd(ElementProcessor *subProcessor) {};

  virtual void onCharactersProcess(const OdAnsiString &str) {};

  friend class OdLandXML2IfcConverter;
};

class ProjectProcessor : public ElementProcessor
{
protected:

  OdAnsiString m_name;
  OdAnsiString m_desc;
  OdAnsiString m_state;

public:

  virtual const xmlChar* name() { return (const xmlChar*)"project"; };

  const OdAnsiString& projectName() { return m_name; }
  const OdAnsiString& desc() { return m_desc; }
  const OdAnsiString& state() { return m_state; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    const xmlChar *projectName = m_converter->getAttr("name", attrs);
    if (projectName)
      m_name = (const char *)projectName;

    const xmlChar *desc = m_converter->getAttr("desc", attrs);
    if (desc)
      m_desc = (const char *)desc;

    const xmlChar *state = m_converter->getAttr("state", attrs);
    if (state)
      m_state = (const char *)state;
  }

  virtual void onEnd(const xmlChar *elementName)
  {
    OdDAI::ApplicationInstancePtr project = m_converter->project();
    project->putAttr("name", m_name);
    project->putAttr("description", m_desc);
    if (!m_state.isEmpty())
      project->putAttr("phase", m_state);
  }
};

class ComponentsProcessor : public ElementProcessor
{
  OdAnsiString m_componentsType;
  OdArray<double> m_components;
  OdAnsiString m_desc;

public:

  ComponentsProcessor(const OdAnsiString &componentsType)
    : m_componentsType(componentsType)
  {}

  const OdAnsiString& componentsType() { return m_componentsType; };

  const OdArray<double>& components() { return m_components; };

  virtual const xmlChar* name() { return (const xmlChar*)"components"; };

  const OdAnsiString& desc() { return m_desc; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    const xmlChar *desc = m_converter->getAttr("desc", attrs);
    if (desc)
      m_desc = (const char *)desc;
  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onCharactersProcess(const OdAnsiString &str)
  {
    if (m_processed)
      return;

    m_components.clear();

    OdAnsiString work = str;
    work.trimLeft();
    work.trimRight();

    int cur = 0;
    int newPos = 0;
    while (newPos > -1)
    {
      newPos = work.find(' ', cur);

      int len;
      if (newPos < 0)
        len = work.getLength() - cur - 1;
      else
        len = newPos - cur;

      OdAnsiString subStr = work.mid(cur, len);
      m_components.append(atof(subStr));
      cur = newPos + 1;
    }
    m_processed = true;
  }
};

class CircCurveProcessor : public ComponentsProcessor
{
protected:

  double m_length;
  double m_radius;

public:

  CircCurveProcessor(const OdAnsiString &componentsType)
    : ComponentsProcessor(componentsType)
  {}

  double length() { return m_length; }
  double radius() { return m_radius; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    const xmlChar *length = m_converter->getAttr("length", attrs);
    if (length)
      m_length = atof((const char *)length);

    const xmlChar *radius = m_converter->getAttr("radius", attrs);
    if (radius)
      m_radius = atof((const char *)radius);
  }

  virtual void onEnd(const xmlChar *elementName)
  {
    int breakpoint = 1;
  }
};

class SegmentProcessor : public ElementProcessor
{
  OdIfc::OdIfcEntityPtr m_horizontalSeg;
  OdGePoint2d m_start;
  OdGePoint2d m_end;
  OdGePoint2d m_center;
  OdGePoint2d m_pi;
  bool m_cw = true;

public:

  virtual const xmlChar* name() { return (const xmlChar*)"segment"; };

  OdIfc::OdIfcEntityPtr horizontalSegment() { return m_horizontalSeg; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    m_horizontalSeg = m_converter->model()->createEntityInstance("ifcalignmenthorizontalsegment");
    m_converter->model()->appendEntityInstance(m_horizontalSeg);
    
    OdAnsiString curveType;
    double startR, endR;
    startR = endR = 0.;
    if (odStrICmpA((const char*)name, "line") == 0)
      curveType = "LINE";
    else if (odStrICmpA((const char*)name, "spiral") == 0)
    {
      OdAnsiString radiusStart = (const char *)m_converter->getAttr("radiusStart", attrs);
      radiusStart.makeLower();
      if (!radiusStart.isEmpty() && radiusStart != "inf")
        startR = atof(radiusStart.c_str());

      OdAnsiString radiusEnd = (const char *)m_converter->getAttr("radiusEnd", attrs);
      radiusEnd.makeLower();
      if (!radiusEnd.isEmpty() && radiusEnd != "inf")
        endR = atof(radiusEnd.c_str());

      OdAnsiString rot = (const char*)m_converter->getAttr("rot", attrs);
      if (rot)
      {
        if (rot != "ccw")
        {
          startR = -startR;
          endR = -endR;
        }
      }

      curveType = (const char *)m_converter->getAttr("spiType", attrs);
      curveType.makeLower();
      if (curveType == "biquadraticparabola")
        curveType = "BIQUADRATICPARABOLA";
      else if (curveType == "bloss")
        curveType = "BLOSSCURVE";
      else if (curveType == "clothoid")
        curveType = "CLOTHOID";
      else if (curveType == "cosine")
        curveType = "COSINECURVE";
      else if (curveType == "cubicparabola")
        curveType = "CUBICSPIRAL";
      else if (curveType == "sinusoid")
        curveType = "SINECURVE";
      else
      {
        /*
        enumeration 	cubic
        enumeration 	revBiquadratic
        enumeration 	revBloss
        enumeration 	revCosine
        enumeration 	revSinusoid
        enumeration 	sineHalfWave
        enumeration 	japaneseCubic
        enumeration 	radioid
        enumeration 	weinerBogen */

        curveType.empty();
      }
    }
    else if (odStrICmpA((const char*)name, "curve") == 0)
    {
      const xmlChar *crvType = m_converter->getAttr("crvType", attrs);
      if (crvType == nullptr || odStrICmpA((const char*)crvType, "arc") == 0)
      {
        curveType = "CIRCULARARC";
        const xmlChar *val;
        val = m_converter->getAttr("radius", attrs);
        if (val)
        {
          double radius = atof((const char*)val);

          val = m_converter->getAttr("rot", attrs);
          OdAnsiString rot = (const char*)val;
          m_cw = rot != "ccw";
          startR = endR = m_cw ? -radius : radius;
        }
      }
      else
      {
        ODA_FAIL_M("Unsupported curve type");
      }
    }
    else
    {
      ODA_FAIL_M("Unsupported curve type");
    }

    if (!m_horizontalSeg.isNull())
    {
      const xmlChar *val = m_converter->getAttr("length", attrs);
      if (val)
        m_horizontalSeg->putAttr("segmentlength", atof((const char*)val));

      m_horizontalSeg->putAttr("startradiusofcurvature", startR);
      m_horizontalSeg->putAttr("endradiusofcurvature", endR);
      m_horizontalSeg->putAttr("predefinedtype", curveType);
    }
  }

  virtual void onEnd(const xmlChar *elementName)
  {
    ODA_ASSERT_ONCE(m_horizontalSeg.get());

    OdIfc::OdIfcEntityPtr start = m_converter->model()->createEntityInstance("ifccartesianpoint");
    OdArray<double> coordinates;
    coordinates.push_back(m_start.x); // Easting
    coordinates.push_back(m_start.y); // Northing
    // Third coordinate is 0. in files we have // Elevation
    start->putAttr("coordinates", coordinates);
    m_converter->model()->appendEntityInstance(start);

    OdGeVector2d dir;

    if (odStrICmpA((const char *)elementName, "line") == 0)
    {
      dir = m_end - m_start;
    }
    else
    if (odStrICmpA((const char *)elementName, "curve") == 0)
    {
      dir = (m_center - m_start).perpVector();
      if (!m_cw)
        dir = -dir;
    }
    else
    {
      dir = (m_pi - m_start);
      if (!m_cw)
        dir = -dir;
    }

    double startDirection = dir.angle();
    // double len = dir.length(); //
    m_horizontalSeg->putAttr("startdirection", startDirection);

    m_horizontalSeg->putAttr("startpoint", OdDAIObjectId(start->id()));
  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {
    //OdString subElementName = (const char *)name;
    //subElementName.makeLower();
    //if (subElementName == "start")
    //  processCartesianPoint(attrs);
  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor)
  {
    ComponentsProcessor *components = dynamic_cast<ComponentsProcessor*>(subProcessor);
    if (components)
    {
      if (components->componentsType() == "start")
      {
        m_start.set(components->components()[1] /* Easting */, components->components()[0] /* Northing */ );

        // The third component is always 0. in files we have
        ODA_ASSERT_ONCE(components->components().size() == 2 || (components->components().size() == 3 && OdEqual(components->components()[2], 0.)));
      }
      if (components->componentsType() == "end")
      {
        m_end.set(components->components()[1] /* Easting */, components->components()[0] /* Northing */);

        // The third component is always 0. in files we have
        ODA_ASSERT_ONCE(components->components().size() == 2 || (components->components().size() == 3 && OdEqual(components->components()[2], 0.)));
      }
      if (components->componentsType() == "pi")
      {
        m_pi.set(components->components()[1] /* Easting */, components->components()[0] /* Northing */);
      }
      if (components->componentsType() == "center")
      {
        m_center.set(components->components()[1] /* Easting */, components->components()[0] /* Northing */);
      }
    }
  };
};

/* \details
Vertical alignment processor.
*/
class ProfAlignProcessor : public ElementProcessor
{
public:

  enum PVIType {
    kStation = 0,
    kCircCurve = 1,
    kTransition = 2
  };

  struct PVI {

    PVIType type;
    OdAnsiString desc;

    double station;
    double elevation;

    double radius = 0.;
    double arcLength = 0.;
  };
  typedef OdArray<PVI> PVIArr;

protected:

  PVIArr m_pvis;
  OdAnsiString m_name;

public:

  

  virtual const xmlChar* name() { return (const xmlChar*)"profalign"; };

  const OdAnsiString& profileName() { return m_name; };

  const PVIArr& pvis() { return m_pvis; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    const char *profileName = (const char*)m_converter->getAttr("name", attrs);
    if (profileName)
      m_name = profileName;
  }

  //const OdAnsiString& getName() { return m_name; }

  virtual void onEnd(const xmlChar *elementName)
  {

  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor)
  {
    ComponentsProcessor *components = dynamic_cast<ComponentsProcessor*>(subProcessor);
    if (components)
    {
      PVI pvi;
      pvi.station = components->components()[0];
      pvi.elevation = components->components()[1];
      pvi.desc = components->desc();
      
      if (components->componentsType() == "pvi")
      {
        pvi.type = kStation;
      }
      else
      if (components->componentsType() == "circcurve")
      {
        CircCurveProcessor *circCurveProcessor = dynamic_cast<CircCurveProcessor*>(components);
        pvi.type = kCircCurve;
        pvi.radius = circCurveProcessor->radius();
        pvi.arcLength = circCurveProcessor->length();
      }
      m_pvis.append(pvi);
    }
  };
};

/* \details
  StaEquation
*/
class StaEquationProcessor : public ElementProcessor
{
protected:



public:

  virtual const xmlChar* name() { return (const xmlChar*)"staequation"; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
   
  }

  virtual void onEnd(const xmlChar *elementName)
  {

  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor)
  {

  }
};

/* \details
Vertical alignment processor.
*/
class ProfileProcessor : public ElementProcessor
{
  ProfAlignProcessor::PVIArr m_pvis;

  OdIfc::OdIfcEntityPtr m_alignmentVertical;

  OdAnsiString m_name;

public:

  virtual const xmlChar* name() { return (const xmlChar*)"profile"; };

  OdIfc::OdIfcEntityPtr alignmentVertical() { return m_alignmentVertical; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs);

  virtual void onEnd(const xmlChar *elementName);

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor)
  {
    ProfAlignProcessor *profAlign = dynamic_cast<ProfAlignProcessor*>(subProcessor);
    if (profAlign)
    {
      m_pvis = profAlign->pvis();
      m_name = profAlign->profileName();
    }
  };
};

/* \details
Horizontal alignment processor.
*/
class CoordGeomProcessor : public ElementProcessor
{
protected:

  OdAnsiString m_name;
  OdIfc::OdIfcEntityPtr m_alignmentHorizontal;

  OdDAIObjectIds m_segments;
  OdDAIObjectIds m_nested;

public:

  virtual const xmlChar* name() { return (const xmlChar*)"coordgeom"; };

  OdIfc::OdIfcEntityPtr alignmentHorizontal() { return m_alignmentHorizontal; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    m_alignmentHorizontal = m_converter->createRooted("ifcalignmenthorizontal");

    m_name = (const char *)m_converter->getAttr("name", attrs);

    m_alignmentHorizontal->putAttr("name", m_name);
  }

  virtual void onEnd(const xmlChar *elementName)
  {
    OdDAI::ApplicationInstancePtr relNests = m_converter->addRelNests(m_alignmentHorizontal, m_nested);
    relNests->setInverseCounterParts();
  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor)
  {
    SegmentProcessor *segment = dynamic_cast<SegmentProcessor*>(subProcessor);
    if (segment)
    {
      OdDAIObjectId id = (OdDAIObjectId)segment->horizontalSegment()->id();
      m_segments.append(id);
      m_nested.append(m_converter->createAlignmentSegment(id)->id());
    }
  }
};

//
// CantStation mapping to IfcAlignmentCantSegment
//
class CantStationProcessor : public ElementProcessor
{
protected:

  double m_station;
  double m_appliedCant;
  OdAnsiString m_curvature;
  OdAnsiString m_transitionType;
  double m_cantGradient;
  double m_speed;

  OdIfc::OdIfcEntityPtr m_alignment2DCantSegment;

public:

  virtual const xmlChar* name() { return (const xmlChar*)"cantstation"; };

  double station() { return m_station; }
  double appliedCant() { return m_appliedCant; }
  const OdAnsiString& curvature() { return m_curvature; }
  const OdAnsiString& transitionType() { return m_transitionType; }
  double cantGradient() { return m_cantGradient; }
  double speed() { return m_speed; }

  OdIfc::OdIfcEntityPtr alignment2DCantSegment() { return m_alignment2DCantSegment; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs);

};

class CantProcessor : public ElementProcessor
{
public:

  struct CantSegment {
    double station = 0.;
    double appliedCant = 0.;
    OdAnsiString curvature;
    OdAnsiString transitionType;
    double cantGradient = 0.;
    double speed = 0.;

    OdIfc::OdIfcEntityPtr m_alignmentCantSegment;
    OdDAIObjectId id;
  };
  typedef OdArray<CantSegment> CantSegmentArr;

protected:

  OdIfc::OdIfcEntityPtr m_alignmentCant;
  double m_gauge = 0.;
  CantSegmentArr m_segments;
  OdAnsiString m_name;
  OdAnsiString transitionName2Ifc(const char *landXMLName);

public:

  virtual const xmlChar* name() { return (const xmlChar*)"cant"; };

  OdIfc::OdIfcEntityPtr alignment2DCant() { return m_alignmentCant; }
  double gauge() { return m_gauge; }
  const OdAnsiString& cantName() { return m_name; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    OdAnsiString gauge = (const char *)m_converter->getAttr("gauge", attrs);
    if (gauge != "")
      m_gauge = atof(gauge);

    const char *cantName = (const char *)m_converter->getAttr("name", attrs);
    if (cantName)
      m_name = cantName;
  }

  virtual void onEnd(const xmlChar *elementName);

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {
    
  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor);
  
};

//
// Alignment
//
class AlignmentProcessor : public ElementProcessor
{
  OdIfc::OdIfcEntityPtr m_ifcAlignmentHorizontal;
  OdIfc::OdIfcEntityPtr m_ifcAlignmentVertical;
  OdIfc::OdIfcEntityPtr m_ifcAlignmentCant;

  double m_staStart = 0.;
  double m_length = 0.;

  void generateGeometry(const OdDAIObjectIds &alignmentNests);

  void generateFixedReferenceSweptAreaSolid(OdDAI::ApplicationInstance* representationCurve);
  void generateSectionSolidHorizontalGeometryWithSegmentedReferenceCurve(OdDAI::ApplicationInstance* representationCurve);
  void generateSectionSolidHorizontalGeometryWithGradientCurve(OdDAI::ApplicationInstance* representationCurve);
  OdIfc::OdIfcEntityPtr createRailsProfile(IfcProfileBuilder* profileBuilder, double railHeadDistance);

public:

  virtual const xmlChar* name() { return (const xmlChar*)"alignment"; };

  OdIfc::OdIfcEntityPtr alignmentHorizontal() { return m_ifcAlignmentHorizontal; }
  OdIfc::OdIfcEntityPtr alignmentVertical() { return m_ifcAlignmentVertical; }
  OdIfc::OdIfcEntityPtr alignmentCant() { return m_ifcAlignmentCant; }

  double staStart() { return m_staStart; }
  double length() { return m_length; }

  virtual void onStart(const xmlChar *name, const xmlChar **attrs);
  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs);
  virtual void onEnd(const xmlChar *elementName);
  virtual void onSubElementEnd(ElementProcessor *subProcessor);
};

//
// Alignments
//
class AlignmentsProcessor : public ElementProcessor
{
public:

  struct Alignment
  {
    double horizontalLength;
    OdIfc::OdIfcEntityPtr ifcAlignmentCurve;
    OdIfc::OdIfcEntityPtr ifcAlignmentHorizontal;
    OdIfc::OdIfcEntityPtr ifcAlignmentVertical;
    OdIfc::OdIfcEntityPtr ifcAlignmentCant;
  };
  typedef OdArray<Alignment> AlignmentArr;

private:

  AlignmentArr m_alignments;

public:

  virtual const xmlChar* name() { return (const xmlChar*)"alignments"; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onEnd(const xmlChar *elementName)
  {
    if (m_alignments.size() == 0)
      return;

    bool hasCants = false;
    for (auto &alignment : m_alignments)
    {
      if (!alignment.ifcAlignmentCant.isNull())
      {
        hasCants = true;
        break;
      }
    }

    if (hasCants == false)
      return;

    OdIfc::OdIfcEntityPtr ctx = m_converter->getGeometricRepresentationContext("Model");

    IfcRailwayBuilderPtr railwayBuilder = m_converter->appendRailway("Railway");
    OdIfc::OdIfcEntityPtr railway = railwayBuilder->railway();

    IfcRepresentationBuilderPtr pRB = m_converter->createRepresentationBuilder(railway);

    //
    // Create common rail profile for all railroad segments
    //
    double scale = 1e-3;
    OdIfc::OdIfcEntityPtr railProfile = pRB->createProfileBuilder()->createAsymmetricIShapeProfileDef(
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

    int ctr = 0;
    for (auto &alignment : m_alignments)
    {
      if (alignment.ifcAlignmentCant.isNull())
        continue; // Not a railroad alignment!

      OdAnsiString railName;
      railName.format("Path_%d", ++ctr);
      OdIfc::OdIfcEntityPtr rail = railwayBuilder->appendRail(railName, IfcRailwayBuilder::kRAIL);

      IfcRepresentationBuilderPtr pRB = m_converter->createRepresentationBuilder(rail);

      OdIfc::OdIfcEntityPtr inclinedReferenceSweptAreaSolid = pRB->createInclinedReferenceSweptAreaSolid(
        railProfile,
        OdIfc::OdIfcEntityPtr(),
        alignment.ifcAlignmentCurve,
        0, alignment.horizontalLength,
        true,
        alignment.ifcAlignmentCant
      );

      //
      // Append representaion for Rail1
      //
      OdIfc::OdIfcEntityPtr pSR = m_converter->model()->createEntityInstance("ifcshaperepresentation");
      pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(ctx->id()));
      OdAnsiString strBody("Body");
      OdAnsiString strType("SweptSolid");
      pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
      pSR->putAttr(OdIfc::kRepresentationType, strType);
      m_converter->appendId(pSR, OdIfc::kItems, OdDAIObjectId(inclinedReferenceSweptAreaSolid->id()));

      OdDAIObjectIds idsRepresentation;
      idsRepresentation.append(m_converter->model()->appendEntityInstance(pSR));

      auto productDefinitionShape = m_converter->model()->createEntityInstance("ifcproductdefinitionshape");
      productDefinitionShape->putAttr("representations", idsRepresentation);
      auto idProductDefinitionShape = m_converter->model()->appendEntityInstance(productDefinitionShape);

      rail->putAttr("representation", idProductDefinitionShape);
    }
  }

  virtual void onSubElementEnd(ElementProcessor *subProcessor)
  {
    AlignmentProcessor *alignment = dynamic_cast<AlignmentProcessor*>(subProcessor);
    if (alignment)
    {
      m_alignments.append({
        alignment->length(),
        alignment->alignmentHorizontal(),
        alignment->alignmentVertical(),
        alignment->alignmentCant()
      });
    }
  };
};

class FeatureProcessor : public ElementProcessor
{
public:

  virtual const xmlChar* name() { return (const xmlChar*)"feature"; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }
};

class PropertyProcessor : public ElementProcessor
{
public:

  virtual const xmlChar* name() { return (const xmlChar*)"property"; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }
};

class IfcAlignmentHorizontalSegmentProcessor : public ElementProcessor
{
public:

  virtual const xmlChar* name() { return (const xmlChar*)"coordgeom"; };

  virtual void onStart(const xmlChar *name, const xmlChar **attrs)
  {
    //m_inst = m_converter->model()->createEntityInstance("IfcAlignment2DCant");
    //m_converter->model()->appendEntityInstance(m_inst);
  }

  virtual void onSubElement(const xmlChar *name, const xmlChar **attrs)
  {

  }

  virtual void onEnd(const xmlChar *elementName)
  {
    ElementProcessor::onEnd(elementName);

    //OdIfc::OdIfcEntityPtr horizontalSegment = m_converter->createRooted("ifcalignmenthorizontalsegment");
    // TODO: How to get it to parent? horizontalSegment->putAttr("curvegeometry", (OdDAIObjectId)pInst->id());
  }
};

#endif // _ELEMENTPROCESSOR_H_

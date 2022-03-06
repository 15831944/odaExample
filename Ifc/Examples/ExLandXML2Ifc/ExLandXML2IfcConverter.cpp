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

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"
#include "OdPerfTimer.h"

#include "IfcExamplesCommon.h"
#include "IfcCore.h"
#include "IfcEntity.h"

#include "ExLandXML2IfcConverter.h"
#include "ElementProcessor.h"

void OdLandXML2IfcConverter::init(const OdLandXML2IfcConverterOptions &options)
{
  m_options = options;
}

ElementProcessor* OdLandXML2IfcConverter::currentProcessor()
{
  if (m_stack.size())
    return m_stack.top();
  return nullptr;
}

ElementProcessor* OdLandXML2IfcConverter::pushProcessor(const xmlChar *name)
{
  ElementProcessor *processor = nullptr;

  OdAnsiString elementName((const char *)name);
  elementName.makeLower();
  if (elementName == "alignments")
    processor = new AlignmentsProcessor();
  else
  if (elementName == "alignment")
    processor = new AlignmentProcessor();
  else
  if (elementName == "profile")
    processor = new ProfileProcessor();
  else
  if (elementName == "profalign")
    processor = new ProfAlignProcessor();
  else
  if (elementName == "coordgeom")
    processor = new CoordGeomProcessor();
  else
  if (elementName == "cant")
    processor = new CantProcessor();
  else
  if (elementName == "cantstation")
    processor = new CantStationProcessor();
  else
  if (elementName == "feature")
    processor = new FeatureProcessor();
  else
  if (elementName == "property")
    processor = new PropertyProcessor();
  else
  if (elementName == "staequation")
    processor = new StaEquationProcessor();
  else
  if (elementName == "line" ||
      elementName == "spiral" ||
      elementName == "curve" ||
      elementName == "chord")
    processor = new SegmentProcessor();
  else
  if (elementName == "start" ||
      elementName == "center" ||
      elementName == "end" ||
      elementName == "pi" ||
      elementName == "pvi")
    processor = new ComponentsProcessor(elementName);
  else
  if (elementName == "circcurve")
    processor = new CircCurveProcessor(elementName);
  else
  if (elementName == "project")
    processor = new ProjectProcessor();

  if (processor)
  {
    processor->m_converter = this;
    if (m_stack.size() > 0)
      processor->setParent(m_stack.top());
    m_stack.push(processor);
  }

  return processor;
}

void OdLandXML2IfcConverter::popProcessor(const xmlChar *name)
{
  ElementProcessor *processor = currentProcessor();
  if (processor)
  {
    processor->onEnd(name);

    m_stack.pop();

    ElementProcessor *parent = currentProcessor();
    if (parent)
      parent->onSubElementEnd(processor);

    delete processor;
  }
}

const xmlChar* OdLandXML2IfcConverter::getAttr(const char *attrName, const xmlChar **attrs)
{
  if (attrs == nullptr)
    return nullptr;

  const xmlChar *result = nullptr;

  const xmlChar *name = nullptr;
  const xmlChar *value = nullptr;

  const xmlChar **cursor = attrs;
  while (*cursor)
  {
    name = *cursor;
    ++cursor;
    value = *cursor;
    ++cursor;
    
    if (odStrICmpA((const char*)name, attrName) == 0)
    {
      result = value;
      break;
    }
  }

  return result;
}

OdDAI::ApplicationInstancePtr appendAsymmetricIShapeProfileDef(OdDAI::Model *model,

  const char *type, const char *name, OdDAI::ApplicationInstance *position,

  double bottomFlangeWidth,
  double overallDepth,
  double webThickness,
  double bottomFlangeThickness,
  double topFlangeWidth,

  double bottomFlangeFilletRadius = OdDAI::Consts::OdNan,
  double topFlangeThickness = OdDAI::Consts::OdNan,
  double topFlangeFilletRadius = OdDAI::Consts::OdNan,
  double bottomFlangeEdgeRadius = OdDAI::Consts::OdNan,
  double bottomFlangeSlope = OdDAI::Consts::OdNan,
  double topFlangeEdgeRadius = OdDAI::Consts::OdNan,
  double topFlangeSlope = OdDAI::Consts::OdNan
)
{
  OdDAI::ApplicationInstancePtr asymmetricIShapeProfileDef = model->createEntityInstance("IfcAsymmetricIShapeProfileDef");

  if (position)
    asymmetricIShapeProfileDef->putAttr("position", OdDAIObjectId(position->id()));

  asymmetricIShapeProfileDef->putAttr("profiletype", type);
  asymmetricIShapeProfileDef->putAttr("profilename", name);

  asymmetricIShapeProfileDef->putAttr("bottomflangewidth", bottomFlangeWidth);
  asymmetricIShapeProfileDef->putAttr("overalldepth", overallDepth);
  asymmetricIShapeProfileDef->putAttr("webthickness", webThickness);
  asymmetricIShapeProfileDef->putAttr("bottomflangethickness", bottomFlangeThickness);
  asymmetricIShapeProfileDef->putAttr("topflangewidth", topFlangeWidth);

  if (!OdDAI::Utils::isUnset(bottomFlangeFilletRadius))
    asymmetricIShapeProfileDef->putAttr("bottomflangefilletradius", bottomFlangeFilletRadius);
  if (!OdDAI::Utils::isUnset(topFlangeThickness))
    asymmetricIShapeProfileDef->putAttr("topflangethickness", topFlangeThickness);
  if (!OdDAI::Utils::isUnset(topFlangeFilletRadius))
    asymmetricIShapeProfileDef->putAttr("topflangefilletradius", topFlangeFilletRadius);
  if (!OdDAI::Utils::isUnset(bottomFlangeEdgeRadius))
    asymmetricIShapeProfileDef->putAttr("bottomflangeedgeradius", bottomFlangeEdgeRadius);
  if (!OdDAI::Utils::isUnset(bottomFlangeSlope))
    asymmetricIShapeProfileDef->putAttr("bottomflangeslope", bottomFlangeSlope);
  if (!OdDAI::Utils::isUnset(topFlangeEdgeRadius))
    asymmetricIShapeProfileDef->putAttr("topflangeedgeradius", topFlangeEdgeRadius);
  if (!OdDAI::Utils::isUnset(topFlangeSlope))
    asymmetricIShapeProfileDef->putAttr("topflangeslope", topFlangeSlope);

  model->appendEntityInstance(asymmetricIShapeProfileDef);
  return asymmetricIShapeProfileDef;
}

OdDAI::ApplicationInstancePtr OdLandXML2IfcConverter::railProfileDef()
{
  if (m_profileDef.isNull())
  {
    double toM = 1e-3;
    m_profileDef = appendAsymmetricIShapeProfileDef(m_model,
    
    "AREA", "Rail Profile", NULL,

      //
      // For R65/RP65 rail type:
      //

      // EXPLICIT
      /* bottomFlangeWidth */ toM * 150.,
      /* overallDepth */ toM * 180.,
      /* webThickness */ toM * 20.,
      /* bottomFlangeThickness */ toM * 11.2,
      /* topFlangeWidth */ toM * 75.,

      // OPTIONAL
      /* bottomFlangeFilletRadius */ toM * 25.,
      /* topFlangeThickness */ toM * 35.6,
      /* topFlangeFilletRadius */ toM * 15.,
      /* bottomFlangeEdgeRadius */ toM * 4.,
      /* bottomFlangeSlope */ OdDAI::Consts::OdNan, // Skip
      /* topFlangeEdgeRadius */ toM * 3.
      /* topFlangeSlope */ // Not used
    );
  }
  return m_profileDef;
}

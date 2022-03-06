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

#include "IfcExamplesCommon.h"
#include "IfcCore.h"

#include "ExIfcModelFiller.h"

#include "OdaCommon.h"
#include "StaticRxObject.h"

#include <stack>

#include "libxml.h"
#include "include/libxml/xmlreader.h"
#include <libxml/parser.h>

class ElementProcessor;

enum SweepsType
{
  tNoSweep,
  tFixedReferenceSweptAreaSolid,
  tSectionedSolidHorizontalWithGradientCurve,
  tSectionedSolidHorizontalWithSegmentedReferenceCurve
};

struct OdLandXML2IfcConverterOptions
{
  bool generateGeometry = true;
  SweepsType generateSweeps = tNoSweep;
};

class OdLandXML2IfcConverter : public ExIfcModelFiller
{
protected:

  OdIfcFilePtr m_pIfcFile;
  OdLandXML2IfcConverterOptions m_options;

  std::stack<ElementProcessor*> m_stack;

  OdDAI::ApplicationInstancePtr m_profileDef;

public:

  OdLandXML2IfcConverter(OdIfcFile *ifcFile)
    : ExIfcModelFiller(ifcFile->getModel(sdaiRW).get())
    , m_pIfcFile(ifcFile)
  {}

  void init(const OdLandXML2IfcConverterOptions &options);

  OdLandXML2IfcConverterOptions& options() { return m_options; }

  ElementProcessor* currentProcessor();

  ElementProcessor *pushProcessor(const xmlChar *name);

  void popProcessor(const xmlChar *name);

  const xmlChar* getAttr(const char *attrName, const xmlChar **attrs);

  OdDAI::ApplicationInstancePtr railProfileDef();

  OdIfcFile* getIfcFile() { return m_pIfcFile; }
};
typedef OdSharedPtr<OdLandXML2IfcConverter> OdLandXML2IfcConverterPtr;

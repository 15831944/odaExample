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
#pragma once
#include <OdAnsiString.h>
#include <RxValue.h>
#include <RxValueType.h>
#include <libxml/tree.h>
#include <OdIds.h>
#ifdef _MSC_VER
#pragma warning(disable : 26812)
#endif // _MSC_VER


struct ODIDS_DLLEXPORT OdXmlRestriction
{
  OdXmlRestriction();
  bool readXml(xmlNodePtr);
  void writeXml(xmlNodePtr) const;
  OdAnsiString base;
  OdRxValue minExclusive;
  OdRxValue minInclusive;
  OdRxValue maxExclusive;
  OdRxValue maxInclusive;
  OdRxValue totalDigits;
  OdRxValue fractionDigits;
  OdRxValue length;
  OdRxValue minLength;
  OdRxValue maxLength;
  OdAnsiStringArray enumeration;
  enum WhiteSpace {
    UNDEFINED, PRESERVE, REPLACE, COLLAPSE
  } whiteSpace;
  OdAnsiString pattern;
  bool operator==(const OdXmlRestriction&) const;
  bool operator!=(const OdXmlRestriction& other) const { return !(*this == other); }
};

typedef OdArray<OdXmlRestriction> OdXmlRestrictionArray;

ODRX_DECLARE_VALUE_TYPE(OdXmlRestriction, ODIDS_DLLEXPORT)
ODRX_DECLARE_VALUE_TYPE(OdXmlRestrictionArray, ODIDS_DLLEXPORT)

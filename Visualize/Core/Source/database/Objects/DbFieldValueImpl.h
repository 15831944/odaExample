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

#ifndef _ODDBFIELDVALUEIMPL_INCLUDED_
#define _ODDBFIELDVALUEIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "OdArray.h"
#include "Ge/GePoint3d.h"
#include "FieldVariant.h"
#include "OdValue.h"
/*
typedef OdUInt64 FldDate;

class OdFieldValueImpl : public OdFieldVariant
{
public:
  enum PathNameFormat 
  {
    kPath = 1,
    kFileName = 2, 
    kExtension = 4
  };
  static void formatFileName(OdString&, const OdString& format);
  enum Case
  {
    kNone = 0,
    kUpperCase = 1,
    kLowerCase = 2,
    kFirstCapital = 3,
    kTitleCase = 4
  };
  static void formatStringCase(OdString&, const OdString& format);
  static void formatBytes(OdString&, const OdString& format, OdInt32);
  static void formatBool(OdString& pszValue, const OdString& format, bool);
  static bool formatL(OdString& pszValue, const OdString& format, double d);
  static bool formatA(OdString& pszValue, const OdString& format, double d);
  enum CoordsIncluded
  {
    kXIncluded = 1,
    kYIncluded = 2, 
    kZIncluded = 4
  };
  static bool formatPoint(OdString& pszValue, const OdString& format, const OdGePoint3d& pt);

  OdValue::DataType m_dataType;
  OdFieldValueImpl();
};
*/
#endif // _ODDBFIELDVALUEIMPL_INCLUDED_

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
#include "tviutils.h"

QString toQString(const OdString& sStr)
{
  std::wstring wstr((wchar_t*)sStr.c_str());
  QString qsStr(QString::fromStdWString(wstr));
  return qsStr;
}

OdString toOdString(const QString& sStr)
{
  //std::wstring wstr(sStr.toStdWString());
  wchar_t* pChars = new wchar_t[ sStr.length() + 1 ];
  sStr.toWCharArray( pChars );
  pChars[ sStr.length() ] = 0;
  OdString odsStr( pChars );
  delete[] pChars;
  return odsStr;
}

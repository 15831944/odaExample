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


#ifndef _OD_DWGR24FILELOADER_H_INCLUDED_
#define _OD_DWGR24FILELOADER_H_INCLUDED_

#include "DwgR18FileLoader.h"

class DBIO_EXPORT OdDwgR24FileLoader : public OdDwgR18FileLoader
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgR24FileLoader);
  OdDwgR24FileLoader();

protected:
  // DbFilerController overridden
  OdDbObjectPtr loadObject(OdUInt64 offset);
// ODA_MT_DBIO_BEGIN
  OdResult loadObject(OdDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId);
// ODA_MT_DBIO_END

  // OdDwgFileController overridden
  OdString rdString();
  OdString rdString32();

  // OdDwgFileLoader overridden
  void loadHeader();
  void loadClasses();
  void loadObjFreeSpace();

  // OdDwgR18FileLoader overridden
  void loadAppInfo();
  void loadAppInfoHistory();
  void loadRevHistory();
};

#endif // _OD_DWGR24FILELOADER_H_INCLUDED_

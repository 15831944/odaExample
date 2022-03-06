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

#ifndef _OD_DWGR21FILELOADER_H_INCLUDED_
#define _OD_DWGR21FILELOADER_H_INCLUDED_

#include "DwgFileLoader.h"
#include "DwgR21Controller.h"
#include "DwgStreams.h"

//----------------------------------------------------------
//
// OdTvDwgR21FileLoader
//
//----------------------------------------------------------
class OdTvDwgR21FileLoader : public OdTvDwgFileLoader,
                           public OdTvDwgR21FileController
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgR21FileLoader);
  OdTvDwgR21FileLoader();

  // OdTvDwgFileLoader overridden
  void loadFileHeader();
  void getVbaProjectData(OdUInt32 size, OdBinaryData& binaryData);

  // OdTvDbFilerController overridden
  OdTvDbDatabasePtr loadDbHeader(OdTvDbHostAppServices* apps);

private:
  // Load R21 system data
  void loadMetadata();
  void loadPagesMap();
  void loadSectionsMap();

  void loadAppInfo();
  void loadRevHistory();

  // OdTvDwgFileController overridden
  OdString rdString();
  OdString rdString32();

  // DbFilerController overridden
  OdTvDbObjectPtr loadObject(OdUInt64 offset);
  virtual void setPassword(const OdPassword& pass){OdTvDwgR21FileController::setPassword(pass);}
protected:
  OdStreamBufPtr m_pObjectData;

// ODA_MT_DBIO_BEGIN
public:
  class R21MTContext : public MTContext
  {
  public:
    OdArray<OdBinaryData> m_buffs0;
    OdArray<OdBinaryData> m_buffs1;
    OdArray<OdTvDwgR21Compressor> m_compressors;
  };
protected:
  // OdTvDwgFileLoader overridden
  OdApcAtomPtr beginMTLoading(int threadsCount, OdTvDbObjectIterator* pObjs = 0, OdMTLoadReactor* pInterruptFlag = 0) ODRX_OVERRIDE;
  OdResult loadObject(OdTvDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId);
// ODA_MT_DBIO_END
};

#endif // _OD_DWGR21FILELOADER_H_INCLUDED_

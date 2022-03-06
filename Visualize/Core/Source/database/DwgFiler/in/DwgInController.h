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

// DwgInController.h: interface for the OdTvDwgInController class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OD_DWGINCONTROLLER_H_INCLUDED_
#define _OD_DWGINCONTROLLER_H_INCLUDED_

#include "DwgFileController.h"
#include "DbSystemInternals.h"


//
// Load R13..R15 sections map
// (used for reading from raw controller stream and dwg stream)
//
template<class T>
OdUInt32 loadSectionsMap(T* pIo, OdTvDwgFileSectionsInfo& secInfo)
{
  ODA_TRACE0("-----------------------------------\nRead File Sections:\n");
  OdUInt32 nSections = pIo->rdInt32();
  OdUInt32 n = nSections;
  while(n--)
  {
    OdUInt8 nSecId = pIo->rdUInt8();
    OdUInt32 nAddr = pIo->rdInt32();
    OdUInt32 nSize = pIo->rdInt32();
    ODA_TRACE2("%08X:[%08X]: ", nAddr, nSize);
    switch (nSecId)
    {
      case 0:
        secInfo.m_HeaderAddr = nAddr;
        secInfo.m_HeaderSize = nSize;
				ODA_TRACE0("drawing header\n");
        break;
      case 1:
        secInfo.m_ClassesAddr = nAddr;
        secInfo.m_ClassesSize = nSize;
				ODA_TRACE0("classes\n");
        break;
      case 2:
        secInfo.m_HandlesAddr = nAddr;
        secInfo.m_HandlesSize = nSize;
				ODA_TRACE0("Handles\n");
        break;
      case 3:
        secInfo.m_ObjFreeSpaceAddr = nAddr;
        secInfo.m_ObjFreeSpaceSize = nSize;
				ODA_TRACE0("ObjFreeSpace\n");
        break;
      case 4:
        secInfo.m_TemplateAddr = nAddr;
        secInfo.m_TemplateSize = nSize;
				ODA_TRACE0("Template\n");
        break;
      case 5:
				secInfo.m_AuxHeaderAddr = nAddr;
				secInfo.m_AuxHeaderSize = nSize;
				ODA_TRACE0("AuxHeader\n");
        break;
      default:
				ODA_TRACE0("unknown\n");
        ODA_FAIL();
        break;
    }
  }
  ODA_TRACE0("-----------------------------------\n");
  return nSections;
}

class OdTvDwgStream;

//
// Support funcs
//
void rdHandleRecord(OdTvDbDwgFiler& io, OdUInt8& nKey, OdUInt64& nHandle);
void correctRootDictionary(OdTvDbDatabase* pDatabase);

class OdTvDbHeaderLoadInfo
{
public:
  void loadR14Dimblk(OdTvDbDatabase* pDb);
  OdString m_strBlk;
  OdString m_strBlk1;
  OdString m_strBlk2;
};

//
//
//
class DBIO_EXPORT OdTvDwgInController : public OdTvDwgFileController
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgInController);
  OdTvDwgInController();

  virtual void openR(OdStreamBuf* pOpenedIo);
  virtual void loadPreviewImg(OdThumbnailImage* pPreview);
  virtual void getPreviewImg(OdThumbnailImage* pPreview);

protected:
  OdBinaryData m_buffer;
  void loadBitBuffer(OdInt32 nLength);

  int rdHandleOffset(OdInt64& nRes);
  int rdMapOffset(OdInt32 &nRes);
  OdResult turnToOriginalObject(OdTvDbObject* pProxyObj);

  OdTvDbHeaderLoadInfo m_LoadInfo;
};

#endif // _OD_DWGINCONTROLLER_H_INCLUDED_

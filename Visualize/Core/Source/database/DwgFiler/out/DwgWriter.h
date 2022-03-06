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


#ifndef _OD_DWGFILEWRITER_H_INCLUDED_
#define _OD_DWGFILEWRITER_H_INCLUDED_

#define  STL_USING_MAP
#include "OdaSTL.h"

#include "DwgFileController.h"
#include "DwgStreams.h"
#include "ObjectDwgOutStream.h"
#include "OdArray.h"
#include "DbTypedId.h"
#include "DbDwgClassMap.h"
#include "DbSecurity.h"
#include "OdLinkedArray.h"
#include "DbProxyObject.h"
#include "DbProxyEntity.h"

template<class T>
void writeSections(T* pIo, OdTvDwgFileSectionsInfo& secInfo)
{
	// writing section map...
	pIo->wrInt32(secInfo.getSectionCount());
	ODA_TRACE0("-----------------------------------\nWrite File Sections:\n");
	if(secInfo.m_HeaderSize)
	{
		pIo->wrUInt8(0);
		pIo->wrInt32(secInfo.m_HeaderAddr);
		pIo->wrInt32(secInfo.m_HeaderSize);
		ODA_TRACE2("%08X:[%08X]: drawing header\n", secInfo.m_HeaderAddr, secInfo.m_HeaderSize);
	}
	if(secInfo.m_ClassesSize)
	{
		pIo->wrUInt8(1);
		pIo->wrInt32(secInfo.m_ClassesAddr);
		pIo->wrInt32(secInfo.m_ClassesSize);
		ODA_TRACE2("%08X:[%08X]: classes\n", secInfo.m_ClassesAddr, secInfo.m_ClassesSize);
	}
	if(secInfo.m_HandlesSize)
	{
		pIo->wrUInt8(2);
		pIo->wrInt32(secInfo.m_HandlesAddr);
		pIo->wrInt32(secInfo.m_HandlesSize);
		ODA_TRACE2("%08X:[%08X]: object map\n", secInfo.m_HandlesAddr, secInfo.m_HandlesSize);
	}
	if(secInfo.m_ObjFreeSpaceSize)
	{
		pIo->wrUInt8(3);
		pIo->wrInt32(secInfo.m_ObjFreeSpaceAddr);
		pIo->wrInt32(secInfo.m_ObjFreeSpaceSize);
		ODA_TRACE2("%08X:[%08X]: IDunno\n", secInfo.m_ObjFreeSpaceAddr, secInfo.m_ObjFreeSpaceSize);
	}
	if(secInfo.m_TemplateSize)
	{
		pIo->wrUInt8(4);
		pIo->wrInt32(secInfo.m_TemplateAddr);
		pIo->wrInt32(secInfo.m_TemplateSize);
		ODA_TRACE2("%08X:[%08X]: Template\n", secInfo.m_TemplateAddr, secInfo.m_TemplateSize);
	}
	if(secInfo.m_AuxHeaderSize)
	{
		pIo->wrUInt8(5);
		pIo->wrInt32(secInfo.m_AuxHeaderAddr);
		pIo->wrInt32(secInfo.m_AuxHeaderSize);
		ODA_TRACE2("%08X:[%08X]: Section5\n", secInfo.m_AuxHeaderAddr, secInfo.m_AuxHeaderSize);
	}
	ODA_TRACE0("-----------------------------------\n");
}

/**/
class DBIO_EXPORT OdTvDwgFileWriter : public OdTvDwgFileController
{
  typedef std::map<OdDbHandle, OdUInt64>  ObjectMap;
protected:
  class AutoCloser;
  friend class AutoCloser;
  class AutoCloser
  {
    OdTvDwgFileWriter &m_p;
    AutoCloser();
  public:
    AutoCloser(OdTvDwgFileWriter &p, bool bSeparateIds) : m_p(p) 
    {
      m_p.openBitStream(bSeparateIds);
    }
    ~AutoCloser() {
      m_p.closeBitStream();
    }
  };

public:
  ODRX_DECLARE_MEMBERS(OdTvDwgFileWriter);

	OdTvDwgFileWriter();
	virtual ~OdTvDwgFileWriter();

  virtual void writeDatabase(OdTvDbDatabase* );
//  void openW(OdStreamBuf* pOpenedIo, OdThumbnailImage* /*pImg*/);

  OdTvDbObjectPtr loadObject(OdUInt64) { ODA_FAIL(); return OdTvDbObjectPtr(); }

  static inline OdUInt16 dwgType(const OdRxClass* pClass)
  {
    OdUInt16 res = ::odTvDbDwgClassMap().dwgType(pClass);
    if(!res) {
      if(pClass==OdTvDbProxyObject::desc())
        res = OdUInt16(499);
      else if(pClass==OdTvDbProxyEntity::desc())
        res = OdUInt16(498);
    }
    return res;
  }

protected:
  void UpdateInt32(OdUInt64& offset, OdUInt32 nVal);
  void wrAuxHeader();
  void wrPreviewImg(OdUInt32 offset = 0);
  void wrHeader();
  void wrClasses();
  void wrObjFreeSpace(OdUInt64 freeSpaceSize);
  void wrTemplate();
  void wrObjects();
  void wrHandles();
  void wrHandlesSection(const OdUInt8* buff, OdUInt32 nSecSize);
  void wrFileHeader();
  void wrSecondFileHeader();

  void wrFileDepList();
  void wrSummaryInfo();

  inline void saveObject(OdTvDwgFileSplitStream* pFiler);
  
  void wrObjectsIncSave();

protected:
  virtual void openBitStream(bool bSeparateIds);
  virtual void closeBitStream();
  virtual OdTvDwgFileSplitStream* bitStream();
  OdStaticRxObject<OdTvDwgFileSplitStream> m_dwgFiler;
  OdBinaryData m_dataBuffer;
  OdBinaryData m_idsBuffer;

  ObjectMap    m_Handles;  
  OdLinkedArray<OdTvDbObjectId> m_IdsOfObjectsToWrite;

private:

  OdTvDbObject*   m_pObj;  

  OdUInt16 getDwgType(const OdRxClass* pClass);
};

typedef OdSmartPtr<OdTvDwgFileWriter> OdTvDwgWriterPtr;

extern "C" int cmpMapEntries(const void* p1, const void* p2);

#endif // _OD_DWGFILEWRITER_H_INCLUDED_


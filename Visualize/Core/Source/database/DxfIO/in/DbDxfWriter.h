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

// OdTvDbDxfWriter.h

#ifndef DXFWRITER_INCLUDED
#define DXFWRITER_INCLUDED

#include "DbFilerController.h"


class OdTvDbDxfWriter : public OdTvDbFilerController
{
private:
  OdSmartPtr<OdTvDbDxfFiler>  m_pFiler;

  OdTvDbObjectIdArray         m_objectsToWrite;

protected:
  OdTvDbDxfWriter();

  void writeHeader();
  void writeClasses();
  void writeTables();
  void writeBlocks();
  void writeEntities();
  void writeObjects();
  void writeThumbnailimage();
  void writeDsData();

public:
  ODRX_DECLARE_MEMBERS(OdTvDbDxfWriter);

  virtual void setFiler(OdTvDbDxfFiler* pFiler);

  void setStream(OdStreamBuf* pInput) { m_pStream = pInput; }

  void writeDatabase(OdTvDbDatabase *);

  OdTvDbObjectPtr loadObject(OdUInt64) { ODA_FAIL(); return OdTvDbObjectPtr(); }

  void addObjectToWrite(OdTvDbObjectId id)
  {
    m_objectsToWrite.append(id);
  }
};

typedef OdSmartPtr<OdTvDbDxfWriter> OdTvDbDxfWriterPtr;

#endif  // DXFWRITER_INCLUDED

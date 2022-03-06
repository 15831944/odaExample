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

// OdDbDxfWriter.h

#ifndef DXFWRITER_INCLUDED
#define DXFWRITER_INCLUDED

#include "DbFilerController.h"


class OdDbDxfWriter : public OdDbFilerController
{
private:
  OdSmartPtr<OdDbDxfFiler>  m_pFiler;

  OdDbObjectIdArray         m_objectsToWrite;

protected:
  OdDbDxfWriter();

  void writeHeader();
  void writeClasses();
  void writeTables();
  void writeBlocks();
  void writeEntities();
  void writeObjects();
  void writeThumbnailimage();
  void writeDsData();

public:
  ODRX_DECLARE_MEMBERS(OdDbDxfWriter);

  virtual void setFiler(OdDbDxfFiler* pFiler);

  void setStream(OdStreamBuf* pInput) { m_pStream = pInput; }

  void writeDatabase(OdDbDatabase *);

  OdDbObjectPtr loadObject(OdUInt64) { ODA_FAIL(); return OdDbObjectPtr(); }

  void addObjectToWrite(OdDbObjectId id)
  {
    m_objectsToWrite.append(id);
  }
};

typedef OdSmartPtr<OdDbDxfWriter> OdDbDxfWriterPtr;

#endif  // DXFWRITER_INCLUDED

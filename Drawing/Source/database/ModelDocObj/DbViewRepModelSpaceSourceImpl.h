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

#ifndef _ODDBVIEWREPMODELSPACESOURCEIMPL_INCLUDED_
#define _ODDBVIEWREPMODELSPACESOURCEIMPL_INCLUDED_

#include "DbViewRepModelSpaceSource.h"
#include "DbObjectImpl.h"
#include "DbViewRepSourceImpl.h"
#include "Ge/GeMatrix3d.h"
#include "UInt8Array.h"

struct ViewRepModelSpaceObjectRef
{
  OdInt32 m_unknown3;
  OdDbHandle m_handle;
  OdDbSoftPointerId m_objId;
  OdDbSoftPointerId m_objId2;
};

struct ViewRepModelSpaceObject1
{
  OdInt32 m_unknown1;
  OdInt32 m_unknown2;

  //OdInt32 m_type;
  //OdInt32 m_unknown3;
  //OdDbHandle m_handle;
  //OdDbSoftPointerId m_objId;
  //OdDbSoftPointerId m_objId2;
  OdArray<ViewRepModelSpaceObjectRef> m_UnknownRefs;

  OdInt32 m_unknown4;

  OdGeMatrix3d m_transform;
};

struct ViewRepModelSpaceObject2
{
  OdInt32 m_unknown;
  OdDbHandle m_handle;

  OdInt32 m_unknown2;
  OdInt16 m_unknown3;
  OdInt16 m_unknown4;

  OdUInt8Array m_unknownBlock;
  OdDbObjectId m_objId;
  OdDbObjectId m_objId2;
};

struct ViewRepModelSpaceObject3
{
  OdInt32 m_unknown;
  OdDbObjectId m_objId;
  OdString m_path; // .\Staircase.dwg

  OdInt32 m_unknown2;
  OdInt16 m_unknown3;
  OdInt16 m_unknown4;

  OdUInt8Array m_unknownBlock;
};

class OdDbViewRepModelSpaceSourceImpl : public OdDbViewRepSourceImpl 
{
private:
  friend class OdDbViewRepModelSpaceSource;

  static OdDbViewRepModelSpaceSourceImpl* getImpl(const OdDbViewRepModelSpaceSource* pObj)
  { 
    return (OdDbViewRepModelSpaceSourceImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbViewRepModelSpaceSourceImpl();

  // OdDbObjectImpl methods
  virtual void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdUInt16 m_ver; // 0 1
  OdArray<ViewRepModelSpaceObject1> m_unknownObjects;
  OdArray<ViewRepModelSpaceObject2> m_unknownObjects2;
  OdArray<ViewRepModelSpaceObject3> m_unknownObjects3;
  // TODO move upper data into OdDbViewRepModelSpaceBodyOccurrenceSnapshot
  // and invoke serialization for it via next member
  // OdSmartPtr<OdDbViewRepModelSpaceBodyOccurrenceSnapshot m_pSnapshot;

  OdArray<OdDbObjectId> m_viewRepModelSpaceViewSelSetIds;
};

#endif //_ODDBVIEWREPMODELSPACESOURCEIMPL_INCLUDED_

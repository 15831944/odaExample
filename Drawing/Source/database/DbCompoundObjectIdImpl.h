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

#ifndef ODDBCOMPOUNDOBJECTIDIMPL_H_INCLUDED
#define ODDBCOMPOUNDOBJECTIDIMPL_H_INCLUDED


#include "DbCompoundObjectId.h"


class DBENT_EXPORT OdDbCompoundObjectIdImpl : public OdRxObject
{
public:
  ODRX_USING_HEAP_OPERATORS(OdRxObject);
  ODRX_DECLARE_MEMBERS(OdDbCompoundObjectIdImpl);
  virtual bool equal(const OdDbCompoundObjectIdImpl&) const = 0;
  virtual OdDbObjectId topId() const = 0;
  virtual OdDbObjectId leafId() const = 0;
  virtual bool isSimpleObjectId() const = 0;
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler) = 0;
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const = 0;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler) = 0;
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const = 0;
  virtual void set(const OdDbObjectId& id, const OdDbObjectIdArray& path, OdDbDatabase* pHostDatabase) = 0;
  virtual void set(const OdDbObjectId& idObj, OdDbDatabase* pHostDatabase) = 0;
  virtual void set(const OdDbCompoundObjectIdImpl& idComp, OdDbDatabase* pHostDatabase) = 0;
  virtual void getFullPath(OdDbObjectIdArray& fullPath) const = 0;
  virtual void getPath(OdDbObjectIdArray& path) const = 0;
  virtual void setFullPath(const OdDbObjectIdArray& fullPath, OdDbDatabase* pHostDatabase) = 0;
  virtual bool remap(const OdDbIdMapping& idMap) = 0;
  virtual void getTransform(OdGeMatrix3d& trans) const = 0;
};

class DBENT_EXPORT OdDbImpBlockRefPathObjectId : public OdDbCompoundObjectIdImpl
{
public:
  ODRX_DECLARE_MEMBERS(OdDbImpBlockRefPathObjectId);

  OdDbImpBlockRefPathObjectId();
  virtual ~OdDbImpBlockRefPathObjectId();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  virtual OdDbObjectId topId() const;
  virtual OdDbObjectId leafId() const;
  virtual void set(const OdDbObjectId& id, const OdDbObjectIdArray& path, OdDbDatabase* pHostDatabase);
  virtual void set(const OdDbObjectId& idObj, OdDbDatabase* pHostDatabase);
  virtual void set(const OdDbCompoundObjectIdImpl& idComp, OdDbDatabase* pHostDatabase);
  virtual void getFullPath(OdDbObjectIdArray& fullPath) const;
  virtual void getPath(OdDbObjectIdArray& path) const;
  virtual void setFullPath(const OdDbObjectIdArray& fullPath, OdDbDatabase* pHostDatabase);
  virtual bool remap(const OdDbIdMapping& idMap);
  virtual void getTransform(OdGeMatrix3d& trans) const;
  virtual bool equal(const OdDbCompoundObjectIdImpl& idComp) const
  {
    return m_path == ((OdDbImpBlockRefPathObjectId&)idComp).m_path;
  }
  virtual bool isSimpleObjectId() const
  {
    return m_path.size() < 2;
  }

protected:
  struct BlockRefPathRecord
  {
    OdInt8 m_UnkFlag0;
    OdInt8 m_XrefFlags;
    OdDbHandle m_handle;  // If XRefFlags == 2 handle of entity in XRef database
    OdDbObjectId m_id;    // If XretFlags == 1 Entity ObjectId
                          // In case XRefFlags == 2 Id of XRef database BlockTableRecord in host database
                         
    bool operator !=(const BlockRefPathRecord& other) const
    {
      return other.m_id != m_id || other.m_handle != m_handle || other.m_UnkFlag0 != m_UnkFlag0 || other.m_XrefFlags != m_XrefFlags;
    }
    OdDbObjectId getId() const;
  };
  OdArray<BlockRefPathRecord, OdMemoryAllocator<BlockRefPathRecord> > m_path;
};


/////////////////////////////////////////////////////////////////////////////////////////////
class OdDbParentTransformOfChildPEForBlkRef : public OdDbParentTransformOfChildPE
{
//  ODRX_DECLARE_MEMBERS(OdDbParentTransformOfChildPEForBlkRef);
  virtual OdResult getParentTransformOfChild(const OdDbObject* pThisParent, const OdDbObjectId& childId, OdGeMatrix3d&);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class OdDbParentTransformOfChildPEForViewport : public OdDbParentTransformOfChildPE
{
//  ODRX_DECLARE_MEMBERS(OdDbParentTransformOfChildPEForViewport);
  virtual OdResult getParentTransformOfChild(const OdDbObject* pThisParent, const OdDbObjectId& childId, OdGeMatrix3d&);
};

#endif //ODDBCOMPOUNDOBJECTIDIMPL_H_INCLUDED

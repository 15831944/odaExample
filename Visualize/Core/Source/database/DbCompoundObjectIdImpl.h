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


class DBENT_EXPORT OdTvDbCompoundObjectIdImpl : public OdRxObject
{
public:
  ODRX_USING_HEAP_OPERATORS(OdRxObject);
  ODRX_DECLARE_MEMBERS(OdTvDbCompoundObjectIdImpl);
  virtual bool equal(const OdTvDbCompoundObjectIdImpl&) const = 0;
  virtual OdTvDbObjectId topId() const = 0;
  virtual OdTvDbObjectId leafId() const = 0;
  virtual bool isSimpleObjectId() const = 0;
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler) = 0;
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const = 0;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler) = 0;
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const = 0;
  virtual void set(const OdTvDbObjectId& id, const OdTvDbObjectIdArray& path, OdTvDbDatabase* pHostDatabase) = 0;
  virtual void set(const OdTvDbObjectId& idObj, OdTvDbDatabase* pHostDatabase) = 0;
  virtual void set(const OdTvDbCompoundObjectIdImpl& idComp, OdTvDbDatabase* pHostDatabase) = 0;
  virtual void getFullPath(OdTvDbObjectIdArray& fullPath) const = 0;
  virtual void getPath(OdTvDbObjectIdArray& path) const = 0;
  virtual void setFullPath(const OdTvDbObjectIdArray& fullPath, OdTvDbDatabase* pHostDatabase) = 0;
  virtual bool remap(const OdTvDbIdMapping& idMap) = 0;
  virtual void getTransform(OdGeMatrix3d& trans) const = 0;
};

class DBENT_EXPORT OdTvDbImpBlockRefPathObjectId : public OdTvDbCompoundObjectIdImpl
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbImpBlockRefPathObjectId);

  OdTvDbImpBlockRefPathObjectId();
  virtual ~OdTvDbImpBlockRefPathObjectId();

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual OdTvDbObjectId topId() const;
  virtual OdTvDbObjectId leafId() const;
  virtual void set(const OdTvDbObjectId& id, const OdTvDbObjectIdArray& path, OdTvDbDatabase* pHostDatabase);
  virtual void set(const OdTvDbObjectId& idObj, OdTvDbDatabase* pHostDatabase);
  virtual void set(const OdTvDbCompoundObjectIdImpl& idComp, OdTvDbDatabase* pHostDatabase);
  virtual void getFullPath(OdTvDbObjectIdArray& fullPath) const;
  virtual void getPath(OdTvDbObjectIdArray& path) const;
  virtual void setFullPath(const OdTvDbObjectIdArray& fullPath, OdTvDbDatabase* pHostDatabase);
  virtual bool remap(const OdTvDbIdMapping& idMap);
  virtual void getTransform(OdGeMatrix3d& trans) const;
  virtual bool equal(const OdTvDbCompoundObjectIdImpl& idComp) const
  {
    return m_path == ((OdTvDbImpBlockRefPathObjectId&)idComp).m_path;
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
    OdTvDbObjectId m_id;    // If XretFlags == 1 Entity ObjectId
                          // In case XRefFlags == 2 Id of XRef database BlockTableRecord in host database
                         
    bool operator !=(const BlockRefPathRecord& other) const
    {
      return other.m_id != m_id || other.m_handle != m_handle || other.m_UnkFlag0 != m_UnkFlag0 || other.m_XrefFlags != m_XrefFlags;
    }
    OdTvDbObjectId getId() const;
  };
  OdArray<BlockRefPathRecord, OdMemoryAllocator<BlockRefPathRecord> > m_path;
};


/////////////////////////////////////////////////////////////////////////////////////////////
class OdTvDbParentTransformOfChildPEForBlkRef : public OdTvDbParentTransformOfChildPE
{
//  ODRX_DECLARE_MEMBERS(OdTvDbParentTransformOfChildPEForBlkRef);
  virtual OdResult getParentTransformOfChild(const OdTvDbObject* pThisParent, const OdTvDbObjectId& childId, OdGeMatrix3d&);
};

/////////////////////////////////////////////////////////////////////////////////////////////
class OdTvDbParentTransformOfChildPEForViewport : public OdTvDbParentTransformOfChildPE
{
//  ODRX_DECLARE_MEMBERS(OdTvDbParentTransformOfChildPEForViewport);
  virtual OdResult getParentTransformOfChild(const OdTvDbObject* pThisParent, const OdTvDbObjectId& childId, OdGeMatrix3d&);
};

#endif //ODDBCOMPOUNDOBJECTIDIMPL_H_INCLUDED

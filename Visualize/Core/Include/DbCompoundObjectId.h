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

#ifndef OdTvDbCompoundObjectId_INCLUDED
#define OdTvDbCompoundObjectId_INCLUDED

#include "RxObject.h"
#include "DbObjectId.h"
#include "IdArrays.h"

class OdTvDbDwgFiler;
class OdTvDbDxfFiler;

class OdGeMatrix3d;
class OdTvDbIdMapping;
class OdTvDbCompoundObjectIdImpl;

#include "TD_PackPush.h"

/** \details

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbCompoundObjectId : public OdRxObject
{
public:
    ODRX_DECLARE_MEMBERS(OdTvDbCompoundObjectId);

    virtual ~OdTvDbCompoundObjectId();

    /** \details
      Increments the reference count of this object.
    */
    void addRef();

    /** \details
      Decrements the reference count of this object.
      \remarks
      This object is deleted when the reference count reaches zero.
    */
    void release();

    /** \details
      Returns the reference count of this object.
    */
    long numRefs() const;

    OdTvDbCompoundObjectId& operator =(const OdTvDbObjectId&);
    OdTvDbCompoundObjectId& operator =(const OdTvDbCompoundObjectId&);

    bool operator ==(const OdTvDbCompoundObjectId&) const;
    bool operator !=(const OdTvDbCompoundObjectId& other) const;

    OdTvDbObjectId topId() const;

    OdTvDbObjectId leafId() const;

    OdResult getFullPath(OdTvDbObjectIdArray& fullPath) const;

    OdResult getPath(OdTvDbObjectIdArray& path) const;

    void setEmpty();

    OdResult set(const OdTvDbObjectId&, OdTvDbDatabase* pHostDatabase = NULL);

    OdResult set(const OdTvDbCompoundObjectId&, OdTvDbDatabase* pHostDatabase = NULL);

    OdResult set(const OdTvDbObjectId& id, const OdTvDbObjectIdArray& path, OdTvDbDatabase* pHostDatabase = NULL);

    OdResult setFullPath(const OdTvDbObjectIdArray& fullPath, OdTvDbDatabase* pHostDatabase = NULL);

    bool isEmpty() const;

    bool isValid(int validityCheckingLevel = 1) const;

    bool isExternal() const;

    bool isSimpleObjectId() const;

    OdResult getTransform(OdGeMatrix3d& trans) const;

    bool remap(const OdTvDbIdMapping& idMap);

    OdResult dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbDatabase* pHostDatabase) const;

    OdResult dwgInFields(OdTvDbDwgFiler* pFiler, int ownerVersion);

    OdResult dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbDatabase* pHostDatabase) const;

    OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbDatabase* pHostDatabase, int ownerVersion);

    static const OdTvDbCompoundObjectId& nullId();

    OdTvDbCompoundObjectId();
    OdTvDbCompoundObjectId(const OdTvDbCompoundObjectId& other);
protected:
    OdTvDbCompoundObjectId(OdTvDbCompoundObjectIdImpl*);

    OdTvDbCompoundObjectIdImpl* m_pImpl;
};

typedef OdSmartPtr<OdTvDbCompoundObjectId> OdTvDbCompoundObjectIdPtr;

/** \details
  This PE provides transform for child objects. Implemented for Block Reference, Viewport. Can be implemented for custom objects.
  <group OdTvDb_Classes> 
*/
class DBENT_EXPORT OdTvDbParentTransformOfChildPE : public OdRxObject
{
public:
        ODRX_DECLARE_MEMBERS(OdTvDbParentTransformOfChildPE);
        virtual OdResult getParentTransformOfChild(const OdTvDbObject* pThisParent, const OdTvDbObjectId& childId, OdGeMatrix3d&) = 0;
};
typedef OdSmartPtr<OdTvDbParentTransformOfChildPE> OdTvDbParentTransformOfChildPEPtr;

#include "TD_PackPop.h"

#endif

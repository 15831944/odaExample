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

#ifndef _ODDB_NAMEDPATH_IMPL_INCLUDED_
#define _ODDB_NAMEDPATH_IMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbNamedPath.h"
#include "DbObjectImpl.h"

class OdTvDbNamedPathImpl : public OdTvDbObjectImpl
{
  protected:
    static OdTvDbNamedPathImpl* getImpl(const OdTvDbNamedPath *pObj)
    {
      return (OdTvDbNamedPathImpl*)OdTvDbSystemInternals::getImpl(pObj);
    }

  public:
    OdTvDbNamedPathImpl();
    virtual ~OdTvDbNamedPathImpl();

  protected:
    enum NamedPathType
    {
      kCurvePath,
      kPointPath
    };
    virtual NamedPathType pathType() const = 0;

    virtual OdResult getGeometry(OdGeCurve3d *& pCurve) const = 0;

    virtual OdResult dwgInFields(OdTvDbObject *pObj, OdTvDbDwgFiler *pFiler) = 0;
    virtual void dwgOutFields(const OdTvDbObject *pObj, OdTvDbDwgFiler *pFiler) const = 0;
    virtual OdResult dxfInFields(OdTvDbObject *pObj, OdTvDbDxfFiler *pFiler) = 0;
    virtual void dxfOutFields(const OdTvDbObject *pObj, OdTvDbDxfFiler *pFiler) const = 0;

    friend class OdTvDbNamedPath;
    friend class OdTvDbCurvePath;
    friend class OdTvDbPointPath;
};

class OdTvDbCurvePathImpl : public OdTvDbNamedPathImpl
{
  protected:
    static OdTvDbCurvePathImpl* getImpl(const OdTvDbCurvePath *pObj)
    {
      return static_cast<OdTvDbCurvePathImpl*>(OdTvDbNamedPathImpl::getImpl(pObj));
    }

  public:
    OdTvDbCurvePathImpl();
    virtual ~OdTvDbCurvePathImpl();

  protected:
    static OdUInt32 kCurrentVersion;

    OdTvDbHardPointerId m_entityId;

    virtual NamedPathType pathType() const { return kCurvePath; }

    virtual OdResult getGeometry(OdGeCurve3d *& pCurve) const;

    void setEntityId(const OdTvDbObjectId &curveId);
    OdTvDbObjectId getEntityId() const;

    virtual OdResult dwgInFields(OdTvDbObject *pObj, OdTvDbDwgFiler *pFiler);
    virtual void dwgOutFields(const OdTvDbObject *pObj, OdTvDbDwgFiler *pFiler) const;
    virtual OdResult dxfInFields(OdTvDbObject *pObj, OdTvDbDxfFiler *pFiler);
    virtual void dxfOutFields(const OdTvDbObject *pObj, OdTvDbDxfFiler *pFiler) const;

    bool isEntityClassApplicable(const OdTvDbObjectId &pEntity) const;

    friend class OdTvDbCurvePath;
};

class OdTvDbPointPathImpl : public OdTvDbNamedPathImpl
{
  protected:
    static OdTvDbPointPathImpl* getImpl(const OdTvDbPointPath *pObj)
    {
      return static_cast<OdTvDbPointPathImpl*>(OdTvDbNamedPathImpl::getImpl(pObj));
    }

  public:
    OdTvDbPointPathImpl();
    virtual ~OdTvDbPointPathImpl();

  protected:
    static OdUInt32 kCurrentVersion;

    OdGePoint3d m_point;

    virtual NamedPathType pathType() const { return kPointPath; }

    virtual OdResult getGeometry(OdGeCurve3d *& pCurve) const;

    void setPoint(const OdGePoint3d &point);
    void getPoint(OdGePoint3d &point) const;

    virtual OdResult dwgInFields(OdTvDbObject *pObj, OdTvDbDwgFiler *pFiler);
    virtual void dwgOutFields(const OdTvDbObject *pObj, OdTvDbDwgFiler *pFiler) const;
    virtual OdResult dxfInFields(OdTvDbObject *pObj, OdTvDbDxfFiler *pFiler);
    virtual void dxfOutFields(const OdTvDbObject *pObj, OdTvDbDxfFiler *pFiler) const;

    friend class OdTvDbPointPath;
};

#endif // _ODDB_NAMEDPATH_IMPL_INCLUDED_

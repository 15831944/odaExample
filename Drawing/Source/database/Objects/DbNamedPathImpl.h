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

class OdDbNamedPathImpl : public OdDbObjectImpl
{
  protected:
    static OdDbNamedPathImpl* getImpl(const OdDbNamedPath *pObj)
    {
      return (OdDbNamedPathImpl*)OdDbSystemInternals::getImpl(pObj);
    }

  public:
    OdDbNamedPathImpl();
    virtual ~OdDbNamedPathImpl();

  protected:
    enum NamedPathType
    {
      kCurvePath,
      kPointPath
    };
    virtual NamedPathType pathType() const = 0;

    virtual OdResult getGeometry(OdGeCurve3d *& pCurve) const = 0;

    virtual OdResult dwgInFields(OdDbObject *pObj, OdDbDwgFiler *pFiler) = 0;
    virtual void dwgOutFields(const OdDbObject *pObj, OdDbDwgFiler *pFiler) const = 0;
    virtual OdResult dxfInFields(OdDbObject *pObj, OdDbDxfFiler *pFiler) = 0;
    virtual void dxfOutFields(const OdDbObject *pObj, OdDbDxfFiler *pFiler) const = 0;

    friend class OdDbNamedPath;
    friend class OdDbCurvePath;
    friend class OdDbPointPath;
};

class OdDbCurvePathImpl : public OdDbNamedPathImpl
{
  protected:
    static OdDbCurvePathImpl* getImpl(const OdDbCurvePath *pObj)
    {
      return static_cast<OdDbCurvePathImpl*>(OdDbNamedPathImpl::getImpl(pObj));
    }

  public:
    OdDbCurvePathImpl();
    virtual ~OdDbCurvePathImpl();

  protected:
    static OdUInt32 kCurrentVersion;

    OdDbHardPointerId m_entityId;

    virtual NamedPathType pathType() const { return kCurvePath; }

    virtual OdResult getGeometry(OdGeCurve3d *& pCurve) const;

    void setEntityId(const OdDbObjectId &curveId);
    OdDbObjectId getEntityId() const;

    virtual OdResult dwgInFields(OdDbObject *pObj, OdDbDwgFiler *pFiler);
    virtual void dwgOutFields(const OdDbObject *pObj, OdDbDwgFiler *pFiler) const;
    virtual OdResult dxfInFields(OdDbObject *pObj, OdDbDxfFiler *pFiler);
    virtual void dxfOutFields(const OdDbObject *pObj, OdDbDxfFiler *pFiler) const;

    bool isEntityClassApplicable(const OdDbObjectId &pEntity) const;

    friend class OdDbCurvePath;
};

class OdDbPointPathImpl : public OdDbNamedPathImpl
{
  protected:
    static OdDbPointPathImpl* getImpl(const OdDbPointPath *pObj)
    {
      return static_cast<OdDbPointPathImpl*>(OdDbNamedPathImpl::getImpl(pObj));
    }

  public:
    OdDbPointPathImpl();
    virtual ~OdDbPointPathImpl();

  protected:
    static OdUInt32 kCurrentVersion;

    OdGePoint3d m_point;

    virtual NamedPathType pathType() const { return kPointPath; }

    virtual OdResult getGeometry(OdGeCurve3d *& pCurve) const;

    void setPoint(const OdGePoint3d &point);
    void getPoint(OdGePoint3d &point) const;

    virtual OdResult dwgInFields(OdDbObject *pObj, OdDbDwgFiler *pFiler);
    virtual void dwgOutFields(const OdDbObject *pObj, OdDbDwgFiler *pFiler) const;
    virtual OdResult dxfInFields(OdDbObject *pObj, OdDbDxfFiler *pFiler);
    virtual void dxfOutFields(const OdDbObject *pObj, OdDbDxfFiler *pFiler) const;

    friend class OdDbPointPath;
};

#endif // _ODDB_NAMEDPATH_IMPL_INCLUDED_

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

#ifndef _ODDBFCFIMPL_INCLUDED_
#define _ODDBFCFIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DimStyleRef.h"
#include "DbFcf.h"
#include "DbSystemInternals.h"
#include "OdMTextIterator.h"
#include "DbObjectContextDataManager.h"
#include "Ge/GeDoubleArray.h"

typedef OdArray<OdTextFragmentData> FcfFragmentsArray;
class OdTvDbFcfObjectContextData;

class OdTvDbFcfImpl : public DimStyleRef<OdTvDbEntityImpl>
{
  static OdTvDbFcfImpl* getImpl(const OdTvDbFcf *pObj)
  { return (OdTvDbFcfImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint3d   m_Point;
  OdString      m_strText;
  OdGeVector3d  m_XDir;
  OdGeVector3d  m_Normal;
  double        m_dTextHeight;
  virtual void copyFromContextData(OdTvDbObject*, OdTvDbObjectContextData* pData, OdTvDbObjectContextData* );

  struct CacheItem
  {
    double scale;
    FcfFragmentsArray    m_Fragments;
    OdArray<OdGeDoubleArray> m_AllCoords;
    OdGeDoubleArray      m_ActualSizeBox;
    bool                 m_bMerged;

    CacheItem() :scale(.0), m_bMerged(false){};
  };
  struct Cache
  {
    OdArray<CacheItem> m_Items;
    OdUInt32 m_nRevision;
    CacheItem& get(double scale);
    void clear(bool bRemoveAll = false, OdTvDbFcfObjectContextData* ctx = 0);

    Cache():m_nRevision(0){};
  };
  Cache m_Cache;
  void clearCache()
  {
    m_Cache.clear(true);
  }
  OdTvDbFcfObjectContextDataPtr getAnnotationScale(const OdTvDbFcf* pObj, double& annoscale);
public:
  OdTvDbFcfImpl();

  friend class OdTvDbFcf;

  OdAnsiString getAnsiText(const OdTvDbFcf* pFcf) const;

  void drawFcf(OdGiCommonDraw* pWd, OdGiGeometry& geom, const OdTvDbFcf* pObj, OdTvDbFcfObjectContextData* ctx, const CacheItem& cache);
  void draw(OdGiCommonDraw* pWd, OdGiGeometry& geom, const OdTvDbFcf* pFcf, bool bAnnotative);
  void getBoundingPoints(OdGePoint3dArray& array, OdTvDbFcfImpl::CacheItem& cache, OdTvDbFcfObjectContextData*) const;
  void getBoundingPline(OdGePoint3dArray& array, const OdTvDbFcfImpl::CacheItem& cache, OdTvDbFcfObjectContextData*) const;

  void setCastShadows(bool) {}
  bool castShadows() const { return false; }

  void setReceiveShadows(bool) {}
  bool receiveShadows() const { return false; }

private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
};

#endif // _ODDBFCFIMPL_INCLUDED_

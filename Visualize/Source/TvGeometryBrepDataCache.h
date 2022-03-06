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

#ifndef _ODTV_ENTITYBREPDATACACHE_H_INCLUDED_
#define _ODTV_ENTITYBREPDATACACHE_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvStatistics.h"
#include "CmColorBase.h"
#include "TvStatisticsImpl.h"

class OdGiCommonDraw;
class OdTvBrepCacheCollector;
class OdTvBrepDataCache;
class OdTvDbDwgFiler;
class OdTvDbDatabase;

class OdTvBrepDataCacheStatistic : public OdTvGeometryStatistic
{
public:
  OdTvBrepDataCacheStatistic() : OdTvGeometryStatistic() {}
  ~OdTvBrepDataCacheStatistic() {}

  void inc( Types type ) { m_counts[ type ]++; }

  void inc( Types type, OdUInt64 count ) { m_counts[ type ] += count; }

  void dec( Types type ) 
  { 
    if( m_counts[ type ] ) m_counts[ type ]--;
    else 
    {
      ODA_FAIL();
    }
  }

  void add( const OdTvBrepDataCacheStatistic& stat )
  {
    for( OdUInt32 i = 0; i < m_counts.size(); ++i ) m_counts[ i ] += stat.m_counts[ i ];
  }

  void reset()
  {
    m_counts.setAll( 0 );
  }

  OdTvGeometryStatistic getOdTvGeometryStatistic() const
  {
    OdTvGeometryStatisticImpl statImpl;

    OdUInt64 nCount = getCount(kShell);
    statImpl.increaseCount(kShell, nCount);
    nCount = getCount(kFace);
    statImpl.increaseCount(kFace, nCount);

    nCount = getCount(kPolyline);
    statImpl.increaseCount(kPolyline, nCount);
    nCount = getCount(kNurbs);
    statImpl.increaseCount(kNurbs, nCount);
    nCount = getCount(kCircle);
    statImpl.increaseCount(kCircle, nCount);
    nCount = getCount(kCircularArc);
    statImpl.increaseCount(kCircularArc, nCount);
    nCount = getCount(kEllipticArc);
    statImpl.increaseCount(kEllipticArc, nCount);
    nCount = getCount(kPoints);
    statImpl.increaseCount(kPoints, nCount);

    OdTvGeometryStatistic newStat;
    OdTvGeometryStatisticImpl::copy(&newStat, statImpl.getCountArray(), statImpl.getObjectsSize());

    return newStat;
  }
};

/** \details
This class implements the brep data cache storage
*/

class OdTvBrepDataCacheStorage
{
public:
  enum RenderMode
  {
    kLinesMode = 1 << 0,
    kShellsMode = 1 << 1,

    kAllMode = kLinesMode | kShellsMode
  };

  OdTvBrepDataCacheStorage();
  ~OdTvBrepDataCacheStorage();

  OdGiCommonDraw* getCollector( RenderMode rm, OdCmEntityColor defaultColor = OdCmEntityColor() );

  void clear( RenderMode rm = kAllMode );

  void draw( OdGiCommonDraw*, RenderMode );

  double surfaceTolerance( RenderMode rm ) const;
  void setSurfaceTolerance( double t, RenderMode rm );

  bool isValidCache( RenderMode rm ) const;
  bool isEmptyCache( RenderMode rm ) const;

  void read( OdTvDbDwgFiler* pFiler, OdTvDbDatabase* pDb, OdTvVSFVersion ver );
  void write( OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver ) const;

  OdTvBrepDataCacheStatistic getStatistic( RenderMode rm = kAllMode );

  bool copyTo( OdTvBrepDataCacheStorage* pStorage, RenderMode rm = kAllMode );

protected:
  OdArray< OdTvBrepCacheCollector* > m_pCollectors;

  enum StorageType
  {
    kStorageLines = 0,
    kStorageShells = 1,
    kStorageLast = kStorageShells
  };
  OdArray< OdTvBrepDataCache* > m_pCaches;
  OdTvBrepDataCache* cache( RenderMode rm );
  void copyCache( OdTvBrepDataCache* pFrom, OdTvBrepDataCache* pTo );
};


#include "TD_PackPop.h"

#endif //_ODTV_ENTITYBREPDATACACHE_H_INCLUDED_



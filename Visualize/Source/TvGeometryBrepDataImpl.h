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

#ifndef _ODTV_ENTITYBREPDATA_H_INCLUDED_
#define _ODTV_ENTITYBREPDATA_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGeometryDataImpl.h"
#include "TvGeometryBrepDataCache.h"

#include "Br/BrBrep.h"


/** \details
This class implements the brep data
*/
class OdTvBrepDataImpl : public OdTvGeometryDataImpl
{
public:

  OdTvBrepDataImpl() : OdTvGeometryDataImpl(), m_dFACETRES(1.), m_pCache(NULL), m_enableCache(false){}
  virtual ~OdTvBrepDataImpl();

  /* own methods */
  OdTvResult set(const OdBrBrep& brep, OdDbBaseDatabase *pDb, OdTvDbDatabase* pParentDb);

  void setFacetRes(double dFacetRes);
  double getFacetRes() const { return m_dFACETRES; }
  void setEnableCaching(bool bEnable);
  bool getCachingEnabled() const;

  OdTvGeometryStatistic getCacheStatistic(OdTvResult* rc) const;

  void clearCache();
  bool isNeedUpdateCache(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity, double surfTol) const;

  //**************************************************************************************
  // Override 'OdTvGeometryDataImpl' methods
  //**************************************************************************************

  virtual TvGeometryType                      entityGeometryDataType() const { return Brep; }
  virtual bool                                draw(OdGiWorldDraw* pWorldDraw, const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                                drawForMarkers(const OdTvEntityImpl* pParentEntity, OdGsMarker& marker) const;
  virtual void                                drawView(OdGiViewportDraw* pViewportDraw, const OdTvEntityImpl* pParentEntity) const;
  virtual OdTvGeometryData::GeometryTypes     getFirstColorGeomType() const { return OdTvGeometryData::kFaces; } // it important to use the same geometry in the following two methods
  virtual OdTvGeometryData::GeometryTypes     getSecondColorGeomType() const { return OdTvGeometryData::kFaces; }
  virtual void                                read(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion());
  virtual void                                write(OdTvDbDwgFiler* pFiler, OdTvVSFExportOptions options, OdTvVSFVersion ver = OdTvVSFVersion()) const;
  virtual bool                                copyTo(OdTvGeometryDataImpl* pTargetGeometry, OdTvEntityImpl* pTargetEntity) const;

  virtual OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

private:
  double                              m_dFACETRES;
  OdBrBrep                            m_Brep;
  OdRxObjectPtr                       m_BrepStore;
  mutable OdTvBrepDataCacheStorage*   m_pCache;   //cache
  bool                                m_enableCache;
};

typedef OdTvSmartPtrInternal<OdTvBrepDataImpl> OdTvBrepDataImplPtr;


/** \details
This is an wrapper of the interface class for OdTvGeometryData object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvBrepDataWrapper : public OdTvBrepData
{
  ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(OdTvBrepData)

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  FacetRes setter
  */
  virtual OdTvResult setFacetRes(double dFacetRes);

  /** \details
  FacetRes getter
  */
  virtual double getFacetRes(OdTvResult* rc = NULL) const;

  /** \details
  set geometry caching enabled ot not
  */
  virtual OdTvResult setEnableCaching(bool bEnable);

  /** \details
  get geometry caching enabled ot not
  */
  virtual bool getCachingEnabled(OdTvResult* rc = NULL) const;

  /** \details
  Return the geometry statics of the cache if the cache exists
  */
  virtual OdTvGeometryStatistic getCacheStatistic(OdTvResult* rc) const;
};

#include "TD_PackPop.h"

#endif //_ODTV_ENTITYBREPDATA_H_INCLUDED_



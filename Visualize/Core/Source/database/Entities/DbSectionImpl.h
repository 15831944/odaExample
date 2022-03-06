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

#ifndef _DBSECTIONIMPL_INCLUDED_
#define _DBSECTIONIMPL_INCLUDED_

#include "DbSection.h"
#include "DbEntityImpl.h"
#include "ModelerGeometry.h"
#include "DbSectionGeom.h"

class OdTvDbSectionImpl : public OdTvDbEntityImpl
{
  OdTvDbSection::State m_nState;
  OdString m_sName;
  OdGeVector3d m_pVerticalDirection;
  OdTvCmColor m_IndicatorFillColor;
  int m_nIndicatorTransparency;
  int m_nPlaneVertices; // including jogs
  OdGePoint3dArray m_pVertices;
  double m_Heights[2];
  OdTvDbObjectId m_pSettingsId;
  bool m_bIsLiveSectionEnabled;
  bool m_bViewDirection; //4

  SolidCache m_solidCache;

  OdTvDbObjectId m_visualStyleId; // run-time cashed value
  OdTvDbSectionSettingsPtr m_pTransientSettings;

  //x-data: ThicknessDepth, IsSlice
  bool m_bIsSlice;
  double m_ThicknessDepth;

public:
  OdTvDbSectionImpl();

  OdTvDbObjectId getSettingsId();

  static void setTransientSectionSettings(OdTvDbSection *pSection, OdTvDbSectionSettings *pSettings)
  { getImpl(pSection)->m_pTransientSettings = pSettings;
    if (pSettings) OdTvDbSystemInternals::getImpl(pSettings)->setDatabase(pSection->database()); }

  OdResult transformBy(const OdGeMatrix3d& xform);

  OdGeVector3d normal();

  OdTvDbObjectId getVisualStyle(bool bCreateIfNotFound);

  void invalidateSolidCache();

  void createBackVertices();

  OdResult plane(OdGeVector3d& uAxis, OdGeVector3d& vAxis) const;

  OdResult addVertex(int nInsertAt, const OdGePoint3d& pt);

  OdResult removeVertex(int nIndex);

  OdResult setVertex(int nIndex, const OdGePoint3d& pt);

  OdResult setVertices(const OdGePoint3dArray& pts);

  OdResult setElevation( double dEval );

  SolidCacheItemPtr getLiveSectionSolidCache();

  void setLiveSectionSolidCache(SolidCacheItem& item);

  void clearSolidCache();

  OdResult setIsSlice( bool bIsSlice, OdTvDbSection* pSect );

  OdResult setThicknesDepth( double depth, OdTvDbSection* pSect );

  OdResult setSectionPlaneOffset( double offset );

  bool hasJogs() const;

  bool isSlice() const;

  double thicknesDepth() const;

  OdResult createJog(const OdGePoint3d& ptOnSection);

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
private:
  static OdTvDbSectionImpl* getImpl(const OdTvDbSection* pObj)
  { return (OdTvDbSectionImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  friend class OdTvDbSection;
};

#endif // _DBSECTIONIMPL_INCLUDED_

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

#ifndef _ODDB_GEODATA_IMPL_INCLUDED_
#define _ODDB_GEODATA_IMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbGeoData.h"
#include "DbObjectImpl.h"
#include "OdDbGeoCoordinateSystem.h"

class OdTvDbGeoDataImpl;


struct OdGeoMeshFace
{
  OdGeoMeshFace() { m_index[0] = m_index[1] = m_index[2] = 0; }
  OdInt32  m_index[3];
};
typedef OdArray<OdGeoMeshFace, OdMemoryAllocator<OdGeoMeshFace> > OdGeoMeshFaceArray;

class OdTvDbObservationMeshFace
{
public:
  OdGeoMeshFace m_face;
  OdGePoint2d m_pt[2];
  double m_z[2];
};
typedef OdArray<OdTvDbObservationMeshFace, OdMemoryAllocator<OdTvDbObservationMeshFace> > OdTvDbObservationMeshFaceArray;

class OdTvDbObservationMesh
{
public:
  OdTvDbObservationMesh(const OdTvDbGeoDataImpl * pGeoData = NULL);
  void set(const OdTvDbGeoDataImpl * pGeoData);
  OdResult transformToLLA(const OdGePoint2d & ptIn, OdGePoint2d & ptOut);
  OdResult transformFromLLA(const OdGePoint2d & ptIn, OdGePoint2d & ptOut);
private:
  OdGePoint2dArray m_arrPt[2];
  OdTvDbObservationMeshFaceArray m_arrFaces;
  void calcMeshFacePt(OdTvDbObservationMeshFace & face);
  OdResult transformTo(const OdGePoint2d & ptIn, OdGePoint2d & ptOut, bool bToGeo);
};

class OdTvDbGeoDataImpl : public OdTvDbObjectImpl
{
  static OdTvDbGeoDataImpl* getImpl(const OdTvDbGeoData *pObj)
  { return (OdTvDbGeoDataImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbGeoDataImpl();

  void decomposeForSave(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

private:
  void dxfInFieldsVer2(OdTvDbDxfFiler* pFiler, unsigned subVer);
  void dxfInFieldsVer1(OdTvDbDxfFiler* pFiler);
  void dxfInCivil3dFields(OdTvDbDxfFiler* pFiler);

  static OdUInt32 kCurrentVersion;

  OdTvDbObjectId m_blockId;
  OdInt16 m_coordinateType;
  OdGePoint3d m_designPoint;
   // The referencePoint contains (longitude, latitude, elevation)
  //    longitude : negative - is west of the Prime Meridian / positive - is east of the Prime Meridian
  //    latitude : negative - is south of the equator / positive - is north of the equator
  OdGePoint3d m_referencePoint;
  double  m_horizontalUnitScale;
  OdInt32 m_horizontalUnits;
  double  m_verticalUnitScale;
  OdInt32 m_verticalUnits;

  OdGeVector3d m_upDirection;
  OdGeVector2d m_northDirection;

  OdInt32  m_scaleEstimationMethod;
  double   m_scaleFactor;
  bool     m_doSeaLevelCorrection;
  double   m_seaLevelElevation;
  double   m_coordinateProjectionRadius;
  OdString m_coordinateSystem;
  OdString m_geoRSSTag;
  OdString m_observationFrom;
  OdString m_observationTo;
  OdString m_observationCoverage;
  // MeshPointMap
  OdGePoint2dArray m_meshSrcPts;
  OdGePoint2dArray m_meshDstPts;
  OdGeoMeshFaceArray m_meshFaces;

  OdDb::MaintReleaseVer m_rv; // needed only for composeForLoad
  friend class OdTvDbGeoData;
  friend class OdTvDbObservationMesh;

  OdResult updateTransformationMatrix();
  OdGeMatrix3d m_matrixToLLA;
  OdGeMatrix3d m_matrixFromLLA;
  OdGeMatrix3d m_matrixLocalToLLA;
  OdGeMatrix3d m_matrixLocalFromLLA;
  OdTvDbObservationMesh m_observationMesh;
  mutable OdTvDbGeoCoordinateSystemTransformerPtr m_pToLLA;
  mutable OdTvDbGeoCoordinateSystemTransformerPtr m_pFromLLA;
};

#endif // _ODDB_GEODATA_IMPL_INCLUDED_

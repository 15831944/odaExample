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

#ifndef _ODDBGEOPOSITIONMARKER_IMPL_INCLUDED_
#define _ODDBGEOPOSITIONMARKER_IMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbGeoPositionMarker.h"
#include "DbEntityImpl.h"

class OdTvDbGeoPositionMarkerMeshGen
{
public:
  OdTvDbGeoPositionMarkerMeshGen();
  ~OdTvDbGeoPositionMarkerMeshGen();
  static const OdGePoint3d * meshSphere();
  static const OdGePoint3d * meshCylinder();
};

class OdTvDbGeoPositionMarkerImpl : public OdTvDbEntityImpl
{
  static OdTvDbGeoPositionMarkerImpl* getImpl(const OdTvDbGeoPositionMarker *pObj)
  { return (OdTvDbGeoPositionMarkerImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  OdGeMatrix3d         getRotationMatrix() const;
  OdGeVector3d         normal() const;
public:
  OdTvDbGeoPositionMarkerImpl();

  virtual void      decomposeForSave(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

private:
  double               m_dRadius;
  OdGePoint3d          m_ptPosition;
  double               m_dLandingGap;
  OdString             m_sNotes;
  OdTvDbMTextPtr         m_pMText;
  OdUInt8              m_flags;
  OdTvDbGeoPositionMarker::OdTextAlignmentType  m_eTextAlignmentType;
  static OdTvDbGeoPositionMarkerMeshGen m_MeshGen;

  friend class OdTvDbGeoPositionMarker;
};

#endif

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

#ifndef _POINTCLOUDIMPL_INCLUDED_
#define _POINTCLOUDIMPL_INCLUDED_

#include "Entities/DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbPointCloudObj/DbPointCloud.h"

class ClipBoundarySaver;

class OdDbPointCloudImpl : public OdDbEntityImpl
{
public:

  OdDbPointCloudImpl()
    : m_nPointsCount(0),
      m_bClipping(true),
      m_showIntensity(false),
      m_intensitySchemeIndex(0)
  {}

  static OdDbPointCloudImpl* getImpl(const OdDbPointCloud *pObj)
  { return (OdDbPointCloudImpl*)OdDbSystemInternals::getImpl(pObj);}

  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void restorePointCloudLinks();

protected:
  void pushClips(ClipBoundarySaver& clipSaver);

  OdGeMatrix3d m_transformation;

  OdInt64 m_nPointsCount;

  OdArray<OdDbPointCloudClipping> m_clipBoundaries;

  OdDbPointCloudIntensityStyle m_intensityStyle;

  OdGeExtents3d m_extents;

  OdString      m_strSavedFile;
  OdStringArray m_SourceFiles;
  OdString      m_strIndexFile; // Run-time only
  OdString      m_strCoordSys;

  OdDbObjectId m_pointCloudDefId;
  OdDbObjectId m_pointCloudDefReactorId;

  OdInt16 m_intensitySchemeIndex;
  bool m_bClipping;
  bool m_showIntensity;

  friend class OdDbPointCloud;
};

#endif // _POINTCLOUDIMPL_INCLUDED_

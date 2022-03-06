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

#ifndef _POINTCLOUDEXIMPL_INCLUDED_
#define _POINTCLOUDEXIMPL_INCLUDED_


#include "Entities/DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbPointCloudObj/DbPointCloudEx.h"

class ClipBoundarySaver;

class OdDbPointCloudExImpl : public OdDbEntityImpl
{
public:

  OdDbPointCloudExImpl()    
  {
    clear();
  }

  void clear();

  static OdDbPointCloudExImpl* getImpl( const OdDbPointCloudEx *pObj )
  {
    return (OdDbPointCloudExImpl*)OdDbSystemInternals::getImpl( pObj );
  }

  //void composeForLoad( OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version );
  void restorePointCloudLinks(const OdString& rcsFilePath);

protected:
  void pushClips( ClipBoundarySaver& clipSaver );

  OdGeMatrix3d m_transformation;
  OdGeExtents3d m_extents;

  bool m_locked;

  OdDbObjectId m_pointCloudDefExId;
  OdDbObjectId m_pointCloudDefReactorExId;
  OdString m_pointCloudName;
  
  bool m_unk291;
  bool m_showCropping;

  OdInt32 m_unk92;
  OdInt32 m_unk93;
  OdInt32 m_unk93_2;

  OdInt16 m_stylizationType;

  OdString m_str1;
  OdString m_currentColorSheme;
  OdString m_str3;

  double m_minElevation;
  double m_maxElevation;

  OdInt32 m_minIntensity;
  OdInt32 m_maxIntensity;

  OdInt16 m_displayIntensityOutOfRange;
  OdInt16 m_displayElevationOutOfRange;

  bool m_elevationApplyToFixedRange;
  bool m_showIntensityAsGradient;
  bool m_showElevationAsGradient;

  //
  OdArray<OdDbPointCloudCropping> m_clipBoundaries;

  friend class OdDbPointCloudEx;
};

#endif // _POINTCLOUDEXIMPL_INCLUDED_

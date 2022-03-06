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

#ifndef __OD_DB_CAMERA_IMPL__
#define __OD_DB_CAMERA_IMPL__

#include "DbEntityImpl.h"
#include "DbCamera.h"

class OdTvDbCameraImpl : public OdTvDbEntityImpl
{
  OdTvDbObjectId          m_viewRecId;
  mutable OdTvDbObjectPtr m_pTransView;
  enum CameraFlags
  {
    kWBlockClonedCamera = 1,
    kHighlightedCamera  = 2
  };
  OdUInt16     m_cameraFlags;
  // Copy of DbViewTableRecord params for prevent object open (update on each synchronization)
  OdGePoint3d  m_cameraOrigin;
  OdGePoint3d  m_cameraTarget;
  double       m_lensLength;
  double       m_fovAngleH;
  double       m_fovAngleV;
  double       m_rollAngle;
  bool         m_bPlot;
  bool         m_bFrontClip;
  double       m_frontClip;
  bool         m_bBackClip;
  double       m_backClip;

  static OdTvDbCameraImpl* getImpl(const OdTvDbCamera *pObj)
  { return (OdTvDbCameraImpl*)OdTvDbSystemInternals::getImpl(pObj); }

public:
  OdTvDbCameraImpl();

  friend class OdTvDbCamera;
  friend void odtvdbUpdateViewTableRecordCamera(OdTvDbViewTableRecord *pVTR);

  OdResult dwgInFields(OdTvDbCamera *pObj, OdTvDbDwgFiler* pFiler);
  void dwgOutFields(const OdTvDbCamera *pObj, OdTvDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdTvDbCamera *pObj, OdTvDbDxfFiler* pFiler);
  void dxfOutFields(const OdTvDbCamera *pObj, OdTvDbDxfFiler* pFiler) const;

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void drawPolyline(OdGiViewportDraw *pVd, const OdGeMatrix3d &xFm, const OdGePoint3d &pt1, const OdGePoint3d &pt2) const;
  void draw(const OdTvDbCamera *pObj, OdGiViewportDraw *pVd) const;

  OdTvDbObjectId view(const OdTvDbCamera *pObj) const;
  void setView(OdTvDbCamera *pObj, const OdTvDbObjectId &viewId);

  OdTvDbViewTableRecordPtr openView(const OdTvDbCamera *pObj, OdDb::OpenMode openMode) const;
  void updateView(OdTvDbCamera *pObj);

  double fovFromLensLength(double ll, bool bVert = false) const;
  double planeLengthAtFov(double distance, double fov) const;
  void syncWithVTR();

  OdTvDbObjectId addToViewTableWithRename(OdTvDbViewTable *pVT, OdTvDbViewTableRecord *pVTR) const;

  // flags
  bool isWBlockCloned() const;
  void setWBlockCloned(bool bSet);

  bool isHighlighted() const;
  void setHighlighted(bool bSet);
};

inline bool OdTvDbCameraImpl::isWBlockCloned() const
{
  return GETBIT(m_cameraFlags, kWBlockClonedCamera);
}
inline void OdTvDbCameraImpl::setWBlockCloned(bool bSet)
{
  SETBIT(m_cameraFlags, kWBlockClonedCamera, bSet);
}

inline bool OdTvDbCameraImpl::isHighlighted() const
{
  return GETBIT(m_cameraFlags, kHighlightedCamera);
}
inline void OdTvDbCameraImpl::setHighlighted(bool bSet)
{
  SETBIT(m_cameraFlags, kHighlightedCamera, bSet);
}

#endif // __OD_DB_CAMERA_IMPL__

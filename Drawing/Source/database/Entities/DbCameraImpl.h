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

class OdDbCameraImpl : public OdDbEntityImpl
{
  OdDbObjectId          m_viewRecId;
  mutable OdDbObjectPtr m_pTransView;
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

  static OdDbCameraImpl* getImpl(const OdDbCamera *pObj)
  { return (OdDbCameraImpl*)OdDbSystemInternals::getImpl(pObj); }

public:
  OdDbCameraImpl();

  friend class OdDbCamera;
  friend void oddbUpdateViewTableRecordCamera(OdDbViewTableRecord *pVTR);

  OdResult dwgInFields(OdDbCamera *pObj, OdDbDwgFiler* pFiler);
  void dwgOutFields(const OdDbCamera *pObj, OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbCamera *pObj, OdDbDxfFiler* pFiler);
  void dxfOutFields(const OdDbCamera *pObj, OdDbDxfFiler* pFiler) const;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  struct CameraXform { OdGeMatrix3d m_xForm; bool m_bIdentity; CameraXform() : m_bIdentity(true) { }
                       CameraXform(const OdGeMatrix3d &xFm) : m_xForm(xFm), m_bIdentity(xFm == OdGeMatrix3d::kIdentity) { } };
  void drawPolyline(OdGiViewportDraw *pVd, const CameraXform &xFm, const OdGePoint3d &pt1, const OdGePoint3d &pt2) const;
  void draw(const OdDbCamera *pObj, OdGiViewportDraw *pVd) const;

  OdDbObjectId view(const OdDbCamera *pObj) const;
  void setView(OdDbCamera *pObj, const OdDbObjectId &viewId);

  OdDbViewTableRecordPtr openView(const OdDbCamera *pObj, OdDb::OpenMode openMode) const;
  void updateView(OdDbCamera *pObj);

  double fovFromLensLength(double ll, bool bVert = false) const;
  double planeLengthAtFov(double distance, double fov) const;
  void syncWithVTR();

  OdDbObjectId addToViewTableWithRename(OdDbViewTable *pVT, OdDbViewTableRecord *pVTR) const;

  // flags
  bool isWBlockCloned() const;
  void setWBlockCloned(bool bSet);

  bool isHighlighted() const;
  void setHighlighted(bool bSet);
};

inline bool OdDbCameraImpl::isWBlockCloned() const
{
  return GETBIT(m_cameraFlags, kWBlockClonedCamera);
}
inline void OdDbCameraImpl::setWBlockCloned(bool bSet)
{
  SETBIT(m_cameraFlags, kWBlockClonedCamera, bSet);
}

inline bool OdDbCameraImpl::isHighlighted() const
{
  return GETBIT(m_cameraFlags, kHighlightedCamera);
}
inline void OdDbCameraImpl::setHighlighted(bool bSet)
{
  SETBIT(m_cameraFlags, kHighlightedCamera, bSet);
}

#endif // __OD_DB_CAMERA_IMPL__

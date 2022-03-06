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

#ifndef __OD_DB_CAMERA__
#define __OD_DB_CAMERA__

#undef DBCAMERA_EXPORT
#ifdef DBCAMERA_EXPORTS
# define DBCAMERA_EXPORT OD_TOOLKIT_EXPORT
#else
# define DBCAMERA_EXPORT OD_TOOLKIT_IMPORT
#endif

#include "DbEntity.h"
#include "DynamicLinker.h"

#include "TD_PackPush.h"

/** \details
  <group OdTvDb_Classes>
*/
class OdTvDbViewTableRecord;
typedef OdSmartPtr<OdTvDbViewTableRecord> OdTvDbViewTableRecordPtr;

/** \details
    Corresponding C++ library: ACCAMERA

    <group OdTvDb_Classes>
*/
class DBCAMERA_EXPORT OdTvDbCamera : public OdTvDbEntity
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbCamera);

  OdTvDbCamera();

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual OdResult subErase(bool erasing);
  virtual void subClose();

  OdTvDbObjectId view() const;
  void setView(const OdTvDbObjectId &viewId);

  // Some helpful methods for NDBRO editing (required for grip points implementation for example)
  // For internal use
  OdTvDbViewTableRecordPtr openView(OdDb::OpenMode openMode = OdDb::kForRead) const;
  // For internal use
  void updateView();

protected:

  virtual OdResult subTransformBy(const OdGeMatrix3d& xfm);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  virtual OdResult subGetClassID(void* pClsid) const;

  virtual OdResult subGetGeomExtents(OdGeExtents3d& extents) const;

  virtual OdTvDbObjectPtr subDeepClone(OdTvDbIdMapping& ownerIdMap, OdTvDbObject*, bool bPrimary) const ODRX_OVERRIDE;
  virtual OdTvDbObjectPtr subWblockClone(OdTvDbIdMapping& ownerIdMap, OdTvDbObject*, bool bPrimary) const ODRX_OVERRIDE;

  virtual void subHighlight(bool bDoIt = true, const OdTvDbFullSubentPath* pSubId = 0, bool highlightAll = false) const;
};

typedef OdSmartPtr<OdTvDbCamera> OdTvDbCameraPtr;

/** \details
  <group OdTvDb_Classes>
*/
class CameraModule : public OdRxModule {
protected:
  virtual void initApp();
  virtual void uninitApp();
public:
  virtual void UpdateViewTableRecordCamera(OdTvDbViewTableRecord *pVTR);
  virtual void InitialUpdateViewTableRecordCameras(OdTvDbDatabase *pDb);
};

typedef OdSmartPtr<CameraModule> CameraModulePtr;

inline void odtvdbUpdateViewTableRecordCamera(OdTvDbViewTableRecord *pVTR) {
  CameraModulePtr cammod(::odrxLoadApp("ACCAMERA"));
  if(cammod.get())
    cammod->UpdateViewTableRecordCamera(pVTR);

}

inline void odtvdbInitialUpdateViewTableRecordCameras(OdTvDbDatabase *pDb) {
  CameraModulePtr cammod(::odrxLoadApp("ACCAMERA"));
  if(cammod.get())
    cammod->InitialUpdateViewTableRecordCameras(pDb);
}

#include "TD_PackPop.h"

#endif // __OD_DB_CAMERA__

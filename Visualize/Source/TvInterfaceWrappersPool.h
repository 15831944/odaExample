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

#ifndef _ODTV_INTERFACEWRAPPERSPOOL_H_INCLUDED_
#define _ODTV_INTERFACEWRAPPERSPOOL_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvDatabaseImpl.h"
#include "TvModelImpl.h"
#include "TvBlockImpl.h"
#include "TvInsertImpl.h"
#include "TvEntityImpl.h"
#include "TvTextStyleImpl.h"
#include "TvLinetypeImpl.h"
#include "TvLayerImpl.h"
#include "TvRasterImageImpl.h"
#include "TvMaterialImpl.h"
#include "TvGeometryDataImpl.h"
#include "TvGeometryTypifiedDataImpl.h"
#include "TvGeometryGridDataImpl.h"
#include "TvGeometryShellDataImpl.h"
#include "TvGeometryPMDataImpl.h"
#include "TvGeometryBrepDataImpl.h"
#include "TvGeometryMeshDataImpl.h"
#include "TvGeometryTypifiedData3DImpl.h"
#include "TvGeometryTypifiedDataMiscImpl.h"
#include "TvGsDeviceImpl.h"
#include "TvLightImpl.h"
#include "TvVisualStyleImpl.h"
#include "TvIdAccess.h"
#include "ThreadsCounter.h"
#include "TvGsViewBackgroundImpl.h"
#include "TvCommonDataAccessTreeImpl.h"
#include "TvCameraImpl.h"
#include "TvAnimationImpl.h"

/** \details
    The factory for the wrappers objects
*/

class OdTvInterfaceWrappersPool
{
  OdTvDatabasePtr                m_databaseInterface;
  OdTvModelPtr                   m_modelInterface;
  OdTvBlockPtr                   m_blockInterface;
  OdTvInsertPtr                  m_insertInterface;
  OdVector<OdTvEntityPtr>        m_entityInterfaces;
  OdVector<OdTvGeometryDataPtr>  m_geometryDataInterfaces;
  OdTvLightPtr                   m_lightInterface;
  OdTvCameraPtr                  m_cameraInterface;

  // collections
  OdTvTextStylePtr               m_textstyleInterface;
  OdTvLinetypePtr                m_linetypeInterface;
  OdTvLayerPtr                   m_layerInterface;
  OdTvRasterImagePtr             m_rasterimageInterface;
  OdTvMaterialPtr                m_materialInterface;
  OdTvVisualStylePtr             m_visualStyleInterface;
  OdTvGsViewSolidBackgroundPtr   m_gsViewSolidBackgroundInterface;
  OdTvGsViewGradientBackgroundPtr m_gsViewGradientBackgroundInterface;
  OdTvGsViewImageBackgroundPtr   m_gsViewImageBackgroundInterface;
  OdTvHighlightStylePtr          m_highlightStyleInterface;

  //Geometrical data wrappers
  OdTvPolylineDataPtr            m_PolylineDataInterface;
  OdTvCircleDataPtr              m_CircleDataInterface;
  OdTvCircleArcDataPtr           m_CircleArcDataInterface;
  OdTvCircleWedgeDataPtr         m_CircleWedgeDataInterface;
  OdTvEllipseDataPtr             m_EllipseDataInterface;
  OdTvEllipticArcDataPtr         m_EllipticArcDataInterface;
  OdTvPolygonDataPtr             m_PolygonDataInterface;
  OdTvShellDataPtr               m_ShellDataInterface;
  OdTvBrepDataPtr                m_BrepDataInterface;
  OdTvMeshDataPtr                m_MeshDataInterface;
  OdTvSphereDataPtr              m_SphereDataInterface;
  OdTvCylinderDataPtr            m_CylinderDataInterface;
  OdTvBoxDataPtr                 m_BoxDataInterface;
  OdTvTextDataPtr                m_TextDataInterface;
  OdTvNurbsDataPtr               m_NurbsDataInterface;
  OdTvInfiniteLineDataPtr        m_InfiniteLineDataInterface;
  OdTvRasterImageDataPtr         m_RasterImageDataInterface;
  OdTvPointCloudDataPtr          m_PointCloudDataInterface;
  OdTvGridDataPtr                m_GridDataInterface;
  OdTvColoredShapeDataPtr        m_ColoredShapeDataInterface;
  OdTvInsertDataPtr              m_InsertDataInterface;
  OdTvRcsPointCloudDataPtr       m_RcsPointCloudDataInterface;
  OdTvProgressiveMeshDataPtr     m_ProgressiveMeshDataInterface;

  //Gs wrappers
  OdTvGsDevicePtr                m_gsDeviceInterface;
  OdTvGsViewPtr                  m_gsViewInterface;

  //Misc wrappers
  OdTvCDATreeStoragePtr          m_cdaTreeStorageInterface;
  OdTvAnimationActionPtr         m_AnimationActionInterface;
  OdTvAnimationContainerPtr      m_AnimationContainerInterface;

  // MT support
  OdMutexPtr m_mutex;

public:
  OdTvInterfaceWrappersPool();
  ~OdTvInterfaceWrappersPool();

  OdTvDatabasePtr      getDatabaseInterface(OdTvDatabaseImpl* pImpl);
  OdTvModelPtr         getModelInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvBlockPtr         getBlockInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvInsertPtr        getInsertInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvEntityPtr        getEntityInterface(const OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvGeometryDataPtr  getGeometryDataInterface(OdTvGeometryDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvLightPtr         getLightInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvCameraPtr        getCameraInterface( OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode );

  // collections
  OdTvTextStylePtr         getTextStyleInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvLinetypePtr          getLinetypeInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvLayerPtr             getLayerInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvRasterImagePtr       getRasterImageInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvMaterialPtr          getMaterialInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvVisualStylePtr       getVisualStyleInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvGsViewSolidBackgroundPtr    getGsViewSolidBackgroundInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvGsViewGradientBackgroundPtr getGsViewGradientBackgroundInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvGsViewImageBackgroundPtr    getGsViewImageBackgroundInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvHighlightStylePtr    getHighlightStyleInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);


  //Geometrical data wrappers
  OdTvPolylineDataPtr          getPolylineDataInterface(OdTvPolylineDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvCircleDataPtr            getCircleDataInterface(OdTvCircleDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvCircleArcDataPtr         getCircleArcDataInterface(OdTvCircleArcDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvCircleWedgeDataPtr       getCircleWedgeDataInterface(OdTvCircleWedgeDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvPolygonDataPtr           getPolygonDataInterface(OdTvPolygonDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvEllipseDataPtr           getEllipseDataInterface(OdTvEllipseDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvEllipticArcDataPtr       getEllipticArcDataInterface(OdTvEllipticArcDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvShellDataPtr             getShellDataInterface(OdTvShellDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvBrepDataPtr              getBrepDataInterface(OdTvBrepDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvMeshDataPtr              getMeshDataInterface(OdTvMeshDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvSphereDataPtr            getSphereDataInterface(OdTvSphereDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvCylinderDataPtr          getCylinderDataInterface(OdTvCylinderDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvBoxDataPtr               getBoxDataInterface(OdTvBoxDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvTextDataPtr              getTextDataInterface(OdTvTextDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvNurbsDataPtr             getNurbsDataInterface(OdTvNurbsDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvInfiniteLineDataPtr      getInfiniteLineDataInterface(OdTvInfiniteLineDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvRasterImageDataPtr       getRasterImageDataInterface(OdTvRasterImageDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvPointCloudDataPtr        getPointCloudDataInterface(OdTvPointCloudDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvGridDataPtr              getGridDataInterface(OdTvGridDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvColoredShapeDataPtr      getColoredShapeDataInterface(OdTvColoredShapeDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvInsertDataPtr            getInsertDataInterface(OdTvInsertDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvRcsPointCloudDataPtr     getRcsPointCloudDataInterface(OdTvRcsPointCloudDataImpl* pData, const OdTvDbObjectId& parentEntityId);
  OdTvProgressiveMeshDataPtr   getProgressiveMeshDataInterface(OdTvProgressiveMeshDataImpl* pData, const OdTvDbObjectId& parentEntityId);

  //Gs wrappers
  OdTvGsDevicePtr              getGsDeviceInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvGsViewPtr                getGsViewInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);

  //Misc wrappers
  OdTvCDATreeStoragePtr        getCDATreeStorageInterface(OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode);
  OdTvAnimationActionPtr       getAnimationActionInterface( OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode );
  OdTvAnimationContainerPtr    getAnimationContainerInterface( OdTvDbObjectId& wrappedObjId, OdTv::OpenMode mode );
};


/** \details
    Declares the define for getting the wrapper as an interface for the typified geometry
*/
#define ODTV_DEFINE_GET_TYPIFIED_GEOMETRY_INTERFACE_WRAPPER(pData, parentEntityId, GeometryName)                                                      \
  TD_AUTOLOCK_P_DEF(m_mutex);                                                                                                                         \
  /*check that the prepared object is not busy*/                                                                                                      \
  OdTv##GeometryName##DataWrapper* pInterfaceWrapper = static_cast<OdTv##GeometryName##DataWrapper*>(OdTvSmartPtrAccess<OdTv##GeometryName##Data>::get(&m_##GeometryName##DataInterface));        \
  if ( pInterfaceWrapper && !pInterfaceWrapper->isBusy() )                                                                                            \
  {                                                                                                                                                   \
    pInterfaceWrapper->assign(pData);                                                                                                                 \
    pInterfaceWrapper->assignEntity(parentEntityId);                                                                                                  \
    return m_##GeometryName##DataInterface;                                                                                                           \
  }                                                                                                                                                   \
  return OdTv##GeometryName##DataWrapper::createObject(false, pData, parentEntityId);                                                                        

#include "TD_PackPop.h"
#endif // _ODTV_INTERFACEWRAPPERSPOOL_H_INCLUDED_


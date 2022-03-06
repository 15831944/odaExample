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

#ifndef __DBGSMANAGER_H_INCLUDED_
#define __DBGSMANAGER_H_INCLUDED_

class OdTvDbObjectId;
class OdTvDbViewport;
class OdTvDbDatabase;
class OdTvGiContextForDbDatabase;

#include "Gs/Gs.h"
#include "DbExport.h"

#include "TD_PackPush.h"

/** \details
    Corresponding C++ library: TD_Db
    <group OdGs_Classes> 
*/
class TOOLKIT_EXPORT OdTvGsLayoutHelper : public OdGsDevice
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGsLayoutHelper);
  /** \details
    Returns the Layout object associated with this LayoutHelper object.
  */
  virtual OdTvDbObjectId layoutId() const = 0;
  /** \details
    Returns the active GsView object of the Layout object associated with this LayoutHelper object.
  */
  virtual OdGsViewPtr activeView() const = 0;
  /** \details
    Sets the active GsView object of the Layout object associated with this LayoutHelper object.
    \param pView [in]  Pointer to the GsView.
  */
  virtual void makeViewActive(OdGsView* pView) = 0;
  /** \details
    Return the OdGsModel object associated with this layout helper.
  */
  virtual OdGsModel* gsModel() = 0;

  /** \details
    Returns the underlying OdGsDevice object associated with this LayoutHelper object.
  */
  virtual OdGsDevicePtr underlyingDevice() const = 0;

  /** \details
    Sets the active viewport
    \param at [in]  Pick point in device coordinates.
  */
  virtual bool setActiveViewport(const OdGePoint2d& screenPt) = 0;

  /** \details
    \param id [in]  ObjectId of viewport which will be made active.
  */
  virtual bool setActiveViewport(const OdTvDbObjectId& id) = 0;

  /** \details
    Restores layout GsView database linkages state.
  */
  virtual void restoreGsViewDbLinkState() = 0;

  /** \details
    Checks does underlying device supports Gs state saving/loading.
  */
  virtual bool supportLayoutGsStateSaving() const = 0;
  /** \details
    Stores Gs state compatible with this LayoutHelper object.
    \param pStream [in]  Pointer onto OdStreamBuf object into which Gs state will be stored.
    \param nFlags [in]  Optional flags.
  */
  virtual bool storeLayoutGsState(OdStreamBuf* pStream, OdUInt32 nFlags = 0) const = 0;
  /** \details
    Extracts Layout object Id from Gs state stream.
    \param pStream [in]  Pointer onto OdStreamBuf object into which Gs state will be stored.
    \param pDb [in]  Opened database pointer.
    \param layoutObjId [out]  Layout object Id will be returned through this argument.
    \param nFlags [in]  Optional flags.
  */
  static bool extractLayoutIdForGsState(OdStreamBuf* pStream, OdTvDbDatabase *pDb, OdTvDbObjectId &layoutObjId, OdUInt32 nFlags = 0);
  /** \details
    Restores Gs state compatible with this LayoutHelper object.
    \param pStream [in]  Pointer onto OdStreamBuf object from which Gs state will be restored.
    \param nFlags [in]  Optional flags.
    \param pRetFiler [out]  Returns filer object invoked for state loading.
  */
  virtual bool restoreLayoutGsState(OdStreamBuf* pStream, OdUInt32 nFlags = 0) = 0;
};

typedef OdSmartPtr<OdTvGsLayoutHelper> OdTvGsLayoutHelperPtr;


/** \details
    Corresponding C++ library: TD_Db
    <group OdGs_Classes> 
*/
class TOOLKIT_EXPORT OdTvGsPaperLayoutHelper : public OdTvGsLayoutHelper
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGsPaperLayoutHelper);

  virtual OdGsViewPtr overallView() const = 0;
  virtual void makeViewOverall(OdGsView* pView) = 0;
  virtual void initGsView(OdGsView* pView, const OdTvDbViewport* pVp) = 0;

  virtual OdGsViewPtr addViewport(const OdTvDbViewport* pVp);
  virtual OdGsViewPtr insertViewport(int viewIndex, const OdTvDbViewport* pVp);
};

typedef OdSmartPtr<OdTvGsPaperLayoutHelper> OdTvGsPaperLayoutHelperPtr;

/** \details

    Corresponding C++ library: TD_Db
    <group OdGs_Classes> 
*/
class TOOLKIT_EXPORT OdTvGsModelLayoutHelper : public OdTvGsLayoutHelper
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGsModelLayoutHelper);
};

typedef OdSmartPtr<OdTvGsModelLayoutHelper> OdTvGsModelLayoutHelperPtr;


/** \details

    <group TD_Namespaces>
*/
namespace OdTvDbGsManager
{
  /** \details
      Populates OdGsDevice-derived object with OdGsViews-derived objects.
      Returns OdGsDevice-derived wrapper that handles some OdGsDevice's calls.
  */
  TOOLKIT_EXPORT OdTvGsLayoutHelperPtr setupActiveLayoutViews(OdGsDevice* pDevice,
    OdTvGiContextForDbDatabase* pGiCtx);

  /** \details
      Populates OdGsDevice-derived object with OdGsViews-derived objects.
      Returns OdGsDevice-derived wrapper that handles some OdGsDevice's calls.
  */
  TOOLKIT_EXPORT OdTvGsLayoutHelperPtr setupLayoutViews(OdTvDbObjectId layoutId, OdGsDevice* pDevice, 
    OdTvGiContextForDbDatabase* pGiCtx);

  /** \details
      Setups OdGsDevice-derived object with the palette associated with specified layout.
  */
  TOOLKIT_EXPORT void setupPalette(OdGsDevice* device, OdTvGiContextForDbDatabase* giContext,
    OdDbStub* layoutId = 0, ODCOLORREF palBackground = ODRGBA(0,0,0,0));
}

#include "TD_PackPop.h"

#endif // __DBGSMANAGER_H_INCLUDED_


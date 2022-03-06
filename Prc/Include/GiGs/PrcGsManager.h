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

#ifndef __PRCGSMANAGER_H_INCLUDED_
#define __PRCGSMANAGER_H_INCLUDED_

class OdPrcObjectId;
class OdPrcFile;
class OdGiContextForPrcDatabase;

#include "Gs/Gs.h"

#include "TD_PackPush.h"

/** \details
An abstract class implementing base functionality for working with layout views in PRC SDK.
<group PRC_Gs_Gi_Classes> 
*/
class PRC_TOOLKIT OdGsPrcLayoutHelper : public OdGsDevice
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGsPrcLayoutHelper);
  //DOM-IGNORE-END
  
  /** \details
  Returns the layout object identifier associated with this LayoutHelper object.
  */
  virtual OdPrcObjectId layoutId() const = 0;
  
  /** \details
  Returns the active GsView object of the layout object associated with this LayoutHelper object.
  */
  virtual OdGsViewPtr activeView() const = 0;
  
  /** \details
  Sets the active GsView object of the layout object associated with this LayoutHelper object.
  \param pView [in]  A pointer to the GsView.
  */
  virtual void makeViewActive(OdGsView* pView) = 0;
  
  /** \details
  Returns the OdGsModel object associated with this layout helper.
  */
  virtual OdGsModel* gsModel() = 0;

  /** \details
  Returns the underlying OdGsDevice object associated with this LayoutHelper object.
  */
  virtual OdGsDevicePtr underlyingDevice() const = 0;

  /** \details
  Sets the active viewport.
  \param screenPt [in] A pick point in device coordinates.
  \returns Returns true if the new active viewport was; otherwise, the method returns false.
  */
  virtual bool setActiveViewport(const OdGePoint2d& screenPt) = 0;

  /** \details
  Sets the active viewport. 
  \param id [in] An object Id of the viewport which will be made active.
  */
  virtual bool setActiveViewport(const OdPrcObjectId& id) = 0;

  /** \details
  Restores layout GsView database linkages state.
  */
  virtual void restoreGsViewDbLinkState() = 0;
};

/** \details 
This template class is a specialization of the OdSmartPtr class for OdGsPrcLayoutHelper object pointers.
*/
typedef OdSmartPtr<OdGsPrcLayoutHelper> OdGsPrcLayoutHelperPtr;

/** \details
A class implementing functionality for working with modeler bases in PRC SDK.
<group PRC_Gs_Gi_Classes> 
*/
class PRC_TOOLKIT OdGsPrcModelHelper : public OdGsPrcLayoutHelper
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGsPrcModelHelper);
  //DOM-IGNORE-END
};

/** \details 
This template class is a specialization of the OdSmartPtr class for OdGsPrcModelHelper object pointers.
*/
typedef OdSmartPtr<OdGsPrcModelHelper> OdGsPrcModelHelperPtr;


/** \details
Contains common functions for working with Gs objects.
*/
namespace OdPrcGsManager
{
  /** \details
  Sets active views for the layout.
  
  \param pDevice  [in] A pointer to a Gs device.
  \param pGiCtx   [in] A pointer to a PRC database context.
  
  \returns Returns an OdGsDevice-derived wrapper that handles some OdGsDevice object calls.
  */
  PRC_TOOLKIT OdGsPrcLayoutHelperPtr setupActiveLayoutViews(OdGsDevice* pDevice,
    OdGiContextForPrcDatabase* pGiCtx);

  /** \details
  Sets layout views. 
  
  \param layoutId [in] A layout object identifier.
  \param pDevice  [in] A pointer to a Gs device. 
  \param pGiCtx   [in] A pointer to a PRC database context.
  
  \returns Returns an OdGsDevice-derived wrapper that handles some OdGsDevice object calls.
  */
  PRC_TOOLKIT OdGsPrcLayoutHelperPtr setupLayoutViews(OdPrcObjectId layoutId, OdGsDevice* pDevice, 
    OdGiContextForPrcDatabase* pGiCtx);

  /** \details
  Sets up an OdGsDevice-derived object with a palette associated with a specified layout.
  
  \param device         [in] A pointer to a Gs device. 
  \param giContext      [in] A pointer to a PRC database context.
  \param layoutId       [in] A pointer to a lyaout object identifier.
  \param palBackground  [in] A palette background color.
  */
  PRC_TOOLKIT void setupPalette(OdGsDevice* device, OdGiContextForPrcDatabase* giContext,
    OdDbStub* layoutId = 0, ODCOLORREF palBackground = ODRGBA(0,0,0,0));
}

#include "TD_PackPop.h"

#endif // __PRCGSMANAGER_H_INCLUDED_


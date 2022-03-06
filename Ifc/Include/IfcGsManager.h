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

#ifndef _IFC_GSMANAGER_H_
#define _IFC_GSMANAGER_H_

#include "IfcBuildOptions.h"

class OdDAIObjectId;
class OdIfcFile;
class OdGiContextForIfcDatabase;

#include "Gs/Gs.h"

/** \details
An abstract class that implements base functionality for working with layout views.
*/
class IFCCORE_EXPORT OdGsIfcLayoutHelper : public OdGsDevice
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGsIfcLayoutHelper);
  //DOM-IGNORE-END

  /** \details
  Retrieves the current layout identifier.
  \returns Returns the layout object's identifier associated with the object.
  */
  virtual OdDAIObjectId layoutId() const = 0;

  /** \details
  Retrieves the current active Gs view object associated with the object.
  \returns Returns a smart pointer to the <exref target="https://docs.opendesign.com/tv/OdGsView.html">OdGsView</exref> object.
  */
  virtual OdGsViewPtr activeView() const = 0;

  /** \details
  Sets a new active Gs view for the layout associated with the object.
  \param pView [in]  A raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsView.html">OdGsView</exref> object.
  */
  virtual void makeViewActive(OdGsView* pView) = 0;

  /** \details
  Retrieves the current Gs model instance associated with the object.
  \returns Returns a raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsModel.html">OdGsModel</exref> object associated with the object.
  */
  virtual OdGsModel* gsModel() = 0;

  /** \details
  Retrieves the current underlying Gs device object associated with the object.
  \returns Returns a smart pointer to the <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">OdGsDevice</exref> underlying object associated with the object.
  */
  virtual OdGsDevicePtr underlyingDevice() const = 0;

  /** \details
  Sets a new active viewport for the object.
  \param screenPt [in] A pick point in the device coordinates that defines the viewport.
  \returns Returns true if the new active viewport was successfully set; otherwise, the method returns false.
  */
  virtual bool setActiveViewport(const OdGePoint2d& screenPt) = 0;

  /** \details
  Sets a new active viewport for the object.
  \param id [in] An identifier of the new viewport object that should be set as active.
  \returns Returns true if the new active viewport was successfully set; otherwise, the method returns false.
  */
  virtual bool setActiveViewport(const OdDAIObjectId& id) = 0;

  /** \details
  Restores the layout GsView database linkage state.
  */
  virtual void restoreGsViewDbLinkState() = 0;
};

/** \details 
A data type that represents a smart pointer to an <link OdGsIfcLayoutHelper, OdGsIfcLayoutHelper> object.
*/
typedef OdSmartPtr<OdGsIfcLayoutHelper> OdGsIfcLayoutHelperPtr;

/** \details
A class implementing functionality for working with modeler bases in IFC SDK.

Library: TD_Db

<group IFC_Gi_Gs_Classes>
*/
class IFCCORE_EXPORT OdGsIfcModelHelper : public OdGsIfcLayoutHelper
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGsIfcModelHelper);
  //DOM-IGNORE-END
};

/** \details 
A data type that represents a smart pointer to an <link OdGsIfcModelHelper, OdGsIfcModelHelper> object.
*/
typedef OdSmartPtr<OdGsIfcModelHelper> OdGsIfcModelHelperPtr;


/** \details
Contains declarations of common functions for Gs object management.
*/
namespace OdIfcGsManager
{
  /** \details
  Sets active views for the layout.
  \param reprContextId [in] An identifier of a representation context object.
  \param pDevice  [in] A raw pointer to a <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">Gs device</exref> object.
  \param pGiCtx   [in] A raw pointer to a <link OdGiContextForIfcDatabase, Gi context object> for the IFC database.
  \returns Returns a smart pointer to the <link OdGsIfcLayoutHelper, OdGsDevice-derived IFC wrapper object> that handles appropriate <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">OdGsDevice</exref> object calls.
  */
  IFCCORE_EXPORT OdGsIfcLayoutHelperPtr setupActiveLayoutViews(OdGsDevice* pDevice, OdGiContextForIfcDatabase* pGiCtx);

//DOM-IGNORE-BEGIN
  /** \details
  Sets layout views.

  \param layoutId [in] A layout object identifier.
  \param pDevice  [in] A pointer to a Gs device.
  \param pGiCtx   [in] A pointer to a PRC database context.

  \returns Returns an OdGsDevice-derived wrapper that handles OdGsDevice object calls.
  */
//DOM-IGNORE-END
//IFCCORE_EXPORT OdGsIfcLayoutHelperPtr setupLayoutViews(OdIfc::OdIfcRepresentationContextPtr layoutId, OdGsDevice* pDevice,
//  OdGiContextForIfcDatabase* pGiCtx);

  /** \details
  Sets a new palette associated with a specified layout for a specified <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">OdGsDevice</exref>-derived object.
  \param device         [in] A raw pointer to an <exref target="https://docs.opendesign.com/tv/OdGsDevice.html">OdGsDevice</exref>-derived object.
  \param giContext      [in] A raw pointer to a <link OdGiContextForIfcDatabase, Gi context object> for the IFC database.
  \param layoutId       [in] A pointer to an identifier of the layout object.
  \param palBackground  [in] A new palette background color value to be set.
  */
  IFCCORE_EXPORT void setupPalette(OdGsDevice* device, OdGiContextForIfcDatabase* giContext,
    OdDbStub* layoutId = 0, ODCOLORREF palBackground = ODRGBA(0, 0, 0, 0));
}

#endif // _IFC_GSMANAGER_H_


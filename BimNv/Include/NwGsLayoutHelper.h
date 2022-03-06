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


#ifndef __ODNWGSLAYOUTHELPER_H__
#define __ODNWGSLAYOUTHELPER_H__

#include "Gs/Gs.h"
#include "NwExport.h"

class OdNwObjectId;
class OdGiContextForNwDatabase;

#include "TD_PackPush.h"

/** \details
    Corresponding C++ library: TG_Db
    <group OdNw_Classes> 
*/
class NWDBEXPORT OdNwGsLayoutHelper : public OdGsDevice
{
  ODRX_DECLARE_MEMBERS(OdNwGsLayoutHelper);
public:
  /** Description:
    Returns the OdNwView object associated with this OdNwGsLayoutHelper object.
  */
  virtual OdNwObjectId layoutId() const = 0;
  /** Description:
    Returns the active GsView object of the OdNwView object associated with this DBDrawingHelper object.
  */
  virtual OdGsViewPtr activeView() const = 0;
  /** Description:
    Sets the active GsView object of the OdNwView object associated with this DBDrawingHelper object.
    Arguments:
    pView (I) Pointer to the GsView.
  */
  virtual void makeViewActive(OdGsView* pView) = 0;
  /** Description:
    Returns the OdGsModel object.
  */
  virtual OdGsModel* gsModel() = 0;

  /** Description:
    Returns the underlying OdGsDevice object.
  */
  virtual OdGsDevicePtr underlyingDevice() const = 0;

  /** Description:
    Sets the active viewport.
    Arguments:
    at (I) Pick point in device coordinates.
  */
  virtual bool setActiveViewport(const OdGePoint2d& screenPt) = 0;

  /** \details
    Populates the OdGsDevice-derived object with OdGsViews-derived objects.
    Returns the OdGsDevice-derived wrapper that handles some of the OdGsDevice's calls.
  */
  static OdGsDevicePtr setupLayoutView(OdNwObjectId idLayout, OdGsDevice* pDevice, OdGiContextForNwDatabase* pGiCtx);
};

typedef OdSmartPtr<OdNwGsLayoutHelper> OdNwGsLayoutHelperPtr;

#include "TD_PackPop.h"

#endif // __ODNWGSLAYOUTHELPER_H__




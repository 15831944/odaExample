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

#ifndef _ODTV_GSMANAGER_H_INCLUDED_
#define _ODTV_GSMANAGER_H_INCLUDED_

class OdTvObjectId;

#include "Gs/Gs.h"

#include "TD_PackPush.h"

/** \details
    Small extension of the OdGsDevice interface

    \remarks
    This class is used for the defenition 'OdGsDeviceForTvImpl', which is need for connection between the device and the 
    reactors system. This interface is need as a base class for the 'OdGsBaseLayoutHelperImpl'.
    Formally in TV we don't plan to use the Layouts. So we will use this inheritance only with the goal not to rewrite 
    the functionality. That's why not all methods will be rewrited and the filed 'm_layoutId' will not be used. Also for this reason this interface has less
    member that usually.
*/

class OdGsDeviceForTv : public OdGsDevice
{
public:
  ODRX_DECLARE_MEMBERS(OdGsDeviceForTv);

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
    Return the OdGsModel object associated with this device extension object.
  */
  virtual OdGsModel* gsModel() = 0;

  /** \details
    Returns the underlying OdGsDevice object associated with this device extension object.
  */
  virtual OdGsDevicePtr underlyingDevice() const = 0;

  /** \details
    send goodbye database event to the parent
  */
  virtual void transferGoodBye() = 0;
};

typedef OdSmartPtr<OdGsDeviceForTv> OdGsDeviceForTvPtr;


#include "TD_PackPop.h"

#endif //_ODTV_GSMANAGER_H_INCLUDED_


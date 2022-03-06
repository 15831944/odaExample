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

#ifndef _ODTV_GSVIEWIMPLPE_H_INCLUDED_
#define _ODTV_GSVIEWIMPLPE_H_INCLUDED_

#include "TD_PackPush.h"

#include "DbExport.h"
#include "DbAbstractViewportDataForDbVpTabRec.h"
#include "OdDbStub.h"

/** \details
This class implements the protocol extension for the ODA Visualize internal (DB) viewport table record (OdTvGsViewImpl)
We need this PE since we want to remove the calling of setViewport from
'setView' method to avoid exceptions since Gs allows to have viewport
boundaries ouside from 0.0 - 1.0 while DB restricts that
*/
class OdTvGsViewImplPE : public OdTvDbAbstractViewportDataForDbVpTabRec
{
public:
  ODRX_DECLARE_MEMBERS(OdTvGsViewImplPE);

  TD_USING(OdAbstractViewPE::setView);

  /** \details
  Applies data from one view to another view.
  \param pDestinationView [in] Input pointer to the destination view object.
  \param pSourceView [in] Input pointer to the source view object.
  */
  virtual void setView(OdRxObject* pDestinationView, const OdRxObject* pSourceView) const;
};

#include "TD_PackPop.h"

#endif //_ODTV_GSVIEWIMPLPE_H_INCLUDED_

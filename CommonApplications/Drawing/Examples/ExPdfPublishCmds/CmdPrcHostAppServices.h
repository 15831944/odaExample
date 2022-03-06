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

#ifndef _CMD_PRCHOSTAPPSERVICES_H_
#define _CMD_PRCHOSTAPPSERVICES_H_

#include "ExPrcHostAppServices.h"

/** \details
  This class implements platform-dependent operations for Publish commands for ODA PRC SDK.

  <group PRC_Protocol_Extensions_Classes>
*/
class OdCmdPrcHostAppServices : public OdExPrcHostAppServices
{
public:
  /** \details
  Creates an instance of services for platform-dependent operations for Publish commands.
  */
  OdCmdPrcHostAppServices();

  /** \details
    Sets a source application services object.
    \param pHostApp [in] A pointer to a database application services object.
  */
  virtual void setSourceHostAppServices(OdDbBaseHostAppServices* pHost);

  /** \details
  Returns the gsBitmapDevice.

  \param pViewObj [in]  OdAbstractViewPE compatible object (OdGsView, OdDbViewport or etc.).
  \param pDb [in]  Pointer to the database context.
  \param flags [in]  Bitmap device flags.

  \remarks
  Returns the gsBitmapDevice associated with this source object, if specified, in another case returns the gsBitmapDevice associated with this HostAppServices object.
  */
  virtual OdGsDevicePtr gsBitmapDevice(OdRxObject* pViewObj = NULL, OdDbBaseDatabase* pDb = NULL, OdUInt32 flags = 0);

private:
  OdDbBaseHostAppServices* m_pHost;
};

#endif  // _CMD_PRCHOSTAPPSERVICES_H_


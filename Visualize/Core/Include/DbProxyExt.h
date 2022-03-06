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




#ifndef _OD_DB_PROXY_EXT_
#define _OD_DB_PROXY_EXT_

#include "TD_PackPush.h"

#include "RxObject.h"
#include "IdArrays.h"

class OdTvDbObject;

/** \details
    This class defines in interface for 
    proxy entities and proxy objects in an OdTvDbDatabase instance.

    <group OdTvDb_Classes>
*/
class DBIO_EXPORT OdTvDbProxyExt : public OdRxObject
{
protected:
  /** \details
      Constructor (no arguments).
  */
  OdTvDbProxyExt();

public:
  ODRX_DECLARE_MEMBERS(OdTvDbProxyExt);

  /** \details
      Returns the edit flags for the class associated with this proxy.
  */
  virtual int proxyFlags(const OdTvDbObject* pProxy) const = 0;

  /** \details
      Returns the class name of the entity stored in this proxy.
  */
  virtual OdString originalClassName(const OdTvDbObject* pProxy) const = 0;

  /** \details
      Returns the DXF name of the entity stored in this proxy.
  */
  virtual OdString originalDxfName(const OdTvDbObject* pProxy) const = 0;

  /** \details
      Returns the application description for the class associated with this proxy.
  */
  virtual OdString applicationDescription(const OdTvDbObject* pProxy) const = 0;

  /** \details
      Returns the references maintained by this proxy.

      \param ids [out]  Object ID array of references contained in this proxy.
      \param types [out]  Reference type array, where each entry is associated with the 
      corresponding entry in the ids array.
  */
  virtual void getReferences(const OdTvDbObject* pProxy, OdTypedIdsArray& ids) const = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbProxyExt object pointers.
*/
typedef OdSmartPtr<OdTvDbProxyExt> OdTvDbProxyExtPtr;

#include "TD_PackPop.h"

#endif


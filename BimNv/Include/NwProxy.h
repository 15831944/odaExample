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

#ifndef __TNW_PROXY_H__
#define __TNW_PROXY_H__

#include "RxSystemServices.h"
#include "NwObject.h"

/** \details
  This class represents a proxy object.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwProxy : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwProxy);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwProxy object.
  */
  OdNwProxy();
  
  /** \details
    Constructor. Creates a new OdNwProxy object.

    \param pImpl [in] OdNwProxy implementation object.
  */
  explicit OdNwProxy(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwProxy();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  an OdNwProxy object pointers.
*/
typedef OdSmartPtr<OdNwProxy> OdNwProxyPtr;

/** \details
  This template class is a specialization of the OdArray class for
  an OdNwProxyPtr's collection.
*/
typedef OdArray<OdNwProxyPtr> OdNwGeometryProxyArray;

#endif //__TNW_PROXY_H__

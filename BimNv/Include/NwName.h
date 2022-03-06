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

#ifndef __TNW_NAME_H__
#define __TNW_NAME_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"

/** \details
  This class represents a named constant with a localized display name.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwName : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwName);
  //DOM-IGNORE-END
  
public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  OdNwName();
  
public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwName();

public:
  /** \details
    Returns the internal name (not localized).

    \returns Internal name as an OdString object.
  */
  OdString getName() const;

  /** \details
    Returns the display name (localized).

    \returns Display name as an OdString object.
  */
  OdString getDisplayName() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwName object pointers.
*/
typedef OdSmartPtr<OdNwName> OdNwNamePtr;

#endif //__TNW_NAME_H__

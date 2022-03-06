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

// IfcSite.h: interface for the OdIfcSite class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_SITE_H_
#define _IFC_SITE_H_

#include "IfcSpatialStructureElement.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details 
  A class that implements working with a site. 
  The site is a territory where a construction is allocated. 
  */
  class IFCGEOM_EXPORT OdIfcSite : public OdIfcSpatialStructureElement
  {
    ODRX_DECLARE_MEMBERS(OdIfcSite);

  public:

    /** \details 
    Composes the site object.
    */
    virtual void compose();

  };
  SMARTPTR(OdIfcSite)

}

#endif // _IFC_SITE_H_


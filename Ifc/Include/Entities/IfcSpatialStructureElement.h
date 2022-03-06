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

// IfcSpatialStructureElement.h: interface for the OdIfcSpatialStructureElement class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_SPATIALSTRUCTUREELEMENT_H_
#define _IFC_SPATIALSTRUCTUREELEMENT_H_

#include "IfcProduct.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details 
  A class that implements working with a spatial structure element. 
  This is a base class for the IFC SDK functionality related to working with spatial elements organizing them into a project structure. 
  */
  class IFCGEOM_EXPORT OdIfcSpatialStructureElement : public OdIfcProduct
  {
    ODRX_DECLARE_MEMBERS(OdIfcSpatialStructureElement);

  public:

    /** \details 
    Composes the spatial structure object.
    */
    virtual void compose();
  };
  SMARTPTR(OdIfcSpatialStructureElement)

}

#endif // _IFC_SPATIALSTRUCTUREELEMENT_H_


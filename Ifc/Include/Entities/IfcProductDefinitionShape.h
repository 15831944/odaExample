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

// IfcProductDefinitionShape.h: interface for the OdIfcProductDefinitionShape class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_PRODUCTDEFINITIONSHAPE_H_
#define _IFC_PRODUCTDEFINITIONSHAPE_H_

#include "IfcProductRepresentation.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  class OdIfcProduct;
  
  /** \details 
  A data type that represents a smart pointer to an <link OdIfc::OdIfcProduct, OdIfcProduct> object.
  */
  typedef OdSmartPtr<OdIfcProduct> OdIfcProductPtr;

  /** \details 
  A class that contains and handles shape representation data of an IFC product instance.
  */
  class IFCGEOM_EXPORT OdIfcProductDefinitionShape : public OdIfcProductRepresentation
  {
    ODRX_DECLARE_MEMBERS(OdIfcProductDefinitionShape);

  public:
    
    /** \details 
    Retrieves the shape representation of the product.
    \returns A smart pointer to the <link OdIfc::OdIfcProduct, OdIfcProduct> object.
    */
    OdIfcProductPtr shapeOfProduct();
    
    /** \details 
    Retrieves the shape representation of the product.
    \returns An object <link OdDAIObjectId, identifier> of the <link OdIfc::OdIfcProduct, OdIfcProduct> object's shape representation.
    */
    OdDAIObjectId shapeOfProduct_() const;
  };
  SMARTPTR(OdIfcProductDefinitionShape)

} //namespace OdIfc

#endif // _IFC_PRODUCTDEFINITIONSHAPE_H_

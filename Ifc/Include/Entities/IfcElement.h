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

// IfcElement.h: interface for the OdIfcElement class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_ELEMENT_H_
#define _IFC_ELEMENT_H_

#include "IfcProduct.h"

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  class OdIfcShapeRepresentation;
  typedef OdSmartPtr<OdIfcShapeRepresentation> OdIfcShapeRepresentationPtr;

  /** \details 
  A class that implements an IFC element.
  This class is a base class for all components, which are contained in a product.
  */
  class IFCGEOM_EXPORT OdIfcElement : public OdIfcProduct
  {
    ODRX_DECLARE_MEMBERS(OdIfcElement);

  public:
  
    /** \details 
    Composes the element object.
    \param pFile [in] A raw pointer to an OdIfcFile object.
    */
    virtual void compose();
    
    /** \details 
    Subtract openings of the element object.
    \param hasOpenings [in] An array of identifiers, which refer to openings.
    \param pThisSR     [in] A raw pointer to an OdIfcShapeRepresentation object.
    */
    void subtractOpenings(const OdDAIObjectIds& hasOpenings, OdIfcShapeRepresentationPtr pThisSR);
  };
  SMARTPTR(OdIfcElement)

}

#endif // _IFC_ELEMENT_H_

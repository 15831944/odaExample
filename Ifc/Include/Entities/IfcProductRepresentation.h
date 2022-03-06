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

// IfcProductRepresentation.h: interface for the OdIfcProductRepresentation class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_PRODUCTREPRESENTATION_H_
#define _IFC_PRODUCTREPRESENTATION_H_

#include "IfcCachedCompound.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  class OdIfcShapeRepresentation;
  typedef OdSmartPtr<OdIfcShapeRepresentation> OdIfcShapeRepresentationPtr;

  /** \details 
  A class that stores and handles a geometric or topological representation of a product entity. 
  Any product instance can have more than one geometry representation but only one of them can be shared for usage by external products. 
  The mapped representations are used for sharing geometry representations.
  */
  class IFCGEOM_EXPORT OdIfcProductRepresentation : public OdIfcCachedCompound
  {
    ODRX_DECLARE_MEMBERS(OdIfcProductRepresentation);

  public:

    /** \details 
    Composes the representation item object.
    */
    virtual void compose();

    /** \details 
    Retrieves the current name of the product representation.
    \returns A string that contains the product representation's name.
    */
    OdString getName();
    
    /** \details 
    Retrieves the current description of the product representation.
    \returns A string that contains the product representation's description.
    */
    OdString getDescription();
    
    /** \details 
    Retrieves all the product's representations.
    \returns An array of <link OdDAIObjectId, DAI identifiers>, which refer to the product's representations.
    */
    OdDAIObjectIds getRepresentations();

    /** \details 
    Retrieves a concrete product's representation by its identifier.
    \param representationIdentifier [in] A string that contains the required representation's identifier.
    \returns A smart pointer to an <link OdIfc::OdIfcShapeRepresentation, OdIfcShapeRepresentation> object.
    \remarks 
    If the representation object with the specified identifier is not found the NULL-pointer is returned.
    */
    OdIfcShapeRepresentationPtr getRepresentationById(const OdString &representationIdentifier);

  };
  SMARTPTR(OdIfcProductRepresentation)

} //namespace OdIfc

#endif // _IFC_PRODUCTREPRESENTATION_H_

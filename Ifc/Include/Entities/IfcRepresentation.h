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

// IfcRepresentation.h: interface for the OdIfcRepresentation class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_REPRESENTATION_H_
#define _IFC_REPRESENTATION_H_

#include "IfcCachedCompound.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details
  A base class that implements an interface for working with product representations. 
  */
  class IFCGEOM_EXPORT OdIfcRepresentation : public OdIfcCachedCompound
  {
    ODRX_DECLARE_MEMBERS(OdIfcRepresentation);

  public:
  
    /** \details 
    Composes the representation item object.
    */
    virtual void compose();

    /** \details 
    Retrieves the representation identifier.
    \returns A string that contains the representation identifier.
    */
    OdString getRepresentationIdentifier();
    
    /** \details 
    Retrieves the representation type.
    \returns A string that contains the representation type.
    */
    OdString getRepresentationType();
    
    /** \details 
    Retrieves the associated product representation.
    \returns A <link OdDAIObjectId, DAI identifier> of the product representations.
    */
    OdDAIObjectId getOfProductRepresentation() const;
    
    /** \details 
    Retrieves the representation items context.
    \returns A <link OdDAIObjectId, DAI identifier> that refers to the items context object.
    */
    OdDAIObjectId getContextOfItems();
    
    /** \details 
    Retrieves the representation items.
    \returns An array of <link OdDAIObjectId, DAI identifiers>, which refer to the representation items.
    */
    const OdDAIObjectIds& getItems();

  };
  SMARTPTR(OdIfcRepresentation)

}

#endif // _IFC_REPRESENTATION_H_


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

// OdIfcProduct.h: interface for the OdIfcProduct class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_PRODUCT_H_
#define _IFC_PRODUCT_H_

#include "IfcObjectDefinition.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  class OdIfcGeometricRepresentationItem;
  SMARTPTR(OdIfcGeometricRepresentationItem)

  /**\details 
  A class that implements a high-level wrapper over the IfcProduct that is needed for generation and visualization of product geometry.  
  */
  class IFCGEOM_EXPORT OdIfcProduct : public OdIfcObjectDefinition
  {
    ODRX_DECLARE_MEMBERS(OdIfcProduct);

  public:

    /** \details 
    Sets the values of the object's subentity traits, and returns the object's subentity traits to the calling subroutine. 
    \param traits [in] A raw pointer to the <exref  target="https://docs.opendesign.com/tv/OdGiDrawableTraits.html">OdGiDrawableTraits</exref> object to be set. 
    \returns A set of flags represented with an unsigned 32-bit integer value.
    \remarks
    When re-implementing this method, use the &quot;or&quot; bit operation (|) for the return value of the parent class' subSetAttributes() method and any flags you have added. 
    \sa 
    <exref target="https://docs.opendesign.com/tv/OdGiDrawableTraits.html">OdGiDrawableTraits</exref> class documentation.
    */
    OdUInt32 subSetAttributes(OdGiDrawableTraits * traits) const;
    
    /**\details 
    Draws the graphical representation of the product object that is independent of any viewport contexts.
    \param wd [in] A raw pointer to the <exref  target="https://docs.opendesign.com/tv/OdGiDrawable.html">OdGiDrawable</exref> object that encapsulates parameters of view port independent vectorization.  
    \returns true if the drawing was successful; otherwise, the method returns false.
    */
    virtual bool subWorldDraw(OdGiWorldDraw * wd) const;
    
    /**\details
    Retrieves the current geometrical extents of the production object.
    \param ext [out] A placeholder for the current geometry extents object to be returned to a calling subroutine.  
    \returns eOk if the current extents were successfully returned; otherwise, the method returns an appropriate error code.
    \remarks 
    The method accepts an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGeExtents3d.html">OdGeExtents3d</exref> class, 
    fills it with the data about the model's extents, and returns it to a calling subroutine.
    */
    OdResult getGeomExtents(OdGeExtents3d& ext) const;

    /** \details 
    Composes the representation item object.
    */
    virtual void compose();
    
    /** \details 
    Retrieves the shape representation of the product.
    \returns An object <link OdDAIObjectId, identifier> of the <link OdIfc::OdIfcProduct, product> shape representation.
    */
    OdDAIObjectId getRepresentation() const;
    
    /** \details 
    Retrieves the product object's placement.
    \returns A <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix3d.html">matrix</exref> object that represents the product object's placement.
    */
    OdGeMatrix3d getObjectPlacement() const;

    /** \details 
    Retrieves representation items of the product object.
    \returns An array of smart pointers to  <link OdIfc::OdIfcRepresentationItem, OdIfcGeometricRepresentationItem> objects. 
    */
    OdIfcGeometricRepresentationItemPtrArray getGeometricRepresentationItems() const;

  };
  SMARTPTR(OdIfcProduct)

}

#endif // _IFC_PRODUCT_H_

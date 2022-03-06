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

// IfcRepresentationItem.h: interface for the OdIfcRepresentationItem class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_REPRESENTATIONITEM_H_
#define _IFC_REPRESENTATIONITEM_H_

#include "Gi/GiWorldDraw.h"

#include "IfcCachedCompound.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details 
  The class that implements work with a representation items for IFC SDK.
  */
  class IFCGEOM_EXPORT OdIfcRepresentationItem : public OdIfcCachedCompound
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcRepresentationItem);
    //DOM-IGNORE-END

  public:
    
    /** \details 
    Destroys the representation item object.
    */
    virtual ~OdIfcRepresentationItem();

    /** \details 
    Composes the representation item object.
    */
    virtual void compose();

    /** \details 
      Draws the representation item to the <exref target="https://docs.opendesign.com/tv/OdGiWorldDraw.html">OdGiWorldDraw interface</exref>.
      \param pWd [in] A raw pointer to the object for the entity-level vectorization.
      \returns true if the representation item was successfully drawn; otherwise, the method returns false.
    */
    virtual bool draw(OdGiWorldDraw* pWd) const;

    /** \details 
    Sets the values of the representation item's sub-entity traits.
    \param pTraits [out] A raw pointer to the traits to be filled and returned to a calling subroutine.  
    \returns The result of the value setting.
    */
    virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
    
    /** \details 
    Draws graphical representation of the item that is independent on any view port contexts.
    \param wd [in] A raw pointer to the object that encapsulates parameters of view port independent vectorization. 
    \returns true if the drawing was successful; otherwise, the method returns false.
    */
    virtual bool subWorldDraw(OdGiWorldDraw * wd) const;
    
    /** \details 
    Transforms the representation item by a specified transformation matrix.
    \param transform [in] A transformation matrix object.
    \returns eOk if the transformation operation succeeds; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult transfromBy(const OdGeMatrix3d &transform);

  //DOM-IGNORE-BEGIN
  protected:
    void updateTraitsAuxData(OdGiWorldDraw * wd) const;
    void resetTraitsAuxData(OdGiWorldDraw * wd) const;
    OdResult setAttributes(OdGiWorldDraw* pWd) const;
    friend class OdIfcShapeRepresentation;
  //DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdIfc::OdIfcRepresentationItem, OdIfcRepresentationItem> object.
  */
  typedef OdSmartPtr<OdIfcRepresentationItem> OdIfcRepresentationItemPtr;

}

#endif // _IFC_REPRESENTATIONITEM_H_


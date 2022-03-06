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

// IfcShapeRepresentation.h: interface for the OdIfcShapeRepresentation class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IFC_SHAPEREPRESENTATION_H_
#define _IFC_SHAPEREPRESENTATION_H_

#include "IfcRepresentation.h"

/** \details
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details 
  A class that implements storing and handling of a shape geometric representation of a product or its component.
  */
  class OdIfcShapeRepresentation : public OdIfcRepresentation
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcShapeRepresentation);

    OdGeMatrix3d m_drawTransf;
    //DOM-IGNORE-END
    
  public:

    /** \details 
    Composes the representation item object.
    */
    virtual void compose();
    
    /** \details 
    Sets the values of the representation item's sub-entity traits.
    \param traits [out] A raw pointer to the traits to be filled and returned to a calling subroutine.  
    \returns The result of the value setting.
    */
    OdUInt32 subSetAttributes(OdGiDrawableTraits * traits) const;
    
    /** \details 
    Draws graphical representation of the item that is independent on any view port contexts.
    \param pWd [in] A raw pointer to the object that encapsulates parameters of view port independent vectorization. 
    \returns true if the drawing was successful; otherwise, the method returns false.
    */
    bool subWorldDraw(OdGiWorldDraw* pWd) const;
    
    /**\details
    Retrieves the current geometrical extents of the production object.
    \param ext [out] A placeholder for the current geometry extents object to be returned to a calling subroutine.  
    \returns eOk if the current extents were successfully returned; otherwise, the method returns an appropriate error code.
    \remarks 
    The method accepts an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGeExtents3d.html">OdGeExtents3d</exref> class, 
    fills it with the data about the model's extents, and returns it to a calling subroutine.
    */
    OdResult getGeomExtents(OdGeExtents3d& ext) const;

  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdIfc::OdIfcShapeRepresentation, OdIfcShapeRepresentation> object.
  */
  typedef OdSmartPtr<OdIfcShapeRepresentation> OdIfcShapeRepresentationPtr;

} //namespace OdIfc

#endif // _IFC_SHAPEREPRESENTATION_H_

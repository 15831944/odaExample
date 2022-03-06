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

// IfcProject.h: interface for the OdIfcProject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_PROJECT_H_
#define _IFC_PROJECT_H_

#include "IfcObjectDefinition.h"

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

/** \details 
A class that implements storing and handling data about an IFC project.
The project determines the design, construction, and maintenance context of a product.
*/
class IFCGEOM_EXPORT OdIfcProject : public OdIfcObjectDefinition
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcProject);

  OdDAIObjectIds arrangeContexts(const OdDAIObjectIds &ids) const;
  //DOM-IGNORE-END
public:

  /** \details 
  Composes the project object.
  */
  virtual void compose();

  /** \details 
  Retrieves the unit context identifier of the project.
  \returns An DAI object identifier of the unit's context.
  */
  OdDAIObjectId getUnitsInContextId();
  
  /** \details 
  Retrieves the project phase.
  \returns A string that contains the phase name.
  */
  OdString getPhase();
  
  /** \details 
  Retrieves the project's long name.
  \returns A string that contains the project's long name.
  */
  OdString getLongName();
  
  /** \details 
  Retrieves the project's representation context.
  \returns An array of DAI object identifiers, which refer to the representation context objects.
  */
  OdDAIObjectIds getRepresentationContexts();

    /**\details 
    Draws the graphical representation of the project object that is independent of any viewport contexts.
    \param pWd [in] A raw pointer to the <exref  target="https://docs.opendesign.com/tv/OdGiDrawable.html">OdGiDrawable</exref> object that encapsulates parameters of view port independent vectorization.  
    \returns true if the drawing was successful; otherwise, the method returns false.
    */
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const ODRX_OVERRIDE;
  
  /** \details 
  Sets the values of the object's subentity traits, and returns the object's subentity traits to the calling subroutine. 
  \param pTraits [in] A raw pointer to the <exref  target="https://docs.opendesign.com/tv/OdGiDrawableTraits.html">OdGiDrawableTraits</exref> object to be set. 
  \returns A set of flags represented with an unsigned 32-bit integer value.
  \remarks
  When re-implementing this method, use the &quot;or&quot; bit operation (|) for the return value of the parent class' subSetAttributes() method and any flags you have added. 
  \sa 
  <exref target="https://docs.opendesign.com/tv/OdGiDrawableTraits.html">OdGiDrawableTraits</exref> class documentation.
  */
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

};

/** \details
A data type that represents a smart pointer to an <link OdIfc::OdIfcProject, OdIfcProject> object.
*/
SMARTPTR(OdIfcProject);

}

#endif // _IFC_PROJECT_H_

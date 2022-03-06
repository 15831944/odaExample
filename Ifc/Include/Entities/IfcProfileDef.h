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

// OdIfcProfileDef.h: interface for the OdIfcProfileDef class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IFC_PROFILEDEF_H_
#define _IFC_PROFILEDEF_H_

#include "IfcCompound.h"

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc {

  /** \details
  A base class that implements storing and handling data about a definition of an IFC profile.
  */
  class IFCGEOM_EXPORT OdIfcProfileDef : public OdIfcCompound
  {
    ODRX_DECLARE_MEMBERS(OdIfcProfileDef);

  public:

    /**\details 
    Retrieves an array of contours, which defines the profile object.
    \returns An array of smart pointers to curve objects, which defines the profile.
    */    
    const OdArray<OdGeCurve2dPtrArray>& getContours() const;

    /** \details 
    Retrieves the profile object's name.
    \returns A string that contains the profile's name.
    */
    OdString getProfileName();

    //IfcProfileTypeEnum getProfileType();

  //DOM-IGNORE-BEGIN
  protected:
    OdArray<OdGeCurve2dPtrArray> m_Contour2dArray;
  //DOM-IGNORE-END
  };
  SMARTPTR(OdIfcProfileDef)

}

#endif // _IFC_PROFILEDEF_H_


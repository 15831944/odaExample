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

#ifndef __TNW_MATERIAL_ATTRIBUTE_H__
#define __TNW_MATERIAL_ATTRIBUTE_H__

#include "NwAttribute.h"

class OdNwColor;

/** \details
  This class represents an attribute with material data.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwMaterialAttribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwMaterialAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwMaterialAttribute
    class.
  */
  OdNwMaterialAttribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwMaterialAttribute();

public:
  /** \details
    Returns the ambient color of this material attribute.

    \returns Ambient color of this material as an OdNwColor object.
  */
  OdNwColor getAmbient() const;

  /** \details
    Returns the diffuse color of this material attribute.

    \returns Diffuse color of this material as an OdNwColor object.
  */
  OdNwColor getDiffuse() const;
  
  /** \details
    Returns the specular color of this material attribute.

    \returns Specular color of this material as an OdNwColor object.
  */
  OdNwColor getSpecular() const;
  
  /** \details
    Returns the emissive color of this material attribute.

    \returns Emissive color of this material as an OdNwColor object.
  */
  OdNwColor getEmissive() const;

  /** \details
    Returns the shininess of this material attribute.

    \returns Shininess of the material as a double value.
  */
  double getShininess() const;

  /** \details
    Returns the transparency of this material.

    \returns Transparency of the material as a double value.
  */
  double getTransperency() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwMaterialAttribute object pointers.
*/
typedef OdSmartPtr<OdNwMaterialAttribute> OdNwMaterialAttributePtr;

#endif //__TNW_MATERIAL_ATTRIBUTE_H__

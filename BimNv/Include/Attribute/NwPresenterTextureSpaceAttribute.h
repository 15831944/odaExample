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

#ifndef __TNW_PRESENTER_TEXTURE_SPACE_ATTRIBUTE_H__
#define __TNW_PRESENTER_TEXTURE_SPACE_ATTRIBUTE_H__

#include "NwAttribute.h"
#include "NwTextureSpaceMapping.h"

/** \details
  This class represents an attribute with presenter material object.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwPresenterTextureSpaceAttribute : public OdNwAttribute
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwPresenterTextureSpaceAttribute);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwPresenterTextureSpaceAttribute
    class.
  */
  OdNwPresenterTextureSpaceAttribute();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwPresenterTextureSpaceAttribute();

public:
  /** \details
    Returns the texture space mapping type.
    
    \returns Texture space mapping type as an NwTextureSpaceMapping::Enum value.
    
    \remarks
    The type must be one of the following:
    
    <table>
    Name                                Value     Description
    NwTextureSpaceMapping::kBox         0x00      Box space mapping.
    NwTextureSpaceMapping::kPlane       0x01      Plane space mapping.
    NwTextureSpaceMapping::kCylinder    0x00      Cylinder space mapping.
    NwTextureSpaceMapping::kSphere      0x01      Sphere space mapping.
    NwTextureSpaceMapping::kExplicit    0x01      Explicit space mapping.
    </table>
  */
  NwTextureSpaceMapping::Enum getMapping() const;

  /** \details
    Returns the shader name for the texture space.
    
    \returns Shader name for the the texture space of the attribute.
  */
  OdString getShaderName() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwPresenterTextureSpaceAttribute object pointers.
*/
typedef OdSmartPtr<OdNwPresenterTextureSpaceAttribute> OdNwPresenterTextureSpaceAttributePtr;

#endif //__TNW_PRESENTER_TEXTURE_SPACE_ATTRIBUTE_H__

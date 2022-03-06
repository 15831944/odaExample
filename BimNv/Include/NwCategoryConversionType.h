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


#ifndef TNW_CATEGORY_CONVERSION_TYPE_H_
#define TNW_CATEGORY_CONVERSION_TYPE_H_

/** \details
  Contains category conversation type definitions.

  <group TNW_Namespaces>
*/
namespace NwCategoryConversionType
{
  /** \details
    Attribute's type masks for selective conversion to model item category.
  */
  enum Enum
  {
    /** Material attribute. */
    Material = 0x0001,
    /** Translation and rotation attribute. */
    TransRotation = 0x0002,
    /** Translation attribute. */
    Translation = 0x0004,
    /** Transform attribute. */
    Transform = 0x0008,
    /** OdUInt64 attribute. */
    OdUInt64 = 0x0010,
    /** Property attribute. */
    Property = 0x0020,
    /** URL attribute. */
    URL = 0x0040,
    /** Presenter material attribute. */
    PresenterMaterial = 0x0080,
    /** Graphic material attribute. */
    GraphicMaterial = 0x0100,
    /** Publish attribute. */
    Publish = 0x0200,
    /** Property override attribute. */
    PropertyOverride = 0x0400,
    /** GUID. */
    Guid = 0x0800,
    /** Hyperlinks override attribute. */
    HyperlinksOverride = 0x1000,
    /** Name attribute. */
    Name = 0x2000,
    /** Binary attribute. */
    Binary = 0x4000,
    /** Presenter texture space attribute. */
    PresenterTextureSpace = 0x8000
  };
}
#endif  // TNW_CATEGORY_CONVERSION_TYPE_H_

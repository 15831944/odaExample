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


#ifndef TNW_TEXTURE_VALUE_TYPE_H_
#define TNW_TEXTURE_VALUE_TYPE_H_

/** \details
  This namespace contains texture value type defititions.

  <group TNW_Namespaces>
*/
namespace NwTextureValueType
{
  /** \details
    This enumeration defines bit masks for getting types of values from a texture.
  */
  enum Enum
  {
    /** OdString value with the path to the pattern of a texture */
    pattern_path           = 0,
    /** OdString value with the original path to the pattern of a texture */
    pattern_original_path,
    /** Double value with real-world y scale of the pattern of a texture */
    pattern_scale_x_value,
    /** Unit value for the real-world x scale of the pattern of a texture */
    pattern_scale_x_unit,
    /** Double value with the real-world y scale of the pattern of a texture */
    pattern_scale_y_value,
    /** Unit value for the real-world y scale of the pattern of a texture */
    pattern_scale_y_unit,
    /** Double value with the real-world x offset of the pattern of a texture */
    pattern_offset_x_value,
    /** Unit value for the real-world x offset of the pattern of a texture */
    pattern_offset_x_unit,
    /** Double value with the real-world y offset of the pattern of a texture */
    pattern_offset_y_value,
    /** Unit value for the real-world y offset of the pattern of a texture */
    pattern_offset_y_unit,
    /** Double value with u scale of the pattern of a texture */
    pattern_scale_u_value,
    /** Double value with v scale of the pattern of a texture */
    pattern_scale_v_value,
    /** Double value with u offset of the pattern of a texture */
    pattern_offset_u_value,
    /** Double value with v offset of the pattern of a texture */
    pattern_offset_v_value,
    /** Raster image of the pattern of a texture */
    pattern_raster_image,
    /** OdGeMatrix3d with mapping transform of pattern texture */
    pattern_transform_mapping,
    /** OdString value with the path to the diffuse of a texture */
    diffuse_path,
    /** OdString value with the original path to the diffuse of a texture */
    diffuse_original_path,
    /** Double value with real-world y scale of the diffuse of a texture */
    diffuse_scale_x_value,
    /** Unit value for the real-world x scale of the diffuse of a texture */
    diffuse_scale_x_unit,
    /** Double value with the real-world y scale of the diffuse of a texture */
    diffuse_scale_y_value,
    /** Unit value for the real-world y scale of the diffuse of a texture */
    diffuse_scale_y_unit,
    /** Double value with the real-world x offset of the diffuse of a texture */
    diffuse_offset_x_value,
    /** Unit value for the real-world x offset of the diffuse of a texture */
    diffuse_offset_x_unit,
    /** Double value with the real-world y offset of the diffuse of a texture */
    diffuse_offset_y_value,
    /** Unit value for the real-world y offset of the diffuse of a texture */
    diffuse_offset_y_unit,
    /** Double value with u scale of the diffuse of a texture */
    diffuse_scale_u_value,
    /** Double value with v scale of the diffuse of a texture */
    diffuse_scale_v_value,
    /** Double value with u offset of the diffuse of a texture */
    diffuse_offset_u_value,
    /** Double value with v offset of the diffuse of a texture */
    diffuse_offset_v_value,
    /** Raster image of the diffuse of a texture */
    diffuse_raster_image,
    /** OdGeMatrix3d with mapping transform of diffuse texture */
    diffuse_transform_mapping,
    /** OdString value with the path to the opacity of a texture */
    opacity_path,
    /** OdString value with the original path to the opacity of a texture */
    opacity_original_path,
    /** Double value with real-world y scale of the opacity of a texture */
    opacity_scale_x_value,
    /** Unit value for the real-world x scale of the opacity of a texture */
    opacity_scale_x_unit,
    /** Double value with the real-world y scale of the opacity of a texture */
    opacity_scale_y_value,
    /** Unit value for the real-world y scale of the opacity of a texture */
    opacity_scale_y_unit,
    /** Double value with the real-world x offset of the opacity of a texture */
    opacity_offset_x_value,
    /** Unit value for the real-world x offset of the opacity of a texture */
    opacity_offset_x_unit,
    /** Double value with the real-world y offset of the opacity of a texture */
    opacity_offset_y_value,
    /** Unit value for the real-world y offset of the opacity of a texture */
    opacity_offset_y_unit,
    /** Double value with u scale of the opacity of a texture */
    opacity_scale_u_value,
    /** Double value with v scale of the opacity of a texture */
    opacity_scale_v_value,
    /** Double value with u offset of the opacity of a texture */
    opacity_offset_u_value,
    /** Double value with v offset of the opacity of a texture */
    opacity_offset_v_value,
    /** Raster image of the opacity of a texture */
    opacity_raster_image,
    /** OdGeMatrix3d with mapping transform of opacity texture */
    opacity_transform_mapping,
    /** OdString value with the path to the bump of a texture */
    bump_path,
    /** OdString value with the original path to the bump of a texture */
    bump_original_path,
    /** Double value with real-world y scale of the bump of a texture */
    bump_scale_x_value,
    /** Unit value for the real-world x scale of the bump of a texture */
    bump_scale_x_unit,
    /** Double value with the real-world y scale of the bump of a texture */
    bump_scale_y_value,
    /** Unit value for the real-world y scale of the bump of a texture */
    bump_scale_y_unit,
    /** Double value with the real-world x offset of the bump of a texture */
    bump_offset_x_value,
    /** Unit value for the real-world x offset of the bump of a texture */
    bump_offset_x_unit,
    /** Double value with the real-world y offset of the bump of a texture */
    bump_offset_y_value,
    /** Unit value for the real-world y offset of the bump of a texture */
    bump_offset_y_unit,
    /** Double value with u scale of the bump of a texture */
    bump_scale_u_value,
    /** Double value with v scale of the bump of a texture */
    bump_scale_v_value,
    /** Double value with u offset of the bump of a texture */
    bump_offset_u_value,
    /** Double value with v offset of the bump of a texture */
    bump_offset_v_value,
    /** Raster image of the bump of a texture */
    bump_raster_image,
    /** OdGeMatrix3d with mapping transform of bump texture */
    bump_transform_mapping,
  };
}
#endif  // TNW_TEXTURE_VALUE_TYPE_H_


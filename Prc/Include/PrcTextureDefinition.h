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

#ifndef _PRCTEXTUREDEFINITION_INCLUDED_
#define _PRCTEXTUREDEFINITION_INCLUDED_ 
 

#include "PrcTextureTransformation.h"
#include "PrcTextureMappingType.h"
#include "PrcBase.h"

SMARTPTR(OdPrcTextureDefinition);

/** \details 
<group PRC_Graphic_Classes> 

Class representing a group of texture parameters used in a texture application. 
*/
class PRC_TOOLKIT OdPrcTextureDefinition : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcTextureDefinition)
  //DOM-IGNORE-END
  
  /** \details
  Returns the current array of texture mapping attribute intensities.
  The array of texture mapping attribute intensities is returned as a reference to an OdGeDoubleArray object, 
  therefore it can be used to set a new array or modify the current one.
  */
  OdGeDoubleArray &textureMappingAttributesIntensities();
  
  /** \details
  Returns the current array of texture mapping attributes intensities.
  */
  const OdGeDoubleArray &textureMappingAttributesIntensities() const;
  
  /** \details
  Returns the current array of texture mapping attribute components.
  The array of texture mapping attribute components is returned as a reference to an OdArray object, 
  therefore it can be used to set a new array or modify the current one.
  */
  OdArray<char> &textureMappingAttributesComponents();
  
  /** \details
  Returns the current array of texture mapping attributes components.
  */
  const OdArray<char> &textureMappingAttributesComponents() const;
 
  /** \details
  Returns the current texture mapping type value.
  The texture mapping type is returned as a reference to an OdPrcTextureMappingType object, therefore it can be used to set a new texture mapping type value.
  */
  OdPrcTextureMappingType &textureMappingType();
  
  /** \details
  Returns the current texture mapping type value.
  */
  const OdPrcTextureMappingType &textureMappingType() const;
  
  /** \details
  Sets a new texture dimension value. 
  Generally the texture dimension can accept the following three integer values: 1, 2, 3, 
  but in the current implementation there is only one acceptable value for the texture dimension: 2. 
  Values 1 and 3 are reserved for future use.

  \param texture_dimension [in] An new texture dimension value to be set.
  */
  void setTextureDimension(OdInt8 texture_dimension);
  
  /** \details
  Returns the current texture dimension value.
  */
  OdInt8 textureDimension() const;
  
   /** \details
  Sets a new texture applying mode.

  \param texture_applying_mode [in] A new texture applying mode to be set.
  */
  void setTextureApplyingMode(OdInt8 texture_applying_mode);
  
  /** \details
  Returns the current texture applying mode.
  */
  OdInt8 textureApplyingMode() const;
  
  /** \details
  Returns current picture.
  Picture is returned as a reference to an OdPrcPicturePtr object, therefore it can be used to set new picture.
  */
  OdPrcPicturePtr & picture();

  /** \details
  Returns current picture.
  */
  const OdPrcPicturePtr & picture() const;
  
  /** \details
  Sets new texture mapping attributes.
  Texture mapping attributes are stored in a bit field which is
  used to represent an applying procedure for the texture.

  \param texture_mapping_attributes [in] New texture mapping attributes to be set. 
  */
  void setTextureMappingAttributes(OdUInt32 texture_mapping_attributes);
  
  /** \details
  Returns the current texture mapping attributes.
  */
  OdUInt32 textureMappingAttributes() const;
  
  /** \details
  Sets a new texture function value.

  \param texture_function [in] A new texture function value to be set.
  */
  void setTextureFunction(OdUInt32 texture_function);
  
  /** \details
  Returns the current texture function value.

  \returns An integer value.
  */
  OdUInt32 textureFunction() const;
  
  /** \details
  Sets a new value of the blend source of RGB color components.
  Reserved for future use.
  
  \param blend_src_rgb [in] A new value of the blend source to be set.
  */
  void setBlendSrcRgb(OdUInt32 blend_src_rgb);
  
  /** \details
  Returns the current value of the blend source of RGB color components.
  */
  OdUInt32 blendSrcRgb() const;
  
  /** \details
  Sets a new value of the blend destination of RGB color components.
  Reserved for future use.
  
  \param blend_dst_rgb [in] A new value of the blend destination to be set.
  */
  void setBlendDstRgb(OdUInt32 blend_dst_rgb);
  
  /** \details
  Returns the current value of the blend destination of RGB color components.
  */
  OdUInt32 blendDstRgb() const;
  
  /** \details
  Sets a new value of the blend source of alpha color components.
  Reserved for future use.
  
  \param blend_src_alpha [in] A new value of the blend destination to be set.
  */
  void setBlendSrcAlpha(OdUInt32 blend_src_alpha);
  
  /** \details
  Returns the current value of the blend source of alpha color components.
  */
  OdUInt32 blendSrcAlpha() const;
  
  /** \details
  Sets a new value of the blend destination alpha color components.
  Reserved for future use.
  
  \param blend_dst_alpha [in] A new value of the blend destination to be set.
  */
  void setBlendDstAlpha(OdUInt32 blend_dst_alpha);
  
  /** \details
  Returns the current value of the blend destination of alpha color components.
  */
  OdUInt32 blendDstAlpha() const;
  
  /** \details
  Sets a new value of the alpha test. Reserved for future use.
  
  \param alpha_test [in] A new value of the alpha test.
  */
  void setAlphaTest(OdUInt32 alpha_test);
  
  /** \details
  Returns the current value of the alpha test.
  */
  OdUInt32 alphaTest() const;
  
  /** \details
  Sets a new value of the repeating mode in the U direction.

  \param texture_wrapping_mode_S [in] A new value of the repeating mode in the U direction to be set.
  */
  void setTextureWrappingModeS(OdUInt32 texture_wrapping_mode_S);
  
  /** \details
  Returns the current value of the repeating mode in the U direction.
  */
  OdUInt32 textureWrappingModeS() const;
  
  /** \details
  Sets a new value of the repeating mode in the V direction.

  \param texture_wrapping_mode_T [in] A new value of the repeating mode in the V direction to be set.
  */
  void setTextureWrappingModeT(OdUInt32 texture_wrapping_mode_T);
  
  /** \details
  Returns the current value of the repeating mode in the V direction.
  */
  OdUInt32 textureWrappingModeT() const;
  
  /** \details
  Sets a new value of the repeating mode in the W direction.

  \param texture_wrapping_mode_R [in] A new value of the repeating mode in the W direction to be set.
  */
  void setTextureWrappingModeR(OdUInt32 texture_wrapping_mode_R);
  
  /** \details
  Returns the current value of the repeating mode in the V direction.
  */
  OdUInt32 textureWrappingModeR() const;
  
  /** \details
  Sets a new red color component value.

  \param red [in] A new value to be set.
  */
  void setRed(OdUInt32 red);
  
  /** \details
  Returns the current red color component value.
  */
  OdUInt32 red() const;
  
  /** \details
  Sets a new green color component value.

  \param green [in] A new value to be set.
  */
  void setGreen(OdUInt32 green);
  
  /** \details
  Returns the current green color component value.
  */
  OdUInt32 green() const;
  
  /** \details
  Sets a new blue color component value.

  \param blue [in] A new value to be set.
  */
  void setBlue(OdUInt32 blue);
  
  /** \details
  Returns the current blue color component value.
  */
  OdUInt32 blue() const;
  
  /** \details
  Sets a new alpha value.

  \param alpha [in] A new alpha value to be set.
  */
  void setAlpha(OdUInt32 alpha);
  
  /** \details
  Returns the current alpha value.
  */
  OdUInt32 alpha() const;
  
  /** \details
  Sets a new threshold value for the alpha test.

  \param alpha_test_reference [in] A new threshold value to be set.
  */
  void setAlphaTestReference(OdUInt32 alpha_test_reference);
  
  /** \details
  Returns the current threshold value for the alpha test.
  */
  OdUInt32 alphaTestReference() const;
  
  /** \details
  Returns current transformation data used in the texture definition. 
  Transformation data is returned as a reference to an OdPrcTextureTransformation object, therefore it can be used to set new transformation data.
  */
  OdPrcTextureTransformation &textureTransformation();
  
  /** \details
  Returns current transformation data used in the texture definition. 
  */
  const OdPrcTextureTransformation &textureTransformation() const;

  /** \details
  Checks if there is transformation data used in the texture definition.

  \returns Returns true if there is transformation data used in the texture definition or returns false in the other case. 
  */ 
  bool hasTextureTransformation() const;
  
  /** \details
  Removes transformation data from the texture definition.
  */
  void removeTextureTransformation();

  /** \details 
  Destroys the texture definition object.  
  */
  virtual ~OdPrcTextureDefinition();
};

#endif // _PRCTEXTUREDEFINITION_INCLUDED_


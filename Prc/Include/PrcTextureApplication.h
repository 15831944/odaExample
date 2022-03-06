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

#ifndef _PRCTEXTUREAPPLICATION_INCLUDED_
#define _PRCTEXTUREAPPLICATION_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcMaterial.h"

/** \details 
<group PRC_Graphic_Classes> 

Class representing a complex texture pipe to be applied. 
*/
class PRC_TOOLKIT OdPrcTextureApplication : public OdPrcMaterial
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcTextureApplication)
  //DOM-IGNORE-END

  /** \details
  Sets a new texture definition identifier.

  \param texture_definitionID [in] A new texture definition identifier to be set.
  */
  void setTextureDefinitionID(const OdPrcObjectId &texture_definitionID);

  /** \details
  Returns the current texture definition identifier.
  */
  OdPrcObjectId getTextureDefinitionID() const;

  /** \details
  Sets a new generic material identifier.

  \param material_genericID [in] A new generic material identifier.
  */
  void setMaterialGenericID(const OdPrcObjectId &material_genericID);

  /** \details
  Returns the current generic material identifier.
  */
  OdPrcObjectId getMaterialGenericID() const;

  /** \details
  Sets a new next texture identifier.

  \param next_textureID [in] A new next texture identifier to be set.
  */
  void setNextTextureID(const OdPrcObjectId &next_textureID);

  /** \details
  Returns the current next texture identifier. 
  */
  OdPrcObjectId getNextTextureID() const;

  /** \details
  Sets a new value for the index of texture mapping coordinates.

  \param UV_coordinates_index [in] A new index for the texture mapping coordinates.
  */
  void setUVCoordinatesIndex(OdUInt32 UV_coordinates_index);
  
  /** \details
  Returns the current value of the texture mapping coordinates index.
  */
  OdUInt32 uvCoordinatesIndex() const;

  /** \details 
  Retrieves the current true color of the texture application.
  \returns An OdCmEntityColor object that represents the true color.
  */
  OdCmEntityColor getTrueColor() const;

//DOM-IGNORE-BEGIN
protected:

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits * pTraits) const;
//DOM-IGNORE-END
};
SMARTPTR(OdPrcTextureApplication);

#endif // _PRCTEXTUREAPPLICATION_INCLUDED_


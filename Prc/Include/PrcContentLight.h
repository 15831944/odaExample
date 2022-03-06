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

#ifndef _PRCCONTENTLIGHT_INCLUDED_
#define _PRCCONTENTLIGHT_INCLUDED_ 
 

#include "PrcBase.h"
#include "PrcColorIndex.h"
#include "PrcRgbColor.h"

/** \details 
<group PRC_Graphic_Classes> 

Class stores data about a light.
*/
class PRC_TOOLKIT OdPrcContentLight : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcContentLight)
  //DOM-IGNORE-END

  /** \details
  Sets a new specular index value.

  \param specular [in] A new specular index value to be set.
  */
  void setSpecular(OdPrcColorIndex specular = OdPrcColorIndex::kUninit);
  
  /** \details
  Returns the current specular index value.
  */
  OdPrcColorIndex specular() const;

  /** \details
  Returns the specular color. Will throw an exception in case of uninitialized object.
  */
  const OdPrcRgbColor &getSpecular() const;

  /** \details
  Sets a new specular color.
  Object must be database resident.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setSpecular(double r, double g, double b, bool preventDuplication = false);
  
  /** \details
  Sets a new value of the emissive index.

  \param emissive [in] A new value of the emissive index to be set.
  */
  void setEmissive(OdPrcColorIndex emissive = OdPrcColorIndex::kUninit);
  
  /** \details
  Returns the current emissive index value.
  */
  OdPrcColorIndex emissive() const;

  /** \details
  Returns emissive color. Will throw an exception in case of uninitialized object.
  */
  const OdPrcRgbColor &getEmissive() const;

  /** \details
  Sets a new emissive color.
  Object must be database resident.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setEmissive(double r, double g, double b, bool preventDuplication = false);
  
  /** \details
  Sets a new diffuse index value.

  \param diffuse [in] A new value of the diffuse index.
  */
  void setDiffuse(OdPrcColorIndex diffuse = OdPrcColorIndex::kUninit);
  
  /** \details
  Returns the current diffuse index value.
  */
  OdPrcColorIndex diffuse() const;

  /** \details
  Returns diffuse color. Will throw an exception in case of uninitialized object.
  */
  const OdPrcRgbColor &getDiffuse() const;

  /** \details
  Sets a new diffuse color.
  Object must be database resident.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setDiffuse(double r, double g, double b, bool preventDuplication = false);
  
  /** \details
  Sets a new value of the ambient index value.

  \param ambient [in] A new value of the ambient index to be set.
  */
  void setAmbient(OdPrcColorIndex ambient = OdPrcColorIndex::kUninit);
  
  /** \details
  Returns the current value of the ambient index.
  */
  OdPrcColorIndex ambient() const;

  /** \details
  Returns ambient color. Will throw an exception in case of uninitialized object.
  */
  const OdPrcRgbColor &getAmbient() const;

  /** \details
  Sets a new ambient color.
  Object must be database resident.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setAmbient(double r, double g, double b, bool preventDuplication = false);

};

#endif // _PRCCONTENTLIGHT_INCLUDED_


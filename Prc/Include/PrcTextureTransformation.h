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

#ifndef _PRCTEXTURETRANSFORMATION_INCLUDED_
#define _PRCTEXTURETRANSFORMATION_INCLUDED_ 
 

#include "PrcTransformation2d.h"

/** \details 
<group PRC_Graphic_Classes> 

Class representing transformation data used in a texture definition.
*/
class PRC_TOOLKIT OdPrcTextureTransformation
{
private:
  OdPrcTransformation2d m_matrix_transformation;
  bool                  m_texture_flip_S;
  bool                  m_texture_flip_T;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcTextureTransformation)
  //DOM-IGNORE-END

  /** \details
  Returns current 2D transformation data.
  2D transformation data is returned as a reference to an OdPrcTransformation2d object, therefore it can be used to set a new transformation.
  */
  OdPrcTransformation2d &matrixTransformation();
  
  /** \details
  Returns current 2D transformation data.
  */
  const OdPrcTransformation2d &matrixTransformation() const;
  
  /** \details
  Sets a new value of the flip flag for the S coordinate.
  The flip flag indicates whether the S coordinate parameter is flipped (if true).

  \param texture_flip_S [in] A new flag value to be set.
  */
  void setTextureFlipS(bool texture_flip_S);
  
  /** \details
  Returns the current value of the flip flag for the S coordinate.
  The flip flag indicates whether the S coordinate parameter is flipped (if true).
  */
  bool textureFlipS() const;
  
  /** \details
  Sets a new value of the flip flag for the T coordinate.
  The flip flag indicates whether the T coordinate parameter is flipped (if true).

  \param texture_flip_T [in] A new flag value to be set.
  */
  void setTextureFlipT(bool texture_flip_T);
  
  /** \details
  Returns the current value of the flip flag for the T coordinate.
  The flip flag indicates whether the T coordinate parameter is flipped (if true).
  */
  bool textureFlipT() const;

  /** \details
  Returns the current type of the PRC object. 
  */
  OdUInt32 prcType() const;
};

#endif // _PRCTEXTURETRANSFORMATION_INCLUDED_


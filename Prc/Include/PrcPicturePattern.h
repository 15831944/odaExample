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

#ifndef _PRCVPICTUREPATTERN_INCLUDED_
#define _PRCVPICTUREPATTERN_INCLUDED_ 
 

#include "PrcMarkupTess.h"
#include "PrcFillPattern.h"

/** \details 
<group PRC_Graphic_Classes> 

Class representing a two-dimensional filling pattern based on a vectorized picture.
*/
class PRC_TOOLKIT OdPrcPicturePattern : public OdPrcFillPattern
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcPicturePattern)
  //DOM-IGNORE-END

  /** \details
  Returns the current pattern size.
  Pattern size is returned as a reference to an OdGeVector2d object, therefore it can be used to set a new size value.
  */
  OdGeVector2d &sizeOfVpattern();
  
  /** \details
  Returns the current pattern size as an OdGeVector2d object.
  */
  const OdGeVector2d &sizeOfVpattern() const;
  
  /** \details
  Returns current tessellation data of the pattern.
  Tessellation data is returned as a reference to an OdPrcMarkupTessPtr object, therefore it can be used to set a new tessellation data.
  */
  OdPrcMarkupTessPtr &tessellationData();
  
  /** \details
  Returns current tessellation data of the pattern.
  */
  const OdPrcMarkupTessPtr &tessellationData() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
  virtual void subViewportDraw (OdGiViewportDraw * pVd) const;
};
SMARTPTR(OdPrcPicturePattern);

#endif // _PRCVPICTUREPATTERN_INCLUDED_


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

#ifndef _PRCSRFTRANSFORM_INCLUDED_
#define _PRCSRFTRANSFORM_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcMath3d.h"

/** \details 
<group PRC_Surface_Classes>

Class representing a surface that is defined by a 3D mathematical transformation applied to a base surface.
*/
class PRC_TOOLKIT OdPrcTransformedSurface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcTransformedSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the transformed surface object.
  */
  ~OdPrcTransformedSurface();
  
  /** \details
  Returns the current 3D mathematical transformation of the transformed surface.
  The 3D mathematical transformation is returned as a reference to an OdPrcMath3dPtr object, therefore it can be used to set a new transformation.
  */
  OdPrcMath3dPtr &mathTransformation();
  
  /** \details
  Returns the current 3D mathematical transformation of the transformed surface.
  */
  const OdPrcMath3dPtr &mathTransformation() const;
  
  /** \details
  Sets a new base surface.

  \param value [in] A pointer to a new base surface to be set.
  
  \returns Returns eOk if a new base surface was successfully applied to the transformed surface or an appropriate error code in the other case.
  */
  OdResult setBaseSurface(const OdPrcSurfacePtr &value);
  
  /** \details
  Returns the current base surface.
  */
  const OdPrcSurfacePtr &baseSurface() const;
};

SMARTPTR(OdPrcTransformedSurface);

#endif // _PRCSRFTRANSFORM_INCLUDED_


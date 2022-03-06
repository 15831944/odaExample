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

#ifndef _PRCTEXTUREMAPPINGTYPE_INCLUDED_
#define _PRCTEXTUREMAPPINGTYPE_INCLUDED_ 
 

#include "PrcTransformation3d.h"

/** \details 
<group PRC_Graphic_Classes> 

Class representing a texture mapping type. 
*/
class PRC_TOOLKIT OdPrcTextureMappingType
{
private:
  EPRCTextureMappingType m_eMappingType;
  OdUInt32               m_eMappingOperator;
  OdPrcTransformation3d *m_CartesianTransformation3d;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcTextureMappingType)
  //DOM-IGNORE-END

  /** \details 
  Destroys the texture mapping type object.
  */
  ~OdPrcTextureMappingType();

  /** \details
  Returns current 3D cartesian transformation data.
  3D cartesian transformation data is returned as a pointer to an OdPrcTransformation3d object, therefore it can be used to set new transformation data.
  */
  OdPrcTransformation3d* cartesianTransformation3d();

  /** \details
  Returns current 3D cartesian transformation data.
  */
  const OdPrcTransformation3d* cartesianTransformation3d() const;

  /** \details
  Returns the current mapping type.
  The mapping type is returned as a reference to an EPRCTextureMappingType value, therefore it can be used to set a mapping type.
  */
  EPRCTextureMappingType &eMappingType();
  
  /** \details
  Returns the current texture mapping type.
  */
  const EPRCTextureMappingType &eMappingType() const;
  
  /** \details
  Sets a new texture mapping operator.

  \param eMappingOperator [in] A new texture mapping operator to be set.
  */
  void setEMappingOperator(OdUInt32 eMappingOperator);
  
  /** \details
  Returns the current texture mapping operator.
  */
  OdUInt32 eMappingOperator() const;
};

#endif // _PRCTEXTUREMAPPINGTYPE_INCLUDED_


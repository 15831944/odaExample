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

#ifndef _PRCCONTENTSURFACE_INCLUDED_
#define _PRCCONTENTSURFACE_INCLUDED_ 
 

#include "PrcBaseGeometry.h"

/** \details 
<group PRC_Surface_Classes> 

Class representing additional information about a surface,
for example, name of surface and attributes and how the surface extends past its boundary.
*/
class PRC_TOOLKIT OdPrcContentSurface
{
private:
  OdPrcBaseGeometry m_BaseGeometry;
  OdUInt32          m_extendInfo;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcContentSurface)
  //DOM-IGNORE-END

  /** \details
  Returns the current base information about the surface.
  The base surface information is returned as a reference to an OdPrcBaseGeometry object, therefore it can be used to set new information.
  */
  OdPrcBaseGeometry &baseGeometry();

  /** \details
  Returns the current base information about the surface.
  */
  const OdPrcBaseGeometry &baseGeometry() const;

  /** \details
  Sets new information about the surface extension.

  \param extendInfo [in] New information about the surface extension.
  */
  void set_extendInfo(OdUInt32 extendInfo);

  /** \details
  Returns the current information about the surface extension.
  */
  OdUInt32 extendInfo() const;

  /** \details
  Destroys additional information about the surface.
  */
  ~OdPrcContentSurface();
};

#endif // _PRCCONTENTSURFACE_INCLUDED_


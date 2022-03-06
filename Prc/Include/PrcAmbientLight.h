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

#ifndef _PRCAMBIENTLIGHT_INCLUDED_
#define _PRCAMBIENTLIGHT_INCLUDED_ 
 

#include "PrcContentLight.h"
SMARTPTR(OdPrcAmbientLight);

/** \details 
<group PRC_Graphic_Classes>

Class representing data about ambient illumination of a scene. 
It contains information about an entity and four indexes to describe its ambient illumination.
*/
class PRC_TOOLKIT OdPrcAmbientLight : public OdPrcContentLight
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS(OdPrcAmbientLight)
  //DOM-IGNORE-END
};

typedef OdArray<OdPrcAmbientLight> OdPrcAmbientLightArray;

#endif // _PRCAMBIENTLIGHT_INCLUDED_


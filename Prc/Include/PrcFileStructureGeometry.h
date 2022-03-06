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

#ifndef _PRCFILESTRUCTUREGEOMETRY_INCLUDED_
#define _PRCFILESTRUCTUREGEOMETRY_INCLUDED_ 
 

#include "PrcUserData.h"
#include "PrcFileStructureExactGeometry.h"
#include "PrcBase.h"

SMARTPTR(OdPrcFileStructureGeometry);

/** \details 
<group PRC_Files_Structures_Assemblies>

Class implements file structure geometry. 
File structure geometry contains exact geometry and user defined data. 
*/
class PRC_TOOLKIT OdPrcFileStructureGeometry : public OdPrcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFileStructureGeometry);
  //DOM-IGNORE-END

  /** \details 
  Returns the current exact geometry of the file structure geometry.
  The exact geometry is returned as a reference to an OdPrcFileStructureExactGeometry object, therefore it can be used to set new exact geometry.
  */
  OdPrcFileStructureExactGeometry &fileStructureExactGeometry();
  
  /** \details 
  Returns the current exact geometry of the file structure geometry.
  */
  const OdPrcFileStructureExactGeometry &fileStructureExactGeometry() const;
  
  /** \details 
  Returns current user defined data of the file structure geometry.
  User data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user data.
  */
  OdPrcUserData &userData();
  
  /** \details 
  Returns current user defined data of the file structure geometry.
  */
  const OdPrcUserData &userData() const;
};

#endif // _PRCFILESTRUCTUREGEOMETRY_INCLUDED_


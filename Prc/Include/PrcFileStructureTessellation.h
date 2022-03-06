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

#ifndef _PRCFILESTRUCTURETESSELLATION_INCLUDED_
#define _PRCFILESTRUCTURETESSELLATION_INCLUDED_ 
 

#include "PrcUserData.h"
#include "PrcBase.h"
#include "PrcBaseTessData.h"

SMARTPTR(OdPrcFileStructureTessellation);

/** \details
<group PRC_Files_Structures_Assemblies>

Class stores tessellation data of the file structure.
*/
class PRC_TOOLKIT OdPrcFileStructureTessellation : public OdPrcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFileStructureTessellation);
  //DOM-IGNORE-END

  /** \details 
  Returns current tessellations of the file structure.
  The tessellation is returned as a reference to an OdPrcBaseTessDataPtrArray object, therefore it can be used to set new tessellation data.
  */
  OdPrcBaseTessDataPtrArray &tessellations();
  
  /** \details 
  Returns current tessellations of the file structure.
  */
  const OdPrcBaseTessDataPtrArray &tessellations() const;
  
  /** \details 
  Returns current user defined data associated within the tessellation of the file structure.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();
  
  /** \details 
  Returns current user defined data of the file structure.
  */
  const OdPrcUserData &userData() const;
};

#endif // _PRCFILESTRUCTURETESSELLATION_INCLUDED_


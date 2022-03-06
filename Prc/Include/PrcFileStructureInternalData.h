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

#ifndef _PRCFILESTRUCTUREINTERNALDATA_INCLUDED_
#define _PRCFILESTRUCTUREINTERNALDATA_INCLUDED_ 
 

#include "PrcBase.h"
SMARTPTR(OdPrcFileStructureInternalData);

/** \details
<group PRC_Files_Structures_Assemblies>

Class represents an implementation of internal data of a .prc file structure.
Internal data of the file structure contains an identifier of the root product occurrence and the current available unique index for assigning entities that can be referenced within the file structure.
*/
class PRC_TOOLKIT OdPrcFileStructureInternalData : public OdPrcBase
{
  friend class OdPrcFileStructure;

  void setNextAvailableIndex(OdUInt32 value); // for internal usage

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFileStructureInternalData)
  //DOM-IGNORE-END
  
  /** \details 
  Sets a new root product occurrence identifier for the file structure.
  
  \param root_product_occurrence_ID [in] A new root product occurrence identifier to be set.
  */
  void setRootProductOccurrence (const OdPrcObjectId &root_product_occurrence_ID);

  /** \details 
  Returns the current root product occurrence identifier for the file structure.
  */
  OdPrcObjectId getRootProductOccurrenceID (void) const;

  /** \details
  Returns current user-defined data of the file structure tree.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData & userData();

  /** \details
  Returns current user-defined data of the file structure tree.
  */
  const OdPrcUserData & userData() const;
};

#endif // _PRCFILESTRUCTUREINTERNALDATA_INCLUDED_


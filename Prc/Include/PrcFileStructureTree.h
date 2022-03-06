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

#ifndef _PRCFILESTRUCTURETREE_INCLUDED_
#define _PRCFILESTRUCTURETREE_INCLUDED_ 
 

#include "PrcUserData.h"
#include "PrcFileStructureInternalData.h"
#include "PrcProductOccurrence.h"
#include "PrcPartDefinition.h"
#include "PrcBase.h"

SMARTPTR(OdPrcFileStructureTree);

/** \details
<group PRC_Files_Structures_Assemblies>

Class implements a file structure tree. 
A file structure tree contains a hierarchy of nodes representing product occurrences, part definitions, representation items, and markups.
*/
class PRC_TOOLKIT OdPrcFileStructureTree : public OdPrcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFileStructureTree);
  //DOM-IGNORE-END

  /** \details 
  Returns the current part definitions array of the file structure tree.
  The part definitions array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new part definitions array.
  Note that the method returns an array of object identifiers, but not the part definition objects themselves.
  */
  OdPrcObjectIdArray &partDefinition();
  
  /** \details 
  Returns the current part definitions array of the file structure tree represented as a constant reference to an OdPrcObjectIdArray object.
  Note that the method returns an array of object identifiers, but not the part definition objects themselves.
  */
  const OdPrcObjectIdArray &partDefinition() const;
  
  /** \details 
  Returns the current product occurrences array of the file structure tree.
  */
  const OdPrcProductOccurrencePtrArray &productOccurrence() const;
  
  /** \details 
  Returns current internal data of the file structure tree.
  Internal data is returned as a reference to an OdPrcFileStructureInternalData object, therefore it can be used to set new internal data instance.
  */
  OdPrcFileStructureInternalData &internalData();
  
  /** \details 
  Returns current internal data of the file structure tree.
  */
  const OdPrcFileStructureInternalData &internalData() const;
  
  /** \details 
  Returns current user-defined data of the file structure tree.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();
  
  /** \details 
  Returns current user defined data of the file structure tree.
  */
  const OdPrcUserData &userData() const;

  /** \details
  Regenerates productOccurrence array in correct order for input file structure.
  \param fsTree [in/out] A reference to a file structure whose productOccurrence array will be regenerated.
  */
  static void updateProductOccurrenceArray(OdPrcFileStructureTree &fsTree);
};

#endif // _PRCFILESTRUCTURETREE_INCLUDED_


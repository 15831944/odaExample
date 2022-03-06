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

#ifndef _PRCSCHEMA_INCLUDED_
#define _PRCSCHEMA_INCLUDED_ 
 

#include "UInt32Array.h"
#include "RxObject.h"

class OdPrcSchema;
SMARTPTR(OdPrcSchema);

/** \details 
<group PRC_Base_Classes>

Class implements PRC schema functionality. 
The schema stores information about the difference between PRC format versions and allows entities of a specified type to be readable by old versions of applications. 
The schema consists of an array of schema definitions for each entity type that has been changed.
The schema definition consists of entity type codes and an array of tokens which determine the type of entity. 
Each token is an array of blocks describing the PRC entity's versions.
*/
class PRC_TOOLKIT OdPrcSchema : public OdRxObject
{
public:
  /** \details
  Structure contains information about PRC schema definition.
  */
  struct schema_type_and_token
  {
    /**Entity type determined with schema definition.*/
    OdUInt32      schema_type; 
    /**Tokens array which determines the entity of the specified type.*/
    OdUInt32Array tokens; 
  };

private:
  OdArray<OdPrcSchema::schema_type_and_token> m_Schemas;

public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE(OdPrcSchema)
  //DOM-IGNORE-END



  /** \details 
  Returns the current array of schema definitions.  
  The array of schema definitions is returned as a reference to an OdArray object, therefore it can be used to set a new array or modify the existing one.
  */
  OdArray<OdPrcSchema::schema_type_and_token> &schemas();
  
  /** \details 
  Returns the current array of schema definitions.
  */
  const OdArray<OdPrcSchema::schema_type_and_token> &schemas() const;
};

#endif // _PRCSCHEMA_INCLUDED_


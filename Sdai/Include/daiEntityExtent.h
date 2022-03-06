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

#include "OdaCommon.h"
#include "RxObject.h"
#include "daiModule.h"
#include "daiObjectId.h"
#include "daiSessionInstance.h"
#include "daiEntity.h"
#include "daiAggr/daiSet.h"

#ifndef _DAI_ENTITY_EXTENT_H_
#define _DAI_ENTITY_EXTENT_H_

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  This class represents a container (folder) that contains entities that
  are a certain schema entity type.
  */
  class DAI_EXPORT EntityExtent : public SessionInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(EntityExtent);
    //DOM-IGNORE-END

    /** \details
    Returns an aggregate of object ids of entity instances for the folder.
    */
    OdDAIObjectIdSet& instances() { return m_instances; }

    /** \details
    Returns a smart pointer to the entity definition of this entity extent.
    */
    const EntityPtr definition() const { return m_definition; }

    /** \details
    Sets the entity definition of this entity extent container (folder).

    \param definition [in] An entity definition that is the parent definition for all entity instances contained in this entity extent.
    */
    void definition(EntityPtr definition) { m_definition = definition; }

    /** \details
    Returns the type name of the entity definition of this entity extent.
    */
    const OdAnsiString& name() const { return m_definition->name(); }

    /** \details
    Unloads all enitites from this entity extent container.
    \returns Returns eOk if success, otherwise it should return an error code
    */
    OdResult unload();

    /** \details
    Loads all enitites from this entity extent container.
    \returns Returns eOk if success, otherwise it should return an error code
    */
    OdResult load();

    /** \details
    Retrieves all instances from extents which are instances of provided entity type name.
    \returns An array of object identifiers of instances of a type.
    */
    OdDAIObjectIds getInstancesOf(const char *entityName) const;

    /** \details
    Retrieves all instances from extents which are instances of provided entity type definition.
    \returns An array of object identifiers of instances of a type.
    */
    OdDAIObjectIds getInstancesOf(const OdDAI::Entity *entityDef) const;

//DOM-IGNORE-BEGIN
  private:

    EntityPtr         m_definition;
    OdDAIObjectIdSet  m_instances;

    friend class ModelContents;
//DOM-IGNORE-END

  };
  typedef OdSmartPtr<EntityExtent> EntityExtentPtr;

}

#endif // _DAI_ENTITY_EXTENT_H_

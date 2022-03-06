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

#ifndef _DAI_SCHEMA_H_
#define _DAI_SCHEMA_H_

#include "OdaCommon.h"
#include "daiEntity.h"
#include "daiDefinedType.h"
#include "daiRules/daiGlobalRule.h"

//DOM-IGNORE-BEGIN
class ScopedSymbolTable;
using ScopedSymbolTablePtr = ScopedSymbolTable*;

class ActivationRecord;
using ActivationRecordPtr = std::shared_ptr<ActivationRecord>;
//DOM-IGNORE-END

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class InstanceFactory;
  typedef OdSmartPtr<InstanceFactory> InstanceFactoryPtr;

  /** \details
  A class that implements working with a schema definition.
  */
  class DAI_EXPORT Schema : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Schema);
    //DOM-IGNORE-END
    
    /** \details
    Destroys the schema object.
    */
    virtual ~Schema();

    /** \details
    Retrieves the name of the schema.
    \returns An ANSI string that contains the name of the schema.
    */
    const OdAnsiString& name() const;

    /** \details
    Retrieves a set of entity definitions of the schema.
    \returns Returns a set of entity definitions of the schema.
    */
    const EntitySet& entities() const;

    /** \details
    Retrieves a set of data types defined within the schema.
    \returns A <link OdDAI::DefinedTypeSet, DefinedTypeSet> object that contains data types defined within the schema.
    */
    const DefinedTypeSet& types() const;

    /** \details
    Searches an entity definition by its name.
    \returns A smart pointer to the found <link OdDAI::Entity, entity definition>. If the entity is not found, the method returns a NULL smart pointer.
    */
    const EntityPtr find(OdAnsiString entityName) const;

    /** \details
    Searches for an entity or type definition by its name.
    \param typeName [in] An ANSI string that contains the entity name.
    \returns A smart pointer to the named type of found entity or type definition. If the entity or type is not found, the method returns a NULL smart pointer.
    */
    const NamedTypePtr namedType(OdAnsiString typeName) const;

    /** \details
    Retrieves the collection of supertypes starting from a specified entity definition.
    The method fills a passed entity list and returns it to a calling subroutine.
    \param targetEntity     [in]  A smart pointer to the starting entity definition.
    \param collectionToFill [out] A placeholder for the supertypes collection.
    */
    void getSuperEntityCollection(const EntityPtr targetEntity, EntityList& collectionToFill) const;

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const;

    /** \details
    Validates model if it satisfies global rule with ruleName.
    \returns OdDAI::Logical::True if model satisfies Global Rule.
    */
    OdDAI::Logical validateGlobalRule(const ModelPtr model, const char *ruleName, OdAnsiStringList &aggr) const;

    /** \details
    Retrieves the array with schema global rules.
    \returns An array with schema global rules.
    */
    const OdArray<GlobalRulePtr>& getGlobalRules() const;

    /** \details
    Writes data from the schema object to a physical file.
    \param fileName [in] A string that contains the full path to the output file to write data.
    \returns eOk if the data was successfully written; otherwise, the method returns an appropriate error code.
    */
    OdResult writeToFile(const OdString& fileName) const;


    /** \details
    Creates a complex entity from the list of entities.
    \param complexEntityList [in] A list of entities to create from.
    \remarks
      * The result is plain list of entities without supertypes.
      * The associativity rule is valid for operation (A+B)+C=A+(B+C) and gets same result = A+B+C.
    */
    OdDAI::EntityPtr getComplexEntity(OdDAI::List<OdDAI::EntityPtr>& complexEntityList);

//DOM-IGNORE-BEGIN

    void setSymbolTable(ScopedSymbolTablePtr symbolTable) { m_symbolTable = symbolTable; };
    ScopedSymbolTablePtr getSymbolTable() const { return m_symbolTable; };

    void setActivationRecord(ActivationRecordPtr &ar) { m_ar = ar; };
    ActivationRecordPtr getActivationRecord() const { return m_ar; };

    void setInstanceFactory(InstanceFactory *instanceFactory);
    InstanceFactoryPtr getInstanceFactory() const;

  protected:

    /** \details
    Sets a new name for the schema definition.
    \param name [in] A name for the schema definition.
    \remarks 
    This method is for internal use only.
    */
    void setName(const OdAnsiString &name);

    /** \details
    Sets a new set of entity definitions for the schema.
    \param entities [in] A set of entity definitions to assign to the schema definition.
    \remarks 
    This method is for internal use only.
    */
    void setEntities(const EntitySet &entities);

    /** \details
    Sets a new set of defined types for the schema.
    \param types [in] A set of defined types to assign to the schema definition.
    \remarks
    This method is for internal use only.
    */
    void setTypes(const DefinedTypeSet &types);

    /** \details
    Sets a new set of unnamed types for the schema.
    \param types [in] A set of unnamed types to assign to the schema definition.
    \remarks
    This method is for internal use only.
    */
    void setUnnamedTypes(const DefinedTypeSet &unnamedTypes);

    /** \details
    Sets a new set of Global Rules for the schema.
    \param globalRules [in] A set of Global Rules to assign to the schema definition.
    \remarks
    This method is for internal use only.
    */
    void setGlobalRules(const OdArray<GlobalRulePtr> &globalRules);

  protected:
    /** The schema name.*/
    OdAnsiString m_name;
    
    /** Entity definitions that are contained in the schema.*/
    OdRxDictionaryPtr m_entities;
    
    /** Entity type definitions that are contained in the schema.*/
    OdRxDictionaryPtr m_types;
    OdArray<GlobalRulePtr> m_globalRules;
    
    /** Entity type definitions without names that are contained in the schema.*/
    OdRxDictionaryPtr m_unnamedTypes;
    
    /** An array of entity type definitions without names that are contained in the schema.*/
    OdArray<OdDAI::DictionaryInstancePtr> m_unnamedTypesArray;

    InstanceFactoryPtr m_instanceFactory;
    ScopedSymbolTablePtr m_symbolTable = nullptr;
    ActivationRecordPtr m_ar = nullptr;

    friend class SchemaFiller;

//DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to a <link OdDAI::Schema, Schema> object.
  */
  typedef OdSmartPtr<Schema> SchemaPtr;
}

#endif // _DAI_SCHEMA_H_

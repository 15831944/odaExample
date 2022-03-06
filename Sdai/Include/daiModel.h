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

#ifndef _DAI_MODEL_H
#define _DAI_MODEL_H

#include "daiSessionInstance.h"
#include "daiApplicationInstance.h"
#include "daiInstanceIterator.h"
#include "daiSchema.h"
#include "daiEntityExtent.h"

#include "SmartPtr.h"

#include "sdai.h"

class OdExpSchemaModule;
class OnModelLoadTest;
class OnModelSaveTest;
typedef OdSmartPtr<OdExpSchemaModule> SchemaModulePtr;

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  //DOM-IGNORE-BEGIN
  class ModelContents;
  typedef OdSmartPtr<ModelContents> ModelContentsPtr;

  class OdSpfFilerBase;
  typedef OdSmartPtr<OdSpfFilerBase> OdSpfFilerBasePtr;

  /** \details
    A data type that represents a smart pointer to a <link OdDAI::Model, Model> object.
    */
  class Model;
  typedef OdSmartPtr<Model> ModelPtr;  
  //DOM-IGNORE-END

  /** \details 
  A class that implements functionality for working with models.
  */
  class DAI_EXPORT Model : public SessionInstance
  {
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Model);
    Model();
    //DOM-IGNORE-END

    /** \details
    Initializes the model object and creates a minimal model hierarchy based on a schema with the specified name.
    \param name       [in] A string that contains the model's name.
    \param schemaName [in] A string that contains the schema's name.
    \param repo       [in] A raw pointer to a repository object that is associated with the model.
    */
    void initialize(const OdAnsiString &name, const OdAnsiString& schemaName, Repository *repo);

    //void initialize(const OdAnsiString& schemaName, OdDAI::OdSpfFilerBasePtr& pFiler);

    /** \details
    Initializes the model object and creates a minimal model hierarchy based on a specified schema.
    \param name   [in] A string that contains the schema's name.
    \param schema [out] A placeholder for a schema object.
    \param repo   [in] A raw pointer to a repository object that is associated with the model.
    */
    void initialize(const OdAnsiString &name, const SchemaPtr &schema, Repository *repo);

    /** \details
    Retrieves the name of the model.
    \returns A string that contains the name of the model.
    */
    OdAnsiString name() const { return m_name; };

    /** \details
    Retrieves a repository that contains the model.
    \returns A raw pointer to the repository that contains the model.
    */
    Repository* repository() const { return m_repository; };

    /** \details
    Assigns a new name to the specified SDAI model.
    \param modelName [in] A string that contains the new name of the SDAI model.
    */
    void renameModel(const OdAnsiString &modelName);


    /** \details
    Retrieves an entity definition by its name. 
    \param entityName [in] The name of an entity definition.
    \returns A raw pointer to the entity definition.
    \remarks 
    If there is no entity definition with the specified name, the method returns a NULL pointer.
    */
    const OdDAI::Entity*     getEntityDefinition(const char *entityName) const;

    /** \details
    Retrieves the underlying schema definition of the model.
    \returns A smart pointer to the model's underlying schema definition.
    */
    const OdDAI::SchemaPtr   underlyingSchema() const;

    /** \details
    Retrieves the name of the model's underlying schema.
    \returns An ANSI string that contains the name of the model's underlying schema.
    */
    const OdAnsiString&      underlyingSchemaName() const;

    /** \details
    Searches the entity in the model by its handle.
    \param h [in] A handle of the searched entity.
    \returns <link OdDAIObjectId, An identifier of an OdDAI object> if the entity was found; otherwise, the method returns a NULL identifier.
    */
    OdDAIObjectId            getEntityInstance(const OdDbHandle &h);

    /** \details
    Creates a new instance of a specified entity type.
    \param entityDef [in] A raw pointer to the entity definition that contains the type name of the new entity to be created.
    \returns A smart pointer to the created entity instance.
    \remarks
    If the current schema does not support the specified type, the method returns a NULL smart pointer.
    In this case, the isNull() method of the smart pointer object returns true.
    The created entity is not attached to the model.
    */
    ApplicationInstancePtr  createEntityInstance(const OdDAI::Entity *entityDef);

    /** \details
    Creates a new instance of a specified entity type.
    \param entityTypeName [in] A string that contains the type name of the new entity to be created.
    \returns A smart pointer to the created entity instance.
    \remarks
    If the current schema does not support the specified type, the method returns a NULL smart pointer.
    In this case, the isNull() method of the smart pointer object returns true.
    The created entity is not attached to the model.
    */
    ApplicationInstancePtr  createEntityInstance(const char *entityTypeName);

    /** \details
    Appends a newly created entity instance to the model.
    \param pInst [in] A smart pointer to the entity instance to be appended.
    \returns An <link OdDAIObjectId, OdDAI object identifier> of the appended entity instance.
    \remarks
    If the specified entity has been already appended to the model, the method returns the existing entity's identifier;
    if the specified entity belongs to another model, the method returns a null identifier
    (the isNull() method of the identifier object returns true).
    */
    OdDAIObjectId appendEntityInstance(ApplicationInstancePtr pInst);

    /** \details
    Inserts a newly created entity instance to the model.
    \param pInstanceToInsert [in] A smart pointer to the entity instance to be inserted.
    \param insertHandle      [in] A handle of the parent object where to insert the entity instance.
    \returns An identifier of the inserted entity instance.
    \remarks
    If the entity being inserted already belongs to another model or it has been already appended or inserted before, the method returns a NULL object identifier.
    If the specified database handle already exists in the model, the entity defined with this handle gets a new handle value
    and the inserted entity (specified with the pInstanceToInsert parameter) takes the passed handle value (the insertHandle parameter value).
    */
    OdDAIObjectId insertEntityInstance(ApplicationInstancePtr pInstanceToInsert, const OdDbHandle& insertHandle);

    /** \details
    Deletes a specified entity instance from the model.
    \param pInstance [in] A raw pointer to the entity instance to be deleted.
    \remarks
    When the method is called the specified instance is marked as deleted, but it still stays in the model. 
    The deleted instance is not written to the file. 
    During the next file reading operation, the instance will not be read from the file 
    therefore it will be physically removed from the model.
    */
    void deleteInstance(ApplicationInstance *pInstance);

    /** \details
    Creates an iterator to get sequential access to all entities of the model.
    \returns A smart pointer to the model's instance iterator.
    */
    OdDAI::InstanceIteratorPtr  newIterator();

    /** \details
    Retrieves the collection of entity instances with entity type which is kind of entityName.
    \param entityName [in] An entity's name.
    \returns A smart pointer to entity extent that keeps the collection of entity instances.
    */
    EntityExtentPtr          getEntityExtent_(const char *entityName) const;

    /** \details
    Retrieves the collection of entity instances, which entity types are subtypes of the specified entity definition.
    \param entityDef [in] An smart pointer to the entity definition.
    \returns A smart pointer to the entity extent that stores the collection of entity instances.
    */
    OdDAIObjectIdSet*         getEntityExtent(EntityPtr entityDef) const;

    /** \details
    Retrieves the collection of entities with the same type (entity's extent) as the entity with a specified name.
    The entity collection is represented with an array of OdDAI objects identifiers.
    \param entityName [in] An entity's name.
    \returns A raw pointer to the array of identifiers of OdDAI objects that represent the extent collection.
    \remarks
    The method returns identifiers of all entities for which the <link OdIfc::OdIfcEntity::isKindOf@OdIfcEntityType@const, isKindOf()> method
    returns the same value as for the specified entity.
    */
    OdDAIObjectIdSet*        getEntityExtent(const char *entityName) const;

    //DOM-IGNORE-BEGIN
    ///** \details
    //*/
    //bool loadEntityExtent(const char* entityName);

    ///** \details
    //*/
    //bool loadEntityExtent(EntityPtr entityDef);
    //DOM-IGNORE-END

    /** \details
    Unloads application instance specified with its name.
    \param entityName [in] An entity's name.
    \returns true if objects were unloaded successfully; otherwise, the method returns false.
    */
    bool unloadEntityExtent(const char* entityName);

    /** \details
    Unload application instances specified by the definition. 
    \param entityDef [in] A raw pointer to the entity that represents the entity definition.
    \returns true if entities were unloaded successfully; otherwise, the method returns false.
    */
    bool unloadEntityExtent(EntityPtr entityDef);


    /** \details
    Retrieves the current access mode for the SDAI model.
    \returns Current access mode of the model.
    */
    SdaiAccessMode           mode() const;

    /** \details
    Closes the SDAI model. 
    When the model is close any access to it ends.
    */
    void                     closeModel();

    /** \details
    Closes the SDAI model. 
    When the model is close any access to it ends.
    */
    void                     closeModel() const;

    /** \details
    Changes the access mode for the SDAI model from the read-only to the read-write.
    */
    void                     promoteModelToReadWrite() const;

    /** \details
    Retrieves the count of all entity instances in this model.
    \returns A signed 32-bit integer value that contains the count of all entity instances within the model.
    */
    OdInt32 entityInstancesCount() const;

    //DOM-IGNORE-BEGIN
    /** \details
    Retrieves contents of a model.
    \returns A smart pointer to model content.
    \remarks
    The specification allows access to model content directly or using the late-bound getAttr() function, however, we still keep model contents in the private section.
    */
    const OdDAI::ModelContentsPtr getModelContents() const;
    //DOM-IGNORE-END

  //DOM-IGNORE-BEGIN
  protected:

    enum StateFlags
    {
      kLoading = 1 << 0,
      kWriting = 1 << 1,
    };
  //DOM-IGNORE-END

  public:

    /** \details
    Retrieves whether the SDAI model is currently being loaded from a file.
    \returns true if the model is currently is being loaded from a file; otherwise, the method returns false.
    */
    bool getIsLoading()
    {
      return GETBIT(m_stateFlags, kLoading);
    }

    /** \details
    Retrieves whether the model is being written to a file.
    \returns true if the model is being written to a file at the moment of the method call; otherwise, the method returns false.
    */
    bool getIsWriting()
    {
      return GETBIT(m_stateFlags, kWriting);
    }

  //DOM-IGNORE-BEGIN
  protected:

    class StateLocker
    {
      OdSmartPtr<Model> m_pModel;
      OdUInt32 m_stateFlags;

    public:

      StateLocker(Model *pModel)
        : m_pModel(pModel)
        , m_stateFlags(0)
      {
        m_stateFlags = m_pModel->m_stateFlags;
      }

      ~StateLocker()
      {
        m_pModel->m_stateFlags = m_stateFlags;
      }

      StateLocker& setIsLoading()
      {
        ODA_ASSERT(GETBIT(m_pModel->m_stateFlags, kLoading) == 0);
        SETBIT(m_pModel->m_stateFlags, kLoading, true);
        return *this;
      }

      StateLocker& setIsWriting()
      {
        ODA_ASSERT(GETBIT(m_pModel->m_stateFlags, kWriting) == 0);
        SETBIT(m_pModel->m_stateFlags, kWriting, true);
        return *this;
      }
      
    };

  protected:

    /** \details
    Sets a name of the model.
    */
    void name(const OdAnsiString &name) { m_name = name; };

    /** details
    Sets a repository that contains the model.
    */
    void repository(Repository *repo) { m_repository = repo; };

    ModelContentsPtr createModelContents(const OdAnsiString &schemaName);
    OdDAI::SchemaPtr getSchemaDef(const OdAnsiString &schemaName);

    friend OnModelLoadTest;
    friend OnModelSaveTest;

  private:
    OdAnsiString m_name;
    SchemaPtr m_underlyingSchema;
    ModelContentsPtr m_contents;
    Repository *m_repository;
    OdUInt32 m_stateFlags;

    friend class Repository; 
    friend class FilerBase;
    mutable SdaiAccessMode  m_accessMode;
//DOM-IGNORE-END
  };
  
  
}

#endif // _DAI_MODEL_H

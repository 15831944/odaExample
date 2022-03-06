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

#ifndef _DAI_REPOSITORY_H
#define _DAI_REPOSITORY_H

#include "daiDictionaryInstance.h"
#include "daiSessionInstance.h"

#include "sdai.h"
#include "OdStreamBuf.h"
#include "OdArray.h"

#include "SmartPtr.h"

#define REPOSITORY_DEFAULT_MODEL_NAME "default"

class OdDAIHostAppServicesBase;

namespace OdDAI {

  class Session;

  class OdHeaderSection;
  typedef OdSmartPtr<OdHeaderSection> OdHeaderSectionPtr;

  class Model;
  typedef OdSmartPtr<Model> ModelPtr;

  class Schema;
  typedef OdSmartPtr <Schema> SchemaPtr;

  class DAI_EXPORT Repository : public SessionInstance
  {

    static OdSmartPtr<Repository> createObject(Session *session);

  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Repository);
    //DOM-IGNORE-END

    Repository();

    /**
    Retrieves the current name of repository.
    \returns Returns a string that contains the name.
    */
    const OdString& name() const
    {
      return m_name;
    }

    /**
    Assigns a name to the repository.
    */
    void name(const OdString &name)
    {
      m_name = name;
    }

    const OdArray<ModelPtr>& models() const { return m_models; };

    /** \details
      Create a new model with name and schema in the repository.
      \param name [in] name of created model
      \param schema [in] schema name of created model
      \returns ModelPtr
    */
    ModelPtr createModel(const OdAnsiString &name, const OdAnsiString &schemaName);

    /** \details
      Create a new model with name and schema in the repository.
      \param name [in] name of created model 
      \param schema [in] schema of created model
      \returns ModelPtr 
    */
    ModelPtr createModel(const OdAnsiString &name, const SchemaPtr schema);


    /** \details
      Get model in read only mode.
      \param modelPtr [in] model which should be open in read only mode
      \returns ModelPtr in read mode
    */
    const ModelPtr getModel(ModelPtr& modelPtr) const;

    /** \details
      Get model in read only mode.
      \param modelPtr [in] model which should be open in read/write mode
      \returns ModelPtr in read/write mode
    */
    ModelPtr getModelRW(ModelPtr& modelPtr);


    /** \details
      Get model in read only mode.
      \param modelPtr [in] model name which should be open in read only mode
      \returns ModelPtr in read only mode
    */
    const ModelPtr getModel(const OdAnsiString &modelName = REPOSITORY_DEFAULT_MODEL_NAME) const;

    /** \details
      Get model in read only mode.
      \param modelName [in] model name which should be open in read/write mode
      \returns ModelPtr in read/write mode
    */
    ModelPtr getModelRW(const OdAnsiString &modelName = REPOSITORY_DEFAULT_MODEL_NAME);

    /* \details
    Removes a model from repository.
    \param model [in] Model that should be deleted from repository.
    */
    void deleteModel(ModelPtr& model);

    /** \details
      Get model access mode by model name.
      \param modelName [in] model name 
      \returns model access mode 
    */
    SdaiAccessMode  getModelAccessMode(const OdAnsiString &modelName = REPOSITORY_DEFAULT_MODEL_NAME) const;

    /* \details
    */
    OdResult initialize();

    OdArray<SchemaPtr> schemas() { return m_schemas; };

    /** \details
    Retrieves the file object's header section.
    \returns Returns a smart pointer to the <link OdDAI::OdHeaderSection, OdHeaderSection> object that represents the file object's header section.
    */
    OdHeaderSectionPtr getHeaderSection();

    /** \details
    */
    OdResult readFile(const OdString& fileName);

    /** \details
    Reads data from a specified stream buffer.
    \param pStream [in] A smart pointer to the stream buffer object to read data from.
    \returns Returns eOk if the data was successfully read; otherwise, the method returns an appropriate error.
    */
    OdResult readStream(OdStreamBufPtr pStream);

    /** \details
    Reads the header section data of a specified IFC file.
    \param fileName [in] A string that contains an IFC file's name.
    \returns Returns a smart pointer to an instance of the <link OdDAI::OdHeaderSection, OdHeaderSection> class that contains read data.
    \remarks
    This method is used to extract information about the IFC file without reading all of its content.
    */
    static OdHeaderSectionPtr readHeaderSection(const OdString& fileName);

    /** \details
    Reads the header section data from a specified stream buffer associated with a Step Physical File.
    \param pStream [in] A raw pointer to a file stream buffer to read data from.
    \returns Returns a smart pointer to an instance of the <link OdDAI::OdHeaderSection, OdHeaderSection> class that contains read data.
    \remarks
    This method is used to extract information about the Step Physical File file without reading all of its content.
    */
    static OdHeaderSectionPtr readHeaderSection(OdStreamBufPtr pStream);

    /** \details
    Writes data from the repository object to a physical file.
    \param filename     [in] A string that contains the full path to the output file to write data.
    \param saveLogFile  [in] A flag that determines whether the log file should be also written (if equal to true) or not (if equal to false).
    \returns Returns eOk if the data was successfully written; otherwise, the method returns an appropriate error.
    */
    virtual OdResult writeFile(const OdString& filename, bool saveLogFile = false);

    /** \details
    Writes data from the specified stream buffer to a physical file.
    \param pStream      [in] A smart pointer to the output stream buffer object to wtite data.
    \param saveLogFile  [in] A flag that determines whether the log file should be also written (if equal to true) or not (if equal to false).
    \returns eOk if the data was successfully written; otherwise, the method returns an appropriate error code.
    \remarks 
    This method does not support writing to Zip format.
    */
    virtual OdResult writeStream(OdStreamBufPtr pStream, bool saveLogFile = false);

    /** \details
    Returns a pointer to session in which the repository was created.
    \returns Returns pointer to the session.
    */
    OdDAI::Session* session() const { return m_session; };

    /** \details
    Retrieves if model with model name already exists in repository.
    returns True if model with same name is already exists in repository, otherwise returns false.
    */
    bool hasModel(const OdAnsiString &modelName);

    //DOM-IGNORE-BEGIN

    /** \details
    Sets a new application services object.
    \param svcs [in] A raw pointer to the <link OdDAIHostAppServicesBase, OdDAIHostAppServicesBase> object to be assigned with the repository.
    */
    void attachTo(OdDAIHostAppServicesBase* svcs, OdRxObject *owner)
    {
      m_svcs = svcs;
      m_owner = owner;
    }

    void detach()
    {
      // TODO: Clean resolved model?
      m_svcs = nullptr;
      m_owner = nullptr;
    }

    OdRxObjectPtr attachedTo()
    {
      return m_owner;
    }

    OdDAIHostAppServicesBase* appServices()
    {
      return m_svcs;
    }

    //DOM-IGNORE-END

  protected:
    bool setModelAccessMode(ModelPtr& modelToSet, SdaiAccessMode accessMode) const;
    void synchronizeSchemas();
    OdResult writeStreamBase(OdStreamBufPtr pStream, bool saveLogFile = false);
    void onClose();

  protected:

    OdString m_name;
    OdHeaderSectionPtr m_pHeaderSection;

    OdArray<ModelPtr> m_models;
    OdArray<SchemaPtr> m_schemas;

    OdDAIHostAppServicesBase *m_svcs;
    OdRxObject *m_owner;

    Session *m_session;

    friend class Session;

    private:
      class ModelModeRestorer;
  };
  typedef OdSmartPtr<Repository> RepositoryPtr;
}


#endif // _DAI_REPOSITORY_H

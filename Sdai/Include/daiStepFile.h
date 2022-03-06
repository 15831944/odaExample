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

#ifndef _DAI_STEP_FILE_H
#define _DAI_STEP_FILE_H

#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"
#include "daiRepository.h"

class OdDAIHostAppServicesBase;

#define CHECK_MODEL_ACCESS \
  ODA_ASSERT_ONCE(m_pModel->mode() != Access_type_unset)

/** \details
A class that implements working with an Step Physical File header and data sections (header and model).
*/
class DAI_EXPORT OdStepFile : public OdRxObject //OdGiDrawable
{
public:

  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdStepFile);
  //DOM-IGNORE-END

  /** \details
  Destroys the OdStepFile file object.
  */
  ~OdStepFile();

  /**
  Retrieves the current name (file name) of a physical file associated with the repository object.
  \returns A string that contains the file name.
  */
  OdString getFileName() const;

  /**
  Assigns a name (file name) to the OdStepFile container.
  */
  void setFileName(const OdString &name);

  /** \details
  Retrieves the application services object that is associated with the OdStepFile object.
  \returns Returns a raw pointer to the <link OdDAIHostAppServices, OdDAIHostAppServices> object associated with the file object.
  */
  OdDAIHostAppServicesBase* getAppServices() const;

  /** \details
  Sets a new application services object with the OdStepFile object.
  \param svcs [in] A raw pointer to the <link OdDAIHostAppServices, OdDAIHostAppServices> object to be assigned with the file.
  */
  void setAppServices(OdDAIHostAppServicesBase* svcs);

  /** \details
  Initializes the STEP file object with a schema specified by its string identifier.
  \param schemaIdentifier [in] A string that contains the schema identifier.
  \returns eOk if the file was successfully initialized; otherwise, the method returns an appropriate error code.
  \remarks
  OdStepFile object without underlying <link OdDAI::Model, OdDAI::Model> object will be created if schema name is empty.
  */
  OdResult initialize(const OdAnsiString &schemaIdentifier);

  /** \details
  Initializes OdStepFile instance with a specified repository. After the initialization, the model becomes opened in read-only
  access mode by default and stays in this mode while the repository is attached to the file object.
  \param repo [in] A raw pointer to the repository object to be attached to the file object.
  \returns eOk if the repository object was successfully attached; otherwise, the method returns an appropriate error code.
  */
  OdResult initialize(OdDAI::Repository* repo);

  /** \details
  Reads model data from a specified file of one of supported physical formats (Step Physical File/HDF5/XML or zipped).
  \param fileName [in] A string that contains the full path to the input file to read data from.
  \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
  */
  OdResult readFile(const OdString& fileName);

  /** \details
  Reads data from a specified stream.
  \param pStream [in] A smart pointer to the data buffer associated with the input stream.
  \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
  */
  OdResult readFile(OdStreamBufPtr pStream);

  /** \details
  Writes data from the file object to a physical file.
  \param fileName     [in] A string that contains the full path to the output file to write data.
  \param saveLogFile  [in] A flag that determines whether the log file should be also written (if equal to true) or not (if equal to false).
  \returns eOk if the data was successfully written; otherwise, the method returns an appropriate error code.
  */
  virtual OdResult writeFile(const OdString& fileName, bool saveLogFile = false);

  /** \details
  Writes data from the specified stream buffer to a physical file.
  \param pStream      [in] A smart pointer to the output stream buffer object to wtite data.
  \param saveLogFile  [in] A flag that determines whether the log file should be also written (if equal to true) or not (if equal to false).
  \returns eOk if the data was successfully written; otherwise, the method returns an appropriate error code.
  */
  virtual OdResult writeFile(OdStreamBufPtr pStream, bool saveLogFile = false);

  /** \details
  Retrieves the file object's header section.
  \returns A smart pointer to the <link OdDAI::OdHeaderSection, OdHeaderSection> object that represents the file object's header section.
  */
  OdDAI::OdHeaderSectionPtr getHeaderSection();

  /** \details
  Retrieves the model object associated with the file object (by default the model is opened in read-only mode).
  \returns A smart pointer to the instance of the <link OdDAI::Model, OdDAI::Model> class that represents the current model of the file object.
  */
  virtual OdDAI::ModelPtr getModel(SdaiAccessMode mode = sdaiRO) const;

  /** \details
  Closes the model attached to the file object and detaches the repository object associated with the model.
  After detaching, it is possible to work with the repository and the model at a low level.
  \returns A smart pointer to the unattached repository instance.
  */
  OdDAI::RepositoryPtr detach();

  //DOM-IGNORE-BEGIN
protected:

  /** \details
  Method is called just after file reading has ended.
  \returns eOk if operation successfully done; otherwise, the method returns an appropriate error code.
  \remarks Default implementation just returns eOk.
  */
  virtual OdResult onReadFileEnd() { return eOk; };

  /** \details
  Checks if schema with identifier provided is supported by OdStepFile schema-dependent implementation.
  \param schemaIdentifier [in] A string that contains the schema identifier.
  \returns true if schema is supported by OdStepFile implementation; otherwise returns false.
  */
  virtual OdResult checkSchema(const OdAnsiString &schemaIdentifier) const = 0;

  /** \details
  Checks if repository can be attached to OdStepFile schema-dependent implementation.
  \param repo [in] A raw pointer to the repository object to be attached to the file object.
  \returns true if repository can be attached to OdStepFile implementation; otherwise returns false.
  */
  virtual OdResult checkRepo(const OdDAI::Repository* repo) const = 0;

  virtual const char* defaultRepoName();

  OdDAIHostAppServicesBase *m_pHostAppServices = nullptr;
  OdDAI::RepositoryPtr m_pRepository;
  OdDAI::ModelPtr m_pModel;

  //DOM-IGNORE-END    
};

/** \details
A data type that represents a smart pointer to an <link OdStepFile, OdStepFile> object.
*/
typedef OdSmartPtr<OdStepFile> OdStepFilePtr;

#endif // _DAI_STEP_FILE_H

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

#ifndef _PRCFILE_INCLUDED_
#define _PRCFILE_INCLUDED_ 
 

#include "PrcFileStructure.h"
#include "PrcSchema.h"
#include "PrcModelFileData.h"
#include "PrcUniqueId.h"
#include "DbAux/PrcUnitsFormatter.h"
#include "PrcFileSettings.h"

class OdPrcHostAppServices;
class OdPrcFile;
class OdPrcAuditInfo;
class OdPrcStreamCreator;
class OdGsView;
class OdPrcFileImpl;

/** \details 
  <group PRC_Files_Structures_Assemblies>
  The structure stores information of a view assigned with a assembly node.
*/
struct OdPrcViewNode
{
  /// An identifier of a view object. 
  OdPrcObjectId view;
  /// A transformation matrix associated with the node.
  OdGeMatrix3d matrix;
  /// An array of object identifiers, which represents the path.
  OdPrcObjectIdArray path;
};

/** \details 
  <group PRC_Files_Structures_Assemblies>
  The class that allows to store and manage parameters for three-dimensional tessellation data in decompressed format.
*/
class Decompress3dTessParams
{
public:
  /** A flag that determines whether normals should be stored in the result tessellation data (if true) or not (if false).*/
  bool bStoreNormals; 
  /** A flag that determines whether the crease angle value should be overwritten (if true) or not (false). If the flag value is equal to true, the crease angle value is overwritten with the dCreaseAngle value.*/
  bool bOverwriteCreaseAngle; 
  /** A crease angle in degrees that is used if the bOverwriteCreaseAngle flag is set to true.*/
  double dCreaseAngle; 
  
  /** \details 
    Creates a new set of tessellation parameters with default values.
  */
  Decompress3dTessParams()
    : bStoreNormals(true)
    , bOverwriteCreaseAngle(false)
    , dCreaseAngle(0.)
  {}
};

/** \details
  A data type that represents a smart pointer to a PRC file object.
*/
SMARTPTR(OdPrcFile);

/** \details 
<group PRC_Files_Structures_Assemblies>

Class implements .prc file functionality. 
A .prc file contains a collection of the .prc file structure, one model file, and one header.
*/
class PRC_TOOLKIT OdPrcFile : public OdRxObject
{
protected:
  void prcOut(OdStreamBufPtr pStream, OdPrcStreamCreator *pCreator);
  void prcIn(OdStreamBufPtr pStream, OdPrcStreamCreator *pCreator, OdPrcAuditInfo *pAuditInfo);

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE_BASE(OdPrcFile)
  //DOM-IGNORE-END

  /** \details 
  Destroys the .prc file object.
  */
  virtual ~OdPrcFile(void);
  
  /** \details 
  Returns the current model file data in the read-write mode.
  Model file data is returned as a reference to an OdPrcModelFileData object, therefore it can be used to set new model file data.
  \returns An instance of the <link OdPrcModelFileData, OdPrcModelFileData> class that represents the model file data. 
  */
  OdPrcModelFileData &modelFileData();
  
  /** \details 
  Returns the current model file data in the read-only mode.
  \returns An instance of the <link OdPrcModelFileData, OdPrcModelFileData> class that represents the model file data. 
  */
  const OdPrcModelFileData &modelFileData() const;
  
  /** \details 
  Returns the current .prc file schema in the read-write mode.
  The schema is returned as a reference to an OdPrcSchema object, therefore it can be used to set a new file schema.
  \returns An instance of the <link OdPrcSchema, OdPrcSchema> class that represents the schema. 
  
  */
  OdPrcSchema &schema();
  
  /** \details 
  Returns the current .prc file schema in the read-only mode.
  \returns An instance of the <link OdPrcSchema, OdPrcSchema> class that represents the schema. 
  */  
  const OdPrcSchema &schema() const;
  
  /** \details 
  Returns file structures contained in the .prc file. 
  The file structure array is returned as a reference to an OdPrcFileStructurePtrArray object, therefore it can be used to set a new file structure array.
  */
  OdPrcFileStructurePtrArray &fileStructures();
  
  /** \details 
  Returns file structures contained in the .prc file.*/
  const OdPrcFileStructurePtrArray &fileStructures() const;

  /** \details 
  Returns the current array of uncompressed files embedded into the .prc file.
  File array is returned as a reference to an OdPrcUncompressedFiles object, therefore it can be used to set a new embedded file array.
  */
  OdPrcUncompressedFiles &uncompressedFiles();
  
  /** \details
  Returns the current array of uncompressed files embedded into the .prc file.*/
  const OdPrcUncompressedFiles &uncompressedFiles() const;
  
  /** \details
  Returns the current unique identifier of the application.
  The unique application identifier is returned as a reference to an OdPrcUniqueId object, therefore it can be used to set a new identifier.
  */
  OdPrcUniqueId &applicationId();
  
  /** \details
  Returns the current unique identifier of the application.
  */
  const OdPrcUniqueId &applicationId() const;
  
  /** \details
  Returns the current unique identifier of the file structure.
  The unique file structure identifier is returned as a reference to an OdPrcUniqueId object, therefore it can be used to set a new identifier.
  */
  OdPrcUniqueId &fileStructureId();
  
  /** \details
  Returns the current unique identifier of the file structure.
  */
  const OdPrcUniqueId &fileStructureId() const;
  
  /** \details
  Sets a new value of the minimum read version and the authoring version.

  \param minimal_version_for_read [in] A new minimum version for reading to be set.
  \param authoring_version [in] A new authoring version to be set.

  \returns Returns eOk if new values were successfully set or an appropriate error code in the other case.
  */
  OdResult setVersions(OdUInt32 minimal_version_for_read, OdUInt32 authoring_version);
  
  /** \details
  Returns the current minimum version for reading.
  */
  OdUInt32 minimalVersionForRead() const;
  
  /** \details
  Returns the current authoring version.
  */
  OdUInt32 authoringVersion() const;

  /** \details 
  Returns a specified file structure from the .prc file.
  
  \param uuid [in] The unique identifier of the file structure to search.
  
  \returns Returns a pointer to the file structure if it is found or NULL in the other case.*/
  const OdPrcFileStructure* findFileStructureByUID (const OdPrcUniqueId &uuid) const;
  
  /** \details 
  Converts all OdPrcCompressedBrepData objects from the file to OdPrcBrepData objects.
  
  \param pFile [in/out] A smart pointer to the .prc file object with compressed brep data.*/
  static void decompressCompressedBreps( OdPrcFilePtr& pFile );

  /** \details 
  Reads the specified .prc file.
  
  \param file [in] The full name of the file to read from.
  \param pAuditInfo [out] Pointer to an OdPrcAuditInfo object for checking whether the created .prc file is correct.*/
  virtual void readFile(const OdString &file, OdPrcAuditInfo *pAuditInfo = 0 );
  
  /** \details 
  Reads a .prc file from a specified stream.
  
  \param pStream [in] Stream buffer to read from.
  \param pAuditInfo [out] Pointer to an OdPrcAuditInfo object for checking whether the created .prc file is correct.*/
  virtual void readFile(OdStreamBufPtr pStream, OdPrcAuditInfo *pAuditInfo = 0);
  
  /** \details
  Compress .prc file data with specified settings.

  \param settings [in] settings for .prc file compression.
  */
  void compressFile(const OdPrcFileSettings & settings);

  /** \details 
  Writes .prc file data to a specified stream with specified settings.
  
  \param pStream [in] A stream buffer to write to.
  \param pSettings [in] A smart pointer to the .prc file object for writing.
  */
  void writeFile(OdStreamBufPtr pStream, const OdPrcFileSettings* pSettings = NULL );

  /** \details 
  Adds the specified file structure to the .prc file.
  
  \param fileStructure [in] The new file structure to be added.
  */
  void addFileStructure (OdPrcFileStructure &fileStructure);

  /** \details 
  Returns the current service for platform dependent operations.
  */
  OdPrcHostAppServices* getAppServices() const;

  /** \details 
  Sets a new instance of a current service for platform dependent operations.
  \param svcs [in] A pointer to a new service instance. 
  */
  void setAppServices(OdPrcHostAppServices* svcs);

  /** \details 
  Initializes the .prc file data.
  \param isDef [in] Not used. 
  */
  void initialize(bool isDef);

  /** \details 
  Sets a new active viewport for the file.
  \param pActiveView [in] A pointer to a new viewport to be set.
  */
  void setActiveView(OdGsView *pActiveView);

  /** \details 
  Returns the current active viewport for the file.
  */
  OdGsView *getActiveView() const;

  /** \details 
  Returns the current units formatter interface.
  \remarks 
  Units formatter interface is returned as a reference.
  */  
  OdPrcUnitsFormatter& formatter();

  /** \details 
  Sets a new drawable object cache.
  \param pGsNode [in] A pointer to a new cache to be set.
  */
  virtual void setGsNode(OdGsCache* pGsNode);

  /** \details 
  Returns the current drawable object cache.
  */
  virtual OdGsCache* gsNode() const;

  /** \details 
  Returns the current number of isolines.
  */
  OdUInt32 getNumberOfIsolines() const;

  /** \details 
  Sets a new current number of isolines.
  \param numIsolines [in] A new number of isolines to be set.
  */
  void setNumberOfIsolines(const OdUInt32 &numIsolines);

  /** \details 
  Returns the current .prc file name.
  */
  OdString getFilename() const;

  //DOM-IGNORE-BEGIN
  #define QVAR_DEF(type, name, unused3, unused4, unused5)               \
  public:                                                                 \
    /** Description: Returns the ##NAME quasi system variable.            \
      Remarks: ##remarks                                                  \
      Notes: ##notes                                                      \
      See Also: ##see_also                                                \
    */                                                                    \
    SVARS_FUNC_MODIFIER type get##name() const;                           \
    /** Description: Sets the ##NAME quasi system variable.               \
      Arguments:  val (I) New value for ##NAME. ##RANGE                   \
      Remarks: ##remarks                                                  \
      Notes: ##notes                                                      \
      See Also: ##see_also                                                \
    */                                                                    \
    SVARS_FUNC_MODIFIER void set##name(type val);

  //DOM-IGNORE-END

  #include "AppServices/PrcQuasiVarDefs.h"

  #undef QVAR_DEF

  /** \details 
  Returns the current viewport object ID.
  */
  OdPrcObjectId getCurrentViewId() const;

  /** \details 
  Returns the current viewport array.
  \param bUpdate [in] A flag that determines whether the view node array should be updated from cache.
  */
  const OdArray<OdPrcViewNode> & getViewNodes(bool bUpdate = true);

  /** \details 
  Sets a new view node.
  \param nViewNodeIndex [in] An index of the new view node.
  */
  bool setViewNode(OdInt32 nViewNodeIndex);

  /** \details 
  Sets a new default view node.
  */
  bool setDefaultViewNode();

  /** \details 
  Returns the current view node index.
  */
  OdInt32 getCurrentViewNode() const;

  /** \details
  Returns the PRC object identifier for a database element specified with a handle.

  \param h [in] A database handle of the PRC object in the database.
  */
  OdPrcObjectId getObjectId(const OdDbHandle& h) const;

  /** \details
  Applies parameters of current view node OdPrcViewNode to active OdGsView.
  */
  bool applyCurrentView();

  /** \details
  Gets the current unit for the PRC file according to ISO 14739-1 item 5.6.
  \returns Returns the current unit for the PRC as an OdPrcUnit object.
  */
  const OdPrcUnit unit() const;

  /** \details
  Decompresses all compressed three-dimensional tessellation data in a specified file with passed parameters and updates file structures with decompressed data. 
  \param pFile  [out] A smart pointer to a file object where the tessellation data should be decompressed. 
  \param params [in] A set of decompression parameters. 
  */
  static void decompressCompressed3dTess(OdPrcFilePtr& pFile, const Decompress3dTessParams & params);
  
  /** \details
  Compresses three-dimensional tessellation data and updates all file structures with compressed data in the specified file.
  \param pFile [out] A smart pointer to a file object where the tessellation data should be compressed. 
  */
  static void compress3dTess(OdPrcFilePtr& pFile);

  /** \details
  Regenerates references arrays of every file structure of the file.
  \param file [in/out] A file whose file structures references arrays should be regenerated.
  */
  static void updateFileStructuresReferences(OdPrcFile &file);
};

#endif // _PRCFILE_INCLUDED_


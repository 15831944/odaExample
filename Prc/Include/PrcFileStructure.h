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

#ifndef _PRCFILESTRUCTURE_INCLUDED_
#define _PRCFILESTRUCTURE_INCLUDED_ 
 

#include "PrcSchema.h"
#include "PrcFileStructureGlobals.h"
#include "PrcFileStructureTree.h"
#include "PrcFileStructureTessellation.h"
#include "PrcFileStructureGeometry.h"
#include "PrcUncompressedFiles.h"

class OdPrcHandleTree;
class OdPrcStub;
class OdPrcFileStructureImpl;

SMARTPTR(OdPrcFileStructure);

/** \details 
<group PRC_Files_Structures_Assemblies>

Class implements a .prc file structure.
Each .prc file structure consists of the following parts:
<table>
Component           Description
Header              Contains common information about the file structure.
Schema              Contains information about entities that have been changed between the minimum format version for reading and original author format version. 
Tree of items       Description of the items tree. Each item can be a product occurrence, a part definition, a representation item, or a markup.
Tessellation data   Contains tessellated data in the leaf items of the structure tree.
Global data         Coordinate systems, colors, line styles, and other file structures referenced in this file structure.
Exact geometry      Exact geometry and topology data of the leaf items of the structure tree.
Extra geometry      Geometry summary information which can be loaded partially without loading all the geometry.
</table>
*/
class PRC_TOOLKIT OdPrcFileStructure : public OdDbBaseDatabase
{
private:
  friend class OdPrcSystemInternals;
  OdPrcFileStructureImpl *m_pImpl;

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcFileStructure);
  //DOM-IGNORE-END

  /** \details
  Returns the current exact geometry of the file structure.
  Exact geometry is returned as a reference to an OdPrcFileStructureGeometry object, therefore it can be used to set new exact geometry for the structure.
  */
  OdPrcFileStructureGeometry &fileStructureGeometry();
  
  /** \details 
  Returns the current exact geometry of the file structure.*/
  const OdPrcFileStructureGeometry &fileStructureGeometry() const;
  
  /** \details
  Returns current tessellation data of the file structure.
  Tessellation data is returned as a reference to an OdPrcFileStructureTessellation object, therefore it can be used to set new tessellation data for the structure.
  */
  OdPrcFileStructureTessellation &fileStructureTessellation();
  
  /** \details 
  Returns current tessellation data of the file structure.*/
  const OdPrcFileStructureTessellation &fileStructureTessellation() const;
  
  /** \details
  Returns the current file structure tree.
  File structure tree is returned as a reference to an OdPrcFileStructureTree object, therefore it can be used to set a new file structure tree.
  */
  OdPrcFileStructureTree &fileStructureTree();
  
  /** \details 
  Returns the current file structure tree.*/
  const OdPrcFileStructureTree &fileStructureTree() const;
  
  /** \details
  Returns current global data of the file structure.
  Global data is returned as a reference to an OdPrcFileStructureGlobals object, therefore it can be used to set new global data for the structure.
  */
  OdPrcFileStructureGlobals &fileStructureGlobals();
  
  /** \details 
  Returns current global data of the file structure.*/
  const OdPrcFileStructureGlobals &fileStructureGlobals() const;
  
  /** \details
  Returns the current schema of the file structure.
  The schema is returned as a reference to an OdPrcSchema object, therefore it can be used to set a new schema for the structure.
  */
  OdPrcSchema &schema();
  
  /** \details 
  Returns the current schema of the file structure.*/
  const OdPrcSchema &schema() const;

  /** \details 
  Returns the current array of private uncompressed files from the file structure header.
  The files array is returned as a reference to an OdPrcUncompressedFiles object, therefore it can be used to set a new file array.
  */
  OdPrcUncompressedFiles &uncompressedFiles();
  
  /** \details 
  Returns the current array of private uncompressed files from the file structure header.*/
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
  Destroys the file structure.*/
  virtual ~OdPrcFileStructure();

  /** \details
  Adds a PRC object to the database.
  
  \param object [in] A pointer to the PRC object to be added to the database.
  */
  void addObject (OdPrcReferencedBase *object);
  
  /** \details
  Adds a PRC object to the database with a specified unique identifier.
  
  \param object [in] A pointer to the PRC object to be added to a database.
  \param uid    [in] A unique identifier for the object to be added.
  */
  void addObject (OdPrcReferencedBase *object, OdUInt32 uid);
  
  /** \details
  Adds a PRC body to the database.
  
  \param body [in] A raw pointer to a PRC body to be added to the database.
  */
  void addObject (OdPrcBody *body);
  
  /** \details
  Returns the PRC object identifier for a database element specified with a handle.
  
  \param h [in] A database handle of the PRC object in the database.
  */
  OdPrcObjectId getObjectId (const OdDbHandle& h) const;

  /** \details
  Sets a new PRC object identifier for the file structure.
  
  \param stub [in] A pointer to a stub.
  */
  void setObjectId (OdDbStub* stub);
  
  /** \details
  Returns the current object identifier for the file structure.*/
  const OdPrcObjectId& objectId() const;

  /** \details
  Writes extra geometry data of the file structure to a specified output stream.
  
  \param pStream [in] A pointer to an output stream to write to.
  */
  void writeExtraGeometry (OdPrcCompressedFiler *pStream);
  
  /** \details
  Reads extra geometry data from a specified input stream.
  
  \param pStream [in] A pointer to an input stream to read from.
  */
  void readExtraGeometry (OdPrcCompressedFiler *pStream);

};

#endif // _PRCFILESTRUCTURE_INCLUDED_


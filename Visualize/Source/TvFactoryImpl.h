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

#ifndef _ODTV_FACTORYIMPL_H_INCLUDED_
#define _ODTV_FACTORYIMPL_H_INCLUDED_

#include "Tv.h"
#include "TvFactory.h"
#include "TvDatabaseImpl.h"
#include "TvInterfaceWrappersPool.h"
#include "TvHostAppServices.h"

#include "../Core/Source/TvTf/TfRevisionControlInternal.h"

/** \details
This is a help class which is need to control the memory allocation/deallocation
*/

class OdTvMemoryChecker
{
  OdUInt64 m_createdTransforms;
  OdUInt64 m_createdLocalTraits;
  OdUInt64 m_createdGeomSpecificTraits;
  OdUInt64 m_createdEntities;
  OdUInt64 m_createdGeometries;
  OdUInt64 m_createdDbDevices;
  OdUInt64 m_createdTvDevices;
  OdUInt64 m_createdLayoutHelpers;
  OdUInt64 m_createdDeviceIterators;
  OdUInt64 m_createdDbViews;
  OdUInt64 m_createdGiContexts;
  OdUInt64 m_createdBlockIterators;
  OdUInt64 m_createdEntityIterators;
  OdUInt64 m_createdEntityDbIterators;
  OdUInt64 m_createdGeometryIterators;
  OdUInt64 m_createdLayersIterators;
  OdUInt64 m_createdLinetypesIterators;
  OdUInt64 m_createdMaterialsIterators;
  OdUInt64 m_createdModelsIterators;
  OdUInt64 m_createdTextStylesIterators;
  OdUInt64 m_createdRasterImagesIterators;
  OdUInt64 m_createdVisualStylesIterators;
  OdUInt64 m_createdBackgroundsIterators;
  OdUInt64 m_createdDataLinks;
  OdUInt64 m_createdDbDatabases;
  OdUInt64 m_createdDatabases;
  OdUInt64 m_createdLayers;
  OdUInt64 m_createdInserts;
  OdUInt64 m_createdLights;
  OdUInt64 m_createdLinetypes;
  OdUInt64 m_createdLinetypeElements;
  OdUInt64 m_createdLinetypeElementsImpl;
  OdUInt64 m_createdMaterials;
  OdUInt64 m_createdRasterImages;
  OdUInt64 m_createdRawRasterImages;
  OdUInt64 m_createdTextStyles;
  OdUInt64 m_createdBlocks;
  OdUInt64 m_createdVisualStyles;
  OdUInt64 m_createdBackgrounds;
  OdUInt64 m_createdBlockTableRecords;
  OdUInt64 m_createdModels;
  OdUInt64 m_createdCDATreeStorages;
  OdUInt64 m_createdDbCDATreeStorageIterator;
  OdUInt64 m_createdGiPath;
  OdUInt64 m_createdHighlightStyles;
  OdUInt64 m_createdHighlightStylesIterators;

  OdUInt64 m_deletedTransforms;
  OdUInt64 m_deletedLocalTraits;
  OdUInt64 m_deletedGeomSpecificTraits;
  OdUInt64 m_deletedEntities;
  OdUInt64 m_deletedGeometries;
  OdUInt64 m_deletedDbDevices;
  OdUInt64 m_deletedTvDevices;
  OdUInt64 m_deletedLayoutHelpers;
  OdUInt64 m_deletedDeviceIterators;
  OdUInt64 m_deletedDbViews;
  OdUInt64 m_deletedGiContexts;
  OdUInt64 m_deletedBlockIterators;
  OdUInt64 m_deletedEntityIterators;
  OdUInt64 m_deletedEntityDbIterators;
  OdUInt64 m_deletedGeometryIterators;
  OdUInt64 m_deletedLayersIterators;
  OdUInt64 m_deletedLinetypesIterators;
  OdUInt64 m_deletedMaterialsIterators;
  OdUInt64 m_deletedModelsIterators;
  OdUInt64 m_deletedTextStylesIterators;
  OdUInt64 m_deletedRasterImagesIterators;
  OdUInt64 m_deletedVisualStylesIterators;
  OdUInt64 m_deletedBackgroundsIterators;
  OdUInt64 m_deletedDataLinks;
  OdUInt64 m_deletedDbDatabases;
  OdUInt64 m_deletedDatabases;
  OdUInt64 m_deletedLayers;
  OdUInt64 m_deletedInserts;
  OdUInt64 m_deletedLights;
  OdUInt64 m_deletedLinetypes;
  OdUInt64 m_deletedLinetypeElements;
  OdUInt64 m_deletedLinetypeElementsImpl;
  OdUInt64 m_deletedMaterials;
  OdUInt64 m_deletedRasterImages;
  OdUInt64 m_deletedRawRasterImages;
  OdUInt64 m_deletedTextStyles;
  OdUInt64 m_deletedBlocks;
  OdUInt64 m_deletedVisualStyles;
  OdUInt64 m_deletedBackgrounds;
  OdUInt64 m_deletedBlockTableRecords;
  OdUInt64 m_deletedModels;
  OdUInt64 m_deletedCDATreeStorages;
  OdUInt64 m_deletedDbCDATreeStorageIterator;
  OdUInt64 m_deletedGiPath;
  OdUInt64 m_deletedHighlightStyles;
  OdUInt64 m_deletedHighlightStylesIterators;

public:

  enum ObjectType
  {
    kTransfrom = 0,
    kLocalTraits = 1,
    kGeomSpecificTraits = 2,
    kEntity = 3,
    kGeometry = 4,
    kDbDevice = 5,
    kDbView = 6,
    kTvDevice = 7,
    kLayoutHelper = 8,
    kGiContext = 9,
    kLayersIterator = 10,
    kDevicesIterator = 11,
    kBlocksIterator = 12,
    kEntitiesIterator = 13,
    kEntitiesIteratorDb = 14,
    kGeometriesIterator = 15,
    kLinetypesIterator = 16,
    kMaterialsIterator = 17,
    kModelsIterator = 18,
    kTextStylesIterator = 19,
    kRasterImagesIterator = 20,
    kDataLink = 21,
    kDbDatabase = 22,
    kDatabase = 23,
    kLayer = 24,
    kInsert = 25,
    kLight = 26,
    kLinetype = 27,
    kLinetypeElement = 28,
    kLinetypeElementImpl = 29,
    kMaterial = 30,
    kRasterImage = 31,
    kRawRasterImage = 32,
    kTextStyle = 33,
    kBlock = 34,
    kBlockTableRecord = 35,
    kModel = 36,
    kVisualStyle = 37,
    kVisualStylesIterator = 38,
    kViewBackground = 39,
    kViewBackgroundIterator = 40,
    kDbCDATreeStorage = 41,
    kDbCDATreeStorageIterator = 42,
    kGiPath = 43,
    kHighlightStyle = 44,
    kHighlightStylesIterator = 45  };

  OdTvMemoryChecker();

  void newObject(ObjectType type);
  void deleteObject(ObjectType type);
  void writeState();

private:
  void addStateStrings(OdUInt64 iAdded, OdUInt64 iDeleted, const OdString& name,
                      OdStringArray& created, OdStringArray& deleted, OdStringArray& undeleted);
};

/** \details
    This is an interface class for OdTvFactory object which needs by TV clients to create new object instances.

    \remarks
    The OdTvFactory class is used through it's API calls to create and delete main TV objects instances (like databases, views etc)
*/
class OdTvFactoryImpl : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvFactoryImpl);

  OdTvFactoryImpl();
  ~OdTvFactoryImpl();

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Interface implementation 
//////////////////////////////////////////////////////////////////////////////////////////////////////
  /** \details
  Creates new database
  */
  OdTvDatabaseId createDatabase(OdCodePageId cp, OdTvResult* rc = NULL);

  /** \details
  Returns the OdTvResult code of this Error object.
  */
  OdTvResult removeDatabase(const OdTvDatabaseId& id);

  /** \details
  Returns the OdTvResult code of this Error object.
  */
  OdTvResult clearDatabases();

  /** \details
  Loads the contents of the specified (.*vsf) file into the new created TV database

  Throws:
  OdTvError if the read is unsuccessful.
  */
  OdTvDatabaseId readFile(const OdString& filename, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL);
  OdTvDatabaseId readVSFX( const OdString& filename, bool bMtMode = false, bool bPartialMode = false, const OdTvVSFXReadOptions& options = OdTvVSFXReadOptions(), OdTvResult* rc = NULL );
  OdTvDatabaseId readVSFX( OdStreamBufPtr pStream, bool bMtMode = false, bool bPartialMode = false, const OdTvVSFXReadOptions& options = OdTvVSFXReadOptions(), OdTvResult* rc = NULL );

  /** \details
  Loads the contents from the specified stream into the new created TV database

  Throws:
  OdTvError if the read is unsuccessful.
  */
  OdTvDatabaseId read(OdStreamBuf* buff, bool bMtMode = false, bool bPartialMode = false, OdTvResult* rc = NULL);

  /** \details
  Imports the contents of the specified file into the new created TV database.

  Throws:
  OdTvError if the import is unsuccessful.
  */
  OdTvDatabaseId importFile(const OdTvBaseImportParams* pParams,  OdTvResult* rc = NULL);

  /** \details
  Imports the contents of the specified file into the VSF file trying to use as much less memory as it is possible (currently implemented only for .dwg files)
  */
  OdTvResult lowMemoryImportFile(const OdTvBaseImportParams* pParams, const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL);

  /** \details
  Loads the contents from the specified stream into the new created database using specific controller
  (mostly for internal using inside other ODA Platform projects)

  Throws:
  OdTvError if the read is unsuccessful.
  */
  OdTvDatabaseId read(OdRxObject* controller, OdStreamBuf *buff, bool closeInput = true, OdTvResult* rc = NULL);

  /** \details
  Removes all fonts from the global font table.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If all fonts objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  This operation has influence on every textstyle in each database. Should be used very carefully.
  */
  OdTvResult clearFontTable();

  /** \details
  Returns instance of OdTvLimitManager that was assigned to the factory, may be NULL
  */
  OdTvLimitManager* limitManager( OdTvResult* rc = NULL ) const;

  /** \details
  Assigns the OdTvLimitManager to the factory
  */
  OdTvResult setLimitManager(OdTvLimitManager* pLimitManager);

  /** \details
  Specifies that geometry data should use allocator or not
  */
  OdTvResult setUseAllocatorForGeometryData( bool bUse );

  /** \details
  Returns true if and only if geometry data should use allocator
  */
  bool getUseAllocatorForGeometryData( OdTvResult* rc = NULL ) const;

  /** \details
  Specifies that we are currently inside handles tree destructor
  */
  void setInsideHandlesTreeDestructor(bool bInside);

  /** \details
  Returns true if and only if we are inside handles tree destructor
  */
  bool getInsideHandlesTreeDestructor() const;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//OdTvFactoryImpl own methods 
//////////////////////////////////////////////////////////////////////////////////////////////////////
  
  OdTvInterfaceWrappersPool* getWrappersPool() {return &m_wrappersPool;}
  OdTvDatabaseImpl*          getTvDatabase(const OdTvDbDatabase* pDbDatabase);
  void                       transferImportParamsToFilerProperties(const OdTvBaseImportParams* pParams, OdRxDictionaryPtr pProperties, const OdString& strExt);
  void                       setVisualize2DwgExporter(OdTvVisualizeExport* pVisualize2DwgExport);
  OdTvVisualizeExport*       getVisualize2DwgExporter() const;

#ifdef ODTV_MEMORYCHECK
  void newObject(OdTvMemoryChecker::ObjectType type);
  void deleteObject(OdTvMemoryChecker::ObjectType type);
  void writeState();
#endif

  OdTvDatabaseReceiverPtr createDatabaseReceiver();
  OdTvDatabaseId createStreamingDatabase();
  void finalizeStreamingDatabase();

private:

#ifdef ODTV_MEMORYCHECK
  OdTvMemoryChecker *m_pMemChecker;
#endif

  // factory for the interfaces
  OdTvInterfaceWrappersPool m_wrappersPool;

  //vectors of the databases
  OdVector<OdTvDatabaseImplPtr> m_databases;

  // App host serives for the creation of the OdTvDbDatabase
  OdStaticRxObject<TvHostAppServices> m_svcs;

  // Exporter for dwg Visualize to DWG export
  OdTvVisualizeExport*        m_pVisualize2DwgExport;

  //LimitManager
  OdTvLimitManager* m_pLimitManager;
  bool              m_bUseAllocator;

  //special flag for solve issues with deleting objects from destructor of the handles tree
  bool              m_bInsideHandlesTreeDestructor;

  //pointer to the currently processing database since it is not in m_databases now
  OdTvDatabaseImpl* m_pCurrentlyLoadingDatabase;

};

typedef OdSmartPtr<OdTvFactoryImpl> OdTvFactoryImplPtr;

/** \details
  Returns the smart pointer to the factory implementation object.
  
  \returns
   the smart pointer to the factory object.
*/

OdTvFactoryImplPtr odTvGetFactoryImpl();

/** \details
Writes the version of the VSF file to stream

\returns
Nothing
*/
void writeVSFVersion(OdTvDbDwgFiler* pFiler, const OdTvVSFVersion& ver);

/** \details
Reads the version of the VSF file from stream

\returns
version of the VSF file.
*/
OdTvVSFVersion readVSFVersion(OdTvDbDwgFiler* pFiler);

/** \details
Cast Dwg filer to OdTvcFiler if it is possible

\returns
pointer to OdTvcFiler or NULL
*/
OdTvcFiler* getTvcFiler(OdTvDbDwgFiler* pFiler);


#endif //_ODTV_FACTORYIMPL_H_INCLUDED_

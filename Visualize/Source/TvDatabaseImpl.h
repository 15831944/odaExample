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


#ifndef _ODTV_DATABASEIMPL_H_INCLUDED_
#define _ODTV_DATABASEIMPL_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvDatabase.h"
#include "TvInterfaceWrappers.h"
#include "TvGsDevice.h"
#include "TvDataLink.h"
#include "TvUserDataImpl.h"
#include "TvStatisticsImpl.h"
#include "TvBlockTableRecordImpl.h"
#include "TvVSFXDatabase.h"

#include "DbDatabase.h"
#include "DbDictionary.h"
#include "DbSymbolTable.h"
#include "Gi/GiVisualStyle.h"

#define STL_USING_MAP
#include "OdaSTL.h"
#include "../Source/database/DbDatabaseImpl.h"
#include "TvCommonDataAccessTree.h"
#include "TvHighlightStyleImpl.h"

#include "TvFilerWrapper.h"
#include "../../TvCore/Include/TvCoreDatabaseSection.h"

class OdGsDeviceForTvImpl;
typedef OdSmartPtr<OdGsDeviceForTvImpl> OdGsDeviceForTvImplPtr;
typedef OdVector<OdRxClass*, OdMemoryAllocator<OdRxClass*> >             OdRxClassArray;

class OdTvDatabaseImpl;

#define _REV_CTRL_

/** \details
This class is used to ensure OdTvDbDatabase::setHANDSEED consistency 
in terms of using negative handles for the objects which should not be saved 
in the file
*/
class OdTvHandseedChanger
{
public:
  OdTvHandseedChanger(const OdTvDbDatabase* pDb, OdUInt64 handseed)
  {
    m_pDb = OdTvDbDatabaseImpl::getImpl(pDb);
    m_curHandseed = m_pDb->getHANDSEED();
    
    // set negative handseed
    m_pDb->setHANDSEED(handseed);
  }

  void setHandseed(OdUInt64 handseed)
  {
    m_pDb->setHANDSEED(handseed);
  }

  ~OdTvHandseedChanger()
  {
    //back old handseed
    m_pDb->setHANDSEED(m_curHandseed);
  }

private:
  OdDbHandle         m_curHandseed;
  OdTvDbDatabaseImpl*  m_pDb;
};



/** \details
This is clear child of the OdTvDbDatabase which is only need for using different from OdTvDbDatabasePE 
protocol extension for the database used in Visualize SDK
*/
class ODTV_EXPORT OdDbDatabaseTv : public OdTvDbDatabase
{
  OdDbDatabaseTv();

public:
  ODRX_DECLARE_MEMBERS(OdDbDatabaseTv);

  virtual ~OdDbDatabaseTv();

  /** \details
  Performs TV specific initialization
  */
  bool initialize(bool createDbDefault);

  /** \details
  Add device to the appropriate dictionary
  */
  OdTvDbObjectId addDevice(const OdString& name, bool bIsBitmap, OdTvResult* rc);

  /** \details
  Remove device from the dictionary

  \param deviceId [in]  Id of the device object.
  */
  void removeDevice(OdTvDbObjectId deviceId);

  /** \details
  Get iterator over devices
  */
  OdTvDbDictionaryIteratorPtr getDevicesIterator() const;

  /** \details
  Add the Common Data Access (CDA) tree to the database.
  */
  OdTvDbObjectId addCDATreeStorage(const OdString& name, OdTvCDATreePtr pTree, OdTvResult* rc);

  /** \details
  Remove CDA tree storage from the dictionary

  \param deviceId [in]  Id of the tree storage object.
  */
  void removeCDATreeStorage(OdTvDbObjectId treeStorageId);

  /** \details
  Get iterator over CDA tree storages
  */
  OdTvDbDictionaryIteratorPtr getCDATreeStoragesIterator() const;

  /** \details
  get active device
  */
  OdGsDeviceForTvImplPtr getActiveDevice() const;

  /** \details
  Mark that during saving to VSF all models should be saved
  */
  void setWriteAllModels(bool bWriteAll);

  /** \details
  Returns true if and only if all models should be save to VSF file
  */
  bool getWriteAllModels();

  /** \details
  Set the model which should be saved to DWG
  */
  void setModelForSaveInDWG(OdTvModelId modelId);

  /** \details
  Returns the Id of the model which should be saved in DWG
  */
  OdTvModelId getModelForSaveInDWG();

  /** \details
  Set device which should be saved to DWG
  */
  void setDeviceForSaveInDWG(OdTvGsDeviceId deviceId);

  /** \details
  Returns the Id of the device which should be saved in DWG
  */
  OdTvGsDeviceId getDeviceForSaveInDWG();

  /** \details
  Set view which should be saved to DWG
  */
  void setViewForSaveInDWG(OdTvGsViewId viewId);

  /** \details
  Returns the Id of the view which should be saved in DWG
  */
  OdTvGsViewId getViewForSaveInDWG();

  /** \details
  Set true if and only if the DWG should be saved as proxy
  */
  void setSaveDWGAsProxy(bool bAsProxy);

  /** \details
  Returns true if and only if the DWG should be saved as proxy
  */
  bool getSaveDWGAsProxy();

  /** \details
  Set 'true' if and only if it is need to disable the internal notifications about the
  modifications of the objects. Setting this option to 'true' allow to speed up the process of the initial
  filling of the database. The default value is 'true'. The 'false' value allow
  to take into account the modifications of the database objects during the paint process
  */
  virtual void setSilentMode(bool bOn);

  /** \details
  Returns the true if and only if the silent mode is On
  */
  bool getSilentMode();

  virtual bool usingCoreOnly() const;

  /** \details
    Set reject reactors flag to database impl
  */
  void setRejectReactors(bool bRejectReactors);

  /** \details
  Returns true if and only if we should simulate onUnerased reactors instead of onAdded
  */
  bool isNeedSimulateUnerased() { return m_bNeedSimulateUnerased; }

  /** \details
  Set need simulate unerased flag
  */
  void setNeedSimulateUnerased(bool bNeedSimulateUnerased) { m_bNeedSimulateUnerased = bNeedSimulateUnerased; }

  bool getStreamingMode() const;

  void setStreamingMode(bool isEnable);

  /** \details
    Set active layout.
  */
  void setActiveLayout(OdDbStub* layoutId);

  /** \details
    Get active layout
  */
  OdTvDbObjectId getActiveLayout() const;

  /** \details
  Returns the version of the VSF file from which this database was read.
  */
  OdTvVSFVersion getVSFVersion() const;

  /** \details
  Sets the version of the VSF file from which this database was read.
  */
  void           setVSFVersion(const OdTvVSFVersion& version);

  const OdTvVSFExportOptions& getExportOptions() const { return m_exportOptions; }
  void setExportOptions(const OdTvVSFExportOptions& options) { m_exportOptions = options; }

  /** \details
    Set pdf export mode flag.
  */
  void setPdfExportMode(bool bVal);

  /** \details
    Get pdf export mode flag.
  */
  bool getPdfExportMode() const;

  /** \details
  Set device for bitmap generation in pdf export.
  */
  void setDeviceForBitmap(OdInt8 deviceId);

  /** \details
  Get device for bitmap generation in pdf export.
  */
  OdInt8 getDeviceForBitmap() const;

  /** \details
  Add animation action to the appropriate dictionary
  */
  OdTvDbObjectId addAnimationAction( const OdString& name, bool bNeedSaveInFile, OdInt64& negHandle, OdTvResult* rc );
  /** \details
  Remove animation action from the dictionary

  \param actionId [in]  Id of the action object.
  */
  void removeAnimationAction( OdTvDbObjectId actionId );

  /** \details
  Get iterator over animation actions
  */
  OdTvDbDictionaryIteratorPtr getAnimationActionIterator() const;

  /** \details
  Add animation container to the appropriate dictionary
  */
  OdTvDbObjectId addAnimationContainer( const OdString& name, bool bNeedSaveInFile, OdInt64& negHandle, OdTvResult* rc );
  /** \details
  Remove animation container from the dictionary

  \param deviceId [in]  Id of the device object.
  */
  void removeAnimationContainer( OdTvDbObjectId managerId );

  /** \details
  Get iterator over animation containers
  */
  OdTvDbDictionaryIteratorPtr getAnimationContainerIterator() const;

  /** \details
  Add the highlight style to the database.
  */
  OdTvDbObjectId addHighlightStyle(const OdString& name, OdTvResult* rc);

  /** \details
  Find highlight style by name.
  */
  OdTvDbObjectId findHighlightStyle(const OdString& name, OdTvResult* rc);

  /** \details
  Remove highlight style from the dictionary
  */
  void removeHighlightStyle(OdTvDbObjectId highlightStyleId);

  /** \details
  Get iterator over highlight styles
  */
  OdTvDbDictionaryIteratorPtr getHighlightStylesIterator() const;

  /** \details
  Sets a new path to a custom folder that contains image files used as textures, backrounds or as separate objects.
  */
  OdTvResult setCustomImageFolder(const OdString& strFolderPath);

  /** \details
  Retrieves the current path to the custom folder that contains image files used as textures, backrounds or as separate objects.
  */
  OdString getCustomImageFolder(OdTvResult* rc = NULL) const;

  /** \details
  get custom image folder from xData
  */
  void initCustomImageFolder();

  /** \details
  Set the drawing units for this database (for internal use only)
  */
  void setUnits(OdTv::Units units);

  /** \details
  Returns the number of points with non-inherited units
  */
  int getNumModelsWithUnits() const;

private:
  void createDefaultHighlightStyles();

private:
  bool          m_bUsingCoreOnly;

  OdTvDbObjectId m_TvGsDeviceDicId;       // dictionary for the OdTvGsDevice
  OdTvDbObjectId m_TvCDATreeDicId;        // dictionary for the CDA trees
  OdTvDbObjectId m_TvHighlightStyleDicId; // dictionary for the highlight styles
  OdTvDbObjectId m_tvAnimationContainerDicId; // dictionary for the OdTvAnimationContainer
  OdTvDbObjectId m_tvAnimationActionDicId; // dictionary for the OdTvAnimationAction

  OdTvVSFVersion  m_version;         // version of the Visualize SDK (usually used for the VSF files)

  // real time flags
  bool          m_bWriteAll;
  bool          m_bSilentModeOn;
  // this flag means that we should call onUnerased instead of onAdded. It is for the methods like insertAt, addInsertAt
  bool          m_bNeedSimulateUnerased;

  //specific data for writing the DWG file
  OdTvGsDeviceId m_tvDeviceForSaveInDWG;
  OdTvModelId   m_tvModelForSaveInDWG;
  OdTvGsViewId  m_tvViewForSaveInDWG;
  bool          m_bSaveDWGAsProxy;
  bool          m_bStreamingModeOn;

  // export options for the VSF file
  OdTvVSFExportOptions  m_exportOptions;

  //data for the PDF export (need for PE)
  OdTvDbObjectId          m_activeLayout;
  bool                  m_bPdfExportModeOn;
  OdInt8                m_deviceForBitmap;  //here -1 means default. Other values are from OdTvPdfExportParams::Device.

  //custom image folder
  OdString m_strCustoImageFolder;

  public:
    void getServiceObjects( OdVector< OdTvDbObjectId >& objects );

};
typedef OdSmartPtr<OdDbDatabaseTv> OdDbDatabaseTvPtr;




/** \details
    This class implements OdTvDatabaseImpl.
*/
class OdTvDatabaseImpl : public OdTvIObjectImpl, public OdTvXDataStorage, public OdTvVSFXDatabase
{
  friend class OdTvFactoryImpl;
  OdTvDatabaseImpl(OdTvDbHostAppServices* pHostApp, bool createDbDefault = true);
protected:
  ODRX_HEAP_OPERATORS();

public:

  static OdTvSmartPtr<OdTvDatabaseImpl> createObject(OdTvDbHostAppServices* pHostApp, bool createDbDefault = true);                        
  virtual ~OdTvDatabaseImpl();

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Interface implementation 
//////////////////////////////////////////////////////////////////////////////////////////////////////
  /** \details
  Creates the model object and returns the appropriate ID

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvModelId createModel(const OdString& name, OdTvModel::Type type, bool bNeedSaveInFile, OdTvResult* rc = NULL);

  /** \details
  Remove model object with the given ID
  */
  OdTvResult removeModel(const OdTvModelId& id);

  /** \details
  Remove all models
  */
  OdTvResult clearModels();

  /** \details
  Find a model by name, and return OdTvModelId
  */
  OdTvModelId findModel(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a block object and returns the appropriate ID

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvBlockId createBlock(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove block object with the given ID
  */
  OdTvResult removeBlock(const OdTvBlockId& id);

  /** \details
  Remove all blocks
  */
  OdTvResult clearBlocks();

  /** \details
  Find a block by name, and return OdTvBlockId
  */
  OdTvBlockId findBlock(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a device object and returns the appropriate ID
  */
  OdTvGsDeviceId createDevice(const OdString& name, OSWindowHandle wnd_handle, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL);

  /** \details
  Creates a device object and returns the appropriate ID
  */
  OdTvGsDeviceId createDeviceWithContext(const OdString& name, OSWindowGLContext wnd_context, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL);

  /** \details
  Creates a "non-setup" device object and returns the appropriate ID
  */
  OdTvGsDeviceId createDevice(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a bitmap device object and returns the appropriate ID
  */
  OdTvGsDeviceId createBitmapDevice(const OdString& name, long x, long y, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL);

  /** \details
  Creates a "non-setup" bitmap device object and returns the appropriate ID
  */
  OdTvGsDeviceId createBitmapDevice(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a device object with the given ID
  */
  OdTvResult removeDevice(const OdTvGsDeviceId& id);

  /** \details
  Remove all devices
  */
  OdTvResult clearDevices();

  /** \details
  Returns the active OdTvGsDevice object associated with this database object.
  If there is no active devices - this method returns first device
  */
  OdTvGsDeviceId getActiveDevice(OdTvResult* rc = NULL);

  /** \details
  Returns the version of the VSF file from which this database was read.
  */
  OdTvVSFVersion getVSFVersion(OdTvResult* rc = NULL) const;

  /** \details
  Sets the compression options which will be used during the export of the Visualize database to the VSF file or stream.
  */
  OdTvResult setVSFExportOptions(const OdTvVSFExportOptions& options);

  /** \details
  Returns the compression options which is used during the export of the Visualize database to the VSF file or stream.
  */
  OdTvVSFExportOptions getVSFExportOptions(OdTvResult* rc = NULL);

  /** \details
  Writes the contents of this database object to the specified file.

  Throws:
  OdTvError if the write is unsuccessful.
  */
  OdTvResult writeFile(const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL);

  bool isPartiallyOpened() const;

  /** \details
  Add the Common Data Access (CDA) tree to the database.
  */
  OdTvCDATreeStorageId addCDATreeStorage(const OdString& name, OdTvCDATreePtr pTree, OdTvResult* rc = NULL);

  /** \details
  Remove CDA tree storage from the dictionary

  \param id [in]  Id of the tree storage object.
  */
  OdTvResult removeCDATreeStorage(const OdTvCDATreeStorageId& id);

  /*PARTIAL SUPPORT*/
  virtual OdTvResult beginPartialImport( const OdString& filename );
  virtual OdTvResult writeObjectPartial( OdTvEntityId id );
  virtual OdTvResult endPartialImport();

  virtual OdTvResult disableInternalNotifications();

  /** \details
  Writes the contents of this database object to the specified stream buffer

  Throws:
  OdTvError if the write is unsuccessful.
  */
  OdTvResult write(OdStreamBuf *buffer, const OdTvVSFExportOptions* pOptions = NULL);

  /** \details
  Get current database' list of branches.
  */
  OdTvResult getBranchList(OdStringArray &branches, OdString &currentBranch);

  /** \details
  Export database into the specified file.
  \param pParams  [in] A pointer to an object that contains the <link OdTvBaseExportParams, export parameters>.
  \returns Returns parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \remarks
  The method throws the <link OdTvError, OdTvError> exception if the import operation is not successful.
  */
   OdTvResult exportTo(const OdTvBaseExportParams* pParams);

  /** \details
  Returns the pointer to the models iterator object
  */
  OdTvModelsIteratorPtr getModelsIterator(OdTvResult* rc = NULL) const;

  /** \details
  Returns the pointer to the blocks iterator object
  */
  OdTvBlocksIteratorPtr getBlocksIterator(OdTvResult* rc = NULL) const;

  /** \details
  Returns the pointer to the linetypes iterator object
  */
  OdTvLinetypesIteratorPtr getLinetypesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the llayers iterator object
  */
  OdTvLayersIteratorPtr getLayersIterator(OdTvResult* rc = NULL);

	/** \details
	Returns the pointer to the textstyles iterator object
	*/
	OdTvTextStylesIteratorPtr getTextStylesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the raster image iterator object
  */
  OdTvRasterImagesIteratorPtr getRasterImagesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the materials iterator object
  */
  OdTvMaterialsIteratorPtr getMaterialsIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the devices iterator object
  */
  OdTvDevicesIteratorPtr getDevicesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the visual styles iterator object
  */
  OdTvVisualStylesIteratorPtr getVisualStylesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns a smart pointer to an iterator object to get sequential access to view background objects in the database.
  */
  OdTvGsViewBackgroundsIteratorPtr getBackgroundsIterator(OdTvResult* rc = NULL);

  /** \details
  Get iterator over CDA tree storages
  */
  OdTvCDATreeStoragesIteratorPtr getCDATreeStoragesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the name of the file associated with the internal database object.
  */
  OdString getFilename(OdTvResult* rc = NULL) const;

  /** \details
  Returns the pointer to the internal database
  */
  virtual void* getInternalDatabase(OdTvResult* rc = NULL) const;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Group of the methods for managing different properties
/////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Creates a linetype object and returns the appropriate ID

  \param name     [in]  Linetype name as a String value up to 255 characters long.
  \param elements [in]  Array of line type pattern elements
  \param rc       [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvLinetypeId createLinetype(const OdString& name, const OdTvLinetypeElementArray& elements, OdTvResult* rc = NULL);

  /** \details
  Creates a linetype object and returns the appropriate ID

  \param name       [in]  Linetype name as a String value up to 255 characters long.
  \param nElements  [in]  Number of linetype pattern elements
  \param elements   [in]  Array of linetype pattern elements
  \param rc         [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvLinetypeId createLinetype(const OdString& name, OdInt32 nElements, const OdTvLinetypeElementPtr* elements, OdTvResult* rc = NULL);

  /** \details
  Remove a linetype object with the given ID
  */
  OdTvResult removeLinetype(const OdTvLinetypeId& id);

  /** \details
  Find a linetype by name, and return OdTvLinetypeId
  */
  OdTvLinetypeId findLinetype(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove all linetypes
  */
  OdTvResult clearLinetypes();

  /** \details
  Creates a layer object and returns the appropriate ID

  \param name         [in]  Layer name as a String value up to 255 characters long.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvLayerId createLayer(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a layer object with the given ID
  */
  OdTvResult removeLayer(const OdTvLayerId& id);

  /** \details
  Remove all layers
  */
  OdTvResult clearLayers();

  /** \details
  Find a layer by name, and return OdTvLayerId
  */
   OdTvLayerId findLayer(const OdString& name, OdTvResult* rc = NULL);


  /** \details
  Creates a text style object and returns the appropriate ID

  \param name     [in]  Text style name as a String value up to 255 characters long.
  \param rc       [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  
  Just created text style will be use the built-in font.
  */
  OdTvTextStyleId createTextStyle(const OdString& name, OdTvResult* rc = NULL);


  /** \details
  Remove a linetype object with the given ID
  */
  OdTvResult removeTextStyle(const OdTvTextStyleId& id);

  /** \details
  Remove all linetypes
  */
  OdTvResult clearTextStyles();

  /** \details
  Find a text style by name, and return OdTvTextStyleId
  */
  OdTvTextStyleId findTextStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a material object and returns the appropriate ID

  \param name         [in]  Material name as a String value up to 255 characters long.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).

  Also there are forbidden name: "Global", "ByBlock", "ByLayer"
  */
  OdTvMaterialId createMaterial(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a device object with the given ID
  */
  OdTvResult removeMaterial(const OdTvMaterialId& id);

  /** \details
  Remove all materials
  */
  OdTvResult clearMaterials();

  /** \details
  Find a material by name, and return OdTvMaterialId
  */
  OdTvMaterialId findMaterial(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Find a material by name or, if it fails, uses comparator.
  */
  OdTvMaterialId findMaterial( const OdTvMaterialComparator* pCmp, const OdString& name = OdString::kEmpty, OdTvResult* rc = NULL );

  /** \details
  Creates a raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param pathName     [in]  The name of the source file containing the raster image
  \param bLoad        [in]  Flag indicating whether it is need immediately loading of the image
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvRasterImageId createRasterImage(const OdString& name, const OdString& pathName, bool bLoad = false, OdTvResult* rc = NULL);

  /** \details
  Creates a raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvRasterImageId createRasterImage(const OdString& name, OdTvRasterImage::Format format, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4, OdTvResult* rc = NULL);

  /** \details
  Creates a palette based binary raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvRasterImageId createRasterImage(const OdString& name, OdTvRasterImage::Format paletteformat, OdUInt32 paletteSize, OdUInt8* paletteData,
                                     OdTvRasterImage::BitPerIndex bpi, OdUInt32 width, OdUInt32 height, const OdUInt8* data,
                                     OdUInt32 iAlignment = 4, OdTvResult* rc = NULL);

  /** \details
  Creates a monochrome raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvRasterImageId createRasterImage(const OdString& name, OdUInt32 width, OdUInt32 height, const OdUInt8* data,
                                      bool bInverted = false, OdUInt32 iAlignment = 4, OdTvResult* rc = NULL);

  /** \details
  Remove a raster image object with the given ID
  */
  OdTvResult removeRasterImage(const OdTvRasterImageId& id);

  /** \details
  Remove all raster images
  */
  OdTvResult clearRasterImages();

  /** \details
  Find a raster image by name, and return OdTvRasterImageId
  */
  OdTvRasterImageId findRasterImage(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a visual style object as a copy of the given visual style and returns the appropriate ID

  \param name         [in]  Visual style name as a String value up to 2049 characters long.
  \param vsId         [in]  Visual style to copy from.
  \param rc           [out] The code of the success or an error.
  */
  OdTvVisualStyleId createVisualStyle(const OdString& name, const OdTvVisualStyleId& vsId, OdTvResult* rc = NULL);

  /** \details
  Creates a visual style object as a empty visual style and returns the appropriate ID

  \param name         [in]  Visual style name as a String value up to 2049 characters long.
  \param rc           [out] The code of the success or an error.
  */
  OdTvVisualStyleId createVisualStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a visual style object with the given ID
  */
  OdTvResult removeVisualStyle(const OdTvVisualStyleId& id);

  /** \details
  Remove all visual styles
  */
  OdTvResult clearVisualStyles();

  /** \details
  Find a visual style by name, and return OdTvVisualStyleId
  */
  OdTvVisualStyleId findVisualStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a view background object and returns the appropriate ID.

  \param name   [in]  A view background name as a String value up to 2049 characters long.
  \param gbType [in]  A view background type.
  \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.

  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  OdTvGsViewBackgroundId createBackground(const OdString& name, OdTvGsViewBackgroundId::BackgroundTypes bgType, OdTvResult* rc = NULL);


  /** \details
  Removes a view background object with the specified identifier from the database.
  \param id [in] An identifier of the view background object that should be deleted.
  */
  OdTvResult removeBackground(const OdTvGsViewBackgroundId& id);

  /** \details
  Removes all view backgrounds objects from the database.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
  \remarks
  If all vview backgrounds objects have been successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  OdTvResult clearBackgrounds();

  /** \details
  Searches for a view background object with a specified name in the database.
  \param name [in] A name of the view background object to be found.
  \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
  */
  OdTvGsViewBackgroundId findBackground(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Registers the name of the app and returns the appropriate ID
  */
  OdTvRegAppId registerAppName(const OdString& appName, bool& bAlreadyExist, OdTvResult* rc = NULL);

  /** \details
  Get object type by handle
  */
  OdTv::HandledObjectType getObjectTypeByHandle(const OdUInt64 h, OdTvResult* rc = NULL);

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdUInt64& attrSize, OdTvResult* rc = NULL) const;

  /** \details
  Returns the OdTvEntityId that matches the original database handle.
  */
  OdTvEntityId findEntity(OdUInt64 originalDatabaseHandle, OdTvResult* rc = NULL);

  /** \details
  Sets a host app progress meter which will be used for direction the info about import process to the host app
  */
  OdTvResult setProgressMeter(OdTvHostAppProgressMeter* pProgressMeter);

  /** \details
  Set given code page to database.
  */
  OdTvResult setCodePage(OdCodePageId cp);

  /** \details
  Returns the pointer to the highlight styles iterator object
  */
  OdTvHighlightStylesIteratorPtr geHighlightStylesIterator(OdTvResult* rc = NULL);

  /** \details
  Creates a highlight style object as a empty highlight style and returns the appropriate ID

  \param name         [in]  highlight style name as a String value up to 2049 characters long.
  \param rc           [out] The code of the success or an error.
  */
  OdTvHighlightStyleId createHighlightStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a highlight style object as a copy of the given highlight style object and returns the appropriate ID.
  */
  OdTvHighlightStyleId createHighlightStyle(const OdString& name, const OdTvHighlightStyleId& highlightStyleId, OdTvResult* rc = NULL);

  /** \details
  Remove a highlight style object with the given ID
  */
  OdTvResult removeHighlightStyle(const OdTvHighlightStyleId& id);

  /** \details
  Remove all highlight styles
  */
  OdTvResult clearHighlightStyles();

  /** \details
  Find a highlight style by name, and return OdTvHighlightStyleId
  */
  OdTvHighlightStyleId findHighlightStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Sets a new path to a custom folder that contains image files used as textures, backrounds or as separate objects.
  */
  OdTvResult setCustomImageFolder(const OdString& strFolderPath);

  /** \details
  Retrieves the current path to the custom folder that contains image files used as textures, backrounds or as separate objects.
  */
  OdString getCustomImageFolder(OdTvResult* rc = NULL) const;

  /** \details
  Returns the drawing units set for this database.
  */
  OdTv::Units getUnits(OdTvResult* rc = NULL) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//OdTvDatabaseImpl own methods 
/////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Return the link to this data. Method for 'OdTvLinkIdAccess'
  */
  OdTvDataLink* getLink()
  {
    return m_pLink;
  }

  /** \details
  Loads the contents of the specified file into this database object

  Throws:
  OdTvError if the write is unsuccessful.
  */
  OdTvResult readFile(const OdString& filename, bool bMtMode, bool bPartialMode);

  /** \details
  Loads the contents of the specified buffer into this database object

  Throws:
  OdTvError if the write is unsuccessful.
  */
  OdTvResult read(OdStreamBuf* buff, bool bMtMode, bool bPartialMode);

  /** \details
  Loads the contents of the specified buffer into this database object using specific controller

  Throws:
  OdTvError if the write is unsuccessful.
  */
  OdTvResult read(OdRxObject* controller, OdStreamBuf *buff, bool closeInput = true);

  /** \details
  After read file actions
  */
  void afterReadFile( bool bFromStreamingService = false );

  /** \details
  Load all attributes (materials, devices, text styles etc) by opening them for the case of partial view mode
  */
  void loadAttributes();

  /** \details
    Remove the itself linkage
    
    \remarks
    This is an equivalent to removeFromDatabase for database objects.
    The object itself could be not deleted but it is already not relevant
  */
  void removeLinkage();

  /** \details
  Mark all text styles as not preloaded
  */
  void markTextStylesAsNotPreloaded();

  /** \details
    Returns true if and only if we should reject reactors actions inside the device
  */
  bool isNeedRejectReactors() {return m_bRejectReactors;}

  /** \details
    Set reject reactors flag
  */
  void setRejectReactors(bool bRejectReactors) { m_bRejectReactors = bRejectReactors; }

  /** \details
    Add data in map container
  */
  void addLinetypeToPredefinedMap(OdTvDbObjectId id, OdTvLinetype::Predefined lt);

  /** \details
    Check is have map this key or not
  */
  bool isHaveLinetypeInPredefinedMap(OdTvDbObjectId id) const;

  /** \details
    Return the predefined linetype
  */
  OdTvLinetype::Predefined getPredefinedLinetypeByDbId(OdTvDbObjectId id, OdTvResult* rc = NULL) const;

  /** \details
  Sets new handseed for database
  */
  void setNegativeHandseed(OdInt64 handseed) { m_nNEGATIVEHANDSEED = handseed; }

  /** \details
  Return the handseed
  */
  OdInt64 getNegativeHandseed() const { return m_nNEGATIVEHANDSEED; }

  /** \details
  Append new data from file to this database.
  */
  OdTvModelId append(const OdTvBaseImportParams* pParams, OdTvResult* rc = NULL);

  /** \details
  Retrieves the statistics for the database.
  */
  OdTvDatabaseStatistic getStatistic(OdTvResult* rc = NULL);

  /** \details
  Return the internal database
  */
  OdDbDatabaseTvPtr getDbDatabaseTv() const;

  /** \details
  Add or update partial view indexes for models of the database
  */
  OdTvResult addPartialViewIndexes(bool bUpdateExisting = true);

  /** \details
  Checks that the database has partial indexes.
  */
  virtual bool hasPartialViewIndexes( bool bCheckExtents = false, OdTvResult* rc = NULL);
  /** \details
  Create an animation action object
  */
  virtual OdTvAnimationActionId createAnimationAction( const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL );
  /** \details
  Remove an animation action object with the given ID
  */
  virtual OdTvResult removeAnimationAction( const OdTvAnimationActionId& id );
  /** \details
  Remove all animation actions
  */
  virtual OdTvResult clearAnimationActions();
  /** \details
  Returns the pointer to the animation actions iterator object
  */
  OdTvAnimationActionsIteratorPtr getAnimationActionsIterator( OdTvResult* rc = NULL );
  /** \details
  Create an animation container object 
  */
  virtual OdTvAnimationContainerId createAnimationContainer( const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL );
  /** \details
  Remove an animation container object with the given ID
  */
  virtual OdTvResult removeAnimationContainer( const OdTvAnimationContainerId& id );
  /** \details
  Remove all animation containers
  */
  virtual OdTvResult clearAnimationContainers();
  /** \details
  Returns the pointer to the animation containers iterator object
  */
  OdTvAnimationContainersIteratorPtr getAnimationContainersIterator( OdTvResult* rc = NULL );
  /** \details
  Set the drawing units for this database (for internal use only)
  */
  void setUnits(OdTv::Units units);
  /** \details
  Returns the number of points with non-inherited units
  */
  int getNumModelsWithUnits() const;

  /** \details
  Returns the number of models
  */
  int getNumModels() const;

  /** \details
  Returns the number of blocks
  */
  int getNumBlocks() const;

  /** \details
  Checks whether the app is already exist (need for safe work in MT, since we can't modifying the database in threads)
  */
  bool isAppNameAlreadyExist(const OdString& appName) const;

 private:
  /** \details
  Returns the pointer to the views DB iterator object
  */
  OdTvDbSymbolTableIteratorPtr getViewsIterator();

  /** \details
  Create default visual style
  */
  void createDefaultVisualStyle(OdTvDbDictionary* pDic, OdGiVisualStyle::Type type, const OdChar* name);

  /** \details
  Transfer appending properties
  */
  void transferAppendParamsToFilerProperties(const OdTvBaseImportParams* pParams, OdRxDictionaryPtr pProperties, const OdString& strExt, bool bDeviceExists = true);

  /** \details
  Get statistic from database
  */
  void getDatabaseStatistic(OdTvDatabaseStatisticImpl& stat);

  /** \details
  Notify devices about the gsmodel freed
  */
  void notifyDevicesGsModelFreed(OdGsModel* pGsModel);

  /** \details
  Cache entities from block to map with original handles and Tv entity id
  */
  void cacheBlockEntities(OdTvBlockTableRecord* pBlock, std::map<OdUInt64, OdTvEntityId>& map, OdTvRegAppId appId) const;

private:

  //Wrapped OdDb database
  OdDbDatabaseTvPtr m_pDbDatabase;

  // index of the following model
  OdUInt32             m_nIndNextModel;

  // negative handseed
  OdInt64    m_nNEGATIVEHANDSEED;

  // this flag means that we should reject actions in reactors for the device.
  // it can happen mostly in to cases. 1. During database writing 2. During changing xData for the model
  bool m_bRejectReactors;

  // pointer to the linker object which contains the pointer to this object
  OdTvDataLink*                         m_pLink;
  
  //map for connection of the predefined linetype with its database ID
  std::map <OdTvDbObjectId, OdTvLinetype::Predefined> m_predefLinetypeMap;

  // Array of object classes
  OdRxClassArray m_objectClasses;

  // Database initial size (memory)
  OdUInt64 m_initialSize;

  //Partial import mode flag
  bool m_bIsPartialImportMode;
  OdStreamBufPtr m_streamBuff;

  //VSF compression options
  OdTvVSFExportOptions m_exportOptions;

  std::map<OdUInt64, OdTvEntityId> m_storedOriginalEntitiesMap;

protected:
  virtual OdUInt64 vsfxWriteServiceObjects( OdTvCoreFilerWrapperPtr pFiler, OdTvVSFXContext* ctx );
  void vsfxWriteObjectHelper( OdTvDbObjectId objectId, OdTvCoreFilerWrapperPtr pFiler, OdTvVSFXContext* ctx );
public:
  virtual void disablePartialViewingModule();
  virtual bool forcePartialViewingRequest( OdGsDevice* pDevice, const std::set< OdTvDbObjectId >& detectedInserts );
};

typedef OdTvSmartPtrInternal<OdTvDatabaseImpl> OdTvDatabaseImplPtr;


/** \details
    This is an wrapper of the interface class for OdTvDatabase object.

    \remarks
    The purpose of this class is to coinnect the internal database object with an interface object
*/
  
class OdTvDatabaseWrapper : public OdTvDatabase
{
  ODTV_DEFINE_WRAPPERS_MEMBERS_DECL(OdTvDatabase)

  friend class OdTvFactoryImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Creates the model object and returns the appropriate ID

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvModelId createModel(const OdString& name, OdTvModel::Type type = OdTvModel::kMain, bool bNeedSaveInFile = true, OdTvResult* rc = NULL);

  /** \details
  Remove model object with the given ID
  */
  virtual OdTvResult removeModel(const OdTvModelId& id);

  /** \details
  Remove all models
  */
  virtual OdTvResult clearModels();

  /** \details
  Find a model by name, and return OdTvModelId
  */
  virtual OdTvModelId findModel(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a block object and returns the appropriate ID

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvBlockId createBlock(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove block object with the given ID
  */
  virtual OdTvResult removeBlock(const OdTvBlockId& id);

  /** \details
  Remove all blocks
  */
  virtual OdTvResult clearBlocks();

  /** \details
  Find a block by name, and return OdTvBlockId
  */
  virtual OdTvBlockId findBlock(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a device object and returns the appropriate ID
  */
  virtual OdTvGsDeviceId createDevice(const OdString& name, OSWindowHandle wnd_handle, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL);

  /** \details
  Creates a device object and returns the appropriate ID
  */
  virtual OdTvGsDeviceId createDeviceWithContext(const OdString& name, OSWindowGLContext wnd_context, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL);

  /** \details
  Creates a "non-setup" device object and returns the appropriate ID
  */
  virtual OdTvGsDeviceId createDevice(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a bitmap device object and returns the appropriate ID
  */
  virtual OdTvGsDeviceId createBitmapDevice(const OdString& name, long x, long y, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL);

  /** \details
  Creates a "non-setup" bitmap device object and returns the appropriate ID
  */
  virtual OdTvGsDeviceId createBitmapDevice(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a device object with the given ID
  */
  virtual OdTvResult removeDevice(const OdTvGsDeviceId& id);

  /** \details
  Remove all devices
  */
  virtual OdTvResult clearDevices();

  /** \details
  Returns the active OdTvGsDevice object associated with this database object.
  If there is no active devices - this method returns first device
  */
  virtual OdTvGsDeviceId getActiveDevice(OdTvResult* rc = NULL);

  /** \details
  Returns the version of the VSF file from which this database was read.
  */
  virtual OdTvVSFVersion getVSFVersion(OdTvResult* rc = NULL) const;

  /** \details
  Sets the compression options which will be used during the export of the Visualize database to the VSF file or stream.
  */
  virtual OdTvResult setVSFExportOptions(const OdTvVSFExportOptions& options);

  /** \details
  Returns the compression options which is used during the export of the Visualize database to the VSF file or stream.
  */
  virtual OdTvVSFExportOptions getVSFExportOptions(OdTvResult* rc = NULL);

  /** \details
  Writes the contents of this database object to the specified file

  Throws:
  OdTvError if the write is unsuccessful.
  */
  virtual OdTvResult writeFile(const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL);

  /** \details
  Add the Common Data Access (CDA) tree to the database.
  */
  virtual OdTvCDATreeStorageId addCDATreeStorage(const OdString& name, OdTvCDATreePtr pTree, OdTvResult* rc = NULL);

  /*PARTIAL SUPPORT*/
  virtual OdTvResult beginPartialImport( const OdString& filename );
  virtual OdTvResult writeObjectPartial( OdTvEntityId id );
  virtual OdTvResult endPartialImport();

  virtual OdTvResult disableInternalNotifications();

  /** \details
  Writes the contents of this database object to the specified stream buffer

  Throws:
  OdTvError if the write is unsuccessful.
  */
  virtual OdTvResult write(OdStreamBuf *buff, const OdTvVSFExportOptions* pOptions = NULL);

  /** \details
  Export database into the specified file.
  \param pParams  [in] A pointer to an object that contains the <link OdTvBaseExportParams, export parameters>.
  \returns Returns parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \remarks
  The method throws the <link OdTvError, OdTvError> exception if the import operation is not successful.
  */
  virtual OdTvResult exportTo(const OdTvBaseExportParams* pParams);

  /** \details
  Returns the pointer to the models iterator object
  */
  virtual OdTvModelsIteratorPtr getModelsIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the blocks iterator object
  */
 virtual  OdTvBlocksIteratorPtr getBlocksIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the linetypes iterator object
  */
  virtual OdTvLinetypesIteratorPtr getLinetypesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the layers iterator object
  */
  virtual OdTvLayersIteratorPtr getLayersIterator(OdTvResult* rc = NULL);

	/** \details
	Returns the pointer to the texttypes iterator object
	*/
	virtual OdTvTextStylesIteratorPtr getTextStylesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the raster image iterator object
  */
  virtual OdTvRasterImagesIteratorPtr getRasterImagesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the materials iterator object
  */
  virtual OdTvMaterialsIteratorPtr getMaterialsIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the devices iterator object
  */
  virtual OdTvDevicesIteratorPtr getDevicesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the visual styles iterator object
  */
  virtual OdTvVisualStylesIteratorPtr getVisualStylesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns a smart pointer to an iterator object to get sequential access to view background objects in the database.
  */
  virtual OdTvGsViewBackgroundsIteratorPtr getBackgroundsIterator(OdTvResult* rc = NULL);

  /** \details
  Returns a smart pointer to an iterator object to get sequential access to CDA tree storages objects in the database.
  */
  virtual OdTvCDATreeStoragesIteratorPtr getCDATreeStoragesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the highlight styles iterator object
  */
  virtual OdTvHighlightStylesIteratorPtr getHighlightStylesIterator(OdTvResult* rc = NULL);

  /** \details
  Returns the name of the file associated with the internal database object.
  */
  virtual OdString getFilename(OdTvResult* rc = NULL) const;

  /** \details
  Returns the pointer to the internal database
  */
  virtual void* getInternalDatabase(OdTvResult* rc = NULL) const;

  //**************************************************************************************
  // Group of the methods for managing different properties
  //**************************************************************************************

  /** \details
  Creates a linetype object and returns the appropriate ID

  \param name     [in]  Linetype name as a String value up to 255 characters long.
  \param elements [in]  Array of line type pattern elements
  \param rc       [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvLinetypeId createLinetype(const OdString& name, const OdTvLinetypeElementArray& elements, OdTvResult* rc = NULL);

  /** \details
  Creates a linetype object and returns the appropriate ID

  \param name       [in]  Linetype name as a String value up to 255 characters long.
  \param nElements  [in]  Number of linetype pattern elements
  \param elements   [in]  Array of linetype pattern elements
  \param rc         [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvLinetypeId createLinetype(const OdString& name, OdInt32 nElements, const OdTvLinetypeElementPtr* elements, OdTvResult* rc = NULL);

  /** \details
  Remove a linetype object with the given ID
  */
  virtual OdTvResult removeLinetype(const OdTvLinetypeId& id);

  /** \details
  Remove all linetypes
  */
  virtual OdTvResult clearLinetypes();

  /** \details
  Find a linetype by name, and return OdTvLinetypeId
  */
  virtual OdTvLinetypeId findLinetype(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a layer object and returns the appropriate ID

  \param name         [in]  Layer name as a String value up to 255 characters long.
  \param color        [in]  Layer color as a OdTvColorDef.
  \param lineWeight   [in]  Layer line weight as a OdUInt8 value.
  \param linetypeId   [in]  Layer linetype as OdTvLinetypeId id of linetype.
  \param description  [in]  Layer description as as a String value up to 255 characters long.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvLayerId createLayer(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a layer object with the given ID
  */
  virtual OdTvResult removeLayer(const OdTvLayerId& id);

  /** \details
  Remove all layers
  */
  virtual OdTvResult clearLayers();

  /** \details
  Find a layer by name, and return OdTvLayerId
  */
  virtual OdTvLayerId findLayer(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a text style object and returns the appropriate ID

  \param name     [in]  Text style name as a String value up to 255 characters long.
  \param rc       [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  
  Just created text style will be use the built-in font.
  */
  virtual OdTvTextStyleId createTextStyle(const OdString& name, OdTvResult* rc = NULL);


  /** \details
  Remove a linetype object with the given ID
  */
  virtual OdTvResult removeTextStyle(const OdTvTextStyleId& id);

  /** \details
  Remove all linetypes
  */
  virtual OdTvResult clearTextStyles();

  /** \details
  Find a text style by name, and return OdTvTextStyleId
  */
  virtual OdTvTextStyleId findTextStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a material object and returns the appropriate ID

  \param name         [in]  Material name as a String value up to 255 characters long.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).

  Also there are forbidden name: "Global", "ByBlock", "ByLayer"
  */
  virtual OdTvMaterialId createMaterial(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a material object with the given ID
  */
  virtual OdTvResult removeMaterial(const OdTvMaterialId& id);

  /** \details
  Remove all materials
  */
  virtual OdTvResult clearMaterials();

  /** \details
  Find a material by name, and return OdTvMaterialId
  */
  virtual OdTvMaterialId findMaterial(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Find a material by name or, if it fails, uses comparator.
  */
  OdTvMaterialId findMaterial( const OdTvMaterialComparator* pCmp, const OdString& name = OdString::kEmpty, OdTvResult* rc = NULL );

  /** \details
  Creates a raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param pathName     [in]  The name of the source file containing the raster image
  \param bLoad        [in]  Flag indicating whether it is need immediately loading of the image
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, const OdString& pathName, bool bLoad = false, OdTvResult* rc = NULL);

  /** \details
  Creates a raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, OdTvRasterImage::Format format, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4, OdTvResult* rc = NULL);

  /** \details
  Creates a palette based binary raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, OdTvRasterImage::Format paletteformat, OdUInt32 paletteSize, OdUInt8* paletteData,
                                              OdTvRasterImage::BitPerIndex bpi, OdUInt32 width, OdUInt32 height, const OdUInt8* data,
                                              OdUInt32 iAlignment = 4, OdTvResult* rc = NULL);

  /** \details
  Creates a monochrome raster image object and returns the appropriate ID

  \param name         [in]  Raster image name as a String value up to 255 characters long.
  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, OdUInt32 width, OdUInt32 height, const OdUInt8* data,
                                              bool bInverted = false, OdUInt32 iAlignment = 4, OdTvResult* rc = NULL);

  /** \details
  Remove a raster image object with the given ID
  */
  virtual OdTvResult removeRasterImage(const OdTvRasterImageId& id);

  /** \details
  Remove all raster images
  */
  virtual OdTvResult clearRasterImages();

  /** \details
  Find a raster image by name, and return OdTvRasterImageId
  */
  virtual OdTvRasterImageId findRasterImage(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a visual style object as a copy of the given visual style and returns the appropriate ID

  \param name         [in]  Visual style name as a String value up to 2049 characters long.
  \param vsId         [in]  Visual style to copy from.
  \param rc           [out] The code of the success or an error.
  */
  virtual OdTvVisualStyleId createVisualStyle(const OdString& name, const OdTvVisualStyleId& vsId, OdTvResult* rc = NULL);

  /** \details
  Creates a visual style object as a empty visual style and returns the appropriate ID

  \param name         [in]  Visual style name as a String value up to 2049 characters long.
  \param rc           [out] The code of the success or an error.
  */
  virtual OdTvVisualStyleId createVisualStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Remove a visual style object with the given ID
  */
  virtual OdTvResult removeVisualStyle(const OdTvVisualStyleId& id);

  /** \details
  Remove all visual styles
  */
  virtual OdTvResult clearVisualStyles();

  /** \details
  Find a visual style by name, and return OdTvVisualStyleId
  */
  virtual OdTvVisualStyleId findVisualStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a view background object and returns the appropriate ID.

  \param name   [in]  A view background name as a String value up to 2049 characters long.
  \param gbType [in]  A view background type.
  \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvGsViewBackgroundId createBackground(const OdString& name, OdTvGsViewBackgroundId::BackgroundTypes bgType, OdTvResult* rc = NULL);


  /** \details
  Removes a view background object with the specified identifier from the database.
  \param id [in] An identifier of the view background object that should be deleted.
  */
  virtual OdTvResult removeBackground(const OdTvGsViewBackgroundId& id);

  /** \details
  Removes all view backgrounds objects from the database.
  */
  virtual OdTvResult clearBackgrounds();

  /** \details
  Searches for a view background object with a specified name in the database.
  \param name [in] A name of the view background object to be found.
  \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
  */
  virtual OdTvGsViewBackgroundId findBackground(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a highlight style object as a empty highlight style and returns the appropriate ID

  \param name         [in]  highlight style name as a String value up to 2049 characters long.
  \param rc           [out] The code of the success or an error.
  */
  virtual OdTvHighlightStyleId createHighlightStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Creates a highlight style object as a copy of the given highlight style object and returns the appropriate ID.
  */
  virtual OdTvHighlightStyleId createHighlightStyle(const OdString& name, const OdTvHighlightStyleId& highlightStyleId, OdTvResult* rc = NULL);

  /** \details
  Remove a highlight style object with the given ID
  */
  virtual OdTvResult removeHighlightStyle(const OdTvHighlightStyleId& id);

  /** \details
  Remove all highlight styles
  */
  virtual OdTvResult clearHighlightStyles();

  /** \details
  Find a highlight style by name, and return OdTvHighlightStyleId
  */
  virtual OdTvHighlightStyleId findHighlightStyle(const OdString& name, OdTvResult* rc = NULL);

  /** \details
  Registers the name of the app and returns the appropriate ID
  */
  virtual OdTvRegAppId registerAppName(const OdString& appName, bool& bAlreadyExist, OdTvResult* rc = NULL);

  /** \details
  Get object type by handle
  */
  virtual OdTv::HandledObjectType getObjectTypeByHandle(const OdUInt64 h, OdTvResult* rc = NULL);

  /** \details
  Append new data from file to this database.
  */
  virtual OdTvModelId append(const OdTvBaseImportParams* pParams, OdTvResult* rc = NULL);

  /** \details
  Add or update partial view indexes for models of the database
  */
  virtual OdTvResult addPartialViewIndexes(bool bUpdateExisting = true);

  /** \details
  Checks that the database has partial indexes.
  */
  virtual bool hasPartialViewIndexes(bool bCheckExtents = false, OdTvResult* rc = NULL);

  /** \details
  Retrieves the statistics for the database.
  */
  virtual OdTvDatabaseStatistic getStatistic(OdTvResult* rc = NULL);

  /** \details
  Returns the OdTvEntityId that matches the original database handle.
  */
  virtual OdTvEntityId findEntity(OdUInt64 originalDatabaseHandle, OdTvResult* rc = NULL);

  /** \details
  Sets a host app progress meter which will be used for direction the info about import process to the host app
  */
  OdTvResult setProgressMeter(OdTvHostAppProgressMeter* pProgressMeter);

  /** \details
  Set given code page to database.
  */
  virtual OdTvResult setCodePage(OdCodePageId cp);

  virtual OdTvResult writeVSFX( const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL );
  virtual OdTvResult writeVSFX( OdStreamBufPtr pStream, const OdTvVSFExportOptions* pOptions = NULL );
  virtual OdTvAnimationActionId createAnimationAction( const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL );
  virtual OdTvResult removeAnimationAction( const OdTvAnimationActionId& id );
  virtual OdTvResult clearAnimationActions();
  virtual OdTvAnimationActionsIteratorPtr getAnimationActionsIterator( OdTvResult* rc = NULL );

  virtual OdTvAnimationContainerId createAnimationContainer( const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL );
  virtual OdTvResult removeAnimationContainer( const OdTvAnimationContainerId& id );
  virtual OdTvResult clearAnimationContainers();
  virtual OdTvAnimationContainersIteratorPtr getAnimationContainersIterator( OdTvResult* rc = NULL );

  /** \details
  Sets a new path to a custom folder that contains image files used as textures, backrounds or as separate objects.
  */
  virtual OdTvResult setCustomImageFolder(const OdString& strFolderPath);

  /** \details
  Retrieves the current path to the custom folder that contains image files used as textures, backrounds or as separate objects.
  */
  virtual OdString getCustomImageFolder(OdTvResult* rc = NULL) const;

  /** \details
  Returns the units used for drawing the contents of this database.
  */
  virtual OdTv::Units getUnits(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
};

#include "TD_PackPop.h"

#endif // _ODTV_DATABASEIMPL_H_INCLUDED_


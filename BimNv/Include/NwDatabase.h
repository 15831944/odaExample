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

#ifndef __TNW_DATABASE_H__
#define __TNW_DATABASE_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#define STL_USING_MAP
#include "OdaSTL.h"
#include "NwModelUnits.h"
#include "NwFormatVersion.h"

class OdNwHostAppServices;
class OdNwModel;
class OdNwCommonLight;
class OdGeMatrix3d;
class OdNwUnitsFormatter;
class OdNwGridSystemElement;
class OdNwSelectionSetsElement;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwModel
  object pointers.
*/
typedef OdSmartPtr<OdNwModel> OdNwModelPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwCommonLight object pointers.
*/
typedef OdSmartPtr<OdNwCommonLight> OdNwCommonLightPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGridSystemElement object pointers.
*/
typedef OdSmartPtr<OdNwGridSystemElement> OdNwGridSystemElementPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSelectionSetsElement object pointers.
*/
typedef OdSmartPtr<OdNwSelectionSetsElement> OdNwSelectionSetsElementPtr;

/** \details
  This class implements the interface for interaction with a BimNv SDK database.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwDatabase : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwDatabase);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwDatabase class.
  */
  OdNwDatabase();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwDatabase();

  /** \details
    Returns the OdNwHostAppServices object associated with this database object.

    \returns OdNwHostAppServices object associated with this database object.
  */
  virtual OdNwHostAppServices* appServices() const;

  /** \details
    Reads the contents of the specified StreamBuf object or a file into this
    database object.

    \param pStreamBuf  [in]  Pointer to the StreamBuf object from which the data is read.
    \param partialLoad [in]  Controls the partial loading of .nwd files.
    \param password    [in]  Password for the file.

    \remarks
    Throws:
    OdError if the read operation is unsuccessful.
  */
  virtual void readFile(OdStreamBuf* pStreamBuf,
                        bool partialLoad = true,
                        const OdString& password = OdString::kEmpty);

  /** \details
    Reads the contents of the specified file into this database object.

    \param fileName    [in]  Name of the file from which the data is read.
    \param partialLoad [in]  Controls the partial loading of .nwd files.
    \param password    [in]  Password for the file.

    \remarks
    Throws:
    OdError if the read oeration is unsuccessful.
  */
  virtual void readFile(const OdString& fileName,
                        bool partialLoad =  true,
                        const OdString& password = OdString::kEmpty);

  /** \details
    Writes this database object to the specific file.
    
    \param fileName [in]  Name of the file to be written.

    \remarks
    Throws:
    OdError if the write operation is unsuccessful.
  */
  virtual void writeFile(const OdString& fileName);

  /** \details
    Writes this database object to the specific stream.
    
    \param pStreamBuf [in]  Pointer to the StreamBuf object.

    \remarks
    Throws:
    OdError if the write is unsuccessful.
  */
  virtual void writeFile(OdStreamBuf* pStreamBuf);

  /** \details
    Returns the name of the file associated with this database object.

    \returns Name of the file associated with this database object.
  */
  virtual OdString getFilename() const;

public:

  /** \details
    Sets the path to a folder with textures.

    \param path [in] Directory's path.

    \remarks 
    The method is deprecated. Use OdNwHostAppServices::setTextureDirectoryPath(const OdString& path, bool rename_path) instead.
  */
  void setTextureFolder(const OdString& path);

public:
  /** \details
    Adds an object to the database.

    \param pObj   [in]  Pointer to the OdNwObject to add to the database.
    \param handle [in]  OdDbHandle object to use when adding.

    \returns OdNwObjectId of the object that is added to the database.
    \remarks 
    The method is deprecated.
  */
  OdNwObjectId addObject(OdNwObjectPtr pObj,
                          const OdDbHandle& handle = OdDbHandle());

  /** \details
    Returns the database's ID of an object by its handle.

    \param handle           [in]  OdDbHandle object with the object's handle.
    \param createIfNotFound [in]  Boolean flag for whether to create the object if it is not found.

    \returns OdNwObjectId of the object.
  */
  OdNwObjectId getObjectId(const OdDbHandle& handle,
                            bool createIfNotFound = false);

public:

  /** \details
    Returns an object ID of the current viewpoint of the database.

    \returns Object ID of the OdNwViewpoint object with the current viewpoint of
    the database. If the database doesn't have a current viewpoint, the returned
    empty object ID.

    \remarks
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getCurrentViewId() const;

  /** \details
    Returns an object ID of the clipping planes of current view of the database.

    \returns Object ID of the OdNwClipPlaneSet object with the clipping planes
    of the current view of the database. If the database doesn't have a current
    view, the method returnes an empty object ID.

    \remarks
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getCurrrentViewClippingPlanesId() const;

  /** \details
    Gets an array of object IDs of the database's saved view elements (with
    viewpoints, animation, etc.).

    \param aSavedViewsElementIds [out] OdArray object of object IDs of the saved view elements.

    \returns eOk if the array of object IDs of the saved view elements is
    retrieved successfully, or an appropriate error code otherwise.

    \remarks
    This method is not applicable for composite databases (.nwf files).
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdResult getSavedViewsElements(OdNwObjectIdArray& aSavedViewsElementIds) const;

  /** \details
    Returns an object ID of the background element.

    \returns Object ID of an OdNwBackgroundElement object with background colors
    of the database. If the database doesn't have a background element, the
    method returnes an empty object ID.

    \remarks
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getBackgroundElementId() const;

  /** \details
    Returns an object ID of the clash element.

    \returns Object ID of an OdNwClashElement object with the saved clash
    element of the database. If the database doesn't have a clash element, the
    method returnes an empty object ID.

    \remarks
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getClashElementId() const;

  /** \details
    Returns an array with object IDs of models.

    \param arrModels [out] Array with object IDs of models.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    Use this method only if the database is a composite model.
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdResult getModels(OdNwObjectIdArray& arrModels) const;

  /** \details
    Returns an object ID of the root model item.

    \returns Object ID of an OdNwModelItem object with the root model item of
    the database. If the database doesn't have a root model item, the method
    returnes an empty object ID.

    \remarks
    Use this method only if the database is not a composite model.
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getModelItemRootId() const;

  /** \details
    Returns a transformation matrix of a model.

    \returns OdGeMatrix3d object with the transformation matrix of a model.

    \remarks
    Use this method only if the database is not a composite model.
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdGeMatrix3d getModelTransform() const;

  /** \details
    Returns a boolean value of a composite database's status.

    \returns True if the database contains more than one object, or returns
    false if not.
  */
  bool isComposite() const;

  /** \details
    Returns the units in which dimensions of this model are defined.

    \remarks
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
    getUnits() Returns one of the following:

    <table>
    Name                              Value   Description
    NwModelUnits::UNITS_METERS        0x00    SI meter. Length of the path travelled by light in a vacuum in 1 299,792,458th of second.
    NwModelUnits::UNITS_CENTIMETERS   0x01    1/100th of an SI meter.
    NwModelUnits::UNITS_MILLIMETERS   0x02    1/1000th of an SI meter.
    NwModelUnits::UNITS_FEET          0x03    1/3rd of a yard.
    NwModelUnits::UNITS_INCHES        0x04    1/12th of a foot, 2.54 SI centimeters.
    NwModelUnits::UNITS_YARDS         0x05    Imperial yard, 0.9144 SI meters.
    NwModelUnits::UNITS_KILOMETERS    0x06    1000 SI meters.
    NwModelUnits::UNITS_MILES         0x07    1760 yards.
    NwModelUnits::UNITS_MICROMETERS   0x08    1/1,000,000th of an SI meter, micron.
    NwModelUnits::UNITS_MILS          0x09    1/1,000th of an inch.
    NwModelUnits::UNITS_MICROINCHES   0x0A    1/1,000,000th of an inch.
    </table>
  */
  NwModelUnits::Enum getUnits() const;

  /** \details
    Returns an array with object IDs of lights.

    \param arrLights [out] Array with object IDs of lights.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.

    \remarks
    This method is not applicable for composite databases (.nwf files).
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdResult getLightElements(OdNwObjectIdArray& arrLights) const;
  
  /** \details
    Returns a smart pointer to the grid system element.

    \returns Smart pointer to an OdNwGridSystemElement object.

    \remarks
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwGridSystemElementPtr getGridSystemElement() const;

  /** \details
    Returns a smart pointer to the selection sets element.

    \returns Smart pointer to an OdNwSelectionSetsElement object.

    \remarks
    This method is not applicable for composite databases (.nwf files).
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
    The method is deprecated. Use getSelectionSetsElementId() instead.
  */
  OdNwSelectionSetsElementPtr getSelectionSetsElement() const;

  /** \details
    Returns an object id with selection sets element.

    \returns OdNwObjectId with an OdNwSelectionSetsElement object.

    \remarks
    This method is not applicable for composite databases (.nwf files).
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getSelectionSetsElementId() const;

  /** \details
    Returns an object ID of the current sheet element.

    \returns Object ID of an OdNwSheetInfo object with the current sheet element
    of the database.
  */
  OdNwObjectId getActiveSheetId() const;

  /** \details
    Returns an array with object IDs of sheets of the database.

    \param aSheets [out] Array with object IDs of sheets.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getSheets(OdNwObjectIdArray& aSheets) const;

  /** \details
    Returns an object ID of the file info object.

    \returns Object ID of the OdNwFileInfo object of the database.
  */
  OdNwObjectId getFileInfo() const;

  /** \details
    Returns the version of the original software the file was created with.

    \returns NwFormatVersion::Enum value of the original file format version.
    If the file wasn't loaded the method returns the latest possible version.
  */
  NwFormatVersion::Enum getOriginalFormatVersion();
  
  /** \details
    Returns an object ID of the saved animation element.

    \returns OdNwObjectId with an OdNwSavedAnimElement object.

    \remarks
    This method is not applicable for composite databases (.nwf files).
    The method returns a value that corresponds to the sheet, selected as active
    for the database.
  */
  OdNwObjectId getSavedAnimationElementId() const;

public:
  /** \details
    Adds a new model to the model collection of the database.

    \param pModel [in] Pointer to the OdNwModel object to add to the collection.

    \returns eOk if the model is added successfully, or an appropriate error
    code otherwise.

    \remarks
    The method is deprecated. Use OdNwObjectId addModel(const OdString& sourcePath, OdResult* pResCode = NULL) instead.
    This method is applicable only for composite databases (.nwf files).
    This method performs an action for the database state with the sheet
    selected as active for the database.
  */
  OdResult addModel(OdNwModelPtr pModel);

  /** \details
    Adds a new model to the model collection of the database by source path to it.

    \param sourcePath [in] String with the path to the source model to be added to the collection.
    \param pResCode [out] Receives eOk if the model is added successfully, or an appropriate error code otherwise.

    \returns ID of the new OdNwModel object from database if successful, or null pointer otherwise.

    \remarks
    This method is applicable only for composite databases (.nwf files).
    This method performs an action for the database state with the sheet
    selected as active for the database.
  */
  OdNwObjectId addModel(const OdString& sourcePath, OdResult* pResCode = NULL);

  /** \details
    Sets a new active sheet and switches the database to the state,
    corresponding to the new sheet.

    \param sheetId [in] Sheet ID.

    \returns eOk if the database is set to the new sheet state successfully,
    or an appropriate error code otherwise.

    \remarks
    The method changes the current state of the database to the selected sheet
    (if the selected sheet has not yet been read, partial loading is performed).
  */
  OdResult setActiveSheet(const OdString& sheetId);

  /** \details
    Retrieves the unit formatter for the database as a constant object.

    \returns Smart pointer to the OdNwUnitsFormatter object that represents the
    currently used unit formatter.
  */
  const OdNwUnitsFormatter& formatter() const;

  /** \details
    Retrieves the unit formatter for the database.

    \returns Smart pointer to the OdNwUnitsFormatter object that represents the
    currently used unit formatter.
  */
  OdNwUnitsFormatter& formatter();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwDatabase object pointers.
*/
typedef OdSmartPtr<OdNwDatabase> OdNwDatabasePtr;

#endif //__TNW_DATABASE_H__

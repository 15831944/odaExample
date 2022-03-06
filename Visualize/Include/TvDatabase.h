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

#ifndef _ODTV_DATABASE_H_INCLUDED_
#define _ODTV_DATABASE_H_INCLUDED_

#include "Tv.h"
#include "TvModel.h"
#include "TvBlock.h"
#include "TvLinetype.h"
#include "TvLayer.h"
#include "TvRasterImage.h"
#include "TvVisualStyle.h"
#include "TvGsViewBackground.h"
#include "TvIObject.h"
#include "TvGsDevice.h"
#include "TvExport.h"
#include "TvStatistics.h"
#include "TvCommonDataAccessTree.h"
#include "TvAnimation.h"

class OdTvBaseImportParams;

/** \details
  Class for storing compression parameters.
*/
struct ODTV_EXPORT OdTvVSFExportOptions
{
  /** \details
    Defines compression type used for the vertices in the different geometry data like nurbs, polylines, shells etc.
  */
  enum Compression
  {
    /** Compression is disabled. */
    kNoCompression,
    /** Use floats instead doubles. */
    kFloat,
    /** Use 4 bytes integers instead doubles. */
    kInt32,
    /** Use 2 bytes integers instead doubles. */
    kInt16,
  };

  /** \details
    Defines compression type for the normals.
  */
  enum NormalsCompression
  {
    /** Compression is disabled. */
    kDisabledCompression,
    /** Use 2 floats instead of 3 doubles. */
    kTwoFloats,
    /** Use 2 integers (4 bytes each) instead of 3 doubles. */
    kTwoInt32,
    /** Use one 2 bytes integer instead of 3 doubles. */
    kOneInt16,
  };

  /** \details
    Default constructor for the OdTvVSFExportOptions class. Creates object
    that specifies that no compression is used for vertices and no compression is used for normals.
  */
  OdTvVSFExportOptions()
    :compression(kNoCompression), normalsCompression(kDisabledCompression)
  {}

  /** \details
    Constructor for the OdTvVSFExportOptions class. Creates object with specified compression parameters.
    
    \param compression          [in] Compression options for vertices.
    \param normalsCompression   [in] Compression options for normals.
  */
  OdTvVSFExportOptions(Compression compression, NormalsCompression normalsCompression)
    :compression(compression), normalsCompression(normalsCompression)
  {}

  /** Represents compression for vertices */
  Compression compression;
  /** Represents compression for normal vectors */
  NormalsCompression normalsCompression;
};

/** \details
    Struct for storing VSFX read parameters.
    
    \sa
    <link tv_working_with_features_streaming, Work with Visualize Streaming>
*/
struct ODTV_EXPORT OdTvVSFXReadOptions
{
  /** \details
    Defines progressive mesh loading mode.
  */
  enum ProgressiveMeshMode
  {
    /** Normal mode - all data loaded. */
    kNormalMode,
    /** Partial mode - LOD info kept in the stream. */
    kPartialMode,
    /** Partial mode - LOD info kept in the stream, but all info is being loaded while switching LOD. */
    kFastPartialMode
  };

  /** \details
    Default constructor for the OdTvVSFXReadOptions struct. Creates object
    that specifies that progressive meshes will be loaded in normal mode.
  */
  OdTvVSFXReadOptions()
    :progressiveMeshMode( kNormalMode )
  {}

  /** \details
    Constructor for the OdTvVSFXReadOptions struct. Creates object with specified parameters.
    
    \param pmMode   [in] Progressive mesh loading mode.
  */
  OdTvVSFXReadOptions( ProgressiveMeshMode pmMode )
    :progressiveMeshMode( pmMode )
  {}

  /** Represents progressive mesh loading mode. */
  ProgressiveMeshMode progressiveMeshMode;
};

/** \details
  An abstract class that implements the interface for interaction with a Visualize SDK database.
  
  \sa
  <link tv_working_with_base_classes_db, Work with Visualize Databases>
*/
class ODTV_EXPORT OdTvDatabase : public OdTvIObjectWithXdata
{
public:

  /** \details
    Creates a new model for the database.
    
    \param name             [in] A model name.
    \param type             [in] A model type.
    \param bNeedSaveInFile  [in] A flag that indicates whether the model should be saved in a file.
    \param rc               [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the created model. 
    \remarks
    If the rc parameter value is not NULL and the model is created successfully,
    the rc parameter accepts the tvOk value; otherwise it contains an error code.
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there are three forbidden names, "*Model_Space", "*Paper_Space", and "*Paper_Space0", which can not be used as model names.
    \sa
    <link tv_working_with_base_classes_model, Work with Models>
  */
  virtual OdTvModelId createModel(const OdString& name, OdTvModel::Type type = OdTvModel::kMain, bool bNeedSaveInFile = true, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes the model with specified identifier from the database.
    
    \param id [in] An identifier of the model to be removed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks 
    If the model is successfully removed from the database, the method returns the tvOk value; otherwise it returns an appropriate
    error code.
    \sa
    <link tv_working_with_base_classes_model, Work with Models>
  */
  virtual OdTvResult removeModel(const OdTvModelId& id) = 0;

  /** \details
    Removes all models from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks 
    If models are successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_base_classes_model, Work with Models>
  */
  virtual OdTvResult clearModels() = 0;

  /** \details
    Searches for a model with the specified name.
    
    \param name [in] A name of the model that should be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found model. If the model is not found, returns a null-value identifier.
    \remarks
    If the rc parameter is not NULL and the model with the specified name is found, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    Another way to understand whether the model was found is to call the isNull() method of the returned
    <link OdTvModelId, OdTvModelId> object. If this method returns false, the model was found.
  */
  virtual OdTvModelId findModel(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object for getting access to models that the database contains.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the model's iterator object. If the iterator can not be retrieved, the returned smart pointer is NULL.
    \remarks 
    If the rc parameter is not NULL and the method returns a valid smart pointer to a valid iterator; the rc parameter
    accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvModelsIteratorPtr getModelsIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new block in the database.
    
    \param name [in] A name of the new block.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the newly created block.
    \remarks
    If the new block is successfully created, the method isNull() of the returned identifier returns false.
    If the rc parameter is not null and the block is created, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    The new block name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there are three forbidden names, "*Model_Space", "*Paper_Space", "*Paper_Space0", which can not be used as a block name.
    \sa
    <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry (Inserts)>
  */
  virtual OdTvBlockId createBlock(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a block object with the specified identifier from the database.
    
    \param id [in] An identifier of the block that should be removed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the block is successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry (Inserts)>
  */
  virtual OdTvResult removeBlock(const OdTvBlockId& id) = 0;

  /** \details
    Removes all blocks from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If all blocks are removed from the database, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry (Inserts)>
  */
  virtual OdTvResult clearBlocks() = 0;

  /** \details
    Finds a block by name.
    
    \param name [in] A name of a block that should be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns the identifier of the found block. If the block is not found, the method returns a null-value identifier.
    \remarks 
    If the rc parameter is not null and the block is found, the rc parameter accepts the tvOk value; otherwise it contains
    an appropriate error code.
    Another way to understand whether the block was found is to call the isNull() method of the returned identifier.
    If it returns false, the block was found. Otherwise the isNull() method returns true.
  */
  virtual OdTvBlockId findBlock(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator for accessing database blocks.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator object.
    \remarks 
    If the rc parameter is not null and the iterator object is successfully returned, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    Another way to check whether a correct iterator was returned is to check the returned smart pointer for the NULL value.
    If it is not NULL, the iterator object returned by the method is correct.
  */
  virtual OdTvBlocksIteratorPtr getBlocksIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new linetype object in the database.
    
    \param name     [in]  A linetype name as a String value up to 255 characters long.
    \param elements [in]  An array of the linetype pattern elements.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created linetype object.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there are three forbidden names, "Continuous", "ByBlock", "ByLayer", which can not be used as the linetype name.
    If the rc parameter is not NULL and a new linetype object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of linetype creation by calling the isNull() method of the returned identifier.
    If this method returns false, the linetype was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeId createLinetype(const OdString& name, const OdTvLinetypeElementArray& elements, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new linetype object in the database.
  
    \param name       [in]  A linetype name as a String value up to 255 characters long.
    \param nElements  [in]  A number of linetype pattern elements.
    \param elements   [in]  A smart pointer that represents the array of the linetype pattern elements.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created linetype object.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there are three forbidden names, "Continuous", "ByBlock", "ByLayer", which can not be used as the linetype name.
    If the rc parameter is not NULL and a new linetype object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the linetype creation by calling the isNull() method of the returned identifier.
    If this method returns false, the linetype was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeId createLinetype(const OdString& name, OdInt32 nElements, const OdTvLinetypeElementPtr* elements, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a linetype object with the specified identifier from the database.
    
    \param id [in] An identifier of the linetype object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If the specified linetype object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult removeLinetype(const OdTvLinetypeId& id) = 0;

  /** \details
    Removes all linetype objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all linetype objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult clearLinetypes() = 0;

  /** \details
    Searches for a linetype object with a specified name in the database.
    
    \param name [in] A name of the linetype object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found linetype object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the linetype object was found; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeId findLinetype(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns an iterator object to get sequential access to linetype objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine), you can check whether the correct iterator is returned by the method
    by checking whether the returned smart pointer is not NULL.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypesIteratorPtr getLinetypesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new layer object in the database.
    
    \param name [in]  A new layer name represented with a string value up to 255 characters long.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created layer if the creation is successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there is a forbidden name, "0", which can not be used as the layer name.
    If the rc parameter is not NULL and the new layer object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of layer creation by calling the isNull() method of the returned identifier.
    If this method returns false, the layer was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerId createLayer(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a layer object with the specified identifier from the database.
    
    \param id [in] An identifier of the layer object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    If the specified layer object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult removeLayer(const OdTvLayerId& id) = 0;

  /** \details
    Removes all layer objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all layer objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult clearLayers() = 0;

  /** \details
    Searches for a layer object with a specified name in the database.
    
    \param name [in] A name of the layer object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found layer object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the layer object was found; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvLayerId findLayer(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to layer objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine), you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvLayersIteratorPtr getLayersIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new text style object in the database.
    
    \param name [in]  A new text style name represented with a string value up to 255 characters long.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created text style if the creation was successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there is a forbidden name, "Standard", which can not be used as the text style name.
    If the rc parameter is not NULL and a new text style is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of text style creation by calling the isNull() method of the returned identifier.
    If this method returns false, the text style was successfully created. Otherwise the isNull() method returns true.
    The created text style uses a built-in font unless you specify another font for it.
    \sa
    <link tv_working_with_attributes_text_style, Work with Text Styles>
  */
  virtual OdTvTextStyleId createTextStyle(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes the text style object with the specified identifier from the database.
    
    \param id [in] An identifier of the text style object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If the specified text style is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_text_style, Work with Text Styles>
  */
  virtual OdTvResult removeTextStyle(const OdTvTextStyleId& id) = 0;

  /** \details
    Removes all text styles from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all text styles are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_text_style, Work with Text Styles>
  */
  virtual OdTvResult clearTextStyles() = 0;

  /** \details
    Searches for a text style with a specified name in the database.
    
    \param name [in] A name of the text style object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found text style if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the text style object was found; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvTextStyleId findTextStyle(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to text styles in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine), you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvTextStylesIteratorPtr getTextStylesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new material object in the database.
    
    \param name [in]  A new material object name represented with a string value up to 255 characters long.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created material object if the creation was successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there are forbidden names, "Global", "ByBlock", "ByLayer", which can not be used as the material name.
    If the rc parameter is not NULL and the new material object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of material object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the material object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialId createMaterial(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes the material object with the specified identifier from the database.
    
    \param id [in] An identifier of the material object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If the specified material object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult removeMaterial(const OdTvMaterialId& id) = 0;

  /** \details
    Removes all material objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all material objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult clearMaterials() = 0;

  /** \details
    Searches for a material object with a specified name in the database.
    
    \param name [in] A name of the material object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found material object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the material object was found; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvMaterialId findMaterial(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Searches for a material object using comparator.
    
    \param pCmp [in] A Pointer to the material comparator.
    \param name [in] A name of the material object to be found (optional).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns 
    Returns an identifier of the found material object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the material object was found; otherwise it contains an
    appropriate error code.
    If the name parameter is specified, method tries to find material by the given name. If material is not found by its name, the method then uses comparator for this material: if it returns true, the found material is returned. Otherwise all other
    database materials are processed using the comparator.
  */
  virtual OdTvMaterialId findMaterial( const OdTvMaterialComparator* pCmp, const OdString& name = OdString::kEmpty, OdTvResult* rc = NULL ) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to material objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvMaterialsIteratorPtr getMaterialsIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new raster image object in the database.
    
    \param name     [in]  A new raster image name represented with a string value up to 255 characters long.
    \param pathName [in]  A path of the image source file.
    \param bLoad    [in]  A flag value that indicates whether the raster image should be immediately loaded.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created raster image object if the creation was successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the rc parameter is not NULL and a new raster image object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of raster image object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the raster image object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_raster_images.html#file-based">Working with Source File-Based Images</EXTLINK>
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, const OdString& pathName, bool bLoad = false, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new raster image object in the database.
    
    \param name       [in]  A new raster image name represented with a string value up to 255 characters long.
    \param format     [in]  A format of the raster image (describes how data in the data array is packed).
    \param width      [in]  A width of the raster image in pixels.
    \param height     [in]  A height of the raster image in pixels.
    \param data       [in]  A byte array that describes the color of each image pixel. This byte array is packed according to the image format.
    \param iAlignment [in]  A byte alignment value.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created raster image object if the creation was successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the rc parameter is not NULL and a new raster image object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of raster image object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the raster image object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_raster_images.html#binary">Working with Binary Images</EXTLINK>
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, OdTvRasterImage::Format format, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a palette-based binary raster image object and returns the appropriate ID.
  
    \param name          [in]  A new raster image name represented with a string value up to 255 characters long.
    \param paletteformat [in]  A description of how the color data in the palette data array is packed.
    \param paletteSize   [in]  The number of colors in the palette.
    \param paletteData   [in]  An array of bytes, packed according to the image format, that describes the color palette.
    \param bpi           [in]  A description of how indexes in the data array are packed.
    \param width         [in]  A width of the raster image in pixels.
    \param height        [in]  A height of the raster image in pixels.
    \param data          [in]  An array of bytes, packed according to the image format, that describes the index in the palette for each pixel in the image.
    \param iAlignment    [in]  A byte alignment value.
    \param rc            [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created raster image object if the creation was successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the rc parameter is not NULL and a new raster image object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of raster image object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the raster image object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_raster_images.html#palette-based">Working with Palette-Based Images</EXTLINK>
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, OdTvRasterImage::Format paletteformat, OdUInt32 paletteSize, OdUInt8* paletteData,
                                              OdTvRasterImage::BitPerIndex bpi, OdUInt32 width, OdUInt32 height, const OdUInt8* data,
                                              OdUInt32 iAlignment = 4, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a monochrome raster image object and returns the appropriate ID.
  
    \param name         [in]  A new raster image name represented with a string value up to 255 characters long.
    \param width        [in]  A width of the raster image in pixels.
    \param height       [in]  A height of the raster image in pixels.
    \param data         [in]  An array of bytes that describes the presence of the main color in each pixel of the image.
    \param bInverted    [in]  A background flag value. If the flag is equal to true, the background color is used as the main color.
    \param iAlignment   [in]  A byte alignment value.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created raster image object if the creation was successful or returns a null identifier.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the rc parameter is not NULL and a new raster image object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of raster image object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the raster image object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_raster_images.html#monochrome_images">Working with Monochrome Images</EXTLINK>
  */
  virtual OdTvRasterImageId createRasterImage(const OdString& name, OdUInt32 width, OdUInt32 height, const OdUInt8* data,
                                              bool bInverted = false, OdUInt32 iAlignment = 4, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes the raster image object with the specified identifier from the database.
    
    \param id [in] An identifier of the raster image object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If the specified raster image object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult removeRasterImage(const OdTvRasterImageId& id) = 0;

  /** \details
    Removes all raster image objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all raster image objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clearRasterImages() = 0;

  /** \details
    Searches for a raster image object with a specified name in the database.
    
    \param name [in] A name of the raster image object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found raster image object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the raster image object was found; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvRasterImageId findRasterImage(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to raster image objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvRasterImagesIteratorPtr getRasterImagesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new device object in the database.
    \param name              [in]  A device name represented with a string value up to 2049 characters long.
    \param wnd_handle        [in]  An operating system window handle.
    \param wndRect           [in]  A window rectangle associated with the device.
    \param device            [in]  A device type name (GLES2, OpenGL etc).
    \param strVectorizerName [in]  A path to the device module (only for when the device parameter is equal to the kCustom value).
    \param rc                [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created device object if the creation was successful or returns a null identifier.
    \remarks
    If the rc parameter is not NULL and a new device object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of device object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the device object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvGsDeviceId createDevice(const OdString& name, OSWindowHandle wnd_handle, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new device object in the database.
    
    \param name              [in]  A device name represented with a string value up to 2049 characters long.
    \param wnd_context       [in]  An operating system window GL context.
    \param wndRect           [in]  A window rectangle associated with the device.
    \param device            [in]  A device type name (GLES2, OpenGL etc).
    \param strVectorizerName [in]  A path to the device module (only for when the device parameter is equal to the kCustom value).
    \param rc                [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created device object if the creation was successful or returns a null identifier.
    \remarks
    If the rc parameter is not NULL and a new device object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of device object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the device object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvGsDeviceId createDeviceWithContext(const OdString& name, OSWindowGLContext wnd_context, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a new "non-setup" device object in the database. The created device does not have defined settings such as window handle, window rectangle, device type name, etc.
  
    \param name [in]  A device name represented with a string value up to 2049 characters long.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created device object if the creation was successful or returns a null identifier.
    \remarks
    The "non-setup" device can only create, add, insert, and erase views. All other methods called from such a device return an error.
    If the rc parameter is not NULL and a new device object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of device object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the device object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvGsDeviceId createDevice(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a bitmap device object and returns the appropriate ID.
  
    \param name               [in]  A device name represented with a string value up to 2049 characters long.
    \param x                  [in]  An output image X-dimension.
    \param y                  [in]  An output image Y-dimension.
    \param device             [in]  A device name (GLES2, OpenGL, etc.)
    \param strVectorizerName  [in]  A path to the device module (should be passed only if the value of the device parameter is equal to kCustom).
    \param rc                 [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created device object if the creation was successful or returns a null identifier.
    \remarks
    If the rc parameter is not NULL and a new device object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of device object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the device object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvGsDeviceId createBitmapDevice(const OdString& name, long x, long y, OdTvGsDevice::Name device, OdString* strVectorizerName = 0, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a "non-setup" bitmap device object and returns the appropriate ID.
    \param name               [in]  A device name represented with a string value up to 2049 characters long.
    \param rc                 [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
  
    \returns Returns an identifier of the created device object if the creation was successful or returns a null identifier.
    \remarks
    A "non-setup" bitmap device can only create, add, insert and erase views. All other methods for the device object return an error.
    If the rc parameter is not NULL and a new device object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of device object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the device object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvGsDeviceId createBitmapDevice(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a device object with the specified identifier from the database.
    
    \param id [in] An identifier of the device object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    If the specified device object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvResult removeDevice(const OdTvGsDeviceId& id) = 0;

  /** \details
    Removes all device objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all device objects is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_base_classes_device_overview, Overview of Visualize Graphics Devices>
  */
  virtual OdTvResult clearDevices() = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to device objects in the database.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvDevicesIteratorPtr getDevicesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a visual style object as a copy of the given visual style object and returns the appropriate ID.
  
    \param name [in]  A visual style name as a String value up to 2049 characters long.
    \param vsId [in]  A visual style object to copy from, represented with its identifier.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the created visual style object if the creation was successful or returns a null identifier.
    If the rc parameter is not NULL and a new visual style object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the visual style object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the visual style object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvVisualStyleId createVisualStyle(const OdString& name, const OdTvVisualStyleId& vsId, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a visual style object as a default visual style object and returns the appropriate ID.
  
    \param name [in]  A visual style name as a String value up to 2049 characters long.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the created visual style object if the creation was successful or returns a null identifier.
    If the rc parameter is not NULL and a new visual style object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the visual style object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the visual style object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvVisualStyleId createVisualStyle(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a visual style object with the specified identifier from the database.
    
    \param id [in] An identifier of the visual style object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    If the specified visual style object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvResult removeVisualStyle(const OdTvVisualStyleId& id) = 0;

  /** \details
    Removes all visual style objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all visual style objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvResult clearVisualStyles() = 0;

  /** \details
    Searches for a visual style object with a specified name in the database.
    
    \param name [in] A name of the visual style object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found visual style object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the visual style object was found; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvVisualStyleId findVisualStyle(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to visual style objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
    \sa
    <link tv_working_with_attributes_visual_styles_overview, Overview of Visual Styles>
  */
  virtual OdTvVisualStylesIteratorPtr getVisualStylesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a view background object and returns the appropriate ID.
  
    \param name   [in]  A view background name as a String value up to 2049 characters long.
    \param bgType [in]  A view background type.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the created view background object if the creation was successful or returns a null identifier.
    If the rc parameter is not NULL and a new view background object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the view background object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the view background object was successfully created. Otherwise the isNull() method returns true.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
  */
  virtual OdTvGsViewBackgroundId createBackground(const OdString& name, OdTvGsViewBackgroundId::BackgroundTypes bgType, OdTvResult* rc = NULL) = 0;


  /** \details
    Removes a view background object with the specified identifier from the database.
    
    \param id [in] An identifier of the view background object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    If the specified view background object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
  */
  virtual OdTvResult removeBackground(const OdTvGsViewBackgroundId& id) = 0;

  /** \details
    Removes all view backgrounds objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all view backgrounds objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
  */
  virtual OdTvResult clearBackgrounds() = 0;

  /** \details
    Searches for a view background object with a specified name in the database.
    
    \param name [in] A name of the view background object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found view background object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the view background object was found; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvGsViewBackgroundId findBackground(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to view background objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvGsViewBackgroundsIteratorPtr getBackgroundsIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a highlight style object as a default highlight style object and returns the appropriate ID.
  
    \param name [in]  A highlight style name as a String value up to 2049 characters long.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the created highlight style object if the creation was successful or returns a null identifier.
    If the rc parameter is not NULL and a new highlight style object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the highlight style object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the highlight style object was successfully created. Otherwise the isNull() method returns true.
  */
  virtual OdTvHighlightStyleId createHighlightStyle(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Creates a highlight style object as a copy of the given highlight style object and returns the appropriate ID.
  
    \param name             [in]  A highlight style name as a String value up to 2049 characters long.
    \param highlightStyleId [in]  A highlight style object to copy from, represented with its identifier.
    \param rc               [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.  
    \returns Returns an identifier of the created highlight style object if the creation was successful or returns a null identifier.
    If the rc parameter is not NULL and a new highlight style object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the highlight style object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the highlight style object was successfully created. Otherwise the isNull() method returns true.
  */
  virtual OdTvHighlightStyleId createHighlightStyle(const OdString& name, const OdTvHighlightStyleId& highlightStyleId, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a highlight style object with the specified identifier from the database.
    
    \param id [in] An identifier of the highlight style object that should be deleted.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    If the specified highlight style object is successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeHighlightStyle(const OdTvHighlightStyleId& id) = 0;

  /** \details
    Removes all highlight style objects from the database.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the remove operation.
    \remarks
    If all highlight style objects are successfully removed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clearHighlightStyles() = 0;

  /** \details
    Searches for a highlight style object with a specified name in the database.
    
    \param name [in] A name of the highlight style object to be found.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search.
    \returns Returns an identifier of the found highlight style object if it is found; otherwise it returns a null identifier.
    \remarks
    To check whether the returned identifier is null, call the isNull() method.
    In addition, if the rc parameter is not null, it accepts the tvOk value if the highlight style object was found; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvHighlightStyleId findHighlightStyle(const OdString& name, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to highlight style objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvHighlightStylesIteratorPtr getHighlightStylesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Returns the version of the VSF file from which this database was read. 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the version of the VSF file from which this database was read. 
    \remarks
    If the database was created not by reading the VSF file the function will return the current version which will be used for writing the VSF file.
    If the rc parameter is not null and the version was successfully returned, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvVSFVersion getVSFVersion(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the compression options which will be used during the export of the Visualize database to the VSF file or stream.
    
    \param options       [in] Structure which describes the compression options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    If the options was successfully set, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
    \remarks
    The method throws an <link OdTvError, OdTvError> exception if the write is unsuccessful.
  */
  virtual OdTvResult setVSFExportOptions(const OdTvVSFExportOptions& options) = 0;

  /** \details
    Returns the compression options which is used during the export of the Visualize database to the VSF file or stream.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns structure which describes the compression options.
    \remarks
    If the rc parameter is not null and the compression options structure was successfully returned, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTvVSFExportOptions getVSFExportOptions(OdTvResult* rc = NULL) = 0;

  /** \details
    This method is deprecated and will be removed soon, use writeVSFX() instead.
    It is possible to use analogue from OdTvDeprecated namespace, but this analogue eventually will be removed too.
    Writes the content of the database to a specified file.
    
    \param filename         [in] A full path to the output file.
    \param pOptions         [in] Pointer to a structure which describes the compression options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    If the write operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
    \remarks
    The method throws an <link OdTvError, OdTvError> exception if the write is unsuccessful.
  */
  virtual OdTvResult writeFile(const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL) = 0;

  /** \details
    Writes the content of the database to a specified .VSFX file.
    
    \param filename         [in] A full path to the output .VSFX file.
    \param pOptions         [in] Pointer to a structure which describes the compression options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    If the write operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
    \remarks
    The method throws an <link OdTvError, OdTvError> exception if the write is unsuccessful.
  */
  virtual OdTvResult writeVSFX( const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL ) = 0;

  /** \details
    This method is deprecated and will be removed soon, use writeVSFX() instead.
    It is possible to use analogue from OdTvDeprecated namespace, but this analogue eventually will be removed too.
    Writes the contents of the database object to the specified stream buffer.
    
    \param buff             [in] Pointer to a stream buffer.
    \param pOptions         [in] Pointer to a structure which describes the compression options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    If the write operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
    \remarks
    The method throws an <link OdTvError, OdTvError> exception if the write is unsuccessful.
  */
  virtual OdTvResult write(OdStreamBuf *buff, const OdTvVSFExportOptions* pOptions = NULL) = 0;

  /** \details
    Writes the content of the database to a specified .VSFX stream.
    
    \param pStream          [in] A smart pointer to the output .VSFX stream.
    \param pOptions         [in] Pointer to a structure which describes the compression options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the write operation.
    If the write operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
    \remarks
    The method throws an <link OdTvError, OdTvError> exception if the write is unsuccessful.
  */
  virtual OdTvResult writeVSFX( OdStreamBufPtr pStream, const OdTvVSFExportOptions* pOptions = NULL ) = 0;

  /** \details
    Exports the TV database to the specified file.
    
    \param pParams  [in] A pointer to an object that contains the <link OdTvBaseExportParams, export parameters>.
    \returns Returns parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \remarks
    The method throws the <link OdTvError, OdTvError> exception if the export operation is not successful.
  */
  virtual OdTvResult exportTo(const OdTvBaseExportParams* pParams) = 0;

  /** \details
    Returns the name of the file associated with the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the full name of the file where the database content was previously saved
    or an empty string if the database has not been saved yet.
    \remarks
    If the rc parameter is not null and the file name returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdString getFilename(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the pointer to the internal database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a pointer to the internal database represented with a void data type pointer.
    \remarks
    If the rc parameter is not null and the pointer returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual void* getInternalDatabase(OdTvResult* rc = NULL) const = 0;

  /** \details
    Adds the Common Data Access (CDA) tree to the database and returns the appropriate ID.
  
    \param name   [in]  A CDA tree storage name as a String value up to 2049 characters long.
    \param pTree  [in]  A pointer to common data access tree object that contains the <link OdTvCDATreePtr, OdTvCDATreePtr>.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the created CDA tree storage object if the creation was successful or returns a null identifier.
    If the rc parameter is not NULL and a new CDA tree storage object is successfully created, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is NULL, you can check the result of the CDA tree storage object creation by calling the isNull() method of the returned identifier.
    If this method returns false, the CDA tree storage object was successfully created. Otherwise the isNull() method returns true.
  */
  virtual OdTvCDATreeStorageId addCDATreeStorage(const OdString& name, OdTvCDATreePtr pTree, OdTvResult* rc = NULL) = 0;

  /** \details
    Returns a smart pointer to an iterator object to get sequential access to CDA tree storages objects in the database.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvCDATreeStoragesIteratorPtr getCDATreeStoragesIterator(OdTvResult* rc = NULL) = 0;

  /** \details
    Registers the name of an application in the database.
    
    \param appName        [in] An application name.
    \param bAlreadyExist  [out] A placeholder to store the flag value that indicates whether an application with specified name was already registered.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the registered application if the application is successfully registered;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the application was registered in the database, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_features_xdata, Work with User Data>
  */
  virtual OdTvRegAppId registerAppName(const OdString& appName, bool& bAlreadyExist, OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the type of an object with specified handle.
    
    \param h [in] An object handle.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the object type represented with a <link OdTv::HandledObjectType, HandledObjectType> enumeration value.
    \remarks
    If the rc parameter is not null and the type of the object was successfully retrieved, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  virtual OdTv::HandledObjectType getObjectTypeByHandle(const OdUInt64 h, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends new data from a file to the database.
    
    \param pParams  [in] A pointer to an object that contains the <link OdTvBaseImportParams, import parameters>.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the model identifier if the model is successfully created and the content of the file is imported to the model;
    otherwise it returns a null identifier.
    \remarks
    If the rc parameter is not null and the model is successfully created and filled with file content, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the append operation is not successful.
  */
  virtual OdTvModelId append(const OdTvBaseImportParams* pParams, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds or updates partial view indexes for models of the database.
    
    \param bUpdateExisting  [in] A flag value that indicates whether the indexes, that exist in the database, should be updated (if equal to true). 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    If the operation was successful, the method returns the tvOk value; otherwise it throws an <link OdTvError, OdTvError> exception.
    \sa
    <link tv_working_with_features_partial_viewing, Work with Partial Viewing>
  */
  virtual OdTvResult addPartialViewIndexes(bool bUpdateExisting = true) = 0;

  /** \details
    Checks that the database has partial indexes.
    
    \param bCheckExtents [in] If true, method will also check that index has valid extents
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if and only if all writable models and blocks in this database have partial indexes.
    \sa
    <link tv_working_with_features_partial_viewing, Work with Partial Viewing>
  */
  virtual bool hasPartialViewIndexes(bool bCheckExtents = false, OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the statistics for the database.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the statistics object for the database.
    \remarks
    If the rc parameter is not null and the statistics object is successfully retrieved, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_features_statistics, Work with Statistics>
  */
  virtual OdTvDatabaseStatistic getStatistic(OdTvResult* rc = NULL) = 0;

  /** \details
    Puts database into Partial Import mode.
    
    \param filename [in] Specifies file (VSF) that will be used as dump file.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    This functionality is designed for Partial Import and is primary for internal usage.
    This method create (or re-write) specified file, but until endPartialImport() call this file will be not a valid VSF-file.
  */
  virtual OdTvResult beginPartialImport( const OdString& filename ) = 0;

  /** \details
    Writes entity into dump file and replace it content by resolver (unloads entity).
    
    \param id [in] Entity to be written
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    This functionality is designed for Partial Import and is primary for internal usage.
    The database have to be in Partial Import mode before calling this method.
    Calling openObject() for written entity will load it from dump file.
  */
  virtual OdTvResult writeObjectPartial( OdTvEntityId id ) = 0;

  /** \details
    Ends Partial Import database mode.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    This functionality is designed for Partial Import and is primary for internal usage.
    This method writes in the dump file all non-dumped data. After it the dump file becomes correct VSF-file.
    However, database state is not equal to Partial Loaded database state, so it is strongly recommended to remove it and re-read database from the dump file.
  */
  virtual OdTvResult endPartialImport() = 0;

  /** \details
    Disables the internal notifications about the modifications of the objects. Notifications will be automatically
    enabled when OdTvGsDevice::update() will be called.
  */
  virtual OdTvResult disableInternalNotifications() = 0;

  /** \details
    Returns the OdTvEntityId that matches the original database handle.
    
    \param originalDatabaseHandle  [in] Original database handle.
    \param rc                      [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the entity identifier if the entity was found by original handle, otherwise it returns a null identifier.
    \remarks
    First call could be slow because of entities caching.
    If the rc parameter is not null and the entity is successfully found, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    The method throws the <link OdTvError, OdTvError> exception if the append operation is not successful.
    \sa
    <link tv_working_with_base_classes_entity, Work with Entities>
  */
  virtual OdTvEntityId findEntity(OdUInt64 originalDatabaseHandle, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets a host app progress meter which will be used for direction the info about import process to the host app
    
    \param pProgressMeter [in] A pointer to an OdDbHostAppProgressMeter object
    \remarks
    Currently supports for the vectorization
  */
  virtual OdTvResult setProgressMeter(OdTvHostAppProgressMeter* pProgressMeter) = 0;

  /** \details
    Sets the given code page to database.
    
    \param cp       [in]  Value for the code page.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setCodePage(OdCodePageId cp) = 0;

  /** \details
    Creates a new Animation action object.
    
    \param name             [in]  An Animation action name represented with a string value up to 2049 characters long.
    \param bNeedSaveInFile  [in] Flag that specifies should animation action be saved in file or not.
    \param rc               [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created Animation action object if the creation was successful or returns a null identifier.
  */
  virtual OdTvAnimationActionId createAnimationAction( const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL ) = 0;
  /** \details
    Removes an animation action object with the given ID.
    
    \param id [in] ID of an animation action object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult removeAnimationAction( const OdTvAnimationActionId& id ) = 0;

  /** \details
    Removes all animation actions.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult clearAnimationActions() = 0;
  
  /** \details
    Returns a smart pointer to an iterator object to get sequential access to animation action objects in the database.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvAnimationActionsIteratorPtr getAnimationActionsIterator( OdTvResult* rc = NULL ) = 0;
  
  /** \details
    Creates a new Animation container object.
  
    \param name [in]  An Animation container name represented with a string value up to 2049 characters long.
    \param bNeedSaveInFile [in] Flag that specifies should animation container be saved in file or not.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the creation.
    \returns Returns an identifier of the created Animation container object if the creation was successful or returns a null identifier.
  */
  virtual OdTvAnimationContainerId createAnimationContainer( const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL ) = 0;
  
  /** \details
    Removes an animation container object with the given ID.
    
    \param id [in] ID of an animation container object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult removeAnimationContainer( const OdTvAnimationContainerId& id ) = 0;

  /** \details
    Removes all animation containers.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult clearAnimationContainers() = 0;
  
  /** \details
    Returns a smart pointer to an iterator object to get sequential access to animation container objects in the database.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator.
    \remarks
    If the rc parameter is not null and the iterator returned by the method is correct, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
    If the rc parameter is null (or not passed in a calling subroutine),
    you can check whether the correct iterator was returned by the method
    by checking whether the returned smart pointer is not NULL.
  */
  virtual OdTvAnimationContainersIteratorPtr getAnimationContainersIterator( OdTvResult* rc = NULL ) = 0;

  /** \details
    Sets a new path to a custom folder that contains image files used as textures, backgrounds or as separate objects.
    
    \param strFolderPath [in] A string that contains the new folder path.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new path to the custom image folder was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCustomImageFolder(const OdString& strFolderPath) = 0;

  /** \details
    Retrieves the current path to the custom folder that contains image files used as textures, backgrounds or as separate objects.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the path to the current custom image folder.
    \remarks
    If the rc parameter is not null and the current path to the custom image folder was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getCustomImageFolder(OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the units used for drawing the contents of this database.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Measuring units set for the first model of the database.
    \remarks
    If the 'rc' parameter is not null and the units was successfully returned, the 'rc' parameter accepts the tvOk value,
    otherwise it contains an appropriate error code. The method returns a value that corresponds to the measuring units set for one of
    models in the database. This value is for reference only and cannot be used as measuring units. For this purpose use the model's units.
  */
  virtual OdTv::Units getUnits(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvDatabase, OdTvDatabase> object.
*/
typedef OdTvSmartPtr<OdTvDatabase> OdTvDatabasePtr;


/** \details
  The interface class for a database object identifier that allows access to the <link OdTvDatabase, OdTvDatabase> object.
*/
class ODTV_EXPORT OdTvDatabaseId : public OdTvLinkId
{
public:
  
  /** \details
    Opens the database determined with its identifier for a read or write operation. 
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the database object.
    \remarks
    If the rc parameter is not null and the database is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvDatabasePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};

#endif //_ODTV_DATABASE_H_INCLUDED_

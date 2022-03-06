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

#ifndef _ODTV_LAYER_H_INCLUDED_
#define _ODTV_LAYER_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvLinetype.h"
#include "TvUserData.h"

class OdTvColorDef;
class OdTvTransparencyDef;
class OdTvLineWeightDef;
class OdTvLinetypeDef;
class OdTvMaterialDef;

/** \details
  The abstract interface class for a Visualize SDK layer object.
  \sa
  <link tv_working_with_attributes_layers, Work with Layers>
*/
class ODTV_EXPORT OdTvLayer : public OdTvHandledIObject
{
public:

  /** \details
    Sets the visible status for the layer object. 
    
    \param bVisible [in] A new value of the visible status. If the value is equal to true, the layer becomes visible; otherwise the layer becomes invisible.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new value of the visible status was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVisible(bool bVisible) = 0;

  /** \details
    Retrieves whether the layer is visible or not. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the layer is visible; otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the visible flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getVisible(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name for the layer object.
    \param sName [in]  A string that contains the layer name to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The name should be a string value with length up to 255 characters.
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new name of the layer object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current layer name. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current name of the layer represented with an OdString object.
    \remarks 
    If the rc parameter is not null and the layer name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Sets a new color for the layer. 
    
    The layer color is used when the color property of an entity located on the layer is equal to the byLayer value.
    \param color [in] A reference to a color definition object that represents the color value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new layer color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColor(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the current layer color. 
    The layer color is used when the color property of an entity located on the layer is equal to the byLayer value.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvColorDef, color definition object> that represents the current color setting for the layer.
    \remarks 
    If the rc parameter is not null and the current layer color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new lineweight value for the layer. 
    The layer lineweight value is used when the lineweight property of an entity located on the layer is equal to the byLayer value.
    
    \param lw [in] A reference to a lineweight definition object that represents the lineweight value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new layer lineweight was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw) = 0;

  /** \details
    Retrieves the current layer lineweight value. 
    The layer lineweight is used when the lineweight property of an entity located on the layer is equal to the byLayer value.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvLineWeightDef, lineweight definition object> that represents the current lineweight setting for the layer.
    \remarks 
    If the rc parameter is not null and current lineweight of the layer was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new linetype for the layer. 
    The layer linetype value is used when the linetype property of an entity located on the layer is equal to the byLayer value.
    
    \param linetypeDef [in] A reference to a linetype definition object that represents the linetype value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new layer linetype was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& linetypeDef) = 0;
  
  /** \details
    Retrieves the current layer linetype. 
    The layer linetype is used when the linetype property of an entity located on the layer is equal to the byLayer value.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvLinetypeDef, linetype definition object> that represents the current linetype setting for the layer.
    \remarks 
    If the rc parameter is not null and current linetype of the layer was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeDef getLinetype(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new description for the layer. The initial description value is an empty string.
    
    \param sDescription [in] A string object that contains the layer description.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The length of the description string should be from 0 to 255 characters.
    If the new description of the layer object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDescription(const OdString& sDescription) = 0;

  /** \details
    Retrieves the current description of the layer.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string object that contains the current layer description.
    \remarks 
    If the rc parameter is not null and the layer description was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getDescription(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new transparency setting for the layer. 
    The layer transparency setting is used when the transparency setting of an entity located on the layer is equal to the byLayer value.
    
    \param transparency [in] A reference to a transparency definition object that represents the transparency setting.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new layer transparency was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTransparency(const OdTvTransparencyDef& transparency) = 0;

  /** \details
    Retrieves the current layer transparency setting. 
    The layer transparency setting is used when the transparency setting of an entity located on the layer is equal to the byLayer value.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvTransparencyDef, transparency definition object> that represents the current transparency setting for the layer.
    \remarks 
    If the rc parameter is not null and the current transparency setting of the layer was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvTransparencyDef getTransparency(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new material to the layer.
    
    \param material [in] A reference to a material definition object that represents the material.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new layer material was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material) = 0;

  /** \details
    Retrieves the current layer material. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvMaterialDef, material definition object> that represents the current material associated with the layer.
    \remarks 
    If the rc parameter is not null and the current material of the layer was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets true if the layer should be ByBlock layer.
    
    \param bIsByBlock [in] True if and only if the layer should be ByBlock layer.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new ByBlock layer state was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setIsByBlock(bool bIsByBlock) = 0;

  /** \details
    Retrieves the ByBlock state of the layer.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns  Returns true if the layer has ByBlock state; otherwise the method returns false.
    \remarks
    If the rc parameter is not null and the current ByBlock state of the layer was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getIsByBlock(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the visibility status for the layer object.
    
    \param bTotallyInvisible [in] A new value of the totally invisible status. If the value is equal to true, the layer becomes totally invisible; otherwise the layer becomes totally visible.
    \returns 
    Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new value of the totally invisibility status was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    Totally invisible layers are considered frozen.
    Entities that are associated with a frozen layer cannot be selected, edited, printed or rendered.
    For more information, see <exref target="https://docs.opendesign.com/td/db_layer.html">Working with Layers</exref> of the Drawings SDK documentation.
  */
  virtual OdTvResult setTotallyInvisible(bool bTotallyInvisible) = 0;

  /** \details
    Checks whether the layer is totally invisible.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns 
    Returns true if the layer is totally invisible; otherwise the method returns false.
    \remarks
    If the rc parameter is not null and the totally invisible flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    Totally invisible layers are considered frozen.
    Entities that are associated with a frozen layer cannot be selected, edited, printed or rendered.
    For more information, see <exref target="https://docs.opendesign.com/td/db_layer.html">Working with Layers</exref> of the Drawings SDK documentation.
  */
  virtual bool getTotallyInvisible(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLayer, OdTvLayer> object.
*/
typedef OdTvSmartPtr<OdTvLayer> OdTvLayerPtr;


/** \details
  The interface class for a layer object identifier that allows access to the <link OdTvLayer, OdTvLayer> object.
*/
class ODTV_EXPORT OdTvLayerId : public OdTvId
{
public:

  /** \details
    Opens the layer determined with its identifier for a read or write operation. 
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the layer object.
    \remarks
    If the rc parameter is not null and the layer is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvLayerPtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};

/** \details
  The base interface class for the iterator of Visualize SDK layer objects.
  An iterator object provides sequential access to a collection of layers.
*/
class ODTV_EXPORT OdTvLayersIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the layer that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the layer identifier if the iterator refers to a layer; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the layer identifier is successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a layer, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvLayerId getLayer(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for the layer defined by its identifier and moves the iterator to this layer if found.
    
    \param layerId [in] A layer identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the layer specified by its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvLayerId& layerId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLayersIterator, OdTvLayersIterator> object.
*/
typedef OdTvSmartPtr<OdTvLayersIterator> OdTvLayersIteratorPtr;

/** \details
  A data type that represents an array of smart pointers to an <link OdTvLayerId, OdTvLayerId> object.
*/
typedef OdArray<OdTvLayerId> OdTvLayerIdsArray;


#endif // _ODTV_LAYER_H_INCLUDED_

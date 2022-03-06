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

#ifndef _ODTV_INSERT_H_INCLUDED_
#define _ODTV_INSERT_H_INCLUDED_

#include "Tv.h"
#include "TvEntity.h"
#include "TvBlock.h"
#include "TvIObject.h"
#include "TvUserData.h"

/** \details
  This is an abstract interface class for an insert (block reference) object.
  \sa
  <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry>
*/
class ODTV_EXPORT OdTvInsert : public OdTvHandledIObject
{  
public:

  /** \details
    Retrieves the block object that is associated with the insert object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an identifier of the block object associated with the insert object.
    \remarks 
    If the rc parameter is not null and the block identifier was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvBlockId getBlock(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a block object to be associated with the insert object.
    
    \param blockId [in]  An identifier of the block object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the block object was successfully associated with the insert object, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBlock(const OdTvBlockId& blockId) = 0;

  /** \details
    Retrieves the current name of the insert object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current name of the insert object. 
    \remarks 
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the rc parameter is not null and the insert object name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name for the insert object.
    
    \param sName [in]  A new name of the insert object. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new name of the insert object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Appends a sub-entity object and returns its identifier. 
    
    \param name [in]  A name of the appended sub-entity.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns an identifier of the appended sub-entity. 
    \remarks 
    If the rc parameter is not null and the sub-entity was successfully appended, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_entities, Work with Sub-Entities>
  */
  virtual OdTvEntityId appendSubEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;
  
  /** \details
    Returns true if and only if insert has at least one sub-entity 
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \remarks 
    If the rc parameter is not null and the sub-entity was successfully appended, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_entities, Work with Sub-Entities>
  */
  virtual bool hasSubEntities( OdTvResult* rc = NULL ) const = 0;

  /** \details
    Retrieves the current insertion point of the insert object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current insertion point of the insert object.
    \remarks 
    If the rc parameter is not null and the current insertion position was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdGePoint3d getPosition(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new insertion point of the insert object.
    
    \param position [in]  A 3D point object that specifies the insertion point of the object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the insertion point was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPosition(const OdGePoint3d& position) = 0;

  /** \details
    Retrieves the current scale factors applied to the insert object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current scale factors.
    \remarks 
    If the rc parameter is not null and the scale factors were successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvScale getScaleFactors(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets new scale factors to the insert object and applies them.
    
    \param scale [in]  A 3D scale factor object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new scale factors were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The method throws the tvInvalidInput exception when one or more scale factors are equal to zero.
  */
  virtual OdTvResult setScaleFactors(const OdTvScale& scale) = 0;

  /** \details
    Retrieves the current rotation angle applied to the insert object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the rotation angle value.
    \remarks
    The rotation is applied about the Z-axis, relative to the X-axis, in the coordinate system parallel to the object's OCS, but with the origin that is located at the object's insertion point.
    All angles are measured in radians.
    If the rc parameter is not null and the new rotation angle was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getRotation(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new rotation angle value to be applied to the insert object.
    
    \param angle [in] A new rotation angle value to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The rotation is applied about the Z-axis, relative to the X-axis, in the coordinate system parallel to the object's OCS, but with the origin that is located at the object's insertion point.
    All angles are measured in radians.
    If the new rotation angle value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setRotation(double angle) = 0;

  /** \details
    Retrieves the WCS normal <link OdTvVector, vector> to the plane where the insert object is located.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the WCS normal <link OdTvVector, vector> to the plane where the insert object is located.
    \remarks 
    If the rc parameter is not null and the normal vector object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getNormal(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the WCS normal <link OdTvVector, vector> to the plane where the insert object is located.
    
    \param normal [in] A new normal <link OdTvVector, vector>.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new normal vector was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setNormal(const OdTvVector& normal) = 0;
  
  /** \details
    Retrieves the current transformation <link OdTvMatrix, matrix> that maps points from the Microspace Coordinate System (MCS) to the World Coordinate System (WCS).
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current transformation <link OdTvMatrix, matrix> for the MCS to WCS transformation. 
    \remarks
    The Microspace Coordinate System (MCS) is the World Coordinate System (WCS) within the block definition.
    For example, applying a transformation matrix to the center of an arc within the block definition returns the center of the arc as it appears in the block reference.
    If the rc parameter is not null and the transformation matrix was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvMatrix getBlockTransform(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new transformation <link OdTvMatrix, matrix> that maps points from the Microspace Coordinate System (MCS) to the World Coordinate System (WCS).
    
    \param xfm [in] A 3D transformation matrix to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The Microspace Coordinate System (MCS) is the World Coordinate System (WCS) within the block definition.
    For example, applying a transformation matrix to the center of an arc within the block definition returns the center of the arc as it appears in the block reference.
    If the new transformation matrix for the insert object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBlockTransform(const OdTvMatrix& xfm) = 0;

  /** \details
    Sets new clipping boundary properties to the insert object. 
    
    \param points               [in] An array of 2D points that represent the boundary definition.
    \param xToClipSpace         [in] A matrix that defines the transformation from model space to clipping space. Often it defines an identity transformation.
    \param xInverseInsertXForm  [in] A matrix that defines the transformation from block space to world space.
    \param frontClip            [in] A front clipping distance in the normal vector direction.
    \param backClip             [in] A back clipping distance in the direction that is opposite from the normal vector direction.
    \param bDrawBoundary        [in] A flag value that enables (if true) or disables (if false) the clip volume.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If no points are passed within the points array (i.e. the array is empty), the clipping that was previously set for the insert object is removed.
    If only two points are passed within the points array, these points define the diagonal of a clipping rectangle.
    In other cases, the points passed in the points array define a non-self-intersecting polygon for clipping. 
    If new clipping boundary properties were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setClippingBoundary(const OdTvPoint2dArray& points, const OdTvMatrix& xToClipSpace, const OdTvMatrix& xInverseInsertXForm,
                                         double frontClip = ODTV_INFINITE_XCLIP_DEPTH, double backClip = ODTV_INFINITE_XCLIP_DEPTH,
                                         bool bDrawBoundary = true) = 0;

  /** \details
    Retrieves the current clipping boundary properties for the insert object. 
    
    \param pts           [out] A placeholder for an array of 2D points that represent the boundary definition.
    \param xfrm          [out] A placeholder for a matrix that defines the transformation from model space to clipping space. Often it defines an identity transformation.
    \param invInsertxfrm [out] A placeholder for a matrix that defines the transformation from block space to world space.
    \param frontClip     [out] A placeholder for a front clipping distance in the normal vector direction.
    \param backClip      [out] A placeholder for a back clipping distance in the direction that is opposite from the normal vector direction.
    \param bDrawBoundary [out] A placeholder for a flag value that enables (if true) or disables (if false) the clip volume.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The method fills passed parameters and returns them to a calling subroutine.
    If no points are returned within the pts array (i.e. the array is empty), it means that the insert object has no clipping boundary properties set.
    If only two points are returned within the pts array, these points define the diagonal of a clipping rectangle.
    In other cases, the points returned in the pts array define a non-self-intersecting polygon for clipping. 
    If current clipping boundary properties were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getClippingBoundary(OdTvPoint2dArray& pts, OdTvMatrix& xfrm, OdTvMatrix& invInsertxfrm, double& frontClip, double& backClip, bool& bDrawBoundary) = 0;

  /** \details
    Sets new extents to the insert object. 
    
    \param ext [in] A new extents object to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If a new extents object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext) = 0;

  /** \details
    Retrieves the current extents of a specified type for the insert object.
    
    \param ext    [out] A placeholder for current extents object. 
    \param eType  [in]  A type of extents to be retrieved. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The method fills the passed extents object and returns it to a calling subroutine. 
    If the extents object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const = 0;

  /** \details
    Sets a new color for the insert object. 
    
    \param color [in] A new color value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If a new color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setColor(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the current color of the insert object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current color represented with an <link OdTvColorDef, OdTvColorDef> object. 
    \remarks 
    The returned color definition object represents a color in RGB format, an inherited color, or a color index in the palette.
    If the rc parameter is not null and the current color definition object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getColor(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets a new  lineweight for the insert object.
    
    \param lw [in] A new lightweight definition to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new lightweight was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw) = 0;

  /** \details
    Retrieves the current lineweight for the insert object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current lineweight definition object applied to the insert object.
    \remarks 
    If the rc parameter is not null and the current lightweight definition object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_lineweights, Work with Lineweights>
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets a new linetype for the insert object. 
    
    \param lt [in] A new linetype definition object to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new linetype definition object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt) = 0;

  /** \details
    Retrieves the current linetype for the insert object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current linetype definition object applied to the insert object. 
    \remarks 
    If the rc parameter is not null and the current linetype definition object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeDef getLinetype(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets a new layer for the insert object.
    
    \param layer [in] A new layer definition object to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new layer definition object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& layer) = 0;

  /** \details
    Retrieves the current layer for the insert object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current layer definition object applied to the insert object. 
    \remarks 
    If the rc parameter is not null and the current layer definition object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getLayer(OdTvResult* rc = NULL) = 0;

  /** \details
    Set a new visibility property value for the insert object. 
    
    \param visible [in] A new visibility definition object to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new visibility definition object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible) = 0;

  /** \details
    Retrieves the current visibility property value for the insert object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current visibility definition object applied to the insert object. 
    \remarks 
    If the rc parameter is not null and the current visibility definition object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVisibilityDef getVisibility(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for a sub-entity with the specified handle in the insert object.
    
    \param h [in] A handle value of the sub-entity being searched for. 
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the search operation.
    \returns Returns the identifier of the found sub-entity. If the sub-entity is not found, returns a NULL identifier (the method isNull() of the identifier returns true).
    \remarks 
    If the rc parameter is not null and the sub-entity was found, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_geometry_sub_entities, Work with Sub-Entities>
  */
  virtual OdTvEntityId findSubEntity(const OdUInt64 h, OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves a smart pointer to the entities iterator.
    
    The entities iterator provides sequential access to subentities that the insert contains.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the entities iterator. If the insert contains no subentities, the method returns a null smart pointer.
    \remarks
    If the rc parameter is not null and the smart pointer to the entities iterator is successfully returned, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvEntitiesIteratorPtr getSubEntitiesIterator(OdTvResult* rc = NULL) const = 0;

  /** \details
    Adds a view object in which the insert object is displayed. By default the insert object is displayed in all views.
    
    \param viewId [in] An identifier of a view object. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that determines whether the addition of a view was successful or not.
    \remarks
    If the new view object was successfully added, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult addViewDependency(const OdTvGsViewId& viewId) = 0;

  /** \details
    Removes a specified view object from the list of views in which the insert object can be displayed.
    
    \param viewId [in] An identifier of a view object that should be removed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that determines whether the view object was successfully removed.
    \remarks
    If the specified view object was successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeViewDependency(const OdTvGsViewId& viewId) = 0;

  /** \details
    Removes all view dependencies of the insert object. This means that the insert object is displayed in all views.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If all view dependencies were successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeViewDependencies() = 0;

  /** \details
    Checks whether the insert object is a view-dependent object. 
    
    The insert object is view dependent when it is displayed in specified views; otherwise it is view independent. 
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the insert object is view dependent; otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the view-dependent check was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isViewDependent(OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the set of views in which the insert object is displayed, if it is view dependent.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an array of view identifiers in which the insert object is displayed.
    \remarks 
    If the rc parameter is not null and the array of view identifiers was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvGsViewIdsArray getViewDependencies(OdTvResult *rc = NULL) = 0;

  /** \details
    Sets the content of the insert object selectable or non-selectable.
    
    \param bSelectable [in] A boolean value that determines whether the content is selectable (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    OBSOLETE. Insert's content is always selectable. Selectability of insert's content depends on the 'kBlocksCache' option of the device and on the selection level.
  */
  virtual OdTvResult setContentsSelectable(bool bSelectable) = 0;

  /** \details
    Retrieves whether the content of the insert object is selectable or non-selectable.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the content of the insert object is selectable; otherwise the method returns false.
    \remarks 
    OBSOLETE. Insert's content is always selectable. Selectability of insert's content depends on the 'kBlocksCache' option of the device and on the selection level.
  */
  virtual bool getContentsSelectable(OdTvResult* rc = NULL) = 0;

  /** \details
    Copies all insert's data to a specified insert (attributes, entities etc).
    All current data in the target insert will be deleted or overwritten.
    
    \param targetInsertId [in] A target <link OdTvEntityId, entity identifier>. The data will be copied to the insert the identifier refers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying inserts within the same database. If source and destination inserts belong to different databases
    default OdTvAttributeResolver will be created and used. Using copyTo(OdTvEntityId& targetInsertId, OdTvAttributeResolverPtr pResolver) will be
    more optimal in this case.
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetInsertId) const = 0;

  /** \details
    Copies all insert's data to a specified insert (attributes, entities etc).
    All current data in the target insert will be deleted or overwritten.
    
    \param targetInsertId [in] A target <link OdTvEntityId, entity identifier>. The data will be copied to the insert the identifier refers.
    \param pResolver [in] A smart pointer to the instance of OdTvAttributeResolver
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying inserts from different databases. If source and destination inserts belong to the same database using
    copyTo(OdTvEntityId& targetInsertId) will be more optimal.
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetInsertId, OdTvAttributeResolverPtr pResolver) const = 0;

  /** \details
  Sets the material for the insert.
  \param material [in] A material definition object.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If the material has been successfully applied, the method returns tvOk; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material) = 0;

  /** \details
  Retrieves the current material applied to the insert.
  \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the current material definition for the insert.
  \remarks
  If the rc parameter is not null and the material definition has been successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
  appropriate error code.
  \sa
  <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvInsert, OdTvInsert> object.
*/
typedef OdTvSmartPtr<OdTvInsert> OdTvInsertPtr;


#endif //_ODTV_INSERT_H_INCLUDED_

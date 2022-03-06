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

#ifndef _ODTV_INSERTIMPL_H_INCLUDED_
#define _ODTV_INSERTIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvInsert.h"
#include "TvInterfaceWrappers.h"
#include "TvTraitsStorage.h"
#include "TvEntityIteratorImpl.h"
#include "TvUserDataImpl.h"

#include "DbBlockReference.h"
#include "Gi/GiDummyGeometry.h"

#define STL_USING_SET
#include "OdaSTL.h"

/** \details
*/
class OdTvDummyWrapperWorldGeometry : public OdGiWrapperGeometry< OdGiWorldGeometry >
{
  friend class OdTvWorldDrawWrapperOverCommonDraw;
public:
  virtual void setExtents(const OdGePoint3d * /*newExtents*/) { }
  virtual void startAttributesSegment() {}

  void addRef() { }
  void release() { }
};

/** \details
Special class which allow to wrap OdGiViewportDraw as OdGiWorldDraw
*/
class OdTvWorldDrawWrapperOverCommonDraw : public OdGiWrapperCommonDraw< OdGiWorldDraw >
{
  OdTvDummyWrapperWorldGeometry m_geometry;
public:
  OdTvWorldDrawWrapperOverCommonDraw(OdGiCommonDraw* pVd)
  {
    setDraw(*pVd);
    m_geometry.setGeom( pVd->rawGeometry() );
  }

  virtual OdGiWorldGeometry& geometry() const { return (OdGiWorldGeometry&)m_geometry; }

  void addRef() { }
  void release() { }
};


/** \details
This struct is used to store the clip boundary specifications for the OdTvInsert object
*/
struct OdTvInsertClipBoundary
{
  OdGePoint2dArray      m_Points;                 // Array of points that defines the clip boundary.
  OdGeMatrix3d          m_xToClipSpace;           // Transformation matrix from ModelSpace to ClipSpace.
  OdGeMatrix3d          m_xInverseBlockRefXForm;  // Transformation matrix from BlockSpace to WorldSpace.
  double                m_dFrontClipZ;            // Distance from target point to FrontClip plane.
  double                m_dBackClipZ;             // Distance from target point to BackClip plane.
  bool                  m_bDrawBoundary;          // Enables clipping boundary to be drawn.

  OdTvInsertClipBoundary()
  {
    m_dFrontClipZ = m_dBackClipZ = ODTV_INFINITE_XCLIP_DEPTH;
    m_bDrawBoundary = false;
  }

  OdUInt64 getObjectSize()
  {
    OdUInt64 res = 0;

    res += sizeof(*this);
    res += sizeof(OdGePoint2d) * m_Points.physicalLength();

    return res;
  }
};


/** \details
This class is the internal implementation of the insert. Such implementation is need
because of special storing of the lineweight attribute and color
*/
class OdTvInsertImpl : public OdTvDbBlockReference, public OdTvXDataStorage
{
  OdTvInsertImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvInsertImpl);

  virtual ~OdTvInsertImpl();

  /** \details
  Sets the values of this object's subentity traits, and returns with the calling
  object's subentity traits.

  \param pTraits [in] Pointer to the OdGiDrawableTraits object to be set.
  */
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  /** \details
  Returns true if the entity has no view-dependent graphics. In another case
  returns false.

  \param pWd [in] Pointer to the OdGiWorldDraw object.
  */
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

  /** \details
  Returns nothing

  \param pVd [in] Pointer to the OdGiViewportDraw object.
  */
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Sets the color for this Insert
  */
  void setTvColor(const OdTvCmEntityColor& color);

  /** \details
  Returns the color of this Insert
  */
  const OdTvCmEntityColor& getTvColor() const;

  /** \details
  Sets the line weight for this Insert
  */
  void setLineweight(OdDb::LineWeight lineWeight);

  /** \details
  Returns the line weight of this Insert
  */
  OdDb::LineWeight getLineweight() const;

  /** \details
  Sets the name for this Insert
  */
  void setName(const OdString& name);

  /** \details
  Returns the name of this Insert
  */
  OdString  getName() const;

  /** \details
  Sets the transformation matrix mapping a point in the MCS
  to the WCS.
  */
  OdTvResult setTransform(const OdTvMatrix& xfm);

  /** \details
  Appends an entity object and returns the appropriate ID
  */
  OdTvEntityId appendSubEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);
  virtual bool hasSubEntities( OdTvResult* rc = NULL ) const;

  /** \details
  Set the clipping boundary property of this Insert

  \param points [in]  Boundary definition.
  \param xToClipSpace [in] The transformation matrix from ModelSpace to ClipSpace. Often this will be an identity transform. 
  \param xInverseInsertXForm [in] The transformation matrix from BlockSpace to WorldSpace.
  \param frontClip [in]  Front clip distance in the normal direction.
  \param backClip [in]  Back clip distance in the -normal direction.
  \param bDrawBoundary [in]  Enables the clip volume.

  \remarks
  If zero points are provided  in points, it means to remove clipping from this insert
  If only two points are provided in points, these points define the diagonal of a rectangle.
  Otherwise, they define a non-self-intersecting polygon.
  */
  OdTvResult setClippingBoundary(const OdTvPoint2dArray& points, const OdTvMatrix& xToClipSpace, const OdTvMatrix& xInverseInsertXForm, double frontClip, double backClip, bool bDrawBoundary);

  /** \details
  Get the clipping boundary property of this Insert

  \param points [out]  Receives the boundary definition.
  \param xfrm [out] Receives the transformation matrix from ModelSpace to ClipSpace
  \param invInsertxfrm [out] Receives the transformation matrix from BlockSpace to WorldSpace
  \param frontClip [out]  Receives the front clip distance in the normal direction.
  \param backClip [out]  Receives the back clip distance in the -normal direction.
  \param bDrawBoundary [out]  Receives the status of the boundary drawing.
  */
  OdTvResult getClippingBoundary(OdTvPoint2dArray& pts, OdTvMatrix& xfrm, OdTvMatrix& invInsertxfrm, double& frontClip, double& backClip, bool& bDrawBoundary);

  /** \details
  Set extents to the insert
  */
  OdTvResult setExtents(const OdTvExtents3d& ext);

  /** \details
  Get extents from this insert
  */
  OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const;

  /** \details
  Find a subentity by handle, and return OdTvEntityId
  */
  OdTvEntityId findSubEntity(const OdUInt64 h, OdTvResult* rc);

  /** \details
  Add view in which insert will be drawn
  */
  OdTvResult addViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove the view from the views in which the insert should be drawn
  */
  OdTvResult removeViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove any view dependencies which means that the insert will be drawn in all views
  */
  OdTvResult removeViewDependencies();

  /** \details
  Checks that the insert is view dependent (means should be drawn in the specified views)
  */
  bool isViewDependent(OdTvResult* rc = NULL);

  /** \details
  Returns the views in which this entity should be drawn
  */
  OdTvGsViewIdsArray getViewDependencies(OdTvResult *rc = NULL);

  /** \details
  Mark subentities of the subentites
  */
  void pushDownSubEntityMark();

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  /** \details
  Copies all insert's data to a specified insert (attributes, geometries etc).
  All current data in the target insert will be deleted or overwrited.
  */
  OdTvResult copyTo(OdTvEntityId& targetInsertId, bool bFromInterface = true) const;

  /** \details
  Copies all insert's data to a specified insert (attributes, geometries etc).
  All current data in the target insert will be deleted or overwrited.
  */
  OdTvResult copyTo(OdTvEntityId& targetInsertId, OdTvAttributeResolverPtr pResolver, bool bFromInterface = true, bool bNeedResolveBlock = true) const;

  /** \details
  Returns true if contents of insert is selectable
  */
  bool getContentsSelectable(OdTvResult* rc = NULL);

  /** \details
  Sets selectable contents or not for current insert
  */
  OdTvResult setContentsSelectable(bool bSelectable);

  /** \details
  Write attributes partial
  */
  void writeAttributesObjectPartial();

  /** \details
  Clear vertices spatial tree in all entities in block of this  insert
  */
  virtual void clearSpatialTreeCacheInEntities();

  /** \details
  Returns the pointer to the subentities iterator object
  */
  virtual OdTvEntitiesIteratorPtr getSubEntitiesIterator(OdTvResult* rc = NULL) const;

private:

  // create new iterator
  OdTvDbObjectIteratorPtr newSubEntityIterator() const;

  //draw
  bool draw(OdGiCommonDraw* pCd, bool bIsViewport = false) const;

  // Removes all entities that the insert contains.
  OdTvResult clearEntities();

  // Remove an entity object with the given ID
  OdTvResult removeEntity(const OdTvEntityId& id);

private:

  // name of the insert
  OdString m_name;

  // color (where index 0 means NOT byBlock)
  OdTvCmEntityColor  m_color;

  // lineweight (not as index - simply as int)
  OdDb::LineWeight    m_lineWeight;

  // childs entities container (empty in initial state)
  // for example for storing the attributes
  OdTvEntityIdContainer m_subEntities;

  // pointer to the clipping boundary properties
  OdTvInsertClipBoundary* m_pClipBoundaryProperties;

  // extents of the insert in the OCS (object (entity coordinate system) with taking into account local transform
  // (NULL by default)
  OdTvExtents3d*            m_pExtents;

  // List of views where this entity should be drawn
  OdHardPtrIdArray    m_views;

  // True if list of view is not empty, even if view was deleted from database
  bool              m_bIsViewDependent;

  // True if contents of this insert is selectable
  bool              m_bContentSelectable;
};

typedef OdSmartPtr<OdTvInsertImpl> OdTvInsertImplPtr;



/** \details
    This is an wrapper of the interface class for OdTvInsert object.

    \remarks
    The purpose of this class is to connect the internal entity object with an interface object
*/
  
class OdTvInsertWrapper : public OdTvInsert
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvInsert, OdTvInsertImpl)

  friend class OdTvBlockWrapper;
  friend class OdTvModelRootEntityImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

public:

  /** \details
  Returns the name of the entity
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Sets the name for the entity

  \param sName [in]  Entity name
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the ID of the block associated with this Insert.
  */
  virtual OdTvBlockId getBlock(OdTvResult* rc = NULL) const;

  /** \details
  Sets the ID of the block associated with this Insert.

  \param blockId [in]  Object ID of the block.
  */
  virtual OdTvResult setBlock(const OdTvBlockId& blockId);

  /** \details
  Appends an entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendSubEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Returns true if and only if insert has at least one sub-entity 
  */
  virtual bool hasSubEntities( OdTvResult* rc = NULL ) const;

  /** \details
  Returns the insertion point of this insert
  */
  virtual OdTvPoint getPosition(OdTvResult* rc = NULL) const;

  /** \details
  Sets the insertion point of this Insert.

  \param position [in]  Any 3D point.
  */
  virtual OdTvResult setPosition(const OdTvPoint& position);

  /** \details
  Returns the scale factors applied to this Insert.
  */
  virtual OdTvScale getScaleFactors(OdTvResult* rc = NULL) const;

  /** \details
  Sets the scale factors to be applied to this Insert.

  \param scale [in]  Any 3D scale factor.

  Throws:
  <table>
  Exception             Cause
  tvInvalidInput       One or more scale factors is 0
  </table>
  */
  virtual OdTvResult setScaleFactors(const OdTvScale& scale);

  /** \details
  Returns the rotation angle applied to this Insert.

  \remarks
  Rotation is about the Z axis, relative the X-axis, in the coordinate system parallel to
  this object's OCS, but with its origin at this object's insertion point.

  \remarks
  All angles are expressed in radians.
  */
  virtual double getRotation(OdTvResult* rc = NULL) const;

  /** \details
  Sets the rotation angle to be applied to this Insert, in radians.

  \remarks
  Rotation is about the Z axis, relative the X-axis, in the coordinate system parallel to
  this object's OCS, but with its origin at this object's insertion point.

  \param angle [in]  Rotation angle.
  */
  virtual OdTvResult setRotation(double angle);

  /** \details
  Returns the WCS normal to the plane of this Insert.
  */
  virtual OdTvVector getNormal(OdTvResult* rc = NULL) const;

  /** \details
  Sets the WCS normal to the plane of this Insert.

  \param normal [in]  Normal.
  */
  virtual OdTvResult setNormal(const OdTvVector& normal);

  /** \details
  Returns the transformation matrix mapping a point in the MCS
  to the WCS.

  \remarks
  The Microspace Coordinate System (MCS) is the WCS within the block definition.
  Applying this matrix to the center of an arc within the block definition
  returns the center of the arc as it appears in the block reference.
  */
  virtual OdTvMatrix getBlockTransform(OdTvResult* rc = NULL) const;

  /** \details
  Sets the transformation matrix mapping a point in the MCS
  to the WCS.

  \param xfm [in]  Any 3D transformation matrix.

  \remarks
  The Microspace Coordinate System (MCS) is the WCS within the block definition.
  Applying this matrix to the center of an arc within the block definition
  returns the center of the arc as it appears in the block reference.
  */
  virtual OdTvResult setBlockTransform(const OdTvMatrix& xfm);

  /** \details
  Set the clipping boundary property of this Insert

  \param points [in]  Boundary definition.
  \param xToClipSpace [in] The transformation matrix from ModelSpace to ClipSpace. Often this will be an identity transform.
  \param xInverseInsertXForm [in] The transformation matrix from BlockSpace to WorldSpace.
  \param frontClip [in]  Front clip distance in the normal direction.
  \param backClip [in]  Back clip distance in the -normal direction.
  \param bDrawBoundary [in]  Enables the clip volume.

  \remarks
  If zero points are provided  in points, it means to remove clipping from this insert
  If only two points are provided in points, these points define the diagonal of a rectangle.
  Otherwise, they define a non-self-intersecting polygon.
  */
  virtual OdTvResult setClippingBoundary(const OdTvPoint2dArray& points, const OdTvMatrix& xToClipSpace, const OdTvMatrix& xInverseInsertXForm,
                                         double frontClip = ODTV_INFINITE_XCLIP_DEPTH, double backClip = ODTV_INFINITE_XCLIP_DEPTH,
                                         bool bDrawBoundary = true);

  /** \details
  Get the clipping boundary property of this Insert

  \param points [out]  Receives the boundary definition.
  \param xfrm [out] Receives the transformation matrix from ModelSpace to ClipSpace
  \param invInsertxfrm [out] Receives the transformation matrix from BlockSpace to WorldSpace
  \param frontClip [out]  Receives the front clip distance in the normal direction.
  \param backClip [out]  Receives the back clip distance in the -normal direction.
  \param bDrawBoundary [out]  Receives the status of the boundary drawing.
  */
  virtual OdTvResult getClippingBoundary(OdTvPoint2dArray& pts, OdTvMatrix& xfrm, OdTvMatrix& invInsertxfrm, double& frontClip, double& backClip, bool& bDrawBoundary);

  /** \details
  Set extents to the insert
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext);

  /** \details
  Get 'eType' extents from this insert
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const;

  /** \details
  Sets the color for this Insert
  */
  virtual OdTvResult setColor(const OdTvColorDef& color);

  /** \details
  Get the color of the Insert as rgb, inherited or index
  */
  virtual OdTvColorDef getColor(OdTvResult* rc = NULL);

  /** \details
  Sets the line weight for this Insert
  */
  virtual OdTvResult setLineWeight(const OdTvLineWeightDef& lw);

  /** \details
  Get the line weight of the Insert
  */
  virtual OdTvLineWeightDef getLineWeight(OdTvResult* rc = NULL);

  /** \details
  Sets the  linetype for this Insert
  */
  virtual OdTvResult setLinetype(const OdTvLinetypeDef& lt);

  /** \details
  Get the linetype of the Insert
  */
  virtual OdTvLinetypeDef getLinetype(OdTvResult* rc = NULL);

  /** \details
  Sets the  layer for this Insert
  */
  virtual OdTvResult setLayer(const OdTvLayerDef& l);

  /** \details
  Get the layer of the Insert
  */
  virtual OdTvLayerDef getLayer(OdTvResult* rc = NULL);
  
  /** \details
  Set the visibility property of the Insert
  */
  virtual OdTvResult setVisibility(const OdTvVisibilityDef& visible);

  /** \details
  Get the visibility property of the Insert
  */
  virtual OdTvVisibilityDef getVisibility(OdTvResult* rc = NULL) const;

  /** \details
  Find a subentity by handle, and return OdTvEntityId
  */
  virtual OdTvEntityId findSubEntity(const OdUInt64 h, OdTvResult* rc = NULL);

  /** \details
  Retrieves a smart pointer to the entities iterator.
  The entities iterator provides sequential access to subentities that the insert contains.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns a smart pointer to the entities iterator. If the insert contains no subentities, the method returns a null smart pointer.
  \remarks
  If the rc parameter is not null and the smart pointer to the entities iterator is successfully returned, the rc parameter accepts the tvOk value, otherwise it contains an
  appropriate error code.
  */
  virtual OdTvEntitiesIteratorPtr getSubEntitiesIterator(OdTvResult* rc = NULL) const;

  /** \details
  Add view in which insert will be drawn
  */
  virtual OdTvResult addViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove the view from the views in which the insert should be drawn
  */
  virtual OdTvResult removeViewDependency(const OdTvGsViewId& viewId);

  /** \details
  Remove any view dependencies which means that the insert will be drawn in all views
  */
  virtual OdTvResult removeViewDependencies();

  /** \details
  Checks that the insert is view dependent (means should be drawn in the specified views)
  */
  virtual bool isViewDependent(OdTvResult* rc = NULL);

  /** \details
  Returns the views in which this entity should be drawn
  */
  virtual OdTvGsViewIdsArray getViewDependencies(OdTvResult *rc = NULL);

  /** \details
  Sets selectable contents or not for current insert
  */
  virtual OdTvResult setContentsSelectable(bool bSelectable);

  /** \details
  Returns true if contents of insert is selectable
  */
  virtual bool getContentsSelectable(OdTvResult* rc = NULL);

  /** \details
  Copies all insert's data to a specified insert (attributes, geometries etc).
  All current data in the target insert will be deleted or overwrited.
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetInsertId) const;

  /** \details
  Copies all insert's data to a specified insert (attributes, geometries etc).
  All current data in the target insert will be deleted or overwrited.
  */
  virtual OdTvResult copyTo(OdTvEntityId& targetInsertId, OdTvAttributeResolverPtr pResolver) const;

  /** \details
  Sets the material for the insert.
  \param material [in] A material definition object.
  */
  virtual OdTvResult setMaterial(const OdTvMaterialDef& material);

  /** \details
  Retrieves the current material applied to the insert.
  */
  virtual OdTvMaterialDef getMaterial(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

#include "TD_PackPop.h"

#endif //_ODTV_INSERTIMPL_H_INCLUDED_

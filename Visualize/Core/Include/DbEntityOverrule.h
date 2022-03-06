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

#ifndef _DBENTITYOVRRULE_H_INCLUDED_
#define _DBENTITYOVRRULE_H_INCLUDED_

#include "RxOverrule.h"
#include "DbEntity.h"

/** \details
  This class overrules a subset of osnap linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.

  Corresponding C++ library: TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbOsnapOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbOsnapOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbOsnapOverrule();

  /** \details
    Overrules the OdTvDbEntity::subGetOsnapPoints() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param osnapMode [in]  Osnap mode to be requested.
    \param gsSelectionMark [in]  GS marker of the subentity involved in the snap operation.
    \param pickPoint [in]  WCS coordinates of the point picked during the snap operation.
    \param lastPoint [in]  WCS coordinates of the point selected just before pickPoint.
    \param xWorldToEye [in]  A transformation matrix to transform from WCS to DCS.
    \param snapPoints [in]  An existing array to append osnap points.
  */
  virtual OdResult getOsnapPoints(
    const OdTvDbEntity* pSubject,
    OdDb::OsnapMode osnapMode,
    OdGsMarker gsSelectionMark,
    const OdGePoint3d& pickPoint,
    const OdGePoint3d& lastPoint,
    const OdGeMatrix3d& xWorldToEye,
    OdGePoint3dArray& snapPoints );

  /** \details
    Overrules the OdTvDbEntity::subGetOsnapPoints() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param osnapMode [in]  Osnap mode to be requested.
    \param gsSelectionMark [in]  GS marker of the subentity involved in the snap operation.
    \param pickPoint [in]  WCS coordinates of the point picked during the snap operation.
    \param lastPoint [in]  WCS coordinates of the point selected just before pickPoint.
    \param xWorldToEye [in]  A transformation matrix to transform from WCS to DCS.
    \param snapPoints [in]  An existing array to append osnap points.
    \param insertionMat [in]  A transformation matrix for block transformation.
  */
  virtual OdResult getOsnapPoints(
    const OdTvDbEntity* pSubject,
    OdDb::OsnapMode osnapMode,
    OdGsMarker gsSelectionMark,
    const OdGePoint3d& pickPoint,
    const OdGePoint3d& lastPoint,
    const OdGeMatrix3d& xWorldToEye,
    OdGePoint3dArray& snapPoints,
    const OdGeMatrix3d& insertionMat);

  /** \details
    Returns True when it is a block entity which requires investigating the block definition, or False otherwise.

    \remarks
    The application can override this function to inform the host application: don't investigate the compounded objects 
    that use a block definition for osnap points. This method is not called for objects that don't use a block definition 
    in the worldDraw() implementation.

    \param pSubject [in]  A raw pointer to an entity.
  */
  virtual bool isContentSnappable(const OdTvDbEntity* pSubject);
};

/** \details
  This class overrules a subset of transformation linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.
  
  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbTransformOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbTransformOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbTransformOverrule();

  /** \details
    Overrules OdTvDbEntity::subTransformBy() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param xform [in]  Transformation matrix.
  */
  virtual OdResult transformBy(OdTvDbEntity* pSubject, const OdGeMatrix3d& xform);

  /** \details
    Overrules OdTvDbEntity::subGetTransformedCopy() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param xform [in]  A transformation matrix.
    \param pEnt [in/out] A reference to an empty pointer in which a pointer to the transformed copy of the entity should be saved.
  */
  virtual OdResult getTransformedCopy(const OdTvDbEntity* pSubject, const OdGeMatrix3d& xform, OdTvDbEntityPtr& pEnt);

  /** \details
    Overrules OdTvDbEntity::subExplode() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param entitySet [in/out] An array of pointers to new entities; this array can contain the pointers from other entities; 
                    all entities which are a result of the exploding operation are appended to this array.
  */
  virtual OdResult explode(const OdTvDbEntity* pSubject, OdRxObjectPtrArray& entitySet);

  /** \details
    Overrules OdTvDbEntity::subCloneMeForDragging() method and calls it in the default implementation.
    This method returns True when a clone will be created for the dragging operation, or False otherwise.

    \param pSubject [in]  A raw pointer to an entity.
  */
  virtual bool cloneMeForDragging(OdTvDbEntity* pSubject);

  /** \details
    Overrules OdTvDbEntity::subHideMeForDragging() method and calls it in the default implementation.
    This method returns True when the original object should be hidden during the dragging operation, 
    or False otherwise.

    \param pSubject [in]  A raw pointer to an entity.
  */
  virtual bool hideMeForDragging(const OdTvDbEntity* pSubject);
};

/** \details
  This class overrules a subset of grip linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.

  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGripOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbGripOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbGripOverrule();

  /** \details
    Overrules OdTvDbEntity::subGetGripPoints() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param gripPoints [in/out] An existing array to which the grip points should be appended.
  */
  virtual OdResult getGripPoints( const OdTvDbEntity* pSubject, OdGePoint3dArray& gripPoints );

  /** \details
    Overrules OdTvDbEntity::subGetGripPoints() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param gripsData [in] An array of pointers to dynamically allocated grip data objects. 
    \param curViewUnitSize [in] A size of one drawing unit in the current viewport (in pixels).
    \param gripSize [in] A size of current grip point (in pixels).
    \param curViewDir [in] A vector that specifies the view direction in the current viewport.
    \param bitFlags [in] Mask of one or more flags specified by the OdTvDbGripOperations::GetGripPointsFlags enumeration.
  */
  virtual OdResult getGripPoints(const OdTvDbEntity* pSubject, 
    OdDbGripDataPtrArray& gripsData,
    const double curViewUnitSize,
    const int gripSize,
    const OdGeVector3d& curViewDir,
    const int bitFlags );

  /** \details
    Overrules OdTvDbEntity::subMoveGripPointsAt() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param indices [in]  An array containing the indices corresponding to grip points obtained from 
                the getGripPoints() method that indicate which grip points are now "hot."
    \param offset [in] A vector that indicates the direction and magnitude which the grip points have been translated.
  */
  virtual OdResult moveGripPointsAt(OdTvDbEntity* pSubject, 
    const OdIntArray& indices,
    const OdGeVector3d& offset );

  /** \details
    Overrules OdTvDbEntity::subMoveGripPointsAt() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param grips [in] An array of pointers referring to each grip point to be moved.
    \param offset [in] A vector that indicates the direction and magnitude which the grip points have been translated.
    \param bitFlags [in] Mask of one or more flags specified by the OdTvDbGripOperations::GetGripPointsFlags enumeration.
  */
  virtual OdResult moveGripPointsAt(OdTvDbEntity* pSubject,
    const OdDbVoidPtrArray& grips,
    const OdGeVector3d& offset,
    int bitFlags );

  /** \details
    Overrules OdTvDbEntity::subGetStretchPoints() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param stretchPoints [in/out] An existing array to which the stretch points should be appended.
  */
  virtual OdResult getStretchPoints(const OdTvDbEntity* pSubject,
    OdGePoint3dArray& stretchPoints);

  /** \details
    Overrules OdTvDbEntity::subMoveStretchPointsAt() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param indices [in]  An array containing the indices that indicate which stretch points are being translated.
  */
  virtual OdResult moveStretchPointsAt(OdTvDbEntity* pSubject,
    const OdIntArray & indices,
    const OdGeVector3d& offset);

  /** \details
    Overrules OdTvDbEntity::subGripStatus() method and calls it in the default implementation.

    \param pSubject [in]  A raw pointer to an entity.
    \param status [in]  The status of the grip operation specified by the OdTvDbGripOperations::GripStatus enumeration.
  */
   virtual void gripStatus(OdTvDbEntity* pSubject, const OdDb::GripStat status);
};

/** \details
  This class overrules a subset of subentity linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.
    
  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbSubentityOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSubentityOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbSubentityOverrule();

  /** \details
    Overrules OdTvDbEntity::subDeleteSubentPaths() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param paths [in]  An array of full subentity path objects identifying the subentities to be deleted from the entity.
  */
  virtual OdResult deleteSubentPaths(OdTvDbEntity* pSubject, const OdTvDbFullSubentPathArray& paths);

  /** \details
    Overrules OdTvDbEntity::subAddSubentPaths() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param paths [in]  An array of full subentity path objects identifying the subentities to be added to the entity.
  */
  virtual OdResult addSubentPaths(OdTvDbEntity* pSubject, const OdTvDbFullSubentPathArray& paths);

  /** \details
    Overrules OdTvDbEntity::subTransformSubentPathsBy() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param paths [in]  An array of full subentity path objects identifying the subentities to be transformed.
    \param xform [in]  A transformation matrix to be applied to each subentity.
  */
  virtual OdResult transformSubentPathsBy(OdTvDbEntity* pSubject,
    const OdTvDbFullSubentPathArray& paths,
    const OdGeMatrix3d&            xform);

  /** \details
    Overrules OdTvDbEntity::subGetGripPointsAtSubentPath() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param path [in]  A full subentity path object identifying the subentity.
    \param grips [in]  An array of pointers to dynamically allocated grip data objects.
    \param curViewUnitSize [in]  A size of one drawing unit in the current viewport (in pixels).
    \param gripSize [in]  A size of current grip point (in pixels).
    \param curViewDir [in]  A vector that specifies the view direction in the current viewport.
    \param bitFlags [in]  Mask of one or more flags specified by the OdTvDbGripOperations::GetGripPointsFlags enumeration.
  */
  virtual OdResult getGripPointsAtSubentPath(
    const OdTvDbEntity*              pSubject,
    const OdTvDbFullSubentPath&      path,
    OdDbGripDataPtrArray&          grips,
    const double                   curViewUnitSize,
    const int                      gripSize,
    const OdGeVector3d&            curViewDir,
    const OdUInt32                 bitflags);

  /** \details
    Overrules OdTvDbEntity::subMoveGripPointsAtSubentPaths() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param paths [in]  An array of full subentity path objects identifying the subentities to be moved.
    \param gripAppData [in]  An array of pointers referring to each grip point to be moved.
    \param offset [in]  A vector that indicates the direction and magnitude of the translation to be applied to the grips.
    \param bitFlags [in]  Mask of one or more flags specified by the OdTvDbGripOperations::GetGripPointsFlags enumeration.
  */
  virtual OdResult moveGripPointsAtSubentPaths(
    OdTvDbEntity*                    pSubject,
    const OdTvDbFullSubentPathArray& paths,
    const OdDbVoidPtrArray&        gripAppData,
    const OdGeVector3d&            offset,
    const OdUInt32                 bitflags);

  /** \details
    Overrules the OdTvDbEntity::subGetSubentPathsAtGsMarker() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param type [in]  A subentity type specified by the OdDb::SubentType enumeration.
    \param gsMark [in]  GS marker representing a specific subentity.
    \param pickPoint [in]  WCS coordinates of the point picked during the selection of the entity.
    \param viewXform [in]  A transformation matrix to transform from WCS to DCS.
    \param subentPaths [out]  An array of full subentity path objects identifying the subentities generated from the GS marker.
    \param pEntAndInsertStack [in]  An array of object IDs that are the nested containers of the subentity.
  */
  virtual  OdResult getSubentPathsAtGsMarker(
    const OdTvDbEntity*      pSubject,
    OdDb::SubentType       type,
    OdGsMarker             gsMark, 
    const OdGePoint3d&     pickPoint,
    const OdGeMatrix3d&    viewXform, 
    OdTvDbFullSubentPathArray&   subentPaths, 
    const OdTvDbObjectIdArray* pEntAndInsertStack = 0);

  /** \details
    Overrules the OdTvDbEntity::subGetGsMarkersAtSubentPath() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param subPath [in]  A full subentity path object identifying the subentity.
    \param gsMarkers [out]   An array with GSMarkers for the subentities.
  */
  virtual  OdResult getGsMarkersAtSubentPath(
    const OdTvDbEntity*         pSubject,
    const OdTvDbFullSubentPath& subPath, 
    OdGsMarkerArray& gsMarkers);

  /** \details
    Overrules the OdTvDbEntity::subentPtr() method and calls it in the default implementation.
    This method returns a smart pointer to the subentity if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param id [in]  A full subentity path object identifying the subentity.
  */
  virtual OdTvDbEntityPtr subentPtr(const OdTvDbEntity* pSubject, const OdTvDbFullSubentPath& id);

  /** \details
    Overrules the OdTvDbEntity::subGetCompoundObjectTransform() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param xMat [out]  A transformation matrix to be filled for nested objects.
  */
  virtual OdResult getCompoundObjectTransform(const OdTvDbEntity* pSubject, OdGeMatrix3d & xMat);

  /** \details
    Overrules OdTvDbEntity::subGetSubentPathGeomExtents() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param path [in]  A full subentity path object identifying the subentity.
    \param extents [out]  An extents object in which subentity extents should be saved.
  */
  virtual OdResult getSubentPathGeomExtents(const OdTvDbEntity* pSubject,
    const OdTvDbFullSubentPath& path, 
    OdGeExtents3d& extents);

  /** \details
    Overrules OdTvDbEntity::subentGripStatus() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param status [in]  A status of the grip operation specified by the OdDb::GripStat enumeration.
    \param path [in]  A full subentity path object identifying the subentity whose grip status is to be changed.
  */
  virtual void subentGripStatus(OdTvDbEntity* pSubject, 
    OdDb::GripStat status,
    const OdTvDbFullSubentPath& subentity);

  /** \details
    Overrules OdTvDbEntity::subGetSubentClassId() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param path [in]  A full subentity path object identifying the subentity.
    \param clsId [out]  A pointer to the class description structure whose contents are set for the subentity.
  */
  virtual OdResult getSubentClassId(const OdTvDbEntity* pSubject,
    const OdTvDbFullSubentPath& path,
    void*                    clsId);
};

/** \details
  This class overrules a subset of highlight linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.
    
  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbHighlightOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbHighlightOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbHighlightOverrule();

  /** \details
    Overrules OdTvDbEntity::subHighlight() method and calls it in the default implementation.

    \param pSubject [in]  A raw pointer to an entity.
    \param bDoIt [in]  Indicates whether to highlight.
    \param pSubId [in]  A full subentity path that identifies the subentity to be highlighted.
    \param highlightAll [in]  Indicates whether to highlight in all viewports.
  */
  virtual void highlight(const OdTvDbEntity* pSubject, bool bDoIt = true, const OdTvDbFullSubentPath* pSubId = 0,
    bool highlightAll = false);
};

/** \details
  This class overrules a subset of visibility linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.

  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbVisibilityOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbVisibilityOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbVisibilityOverrule();

  /** \details
    Overrules OdTvDbEntity::subVisibility() method and calls it in the default implementation.
    This method returns the visibility state of the object as the OdDb::Visibility enumeration.

    \param pSubject [in]  A raw pointer to an entity.
  */
  virtual OdDb::Visibility visibility(const OdTvDbEntity* pSubject);

  /** \details
    Overrules OdTvDbEntity::subSetVisibility() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param visibility [in]  A visibility state as the OdDb::Visibility enumeration.
    \param doSubents [in]  Indicates whether the new value should be applied to the subentitites.
  */
  virtual OdResult setVisibility(OdTvDbEntity* pSubject, OdDb::Visibility visibility, bool doSubents = true);
};

/** \details
  This class overrules a subset of geometry linked operations which an entity specifies. 
  It is used as a base class for classes derived from OdTvDbEntity to change their behavior. 
  Each default implementation calls the corresponding method of the target class.
    
  Corresponding C++ library:  TD_Db
  <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGeometryOverrule : public OdRxOverrule
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbGeometryOverrule);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbGeometryOverrule();

  /** \details
    Overrules OdTvDbEntity::subIntersectWith() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pThisEnt [in]  A raw pointer to an entity.
    \param pEnt [in]  An entity with which this entity is intersected.
    \param intType [in]  Type of intersection.
    \param points [out]  An array of points in which the intersection points should be appended.
    \param thisGsMarker [in]  GS marker of the subentity of this entity which is involved in the intersection.
    \param otherGsMarker [in]  GS marker of the subentity of the entity pointed to by pEnt which is involved in the intersection.
  */
  virtual OdResult intersectWith(const OdTvDbEntity* pThisEnt,
    const OdTvDbEntity* pEnt, OdDb::Intersect intType,
    OdGePoint3dArray& points, OdGsMarker thisGsMarker = 0,
    OdGsMarker otherGsMarker = 0);
  /** \details
    Overrules OdTvDbEntity::subIntersectWith() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pThisEnt [in]  A raw pointer to an entity.
    \param pEnt [in]  An entity with which this entity is intersected.
    \param intType [in]  Type of intersection.
    \param projPlane [in]  A projection plane for the intersection of the two entities.
    \param points [out]  An array of points in which the intersection points should be appended.
    \param thisGsMarker [in]  GS marker of the subentity of this entity which is involved in the intersection.
    \param otherGsMarker [in]  GS marker of the subentity of the entity pointed to by pEnt which is involved in the intersection.
  */
  virtual OdResult intersectWith(const OdTvDbEntity* pThisEnt,
    const OdTvDbEntity* pEnt, OdDb::Intersect intType,
    const OdGePlane& projPlane, OdGePoint3dArray& points,
    OdGsMarker thisGsMarker = 0, OdGsMarker otherGsMarker = 0);

  /** \details
    Overrules OdTvDbEntity::subGetGeomExtents() method and calls it in the default implementation.
    This method returns eOk if successful.

    \param pSubject [in]  A raw pointer to an entity.
    \param extents [out]  An extents object in which entity extents should be saved.
  */
  virtual OdResult getGeomExtents(const OdTvDbEntity* pSubject, OdGeExtents3d& extents);
};

#endif //_DBENTITYOVRRULE_H_INCLUDED_

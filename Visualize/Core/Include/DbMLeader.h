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

#ifndef OD_MLEADER_H
#define OD_MLEADER_H

#include "TD_PackPush.h"
#include "DbMLeaderStyle.h"
#include "DbEntity.h"
#include "DbSubentId.h"
#include "DbAttribute.h"
#include "IntArray.h"

#define MAX_LEADER_NUMBER     5000
#define MAX_LEADERLINE_NUMBER 5000

class OdTvDbAttribute;
class OdTvDbMLeaderObjectContextData;

/** \details
    This class is the main class used for the multiple leader (MLeader) objects. 
        
    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbMLeader : public OdTvDbEntity
{
public:
  /** \details
    Enumeration for MLeader move type.
  */
  enum MoveType {
    /** \details
      All MLeader points should be moved.
    */
    kMoveAllPoints,

    /** \details
      All MLeader points should be moved, except the arrowhead points of the leader line.
    */
    kMoveAllExceptArrowHeaderPoints,

    /** \details
      MLeader content points and dog-leg points should be moved.
    */
    kMoveContentAndDoglegPoints
  };

  /** \details
    Enumeration for MLeader GS mark type.
  */
  enum gsMarkType {
    /** \details
      No GS mark.
    */
    kNone               = 0,

    /** \details
      GS mark of arrow.
    */
    kArrowMark          = 1,

    /** \details
      GS mark of leader line.
    */
    kLeaderLineMark     = kArrowMark  + MAX_LEADERLINE_NUMBER,

    /** \details
      GS mark of dog-leg.
    */
    kDoglegMark         = kLeaderLineMark + MAX_LEADERLINE_NUMBER,

    /** \details
      GS mark of MText content.
    */
    kMTextMark          = kDoglegMark + MAX_LEADER_NUMBER,

    /** \details
      GS mark of MText underline content (includes text frame if present).
    */
    kMTextUnderLineMark = kMTextMark + 1,

    /** \details
      GS mark of tolerance content.
    */
    kToleranceMark      = kMTextUnderLineMark + 1,

    /** \details
      GS mark of block content.
    */
    kBlockMark          = kToleranceMark + 1,

    /** \details
      GS mark of block attribute content.
    */
    kBlockAttribute     = kBlockMark + 1
  };

  /** \details
      Enumeration for MLeader properties which can be overridden.
  */
  enum PropertyOverrideType {
    /** \details
      Leader line type.
    */
    kLeaderLineType         = 0,

    /** \details
      Leader line color.
    */
    kLeaderLineColor        = 1,

    /** \details
      Leader line type ID.
    */
    kLeaderLineTypeId       = 2,

    /** \details
      Leader line weight.
    */
    kLeaderLineWeight       = 3,

    /** \details
      Enable landing.
    */
    kEnableLanding          = 4,

    /** \details
      Landing gap.
    */
    kLandingGap             = 5,

    /** \details
      Enable dog-leg.
    */
    kEnableDogleg           = 6,

    /** \details
      Dog-leg length.
    */
    kDoglegLength           = 7,

    /** \details
      Arrow symbol ID.
    */
    kArrowSymbolId          = 8,

    /** \details
      Arrow symbol size.
    */
    kArrowSize              = 9,

    /** \details
      MLeader content type.
    */
    kContentType            = 10,

    /** \details
      Text style ID (of MText).
    */
    kTextStyleId            = 11,

    /** \details
      Text left attachment type (of MText).
    */
    kTextLeftAttachmentType = 12,

    /** \details
      Text angle type (of MText).
    */
    kTextAngleType          = 13,

    /** \details
      Text alignment type (of MText).
    */
    kTextAlignmentType      = 14,

    /** \details
      Text color (of MText).
    */
    kTextColor              = 15,

    /** \details
      Text height (of MText).
    */
    kTextHeight             = 16,

    /** \details
      Enable text frame.
    */
    kEnableFrameText        = 17,

    /** \details
      Enable use of default MText (from MLeaderStyle).
    */
    kDefaultMText           = 18,

    /** \details
      Block content block ID.
    */
    kBlockId                = 19,

    /** \details
      Block content color.
    */
    kBlockColor             = 20,

    /** \details
      Block content scale.
    */
    kBlockScale             = 21,

    /** \details
      Block content rotation.
    */
    kBlockRotation          = 22,

    /** \details
      Block content connection type.
    */
    kBlockConnectionType    = 23,

    /** \details
      MLeader scale.
    */
    kScale                  = 24,

    /** \details
      Text right attachment type (of MText).
    */
    kTextRightAttachmentType = 25,

    /** \details
      Text switch alignment type (of MText).
    */
    kTextSwitchAlignmentType = 26,

    /** \details
      Text attachment direction (of MText).
    */
    kTextAttachmentDirection = 27,

    /** \details
      Text top attachment type (of MText).
    */
    kTextTopAttachmentType   = 28,

    /** \details
      Text bottom attachment type (of MText).
    */
    kTextBottomAttachmentType = 29,

    /** \details
      Extend leader line to text.
    */
    kExtendLeaderToText      = 30,

    /** \details
      Size of bit set.
    */
    kSize = kExtendLeaderToText + 1
  };


  ODDB_DECLARE_MEMBERS(OdTvDbMLeader);

  OdTvDbMLeader();

  virtual OdResult dwgInFields (OdTvDbDwgFiler* filer) ODRX_OVERRIDE;

  virtual void dwgOutFields(OdTvDbDwgFiler* filer) const ODRX_OVERRIDE;

  virtual OdResult dxfInFields (OdTvDbDxfFiler* filer) ODRX_OVERRIDE;

  virtual void dxfOutFields(OdTvDbDxfFiler* filer) const ODRX_OVERRIDE;

protected:
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const ODRX_OVERRIDE;

  virtual void  subViewportDraw(OdGiViewportDraw* mode) const ODRX_OVERRIDE;

  virtual OdResult subTransformBy(const OdGeMatrix3d& xform) ODRX_OVERRIDE;

  virtual OdResult subMoveGripPointsAt(const OdIntArray& indices, const OdGeVector3d& offset);

  /** \details
	Returns all subentity paths by graphic system marker.

	\param type [in]  The subentity type being queried. ( Only OdDb::kClassSubentType )
	\param gsMarker [in]  The GS marker of the subentity being queried.
	\param pickPoint [in]  The WCS point being queried. ( Not used )
	\param xrm [in]  The WCS->DCS transformation matrix. ( Not used )
	\param subentPaths [out] The array of OdTvDbFullSubentPath objects.
	\param entAndInsertStack [in] The array of objectIds of the objects that are the nested containers of the subentity.
  */

  virtual OdResult subGetSubentPathsAtGsMarker(OdDb::SubentType type, OdGsMarker gsMark, 
										const OdGePoint3d& pickPoint,const OdGeMatrix3d& xfm, 
										OdTvDbFullSubentPathArray& subentPaths, 
										const OdTvDbObjectIdArray* pEntAndInsertStack = 0) const ODRX_OVERRIDE;

  /** \details
	Returns all graphic system marker by subentity paths.

	\param subPath [in]  The OdTvDbFullSubentPath to the subentity.
	\param gsMarkers [in/out] The array of integer identifiers (GS markers).
  */

  virtual OdResult subGetGsMarkersAtSubentPath( const OdTvDbFullSubentPath& subPath, 
											 OdGsMarkerArray& gsMarkers) const ODRX_OVERRIDE;

  /** \details
	Deletes one or more subentities from an entity.

	\param paths [in]  The array of OdTvDbFullSubentPath objects.
  */

  virtual OdResult subDeleteSubentPaths(const OdTvDbFullSubentPathArray& paths) ODRX_OVERRIDE;

  /** \details
	Create an object by OdTvDbFullSubentPath to the subentity.

	\param path [in]  The OdTvDbFullSubentPath to the subentity.
  */

  virtual OdTvDbEntityPtr subSubentPtr(const OdTvDbFullSubentPath& path) const ODRX_OVERRIDE;

  virtual void subClose() ODRX_OVERRIDE;

  virtual OdResult subExplode(OdRxObjectPtrArray& entitySet) const ODRX_OVERRIDE;

  virtual OdResult subGetGeomExtents(OdGeExtents3d& extents) const ODRX_OVERRIDE;

  /*virtual OdResult subGetClassID(
    void* pClsid) const ODRX_OVERRIDE;*/

//#if 0
////////////////////////////////////////////////////////////////////////////////
//
//  virtual OdResult getGripEntityUCS(
//    const void* pGripAppData,
//    OdGeVector3d& normalVec,
//    OdGePoint3d& origin,
//    OdGeVector3d& xAxis) const;
//
//  virtual void  gripStatus(
//    const OdDb::GripStat status);
//
///////////////////////////////////////////////////////////////////////////////////
//#endif

  virtual OdResult subGetTransformedCopy(
    const OdGeMatrix3d& xform,
    OdTvDbEntityPtr& pEnt) const;


public:
  /** \details
    Sets the override status for the specified PropertyOverrideType.

    \param propertyType [in]  PropertyOverrideType which will be set.
    \param isOverride [in]  true if an override for propertyType is to be set, false otherwise.
  */
  void setOverride(
    PropertyOverrideType propertyType,
    bool isOverride = true);

  /** \details
    Returns the override status for the specified PropertyOverrideType.

    \param propertyType [in]  PropertyOverrideType for which status is to be returned.

    \returns
    Returns true if an override has been set for the specified propertyType, false otherwise.
  */
  bool  isOverride(
    PropertyOverrideType propertyType) const;

  /** \details
    Sets the MLeader scale, which affects arrowhead size and content scale.

    \param scale [in]  The scale value.

    \returns
    Returns eOk if successful.  Note that this function will set an override 
    for kScale PropertyOverrideType.
  */
  OdResult setScale(
    double scale);

  /** \details
    Returns the MLeader scale, which affects arrowhead size and content scale.

  */
  double  scale() const;

  /** \details
    Returns the specified attribute from the associated block content.

    \param attdefId [in]  ObjectID of an attribute definition.
    \param pAtt [out]  Returned attribute object corresponding to attdefId.

    \remarks
    If successful, returns eOk.
  */
  OdResult getBlockAttributeValue(
    OdTvDbObjectId attdefId,
    OdTvDbAttributePtr& pAtt) const;

  /** \details
    Sets the specified attribute within associated block content.

    \param attdefId [in]  ObjectID of attribute definition.
    \param pAtt [in]  Attribute object pointer.

    \returns
    Returns eOk if successful.
  */
  OdResult setBlockAttributeValue(
    OdTvDbObjectId attdefId,
    const OdTvDbAttribute* pAtt);

  /** \details
    Returns the WCS plane containing this MLeader object.
  */
  OdGePlane plane() const;

  /** \details
    Sets the WCS plane containing this MLeader object.

    \param plane [in]  Place which will contain the MLeader.

    \remarks
    Note that MLeader geometry will be updated appropriately to reflect the new location.
  */
  void  setPlane(
    const OdGePlane& plane);

  OdGeVector3d  normal() const;

  /** \details
    Moves this MLeader object as specified by an input vector.

    \param vector [in] Vector which specifies the direction and distance of the move.
    \param moveType [in] Indicates how to move the MLeader.
    \param bAutoSwitchDogleg [in] If true, automatically switch leader lines after movoing the MLeader.

    \returns
    Returns eOk if successful.
  */
  OdResult moveMLeader(
    const OdGeVector3d& vector,
    MoveType moveType,
    bool bAutoSwitchDogleg = true);

  /** \details
    Returns the the extents of the content for this MLeader.

    \param extents [out]  Receives the content extents.

    \returns
    Returns eOk if successful.
  */
  OdResult getContentGeomExtents(
    OdGeExtents3d& extents) const;

  // Deprecated (Instead, use the method getLeaderIndexes(...))
  int numLeaders();

  /** \details

    \param leaderIndexes [out]  Returned indexes.
  */
  void getLeaderIndexes(
    OdIntArray& leaderIndexes);

  /** \details
    Causes a new cluster to be added to this MLeader object, and returns the index of the new cluster.

    \param leaderIndex [out]  Index of newly added cluster.

    \remarks
    A leader cluster consists of a dog-leg and leader lines.
  */
  void addLeader(
    int& leaderIndex);

  /** \details
    Removes the leader cluster specified by the passed-in index.

    \param leaderIndex [in]  Index of the cluster to be removed.

    \remarks
    A leader cluster consists of a dog-leg and leader lines.
  */
  void removeLeader(
    int leaderIndex);

  // Deprecated (Instead, use the method getLeaderLineIndexes(...))
  int numLeaderLines();

  /** \details
    Returns the indexes of all leader lines for this MLeader object.
    \param leaderIndexes [out]  Receives the indexes of leader lines for this MLeader.
  */
  void getLeaderLineIndexes(
    OdIntArray& leaderLineIndexes);

  /** \details
    Adds a leader line to the leader cluster specified by the supplied index.

    \param leaderIndex [in]  Leader cluster index.
    \param leaderLineIndex [out]  Receives the index of the newly added leader line.
  */
  OdResult addLeaderLine(
    int leaderIndex, 
    int& leaderLineIndex);

  /** \details
    Adds a new leader line to this MLeader.  The first point of the new leader line is passed in.

    \param point [in]  Specifies the first point of the new leader line.
    \param leaderLineIndex [out]  Receives the index of the newly added leader line.

    \returns
    Returns eOk if successful. 
  */
  OdResult addLeaderLine(
    const OdGePoint3d& point, 
    int& leaderLineIndex);

  /** \details
    Removes the leader line specified by the passed-in index.

    \param leaderLineIndex [in]  Index of the leader line to remove.

    \remarks
    Note that removal of all leader lines will cause the leader cluster to be removed as well.
  */
  void removeLeaderLine(
    int leaderLineIndex);

  /** \details
    Inserts a new first vertex into the specified leader line.

    \param leaderLineIndex [in]  Index of the leader line to which the vertex will be added.
    \param point [in]  The position of the vertex.
  */
  OdResult addFirstVertex(
    int leaderLineIndex, const OdGePoint3d& point);

  /** \details
    Removes the first vertex from the specified leader line.

    \param leaderLineIndex [in]  Index of the leader line from which the first vertex will be removed.

    \returns
    Returns eOk if successful.
  */
  OdResult removeFirstVertex(
    int leaderLineIndex);

  /** \details
    Returns the first vertex from the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param point [out]  Receives the first vertex.

    \returns
    Returns eOk if successful.
  */
  OdResult getFirstVertex(
    int leaderLineIndex, 
    OdGePoint3d& point) const;

  /** \details
    Sets the first vertex of the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param point [in]  New position for the first vertex.

    \remarks
    Note that this function only sets the values for an existing 
    first vertex, but does not create any new vertices.
    
    \returns
    Returns eOk if successful.  
  */
  OdResult setFirstVertex(
    int leaderLineIndex, 
    const OdGePoint3d& point);

  /** \details
    Appends a new last vertex onto the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param point [in]  The new vertex position.

    \returns
    Returns eOk if successful.
  */
  OdResult addLastVertex(
    int leaderLineIndex,
    const OdGePoint3d& point);

  /** \details
    Removes the last vertex from the specified leader line.

    \param leaderLineIndex [in]  Leader line index.

    \returns
    Returns eOk if successful.
  */
  OdResult removeLastVertex(
    int leaderLineIndex);

  /** \details
    Returns the last vertex from the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param point [out]  Receives the last vertex from the specified leader line.

    \returns
    Returns eOk if successful.
  */
  OdResult getLastVertex(
    int leaderLineIndex,
    OdGePoint3d& point) const;

  /** \details
    Sets the last vertex of the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param point [in]  New last vertex for specified leader line.
    
    \returns
    Returns eOk if successful.
  */
  OdResult setLastVertex(
    int leaderLineIndex,
    const OdGePoint3d& point);

  /** \details
    Returns the number of vertices in the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param num [out]  Receives the number of vertices in the specified leader line.

    \returns
    Returns eOk if successful.
  */
  OdResult numVertices(
    int leaderLineIndex, 
    int& num) const;

  /** \details
    Sets the position for a specified vertex in a specified leader line. 

    \param leaderLineIndex [in]  Leader line index.
    \param index [in]  The index of the vertex to be set.
    \param point [in]  New coordinate value for the specified vertex.

    \returns
    Returns eOk if successful.
  */
  OdResult setVertex(
    int leaderLineIndex,
    int index,
    const OdGePoint3d& point);

  /** \details
    Returns the position of a specified vertex in a specified leader line. 

    \param leaderLineIndex [in]  Leader line index.
    \param index [in]  The index of the vertex.
    \param point [out]  Receives the position value for the specified vertex.
    
    \returns
    Returns eOk if successful.
  */
  void getVertex(
    int leaderLineIndex,
    int index, OdGePoint3d& point) const;

  /** \details
    Returns the index of the leader cluster which contains the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param leaderIndex [out]  Receives the index of the lead line owner.
  */
  void getLeaderIndex(
    int leaderLineIndex,
    int& leaderIndex); 

  /** \details
    Returns the indexes of all leader lines for the specified leader.

    \param leaderIndex [in]  Leader index.
    \param leaderLineIndexes [out]  Receives the indexes of the owned leader lines.
  */
  void getLeaderLineIndexes(
    int leaderIndex,
    OdIntArray& leaderLineIndexes);

  /** \details
    Sets the dog-leg direction for the specified leader cluster.

    \param leaderIndex [in]  Leader index.
    \param vector [in]  The new dog-leg direction.
  */
  void setDoglegDirection(
    int leaderIndex,
    const OdGeVector3d& vector);

  /** \details
    Returns the dog-leg direction for the specified leader cluster.

    \remarks
    \param leaderIndex [in] Leader index.
    \param vector [out] Receives the dog-leg direction.
  */
  void getDoglegDirection(
    int leaderIndex,
    OdGeVector3d& vector);

  /** \details
    Sets the leader line type for this MLeader object.

    \param leaderLineType [in]  Leader line type. 

    \remarks
    The kLeaderLineType PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineType(
    OdTvDbMLeaderStyle::LeaderType leaderLineType);

  /** \details
    Returns the leader line type for this MLeader object.
  */
  OdTvDbMLeaderStyle::LeaderType  leaderLineType() const;

  /** \details
    Sets the leader line color for this MLeader.

    \param leaderLineColor [in]  Leader line color.

    \remarks
    The kLeaderLineColor PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineColor(
    const OdTvCmColor& leaderLineColor);

  /** \details
    Returns the leader line color for this MLeader.
  */
  OdTvCmColor leaderLineColor() const;

  /** \details
    Sets the leader line linetype for this MLeader by OdTvDbObjectId.

    \param leaderLineTypeId [in]  Leader line type ObjectId.

    \remarks
    The kLeaderLineTypeId PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineTypeId(
    OdTvDbObjectId leaderLineTypeId);

  /** \details
    Returns the leader line linetype for this MLeader by OdTvDbObjectId.
  */
  OdTvDbObjectId  leaderLineTypeId() const;

  /** \details
    Sets the leader line weight for this MLeader.

    \param leaderLineWeight [in]  Leader line weight.

    \remarks
    The kLeaderLineWeight PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineWeight(
    OdDb::LineWeight leaderLineWeight);

  /** \details
    Returns the leader line weight for this MLeader.
  */
  OdDb::LineWeight  leaderLineWeight() const;

  /** \details
    Sets the landing gap for this MLeader (gap between the leader tail and associated MText).

    \param landingGap [in]  Landing gap (gap between the leader tail and associated MText).

    \remarks
    The kLandingGap PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLandingGap(
    double landingGap);

  /** \details
    Returns the landing gap for this MLeader (gap between the leader tail and associated MText).
  */
  double  landingGap() const;

  /** \details
    Sets the enabled/disabled status for leader landing line.

    \param enableLanding [in]  Leader landing line enabled status.

    \remarks
    The kEnableLanding PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setEnableLanding(
    bool enableLanding);

  /** \details
    Returns the enabled/disabled status for leader landing line.
  */
  bool  enableLanding() const;

  /** \details
    Sets the enabled/disabled status for dog-leg leader line.

    \param enableDogleg [in]  Leader dog-leg line enabled status.

    \remarks
    The kEnableDogleg PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setEnableDogleg(
    bool enableDogleg);

  /** \details
    Returns the enabled/disabled status for dog-leg leader line.
  */
  bool  enableDogleg() const;

  /** \details
    Sets the length for the dog-leg of the specified leader cluster.

    \param leaderIndex [in]  Leader index.
    \param dDoglegLength [in]  Dog-leg length.

    \remarks
    The kDoglegLength PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setDoglegLength(
    int leaderIndex,
    double dDoglegLength);

  /** \details
    Returns the length for the dog-leg of the specified leader cluster.

    \param leaderIndex [in] Leader index.
  */
  double doglegLength(
    int leaderIndex );

  //deprecated 
  OdResult    setDoglegLength        (double doglegLength);
  //deprecated 
  double      doglegLength           () const;

  /** \details
    Sets the arrow symbol for this MLeader (by ObjectId).

    \param arrowSymbolId [in]  Arrow symbol ObjectId.

    \remarks
    The kDoglegLength PropertyOverrideType override will be set as a result of
    calling this function.  If this value is not set, the default arrow symbol 
    will be used.
  */
  void setArrowSymbolId(
    OdTvDbObjectId arrowSymbolId);

  /** \details
    Returns the arrow symbol for this MLeader (by ObjectId).
  */
  OdTvDbObjectId  arrowSymbolId() const;

  /** \details
    Sets the arrow size for this MLeader object.

    \param arrowSize [in]  Arrow size.

    \remarks
    The kArrowSize PropertyOverrideType override will be set as a result of
    calling this function.  
  */
  void setArrowSize(
    double arrowSize);

  /** \details
    Returns the arrow size for this MLeader object.
  */
  double  arrowSize() const;

  /** \details
    Sets the content type for this MLeader object.

    \param contentType [in]  Content type.

    \remarks
    The kContentType PropertyOverrideType override will be set as a result of
    calling this function.  
  */
  void setContentType(
    OdTvDbMLeaderStyle::ContentType contentType);

  /** \details
    Returns the content type for this MLeader object.
  */
  OdTvDbMLeaderStyle::ContentType contentType() const;

  /** \details
    Sets the textstyle used by MText content (by ObjectId).

    \param textStyleId [in]  OdTvDbTextStyle ObjectId.

    \remarks
    The kTextStyleId PropertyOverrideType override will be set as a result of
    calling this function.  
  */
  void setTextStyleId(
    OdTvDbObjectId textStyleId);

  /** \details
    Return the textstyle used by MText content (by ObjectId).
  */
  OdTvDbObjectId  textStyleId() const;

  /** \details
    Sets the text attachment type used by MText content.

    \param textAttachmentType [in]  Text attachment type.
    \param leaderDirection [in]  Text leader direction type.

    \remarks
    The kTextLeftAttachmentType/kTextRightAttachmentType PropertyOverrideType override 
    will be set as a result of calling this function.  
  */
  void setTextAttachmentType(
      OdTvDbMLeaderStyle::TextAttachmentType textAttachmentType,
      OdTvDbMLeaderStyle::LeaderDirectionType leaderDirection);

  /** \details
    Returns the text attachment type used by MText content.

    \param leaderDirection [in]  Text leader direction type.
  */
  OdTvDbMLeaderStyle::TextAttachmentType  textAttachmentType(
      OdTvDbMLeaderStyle::LeaderDirectionType leaderDirection) const;

  /** \details
    Sets the angle type for MText content, with respect to the last leader line segment.

    \param textAngleType [in]  Text text angle type.

    \remarks
    The kTextAngleType PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setTextAngleType(
    OdTvDbMLeaderStyle::TextAngleType textAngleType);

  /** \details
    Returns the angle type for MText content, with respect to the last leader line segment.
  */
  OdTvDbMLeaderStyle::TextAngleType textAngleType() const;

  /** \details
    Sets the text alignment type for MText content.

    \param textAlignmentType [in]  Text alignment type.

    \remarks
    The kTextAlignmentType PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setTextAlignmentType(
    OdTvDbMLeaderStyle::TextAlignmentType textAlignmentType);

  /** \details
    Returns the text alignment type for MText content.
  */
  OdTvDbMLeaderStyle::TextAlignmentType textAlignmentType() const;

  /** \details
    Sets the text color for MText content.

    \param textColor [in]  Text color.

    \remarks
    The kTextColor PropertyOverrideType override will be set as a result 
    of calling this function.
  */
  void setTextColor(const OdTvCmColor& textColor);

  /** \details
    Returns the text color for MText content.
  */
  OdTvCmColor textColor() const;

  /** \details
    Sets the text height for MText content.

    \param textHeight [in]  Text height.

    \remarks
    The kTextHeight PropertyOverrideType override will be set as a result 
    of calling this function.
  */
  void setTextHeight(
    double textHeight);

  /** \details
    Returns the text height for MText content.
  */
  double  textHeight() const;

  /** \details
    Sets the text frame visibility for MText content.

    \param enableFrameText [in]  True to enable the text frame, false otherwise.

    \remarks
    The kEnableFrameText PropertyOverrideType override will be set as a result 
    of calling this function.
  */
  void setEnableFrameText(
    bool enableFrameText);

  /** \details
    Returns the text frame visibility for MText content.
  */
  bool  enableFrameText() const;

  /** \details
    Sets the MText object to be associated with this MLeader.

    \param pMText [in]  The MText object to associate with this MLeader (if NULL, 
      the default MText defined in the associated MLeaderStyle is used).

    \remarks
    The kDefaultMText PropertyOverrideType override will be set as a result 
    of calling this function.  The supplied MText object can be DBR or non-DBR.
  */
  void setMText(
    const OdTvDbMText* pMText);

  /** \details
    Returns the MText content associated with this MLeader.
  */
  OdTvDbMTextPtr mtext() const;

  /** \details
    Sets the referenced block for this MLeader, by block ObjectId.

    \param blockId [in]  Block table record ObjectId.

    \remarks
    The kBlockId PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setBlockContentId(
    OdTvDbObjectId blockId);

  /** \details
    Returns the referenced block for this MLeader, by block ObjectId.
  */
  OdTvDbObjectId  blockContentId() const;

  /** \details
    Sets the color used for block content.

    \param blockColor [in]  Block color.

    \remarks
    The kBlockColor PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setBlockColor(
    const OdTvCmColor& blockColor);

  /** \details
    Returns the color used for block content.
  */
  OdTvCmColor blockColor() const;

  /** \details
    Sets the scale used by the referenced block.

    \param scale [in]  Referenced block scale.

    \remarks
    The kBlockScale PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setBlockScale(
    const OdGeScale3d& scale);

  /** \details
    Returns the scale used by the referenced block.
  */
  OdGeScale3d blockScale() const;

  /** \details
    Sets the rotation used by the referenced block.

    \param rotation [in]  Referenced block rotation.

    \remarks
    The kBlockRotation PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setBlockRotation(
    double rotation);

  /** \details
    Returns the rotation used by the referenced block.
  */
  double blockRotation() const;

  /** \details
    Sets the block connection type for this MLeader, which specifies how the 
    referenced block is connected to the leader lines.

    \param blockConnectionType [in]  Block connection type.

    \remarks
    The kBlockConnectionType PropertyOverrideType override will be set as a result 
    of calling this function.  
  */
  void setBlockConnectionType(
    OdTvDbMLeaderStyle::BlockConnectionType blockConnectionType);

  /** \details
    Returns the block connection type for this MLeader, which specifies how the 
    referenced block is connected to the leader lines.
  */
  OdTvDbMLeaderStyle::BlockConnectionType blockConnectionType() const;

  /** \details
    Sets the annotation scale enabled status for this MLeader.

    \param enableAnnotationScale [in]  true if annotation scale is to be enabled, false otherwise.
  */
  void setEnableAnnotationScale(
    bool enableAnnotationScale);

  /** \details
    Returns the annotation scale enabled status for this MLeader.
  */
  bool  enableAnnotationScale() const;

  /** \details
    Sets the MLeaderStyle used for this MLeader, by ObjectId.

    \param newStyleId [in]  New MLeaderStyle.
  */
  void setMLeaderStyle(
    OdTvDbObjectId newStyleId);

  /** \details
    Returns the MLeaderStyle used for this MLeader, by ObjectId.
  */
  OdTvDbObjectId  MLeaderStyle();

  /** \details
    Returns the property set for the MLeader, including override values.

    \param mleaderStyle [out]  Receives the properties of this MLeader.

    \returns
    Returns eOk if successful. 
  */
  OdResult getOverridedMLeaderStyle(
    OdTvDbMLeaderStyle& mleaderStyle);

  /** \details
    Sets the context data manager for this MLeader object.

    \param pContextDataManager [in]  Pointer to a context data manager.

    \returns
    Returns eOk if successful.
  */
  OdResult setContextDataManager(
    void* pContextDataManager);

  /** \details
    Returns the context data manager for this MLeader object.
  */
  void* getContextDataManager() const;

  /** \details
    Sets the position for the block referenced by this MLeader.

    \param position [in]  Block position.
  */
  void setBlockPosition(
    const OdGePoint3d& position);

  /** \details
    Returns the position for the block referenced by this MLeader.

    \param position [out]  Receives the block position.
  */
  void getBlockPosition(
    OdGePoint3d& position);

  /** \details
    Sets the location for the MText content associated with this MLeader.

    \param location [in]  MLeader mtext location.
  */
  void setTextLocation(
    const OdGePoint3d& location);

  /** \details
    Returns the location for the MText content associated with this MLeader.
  
    \param location [out]  Receives the MText location.
  */
  void getTextLocation(
    OdGePoint3d& location);

  /** \details
    Sets the location for MLeader tolerance content.

    \param location [in]  MLeader tolerance content location

    \returns
    Returns eOk if successful.
  */
  OdResult setToleranceLocation(
    const OdGePoint3d& location);

  /** \details
    Returns the location for MLeader tolerance content.

    \param location [out]  Receives the MLeader tolerance content location.

    Returns eOk if successful.
  */
  OdResult getToleranceLocation(
    OdGePoint3d& location) const;

  /** \details
    Sets the arrow head symbol for a specified leader line, by ObjectId.

    \param leaderLineIndex [in]  Leader line index.
    \param arrowSymbolId [in]  Arrow symbol ObjectId.

    \returns
    Returns eOk if successful.
  */
  void setArrowSymbolId(
    int leaderLineIndex,
    OdTvDbObjectId arrowSymbolId);

  /** \details
    Returns the arrow head symbol for a specified leader line, by ObjectId.

    \param leaderLineIndex [in]  Leader line index.
  */
  OdTvDbObjectId  arrowSymbolId(
    int leaderLineIndex) const;

  /** \details
    Returns true if this MLeader has content, false otherwise.
  */
  bool  hasContent() const;

  /** \details
    Returns the connection point of this MLeader, for the speciefied direction.

    \param vect [in]  The specified direction.
    \param point [out]  Receives the connection point.
  */
  OdResult connectionPoint(
    const OdGeVector3d& vect,
    OdGePoint3d& point) const;

  /** \details
  Returns the connection point of this MLeader, for the speciefied direction.

  \param vect [in]  The specified direction.
  \param point [out]  Receives the connection point.
  direction  The text attachment direction of MText. (Horizontally by default).  
  */
  OdResult connectionPoint(
    const OdGeVector3d& vect,
    OdGePoint3d& point,
    OdTvDbMLeaderStyle::TextAttachmentDirection direction) const;

  /** \details
    Recomputes the dimension break points.

    \returns
    Returns eOk if successful.
  */
    OdResult recomputeBreakPoints();

  /** \details
    Adds this MLeader object to the Model Space block of the specified database.

    \param pDb [in]  Database to which this MLeader object should be added.

    \returns
    Returns eOk if successful.
  */
  OdResult postMLeaderToDb(
    OdTvDbDatabase* pDb);

  // dim associativity support

  /** \details
    Updates leader line positions.

    \returns
    Returns eOk if successful.
  */
  OdResult updateLeaderLinePosition();

  /** \details
    Removes the specified leader line's geometry association.

    \param leaderLineIndex [in]  Leader line index.

    \returns
    Returns eOk if successful.
  */
  OdResult removeLeaderLineRefAssoc(
    int leaderLineIndex) const;

  /** \details
    Updates this MLeaders's arrow head, landing gap, dog-leg length, and text height or block scale.

    \param pContext [in]  MLeader context data.

    \returns
    Returns eOk if successful.
  */
  OdResult updateContentScale(
    OdTvDbMLeaderObjectContextData* pContext);

  virtual bool isPlanar() const ODRX_OVERRIDE;
  virtual OdResult getPlane(OdGePlane& plane, OdDb::Planarity& planarity) const ODRX_OVERRIDE;

  /** \details
    Sets the text attachment direction of MText.

    \param direction [in]  The text attachment direction of MText.
  */
  void setTextAttachmentDirection(
    OdTvDbMLeaderStyle::TextAttachmentDirection direction);

  /** \details
    Returns the text attachment direction of MText.
  */
  OdTvDbMLeaderStyle::TextAttachmentDirection textAttachmentDirection() const;

  /** \details
      Enumeration of the individual leader line properties which can be overridden.
  */
  enum LeaderLineOverrideType
  {
    /** \details
      Leader line type (OdTvDbMLeaderStyle::LeaderType).
    */
    kOverrideLeaderType = 0,
    /** \details
      Leader line color.
    */
    kOverrideLineColor,
    /** \details
      Leader line linetype ID.
    */
    kOverrideLineTypeId,
    /** \details
      Leader line weight.
    */
    kOverrideLineWeight,
    /** \details
      Leader line arrow size.
    */
    kOverrideArrowSize,
    /** \details
      Leader line arrow symbol.
    */
    kOverrideArrowSymbolId  
  };
  
  /** \details
    Returns the override status for the specified line property.

    \param leaderLineIndex [in]  Leader line index for which status is to be returned.
    \param value [in]  property identifier

    \returns
    Returns true if an override has been set for the specified property, false otherwise.
    (Override is set in the set* functions listed below, which accept leader line index as a first argument)
  */
  bool isOverride(int leaderLineIndex, LeaderLineOverrideType value);

  /** \details
    Sets the leader line type for the specified line.

    \param leaderLineIndex [in]  Leader line index.
    \param leaderLineType [in]  Leader line type. 

    \remarks
    The kLeaderLineType PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineType(
    int leaderLineIndex,
    OdTvDbMLeaderStyle::LeaderType leaderLineType);
  
  /** \details
    Returns the leader line type for the specified leader line.
    
    \param leaderLineIndex [in]  Leader line index for which type is to be returned.
  */
  OdTvDbMLeaderStyle::LeaderType leaderLineType(
    int leaderLineIndex) const;

  /** \details
    Sets the leader line color for the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param leaderLineColor [in]  Leader line color.

    \remarks
    The kLeaderLineColor PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineColor(
    int leaderLineIndex,
    const OdTvCmColor& leaderLineColor);

  /** \details
    Returns the leader line color for the specified leader line. 
    
    \param leaderLineIndex [in]  Leader line index for which color is to be returned.
  */    
  OdTvCmColor leaderLineColor(
    int leaderLineIndex) const;

  /** \details
    Sets the leader line linetype for the specified leader line.
    
    \param leaderLineIndex [in]  Leader line index.
    \param leaderLineTypeId [in]  Leader line type ObjectId.

    \remarks
    The kLeaderLineTypeId PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineTypeId(
    int leaderLineIndex,
    OdTvDbObjectId leaderLineTypeId);

  /** \details
    Returns the leader line linetype for the specified leader line.
    
    \param leaderLineIndex [in]  Leader line index.
  */
  OdTvDbObjectId leaderLineTypeId(
    int leaderLineIndex) const;

  /** \details
    Sets the leader line weight for the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param leaderLineWeight [in]  Leader line weight.

    \remarks
    The kLeaderLineWeight PropertyOverrideType override will be set as a result of
    calling this function.
  */
  void setLeaderLineWeight(
    int leaderLineIndex,
    OdDb::LineWeight leaderLineWeight);

  /** \details
    Returns the leader line weight for the specified leader line.
    
    \param leaderLineIndex [in]  Leader line index.
  */
  OdDb::LineWeight leaderLineWeight(
    int leaderLineIndex) const;

  /** \details
    Sets the arrow size for the specified leader line.

    \param leaderLineIndex [in]  Leader line index.
    \param arrowSize [in]  Arrow size.

    \remarks
    The kArrowSize PropertyOverrideType override will be set as a result of
    calling this function.  
  */
  void setArrowSize(
    int leaderLineIndex,
    double arrowSize);

  /** \details
    Returns the arrow size for a specified leader line.
    
    \param leaderLineIndex  [in] Leader line index. 
  */
  double arrowSize(
    int leaderLineIndex) const;

  /** \details
    Set extend to text mode.

    \param bSet [in]  New value for extend to text mode flag.
  */
  void setExtendLeaderToText(bool bSet);

  /** \details
    Returns extend to text mode flag.
  */
  bool extendLeaderToText() const;

  virtual void copyFrom(const OdRxObject* pSource);
protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const ODRX_OVERRIDE;
  virtual void subSetDatabaseDefaults(OdTvDbDatabase *pDb, bool doSubents) ODRX_OVERRIDE;
  virtual OdTvDbObjectPtr subWblockClone(OdTvDbIdMapping& ownerIdMap, OdTvDbObject* pObj, bool bPrimary) const ODRX_OVERRIDE;
  virtual OdTvDbObjectPtr subDeepClone(OdTvDbIdMapping& ownerIdMap, OdTvDbObject* pObj, bool bPrimary) const ODRX_OVERRIDE;

  virtual void modified(const OdTvDbObject* pObj) ODRX_OVERRIDE;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbMLeader object pointers.
*/
typedef OdSmartPtr<OdTvDbMLeader> OdTvDbMLeaderPtr;

/** \details
  This class is the MLeader Recompute Protocol Extension class.
   
  \sa
  TD_Db

  <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbMLeaderRecomputePE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbMLeaderRecomputePE);

  virtual OdResult recomputeBreakPoints(OdTvDbMLeader* pMLeader) = 0;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbMLeaderRecomputePE object pointers.
*/
typedef OdSmartPtr<OdTvDbMLeaderRecomputePE> OdTvDbMLeaderRecomputePEPtr;

///** { Secret } */
OdUInt32 DBDIM_EXPORT OdTvDbMLeader_setRecomputeFlags(OdTvDbMLeader* pMLeader, OdUInt32 flags); // for tests only

///** { Secret } */
bool DBDIM_EXPORT OdTvDbMLeader_setAcadBehaviour(OdTvDbMLeader* pMLeader, OdUInt32 bug, bool bValue); // for tests only

///** { Secret } */
OdGePoint3d DBENT_EXPORT OdTvDbMLeader_getPtInternal(OdTvDbMLeader* pMLeader, OdUInt32 index = 0); // for tests only

///** { Secret } */
void DBENT_EXPORT OdTvDbObject_clearDatabase(OdTvDbObject* pObj); // for tests only

///** { Secret } */
//void DBENT_EXPORT OdTvDbObject_clearModified(OdTvDbObject* pObj); // for tests only

#include "TD_PackPop.h"

#endif // OD_MLEADER_H


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




#ifndef OD_DBMLEADERSTYLE_H
#define OD_DBMLEADERSTYLE_H

#include "TD_PackPush.h"

#include "DbObject.h"
#include "DbMText.h"

class OdGeScale3d;
class OdString;

/** \details
    This class represents MLeader Style objects in an OdTvDbDatabase instance.
    
    \sa
    TD_Db

    OdTvDbMLeaderStyle objects are stored in the TV_ACAD_MLEADERSTYLE dictionary 
    in the Named Object Dictionary of an OdTvDbDatabase.
    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbMLeaderStyle : public OdTvDbObject
{
public:
  /** \details
    Enumeration for the content type of an MLeader.
  */
  enum ContentType {
    /** \details
      The MLeader has no content.
    */
    kNoneContent                = 0,

    /** \details
      The MLeader has block content.
    */
    kBlockContent               = 1,

    /** \details
      The MLeader has mtext content.
    */
    kMTextContent               = 2,

    /** \details
      The MLeader has tolerance content.
    */
    kToleranceContent           = 3
  };

  /** \details
    Enumeration for the draw order type of an MLeader.
  */
  enum DrawMLeaderOrderType {
    /** \details
      MLeader content should be drawn first.
    */
    kDrawContentFirst           = 0,

    /** \details
      MLeader leaderline should be drawn first.
    */
    kDrawLeaderFirst            = 1
  };

  /** \details
    Enumeration for MLeader Line draw order type.
  */
  enum DrawLeaderOrderType {
    /** \details
      MLeader leaderline head should be drawn first.
    */
    kDrawLeaderHeadFirst        = 0,

    /** \details
      MLeader leaderline tail should be drawn first.
    */
    kDrawLeaderTailFirst        = 1
  };

  /** \details
    Enumeration for the leader type of MLeader.
  */
  enum LeaderType {
    /** \details
      Invisible leader.
    */
    kInVisibleLeader            = 0,

    /** \details
      Straight line leader.
    */
    kStraightLeader             = 1,
    
    /** \details
      Spline leader.
    */
    kSplineLeader               = 2
  };

  /** \details
    Enumeration for the text attachment direction of MLeader text.
  */
  enum TextAttachmentDirection {
    /** \details
      Horizontal.
    */
    kAttachmentHorizontal       = 0,
    /** \details
      Vertical.
    */
    kAttachmentVertical         = 1
  };

  /** \details
    Enumeration for the text attachment type of MLeader text.
  */
  enum TextAttachmentType {
    /** \details
      Use the top of the top text line as the attachment point.
    */
    kAttachmentTopOfTop         = 0,

    /** \details
      Use the middle of the top text line as the attachment point.
    */
    kAttachmentMiddleOfTop      = 1,

    /** \details
      Use the middle of the text as the attachment point.
    */
    kAttachmentMiddle           = 2,

    /** \details
      Use the middle of the bottom text line as the attachment point.
    */
    kAttachmentMiddleOfBottom   = 3,

    /** \details
      Use the bottom of the bottom text line as the attachment point.
    */
    kAttachmentBottomOfBottom   = 4,

    /** \details
      Use the bottom of bottom text line as the attachment point. Underline the bottom line.
    */
    kAttachmentBottomLine       = 5,

    /** \details
      Use the bottom of the top text line as the attachment point. Underline the top line.
    */
    kAttachmentBottomOfTopLine  = 6,

    /** \details
      Use the bottom of the top text line as the attachment point.
    */
    kAttachmentBottomOfTop      = 7,

    /** \details
      Use the bottom of the top text line as the attachment point, and underline all content.
    */
    kAttachmentAllLine          = 8,

    /** \details
      Use the center of the mtext as the attachment point for vertical attachment.
    */
    kAttachmentCenter           = 9,

    /** \details
      Use the center of the mtext as the attachment point for vertical attachment, and overline/underline all content.
    */
    kAttachmentLinedCenter      = 10
  };

  /** \details
    Enumeration for the text angle type of MLeader text.
  */
  enum TextAngleType {
    /** \details
      Text angle is specified according to the angle of the last leader line segment.
    */
    kInsertAngle                = 0,

    /** \details
      Text is unconditionally horizontal.
    */
    kHorizontalAngle            = 1,
        
    /** \details
      Text angle is specified according to the angle of the last leader line segment, 
      and text is always oriented right side up to be readable.
    */
    kAlwaysRightReadingAngle    = 2
  };

  /** \details
    Enumeration for MLeader text alignment type.
  */
  enum TextAlignmentType {
    /** \details
      MLeader text is left justified.
    */
    kLeftAlignment              = 0,

    /** \details
      MLeader text is center justified.
    */
    kCenterAlignment            = 1,

    /** \details
      MLeader text is right justified.
    */
    kRightAlignment             = 2
  };

  /** \details
    Enumeration for the block connection type of MLeader block content.
  */
  enum BlockConnectionType {
    /** \details
      MLeader should connect to the extents of the block.
    */
    kConnectExtents             = 0,

    /** \details
      MLeader should connect to the base point of the block.
    */
    kConnectBase                = 1
  };

  /** \details
    Enumeration for the direction type of an MLeader.
  */
  enum LeaderDirectionType {
    /** \details
      Unknown direction type.
    */
    kUnknownLeader              = 0,

    /** \details
      Direction type of left.
    */
    kLeftLeader                 = 1,

    /** \details
      Direction type of right.
    */
    kRightLeader                = 2,

    /** \details
      Direction type of top.
    */
    kTopLeader                  = 3,

    /** \details
      Direction type of bottom.
    */
    kBottomLeader               = 4
  };


  /** \details
    Enumeration for the segment angle type of an MLeader.
  */
  enum SegmentAngleType {
    /** \details
      Any.
    */
    kAny                        = 0, 

    /** \details
      Angle of 15 degrees.
    */
        k15                         = 1,

    /** \details
      Angle of 30 degrees.
    */
    k30                         = 2,

    /** \details
      Angle of 45 degrees.
    */
    k45                         = 3,

    /** \details
      Angle of 60 degrees.
    */
    k60                         = 4,

    /** \details
      Angle of 90 degrees.
    */
    k90                         = 6,

    /** \details
      Angle of 180 degrees.
    */
    kHorz                       = 12
  };

public:
  ODDB_DECLARE_MEMBERS(OdTvDbMLeaderStyle);

  OdTvDbMLeaderStyle();

  void setDatabaseDefaults( OdTvDbDatabase* pDb );

//  virtual ~OdTvDbMLeaderStyle();

  /** \details
    Returns the name of this OdTvDbMLeaderStyle.
  */
  virtual OdString getName() const;
 
  /** \details
    Sets the name of this OdTvDbMLeaderStyle.

    \param name [in]  Holds the name of OdTvDbMLeaderStyle.
  */
  virtual void   setName(
    const OdString& name);

  /** \details
    Returns the description of this OdTvDbMLeaderStyle.
  */
  virtual OdString  description() const;

  /** \details
    Sets the description of this OdTvDbMLeaderStyle.

    \param description [in]  OdTvDbMLeaderStyle description string.
  */
  virtual void   setDescription(
    const OdString& description);

  /** \details
    Returns the set of bit flags this OdTvDbMLeaderStyle.
  */
  virtual OdUInt32       bitFlags() const;

  /** \details
    Sets the bit flags for this OdTvDbMLeaderStyle.

    \param flags [in]  The bit flags for this OdTvDbMLeaderStyle.
  */
  virtual void setBitFlags(
    OdUInt32 flags);

  /** \details
    Sets the content type for this OdTvDbMLeaderStyle.

    \param contentType [in]  The content type.
  */
  void setContentType(
    ContentType contentType);

  /** \details
    Returns the content type for this OdTvDbMLeaderStyle.
  */
  ContentType contentType() const;

  /** \details
    Sets the draw order for the content of OdTvDbMLeader objects using this OdTvDbMLeaderStyle.

    \param drawMLeaderOrderType [in] Draw order type for MLeader content.
  */
  void setDrawMLeaderOrderType(
    DrawMLeaderOrderType drawMLeaderOrderType);

  /** \details
    Returns the draw order for the content of OdTvDbMLeader objects using this OdTvDbMLeaderStyle.
  */
  DrawMLeaderOrderType  drawMLeaderOrderType() const;

  /** \details
    Sets the leader line draw order for OdTvDbMLeader objects using this OdTvDbMLeaderStyle.
  
    \param drawLeaderOrderType [in]  The Leader line draw order.
  */
  void setDrawLeaderOrderType(
    DrawLeaderOrderType drawLeaderOrderType);

  /** \details
    Returns the leader line draw order for OdTvDbMLeader objects using this OdTvDbMLeaderStyle.
  */
  DrawLeaderOrderType drawLeaderOrderType() const;

  /** \details
    Sets the maximun number of segment points used for leader lines.

    \param maxLeaderSegmentsPoints [in]  The maximum number of segment points.

    \remarks
    A value of 0 for maxLeaderSegmentsPoints indicates no limit.
  */
  void setMaxLeaderSegmentsPoints(
    int maxLeaderSegmentsPoints);

  /** \details
    Returns the maximun number of segment points used for leader lines.
  */
  int maxLeaderSegmentsPoints() const;

  /** \details
    Sets the constraint angle for the first segment (used for creating OdTvDbMLeader objects).

    \param angle [in]  Constraint angle.

    \remarks
    A value of kAny for "angle" indicates that no constraint is used.
  */
  void setFirstSegmentAngleConstraint(
    SegmentAngleType angle);

  /** \details
    Returns the constraint angle for the first segment (used for creating OdTvDbMLeader objects).

    \remarks
    A return value of kAny indicates that no constraint is used.
  */
  SegmentAngleType  firstSegmentAngleConstraint() const;

  /** \details
    Sets the constraint angle for the second segment (used for creating OdTvDbMLeader objects).

    \param angle [in]  Constraint angle.

    \remarks
    A value of kAny for "angle" indicates that no constraint is used.
  */
  void setSecondSegmentAngleConstraint(
    SegmentAngleType angle);

  /** \details
    Sets the constraint angle for the second segment (used for creating OdTvDbMLeader objects).

    \remarks
    A return value of kAny indicates that no constraint is used.
  */
  SegmentAngleType  secondSegmentAngleConstraint() const;

  /** \details
    Sets the leader line type for this OdTvDbMLeaderStyle.

    \param leaderLineType [in]  The leader line type.
  */
  void setLeaderLineType(
    LeaderType leaderLineType);

  /** \details
    Returns the leader line type for this OdTvDbMLeaderStyle.
  */
  LeaderType  leaderLineType() const;

  /** \details
    Set the leader line color for this OdTvDbMLeaderStyle.

    \param leaderLineColor [in]  The leader line color.
  */
  void setLeaderLineColor(
    const OdTvCmColor& leaderLineColor);

  /** \details
    Returns the leader line color for this OdTvDbMLeaderStyle.
  */
  OdTvCmColor leaderLineColor() const;

  /** \details
    Sets the leader line linetype for this OdTvDbMLeaderStyle.

    \param leaderLineTypeId [in]  The linetype Id.
  */
  void setLeaderLineTypeId(
    OdTvDbObjectId leaderLineTypeId);

  /** \details
    Returns the leader line linetype for this OdTvDbMLeaderStyle.
  */
  OdTvDbObjectId  leaderLineTypeId() const;

  /** \details
    Sets the leader line lineweight for this OdTvDbMLeaderStyle.

    \param leaderLineWeight [in]  The leader line lineweight.
  */
  void setLeaderLineWeight(
    OdDb::LineWeight leaderLineWeight);

  /** \details
    Returns the leader line lineweight for this OdTvDbMLeaderStyle.
  */
  OdDb::LineWeight  leaderLineWeight() const;

  /** \details
    Sets the leader line landing for this OdTvDbMLeaderStyle.

    \param enableLanding [in]  The leader line landing.

    \remarks
    If landing is disabled, landing gap is ignored.
  */
  void setEnableLanding(
    bool enableLanding);

  /** \details
    Returns leader line landing for this OdTvDbMLeaderStyle.
  */
  bool  enableLanding() const;

  /** \details
    Sets the gap between the leader line tail and the MText associated with the OdTvDbMLeader.

    \param landingGap [in]  The gap between the leader line tail and the MText associated with the OdTvDbMLeader.
  */
  void setLandingGap(
    double landingGap);

  /** \details
    Returns the gap between the leader line tail and the MText associated with the OdTvDbMLeader.
  */
  double  landingGap() const;

  /** \details
    Sets the "dog leg" flag for this OdTvDbMLeaderStyle, which controls dog leg leader lines.

    \param enableDogleg [in]  "Dog leg" flag.
  */
  void setEnableDogleg(
    bool enableDogleg);

  /** \details
    Returns the "dog leg" flag for this OdTvDbMLeaderStyle, which controls dog leg leader lines.
  */
  bool  enableDogleg() const;

  /** \details
    Sets the "dog leg" leader line length for this OdTvDbMLeaderStyle.

    \param doglegLength [in]  The "dog leg" leader line length.
  */
  void setDoglegLength(
    double doglegLength);

  /** \details
    Returns the "dog leg" leader line length for this OdTvDbMLeaderStyle.
  */
  double  doglegLength() const;

  /** \details
    Sets the arrow symbol for this OdTvDbMLeaderStyle by name.

    \param name [in]  Name of the arrow symbol.
  */
  void setArrowSymbolId(
    const OdString& name);

  /** \details
    Sets the arrow symbol for this OdTvDbMLeaderStyle by OdTvDbObjectId.

    \param arrowSymbolId [in]  OdTvDbObjectId of the arrow symbol.
  */
  void setArrowSymbolId(
    OdTvDbObjectId arrowSymbolId);

  /** \details
    Returns the arrow symbol for this OdTvDbMLeaderStyle as an OdTvDbObjectId.
  */
  OdTvDbObjectId  arrowSymbolId() const;

  /** \details
    Sets the arrow size for this OdTvDbMLeaderStyle.

    \param arrowSize [in]  The arrow size.
  */
  void setArrowSize(
    double arrowSize);

  /** \details
    Returns the arrow size for this OdTvDbMLeaderStyle.
  */
  double  arrowSize() const;

  /** \details
    Sets the default text used in an associated MText balloon.

    \param defaultMText [in]  The default text used in an associated MText balloon.
  */
  void setDefaultMText(
    const OdTvDbMTextPtr defaultMText);

  /** \details
    Sets the default text used in an associated MText balloon.

    \remarks
    The returned MText object is cloned, and can be NULL if there is no default MText.
  */
  OdTvDbMTextPtr  defaultMText() const;

  /** \details
    Sets the text style for this OdTvDbMLeaderStyle by OdTvDbObjectId.

    \param textStyleId [in]  The text style.
  */
  void setTextStyleId(
    OdTvDbObjectId textStyleId);

  /** \details
    Returns the text style OdTvDbObjectId for this OdTvDbMLeaderStyle.
  */
  OdTvDbObjectId  textStyleId() const;

  /** \details
    Sets the text attachment type for this OdTvDbMLeaderStyle.

    \param textAttachmentType [in]  The text attachment type.
    \param leaderDirection [in]  The leader direction type.
  */
  void setTextAttachmentType(
    TextAttachmentType textAttachmentType,
    LeaderDirectionType leaderDirection);

  /** \details
    Returns the text attachment type for this OdTvDbMLeaderStyle.

    \param leaderDirection [in]  The leader direction type.

    \returns
    Returns the text attachment type.
  */
  TextAttachmentType  textAttachmentType(
    LeaderDirectionType leaderDirection) const;

  /** \details
    Sets the text angle type for this OdTvDbMLeaderStyle.

    \param textAngleType [in]  The text angle type.
  */
  void setTextAngleType(
    TextAngleType textAngleType);

  /** \details
    Returns the text angle type for this OdTvDbMLeaderStyle.
  */
  TextAngleType textAngleType() const;

  /** \details
    Sets the text alignment type for this OdTvDbMLeaderStyle.

    \param textAlignmentType [in]  The text alignment type.
  */
  void setTextAlignmentType(
    TextAlignmentType textAlignmentType);

  /** \details
    Returns the text alignment type for this OdTvDbMLeaderStyle.
  */
  TextAlignmentType textAlignmentType() const;

  /** \details
    Sets the "always create left aligned text" property for this OdTvDbMLeaderStyle.

    \param bAlwaysLeft [in]  If true, text will be left aligned for newly created OdTvDbMLeader objects.
  */
  void setTextAlignAlwaysLeft(
    bool bAlwaysLeft);

  /** \details
    Returns the "always create left aligned text" property for this OdTvDbMLeaderStyle.
  */
  bool  textAlignAlwaysLeft() const;

  /** \details
    Sets the text color for this OdTvDbMLeaderStyle.

    \param textColor [in]  The text color used for associated OdTvDbMText object.
  */
  void setTextColor(
    const OdTvCmColor& textColor);

  /** \details
    Returns the text color for this OdTvDbMLeaderStyle.
  */
  OdTvCmColor textColor() const;

  /** \details
    Sets the text height for the associated OdTvDbMText object.
  
    \param textHeight [in]  The text height.
  */
  void setTextHeight(
    double textHeight);

  /** \details
    Returns the text height for the associated OdTvDbMText object.
  */
  double  textHeight() const;

  /** \details
    Sets the display/hide property for the frame around associated text.
  
    \param enableFrameText [in]  True if a frame is to be displayed around associated text, false otherwise.
  */
  void setEnableFrameText(
    bool enableFrameText);

  /** \details
    Returns true if a frame is to be displayed around associated text, false otherwise.
  */
  bool  enableFrameText() const;

  /** \details
    Sets the alignment space value for this OdTvDbMLeaderStyle.

    \param alignSpace [in]  The alignment space value.
  */
  void setAlignSpace(
    double alignSpace);

  /** \details
    Returns the alignment space value for this OdTvDbMLeaderStyle.
  */
  double  alignSpace() const;

  /** \details
    Sets the block to be associated with this OdTvDbMLeaderStyle by name.

    \param name [in]  The name of the standard block.
  */
  void setBlockId(
    const OdString& name);

  /** \details
    Sets the block to be associated with this OdTvDbMLeaderStyle by OdTvDbObjectId.

    \param blockId [in]  OdTvDbObjectId of the OdTvDbBlockTableRecord associated with this OdTvDbMLeaderStyle.
  */
  void setBlockId(
    OdTvDbObjectId blockId);

  /** \details
    Returns the OdTvDbObjectId of the block associated with this OdTvDbMLeaderStyle.
  */
  OdTvDbObjectId  blockId() const;

  /** \details
    Sets the color for block content associated with this OdTvDbMLeaderStyle.

    \param blockColor [in]  The color for block content.
  */
  void setBlockColor(
    const OdTvCmColor& blockColor);

  /** \details
    Returns the color for block content associated with this OdTvDbMLeaderStyle.
  */
  OdTvCmColor blockColor() const;

  /** \details
    Sets the scale for the block associated with this by OdTvDbMLeaderStyle.

    \param scale [in]  The block scale.
  */
  void setBlockScale(
    const OdGeScale3d& scale);

  /** \details
    Returns the scale for the block associated with this by OdTvDbMLeaderStyle.
  */
  OdGeScale3d blockScale() const;

  /** \details
    Enables/disables usage of the scale value set by setBlockScale().

    \param enableBlockScale [in]  true if block scale is to be used, false otherwise.
  */
  void setEnableBlockScale(
    bool enableBlockScale);

  /** \details
    Returns true if block scale (set by setBlockScale) is to be used, false otherwise.
  */
  bool  enableBlockScale() const;

  /** \details
    Sets the rotation value for the block referenced by this OdTvDbMLeaderStyle.

    \param rotation [in]  The rotation value.
  */
  void setBlockRotation(
    double rotation);

  /** \details
    Returns the rotation value for the block referenced by this OdTvDbMLeaderStyle.
  */
  double  blockRotation() const;

  /** \details
    Enables/disables usage of the rotation value set by setBlockRotation().

    \param enableBlockRotation [in]  true if block rotation is to be used, false otherwise.

  */
  void setEnableBlockRotation(
    bool enableBlockRotation);

  /** \details
    Returns true if block rotation (set by setBlockRotation) is to be used, false otherwise.
  */
  bool  enableBlockRotation() const;

  /** \details
    Sets the connection type for the associated block.

    \param blockConnectionType [in]  The connection type.
  */
  void setBlockConnectionType(
    BlockConnectionType blockConnectionType);

  /** \details
    Returns the connection type for the associated block.
  */
  BlockConnectionType blockConnectionType() const;

  /** \details
    Sets the scale factor for this OdTvDbMLeaderStyle.

    \param scale [in]  Scale factor.
  */
  void setScale(
    double scale);

  /** \details
    Returns the scale factor for this OdTvDbMLeaderStyle.
  */
  virtual double  scale() const;

  /** \details
    Returns true if properties were modified, false otherwise.
  */
  bool  overwritePropChanged() const;

  /** \details
    Add this OdTvDbMLeaderStyle to the specified OdTvDbDatabase object.
    
    \param pDb [in]  Pointer of the database which will receive the OdTvDbMLeaderStyle object.
    \param styleName [in]  Name of the style.
    
    \returns
    Returns the OdTvDbObjectID of the newly added OdTvDbMLeaderStyle object.
  */
  OdTvDbObjectId postMLeaderStyleToDb(
    OdTvDbDatabase* pDb, 
    const OdString& styleName);

  /** \details
    Sets the annotative flag for this OdTvDbMLeaderStyle.

    \param isAnnotative [in]  The annotative status.
  */
  void setAnnotative(
    bool isAnnotative);

  /** \details
    Returns the annotative flag for this OdTvDbMLeaderStyle.
  */
  virtual bool  annotative() const;

  /** \details
    Sets the gap used in the process of breaking leader lines.

    \param size [in]  The gap used in the process of breaking leader lines.
  */
  void setBreakSize (
    double size);

  /** \details
    Returns the gap used in the process of breaking leader lines.
  */
  double  breakSize() const;

  /** \details
    Sets the text attachment direction of MText.

    \param direction [in]  The text attachment direction of MText.
  */

  void setTextAttachmentDirection(
    TextAttachmentDirection direction);

  /** \details
    Returns the text attachment direction of MText.
  */
  TextAttachmentDirection textAttachmentDirection() const;

  /** \details
    Sets horizontal mleader lines extend to text mode.

    \param bSet [in]  Extend to text mode status.
  */
  void setExtendLeaderToText(bool bSet);

  /** \details
    Returns horizontal mleader lines extend to text mode.
  */
  bool extendLeaderToText() const;

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual void subClose();

  /*OdResult subGetClassID(void* pClsid) const;*/
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbMLeaderStyle object pointers.
*/
typedef OdSmartPtr<OdTvDbMLeaderStyle> OdTvDbMLeaderStylePtr;

#include "TD_PackPop.h"

#endif

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

#ifndef OD_SECTIONVIEWSTYLE_H
#define OD_SECTIONVIEWSTYLE_H

#include "DbModelDocViewStyle.h"
#include "Ge/GeDoubleArray.h"

#include "TD_PackPush.h"

/** \details
    This class represents detail view style objects.
    
    Corresponding C++ library:  TD_Db
    <group OdTvDb_Classes> 
*/
class DBENT_EXPORT OdTvDbSectionViewStyle : public OdTvDbModelDocViewStyle
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbSectionViewStyle);

  /** \details
    Defines identifier position types.
  */
  enum IdentifierPosition {
    kEndCuttingPlane             = 0, // The identifier is placed at the end of the cutting plane.
    kAboveDirectionArrowLine     = 1, // The identifier is placed above the direction arrow line.
    kAboveDirectionArrowSymbol   = 2, // The identifier is placed above the direction arrow symbol.
    kStartDirectionArrow         = 3, // The identifier is placed at the start of the direction arrow.
    kEndDirectionArrow           = 4, // The identifier is placed at the end of the direction arrow.
  };

  /** \details
    Defines section view symbol arrowhead direction.
  */
  enum ArrowDirection {
    kTowardsCuttingPlane    = 0, // The arrowheads are oriented towards the cutting plane.
    kAwayFromCuttingPlane   = 1, // The arrowheads are oriented away from the cutting plane.
  };

  /** \details
    Default constructor. Creates an OdTvDbSectionViewStyle instance.
  */
  OdTvDbSectionViewStyle();
  ~OdTvDbSectionViewStyle();
   
  /** \details
    Returns the object ID of the style assigned to the identifier.
  */
  OdTvDbObjectId identifierStyleId() const;

  /** \details
    Sets the identifier's text style.


    ObjectId The ID of the text style for the identifier.

	\returns
	OdDb::eOk if successful.
  */
  OdResult setIdentifierStyleId(const OdTvDbObjectId &objId);

  /** \details
    Returns the identifier's color.
  */
  OdTvCmColor identifierColor() const;

  /** \details
    Sets the identifier's color.
  */
  OdResult setIdentifierColor(const OdTvCmColor& color);

  /** \details
    Returns the identifier's height.
  */
  double identifierHeight() const;

  /** \details
    Sets the identifier's height.
  */
  OdResult setIdentifierHeight(double height);

  /** \details
    Returns the excluded characters that are specified for the identifier.
  */
  OdString identifierExcludeCharacters() const;

  /** \details
    Sets the characters to exclude for the identifier.


    str   Characters to exclude, each separated by a comma. 

    \returns
    eOk if successful 
    or 
    eInvalidInput if incorrect format or invalid characters.
  */
  OdResult setIdentifierExcludeCharacters(const OdString& str);

  /** \details
    Returns the object ID of the arrow start symbol.
  */
  OdTvDbObjectId arrowStartSymbolId() const;

  /** \details
    Sets the arrow start symbol to use a specified block.
  */
  OdResult setArrowStartSymbolId(const OdTvDbObjectId &arrowSymbolId);

  /** \details
    Returns the object ID of the arrow end symbol.
  */
  OdTvDbObjectId arrowEndSymbolId() const;

  /** \details
    Sets the arrow end symbol to use a specified block.
  */
  OdResult setArrowEndSymbolId(const OdTvDbObjectId &arrowSymbolId);

  /** \details
    Returns the arrow symbol's color.
  */
  OdTvCmColor arrowSymbolColor() const;

  /** \details
    Sets the arrow symbol's color.
  */
  OdResult setArrowSymbolColor(const OdTvCmColor& color);

  /** \details
    Returns the arrow symbol's size.
  */
  double arrowSymbolSize() const;

  /** \details
    Sets the arrow symbol's size.
  */
  OdResult setArrowSymbolSize(double size);

  /** \details
    Returns the arrow symbol's extension length.
  */
  double arrowSymbolExtensionLength() const;

  /** \details
    Sets the arrow symbol's extension length.
  */
  OdResult setArrowSymbolExtensionLength(double length);

  /** \details
    Returns the plane line's lineweight.
  */
  OdDb::LineWeight planeLineWeight() const;

  /** \details
    Sets the plane line's lineweight.
  */
  OdResult setPlaneLineWeight(OdDb::LineWeight lineweight);

  /** \details
    Returns the plane line's color.
  */
  OdTvCmColor planeLineColor() const;

  /** \details
    Sets the plane line's color.
  */
  OdResult setPlaneLineColor(const OdTvCmColor& color);

  /** \details
    Returns the object ID of the plane line's linetype.
  */
  OdTvDbObjectId planeLineTypeId() const;

  /** \details
    Sets the plane line's linetype according to the linetype's object ID.
  */
  OdResult setPlaneLineTypeId(const OdTvDbObjectId &objId);

  /** \details
    Returns the bend line's color.
  */
  OdTvCmColor bendLineColor() const;

  /** \details
    Sets the bend line's color.
  */
  OdResult setBendLineColor(const OdTvCmColor& color);

  /** \details
    Returns the bend line's lineweight.
  */
  OdDb::LineWeight  bendLineWeight() const;

  /** \details
    Sets the bend line's lineweight.
  */
  OdResult setBendLineWeight(OdDb::LineWeight lineweight);

  /** \details
    Returns the object ID of the bend line's linetype.
  */
  OdTvDbObjectId bendLineTypeId() const;

  /** \details
    Sets the bend line's linetype.
  */
  OdResult setBendLineTypeId(const OdTvDbObjectId &objId);

  /** \details
    Returns the bend line's length.
  */
  double bendLineLength() const;

  /** \details
    Sets the bend line's length.
  */
  OdResult setBendLineLength(double length);

  /** \details
    Returns the end line's length.
  */
  double endLineLength() const;

  /** \details
    Sets the end line's length.
  */
  OdResult setEndLineLength(double length);

  /** \details
    Returns the object ID of the view label's text style.
  */
  OdTvDbObjectId viewLabelTextStyleId() const;

  /** \details
    Sets the view label's text style.
  */
  OdResult setViewLabelTextStyleId(const OdTvDbObjectId &objId);

  /** \details
    Returns the view label's color.
  */
  OdTvCmColor viewLabelTextColor() const;

  /** \details
    Sets the view label's color.
  */
  OdResult setViewLabelTextColor(const OdTvCmColor& color);

  /** \details
    Returns the view label's text height.
  */
  double viewLabelTextHeight() const;

  /** \details
    Sets the view label's text height.
  */
  OdResult setViewLabelTextHeight(double height);

  /** \details
    Returns the view label's offset.
  */
  double viewLabelOffset() const;

  /** \details
    Sets the view label's offset.
  */
  OdResult setViewLabelOffset(double offset);

  /** \details
    Returns the view label's attachment point.
  */
  OdTvDbModelDocViewStyle::AttachmentPoint viewLabelAttachment() const;

  /** \details
    Sets the view label's attachment point.
  */
  OdResult setViewLabelAttachment(OdTvDbModelDocViewStyle::AttachmentPoint attachment);

  /** \details
    Returns the view label's text alignment.
  */
  OdTvDbModelDocViewStyle::TextAlignment viewLabelAlignment() const;

  /** \details
    Sets the view label's text alignment.
  */
  OdResult setViewLabelAlignment(OdTvDbModelDocViewStyle::TextAlignment alignment);

  /** \details
    Returns the view label's pattern.
  */
  OdString viewLabelPattern() const;

  /** \details
    Returns the view label's pattern.


    pField  (Optional) If the pattern uses fields,
            they are copied 'pField'.
    \returns
    Pattern of the view label.
  */
  OdString getViewLabelPattern(OdTvDbField* pField = NULL) const;

  /** \details
    Sets the view label's pattern.
    

    pattern     Pattern to assign to the view label.
    pField      (Optional) Specify a field to assign the pattern from the field
                (instead of the pattern itself).

    \returns
    OdDb::eOk if successful.
  */
  OdResult setViewLabelPattern(const OdString& pattern,
                               const OdTvDbField* pField = NULL);

  /** \details
    Returns the hatch pattern.
  */
  OdString hatchPattern() const;

  /** \details
    Sets the hatch pattern.
  */
  OdResult setHatchPattern(const OdString& pattern);

  /** \details
    Returns the hatch's color.
  */
  OdTvCmColor hatchColor() const;

  /** \details
    Sets the hatch's color.
  */
  OdResult setHatchColor(const OdTvCmColor& color);

  /** \details
    Returns the hatch's background color.
  */
  OdTvCmColor hatchBackgroundColor() const;

  /** \details
    Sets the hatch's background color.
  */
  OdResult setHatchBackgroundColor(const OdTvCmColor& color);

  /** \details
    Returns the hatch's scale.
  */
  double hatchScale() const;

  /** \details
    Sets the hatch's scale.
  */
  OdResult setHatchScale(double scale);

  /** \details
    Returns the hatch's angle array as a pointer to an OdGeDoubleArray object.
  */
  const OdGeDoubleArray& hatchAngles() const;

  /** \details
    Sets the hatch's angle array.
    
    \param angleArray [in]  Array of doubles to set hatch's angles used by section views.

    \returns
    eOk if successful.

    \remarks
    Angles are set in radians. At least one angle value must be present in the array. The first element is used by the first section view component, the second element is used by the second component and so on. 
    If the component number is more than the array size then the sequence is cycled. 
  */
  OdResult setHatchAngles(const OdGeDoubleArray& angleArray);

  /** \details
    Sets the hatch's transparency.
    
    \param transparency [in]  Transparency object to set hatch's transparency.

    \returns
    eOk if successful.
  */
  OdResult setHatchTransparency(const OdTvCmTransparency& transparency);

  /** \details
    Returns the hatch's transparency as an OdTvCmTransparency object.
  */
  OdTvCmTransparency hatchTransparency() const;

  /** \details
    Returns whether continuous labeling is enabled.
  */
  bool isContinuousLabeling() const;

  /** \details
    Sets whether continuous labeling is enabled or disabled.

    \param bValue [in]  True if continuous labeling is to be enabled, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setContinuousLabeling(bool bValue);

  /** \details
    Returns whether arrowheads display.
  */
  bool showArrowheads() const;

  /** \details
    Sets whether arrowheads are shown or not.

    \param bValue [in]  True if arrowheads are to be shown, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setShowArrowheads(bool bValue);

  /** \details
    Returns whether view labels display.
  */
  bool showViewLabel() const;

  /** \details
    Sets whether view labels are shown or not.

    \param bValue [in]  True if view labels are to be shown, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setShowViewLabel(bool bValue);

  /** \details
    Returns whether plane lines display.
  */
  bool showAllPlaneLines() const;

  /** \details
    Sets whether plane lines are shown or not.

    \param bValue [in]  True if plane lines are to be shown, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setShowAllPlaneLines(bool bValue);

  /** \details
    Returns whether identifiers at all bends of the cutting plane lines display.
  */
  bool showAllBendIndentifiers() const;

  /** \details
    Sets whether identifiers at all bends are shown or not.

    \param bValue [in]  True if identifiers at all bends are to be shown, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setShowAllBendIndentifiers(bool bValue);

  /** \details
    Returns whether end lines and bend lines display.
  */
  bool showEndAndBendLines() const;

  /** \details
    Sets whether end lines and bend lines are shown or not.

    \param bValue [in]  True if end lines and bend lines are to be shown, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setShowEndAndBendLines(bool bValue);

  /** \details
    Returns whether hatches display.
  */
  bool showHatching() const;

  /** \details
    Sets whether hatches are shown or not.

    \param bValue [in]  True if hatches are to be shown, false otherwise.

    \returns
    eOk if successful.
  */
  OdResult setShowHatching(bool bValue);

  ///** \details
  //  Inspects the string that defines the excluded characters of an identifier and checks it
  //  for valid characters and the correct format.
  //
  //  \param [in] str  String of characters that is set as the excluded characters for the identifier.
  //
  //  \returns
  //  True if the string is formatted correctly; false otherwise.
  //*/
  //static bool validateIdentifierExcludeCharacters(const OdString& str);

  /** \details
    Returns view identifier position as an OdTvDbSectionViewStyle::IdentifierPosition value.
  */
  OdTvDbSectionViewStyle::IdentifierPosition viewIdentifierPosition() const;

  /** \details
    Sets view identifier position type.

    \param type [in]  Identifier position type.

    \returns
    eOk if successful.
  */
  OdResult setViewIdentifierPosition(OdTvDbSectionViewStyle::IdentifierPosition type);

  /** \details
    Returns view identifier offset as a double value.
  */
  double viewIdentifierOffset() const;

  /** \details
    Sets view identifier offset.

    \param offset [in]  View identifier offset.

    \returns
    eOk if successful.
  */
  OdResult setViewIdentifierOffset(double offset);

  /** \details
    Returns arrow position type for this OdTvDbSectionViewStyle object as an OdTvDbSectionViewStyle::ArrowDirection value.
  */
  OdTvDbSectionViewStyle::ArrowDirection arrowPosition() const;

  /** \details
    Sets section view symbol arrowhead direction for this OdTvDbSectionViewStyle object.

    \param type [in]  Arrowhead direction.

    \returns
    eOk if successful.
  */
  OdResult setArrowPosition(OdTvDbSectionViewStyle::ArrowDirection type);

  /** \details
    Returns the end line's overshoot value.
  */
  double endLineOvershoot() const;

  /** \details
    Sets the end line's overshoot value.

    \param length [in]  Line's overshoot length.

    \returns
    eOk if successful.
  */
  OdResult setEndLineOvershoot(double length);

  // OdTvDbModelDocViewStyle overridden functions
  virtual OdTvDbObjectId postViewStyleToDb(OdTvDbDatabase* pDb, const OdString& styleName);

protected:
  // OdTvDbObject overridden functions
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

//protected:
//  // For internal use only
//  virtual OdTvDbObjectPtr subDeepClone(OdTvDbObject* pOwner,
//                                     OdTvDbIdMapping& idMap, bool isPrimary = true) const;
//  virtual OdTvDbObjectPtr subWblockClone(OdTvDbObject* pOwner,
//                                       OdTvDbIdMapping& idMap, bool isPrimary = true) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbSectionViewStyle object pointers.
*/
typedef OdSmartPtr<OdTvDbSectionViewStyle> OdTvDbSectionViewStylePtr;

#include "TD_PackPop.h"

#endif // OD_SECTIONVIEWSTYLE_H

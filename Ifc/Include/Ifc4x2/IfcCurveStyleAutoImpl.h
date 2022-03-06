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

// This file is generated automatically.

#ifndef _IFC4X2_IFCCURVESTYLE_AUTO_IMPL_H
#define _IFC4X2_IFCCURVESTYLE_AUTO_IMPL_H

#include "IfcPresentationStyleAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC4X2 express schema definitions.
*/
namespace OdIfc4x2 {

/** \details
  An IfcCurveStyle provides the style table for presentation information assigned to geometric curves. 
  The style is defined by a color, a font and a width. The IfcCurveStyle defines curve patterns as model patterns, 
  that is, the distance between visible and invisible segments of curve patterns that are given in model space dimensions 
  (that have to be scaled using the target plot scale).
*/
class IFC4X2_EXPORT IfcCurveStyle : public IfcPresentationStyle
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc4x2::IfcCurveStyle);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //


  /** \details
  Returns the value of CurveFont attribute. CurveFont is a curve style font which is used to present a curve. 
  It can either be a predefined curve font, or an explicitly defined curve font. Both may be scaled. 
  If not specified, the curve font should be taken from the layer assignment with style, 
  if that is not specified either, then the default curve font is applied.
  \returns
  Returns the value of CurveFont.
  */
  IfcCurveFontOrScaledCurveFontSelect curveFont();

  /** \details
  Returns the value of CurveWidth attribute. CurveWidth is the a positive length measure in units of the presentation area for the width of a presented curve. 
If not specified, the style should be taken from the layer assignment with style, if that is not specified either, then the default style is applied.
  \returns
  Returns the value of CurveWidth.
  */
  IfcSizeSelect curveWidth();

  /** \details
  Returns the value of CurveColour attribute. CurveColour is the the color of the visible part of the curve. 
If not specified, the color should be taken from the layer assignment with style, if that is not specified either, then the default colour is applied.
  \returns
  Returns the value of CurveColour.
  */
  IfcColour curveColour();

  /** \details
  Returns the value of ModelOrDraughting attribute. ModelOrDraughting is the indication whether the length measures 
  provided for the presentation style are model based or draughting based.
  \returns
  Returns the value of ModelOrDraughting.
  */
  OdDAI::Boolean getModelOrDraughting() const;

  /** \details
  Sets the value of ModelOrDraughting attribute. ModelOrDraughting is the indication whether the length measures 
  provided for the presentation style are model based or draughting based.
  \param ModelOrDraughting [in] Model or draughting to set.
  */
  void setModelOrDraughting(OdDAI::Boolean ModelOrDraughting);


public:

  /** \details
  Default constructor for the IfcCurveStyle class.
  */
  IfcCurveStyle();

  /** \details
  Reads object's data from the specified filer.
  \param rdFiler [in] Pointer to a filer from which to read the data.
  \returns
  A value of OdResult type that contains the result of the method execution.
  */
  virtual OdResult inFields(OdDAI::OdSpfFilerBase* rdFiler);

  /** \details
  Writes object's data the the specified filer.
  \param wrFiler [in] Pointer to a filer to which to write the data.
  \returns
  A value of OdResult type that contains the result of the method execution.
  */
  virtual OdResult outFields(OdDAI::OdSpfFilerBase* wrFiler);

  /** \details
  Returns a type of a class instance.
  \returns
  Pointer to the <link OdDAI__Entity, OdDAI::Entity> type that determines an entity definition within a schema.
  */
  virtual OdDAI::Entity* getInstanceType() const;

  /** \details
  Returns an attribute value for the specified attribute name.
  \param attrName [in] Name of an attribute to query.
  \returns
  OdRxValue object that represents a generic variant type value.
  */
  virtual OdRxValue getAttr(const char * attrName) const;

  /** \details
  Resets a value for the specified attribute.
  \param explicitAttrName [in] Explicit name of the attribute to reset.
  */
  virtual void unsetAttr(const char * explicitAttrName);

  /** \details
  Checks whether the specified attribute is set.
  \param explicitAttrName [in] Explicit name of the attribute to test.
  \returns
  true if the specified attribute is set, false otherwise.
  */
  virtual bool testAttr(const char * explicitAttrName) const;

  /** \details
  Sets the specified attribute with a given value.
  \param explicitAttrName [in] Explicit name of the attribute to set.
  \param val [in] Value to set.
  \returns
  true if the value is successfully set for the specified attribute, false otherwise.
  */
  virtual bool putAttr(const char * explicitAttrName, const OdRxValue &val);

  /** \details
  Checks whether the specified instance is the object derived from or belongs to this class.
  \param entityType [in] Entity to check.
  \returns
  true if the specified instance is the object derived from or belongs to this class, false otherwise.
  */
  virtual bool isKindOf(OdIfc::OdIfcEntityType entityType) const;

  /** \details
  Returns the type of this entity.
  \returns
  A value of the <link OdIfc__OdIfcEntityType, OdIfc::OdIfcEntityType> type that represents type of this entity.
  */
  virtual OdIfc::OdIfcEntityType type() const;

  /** \details
  Returns an attribute value for the specified attribute definition.
  \param attrDef [in] Attribute definition to query.
  \returns
  OdRxValue object that represents a generic variant type value.
  */
  virtual OdRxValue getAttr(const OdIfc::OdIfcAttribute attrDef) const;

  /** \details
  Resets a value for the specified attribute.
  \param explicitAttrDef [in] Explicit definition that represents an attribute to reset.
  */
  virtual void unsetAttr(const OdIfc::OdIfcAttribute explicitAttrDef);

  /** \details
  Checks whether the specified attribute is set.
  \param explicitAttrDef [in] Attribute definition to test.
  \returns
  true if the specified attribute is set, false otherwise.
  */
  virtual bool testAttr(const OdIfc::OdIfcAttribute explicitAttrDef) const;

  /** \details
  Sets the specified attribute with a given value.
  \param explicitAttrDef [in] Explicit attribute definition to set.
  \param val [in] Value to set.
  \returns
  true if the value is successfully set for the specified attribute, false otherwise.
  */
  virtual bool putAttr(const OdIfc::OdIfcAttribute explicitAttrDef, const OdRxValue &val);

protected:
  // Fields declaration: 
  OdDAI::Select m_CurveFont;   // IfcCurveFontOrScaledCurveFontSelect  [optional]
  OdDAI::Select m_CurveWidth;   // IfcSizeSelect  [optional]
  OdDAI::Select m_CurveColour;   // IfcColour  [optional]
  OdDAI::Boolean m_ModelOrDraughting;   // IfcBoolean  [optional]
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc4x2::IfcCurveStyle, IfcCurveStyle> object.
*/
typedef OdSmartPtr<IfcCurveStyle> IfcCurveStylePtr;

} // namespace

#endif // _IFC4X2_IFCCURVESTYLE_AUTO_IMPL_H

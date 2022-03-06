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

#ifndef _ODTV_VISUALSTYLE_H_INCLUDED_
#define _ODTV_VISUALSTYLE_H_INCLUDED_

#include "OdaCommon.h"

#include "Tv.h"
#include "TvIObject.h"
#include "TvTraitsDef.h"

class OdTvVisualStyleId;

/** \details
  Contains visual style option declarations.
  \sa
  <link tv_working_with_attributes_visual_styles_overview, Overview of Visual Styles>
  \sa
  <link tv_working_with_attributes_visual_styles_properties, Visual Style Properties>
*/
namespace OdTvVisualStyleOptions
{
  /** \details
    Visual style options.
  */
  enum Options
  {
    //DOM-IGNORE-BEGIN
    // Face-related options
    //DOM-IGNORE-END
    kFaceLightingModel = 0,       // The lighting model applied to the faces of drawings. See the <link OdTvVisualStyleOptions::FaceLightingModel, FaceLightingModel enumeration>.
    kFaceLightingQuality = 1,     // The calculation method of lighting effects applied to faces. See the <link OdTvVisualStyleOptions::FaceLightingQuality, FaceLightingQuality enumeration>.
    kFaceColorMode = 2,           // The color mode applied to faces. See the <link OdTvVisualStyleOptions::FaceColorMode, FaceColorMode enumeration>.
    kFaceModifiers = 3,           // Modifications applied to faces. See the <link OdTvVisualStyleOptions::FaceModifiers, FaceModifiers enumeration>.
    kFaceOpacityAmount = 4,       // The face opacity property: a double value that represents the face opacity level in the range from 0.0 (faces are fully transparent) to 1.0 (no transparency).
    kFaceSpecularAmount = 5,      // The face specular property: a double value that represents the specular highlight amount (indicating reflection and shininess values) of the material that is applied to faces.
    kFaceMonoColor = 6,           // The face monocolor effect property. The <link OdTvColorDef, OdTvColorDef> class represents the color applied to produce a "monochromatic" effect on faces.

    //DOM-IGNORE-BEGIN
    // Edge-related options
    //DOM-IGNORE-END
    kEdgeModel = 7,                     // The edge model property. See the <link OdTvVisualStyleOptions::EdgeModel, EdgeModel enumeration>.
    kEdgeStyles = 8,                    // The edge style property. See the <link OdTvVisualStyleOptions::EdgeStyles, EdgeStyles enumeration>.
    kEdgeIntersectionColor = 9,         // The color of intersection edges. The <link OdTvColorDef, OdTvColorDef> class represents the color applied to intersection edges.
    kEdgeObscuredColor = 10,            // The color of obscured edges. The <link OdTvColorDef, OdTvColorDef> class represents the color applied to obscured edges.
    kEdgeObscuredLinePattern = 11,      // The line pattern applied to obscured edges. See the <link OdTvVisualStyleOptions::EdgeLinePattern, EdgeLinePattern enumeration>.
    kEdgeIntersectionLinePattern = 12,  // The line pattern applied to intersection edges. See the <link OdTvVisualStyleOptions::EdgeLinePattern, EdgeLinePattern enumeration>.
    kEdgeCreaseAngle = 13,              // The edge crease angle: a double value that contains the angle threshold, above which a facet edge representing adjoining facets is displayed.
    kEdgeModifiers = 14,                // Modifications applied to edges. See the <link OdTvVisualStyleOptions::EdgeModifiers, EdgeModifiers enumeration>.
    kEdgeColorValue = 15,               // The edge color property. The <link OdTvColorDef, OdTvColorDef> class represents the color applied to edges. 
    kEdgeOpacityAmount = 16,            // The edge opacity property: a double value that represents the edge opacity level in the range from 0.0 (faces are fully transparent) to 1.0 (no transparency).
    kEdgeWidthAmount = 17,              // The edge width property: an integer value that represents the edge width in pixels.
    kEdgeOverhangAmount = 18,           // The edge overhang property: an integer value that represents the amount, in pixels, that edges should overhang their start and end points.
    kEdgeJitterAmount = 19,             // The edge jitter amount. See the <link OdTvVisualStyleOptions::EdgeJitterAmount, EdgeJitterAmount enumeration>.
    kEdgeSilhouetteWidth = 20,          // The edge silhouette width property: a short value that represents the silhouette edge width in pixels. 
    kEdgeHaloGapAmount = 21,            // The edge halo gap amount: an integer value from 0 to 100 that represents the halo gap. 

    //DOM-IGNORE-BEGIN
    // Display-related options
    //DOM-IGNORE-END
    kDisplayStyles = 22,                // The display settings. See the <link OdTvVisualStyleOptions::DisplayStyles, DisplayStyles enumeration>.

    //DOM-IGNORE-BEGIN
    // Misc options
    //DOM-IGNORE-END
    kUseDrawOrder = 23,                 // The boolean value indicating whether drawing order is enabled (if equal to true) or not (if equal to false).

    kDisplayShadow = 24,            // The boolean value indicating whether shadows should be rendered (true) or not (false).

    kPropertyCount                      // The number of visual style options. 
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Face-related options
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
    Lighting models that are applicable to faces.
  */
  enum FaceLightingModel
  {
    kInvisible = 0,   // Faces are invisible.
    kConstant = 1,    // Faces are drawn with a constant color.
    kPhong = 2,       // Faces are drawn with the Phong model to approximate realistic direct lighting.
    kGooch = 3        // Faces are drawn with a non-photorealistic lighting model for automatic technical illustrations.
  };

  /** \details
    Calculation methods of lighting effects that are applicable to faces.
  */
  enum FaceLightingQuality
  {
    kNoLighting = 0,          // No lighting calculations are applied to the faces.
    kPerFaceLighting = 1,     // Color is calculated for each face based on its orientation to the light sources of the scene.
    kPerVertexLighting = 2,   // Color is calculated for each vertex of a face based on its orientation to the light sources of the scene.
    kPerPixelLighting = 3     // Color is calculated for each pixel of a face based on its orientation to the light sources of the scene.
  };

  /** \details
    Modifications that affect the color of a face before any lighting and shading calculations are performed.
  */
  enum FaceColorMode
  {
    kNoColorMode = 0,           // Apply no modifications to the faces. 
    kObjectColor = 1,           // Apply the color of the drawable object to the faces of the object.
    kBackgroundColor = 2,       // Apply the display background color to the faces.
    kMono = 3,                  // All faces are treated as having a specific color, resulting in a monochromatic effect. 
    kTint = 4,                  // All faces have the hue and saturation values of their colors mapped to the hue and saturation values of a specific color, resulting in a "tinted" effect. The luminance value remains unchanged. 
    kDesaturate = 5,            // Apply a desaturation percentage to the diffuse color of a material.
    kBackgroundTexture = 6      // Apply actual background texture to the faces (work only on desktop platforms)
  };

  /** \details
    The field of bits that describe modifications to faces made before
    any lighting and shading calculations are performed.
  */
  enum FaceModifiers
  {
    kNoFaceModifiers = 0,       // Apply no face modifiers to the faces. 
    kFaceOpacityFlag = 1,       // Apply an opacity value to the faces. If not set, faces display with full opacity. If set, faces display with a specified degree of opacity from completely opaque to completely transparent. 
    kSpecularFlag = 2           // Apply a specular highlight (indicating reflection and shininess values) to a material that is applied to the faces.
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Edge-related options
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
    Edge display models.
  */
  enum  EdgeModel
  {
    kNoEdges = 0,           // No edges are displayed.
    kIsolines = 1,          // Display isolines.
    kFacetEdges = 2         // Display facet edges (the edges between neighboring faces).
  };

  /** \details
    The collection of bit flags that represents the combination of edge styles to display.
  */
  enum EdgeStyles
  {
    kNoEdgeStyle = 0,       // No edge styles are applied to the edges.
    kSilhouette = 1,        // Silhouette edges are displayed. A silhouette edge is an edge connecting a back facing polygon with a front facing polygon.
    kObscured = 2,          // Obscured edges are displayed.
    kIntersection = 4       // Intersection edges are displayed.
  };

  /** \details
    The collection of modifiers that can be applied to edges to adjust a different type of effect.
  */
  enum EdgeModifiers
  {
    kNoEdgeModifiers = 0,   // No modifiers are applied.
    kEdgeOverhang = 1,      // Allow an edge to overhang its start and end points by a specified amount. 
    kEdgeJitter = 2,        // Apply a jitter effect to the edges. The jitter effect is produced by drawing extra lines adjacent to the original line, with a specific amount of perturbation away from the original line.
    kEdgeWidth = 4,         // Apply a width to the edges.
    kEdgeColor = 8,         // Apply a color that differs from the drawable object color to the edges. 
    kEdgeHaloGap = 16,      // Apply a halo gap percentage to the edges of an object that is hidden by another object, such that the specified gap is displayed between the edges of the hidden object and the edges of the object that hides it.
    kAlwaysOnTop = 64,      // Force edges to be on top. Edges will not participate in the Z-ordering of the displayed drawables.
    kEdgeOpacity = 128,     // Apply an opacity value to the edges. If not set, edges display with full opacity. If set, edges display with a specified degree of opacity from completely opaque to completely transparent.
  };

  /** \details
    The collection of jitter values that can be applied to edges.
  */
  enum EdgeJitterAmount
  {
    kLow = 1,               // A small amount of perturbation.
    kMedium = 2,            // A medium amount of perturbation.
    kHigh = 3               // A large amount of perturbation.
  };

  /** \details
    The collection of line patterns that can be applied to edges.
  */
  enum EdgeLinePattern
  {
    kSolid = 1,                   // A solid line pattern is used to display edges.
    kDashedLine = 2,              // A dashed line pattern is used to display edges.
    kDotted = 3,                  // A dotted line pattern is used to display edges.
    kShortDash = 4,               // A short dashed line pattern is used to display edges.
    kMediumDash = 5,              // A medium dashed line pattern is used to display edges.
    kLongDash = 6,                // A long dashed line pattern is used to display edges.
    kDoubleShortDash = 7,         // A double short dashed line pattern is used to display edges.
    kDoubleMediumDash = 8,        // A double medium dashed line pattern is used to display edges.
    kDoubleLongDash = 9,          // A double long dashed line pattern is used to display edges.
    kMediumLongDash = 10,         // A medium long dashed line pattern is used to display edges.
    kSparseDot = 11               // A sparse dotted line pattern is used to display edges.
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Display-related options
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
    The combination of display settings that can be enabled.
  */
  enum DisplayStyles
  {
    kNoDisplayStyle = 0,    // No display settings are used.
    kBackgrounds = 1,       // Backgrounds are enabled.
    kMaterials = 2,         // Materials are enabled.
    kTextures = 4           // Textures are enabled.
  };
};


/** \details
  Contains declarations of operation types for setting visual style options.
  \sa
  <link tv_working_with_attributes_visual_styles_properties, Visual Style Properties>
*/
namespace OdTvVisualStyleOperations
{
  /** \details
  Visual style operations.
  */
  enum Operation
  {
    kInherit = 0,           // The option value is inherited.
    kSet = 1                // The option value is set separately.
  };
};


/** \details
  The abstract interface class for managing visual styles in Visualize SDK.
  \sa
  <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
*/
class ODTV_EXPORT OdTvVisualStyle : public OdTvHandledIObject
{
public:

  /** \details
    Sets a new description for the visual style object.
    
    \param description [in] A string that contains a new description for the visual style.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new description of the visual style object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDescription(const OdString& description) = 0;

  /** \details
    Retrieves the current visual style description.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the current description of the visual style object.
    \remarks 
    If the rc parameter is not null and the current description was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual const OdString getDescription(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name for the visual style object.
    
    \param sName [in] A string that contains the new name for the visual style.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new name of the visual style object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current visual style name.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the current name of the visual style object.
    \remarks 
    If the rc parameter is not null and the current name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual const OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current default flag value. 
    
    If the default flag value is equal to true, the visual style is used as a default one; if the visual style is not used as a default, the method returns false.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the visual style is the default; otherwise the method returns false.
    The default visual style can not be deleted or renamed; the description of the default visual style also can not be changed.
    If the rc parameter is not null and the current value of the default flag was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getDefault(OdTvResult* rc = NULL) const = 0;

  /** \details
    Copies options from a specified visual style object.
    
    \param vsId [in] An identifier of a visual style object to copy options from.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the copy operation.
    \remarks
    If the visual style options were successfully copied, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult copyFrom(const OdTvVisualStyleId& vsId) = 0;

  /** \details
    Sets a new value of an integer <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt  [in] An <link OdTvVisualStyleOptions::Options, option> to be set.
    \param nVal [in] A new option integer value to be set.
    \param op   [in] An <link OdTvVisualStyleOperations::Operation, operation> to use for setting the new option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visual style option value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, OdInt32 nVal,
                               OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet) = 0;

  /** \details
    Sets a new value of a boolean <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt  [in] An <link OdTvVisualStyleOptions::Options, option> to be set.
    \param bVal [in] A new option boolean value to be set.
    \param op   [in] An <link OdTvVisualStyleOperations::Operation, operation> to use for setting the new option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visual style option value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, bool bVal,
                               OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet) = 0;

  /** \details
    Sets a new value of a double <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt  [in] An <link OdTvVisualStyleOptions::Options, option> to be set.
    \param dVal [in] A new option double value to be set.
    \param op   [in] An <link OdTvVisualStyleOperations::Operation, operation> to use for setting the new option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visual style option value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, double dVal,
                               OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet) = 0;

  /** \details
    Sets a new color <link OdTvVisualStyleOptions::Options, option> value of the visual style object.
    
    \param opt    [in] An <link OdTvVisualStyleOptions::Options, option> to be set.
    \param color  [in] A new color option value to be set.
    \param op     [in] An <link OdTvVisualStyleOperations::Operation, operation> to use for setting the new color option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visual style color option value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOption(OdTvVisualStyleOptions::Options opt, const OdTvColorDef& color,
                               OdTvVisualStyleOperations::Operation op = OdTvVisualStyleOperations::kSet) = 0;

  /** \details
    Retrieves the current value of an integer <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt  [in] An <link OdTvVisualStyleOptions::Options, option> with the value to return.
    \param nVal [out] A placeholder for the integer option's current value that is returned to a calling subroutine.
    \param pOp  [out] A pointer to the <link OdTvVisualStyleOperations::Operation, operation> value that represents the operation used for changing the option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \remarks
    If the visual style option value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the requested option has another type or is absent, the method returns an error.
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, OdInt32& nVal, OdTvVisualStyleOperations::Operation *pOp = NULL) = 0;

  /** \details
    Retrieves the current value of a boolean <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt  [in] An <link OdTvVisualStyleOptions::Options, option> with the value to return.
    \param bVal [out] A placeholder for the boolean option's current value that is returned to a calling subroutine.
    \param pOp  [out] A pointer the <link OdTvVisualStyleOperations::Operation, operation> value that represents the operation used for changing the option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \remarks
    If the visual style option value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the requested option has another type or is absent, the method returns an error.
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, bool& bVal, OdTvVisualStyleOperations::Operation *pOp = NULL) = 0;

  /** \details
    Retrieves the current value of a double <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt  [in] An <link OdTvVisualStyleOptions::Options, option> with the value to return.
    \param dVal [out] A placeholder for the double option's current value that is returned to a calling subroutine.
    \param pOp  [out] A pointer the <link OdTvVisualStyleOperations::Operation, operation> value that represents the operation used for changing the option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \remarks
    If the visual style option value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the requested option has another type or is absent, the method returns an error.
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, double& dVal, OdTvVisualStyleOperations::Operation *pOp = NULL) = 0;

  /** \details
    Retrieves the current value of the color <link OdTvVisualStyleOptions::Options, option> of the visual style object.
    
    \param opt    [in] An <link OdTvVisualStyleOptions::Options, option> with the value to return.
    \param color  [out] A placeholder for the <link OdTvColorDef, color definition> object that contains the color option's current value. This color definition object is returned to a calling subroutine.
    \param pOp    [out] A pointer the <link OdTvVisualStyleOperations::Operation, operation> value that represents the operation used for changing the option value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \remarks
    If the visual style option value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the requested option has another type or is absent, the method returns an error.
  */
  virtual OdTvResult getOption(OdTvVisualStyleOptions::Options opt, OdTvColorDef& color, OdTvVisualStyleOperations::Operation *pOp = NULL) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvVisualStyle, OdTvVisualStyle> object.
*/
typedef OdTvSmartPtr<OdTvVisualStyle> OdTvVisualStylePtr;


/** \details
  The interface class for a visual style object identifier that allows access to the <link OdTvVisualStyle, OdTvVisualStyleId> object.
*/
class ODTV_EXPORT OdTvVisualStyleId : public OdTvId
{
public:

  /** \details
    Opens the visual style determined by its identifier for a read or write operation. 
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the visual style object.
    \remarks
    If the rc parameter is not null and the visual style was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvVisualStylePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};


/** \details
  The base interface class for the iterator of Visualize SDK visual style objects.
  An iterator object provides sequential access to a collection of visual styles.
*/
class ODTV_EXPORT OdTvVisualStylesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the visual style that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the visual style identifier if the iterator refers to a visual style; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the visual style identifier was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a visual style, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvVisualStyleId getVisualStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for the visual style defined by its identifier and moves the iterator to this visual style if found.
    
    \param visualStyleId [in] A visual style identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the visual style specified by its identifier was found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvVisualStyleId& visualStyleId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvVisualStylesIterator, OdTvVisualStylesIterator> object.
*/
typedef OdTvSmartPtr<OdTvVisualStylesIterator> OdTvVisualStylesIteratorPtr;

#endif //_ODTV_VISUALSTYLE_H_INCLUDED_

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

#ifndef __ODGICONTEXTUALCOLORS_H__
#define __ODGICONTEXTUALCOLORS_H__

#include "Gi/GiExport.h"
#include "RxObject.h"
#include "CmColorBase.h"

#include "TD_PackPush.h"

/** \details
    Defines colors depending on the vectorization context.

    \sa
    TD_Gi 
    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiContextualColors : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdGiContextualColors);

  // Color accessors

  // Grid

  /** \details
    Retrieves the color of major grid lines in the current vectorization context.
    
    \returns
    color of major grid lines as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor gridMajorLines() const;

  /** \details
    Retrieves the color of minor grid lines in the current vectorization context.
    
    \returns
    color of minor grid lines as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor gridMinorLines() const;

  /** \details
    Retrieves the color of axis rays emitted from the grid origin in the current vectorization context.
    
    \returns
    color of axis rays emitted from the grid origin as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor gridAxisLines() const;

  /** \details
    Checks whether X, Y and Z axis color tinting is applied to the major grid lines
    in the current vectorization context.
    
    \returns
    true if the X, Y and Z axis color tinting is applied to the major grid lines, false otherwise
  */
  virtual bool gridMajorLineTintXYZ() const;

  /** \details
    Checks whether X, Y and Z axis color tinting is applied to the minor grid lines
    in the current vectorization context.
    
    \returns
    true if the X, Y and Z axis color tinting is applied to the minor grid lines, false otherwise
  */
  virtual bool gridMinorLineTintXYZ() const;

  /** \details
     Checks whether X, Y and Z axis color tinting is applied to the axis rays emitted from the grid origin
    in the current vectorization context. Otherwise returns false.
    
    \returns
    true if the X, Y and Z axis color tinting is applied to the axis rays emitted from the grid origin, false otherwise
  */
  virtual bool gridAxisLineTintXYZ() const;

  // Light

  /** \details
    Retrieves the color of light glyphs in the current vectorization context.
    
    \returns
    color of light glyphs as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightGlyphs() const;

  /** \details
    Retrieves the color of the light hotspot in the current vectorization context.
    
    \returns
    color of the light hotspot as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightHotspot() const;

  /** \details
    Retrieves the color of the light fall off area in the current vectorization context.
    
    \returns
    color of the light fall off area as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightFalloff() const;

  /** \details
    Retrieves the color of the light start limit indicator in the current vectorization context.
    
    \returns
    color of the light start limit indicator as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightStartLimit() const;

  /** \details
    Retrieves the color of the light end limit indicator in the current vectorization context.
    
    \returns
    color of the light end limit indicator as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightEndLimit() const;

  /** \details
    Retrieves the color of the light shape glyph in the current vectorization context.
    
    \returns
    color of the light shape glyph as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightShapeColor() const;

  /** \details
    Retrieves the color of the light distance glyphs in the current vectorization context.
    
    \returns
    color of the light distance glyph as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor lightDistanceColor() const;

  /** \details
    Retrieves the color of the web light glyphs in the current vectorization context.
    
    \returns
    color of the web light glyph as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor webMeshColor() const;

  /** \details
    Retrieves the color of the web light glyphs in the current vectorization context
    when the web light file is unavailable.
    
    \returns
    color of the web light shape glyph as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor webMeshMissingColor() const;

  // Camera

  /** \details
    Retrieves the color of the camera glyphs in the current vectorization context.
    
    \returns
    color of the camera glyphs as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor cameraGlyphs() const;

  /** \details
    Retrieves the color of the camera frustrum in the current vectorization context.
    
    \returns
    color of the camera frustrum as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor cameraFrustrum() const;

  /** \details
    Retrieves the color of the camera clipping planes in the current vectorization context.
    
    \returns
    color of the camera clipping planes as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor cameraClipping() const;

  // Runtime parameters

  /** \details
    Sets the specified runtime context flag to the specified value.

    \param nFlags [in]  Flag to set.
    \param bSet [in]  Value to set.
  */
  virtual void setContextFlags(OdUInt32 nFlags, bool bSet = true) = 0;

  /** \details
    Retrieves the current state of the specified runtime context flag.

    \param nFlags [in]  Flag of the state that should be checked.
    
    \returns
    true if the specified flag is set, false otherwise.
  */
  virtual bool flagsSet(OdUInt32 nFlags) const = 0;

  // This part is for internal use. Provides interface extensibility feature.

  /** \details
    Specifies the list of interface elements for which the color can be changed
    in the current vectorization context.
  */
  enum ColorType
  {
    kGridMajorLinesColor = 0, // major grid lines color
    kGridMinorLinesColor,     // minor grid lines color
    kGridAxisLinesColor,      // axis grid lines color
    kLightGlyphsColor,        // light glyphs color
    kLightHotspotColor,       // light hotspot color
    kLightFalloffColor,       // light fall off color
    kLightStartLimitColor,    // light start limit indicator color
    kLightEndLimitColor,      // light end limit indicator color
    kLightShapeColor,         // light shape glyphs color
    kLightDistanceColor,      // light distance glyphs color
    kWebMeshColor,            // web light shape glyphs color
    kWebMeshMissingColor,     // web light shape glyphs color when light file is missing
    kCameraGlyphsColor,       // camera glyphs color
    kCameraFrustrumColor,     // camera frustrum color
    kCameraClippingColor,     // camera clipping planes color

    kNumColors                // number of colors
  };

  /** \details
    Specifies the list of interface elements for which X, Y and Z axis color tinting
    can be applied in the current vectorization context.
  */
  enum ColorTint
  {
    kGridMajorLineTint = 0,   // tint of major lines on a grid
    kGridMinorLineTint,       // tint of minor lines on a grid
    kGridAxisLineTint,        // tint of axis lines on a grid

    kNumTintFlags             // major grid lines color
  };

  /** \details
    Retrieves the color of the specified interface element in the current vectorization context.

    \param type [in]  Interface element.
    
    \returns
    color of the specified interface element as OdCmEntityColor instance.
  */
  virtual OdCmEntityColor contextualColor(ColorType /*type*/) const { return OdCmEntityColor(OdCmEntityColor::kForeground); }

  /** \details
    Checks whether X, Y and Z axis color tinting is applied to the specified interface element.

    \param type [in]  Interface element.
    
    \returns
    true if tinting is applied to a specified interface element, false otherwise.
  */
  virtual bool contextualColorTint(ColorTint /*type*/) const { return false; }
};

/** \details
  This template class is a specialization of the OdSmartPtr class template for OdGiContextualColors object pointers.
*/
typedef OdSmartPtr<OdGiContextualColors> OdGiContextualColorsPtr;

// Default implementations of OdGiContextualColors accessor methods

inline OdCmEntityColor OdGiContextualColors::gridMajorLines() const
{
  return contextualColor(kGridMajorLinesColor);
}

inline OdCmEntityColor OdGiContextualColors::gridMinorLines() const
{
  return contextualColor(kGridMinorLinesColor);
}

inline OdCmEntityColor OdGiContextualColors::gridAxisLines() const
{
  return contextualColor(kGridAxisLinesColor);
}

inline bool OdGiContextualColors::gridMajorLineTintXYZ() const
{
  return contextualColorTint(kGridMajorLineTint);
}

inline bool OdGiContextualColors::gridMinorLineTintXYZ() const
{
  return contextualColorTint(kGridMinorLineTint);
}

inline bool OdGiContextualColors::gridAxisLineTintXYZ() const
{
  return contextualColorTint(kGridAxisLineTint);
}

inline OdCmEntityColor OdGiContextualColors::lightGlyphs() const
{
  return contextualColor(kLightGlyphsColor);
}

inline OdCmEntityColor OdGiContextualColors::lightHotspot() const
{
  return contextualColor(kLightHotspotColor);
}

inline OdCmEntityColor OdGiContextualColors::lightFalloff() const
{
  return contextualColor(kLightFalloffColor);
}

inline OdCmEntityColor OdGiContextualColors::lightStartLimit() const
{
  return contextualColor(kLightStartLimitColor);
}

inline OdCmEntityColor OdGiContextualColors::lightEndLimit() const
{
  return contextualColor(kLightEndLimitColor);
}

inline OdCmEntityColor OdGiContextualColors::lightShapeColor() const
{
  return contextualColor(kLightShapeColor);
}

inline OdCmEntityColor OdGiContextualColors::lightDistanceColor() const
{
  return contextualColor(kLightDistanceColor);
}

inline OdCmEntityColor OdGiContextualColors::webMeshColor() const
{
  return contextualColor(kWebMeshColor);
}

inline OdCmEntityColor OdGiContextualColors::webMeshMissingColor() const
{
  return contextualColor(kWebMeshMissingColor);
}

inline OdCmEntityColor OdGiContextualColors::cameraGlyphs() const
{
  return contextualColor(kCameraGlyphsColor);
}

inline OdCmEntityColor OdGiContextualColors::cameraFrustrum() const
{
  return contextualColor(kCameraFrustrumColor);
}

inline OdCmEntityColor OdGiContextualColors::cameraClipping() const
{
  return contextualColor(kCameraClippingColor);
}

/** \details
    Provides a default implementation for OdGiContextualColors.

    \sa
    TD_Gi 
    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiContextualColorsImpl : public OdGiContextualColors
{
public:
  ODRX_DECLARE_MEMBERS(OdGiContextualColorsImpl);

  /** \details
    Specifies the list of vectorization context types.
  */
  enum VisualType
  {
    kVisualTypeNotSet = -1,  // No visual type is set.
    k2dModel = 0,            // 2D model context type.
    kLayout,                 // Layout context type.
    k3dParallel,             // 3D parallel context type.
    k3dPerspective,          // 3D perspective context type.
    kBlock,                  // Block context type.
    
    kNumVisualTypes          // Number of visual types.
  };
  
  /** \details
    Sets a type of vectorization context.

    \param type [in]  Context type to set.
  */
  virtual void setVisualType(VisualType type) = 0;

  /** \details
    Retrieves the type of vectorization context.
    
    \returns
    type of vectorization context.
  */
  virtual VisualType visualType() const = 0;

  /** \details
    Sets a color for the specified interface element.

    \param type [in]  Interface element.
    \param color [in]  Color to set.
  */
  virtual void setContextualColor(ColorType type, const OdCmEntityColor &color) = 0;

  /** \details
    Sets a color for the specified interface element.

    \param type [in]  Interface element.
    \param color [in]  Color to set.
  */
  void setContextualColor(ColorType type, ODCOLORREF color) { setContextualColor(type, ODTOCMCOLOR(color)); }

  /** \details
    Sets a boolean value that indicates whether X, Y and Z axis color tinting is applied
    to the specified interface element.

    \param type [in]  Interface element.
    \param bSet [in]  Boolean value to set.
  */
  virtual void setContextualColorTint(ColorTint type, bool bSet) = 0;

  /** \details
    Sets up the default color and tint values for the currently specified type of vectorization context.
  */
  virtual void setDefaultForType() = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class template for OdGiContextualColorsImpl object pointers.
*/
typedef OdSmartPtr<OdGiContextualColorsImpl> OdGiContextualColorsImplPtr;

/** \details
    Provides redirection ability for OdGiContextualColors.

    \sa
    TD_Gi 
    <group OdGi_Classes> 
*/
class ODGI_EXPORT OdGiContextualColorsRedir : public OdGiContextualColors
{
public:
  ODRX_DECLARE_MEMBERS(OdGiContextualColorsRedir);

  /** \details
    Sets an existing OdGiContextualColors object for redirection.

    \param pObj [in]  Redirection object.
  */
  virtual void setRedirectionObject(OdGiContextualColors *pObj) = 0;

  /** \details
    Retrieves the redirection object.
    
    \returns
    pointer to the redirection OdGiContextualColors object.
  */ 
  virtual const OdGiContextualColors *redirectionObject() const = 0;

  /** \details
    Retrieves the redirection object.
    
    \returns
    pointer to the redirection OdGiContextualColors object.
  */ 
  virtual OdGiContextualColors *redirectionObject() = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class template for OdGiContextualColorsRedir object pointers.
*/
typedef OdSmartPtr<OdGiContextualColorsRedir> OdGiContextualColorsRedirPtr;

#include "TD_PackPop.h"

#endif // __ODGICONTEXTUALCOLORS_H__

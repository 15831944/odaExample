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
#ifndef __NW_ABSTRACT_VIEWPORT_DATA_H__
#define __NW_ABSTRACT_VIEWPORT_DATA_H__

#include "NwExport.h"
#include "AbstractViewPE.h"

class OdGsView;

//----------------------------------------------------------
// OdNwAbstractViewportData

/** \details
  This class represents abstract viewport data.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwAbstractViewportData : public OdAbstractViewPE
{
public:
  /** \details
    Default constructor for objects of the OdNwAbstractViewportData class.
  */
  OdNwAbstractViewportData() = default;

  /** \details
    Default destructor for objects of the OdNwAbstractViewportData class. Frees
    allocated resources.
  */
  virtual ~OdNwAbstractViewportData() = default;

  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwAbstractViewportData);
  //DOM-IGNORE-END

  /** \details
    Returns the view target of the specified viewport object (DXF 17).
    \param pViewport [in] Viewport object to get the target of.
    \returns Viewport target point in WCS.
  */
  OdGePoint3d target(const OdRxObject* pViewport) const override;

  /** \details
    Returns the view direction of the specified viewport object (DXF 16).
    \param pViewport [in] Viewport object to get the direction of.
    \returns Viewport direction vector in WCS.
  */
  OdGeVector3d direction(const OdRxObject* pViewport) const override;

  /** \details
    Returns the up vector of the specified viewport object.
    \param pViewport [in] Viewport object to get the up vector of.
    \returns Viewport up vector in WCS.
  */
  OdGeVector3d upVector (const OdRxObject* pViewport) const override;

  /** \details
    Returns the width of the specified viewport object (DXF 40).
    \param pViewport [in] Viewport object to get the width of.
    \returns Viewport width value.
  */
  double fieldWidth(const OdRxObject* pViewport) const override;

  /** \details
    Returns the height of the specified viewport object (DXF 41).
    \param pViewport [in] Viewport object to get the height of.
    \returns Viewport height value.
  */
  double fieldHeight(const OdRxObject* pViewport) const override;

  /** \details
    Indicates whether perspective is on for the specified viewport object
    (DXF 90, bit 0x01).
    \param pViewport [in] Viewport object to get the perspective state of.
    \returns True if perspective is on; false otherwise.
  */
  bool isPerspective(const OdRxObject* pViewport) const override;

  /** \details
    Returns the view offset of the specified viewport object.
    \param pViewport [in] Viewport object to get the view offset of.
    \returns Viewport view offset value.
  */
  OdGeVector2d viewOffset(const OdRxObject* pViewport) const;

  /** \details
    Indicates whether the specified viewport object has a view offset.
    \param pViewport [in] Viewport object to get the presence of a view offset for.
    \returns True if the specified viewport object has a view offset; false
    otherwise.
  */
  bool hasViewOffset(const OdRxObject* pViewport) const;

  /** \details
    Returns the twist angle value of the specified viewport object.
    \param pViewport [in] Viewport object to get the twist angle value of.
    \returns Viewport twist angle value.
  */
  double viewTwist(const OdRxObject* pViewport) const override;

  /** \details
    Sets parameters of the specified viewport object.
    \param pViewport     [in] Viewport object to set parameters of.
    \param target        [in] Target point in WCS.
    \param direction     [in] Direction vector in WCS.
    \param upVector      [in] Up vector in WCS.
    \param fieldWidth    [in] Width value.
    \param fieldHeight   [in] Height value.
    \param isPerspective [in] Perspective state.
    \param viewOffset    [in] View offset vector.
  */
  void setView(
      OdRxObject* pViewport,
      const OdGePoint3d& target,
      const OdGeVector3d& direction,
      const OdGeVector3d& upVector,
      double fieldWidth,
      double fieldHeight,
      bool isPerspective,
      const OdGeVector2d& viewOffset = OdGeVector2d::kIdentity) const override;

  /** \details
    Returns the GsView for the non-annotated elements of the specified viewport.

    \param pViewport [in] Viewport, view of which will be returned.
    \returns GsView of the specified viewport.
  */
  virtual OdGsView* gsView(OdRxObject* pViewport) const;


  /** \details
    Sets the perspective mode lens length of the specified viewport object
    (DXF 42).
    \param pViewport  [in] Viewport object to set the lens length for.
    \param lensLength [in] Lens length value (mm).
  */
  void setLensLength(OdRxObject* pViewport, double lensLength) const override;

  /** \details
    Returns the perspective mode lens length (in mm) of the specified viewport
    object (DXF 42).
    \param pViewport [in] Viewport object to get the lens length of.
    \returns Lens length value (mm).
  */
  double lensLength(const OdRxObject* pViewport) const override;

  /** \details
    Indicates whether the front clipping is on for the specified viewport object
    (DXF 90, bit 0x02).
    \param pViewport [in] Viewport object to get the front clipping state of.
    \returns True if front clipping is on for the specified viewport object;
    false otherwise.
  */
  bool isFrontClipOn(const OdRxObject* pViewport) const override;

  /** \details
    Turns on and off front clipping for the specified viewport object (DXF 90,
    bit 0x02).
    \param pViewport [in] Viewport object to set the front clipping state for.
    \param frontClip [in] True to turn front clipping on; false to turn front clipping off.
  */
  void setFrontClipOn(OdRxObject* pViewport, bool frontClip) const override;

  /** \details
    Indicates whether the back clipping is on for the specified viewport object
    (DXF 90, bit 0x04).
    \param pViewport [in] Viewport object to get the back clipping state of.
    \returns True if back clipping is on for the specified viewport object;
    false otherwise.
  */
  bool isBackClipOn(const OdRxObject* pViewport) const override;

  /** \details
    Turns on and off back clipping for the specified viewport object (DXF 90,
    bit 0x04).
    \param pViewport [in] Viewport object to set the back clipping state for.
    \param frontClip [in] True to turn back clipping on; false to turn back clipping off.
  */
  void setBackClipOn(OdRxObject* pViewport, bool backClip) const override;

  /** \details
    Indicates whether the front clipping plane passes through the camera
    (DXF 90, bit 0x10).
    \param pViewport [in] Viewport object to get the property of.
    \returns True if the front clipping plane passes through the camera; false
    otherwise.
    \remarks
    If true, the front clipping plane ignores the front clip distance.
  */
  bool isFrontClipAtEyeOn(const OdRxObject* pViewport) const override;

  /** \details
    Sets the property, indicating if the front clipping plane passes through the
    camera (DXF 90, bit 0x10).
    \param pViewport      [in] Viewport object to set the property for.
    \param frontClipAtEye [in] Property value.
    \remarks
    If the property is set to true, the front clipping plane ignores the front
    clip distance.
  */
  void setFrontClipAtEyeOn(OdRxObject* pViewport, bool frontClipAtEye) const override;

  /** \details
    Returns the front clip distance of the specified viewport object (DXF 43).
    \param pViewport [in] Viewport object to get the front clip distance of.
    \returns Front clip distance value.
  */
  double frontClipDistance(const OdRxObject* pViewport) const override;

  /** \details
    Sets the front clip distance for the specified viewport object (DXF 43).
    \param pViewport         [in] Viewport object to set the front clip distance for.
    \param frontClipDistance [in] Front clip distance value.
  */
  void setFrontClipDistance(OdRxObject* pViewport, double frontClipDistance) const override;

  /** \details
    Returns the back clip distance of the specified viewport object (DXF 44).
    \param pViewport [in] Viewport object to get the back clip distance of.
    \returns Back clip distance value.
  */
  double backClipDistance(const OdRxObject* pViewport) const override;

  /** \details
    Sets the back clip distance for the specified viewport object (DXF 44).
    \param pViewport        [in] Viewport object to set the back clip distance for.
    \param backClipDistance [in] Back clip distance value.
  */
  void setBackClipDistance(OdRxObject* pViewport, double backClipDistance) const override;

  /** \details
    Sets the render mode for the specified viewport object (DXF 281).
    \param pViewport  [in] Viewport object to set the render mode for.
    \param renderMode [in] Render mode.
    \remarks
    The renderMode value must be one of the following:

    <table>
    Name                           Value    Description
    kBoundingBox                   -1       Bounding box. For internal use only.
    k2DOptimized                   0        Standard display. Optimized for 2D.
    kWireframe                     1        Standard display. Uses 3D pipeline.
    kHiddenLine                    2        Wireframe display. Hidden lines removed.
    kFlatShaded                    3        Faceted display. One color per face.
    kGouraudShaded                 4        Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe       5        Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe    6        Smooth shaded display with wireframe overlay.
    </table>
  */
  void setRenderMode(OdRxObject* pViewport, OdDb::RenderMode renderMode) const override;

  /** \details
    Returns the render mode of the specified viewport object (DXF 281).
    \param pViewport [in] Viewport object to get the render mode of.
    \returns Render mode.
    \remarks
    The return value is one of the following:

    <table>
    Name                           Value    Description
    kBoundingBox                   -1       Bounding box. For internal use only.
    k2DOptimized                   0        Standard display. Optimized for 2D.
    kWireframe                     1        Standard display. Uses 3D pipeline.
    kHiddenLine                    2        Wireframe display. Hidden lines removed.
    kFlatShaded                    3        Faceted display. One color per face.
    kGouraudShaded                 4        Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe       5        Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe    6        Smooth shaded display with wireframe overlay.
    </table>
  */
  OdDb::RenderMode renderMode(const OdRxObject* pViewport) const override;

  /** \details
    Sets the visual style for the specified viewport object.
    \param pViewport     [in] Viewport object to set the visual style for.
    \param visualStyleId [in] Identifier of the visual style object.
  */
  void setVisualStyle(OdRxObject* pViewport, OdDbStub* visualStyleId) const override;

  /** \details
    Returns the visual style of the specified viewport object.
    \param pViewport [in] Viewport object to get the visual style of.
    \returns Identifier of the visual style object.
  */
  OdDbStub* visualStyle(const OdRxObject* pViewport) const override;

  /** \details
    Sets the view background for the specified viewport object.
    \param pViewport    [in] Viewport object to set the view background for.
    \param backgroundId [in] Identifier of the background object.
  */
  void setBackground(OdRxObject* pViewport, OdDbStub* backgroundId) const override;

  /** \details
    Returns the view background of the specified viewport object.
    \param pViewport [in] Viewport object to get the view background of.
    \returns Identifier of the background object.
  */
  OdDbStub* background(const OdRxObject* pViewport) const override;

  /** \details
    Gets the view extents of the specified viewport object.
    \param pViewport [in] Viewport object to get the view extents of.
    \param extents  [out] View extents of the specified viewport object.
    \returns True if the operation is successful; false otherwise.
  */
  bool viewExtents(const OdRxObject* pViewport, OdGeBoundBlock3d& extents) const override;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwAbstractViewportData object pointers.
*/
typedef OdSmartPtr<OdNwAbstractViewportData> OdNwAbstractViewportDataPtr;

#endif //__NW_ABSTRACT_VIEWPORT_DATA_H__



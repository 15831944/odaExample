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

#ifndef _ODTV_GROUNDSHADOW_H_INCLUDED_
#define _ODTV_GROUNDSHADOW_H_INCLUDED_

#include "TvToolsExport.h"
#include "TvGsView.h"
#include "TvEntity.h"

/** \details
  This class modifies the specified model and view for adding ground shadow.
*/
class ODTVTOOLS_EXPORT OdTvGroundShadow
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details
    Ground plane placement.
  */
  enum AxisPlane
  {
    kZMin,  //Minimum extents XY plane
    kZMax,  //Maximum extents XY plane
    kXMin,  //Minimum extents YZ plane
    kXMax,  //Maximum extents YZ plane
    kYMin,  //Minimum extents XZ plane
    kYMax   //Maximum extents XZ plane
  };

  /** \details
    Constructs an instance with default parameters.
  */
  OdTvGroundShadow();

  /** \details
    Destroys an instance (removes Visualize objects used to create the ground shadow effect, if such objects have been added with the 'add' method but not deleted).
  */
  virtual ~OdTvGroundShadow();

  /** \details
    Modifies the specified model and view for adding ground shadow.
    
    \param modelId              [in] Model for which to add ground shadow.
    \param viewId               [in] View to be modified.
    \param groundPlane          [in] Ground plane placement.
    \param shadowOpacityEffect  [in] Describes how dark the shadow will be (from 0 to 1).
    \returns Returns true if adding was successful, otherwise returns false.
    \remarks
    Steps:
    1) Adds ground plane that receives shadows
    2) Adds pseudo sun light source
    3) Simulates default lighting
  */
  bool add( OdTvModelId modelId, OdTvGsViewId viewId, AxisPlane groundPlane, double shadowOpacityEffect);

  /** \details
    Removes data which is added for ground shadows.
    Simulation steps:
    1) Removes ground plane
    2) Removes pseudo sun light
    3) Resets default lighting
  */
  void remove();

  /** \details
    Emulator options.
    
    \remarks
    This object uses model extents. All offsets calculated from distance between ground plane and opposite plane. Opposite pairs: kZMin - kZMax, kXMin - kXMax, kYMin - kYMax.
    Default plane size is equal to extents corresponding size, size multiplier changes it.
  */
  struct Options
  {
    /** \details
      Ground offset, percents.
    */
    double m_groundOffset;

    /** \details
      Light offset, percents.
    */
    double m_ligthOffset;
   
    /** \details
      Ground plane size multiplier.
    */
    double m_diagMult;
    
    /** \details
      Pseudo sun light intensity.
    */
    double m_lightIntensity;
  };

  /** \details
    Emulator options access.
    
    \returns Returns reference to the emulator options.
  */
  Options& options() { return m_options; }

  /** \details
    Emulator options access.
    
    \returns Returns constant reference to the emulator options.
  */
  const Options& options() const { return m_options; }

  /** \details
    Checks whether the ground shadow is already added.
    
    \returns true if and only if the ground shadow was already added.
  */
  bool isAdded() const { return m_bWasAdded; }

  /** \details
    Checks whether the specified view allows adding a ground shadow.
    
    \returns true if and only if incoming view allow ground shadow (has appropriate render mode or visual style).
  */
  bool isViewAllowGroundShadow(OdTvGsViewId viewId);

  //DOM-IGNORE-BEGIN
protected:
  AxisPlane opposite( AxisPlane plane ) const;

  bool getPlane( const OdTvExtents3d& exts, AxisPlane plane, OdTvPoint& pt, OdTvVector& normal, double* pDiag = NULL );

  bool getCenterPlane( const OdTvExtents3d& exts, AxisPlane plane, OdTvPoint& pt, double* pDiag = NULL );

  double getDistance( const OdTvExtents3d& exts, AxisPlane plane );

  void setDefLight( OdTvLightPtr pLight, const OdGeVector3d& toUp, double rotY, double rotX);

protected:

  Options m_options;
  OdTvModelId m_groundModel;
  OdTvGsViewId m_viewId;
  bool m_bDefLightWasEnebled;
  OdTvGsView::DefaultLightingType m_defType;

  OdTvEntityId m_groundEntityId;
  OdTvEntityId m_sunLightId;
  OdTvMaterialId m_groundMaterialId;
  OdTvEntityId m_defLights[2];

  bool m_bWasAdded;

  //DOM-IGNORE-END
};

#endif //_ODTV_GROUNDSHADOW_H_INCLUDED_

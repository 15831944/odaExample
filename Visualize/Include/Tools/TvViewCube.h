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

#ifndef _ODTV_VIEWCUBE_H_INCLUDED_
#define _ODTV_VIEWCUBE_H_INCLUDED_

#include "TvToolsExport.h"

// Visualize SDK
#include "TvDatabase.h"
#include "TvModel.h"
#include "TvGsView.h"
#include <map>

class OdTvExtendedView;

/** \details
  This class represents a view cube that can be used to set view parameters for an extended view according to sides of a cube.
*/
class ODTVTOOLS_EXPORT OdTvViewCube
{
public:
  /** \details
    Constructor of the OdTvViewCube class.
    
    \param pExtView [in] Pointer to the extended view to associate with this object.
  */
  OdTvViewCube(OdTvExtendedView* pExtView);

  /** \details
    Destructor of the OdTvViewCube class.
  */
  virtual ~OdTvViewCube();

  /** \details
    View Cube side type.
  */
  enum ViewCubeSide
  {
    /** Top view.*/
    kVCTop,
    /** Bottom view.*/
    kVCBottom,
    /** Left view.*/
    kVCLeft,
    /** Right view.*/
    kVCRight,
    /** Front view.*/
    kVCFront,
    /** Back view.*/
    kVCBack,
    /** South-west view.*/
    kVCSWtop,
    /** South-east view.*/
    kVCSEtop,
    /** North-east view.*/
    kVCNEtop,
    /** North-west view.*/
    kVCNWtop,
    /** South-west bottom view.*/
    kVCSWbottom,
    /** South-east bottom view.*/
    kVCSEbottom,
    /** North-east bottom view.*/
    kVCNEbottom,
    /** North-west bottom view.*/
    kVCNWbottom,
    /** Top-left view.*/
    kVCTopLeft,
    /** Top-right view.*/
    kVCTopRight,
    /** Top-front view.*/
    kVCTopFront,
    /** Top-back view.*/
    kVCTopBack,
    /** Bottom-left view.*/
    kVCBottomLeft,
    /** Bottom-right view.*/
    kVCBottomRight,
    /** Bottom-front view.*/
    kVCBottomFront,
    /** Bottom-back view.*/
    kVCBottomBack,
    /** Left-back view.*/
    kVCLeftBack,
    /** Left-front view.*/
    kVCLeftFront,
    /** Right-back view.*/
    kVCRightBack,
    /** Right-front view.*/
    kVCRightFront,
    /** Count of view cube sides.*/
    kVCSidesCount
  };

  /** \details
    Updates View Cube geometry and view.
  */
  virtual void updateViewCube();

  /** \details
    Initializes the View Cube model and view.
  */
  virtual void initialize();

  /** \details
    Synchronizes View Cube view with main view.
  */
  virtual void sync();

  /** \details
    Performs mouse move action for the View Cube object and highlights the appropriate part of the view cube geometry.
    
    \param x [in] Coordinate by X axis in device coordinate space (pixels).
    \param y [in] Coordinate by Y axis in device coordinate space (pixels).
    \return Returns true if the View Cube is selected; otherwise the method returns false.
  */
  virtual bool viewCubeProcessHover(int x, int y);

  /** \details
    Process mouse click action for the View Cube object. All change view parameters according to the view cube geometry.
    
    \param x [in] Coordinate by X axis in device coordinate space (pixels).
    \param y [in] Coordinate by Y axis in device coordinate space (pixels).
    \return Returns true if the View Cube side is changed; otherwise the method returns false.
  */
  virtual bool viewCubeProcessClick(int x, int y);

  /** \details
    Notifies that the size of the main view is changed.
  */
  virtual void onViewResized();

  //DOM-IGNORE-BEGIN
protected:
  /** \details
    Re-creates the geometry for the View Cube.
  */
  void createViewCubeGeometry();

  /** \details
    Re-creates the geometry for the View Cube.
  */
  void highlightViewCubeGeometry(bool bDoIt = true);

  /** \details
    Changes view parameters for main view, View Cube view and WCS view.
  */
  void setViewCubeSideInternal(OdTvViewCube::ViewCubeSide side, bool bZoomToExtents = true);

  /** \details
    Sets up view cube viewport parameters.
  */
  void setupViewportForVCView();

public:

  OdTvExtendedView* m_pExtView;

  // Enable View Cube
  bool        m_bEnableViewCube;

  // Special model for ViewCube object
  OdTvModelId m_TvViewCubeModelId;

  // Special view for the ViewCube
  OdTvGsViewId m_viewCubeViewId;

protected:
  // View Cube selection set
  OdTvSelectionSetPtr m_pVCSSet;

  // Map with geometry id and side
  std::map<OdTvGeometryDataId, ViewCubeSide> m_viewCubeSideMap;

  // Map with text entities and appropriate cube side
  std::map<OdTvEntityId, OdTvEntityId> m_txtCubeSideMap;

  friend class OdTvExtendedView;
  //DOM-IGNORE-END
};

#endif //_ODTV_VIEWCUBE_H_INCLUDED_

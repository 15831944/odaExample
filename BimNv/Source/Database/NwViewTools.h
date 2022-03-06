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


#ifndef TNW_VIEW_TOOLS_H_
#define TNW_VIEW_TOOLS_H_

namespace NwViewTools
{
  enum Enum
  {
  None = 0,// No active tool  
  Select = 1,// Select  
  SelectBox = 2,// Select Box  
  RedlineFreehand = 3,// Redline Freehand  
  RedlineLine = 4,// Redline Line  
  RedlineEllipse = 5,// Redline Ellipse  
  RedlineCloud = 6,// Redline Cloud  
  RedlineLineString = 7,// Redline Line String  
  RedlineTag = 8,// Redline Tag  
  RedlineText = 9,// Redline Text  
  RedlineErase = 10,// Redline Erase  
  RedlineArrow = 11,// Redline Arrow  
  MeasurePointToPoint = 12,// Measure Point To Point  
  MeasurePointToMultiplePoints = 13,// Measure Point To Multiple Points  
  MeasurePointLine = 14,// Measure Point Line  
  MeasureAccumulate = 15,// Measure Accumulate  
  MeasureAngle = 16,// Measure Angle  
  MeasureArea = 17,// Measure Area  
  BasicViewObjectWheel = 18,// Basic View Object Wheel  
  BasicTourBuildingWheel = 19,// Basic Tour Building Wheel  
  FullNavigationWheel = 20,// Full Navigation Wheel  
  MiniViewObjectWheel = 21,// Mini View Object Wheel  
  MiniTourBuildingWheel = 22,// Mini Tour Building Wheel  
  MiniFullNavigationWheel = 23,// Mini Full Navigation Wheel  
  Full2DNavigationWheel = 24,// Full 2D Navigation Wheel  
  CommonPan = 25,// Pan common across all Autodesk products  
  CommonZoom = 26,// Zoom common across all Autodesk products  
  CommonZoomWindow = 27,// Zoom Window common across all Autodesk products  
  CommonOrbit = 28,// Orbit common across all Autodesk products  
  CommonFreeOrbit = 29,// Free Orbit common across all Autodesk products  
  CommonConstrainedOrbit = 30,// Constrained Orbit common across all Autodesk products  
  CommonLookAt = 31,// Look At common across all Autodesk products  
  CommonLookAround = 32,// Look Around common across all Autodesk products  
  CommonWalk = 33,// Walk common across all Autodesk products  
  CommonCenter = 34,// Center common across all Autodesk products  
  NavigateFixed = 35,// Camera fixed in place  
  NavigateFreeLookAround = 36,// Classic Navisworks Free Look Around (Swivel)  
  NavigateFreeOrbit = 37,// Classic Navisworks Free Orbit (Examine)  
  NavigateWalk = 38,// Classic Navisworks Walk  
  NavigateFly = 39,// Classic Navisworks Fly  
  NavigateConstrainedOrbit = 40,// Classic Navisworks Constrained Orbit (Turntable)  
  NavigateZoom = 41,// Classic Navisworks Zoom  
  NavigatePan = 42,// Classic Navisworks Pan  
  NavigateConstrainedPan = 43,// Classic Navisworks Constrained Pan  
  NavigateLookAround = 44,// Clasic Navisworks Look Around (Swivel)  
  NavigateOrbit = 45,// Classic Navisworks Orbit  
  NavigateZoomWindow = 46,// Classic Navisworks Zoom Window (Zoom Box)  
  ZoneCreateCornerToCornerHeight = 47,// Create Zones by a corner to corner defined rectangle with a height.  
  ZoneCreate3PointsHeight = 48,// Create Zones by a 3 points defined rectangle with a height.  
  CustomToolPlugin = 49,// Functionality is provided by a ToolPlugin  
  };
}
#endif  // TNW_VIEW_TOOLS_H_


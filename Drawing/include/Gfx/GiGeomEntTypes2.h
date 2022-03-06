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

#ifndef __OD_GI_GEOM_ENTITY_TYPES2__
#define __OD_GI_GEOM_ENTITY_TYPES2__

enum GeomEntType2
{
  kExtents            ,
  kCircle             ,
  kCircle3pt          ,
  kCircularArc        ,
  kCircularArc3pt     ,
  kPolyline0          ,
  kPolyline1          ,
  kPolygon            ,
  kMesh               ,
  kShell              ,
  kText               ,
  kText2              ,
  kShape              ,
  kNurbs              ,
  kEllipArc           ,
  kRasterImage        ,
  kEnhancedMetafile   ,
  kXline              ,
  kRay                ,
  kSubentColor        ,
  kSubentColorRGB     ,
  kSubentLayer        ,
  kSubentLinetype     ,
  kSubentMarker       ,
  kSubentFillOn       ,
  kSubentFillOff      ,
  kSubentTruecolor    ,
  kSubentLnweight     ,
  kSubentLtscale      ,
  kSubentThickness    ,
  kSubentPlstName     ,
  kPushClip           ,
  kPopClip            ,
  kPushModelTransform ,
  kPushModelTransform2,
  kPopModelTransform  ,
  kDraw               ,
  kPolypoint          ,
  kRowOfDots          ,
  kXline2             ,
  kRay2               ,
  kTTFPolyDraw        ,
  kEdge               ,
  kSubentMaterial     ,
  kSubentMapper       ,
  kSubentMapper0      ,
  kSubentVisualStyle  ,
  kSubentTransparency ,
  kSubentDrawFlags    ,
  kSubentSelectionGeom,
  kSubentShadowFlags  ,
  kSubentSectionable  ,
  kSubentSelFlags     ,
  kSubentSecColor     ,
  kSubentLStyleMods   ,
  kSubentFill         ,

  kHasExtrusion   = 0x100
};

#endif // __OD_GI_GEOM_ENTITY_TYPES2__

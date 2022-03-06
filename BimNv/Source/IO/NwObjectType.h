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

#ifndef __NW_OBJECTTYPE_H__
#define __NW_OBJECTTYPE_H__

#include "NwObject.h"

namespace NwObjectType
{
  enum Enum
  {
    Unknown                       = 0x00,

    Fragment                      = 0x0D,
    ObjectTranslation             = 0x0E,
    ObjectTransRot                = 0x0F,
    ObjectTransRotScale           = 0x10,
    ObjectMatrix                  = 0x11,

    GeometryModelItem             = 0x16,

    DistantLight                  = 0x1B,
    PointLight                    = 0x1C,
    SpotLight                     = 0x1D,

    MaterialAttribute             = 0x1F,
    Partition                     = 0x20,

    TransformAttribute            = 0x27,
    TransAttribute                = 0x28,
    TransRotationAttribute        = 0x29,

    Name                          = 0x34,
    GroupModelItem                = 0x35,
    GraphicMaterial               = 0x36,
    GraphicAppearance             = 0x37,

    //GraphicColorSetRGB_F          = 0x38, 
    //GraphicColorSetRGBA_F         = 0x39, 
    GraphicColorSetRGBA_BYTE      = 0x3A,
    //GraphicNormalSetXYZ_F         = 0x3B,
    GraphicVertexSet              = 0x3C, 
    GraphicTexCoordSetUV_F        = 0x3D, 
    //GraphicTriangleSet            = 0x3E,

    UInt64Attribute               = 0x42,
    NameAttribute                 = 0x46,
    ObjectTransDynamic            = 0x48,
    TextAttribute                 = 0x4C,
    URLAttribute                  = 0x4F,

    GraphicPointSet               = 0x50,
    GraphicLineSet                = 0x51,

    PropertyAttribute             = 0x56,

    BinaryAttribute               = 0x58,
    ElementRecord                 = 0x59,

    PublishAttribute              = 0x5C,
    GeometryRef                   = 0x5D,
    GraphicTriangleSetElement     = 0x5E,
    GraphicLineSetElement         = 0x5F,
    GraphicPointSetElement        = 0x60,

    PresenterMaterialAttribute    = 0x61,
    PresenterTextureSpaceAttribute = 0x62,
    GraphicNormalSetXYZ_S         = 0x64,

    TextStyle                     = 0x66,
    GraphicTextElement            = 0x67,
    GraphicCircleElement          = 0x68,
    GraphicCylinderElement        = 0x69,
    

    GraphicPlotGeometryAttribute  = 0x6A,
    GraphicPlotPaperAttribute     = 0x6B,
    GraphicPlotEmbeddedFontsAttribute = 0x6C,
    GraphicPlotTransform          = 0x6D,
    GraphicPlotAppearance         = 0x6E,
    GraphicPlotArcSegment         = 0x6F,
    GraphicPlotCanvas             = 0x70,
    GraphicPlotCanvasStyle        = 0x71,
    GraphicPlotCircleSegment      = 0x72,
    GraphicPlotColor              = 0x73,
    GraphicPlotEllipseSegment     = 0x74,
    GraphicPlotEmbeddedFont       = 0x75,
    GraphicPlotFontStyle          = 0x76,
    GraphicPlotGeometryBrush      = 0x77,
    GraphicPlotGeometryStream     = 0x78,
    GraphicPlotHatchBrush         = 0x79,
    GraphicPlotImageBrush         = 0x7A,
    GraphicPlotImageHeader        = 0x7B,
    GraphicPlotLinearGradientBrush = 0x7C,
    GraphicPlotPaperStyle         = 0x7D,
    GraphicPlotPath               = 0x7E,
    GraphicPlotPathFigure       = 0x7F,
    GraphicPlotPathFigureStyle = 0x80,
    GraphicPlotPathStreamStyle = 0x81,
    GraphicPlotPathStyle = 0x82,
    GraphicPlotSegmentOfPoints = 0x83,
    GraphicPlotPointListSegment = 0x84,
    GraphicPlotPolyBezierSegment = 0x85,
    GraphicPlotPolyLineSegment = 0x86,
    GraphicPlotPolyQuadraticBezierSegment = 0x87,
    GraphicPlotPolyTriangle = 0x88,
    GraphicPlotRadialGradientBrush = 0x89,
    GraphicPlotResource = 0x8A,
    GraphicPlotSolidColorBrush = 0x8B,
    GraphicPlotStream = 0x8C,
    GraphicPlotStreamEntry = 0x8D,
    GraphicPlotStreamEntryContainer = 0x8E,
    GraphicPlotStroke = 0x8F,
    GraphicPlotText = 0x90,
    GraphicPlotTextLine = 0x91,
    GraphicPlotTextStyle = 0x92,
    GraphicPlotTransform2 = 0x93,
    GraphicPlotVertexColorBrush = 0x94,
    GraphicPlotViewport = 0x95,

    GraphicPlotViewportStyle = 0xA8,
    GraphicPlotCoreShape = 0xA9,
    GraphicPlotGeomRef = 0xAA,
    GraphicPlotCoreShapeRepresentation = 0xAB,
    GraphicPlotCoreShapePathFigure = 0xAC,
    GraphicPlotPathFigure2 = 0xAD,
    GraphicPlotSegment = 0xAE,
    GraphicPlotCoreShapeText = 0xAF,
    GraphicPlotPathFigureAppearance = 0xB0,
    GraphicPlotTextAppearance = 0xB1,
    GraphicPlotBrush = 0xB2,
    GraphicPlotHatchPattern = 0xB3,

    GuidAttribute                 = 0xB4, // NWS-410
    GraphicExternalGeometry       = 0xB5, // TODO: NWS-298
    GraphicBundle                 = 0xB6, // TODO: NWS-297
    GraphicBundleSchema           = 0xB7,
    GraphicJsonBundle             = 0xB9,
    GraphicMaterialAttribute      = 0xC8
  };
}

NwObjectType::Enum getObjectType(const OdNwObjectPtr& aObj);


#endif //__NW_OBJECTTYPE_H__

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
#ifndef __DGDATABASEPROPS__H__
#define __DGDATABASEPROPS__H__

#include "DgProperties.h"
#include "DgDatabase.h"

// Class OdDgDatabase properties. Category "Database Properties":

// Category "Database Properties"

/* 1  - FileName                             */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, FileName, OdString, "Database Properties", 1, "Path to current database file");
/* 2  - MajorVersion                         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, MajorVersion, OdUInt32, "Database Properties", 2, "Major version of current database file");
/* 3  - MinorVersion                         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, MinorVersion, OdUInt32, "Database Properties", 3, "Minor version of current database file");
/* 4  - LevelTableId                         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, LevelTableId,OdDgElementId,"Database Properties",4,"Level table element id");
/* 5  - LineStyleTableId                     */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, LineStyleTableId, OdDgElementId, "Database Properties", 5, "Line style table element id");
/* 6  - TextStyleTableId                     */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, TextStyleTableId, OdDgElementId, "Database Properties", 6, "Text style table element id");
/* 7  - FontTableId                          */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, FontTableId, OdDgElementId, "Database Properties", 7, "Font table element id");
/* 8  - MaterialTableId                      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, MaterialTableId, OdDgElementId, "Database Properties", 8, "Material table element id");
/* 9  - ColorPalette                         */ ODRX_DECLARE_RX_PROPERTY_COLLECTION(OdDgDatabase, ColorPalette, OdCmEntityColor, "Database Properties", 9, "Current color palette");
/* 10 - DisplayStyleTableId                  */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, DisplayStyleTableId, OdDgElementId, "Database Properties", 10, "Display style table element id");
/* 11 - LevelFilterTableId                   */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase,LevelFilterTableId,OdDgElementId,"Database Properties",11,"Level table element id");
/* 12 - Models                               */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_TREE(OdDgDatabase,Models,OdDgElementId,"Database Properties",12,"Array of model ids","Model");
/* 13 - SharedCellDefinitions                */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase,SharedCellDefinitions,OdDgElementId,"Database Properties",13,"Array of shared cell definition ids", false);
/* 14 - RetainOriginalThumbnailBitmap        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, RetainOriginalThumbnailBitmap, bool, "Database Properties", 14, "State of the RetainOriginalThumbnailBitmap flag", "");
/* 15 - DimStyleTableId                      */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, DimStyleTableId, OdDgElementId, "Database Properties", 15, "Dim style table element id");
/* 16 - MultilineStyleTableId                */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, MultilineStyleTableId, OdDgElementId, "Database Properties", 16, "Multiline style table element id");
/* 17 - RegApps                              */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, RegApps, OdDgElementId, "Database Properties", 17, "Collection of reg apps", false);
/* 18 - ViewGroups                           */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, ViewGroups, OdDgElementId, "Database Properties", 18, "Collection of view groups", false);
/* 19 - NamedViews                           */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, NamedViews, OdDgElementId, "Database Properties", 19, "Collection of named views", false);
/* 20 - PrintStyles                          */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, PrintStyles, OdDgElementId, "Database Properties", 20, "Collection of print styles", false);
/* 21 - ModelTableId                         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, ModelTableId, OdDgElementId, "Database Properties", 21, "Model table element id");
/* 22 - TagDefinitions                       */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, TagDefinitions, OdDgElementId, "Database Properties", 22, "Collection of tag definition sets", false);
/* 23 - ElementTemplates                     */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, ElementTemplates, OdDgElementId, "Database Properties", 23, "Collection of tag element templates", false);
/* 24 - LinkSets                             */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, LinkSets, OdDgElementId, "Database Properties", 24, "Collection of link sets", false);
/* 25 - NonModelElementCollection            */ ODRX_DECLARE_RX_PROPERTY_COLLECTION(OdDgDatabase, NonModelElementCollection, OdDgElementId, "Database Properties", 25, "Collection of non-model elements");
/* 26 - EnvironmentMaps                      */ ODRX_DECLARE_RX_PROPERTY_COLLECTION(OdDgDatabase, EnvironmentMaps, OdDgEnvironmentMap, "Database Properties", 26, "Collection of environment maps");
/* 27 - PrototypeElements                    */ ODRX_DECLARE_RX_PROPERTY_COLLECTION_NAMED(OdDgDatabase, PrototypeElements, OdDgElementId, "Database Properties", 27, "Collection of prototype elements", false);
/* 28 - DictionaryTableId                    */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, DictionaryTableId, OdDgElementId, "Database Properties", 28, "Dictionary table id");
/* 29 - ControlFlags                         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, ControlFlags, OdUInt32, "Database Properties", 29, "Control flags of current database file");
/* 30 - LockFlags                            */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, LockFlags, OdUInt16, "Database Properties", 30, "Lock flags of current database file");
/* 31 - ExtLockFlags                         */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, ExtLockFlags, OdUInt32, "Database Properties", 31, "Extended lock flags of current database file");
/* 32 - SaveMaterialAssignmentTableFileFlag  */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SaveMaterialAssignmentTableFileFlag, bool, "Database Properties", 32, "State of the SaveMaterialAssignmentTableFile flag", "");
/* 33 - ActAngle                             */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActAngle, double, "Database Properties", 33, "Active angle value", "");
/* 34 - AngleRnd                             */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleRnd, double, "Database Properties", 34, "Angle round-off", "");
/* 35 - XActScale                            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, XActScale, double, "Database Properties", 35, "Active scale in x-axis", "");
/* 36 - YActScale                            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, YActScale, double, "Database Properties", 36, "Active scale in y-axis", "");
/* 37 - ZActScale                            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ZActScale, double, "Database Properties", 37, "Active scale in z-axis", "");
/* 38 - RoundScale                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, RoundScale, double, "Database Properties", 38, "Round scale", "");
/* 39 - Azimuth                              */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, Azimuth, double, "Database Properties", 39, "Azimuth true north angle", "");
/* 40 - ExtMin                               */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ExtMin, OdGePoint3d, "Database Properties", 40, "ExtMin", "");
/* 41 - ExtMax                               */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ExtMax, OdGePoint3d, "Database Properties", 41, "ExtMax", "");
/* 42 - ActiveLevelEntryId                   */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveLevelEntryId, OdDgElementId, "Database Properties", 42, "Active level entry id", "");
/* 43 - ActiveLineStyleEntryId               */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveLineStyleEntryId, OdDgElementId, "Database Properties", 43, "Active linestyle entry id", "");
/* 44 - ActiveLineWeight                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveLineWeight, OdDb::LineWeight, "Database Properties", 44, "Active line weight", "");
/* 45 - ActiveColor                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveColorIndex, OdUInt32, "Database Properties", 45, "Active color index", "");
/* 46 - FillColorIndex                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, FillColor, OdCmEntityColor, "Database Properties", 46, "Fill color index", "");
/* 47 - ActiveProps                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveProps, OdUInt16, "Database Properties", 47, "Element properties word", "");
/* 48 - LineStyleInfo                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, LineStyleInfo, OdDgLineStyleInfo, "Database Properties", 48, "Current line style", "");
/* 49 - LineStyleScale                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, LineStyleScale, double, "Database Properties", 49, "Linestyle scale", "");
/* 50 - MultiLineFlags                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, MultiLineFlags, OdUInt16, "Database Properties", 50, "Multiline flags", "");
/* 51 - OriginalFileVersion                  */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, OriginalFileVersion, OdUInt32, "Database Properties", 51, "Original file version");
/* 52 - ActiveTextStyleEntryId               */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveTextStyleEntryId, OdDgElementId, "Database Properties", 52, "Last selected text style id", "");
/* 53 - TextScaleLock                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, TextScaleLock, OdUInt16, "Database Properties", 53, "Lock fo text scale", "");
/* 54 - ActiveViewGroupId                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveViewGroupId, OdDgElementId, "Database Properties", 54, "Active viewgroup Id", "");
/* 55 - ActiveModelId                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveModelId, OdDgElementId, "Database Properties", 55, "Active model Id", "");
/* 56 - AngleFormat                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleFormat, OdDgDimTextFormat::AngleValueDisplayMode, "Database Properties", 56, "Current readout angle format", "");
/* 57 - AngleReadoutPrec                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleReadoutPrec, OdDg::OdDgDecimalAccuracy, "Database Properties", 57, "Current angle readout prec", "");
/* 58 - AngleReadoutDirectionMode            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleReadoutDirectionMode, OdDg::OdDgAngleReadoutDirectionMode, "Database Properties", 58, "Current angle readout direction mode", "");
/* 59 - AngleReadoutBaseAngle                */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleReadoutBaseAngle, double, "Database Properties", 59, "Angle readout base angle", "");
/* 60 - AngleReadoutClockwiseFlag            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleReadoutClockwiseFlag, bool, "Database Properties", 60, "State of the AngleReadoutClockwise flag", "");
/* 61 - TentativeMode                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, TentativeMode, OdUInt16, "Database Properties", 61, "State of the TentativeMode flag", "");
/* 62 - TentativeSubMode                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, TentativeSubMode, OdUInt16, "Database Properties", 62, "State of the TentativeSubMode flag", "");
/* 63 - KeyPointDividend                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, KeyPointDividend, OdUInt16, "Database Properties", 63, "Divisor for keypoint snapping", "");
/* 64 - DefaultSnapMode                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, DefaultSnapMode, OdUInt16, "Database Properties", 64, "Default mode for snapping", "");
/* 65 - SystemClass                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SystemClass, OdUInt16, "Database Properties", 65, "System class bitmap", "");
/* 66 - DMRSFlag                             */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, DMRSFlag, OdUInt8, "Database Properties", 66, "DMRS flag", "");
/* 67 - DMRSLinkageGenerationMode            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, DMRSLinkageGenerationMode, OdUInt16, "Database Properties", 67, "DMRS linkage generation mode", "");
/* 68 - AutoDimFlags                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AutoDimFlags, OdUInt16, "Database Properties", 68, "Automatic dimensioning flags", "");
/* 69 - AssocLockMask                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AssocLockMask, OdUInt16, "Database Properties", 69, "Association lock mask", "");
/* 70 - ActiveCell                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveCell, OdString, "Database Properties", 70, "Active cell name", "");
/* 71 - ActiveTermCell                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveTermCell, OdString, "Database Properties", 71, "Active terminator cell name", "");
/* 72 - ActiveTermScale                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActiveTermScale, double, "Database Properties", 72, "Active line terminator scale", "");
/* 73 - ActivePatternCell                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePatternCell, OdString, "Database Properties", 73, "Active patterning cell", "");
/* 74 - ActivePatternScale                   */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePatternScale, double, "Database Properties", 74, "Active patterning scale", "");
/* 75 - ActivePatternAngle                   */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePatternAngle, double, "Database Properties", 75, "Active patterning angle", "");
/* 76 - ActivePatternAngle2                  */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePatternAngle2, double, "Database Properties", 76, "Active patterning angle (for x-hatch)", "");
/* 77 - ActivePatternRowSpacing              */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePatternRowSpacing, double, "Database Properties", 77, "Active patterning row spacing", "");
/* 78 - ActivePatternColumnSpacing           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePatternColumnSpacing, double, "Database Properties", 78, "Active patterning column spacing", "");
/* 79 - PatternTolerance                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, PatternTolerance, double, "Database Properties", 79, "Stroke tolerance for patterns", "");
/* 80 - ActivePointType                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePointType, OdUInt32, "Database Properties", 80, "Active point type (0 - none, 1 - symbol, 2 - cell)", "");
/* 81 - ActivePointSymbol                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePointSymbol, OdUInt16, "Database Properties", 81, "Active point character (if symbol)", "");
/* 82 - ActivePointCell                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ActivePointCell, OdString, "Database Properties", 82, "Active point cell name", "");
/* 83 - AreaPatternAngle                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AreaPatternAngle, double, "Database Properties", 83, "Active area patterning angle", "");
/* 84 - AreaPatternRowSpacing                */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AreaPatternRowSpacing, double, "Database Properties", 84, "Active area patterning row spacing", "");
/* 85 - AreaPatternColumnSpacing             */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AreaPatternColumnSpacing, double, "Database Properties", 85, "Active area patterning column spacing", "");
/* 86 - ReservedCell                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ReservedCell, double, "Database Properties", 86, "Reserved for future cell settings", "");
/* 87 - ZRange2dLow                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ZRange2dLow, double, "Database Properties", 87, "Z range of 2d elements for this value (low)", "");
/* 88 - ZRange2dHigh                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ZRange2dHigh, double, "Database Properties", 88, "Z range of 2d elements for this value (high)", "");
/* 89 - StreamDelta                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, StreamDelta, double, "Database Properties", 89, "Stream delta", "");
/* 90 - StreamTolerance                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, StreamTolerance, double, "Database Properties", 90, "Stream Tolerance", "");
/* 91 - AngleTolerance                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AngleTolerance, double, "Database Properties", 91, "Angle threshold (radians)", "");
/* 92 - AreaTolerance                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AreaTolerance, double, "Database Properties", 92, "Area threshold (radians)", "");
/* 93 - HighlightColorIndex                  */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, HighlightColorIndex, OdUInt32, "Database Properties", 93, "Highlight color", "");
/* 94 - XorColorIndex                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, XorColorIndex, OdUInt32, "Database Properties", 94, "Xor color", "");
/* 95 - AxisLockAngle                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AxisLockAngle, double, "Database Properties", 95, "Axis lock angle", "");
/* 96 - AxisLockOrigin                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AxisLockOrigin, double, "Database Properties", 96, "Axis lock origin", "");
/* 97 - ChamferDist1                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ChamferDist1, double, "Database Properties", 97, "Chamfer distance 1", "");
/* 98 - ChamferDist2                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ChamferDist2, double, "Database Properties", 98, "Chamfer distance 2", "");
/* 99 - AutochainTolerance                   */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AutochainTolerance, double, "Database Properties", 99, "Autochain Tolerance", "");
/* 100 - ConslineDistance                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ConslineDistance, double, "Database Properties", 100, "Consline distance", "");
/* 101 - ArcRadius                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArcRadius, double, "Database Properties", 101, "Arc radius", "");
/* 102 - ArcLength                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArcLength, double, "Database Properties", 102, "Arc length", "");
/* 103 - ConeRadius1                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ConeRadius1, double, "Database Properties", 103, "Cone radius 1", "");
/* 104 - ConeRadius2                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ConeRadius2, double, "Database Properties", 104, "Cone radius 2", "");
/* 105 - PolygonRadius                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, PolygonRadius, double, "Database Properties", 105, "PolygonRadius", "");
/* 106 - SurrevAngle                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SurrevAngle, double, "Database Properties", 106, "SurrevAngle", "");
/* 107 - ExtendDistance                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ExtendDistance, double, "Database Properties", 107, "ExtendDistance", "");
/* 108 - FilletRadius                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, FilletRadius, double, "Database Properties", 108, "FilletRadius", "");
/* 109 - CopparDistance                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, CopparDistance, double, "Database Properties", 109, "CopparDistance", "");
/* 110 - ArrayRowDistance                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayRowDistance, double, "Database Properties", 110, "ArrayRowDistance", "");
/* 111 - ArrayColumnDistance                 */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayColumnDistance, double, "Database Properties", 111, "ArrayColumnDistance", "");
/* 112 - ArrayFillAngle                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayFillAngle, double, "Database Properties", 112, "ArrayFillAngle", "");
/* 113 - PointDistance                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, PointDistance, double, "Database Properties", 113, "PointDistance", "");
/* 114 - PolygonEdges                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, PolygonEdges, OdUInt16, "Database Properties", 114, "PolygonEdges", "");
/* 115 - PointsBetween                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, PointsBetween, OdUInt16, "Database Properties", 115, "PointsBetween", "");
/* 116 - ArrayNumItems                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayNumItems, OdUInt16, "Database Properties", 116, "ArrayNumItems", "");
/* 117 - ArrayNumRows                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayNumRows, OdUInt16, "Database Properties", 117, "ArrayNumRows", "");
/* 118 - ArrayNumCols                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayNumCols, OdUInt16, "Database Properties", 118, "ArrayNumCols", "");
/* 119 - ArrayRotate                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArrayRotate, OdUInt8, "Database Properties", 119, "ArrayRotate", "");
/* 120 - BSplineOrder                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, BSplineOrder, OdUInt8, "Database Properties", 120, "BSplineOrder", "");
/* 121 - DispAttrType                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, DispAttrType, OdUInt8, "Database Properties", 121, "DispAttrType", "");
/* 122 - AmbientFlag                         */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AmbientFlag, bool, "Database Properties", 122, "AmbientFlag", "");
/* 123 - FlashbulbFlag                       */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, FlashbulbFlag, bool, "Database Properties", 123, "FlashbulbFlag", "");
/* 124 - SolarFlag                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarFlag, bool, "Database Properties", 124, "SolarFlag", "");
/* 125 - SolarShadowsFlag                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarShadowsFlag, bool, "Database Properties", 125, "SolarShadowsFlag", "");
/* 126 - SolarShadowResolution               */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarShadowResolution, OdUInt16, "Database Properties", 126, "SolarShadowResolution", "");
/* 127 - KeepSolarDirectionFlag              */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, KeepSolarDirectionFlag, bool, "Database Properties", 127, "KeepSolarDirectionFlag", "");
/* 128 - Latitude                            */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, Latitude, OdAngleCoordinate, "Database Properties", 128, "Latitude", "");
/* 129 - Longitude                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, Longitude, OdAngleCoordinate, "Database Properties", 129, "Longitude", "");
/* 130 - SolarTime                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarTime, OdUInt32, "Database Properties", 130, "SolarTime", "");
/* 131 - SolarYear                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarYear, OdUInt32, "Database Properties", 131, "SolarYear", "");
/* 132 - GMTOffset                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, GMTOffset, double, "Database Properties", 132, "GMTOffset", "");
/* 133 - SolarDirection                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarDirection, OdGePoint3d, "Database Properties", 133, "SolarDirection", "");
/* 134 - SolarVectorOverride                 */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarVectorOverride, OdGePoint3d, "Database Properties", 134, "SolarVectorOverride", "");
/* 135 - SolarIntensity                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SolarIntensity, OdDgLightColor, "Database Properties", 135, "SolarIntensity", "");
/* 136 - AmbientIntensity                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, AmbientIntensity, OdDgLightColor, "Database Properties", 136, "AmbientIntensity", "");
/* 137 - FlashIntensity                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, FlashIntensity, OdDgLightColor, "Database Properties", 137, "FlashIntensity", "");
/* 138 - NearDepthDensity                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, NearDepthDensity, double, "Database Properties", 138, "NearDepthDensity", "");
/* 139 - FarDepthDensity                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, FarDepthDensity, double, "Database Properties", 139, "FarDepthDensity", "");
/* 140 - NearDepthDistance                   */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, NearDepthDistance, double, "Database Properties", 140, "NearDepthDistance", "");
/* 141 - HazeColor                           */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, HazeColor, OdDgLightColor, "Database Properties", 141, "Color of fog", "");
/* 142 - ShadowTolerance                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ShadowTolerance, double, "Database Properties", 142, "ShadowTolerance", "");
/* 143 - StrokeTolerance                     */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, StrokeTolerance, double, "Database Properties", 143, "StrokeTolerance", "");
/* 144 - MaxPolygonSize                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, MaxPolygonSize, OdInt16, "Database Properties", 144, "MaxPolygonSize", "");
/* 145 - ArcMinimum                          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ArcMinimum, OdInt16, "Database Properties", 145, "ArcMinimum", "");
/* 146 - ExactHLineAccuracy                  */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ExactHLineAccuracy, OdUInt32, "Database Properties", 146, "ExactHLineAccuracy", "");
/* 147 - ExactHLineTolerance                 */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, ExactHLineTolerance, double, "Database Properties", 147, "ExactHLineTolerance", "");
/* 148 - SelectionHighlightOverride          */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SelectionHighlightOverride, OdUInt32, "Database Properties", 148, "SelectionHighlightOverride", "");
/* 149 - SelectionHighlightColor             */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, SelectionHighlightColor, OdUInt32, "Database Properties", 149, "SelectionHighlightColor", "");
/* 150 - CellFileName                        */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, CellFileName, OdString, "Database Properties", 150, "CellFileName", "");
/* 151 - BackgroundFile                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, BackgroundFile, OdString, "Database Properties", 151, "BackgroundFile", "");
/* 152 - DesignCenterUnits                   */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, DesignCenterUnits, OdDg::OdDgDesignCenterUnits, "Database Properties", 152, "Design center units", "");
/* 153 - NextGraphicGroup                    */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, NextGraphicGroup, OdUInt32, "Database Properties", 153, "NextGraphicGroup", "");
/* 154 - Handseed                            */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, Handseed, OdDbHandle, "Database Properties", 154, "Handseed");
/* 155 - LastSaveTime                        */ ODRX_DECLARE_RX_PROPERTY_RO(OdDgDatabase, LastSaveTime, OdTimeStamp, "Database Properties", 155, "Last save time");
/* 156 - DefaultModelId                      */ ODRX_DECLARE_RX_PROPERTY(OdDgDatabase, DefaultModelId, OdDgElementId, "Database Properties", 156, "Default model id", "");



#endif // __DGDATABASEPROPS__H__

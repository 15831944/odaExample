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

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"
#include "ExPrintConsole.h"

#include "sdai.h"
#include "daiRepository.h"
#include "daiHeaderSection.h"

#include "IfcCore.h"
#include "IfcExamplesCommon.h"
#include "RailProfileDef.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  using namespace OdIfc;                                                             \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4x3_RC4Module);                        \
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4x3RC4ModuleName, OdIfc4x3_RC4Module)          \
  ODRX_END_STATIC_MODULE_MAP()
#endif

SdaiBoolean assignGlobalId(SdaiAppInstance root)
{
  if (sdaiIsKindOfBN(root, "IfcRoot") == sdaiFALSE)
    return sdaiFALSE;

  SdaiString globalId = OdIfcGUID::generate();
  sdaiPutAttrBN(root, "GlobalId", sdaiSTRING, globalId);

  return sdaiTRUE;
}

SdaiAppInstance appendCartesianPoint2D(SdaiModel model, double x, double y)
{
  SdaiAppInstance cartesianPoint2D = sdaiCreateInstanceBN(model, "IfcCartesianPoint");
  SdaiList coordinates = sdaiCreateAggrBN(cartesianPoint2D, "Coordinates");
  sdaiPutAggrByIndex(coordinates, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(coordinates, 1, sdaiREAL, y);
  return cartesianPoint2D;
}

SdaiAppInstance appendCartesianPoint3D(SdaiModel model, double x, double y, double z)
{
  SdaiAppInstance cartesianPoint3D = sdaiCreateInstanceBN(model, "IfcCartesianPoint");
  SdaiList coordinates = sdaiCreateAggrBN(cartesianPoint3D, "Coordinates");
  sdaiPutAggrByIndex(coordinates, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(coordinates, 1, sdaiREAL, y);
  sdaiPutAggrByIndex(coordinates, 2, sdaiREAL, z);
  return cartesianPoint3D;
}

SdaiAppInstance appendDirection2D(SdaiModel model, double x, double y)
{
  SdaiAppInstance direction2D = sdaiCreateInstanceBN(model, "IfcDirection");
  SdaiList directionRatios = sdaiCreateAggrBN(direction2D, "DirectionRatios");
  sdaiPutAggrByIndex(directionRatios, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(directionRatios, 1, sdaiREAL, y);
  return direction2D;
}

SdaiAppInstance appendDirection3D(SdaiModel model, double x, double y, double z)
{
  SdaiAppInstance direction3D = sdaiCreateInstanceBN(model, "IfcDirection");
  SdaiList directionRatios = sdaiCreateAggrBN(direction3D, "DirectionRatios");
  sdaiPutAggrByIndex(directionRatios, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(directionRatios, 1, sdaiREAL, y);
  sdaiPutAggrByIndex(directionRatios, 2, sdaiREAL, z);
  return direction3D;
}

SdaiAppInstance appendAxis2Placement2D(SdaiModel model, SdaiAppInstance location, SdaiAppInstance refDirection = NULL)
{
  SdaiAppInstance axis2Placement2D = sdaiCreateInstanceBN(model, "IfcAxis2Placement2D");
  sdaiPutAttrBN(axis2Placement2D, "Location", sdaiINSTANCE, location);
  if (refDirection)
    sdaiPutAttrBN(axis2Placement2D, "RefDirection", sdaiINSTANCE, refDirection);
  return axis2Placement2D;
}

SdaiAppInstance appendAxis2Placement3D(SdaiModel model, SdaiAppInstance location, SdaiAppInstance axis = NULL, SdaiAppInstance refDirection = NULL)
{
  SdaiAppInstance axis2Placement3D = sdaiCreateInstanceBN(model, "IfcAxis2Placement3D");
  sdaiPutAttrBN(axis2Placement3D, "Location", sdaiINSTANCE, location);
  if (axis)
    sdaiPutAttrBN(axis2Placement3D, "Axis", sdaiINSTANCE, axis);
  if (refDirection)
    sdaiPutAttrBN(axis2Placement3D, "RefDirection", sdaiINSTANCE, refDirection);
  return axis2Placement3D;
}

SdaiAppInstance appendGeometricRepresentationContext(SdaiModel model,
  SdaiString contextIdentifier, SdaiString contextType, SdaiInteger coordinateSpaceDimension,
  SdaiReal precision, SdaiAppInstance worldCoordinateSystem, SdaiAppInstance trueNorth = NULL)
{
  SdaiAppInstance geometricRepresentationContext = sdaiCreateInstanceBN(model, "IfcGeometricRepresentationContext");
  sdaiPutAttrsBN(geometricRepresentationContext, 5,
    "ContextIdentifier", sdaiSTRING, contextIdentifier,
    "ContextType", sdaiSTRING, contextType,
    "CoordinateSpaceDimension", sdaiINTEGER, coordinateSpaceDimension,
    "Precision", sdaiREAL, precision,
    "WorldCoordinateSystem", sdaiINSTANCE, worldCoordinateSystem
  );
  if (trueNorth)
    sdaiPutAttrBN(geometricRepresentationContext, "TrueNorth", sdaiINSTANCE, trueNorth);
  return geometricRepresentationContext;
}

SdaiAppInstance appendSiUnit(SdaiModel model, SdaiEnum unitType, SdaiEnum prefix, SdaiEnum name)
{
  ODA_ASSERT(unitType);
  ODA_ASSERT(name);

  SdaiAppInstance SiUnit = sdaiCreateInstanceBN(model, "ifcsiunit");
  sdaiPutAttrBN(SiUnit, "UnitType", sdaiENUM, unitType);
  if (prefix != NULL)
    sdaiPutAttrBN(SiUnit, "Prefix", sdaiENUM, prefix);
  sdaiPutAttrBN(SiUnit, "Name", sdaiENUM, name);
  return SiUnit;
}

SdaiAppInstance appendUnitAssignment(SdaiModel model)
{
  //
  // IfcUnitAssignment
  //
  SdaiAppInstance unitAssignment = sdaiCreateInstanceBN(model, "IfcUnitAssignment");
  SdaiSet units = sdaiCreateAggrBN(unitAssignment, "Units");

  SdaiADB adbIfcUnit = sdaiCreateEmptyADB();
  SdaiString typePath[] = { "IfcNamedUnit" };
  sdaiPutADBTypePath(adbIfcUnit, 1, typePath);

  // Warning: inconsistency of values oftenly, pathways better to define in meters (architectural),
  // however millimeters are typical (mechanical) units for [rail] profiles. So in case of mechanical
  // units they always should be scaled.
  sdaiPutADBValue(adbIfcUnit, sdaiINSTANCE, appendSiUnit(model, "LENGTHUNIT", NULL /* "MILLI" */, "METRE"));
  sdaiAdd(units, sdaiADB, adbIfcUnit);

  SdaiAppInstance planeAngleUnit = appendSiUnit(model, "PLANEANGLEUNIT", NULL, "RADIAN");
  sdaiPutADBValue(adbIfcUnit, sdaiINSTANCE, planeAngleUnit);
  sdaiAdd(units, sdaiADB, adbIfcUnit);

  sdaiPutADBValue(adbIfcUnit, sdaiINSTANCE, appendSiUnit(model, "AREAUNIT", NULL, "SQUARE_METRE"));
  sdaiAdd(units, sdaiADB, adbIfcUnit);

  sdaiPutADBValue(adbIfcUnit, sdaiINSTANCE, appendSiUnit(model, "VOLUMEUNIT", NULL, "CUBIC_METRE"));
  sdaiAdd(units, sdaiADB, adbIfcUnit);

  

  SdaiAppInstance measureWithUnit = sdaiCreateInstanceBN(model, "IfcMeasureWithUnit");
  SdaiADB adbPlaneAngleMeasure = sdaiCreateEmptyADB();
  SdaiString typePathPlaneAngleMeasure[] = { "IfcPlaneAngleMeasure" };
  sdaiPutADBTypePath(adbPlaneAngleMeasure, 1, typePathPlaneAngleMeasure);
  const double toRadians = OdaPI / 180.;
  sdaiPutADBValue(adbPlaneAngleMeasure, sdaiREAL, toRadians);
  sdaiPutAttrsBN(measureWithUnit, 2,
    "ValueComponent", sdaiADB, adbPlaneAngleMeasure,
    "UnitComponent", sdaiINSTANCE, planeAngleUnit);
  sdaiDeleteADB(adbPlaneAngleMeasure);

  SdaiAppInstance dimensionalExponents = sdaiCreateInstanceBN(model, "IfcDimensionalExponents");
  sdaiPutAttrsBN(dimensionalExponents, 7,
    "LengthExponent", sdaiINTEGER, 0,
    "MassExponent", sdaiINTEGER, 0,
    "TimeExponent", sdaiINTEGER, 0,
    "ElectricCurrentExponent", sdaiINTEGER, 0,
    "ThermodynamicTemperatureExponent", sdaiINTEGER, 0,
    "AmountOfSubstanceExponent", sdaiINTEGER, 0,
    "LuminousIntensityExponent", sdaiINTEGER, 0
  );

  SdaiAppInstance conversionBasedUnit = sdaiCreateInstanceBN(model, "IfcConversionBasedUnit");
  sdaiPutAttrsBN(conversionBasedUnit, 4,
    "Dimensions", sdaiINSTANCE, dimensionalExponents,
    "UnitType", sdaiENUM, "PLANEANGLEUNIT",
    "Name", sdaiSTRING, "DEGREE",
    "ConversionFactor", sdaiINSTANCE, measureWithUnit
  );

  sdaiAdd(units, sdaiINSTANCE, conversionBasedUnit);

  return unitAssignment;
}

SdaiAppInstance appendRelAggregates(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName)
{
  SdaiAppInstance ownerHistory = NULL;
  sdaiGetAttrBN(relating, "OwnerHistory", sdaiINSTANCE, &ownerHistory);

  SdaiAppInstance relAggregates = sdaiCreateInstanceBN(model, "IfcRelAggregates");

  assignGlobalId(relAggregates);

  if (ownerHistory)
    sdaiPutAttrBN(relAggregates, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  sdaiPutAttrBN(relAggregates, "RelatingObject", sdaiINSTANCE, relating);

  SdaiAppInstance related = sdaiCreateInstanceBN(model, relatedEntityName);
  if (ownerHistory)
    sdaiPutAttrBN(related, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  SdaiSet relatedObjects = sdaiCreateAggrBN(relAggregates, "RelatedObjects");
  sdaiAdd(relatedObjects, sdaiINSTANCE, related);

  return related;
}

SdaiAppInstance appendRelContainedInSpatialStructure(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName)
{
  //#22 = IFCRELCONTAINEDINSPATIALSTRUCTURE('3Rgz1HUxT6_RLwqCLc1YQg', $, $, $, (#23), #14);

  SdaiAppInstance ownerHistory = NULL;
  sdaiGetAttrBN(relating, "OwnerHistory", sdaiINSTANCE, &ownerHistory);

  SdaiAppInstance relContainedInSpatialStructure = sdaiCreateInstanceBN(model, "IfcRelContainedInSpatialStructure");

  assignGlobalId(relContainedInSpatialStructure);

  if (ownerHistory)
    sdaiPutAttrBN(relContainedInSpatialStructure, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  sdaiPutAttrBN(relContainedInSpatialStructure, "RelatingStructure", sdaiINSTANCE, relating);

  SdaiAppInstance related = sdaiCreateInstanceBN(model, relatedEntityName);
  if (ownerHistory)
    sdaiPutAttrBN(related, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  SdaiSet relatedElements = sdaiCreateAggrBN(relContainedInSpatialStructure, "RelatedElements");
  sdaiAdd(relatedElements, sdaiINSTANCE, related);

  return related;
}

SdaiAppInstance appendRelNests(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName, SdaiAppInstance &relNests)
{
  //#22 = IFCRELCONTAINEDINSPATIALSTRUCTURE('3Rgz1HUxT6_RLwqCLc1YQg', $, $, $, (#23), #14);

  SdaiAppInstance ownerHistory = NULL;
  sdaiGetAttrBN(relating, "OwnerHistory", sdaiINSTANCE, &ownerHistory);

  if (relNests == nullptr)
  {
    relNests = sdaiCreateInstanceBN(model, "IfcRelNests");
    assignGlobalId(relNests);
  }

  if (ownerHistory)
    sdaiPutAttrBN(relNests, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  sdaiPutAttrBN(relNests, "RelatingObject", sdaiINSTANCE, relating);

  SdaiAppInstance related = sdaiCreateInstanceBN(model, relatedEntityName);
  if (ownerHistory)
    sdaiPutAttrBN(related, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  SdaiList relatedObjects = nullptr;
  sdaiGetAttrBN(relNests, "RelatedObjects", sdaiAGGR, &relatedObjects);
  if (relatedObjects == nullptr)
    relatedObjects = sdaiCreateAggrBN(relNests, "RelatedObjects");

  sdaiPutAggrByIndex(relatedObjects, sdaiGetMemberCount(relatedObjects), sdaiINSTANCE, related);

  return related;
}


SdaiAppInstance appendAsymmetricIShapeProfileDef(SdaiModel model,

  SdaiString type, SdaiString name, SdaiAppInstance position,

  double bottomFlangeWidth,
  double overallDepth,
  double webThickness,
  double bottomFlangeThickness,
  double topFlangeWidth,

  double bottomFlangeFilletRadius  = OdDAI::Consts::OdNan,
  double topFlangeThickness = OdDAI::Consts::OdNan,
  double topFlangeFilletRadius = OdDAI::Consts::OdNan,
  double bottomFlangeEdgeRadius = OdDAI::Consts::OdNan,
  double bottomFlangeSlope = OdDAI::Consts::OdNan,
  double topFlangeEdgeRadius = OdDAI::Consts::OdNan,
  double topFlangeSlope = OdDAI::Consts::OdNan
)
{
  SdaiAppInstance asymmetricIShapeProfileDef = sdaiCreateInstanceBN(model, "IfcAsymmetricIShapeProfileDef");

  if (position)
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "position", sdaiINSTANCE, position);

  sdaiPutAttrsBN(asymmetricIShapeProfileDef, 7,
    "ProfileType", sdaiENUM, type,
    "ProfileName", sdaiSTRING, name,

    "BottomFlangeWidth", sdaiREAL, bottomFlangeWidth,
    "OverallDepth", sdaiREAL, overallDepth,
    "WebThickness", sdaiREAL, webThickness,
    "BottomFlangeThickness", sdaiREAL, bottomFlangeThickness,
    "TopFlangeWidth", sdaiREAL, topFlangeWidth
  );
  
  if (!OdDAI::Utils::isUnset(bottomFlangeFilletRadius))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "BottomFlangeFilletRadius", sdaiREAL, bottomFlangeFilletRadius);
  if (!OdDAI::Utils::isUnset(topFlangeThickness))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "topflangethickness", sdaiREAL, topFlangeThickness);
  if (!OdDAI::Utils::isUnset(topFlangeFilletRadius))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "topflangefilletradius", sdaiREAL, topFlangeFilletRadius);
  if (!OdDAI::Utils::isUnset(bottomFlangeEdgeRadius))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "bottomflangeedgeradius", sdaiREAL, bottomFlangeEdgeRadius);
  if (!OdDAI::Utils::isUnset(bottomFlangeSlope))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "bottomflangeslope", sdaiREAL, bottomFlangeSlope);
  if (!OdDAI::Utils::isUnset(topFlangeEdgeRadius))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "topflangeedgeradius", sdaiREAL, topFlangeEdgeRadius);
  if (!OdDAI::Utils::isUnset(topFlangeSlope))
    sdaiPutAttrBN(asymmetricIShapeProfileDef, "topflangeslope", sdaiREAL, topFlangeSlope);

  return asymmetricIShapeProfileDef;
}

SdaiAppInstance appendAlignmentSegment(SdaiModel model, SdaiAppInstance designParameters)
{
  SdaiAppInstance alignmentSegment = sdaiCreateInstanceBN(model, "IfcAlignmentSegment");
  sdaiPutAttrBN(alignmentSegment, "DesignParameters", sdaiINSTANCE, designParameters);
  return alignmentSegment;
}

SdaiAppInstance appendAlignmentCantSegLine(
  SdaiModel model,
  SdaiReal startDistAlong,
  SdaiReal horizontalLength,
  SdaiReal startCantLeft,
  SdaiReal endCantLeft,
  SdaiReal startCantRight,
  SdaiReal endCantRight,

  SdaiString startTag = NULL,
  SdaiString endTag = NULL
)
{
  SdaiAppInstance alignmentCantSegLine = sdaiCreateInstanceBN(model, "IfcAlignmentCantSegment");

  if (startTag)
    sdaiPutAttrBN(alignmentCantSegLine, "StartTag", sdaiSTRING, startTag);
  if (endTag)
    sdaiPutAttrBN(alignmentCantSegLine, "EndTag", sdaiSTRING, endTag);

  SdaiString predefinedType = "CONSTANTCANT";
  if (!OdEqual(startCantLeft, endCantLeft) ||
    !OdEqual(startCantRight, endCantRight))
    predefinedType = "LINEARTRANSITION";

  sdaiPutAttrsBN(alignmentCantSegLine, 7,
    "StartDistAlong", sdaiREAL, startDistAlong,
    "HorizontalLength", sdaiREAL, horizontalLength,
    "StartCantLeft", sdaiREAL, startCantLeft,
    "EndCantLeft", sdaiREAL, endCantLeft,
    "StartCantRight", sdaiREAL, startCantRight,
    "EndCantRight", sdaiREAL, endCantRight,
    "PredefinedType", sdaiENUM, predefinedType
  );

  return alignmentCantSegLine;
}

SdaiAppInstance appendHorizontalLineSegment(SdaiModel model,
  double startPointX, double startPointY,
  double startDirection, double segmentLength
)
{
  SdaiAppInstance startPoint = appendCartesianPoint2D(model, startPointX, startPointY);
  SdaiAppInstance lineSegment = sdaiCreateInstanceBN(model, "IfcAlignmentHorizontalSegment");
  sdaiPutAttrsBN(lineSegment, 6,
    "StartPoint", sdaiINSTANCE, startPoint,
    "StartDirection", sdaiREAL, startDirection,
    "StartRadiusOfCurvature", sdaiREAL, 0.,
    "EndRadiusOfCurvature", sdaiREAL, 0.,
    "SegmentLength", sdaiREAL, segmentLength,
    "PredefinedType", sdaiENUM, "LINE"
  );

  return lineSegment;
}

SdaiAppInstance appendHorizontalCircularArcSegment(SdaiModel model,
  double startPointX, double startPointY,
  double startDirection, double segmentLength,
  double radius,
  SdaiBoolean isCCW
)
{
  SdaiAppInstance startPoint = appendCartesianPoint2D(model, startPointX, startPointY);
  SdaiAppInstance circularArcSegment = sdaiCreateInstanceBN(model, "IfcAlignmentHorizontalSegment");
  sdaiPutAttrsBN(circularArcSegment, 6,
    "StartPoint", sdaiINSTANCE, startPoint,
    "StartDirection", sdaiREAL, startDirection,
    "StartRadiusOfCurvature", sdaiREAL, isCCW ? radius : -radius,
    "EndRadiusOfCurvature", sdaiREAL, isCCW ? radius : -radius,
    "SegmentLength", sdaiREAL, segmentLength,
    "PredefinedType", sdaiENUM, "CIRCULARARC"
  );

  return circularArcSegment;
}

SdaiAppInstance appendHorizontalTransitionCurveSegment(SdaiModel model,
  double startPointX, double startPointY,
  double startDirection, double segmentLength,
  double startRadius, double endRadius,
  SdaiBoolean isStartRadiusCCW,
  SdaiBoolean isEndRadiusCCW,
  SdaiEnum transitionCurveType
)
{
  SdaiAppInstance startPoint = appendCartesianPoint2D(model, startPointX, startPointY);
  SdaiAppInstance transitionCurveSegment = sdaiCreateInstanceBN(model, "IfcAlignmentHorizontalSegment");
  sdaiPutAttrsBN(transitionCurveSegment, 6,
    "StartPoint", sdaiINSTANCE, startPoint,
    "StartDirection", sdaiREAL, startDirection,
    "StartRadiusOfCurvature", sdaiREAL, isStartRadiusCCW ? startRadius : -startRadius,
    "EndRadiusOfCurvature", sdaiREAL, isEndRadiusCCW ? endRadius : -endRadius,
    "SegmentLength", sdaiREAL, segmentLength,
    "PredefinedType", sdaiENUM, transitionCurveType
  );

  return transitionCurveSegment;
}

SdaiAppInstance appendAlignmentVerSegLine(SdaiModel model,
  double startDistAlong, double horizontalLength, double startHeight, double startGradient)
{
  SdaiAppInstance alignmentVerSegLine = sdaiCreateInstanceBN(model, "IfcAlignmentVerticalSegment");
  sdaiPutAttrsBN(alignmentVerSegLine, 6,
    "StartDistAlong", sdaiREAL, startDistAlong,
    "HorizontalLength", sdaiREAL, horizontalLength,
    "StartHeight", sdaiREAL, startHeight,
    "StartGradient", sdaiREAL, startGradient,
    "EndGradient", sdaiREAL, startGradient,
    "PredefinedType", sdaiENUM, "CONSTANTGRADIENT"
  );
  return alignmentVerSegLine;
}

SdaiAppInstance appendAlignmentVerSegCircularArc(SdaiModel model,
  double startDistAlong, double horizontalLength, double startHeight, double startGradient,
  double radius, SdaiBoolean isConvex)
{
  SdaiReal signedRadius = isConvex ? -radius : radius;
  SdaiReal startGradientAngle = atan(startGradient);
  SdaiReal cosGradient = cos(startGradientAngle);
  SdaiReal sinGradient = sin(startGradientAngle);

  double R2 = signedRadius * signedRadius;
  double G2 = startGradientAngle * startGradientAngle;

  OdGeVector2d gradientVector(cosGradient, sinGradient);
  OdGeVector2d gradientPerp = gradientVector.perpVector();
  OdGePoint2d s(startDistAlong, startHeight);
  OdGePoint2d c = s + gradientPerp * signedRadius;

  // Arc center in (DistAlong, Height) coordinate system
  double Sc = c.x; // seg.startDistAlong + fabs(seg_startRadius) * gradientRadians / sqrt(1. + G2);
  double Zc = c.y; // seg.startHeight - fabs(seg_startRadius) / sqrt(1. + G2);

  double S1 = startDistAlong + horizontalLength;
  double dS = (S1 - Sc); // Direction along horizontal length from center to S1
  double dS2 = dS * dS; // Squared
  double dZ = sqrt(R2 - dS2);
  double Z1 = isConvex ? Zc + dZ : Zc - dZ;
  OdGePoint2d e(S1, Z1);
  OdGeVector2d endGradientVecor = (e - c).perpVector();

  SdaiReal endGradientAngle = endGradientVecor.angle();// dS / (Z1 - Zc);
  SdaiReal endGradientPerMill = tan(endGradientAngle);

  SdaiAppInstance alignmentVerSegCircularArc = sdaiCreateInstanceBN(model, "IfcAlignmentVerticalSegment");
  sdaiPutAttrsBN(alignmentVerSegCircularArc, 7,
    "StartDistAlong", sdaiREAL, startDistAlong,
    "HorizontalLength", sdaiREAL, horizontalLength,
    "StartHeight", sdaiREAL, startHeight,
    "StartGradient", sdaiREAL, startGradient,
    "EndGradient", sdaiREAL, endGradientPerMill,
    "RadiusOfCurvature", sdaiREAL, radius,
    "PredefinedType", sdaiENUM, "CIRCULARARC"
  );
  return alignmentVerSegCircularArc;
}

#include <iostream>
#include <cstdlib>

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int nRes = 0; // Return value for main

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExSDAISAS (IfcInclinedReferenceSweptAreaSolid creation using SDAI) developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc < 2);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: ExSDAISAS <filename>");
    odPrintConsoleString(L"\n<filename> - output IFC file\n");
    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);

  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize ODA IFC SDK                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  try
  {
    SdaiSession session = sdaiOpenSession();
    SdaiRep repo = _sdaiCreateRepository(session, "SAS_UnitTest");

    SdaiSchema schemaIfc4x3RC4 = sdaiGetSchema("IFC4X3_RC4");
    SdaiModel emptyModel = sdaiCreateModel(repo, "SAS_UnitTest_1", schemaIfc4x3RC4);
    SdaiModel model = sdaiAccessModel(emptyModel, sdaiRW);

    //
    // Footer creation (IfcProject + IfcSite)
    //
    SdaiAppInstance organization = sdaiCreateInstanceBN(model, "IfcOrganization");
    sdaiPutAttrsBN(organization, 2,
      "Name", sdaiSTRING, "Open Design Alliance",
      "Description", sdaiSTRING, "IFC SDK Development"
    );

    SdaiAppInstance person = sdaiCreateInstanceBN(model, "IfcPerson");

    SdaiAppInstance personAndOrganization = sdaiCreateInstanceBN(model, "IfcPersonAndOrganization");
    sdaiPutAttrsBN(personAndOrganization, 2,
      "TheOrganization", sdaiINSTANCE, organization,
      "ThePerson", sdaiINSTANCE, person
    );

    SdaiAppInstance application = sdaiCreateInstanceBN(model, "IfcApplication");
    sdaiPutAttrsBN(application, 4,
      "ApplicationDeveloper", sdaiINSTANCE, organization,
      "Version", sdaiSTRING, TD_SHORT_STRING_VER_S,
      "ApplicationFullName", sdaiSTRING, "Example of IfcInclinedReferenceSweptAreaSolid creation using SDAI",
      "ApplicationIdentifier", sdaiSTRING, "ExSDAISAS"
    );

    SdaiAppInstance ownerHistory = sdaiCreateInstanceBN(model, "IfcOwnerHistory");
    sdaiPutAttrsBN(ownerHistory, 5,
      "OwningUser", sdaiINSTANCE, personAndOrganization,
      "OwningApplication", sdaiINSTANCE, application,
      "State", sdaiENUM, "READWRITE",
      "ChangeAction", sdaiENUM, "ADDED",
      "CreationDate", sdaiINTEGER, 0
    );

    SdaiAppInstance nullPt2D = appendCartesianPoint2D(model, 0., 0.);
    SdaiAppInstance nullPt3D = appendCartesianPoint3D(model, 0., 0., 0.);
    SdaiAppInstance dirZ = appendDirection3D(model, 0., 0., 1.);

    SdaiAppInstance origin2D = appendAxis2Placement2D(model, nullPt2D);
    SdaiAppInstance context2D = appendGeometricRepresentationContext(model, "2D", "Plan", 2, 1e-6, origin2D);

    SdaiAppInstance origin3D = appendAxis2Placement3D(model, nullPt3D);
    SdaiAppInstance context3D = appendGeometricRepresentationContext(model, "3D", "Model", 3, 1e-6, origin3D);

    SdaiAppInstance unitAssignment = appendUnitAssignment(model);

    SdaiAppInstance project = sdaiCreateInstanceBN(model, "IfcProject");
    assignGlobalId(project);
    sdaiPutAttrsBN(project, 4,
      "OwnerHistory", sdaiINSTANCE, ownerHistory,
      "Name", sdaiSTRING, "ExSDAI_SweptAreaSolid",
      "Description", sdaiSTRING, "SAS_Unit_Test_1",
      "UnitsInContext", sdaiINSTANCE, unitAssignment
    );
    SdaiSet representationContexts = sdaiCreateAggrBN(project, "RepresentationContexts");
    sdaiAdd(representationContexts, sdaiINSTANCE, context2D);
    sdaiAdd(representationContexts, sdaiINSTANCE, context3D);

    //
    // Spatial structure (IfcProject <- IfcSite <- IfcRailway <- IfcRail)
    //
    SdaiAppInstance site = appendRelAggregates(model, project, "IfcSite");
    assignGlobalId(site);
    sdaiPutAttrBN(site, "Name", sdaiSTRING, "Railway_Site");

    SdaiAppInstance railway = appendRelAggregates(model, site, "IfcRailway");
    assignGlobalId(railway);
    sdaiPutAttrBN(railway, "Name", sdaiSTRING, "Railway");

    SdaiAppInstance rail = appendRelAggregates(model, railway, "IfcRail");
    assignGlobalId(rail);
    sdaiPutAttrBN(rail, "Name", sdaiSTRING, "Rail");

    //
    // Rail Profile (TODO: Create with composite profile def as in data set), in meters
    //
    double archToMechScaleFactor = 1. / 1000.;

#define I_SHAPE_RAIL_PROFILE
#ifdef I_SHAPE_RAIL_PROFILE
    SdaiAppInstance railProfile = appendAsymmetricIShapeProfileDef(model,

      "AREA", "Rail Profile", NULL,

      //
      // For R65/RP65 rail type:
      //

      // EXPLICIT
      /* bottomFlangeWidth */ archToMechScaleFactor * 150.,
      /* overallDepth */ archToMechScaleFactor * 180.,
      /* webThickness */ archToMechScaleFactor * 20.,
      /* bottomFlangeThickness */ archToMechScaleFactor * 11.2,
      /* topFlangeWidth */ archToMechScaleFactor * 75.,

      // OPTIONAL
      /* bottomFlangeFilletRadius */ archToMechScaleFactor * 25.,
      /* topFlangeThickness */ archToMechScaleFactor * 35.6,
      /* topFlangeFilletRadius */ archToMechScaleFactor * 15.,
      /* bottomFlangeEdgeRadius */ archToMechScaleFactor * 4.,
      /* bottomFlangeSlope */ OdDAI::Consts::OdNan, // Skip
      /* topFlangeEdgeRadius */ archToMechScaleFactor * 3.
      /* topFlangeSlope */ // Not used
    );
#else
    SdaiAppInstance railProfile = sdaiCreateInstanceBN(model, "IFCARBITRARYCLOSEDPROFILEDEF");
    sdaiPutAttrBN(railProfile, "profiletype", sdaiENUM, "AREA");
    sdaiPutAttrBN(railProfile, "profilename", sdaiSTRING, "rail profile");

    RailProfileDef  profileDef(0.5 * archToMechScaleFactor);

    profileDef.buildProfile(model, railProfile);
#endif

    SdaiAppInstance alignment = appendRelContainedInSpatialStructure(model, site, "IfcAlignment");
    assignGlobalId(alignment);
    sdaiPutAttrsBN(alignment, 2,
      "Name", sdaiSTRING, "Primary Alignment",
      "PredefinedType", sdaiENUM, "NOTDEFINED"
    );

    SdaiAppInstance alignmentNests = nullptr;

    //
    // Horizontal alignment, in meters
    //
    SdaiAppInstance alignmentHorizontal = appendRelNests(model, alignment, "IfcAlignmentHorizontal", alignmentNests);
    assignGlobalId(alignmentHorizontal);

    SdaiAppInstance horizontalNests = sdaiCreateInstanceBN(model, "ifcrelnests");
    assignGlobalId(horizontalNests);
    sdaiPutAttrBN(horizontalNests, "RelatingObject", sdaiINSTANCE, alignmentHorizontal);
    SdaiList segmentsHorizontal = sdaiCreateAggrBN(horizontalNests, "RelatedObjects");

    sdaiPutAggrByIndex(segmentsHorizontal, 0, sdaiINSTANCE,
      appendHorizontalLineSegment(model, 2723136.86385, 1213608.32793, -87.555627, 488.5896));

    sdaiPutAggrByIndex(segmentsHorizontal, 1, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723157.70188, 1213120.1829, -87.555627, 72., 0., 467., sdaiFALSE, sdaiTRUE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 2, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalCircularArcSegment(model, 2723162.61845, 1213048.37002, -83.138823, 157.77472, 467., sdaiTRUE)));

    sdaiPutAggrByIndex(segmentsHorizontal, 3, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723207.32062, 1212897.84194, -63.781596, 72., 467., 0., sdaiTRUE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 4, sdaiINSTANCE,
      appendHorizontalLineSegment(model, 2723242.39667, 1212834.98549, -59.364792, 191.97447));

    sdaiPutAggrByIndex(segmentsHorizontal, 5, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723340.22115, 1212669.80508, -59.364792, 68., 0., 472., sdaiFALSE, sdaiTRUE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 6, sdaiINSTANCE,
      appendAlignmentSegment(model, 
        appendHorizontalCircularArcSegment(model, 2723376.25831, 1212612.15796, -55.237554, 67.74031, 472., sdaiTRUE)));

    sdaiPutAggrByIndex(segmentsHorizontal, 7, sdaiINSTANCE,
      appendAlignmentSegment(model, 
        appendHorizontalTransitionCurveSegment(model, 2723418.73625, 1212559.46542, -47.014596, 68., 472., 0., sdaiTRUE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 8, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723467.42275, 1212512.01552, -42.887358, 65., 0., 467., sdaiFALSE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 9, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalCircularArcSegment(model, 2723513.99891, 1212466.69618, -46.874754, 46.06931, 467., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsHorizontal, 10, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723543.78346, 1212431.57438, -52.526952, 39., 467., 904., sdaiFALSE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 11, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalCircularArcSegment(model, 2723566.40828, 1212399.81582, -56.155302, 44.63924, 904., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsHorizontal, 12, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723590.34453, 1212362.14205, -58.984551, 39., 904., 470., sdaiFALSE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 13, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalCircularArcSegment(model, 2723609.48607, 1212328.17009, -62.597637, 91.20524, 470., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsHorizontal, 14, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723643.36729, 1212243.64561, -73.716093, 66., 470., 0., sdaiFALSE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 15, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723658.88542, 1212179.51076, -77.738985, 66., 0., 462., sdaiFALSE, sdaiTRUE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 16, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalCircularArcSegment(model, 2723674.42942, 1212115.38269, -73.646433, 93.4246, 462., sdaiTRUE)));

    sdaiPutAggrByIndex(segmentsHorizontal, 17, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalTransitionCurveSegment(model, 2723709.58855, 1212028.99815, -62.060211, 87., 462., 0., sdaiTRUE, sdaiFALSE, "CLOTHOID")));

    sdaiPutAggrByIndex(segmentsHorizontal, 18, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendHorizontalLineSegment(model, 2723755.07513, 1211954.87657, -56.665476, 254.74363)));

    //
    // Vertical alignment, in meters
    //
    SdaiAppInstance alignmentVertical = appendRelNests(model, alignment, "IfcAlignmentVertical", alignmentNests);
    assignGlobalId(alignmentVertical);

    SdaiAppInstance verticalNests = sdaiCreateInstanceBN(model, "ifcrelnests");
    assignGlobalId(verticalNests);
    sdaiPutAttrBN(verticalNests, "RelatingObject", sdaiINSTANCE, alignmentVertical);
    SdaiList segmentsVertical = sdaiCreateAggrBN(verticalNests, "RelatedObjects");

    sdaiPutAggrByIndex(segmentsVertical, 0, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 0., 33.1223, 459.3108, 6.6511E-3)));
    
    sdaiPutAggrByIndex(segmentsVertical, 1, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 33.1223, 7.5008E-1, 459.531, 6.65012E-3, 1000., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 2, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 33.87238, 462.76333, 459.5357, 5.9E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 3, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 496.63571, 5.9997E-1, 462.266, 5.9E-3, 1500., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 4, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 497.23568, 107.84169, 462.2694, 5.5E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 5, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 605.07737, 6.4997E-1, 462.8626, 5.5E-3, 1000., sdaiTRUE)));

    sdaiPutAggrByIndex(segmentsVertical, 6, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 605.72733, 159.04448, 462.8663, 6.15E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 7, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 764.7718, 5.9997E-1, 463.8445, 6.15E-3, 2000., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 8, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 765.37178, 413.39066, 463.8481, 5.85E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 9, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 1178.76245, 7.3497E-1, 466.2664, 5.85E-3, 700., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 10, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 1179.49739, 380.96596, 466.2703, 4.8E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 11, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 1560.46337, 6.5998E-1, 468.099, 4.8E-3, 1200., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 12, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 1561.12334, 97.23633, 468.1019, 4.25E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 13, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 1658.35967, 6.2999E-1, 468.5152, 4.25E-3, 900., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 14, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 1658.98965, 334.36918, 468.5177, 3.55E-3)));

    sdaiPutAggrByIndex(segmentsVertical, 15, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegCircularArc(model, 1993.35884, 6.9999E-1, 469.7047, 3.55E-3, 7000., sdaiFALSE)));

    sdaiPutAggrByIndex(segmentsVertical, 16, sdaiINSTANCE,
      appendAlignmentSegment(model,
        appendAlignmentVerSegLine(model, 1994.05883, 84.10229, 469.7071, 3.45E-3)));

    //
    // Cant + Segments, in meters
    //
    SdaiAppInstance alignmentCant = appendRelNests(model, alignment, "IfcAlignmentCant", alignmentNests);
    assignGlobalId(alignmentCant);
    sdaiPutAttrBN(alignmentCant, "RailHeadDistance", sdaiREAL, 1.520);

    SdaiAppInstance cantNests = sdaiCreateInstanceBN(model, "ifcrelnests");
    assignGlobalId(cantNests);
    sdaiPutAttrBN(cantNests, "RelatingObject", sdaiINSTANCE, alignmentCant);
    SdaiList segmentsCant = sdaiCreateAggrBN(cantNests, "RelatedObjects");

    sdaiPutAggrByIndex(segmentsCant, 0, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 0., 488.5896, 0., 0., -0., -0.)));
    sdaiPutAggrByIndex(segmentsCant, 1, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 488.5896, 72., 0., -1.89E-1, -0., -1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 2, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 560.5896, 157.77472, -1.89E-1, -1.89E-1, 1.89E-1, 1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 3, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 718.36431, 72., -1.89E-1, 0., 1.89E-1, -0.)));
    sdaiPutAggrByIndex(segmentsCant, 4, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 790.36431, 191.97447, 0., 0., -0., -0.)));
    sdaiPutAggrByIndex(segmentsCant, 5, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 982.33878, 68., 0., -1.89E-1, -0., 1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 6, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1050.33878, 67.74031, -1.89E-1, -1.89E-1, 1.89E-1, 1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 7, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1118.0791, 68., -1.89E-1, 0., 1.89E-1, -0.)));
    sdaiPutAggrByIndex(segmentsCant, 8, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1186.0791, 65., 0., 1.86E-1, -0., -1.86E-1)));
    sdaiPutAggrByIndex(segmentsCant, 9, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1251.0791, 46.06931, 1.86E-1, 1.86E-1, -1.86E-1, -1.86E-1)));
    sdaiPutAggrByIndex(segmentsCant, 10, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1297.14841, 39., 1.86E-1, 9.75E-2, -1.86E-1, -9.75E-2)));
    sdaiPutAggrByIndex(segmentsCant, 11, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1336.14841, 44.63924, 9.75E-2, 9.75E-2, -9.75E-2, -9.75E-2)));
    sdaiPutAggrByIndex(segmentsCant, 12, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1380.78765, 39., 9.75E-2, 1.89E-1, -9.75E-2, -1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 13, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1419.78765, 91.20524, 1.89E-1, 1.89E-1, -1.89E-1, -1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 14, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1510.99289, 66., 1.89E-1, 0., -1.89E-1, -0.)));
    sdaiPutAggrByIndex(segmentsCant, 15, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1576.99289, 66., 0., -1.89E-1, -0., 1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 16, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1642.99289, 93.4246, -1.89E-1, -1.89E-1, 1.89E-1, 1.89E-1)));
    sdaiPutAggrByIndex(segmentsCant, 17, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1736.41749, 87., -1.89E-1, 0., 1.89E-1, -0.)));
    sdaiPutAggrByIndex(segmentsCant, 18, sdaiINSTANCE, appendAlignmentSegment(model,
      appendAlignmentCantSegLine(model, 1823.41749, 254.74363, 0., 0., -0., -0.)));

    //
    // Geometrical representation
    //

    // Axis
    /*SdaiAppInstance linearAxisWithInclination = sdaiCreateInstanceBN(model, "IfcLinearAxisWithInclination");
    sdaiPutAttrsBN(linearAxisWithInclination, 2,
      "Directrix", sdaiINSTANCE, alignmentCurve,
      "Inclinating", sdaiINSTANCE, alignmentCant
    );
    SdaiAppInstance shapeRepresentationAxis = sdaiCreateInstanceBN(model, "IfcShapeRepresentation");
    sdaiPutAttrsBN(shapeRepresentationAxis, 3,
      "ContextOfItems", sdaiINSTANCE, context2D,
      "RepresentationIdentifier", sdaiSTRING, "Axis",
      "RepresentationType", sdaiSTRING, "Curve"
    );
    SdaiSet itemsAxis = sdaiCreateAggrBN(shapeRepresentationAxis, "Items");
    sdaiAdd(itemsAxis, sdaiINSTANCE, linearAxisWithInclination);*/

    // SweptSolid
    /*SdaiAppInstance inclinedReferenceSweptAreaSolid = sdaiCreateInstanceBN(model, "IfcInclinedReferenceSweptAreaSolid");
    sdaiPutAttrsBN(inclinedReferenceSweptAreaSolid, 2,
      "SweptArea", sdaiINSTANCE, railProfile,
      //"Directrix", sdaiINSTANCE, alignmentCurve,
      "Inclinating", sdaiINSTANCE, alignmentCant
    );
    SdaiAppInstance shapeRepresentationSweptSolid = sdaiCreateInstanceBN(model, "IfcShapeRepresentation");
    sdaiPutAttrsBN(shapeRepresentationSweptSolid, 3,
      "ContextOfItems", sdaiINSTANCE, context3D,
      "RepresentationIdentifier", sdaiSTRING, "Body",
      "RepresentationType", sdaiSTRING, "SweptSolid"
    );
    SdaiSet itemsSweptSolid = sdaiCreateAggrBN(shapeRepresentationSweptSolid, "Items");
    sdaiAdd(itemsSweptSolid, sdaiINSTANCE, inclinedReferenceSweptAreaSolid);

    // ProductDefinitionShape
    SdaiAppInstance productDefinitionShape = sdaiCreateInstanceBN(model, "IfcProductDefinitionShape");
    SdaiList representations = sdaiCreateAggrBN(productDefinitionShape, "Representations");
    sdaiPutAggrByIndex(representations, 0, sdaiINSTANCE, shapeRepresentationSweptSolid);
    //sdaiPutAggrByIndex(representations, 1, sdaiINSTANCE, shapeRepresentationAxis);

    sdaiPutAttrBN(rail, "Representation", sdaiINSTANCE, productDefinitionShape);*/

    //
    // Write model to a file
    //

    // Fill header description using SDAI
    SdaiInstance headerDescription = _sdaiHeaderDescription(repo);

    SdaiAggr aggrDescription = NULL;
    if (sdaiGetAttrBN(headerDescription, "description", sdaiAGGR, &aggrDescription))
    {
      sdaiPutAggrByIndex(aggrDescription, 0, sdaiSTRING, "Generated with ExSDAISaS example module");
      //sdaiPutAggrByIndex(aggrDescription, 1, sdaiSTRING, "File contains IfcInclinedReferenceSweptAreaSolid instance");
    }

    OdString wstrFileName(argv[1]);
    OdAnsiString outputFileName(wstrFileName, CP_UTF_8);
    _sdaiWriteRepositoryToFile(repo, const_cast<SdaiString>(outputFileName.c_str()));

    sdaiCloseSession(session);

    //odPrintConsoleString(L"\nPress any key.\n");
    //getchar();
  }
  catch(OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch(...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  odDbRootUninitialize();
  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}

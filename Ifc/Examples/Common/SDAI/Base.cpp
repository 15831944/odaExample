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
#include "Base.h"

SdaiBoolean assignGlobalId(SdaiAppInstance root)
{
  if (sdaiIsKindOfBN(root, "IfcRoot") == sdaiFALSE)
    return sdaiFALSE;
  SdaiString globalId = OdIfcGUID::generate();
  sdaiPutAttrBN(root, "GlobalId", sdaiSTRING, globalId);
  return sdaiTRUE;
}

SdaiAppInstance createCartesianPoint2D(SdaiModel model, SdaiReal x, SdaiReal y)
{
  SdaiAppInstance cartesianPoint2D = sdaiCreateInstanceBN(model, "IfcCartesianPoint");
  SdaiList coordinates = sdaiCreateAggrBN(cartesianPoint2D, "Coordinates");
  sdaiPutAggrByIndex(coordinates, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(coordinates, 1, sdaiREAL, y);
  return cartesianPoint2D;
}

SdaiAppInstance createCartesianPoint3D(SdaiModel model, SdaiReal x, SdaiReal y, SdaiReal z)
{
  SdaiAppInstance cartesianPoint3D = sdaiCreateInstanceBN(model, "IfcCartesianPoint");
  SdaiList coordinates = sdaiCreateAggrBN(cartesianPoint3D, "Coordinates");
  sdaiPutAggrByIndex(coordinates, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(coordinates, 1, sdaiREAL, y);
  sdaiPutAggrByIndex(coordinates, 2, sdaiREAL, z);
  return cartesianPoint3D;
}

SdaiAppInstance createDirection2D(SdaiModel model, SdaiReal x, SdaiReal y)
{
  SdaiAppInstance direction2D = sdaiCreateInstanceBN(model, "IfcDirection");
  SdaiList directionRatios = sdaiCreateAggrBN(direction2D, "DirectionRatios");
  sdaiPutAggrByIndex(directionRatios, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(directionRatios, 1, sdaiREAL, y);
  return direction2D;
}

SdaiAppInstance createDirection3D(SdaiModel model, SdaiReal x, SdaiReal y, SdaiReal z)
{
  SdaiAppInstance direction3D = sdaiCreateInstanceBN(model, "IfcDirection");
  SdaiList directionRatios = sdaiCreateAggrBN(direction3D, "DirectionRatios");
  sdaiPutAggrByIndex(directionRatios, 0, sdaiREAL, x);
  sdaiPutAggrByIndex(directionRatios, 1, sdaiREAL, y);
  sdaiPutAggrByIndex(directionRatios, 2, sdaiREAL, z);
  return direction3D;
}

SdaiAppInstance createVector(SdaiModel model, SdaiAppInstance orientation, SdaiReal magnitude)
{
  SdaiAppInstance vector = sdaiCreateInstanceBN(model, "IfcVector");
  sdaiPutAttrBN(vector, "Orientation", sdaiINSTANCE, orientation);
  sdaiPutAttrBN(vector, "Magnitude", sdaiREAL, magnitude);
  return vector;
}

SdaiAppInstance createAxis2Placement2D(SdaiModel model, SdaiAppInstance location, SdaiAppInstance refDirection /* = NULL */)
{
  SdaiAppInstance axis2Placement2D = sdaiCreateInstanceBN(model, "IfcAxis2Placement2D");
  sdaiPutAttrBN(axis2Placement2D, "Location", sdaiINSTANCE, location);
  if (refDirection)
    sdaiPutAttrBN(axis2Placement2D, "RefDirection", sdaiINSTANCE, refDirection);
  return axis2Placement2D;
}

SdaiAppInstance createAxis2Placement3D(SdaiModel model, SdaiAppInstance location, SdaiAppInstance axis /* = NULL */, SdaiAppInstance refDirection /* = NULL */)
{
  SdaiAppInstance axis2Placement3D = sdaiCreateInstanceBN(model, "IfcAxis2Placement3D");
  sdaiPutAttrBN(axis2Placement3D, "Location", sdaiINSTANCE, location);
  if (axis)
    sdaiPutAttrBN(axis2Placement3D, "Axis", sdaiINSTANCE, axis);
  if (refDirection)
    sdaiPutAttrBN(axis2Placement3D, "RefDirection", sdaiINSTANCE, refDirection);
  return axis2Placement3D;
}

SdaiAppInstance createGeometricRepresentationContext(SdaiModel model,
  SdaiString contextIdentifier, SdaiString contextType, SdaiInteger coordinateSpaceDimension,
  SdaiReal precision, SdaiAppInstance worldCoordinateSystem, SdaiAppInstance trueNorth /* = NULL */)
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

SdaiAppInstance appendRelAggregates(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName, SdaiAppInstance &relAggregates)
{
  SdaiAppInstance ownerHistory = NULL;
  sdaiGetAttrBN(relating, "OwnerHistory", sdaiINSTANCE, &ownerHistory);

  SdaiSet relatedObjects = nullptr;
  if (relAggregates == nullptr)
  {
    relAggregates = sdaiCreateInstanceBN(model, "IfcRelAggregates");
    assignGlobalId(relAggregates);
    if (ownerHistory)
      sdaiPutAttrBN(relAggregates, "OwnerHistory", sdaiINSTANCE, ownerHistory);
    sdaiPutAttrBN(relAggregates, "RelatingObject", sdaiINSTANCE, relating);
    relatedObjects = sdaiCreateAggrBN(relAggregates, "RelatedObjects");
  }
  else
  {
    SdaiAppInstance _relating = nullptr;
    sdaiGetAttrBN(relAggregates, "RelatingObject", sdaiINSTANCE, &_relating);
    ODA_ASSERT(relating == _relating);
    sdaiGetAttrBN(relAggregates, "RelatedObjects", sdaiAGGR, &relatedObjects);
  }

  SdaiAppInstance related = sdaiCreateInstanceBN(model, relatedEntityName);
  if (ownerHistory)
    sdaiPutAttrBN(related, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  sdaiAdd(relatedObjects, sdaiINSTANCE, related);

  return related;
}

SdaiAppInstance appendRelNests(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName, SdaiAppInstance &relNests)
{
  SdaiAppInstance ownerHistory = NULL;
  sdaiGetAttrBN(relating, "OwnerHistory", sdaiINSTANCE, &ownerHistory);

  SdaiList relatedObjects = nullptr;
  if (relNests == nullptr)
  {
    relNests = sdaiCreateInstanceBN(model, "IfcRelNests");
    assignGlobalId(relNests);
    if (ownerHistory)
      sdaiPutAttrBN(relNests, "OwnerHistory", sdaiINSTANCE, ownerHistory);
    sdaiPutAttrBN(relNests, "RelatingObject", sdaiINSTANCE, relating);
    relatedObjects = sdaiCreateAggrBN(relNests, "RelatedObjects");
  }
  else
  {
    SdaiAppInstance _relating = nullptr;
    sdaiGetAttrBN(relNests, "RelatingObject", sdaiINSTANCE, &_relating);
    ODA_ASSERT(relating == _relating);
    sdaiGetAttrBN(relNests, "RelatedObjects", sdaiAGGR, &relatedObjects);
  }

  SdaiAppInstance related = sdaiCreateInstanceBN(model, relatedEntityName);
  if (ownerHistory)
    sdaiPutAttrBN(related, "OwnerHistory", sdaiINSTANCE, ownerHistory);

  SdaiAggrIndex nextIndex = sdaiGetMemberCount(relatedObjects);
  sdaiPutAggrByIndex(relatedObjects, nextIndex, sdaiINSTANCE, related);

  return related;
}

SdaiAppInstance appendRelContainedInSpatialStructure(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName)
{
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

template<typename ItemType>
void _sdaiFillOrdered(SdaiOrderedAggr orderedAggr, const OdArray<ItemType> &arr)
{
  unsigned int size = arr.size();
  for (unsigned int i = 0; i < size; ++i)
  {
    sdaiPutAggrByIndex(orderedAggr, i, sdaiINSTANCE, arr.at(i));
  }
}

SdaiAppInstance createRelNests(SdaiModel model, SdaiAppInstance relatingObject, const OdArray<SdaiAppInstance> &relatedObjects)
{
  SdaiAppInstance relNests = sdaiCreateInstanceBN(model, "IfcRelNests");
  assignGlobalId(relNests);
  sdaiPutAttrBN(relNests, "RelatingObject", sdaiINSTANCE, relatingObject);
  SdaiList list = sdaiCreateAggrBN(relNests, "RelatedObjects");

  _sdaiFillOrdered(list, relatedObjects);

  return relNests;
}

SdaiAppInstance createShapeRepresentation(SdaiModel model, SdaiAppInstance product, SdaiAppInstance context, SdaiString representationIdentifier, SdaiString representationType, SdaiString entityName)
{
  SdaiAppInstance representationItem = sdaiCreateInstanceBN(model, entityName);

  SdaiAppInstance shapeRepresentation = sdaiCreateInstanceBN(model, "IfcShapeRepresentation");
  sdaiPutAttrBN(shapeRepresentation, "ContextOfItems", sdaiINSTANCE, context);
  sdaiPutAttrBN(shapeRepresentation, "RepresentationIdentifier", sdaiSTRING, representationIdentifier);
  sdaiPutAttrBN(shapeRepresentation, "RepresentationType", sdaiSTRING, representationType);
  SdaiSet items = sdaiCreateAggrBN(shapeRepresentation, "Items");
  sdaiAdd(items, sdaiINSTANCE, representationItem);

  SdaiAppInstance productDefinitionShape = sdaiCreateInstanceBN(model, "IfcProductDefinitionShape");
  SdaiList representations = sdaiCreateAggrBN(productDefinitionShape, "Representations");
  sdaiPutAggrByIndex(representations, 0, sdaiINSTANCE, shapeRepresentation);

  sdaiPutAttrBN(product, "Representation", sdaiINSTANCE, productDefinitionShape);

  return representationItem;
}

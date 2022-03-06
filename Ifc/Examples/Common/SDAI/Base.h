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

#include "IfcCore.h"
#include "sdai.h"

SdaiBoolean assignGlobalId(SdaiAppInstance root);

SdaiAppInstance createCartesianPoint2D(SdaiModel model, SdaiReal x, SdaiReal y);
SdaiAppInstance createCartesianPoint3D(SdaiModel model, SdaiReal x, SdaiReal y, SdaiReal z);

SdaiAppInstance createDirection2D(SdaiModel model, SdaiReal x, SdaiReal y);
SdaiAppInstance createDirection3D(SdaiModel model, SdaiReal x, SdaiReal y, SdaiReal z);

SdaiAppInstance createAxis2Placement2D(SdaiModel model, SdaiAppInstance location, SdaiAppInstance refDirection = NULL);
SdaiAppInstance createAxis2Placement3D(SdaiModel model, SdaiAppInstance location, SdaiAppInstance axis = NULL, SdaiAppInstance refDirection = NULL);

SdaiAppInstance createVector(SdaiModel model, SdaiAppInstance orientation, SdaiReal magnitude);

SdaiAppInstance createGeometricRepresentationContext(SdaiModel model,
  SdaiString contextIdentifier, SdaiString contextType, SdaiInteger coordinateSpaceDimension,
  SdaiReal precision, SdaiAppInstance worldCoordinateSystem, SdaiAppInstance trueNorth = NULL);

SdaiAppInstance appendSiUnit(SdaiModel model, SdaiEnum unitType, SdaiEnum prefix, SdaiEnum name);
SdaiAppInstance appendUnitAssignment(SdaiModel model);

SdaiAppInstance appendRelAggregates(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName, SdaiAppInstance &relAggregates);
SdaiAppInstance appendRelContainedInSpatialStructure(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName);

SdaiAppInstance appendRelNests(SdaiModel model, SdaiAppInstance relating, SdaiString relatedEntityName, SdaiAppInstance &relNests);
SdaiAppInstance createRelNests(SdaiModel model, SdaiAppInstance relatingObject, const OdArray<SdaiAppInstance> &relatedObjects);

SdaiAppInstance createShapeRepresentation(SdaiModel model, SdaiAppInstance product, SdaiAppInstance context, SdaiString representationIdentifier, SdaiString representationType, SdaiString entityName);

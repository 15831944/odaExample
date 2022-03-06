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

#include <iostream>
#include "DerivedAttributes.h"
#include "RxValue.h"

using namespace OdIfc;
using namespace OdDAI;

OdAnsiString dumpCoordinates(OdDAI::DoubleList *doubleList)
{
  double x = doubleList->getByIndex<double>(0);
  double y = doubleList->getByIndex<double>(1);
  double z = doubleList->getByIndex<double>(2);
  return OdAnsiString().format("(%.4f, %.4f, %.4f)", x, y, z);
}

/*

ENTITY IfcMaterialLayer;
	Material : OPTIONAL IfcMaterial;
	LayerThickness : IfcPositiveLengthMeasure;
	IsVentilated : OPTIONAL IfcLogical;
 INVERSE
	ToMaterialLayerSet : IfcMaterialLayerSet FOR MaterialLayers;
END_ENTITY;

ENTITY IfcMaterialLayerSet;
	MaterialLayers : LIST [1:?] OF IfcMaterialLayer;
	LayerSetName : OPTIONAL IfcLabel;
 DERIVE
	TotalThickness : IfcLengthMeasure := IfcMlsTotalThickness(SELF);
END_ENTITY;

(*
  Calculates a sum of all IfcMaterialLayer.LayerThickness
*)
FUNCTION IfcMlsTotalThickness
	(LayerSet : IfcMaterialLayerSet)
	: IfcLengthMeasure;
    LOCAL
      Max : IfcLengthMeasure := LayerSet.MaterialLayers[1].LayerThickness;
    END_LOCAL;
  
    IF SIZEOF(LayerSet.MaterialLayers) > 1 THEN
      REPEAT i := 2 TO HIINDEX(LayerSet.MaterialLayers);
         Max := Max + LayerSet.MaterialLayers[i].LayerThickness;
      END_REPEAT;
    END_IF;
    RETURN (Max);
END_FUNCTION;

*/
void evaluateMaterialLayerSet_TotalThickness(const MyServices &svcs)
{
  OdIfcFilePtr ifcFile = svcs.createDatabase("IFC2X3"); // Create empty IFC database
  OdDAI::ModelPtr model = ifcFile->getModel(sdaiRW); // Access IFC model in Read-Write mode.

  OdDAI::ApplicationInstancePtr materialLayerSet = model->createEntityInstance("IfcMaterialLayerSet");
  model->appendEntityInstance(materialLayerSet);

  OdDAI::Aggr *aggr = nullptr;
  materialLayerSet->getAttr("materiallayers") >> aggr;

  OdDAI::List<OdDAIObjectId> *materialLayers = static_cast<OdDAI::List<OdDAIObjectId>*>(aggr);
  if (materialLayers->isNil())
    materialLayers->createEmpty();

  odPrintConsoleString(L"\n\nIfcMaterialLayerSet.TotalThickness evaluation example for IFC2X3:\n\n");

  double totalThickness = OdDAI::Consts::OdNan;

  OdRxValue valueTotalThickness = materialLayerSet->getAttrCaseInsensitive("TotalThickness");
  odPrintConsoleString(L"No layers, %hs\n", (valueTotalThickness.isEmpty() ? "no total thickness!" : "Hmm!"));

  std::vector<double> layerThicknesses = { 20., 10.03, 10.77, 1.2 };

  size_t index = 0;
  for (double layerThickness : layerThicknesses)
  {
    OdDAI::ApplicationInstancePtr materialLayer = model->createEntityInstance("ifcmateriallayer");
    materialLayer->putAttr("layerthickness", layerThickness);
    materialLayers->putByIndex(index++, model->appendEntityInstance(materialLayer));

    materialLayerSet->getAttrCaseInsensitive("TotalThickness") >> totalThickness;
    odPrintConsoleString(L"Total thickness for %d layer(s): %.2f\n", index, totalThickness);
  }
}



/*

ENTITY IfcAxis2Placement3D
 SUBTYPE OF (IfcPlacement);
	Axis : OPTIONAL IfcDirection;
	RefDirection : OPTIONAL IfcDirection;
 DERIVE
	P : LIST [3:3] OF IfcDirection := IfcBuildAxes(Axis, RefDirection);
 WHERE
	WR1 : SELF\IfcPlacement.Location.Dim = 3;
	WR2 : (NOT (EXISTS (Axis))) OR (Axis.Dim = 3);
	WR3 : (NOT (EXISTS (RefDirection))) OR (RefDirection.Dim = 3);
	WR4 : (NOT (EXISTS (Axis))) OR (NOT (EXISTS (RefDirection))) OR (IfcCrossProduct(Axis,RefDirection).Magnitude > 0.0);
	WR5 : NOT ((EXISTS (Axis)) XOR (EXISTS (RefDirection)));
END_ENTITY;

FUNCTION IfcBuildAxes
	(Axis, RefDirection : IfcDirection)
	: LIST [3:3] OF IfcDirection;
  LOCAL
    D1, D2 : IfcDirection;
  END_LOCAL;
    D1 := NVL(IfcNormalise(Axis), IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcDirection([0.0,0.0,1.0]));
    D2 := IfcFirstProjAxis(D1, RefDirection);
    RETURN ([D2, IfcNormalise(IfcCrossProduct(D1,D2))\IfcVector.Orientation, D1]);
END_FUNCTION;

FUNCTION IfcCrossProduct
	(Arg1, Arg2 : IfcDirection)
	: IfcVector;
  LOCAL
    Mag : REAL;
    Res : IfcDirection;
    V1,V2  : LIST[3:3] OF REAL;
    Result : IfcVector;
  END_LOCAL;
  
    IF (NOT EXISTS (Arg1) OR (Arg1.Dim = 2)) OR (NOT EXISTS (Arg2) OR (Arg2.Dim = 2)) THEN
      RETURN(?);
    ELSE
      BEGIN
        V1  := IfcNormalise(Arg1).DirectionRatios;
        V2  := IfcNormalise(Arg2).DirectionRatios;
        Res := IfcRepresentationItem() || IfcGeometricRepresentationItem () 
               || IfcDirection([(V1[2]*V2[3] - V1[3]*V2[2]), (V1[3]*V2[1] - V1[1]*V2[3]), (V1[1]*V2[2] - V1[2]*V2[1])]);
        Mag := 0.0;
        REPEAT i := 1 TO 3;
          Mag := Mag + Res.DirectionRatios[i]*Res.DirectionRatios[i];
        END_REPEAT;
        IF (Mag > 0.0) THEN
          Result := IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcVector(Res, SQRT(Mag));
        ELSE
          Result := IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcVector(Arg1, 0.0);
        END_IF;
        RETURN(Result);
      END;
    END_IF;
END_FUNCTION;

FUNCTION IfcNormalise
	(Arg : IfcVectorOrDirection)
	: IfcVectorOrDirection;
  LOCAL
    Ndim : INTEGER;
    V    : IfcDirection
         := IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcDirection([1.,0.]); 
    Vec  : IfcVector 
         := IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcVector (
              IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcDirection([1.,0.]), 1.);
    Mag  : REAL;
    Result : IfcVectorOrDirection
           := V;
  END_LOCAL;
  
    IF NOT EXISTS (Arg) THEN
      RETURN (?);
    ELSE
      Ndim := Arg.Dim;
      IF 'IFC2X3.IFCVECTOR' IN TYPEOF(Arg) THEN
        BEGIN
  	V.DirectionRatios := Arg\IfcVector.Orientation.DirectionRatios;
          Vec.Magnitude := Arg\IfcVector.Magnitude;
  	Vec.Orientation := V;
          IF Arg.Magnitude = 0.0 THEN
            RETURN(?);
          ELSE
            Vec.Magnitude := 1.0;
          END_IF;
        END;
      ELSE
        V.DirectionRatios := Arg.DirectionRatios;
      END_IF;
      Mag := 0.0;
        REPEAT i := 1 TO Ndim;
          Mag := Mag + V.DirectionRatios[i]*V.DirectionRatios[i];
        END_REPEAT;
      IF Mag > 0.0 THEN
        Mag := SQRT(Mag);
        REPEAT i := 1 TO Ndim;
          V.DirectionRatios[i] := V.DirectionRatios[i]/Mag;
        END_REPEAT;
        IF 'IFC2X3.IFCVECTOR' IN TYPEOF(arg) THEN
          Vec.Orientation := V;
          Result := Vec;
        ELSE
          Result := V;
        END_IF;
      ELSE
        RETURN(?);
      END_IF;
    END_IF;
    RETURN (Result);
END_FUNCTION;

FUNCTION IfcFirstProjAxis
	(ZAxis, Arg : IfcDirection)
	: IfcDirection;
  LOCAL
    XAxis : IfcDirection;
    V     : IfcDirection;
    Z     : IfcDirection;
    XVec  : IfcVector;
  END_LOCAL;
  
    IF (NOT EXISTS(ZAxis)) THEN
      RETURN (?) ;
    ELSE
      Z := IfcNormalise(ZAxis);
      IF NOT EXISTS(Arg) THEN
        IF (Z.DirectionRatios <> [1.0,0.0,0.0]) THEN
          V := IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcDirection([1.0,0.0,0.0]);
        ELSE
          V := IfcRepresentationItem() || IfcGeometricRepresentationItem () || IfcDirection([0.0,1.0,0.0]);
        END_IF;
      ELSE
        IF (Arg.Dim <> 3) THEN
          RETURN (?) ;
        END_IF;
        IF ((IfcCrossProduct(Arg,Z).Magnitude) = 0.0) THEN
          RETURN (?);
        ELSE
          V := IfcNormalise(Arg);
        END_IF;
      END_IF;
      XVec  := IfcScalarTimesVector(IfcDotProduct(V, Z), Z);
      XAxis := IfcVectorDifference(V, XVec).Orientation;
      XAxis := IfcNormalise(XAxis);
    END_IF;
    RETURN(XAxis);
END_FUNCTION;

*/
void evaluateAxis2Placement3D_P(const MyServices &svcs)
{
  OdIfcFilePtr ifcFile = svcs.createDatabase("IFC4X3_RC4"); // Create empty IFC database
  OdDAI::ModelPtr model = ifcFile->getModel(sdaiRW); // Access IFC model in Read-Write mode.

  OdDAI::ApplicationInstancePtr axis2Placement3D = model->createEntityInstance("IfcAxis2Placement3D");
  model->appendEntityInstance(axis2Placement3D);

  odPrintConsoleString(L"\nIfcAxis2Placement3D.P (Coordinate system) evaluation example for IFC4X3:\n\n");

  // Create X axis
  OdDAI::ApplicationInstancePtr xAxis = model->createEntityInstance("IfcDirection");
  OdDAI::DoubleList *directionRatiosX = nullptr;
  xAxis->getAttrCaseInsensitive("DirectionRatios") >> directionRatiosX;
  directionRatiosX->createEmpty();
  directionRatiosX->putByIndex(0, cos(OdaPI4));
  directionRatiosX->putByIndex(1, sin(OdaPI4));
  directionRatiosX->putByIndex(2, 0.);
  axis2Placement3D->putAttrCaseInsensitive("RefDirection", model->appendEntityInstance(xAxis));
  odPrintConsoleString(L"Original X-Axis is %hs\n", dumpCoordinates(directionRatiosX).c_str());

  // Create Z axis
  OdDAI::ApplicationInstancePtr zAxis = model->createEntityInstance("IfcDirection");
  OdDAI::DoubleList *directionRatiosZ = nullptr;
  zAxis->getAttrCaseInsensitive("DirectionRatios") >> directionRatiosZ;
  directionRatiosZ->createEmpty();
  directionRatiosZ->putByIndex(0, 0.);
  directionRatiosZ->putByIndex(1, 0.);
  directionRatiosZ->putByIndex(2, 10.); // Not normalised direction
  axis2Placement3D->putAttrCaseInsensitive("Axis", model->appendEntityInstance(zAxis));
  odPrintConsoleString(L"Original Z-Axis is %hs\n\n", dumpCoordinates(directionRatiosZ).c_str());

  OdDAI::Aggr *aggr = nullptr;
  axis2Placement3D->getAttrCaseInsensitive("P") >> aggr; // Evaluate coordinate system
  OdDAI::OdDAIObjectIdList *p = static_cast<OdDAI::OdDAIObjectIdList*>(aggr);

  OdDAIObjectId idXAxis = p->getByIndex<OdDAIObjectId>(0);
  xAxis = idXAxis.openObject();
  OdDAI::DoubleList *xDirectionRatios = nullptr;
  xAxis->getAttrCaseInsensitive("DirectionRatios") >> xDirectionRatios;
  odPrintConsoleString(L"Evaluated X-Axis is %hs\n", dumpCoordinates(xDirectionRatios).c_str());

  OdDAIObjectId idYAxis = p->getByIndex<OdDAIObjectId>(1);
  OdDAI::ApplicationInstancePtr yAxis = idYAxis.openObject();
  OdDAI::DoubleList *yDirectionRatios = nullptr;
  yAxis->getAttrCaseInsensitive("DirectionRatios") >> yDirectionRatios;
  odPrintConsoleString(L"Evaluated Y-Axis is %hs - evaluated cross product\n", dumpCoordinates(yDirectionRatios).c_str());

  OdDAIObjectId idZAxis = p->getByIndex<OdDAIObjectId>(2);
  zAxis = idZAxis.openObject();
  OdDAI::DoubleList *zDirectionRatios = nullptr;
  zAxis->getAttrCaseInsensitive("DirectionRatios") >> zDirectionRatios;
  odPrintConsoleString(L"Evaluated Z-Axis is %hs - normalized original Z-Axis\n", dumpCoordinates(zDirectionRatios).c_str());
}


/*

ENTITY IfcCShapeProfileDef
 SUBTYPE OF (IfcParameterizedProfileDef);
	Depth : IfcPositiveLengthMeasure;
	Width : IfcPositiveLengthMeasure;
	WallThickness : IfcPositiveLengthMeasure;
	Girth : IfcPositiveLengthMeasure;
	InternalFilletRadius : OPTIONAL IfcNonNegativeLengthMeasure;
 WHERE
	ValidGirth : Girth < (Depth / 2.);
	ValidInternalFilletRadius : NOT(EXISTS(InternalFilletRadius)) OR
((InternalFilletRadius <= Width/2. - WallThickness) AND (InternalFilletRadius <= Depth/2. - WallThickness));
	ValidWallThickness : (WallThickness < Width/2.) AND (WallThickness < Depth/2.);
END_ENTITY;

*/
void validateIfcCShapeProfileDef(const MyServices &svcs)
{
  OdIfcFilePtr ifcFile = svcs.createDatabase("IFC4"); // Create empty IFC database
  OdDAI::ModelPtr model = ifcFile->getModel(sdaiRW); // Access IFC model in Read-Write mode.

  OdDAI::ApplicationInstancePtr cshapeProfileDef = model->createEntityInstance("IfcCShapeProfileDef");
  model->appendEntityInstance(cshapeProfileDef);

  odPrintConsoleString(L"\nIfcCShapeProfileDef Where Rules validation example for IFC4:\n\n");

  cshapeProfileDef->putAttr("depth", 30.);
  cshapeProfileDef->putAttr("width", 7.);
  cshapeProfileDef->putAttr("wallthickness", 3.);
  cshapeProfileDef->putAttr("girth", 2.2);
  cshapeProfileDef->putAttr("internalfilletradius", 0.7);

  OdDAI::Logical resValidGirth = cshapeProfileDef->validateWhereRule("ValidGirth");
  odPrintConsoleString(L"ValidGirth validation result: %hs\n",
    OdAnsiString(resValidGirth).c_str()); // True

  OdDAI::Logical resValidInternalFilletRadius = cshapeProfileDef->validateWhereRule("ValidInternalFilletRadius");
  odPrintConsoleString(L"ValidInternalFilletRadius validation result: %hs\n",
    OdAnsiString(resValidInternalFilletRadius).c_str()); // False, as InternalFilletRadius > Width/2. - WallThickness

  OdDAI::Logical resValidWallThickness = cshapeProfileDef->validateWhereRule("ValidWallThickness");
  odPrintConsoleString(L"ValidWallThickness validation result: %hs\n",
    OdAnsiString(resValidWallThickness).c_str()); // True
}

int DerivedAttributes(int argc, wchar_t* argv[], const MyServices &svcs)
{
  evaluateMaterialLayerSet_TotalThickness(svcs);
  evaluateAxis2Placement3D_P(svcs);
  validateIfcCShapeProfileDef(svcs);
  return 0;
}

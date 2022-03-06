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

//#include "OdArray.h"
#include "ExPrintConsole.h"
#include "IfcExamplesCommon.h"
#include "IfcCore.h"
#include "IfcModel.h"

#include "OdaCommon.h"

int Tutorial_ProjectSetup(int argc, wchar_t* argv[], const MyServices &svcs);

struct ProjectData
{
  OdDAIObjectId ownerHistory;
  OdDAIObjectId project;
  OdDAIObjectId modelContext;
  OdDAIObjectId planContext;

  OdDAIObjectId origin2d;
  OdDAIObjectId origin3d;
  OdDAIObjectId dirZ;
};

enum class PlaneAngleUnits
{
  kRadians,
  kDegrees
};

int ProjectSetup(OdDAI::Model *ifcModel, ProjectData &projectData, PlaneAngleUnits planeAngleUnits = PlaneAngleUnits::kRadians, const char *lengthUnitPrefix = "MILLI");

OdDAIObjectId appendIfcDimensionalExponents(OdIfcModel *model, int LengthExponent = 0, int MassExponent = 0, int TimeExponent = 0, int ElectricCurrentExponent = 0, int ThermodynamicTemperatureExponent = 0, int AmountOfSubstanceExponent = 0, int LuminousIntensityExponent = 0);
OdDAIObjectId appendIfcSiUnit(OdIfcModel *model, const char *unitType, const char *prefix, const char *name);
OdDAIObjectId appendCartesianPoint(OdIfcModel *model, const OdArray<double> &dblArr);
OdDAIObjectId appendDirection(OdIfcModel *model, const OdArray<double> &dblArr);
OdDAIObjectId appendSpatialChild(OdIfcModel *model, const OdDAIObjectId &relating, OdIfc::OdIfcEntity *related, const OdDAIObjectId &ownerHistory = OdDAIObjectId::kNull);
OdDAIObjectId appendContained(OdIfcModel *model, const OdDAIObjectId &relating, OdIfc::OdIfcEntity *related, const OdDAIObjectId &ownerHistory = OdDAIObjectId::kNull);

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
#include "RxValue.h"

#include "IfcExamplesCommon.h"
#include "ExIfcHostAppServices.h"

#define STL_USING_IOSTREAM
#define STL_USING_SET
#define STL_USING_MAP
#include "OdaSTL.h"
#define  STD(a)  std:: a

#include "ExIfcBridge.h"
#include "ExSectionedSolid.h"

//
// Define module map for statically linked modules:
//
#ifndef _TOOLKIT_IN_DLL_
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

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

ODGI_EXPORT void odgiInitialize();
ODGI_EXPORT void odgiUninitialize();

void appInit()
{
  IfcBuilder::rxInit();
    IfcBuildingBuilder::rxInit();
    IfcBridgeBuilder::rxInit();
    IfcRepresentationBuilder::rxInit();
    IfcProfileBuilder::rxInit();
    IfcPropertySetFiller::rxInit();
    IfcQuantitySetFiller::rxInit();
}

void appUninit()
{
    IfcQuantitySetFiller::rxUninit();
    IfcPropertySetFiller::rxUninit();
    IfcProfileBuilder::rxUninit();
    IfcRepresentationBuilder::rxUninit();
    IfcBridgeBuilder::rxUninit();
    IfcBuildingBuilder::rxUninit();
  IfcBuilder::rxUninit();
}

OdIfc::OdIfcEntityPtr AppendPileNetwork(
  IfcBridgeBuilderPtr pBridgeBuilder,
  OdIfc::OdIfcEntityPtr pFoundation,
  OdGePoint3d objectPlacement,
  const OdAnsiString &pileNetworkName,
  double elevation,
  double pierHeight,

  double footingXDim,
  double footingYDim,
  double footingDepth,

  double pileRadius,
  double pileHeight,
  
  double rebarDiam = 0.)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  // TODO: mPlacement to appendBridgePart
  OdGeMatrix3d mPlacement;
  mPlacement.setTranslation(objectPlacement.asVector() + OdGeVector3d(0., 0., elevation - pierHeight - footingDepth));
  OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(mPlacement);
  OdIfc::OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);

  OdIfc::OdIfcEntityPtr pileNetwork = pBridgeBuilder->appendBridgePart(pileNetworkName, pFoundation, IfcBridgeBuilder::kUSERDEFINED_PART_TYPE);
  pileNetwork->putAttr("objectplacement", OdDAIObjectId(pPlacement->id()));

  OdDAIObjectId idReplPlacement;

  int numX = footingXDim / (pileRadius * 3);
  numX += numX % 2 - 1; // odd
  int numY = footingYDim / (pileRadius * 3);
  numY += numY % 2; // even
  double stepY = footingYDim / (double)(numY + 1.);

  int ctr = 0;
  for (int j = 0; j < numY; ++j)
  {
    int xCtr = 0;
    for (int i = -numX * 0.5; i < numX * 0.5; ++i)
    {
      OdAnsiString pileName;
      pileName.format("Pile %i %i", j+1, ++xCtr);
      OdIfc::OdIfcEntityPtr pile = pBridgeBuilder->appendProduct(pileNetwork, "ifcpile", pileName, pPlacement);
      if (!pile.isNull())
      {
        IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pile);
        if (!pRB.isNull())
        {
          OdGeMatrix3d localPlacement;
          
          double y = -footingYDim * 0.5 + stepY * (j + 1);
          localPlacement.setTranslation(OdGeVector3d(i * 3 * pileRadius, y, 0));

          ExPile *pileGeom = new ExPile(localPlacement, pileRadius, pileHeight);
          pRB->process(pileGeom);
          delete pileGeom;
        }
        IfcPropertySetFillerPtr propertySet = filler->createPropertySet(pile);
        propertySet->
          appendPropertySingleValue("Reference", OdAnsiString("Footing with piles"), "IfcIdentifier").
          appendPropertySingleValue("Status", OdAnsiString("New"), "IfcLabel").
          createPropertySet("Pset_PileCommon");
      }

      if (!OdEqual(rebarDiam, 0.))
      {
        rebarDiam = fabs(rebarDiam);
        OdAnsiString reinforcingMeshName;
        reinforcingMeshName.format("Reinforcing mesh %i %i", j + 1, ++xCtr);
        OdIfc::OdIfcEntityPtr reinforcingMesh = pBridgeBuilder->appendProduct(pileNetwork, "ifcreinforcingmesh", reinforcingMeshName, pPlacement);
        if (!reinforcingMesh.isNull())
        {
          IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(reinforcingMesh);
          if (!pRB.isNull())
          {
            OdGeMatrix3d localPlacement;

            double y = -footingYDim * 0.5 + stepY * (j + 1);
            localPlacement.setTranslation(OdGeVector3d(i * 3 * pileRadius, y, 0));

            ExReinforcingMeshCirc *reinforcingMeshGeom = new ExReinforcingMeshCirc(localPlacement, 2. / 3. * pileRadius, pileHeight, 1000., rebarDiam, false, 12, 1);
            pRB->process(reinforcingMeshGeom);
            delete reinforcingMeshGeom;
          }
          //IfcPropertySetFillerPtr propertySet = filler->createPropertySet(reinforcingMesh);
          //propertySet->
          //  appendPropertySingleValue("Reference", OdAnsiString("Footing with piles"), "IfcIdentifier").
          //  appendPropertySingleValue("Status", OdAnsiString("New"), "IfcLabel").
          //  createPropertySet("Pset_PileCommon");
        }
      }
    }
  }

  return pileNetwork;
}

OdIfc::OdIfcEntityPtr AppendPier(
  IfcBridgeBuilderPtr pBridgeBuilder,
  OdIfc::OdIfcEntityPtr pSubStructure,
  OdGePoint3d objectPlacement,
  const OdAnsiString &pierName,
  double elevation,
  double pierHeight,
  double footingXDim,
  double footingYDim,
  double footingDepth,
  double bearingXDim,
  double bearingYDim,
  double bearingDistance,
  double bearingOffset,
  double bearingThickness,
  double capHeight,
  double capWing)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  // TODO: mPlacement to appendBridgePart
  OdGeMatrix3d mPlacement;
  mPlacement.setTranslation(objectPlacement.asVector() + OdGeVector3d(0., 0., elevation - pierHeight));
  OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(mPlacement);
  OdIfc::OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);

  OdIfc::OdIfcEntityPtr pPier = pBridgeBuilder->appendBridgePart(pierName, pSubStructure, IfcBridgeBuilder::kPIER);
  pPier->putAttr("objectplacement", OdDAIObjectId(pPlacement->id()));

  double columnLevel = footingDepth + pierHeight;

  OdDAIObjectId idReplPlacement;

  OdIfc::OdIfcEntityPtr pBearing3 = pBridgeBuilder->appendProduct(pPier, "ifcbearing", "Bearing 1.1", pPlacement);
  if (!pBearing3.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearing3);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPlacement;
      localPlacement.setTranslation(OdGeVector3d(-bearingDistance, -bearingOffset, pierHeight));
      ExBearing *bearingGeom = new ExBearing(localPlacement, bearingXDim, bearingYDim, 80., 80., 500);
      pRB->process(bearingGeom);
      delete bearingGeom;
    }
  }

  OdIfc::OdIfcEntityPtr pBearing4 = pBridgeBuilder->appendProduct(pPier, "ifcbearing", "Bearing 1.2", pPlacement);
  if (!pBearing4.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearing4);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPlacement;
      localPlacement.setTranslation(OdGeVector3d(bearingDistance, -bearingOffset, pierHeight));
      ExBearing *bearingGeom = new ExBearing(localPlacement, bearingXDim, bearingYDim, 80, 80, 500);
      pRB->process(bearingGeom);
      delete bearingGeom;
    }
  }

  OdIfc::OdIfcEntityPtr pBearing2 = pBridgeBuilder->appendProduct(pPier, "ifcbearing", "Bearing 2.1", pPlacement);
  if (!pBearing2.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearing2);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPlacement;
      localPlacement.setTranslation(OdGeVector3d(bearingDistance, bearingOffset, pierHeight));
      ExBearing *bearingGeom = new ExBearing(localPlacement, bearingXDim, bearingYDim, 80, 80, 500);
      pRB->process(bearingGeom);
      delete bearingGeom;
    }
  }

  OdIfc::OdIfcEntityPtr pBearing1 = pBridgeBuilder->appendProduct(pPier, "ifcbearing", "Bearing 2.2", pPlacement);
  if (!pBearing1.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearing1);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPosition;
      localPosition.setTranslation(OdGeVector3d(-bearingDistance, bearingOffset, pierHeight));
      ExBearing *bearingGeom = new ExBearing(localPosition, bearingXDim, bearingYDim, 80., 80., 500);
      pRB->process(bearingGeom);
      delete bearingGeom;
    }
  }

  OdIfc::OdIfcEntityPtr pColumn = pBridgeBuilder->appendProduct(pPier, "ifccolumn", "Column", pPlacement);
  if (!pColumn.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pColumn);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPlacement;
      localPlacement.setTranslation(OdGeVector3d(0., 0., 0.));
      ExPier *columnGeom = new ExPier(localPlacement, pierHeight, 6000., 2000., 400., 9000., 3000., capHeight, capWing, bearingThickness);
      pRB->process(columnGeom);
      delete columnGeom;
    }
    IfcPropertySetFillerPtr propertySet = filler->createPropertySet(pColumn);
    propertySet->
      appendPropertySingleValue("Reference", OdAnsiString("P1"), "IfcIdentifier").
      appendPropertySingleValue("Status", OdAnsiString("New"), "IfcLabel").
      appendPropertySingleValue("Slope", 0., "IfcPlaneAngleMeasure").
      appendPropertySingleValue("Roll", 0., "IfcPlaneAngleMeasure").
      appendPropertySingleValue("IsExternal", true, "IfcBoolean").
      appendPropertySingleValue("ThermalTransmittance", 0., "IfcThermalTransmittanceMeasure").
      appendPropertySingleValue("LoadBearing", true, "IfcBoolean").
      appendPropertySingleValue("FireRating", OdAnsiString("FR1"), "IfcLabel").
      createPropertySet("Pset_ColumnCommon");
  }

  OdIfc::OdIfcEntityPtr pFooting = pBridgeBuilder->appendProduct(pPier, "ifcfooting", "Footing", pPlacement);
  if (!pFooting.isNull())
  {
    pFooting->putAttr("predefinedtype", OdAnsiString("pile_cap"));
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pFooting);
    if (!pRB.isNull())
    {
      ExFooting *columnGeom = new ExFooting(OdGeMatrix3d::kIdentity, footingXDim, footingYDim, footingDepth);
      pRB->process(columnGeom);
      delete columnGeom;
    }
    IfcPropertySetFillerPtr propertySet = filler->createPropertySet(pFooting);
    propertySet->
      appendPropertySingleValue("Reference", OdAnsiString("Footing with piles"), "IfcIdentifier").
      appendPropertySingleValue("Status", OdAnsiString("New"), "IfcLabel").
      appendPropertySingleValue("LoadBearing", false, "IfcBoolean").
      createPropertySet("Pset_FootingCommon");
  }

  return pPier;
}

OdIfc::OdIfcEntityPtr AppendPavement(
  IfcBridgeBuilderPtr pBridgeBuilder,
  OdIfc::OdIfcEntityPtr pSuperStructure,
  const OdAnsiString &name, // asphalt/concrete

  OdGePoint3d startPoint,
  OdGePoint3d endPoint,
  double xdim,
  double ydim,
  const OdAnsiString &styleName
)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  // TODO: mPlacement to appendBridgePart
  OdGeMatrix3d mPlacement = OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kZAxis);
  //mPlacement *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
  //objectPlacement.z += elevation;
  //mPlacement.setTranslation(objectPlacement.asVector());
  mPlacement.setToTranslation(startPoint.asVector());
  OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(mPlacement);
  OdIfc::OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);

  //OdIfc::OdIfcEntityPtr pGirder = pBridgeBuilder->appendBridgePart(girderName, pSuperStructure, IfcBridgeBuilder::kGIRDER);
  //pGirder->putAttr("objectplacement", OdDAIObjectId(pPlacement->id()));

  OdDAIObjectId idReplPlacement;

  OdIfc::OdIfcEntityPtr pParapet = pBridgeBuilder->appendProduct(pSuperStructure, "ifcslab", name, pPlacement);
  if (!pParapet.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pParapet);
    if (!pRB.isNull())
    {
      ExPavement *pavementGeom = new ExPavement(startPoint, endPoint, name, xdim, ydim, styleName);
      pRB->process(pavementGeom);
      delete pavementGeom;
    }
  }

  return pParapet;
}

OdIfc::OdIfcEntityPtr AppendGirder(IfcBridgeBuilderPtr pBridgeBuilder,
                                   OdIfc::OdIfcEntityPtr pSuperStructure,
                                   OdIfc::OdIfcEntityPtr pPlacement,
                                   const OdAnsiString& name,
                                   OdDAIObjectId idAlignmentCurve,
                                   OdDAIObjectId idGirderProfile,
                                   OdDAIObjectId start,
                                   OdDAIObjectId end)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  OdIfc::OdIfcEntityPtr pGirder = pBridgeBuilder->appendProduct(pSuperStructure, "ifcbeam", name, pPlacement);
  if (!pGirder.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pGirder);
    if (!pRB.isNull())
    {
      OdGeMatrix3d mObjectPlacement;

      ExSectionedSolid* pBearingGeom = new ExSectionedSolid(idAlignmentCurve, idGirderProfile, start, end);

      pRB->process(pBearingGeom);
      delete pBearingGeom;
    }
  }

  return pGirder;
}

OdIfc::OdIfcEntityPtr AppendDeck(IfcBridgeBuilderPtr pBridgeBuilder,
                                 OdIfc::OdIfcEntityPtr pSuperStructure,
                                 OdIfc::OdIfcEntityPtr pPlacement,
                                 const OdAnsiString& name,
                                 OdDAIObjectId idAlignmentCurve,
                                 OdDAIObjectId idGirderProfile,
                                 OdDAIObjectId start,
                                 OdDAIObjectId end)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  OdIfc::OdIfcEntityPtr pDeck = pBridgeBuilder->appendProduct(pSuperStructure, "ifcslab", name, pPlacement);
  if (!pDeck.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pDeck);
    if (!pRB.isNull())
    {
      ExSectionedSolid* deckGeom = new ExSectionedSolid(idAlignmentCurve, idGirderProfile, start, end);
      pRB->process(deckGeom);
      delete deckGeom;
    }
  }

  return pDeck;
}

OdIfc::OdIfcEntityPtr AppendBarrier(
  IfcBridgeBuilderPtr pBridgeBuilder,
  OdIfc::OdIfcEntityPtr pSuperStructure,
  OdIfc::OdIfcEntityPtr pPlacement,
  const OdAnsiString& name,
  OdDAIObjectId idAlignmentCurve,
  OdDAIObjectId idProfile,
  OdDAIObjectId start,
  OdDAIObjectId end
)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  OdIfc::OdIfcEntityPtr pBarrier = pBridgeBuilder->appendProduct(pSuperStructure, "ifcbeam", name, pPlacement);
  if (!pBarrier.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBarrier);
    if (!pRB.isNull())
    {
      ExSectionedSolid* barrierGeom = new ExSectionedSolid(idAlignmentCurve, idProfile, start, end);
      pRB->process(barrierGeom);
      delete barrierGeom;
    }
  }

  return pBarrier;
}


OdIfc::OdIfcEntityPtr AppendAbutment(
  IfcBridgeBuilderPtr pBridgeBuilder,
  OdIfc::OdIfcEntityPtr pSuperStructure,
  OdGePoint3d objectPlacement,
  const OdAnsiString &abutmentName,
  bool rotate,

  double elevation,
  double girderYDim,

  double bearingSeatXDim,
  double bearingSeatYDim,
  double bearingDistance,
  double bearingOffset,

  double footingXDimDelta,
  double footingYDim,
  double footingDepth,

  double wingWallWidth,
  double wingWallLength,

  double wingWallBrickWidth
)
{
  double halfBearingSeatXDim = bearingSeatXDim * 0.5;

  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  // TODO: mPlacement to appendBridgePart
  OdGeMatrix3d mPlacement;
  if (rotate)
  {
    mPlacement.setToRotation(OdaPI, OdGeVector3d(0., 0., 1.));
  }
  mPlacement.setTranslation(objectPlacement.asVector());
  OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(mPlacement);
  OdIfc::OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);

  OdIfc::OdIfcEntityPtr pAbutment = pBridgeBuilder->appendBridgePart(abutmentName, pSuperStructure, IfcBridgeBuilder::kABUTMENT);
  pAbutment->putAttr("objectplacement", OdDAIObjectId(pPlacement->id()));

  OdIfc::OdIfcEntityPtr pFoundation = pBridgeBuilder->appendProduct(pAbutment, "ifccolumn", "Foundation", pPlacement);
  if (!pFoundation.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pFoundation);
    if (!pRB.isNull())
    {
      ExFooting *columnGeom = new ExFooting(OdGeMatrix3d::kIdentity, bearingSeatXDim + footingXDimDelta, footingYDim, footingDepth);
      pRB->process(columnGeom);
      delete columnGeom;
    }
    IfcPropertySetFillerPtr propertySet = filler->createPropertySet(pFoundation);
    propertySet->
      appendPropertySingleValue("Reference", OdAnsiString("Abutment foundation"), "IfcIdentifier").
      appendPropertySingleValue("Status", OdAnsiString("New"), "IfcLabel").
      appendPropertySingleValue("LoadBearing", false, "IfcBoolean").
      createPropertySet("Pset_FootingCommon");
  }

  OdIfc::OdIfcEntityPtr pBearing1 = pBridgeBuilder->appendProduct(pAbutment, "ifcbearing", "Bearing 2", pPlacement);
  if (!pBearing1.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearing1);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPosition;
      localPosition.setTranslation(OdGeVector3d(-bearingDistance, bearingOffset, elevation));
      ExBearing *bearingGeom = new ExBearing(localPosition, 1200., 1200., 80., 80., 500.);
      pRB->process(bearingGeom);
      delete bearingGeom;
    }
  }

  OdIfc::OdIfcEntityPtr pBearing2 = pBridgeBuilder->appendProduct(pAbutment, "ifcbearing", "Bearing 1", pPlacement);
  if (!pBearing2.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearing2);
    if (!pRB.isNull())
    {
      OdGeMatrix3d localPlacement;
      localPlacement.setTranslation(OdGeVector3d(bearingDistance, bearingOffset, elevation));
      ExBearing *bearingGeom = new ExBearing(localPlacement, 1200., 1200., 80., 80., 500.);
      pRB->process(bearingGeom);
      delete bearingGeom;
    }
  }

  //
  // Create geometry without Representation Adapters
  //
  OdIfc::OdIfcEntityPtr grc = filler->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdAnsiString strBody("Body");
  OdIfc::OdIfcEntityPtr pSR = filler->model()->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr("contextofitems", OdDAIObjectId(grc->id()));
  pSR->putAttr("representationidentifier", strBody);

  OdIfc::OdIfcEntityPtr pBearingSeat = pBridgeBuilder->appendProduct(pAbutment, "ifcwall", "Bearing Seat Wall", pPlacement);
  if (!pBearingSeat.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pBearingSeat);
    if (!pRB.isNull())
    {
      // Abutment wall (bearing seat + frontal wall)
      IfcProfileBuilderPtr profileBuilder = pRB->createProfileBuilder();
      OdGePoint2dArray points;
      points.append(OdGePoint2d(-halfBearingSeatXDim, 0));
      points.append(OdGePoint2d(halfBearingSeatXDim, 0));
      points.append(OdGePoint2d(halfBearingSeatXDim, bearingSeatYDim));
      points.append(OdGePoint2d(-halfBearingSeatXDim, bearingSeatYDim));
      OdIfc::OdIfcEntityPtr profile = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "Bearing Seat Wall Profile", points);
      OdIfc::OdIfcEntityPtr extrudeInst = pRB->createExtrudedAreaSolid(profile, elevation, filler->dirZ());

      points.clear();
      points.append(OdGePoint2d(-halfBearingSeatXDim, -(bearingSeatYDim + 500)));
      points.append(OdGePoint2d(halfBearingSeatXDim, -(bearingSeatYDim + 500)));
      points.append(OdGePoint2d(halfBearingSeatXDim, 0.));
      points.append(OdGePoint2d(-halfBearingSeatXDim, 0.));
      OdIfc::OdIfcEntityPtr profileBackWall = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "Bearing Seat Wall Profile", points);
      OdIfc::OdIfcEntityPtr extrudeBackWallInst = pRB->createExtrudedAreaSolid(profileBackWall, elevation + girderYDim, filler->dirZ());

      OdIfc::OdIfcEntityPtr booleanInst = pRB->createIfcBooleanResult(extrudeInst, extrudeBackWallInst, "union");

      // Left
      {
        points.clear();
        points.append(OdGePoint2d(-halfBearingSeatXDim, -(bearingSeatYDim + 500)));
        points.append(OdGePoint2d(-halfBearingSeatXDim, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(-halfBearingSeatXDim + wingWallWidth, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(-halfBearingSeatXDim + wingWallWidth, -(bearingSeatYDim + 500)));
        OdIfc::OdIfcEntityPtr profileLeftWingWall = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "Left Wing Wall Profile", points);
        OdIfc::OdIfcEntityPtr leftWingWallInst = pRB->createExtrudedAreaSolid(profileLeftWingWall, elevation + girderYDim, filler->dirZ());
        booleanInst = pRB->createIfcBooleanResult(booleanInst, leftWingWallInst, "union");
      }

      // Right
      {
        points.clear();
        points.append(OdGePoint2d(halfBearingSeatXDim - wingWallWidth, -(bearingSeatYDim + 500)));
        points.append(OdGePoint2d(halfBearingSeatXDim - wingWallWidth, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(halfBearingSeatXDim, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(halfBearingSeatXDim, -(bearingSeatYDim + 500)));
        OdIfc::OdIfcEntityPtr profileRightWingWall = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "Left Wing Wall Profile", points);
        OdIfc::OdIfcEntityPtr rightWingWallInst = pRB->createExtrudedAreaSolid(profileRightWingWall, elevation + girderYDim, filler->dirZ());
        booleanInst = pRB->createIfcBooleanResult(booleanInst, rightWingWallInst, "union");
      }

      filler->appendId(pSR, OdIfc::kItems, OdDAIObjectId(booleanInst->id()));

      //setStyledItem(leftWingWallInst, "ConcreteDark");
      OdIfc::OdIfcEntityPtr abutmentConcreteStyle = filler->findSurfaceStyle("ConcreteDark");
      if (!abutmentConcreteStyle.isNull())
      {
        filler->createStyledItem(booleanInst, abutmentConcreteStyle);
      }

      //
      // Wing walls
      //

      OdIfc::OdIfcEntityPtr surfaceWingStyle = filler->findSurfaceStyle("AbutmentBrick");

      // Left wing wall lining 
      {
        points.clear();
        points.append(OdGePoint2d(-halfBearingSeatXDim - wingWallBrickWidth, 0.));
        points.append(OdGePoint2d(-halfBearingSeatXDim - wingWallBrickWidth, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(-halfBearingSeatXDim , -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(-halfBearingSeatXDim , 0.));
        OdIfc::OdIfcEntityPtr profileLeftWingWall = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "Left Wing Wall Profile", points);
        OdIfc::OdIfcEntityPtr leftWingWallInst = pRB->createExtrudedAreaSolid(profileLeftWingWall, elevation + girderYDim, filler->dirZ());

        if (!surfaceWingStyle.isNull())
        {
          filler->createStyledItem(leftWingWallInst, surfaceWingStyle);
        }

        filler->appendId(pSR, OdIfc::kItems, OdDAIObjectId(leftWingWallInst->id()));
      }

      // Right wing wall lining
      {
        points.clear();
        points.append(OdGePoint2d(halfBearingSeatXDim, 0.));
        points.append(OdGePoint2d(halfBearingSeatXDim, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(halfBearingSeatXDim + wingWallBrickWidth, -(bearingSeatYDim + 500 + wingWallLength)));
        points.append(OdGePoint2d(halfBearingSeatXDim + wingWallBrickWidth, 0.));
        OdIfc::OdIfcEntityPtr profileRightWingWall = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "Left Wing Wall Profile", points);
        OdIfc::OdIfcEntityPtr rightWingWallInst = pRB->createExtrudedAreaSolid(profileRightWingWall, elevation + girderYDim, filler->dirZ());

        if (!surfaceWingStyle.isNull())
        {
          filler->createStyledItem(rightWingWallInst, surfaceWingStyle);
        }

        filler->appendId(pSR, OdIfc::kItems, OdDAIObjectId(rightWingWallInst->id()));
      }
    }
  }

  filler->model()->appendEntityInstance(pSR);

  OdIfcModelPtr model = filler->model();
  OdIfc::OdIfcEntityPtr pInst = model->createEntityInstance("ifcproductdefinitionshape");
  filler->appendId(pInst, OdIfc::kRepresentations, OdDAIObjectId(pSR->id()));
  OdDAIObjectId idPDS = model->appendEntityInstance(pInst);

  //processPlacement();
  OdGeMatrix3d localPlacement;
  localPlacement.setTranslation(OdGeVector3d(0., 0., 0.));
  OdIfc::OdIfcEntityPtr relativePlacement = filler->createAxis2Placement3D(localPlacement);

  {
    OdIfc::OdIfcEntityPtr objectPlacement;
    OdDAIObjectId id;
    if (pBearingSeat->getAttr("objectplacement") >> id)
    {
      OdIfc::OdIfcEntityPtr objectPlacement = id.openObject();
      objectPlacement->putAttr("relativeplacement", OdDAIObjectId(relativePlacement->id()));
    }
    else
    {
      objectPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), relativePlacement);
      pBearingSeat->putAttr("objectplacement", OdDAIObjectId(objectPlacement->id()));
    }
  }

  pBearingSeat->putAttr("representation", idPDS);

  return pAbutment;
}

OdIfc::OdIfcEntityPtr AppendParapet(
  IfcBridgeBuilderPtr pBridgeBuilder,
  OdIfc::OdIfcEntityPtr pSuperStructure,
  //OdGePoint3d objectPlacement,
  const OdAnsiString &name,

  OdGePoint3d startPoint,
  OdGePoint3d endPoint,
  double height,
  double width,
  unsigned int hrzSegmentsCount,
  unsigned int vrtSegmentsCount
)
{
  ExIfcModelFiller *filler = pBridgeBuilder->filler();

  // TODO: mPlacement to appendBridgePart
  OdGeMatrix3d mPlacement = OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kZAxis);
  //mPlacement *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
  //objectPlacement.z += elevation;
  //mPlacement.setTranslation(objectPlacement.asVector());
  mPlacement.setToTranslation(startPoint.asVector());
  OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(mPlacement);
  OdIfc::OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);

  //OdIfc::OdIfcEntityPtr pGirder = pBridgeBuilder->appendBridgePart(girderName, pSuperStructure, IfcBridgeBuilder::kGIRDER);
  //pGirder->putAttr("objectplacement", OdDAIObjectId(pPlacement->id()));

  OdDAIObjectId idReplPlacement;

  OdIfc::OdIfcEntityPtr pParapet = pBridgeBuilder->appendProduct(pSuperStructure, "ifcrailing", name, pPlacement);
  if (!pParapet.isNull())
  {
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pParapet);
    if (!pRB.isNull())
    {
      ExParapet *parapetGeom = new ExParapet(startPoint, endPoint, name,
        height, width, hrzSegmentsCount, vrtSegmentsCount);
      pRB->process(parapetGeom);
      delete parapetGeom;
    }
  }

  return pParapet;
}

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  /**********************************************************************/
  /* Command line parameters description                                */
  /**********************************************************************/
  if (argc < 2 || argc > 2)
  {
    odPrintConsoleString(L"\nExIfcBridge sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: ExIfcBridge <target IFC4X3_RC4 filename>\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    STD(cin).get();
    return 1;
  }

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  int nRes = 0; // Return value for main

  // create a service
  OdStaticRxObject< MyServices > svcs;

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize( &svcs );
  odDbRootInitialize();

  if (odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */))
    return 2;

  appInit();

  //
  // Call of IfcCore
  //
  OdIfcFilePtr pIfcFile = svcs.createDatabase("IFC4X3_RC4");

  {
    using namespace OdIfc;

    // OdIfcFile keeps model opened to avoid outside access.
    OdIfcModelPtr pModel = pIfcFile->getModel(sdaiRW);

    ExIfcModelFillerPtr filler(new ExIfcModelFiller(pModel));
    OdArray<OdIfcEntityPtr> units;
    units.append(filler->createSiUnit("LENGTHUNIT", "MILLI", "METRE"));
    units.append(filler->createSiUnit("PLANEANGLEUNIT", NULL, "RADIAN"));
    units.append(filler->createSiUnit("AREAUNIT", NULL, "SQUARE_METRE"));
    units.append(filler->createSiUnit("VOLUMEUNIT", NULL, "CUBIC_METRE"));
    OdIfcEntityPtr project = filler->fromScratch("Open Design Alliance", "ExIfcBridge", units);
    filler->appendGeometricRepresentationContext("2D", "Plan", 2);
    filler->appendGeometricRepresentationContext("3D", "Model", 3, 1e-6);

    // Colors for surfaces (not materials in IFC sense of word)
    filler->createSurfaceStyle("ConcreteDark", OdCmEntityColor(128, 128, 128));
    filler->createSurfaceStyle("ConcreteLight", OdCmEntityColor(192, 192, 192));
    filler->createSurfaceStyle("Asphalt", OdCmEntityColor(0, 0, 64));
    filler->createSurfaceStyle("PavingStone", OdCmEntityColor(128, 64, 64));
    filler->createSurfaceStyle("RailingSteel", OdCmEntityColor(158, 207, 207));
    filler->createSurfaceStyle("BearingBase", OdCmEntityColor(0, 128, 128));
    filler->createSurfaceStyle("BearingLiner", OdCmEntityColor(192, 255, 255));
    filler->createSurfaceStyle("AbutmentBrick", OdCmEntityColor(96, 32, 32));
    filler->createSurfaceStyle("Terrain", OdCmEntityColor(38, 76, 0));
    filler->createSurfaceStyle("RebarSteel", OdCmEntityColor(224, 0, 0));

    // IfcSite
    filler->site()->putAttr("name", OdAnsiString("Site"));
    filler->createPropertySet(filler->site())->
      appendPropertySingleValue("Reference", OdAnsiString("Surface"), "IfcIdentifier").
      createPropertySet("Pset_SiteCommon");

    // IfcAlignment for such points array

    double spanLength = 20000.; // distance between piers

    OdGePoint3dArray points;
    points.push_back(OdGePoint3d(0., -spanLength, 0.));
    points.push_back(OdGePoint3d(0., 0., 0.));
    points.push_back(OdGePoint3d(0., spanLength, 0.));
    points.push_back(OdGePoint3d(0., spanLength * 2, 0.));
    points.push_back(OdGePoint3d(0., spanLength * 3, 0.));
    points.push_back(OdGePoint3d(0., spanLength * 4, 0.));
    points.push_back(OdGePoint3d(0., spanLength * 5, 0.));
    OdGePoint3d pointForAbutment2(0., spanLength * 6, 0.);

    OdArray<double> substructureHeights;
    substructureHeights.append(6000.);
    substructureHeights.append(6000.);
    substructureHeights.append(9000.);
    substructureHeights.append(19000.);
    substructureHeights.append(21000.);
    substructureHeights.append(13500.);
    substructureHeights.append(6000.);

    OdArray<double> pileHeights;
    pileHeights.append(1500.);
    pileHeights.append(1500.);
    pileHeights.append(2000.);
    pileHeights.append(4000.);
    pileHeights.append(3000.);
    pileHeights.append(2000.);
    pileHeights.append(1500.);
    pileHeights.append(1500.);

    int spansCount = points.size(); // points.size - 1 + one more point

    OdDAIObjectId idAlignmentCurve = OdDAI::Utils::getUnset<OdDAIObjectId>();

    const OdDAI::Entity *pAlignmentDef = pModel->getEntityDefinition("ifcalignment");
    if (pAlignmentDef)
    {
      OdIfcEntityPtr startPoint = filler->createCartesianPoint3D(points[0]);
      OdIfcEntityPtr lineSegment2d = pModel->createEntityInstance("ifcalignmenthorizontalsegment");
      const double curveLength = (spansCount + 1.) * spanLength;
      {
        OdRxValue val;
        val << OdAnsiString("Bridge Start Point");
        OdRxSpecifiedValueType vt(val.type(), "IfcLabel");
        lineSegment2d->putAttr("starttag", OdRxValue(vt, val));
        val << OdAnsiString("Bridge End Point");
        lineSegment2d->putAttr("endtag", OdRxValue(vt, val));
      }

      OdDAIObjectId startPoint3dId = OdDAIObjectId(startPoint->id());
      lineSegment2d->putAttr("startpoint", startPoint3dId);
      lineSegment2d->putAttr("startdirection", OdaPI2);
      lineSegment2d->putAttr("startradiusofcurvature", 0.);
      lineSegment2d->putAttr("endradiusofcurvature", 0.);
      lineSegment2d->putAttr("segmentlength", curveLength);
      lineSegment2d->putAttr("predefinedtype", OdAnsiString("LINE"));
      OdDAIObjectId idLine2DSegment = pModel->appendEntityInstance(lineSegment2d);

      OdIfcEntityPtr alignment2Dsegment = pModel->createEntityInstance("ifcalignmentsegment");
      OdIfc::Utils::assignGlobalId(alignment2Dsegment);
      alignment2Dsegment->putAttr("designparameters", idLine2DSegment);
      OdDAIObjectId idAlignment2DSegment = pModel->appendEntityInstance(alignment2Dsegment);

      OdIfcEntityPtr pAlignment2Dhrz = pModel->createEntityInstance("ifcalignmenthorizontal");
      OdIfc::Utils::assignGlobalId(pAlignment2Dhrz);
      OdDAIObjectId idAlignment2Dhrz = pModel->appendEntityInstance(pAlignment2Dhrz);

      OdDAIObjectIds idsSegments;
      idsSegments.append(idAlignment2DSegment);
      filler->addRelNests(pAlignment2Dhrz, idsSegments);

      //
      // Create represenation of Alignment
      //

      // Create IfcCurve for horizontal part
      OdIfcEntityPtr pLineHorizontal = pModel->createEntityInstance("ifcline");
      {
        OdGeVector2d direction = OdGeVector2d::kYAxis;
        OdIfcEntityPtr pDirection = filler->createDirection2D(direction);
        OdIfcEntityPtr pVector = filler->createVector(pDirection, 1.);
        OdIfcEntityPtr pStartPoint2d = filler->createCartesianPoint2D(OdGePoint2d::kOrigin);
        
        pLineHorizontal->putAttr("pnt", OdDAIObjectId(pStartPoint2d->id()));
        pLineHorizontal->putAttr("dir", OdDAIObjectId(pVector->id()));

//         OdGePoint2d endPoint2d = (OdGeVector2d::kYAxis * spanLength * spansCount).asPoint();
//         OdIfcEntityPtr pEndPoint2d = filler->createCartesianPoint2D(endPoint2d);
//         OdGePoint2d startPoint2d = points[0].convert2d();
//         OdIfcEntityPtr pStartPoint2d = filler->createCartesianPoint2D(startPoint2d);
//         OdDAIObjectId endPoint2dId = OdDAIObjectId(pEndPoint2d->id());
//         OdDAIObjectId startPoint2dId = OdDAIObjectId(pStartPoint2d->id());
//         OdDAIObjectIds cartesianPoints(2);
//         cartesianPoints.append(startPoint2dId);
//         cartesianPoints.append(endPoint2dId);
//         pPLineHorizontal->putAttr("points", cartesianPoints);
      }
      OdDAIObjectId pPLineHorizontalId = pModel->appendEntityInstance(pLineHorizontal);

      // Create IfcCurveSegment for horizontal part
      OdIfcEntityPtr pHorizontalSegment = pModel->createEntityInstance("ifccurvesegment");
      pHorizontalSegment->putAttr("transition", OdAnsiString("DISCONTINUOUS"));
      OdIfcEntityPtr pPlacement;
      {
        OdGeMatrix2d matr;
        OdGePoint2d origin = points[0].convert2d();
        matr.setCoordSystem(origin, OdGeVector2d::kYAxis, OdGeVector2d::kYAxis.perpVector());
        pPlacement = filler->createAxis2Placement2D(matr);
      }
      pHorizontalSegment->putAttr("placement", OdDAIObjectId(pPlacement->id()));

      {
        OdRxValue val;
        val << 0.;
        OdRxSpecifiedValueType vt(val.type(), "IfcNonNegativeLengthMeasure");
        pHorizontalSegment->putAttr("segmentstart", OdRxValue(vt, val));
        val << curveLength;
        pHorizontalSegment->putAttr("segmentlength", OdRxValue(vt, val));
      }
      pHorizontalSegment->putAttr("parentcurve", pPLineHorizontalId);
      OdDAIObjectId curveSegmentId = pModel->appendEntityInstance(pHorizontalSegment);

      // Create IfcCompositeCurve
      OdIfcEntityPtr pCompositeCurve = pModel->createEntityInstance("ifccompositecurve");
      {
        OdDAIObjectIds segmentIds;
        segmentIds.append(curveSegmentId);
        pCompositeCurve->putAttr("segments", segmentIds);
      }
      pCompositeCurve->putAttr("selfintersect", OdDAI::Logical(false));
      OdDAIObjectId compositeCurveId = pModel->appendEntityInstance(pCompositeCurve);

      {
        // Create IfcShapeRepresentation
        OdIfc::OdIfcEntityPtr pSR = filler->model()->createEntityInstance("ifcshaperepresentation");
        {
          OdDAIObjectIds items;
          items.append(compositeCurveId);
          pSR->putAttr("items", items);
        }
        pSR->putAttr("contextofitems", OdDAIObjectId(filler->getGeometricRepresentationContext("Plan")->id()));
        pSR->putAttr("representationidentifier", OdAnsiString("Curve2D"));
        OdDAIObjectId shapeRepresentationId = pModel->appendEntityInstance(pSR);

        // Create IfcProductDefinitionShape
        OdIfc::OdIfcEntityPtr pInst = pModel->createEntityInstance("ifcproductdefinitionshape");
        filler->appendId(pInst, OdIfc::kRepresentations, shapeRepresentationId);
        OdDAIObjectId idPDS = pModel->appendEntityInstance(pInst);
        pAlignment2Dhrz->putAttr("representation", idPDS);
      }

      // Create IfcCurve for vertical part
      OdIfcEntityPtr pLineVertical = pModel->createEntityInstance("ifcline");
      {
        OdGeVector2d direction = OdGeVector2d::kXAxis;
        OdIfcEntityPtr pDirection = filler->createDirection2D(direction);
        OdIfcEntityPtr pVector = filler->createVector(pDirection, 1.);
        OdIfcEntityPtr pStartPoint2d = filler->createCartesianPoint2D(OdGePoint2d::kOrigin);

        pLineVertical->putAttr("pnt", OdDAIObjectId(pStartPoint2d->id()));
        pLineVertical->putAttr("dir", OdDAIObjectId(pVector->id()));

//         OdGePoint2d startPoint2d = OdGePoint2d::kOrigin;
//         OdGePoint2d endPoint2d(curveLength, 0.);
//         OdIfcEntityPtr pStartPoint2d = filler->createCartesianPoint2D(startPoint2d);
//         OdIfcEntityPtr pEndPoint2d = filler->createCartesianPoint2D(endPoint2d);
//         OdDAIObjectId startPoint2dId = OdDAIObjectId(pStartPoint2d->id());
//         OdDAIObjectId endPoint2dId = OdDAIObjectId(pEndPoint2d->id());
//         OdDAIObjectIds pointIds(2);
//         pointIds.append(startPoint2dId);
//         pointIds.append(endPoint2dId);
//         pPLineVertical->putAttr("points", pointIds);
      }
      OdDAIObjectId pPLineVerticalId = pModel->appendEntityInstance(pLineVertical);

      // Create IfcCurveSegment for vertical part
      OdIfcEntityPtr pVerticalSegment = pModel->createEntityInstance("ifccurvesegment");
      pVerticalSegment->putAttr("transition", OdAnsiString("DISCONTINUOUS"));
      pVerticalSegment->putAttr("placement", filler->identity2D());
      {
        OdRxValue val;
        val << 0.;
        OdRxSpecifiedValueType vt(val.type(), "IfcNonNegativeLengthMeasure");
        pVerticalSegment->putAttr("segmentstart", OdRxValue(vt, val));
        val << curveLength;
        pVerticalSegment->putAttr("segmentlength", OdRxValue(vt, val));
      }
      pVerticalSegment->putAttr("parentcurve", pPLineVerticalId);
      OdDAIObjectId verticalSegmentId = pModel->appendEntityInstance(pVerticalSegment);

      // CreateIfcGradientCurve
      OdIfcEntityPtr pGradientCurve = pModel->createEntityInstance("ifcgradientcurve");
      {
        OdDAIObjectIds segmentIds;
        segmentIds.append(verticalSegmentId);
        pGradientCurve->putAttr("segments", segmentIds);
      }
      pGradientCurve->putAttr("selfintersect", OdDAI::Logical(false));
      pGradientCurve->putAttr("basecurve", compositeCurveId);
      OdDAIObjectId gradientCurveId = pModel->appendEntityInstance(pGradientCurve);
      idAlignmentCurve = gradientCurveId;


      // Create IfcAlignment
      OdIfcEntityPtr alignment = pModel->createEntityInstance(pAlignmentDef);
      OdIfc::Utils::assignGlobalId(alignment);
      alignment->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
      alignment->putAttr("name", OdAnsiString("Alignment"));
      alignment->putAttr("predefinedtype", OdAnsiString("NOTDEFINED"));
      {
        // Create IfcShapeRepresentation
        OdIfc::OdIfcEntityPtr pSR = filler->model()->createEntityInstance("ifcshaperepresentation");
        {
          OdDAIObjectIds items;
          items.append(gradientCurveId);
          pSR->putAttr("items", items);
        }
        pSR->putAttr("contextofitems", OdDAIObjectId(filler->getGeometricRepresentationContext("Model")->id()));
        pSR->putAttr("representationidentifier", OdAnsiString("Curve3D"));
        OdDAIObjectId shapeRepresentationId = pModel->appendEntityInstance(pSR);

        // Create IfcProductDefinitionShape
        OdIfc::OdIfcEntityPtr pInst = pModel->createEntityInstance("ifcproductdefinitionshape");
        filler->appendId(pInst, OdIfc::kRepresentations, shapeRepresentationId);
        OdDAIObjectId idPDS = pModel->appendEntityInstance(pInst);

        alignment->putAttr("representation", idPDS);
      }
      filler->appendRelContainedInSpatialStructure(filler->site(), alignment);
    
      OdDAIObjectIds parts;
      parts.append(idAlignment2Dhrz);
      filler->addRelNests(alignment, parts);
    }

    IfcBridgeBuilderPtr pBridgeBuilder = filler->appendBridge("Girder Bridge Example", IfcBridgeBuilder::kGIRDER);
    if (!pBridgeBuilder.isNull())
    {
      IfcPropertySetFillerPtr propertySet = filler->createPropertySet(pBridgeBuilder->getBridge());
      propertySet->
        appendPropertySingleValue("StructureIndicator", OdAnsiString("COMPOSITE"), "IfcLabel").
        createPropertySet("Pset_BridgeCommon");
      propertySet->
        appendPropertySingleValue("Piers", 6, "IfcInteger").
        appendPropertySingleValue("Abutments", 2, "IfcInteger").
        createPropertySet("Pset_ExIfcBridgeApp");

      double elevation = 6000.; // elevation to bearing seat (from zero height)
      
      // Pier
      double footingXDim = 11000.;
      double footingYDim = 4000.;
      double pierCapHeight = 3000.;
      double pierCapWing = 1000.;

      // Road cap elements
      double parapetXDim = 200.;
      double parapetHeight = 1400.;
      int columnsNumInParapetSegment = 12;
      int parapetVrtSegmentsCount = 4;
      double trafficBarrierXDim = 300.;
      double trafficBarrierYDim = 1200.;
      double footPathWidth = 1500.;
      double footPathThickness = 150.;
      double roadSurfacingWidth = 3500. * 4.;
      double asphaltThickness = 100.;
      
      double deskWidth = parapetXDim + footPathWidth + trafficBarrierXDim + roadSurfacingWidth + trafficBarrierXDim + footPathWidth + parapetXDim;
      double girderXDim = deskWidth;
      double girderYDim = 2500.;
      double bearingDistance = 3500.; // distance from center oh a pier to the bearing
      double bearingOffset = 750.;
      double bearingXDim = 1200.; // X-size of bearing
      double bearingYDim = 1200.; // Y-size of bearing
      double bearingTopThickness = 80.;
      double bearingBaseThisckness = 80.;
      double bearingThickness = bearingTopThickness + bearingBaseThisckness;
      double bearingSeatXDim = 15000.;
      double bearingSeatYDim = 1500.;

      // Girder
      double plateThickness = 500.;

      double pierFootingDepth = 3000.;
      double pierFootingXDim = 11000.;
      double pierFootingYDim = 2500.;
      double abutmentFootingDepth = 2000.;
      double abutmentFootingXDimDelta = 2000.;
      double abutmentFootingYDim = 11000.;
      double abutmentWingWallWidth = bearingSeatYDim;
      double abutmentWingWallLength = 7000.;
      double abutmentWingWallBrickWidth = 320.;


      // Piles
      double pileRadius = 600.;
      double pileHeight = 2500.;
      double rebarDiam = 35.81;

      //
      // Foundation
      //
      {
        OdIfc::OdIfcEntityPtr pFoundation = pBridgeBuilder->appendBridgePart("Foundation", pBridgeBuilder->getBridge(), IfcBridgeBuilder::kFOUNDATION);
        if (!pFoundation.isNull())
        {
          //
          // Pile sets for piers
          //
          for (unsigned int i = 1; i < points.size(); ++i)
          {
            OdAnsiString strName;
            strName.format("Piles set %i", i);

            AppendPileNetwork(
              pBridgeBuilder,
              pFoundation,
              points[i],
              strName,
              elevation,
              substructureHeights[i],

              footingXDim,
              footingYDim,
              pierFootingDepth,

              pileRadius,
              pileHeights[i],
              rebarDiam
              );
          }

          AppendPileNetwork(
            pBridgeBuilder,
            pFoundation,
            points[0] + OdGeVector3d(0., abutmentFootingYDim / 3., 0.),
            "Abutment 1 piles",
            elevation,
            substructureHeights[0],

            deskWidth,
            abutmentFootingYDim / 2.5,
            abutmentFootingDepth,

            pileRadius,
            4000.,

            rebarDiam);

          AppendPileNetwork(
            pBridgeBuilder,
            pFoundation,
            pointForAbutment2 + OdGeVector3d(0., -abutmentFootingYDim / 3., 0.),
            "Abutment 2 piles",
            elevation,
            substructureHeights[0],

            deskWidth,
            abutmentFootingYDim / 2.5,
            abutmentFootingDepth,

            pileRadius,
            4000.,

            rebarDiam);

        }
      }

      ExGirderProfile  girderProfile(filler.get(), "common_girder_profile", 
                                     girderXDim, girderYDim, 
                                     plateThickness, 3000., 
                                     bearingDistance, 
                                     bearingXDim);

      ExDeckProfile  deckProfile(filler.get(), "common_deck_profile",
                                 girderXDim, girderYDim,
                                 plateThickness, 3000.,
                                 bearingDistance,
                                 bearingXDim,
                                 spanLength);

      ExBarrierProfile leftBarrierProfile(filler.get(), "left_barier_profile",
                                          trafficBarrierXDim,
                                          trafficBarrierYDim,
                                          asphaltThickness,
                                          footPathThickness,
                                          spanLength,
                                          (trafficBarrierXDim + roadSurfacingWidth) * 0.5,
                                          pierFootingYDim);

      ExBarrierProfile rightBarrierProfile(filler.get(), "right_barier_profile",
                                           trafficBarrierXDim,
                                           trafficBarrierYDim,
                                           asphaltThickness,
                                           footPathThickness,
                                           spanLength,
                                           -(trafficBarrierXDim + roadSurfacingWidth) * 0.5,
                                           pierFootingYDim);
      //
      // Substructure
      //
      {
        OdIfc::OdIfcEntityPtr pSubStructure = pBridgeBuilder->appendBridgePart("Substructure", pBridgeBuilder->getBridge(), IfcBridgeBuilder::kSUBSTRUCTURE);
        if (!pSubStructure.isNull())
        {
          for (unsigned int i = 1; i < points.size(); ++i)
          {
            OdAnsiString pierName;
            pierName.format("Pier %i", i);

            OdIfcEntityPtr pier = AppendPier(pBridgeBuilder, pSubStructure, points[i], pierName,
              elevation,
              substructureHeights[i],
              footingXDim, footingYDim, pierFootingDepth,
              bearingXDim, bearingYDim,
              bearingDistance, bearingOffset, bearingThickness,
              pierCapHeight, pierCapWing);
          }

          AppendAbutment(
            pBridgeBuilder, pSubStructure, points[0], "Abutment 1", false,

            /* bearing seat elevation */ elevation, girderYDim + bearingThickness,
            /* bearing parameters */ deskWidth, bearingSeatYDim, bearingDistance, bearingOffset,
            /* foundation */ abutmentFootingXDimDelta + abutmentWingWallBrickWidth, abutmentFootingYDim, abutmentFootingDepth,
            /* wing walls */ abutmentWingWallWidth, abutmentWingWallLength, abutmentWingWallBrickWidth);

          AppendAbutment(
            pBridgeBuilder, pSubStructure, pointForAbutment2, "Abutment 2", true,

            /* bearing seat elevation */ elevation, girderYDim + bearingThickness,
            /* bearing parameters */ deskWidth, bearingSeatYDim, bearingDistance, bearingOffset,
            /* foundation */ abutmentFootingXDimDelta + abutmentWingWallBrickWidth, abutmentFootingYDim, abutmentFootingDepth,
            /* wing walls */ abutmentWingWallWidth, abutmentWingWallLength, abutmentWingWallBrickWidth);
        }
      }
      
      //
      // Superstructure
      //
      {
        OdIfc::OdIfcEntityPtr pSuperStructure = pBridgeBuilder->appendBridgePart("Superstructure", pBridgeBuilder->getBridge(), IfcBridgeBuilder::kSUPERSTRUCTURE);
        if (!pSuperStructure.isNull())
        {
          auto commonMatrix = OdGeMatrix3d::kIdentity;
          OdGePoint3d objectPlacement = OdGePoint3d::kOrigin;
          objectPlacement.z = elevation + bearingThickness;
          commonMatrix.setTranslation(objectPlacement.asVector());

          OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(commonMatrix);
          OdIfc::OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);

          OdAnsiString griderName("Girder");
          OdAnsiString deckName("Deck");
          OdAnsiString barrierName("Barrier");
          OdAnsiString deckSegmentName;
          OdDAIObjectIds pntIds(points.length());
          points.append(pointForAbutment2);
          for (auto pnt : points)
            pntIds.append(filler->createCartesianPoint3D(pnt)->id());
          for (unsigned int ctr = 1; ctr < pntIds.length(); ++ctr)
          {
            deckSegmentName.format("Deck segment %d", ctr);
            OdIfcEntityPtr pSegment = pBridgeBuilder->appendBridgePart(deckSegmentName, pSuperStructure, IfcBridgeBuilder::kDECK_SEGMENT);
            if (!pSegment.isNull())
            {
              griderName = "Girder";

              OdIfcEntityPtr pGirder = AppendGirder(pBridgeBuilder, 
                                                    pSegment,
                                                    pPlacement, 
                                                    griderName,
                                                    idAlignmentCurve, 
                                                    girderProfile.profile(),
                                                    pntIds[ctr - 1.],
                                                    pntIds[ctr]);

              OdIfcEntityPtr pDeck = AppendDeck(pBridgeBuilder,
                                                pSegment,
                                                pPlacement,
                                                deckName,
                                                idAlignmentCurve,
                                                deckProfile.profile(),
                                                pntIds[ctr - 1.],
                                                pntIds[ctr]);

              barrierName = "Left barrier";
              OdIfcEntityPtr pBarrierLeft = AppendBarrier(pBridgeBuilder, 
                                                          pSegment,
                                                          pPlacement, 
                                                          barrierName, 
                                                          idAlignmentCurve,
                                                          leftBarrierProfile.profile(),
                                                          pntIds[ctr - 1.],
                                                          pntIds[ctr]);

              barrierName = "Right barrier";
              OdIfcEntityPtr pBarrierRight = AppendBarrier(pBridgeBuilder,
                                                           pSegment,
                                                           pPlacement,
                                                           barrierName,
                                                           idAlignmentCurve,
                                                           rightBarrierProfile.profile(),
                                                           pntIds[ctr - 1.],
                                                           pntIds[ctr]);
            }
          }

          double xPosFootpath = (roadSurfacingWidth + footPathWidth) * 0.5 + trafficBarrierXDim;
          double xPos = footPathWidth + trafficBarrierXDim + (parapetXDim + roadSurfacingWidth) * 0.5;
          double yPos = -spanLength;
          double parapetElevation = elevation + girderYDim + bearingThickness;
          double parapetFullLength = spansCount * spanLength;

          // Left footpath
          {
            OdGePoint3d startPoint(-xPosFootpath, yPos, parapetElevation);
            OdGePoint3d endPoint(-xPosFootpath, yPos + parapetFullLength, parapetElevation);
            OdIfcEntityPtr pGirder = AppendPavement(pBridgeBuilder, pSuperStructure, "Footpath left",
              startPoint, endPoint,
              footPathWidth, footPathThickness,
              "PavingStone");
          }

          // Road pavement
          {
            OdGePoint3d startPoint(0, yPos - 600., parapetElevation);
            OdGePoint3d endPoint(0, yPos + parapetFullLength + 1200., parapetElevation);
            OdIfcEntityPtr pRoadPavement = AppendPavement(pBridgeBuilder, pSuperStructure, "Road pavement",
              startPoint, endPoint,
              roadSurfacingWidth, asphaltThickness,
              "Asphalt");
          }

          // Right footpath
          {
            OdGePoint3d startPoint(xPosFootpath, yPos - 500., parapetElevation);
            OdGePoint3d endPoint(xPosFootpath, yPos + parapetFullLength + 500., parapetElevation);
            OdIfcEntityPtr pGirder = AppendPavement(pBridgeBuilder, pSuperStructure, "Footpath right",
              startPoint, endPoint,
              footPathWidth, footPathThickness,
              "PavingStone");
          }

          // Parapet left
          {
            OdGePoint3d startPoint(-xPos, yPos, parapetElevation);
            OdGePoint3d endPoint(-xPos, yPos + parapetFullLength, parapetElevation);
            OdIfcEntityPtr pBarrierLeft = AppendParapet(
              pBridgeBuilder,
              pSuperStructure,
              "Parapet left",
              startPoint, endPoint,
              parapetHeight, parapetXDim,
              columnsNumInParapetSegment * spansCount, parapetVrtSegmentsCount);
          }

          // Parapet right
          {
            OdGePoint3d startPoint(xPos, yPos, parapetElevation);
            OdGePoint3d endPoint(xPos, yPos + parapetFullLength, parapetElevation);
            OdIfcEntityPtr pBarrierLeft = AppendParapet(
              pBridgeBuilder,
              pSuperStructure,
              "Parapet right",
              startPoint, endPoint,
              parapetHeight, parapetXDim,
              columnsNumInParapetSegment * spansCount, parapetVrtSegmentsCount);
          }
        }

      }
    }

  }

  OdDAI::OdHeaderSectionPtr header = pIfcFile->getHeaderSection();
  OdDAI::ApplicationInstancePtr pFileName = header->getEntityByType(OdDAI::kFileName);
  OdArray<OdAnsiString> authors;
  if (pFileName->getAttr("author") >> authors)
  {
    authors.push_back("ExIfcBridge app");
    pFileName->putAttr("author", authors);
  }

  pIfcFile->writeFile(argv[1]);
  pIfcFile.release();

  appUninit();

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize Runtime Extension environment                         */
  /**********************************************************************/
  odDbRootUninitialize();
  ::odrxUninitialize();

  return nRes;
}

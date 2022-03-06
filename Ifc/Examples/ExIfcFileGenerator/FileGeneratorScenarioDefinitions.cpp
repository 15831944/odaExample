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

#include "RxDynamicModule.h"
#include "DynamicLinker.h"

#include "OdPlatformStreamer.h"
#include "RxObjectImpl.h"

#include "SharedPtr.h"

#ifndef _TOOLKIT_IN_DLL_
#define _TOOLKIT_IN_DLL_
#include "ExampleScenariosEngine.h"
#undef _TOOLKIT_IN_DLL_
#else
#include "ExampleScenariosEngine.h"
#endif

#include "daiHeaderSection.h"
#include "daiHeader/daiHeaderEntities.h"

#include "IfcExamplesCommon.h"

#include "ExBlock.h"
#include "ExRectangularPyramid.h"
#include "ExRightCircularCone.h"
#include "ExRightCircularCylinder.h"
#include "ExSphere.h"
#include "ExIfcFixedReferenceSweptAreaSolid.h"
#include "ExIfcFixedReferenceSweptAreaSolid2.h"
#include "ExIfcFixedReferenceSweptAreaSolid3.h"
#include "ExIfcSweptDiskSolid.h"
#include "ExIfcOpenCrossProfileDef.h"

typedef OdArray<OdSharedPtr<IfcRepresentationAdapter> > IfcRepresentationAdapterArray;

void appendObjects(IfcRepresentationAdapterArray &objects, ExIfcModelFillerPtr &filler)
{
  for (IfcRepresentationAdapterArray::iterator it = objects.begin(), end = objects.end(); it != end; it++)
  {
    OdIfc::OdIfcEntityPtr pV = filler->model()->createEntityInstance("ifcbuildingelementproxy");
    OdIfc::Utils::assignGlobalId(pV);
    pV->putAttr(OdIfc::kOwnerHistory, OdDAIObjectId(filler->ownerHistory()->id()));

    OdAnsiString setName;
    setName.format("Object set %i", (int)(it - objects.begin()));
    pV->putAttr(OdIfc::kName, setName);

    OdIfc::OdIfcEntityPtr pAxis = filler->createAxis2Placement3D((*it)->getObjectPlacement());
    OdIfc::OdIfcEntityPtr pObjectPlacement = filler->createLocalPlacement(OdIfc::OdIfcEntityPtr(), pAxis);
    pV->putAttr("objectplacement", OdDAIObjectId(pObjectPlacement->id()));
    filler->appendRelContainedInSpatialStructure(filler->site(), pV);

    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pV);
    pRB->process(it->get());
  }
}

int createIfcFile(const char *fileName, OdIfcFilePtr pIfcFile, IfcRepresentationAdapterArray &objects, OdGeMatrix3d position = OdGeMatrix3d())
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
  OdIfcEntityPtr project = filler->fromScratch("Open Design Alliance", "ExIfcFileGenerator", units);
  filler->appendGeometricRepresentationContext("2D", "Plan", 2);
  filler->appendGeometricRepresentationContext("3D", "Model", 3, 1e-6);

  // Colors for surfaces (not materials in IFC sense of word)
  filler->createSurfaceStyle("Dark", OdCmEntityColor(0, 0, 64));

  // IfcSite
  filler->site()->putAttr("name", OdAnsiString("Site"));
  filler->createPropertySet(filler->site())->
    appendPropertySingleValue("Reference", OdAnsiString("Surface"), "IfcIdentifier").
    createPropertySet("Pset_SiteCommon");

  OdIfcEntityPtr pAxis = filler->createAxis2Placement3D(position);
  OdIfcEntityPtr pPlacement = filler->createLocalPlacement(OdIfcEntityPtr(), pAxis);
  filler->site()->putAttr("objectplacement", OdDAIObjectId(pPlacement->id()));

  appendObjects(objects, filler);
  
  OdDAI::OdHeaderSectionPtr header = pIfcFile->getHeaderSection();
  OdDAI::ApplicationInstancePtr pFileName = header->getEntityByType(OdDAI::kFileName);
  OdArray<OdAnsiString> authors;
  if (pFileName->getAttr("author") >> authors)
  {
    authors.push_back("ExIfcFileGenerator app");
    pFileName->putAttr("author", authors);
  }

  pIfcFile->writeFile(fileName);

  return 0;
}

void IfcCSGPrimitives(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  double scale = 1000;

  objects.push_back(new ExBlock(OdGeMatrix3d(), scale, scale, scale, false));
  objects.push_back(new ExBlock(OdGeMatrix3d(), scale, scale, scale, true));
  objects.push_back(new ExRectangularPyramid(OdGeMatrix3d(), scale, scale, scale, false));
  objects.push_back(new ExRectangularPyramid(OdGeMatrix3d(), scale, scale, scale, true));
  objects.push_back(new ExRightCircularCone(OdGeMatrix3d(), scale, scale, false));
  objects.push_back(new ExRightCircularCone(OdGeMatrix3d(), scale, scale, true));
  objects.push_back(new ExRightCircularCylinder(OdGeMatrix3d(), scale, scale, false));
  objects.push_back(new ExRightCircularCylinder(OdGeMatrix3d(), scale, scale, true));
  objects.push_back(new ExSphere(OdGeMatrix3d(), scale, false));
  objects.push_back(new ExSphere(OdGeMatrix3d(), scale, true));

  for (IfcRepresentationAdapterArray::iterator it = objects.begin(), end = objects.end(); it != end; it++)
  {
    (*it)->setObjectPlacement(OdGeMatrix3d().setToTranslation(OdGeVector3d((it - objects.begin()) * scale * 2, 0, 0)));
  }

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);
  createIfcFile(pApp->getFileName(), pApp->createDatabase(kScmIfc4), objects);
}

void IfcFixedReferenceSweptAreaSolid(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  double scale = 1000;

  objects.push_back(new ExIfcFixedReferenceSweptAreaSolid(OdGeMatrix3d(), scale * 0.25, scale));

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);
  createIfcFile(pApp->getFileName(), pApp->createDatabase(kScmIfc4), objects);
}

void IfcSweptDiskSolid(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  double scale = 1000;

  objects.push_back(new ExIfcSweptDiskSolid(OdGeMatrix3d(), scale * 0.1, scale));

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);
  createIfcFile(pApp->getFileName(), pApp->createDatabase(kScmIfc4), objects);
}

void IfcFixedReferenceSweptAreaSolid2(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  double scale = 1000;

  objects.push_back(new ExIfcFixedReferenceSweptAreaSolid2(OdGeMatrix3d(), 15., 80., 5., 3., scale));

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);
  createIfcFile(pApp->getFileName(), pApp->createDatabase(kScmIfc4), objects);
}

void IfcFixedReferenceSweptAreaSolid3(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  double scale = 1000.;

  for (int ind = 0; ind < 8; ind++)
  {
    objects.push_back(new ExIfcFixedReferenceSweptAreaSolid3(OdGeMatrix3d().setToTranslation(OdGeVector3d(ind * scale * 2, 0, 0)), scale * 0.25, scale, ind));
  }

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);
  createIfcFile(pApp->getFileName(), pApp->createDatabase(kScmIfc4), objects);
}

void IfcAlignmentWithoutCant(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  
  using namespace OdIfc;

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);

  OdIfcFilePtr pIfcFile = pApp->createDatabase(kScmIfc4x3_RC4);

  // OdIfcFile keeps model opened to avoid outside access.
  OdIfcModelPtr pModel = pIfcFile->getModel(sdaiRW);

  ExIfcModelFillerPtr filler(new ExIfcModelFiller(pModel));
  
  OdArray<OdIfcEntityPtr> units;
  units.append(filler->createSiUnit("LENGTHUNIT", "MILLI", "METRE"));
  units.append(filler->createSiUnit("PLANEANGLEUNIT", NULL, "RADIAN"));
  units.append(filler->createSiUnit("AREAUNIT", NULL, "SQUARE_METRE"));
  units.append(filler->createSiUnit("VOLUMEUNIT", NULL, "CUBIC_METRE"));
  OdIfcEntityPtr project = filler->fromScratch("Open Design Alliance", "ExIfcFileGenerator", units);
  filler->site()->putAttr("name", OdAnsiString("Railway_Site"));
  filler->appendGeometricRepresentationContext("2D", "Plan", 2);
  filler->appendGeometricRepresentationContext("3D", "Model", 3, 1e-6);

  IfcAlignmentBuilderPtr alignmentBuilder = filler->appendAlignment("Primary Alignment");

  //
  // Alignment horizontal segments
  //
  OdGeCurve2dPtrArray segments;

  //
  // Linear segment (0,0)-(0,10000)
  //
  OdGePoint2dArray ptsSegm01;
  ptsSegm01.append(OdGePoint2d(0., 0.));
  ptsSegm01.append(OdGePoint2d(0., 10000.));
  segments.append(new OdGePolyline2d(ptsSegm01));

  //
  // Linear segment (0,10000)-(10000,10000)
  //
  /*OdGePoint2dArray ptsSegm02;
  ptsSegm02.append(OdGePoint2d(0., 10000.));
  ptsSegm02.append(OdGePoint2d(10000., 10000.));
  segments.append(new OdGePolyline2d(ptsSegm02));*/

  //
  // Create horizontal alignment from segments
  //
  alignmentBuilder->appendHorizontalAlignment(segments);

  //
  // Create vertical alignment
  //
  OdIfc::OdIfcEntityPtr alignmentVertical = filler->model()->createEntityInstance("ifcalignmentvertical");
  OdIfc::Utils::assignGlobalId(alignmentVertical);
  alignmentVertical->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
  OdDAIObjectId idAlignmentVertical = filler->model()->appendEntityInstance(alignmentVertical);
  filler->appendRelNests(alignmentBuilder->alignment(), alignmentVertical);

  OdDAIObjectIds verticalSegments;
  for (int i = 0; i < 1; ++i)
  {
    //
    // IfcProduct-derived container for segment
    //
    OdIfc::OdIfcEntityPtr alignmentSegment = pModel->createEntityInstance("ifcalignmentsegment");
    OdIfc::Utils::assignGlobalId(alignmentSegment);
    alignmentSegment->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
    pModel->appendEntityInstance(alignmentSegment);

    //
    // Vertical segment
    //
    OdIfc::OdIfcEntityPtr verticalSegment = filler->model()->createEntityInstance("ifcalignmentverticalsegment");
    verticalSegment->putAttr("startdistalong", 0.);
    verticalSegment->putAttr("horizontallength", 10000.);
    verticalSegment->putAttr("startheight", 0.);
    verticalSegment->putAttr("startgradient", 0.);
    verticalSegment->putAttr("endgradient", 0.);
    verticalSegment->putAttr("predefinedtype", OdAnsiString("CONSTANTGRADIENT"));
    OdDAIObjectId idVerticalSegment = filler->model()->appendEntityInstance(verticalSegment);

    alignmentSegment->putAttr("designparameters", idVerticalSegment);
    verticalSegments.append(pModel->appendEntityInstance(alignmentSegment));
  }
  filler->addRelNests(alignmentVertical, verticalSegments);

  //
  // Rail head distance for rails profile
  //
  const double railHeadDistance = 1520.;

  //
  // Append representaion for Alignment as sweep which isnt assumed by schema
  //

  //IfcRailwayBuilderPtr railwayBuilder = filler->appendRailway("Railway");
  //OdIfcEntityPtr rail1 = railwayBuilder->appendRail("Rail_1", IfcRailwayBuilder::kRAIL);

  IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(alignmentBuilder->alignment());

  IfcProfileBuilderPtr profileBuilder = pRB->createProfileBuilder();
  OdIfc::OdIfcEntityPtr railProfile = profileBuilder->createAsymmetricIShapeProfileDef(
    IfcProfileBuilder::kAREA,
    "Rail Profile",
    filler->identity2D(),

    //
    // For R65/RP65 rail type:
    //

    // EXPLICIT
    /* bottomFlangeWidth */ 150.,
    /* overallDepth */ 180.,
    /* webThickness */ 20.,
    /* bottomFlangeThickness */ 11.2,
    /* topFlangeWidth */ 75.,

    // OPTIONAL
    /* bottomFlangeFilletRadius */ 25.,
    /* topFlangeThickness */ 35.6,
    /* topFlangeFilletRadius */ 15., 

    // Not used OPTIONAL
    /* bottomFlangeEdgeRadius */ 4.,
    /* bottomFlangeSlope */ OdDAI::Consts::OdNan,
    /* topFlangeEdgeRadius */ 3.
    /* topFlangeSlope */
  );

  OdIfc::OdIfcEntityPtr leftRailProfile = profileBuilder->createDerivedProfileDef("Left rail",
    OdDAIObjectId(railProfile->id()),
    OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(-railHeadDistance * 0.5, 0.))->id()));
  OdIfc::OdIfcEntityPtr rightRailProfile = profileBuilder->createDerivedProfileDef("Right rail",
    OdDAIObjectId(railProfile->id()),
    OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(railHeadDistance * 0.5, 0.))->id()));
  OdDAIObjectIds profiles;
  profiles.append(OdDAIObjectId(leftRailProfile->id()));
  profiles.append(OdDAIObjectId(rightRailProfile->id()));
  OdIfc::OdIfcEntityPtr compositeProfile = profileBuilder->createCompositeProfileDef(IfcProfileBuilder::kAREA, "Rails", profiles);

  OdGePoint3dArray points;
  points.append(OdGePoint3d(0., 0., 0.));
  points.append(OdGePoint3d(0., 10000., 0.));
  OdIfc::OdIfcEntityPtr polyline = pRB->createPolyline(points);

  OdIfc::OdIfcEntityPtr fixedReferenceSweptAreaSolid = pRB->createFixedReferenceSweptAreaSolid(
    compositeProfile, /* railProfile, */
    OdIfc::OdIfcEntityPtr(),
    polyline,
    0., 10000.,
    filler->dirX()
  );

  OdIfc::OdIfcEntityPtr ctxModel = filler->getGeometricRepresentationContext("Model");
  pRB->appendRepresentation(fixedReferenceSweptAreaSolid, ctxModel, "Body", "SweptSolid");

  //pRB->process(inclination scenario N);

  OdDAI::OdHeaderSectionPtr header = pIfcFile->getHeaderSection();
  OdDAI::ApplicationInstancePtr pFileName = header->getEntityByType(OdDAI::kFileName);
  OdArray<OdAnsiString> authors;
  if (pFileName->getAttr("author") >> authors)
  {
    authors.push_back("ExIfcFileGenerator app");
    pFileName->putAttr("author", authors);
  }

  pIfcFile->writeFile(pApp->getFileName());
}

#include "AlignmentGeometryBuilder.h"

void IfcAlignmentWithCant(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;

  using namespace OdIfc;

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);

  OdIfcFilePtr pIfcFile = pApp->createDatabase(kScmIfc4x3_RC4);

  // OdIfcFile keeps model opened to avoid outside access.
  OdIfcModelPtr pModel = pIfcFile->getModel(sdaiRW);

  ExIfcModelFillerPtr filler(new ExIfcModelFiller(pModel));

  OdArray<OdIfcEntityPtr> units;
  units.append(filler->createSiUnit("LENGTHUNIT", "MILLI", "METRE"));
  units.append(filler->createSiUnit("PLANEANGLEUNIT", NULL, "RADIAN"));
  units.append(filler->createSiUnit("AREAUNIT", NULL, "SQUARE_METRE"));
  units.append(filler->createSiUnit("VOLUMEUNIT", NULL, "CUBIC_METRE"));
  OdIfcEntityPtr project = filler->fromScratch("Open Design Alliance", "ExIfcFileGenerator", units);
  filler->site()->putAttr("name", OdAnsiString("Railway_Site"));
  filler->appendGeometricRepresentationContext("2D", "Plan", 2);
  filler->appendGeometricRepresentationContext("3D", "Model", 3, 1e-6);

  IfcAlignmentBuilderPtr alignmentBuilder = filler->appendAlignment("Primary Alignment");

  //
  // Alignment horizontal segments
  //
  OdGeCurve2dPtrArray segments;

  //
  // Linear segment (0,0)-(0,10000)
  //
  OdGePoint2dArray ptsSegm01;
  ptsSegm01.append(OdGePoint2d(0., 0.));
  ptsSegm01.append(OdGePoint2d(0., 10000.));
  segments.append(new OdGePolyline2d(ptsSegm01));

  //
  // Linear segment (0,10000)-(10000,10000)
  //
  /*OdGePoint2dArray ptsSegm02;
  ptsSegm02.append(OdGePoint2d(0., 10000.));
  ptsSegm02.append(OdGePoint2d(10000., 10000.));
  segments.append(new OdGePolyline2d(ptsSegm02));*/

  //
  // Create horizontal alignment from segments
  //
  alignmentBuilder->appendHorizontalAlignment(segments);

  //
  // Create vertical alignment
  //
  OdIfc::OdIfcEntityPtr alignmentVertical = filler->model()->createEntityInstance("ifcalignmentvertical");
  OdIfc::Utils::assignGlobalId(alignmentVertical);
  alignmentVertical->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
  OdDAIObjectId idAlignmentVertical = filler->model()->appendEntityInstance(alignmentVertical);
  OdIfc::OdIfcEntityPtr relNestsVertical = filler->appendRelNests(alignmentBuilder->alignment(), alignmentVertical);
  relNestsVertical->setInverseCounterParts();

  OdDAIObjectIds verticalSegments;
  for (int i = 0; i < 1; ++i)
  {
    //
    // IfcProduct-derived container for segment
    //
    OdIfc::OdIfcEntityPtr alignmentSegment = pModel->createEntityInstance("ifcalignmentsegment");
    OdIfc::Utils::assignGlobalId(alignmentSegment);
    alignmentSegment->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
    pModel->appendEntityInstance(alignmentSegment);

    //
    // Vertical segment
    //
    OdIfc::OdIfcEntityPtr verticalSegment = filler->model()->createEntityInstance("ifcalignmentverticalsegment");
    verticalSegment->putAttr("startdistalong", 0.);
    verticalSegment->putAttr("horizontallength", 10000.);
    verticalSegment->putAttr("startheight", 0.);
    verticalSegment->putAttr("startgradient", 0.);
    verticalSegment->putAttr("endgradient", 0.);
    verticalSegment->putAttr("predefinedtype", OdAnsiString("CONSTANTGRADIENT"));
    OdDAIObjectId idVerticalSegment = filler->model()->appendEntityInstance(verticalSegment);

    alignmentSegment->putAttr("designparameters", idVerticalSegment);
    verticalSegments.append(pModel->appendEntityInstance(alignmentSegment));
  }
  OdIfc::OdIfcEntityPtr verticalSegmentsRelNests = filler->addRelNests(alignmentVertical, verticalSegments);
  verticalSegmentsRelNests->setInverseCounterParts();

  //
  // Create cant alignment
  //
  const double railHeadDistance = 1520.;
  OdIfc::OdIfcEntityPtr alignmentCant = filler->model()->createEntityInstance("ifcalignmentcant");
  OdIfc::Utils::assignGlobalId(alignmentCant);
  alignmentCant->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
  alignmentCant->putAttr("railheaddistance", railHeadDistance);
  OdDAIObjectId idAlignmentCant = filler->model()->appendEntityInstance(alignmentCant);
  OdIfc::OdIfcEntityPtr relNestsCant = filler->appendRelNests(alignmentBuilder->alignment(), alignmentCant);
  relNestsCant->setInverseCounterParts();

  OdDAIObjectIds cantSegments;
  for (int i = 0; i < 1; ++i)
  {
    //
    // IfcProduct-derived container for segment
    //
    OdIfc::OdIfcEntityPtr alignmentSegment = pModel->createEntityInstance("ifcalignmentsegment");
    OdIfc::Utils::assignGlobalId(alignmentSegment);
    alignmentSegment->putAttr("ownerhistory", OdDAIObjectId(filler->ownerHistory()->id()));
    pModel->appendEntityInstance(alignmentSegment);

    //
    // Cant segment
    //
    OdIfc::OdIfcEntityPtr cantSegment = filler->model()->createEntityInstance("ifcalignmentcantsegment");
    cantSegment->putAttr("startdistalong", 0.);
    cantSegment->putAttr("horizontallength", 10000.);

    double linearCantValue = 200.;

    cantSegment->putAttr("startcantleft", -linearCantValue);
    cantSegment->putAttr("startcantright", linearCantValue);
    cantSegment->putAttr("endcantleft", linearCantValue);
    cantSegment->putAttr("endcantright", -linearCantValue);
    cantSegment->putAttr("predefinedtype", OdAnsiString("LINEARTRANSITION"));
    OdDAIObjectId idCantSegment = filler->model()->appendEntityInstance(cantSegment);

    alignmentSegment->putAttr("designparameters", idCantSegment);
    cantSegments.append(pModel->appendEntityInstance(alignmentSegment));
  }
  OdIfc::OdIfcEntityPtr cantSegmentsRelNests = filler->addRelNests(alignmentCant, cantSegments);
  cantSegmentsRelNests->setInverseCounterParts();
  

  //
  // Append representaion for Alignment as sweep which isnt assumed by schema
  //

  //IfcRailwayBuilderPtr railwayBuilder = filler->appendRailway("Railway");
  //OdIfcEntityPtr rail1 = railwayBuilder->appendRail("Rail_1", IfcRailwayBuilder::kRAIL);

  IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(alignmentBuilder->alignment());

  IfcProfileBuilderPtr profileBuilder = pRB->createProfileBuilder();
  OdIfc::OdIfcEntityPtr railProfile = profileBuilder->createAsymmetricIShapeProfileDef(
    IfcProfileBuilder::kAREA,
    "Rail Profile",
    filler->identity2D(),

    //
    // For R65/RP65 rail type:
    //

    // EXPLICIT
    /* bottomFlangeWidth */ 150.,
    /* overallDepth */ 180.,
    /* webThickness */ 20.,
    /* bottomFlangeThickness */ 11.2,
    /* topFlangeWidth */ 75.,

    // OPTIONAL
    /* bottomFlangeFilletRadius */ 25.,
    /* topFlangeThickness */ 35.6,
    /* topFlangeFilletRadius */ 15.,

    // Not used OPTIONAL
    /* bottomFlangeEdgeRadius */ 4.,
    /* bottomFlangeSlope */ OdDAI::Consts::OdNan,
    /* topFlangeEdgeRadius */ 3.
    /* topFlangeSlope */
  );

  OdIfc::OdIfcEntityPtr leftRailProfile = profileBuilder->createDerivedProfileDef("Left rail",
    OdDAIObjectId(railProfile->id()),
    OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(-railHeadDistance * 0.5, 0.))->id()));
  OdIfc::OdIfcEntityPtr rightRailProfile = profileBuilder->createDerivedProfileDef("Right rail",
    OdDAIObjectId(railProfile->id()),
    OdDAIObjectId(profileBuilder->createCartesianTransformationOperator2D(OdGePoint2d(railHeadDistance * 0.5, 0.))->id()));
  OdDAIObjectIds profiles;
  profiles.append(OdDAIObjectId(leftRailProfile->id()));
  profiles.append(OdDAIObjectId(rightRailProfile->id()));
  OdIfc::OdIfcEntityPtr compositeProfile = profileBuilder->createCompositeProfileDef(IfcProfileBuilder::kAREA, "Rails", profiles);

  OdDAI::ApplicationInstancePtr segmentedReferenceCurve;
  OdAlignmentGeometryBuilder geometryBuilder(pModel);

  OdDAI::ApplicationInstancePtr alignment = alignmentBuilder->alignment();
  
  geometryBuilder.process(alignment, segmentedReferenceCurve);

  /*
  OdGePoint3dArray points;
  points.append(OdGePoint3d(0., 0., 0.));
  points.append(OdGePoint3d(0., 10000., 0.));
  OdIfc::OdIfcEntityPtr polyline = pRB->createPolyline(points);

  OdIfc::OdIfcEntityPtr segmentedReferenceCurve = pModel->createEntityInstance("ifcsegmentedreferencecurve");

  OdDAI::List<OdDAIObjectId> *segmentsList = nullptr;
  segmentedReferenceCurve->getAttr("segments") >> segmentsList;
  ODA_ASSERT(segmentsList->isNil());
  segmentsList->createEmpty();

  //#135=IFCCURVESEGMENT(.CONTSAMEGRADIENTSAMECURVATURE.,#138,IFCNONNEGATIVELENGTHMEASURE(0.),IFCNONNEGATIVELENGTHMEASURE(218.61014513564817),#142);

  OdIfc::OdIfcEntityPtr line = pRB->createLine2d(OdGePoint2d(0., 0.), OdGeVector2d(0., 1.));
  OdDAI::AttributeDataBlock adb;
  adb.typePath.add("ifcnonnegativelengthmeasure");
  
  OdIfc::OdIfcEntityPtr curveSegment = pModel->createEntityInstance("ifccurvesegment");
  curveSegment->putAttr("transition", (const char *)"CONTSAMEGRADIENTSAMECURVATURE");
  adb.value.setValue(0.);
  curveSegment->putAttr("segmentstart", &adb);
  adb.value.setValue(10000.);
  curveSegment->putAttr("segmentlength", &adb);
  curveSegment->putAttr("parentcurve", OdDAIObjectId(line->id()));
  segmentsList->putByIndex(0, pModel->appendEntityInstance(curveSegment));
    
  segmentedReferenceCurve->putAttr("selfintersect", OdDAI::Logical::False);
  segmentedReferenceCurve->putAttr("basecurve", OdDAIObjectId(polyline->id()));
  pModel->appendEntityInstance(segmentedReferenceCurve);*/

  OdIfc::OdIfcEntityPtr fixedReferenceSweptAreaSolid = pRB->createFixedReferenceSweptAreaSolid(
    compositeProfile, /* railProfile, */
    OdIfc::OdIfcEntityPtr(),
    segmentedReferenceCurve,
    0., 10000.,
    filler->dirX()
  );

  OdIfc::OdIfcEntityPtr ctxModel = filler->getGeometricRepresentationContext("Model");
  pRB->appendRepresentation(fixedReferenceSweptAreaSolid, ctxModel, "Body", "SweptSolid");

  //pRB->process(inclination scenario N);

  OdDAI::OdHeaderSectionPtr header = pIfcFile->getHeaderSection();
  OdDAI::ApplicationInstancePtr pFileName = header->getEntityByType(OdDAI::kFileName);
  OdArray<OdAnsiString> authors;
  if (pFileName->getAttr("author") >> authors)
  {
    authors.push_back("ExIfcFileGenerator app");
    pFileName->putAttr("author", authors);
  }

  pIfcFile->writeFile(pApp->getFileName());
}

void IfcSweptDiskSolidIndexedPolycurve(OdIfcHostAppServices* app, int curRun)
{
  using namespace OdIfc;

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);

  OdIfcFilePtr pIfcFile = pApp->createDatabase(kScmIfc4);

  // OdIfcFile keeps model opened to avoid outside access.
  OdIfcModelPtr pModel = pIfcFile->getModel(sdaiRW);

  ExIfcModelFillerPtr filler(new ExIfcModelFiller(pModel));

  OdArray<OdIfcEntityPtr> units;
  units.append(filler->createSiUnit("LENGTHUNIT", "MILLI", "METRE"));
  units.append(filler->createSiUnit("PLANEANGLEUNIT", NULL, "RADIAN"));
  units.append(filler->createSiUnit("AREAUNIT", NULL, "SQUARE_METRE"));
  units.append(filler->createSiUnit("VOLUMEUNIT", NULL, "CUBIC_METRE"));
  OdIfcEntityPtr project = filler->fromScratch("Open Design Alliance", "ExIfcFileGenerator", units);
  filler->site()->putAttr("name", OdAnsiString("Railway_Site"));
  OdIfcEntityPtr ctxPlan = filler->appendGeometricRepresentationContext("2D", "Plan", 2);
  OdIfcEntityPtr ctxModel = filler->appendGeometricRepresentationContext("3D", "Model", 3, 1e-6);

  // Fill spatial structure
  OdIfcEntityPtr building = pModel->createEntityInstance("ifcbuilding");
  building->putAttr("globalid", OdIfcGUID::generate());
  building->putAttr("name", OdAnsiString("Building"));
  filler->addRelAggregates(filler->site(), building);

  OdIfcEntityPtr buildingStorey = pModel->createEntityInstance("ifcbuildingstorey");
  buildingStorey->putAttr("globalid", OdIfcGUID::generate());
  buildingStorey->putAttr("name", OdAnsiString("Floor 0"));
  filler->addRelAggregates(building, buildingStorey);

  OdArray<OdGeVector2d> vectors;
  vectors.append(OdGeVector2d(0., 0.));
  vectors.append(OdGeVector2d(0., 300.));
  vectors.append(OdGeVector2d(600., 0.));
  vectors.append(OdGeVector2d(600., 300.));
  vectors.append(OdGeVector2d(1200, 0.));
  vectors.append(OdGeVector2d(1200, 300.));
  vectors.append(OdGeVector2d(1800, 0.));
  vectors.append(OdGeVector2d(1800, 300.));

  for (unsigned int i = 0; i < vectors.size(); ++i)
  {
    OdGeVector2d &offset = vectors.at(i);

    OdAnsiString segmentName;
    segmentName.format("Pipe segment %d", i + 1);

    OdIfcEntityPtr pipeSegment = pModel->createEntityInstance("ifcpipesegment");
    pipeSegment->putAttr("globalid", OdIfcGUID::generate());
    pipeSegment->putAttr("name", segmentName);
    filler->addRelContainedInSpatialStructure(buildingStorey, pipeSegment);

    //
    // Representation (just an extrude)
    //
    IfcRepresentationBuilderPtr pRB = filler->createRepresentationBuilder(pipeSegment);

    OdArray<OdGePoint3d> points;

    double arcR = 100.;
    OdGePoint2d pointOnArc(arcR * cos(OdaPI2), arcR * sin(OdaPI2));

    IfcIndexedPolycurveBuilderPtr pIPB = pRB->createIndexedPolycurveBuilder();
    pIPB->appendLinear(OdGePoint2d(0., 0.) + offset);
    pIPB->appendLinear(OdGePoint2d(0., 50.) + offset);
    pIPB->appendLinear(OdGePoint2d(50., 50.) + offset);
    pIPB->appendLinear(OdGePoint2d(100., 50.) + offset);
    pIPB->appendLinear(OdGePoint2d(100., 100.) + offset);
    pIPB->appendLinear(OdGePoint2d(200., 200.) + offset);
    pIPB->appendLinear(OdGePoint2d(300., 200.) + offset);
    
    if (i % 2 == 0)
      pIPB->appendLinear(OdGePoint2d(400., 100.) + offset);
    else
      pIPB->appendArc(pointOnArc + OdGeVector2d(300., 100.) + offset, OdGePoint2d(400., 100.) + offset);

    pIPB->appendLinear(OdGePoint2d(400., 0.) + offset);

    if (i > 6) // Close with coincide start and end points
      pIPB->appendArc(OdGePoint2d(200., -100.) + offset, OdGePoint2d(0., 0.) + offset);

    OdIfcEntityPtr indexedPolycurve = pIPB->finish(
      /* forceWriteSegments */ (i == 2 || i == 3),
      /* close */ i > 3
    );

    OdIfcEntityPtr sweptDiskSolid = pRB->createSweptDiskSolid(indexedPolycurve, 10., 8.);

    pRB->appendRepresentation(sweptDiskSolid, ctxModel, "Body", "SweptSolid");
  }

  OdDAI::OdHeaderSectionPtr header = pIfcFile->getHeaderSection();
  OdDAI::ApplicationInstancePtr pFileName = header->getEntityByType(OdDAI::kFileName);
  OdArray<OdAnsiString> authors;
  if (pFileName->getAttr("author") >> authors)
  {
    authors.push_back("ExIfcFileGenerator app");
    pFileName->putAttr("author", authors);
  }

  pIfcFile->writeFile(pApp->getFileName());
}

void IfcOpenCrossProfileDef(OdIfcHostAppServices* app, int curRun)
{
  IfcRepresentationAdapterArray objects;
  double scale = 10.;

  objects.push_back(new ExIfcOpenCrossProfileDef(OdGeMatrix3d(), scale * 0.1, scale));

  FileGeneratorExampleScenario::FileGeneratorAppServices* pApp = dynamic_cast<FileGeneratorExampleScenario::FileGeneratorAppServices*>(app);
  createIfcFile(pApp->getFileName(), pApp->createDatabase(kScmIfc4x3_RC4), objects);
}

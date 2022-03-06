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
using System;
using System.Collections.Generic;
using OdCreationNetSwigExampleLib;
using OdPrcCreateSwigMgd.Samples;
using OdPrcCreateSwigMgd.Samples.OdAttributeSamples;
using OdPrcCreateSwigMgd.Samples.OdBobySamples;
using OdPrcCreateSwigMgd.Samples.OdBrepByVerticesSamples;
using OdPrcCreateSwigMgd.Samples.OdBrepModelSamples;
using OdPrcCreateSwigMgd.Samples.OdBrepSamples;
using OdPrcCreateSwigMgd.Samples.OdComplexSamples;
using OdPrcCreateSwigMgd.Samples.OdCrossSectionSamples;
using OdPrcCreateSwigMgd.Samples.OdMarkupSamples;
using OdPrcCreateSwigMgd.Samples.OdMeshSamples;
using OdPrcCreateSwigMgd.Samples.OdRepresentationItemSamples;
using OdPrcCreateSwigMgd.Samples.OdTessSamples;
using Teigha.Core;
using Teigha.PRC;

namespace OdPrcCreateSwigMgd
{
  public enum OdPrcCreateSwigMgd_ExampleModes
  {
    None = 0,
    BrepSphere,
    BrepBox,
    MeshBox,
    TriangleFan,
    TriangleStripe,
    TessCombination,
    SingleWireBodyCrvLine,
    SingleWireBodyCrvNURBS,
    SingleWireBodyCrvCircle,
    SingleWireBodyCrvPolyLine,
    SingleWireBodyCrvHyperbola,
    SingleWireBodyCrvParabola,
    SingleWireBodyCrvEllipse,
    SingleWireBodyCrvOnSurf,
    SingleWireBodyCrvHelixT0,
    SingleWireBodyCrvHelixT1,
    SingleWireBodyCrvIntersection,
    SingleWireBodyCrvBlend02Boundary,
    SingleWireBodyCrvComposite,
    SingleWireBodyCrvTransform,
    SingleWireBodyCrvOffset,
    SingleWireBodyCrvEquation,
    SingleWireBodyCrvPolyLine2d,
    SingleWireBodyCrvEquation2d,
    SingleWireBodyCrvNURBS2d,
    SingleWireBodyCrvComposite2d,
    SingleWireBodyCrvTransform2d,
    SingleWireBodyCrvLine2d,
    SingleWireBodyCrvCircle2d,
    SingleWireBodyCrvHyperbola2d,
    SingleWireBodyCrvParabola2d,
    SingleWireBodyCrvEllipse2d,
    AllSingleWireBodies,
    BrepModelSphere,
    BrepModelCylinder,
    BrepModelCone,
    BrepModelRuled,
    BrepModelExtrusion,
    BrepModelFromCurves,
    BrepModelRevolution,
    BrepModelCylindrical,
    BrepModelNURBS,
    BrepModelTorusT1,
    BrepModelTorusT2,
    BrepModelOffset,
    BrepModelTransform,
    BrepModelPlane,
    BrepModelBlend01,
    BrepModelBlend02,
    BrepModelBlend03,
    AllBrepModelExamples,
    PlainTextMarkup,
    DistanceDimensionMarkup,
    DimensionRadiusMarkup,
    DiameterDimensionMarkup,
    TangentDiameterDimensionMarkup,
    CylinderDiameterDimensionMarkup,
    LengthDimensionMarkup,
    AngleDimensionMarkup,
    DatumIdentifierMarkup,
    DatumTargetMarkup,
    GDTMarkup,
    RoughnessMarkup,
    TableMarkup,
    AllMarkupExamples,
    CreateComplexExample,
    MarkupViewExample,
    BrepModelConeWithLoops,
    MarkupAnnotationExample,
    RepresentationItemPolyWire,
    RepresentationItemPointSet,
    RepresentationItemPolyBrepModel,
    RepresentationItemSet,
    TessObjectTexture,
    BrepObjectMaterial,
    WireTessWithFlags,
    BoxByVerticesExample,
    PyramidByVerticesExample,
    TqsSolidByVerticesExample,
    ManyTqsSolidByVerticesExample,
    TessExample2,
    TessExample1,
    AttributeToRepresentationItem,
    AttributeToPartDefinition,
    AttributeToProductOccurrence,
    TessExample3,
    SimpleSection,
    MarkupViewWithFilteringExample,
    BackgroundExample,
    MultipleEntitiesExportExample,
    CloneConnexesFromComplexExample,
  }

  public class OdPrcCreateSwigMgd_ApplicationInterface : ExampleApplicationInterface<OdPrcCreateSwigMgd_ExampleModes>
  {
    private OdPrcHostAppServices PrcHostApp { get; }
    public OdPrcCreateSwigMgd_ApplicationInterface(OdDbBaseHostAppServices hostApp, OdPrcHostAppServices prcHostApp, string[] app_args) : base(hostApp, app_args)
    {
      this.PrcHostApp = prcHostApp;
    }

    #region ModeToExample
    private static Dictionary<OdPrcCreateSwigMgd_ExampleModes, Type> ModeToExample = new Dictionary<OdPrcCreateSwigMgd_ExampleModes, Type>()
    {
        {OdPrcCreateSwigMgd_ExampleModes.BrepSphere,typeof(OdBrepExample_BrepSphere)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepBox,typeof(OdBrepExample_BrepBox)},
        {OdPrcCreateSwigMgd_ExampleModes.MeshBox,typeof(OdMeshExample_MeshBox)},
        {OdPrcCreateSwigMgd_ExampleModes.TriangleFan,typeof(OdMeshExample_TriangleFan)},
        {OdPrcCreateSwigMgd_ExampleModes.TriangleStripe,typeof(OdMeshExample_TriangleStripe)},
        {OdPrcCreateSwigMgd_ExampleModes.TessCombination,typeof(OdMeshExample_TessCombination)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvLine,typeof(OdBodyExample_SingleWireBodyCrvLine)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvNURBS,typeof(OdBodyExample_SingleWireBodyCrvNURBS)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvCircle,typeof(OdBodyExample_SingleWireBodyCrvCircle)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvPolyLine,typeof(OdBodyExample_SingleWireBodyCrvPolyLine)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHyperbola,typeof(OdBodyExample_SingleWireBodyCrvHyperbola)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvParabola,typeof(OdBodyExample_SingleWireBodyCrvParabola)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEllipse,typeof(OdBodyExample_SingleWireBodyCrvEllipse)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvOnSurf,typeof(OdBodyExample_SingleWireBodyCrvOnSurf)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHelixT0,typeof(OdBodyExample_SingleWireBodyCrvHelixT0)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHelixT1,typeof(OdBodyExample_SingleWireBodyCrvHelixT1)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvIntersection,typeof(OdBodyExample_SingleWireBodyCrvIntersection)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvBlend02Boundary,typeof(OdBodyExample_SingleWireBodyCrvBlend02Boundary)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvComposite,typeof(OdBodyExample_SingleWireBodyCrvComposite)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvTransform,typeof(OdBodyExample_SingleWireBodyCrvTransform)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvOffset,typeof(OdBodyExample_SingleWireBodyCrvOffset)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEquation,typeof(OdBodyExample_SingleWireBodyCrvEquation)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvPolyLine2d,typeof(OdBodyExample_SingleWireBodyCrvPolyLine2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEquation2d,typeof(OdBodyExample_SingleWireBodyCrvEquation2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvNURBS2d,typeof(OdBodyExample_SingleWireBodyCrvNURBS2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvComposite2d,typeof(OdBodyExample_SingleWireBodyCrvComposite2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvTransform2d,typeof(OdBodyExample_SingleWireBodyCrvTransform2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvLine2d,typeof(OdBodyExample_SingleWireBodyCrvLine2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvCircle2d,typeof(OdBodyExample_SingleWireBodyCrvCircle2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHyperbola2d,typeof(OdBodyExample_SingleWireBodyCrvHyperbola2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvParabola2d,typeof(OdBodyExample_SingleWireBodyCrvParabola2d)},
        {OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEllipse2d,typeof(OdBodyExample_SingleWireBodyCrvEllipse2d)},
        {OdPrcCreateSwigMgd_ExampleModes.AllSingleWireBodies,typeof(OdBodyExample_AllSingleWireBodies)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelSphere,typeof(OdBrepModelExample_BrepModelSphere)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelCylinder,typeof(OdBrepModelExample_BrepModelCylinder)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelCone,typeof(OdBrepModelExample_BrepModelCone)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelRuled,typeof(OdBrepModelExample_BrepModelRuled)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelExtrusion,typeof(OdBrepModelExample_BrepModelExtrusion)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelFromCurves,typeof(OdBrepModelExample_BrepModelFromCurves)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelRevolution,typeof(OdBrepModelExample_BrepModelRevolution)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelCylindrical,typeof(OdBrepModelExample_BrepModelCylindrical)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelNURBS,typeof(OdBrepModelExample_BrepModelNURBS)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelTorusT1,typeof(OdBrepModelExample_BrepModelTorusT1)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelTorusT2,typeof(OdBrepModelExample_BrepModelTorusT2)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelOffset,typeof(OdBrepModelExample_BrepModelOffset)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelTransform,typeof(OdBrepModelExample_BrepModelTransform)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelPlane,typeof(OdBrepModelExample_BrepModelPlane)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelBlend01,typeof(OdBrepModelExample_BrepModelBlend01)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelBlend02,typeof(OdBrepModelExample_BrepModelBlend02)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelBlend03,typeof(OdBrepModelExample_BrepModelBlend03)},
        {OdPrcCreateSwigMgd_ExampleModes.AllBrepModelExamples,typeof(OdBrepModelExample_AllBrepModelExamples)},
        {OdPrcCreateSwigMgd_ExampleModes.PlainTextMarkup,typeof(OdMarkupExample_PlainTextMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.DistanceDimensionMarkup,typeof(OdMarkupExample_DistanceDimensionMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.DimensionRadiusMarkup,typeof(OdMarkupExample_DimensionRadiusMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.DiameterDimensionMarkup,typeof(OdMarkupExample_DiameterDimensionMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.TangentDiameterDimensionMarkup,typeof(OdMarkupExample_TangentDiameterDimensionMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.CylinderDiameterDimensionMarkup,typeof(OdMarkupExample_CylinderDiameterDimensionMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.LengthDimensionMarkup,typeof(OdMarkupExample_LengthDimensionMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.AngleDimensionMarkup,typeof(OdMarkupExample_AngleDimensionMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.DatumIdentifierMarkup,typeof(OdMarkupExample_DatumIdentifierMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.DatumTargetMarkup,typeof(OdMarkupExample_DatumTargetMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.GDTMarkup,typeof(OdMarkupExample_GDTMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.RoughnessMarkup,typeof(OdMarkupExample_RoughnessMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.TableMarkup,typeof(OdMarkupExample_TableMarkup)},
        {OdPrcCreateSwigMgd_ExampleModes.AllMarkupExamples,typeof(OdMarkupExample_AllMarkupExamples)},
        {OdPrcCreateSwigMgd_ExampleModes.CreateComplexExample,typeof(OdComplexExample_CreateComplexExample)},
        {OdPrcCreateSwigMgd_ExampleModes.MarkupViewExample,typeof(OdMarkupExample_MarkupViewExample)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepModelConeWithLoops,typeof(OdBrepModelExample_BrepModelConeWithLoops)},
        {OdPrcCreateSwigMgd_ExampleModes.MarkupAnnotationExample,typeof(OdMarkupExample_MarkupAnnotationExample)},
        {OdPrcCreateSwigMgd_ExampleModes.RepresentationItemPolyWire,typeof(OdRepresentationItemExample_RepresentationItemPolyWire)},
        {OdPrcCreateSwigMgd_ExampleModes.RepresentationItemPointSet,typeof(OdRepresentationItemExample_RepresentationItemPointSet)},
        {OdPrcCreateSwigMgd_ExampleModes.RepresentationItemPolyBrepModel,typeof(OdRepresentationItemExample_RepresentationItemPolyBrepModel)},
        {OdPrcCreateSwigMgd_ExampleModes.RepresentationItemSet,typeof(OdRepresentationItemExample_RepresentationItemSet)},
        {OdPrcCreateSwigMgd_ExampleModes.TessObjectTexture,typeof(OdTessExample_TessObjectTexture)},
        {OdPrcCreateSwigMgd_ExampleModes.BrepObjectMaterial,typeof(OdBrepModelExample_BrepObjectMaterial)},
        {OdPrcCreateSwigMgd_ExampleModes.WireTessWithFlags,typeof(OdRepresentationItemExample_WireTessWithFlags)},
        {OdPrcCreateSwigMgd_ExampleModes.BoxByVerticesExample,typeof(OdBrepByVerticesExample_BoxByVerticesExample)},
        {OdPrcCreateSwigMgd_ExampleModes.PyramidByVerticesExample,typeof(OdBrepByVerticesExample_PyramidByVerticesExample)},
        {OdPrcCreateSwigMgd_ExampleModes.TqsSolidByVerticesExample,typeof(OdBrepByVerticesExample_TqsSolidByVerticesExample)},
        {OdPrcCreateSwigMgd_ExampleModes.ManyTqsSolidByVerticesExample,typeof(OdBrepByVerticesExample_ManyTqsSolidByVerticesExample)},
        {OdPrcCreateSwigMgd_ExampleModes.TessExample2,typeof(OdTessExample_TessExample2)},
        {OdPrcCreateSwigMgd_ExampleModes.TessExample1,typeof(OdTessExample_TessExample1)},
        {OdPrcCreateSwigMgd_ExampleModes.AttributeToRepresentationItem,typeof(OdAttributeExample_AttributeToRepresentationItem)},
        {OdPrcCreateSwigMgd_ExampleModes.AttributeToPartDefinition,typeof(OdAttributeExample_AttributeToPartDefinition)},
        {OdPrcCreateSwigMgd_ExampleModes.AttributeToProductOccurrence,typeof(OdAttributeExample_AttributeToProductOccurrence)},
        {OdPrcCreateSwigMgd_ExampleModes.TessExample3,typeof(OdTessExample_TessExample3)},
        {OdPrcCreateSwigMgd_ExampleModes.SimpleSection,typeof(OdCrossSectionExample_SimpleSection)},
        {OdPrcCreateSwigMgd_ExampleModes.MarkupViewWithFilteringExample,typeof(OdMarkupExample_MarkupViewWithFilteringExample)},
        {OdPrcCreateSwigMgd_ExampleModes.BackgroundExample,typeof(OdCrossSectionExample_BackgroundExample)},
        {OdPrcCreateSwigMgd_ExampleModes.MultipleEntitiesExportExample,typeof(OdMultipleEntitiesExportExample)},
        {OdPrcCreateSwigMgd_ExampleModes.CloneConnexesFromComplexExample,typeof(OdComplexExample_CloneConnexesFromComplexExample)},
    };
    #endregion

    protected override Dictionary<OdPrcCreateSwigMgd_ExampleModes, Type> ModeToExampleClass => ModeToExample;

    protected override bool InitExample(Example instance)
    {
      OdPrcCreateExample _prc_example = instance as OdPrcCreateExample;
      if (_prc_example == null)
        return false;
      if (app_args.Length < 2)
        return false;
      OdPrcCreateSwigMgd_ExampleModes mode = GetModeFromExampleType(instance.GetType());
      if (mode == OdPrcCreateSwigMgd_ExampleModes.None)
        return false;

      _prc_example.out_prcFileName = app_args[1];
      _prc_example.pPrcHost = PrcHostApp;
      _prc_example.mode = mode;

      return base.InitExample(instance);
    }


  }
}

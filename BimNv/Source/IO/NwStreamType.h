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

#ifndef __NW_STREAMTYPE_H__
#define __NW_STREAMTYPE_H__

namespace NwStreamType
{
  enum Enum
  {
    Unknown = 0,
    PartitionProps,
    CurrentViewElement,
    DBCache,
    Fragments,
    Geometry,
    GeometryCompress,
    LogicalHierarchy,
    Partition,
    Serial,
    SpatialHierarchy,
    ScenePropsChunk,
    PresenterElement,
    OwLightsElement,
    BackgroundElement,
    ClashElement,
    CullingElement,
    CurrentAnimationElement,
    GuidStore,
    HeadlightElement,
    LightsElement,
    SharedNodes,
    Stats,
    Publish,
    PlanViewElement,
    SavedViewsElement,
    SelectionSetsElement,
    SpeedElement,
    ToolElement,
    SectionViewElement,
    GUISettingsElement,
    SimulateDurationElement,
    TimelinerElement,
    TaskTypeDefinitionsElement,
    AppearanceDefinitionsElement,
    DefaultStatusElement,

    CommonSchemas,
    OdyFileInfoChunk,
    XRefTable,
    PropertyOverrideElement,
    HyperlinksOverrideElement,
    ZoneElement,
    SceneSet,
    PathMap,
    ShadFragTransformElement2,
    ShadFragMaterialElement,
    NwdEvalTimeOut,
    FileDatabaseElementNWD,
    NextCommentIdElement,
    ShadOverridesElement,
    TextureSpaceElement,
    MaterialElement,
    HomeViewElement,
    GraphicsSystemElement,
    TasksElement,
    GridElement,
    DBDatabasePropertyElement,
    NwdEmbedded,
    Thumb,
    SavedAnimationsElement,
    RenderSettingElement
  };
}

static NwStreamType::Enum getStreamTypeByName(const OdString& aName)
{
  // stream name can contain source file name
  // like "gatehouse_pub.nwd\\LcOpNwdPartition"
  // we need at least one file with different stream names of file like
  // "gatehouse_pub.nwd\\LcOpNwdPartition"
  // "somethingelse.nwd\\LcOpNwdPartition"
  // to make the suitable investigation
  const OdInt32 nSeparatorPos = aName.find(L"\\");
  OdString name = (-1 == nSeparatorPos)
    ? aName
    : aName.mid(nSeparatorPos + 1);
  using namespace NwStreamType;
  NwStreamType::Enum nType = NwStreamType::Unknown;
  if (!name.iCompare(L"LcOaPartitionProps"))
    nType = PartitionProps;
  else if (!name.iCompare(L"LcOpCurrentViewElement"))
    nType = CurrentViewElement;
  else if (!name.iCompare(L"LcOpDBCache"))
    nType = DBCache;
  else if (!name.iCompare(L"LcOpNwdFragments"))
    nType = Fragments;
  else if (!name.iCompare(L"LcOpNwdGeometry"))
    nType = Geometry;
  else if (!name.iCompare(L"LcOpNwdGeometryCompress"))
    nType = GeometryCompress;
  else if (!name.iCompare(L"LcOpNwdLogicalHierarchy"))
    nType = LogicalHierarchy;
  else if (!name.iCompare(L"LcOpNwdPartition"))
    nType = Partition;
  else if (!name.iCompare(L"LcOpNwdSerial"))
    nType = Serial;
  else if (!name.iCompare(L"LcOpNwdSpatialHierarchy"))
    nType = SpatialHierarchy;
  else if (!name.iCompare(L"LcOpOdyScenePropsChunk"))
    nType = ScenePropsChunk;
  else if (!name.iCompare(L"LcOwPresenterElement"))
    nType = PresenterElement;
  else if (!name.iCompare(L"LcOwLightsElement"))
    nType = OwLightsElement;
  else if (!name.iCompare(L"LcOpBackgroundElement"))
    nType = BackgroundElement;
  else if (!name.iCompare(L"LcOpClashElement"))
    nType = ClashElement;
  else if (!name.iCompare(L"LcOpCullingElement"))
    nType = CullingElement;
  else if (!name.iCompare(L"LcOpCurrentAnimationElement"))
    nType = CurrentAnimationElement;
  else if (!name.iCompare(L"LcOpGuidStore"))
    nType = GuidStore;
  else if (!name.iCompare(L"LcOpHeadlightElement"))
    nType = HeadlightElement;
  else if (!name.iCompare(L"LcOpLightsElement"))
    nType = LightsElement;
  else if (!name.iCompare(L"LcOpNwdSharedNodes"))
    nType = SharedNodes;
  else if (!name.iCompare(L"LcOpNwdStats"))
    nType = Stats;
  else if (!name.iCompare(L"LcOpNwdPublish"))
    nType = Publish;
  else if (!name.iCompare(L"LcOpPlanViewElement"))
    nType = PlanViewElement;
  else if (!name.iCompare(L"LcOpSavedViewsElement"))
    nType = SavedViewsElement;
  else if (!name.iCompare(L"LcOpSelectionSetsElement"))
    nType = SelectionSetsElement;
  else if (!name.iCompare(L"LcOpSpeedElement"))
    nType = SpeedElement;
  else if (!name.iCompare(L"LcOpToolElement"))
    nType = ToolElement;
  else if (!name.iCompare(L"LcOpSectionViewElement"))
    nType = SectionViewElement;
  else if (!name.iCompare(L"LcTlGUISettingsElement"))
    nType = GUISettingsElement;
  else if (!name.iCompare(L"LcTlSimulateDurationElement"))
    nType = SimulateDurationElement;
  else if (!name.iCompare(L"LcTlTimelinerElement"))
    nType = TimelinerElement;
  else if (!name.iCompare(L"LcTlTaskTypeDefinitionsElement"))
    nType = TaskTypeDefinitionsElement;
  else if (!name.iCompare(L"LcTlAppearanceDefinitionsElement"))
    nType = AppearanceDefinitionsElement;
  else if (!name.iCompare(L"LcTlDefaultStatusElement"))
    nType = DefaultStatusElement;
  else if (!name.iCompare(L"LcOpCommonSchemas"))
    nType = CommonSchemas;
  else if (!name.iCompare(L"LcOpOdyFileInfoChunk"))
    nType = OdyFileInfoChunk;
  else if (!name.iCompare(L"LcOpXRefTable"))
    nType = XRefTable;
  else if (!name.iCompare(L"LcOpPropertyOverrideElement"))
    nType = PropertyOverrideElement;
  else if (!name.iCompare(L"LcOpHyperlinksOverrideElement"))
    nType = HyperlinksOverrideElement;
  else if (!name.iCompare(L"LcOpZoneElement"))
    nType = ZoneElement;
  else if (!name.iCompare(OD_T("LcOpNwfSceneSet")))
    nType = SceneSet;
  else if (!name.iCompare(OD_T("LcOpNwfPathMap")))
    nType = PathMap;
  else if (!name.iCompare(OD_T("LcOpShadFragTransformElement2")))
    nType = ShadFragTransformElement2;
  else if (!name.iCompare(OD_T("LcOpShadFragMaterialElement")))
    nType = ShadFragMaterialElement;
  else if (!name.iCompare(OD_T("LcOpNwdEvalTimeOut")))
    nType = NwdEvalTimeOut;
  else if (!name.iCompare(OD_T("LcOpFileDatabaseElementNWD")))
    nType = FileDatabaseElementNWD;
  else if (!name.iCompare(OD_T("LcOpNextCommentIdElement")))
    nType = NextCommentIdElement;
  else if (!name.iCompare(OD_T("LcOpShadOverridesElement")))
    nType = ShadOverridesElement;
  else if (!name.iCompare(OD_T("LcOpTextureSpaceElement")))
    nType = TextureSpaceElement;
  else if (!name.iCompare(OD_T("LcReMaterialElement")))
    nType = MaterialElement;
  else if (!name.iCompare(OD_T("LcOpHomeViewElement")))
    nType = HomeViewElement;
  else if (!name.iCompare(OD_T("LcOpGraphicsSystemElement")))
    nType = GraphicsSystemElement;
  else if (!name.iCompare(OD_T("LcTlTasksElement")))
    nType = TasksElement;
  else if (!name.iCompare(OD_T("LcOpGridElement")))
    nType = GridElement;
  else if (!name.iCompare(OD_T("LcOdpDBDatabasePropertyElement")))
    nType = DBDatabasePropertyElement;
  else if (!name.iCompare(OD_T("LcAnSavedAnimationsElement")))
    nType = SavedAnimationsElement;
  else if (!name.iCompare(OD_T("LcOpRenderSettingElement")))
    nType = RenderSettingElement;
  else if (!name.find(OD_T("nwd:")))
    nType = NwdEmbedded;
  else if (!name.find(OD_T("LcOpThumb:")))
    nType = Thumb;
  else {
    // unknown stream type
    ODA_ASSERT(false);
  }
  return nType;
}

#endif //__NW_STREAMTYPE_H__

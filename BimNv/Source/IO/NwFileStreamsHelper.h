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

#ifndef __NWFILESTREAMSHELPER_H__
#define __NWFILESTREAMSHELPER_H__

#include "NwStreamType.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"

namespace NwFileType
{
  enum Enum
  {
    isNwd = 0,
    isNwc = 1,
    isNwf = 2
  };
}

using OdNwSaveStreamType = std::pair<NwStreamType::Enum, bool>;
using OdNwSaveStreamTypeCollection = std::vector<OdNwSaveStreamType>;

static OdString getStreamNameByType(NwStreamType::Enum streamType, const OdString& sheetId = OD_T(""))
{
  OdString sTemp;
  switch(streamType)
  {
    case NwStreamType::PartitionProps:
      sTemp = L"LcOaPartitionProps";
      break;
    case NwStreamType::CurrentViewElement:
      sTemp = L"LcOpCurrentViewElement";
      break;
    case NwStreamType::DBCache:
      sTemp = L"LcOpDBCache";
      break;
    case NwStreamType::Fragments:
      sTemp = L"LcOpNwdFragments";
      break;
    case NwStreamType::Geometry:
      sTemp = L"LcOpNwdGeometry";
      break;
    case NwStreamType::GeometryCompress:
      sTemp = L"LcOpNwdGeometryCompress";
      break;
    case NwStreamType::LogicalHierarchy:
      sTemp = L"LcOpNwdLogicalHierarchy";
      break;
    case NwStreamType::Partition:
      sTemp = L"LcOpNwdPartition";
      break;
    case NwStreamType::Serial:
      sTemp = L"LcOpNwdSerial";
      break;
    case NwStreamType::SpatialHierarchy:
      sTemp = L"LcOpNwdSpatialHierarchy";
      break;
    case NwStreamType::ScenePropsChunk:
      sTemp = L"LcOpOdyScenePropsChunk";
      break;
    case NwStreamType::BackgroundElement:
      sTemp = L"LcOpBackgroundElement";
      break;
    case NwStreamType::ClashElement:
      sTemp = L"LcOpClashElement";
      break;
    case NwStreamType::CullingElement:
      sTemp = L"LcOpCullingElement";
      break;
    case NwStreamType::CurrentAnimationElement:
      sTemp = L"LcOpCurrentAnimationElement";
      break;
    case NwStreamType::GuidStore:
      sTemp = L"LcOpGuidStore";
      break;
    case NwStreamType::HeadlightElement:
      sTemp = L"LcOpHeadlightElement";
      break;
    case NwStreamType::LightsElement:
      sTemp = L"LcOpLightsElement";
      break;
    case NwStreamType::SharedNodes:
      sTemp = L"LcOpNwdSharedNodes";
      break;
    case NwStreamType::Stats:
      sTemp = L"LcOpNwdStats";
      break;
    case NwStreamType::Publish:
      sTemp = L"LcOpNwdPublish";
      break;
    case NwStreamType::PlanViewElement:
      sTemp = L"LcOpPlanViewElement";
      break;
    case NwStreamType::SavedViewsElement:
      sTemp = L"LcOpSavedViewsElement";
      break;
    case NwStreamType::SelectionSetsElement:
      sTemp = L"LcOpSelectionSetsElement";
      break;
    case NwStreamType::SpeedElement:
      sTemp = L"LcOpSpeedElement";
      break;
    case NwStreamType::ToolElement:
      sTemp = L"LcOpToolElement";
      break;
    case NwStreamType::SectionViewElement:
      sTemp = L"LcOpSectionViewElement";
      break;
    case NwStreamType::GUISettingsElement:
      sTemp = L"LcTlGUISettingsElement";
      break;
    case NwStreamType::SimulateDurationElement:
      sTemp = L"LcTlSimulateDurationElement";
      break;
    case NwStreamType::TimelinerElement:
      sTemp = L"LcTlTimelinerElement";
      break;
    case NwStreamType::TaskTypeDefinitionsElement:
      sTemp = L"LcTlTaskTypeDefinitionsElement";
      break;
    case NwStreamType::AppearanceDefinitionsElement:
      sTemp = L"LcTlAppearanceDefinitionsElement";
      break;
    case NwStreamType::DefaultStatusElement:
      sTemp = L"LcTlDefaultStatusElement";
      break;
    case NwStreamType::CommonSchemas:
      sTemp = L"LcOpCommonSchemas";
      break;
    case NwStreamType::OdyFileInfoChunk:
      sTemp = L"LcOpOdyFileInfoChunk";
      break;
    case NwStreamType::XRefTable:
      sTemp = L"LcOpXRefTable";
      break;
    case NwStreamType::PropertyOverrideElement:
      sTemp = L"LcOpPropertyOverrideElement";
      break;
    case NwStreamType::HyperlinksOverrideElement:
      sTemp = L"LcOpHyperlinksOverrideElement";
      break;
    case NwStreamType::ZoneElement:
      sTemp = L"LcOpZoneElement";
      break;
    case NwStreamType::SceneSet:
      sTemp = L"LcOpNwfSceneSet";
      break;
    case NwStreamType::PathMap:
      sTemp = L"LcOpNwfPathMap";
      break;
    case NwStreamType::ShadFragTransformElement2:
      sTemp = L"LcOpShadFragTransformElement2";
      break;
    case NwStreamType::ShadFragMaterialElement:
      sTemp = L"LcOpShadFragMaterialElement";
      break;
    case NwStreamType::NwdEvalTimeOut:
      sTemp = L"LcOpNwdEvalTimeOut";
      break;
    case NwStreamType::FileDatabaseElementNWD:
      sTemp = L"LcOpFileDatabaseElementNWD";
      break;
    case NwStreamType::NextCommentIdElement:
      sTemp = L"LcOpNextCommentIdElement";
      break;
    case NwStreamType::ShadOverridesElement:
      sTemp = L"LcOpShadOverridesElement";
      break;
    case NwStreamType::TextureSpaceElement:
      sTemp = L"LcOpTextureSpaceElement";
      break;
    case NwStreamType::MaterialElement:
      sTemp = L"LcReMaterialElement";
      break;
    case NwStreamType::HomeViewElement:
      sTemp = L"LcOpHomeViewElement";
      break;
    case NwStreamType::GraphicsSystemElement:
      sTemp = L"LcOpGraphicsSystemElement";
      break;
    case NwStreamType::TasksElement:
      sTemp = L"LcTlTasksElement";
      break;
    case NwStreamType::GridElement:
      sTemp = L"LcOpGridElement";
      break;
    case NwStreamType::DBDatabasePropertyElement:
      sTemp = L"LcOdpDBDatabasePropertyElement";
      break;
    case NwStreamType::SavedAnimationsElement:
      sTemp = L"LcAnSavedAnimationsElement";
      break;
  }
  if (sheetId.isEmpty())
    return sTemp;
  else
    return sheetId + OD_T("\\") + sTemp;
}

template <NwFileType::Enum T> struct OdNwFileStreamsHelper;

template <>
struct OdNwFileStreamsHelper<NwFileType::isNwd>
{
  static OdNwSaveStreamTypeCollection getSheetStreams()
  {
    return { { NwStreamType::NwdEvalTimeOut, false },
             { NwStreamType::GeometryCompress, false },
             { NwStreamType::Geometry, true },
             { NwStreamType::SharedNodes, false },
             { NwStreamType::Partition, true },
             { NwStreamType::PartitionProps, true },
             { NwStreamType::LogicalHierarchy, true },
             { NwStreamType::Fragments, true },
             { NwStreamType::SpatialHierarchy, true },
             { NwStreamType::GuidStore, false},
             { NwStreamType::Stats, false},
             { NwStreamType::Serial, false},
             { NwStreamType::ScenePropsChunk, false},
             { NwStreamType::CurrentViewElement, false},
             { NwStreamType::PlanViewElement, false},
             { NwStreamType::SectionViewElement, false},
             { NwStreamType::CurrentAnimationElement, false},
             { NwStreamType::HeadlightElement, false},
             { NwStreamType::SpeedElement, false},
             { NwStreamType::CullingElement, false},
             { NwStreamType::BackgroundElement, false},
             { NwStreamType::SelectionSetsElement, false},
             { NwStreamType::SavedViewsElement, false},
             { NwStreamType::NextCommentIdElement, false},
             { NwStreamType::ClashElement, false},
             { NwStreamType::ShadOverridesElement, false},
             { NwStreamType::HyperlinksOverrideElement, false},
             { NwStreamType::PropertyOverrideElement, false},
             { NwStreamType::GridElement, false},
             { NwStreamType::LightsElement, false},
             { NwStreamType::TextureSpaceElement, false},
             { NwStreamType::ZoneElement, false},
             { NwStreamType::ToolElement, false},
             { NwStreamType::HomeViewElement, false},//place of this stream in list is inaccurate
             { NwStreamType::GraphicsSystemElement, false},//place of this stream in list is inaccurate
             { NwStreamType::MaterialElement, false},
             { NwStreamType::DBDatabasePropertyElement, false},
             { NwStreamType::SimulateDurationElement, false},
             { NwStreamType::TimelinerElement, false},
             { NwStreamType::GUISettingsElement, false},
             { NwStreamType::TaskTypeDefinitionsElement, false},//place of this stream in list is inaccurate
             { NwStreamType::AppearanceDefinitionsElement, false},//place of this stream in list is inaccurate
             { NwStreamType::DefaultStatusElement, false},//place of this stream in list is inaccurate
             { NwStreamType::TasksElement, false},//place of this stream in list is inaccurate
             { NwStreamType::Publish, false},
             { NwStreamType::SavedAnimationsElement, false}//place of this stream in list is inaccurate
           };
  }

  static OdNwSaveStreamTypeCollection getCommonStreams()
  {
    return {
             { NwStreamType::OdyFileInfoChunk, true },
             { NwStreamType::CommonSchemas, false },
             { NwStreamType::XRefTable, false }
           };
  }
};
template <>
struct OdNwFileStreamsHelper<NwFileType::isNwc>
{
  static OdNwSaveStreamTypeCollection getSheetStreams()
  {
    return { { NwStreamType::DBCache, true},
             { NwStreamType::GeometryCompress, false },
             { NwStreamType::Geometry, true },
             { NwStreamType::SharedNodes, false },
             { NwStreamType::Partition, true },
             { NwStreamType::PartitionProps, true },
             { NwStreamType::LogicalHierarchy, true },
             { NwStreamType::Fragments, true },
             { NwStreamType::SpatialHierarchy, true },
             { NwStreamType::GuidStore, false},
             { NwStreamType::Stats, false},
             { NwStreamType::Serial, false},
             { NwStreamType::ScenePropsChunk, false},
             { NwStreamType::CurrentViewElement, false},
             { NwStreamType::BackgroundElement, false},
             { NwStreamType::SavedViewsElement, false},
             { NwStreamType::GridElement, false}
           };
  }

  static OdNwSaveStreamTypeCollection getCommonStreams()
  {
    return { 
             { NwStreamType::OdyFileInfoChunk, true },
             { NwStreamType::CommonSchemas, false },
             { NwStreamType::XRefTable, false }
           };
  }
};
template <>
struct OdNwFileStreamsHelper<NwFileType::isNwf>
{
  static OdNwSaveStreamTypeCollection getSheetStreams()
  {
    return { { NwStreamType::SceneSet, true},
             { NwStreamType::PathMap, false},
             { NwStreamType::ScenePropsChunk, false},
             { NwStreamType::CurrentViewElement, false},
             { NwStreamType::PlanViewElement, false},
             { NwStreamType::SectionViewElement, false},
             { NwStreamType::CurrentAnimationElement, false},
             { NwStreamType::HeadlightElement, false},
             { NwStreamType::SpeedElement, false},
             { NwStreamType::CullingElement, false},
             { NwStreamType::BackgroundElement, false},
             { NwStreamType::SelectionSetsElement, false},
             { NwStreamType::SavedViewsElement, false},
             { NwStreamType::NextCommentIdElement, false},
             { NwStreamType::ClashElement, false},
             { NwStreamType::ShadFragTransformElement2, false},
             { NwStreamType::ShadFragMaterialElement, false},
             { NwStreamType::ShadOverridesElement, false},
             { NwStreamType::HyperlinksOverrideElement, false},
             { NwStreamType::PropertyOverrideElement, false},
             { NwStreamType::GridElement, false},
             { NwStreamType::LightsElement, false},
             { NwStreamType::TextureSpaceElement, false},
             { NwStreamType::ZoneElement, false},
             { NwStreamType::ToolElement, false},
             { NwStreamType::HomeViewElement, false}//place of this stream in list is inaccurate
           };
  }

  static OdNwSaveStreamTypeCollection getCommonStreams()
  {
    return { 
             { NwStreamType::OdyFileInfoChunk, true },
             { NwStreamType::CommonSchemas, false },
             { NwStreamType::XRefTable, false }
           };
  }
};


#endif // __NWFILESTREAMSHELPER_H__

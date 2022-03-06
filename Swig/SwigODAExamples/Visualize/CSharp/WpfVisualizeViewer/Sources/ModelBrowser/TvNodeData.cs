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

using System.Collections.Generic;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser
{
    public enum TvBrowserItemType
    {
        None = 0,
        Database = 1,
        Devices = 2,
        DevicesFold = 3,
        Views = 4,
        Materials = 5,
        MaterialsFold = 6,
        Linetypes = 7,
        LinetypesFold = 8,
        TextStyles = 9,
        TextStylesFold = 10,
        Models = 11,
        ModelsFold = 12,
        RasterImages = 13,
        RasterImagesFold = 14,
        Blocks = 15,
        BlocksFold = 16,
        Layers = 17,
        LayersFold = 18,
        Entity = 19,
        Light = 20,
        Insert = 21,
        Geometry = 22
    }

    public class TvNodeData
    {
        public TvBrowserItemType Type { get; private set; }

        public OdTvDatabaseId DbId { get; private set; }
        public OdTvGsDeviceId DeviceId { get; private set; }
        public OdTvGsViewId ViewId { get; private set; }
        public OdTvModelId ModelId { get; private set; }
        public OdTvLinetypeId LinetypeId { get; private set; }
        public OdTvTextStyleId TextStyleId { get; private set; }
        public OdTvRasterImageId RasterImgId { get; private set; }
        public OdTvBlockId BlockId { get; private set; }
        public OdTvLayerId LayerId { get; private set; }
        public OdTvMaterialId MaterialId { get; private set; }

        public OdTvEntityId EntityId { get; private set; }
        public OdTvGeometryDataId GeomId { get; private set; }
        public OdTvGeometryDataId SubEntId { get; private set; }

        public bool IsLoaded { get; set; }
        public int CountOfChild { get; set; }

        public Dictionary<ulong, TvTreeItem> ModelsDictionary = new Dictionary<ulong, TvTreeItem>();
        public Dictionary<ulong, TvTreeItem> EntitiesDictionary = new Dictionary<ulong, TvTreeItem>();

        public TvNodeData(TvBrowserItemType type, object id, OdTvGsDeviceId devId = null)
        {
            IsLoaded = false;
            CountOfChild = 0;
            if (devId != null)
                DeviceId = devId;

            Type = type;
            switch (type)
            {
                case TvBrowserItemType.Database:
                    DbId = id as OdTvDatabaseId;
                    break;
                case TvBrowserItemType.Devices:
                    DeviceId = id as OdTvGsDeviceId;
                    break;
                case TvBrowserItemType.Views:
                    ViewId = id as OdTvGsViewId;
                    break;
                case TvBrowserItemType.Materials:
                    MaterialId = id as OdTvMaterialId;
                    break;
                case TvBrowserItemType.Linetypes:
                    LinetypeId = id as OdTvLinetypeId;
                    break;
                case TvBrowserItemType.TextStyles:
                    TextStyleId = id as OdTvTextStyleId;
                    break;
                case TvBrowserItemType.Models:
                    ModelId = id as OdTvModelId;
                    break;
                case TvBrowserItemType.RasterImages:
                    RasterImgId = id as OdTvRasterImageId;
                    break;
                case TvBrowserItemType.Blocks:
                    BlockId = id as OdTvBlockId;
                    break;
                case TvBrowserItemType.Layers:
                    LayerId = id as OdTvLayerId;
                    break;
                case TvBrowserItemType.Entity:
                case TvBrowserItemType.Light:
                case TvBrowserItemType.Insert:
                    EntityId = id as OdTvEntityId;
                    break;
                case TvBrowserItemType.Geometry:
                    GeomId = id as OdTvGeometryDataId;
                    if (GeomId != null && GeomId.getType() == OdTvGeometryDataType.kSubEntity)
                    {
                        SubEntId = GeomId;
                        GeomId = null;
                    }
                    break;
            }
        }
    }

}

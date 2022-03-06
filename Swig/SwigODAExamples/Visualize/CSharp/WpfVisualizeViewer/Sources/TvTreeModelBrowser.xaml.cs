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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Media.Imaging;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.ModelBrowser;
using MessageBox = System.Windows.Forms.MessageBox;
using Orientation = System.Windows.Controls.Orientation;
using UserControl = System.Windows.Controls.UserControl;
using Button = System.Windows.Controls.Button;

namespace WpfVisualizeViewer
{
    /// <summary>
    /// Interaction logic for TvTreeModelBrowser.xaml
    /// </summary>
    public partial class TvTreeModelBrowser : UserControl
    {
        private MemoryManager MM = MemoryManager.GetMemoryManager();
        private OdTvDatabaseId _tvDbId = null;

        private ResourceDictionary Resource = App.Current.Resources;

        private OdTvWpfView _wpfView;

        private int _countOfDisplayedObjects = 200;

        private static int _entityNum = 0;
        private static int _lightNum = 0;
        private static int _insertNum = 0;

        private TvTreeItem _dbItem = null;
        private TvTreeItem _modelsFoldItm = null;

        public delegate void ResetHandler(TvTreeItem dbNode);
        public event ResetHandler ResetEvent;

        public TvTreeModelBrowser()
        {
            InitializeComponent();
        }

        public void ResetBrowser()
        {
            _wpfView.ClearSelectedNodes();
            _dbItem.IsSelected = true;
            if(ResetEvent != null)
                ResetEvent(_dbItem);
        }

        public void SelectObject(OdTvSelectionSet sSet, OdTvModelId modelId)
        {
            if (sSet == null || modelId.isNull())
                return;

            ResetBrowser();

            MemoryTransaction mtr = MM.StartTransaction();

            // expand models folder
            _modelsFoldItm.IsExpanded = true;
            // get node data from models folder
            TvNodeData modelsFoldData = _modelsFoldItm.NodeData;
            if (modelsFoldData == null)
                return;
            // get model node
            ulong modelHandle = modelId.openObject().getDatabaseHandle();
            if (!modelsFoldData.ModelsDictionary.ContainsKey(modelHandle))
                return;
            TvTreeItem modelNode = modelsFoldData.ModelsDictionary[modelHandle];
            // expand model node
            modelNode.IsExpanded = true;
            // get model data
            TvNodeData modelData = modelNode.NodeData;
            if (modelData == null)
                return;

            // get selection options
            OdTvSelectionOptions selectionOpt = sSet.getOptions();
            // get selection set iterator
            OdTvSelectionSetIterator iter = sSet.getIterator();
            if (iter == null)
                return;

            TvTreeItem entityItem = null;

            for (; !iter.done(); iter.step())
            {
                if(selectionOpt.getLevel() == OdTvSelectionOptions.Level.kEntity)
                {
                    OdTvEntityId enId = iter.getEntity();
                    if (enId.isNull())
                        continue;

                    // check entity existing
                    ulong entityHandle = 0;
                    if (enId.getType() == OdTvEntityId.EntityTypes.kEntity)
                        entityHandle = enId.openObject().getDatabaseHandle();
                    else
                        entityHandle = enId.openObjectAsInsert().getDatabaseHandle();

                    if (!modelData.EntitiesDictionary.ContainsKey(entityHandle))
                        continue;
                    entityItem = modelData.EntitiesDictionary[entityHandle];
                }
            }

            MM.StopTransaction(mtr);

            if(entityItem != null)
                entityItem.IsSelected = true;
        }

        public void Initialize(OdTvDatabaseId id, OdTvWpfView wpfview)
        {
            if (id == null || !id.isValid())
                return;
            _wpfView = wpfview;
            ModelBrowser.Items.Clear();
            _tvDbId = id;
            _dbItem = new TvTreeItem("Database", Resource["MbDbImg"] as BitmapImage, null, new TvNodeData(TvBrowserItemType.Database, id), _wpfView.VM);
            _dbItem.SetBold();
            ModelBrowser.Items.Add(_dbItem);

            AddDevices(_dbItem);
            AddModels(_dbItem);
            AddBlocks(_dbItem);
            AddLinetypes(_dbItem);
            AddTextStyles(_dbItem);
            AddLayers(_dbItem);
            AddMaterials(_dbItem);
            AddRasterImages(_dbItem);

            _dbItem.IsExpanded = true;
            _dbItem.IsSelected = true;
        }

        private void ButtonRefresh_OnClick(object sender, RoutedEventArgs e)
        {
            Initialize(_tvDbId, _wpfView);
        }

        private void AddDevices(TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvDevicesIterator it = _tvDbId.openObject().getDevicesIterator();
            TvTreeItem itm = null;
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.DevicesFold, null);
                itm = new TvTreeItem("Devices", Resource["MbDeviceImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.SetBold();

                int cnt = 0;
                while (!it.done())
                {
                    TvNodeData nDatadev = new TvNodeData(TvBrowserItemType.Devices, it.getDevice());
                    nData.CountOfChild = it.getDevice().openObject().numViews();
                    TvTreeItem deviceNode = new TvTreeItem("Device<" + it.getDevice().openObject().getName() + ">", Resource["MbDeviceImg"] as BitmapImage, itm, nDatadev, _wpfView.VM);
                    AddViews(it.getDevice().openObject(), deviceNode);
                    cnt++;
                    it.step();
                }

                nData.CountOfChild = cnt;
            }

            MM.StopTransaction(mtr);
        }

        private void AddViews(OdTvGsDevice device, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            int numViews = device.numViews();
            for (int i = 0; i < numViews; i++)
            {
                new TvTreeItem("View<" + device.viewAt(i).openObject().getName() + ">",
                    Resource["MbViewImg"] as BitmapImage, parent, new TvNodeData(TvBrowserItemType.Views, device.viewAt(i)), _wpfView.VM);
            }

            MM.StopTransaction(mtr);
        }

        private void AddModels(TvTreeItem parent)
        {
            _modelsFoldItm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvModelsIterator it = _tvDbId.openObject().getModelsIterator();
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.ModelsFold, null);
                int cnt = 0;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                _modelsFoldItm = new TvTreeItem("Models", Resource["MbModelFoldImg"] as BitmapImage, parent, nData, _wpfView.VM);
                _modelsFoldItm.Expanded += TvTreeItem_Expanded;
                _modelsFoldItm.SetBold();
                _modelsFoldItm.Items.Add(null);
            }

            MM.StopTransaction(mtr);
        }

        private void AddEntities(object id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEntitiesIterator it = null;
            if (parent.NodeData.Type == TvBrowserItemType.Blocks)
            {
                OdTvBlockId blockId = id as OdTvBlockId;
                if (blockId != null && !blockId.isNull())
                    it = blockId.openObject().getEntitiesIterator();
            }
            else if (parent.NodeData.Type == TvBrowserItemType.Models)
            {
                OdTvModelId modelId = id as OdTvModelId;
                if (modelId != null && !modelId.isNull())
                    it = modelId.openObject().getEntitiesIterator();
            }
            else
                return;

            int pos = 1;
            while (!it.done())
            {
                AddEntity(it.getEntity(), parent);
                if (pos % _countOfDisplayedObjects == 0)
                {
                    AddExpandButton(parent, pos);
                    break;
                }
                pos++;
                it.step();
            }

            MM.StopTransaction(mtr);
        }

        private void AddEntity(OdTvEntityId enId, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (enId.getType() == OdTvEntityId.EntityTypes.kEntity)
            {
                OdTvEntity en = enId.openObject();
                string name = en.getName();
                TvTreeItem child = new TvTreeItem("Entity<" + (name.Length > 0 ? name : _entityNum++.ToString()) + ">",
                    Resource["MbEntityImg"] as BitmapImage, parent, new TvNodeData(TvBrowserItemType.Entity, enId, _wpfView.TvDeviceId), _wpfView.VM);
                ulong hndl = enId.openObject().getDatabaseHandle();
                if(!parent.NodeData.EntitiesDictionary.ContainsKey(hndl))
                    parent.NodeData.EntitiesDictionary.Add(hndl, child);
                if (!en.getGeometryDataIterator().done())
                {
                    child.Expanded += TvTreeItem_Expanded;
                    child.Items.Add(null);
                }
            }
            else if (enId.getType() == OdTvEntityId.EntityTypes.kLight)
            {
                string name = enId.openObjectAsLight().getName();
                new TvTreeItem("Light<" + (name.Length > 0 ? name : _lightNum++.ToString()) + ">",
                    Resource["MbLightImg"] as BitmapImage, parent, new TvNodeData(TvBrowserItemType.Light, enId), _wpfView.VM);
            }
            else
            {
                string name = enId.openObjectAsInsert().getName();
                TvTreeItem child = new TvTreeItem("Insert<" + (name.Length > 0 ? name : _insertNum++.ToString()) + ">",
                    Resource["MbEntityImg"] as BitmapImage, parent, new TvNodeData(TvBrowserItemType.Insert, enId), _wpfView.VM);
                ulong hndl = enId.openObjectAsInsert().getDatabaseHandle();
                if (!parent.NodeData.EntitiesDictionary.ContainsKey(hndl))
                    parent.NodeData.EntitiesDictionary.Add(hndl, child);
            }
            MM.StopTransaction(mtr);
        }

        private void AddGeometries(OdTvGeometryDataIterator it, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            int index = 1;
            while (!it.done())
            {
                AddGeometry(it.getGeometryData(), parent);
                if (index % _countOfDisplayedObjects == 0)
                {
                    AddExpandButton(parent, index);
                    break;
                }
                index++;
                it.step();
            }
            MM.StopTransaction(mtr);
        }

        private void AddGeometry(OdTvGeometryDataId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            if (id.getType() == OdTvGeometryDataType.kSubEntity)
            {
                OdTvEntity en = id.openAsSubEntity();
                TvTreeItem child = new TvTreeItem("SubEntity<" + en.getName() + ">",
                    Resource["MbGeomImg"] as BitmapImage, parent, new TvNodeData(TvBrowserItemType.Geometry, id, _wpfView.TvDeviceId), _wpfView.VM);
                if (!en.getGeometryDataIterator().done())
                {
                    child.Expanded += TvTreeItem_Expanded;
                    child.Items.Add(null);
                }
            }
            else
            {
                new TvTreeItem("<" + GetGeomNameFromType(id.getType()) + ">",
                    Resource["MbGeomImg"] as BitmapImage, parent, new TvNodeData(TvBrowserItemType.Geometry, id, _wpfView.TvDeviceId), _wpfView.VM);
            }
            MM.StopTransaction(mtr);
        }

        private string GetGeomNameFromType(OdTvGeometryDataType type)
        {
            string[] geomTypes = { "Undefinied", "Polyline", "Circle", "CircleWedge", "CircularArc", "Ellipse", "EllipticArc", "Polygon", "Text", "Shell", "Sphere", "Cylinder"
                , "Insert", "SubEntity", "Nurbs", "RasterImage", "InfiniteLine", "Mesh", "PointCloud", "Grid", "ColoredShape"};
            return geomTypes[(int)type];
        }

        private void AddBlocks(TvTreeItem parent)
        {
            TvTreeItem itm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvBlocksIterator it = _tvDbId.openObject().getBlocksIterator();
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.BlocksFold, null);
                int cnt = 0;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                itm = new TvTreeItem("Blocks", Resource["MbBlockImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.Expanded += TvTreeItem_Expanded;
                itm.Items.Add(null);
                itm.SetBold();
            }
            MM.StopTransaction(mtr);
        }

        private void AddBlock(OdTvBlockId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvBlock block = id.openObject();
            TvNodeData nData = new TvNodeData(TvBrowserItemType.Blocks, id);

            OdTvEntitiesIterator it = block.getEntitiesIterator();
            int cnt = 0;
            while (!it.done())
            {
                cnt++;
                it.step();
            }
            nData.CountOfChild = cnt;

            TvTreeItem child = new TvTreeItem("Block<" + id.openObject().getName() + ">", Resource["MbBlockImg"] as BitmapImage
                , parent, nData, _wpfView.VM);
            if (!block.getEntitiesIterator().done())
            {
                child.Expanded += TvTreeItem_Expanded;
                child.Items.Add(null);
            }
            MM.StopTransaction(mtr);
        }

        private void AddLinetypes(TvTreeItem parent)
        {
            TvTreeItem itm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetypesIterator it = _tvDbId.openObject().getLinetypesIterator();
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.LinetypesFold, null);
                int cnt = 1;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                itm = new TvTreeItem("Linetypes", Resource["MbLinetypeImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.SetBold();
                itm.Items.Add(null);
                itm.Expanded += TvTreeItem_Expanded;
            }
            MM.StopTransaction(mtr);
        }

        private void AddLinetype(OdTvLinetypeId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            new TvTreeItem("Linetype<" + id.openObject().getName() + ">", Resource["MbLinetypeImg"] as BitmapImage
                , parent, new TvNodeData(TvBrowserItemType.Linetypes, id), _wpfView.VM);
            MM.StopTransaction(mtr);
        }

        private void AddTextStyles(TvTreeItem parent)
        {
            TvTreeItem itm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextStylesIterator it = _tvDbId.openObject().getTextStylesIterator();
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.TextStylesFold, null);
                int cnt = 0;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                itm = new TvTreeItem("TextStyles", Resource["MbTxtStyleImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.SetBold();
                itm.Items.Add(null);
                itm.Expanded += TvTreeItem_Expanded;
            }
            MM.StopTransaction(mtr);
        }

        private void AddTextStyle(OdTvTextStyleId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            new TvTreeItem("TextStyle<" + id.openObject().getName() + ">", Resource["MbTxtStyleImg"] as BitmapImage
                , parent, new TvNodeData(TvBrowserItemType.TextStyles, id), _wpfView.VM);
            MM.StopTransaction(mtr);
        }

        private void AddLayers(TvTreeItem parent)
        {
            TvTreeItem itm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayersIterator it = _tvDbId.openObject().getLayersIterator();
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.LayersFold, null);
                int cnt = 0;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                itm = new TvTreeItem("Layers", Resource["MbLayersImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.SetBold();
                itm.Items.Add(null);
                itm.Expanded += TvTreeItem_Expanded;
            }
            MM.StopTransaction(mtr);
        }

        private void AddLayer(OdTvLayerId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            new TvTreeItem("Layer<" + id.openObject().getName() + ">", Resource["MbLayerImg"] as BitmapImage
                , parent, new TvNodeData(TvBrowserItemType.Layers, id), _wpfView.VM);
            MM.StopTransaction(mtr);
        }

        private void AddMaterials(TvTreeItem parent)
        {
            TvTreeItem itm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMaterialsIterator it = _tvDbId.openObject().getMaterialsIterator();
            if (!it.done())
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.MaterialsFold, null);
                int cnt = 0;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                itm = new TvTreeItem("Materials", Resource["MbMaterialsFoldImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.Items.Add(null);
                itm.SetBold();
                itm.Expanded += TvTreeItem_Expanded;
            }
            MM.StopTransaction(mtr);
        }

        private void AddMaterial(OdTvMaterialId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            new TvTreeItem("Material<" + id.openObject().getName() + ">", Resource["MbMaterialImg"] as BitmapImage
                , parent, new TvNodeData(TvBrowserItemType.Materials, id), _wpfView.VM);
            MM.StopTransaction(mtr);
        }

        private void AddRasterImages(TvTreeItem parent)
        {
            TvTreeItem itm = null;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvRasterImagesIterator it = _tvDbId.openObject().getRasterImagesIterator();
            if (!it.done() && it.getRasterImage().openObject().getSourceFileName().Length > 0)
            {
                TvNodeData nData = new TvNodeData(TvBrowserItemType.RasterImagesFold, null);
                int cnt = 0;
                while (!it.done())
                {
                    cnt++;
                    it.step();
                }
                nData.CountOfChild = cnt;

                itm = new TvTreeItem("Raster Images", Resource["MbImagesFoldImg"] as BitmapImage, parent, nData, _wpfView.VM);
                itm.SetBold();
                itm.Items.Add(null);
                itm.Expanded += TvTreeItem_Expanded;
            }
            MM.StopTransaction(mtr);
        }

        private void AddRasterImage(OdTvRasterImageId id, TvTreeItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            new TvTreeItem("RasterImage<" + id.openObject().getSourceFileName() + ">", Resource["MbImageImg"] as BitmapImage
                , parent, new TvNodeData(TvBrowserItemType.RasterImages, id), _wpfView.VM);
            MM.StopTransaction(mtr);
        }

        private void TvTreeItem_Expanded(object sender, RoutedEventArgs e)
        {
            TvTreeItem itm = sender as TvTreeItem;
            if (itm == null || itm.NodeData.IsLoaded)
                return;

            switch (itm.NodeData.Type)
            {
                case TvBrowserItemType.MaterialsFold:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        OdTvMaterialsIterator it = _tvDbId.openObject().getMaterialsIterator();
                        int ind = 1;
                        while (!it.done())
                        {
                            AddMaterial(it.getMaterial(), itm);
                            if (ind % _countOfDisplayedObjects == 0)
                            {
                                AddExpandButton(itm, ind);
                                break;
                            }
                            ind++;
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.LinetypesFold:
                    {
                        MemoryTransaction mtr = MM.StartTransaction();
                        itm.Items.Clear();
                        OdTvLinetypesIterator it = _tvDbId.openObject().getLinetypesIterator();
                        int ind = 1;
                        while (!it.done())
                        {
                            AddLinetype(it.getLinetype(), itm);
                            if (ind % _countOfDisplayedObjects == 0)
                            {
                                AddExpandButton(itm, ind);
                                break;
                            }
                            ind++;
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.TextStylesFold:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        OdTvTextStylesIterator it = _tvDbId.openObject().getTextStylesIterator();
                        int ind = 1;
                        while (!it.done())
                        {
                            AddTextStyle(it.getTextStyle(), itm);
                            if (ind % _countOfDisplayedObjects == 0)
                            {
                                AddExpandButton(itm, ind);
                                break;
                            }
                            ind++;
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.Models:
                    {
                        MemoryTransaction mtr = MM.StartTransaction();
                        itm.Items.Clear();
                        if (itm.NodeData.ModelId != null && itm.NodeData.ModelId.openObject() != null)
                            AddEntities(itm.NodeData.ModelId, itm);
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.ModelsFold:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        OdTvModelsIterator it = _tvDbId.openObject().getModelsIterator();
                        while (!it.done())
                        {
                            TvNodeData nData = new TvNodeData(TvBrowserItemType.Models, it.getModel(), _wpfView.TvDeviceId);

                            OdTvModel model = it.getModel().openObject();
                            TvTreeItem child = new TvTreeItem("Model<" + model.getName() + ">", Resource["MbModelFoldImg"] as BitmapImage, itm, nData, _wpfView.VM);
                            itm.NodeData.ModelsDictionary.Add(it.getModel().openObject().getDatabaseHandle(), child);

                            OdTvEntitiesIterator enIt = model.getEntitiesIterator();
                            if (!enIt.done())
                            {
                                child.Expanded += TvTreeItem_Expanded;
                                child.Items.Add(null);

                                int cnt = 0;
                                while (!enIt.done())
                                {
                                    cnt++;
                                    enIt.step();
                                }
                                nData.CountOfChild = cnt;
                            }
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.RasterImagesFold:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        OdTvRasterImagesIterator it = _tvDbId.openObject().getRasterImagesIterator();
                        int ind = 1;
                        while (!it.done())
                        {
                            AddRasterImage(it.getRasterImage(), itm);
                            if (ind % _countOfDisplayedObjects == 0)
                            {
                                AddExpandButton(itm, ind);
                                break;
                            }
                            ind++;
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.Blocks:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        AddEntities(itm.NodeData.BlockId, itm);
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.BlocksFold:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        OdTvBlocksIterator it = _tvDbId.openObject().getBlocksIterator();
                        int ind = 1;
                        while (!it.done())
                        {
                            AddBlock(it.getBlock(), itm);
                            if (ind % _countOfDisplayedObjects == 0)
                            {
                                AddExpandButton(itm, ind);
                                break;
                            }
                            ind++;
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.LayersFold:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        OdTvLayersIterator it = _tvDbId.openObject().getLayersIterator();
                        int ind = 1;
                        while (!it.done())
                        {
                            AddLayer(it.getLayer(), itm);
                            if (ind % _countOfDisplayedObjects == 0)
                            {
                                AddExpandButton(itm, ind);
                                break;
                            }
                            ind++;
                            it.step();
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.Entity:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        if (itm.NodeData.EntityId != null && !itm.NodeData.EntityId.isNull())
                        {
                            if (itm.NodeData.EntityId != null && itm.NodeData.EntityId.openObject() != null)
                                AddGeometries(itm.NodeData.EntityId.openObject().getGeometryDataIterator(), itm);
                        }
                        MM.StopTransaction(mtr);
                        break;
                    }
                case TvBrowserItemType.Geometry:
                    {
                        itm.Items.Clear();
                        MemoryTransaction mtr = MM.StartTransaction();
                        if (itm.NodeData.SubEntId != null && itm.NodeData.SubEntId.isValid())
                            AddGeometries(itm.NodeData.SubEntId.openAsSubEntity().getGeometryDataIterator(), itm);
                        MM.StopTransaction(mtr);
                        break;
                    }
            }

            itm.NodeData.IsLoaded = true;
        }

        private void AddExpandButton(TvTreeItem parent, int index)
        {
            TreeViewItem itm = new TreeViewItem();

            Button btn = new Button
            {
                Content = new Image() { Source = Resource["MbExpandImg"] as BitmapImage, Height = 9 },
                Width = 100,
                Height = 15,
                Tag = index,
                ToolTip = "Expand"
            };
            btn.Click += ExpandMoreItems_Click;

            Button btnAll = new Button
            {
                Margin = new Thickness(5, 0, 0, 0),
                Width = 30,
                Content = new Image() { Source = Resource["MbExpandAllImg"] as BitmapImage },
                Height = 15,
                Tag = -1,
                ToolTip = "Expand all"
            };
            btnAll.Click += ExpandMoreItems_Click;

            StackPanel panel = new StackPanel() { Orientation = Orientation.Horizontal, Margin = new Thickness(0, 2, 0, 5) };
            panel.Children.Add(btn);
            panel.Children.Add(btnAll);

            itm.Header = panel;
            parent.Items.Add(itm);
        }

        private void ExpandMoreItems_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            if (btn == null)
                return;
            StackPanel firstParent = btn.Parent as StackPanel;
            TreeViewItem secparent = firstParent.Parent as TreeViewItem;
            TvTreeItem globParent = secparent.Parent as TvTreeItem;
            if (globParent == null)
            {
                MessageBox.Show("Parent is wrong!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            globParent.Items.Remove(secparent);

            LoadElements(globParent, (int)btn.Tag, (int)btn.Tag > 0 ? (int)btn.Tag + _countOfDisplayedObjects : Int32.MaxValue);
        }

        private void LoadElements(TvTreeItem parent, int startInd, int endInd)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            switch (parent.NodeData.Type)
            {
                case TvBrowserItemType.MaterialsFold:
                    LoadByType<OdTvMaterialsIterator>(_tvDbId.openObject().getMaterialsIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.LinetypesFold:
                    LoadByType<OdTvLinetypesIterator>(_tvDbId.openObject().getLinetypesIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.TextStylesFold:
                    LoadByType<OdTvTextStylesIterator>(_tvDbId.openObject().getTextStylesIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.Models:
                    LoadByType<OdTvEntitiesIterator>(parent.NodeData.ModelId.openObject().getEntitiesIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.RasterImagesFold:
                    LoadByType<OdTvRasterImagesIterator>(_tvDbId.openObject().getRasterImagesIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.Blocks:
                    LoadByType<OdTvBlocksIterator>(_tvDbId.openObject().getBlocksIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.LayersFold:
                    LoadByType<OdTvLayersIterator>(_tvDbId.openObject().getLayersIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.Entity:
                    LoadByType<OdTvGeometryDataIterator>(parent.NodeData.EntityId.openObject().getGeometryDataIterator(), startInd, endInd, parent);
                    break;
                case TvBrowserItemType.Geometry:
                    LoadByType<OdTvGeometryDataIterator>(parent.NodeData.SubEntId.openAsSubEntity().getGeometryDataIterator(), startInd, endInd, parent);
                    break;
            }

            MM.StopTransaction(mtr);
        }

        private void LoadByType<T>(T it, int startInd, int endInd, TvTreeItem parent) where T : OdTvIterator
        {
            int curInd = 1;
            while (!it.done())
            {
                if (curInd <= startInd)
                {
                    curInd++;
                    it.step();
                    continue;
                }
                if (curInd > endInd)
                    break;

                switch (parent.NodeData.Type)
                {
                    case TvBrowserItemType.MaterialsFold:
                        {
                            OdTvMaterialsIterator itr = it as OdTvMaterialsIterator;
                            if (itr != null)
                                AddMaterial(itr.getMaterial(), parent);
                            break;
                        }
                    case TvBrowserItemType.LinetypesFold:
                        {
                            OdTvLinetypesIterator itr = it as OdTvLinetypesIterator;
                            if (itr != null)
                                AddLinetype(itr.getLinetype(), parent);
                            break;
                        }
                    case TvBrowserItemType.TextStylesFold:
                        {
                            OdTvTextStylesIterator itr = it as OdTvTextStylesIterator;
                            if (itr != null)
                                AddTextStyle(itr.getTextStyle(), parent);
                            break;
                        }
                    case TvBrowserItemType.BlocksFold:
                        {
                            OdTvBlocksIterator itr = it as OdTvBlocksIterator;
                            if (itr != null)
                                AddBlock(itr.getBlock(), parent);
                            break;
                        }
                    case TvBrowserItemType.Blocks:
                    case TvBrowserItemType.Models:
                        {
                            OdTvEntitiesIterator itr = it as OdTvEntitiesIterator;
                            if (itr != null)
                                AddEntity(itr.getEntity(), parent);
                            break;
                        }
                    case TvBrowserItemType.RasterImagesFold:
                        {
                            OdTvRasterImagesIterator itr = it as OdTvRasterImagesIterator;
                            if (itr != null)
                                AddRasterImage(itr.getRasterImage(), parent);
                            break;
                        }
                    case TvBrowserItemType.LayersFold:
                        {
                            OdTvLayersIterator itr = it as OdTvLayersIterator;
                            if (itr != null)
                                AddLayer(itr.getLayer(), parent);
                            break;
                        }
                    case TvBrowserItemType.Geometry:
                    case TvBrowserItemType.Entity:
                        {
                            OdTvGeometryDataIterator itr = it as OdTvGeometryDataIterator;
                            if (itr != null)
                                AddGeometry(itr.getGeometryData(), parent);
                            break;
                        }
                }

                curInd++;
                it.step();
            }

            if (!it.done())
                AddExpandButton(parent, curInd);
        }

    }
}

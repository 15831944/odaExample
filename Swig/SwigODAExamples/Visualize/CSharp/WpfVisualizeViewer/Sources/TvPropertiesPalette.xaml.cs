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
using System.Windows.Media;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.ModelBrowser;
using WpfVisualizeViewer.ModelBrowser.ObjectProperties;
using WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties;

namespace WpfVisualizeViewer
{
    /// <summary>
    /// Interaction logic for TvPropertiesPalette.xaml
    /// </summary>
    public partial class TvPropertiesPalette : UserControl
    {
        private MemoryManager _mm = MemoryManager.GetMemoryManager();
        private OdTvGsDeviceId _devId;
        private OdTvWpfView _renderArea;
        private Colorpicker _colorPicker;

        private OdTvWpfMainWindowModel _vm = null;

        private bool _isDeviceExist = false;
        public bool IsDeviceExist
        {
            get { return _isDeviceExist; }
            set
            {
                _isDeviceExist = value;
                if (_isDeviceExist)
                {
                    MemoryTransaction mtr = _mm.StartTransaction();
                    _colorPicker = new Colorpicker(BasePaletteProperties.GetColorDefFromUInt(_devId.openObject().getBackgroundColor()), _devId);
                    _colorPicker.Margin = new Thickness(10, 0, 0, 0);
                    _colorPicker.HorizontalAlignment = HorizontalAlignment.Stretch;
                    _colorPicker.ColorChanged += Background_ColorChanged;
                    BackgroundPanel.Children.Add(_colorPicker);
                    _mm.StopTransaction(mtr);
                }
                else if (!_isDeviceExist && _colorPicker != null)
                {
                    BackgroundPanel.Children.Remove(_colorPicker);
                    _colorPicker = null;
                }

                BackgroundTextBlock.Visibility = _isDeviceExist ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private double _zoomStep = 2;
        public double ZoomStep
        {
            get { return _zoomStep; }
            set
            {
                _zoomStep = value;
                if (_vm != null)
                    _vm.ZoomStep = _zoomStep;
            }
        }

        private void Background_ColorChanged(object sender, OdTvColorDef newColor)
        {
            MemoryTransaction mtr = _mm.StartTransaction();
            OdTvGsDevice dev = _devId.openObject(OpenMode.kForWrite);
            byte r, g, b;
            newColor.getColor(out r, out g, out b);
            uint color = BasePaletteProperties.ColorToUInt(newColor);
            if (dev.getBackgroundColor() != color)
            {
                dev.setBackgroundColor(color);
                dev.update();
            }
            _mm.StopTransaction(mtr);
        }

        public TvPropertiesPalette()
        {
            DataContext = this;
            InitializeComponent();
            _vm = OdTvWpfMainWindow.ViewModel;
        }

        public void InitializePalette(OdTvGsDeviceId devId, OdTvWpfView renderArea)
        {
            _devId = devId;
            _renderArea = renderArea;
            BackgroundTextBlock.Visibility = Visibility.Visible;
            IsDeviceExist = true;
        }

        public void FillObjectParameters(TvTreeItem itm)
        {
            PropertiesPaletteList.Children.Clear();
            switch (itm.NodeData.Type)
            {
                case TvBrowserItemType.Database:
                    {
                        TvDatabaseProperties dbProperties = new TvDatabaseProperties(_devId, _renderArea);
                        PropertiesPaletteList.Children.Add(dbProperties);
                        break;
                    }
                case TvBrowserItemType.Devices:
                    TvDeviceProperties devProp = new TvDeviceProperties(itm.NodeData.DeviceId, _renderArea);
                    PropertiesPaletteList.Children.Add(devProp);
                    break;
                case TvBrowserItemType.DevicesFold:
                    AddTextItem("Number of devices:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.Views:
                    TvViewProperties viewProp = new TvViewProperties(itm.NodeData.ViewId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(viewProp);
                    break;
                case TvBrowserItemType.Materials:
                    TvMaterialProperties matProp = new TvMaterialProperties(itm.NodeData.MaterialId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(matProp);
                    break;
                case TvBrowserItemType.MaterialsFold:
                    AddTextItem("Number of materials:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.Linetypes:
                    TvLinetypeProperties ltProperties = new TvLinetypeProperties(itm.NodeData.LinetypeId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(ltProperties);
                    break;
                case TvBrowserItemType.LinetypesFold:
                    AddTextItem("Number of linetypes:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.TextStyles:
                    TvTextStyleProperties txtStyleProperties = new TvTextStyleProperties(itm.NodeData.TextStyleId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(txtStyleProperties);
                    break;
                case TvBrowserItemType.TextStylesFold:
                    AddTextItem("Number of text styles:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.Models:
                    TvModelProperties modelProperties = new TvModelProperties(itm.NodeData.ModelId, itm.NodeData.CountOfChild, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(modelProperties);
                    break;
                case TvBrowserItemType.ModelsFold:
                    AddTextItem("Number of models:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.RasterImages:
                    TvRasterImageProperties imgProperties = new TvRasterImageProperties(itm.NodeData.RasterImgId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(imgProperties);
                    break;
                case TvBrowserItemType.RasterImagesFold:
                    AddTextItem("Number of raster images", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.Blocks:
                    AddTextItem("Count of entities:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.BlocksFold:
                    AddTextItem("Number of blocks:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.Layers:
                    TvLayerProperties layerProperties = new TvLayerProperties(itm.NodeData.LayerId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(layerProperties);
                    break;
                case TvBrowserItemType.LayersFold:
                    AddTextItem("Number of layers:", itm.NodeData.CountOfChild.ToString(), isReadOnly: true);
                    break;
                case TvBrowserItemType.Entity:
                    TvEntityProperties entityProperties = new TvEntityProperties(itm.NodeData.EntityId, itm.NodeData.CountOfChild, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(entityProperties);
                    break;
                case TvBrowserItemType.Insert:
                    TvInsertProperties insertProperties = new TvInsertProperties(itm.NodeData.EntityId, itm.NodeData.CountOfChild, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(insertProperties);
                    break;
                case TvBrowserItemType.Light:
                    TvLightProperties lightProperties = new TvLightProperties(itm.NodeData.EntityId, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(lightProperties);
                    break;
                case TvBrowserItemType.Geometry:
                    FillGeometry(itm.NodeData.GeomId ?? itm.NodeData.SubEntId, itm.NodeData.CountOfChild);
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private void AddTextItem(string label, string text, StretchingTreeViewItem parent = null,
            bool isReadOnly = false)
        {
            AddItemToPalette(GetPanelWithText(label, text, isReadOnly), parent);
        }

        private Grid CreateGridWithElements(int countOfColumns, params UIElement[] uiElements)
        {
            Grid grid = new Grid();
            for (int i = 0; i < countOfColumns; i++)
            {
                grid.ColumnDefinitions.Add(i < 2
                    ? new ColumnDefinition()
                    : new ColumnDefinition() { Width = GridLength.Auto });
            }

            foreach (var element in uiElements)
                grid.Children.Add(element);

            return grid;
        }

        private Grid GetPanelWithText(string label, string text, bool isReadOnly = false, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetColumn(lbl, 0);
            TextBox txt = new TextBox()
            {
                Text = text,
                IsReadOnly = isReadOnly,
                VerticalContentAlignment = VerticalAlignment.Center,
            };
            Grid.SetColumn(txt, 1);

            return CreateGridWithElements(2, lbl, txt);
        }

        private void AddItemToPalette(Grid grid, StretchingTreeViewItem parent)
        {
            if (parent != null)
                parent.Items.Add(new StretchingTreeViewItem { Header = grid });
            else
            {
                ListBoxItem itm = new ListBoxItem
                {
                    HorizontalAlignment = HorizontalAlignment.Stretch,
                    HorizontalContentAlignment = HorizontalAlignment.Stretch,
                    Content = grid,
                    BorderBrush = Brushes.Black,
                    IsHitTestVisible = false
                };
                PropertiesPaletteList.Children.Add(itm);
            }
        }

        private void FillGeometry(OdTvGeometryDataId id, int cnt)
        {
            switch (id.getType())
            {
                case OdTvGeometryDataType.kPolyline:
                    TvPolylineProperties polylineProperties = new TvPolylineProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(polylineProperties);
                    break;
                case OdTvGeometryDataType.kCircle:
                    TvCircleProperties circProperties = new TvCircleProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(circProperties);
                    break;
                case OdTvGeometryDataType.kCircleWedge:
                    TvCircWedgeProperties circWedgeProperties = new TvCircWedgeProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(circWedgeProperties);
                    break;
                case OdTvGeometryDataType.kCircularArc:
                    TvCircArcProperties circArcProperties = new TvCircArcProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(circArcProperties);
                    break;
                case OdTvGeometryDataType.kEllipse:
                    TvEllipseProperties ellipseProperties = new TvEllipseProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(ellipseProperties);
                    break;
                case OdTvGeometryDataType.kEllipticArc:
                    TvEllipticArcProperties ellipArcProperties = new TvEllipticArcProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(ellipArcProperties);
                    break;
                case OdTvGeometryDataType.kPolygon:
                    TvPolygonProperties polygonProperties = new TvPolygonProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(polygonProperties);
                    break;
                case OdTvGeometryDataType.kText:
                    TvTextProperties textProperties = new TvTextProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(textProperties);
                    break;
                case OdTvGeometryDataType.kShell:
                    TvShellProperties shellProperties = new TvShellProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(shellProperties);
                    break;
                case OdTvGeometryDataType.kSphere:
                    TvSphereProperties sphereProperties = new TvSphereProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(sphereProperties);
                    break;
                case OdTvGeometryDataType.kCylinder:
                    TvCylinderProperties cylinderProperties = new TvCylinderProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(cylinderProperties);
                    break;
                case OdTvGeometryDataType.kSubInsert:
                    {
                        MemoryTransaction mtr = MemoryManager.GetMemoryManager().StartTransaction();
                        OdTvInsertData ins = id.openAsInsert();
                        AddTextItem("Block:", ins.getBlock().openObject().getName(), isReadOnly: true);
                        MemoryManager.GetMemoryManager().StopTransaction(mtr);
                        break;
                    }
                case OdTvGeometryDataType.kSubEntity:
                    TvEntityProperties subEntProperties = new TvEntityProperties(id, cnt, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(subEntProperties);
                    break;
                case OdTvGeometryDataType.kNurbs:
                    TvNurbsProperties nurbsProperties = new TvNurbsProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(nurbsProperties);
                    break;
                case OdTvGeometryDataType.kRasterImage:
                    TvRasterImageDataProperties imgProperties = new TvRasterImageDataProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(imgProperties);
                    break;
                case OdTvGeometryDataType.kInfiniteLine:
                    TvInfiniteLineProperties infiniteLineProperties = new TvInfiniteLineProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(infiniteLineProperties);
                    break;
                case OdTvGeometryDataType.kMesh:
                    TvMeshProperties meshProperties = new TvMeshProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(meshProperties);
                    break;
                case OdTvGeometryDataType.kPointCloud:
                    TvPointCloudProperties pointCloudProperties = new TvPointCloudProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(pointCloudProperties);
                    break;
                case OdTvGeometryDataType.kGrid:
                    TvGridProperties gridProperties = new TvGridProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(gridProperties);
                    break;
                case OdTvGeometryDataType.kColoredShape:
                    TvColoredShapeProperties shapeProperties = new TvColoredShapeProperties(id, _devId, _renderArea);
                    PropertiesPaletteList.Children.Add(shapeProperties);
                    break;
            }
        }

        private void ScrollViewer_PreviewMouseWheel(object sender, System.Windows.Input.MouseWheelEventArgs e)
        {
            ScrollViewer scv = (ScrollViewer)sender;
            scv.ScrollToVerticalOffset(scv.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        private void OnOffFPS_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            _vm.AppearanceOpt = cb.IsChecked == true ?
                _vm.AppearanceOpt | OdTvWpfMainWindowModel.AppearanceOptions.FPSEnabled
                : _vm.AppearanceOpt ^ OdTvWpfMainWindowModel.AppearanceOptions.FPSEnabled;
        }

        private void OnOffWcs_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            _vm.AppearanceOpt = cb.IsChecked == true ?
                _vm.AppearanceOpt | OdTvWpfMainWindowModel.AppearanceOptions.WCSEnabled
                : _vm.AppearanceOpt ^ OdTvWpfMainWindowModel.AppearanceOptions.WCSEnabled;
        }

        private void OnOffAnimation_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            _vm.AppearanceOpt = cb.IsChecked == true ?
                _vm.AppearanceOpt | OdTvWpfMainWindowModel.AppearanceOptions.UseAnimation
                : _vm.AppearanceOpt ^ OdTvWpfMainWindowModel.AppearanceOptions.UseAnimation;
        }

        public void ShowSelectionInfo(OdTvSelectionSet sSet, OdTvModelId modelId)
        {
            TvSelectionInfo selInfo = new TvSelectionInfo(sSet, _devId, _renderArea);
            PropertiesPaletteList.Children.Add(selInfo);
        }
    }
}

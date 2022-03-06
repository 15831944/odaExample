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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.ModelBrowser;
using Application = System.Windows.Application;
using Button = System.Windows.Controls.Button;
using CheckBox = System.Windows.Controls.CheckBox;
using ComboBox = System.Windows.Controls.ComboBox;
using HorizontalAlignment = System.Windows.HorizontalAlignment;
using KeyEventArgs = System.Windows.Input.KeyEventArgs;
using Label = System.Windows.Controls.Label;
using MessageBox = System.Windows.Forms.MessageBox;
using Orientation = System.Windows.Controls.Orientation;
using TextBox = System.Windows.Controls.TextBox;
using UserControl = System.Windows.Controls.UserControl;

namespace WpfVisualizeViewer
{
    /// <summary>
    /// Interaction logic for BasePaletteProperties.xaml
    /// </summary>
    public partial class BasePaletteProperties : UserControl
    {
        public OdTvGsDeviceId TvDeviceId { get; private set; }
        public OdTvDatabaseId TvDatabaseId { get; private set; }
        protected OdTvWpfView _renderArea;
        protected MemoryManager MM = MemoryManager.GetMemoryManager();

        public enum CoordinateType
        {
            X,
            Y,
            Z
        }

        public enum DcSizeType
        {
            xMin,
            xMax,
            yMin,
            yMax
        }

        public struct MatrixData
        {
            public enum DataType
            {
                Origin,
                XAxis,
                YAxis,
                ZAxis,
                Translation
            }

            public CoordinateType Type;
            public DataType Data;

            public MatrixData(CoordinateType type, DataType dType)
            {
                Type = type;
                Data = dType;
            }

        }

        public BasePaletteProperties(OdTvGsDeviceId id, OdTvWpfView renderArea)
        {
            if (id == null || renderArea == null)
                return;
            DataContext = this;
            InitializeComponent();
            TvDeviceId = id;
            MemoryTransaction mtr = MemoryManager.GetMemoryManager().StartTransaction();
            TvDatabaseId = id.openObject().getDatabase();
            _renderArea = renderArea;
            MainGrid.MaxWidth = Scroller.IsVisible ? renderArea.VM.CurrentPropertiesWidth - 10 + Scroller.Width : renderArea.VM.CurrentPropertiesWidth - 10;
            MemoryManager.GetMemoryManager().StopTransaction(mtr);
            SizeChanged += BasePaletteProperties_SizeChanged;
        }

        private void BasePaletteProperties_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            Visibility verticalScrollBarVisibility = Scroller.ComputedVerticalScrollBarVisibility;
            MainGrid.MaxWidth = verticalScrollBarVisibility == Visibility.Visible
                ? _renderArea.VM.CurrentPropertiesWidth - 10 - SystemParameters.VerticalScrollBarWidth : _renderArea.VM.CurrentPropertiesWidth - 10;
        }

        protected void Update()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            _renderArea.Focus();
            if (TvDeviceId != null && !TvDeviceId.isNull())
                TvDeviceId.openObject().update();
            if (_renderArea != null)
                _renderArea.Invalidate();
            MM.StopTransaction(mtr);
        }

        public static uint ColorToUInt(Color color)
        {
            return (uint)((color.A << 24) | (color.B << 16) |
                          (color.G << 8) | (color.R << 0));
        }

        public static uint ColorToUInt(OdTvColorDef color, int alpha = -1)
        {
            byte r, g, b;
            color.getColor(out r, out g, out b);
            uint iColor = 0;
            if (alpha < 0)
                iColor = (uint)((b << 16) | (g << 8) | (r << 0));
            else
                iColor = (uint)((alpha << 24) | (b << 16) | (g << 8) | (r << 0));
            return iColor;
        }

        public static OdTvColorDef GetColorDefFromUInt(uint color)
        {
            byte b = (byte)(color >> 16);
            byte g = (byte)(color >> 8);
            byte r = (byte)(color >> 0);
            return new OdTvColorDef(r, g, b);
        }

        public static byte GetAlphaFromColor(uint color)
        {
            return (byte)(color >> 24);
        }

        protected Grid CreateGridWithElements(int countOfColumns, params UIElement[] uiElements)
        {
            Grid grid = new Grid();
            for (int i = 0; i < countOfColumns; i++)
                grid.ColumnDefinitions.Add(new ColumnDefinition());

            foreach (var element in uiElements)
                grid.Children.Add(element);

            return grid;
        }

        protected Colorpicker AddColorDef(string label, OdTvColorDef color, int[] layots, Grid grid, bool isObjColor = true)
        {
            Label lbl = new Label() { Content = label };
            Grid.SetRow(lbl, layots[0]);
            Grid.SetColumn(lbl, layots[1]);
            Colorpicker clrp = new Colorpicker(color, TvDeviceId, isObjColor);
            if (color.getType() == OdTvColorDef.ColorType.kDefault)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(clrp, layots[2]);
            Grid.SetColumn(clrp, layots[3]);
            grid.Children.Add(lbl);
            grid.Children.Add(clrp);
            return clrp;
        }

        protected Colorpicker AddColorDef(string label, OdTvColorDef color, StretchingTreeViewItem parent, bool isObjColor = true)
        {
            Label lbl = new Label() { Content = label };
            Grid.SetColumn(lbl, 0);
            Colorpicker clrp = new Colorpicker(color, TvDeviceId, isObjColor);
            if (color.getType() == OdTvColorDef.ColorType.kDefault)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetColumn(clrp, 1);
            parent.Items.Add(CreateGridWithElements(2, lbl, clrp));
            return clrp;
        }

        protected ComboBox AddLinetypeDef(string label, OdTvLinetypeDef linetype, Grid grid, int[] arr,
            bool isLayer = false)
        {
            return AddLabelAndComboBox(label, GetLinetypesList(isLayer), GetLinetypeName(linetype), grid, arr,
                linetype.getType() == OdTvLinetypeDef.LinetypeType.kDefault);
        }
        protected string GetLinetypeName(OdTvLinetypeDef ltDef)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            string name = "";
            switch (ltDef.getType())
            {
                case OdTvLinetypeDef.LinetypeType.kId:
                    name = ltDef.getLinetype().openObject().getName();
                    if (name == null) name = "";
                    break;
                case OdTvLinetypeDef.LinetypeType.kPredefined:
                    name = ltDef.getPredefinedLinetype().ToString().Remove(0, 1);
                    break;
                case OdTvLinetypeDef.LinetypeType.kInherited:
                    name = ltDef.getInheritedLinetype().ToString().Remove(0, 1);
                    break;
            }
            MM.StopTransaction(mtr);
            return name;
        }

        protected ComboBox AddLayerDef(string label, OdTvLayerDef layer, Grid grid, int[] arr)
        {
            return AddLabelAndComboBox(label, GetLayersList(), GetLayerName(layer), grid, arr,
                layer.getType() == OdTvLayerDef.LayerType.kDefault);
        }
        protected string GetLayerName(OdTvLayerDef layer)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            string name = "";
            if (layer.getType() == OdTvLayerDef.LayerType.kId)
                name = layer.getLayer().openObject().getName();
            MM.StopTransaction(mtr);
            return name;
        }

        protected CheckBox AddVisibilityDef(string label, OdTvVisibilityDef vis, Grid grid, int[] arr, HorizontalAlignment align = HorizontalAlignment.Left)
        {
            return AddLabelAndCheckBox(label, vis.getType() != OdTvVisibilityDef.VisibilityType.kInvisible, grid, arr, false,
                vis.getType() == OdTvVisibilityDef.VisibilityType.kDefault);
        }
        protected OdTvLinetypeDef GetLinetypeDef(string name)
        {
            OdTvLinetypeDef lt = null;
            switch (name)
            {
                case "":
                    lt = new OdTvLinetypeDef();
                    lt.setDefault();
                    break;
                case "ByBlock":
                    lt = new OdTvLinetypeDef(InheritedAttribute.kByBlock);
                    break;
                case "ByLayer":
                    lt = new OdTvLinetypeDef(InheritedAttribute.kByLayer);
                    break;
                case "Solid":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kSolid);
                    break;
                case "DashDot":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kDashDot);
                    break;
                case "Dashed":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kDashed);
                    break;
                case "Dotted":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kDotted);
                    break;
                case "Dash2Dot":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kDash2Dot);
                    break;
                case "Dash3Dot":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kDash3Dot);
                    break;
                case "LongDash":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kLongDash);
                    break;
                case "LongDashShortDash":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kLongDashShortDash);
                    break;
                case "LongDash2ShortDash":
                    lt = new OdTvLinetypeDef(OdTvLinetype.Predefined.kLongDash2ShortDash);
                    break;
                default:
                    {
                        MemoryTransaction mtr = MM.StartTransaction();
                        for (OdTvLinetypesIterator it = TvDatabaseId.openObject().getLinetypesIterator(); !it.done(); it.step())
                            if (it.getLinetype().openObject().getName() == name)
                            {
                                lt = new OdTvLinetypeDef(it.getLinetype());
                                break;
                            }
                        MM.StopTransaction(mtr);
                        break;
                    }
            }

            return lt;
        }

        protected OdTvLayerDef GetLayerDef(string name)
        {
            OdTvLayerDef lyDef = new OdTvLayerDef();
            lyDef.setDefault();
            MemoryTransaction mtr = MM.StartTransaction();
            for (OdTvLayersIterator it = TvDatabaseId.openObject().getLayersIterator(); !it.done(); it.step())
                if (it.getLayer().openObject().getName() == name)
                {
                    lyDef = new OdTvLayerDef(it.getLayer());
                    break;
                }
            MM.StopTransaction(mtr);
            return lyDef;
        }

        protected OdTvTextStyleDef GetTextStyleDef(string name)
        {
            OdTvTextStyleDef txtDef = new OdTvTextStyleDef();
            txtDef.setDefault();
            MemoryTransaction mtr = MM.StartTransaction();
            for (OdTvTextStylesIterator it = TvDatabaseId.openObject().getTextStylesIterator(); !it.done(); it.step())
                if (it.getTextStyle().openObject().getName() == name)
                {
                    txtDef = new OdTvTextStyleDef(it.getTextStyle());
                    break;
                }
            MM.StopTransaction(mtr);
            return txtDef;
        }

        protected OdTvMaterialDef GetMaterialDef(string name)
        {
            OdTvMaterialDef matDef = new OdTvMaterialDef();
            matDef.setDefault();
            MemoryTransaction mtr = MM.StartTransaction();
            for (OdTvMaterialsIterator it = TvDatabaseId.openObject().getMaterialsIterator(); !it.done(); it.step())
                if (it.getMaterial().openObject().getName() == name)
                {
                    matDef = new OdTvMaterialDef(it.getMaterial());
                    break;
                }
            MM.StopTransaction(mtr);
            return matDef;
        }

        protected string GetMaterialName(OdTvMaterialDef matDef)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            string name = "";
            switch (matDef.getType())
            {
                case OdTvMaterialDef.MaterialType.kId:
                    name = matDef.getMaterial().openObject().getName();
                    break;
                case OdTvMaterialDef.MaterialType.kInherited:
                    name = matDef.getInheritedMaterial().ToString().Remove(0, 1);
                    break;
            }
            MM.StopTransaction(mtr);
            return name;
        }

        protected string GetTextStyleName(OdTvTextStyleDef txtDef)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            string name = "";
            if (txtDef.getType() == OdTvTextStyleDef.TextStyleType.kId)
                name = txtDef.getTextStyle().openObject().getName();
            MM.StopTransaction(mtr);
            return name;
        }

        protected TextBox AddLineweightDef(string label, OdTvLineWeightDef lineWeight, Grid grid, int[] arr)
        {
            return AddLabelAndTextBox(label, lineWeight.getValue().ToString(), grid, arr, false,
                lineWeight.getType() == OdTvLineWeightDef.LineWeightType.kDefault, true);
        }
        protected TextBox AddTransparencyDef(string label, OdTvTransparencyDef trDef, Grid grid, int[] arr)
        {
            return AddLabelAndTextBox(label, trDef.getValue().ToString(), grid, arr, false,
                trDef.getType() == OdTvTransparencyDef.TransparencyType.kDefault);
        }
        protected ComboBox AddMatrialDef(string label, OdTvMaterialDef material, Grid grid, int[] arr)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvResult rc = OdTvResult.tvMissingObject;
            OdTvMaterial mat = material.getMaterial().openObject(OpenMode.kForWrite, ref rc);
            ComboBox cb = AddLabelAndComboBox(label, GetMaterialsList(), rc == OdTvResult.tvOk ? mat.getName() : "", grid, arr,
                material.getType() == OdTvMaterialDef.MaterialType.kDefault);
            MM.StopTransaction(mtr);
            return cb;
        }

        protected ComboBox AddTextStyleDef(string label, OdTvTextStyleDef txtStyle, Grid grid, int[] arr)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            ComboBox cb = AddLabelAndComboBox(label, GetTextStylesList(),
                txtStyle.getType() == OdTvTextStyleDef.TextStyleType.kId
                    ? txtStyle.getTextStyle().openObject().getName()
                    : "", grid, arr,
                txtStyle.getType() == OdTvTextStyleDef.TextStyleType.kDefault);
            MM.StopTransaction(mtr);
            return cb;
        }

        protected OdTvMaterialId FindMaterial(string materialName)
        {
            OdTvMaterialId id = null;
            MemoryTransaction mtr = MM.StartTransaction();
            if (GetMaterialsList().Contains(materialName))
            {
                for (OdTvMaterialsIterator it = TvDatabaseId.openObject().getMaterialsIterator(); !it.done(); it.step())
                    if (it.getMaterial().openObject().getName() == materialName)
                    {
                        id = it.getMaterial();
                        break;
                    }
            }
            MM.StopTransaction(mtr);
            return id;
        }

        private List<TextBox> AddMatrixDatas(OdGeMatrix3d matr, StretchingTreeViewItem parent)
        {
            TextBox[] origin = AddPoint3D("Origin", matr.getCsOrigin(), parent);
            foreach (var pt in origin)
                pt.Tag = new MatrixData((CoordinateType)pt.Tag, MatrixData.DataType.Origin);
            TextBox[] xAxis = AddVector3D("X-Axis", matr.getCsXAxis(), parent);
            foreach (var pt in xAxis)
                pt.Tag = new MatrixData((CoordinateType)pt.Tag, MatrixData.DataType.XAxis);
            TextBox[] yAxis = AddVector3D("Y-Axis", matr.getCsYAxis(), parent);
            foreach (var pt in yAxis)
                pt.Tag = new MatrixData((CoordinateType)pt.Tag, MatrixData.DataType.YAxis);
            TextBox[] zAxis = AddVector3D("Z-Axis", matr.getCsZAxis(), parent);
            foreach (var pt in zAxis)
                pt.Tag = new MatrixData((CoordinateType)pt.Tag, MatrixData.DataType.ZAxis);
            TextBox[] translation = AddVector3D("Translation", matr.translation(), parent);
            foreach (var pt in translation)
                pt.Tag = new MatrixData((CoordinateType)pt.Tag, MatrixData.DataType.Translation);
            List<TextBox> list = new List<TextBox>();
            list.AddRange(origin);
            list.AddRange(xAxis);
            list.AddRange(yAxis);
            list.AddRange(zAxis);
            list.AddRange(translation);
            return list;
        }

        protected List<TextBox> AddMatrix(string label, OdGeMatrix3d matr, Grid grid, int[] arr)
        {
            StretchingTreeViewItem matrItm = AddTreeItem(label, grid, arr);
            return AddMatrixDatas(matr, matrItm);
        }

        protected List<TextBox> AddMatrix(string label, OdGeMatrix3d matr, StretchingTreeViewItem parent = null)
        {
            StretchingTreeViewItem matrItm = AddTreeItem(label, null, null, parent);
            return AddMatrixDatas(matr, matrItm);
        }

        protected TextBox AddLabelAndTextBox(string label, string text, Grid grid, int[] arr, bool isReadOnly = false, bool isDefValue = false, bool isIntValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(lbl, arr[0]);
            Grid.SetColumn(lbl, arr[1]);

            TextBox txt = null;
            if (isReadOnly)
            {
                txt = new TextBox()
                {
                    Text = text,
                    IsReadOnly = isReadOnly,
                    VerticalContentAlignment = VerticalAlignment.Center
                };
            }
            else if(isIntValue)
            {
                txt = new IntTextBox()
                {
                    Text = text,
                    VerticalContentAlignment = VerticalAlignment.Center
                };
            }
            else
            {
                txt = new DoubleTextBox()
                {
                    Text = text,
                    VerticalContentAlignment = VerticalAlignment.Center
                };
            }

            Grid.SetRow(txt, arr[2]);
            Grid.SetColumn(txt, arr[3]);

            grid.Children.Add(lbl);
            grid.Children.Add(txt);

            return txt;
        }

        protected TextBox AddLabelAndTextBox(string label, string text, StretchingTreeViewItem parent, bool isReadOnly = false, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetColumn(lbl, 0);
            TextBox txt = new TextBox()
            {
                Text = text,
                IsReadOnly = isReadOnly,
                VerticalContentAlignment = VerticalAlignment.Center
            };
            Grid.SetColumn(txt, 1);
            parent.Items.Add(CreateGridWithElements(2, lbl, txt));
            return txt;
        }

        protected Button AddLabelAndButton(string label, string btnName, Grid grid, int[] arr, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(lbl, arr[0]);
            Grid.SetColumn(lbl, arr[1]);

            Button btn = new Button { Content = btnName, Margin = new Thickness(0, 0, 0, 2) };
            Grid.SetRow(btn, arr[2]);
            Grid.SetColumn(btn, arr[3]);

            grid.Children.Add(lbl);
            grid.Children.Add(btn);

            return btn;
        }

        protected Button AddLabelAndButton(string label, string btnName, StretchingTreeViewItem parent, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetColumn(lbl, 0);
            Button btn = new Button { Content = btnName, Margin = new Thickness(0, 0, 0, 2) };
            Grid.SetColumn(btn, 1);
            parent.Items.Add(CreateGridWithElements(2, lbl, btn));

            return btn;
        }

        protected CheckBox AddLabelAndCheckBox(string label, bool flag, Grid grid, int[] arr, bool isReadOnly = false, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(lbl, arr[0]);
            Grid.SetColumn(lbl, arr[1]);

            CheckBox cb = new CheckBox()
            {
                IsChecked = flag,
                VerticalAlignment = VerticalAlignment.Center
            };
            if (isReadOnly)
                cb.IsHitTestVisible = false;
            Grid.SetRow(cb, arr[2]);
            Grid.SetColumn(cb, arr[3]);

            grid.Children.Add(lbl);
            grid.Children.Add(cb);

            return cb;
        }

        protected CheckBox AddLabelAndCheckBox(string label, bool flag, StretchingTreeViewItem parent, bool isReadOnly = false, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetColumn(lbl, 0);
            CheckBox cb = new CheckBox()
            {
                IsChecked = flag,
                VerticalAlignment = VerticalAlignment.Center,
                HorizontalAlignment = HorizontalAlignment.Right,
                Margin = new Thickness(0, 0, 5, 0)
            };
            if (isReadOnly)
                cb.IsHitTestVisible = false;
            Grid.SetColumn(cb, 1);
            parent.Items.Add(CreateGridWithElements(2, lbl, cb));
            return cb;
        }

        protected ComboBox AddLabelAndComboBox(string label, List<string> list, int ind, Grid grid, int[] arr, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(lbl, arr[0]);
            Grid.SetColumn(lbl, arr[1]);

            ComboBox cb = new ComboBox { VerticalContentAlignment = VerticalAlignment.Center, ItemsSource = list, SelectedIndex = ind };
            Grid.SetRow(cb, arr[2]);
            Grid.SetColumn(cb, arr[3]);

            grid.Children.Add(lbl);
            grid.Children.Add(cb);

            return cb;
        }

        protected ComboBox AddLabelAndComboBox(string label, List<string> list, int ind, StretchingTreeViewItem parent, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetColumn(lbl, 0);
            ComboBox cb = new ComboBox { VerticalContentAlignment = VerticalAlignment.Center, ItemsSource = list, SelectedIndex = ind };
            Grid.SetColumn(cb, 1);
            if (parent != null)
                parent.Items.Add(CreateGridWithElements(2, lbl, cb));
            return cb;
        }

        protected ComboBox AddLabelAndComboBox(string label, List<string> list, string text, Grid grid, int[] arr, bool isDefValue = false)
        {
            for (int i = 0; i < list.Count; i++)
                if (list[i] == text)
                    return AddLabelAndComboBox(label, list, i, grid, arr, isDefValue);
            return null;
        }

        protected ComboBox AddLabelAndComboBox(string label, List<string> list, string text, StretchingTreeViewItem parent, bool isDefValue = false)
        {
            for (int i = 0; i < list.Count; i++)
                if (list[i] == text)
                    return AddLabelAndComboBox(label, list, i, parent, isDefValue);
            return null;
        }

        protected TextBox[] AddSize(string label, OdTvDCRect rect, Grid grid, int[] arr, bool isReadOnly = false)
        {
            StretchingTreeViewItem itm = AddTreeItem(label, grid, arr);
            Grid newGrid = CreateGrid(2, 4);
            TextBox xMin = AddLabelAndTextBox("xMin:", rect.xmin.ToString(), newGrid, new[] { 0, 0, 0, 1 }, isReadOnly, false, true);
            xMin.Tag = DcSizeType.xMin;
            TextBox xMax = AddLabelAndTextBox("xMax:", rect.xmax.ToString(), newGrid, new[] { 1, 0, 1, 1 }, isReadOnly, false, true);
            xMax.Tag = DcSizeType.xMax;
            TextBox yMin = AddLabelAndTextBox("yMin:", rect.ymin.ToString(), newGrid, new[] { 2, 0, 2, 1 }, isReadOnly, false, true);
            yMin.Tag = DcSizeType.yMin;
            TextBox yMax = AddLabelAndTextBox("yMax:", rect.ymax.ToString(), newGrid, new[] { 3, 0, 3, 1 }, isReadOnly, false, true);
            yMax.Tag = DcSizeType.yMax;
            itm.Items.Add(newGrid);

            return new[] { xMin, xMax, yMin, yMax };
        }

        protected StretchingTreeViewItem AddTreeItem(string label, Grid grid, int[] arr, StretchingTreeViewItem parent = null)
        {

            StretchingTreeViewItem tItm = new StretchingTreeViewItem { Header = label };
            if (parent != null)
                parent.Items.Add(tItm);
            else
            {
                StretchingTreeView tree = new StretchingTreeView()
                {
                    HorizontalAlignment = HorizontalAlignment.Stretch,
                    HorizontalContentAlignment = HorizontalAlignment.Stretch,
                    VerticalAlignment = VerticalAlignment.Stretch,
                    VerticalContentAlignment = VerticalAlignment.Stretch,
                    Margin = new Thickness(0, 0, 0, 3)
                };
                tree.Items.Add(tItm);
                Grid.SetRow(tree, arr[0]);
                Grid.SetColumn(tree, arr[1]);
                Grid.SetColumnSpan(tree, 3);
                grid.Children.Add(tree);
            }
            return tItm;
        }

        protected StretchingTreeViewItem AddTreeItem(string label, StretchingTreeView tree)
        {
            StretchingTreeViewItem tItm = new StretchingTreeViewItem { Header = label };
            if(tree != null)
                tree.Items.Add(tItm);
            return tItm;
        }

        protected Grid CreateGrid(int countOfColumns, int countOfRows)
        {
            Grid grid = new Grid();

            for (int i = 0; i < countOfColumns; i++)
                grid.ColumnDefinitions.Add(new ColumnDefinition());

            for (int i = 0; i < countOfRows; i++)
                grid.RowDefinitions.Add(new RowDefinition());

            return grid;
        }

        private string GetDoubleStringValue(double value)
        {
            string str = "0";
            if (Math.Abs(value) > 0.0001)
                str = value.ToString();
            return str;
        }

        protected TextBox[] GetXyz(StretchingTreeViewItem parent, OdGePoint3d pnt, bool isReadOnly = false)
        {
            Grid newGrid = CreateGrid(2, 3);
            TextBox x = AddLabelAndTextBox("X:", GetDoubleStringValue(pnt.x), newGrid, new[] { 0, 0, 0, 1 }, isReadOnly);
            x.Tag = CoordinateType.X;
            TextBox y = AddLabelAndTextBox("Y:", GetDoubleStringValue(pnt.y), newGrid, new[] { 1, 0, 1, 1 }, isReadOnly);
            y.Tag = CoordinateType.Y;
            TextBox z = AddLabelAndTextBox("Z:", GetDoubleStringValue(pnt.z), newGrid, new[] { 2, 0, 2, 1 }, isReadOnly);
            z.Tag = CoordinateType.Z;
            parent.Items.Add(newGrid);
            return new[] { x, y, z };
        }

        protected TextBox[] GetXyz(string label, StretchingTreeView tree, OdGePoint3d pnt, bool isReadOnly = false)
        {
            Grid newGrid = CreateGrid(2, 3);
            TextBox x = AddLabelAndTextBox("X:", GetDoubleStringValue(pnt.x), newGrid, new[] { 0, 0, 0, 1 }, isReadOnly);
            x.Tag = CoordinateType.X;
            TextBox y = AddLabelAndTextBox("Y:", GetDoubleStringValue(pnt.y), newGrid, new[] { 1, 0, 1, 1 }, isReadOnly);
            y.Tag = CoordinateType.Y;
            TextBox z = AddLabelAndTextBox("Z:", GetDoubleStringValue(pnt.z), newGrid, new[] { 2, 0, 2, 1 }, isReadOnly);
            z.Tag = CoordinateType.Z;
            StretchingTreeViewItem tItm = new StretchingTreeViewItem { Header = label, Focusable = false };
            tree.Items.Add(tItm);
            tItm.Items.Add(newGrid);
            return new[] { x, y, z };
        }

        protected TextBox[] GetXy(StretchingTreeViewItem parent, OdGePoint2d pnt, bool isReadOnly = false)
        {
            Grid newGrid = CreateGrid(2, 3);
            TextBox x = AddLabelAndTextBox("X:", GetDoubleStringValue(pnt.x), newGrid, new[] { 0, 0, 0, 1 }, isReadOnly);
            x.Tag = CoordinateType.X;
            TextBox y = AddLabelAndTextBox("Y:", GetDoubleStringValue(pnt.y), newGrid, new[] { 1, 0, 1, 1 }, isReadOnly);
            y.Tag = CoordinateType.Y;
            parent.Items.Add(newGrid);
            return new[] { x, y };
        }

        protected TextBox[] GetXyz(StretchingTreeViewItem parent, OdGeVector3d vec, bool isReadOnly = false)
        {
            Grid newGrid = CreateGrid(2, 3);
            TextBox x = AddLabelAndTextBox("X:", GetDoubleStringValue(vec.x), newGrid, new[] { 0, 0, 0, 1 }, isReadOnly);
            x.Tag = CoordinateType.X;
            TextBox y = AddLabelAndTextBox("Y:", GetDoubleStringValue(vec.y), newGrid, new[] { 1, 0, 1, 1 }, isReadOnly);
            y.Tag = CoordinateType.Y;
            TextBox z = AddLabelAndTextBox("Z:", GetDoubleStringValue(vec.z), newGrid, new[] { 2, 0, 2, 1 }, isReadOnly);
            z.Tag = CoordinateType.Z;
            parent.Items.Add(newGrid);
            return new[] { x, y, z };
        }

        protected TextBox[] GetXy(StretchingTreeViewItem parent, OdGeVector2d vec, bool isReadOnly = false)
        {
            Grid newGrid = CreateGrid(2, 3);
            TextBox x = AddLabelAndTextBox("X:", GetDoubleStringValue(vec.x), newGrid, new[] { 0, 0, 0, 1 }, isReadOnly);
            x.Tag = CoordinateType.X;
            TextBox y = AddLabelAndTextBox("Y:", GetDoubleStringValue(vec.y), newGrid, new[] { 1, 0, 1, 1 }, isReadOnly);
            y.Tag = CoordinateType.Y;
            parent.Items.Add(newGrid);
            return new[] { x, y };
        }

        protected TextBox[] AddPoint3D(string label, OdGePoint3d pnt, Grid grid, int[] arr, bool isReadOny = false)
        {
            return GetXyz(AddTreeItem(label, grid, arr), pnt, isReadOny);
        }
        protected TextBox[] AddPoint3D(string label, OdGePoint3d pnt, StretchingTreeViewItem parent,
            bool isReadOny = false)
        {
            return GetXyz(AddTreeItem(label, null, null, parent), pnt, isReadOny);
        }

        protected TextBox[] AddPoint3D(string label, OdGePoint3d pnt, StretchingTreeView tree,
            bool isReadOny = false)
        {
            return GetXyz(label, tree, pnt, isReadOny);
        }

        protected TextBox[] AddPoint2D(string label, OdGePoint2d pnt, Grid grid, int[] arr, bool isReadOny = false)
        {
            return GetXy(AddTreeItem(label, grid, arr), pnt, isReadOny);
        }

        protected TextBox[] AddPoint2D(string label, OdGePoint2d pnt, StretchingTreeViewItem parent,
            bool isReadOny = false)
        {
            return GetXy(AddTreeItem(label, null, null, parent), pnt, isReadOny);
        }

        protected TextBox[] AddVector3D(string label, OdGeVector3d vec, Grid grid, int[] arr, bool isReadOny = false)
        {
            return GetXyz(AddTreeItem(label, grid, arr), vec, isReadOny);
        }

        protected TextBox[] AddVector3D(string label, OdGeVector3d vec, StretchingTreeViewItem parent,
            bool isReadOny = false)
        {
            return GetXyz(AddTreeItem(label, null, null, parent), vec, isReadOny);
        }

        protected TextBox[] AddVector2D(string label, OdGeVector2d vec, Grid grid, int[] arr, bool isReadOny = false)
        {
            return GetXy(AddTreeItem(label, grid, arr), vec, isReadOny);
        }

        protected TextBox[] AddVector2D(string label, OdGeVector2d vec, StretchingTreeViewItem parent,
            bool isReadOny = false)
        {
            return GetXy(AddTreeItem(label, null, null, parent), vec, isReadOny);
        }

        protected OdGePoint3d SetPointCoordByType(OdGePoint3d curPnt, CoordinateType type, string text)
        {
            text = text.Replace(".", ",");
            OdGePoint3d pnt = new OdGePoint3d(curPnt);
            double val = Convert.ToDouble(text);
            if (type == CoordinateType.X && !curPnt.x.Equals(val))
                pnt.x = val;
            else if (type == CoordinateType.Y && !curPnt.y.Equals(val))
                pnt.y = val;
            else if (type == CoordinateType.Z && !curPnt.z.Equals(val))
                pnt.z = val;
            return pnt;
        }

        protected OdGePoint2d SetPointCoordByType(OdGePoint2d curPnt, CoordinateType type, string text)
        {
            text = text.Replace(".", ",");
            OdGePoint2d pnt = new OdGePoint2d(curPnt);
            double val = Convert.ToDouble(text);
            if (type == CoordinateType.X && !curPnt.x.Equals(val))
                pnt.x = val;
            else if (type == CoordinateType.Y && !curPnt.y.Equals(val))
                pnt.y = val;
            return pnt;
        }

        protected OdGeVector3d SetVectorCoordByType(OdGeVector3d curVec, CoordinateType type, string text)
        {
            text = text.Replace(".", ",");
            OdGeVector3d vec = new OdGeVector3d(curVec);
            double val = Convert.ToDouble(text);
            if (type == CoordinateType.X && !curVec.x.Equals(val))
                vec.x = val;
            else if (type == CoordinateType.Y && !curVec.y.Equals(val))
                vec.y = val;
            else if (type == CoordinateType.Z && !curVec.z.Equals(val))
                vec.z = val;
            return vec;
        }

        protected OdGeVector2d SetVectorCoordByType(OdGeVector2d curVec, CoordinateType type, string text)
        {
            text = text.Replace(".", ",");
            OdGeVector2d vec = new OdGeVector2d(curVec);
            double val = Convert.ToDouble(text);
            if (type == CoordinateType.X && !curVec.x.Equals(val))
                vec.x = val;
            else if (type == CoordinateType.Y && !curVec.y.Equals(val))
                vec.y = val;
            return vec;
        }

        private void TextBox_OnEnterPressed(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                TextBox tb = sender as TextBox;
                Keyboard.ClearFocus();
            }
        }

        protected List<string> GetTextStylesList()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            List<string> list = new List<string>() { "" };
            OdTvTextStylesIterator it = TvDatabaseId.openObject().getTextStylesIterator();
            while (!it.done())
            {
                list.Add(it.getTextStyle().openObject().getName());
                it.step();
            }
            MM.StopTransaction(mtr);
            return list;
        }

        protected List<string> GetLayersList()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            List<string> list = new List<string>() { "" };
            OdTvLayersIterator it = TvDatabaseId.openObject().getLayersIterator();
            while (!it.done())
            {
                list.Add(it.getLayer().openObject().getName());
                it.step();
            }
            MM.StopTransaction(mtr);
            return list;
        }

        protected List<string> GetLinetypesList(bool isLayer = false)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            List<string> list;
            if (!isLayer)
            {
                list = new List<string>()
                {
                    "",
                    "ByBlock",
                    "ByLayer",
                    "Solid",
                    "DashDot",
                    "Dashed",
                    "Dotted",
                    "Dash2Dot",
                    "Dash3Dot",
                    "LongDash",
                    "LongDashShortDash",
                    "LongDash2ShortDash"
                };
            }
            else
                list = new List<string>() { "" };

            OdTvLinetypesIterator it = TvDatabaseId.openObject().getLinetypesIterator();
            while (!it.done())
            {
                list.Add(it.getLinetype().openObject().getName());
                it.step();
            }

            MM.StopTransaction(mtr);
            return list;
        }

        protected List<string> GetMaterialsList()
        {
            MemoryTransaction mtr = MM.StartTransaction();
            List<string> list = new List<string>() { "" };
            OdTvMaterialsIterator it = TvDatabaseId.openObject().getMaterialsIterator();
            while (!it.done())
            {
                list.Add(it.getMaterial().openObject().getName());
                it.step();
            }
            MM.StopTransaction(mtr);
            return list;
        }

        protected Window CreateDialog(string title, Size size, UIElement panel)
        {
            Grid mainGrid = new Grid();
            mainGrid.RowDefinitions.Add(new RowDefinition());
            mainGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

            ScrollViewer scroll = new ScrollViewer() { VerticalScrollBarVisibility = ScrollBarVisibility.Auto };
            scroll.Content = mainGrid;
            scroll.ScrollChanged += ScrollDialog_ScrollChanged;
            scroll.PreviewMouseWheel += Scroll_PreviewMouseWheel;
            scroll.Content = panel;

            Grid.SetRow(scroll, 0);

            StackPanel btnPanel = new StackPanel()
            {
                Orientation = Orientation.Horizontal,
                HorizontalAlignment = HorizontalAlignment.Right,
                Margin = new Thickness(5)
            };
            Button ok = new Button { Content = "Ok", IsDefault = true, Height = 25, Width = 70 };
            Button cancel = new Button { Content = "Cancel", IsCancel = true, Margin = new Thickness(10, 0, 0, 0), Height = 25, Width = 70 };
            btnPanel.Children.Add(ok);
            btnPanel.Children.Add(cancel);
            Grid.SetRow(btnPanel, 1);

            mainGrid.Children.Add(scroll);
            mainGrid.Children.Add(btnPanel);
            Window wnd = new Window
            {
                WindowStartupLocation = WindowStartupLocation.CenterScreen,
                MinWidth = size.Width,
                MinHeight = size.Height,
                Width = size.Width,
                Height = size.Height,
                Icon = Application.Current.Resources["OdalogoImg"] as BitmapImage,
                Title = title,
                Content = mainGrid
            };

            ok.Tag = wnd;
            ok.Click += Ok_Click;

            return wnd;
        }

        private void Scroll_PreviewMouseWheel(object sender, MouseWheelEventArgs e)
        {
            ScrollViewer scv = (ScrollViewer)sender;
            scv.ScrollToVerticalOffset(scv.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        protected virtual void ScrollDialog_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
        }

        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            if (btn == null)
                return;
            Window wnd = (Window)btn.Tag;
            if (wnd != null)
                wnd.DialogResult = true;
        }

        protected void SetMatrix(OdGeMatrix3d matr, MatrixData data, string value)
        {
            switch (data.Data)
            {
                case MatrixData.DataType.Origin:
                    matr.setCoordSystem(SetPointCoordByType(matr.getCsOrigin(), data.Type, value), matr.getCsXAxis(), matr.getCsYAxis(), matr.getCsZAxis());
                    break;
                case MatrixData.DataType.XAxis:
                    matr.setCoordSystem(matr.getCsOrigin(), SetVectorCoordByType(matr.getCsXAxis(), data.Type, value), matr.getCsYAxis(), matr.getCsZAxis());
                    break;
                case MatrixData.DataType.YAxis:
                    matr.setCoordSystem(matr.getCsOrigin(), matr.getCsXAxis(), SetVectorCoordByType(matr.getCsYAxis(), data.Type, value), matr.getCsZAxis());
                    break;
                case MatrixData.DataType.ZAxis:
                    matr.setCoordSystem(matr.getCsOrigin(), matr.getCsXAxis(), matr.getCsYAxis(), SetVectorCoordByType(matr.getCsZAxis(), data.Type, value));
                    break;
                case MatrixData.DataType.Translation:
                    matr.setTranslation(SetVectorCoordByType(matr.translation(), data.Type, value));
                    break;
            }
        }

        protected bool CheckCountOfObject(int cnt)
        {
            if (cnt > 500 && MessageBox.Show("Count of objects is" + cnt + ",\n Do you want to continue?"
                    , "Large number of objects", MessageBoxButtons.OKCancel
                    , MessageBoxIcon.Warning) == DialogResult.Cancel)
                return false;
            return true;
        }
    }
}

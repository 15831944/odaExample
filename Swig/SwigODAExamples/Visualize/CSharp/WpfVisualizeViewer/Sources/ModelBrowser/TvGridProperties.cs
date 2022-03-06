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
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvGridProperties : TvBaseGeometryProperties
    {
        private enum PointType
        {
            Origin,
            FirstPoint,
            SecondPoint
        }

        private struct NodeData
        {
            public CoordinateType CoordType;
            public PointType PType;

            public NodeData(CoordinateType ctype, PointType ptype)
            {
                CoordType = ctype;
                PType = ptype;
            }
        }

        private enum TextType
        {
            FirstCount,
            SecondCount,
            XDivide,
            YDivide
        }

        public TvGridProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGridData grid = GeomId.openAsGrid();
            int row = 0;
            TextBox[] origin = AddPoint3D("Origin", grid.getOrigin(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in origin)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Origin);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] fPt = AddPoint3D("First point", grid.getFirstPoint(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in fPt)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.FirstPoint);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] sPt = AddPoint3D("Second point", grid.getSecondPoint(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in sPt)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.SecondPoint);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox fCnt = AddLabelAndTextBox("First count:", grid.getFirstCount().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            fCnt.Tag = TextType.FirstCount;
            fCnt.LostKeyboardFocus += TextType_LostKeyboardFocus;
            TextBox sCnt = AddLabelAndTextBox("Second count:", grid.getSecondCount().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            sCnt.Tag = TextType.SecondCount;
            sCnt.LostKeyboardFocus += TextType_LostKeyboardFocus;
            List<string> list = new List<string>() { "Quadratic", "Radial" };
            ComboBox type = AddLabelAndComboBox("Type:", list, (int)grid.getType(), MainGrid, new[] { row, 0, row++, 1 });
            type.SelectionChanged += Type_SelectionChanged;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            OdTvColorDef colorDef = new OdTvColorDef();
            bool enabled;
            int div1, div2;
            grid.getMinorGridParams(out enabled, colorDef, out div1, out div2);
            CheckBox isEnabled = AddLabelAndCheckBox("Is enabled:", enabled, misc);
            isEnabled.Click += IsEnabled_Click;
            Colorpicker color = AddColorDef("Color:", colorDef, misc);
            color.ColorChanged += Color_ColorChanged;
            TextBox xDiv = AddLabelAndTextBox("X divide:", div1.ToString(), misc);
            xDiv.Tag = TextType.XDivide;
            xDiv.LostKeyboardFocus += TextType_LostKeyboardFocus;
            TextBox yDiv = AddLabelAndTextBox("Y divide:", div2.ToString(), misc);
            yDiv.Tag = TextType.YDivide;
            yDiv.LostKeyboardFocus += TextType_LostKeyboardFocus;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);
            MM.StopTransaction(mtr);

        }

        private void Color_ColorChanged(object sender, OdTvColorDef newColor)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGridData grid = GeomId.openAsGrid();
            OdTvColorDef colorDef = new OdTvColorDef();
            bool enabled;
            int div1, div2;
            grid.getMinorGridParams(out enabled, colorDef, out div1, out div2);
            if(colorDef != newColor)
            {
                grid.setMinorGridParams(enabled, newColor, div1, div2);
                Update();
            }
            MM.StopTransaction(mtr);

        }

        private void IsEnabled_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGridData grid = GeomId.openAsGrid();
            OdTvColorDef colorDef = new OdTvColorDef();
            bool enabled;
            int div1, div2;
            grid.getMinorGridParams(out enabled, colorDef, out div1, out div2);
            grid.setMinorGridParams(cb.IsChecked == true, colorDef, div1, div2);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Type_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGridData grid = GeomId.openAsGrid();
            grid.setType((OdTvGridData.Type) cb.SelectedIndex);
            Update();
            MM.StopTransaction(mtr);
        }

        private void TextType_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGridData grid = GeomId.openAsGrid();
            int val = int.Parse(tb.Text);
            OdTvColorDef colorDef = new OdTvColorDef();
            bool enabled;
            int div1, div2;
            grid.getMinorGridParams(out enabled, colorDef, out div1, out div2);
            switch ((TextType)tb.Tag)
            {
                case TextType.FirstCount:
                    if (val != grid.getFirstCount())
                        grid.setFirstCount(val);
                    break;
                case TextType.SecondCount:
                    if (val != grid.getSecondCount())
                        grid.setSecondCount(val);
                    break;
                case TextType.XDivide:
                    if (val != div1)
                        grid.setMinorGridParams(enabled, colorDef, val, div2);
                    break;
                case TextType.YDivide:
                    if (val != div2)
                        grid.setMinorGridParams(enabled, colorDef, div1, val);
                    break;
            }

            Update();
            MM.StopTransaction(mtr);

        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGridData grid = GeomId.openAsGrid();
            NodeData data = (NodeData)tb.Tag;

            switch (data.PType)
            {
                case PointType.Origin:
                    OdGePoint3d newPt = SetPointCoordByType(grid.getOrigin(), data.CoordType, tb.Text);
                    if (newPt != grid.getOrigin())
                        grid.setOrigin(newPt);
                    break;
                case PointType.FirstPoint:
                    OdGePoint3d newFpt = SetPointCoordByType(grid.getFirstPoint(), data.CoordType, tb.Text);
                    if (newFpt != grid.getFirstPoint())
                        grid.setFirstPoint(newFpt);
                    break;
                case PointType.SecondPoint:
                    OdGePoint3d newSpt = SetPointCoordByType(grid.getSecondPoint(), data.CoordType, tb.Text);
                    if (newSpt != grid.getSecondPoint())
                        grid.setSecondPoint(newSpt);
                    break;
            }

            Update();
            MM.StopTransaction(mtr);
        }
    }
}

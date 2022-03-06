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
using System.Windows;
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvTextProperties : TvBaseGeometryProperties
    {

        private enum PointType
        {
            Position,
            Normal,
            AlighmentPoint
        }

        private struct NodeData
        {
            public CoordinateType CoordType;
            public PointType Type;

            public NodeData(CoordinateType ctype, PointType ptype)
            {
                CoordType = ctype;
                Type = ptype;
            }
        }

        private enum TextType
        {
            Text,
            Rotation,
            TextSize,
            WidthFactor
        }

        private enum ComboboxType
        {
            Alignment,
            Underlined,
            Overlined,
            Striked,
            TextStyle
        }

        public TvTextProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextData txt = GeomId.openAsText();
            int row = 0;
            TextBox text = AddSimpleText("Text:", txt.getString(), MainGrid, new[] { row, 0, row++, 1 });
            text.Tag = TextType.Text;
            text.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            TextBox[] position = AddPoint3D("Position", txt.getPosition(), MainGrid, new[] { row++, 0 });
            foreach (var p in position)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Position);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }
            TextBox[] normal = AddVector3D("Normal", txt.getNormal(), MainGrid, new[] { row++, 0 });
            foreach (var p in normal)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Normal);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }
            List<string> alighList = new List<string>()
            {
                "Left", "Center", "Right", "Aligned", "Middle", "Fit", "TopLeft", "TopCenter", "TopRight",
                "MiddleLeft", "MiddleCenter", "MiddleRight", "BottomLeft", "BottomCenter", "BottomRight"
            };
            ComboBox align = AddLabelAndComboBox("Alignment mode:", alighList, (int)txt.getAlignmentMode(), MainGrid, new[] { row, 0, row++, 1 });
            align.Tag = ComboboxType.Alignment;
            align.SelectionChanged += ComboBox_SelectionChanged;
            TextBox rotation = AddLabelAndTextBox("Rotation:", txt.getRotation().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            rotation.Tag = TextType.Rotation;
            rotation.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            TextBox[] alignPoint = AddPoint3D("Alignment point", txt.getAlignmentPoint(), MainGrid, new[] { row++, 0 });
            foreach (var p in alignPoint)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.AlighmentPoint);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }
            TextBox textSize = AddLabelAndTextBox("Text size:", txt.getTextSize().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            textSize.Tag = TextType.TextSize;
            textSize.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            TextBox witdhFact = AddLabelAndTextBox("Width factor:", txt.getWidthFactor().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            witdhFact.Tag = TextType.WidthFactor;
            witdhFact.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            CheckBox nonRot = AddLabelAndCheckBox("Non rotatable:", txt.getNonRotatable(), MainGrid, new[] { row, 0, row++, 1 });
            nonRot.Click += NonRot_Click;
            List<string> list = new List<string>() { "Inherit", "On", "Off" };
            ComboBox underlined = AddLabelAndComboBox("Underlined:", list, (int)txt.getUnderlined(), MainGrid, new[] { row, 0, row++, 1 });
            underlined.Tag = ComboboxType.Underlined;
            underlined.SelectionChanged += ComboBox_SelectionChanged;
            ComboBox overlined = AddLabelAndComboBox("Overlined:", list, (int)txt.getOverlined(), MainGrid, new[] { row, 0, row++, 1 });
            overlined.Tag = ComboboxType.Overlined;
            overlined.SelectionChanged += ComboBox_SelectionChanged;
            ComboBox striked = AddLabelAndComboBox("Striked:", list, (int)txt.getStriked(), MainGrid, new[] { row, 0, row++, 1 });
            striked.Tag = ComboboxType.Striked;
            striked.SelectionChanged += ComboBox_SelectionChanged;
            ComboBox txtStyle = AddTextStyleDef("Text style:", txt.getTextStyle(), MainGrid, new[] { row, 0, row++, 1 });
            txtStyle.Tag = ComboboxType.TextStyle;
            txtStyle.SelectionChanged += ComboBox_SelectionChanged;

            StretchingTreeViewItem common = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(common);
            MM.StopTransaction(mtr);

        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextData txt = GeomId.openAsText();
            switch ((ComboboxType)cb.Tag)
            {
                case ComboboxType.Alignment:
                    txt.setAlignmentMode((OdTvTextStyle.AlignmentType)cb.SelectedIndex);
                    break;
                case ComboboxType.Underlined:
                    txt.setUnderlined((OdTvTextData.StrokeState)cb.SelectedIndex);
                    break;
                case ComboboxType.Overlined:
                    txt.setOverlined((OdTvTextData.StrokeState)cb.SelectedIndex);
                    break;
                case ComboboxType.Striked:
                    txt.setStriked((OdTvTextData.StrokeState)cb.SelectedIndex);
                    break;
                case ComboboxType.TextStyle:
                    txt.setTextStyle(GetTextStyleDef(cb.SelectedItem.ToString()));
                    break;
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void NonRot_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsText().setNonRotatable(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextData txt = GeomId.openAsText();
            NodeData data = (NodeData)tb.Tag;
            switch (data.Type)
            {
                case PointType.Position:
                    {
                        OdGePoint3d newPt = SetPointCoordByType(txt.getPosition(), data.CoordType, tb.Text);
                        if (newPt != txt.getPosition())
                            txt.setPosition(newPt);
                        break;
                    }
                case PointType.Normal:
                    {
                        OdGeVector3d newVec = SetVectorCoordByType(txt.getNormal(), data.CoordType, tb.Text);
                        if (newVec != txt.getNormal())
                            txt.setNormal(newVec);
                        break;
                    }
                case PointType.AlighmentPoint:
                    {
                        OdGePoint3d newPt = SetPointCoordByType(txt.getAlignmentPoint(), data.CoordType, tb.Text);
                        if (newPt != txt.getAlignmentPoint())
                            txt.setAlignmentPoint(newPt);
                        break;
                    }
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void TextBox_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextData txt = GeomId.openAsText();
            switch ((TextType)tb.Tag)
            {
                case TextType.Text:
                    if (txt.getString() != tb.Text)
                        txt.setString(tb.Text);
                    break;
                case TextType.Rotation:
                    if (!txt.getRotation().Equals(double.Parse(tb.Text)))
                        txt.setRotation(double.Parse(tb.Text));
                    break;
                case TextType.TextSize:
                    if (!txt.getTextSize().Equals(double.Parse(tb.Text)))
                        txt.setTextSize(double.Parse(tb.Text));
                    break;
                case TextType.WidthFactor:
                    if (!txt.getWidthFactor().Equals(double.Parse(tb.Text)))
                        txt.setWidthFactor(double.Parse(tb.Text));
                    break;
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private TextBox AddSimpleText(string label, string text, Grid grid, int[] arr)
        {
            Label lbl = new Label() { Content = label };
            Grid.SetRow(lbl, arr[0]);
            Grid.SetColumn(lbl, arr[1]);
            TextBox txt = new TextBox()
            {
                Text = text,
                VerticalContentAlignment = VerticalAlignment.Center
            };
            Grid.SetRow(txt, arr[2]);
            Grid.SetColumn(txt, arr[3]);
            grid.Children.Add(lbl);
            grid.Children.Add(txt);
            return txt;
        }
    }
}

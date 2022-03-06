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
using System.Windows.Controls;
using System.Windows.Forms;
using Teigha.Core;
using Teigha.Visualize;
using CheckBox = System.Windows.Controls.CheckBox;
using ComboBox = System.Windows.Controls.ComboBox;
using TextBox = System.Windows.Controls.TextBox;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvInsertProperties : BasePaletteProperties
    {
        private OdTvEntityId _insertId;

        private enum TextType
        {
            Position,
            Normal,
            Rotation,
            ScaleFactor,
            Lineweight
        }

        struct ControlData
        {
            public TextType ProperyType;
            public CoordinateType CoordType;

            public ControlData(TextType propType, CoordinateType coordType)
            {
                ProperyType = propType;
                CoordType = coordType;
            }
        }

        public TvInsertProperties(OdTvEntityId entityId, int countOfChild, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            if (entityId == null || entityId.isNull())
                return;
            _insertId = entityId;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInsert ins = entityId.openObjectAsInsert();
            int row = 0;
            AddLabelAndTextBox("Name:", ins.getName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Block:", ins.getBlock().openObject().getName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            TextBox[] pos = AddPoint3D("Position", ins.getPosition(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var pt in pos)
            {
                pt.Tag = new ControlData(TextType.Position, (CoordinateType)pt.Tag);
                pt.LostKeyboardFocus += TextType_LostKeyboardFocus;
            }
            TextBox[] normal = AddVector3D("Normal", ins.getNormal(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var pt in normal)
            {
                pt.Tag = new ControlData(TextType.Normal, (CoordinateType)pt.Tag);
                pt.LostKeyboardFocus += TextType_LostKeyboardFocus;
            }

            TextBox rotation = AddLabelAndTextBox("Rotation:", ins.getRotation().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            rotation.Tag = new ControlData() { ProperyType = TextType.Rotation };
            rotation.LostKeyboardFocus += TextType_LostKeyboardFocus;

            StretchingTreeViewItem scaleFactItm = AddTreeItem("Scale factor", MainGrid, new[] { row++, 0 });
            OdGeScale3d scale = ins.getScaleFactors();
            TextBox xScale = AddLabelAndTextBox("X scale:", scale.sx.ToString(), scaleFactItm);
            xScale.Tag = new ControlData(TextType.ScaleFactor, CoordinateType.X);
            xScale.LostKeyboardFocus += TextType_LostKeyboardFocus;
            TextBox yScale = AddLabelAndTextBox("Y scale:", scale.sy.ToString(), scaleFactItm);
            yScale.Tag = new ControlData(TextType.ScaleFactor, CoordinateType.Y);
            yScale.LostKeyboardFocus += TextType_LostKeyboardFocus;
            TextBox zScale = AddLabelAndTextBox("Z scale:", scale.sz.ToString(), scaleFactItm);
            zScale.Tag = new ControlData(TextType.ScaleFactor, CoordinateType.Z);
            zScale.LostKeyboardFocus += TextType_LostKeyboardFocus;

            List<TextBox> transform = AddMatrix("Block transform", ins.getBlockTransform(), MainGrid, new[] { row++, 0 });
            transform.ForEach(o => o.LostKeyboardFocus += Transform_LostKeyboardFocus);

            StretchingTreeViewItem secItm = AddTreeItem("Secondary properties", MainGrid, new[] { row++, 0 });
            Grid grid = CreateGrid(2, 5);
            secItm.Items.Add(grid);
            int secRow = 0;
            Colorpicker color = AddColorDef("Color:", ins.getColor(), new[] { secRow, 0, secRow++, 1 }, grid);
            color.ColorChanged += Color_ColorChanged;
            TextBox lineweight = AddLineweightDef("Lineweight:", ins.getLineWeight(), grid, new[] { secRow, 0, secRow++, 1 });
            lineweight.Tag = new ControlData() { ProperyType = TextType.Lineweight };
            lineweight.LostKeyboardFocus += TextType_LostKeyboardFocus;
            ComboBox layer = AddLayerDef("Layer:", ins.getLayer(), grid, new[] { secRow, 0, secRow++, 1 });
            layer.SelectionChanged += Layer_SelectionChanged;
            ComboBox linetype = AddLinetypeDef("Linetype:", ins.getLinetype(), grid, new[] { secRow, 0, secRow++, 1 });
            linetype.SelectionChanged += Linetype_SelectionChanged;
            CheckBox visibility = AddVisibilityDef("Visibility:", ins.getVisibility(), grid, new[] { secRow, 0, secRow, 1 });
            visibility.Click += Visibility_Click;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row, 0 });
            AddLabelAndTextBox("Count of child:", countOfChild.ToString(), misc, true);
            MM.StopTransaction(mtr);
        }

        private void Visibility_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInsert ins = _insertId.openObjectAsInsert(OpenMode.kForWrite);
            ins.setVisibility(new OdTvVisibilityDef(cb.IsChecked == true));
            Update();
            MM.StopTransaction(mtr);
        }

        private void Linetype_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInsert ins = _insertId.openObjectAsInsert();
            if (GetLinetypeName(ins.getLinetype()) != cb.SelectedItem.ToString())
                ins.setLinetype(GetLinetypeDef(cb.SelectedItem.ToString()));
            Update();
            MM.StopTransaction(mtr);
        }

        private void Layer_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInsert ins = _insertId.openObjectAsInsert();
            if (GetLayerName(ins.getLayer()) != cb.SelectedItem.ToString())
                ins.setLayer(GetLayerDef(cb.SelectedItem.ToString()));
            Update();
            MM.StopTransaction(mtr);
        }

        private void Color_ColorChanged(object sender, OdTvColorDef newColor)
        {
            Colorpicker cp = sender as Colorpicker;
            if (cp == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInsert ins = _insertId.openObjectAsInsert();
            if (ins.getColor() != newColor)
                ins.setColor(newColor);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Transform_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            DoubleTextBox dtb = sender as DoubleTextBox;
            if (dtb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInsert ins = _insertId.openObjectAsInsert();
            OdGeMatrix3d matr = ins.getBlockTransform();
            SetMatrix(matr, (MatrixData)dtb.Tag, dtb.Text);
            try
            {
                ins.setBlockTransform(matr);
                Update();
            }
            catch (Exception)
            {
                MessageBox.Show("Invalid parameters of block transform", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void TextType_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            ControlData data = (ControlData)tb.Tag;
            OdTvInsert ins = _insertId.openObjectAsInsert(OpenMode.kForWrite);
            switch (data.ProperyType)
            {
                case TextType.Position:
                    {
                        OdGePoint3d newPt = SetPointCoordByType(ins.getPosition(), data.CoordType, tb.Text);
                        if (newPt != ins.getPosition())
                            ins.setPosition(newPt);
                        break;
                    }
                case TextType.Normal:
                    {
                        OdGeVector3d newVec = SetVectorCoordByType(ins.getNormal(), data.CoordType, tb.Text);
                        if (newVec != ins.getNormal())
                            ins.setNormal(newVec);
                        break;
                    }
                case TextType.Rotation:
                    {
                        double val = double.Parse(tb.Text);
                        if (!ins.getRotation().Equals(val))
                            ins.setRotation(val);
                        break;
                    }
                case TextType.ScaleFactor:
                    {
                        OdGeScale3d scale = ins.getScaleFactors();
                        OdGePoint3d temp = SetPointCoordByType(new OdGePoint3d(scale.sx, scale.sy, scale.sz),
                            data.CoordType, tb.Text);
                        OdGeScale3d newScale = new OdGeScale3d(temp.x, temp.y, temp.z);
                        if (scale != newScale)
                            ins.setScaleFactors(newScale);
                        break;
                    }
                case TextType.Lineweight:
                    {
                        byte val = byte.Parse(tb.Text);
                        if (ins.getLineWeight().getValue() != val)
                            ins.setLineWeight(new OdTvLineWeightDef(val));
                        break;
                    }
            }
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

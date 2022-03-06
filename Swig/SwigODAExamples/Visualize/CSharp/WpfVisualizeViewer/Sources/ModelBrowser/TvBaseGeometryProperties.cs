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
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvBaseGeometryProperties : BasePaletteProperties
    {
        protected OdTvGeometryDataId GeomId;

        private enum ComboboxType
        {
            Layer,
            Linetype,
            DisplayMode
        }

        private enum TextType
        {
            Lineweight,
            Transparency,
            LinetypeScale
        }

        public TvBaseGeometryProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            if (geomId == null || !geomId.isValid())
                return;
            GeomId = geomId;
        }

        protected void GetProperties(StretchingTreeViewItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryData geom = GeomId.openObject();
            Grid newGrid = CreateGrid(2, 9);
            parent.Items.Add(newGrid);
            int row = 0;
            Colorpicker color = AddColorDef("Color:", geom.getColor(), new[] { row, 0, row++, 1 }, newGrid);
            color.ColorChanged += Color_ColorChanged;
            ComboBox layer = AddLayerDef("Layer:", geom.getLayer(), newGrid, new[] { row, 0, row++, 1 });
            layer.Tag = ComboboxType.Layer;
            layer.SelectionChanged += Combobox_SelectionChanged;
            ComboBox linetype = AddLinetypeDef("Linetype:", geom.getLinetype(), newGrid, new[] { row, 0, row++, 1 });
            linetype.Tag = ComboboxType.Linetype;
            linetype.SelectionChanged += Combobox_SelectionChanged;
            TextBox lineweight = AddLineweightDef("Lineweight:", geom.getLineWeight(), newGrid, new[] { row, 0, row++, 1 });
            lineweight.Tag = TextType.Lineweight;
            lineweight.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            TextBox transparency = AddTransparencyDef("Transparency:", geom.getTransparency(), newGrid, new[] { row, 0, row++, 1 });
            transparency.Tag = TextType.Transparency;
            transparency.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            CheckBox visibility = AddVisibilityDef("Visibility:", geom.getVisibility(), newGrid, new[] { row, 0, row++, 1 });
            visibility.Click += Visibility_Click;
            List<TextBox> modelMatrix = AddMatrix("Modeling matrix:", geom.getModelingMatrix(), parent);
            modelMatrix.ForEach(o => o.LostKeyboardFocus += Matrix_LostKeyboardFocus);
            TextBox ltScale = AddLabelAndTextBox("Linetype scale:", geom.getLinetypeScale().ToString(), newGrid, new[] { row, 0, row++, 1 });
            ltScale.Tag = TextType.LinetypeScale;
            ltScale.LostKeyboardFocus += TextBox_LostKeyboardFocus;
            List<string> dispList = new List<string>() { "EveryWhere", "Wirefame", "Render" };
            ComboBox dispMode = AddLabelAndComboBox("Target display mode:", dispList, (int)geom.getTargetDisplayMode(), newGrid, new[] { row, 0, row, 1 });
            dispMode.Tag = ComboboxType.DisplayMode;
            dispMode.SelectionChanged += Combobox_SelectionChanged;

            MM.StopTransaction(mtr);
        }

        private void Matrix_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryData geom = GeomId.openObject();
            OdGeMatrix3d matr = geom.getModelingMatrix();
            SetMatrix(matr, (MatrixData)tb.Tag, tb.Text);
            geom.setModelingMatrix(matr);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Visibility_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openObject().setVisibility(new OdTvVisibilityDef(cb.IsChecked == true));
            Update();
            MM.StopTransaction(mtr);
        }

        private void Color_ColorChanged(object sender, OdTvColorDef newColor)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryData geom = GeomId.openObject();
            if (geom.getColor() != newColor)
            {
                geom.setColor(newColor);
                Update();
            }
            MM.StopTransaction(mtr);

        }

        private void TextBox_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryData geom = GeomId.openObject();
            switch ((TextType)tb.Tag)
            {
                case TextType.Lineweight:
                    if (geom.getLineWeight().getValue() != byte.Parse(tb.Text))
                        geom.setLineWeight(new OdTvLineWeightDef(byte.Parse(tb.Text)));
                    break;
                case TextType.Transparency:
                    if (Math.Abs(geom.getTransparency().getValue() - double.Parse(tb.Text)) > 0.001)
                        geom.setTransparency(new OdTvTransparencyDef(double.Parse(tb.Text)));
                    break;
                case TextType.LinetypeScale:
                    if (Math.Abs(geom.getLinetypeScale() - double.Parse(tb.Text)) > 0.001)
                        geom.setLinetypeScale(double.Parse(tb.Text));
                    break;
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void Combobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGeometryData geom = GeomId.openObject();
            switch ((ComboboxType)cb.Tag)
            {
                case ComboboxType.Layer:
                    geom.setLayer(GetLayerDef(cb.SelectedItem.ToString()));
                    break;
                case ComboboxType.Linetype:
                    geom.setLinetype(GetLinetypeDef(cb.SelectedItem.ToString()));
                    break;
                case ComboboxType.DisplayMode:
                    geom.setTargetDisplayMode((OdTvGeometryData.TargetDisplayMode)cb.SelectedIndex);
                    break;
            }
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

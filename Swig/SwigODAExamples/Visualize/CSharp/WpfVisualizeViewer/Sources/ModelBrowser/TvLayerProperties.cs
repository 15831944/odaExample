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
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvLayerProperties : BasePaletteProperties
    {
        private new MemoryManager MM = MemoryManager.GetMemoryManager();
        private OdTvLayerId _layerId;

        public TvLayerProperties(OdTvLayerId lyrId, OdTvGsDeviceId devId, OdTvWpfView view)
            : base(devId, view)
        {
            _layerId = lyrId;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayer layer = _layerId.openObject();
            int row = 0;
            AddLabelAndTextBox("Name:", layer.getName(), MainGrid, new []{row, 0, row++, 1}, true);
            AddLabelAndTextBox("Description:", layer.getDescription(), MainGrid, new[] { row, 0, row++, 1 }, true);
            Colorpicker color = AddColorDef("Color:", layer.getColor(), new[] { row, 0, row++, 1 }, MainGrid, false);
            color.ColorChanged += Color_ColorChanged;
            ComboBox linetype = AddLinetypeDef("Linetype:", layer.getLinetype(), MainGrid, new[] { row, 0, row++, 1 });
            linetype.SelectionChanged += Linetype_SelectionChanged;
            TextBox lineweight = AddLineweightDef("Lineweight", layer.getLineWeight(), MainGrid, new []{row, 0, row++, 1});
            lineweight.LostKeyboardFocus += Lineweight_LostKeyboardFocus;
            TextBox tranparency = AddTransparencyDef("Transparency:", layer.getTransparency(), MainGrid, new[] { row, 0, row++, 1 });
            tranparency.LostKeyboardFocus += Tranparency_LostKeyboardFocus;
            CheckBox visibility = AddLabelAndCheckBox("Visible:", layer.getVisible(), MainGrid, new[] { row, 0, row++, 1 });
            visibility.Click += Visibility_Click;
            ComboBox material = AddMatrialDef("Material:", layer.getMaterial(), MainGrid, new[] { row, 0, row++, 1 });
            material.SelectionChanged += Material_SelectionChanged;
            MM.StopTransaction(mtr);
        }

        private void Material_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayer layer = _layerId.openObject(OpenMode.kForWrite);
            layer.setMaterial(GetMaterialDef(cb.SelectedItem.ToString()));
            Update();
            MM.StopTransaction(mtr);
        }

        private void Visibility_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _layerId.openObject(OpenMode.kForWrite).setVisible(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);

        }

        private void Tranparency_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayer layer = _layerId.openObject(OpenMode.kForWrite);
            if (!layer.getTransparency().getValue().Equals(double.Parse(tb.Text)))
            {
                layer.setTransparency(new OdTvTransparencyDef(double.Parse(tb.Text)));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Lineweight_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayer layer = _layerId.openObject(OpenMode.kForWrite);
            if(layer.getLineWeight().getValue() != byte.Parse(tb.Text))
            {
                layer.setLineWeight(new OdTvLineWeightDef(byte.Parse(tb.Text)));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Linetype_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if(cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayer layer = _layerId.openObject(OpenMode.kForWrite);
            layer.setLinetype(GetLinetypeDef(cb.SelectedItem.ToString()));
            Update();
            MM.StopTransaction(mtr);
        }

        private void Color_ColorChanged(object sender, OdTvColorDef newColor)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLayer layer = _layerId.openObject(OpenMode.kForWrite);
            if (layer.getColor() != newColor)
            {
                layer.setColor(newColor);
                Update();
            }
            MM.StopTransaction(mtr);
        }
    }
}

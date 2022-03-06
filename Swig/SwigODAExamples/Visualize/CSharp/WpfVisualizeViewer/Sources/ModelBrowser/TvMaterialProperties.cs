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

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvMaterialProperties : BasePaletteProperties
    {
        private OdTvMaterialId _matId;

        private enum ValueProperty
        {
            Opacity,
            SpecularGloss,
            AmbitientFactor,
            DiffuseFactor,
            DiffuseMatMapBlendFactor,
            EmissionFactor,
            SpecularFactor,
        }

        private enum ColorProperty
        {
            AmbitientColor,
            DiffuseColor,
            EmissionColor,
            SpecularColor
        }

        private enum ComboboxProperty
        {
            AmbitientColorMethod,
            DiffuseColorMethod,
            DifMatMapXtiling,
            DifMatMapYtiling,
            EmissionColorMethod,
            SpecularColorMethod
        }

        public TvMaterialProperties(OdTvMaterialId matId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            _matId = matId;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMaterial mat = matId.openObject();
            int row = 0;
            AddLabelAndTextBox("Name:", mat.getName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Description:", mat.getDescription(), MainGrid, new[] { row, 0, row++, 1 }, true);
            OdTvMaterialMap map = new OdTvMaterialMap();
            double d_opacity;
            mat.getOpacity(out d_opacity, map);
            TextBox opacity = AddLabelAndTextBox("Opacity:", d_opacity.ToString(), MainGrid, new[] { row, 0, row++, 1 });
            opacity.Tag = ValueProperty.Opacity;
            opacity.LostKeyboardFocus += ValueType_LostKeyboardFocus;
            TextBox specClogg = AddLabelAndTextBox("Specular gloss:", mat.getSpecularGloss().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            specClogg.Tag = ValueProperty.SpecularGloss;
            specClogg.LostKeyboardFocus += ValueType_LostKeyboardFocus;

            StretchingTreeViewItem ambItm = AddTreeItem("Ambitient", MainGrid, new[] { row++, 0 });
            Grid ambGrid = CreateGrid(2, 3);
            ambItm.Items.Add(ambGrid);
            List<string> colorMethods = new List<string>() { "Inherit", "Override" };
            OdTvMaterialColor amb = mat.getAmbient();
            ComboBox ambColorMethod = AddLabelAndComboBox("Color method:", colorMethods, (int)amb.getMethod(), ambGrid, new[] { 0, 0, 0, 1 });
            ambColorMethod.Tag = ComboboxProperty.AmbitientColorMethod;
            ambColorMethod.SelectionChanged += Combobox_SelectionChanged;
            Colorpicker ambColor = AddColorDef("Color:", amb.getColor(), new[] { 1, 0, 1, 1 }, ambGrid);
            ambColor.Tag = ColorProperty.AmbitientColor;
            ambColor.ColorChanged += Color_ColorChanged;
            TextBox ambFactor = AddLabelAndTextBox("Factor:", amb.getFactor().ToString(), ambGrid, new[] { 2, 0, 2, 1 });
            ambFactor.Tag = ValueProperty.AmbitientFactor;
            ambFactor.LostKeyboardFocus += ValueType_LostKeyboardFocus;

            StretchingTreeViewItem difItm = AddTreeItem("Diffuse", MainGrid, new[] { row++, 0 });
            Grid difGrid = CreateGrid(2, 4);
            difItm.Items.Add(difGrid);
            OdTvMaterialColor difColor = new OdTvMaterialColor();
            OdTvMaterialMap difMap = new OdTvMaterialMap();
            mat.getDiffuse(difColor, difMap);
            ComboBox difColorMethod = AddLabelAndComboBox("Color method:", colorMethods, (int)difColor.getMethod(), difGrid, new[] { 0, 0, 0, 1 });
            difColorMethod.Tag = ComboboxProperty.DiffuseColorMethod;
            difColorMethod.SelectionChanged += Combobox_SelectionChanged;
            Colorpicker defColor = AddColorDef("Color:", difColor.getColor(), new[] { 1, 0, 1, 1 }, difGrid);
            defColor.Tag = ColorProperty.DiffuseColor;
            defColor.ColorChanged += Color_ColorChanged;
            TextBox difFactor = AddLabelAndTextBox("Factor:", difColor.getFactor().ToString(), difGrid, new[] { 2, 0, 2, 1 });
            difFactor.Tag = ValueProperty.DiffuseFactor;
            difFactor.LostKeyboardFocus += ValueType_LostKeyboardFocus;

            StretchingTreeViewItem difMapItm = AddTreeItem("Material map", null, null, difItm);
            Grid difMapGrid = CreateGrid(2, 3);
            difMapItm.Items.Add(difMapGrid);
            AddLabelAndTextBox("Source filename:", difMap.getSourceFileName(), difMapGrid, new[] { 0, 0, 0, 1 }, true);
            TextBox difMatMapFactor = AddLabelAndTextBox("Blend factor:", difMap.getBlendFactor().ToString(), difMapGrid, new[] { 1, 0, 1, 1 });
            difMatMapFactor.Tag = ValueProperty.DiffuseMatMapBlendFactor;
            difMatMapFactor.LostKeyboardFocus += ValueType_LostKeyboardFocus;

            StretchingTreeViewItem difMapperItm = AddTreeItem("Mapper", null, null, difMapItm);
            List<string> tilingList = new List<string>() { "InheritTiling", "Tile", "Crop", "Clamp", "Mirror" };
            ComboBox mapperXtiling = AddLabelAndComboBox("X-axis tiling:", tilingList, (int)difMap.getMapper().uTiling(), difMapperItm);
            mapperXtiling.Tag = ComboboxProperty.DifMatMapXtiling;
            mapperXtiling.SelectionChanged += Combobox_SelectionChanged;
            ComboBox mapperYtiling = AddLabelAndComboBox("Y-axis tiling:", tilingList, (int)difMap.getMapper().vTiling(), difMapperItm);
            mapperYtiling.Tag = ComboboxProperty.DifMatMapYtiling;
            mapperYtiling.SelectionChanged += Combobox_SelectionChanged;
            AddMatrix("Transform", difMap.getMapper().transform(), difMapperItm);

            StretchingTreeViewItem emisItm = AddTreeItem("Emission", MainGrid, new[] { row++, 0 });
            Grid emGrid = CreateGrid(2, 3);
            emisItm.Items.Add(emGrid);
            OdTvMaterialColor emis = mat.getEmission();
            ComboBox emisColorMethod = AddLabelAndComboBox("Color method:", colorMethods, (int)emis.getMethod(), emGrid, new[] { 0, 0, 0, 1 });
            emisColorMethod.Tag = ComboboxProperty.EmissionColorMethod;
            emisColorMethod.SelectionChanged += Combobox_SelectionChanged;
            Colorpicker emisColor = AddColorDef("Color:", emis.getColor(), new[] { 1, 0, 1, 1 }, emGrid);
            emisColor.Tag = ColorProperty.EmissionColor;
            emisColor.ColorChanged += Color_ColorChanged;
            TextBox emisFactor = AddLabelAndTextBox("Factor:", emis.getFactor().ToString(), emGrid, new[] { 2, 0, 2, 1 });
            emisFactor.Tag = ValueProperty.EmissionFactor;
            emisFactor.LostKeyboardFocus += ValueType_LostKeyboardFocus;

            StretchingTreeViewItem specItm = AddTreeItem("Specular", MainGrid, new[] { row, 0 });
            Grid specGrid = CreateGrid(2, 3);
            specItm.Items.Add(specGrid);
            OdTvMaterialColor spec = new OdTvMaterialColor();
            double fact;
            mat.getSpecular(spec, out fact);
            ComboBox specColorMethod = AddLabelAndComboBox("Color method:", colorMethods, (int)spec.getMethod(), specGrid, new[] { 0, 0, 0, 1 });
            specColorMethod.Tag = ComboboxProperty.SpecularColorMethod;
            specColorMethod.SelectionChanged += Combobox_SelectionChanged;
            Colorpicker specColor = AddColorDef("Color:", spec.getColor(), new[] { 1, 0, 1, 1 }, specGrid);
            specColor.Tag = ColorProperty.SpecularColor;
            specColor.ColorChanged += Color_ColorChanged;
            TextBox specFactor = AddLabelAndTextBox("Factor:", spec.getFactor().ToString(), specGrid, new[] { 2, 0, 2, 1 });
            specFactor.Tag = ValueProperty.SpecularFactor;
            specFactor.LostKeyboardFocus += ValueType_LostKeyboardFocus;

            MM.StopTransaction(mtr);
        }

        private void Combobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMaterial mat = _matId.openObject(OpenMode.kForWrite);
            switch ((ComboboxProperty)cb.Tag)
            {
                case ComboboxProperty.AmbitientColorMethod:
                    {
                        OdTvMaterialColor amb = mat.getAmbient();
                        if ((int)amb.getMethod() != cb.SelectedIndex)
                        {
                            amb.setMethod((OdTvMaterialColor.Method)cb.SelectedIndex);
                            mat.setAmbient(amb);
                        }
                        break;
                    }
                case ComboboxProperty.DiffuseColorMethod:
                    {
                        OdTvMaterialColor dif = new OdTvMaterialColor();
                        OdTvMaterialMap map = new OdTvMaterialMap();
                        mat.getDiffuse(dif, map);
                        if ((int)dif.getMethod() != cb.SelectedIndex)
                        {
                            dif.setMethod((OdTvMaterialColor.Method)cb.SelectedIndex);
                            mat.setDiffuse(dif, map);
                        }
                        break;
                    }
                case ComboboxProperty.DifMatMapXtiling:
                    {
                        OdTvMaterialColor dif = new OdTvMaterialColor();
                        OdTvMaterialMap map = new OdTvMaterialMap();
                        mat.getDiffuse(dif, map);
                        if ((int)map.getMapper().uTiling() != cb.SelectedIndex)
                        {
                            OdTvTextureMapper texMap = map.getMapper();
                            texMap.setUTiling((OdTvTextureMapper.Tiling)cb.SelectedIndex);
                            map.setMapper(texMap);
                            mat.setDiffuse(dif, map);
                        }
                        break;
                    }
                case ComboboxProperty.DifMatMapYtiling:
                    {
                        OdTvMaterialColor dif = new OdTvMaterialColor();
                        OdTvMaterialMap map = new OdTvMaterialMap();
                        mat.getDiffuse(dif, map);
                        if ((int)map.getMapper().vTiling() != cb.SelectedIndex)
                        {
                            OdTvTextureMapper texMap = map.getMapper();
                            texMap.setVTiling((OdTvTextureMapper.Tiling)cb.SelectedIndex);
                            map.setMapper(texMap); mat.setDiffuse(dif, map);
                        }
                        break;
                    }
                case ComboboxProperty.EmissionColorMethod:
                    {
                        OdTvMaterialColor emis = mat.getEmission();
                        if ((int)emis.getMethod() != cb.SelectedIndex)
                        {
                            emis.setMethod((OdTvMaterialColor.Method)cb.SelectedIndex);
                            mat.setEmission(emis);
                        }
                        break;
                    }
                case ComboboxProperty.SpecularColorMethod:
                    {
                        OdTvMaterialColor spec = new OdTvMaterialColor();
                        double fact = 0;
                        mat.getSpecular(spec, out fact);
                        if ((int)spec.getMethod() != cb.SelectedIndex)
                        {
                            spec.setMethod((OdTvMaterialColor.Method)cb.SelectedIndex);
                            mat.setSpecular(spec, fact);
                        }
                        break;
                    }
            }

            Update();
            MM.StopTransaction(mtr);
        }

        private void Color_ColorChanged(object sender, OdTvColorDef newColor)
        {
            Colorpicker cp = sender as Colorpicker;
            if (cp == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMaterial mat = _matId.openObject(OpenMode.kForWrite);
            switch ((ColorProperty)cp.Tag)
            {
                case ColorProperty.AmbitientColor:
                    {
                        OdTvMaterialColor amb = mat.getAmbient();
                        if (amb.getColor() != newColor)
                        {
                            amb.setColor(newColor);
                            mat.setAmbient(amb);
                        }
                        break;
                    }
                case ColorProperty.DiffuseColor:
                    {
                        OdTvMaterialColor dif = new OdTvMaterialColor();
                        OdTvMaterialMap map = new OdTvMaterialMap();
                        mat.getDiffuse(dif, map);
                        if (dif.getColor() != newColor)
                        {
                            dif.setColor(newColor);
                            mat.setDiffuse(dif, map);
                        }
                        break;
                    }
                case ColorProperty.EmissionColor:
                    {
                        OdTvMaterialColor emis = mat.getAmbient();
                        if (emis.getColor() != newColor)
                        {
                            emis.setColor(newColor);
                            mat.setEmission(emis);
                        }
                        break;
                    }
                case ColorProperty.SpecularColor:
                    {
                        OdTvMaterialColor spec = new OdTvMaterialColor();
                        double fact;
                        mat.getSpecular(spec, out fact);
                        if (spec.getColor() != newColor)
                        {
                            spec.setColor(newColor);
                            mat.setSpecular(spec, fact);
                        }
                        break;
                    }
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void ValueType_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMaterial mat = _matId.openObject(OpenMode.kForWrite);
            tb.Text = tb.Text.Replace(".", ",");
            double val = double.Parse(tb.Text);
            switch ((ValueProperty)tb.Tag)
            {
                case ValueProperty.Opacity:
                    OdTvMaterialMap map_ = new OdTvMaterialMap();
                    double d_opacity;
                    mat.getOpacity(out d_opacity, map_);
                    if (!d_opacity.Equals(val))
                        mat.setOpacity(val);
                    break;
                case ValueProperty.SpecularGloss:
                    if (!mat.getSpecularGloss().Equals(val))
                        mat.setSpecularGloss(val);
                    break;
                case ValueProperty.AmbitientFactor:
                    {
                        OdTvMaterialColor amb = mat.getAmbient();
                        if (!amb.getFactor().Equals(val))
                        {
                            amb.setFactor(val);
                            mat.setAmbient(amb);
                        }
                        break;
                    }
                case ValueProperty.DiffuseFactor:
                    {
                        OdTvMaterialColor dif = new OdTvMaterialColor();
                        OdTvMaterialMap map = new OdTvMaterialMap();
                        mat.getDiffuse(dif, map);
                        if (!dif.getFactor().Equals(val))
                        {
                            dif.setFactor(val);
                            mat.setDiffuse(dif, map);
                        }
                        break;
                    }
                case ValueProperty.DiffuseMatMapBlendFactor:
                    {
                        OdTvMaterialColor dif = new OdTvMaterialColor();
                        OdTvMaterialMap map = new OdTvMaterialMap();
                        mat.getDiffuse(dif, map);
                        if (!map.getBlendFactor().Equals(val))
                        {
                            map.setBlendFactor(val);
                            mat.setDiffuse(dif, map);
                        }
                        break;
                    }
                case ValueProperty.EmissionFactor:
                    {
                        OdTvMaterialColor emis = mat.getEmission();
                        if (!emis.getFactor().Equals(val))
                        {
                            emis.setFactor(val);
                            mat.setEmission(emis);
                        }
                        break;
                    }
                case ValueProperty.SpecularFactor:
                    {
                        OdTvMaterialColor spec = new OdTvMaterialColor();
                        double fact;
                        mat.getSpecular(spec, out fact);
                        if (!spec.getFactor().Equals(val))
                        {
                            spec.setFactor(val);
                            mat.setSpecular(spec, fact);
                        }
                        break;
                    }
            }
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

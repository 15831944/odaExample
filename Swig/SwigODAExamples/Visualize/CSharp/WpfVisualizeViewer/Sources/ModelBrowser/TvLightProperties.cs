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
using System.Globalization;
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvLightProperties : BasePaletteProperties
    {
        private OdTvEntityId _lightId;

        private enum TextType
        {
            FalloffAngle,
            HotSpotAngle,
            Intensity,
            StartLimit,
            EndLimit,
            Direction,
            Position,
            TargLoc
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

        public TvLightProperties(OdTvEntityId lightId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            if (lightId == null || lightId.isNull())
                return;
            _lightId = lightId;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLight light = _lightId.openObjectAsLight();
            int row = 0;
            Colorpicker color = AddColorDef("Color:", light.getLightColor(), new[] { row, 0, row++, 1 }, MainGrid);
            color.ColorChanged += Color_ColorChanged;
            List<string> typeList = new List<string>() { "DistantLight", "PointLight", "SpotLight" };
            ComboBox type = AddLabelAndComboBox("Type:", typeList, light.getLightType().ToString().Remove(0, 1), MainGrid, new[] { row, 0, row++, 1 });
            type.SelectionChanged += Type_SelectionChanged;
            TextBox fallAng = AddLabelAndTextBox("Falloff angle:", light.getFalloffAngle().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            fallAng.Tag = new ControlData() { ProperyType = TextType.FalloffAngle };
            fallAng.LostKeyboardFocus += TextProperty_LostKeyboardFocus;
            TextBox hotSpotAng = AddLabelAndTextBox("Hotspot angle:", light.getHotspotAngle().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            hotSpotAng.Tag = new ControlData() { ProperyType = TextType.HotSpotAngle };
            hotSpotAng.LostKeyboardFocus += TextProperty_LostKeyboardFocus;
            TextBox intensity = AddLabelAndTextBox("Intensity:", light.getIntensity().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            intensity.Tag = new ControlData() { ProperyType = TextType.Intensity };
            intensity.LostKeyboardFocus += TextProperty_LostKeyboardFocus;

            StretchingTreeViewItem attenItm = AddTreeItem("Light attenuation", MainGrid, new[] { row++, 0 });
            OdTvLightAttenuation la = light.getLightAttenuation();
            List<string> attenTypeList = new List<string>() { "None", "InverseLinear", "InverseSquare" };
            ComboBox attenType = AddLabelAndComboBox("Type:", attenTypeList, (int)la.getAttenuationType(), attenItm);
            attenType.SelectionChanged += AttenType_SelectionChanged;
            CheckBox useLimits = AddLabelAndCheckBox("Use limits:", la.getUseLimits(), attenItm);
            useLimits.Click += UseLimits_Click;
            TextBox startLimit = AddLabelAndTextBox("Start limit:", la.getStartLimit().ToString(), attenItm);
            startLimit.Tag = new ControlData() { ProperyType = TextType.StartLimit };
            startLimit.LostKeyboardFocus += TextProperty_LostKeyboardFocus;
            TextBox endLimit = AddLabelAndTextBox("End limit:", la.getEndLimit().ToString(), attenItm);
            endLimit.Tag = new ControlData() { ProperyType = TextType.EndLimit };
            endLimit.LostKeyboardFocus += TextProperty_LostKeyboardFocus;

            TextBox[] dir = AddVector3D("Light direction", light.getLightDirection(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var pt in dir)
            {
                pt.Tag = new ControlData(TextType.Direction, (CoordinateType)pt.Tag);
                pt.LostKeyboardFocus += TextProperty_LostKeyboardFocus;
            }
            TextBox[] pos = AddPoint3D("Position", light.getPosition(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var pt in pos)
            {
                pt.Tag = new ControlData(TextType.Direction, (CoordinateType)pt.Tag);
                pt.LostKeyboardFocus += TextProperty_LostKeyboardFocus;
            }
            TextBox[] targLoc = AddPoint3D("Target location", light.getTargetLocation(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var pt in targLoc)
            {
                pt.Tag = new ControlData(TextType.Direction, (CoordinateType)pt.Tag);
                pt.LostKeyboardFocus += TextProperty_LostKeyboardFocus;
            }
            MM.StopTransaction(mtr);
        }

        private void UseLimits_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLight light = _lightId.openObjectAsLight(OpenMode.kForWrite);
            OdTvLightAttenuation la = light.getLightAttenuation();
            la.setUseLimits(cb.IsChecked == true);
            light.setLightAttenuation(la);
            Update();
            MM.StopTransaction(mtr);
        }

        private void AttenType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLight light = _lightId.openObjectAsLight(OpenMode.kForWrite);
            OdTvLightAttenuation atten = light.getLightAttenuation();
            atten.setAttenuationType((OdTvLightAttenuation.AttenuationType)cb.SelectedIndex);
            light.setLightAttenuation(atten);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Color_ColorChanged(object sender, OdTvColorDef newColor)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLight light = _lightId.openObjectAsLight(OpenMode.kForWrite);
            if (light.getLightColor() != newColor)
            {
                light.setLightColor(newColor);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Type_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _lightId.openObjectAsLight(OpenMode.kForWrite).setLightType((OdTvLight.LightType) cb.SelectedIndex + 1);
            Update();
            MM.StopTransaction(mtr);
        }

        private void TextProperty_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLight light = _lightId.openObjectAsLight(OpenMode.kForWrite);
            ControlData data = (ControlData)tb.Tag;
            switch (data.ProperyType)
            {
                case TextType.FalloffAngle:
                    {
                        double val = double.Parse(tb.Text);
                        if (!light.getFalloffAngle().Equals(val))
                            light.setHotspotAndFalloff(light.getHotspotAngle(), val);
                        break;
                    }
                case TextType.HotSpotAngle:
                    {
                        double val = double.Parse(tb.Text);
                        if (!light.getHotspotAngle().Equals(val))
                            light.setHotspotAndFalloff(val, light.getFalloffAngle());
                        break;
                    }
                case TextType.Intensity:
                    {
                        double val = double.Parse(tb.Text);
                        if (!light.getIntensity().Equals(val))
                            light.setIntensity(val);
                        break;
                    }
                case TextType.StartLimit:
                    {
                        double val = double.Parse(tb.Text);
                        OdTvLightAttenuation atten = light.getLightAttenuation();
                        if (!atten.getStartLimit().Equals(val))
                        {
                            atten.setLimits(val, atten.getEndLimit());
                            light.setLightAttenuation(atten);
                        }
                        break;
                    }
                case TextType.EndLimit:
                {
                    double val = double.Parse(tb.Text);
                    OdTvLightAttenuation atten = light.getLightAttenuation();
                    if (atten.getEndLimit().Equals(val))
                    {
                        atten.setLimits(atten.getStartLimit(), val);
                        light.setLightAttenuation(atten);
                    }
                    break;
                }
                case TextType.Direction:
                {
                    OdGeVector3d newDir = SetVectorCoordByType(light.getLightDirection(), data.CoordType, tb.Text);
                    if (newDir != light.getLightDirection())
                        light.setLightDirection(newDir);
                    break;
                }
                case TextType.Position:
                {
                    OdGePoint3d newPt = SetPointCoordByType(light.getPosition(), data.CoordType, tb.Text);
                    if (newPt != light.getPosition())
                        light.setPosition(newPt);
                    break;
                }
                case TextType.TargLoc:
                {
                    OdGePoint3d newPt = SetPointCoordByType(light.getTargetLocation(), data.CoordType, tb.Text);
                    if (newPt != light.getTargetLocation())
                        light.setTargetLocation(newPt);
                    break;
                }
            }

            Update();
            MM.StopTransaction(mtr);
        }
    }
}

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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser
{
    public class PropertiesCommon : UserControl
    {
        public OdTvGsDeviceId DeviceId { get; private set; }

        public PropertiesCommon(OdTvGsDeviceId id)
        {
            DeviceId = id;
        }

        public ComboBox AddColorDef(string label, OdTvColorDef color, int[] layots, Grid grid, bool isObjColor = true)
        {
            Label lbl = new Label() { Content = label };
            Grid.SetRow(lbl, layots[0]);
            Grid.SetColumn(lbl, layots[1]);
            Colorpicker clrp = new Colorpicker(color, DeviceId, isObjColor);
            if (color.getType() == OdTvColorDef.ColorType.kDefault)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(clrp, layots[2]);
            Grid.SetColumn(clrp, layots[3]);
            grid.Children.Add(lbl);
            grid.Children.Add(clrp);
            return clrp.ComboBox;
        }

        public TextBox CreateLabelAndTextBox(string label, string text, Grid grid, int[] arr, bool isReadOnly = false, bool isDefValue = false)
        {
            Label lbl = new Label() { Content = label };
            if (isDefValue)
                lbl.Foreground = new SolidColorBrush() { Color = Colors.Gray };
            Grid.SetRow(lbl, arr[0]);
            Grid.SetColumn(lbl, arr[1]);

            TextBox txt = new TextBox()
            {
                Text = text,
                IsReadOnly = isReadOnly,
                VerticalContentAlignment = VerticalAlignment.Center
            };
            Grid.SetRow(txt, arr[2]);
            Grid.SetColumn(txt, arr[3]);

            grid.Children.Add(lbl);
            grid.Children.Add(txt);

            return txt;
        }

        public uint ColorToUInt(Color color)
        {
            return (uint)((color.A << 24) | (color.B << 16) |
                          (color.G << 8) | (color.R << 0));
        }

        public static OdTvColorDef GetColorDefFromUInt(uint color)
        {
            byte b = (byte)(color >> 16);
            byte g = (byte)(color >> 8);
            byte r = (byte)(color >> 0);
            return new OdTvColorDef(r, g, b);
        }

        public CheckBox CreateLabelAndCheckBox(string label, bool flag, Grid grid, int[] arr, bool isReadOnly = false, bool isDefValue = false)
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
            Grid.SetRow(cb, arr[2]);
            Grid.SetColumn(cb, arr[3]);

            grid.Children.Add(lbl);
            grid.Children.Add(cb);

            return cb;
        }
    }
}

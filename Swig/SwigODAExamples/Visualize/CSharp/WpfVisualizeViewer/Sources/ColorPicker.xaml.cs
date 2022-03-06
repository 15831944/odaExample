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
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using Teigha.Core;
using Teigha.Visualize;
using Brushes = System.Windows.Media.Brushes;
using ComboBox = System.Windows.Controls.ComboBox;
using Orientation = System.Windows.Controls.Orientation;
using UserControl = System.Windows.Controls.UserControl;

namespace WpfVisualizeViewer
{
    /// <summary>
    /// Interaction logic for Colorpicker.xaml
    /// </summary>
    public partial class Colorpicker : UserControl
    {
        private OdTvGsDeviceId _devId;

        public delegate void ColorChangedHandler(object sender, OdTvColorDef newColor);

        public event ColorChangedHandler ColorChanged;

        private bool _isObjColor;

        public OdTvColorDef SelectedColor { get; private set; }

        public static List<TvComboboxItem> ColorsList = new List<TvComboboxItem>()
        {
            new TvComboboxItem(""),
            new TvComboboxItem("ByBlock"),
            new TvComboboxItem("ByLayer"),
            new TvComboboxItem(Brushes.Red, "Red"),
            new TvComboboxItem(Brushes.Green, "Green"),
            new TvComboboxItem(Brushes.Blue, "Blue"),
            new TvComboboxItem(Brushes.Yellow, "Yellow"),
            new TvComboboxItem(Brushes.White, "White"),
            new TvComboboxItem(Brushes.Black, "Black"),
            new TvComboboxItem(Brushes.Magenta, "Magenta"),
            new TvComboboxItem(Brushes.Indigo, "Indigo"),
            new TvComboboxItem(Brushes.Purple, "Purple"),
            new TvComboboxItem(Brushes.OrangeRed, "OrangeRed"),
            new TvComboboxItem(Brushes.Orange, "Orange"),
            new TvComboboxItem("Choose color...")
        };

        public Colorpicker(OdTvColorDef startColor, OdTvGsDeviceId id, bool isObjColor = true)
        {
            InitializeComponent();
            ComboBox.SelectionChanged += ComboBox_SelectionChanged;
            ComboBox.DataContext = this;
            _devId = id;
            _isObjColor = isObjColor;
            List<TvComboboxItem> itmList = new List<TvComboboxItem>();
            foreach (var ci in ColorsList)
            {
                if (!isObjColor && (ci.ColorName == "ByBlock" || ci.ColorName == "ByLayer"))
                    continue;
                itmList.Add(new TvComboboxItem(ci));
            }
            ComboBox.ItemsSource = itmList;
            FindColor(startColor);
            SelectedColor = startColor;
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            Colorpicker.TvComboboxItem itm = cb.SelectedItem as Colorpicker.TvComboboxItem;
            if (itm == null)
                return;
            bool isCustom = false;

            if (itm.ColorName == "")
                SelectedColor = new OdTvColorDef(255, 255, 255);
            else if (itm.ColorName == "ByBlock")
                SelectedColor = new OdTvColorDef(InheritedAttribute.kByBlock);
            else if (itm.ColorName == "ByLayer")
                SelectedColor = new OdTvColorDef(InheritedAttribute.kByLayer);
            else if (itm.ColorName == "Choose color...")
            {
                ColorDialog dlg = new ColorDialog();
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    System.Drawing.Color clr = dlg.Color;
                    SelectedColor = new OdTvColorDef(clr.R, clr.G, clr.B);
                    isCustom = true;
                }
                FindColor(SelectedColor);
            }
            else
            {
                Color clr = itm.ItemColor.Color;
                SelectedColor = new OdTvColorDef(clr.R, clr.G, clr.B);
            }

            if (isCustom)
                FindColor(SelectedColor);
            if(ColorChanged != null)
                ColorChanged.Invoke(this, SelectedColor);
        }

        public void FindColor(OdTvColorDef startColor)
        {
            switch (startColor.getType())
            {
                case OdTvColorDef.ColorType.kDefault:
                    ComboBox.SelectedItem = FindItemByName("");
                    break;
                case OdTvColorDef.ColorType.kColor:
                {
                    byte r, g, b;
                        startColor.getColor(out r, out g, out b);
                        SolidColorBrush color = new SolidColorBrush() { Color = new Color { R = r, G = g, B = b, A = 255 } };

                        foreach (var col in ComboBox.Items)
                        {
                            TvComboboxItem ci = col as TvComboboxItem;
                            if (ci != null && (ci.ItemColor != null && ci.ItemColor.Color == color.Color &&
                                 ci.ItemColor.Opacity.Equals(color.Opacity)))
                            {
                                ComboBox.SelectedItem = col;
                                return;
                            }
                        }

                        TvComboboxItem itm = new TvComboboxItem(color, "(" + r +"," + g + "," + b + ")");
                        ColorsList.Insert(0, itm);

                        List<TvComboboxItem> itmList = new List<TvComboboxItem>();
                        foreach (var ci in ColorsList)
                        {
                            if (!_isObjColor && (ci.ColorName == "ByBlock" || ci.ColorName == "ByLayer"))
                                continue;
                            itmList.Add(new TvComboboxItem(ci));
                        }
                        ComboBox.ItemsSource = itmList;
                        ComboBox.SelectedIndex = 0;
                        break;
                    }
                case OdTvColorDef.ColorType.kInherited:
                    ComboBox.SelectedItem = FindItemByName(startColor.getInheritedColor() == InheritedAttribute.kByBlock ? "ByBlock" : "ByLayer");
                    break;
                case OdTvColorDef.ColorType.kIndexed:
                    {
                        string indColorName = startColor.getIndexedColor().ToString();
                        TvComboboxItem itm = FindItemByName(indColorName);
                        if (itm != null)
                            ComboBox.SelectedItem = itm;
                        else
                        {
                            MemoryTransaction mtr = MemoryManager.GetMemoryManager().StartTransaction();
                            OdTvGsDevice pDevice = _devId.openObject();
                            uint[] pNums = pDevice.getLogicalPalette();
                            uint incol = pNums[startColor.getIndexedColor()];
                            OdTvColorDef colorDef = BasePaletteProperties.GetColorDefFromUInt(incol);
                            byte r, g, b;
                            colorDef.getColor(out  r, out g, out b);
                            TvComboboxItem newItm = new TvComboboxItem(new SolidColorBrush(new Color { R = r, G = g, B = b, A = 255 }), indColorName);
                            ColorsList.Insert(0, newItm);

                            List<TvComboboxItem> itmList = new List<TvComboboxItem>();
                            foreach (var ci in ColorsList)
                            {
                                if (!_isObjColor && (ci.ColorName == "ByBlock" || ci.ColorName == "ByLayer"))
                                    continue;
                                itmList.Add(new TvComboboxItem(ci));
                            }
                            ComboBox.ItemsSource = itmList;
                            ComboBox.SelectedIndex = 0;

                            MemoryManager.GetMemoryManager().StopTransaction(mtr);
                        }
                        break;
                    }
            }
        }

        public TvComboboxItem FindItemByName(string colorName)
        {
            foreach (var ci in ComboBox.Items)
            {
                TvComboboxItem itm = ci as TvComboboxItem;
                if (itm != null && itm.ColorName == colorName)
                    return itm;
            }

            return null;
        }

        public class TvComboboxItem : StackPanel
        {
            public SolidColorBrush ItemColor { get; set; }
            public string ColorName { get; private set; }
            public TvComboboxItem(string label)
            {
                ColorName = label;
                TextBlock txt = new TextBlock()
                {
                    Text = label,
                    VerticalAlignment = VerticalAlignment.Center,
                    TextAlignment = TextAlignment.Center
                };
                Children.Add(txt);
            }

            public TvComboboxItem(SolidColorBrush color, string label)
            {
                ColorName = label;
                ItemColor = color;
                Orientation = Orientation.Horizontal;
                VerticalAlignment = VerticalAlignment.Center;
                Rectangle rect = new Rectangle { Width = 20, Height = 20, Fill = color, Margin = new Thickness(0, 0, 5, 0) };
                TextBlock txt = new TextBlock() { Text = label, VerticalAlignment = VerticalAlignment.Center, TextAlignment = TextAlignment.Center };
                Children.Add(rect);
                Children.Add(txt);
            }

            public TvComboboxItem(TvComboboxItem itm)
            {
                ColorName = itm.ColorName;
                ItemColor = itm.ItemColor;

                Orientation = Orientation.Horizontal;
                VerticalAlignment = VerticalAlignment.Center;

                if (ItemColor != null)
                {
                    Rectangle rect = new Rectangle
                    {
                        Width = 20,
                        Height = 20,
                        Fill = ItemColor,
                        Margin = new Thickness(0, 0, 5, 0)
                    };
                    Children.Add(rect);
                }

                TextBlock txt = new TextBlock() { Text = ColorName, VerticalAlignment = VerticalAlignment.Center, TextAlignment = TextAlignment.Center };
                Children.Add(txt);
            }
        }
    }
}
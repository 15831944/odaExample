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
using System.Windows.Forms;
using System.Windows.Media;
using Teigha.Core;
using Teigha.Visualize;
using Button = System.Windows.Controls.Button;
using CheckBox = System.Windows.Controls.CheckBox;
using Label = System.Windows.Controls.Label;
using Orientation = System.Windows.Controls.Orientation;
using TextBox = System.Windows.Controls.TextBox;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvDeviceProperties : BasePaletteProperties
    {
        private uint[] _palette;

        public TvDeviceProperties(OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();

            OdTvGsDevice dev = devId.openObject();
            int row = 0;
            AddLabelAndTextBox("Name:", dev.getGsDeviceName().ToString().Remove(0, 1), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of views:", dev.numViews().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            OdTvDCRect rect = new OdTvDCRect();
            dev.getSize(rect);
            AddSize("Size", rect, MainGrid, new[] { row++, 0 }, true);
            Colorpicker bgColor = AddColorDef("Background:", GetColorDefFromUInt(dev.getBackgroundColor()),
                new[] { row, 0, row++, 1 }, MainGrid, false);
            bgColor.ColorChanged += BgColor_ColorChanged;
            StretchingTreeViewItem paletteItm = AddTreeItem("Logical palette", MainGrid, new[] { row++, 0 });
            Grid paletteGrid = CreateGrid(2, 2);
            paletteItm.Items.Add(paletteGrid);

            AddLabelAndTextBox("Number of indexes:", "256", paletteGrid, new[] { 0, 0, 0, 1 }, true);
            Button btn = AddLabelAndButton("Logical palette:", "...", paletteGrid, new[] { 1, 0, 1, 1 });
            btn.Click += Btn_Click;

            AddLabelAndCheckBox("Is bitmap:", dev.isBitmap(), MainGrid, new[] { row, 0, row++, 1 }, true);

            StretchingTreeViewItem cmnOptItm = AddTreeItem("Common options", MainGrid, new[] { row++, 0 });
            Grid cmnOptGrid = CreateGrid(2, 5);
            cmnOptItm.Items.Add(cmnOptGrid);
            int optRow = 0;
            AddBoolDeviceOption("DoubleBufferEnabled:", dev, OdTvGsDevice.Options.kDoubleBufferEnabled, cmnOptGrid, optRow++);
            AddBoolDeviceOption("BlocksCache:", dev, OdTvGsDevice.Options.kBlocksCache, cmnOptGrid, optRow++);
            AddBoolDeviceOption("EnableMultithread:", dev, OdTvGsDevice.Options.kEnableMultithread, cmnOptGrid, optRow++);
            short val;
            dev.getOption(OdTvGsDevice.Options.kMaxRegenThreads, out val);
            TextBox maxRegTh = AddLabelAndTextBox("MaxRegenThreads:", val.ToString(), cmnOptGrid, new[] { optRow, 0, optRow++, 1 });
            maxRegTh.LostKeyboardFocus += MaxRegTh_LostKeyboardFocus;
            AddBoolDeviceOption("UseDynamicSubEntHlt:", dev, OdTvGsDevice.Options.kUseDynamicSubEntHlt, cmnOptGrid, optRow++);

            StretchingTreeViewItem specOptItm = AddTreeItem("Specific options", MainGrid, new[] { row++, 0 });
            Grid specOptGrid = CreateGrid(2, 6);
            specOptItm.Items.Add(specOptGrid);
            optRow = 0;
            AddBoolDeviceOption("DiscardBackFaces:", dev, OdTvGsDevice.Options.kDiscardBackFaces, specOptGrid, optRow++);
            AddBoolDeviceOption("UseTTFCache:", dev, OdTvGsDevice.Options.kUseTTFCache, specOptGrid, optRow++);
            AddBoolDeviceOption("UseVisualStyles:", dev, OdTvGsDevice.Options.kUseVisualStyles, specOptGrid, optRow++);
            AddBoolDeviceOption("UseOverlayBuffers:", dev, OdTvGsDevice.Options.kUseOverlayBuffers, specOptGrid, optRow++);
            int iVal;
            OdTvResult rc = dev.getOption(OdTvGsDevice.Options.kUseLutPalette, out iVal);
            if (rc == OdTvResult.tvOk)
            {
                bool lutMonochrome = ((iVal) & (0x1)) != 0;
                bool lutPalette = ((iVal) & (0x2)) != 0;
                CheckBox cb1 = AddLabelAndCheckBox("LutMonochrome:", lutMonochrome, specOptGrid, new[] { optRow, 0, optRow++, 1 });
                cb1.Click += TvDeviceLutPalette_Click; ;
                cb1.Tag = 0x1;
                CheckBox cb2 = AddLabelAndCheckBox("LutPalette:", lutPalette, specOptGrid, new[] { optRow, 0, optRow, 1 });
                cb2.Click += TvDeviceLutPalette_Click; ;
                cb2.Tag = 0x2;
            }

            MM.StopTransaction(mtr);
        }

        private void Btn_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = TvDeviceId.openObject();
            _palette = dev.getLogicalPalette();
            Grid grid = CreateGrid(4, 64);
            int row = 0;
            int col = 0;
            for (int i = 0; i < 256; i++)
            {
                OdTvColorDef color = GetColorDefFromUInt(_palette[i]);
                byte r, g, b;
                color.getColor(out r, out g, out b);
                StackPanel stackPanel = new StackPanel { Orientation = Orientation.Horizontal };
                SolidColorBrush brush = new SolidColorBrush(new Color {R = r, G = g, B = b, A = 255});
                Button btn = new Button { Background = brush, Width = 30, Height = 30, Margin = new Thickness(2.5)};
                btn.Click += ChangePaletteColor_Click;
                btn.Tag = i;
                Label lbl = new Label { Content = i.ToString(), VerticalContentAlignment = VerticalAlignment.Center };
                stackPanel.Children.Add(btn);
                stackPanel.Children.Add(lbl);
                Grid.SetRow(stackPanel, row);
                Grid.SetColumn(stackPanel, col);
                grid.Children.Add(stackPanel);
                col++;
                if (col == 4)
                {
                    col = 0;
                    row++;
                }
            }

            if (CreateDialog("Device logical palette", new Size(320, 350), grid).ShowDialog() == true)
                dev.setLogicalPalette(_palette, 256);

            _palette = null;

            MM.StopTransaction(mtr);
        }

        private void ChangePaletteColor_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            if(btn == null)
                return;
            ColorDialog dlg = new ColorDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                System.Drawing.Color clr = dlg.Color;
                Color color = new Color() { R = clr.R, G = clr.G, B = clr.B, A = 255 };
                btn.Background = new SolidColorBrush(color);
                _palette[(int) btn.Tag] = ColorToUInt(color);
            } 
        }

        private void BgColor_ColorChanged(object sender, OdTvColorDef newColor)
        {
            Colorpicker cp = sender as Colorpicker;
            if (cp == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = TvDeviceId.openObject(OpenMode.kForWrite);
            byte r, g, b;
            newColor.getColor(out r, out g, out b);
            uint color = (uint)((b << 16) | (g << 8) | (r << 0));
            dev.setBackgroundColor(color);
            Update();
            MM.StopTransaction(mtr);
        }

        private void MaxRegTh_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = TvDeviceId.openObject(OpenMode.kForWrite);
            dev.setOption(OdTvGsDevice.Options.kMaxRegenThreads, short.Parse(tb.Text));
            Update();
            MM.StopTransaction(mtr);
        }

        private void AddBoolDeviceOption(string label, OdTvGsDevice dev, OdTvGsDevice.Options option, Grid grid, int curRow)
        {
            bool flag;
            OdTvResult rc = dev.getOption(option, out flag);
            if (rc == OdTvResult.tvOk)
            {
                CheckBox cb = AddLabelAndCheckBox(label, flag, grid, new[] { curRow, 0, curRow, 1 });
                cb.Click += TvDeviceProperties_Click; ;
                cb.Tag = option;
            }
        }

        private void TvDeviceProperties_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice.Options opt = (OdTvGsDevice.Options)cb.Tag;
            OdTvGsDevice dev = TvDeviceId.openObject(OpenMode.kForWrite);
            dev.setOption(opt, cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void TvDeviceLutPalette_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsDevice dev = TvDeviceId.openObject(OpenMode.kForWrite);
            int val;
            dev.getOption(OdTvGsDevice.Options.kUseLutPalette, out val);
            int tag = (int)cb.Tag;
            val = ((cb.IsChecked == true) ? (val |= (tag)) : (val &= ~(tag)));
            dev.setOption(OdTvGsDevice.Options.kUseLutPalette, val);
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

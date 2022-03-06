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
    class TvTextStyleProperties : BasePaletteProperties
    {
        private OdTvTextStyleId _textStyleId;

        private enum BoolParams
        {
            Backwards,
            Bold,
            Italic,
            ShapeStatus,
            UpsideDown,
            Vertical,
            Underlined,
            Overlined,
            Striked
        }

        private enum TextParams
        {
            ObliquingAngle,
            TextSize,
            WidthFactor
        }

        public TvTextStyleProperties(OdTvTextStyleId txtStyleId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            _textStyleId = txtStyleId;
            OdTvTextStyle txtStyle = txtStyleId.openObject();
            int row = 0;
            AddLabelAndTextBox("Filename:", txtStyle.getFileName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Big font filename:", txtStyle.getBigFontFileName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            List<string> list = new List<string>()
            {
                "Left",
                "Center",
                "Right",
                "Aligned",
                "Middle",
                "Fit",
                "TopLeft",
                "TopCenter",
                "TopRight",
                "MiddleLeft",
                "MiddleCenter",
                "MiddleRight",
                "BottomLeft",
                "BottomCenter",
                "BottomRight"
            };
            ComboBox alignMode = AddLabelAndComboBox("Alignment mode:", list, (int)txtStyle.getAlignmentMode(), MainGrid, new[] { row, 0, row++, 1 });
            alignMode.SelectionChanged += AlignMode_SelectionChanged;
            CheckBox backw = AddLabelAndCheckBox("Backwards:", txtStyle.getBackwards(), MainGrid, new[] { row, 0, row++, 1 });
            backw.Click += BoolParam_Click;
            backw.Tag = BoolParams.Backwards;

            StretchingTreeViewItem font = AddTreeItem("Font", MainGrid, new[] { row++, 0 });
            Grid fontGrid = CreateGrid(2, 5);
            font.Items.Add(fontGrid);
            int fRow = 0;
            string typeface = "";
            bool bold, italic;
            int charset, pitchAndFamily;
            txtStyle.getFont(ref typeface, out bold, out italic, out charset, out pitchAndFamily);
            AddLabelAndTextBox("Typeface:", typeface, fontGrid, new[] { fRow, 0, fRow++, 1 }, true);
            CheckBox boldCb = AddLabelAndCheckBox("Bold:", bold, fontGrid, new[] { fRow, 0, fRow++, 1 }, typeface.Length == 0);
            boldCb.Click += BoolParam_Click;
            boldCb.Tag = BoolParams.Bold;
            CheckBox italicCb = AddLabelAndCheckBox("Italic:", italic, fontGrid, new[] { fRow, 0, fRow++, 1 }, typeface.Length == 0);
            italicCb.Click += BoolParam_Click;
            italicCb.Tag = BoolParams.Italic;
            AddLabelAndTextBox("Charset:", charset.ToString(), fontGrid, new[] { fRow, 0, fRow++, 1 }, true);
            AddLabelAndTextBox("Typeface:", pitchAndFamily.ToString(), fontGrid, new[] { fRow, 0, fRow++, 1 }, true);

            TextBox oblAng = AddLabelAndTextBox("Obliquing angle:", txtStyle.getObliquingAngle().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            oblAng.LostKeyboardFocus += TextParam_LostKeyboardFocus;
            oblAng.Tag = TextParams.ObliquingAngle;
            CheckBox shapeStatus = AddLabelAndCheckBox("Shape status:", txtStyle.getShapeStatus(), MainGrid, new[] { row, 0, row++, 1 });
            shapeStatus.Click += BoolParam_Click;
            shapeStatus.Tag = BoolParams.ShapeStatus;
            CheckBox upsideDown = AddLabelAndCheckBox("Upside down:", txtStyle.getUpsideDown(), MainGrid, new[] { row, 0, row++, 1 });
            upsideDown.Click += BoolParam_Click;
            upsideDown.Tag = BoolParams.UpsideDown;
            CheckBox vertical = AddLabelAndCheckBox("Vertical:", txtStyle.getVertical(), MainGrid, new[] { row, 0, row++, 1 });
            vertical.Click += BoolParam_Click;
            vertical.Tag = BoolParams.Vertical;
            TextBox txtSize = AddLabelAndTextBox("Text size:", txtStyle.textSize().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            txtSize.LostKeyboardFocus += TextParam_LostKeyboardFocus;
            txtSize.Tag = TextParams.TextSize;
            TextBox widthFact = AddLabelAndTextBox("Width factor:", txtStyle.widthFactor().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            widthFact.LostKeyboardFocus += TextParam_LostKeyboardFocus;
            widthFact.Tag = TextParams.WidthFactor;
            CheckBox undelined = AddLabelAndCheckBox("Underlined:", txtStyle.getUnderlined(), MainGrid, new[] { row, 0, row++, 1 });
            undelined.Click += BoolParam_Click;
            undelined.Tag = BoolParams.Underlined;
            CheckBox overlined = AddLabelAndCheckBox("Overlined:", txtStyle.getOverlined(), MainGrid, new[] { row, 0, row++, 1 });
            overlined.Click += BoolParam_Click;
            overlined.Tag = BoolParams.Overlined;
            CheckBox striked = AddLabelAndCheckBox("Striked:", txtStyle.getStriked(), MainGrid, new[] { row, 0, row, 1 });
            striked.Click += BoolParam_Click;
            striked.Tag = BoolParams.Striked;

            MM.StopTransaction(mtr);
        }

        private void TextParam_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextStyle txtStyle = _textStyleId.openObject(OpenMode.kForWrite);
            TextParams param = (TextParams)tb.Tag;
            double val = double.Parse(tb.Text);
            switch (param)
            {
                case TextParams.ObliquingAngle:
                    txtStyle.setObliquingAngle(val);
                    break;
                case TextParams.TextSize:
                    txtStyle.setTextSize(val);
                    break;
                case TextParams.WidthFactor:
                    txtStyle.setWidthFactor(val);
                    break;
            }

            TvDeviceId.openObject().regen(OdTvGsDevice.RegenMode.kRegenAll);
            Update();
            MM.StopTransaction(mtr);

        }

        private void BoolParam_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb != null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvTextStyle txtStyle = _textStyleId.openObject(OpenMode.kForWrite);
            BoolParams param = (BoolParams)cb.Tag;
            bool flag = cb.IsChecked == true;
            switch (param)
            {
                case BoolParams.Backwards:
                    txtStyle.setBackwards(flag);
                    break;
                case BoolParams.Bold:
                    {
                        string typeface = "";
                        bool bold, italic;
                        int charset, pitchAndFamily;
                        txtStyle.getFont(ref typeface, out bold, out italic, out charset, out pitchAndFamily);
                        txtStyle.setFont(typeface, flag, italic, charset, pitchAndFamily);
                        break;
                    }
                case BoolParams.Italic:
                    {
                        string typeface = "";
                        bool bold, italic;
                        int charset, pitchAndFamily;
                        txtStyle.getFont(ref typeface, out bold, out italic, out charset, out pitchAndFamily);
                        txtStyle.setFont(typeface, bold, flag, charset, pitchAndFamily);
                        break;
                    }
                case BoolParams.ShapeStatus:
                    txtStyle.setShapeStatus(flag);
                    break;
                case BoolParams.UpsideDown:
                    txtStyle.setUpsideDown(flag);
                    break;
                case BoolParams.Vertical:
                    txtStyle.setVertical(flag);
                    break;
                case BoolParams.Underlined:
                    txtStyle.setUnderlined(flag);
                    break;
                case BoolParams.Overlined:
                    txtStyle.setOverlined(flag);
                    break;
                case BoolParams.Striked:
                    txtStyle.setStriked(flag);
                    break;
            }
            TvDeviceId.openObject(OpenMode.kForWrite).regen(OdTvGsDevice.RegenMode.kRegenAll);
            TvDeviceId.openObject(OpenMode.kForWrite).viewAt(0).openObject().regen();

            MM.StopTransaction(mtr);
        }

        private void AlignMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _textStyleId.openObject(OpenMode.kForWrite).setAlignmentMode((OdTvTextStyle.AlignmentType)cb.SelectedIndex);
            TvDeviceId.openObject().regen(OdTvGsDevice.RegenMode.kRegenAll);
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

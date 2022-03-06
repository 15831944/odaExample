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
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvLinetypeProperties : BasePaletteProperties
    {
        private OdTvLinetypeId _ltId;

        struct CoordData
        {
            public int Ind;
            public CoordinateType Type;
        }

        public TvLinetypeProperties(OdTvLinetypeId ltId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            _ltId = ltId;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject();
            int row = 0;
            AddLabelAndTextBox("Name:", lt.getName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Description:", lt.getDescription(), MainGrid, new[] { row, 0, row++, 1 }, true);
            CheckBox scaledToFit = AddLabelAndCheckBox("Scaled to fit:", lt.getScaledToFit(), MainGrid, new[] { row, 0, row++, 1 });
            scaledToFit.Click += ScaledToFit_Click;
            StretchingTreeViewItem elements = AddTreeItem("Elements", MainGrid, new[] { row, 0 });
            OdTvLinetypeElementArray elArr = new OdTvLinetypeElementArray();
            lt.getElements(elArr);
            for (int i = 0; i < elArr.Count; i++)
                FillLinetypeElements(elArr[i], elements, i);
            MM.StopTransaction(mtr);
        }

        private void ScaledToFit_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _ltId.openObject(OpenMode.kForWrite).setScaledToFit(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void FillLinetypeElements(OdTvLinetypeElementPtr ltEl, StretchingTreeViewItem parent, int ind)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            StretchingTreeViewItem itm = AddTreeItem("Element_" + ind, MainGrid, null, parent);
            if (ltEl.getAsDash() != null)
            {
                OdTvLinetypeDashElement dash = ltEl.getAsDash();
                AddLabelAndTextBox("Type:", "Dash", itm, true);
                TextBox size = AddLabelAndTextBox("Size:", dash.getSize().ToString(), itm);
                size.LostKeyboardFocus += Size_LostKeyboardFocus;
                size.Tag = ind;
            }
            else if (ltEl.getAsSpace() != null)
            {
                OdTvLinetypeSpaceElement space = ltEl.getAsSpace();
                AddLabelAndTextBox("Type:", "Space", itm, true);
                TextBox size = AddLabelAndTextBox("Size:", space.getSize().ToString(), itm);
                size.LostKeyboardFocus += Size_LostKeyboardFocus;
                size.Tag = ind;
            }
            else if (ltEl.getAsDot() != null)
                AddLabelAndTextBox("Type:", "Dot", itm, true);
            else if (ltEl.getAsShape() != null)
            {
                OdTvLinetypeShapeElement shape = ltEl.getAsShape();
                AddLabelAndTextBox("Type:", "Shape", itm, true);
                AddLabelAndTextBox("Source number:", shape.getSourceNumber().ToString(), itm, true);
                TextBox size = AddLabelAndTextBox("Size:", shape.getSize().ToString(), itm);
                size.LostKeyboardFocus += Size_LostKeyboardFocus;
                size.Tag = ind;
                TextBox[] offset = AddVector2D("Offset", shape.getOffset(), itm);
                foreach (var o in offset)
                {
                    CoordData data = new CoordData { Ind = ind, Type = (CoordinateType)o.Tag };
                    o.Tag = data;
                    o.LostKeyboardFocus += Offset_LostKeyboardFocus;
                }
                ComboBox txtStyle = AddLabelAndComboBox("TextStyle:", GetTextStylesList(), shape.getStyle().openObject().getName(), itm);
                txtStyle.Tag = ind;
                txtStyle.SelectionChanged += TxtStyle_SelectionChanged;
                CheckBox usc = AddLabelAndCheckBox("UCS oriented:", shape.getUcsOriented(), itm);
                usc.Tag = ind;
                usc.Click += Usc_Click;
                CheckBox upRight = AddLabelAndCheckBox("Upright:", shape.getUpright(), itm);
                upRight.Tag = ind;
                upRight.Click += UpRight_Click;
            }
            else if (ltEl.getAsText() != null)
            {
                OdTvLinetypeTextElement text = ltEl.getAsText();
                AddLabelAndTextBox("Type:", "Text", itm, true);
                TextBox txtBox = AddLabelAndTextBox("Text:", text.getText().ToString(), itm);
                txtBox.Tag = ind;
                txtBox.LostKeyboardFocus += Text_LostKeyboardFocus;
                TextBox size = AddLabelAndTextBox("Size:", text.getSize().ToString(), itm);
                size.LostKeyboardFocus += Size_LostKeyboardFocus;
                size.Tag = ind;
                TextBox[] offset = AddVector2D("Offset", text.getOffset(), itm);
                foreach (var o in offset)
                {
                    CoordData data = new CoordData { Ind = ind, Type = (CoordinateType)o.Tag };
                    o.Tag = data;
                }
                ComboBox txtStyle = AddLabelAndComboBox("TextStyle:", GetTextStylesList(), text.getStyle().openObject().getName(), itm);
                txtStyle.Tag = ind;
                txtStyle.SelectionChanged += TxtStyle_SelectionChanged;
                CheckBox usc = AddLabelAndCheckBox("UCS oriented:", text.getUcsOriented(), itm);
                usc.Tag = ind;
                usc.Click += Usc_Click;
                CheckBox upRight = AddLabelAndCheckBox("Upright:", text.getUpright(), itm);
                upRight.Tag = ind;
                upRight.Click += UpRight_Click;
            }
            else
                AddLabelAndTextBox("Type:", "Undefined", itm, true);

            MM.StopTransaction(mtr);
        }

        private void Text_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            tb.Text = tb.Text.Replace(".", ",");
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject(OpenMode.kForWrite);
            OdTvLinetypeElementArray arr = new OdTvLinetypeElementArray();
            lt.getElements(arr);
            OdTvLinetypeElementPtr ltEl = arr[(int)tb.Tag];
            if (ltEl.getAsText() != null)
                ltEl.getAsText().setText(tb.Text);
            lt.setElements(arr);
            Update();
            MM.StopTransaction(mtr);
        }

        private void UpRight_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject(OpenMode.kForWrite);
            OdTvLinetypeElementArray arr = new OdTvLinetypeElementArray();
            lt.getElements(arr);
            OdTvLinetypeElementPtr ltEl = arr[(int)cb.Tag];
            if (ltEl.getAsShape() != null)
                ltEl.getAsShape().setUpright(cb.IsChecked == true);
            else if (ltEl.getAsText() != null)
                ltEl.getAsText().setUpright(cb.IsChecked == true);
            lt.setElements(arr);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Usc_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject(OpenMode.kForWrite);
            OdTvLinetypeElementArray arr = new OdTvLinetypeElementArray();
            lt.getElements(arr);
            OdTvLinetypeElementPtr ltEl = arr[(int)cb.Tag];
            if (ltEl.getAsShape() != null)
                ltEl.getAsShape().setUcsOriented(cb.IsChecked == true);
            else if (ltEl.getAsText() != null)
                ltEl.getAsText().setUcsOriented(cb.IsChecked == true);
            lt.setElements(arr);
            Update();
            MM.StopTransaction(mtr);
        }

        private void TxtStyle_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject(OpenMode.kForWrite);
            OdTvLinetypeElementArray arr = new OdTvLinetypeElementArray();
            lt.getElements(arr);
            OdTvLinetypeElementPtr ltEl = arr[(int)cb.Tag];
            OdTvTextStyleId newTxtStyle = null;
            string name = cb.SelectedItem.ToString();
            if (name.Length > 0)
            {
                OdTvTextStylesIterator it = TvDatabaseId.openObject().getTextStylesIterator();
                while (!it.done())
                {
                    if (it.getTextStyle().openObject().getName() == name)
                    {
                        newTxtStyle = it.getTextStyle();
                        break;
                    }
                    it.step();
                }
            }

            if (ltEl.getAsShape() != null)
                ltEl.getAsShape().setStyle(newTxtStyle);
            else if (ltEl.getAsText() != null)
                ltEl.getAsText().setStyle(newTxtStyle);
            lt.setElements(arr);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Offset_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            tb.Text = tb.Text.Replace(".", ",");
            CoordData data = (CoordData)tb.Tag;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject(OpenMode.kForWrite);
            OdTvLinetypeElementArray arr = new OdTvLinetypeElementArray();
            lt.getElements(arr);
            OdTvLinetypeElementPtr ltEl = arr[data.Ind];
            if (ltEl.getAsShape() != null)
            {
                OdTvLinetypeShapeElement el = ltEl.getAsShape();
                el.setOffset(SetVectorCoordByType(el.getOffset(), data.Type, tb.Text));
            }
            else if (ltEl.getAsText() != null)
            {
                OdTvLinetypeTextElement el = ltEl.getAsText();
                el.setOffset(SetVectorCoordByType(el.getOffset(), data.Type, tb.Text));
            }

            lt.setElements(arr);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Size_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            tb.Text = tb.Text.Replace(".", ",");
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvLinetype lt = _ltId.openObject(OpenMode.kForWrite);
            OdTvLinetypeElementArray arr = new OdTvLinetypeElementArray();
            lt.getElements(arr);
            OdTvLinetypeElementPtr ltEl = arr[(int)tb.Tag];
            if (ltEl.getAsDash() != null)
                ltEl.getAsDash().setSize(Double.Parse(tb.Text));
            else if (ltEl.getAsSpace() != null)
                ltEl.getAsSpace().setSize(Double.Parse(tb.Text));
            else if (ltEl.getAsShape() != null)
                ltEl.getAsShape().setSize(Double.Parse(tb.Text));
            else if (ltEl.getAsText() != null)
                ltEl.getAsText().setSize(Double.Parse(tb.Text));
            lt.setElements(arr);
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

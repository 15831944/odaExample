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

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    public class TvViewProperties : BasePaletteProperties
    {
        private OdTvGsViewId _viewId;

        public TvViewProperties(OdTvGsViewId viewId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            _viewId = viewId;

            MemoryTransaction mtr = MM.StartTransaction();

            int curRow = 0;
            OdTvGsView view = viewId.openObject();

            CheckBox isActive = AddLabelAndCheckBox("Active", view.getActive(), MainGrid, new[] { curRow, 0, curRow++, 1 }, true);
            TextBox[] pos = AddPoint3D("Position:", view.position(), MainGrid, new[] { curRow++, 0 });
            foreach (TextBox tb in pos) tb.LostKeyboardFocus += Pos_LostKeyboardFocus;
            TextBox[] target = AddPoint3D("Target:", view.target(), MainGrid, new[] { curRow++, 0 });
            foreach (TextBox tb in target) tb.LostKeyboardFocus += Target_LostKeyboardFocus;
            TextBox[] upVect = AddVector3D("Up vector:", view.upVector(), MainGrid, new[] { curRow++, 0 });
            foreach (TextBox tb in upVect) tb.LostKeyboardFocus += UpVect_LostKeyboardFocus;
            TextBox fieldWidth = AddLabelAndTextBox("Field width:", view.fieldWidth().ToString(), MainGrid, new[] { curRow, 0, curRow++, 1 });
            fieldWidth.LostKeyboardFocus += FieldWidth_LostKeyboardFocus;
            TextBox fieldHeight = AddLabelAndTextBox("Field height:", view.fieldHeight().ToString(), MainGrid, new[] { curRow, 0, curRow++, 1 });
            fieldHeight.LostKeyboardFocus += FieldHeight_LostKeyboardFocus;

            List<string> modesList = new List<string>()
                { "2DOptimized", "Wireframe", "HiddenLine", "FlatShaded", "GouraudShaded", "FlatShadedWithWireframe", "GouraudShadedWithWireframe" };
            ComboBox mode = AddLabelAndComboBox("Mode:", modesList, (int)view.mode(), MainGrid,
                new[] { curRow, 0, curRow++, 1 });
            mode.SelectionChanged += Mode_SelectionChanged;

            CheckBox isPersp = AddLabelAndCheckBox("Is perspective:", view.isPerspective(), MainGrid, new[] { curRow, 0, curRow++, 1 }, true);
            isPersp.Click += IsPerspective_Click;
            TextBox lensLen = AddLabelAndTextBox("Lens length:", view.lensLength().ToString(), MainGrid, new[] { curRow, 0, curRow++, 1 });
            lensLen.LostKeyboardFocus += LensLen_LostKeyboardFocus;
            CheckBox enableDefLight = AddLabelAndCheckBox("Enable default lighting:", view.defaultLightingEnabled(), MainGrid, new[] { curRow, 0, curRow++, 1 }, true);
            enableDefLight.Click += EnableDefLight_Click;
            List<string> defLightTypes = new List<string>() { "OneLight", "TwoLights", "BackLight" };
            ComboBox defLightType = AddLabelAndComboBox("Default lighting type:", defLightTypes, (int)view.defaultLightingType(), MainGrid, new[] { curRow, 0, curRow++, 1 });
            defLightType.SelectionChanged += DefLightType_SelectionChanged;
            List<string> lwModes = new List<string>() { "DeviceFixed", "WorldFixed", "Indexed" };
            ComboBox linewMode = AddLabelAndComboBox("Lineweight mode:", lwModes, (int)view.getLineWeightMode(), MainGrid, new[] { curRow, 0, curRow++, 1 });
            linewMode.SelectionChanged += LineweightMode_SelectionChanged;
            TextBox lwScale = AddLabelAndTextBox("Lineweight scale:", view.getLineWeightScale().ToString(), MainGrid, new[] { curRow, 0, curRow++, 1 });
            lwScale.LostKeyboardFocus += LineweightScale_LostKeyboardFocus;
            OdTvDCRect rect = new OdTvDCRect();
            view.getViewport(rect);
            TextBox[] sizePix = AddSize("Viewport(Pixel)", rect, MainGrid, new[] { curRow++, 0 });
            foreach (TextBox tb in sizePix) tb.LostKeyboardFocus += ViewportSize_LostKeyboardFocus;
            OdGePoint2d ll = new OdGePoint2d();
            OdGePoint2d ur = new OdGePoint2d();
            view.getViewport(ll, ur);
            TextBox[] sizeRel = AddSize("Viewport(Relative)", new OdTvDCRect((int)ll.x, (int)ur.x, (int)ll.y, (int)ur.y), MainGrid, new[] { curRow++, 0 });
            foreach (TextBox tb in sizeRel) tb.LostKeyboardFocus += ViewportSize_LostKeyboardFocus;

            StretchingTreeViewItem models = AddTreeItem("Models", MainGrid, new[] { curRow++, 0 });
            Grid modelsGrid = CreateGrid(2, view.numModels());
            for (int i = 0; i < view.numModels(); i++)
                AddLabelAndTextBox("Model_" + i, view.modelAt(i).openObject().getName(), modelsGrid, new[] { i, 0, i, 1 }, true);
            AddLabelAndTextBox("Owner(sibling):", view.getSiblingOwner().isNull() ? "" : view.getSiblingOwner().openObject().getName()
                , MainGrid, new[] { curRow, 0, curRow++, 1 }, true);
            AddLabelAndTextBox("Owner(view object):", view.getViewportObjectOwner().isNull() ? "" : view.getViewportObjectOwner().openObject().getName()
                , MainGrid, new[] { curRow, 0, curRow, 1 }, true);
            models.Items.Add(modelsGrid);
            MM.StopTransaction(mtr);
        }

        private void Pos_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            if (view != null)
            {
                view.setView(SetPointCoordByType(view.position(), (CoordinateType)tb.Tag, tb.Text), view.target(),
                    view.upVector(), view.fieldWidth(), view.fieldHeight(),
                    view.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Target_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            if (view != null)
            {
                view.setView(view.position(), SetPointCoordByType(view.target(), (CoordinateType)tb.Tag, tb.Text),
                    view.upVector(), view.fieldWidth(), view.fieldHeight(),
                    view.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void UpVect_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            view.setView(view.position(), view.target(), SetVectorCoordByType(view.upVector(), (CoordinateType)tb.Tag, tb.Text), view.fieldWidth(), view.fieldHeight(),
                view.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
            Update();
            MM.StopTransaction(mtr);
        }

        private void FieldWidth_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            view.setView(view.position(), view.target(), view.upVector(), Convert.ToDouble(tb.Text), view.fieldHeight(),
                view.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
            Update();
            MM.StopTransaction(mtr);
        }

        private void FieldHeight_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            view.setView(view.position(), view.target(), view.upVector(), view.fieldWidth(), Convert.ToDouble(tb.Text),
                view.isPerspective() ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Mode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _viewId.openObject(OpenMode.kForWrite).setMode((OdTvGsView.RenderMode)cb.SelectedIndex);
            Update();
            MM.StopTransaction(mtr);
        }

        private void IsPerspective_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            view.setView(view.position(), view.target(), view.upVector(), view.fieldWidth(), view.fieldHeight(),
                cb.IsChecked == true ? OdTvGsView.Projection.kPerspective : OdTvGsView.Projection.kParallel);
            Update();
            MM.StopTransaction(mtr);
        }

        private void LensLen_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _viewId.openObject(OpenMode.kForWrite).setLensLength(Convert.ToDouble(tb.Text));
            Update();
            MM.StopTransaction(mtr);
        }

        private void EnableDefLight_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _viewId.openObject(OpenMode.kForWrite).enableDefaultLighting(cb.IsChecked == true, _viewId.openObject().defaultLightingType());
            Update();
            MM.StopTransaction(mtr);
        }

        private void DefLightType_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _viewId.openObject(OpenMode.kForWrite).enableDefaultLighting(_viewId.openObject().defaultLightingEnabled(), (OdTvGsView.DefaultLightingType)cb.SelectedIndex + 1);
            Update();
            MM.StopTransaction(mtr);
        }

        private void LineweightMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _viewId.openObject(OpenMode.kForWrite).setLineWeightMode((OdTvGsView.LineWeightMode)cb.SelectedIndex);
            Update();
            MM.StopTransaction(mtr);
        }

        private void LineweightScale_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            _viewId.openObject(OpenMode.kForWrite).setLineWeightScale(Convert.ToDouble(tb.Text));
            Update();
            MM.StopTransaction(mtr);
        }

        private void ViewportSize_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null || OdTvWpfMainWindow.IsClosing)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            double val = Convert.ToDouble(tb.Text.Replace(".", ","));
            OdTvGsView view = _viewId.openObject(OpenMode.kForWrite);
            DcSizeType type = (DcSizeType)tb.Tag;
            if (val < 1)
            {
                OdGePoint2d ll = new OdGePoint2d();
                OdGePoint2d ur = new OdGePoint2d();
                view.getViewport(ll, ur);
                if (type == DcSizeType.xMin)
                    ll.x = val;
                else if (type == DcSizeType.xMax)
                    ur.x = val;
                else if (type == DcSizeType.yMin)
                    ll.y = val;
                else if (type == DcSizeType.yMax)
                    ur.y = val;
                view.setViewport(ll, ur);
            }
            else
            {
                OdTvDCRect rect = new OdTvDCRect();
                view.getViewport(rect);
                if (type == DcSizeType.xMin)
                    rect.xmin = (int)val;
                else if (type == DcSizeType.xMax)
                    rect.xmax = (int)val;
                else if (type == DcSizeType.yMin)
                    rect.ymin = (int)val;
                else if (type == DcSizeType.yMax)
                    rect.ymax = (int)val;
                view.setViewport(rect);
            }
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

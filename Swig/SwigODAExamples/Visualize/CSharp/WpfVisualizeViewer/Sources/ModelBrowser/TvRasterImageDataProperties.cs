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
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvRasterImageDataProperties : TvBaseGeometryProperties
    {
        private enum Properties
        {
            Origin,
            WidthAndDirection,
            Height,
            Brightness,
            ClipInverted,
            Contrast,
            Fade
        }

        private struct NodeData
        {
            public CoordinateType CoordType;
            public Properties Property;
        }

        private OdTvPoint2dArray _pointsArr;
        private bool _isChanged = false;
        private UIElement currentPanel;

        public TvRasterImageDataProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvRasterImageData img = GeomId.openAsRasterImage();
            int row = 0;
            AddLabelAndTextBox("Filename:", img.getImageId().openObject().getSourceFileName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            OdGePoint3d or = new OdGePoint3d();
            OdGeVector3d u = new OdGeVector3d(), v = new OdGeVector3d();
            img.getOrientation(or, u, v);
            TextBox[] origin = AddPoint3D("Origin", or, MainGrid, new[] { row++, 0 });
            foreach (var p in origin)
            {
                p.Tag = new NodeData() { CoordType = (CoordinateType)p.Tag, Property = Properties.Origin };
                p.LostKeyboardFocus += PointType_LostKeyboardFocus;
            }
            TextBox[] widthAndDir = AddVector3D("Width and direction", u, MainGrid, new[] { row++, 0 });
            foreach (var p in widthAndDir)
            {
                p.Tag = new NodeData() { CoordType = (CoordinateType)p.Tag, Property = Properties.WidthAndDirection };
                p.LostKeyboardFocus += PointType_LostKeyboardFocus;
            }
            TextBox[] height = AddVector3D("Height", u, MainGrid, new[] { row++, 0 });
            foreach (var p in height)
            {
                p.Tag = new NodeData() { CoordType = (CoordinateType)p.Tag, Property = Properties.Height };
                p.LostKeyboardFocus += PointType_LostKeyboardFocus;
            }

            AddVector2D("Image size", img.getImageSize(), MainGrid, new[] { row++, 0 }, true);

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            TextBox brightness = AddLabelAndTextBox("Brightness:", img.getBrightness().ToString(), misc);
            brightness.Tag = Properties.Brightness;
            brightness.LostKeyboardFocus += SimpleTextType_LostKeyboardFocus;
            CheckBox clipInv = AddLabelAndCheckBox("Clip inverted:", img.getClipInverted(), misc);
            clipInv.Tag = Properties.ClipInverted;
            clipInv.Click += BoolType_Click;
            CheckBox clipped = AddLabelAndCheckBox("Clipped:", img.getClipped(), misc);
            TextBox contrast = AddLabelAndTextBox("Contrast:", img.getContrast().ToString(), misc);
            contrast.Tag = Properties.Contrast;
            contrast.LostKeyboardFocus += SimpleTextType_LostKeyboardFocus;
            TextBox fade = AddLabelAndTextBox("Fade:", img.getFade().ToString(), misc);
            fade.Tag = Properties.Fade;
            fade.LostKeyboardFocus += SimpleTextType_LostKeyboardFocus;
            Button clipBoundary = AddLabelAndButton("Clip boundary", "...", misc);
            clipBoundary.Click += ClipBoundary_Click;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);

            MM.StopTransaction(mtr);
        }

        private void ClipBoundary_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvRasterImageData img = GeomId.openAsRasterImage();
            _pointsArr = new OdTvPoint2dArray();
            img.getClipBoundary(_pointsArr);
            if (!CheckCountOfObject(_pointsArr.Count))
            {
                _pointsArr.Clear();
                MM.StopTransaction(mtr);
                return;
            }

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };

            LoadPoints();

            if (CreateDialog("Clip boundary", new Size(300, 300), currentPanel).ShowDialog() == true && _isChanged)
            {
                img.setClipBoundary(_pointsArr);
                Update();
            }
            _pointsArr.Clear();
            MM.StopTransaction(mtr);
        }

        private void LoadPoints()
        {
            for (int i = 0; i < _pointsArr.Count; i++)
            {
                StretchingTreeViewItem itm = AddTreeItem("Point_" + i, (StretchingTreeView)currentPanel);
                itm.Tag = i;
                itm.Items.Add(null);
                itm.Expanded += Point_Expanded;
            }
        }

        private void Point_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            TextBox[] pnt = GetXy(itm, _pointsArr[(int)itm.Tag]);
            foreach (var p in pnt)
            {
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
                p.Margin = new Thickness(0, 0, 0, 2);
            }
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            Grid grid = (Grid)tb.Parent;
            StretchingTreeViewItem parent = (StretchingTreeViewItem)grid.Parent;
            int ind = (int)parent.Tag;
            CoordinateType type = (CoordinateType)tb.Tag;
            OdGePoint2d newPt = SetPointCoordByType(_pointsArr[ind], type, tb.Text);
            if (newPt != _pointsArr[ind])
            {
                _pointsArr[ind] = newPt;
                if (!_isChanged) _isChanged = true;
            }
        }

        private void BoolType_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvRasterImageData img = GeomId.openAsRasterImage();
            img.setClipInverted(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void SimpleTextType_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvRasterImageData img = GeomId.openAsRasterImage();
            sbyte val = sbyte.Parse(tb.Text);
            switch ((Properties)tb.Tag)
            {
                case Properties.Brightness:
                    if (img.getBrightness() != val)
                        img.setBrightness(val);
                    break;
                case Properties.Contrast:
                    if (img.getContrast() != val)
                        img.setContrast(val);
                    break;
                case Properties.Fade:
                    if (img.getFade() != val)
                        img.setFade(val);
                    break;
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void PointType_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvRasterImageData img = GeomId.openAsRasterImage();
            OdGePoint3d or = new OdGePoint3d();
            OdGeVector3d u = new OdGeVector3d(), v = new OdGeVector3d();
            img.getOrientation(or, u, v);
            NodeData data = (NodeData)tb.Tag;
            switch (data.Property)
            {
                case Properties.Origin:
                    {
                        OdGePoint3d newPt = SetPointCoordByType(or, data.CoordType, tb.Text);
                        if (newPt != or)
                            img.setOrientation(newPt, u, v);
                        break;
                    }
                case Properties.WidthAndDirection:
                    {
                        OdGeVector3d newV = SetVectorCoordByType(u, data.CoordType, tb.Text);
                        if (newV != u)
                            img.setOrientation(or, newV, v);
                        break;
                    }
                case Properties.Height:
                    {
                        OdGeVector3d newV = SetVectorCoordByType(v, data.CoordType, tb.Text);
                        if (newV != v)
                            img.setOrientation(or, u, newV);
                        break;
                    }
            }
            Update();
            MM.StopTransaction(mtr);
        }
    }
}

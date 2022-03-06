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

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvEllipseProperties : TvBaseGeometryProperties
    {
        private enum PointType
        {
            Center,
            Major,
            Minor
        }

        private struct NodeData
        {
            public CoordinateType CoordType;
            public PointType PType;

            public NodeData(CoordinateType ctype, PointType ptype)
            {
                CoordType = ctype;
                PType = ptype;
            }
        }

        public TvEllipseProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipseData ellip = GeomId.openAsEllipse();
            int row = 0;
            TextBox[] center = AddPoint3D("Center", ellip.getCenter(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in center)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Center);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] maj = AddPoint3D("Major point", ellip.getMajor(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in maj)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Major);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] end = AddPoint3D("Minor point", ellip.getMinor(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in end)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Minor);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            TextBox thickness = AddLabelAndTextBox("Thickness:", ellip.getThickness().ToString(), misc);
            thickness.LostKeyboardFocus += Thickness_LostKeyboardFocus;
            CheckBox filled = AddLabelAndCheckBox("Filled:", ellip.getFilled(), misc);
            filled.Click += Filled_Click;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);
            MM.StopTransaction(mtr);

        }

        private void Thickness_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipseData ellip = GeomId.openAsEllipse();
            if (!ellip.getThickness().Equals(double.Parse(tb.Text)))
            {
                ellip.setThickness(double.Parse(tb.Text));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Filled_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsEllipse().setFilled(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipseData ellip = GeomId.openAsEllipse();
            NodeData data = (NodeData)tb.Tag;

            switch (data.PType)
            {
                case PointType.Center:
                    OdGePoint3d newCenter = SetPointCoordByType(ellip.getCenter(), data.CoordType, tb.Text);
                    if (newCenter != ellip.getCenter())
                        ellip.setCenter(newCenter);
                    break;
                case PointType.Major:
                    OdGePoint3d newMaj = SetPointCoordByType(ellip.getMajor(), data.CoordType, tb.Text);
                    if (newMaj != ellip.getMajor())
                        ellip.setMajor(newMaj);
                    break;
                case PointType.Minor:
                    OdGePoint3d newMinor = SetPointCoordByType(ellip.getMinor(), data.CoordType, tb.Text);
                    if (newMinor != ellip.getMinor())
                        ellip.setMinor(newMinor);
                    break;
            }

            Update();
            MM.StopTransaction(mtr);
        }
    }
}

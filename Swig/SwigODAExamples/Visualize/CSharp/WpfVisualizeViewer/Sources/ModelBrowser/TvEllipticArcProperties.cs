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
    class TvEllipticArcProperties : TvBaseGeometryProperties
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

        public TvEllipticArcProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipticArcData arc = GeomId.openAsEllipticArc();
            int row = 0;
            TextBox[] center = AddPoint3D("Center", arc.getCenter(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in center)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Center);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] maj = AddPoint3D("Major point", arc.getMajor(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in maj)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Major);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] minor = AddPoint3D("Minor point", arc.getMinor(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in minor)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Minor);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox start = AddLabelAndTextBox("Start:", arc.getStart().ToString(), MainGrid, new[] {row, 0, row++, 1});
            start.LostKeyboardFocus += Start_LostKeyboardFocus;
            TextBox end = AddLabelAndTextBox("End:", arc.getEnd().ToString(), MainGrid, new[] { row, 0, row++, 1 });
            end.LostKeyboardFocus += End_LostKeyboardFocus;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            TextBox thickness = AddLabelAndTextBox("Thickness:", arc.getThickness().ToString(), misc);
            thickness.LostKeyboardFocus += Thickness_LostKeyboardFocus;
            CheckBox filled = AddLabelAndCheckBox("Filled:", arc.getFilled(), misc);
            filled.Click += Filled_Click;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);
            MM.StopTransaction(mtr);

        }

        private void End_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipticArcData arc = GeomId.openAsEllipticArc();
            if (!arc.getEnd().Equals(double.Parse(tb.Text)))
            {
                arc.setEnd(double.Parse(tb.Text));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Start_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipticArcData arc = GeomId.openAsEllipticArc();
            if (!arc.getStart().Equals(double.Parse(tb.Text)))
            {
                arc.setStart(double.Parse(tb.Text));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Thickness_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipticArcData arc = GeomId.openAsEllipticArc();
            if (!arc.getThickness().Equals(double.Parse(tb.Text)))
            {
                arc.setThickness(double.Parse(tb.Text));
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
            GeomId.openAsEllipticArc().setFilled(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEllipticArcData arc = GeomId.openAsEllipticArc();
            NodeData data = (NodeData)tb.Tag;

            switch (data.PType)
            {
                case PointType.Center:
                    OdGePoint3d newCenter = SetPointCoordByType(arc.getCenter(), data.CoordType, tb.Text);
                    if (newCenter != arc.getCenter())
                        arc.setCenter(newCenter);
                    break;
                case PointType.Major:
                    OdGePoint3d newMaj = SetPointCoordByType(arc.getMajor(), data.CoordType, tb.Text);
                    if (newMaj != arc.getMajor())
                        arc.setMajor(newMaj);
                    break;
                case PointType.Minor:
                    OdGePoint3d newMinor = SetPointCoordByType(arc.getMinor(), data.CoordType, tb.Text);
                    if (newMinor != arc.getMinor())
                        arc.setMinor(newMinor);
                    break;
            }

            Update();
            MM.StopTransaction(mtr);
        }
    }
}

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
    class TvCircWedgeProperties : TvBaseGeometryProperties
    {
        private enum PointType
        {
            Start,
            Middle,
            End
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

        public TvCircWedgeProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvCircleWedgeData wedge = GeomId.openAsCircleWedge();
            int row = 0;
            TextBox[] start = AddPoint3D("Start", wedge.getStart(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in start)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Start);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] mid = AddPoint3D("Middle", wedge.getMiddle(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in mid)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Middle);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] end = AddPoint3D("End", wedge.getEnd(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in end)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.End);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            TextBox thickness = AddLabelAndTextBox("Thickness:", wedge.getThickness().ToString(), misc);
            thickness.LostKeyboardFocus += Thickness_LostKeyboardFocus;
            CheckBox filled = AddLabelAndCheckBox("Filled:", wedge.getFilled(), misc);
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
            OdTvCircleWedgeData wed = GeomId.openAsCircleWedge();
            if (!wed.getThickness().Equals(double.Parse(tb.Text)))
            {
                wed.setThickness(double.Parse(tb.Text));
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
            GeomId.openAsCircleWedge().setFilled(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvCircleWedgeData wed = GeomId.openAsCircleWedge();
            NodeData data = (NodeData)tb.Tag;

            switch (data.PType)
            {
                case PointType.Start:
                    OdGePoint3d newStart = SetPointCoordByType(wed.getStart(), data.CoordType, tb.Text);
                    if (newStart != wed.getStart())
                        wed.setStart(newStart);
                    break;
                case PointType.Middle:
                    OdGePoint3d newMid = SetPointCoordByType(wed.getMiddle(), data.CoordType, tb.Text);
                    if (newMid != wed.getMiddle())
                        wed.setMiddle(newMid);
                    break;
                case PointType.End:
                    OdGePoint3d newEnd = SetPointCoordByType(wed.getEnd(), data.CoordType, tb.Text);
                    if (newEnd != wed.getEnd())
                        wed.setEnd(newEnd);
                    break;
            }

            Update();
            MM.StopTransaction(mtr);
        }
    }
}

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
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvPolylineProperties : TvBaseGeometryProperties
    {
        private struct NodeData
        {
            public CoordinateType CoordType;
            public int Index;

            public NodeData(CoordinateType type, int ind)
            {
                CoordType = type;
                Index = ind;
            }
        }

        private List<int> _changedIndexes = new List<int>();

        public TvPolylineProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
          : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolylineData line = GeomId.openAsPolyline();
            int row = 0;
            AddLabelAndTextBox("Number of points:", line.getPointsCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            Button btn = AddLabelAndButton("Points:", "...", MainGrid, new[] { row, 0, row++, 1 });
            btn.Click += ShowPoint_Click;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            bool bFilled;
            TextBox thickness = AddLabelAndTextBox("Thickness:", line.getThickness(out bFilled).ToString(CultureInfo.InvariantCulture), misc);
            thickness.LostKeyboardFocus += Thickness_LostKeyboardFocus;
            CheckBox filled = AddLabelAndCheckBox("Filled:", bFilled, misc);
            filled.Click += Filled_Click;
            OdGeVector3d vnormal = new OdGeVector3d();
            line.getNormal(vnormal);
            TextBox[] normal = AddVector3D("Normal", vnormal, misc);
            foreach (var n in normal)
                n.LostKeyboardFocus += Normal_LostKeyboardFocus;

            StretchingTreeViewItem common = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(common);

            MM.StopTransaction(mtr);
        }

        private void Normal_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolylineData line = GeomId.openAsPolyline();
            OdGeVector3d oldVec = new OdGeVector3d();
            line.getNormal(oldVec);
            OdGeVector3d newVec = SetVectorCoordByType(oldVec, (CoordinateType)tb.Tag, tb.Text);
            if (oldVec != newVec)
            {
                line.setNormal(newVec);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Filled_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolylineData line = GeomId.openAsPolyline();
            bool bFilled;
            line.setThickness(line.getThickness(out bFilled), cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Thickness_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolylineData line = GeomId.openAsPolyline();
            double val = double.Parse(tb.Text);
            bool bFilled;
            if (Math.Abs(line.getThickness(out bFilled) - val) > 0.001)
            {
                line.setThickness(val);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void ShowPoint_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolylineData line = GeomId.openAsPolyline();
            OdTvPointArray pnts = new OdTvPointArray();
            line.getPoints(pnts);

            StretchingTreeView tree = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch
            };

            List<TextBox> textBoxes = new List<TextBox>();
            for (int i = 0; i < pnts.Count; i++)
            {
                TextBox[] pnt = AddPoint3D("Point_" + i, pnts[i], tree);
                foreach (var p in pnt)
                {
                    p.Tag = new NodeData((CoordinateType)p.Tag, i);
                    p.LostKeyboardFocus += Point_LostKeyboardFocus;
                    textBoxes.Add(p);
                }
            }

            if (CreateDialog("Polyline points", new Size(250, 270), tree).ShowDialog() == true)
            {
                bool isNeedUpdate = false;
                foreach (var i in _changedIndexes)
                {
                    int ind = i / 3;
                    NodeData data = (NodeData)textBoxes[i].Tag;
                    OdGePoint3d newPt = SetPointCoordByType(pnts[ind], data.CoordType, textBoxes[i].Text);
                    if (newPt != pnts[ind])
                    {
                        pnts[ind] = newPt;
                        isNeedUpdate = true;
                    }
                }
                if (isNeedUpdate)
                {
                    line.setPoints(pnts);
                    Update();
                }
            }

            MM.StopTransaction(mtr);
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            NodeData data = (NodeData)tb.Tag;
            int newInd = data.CoordType == CoordinateType.X ? data.Index * 3 :
                data.CoordType == CoordinateType.Y ? data.Index * 3 + 1 : data.Index * 3 + 2;
            if (!_changedIndexes.Contains(newInd))
                _changedIndexes.Add(newInd);
        }
    }
}

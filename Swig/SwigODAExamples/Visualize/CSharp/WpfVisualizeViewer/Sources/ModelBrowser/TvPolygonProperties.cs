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
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvPolygonProperties : TvBaseGeometryProperties
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

        public TvPolygonProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
          : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolygonData pol = GeomId.openAsPolygon();
            int row = 0;
            AddLabelAndTextBox("Number of points:", pol.getPointsCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            Button btn = AddLabelAndButton("Points:", "...", MainGrid, new[] { row, 0, row++, 1 });
            btn.Click += ShowPoint_Click;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            CheckBox filled = AddLabelAndCheckBox("Filled:", pol.getFilled(), misc);
            filled.Click += Filled_Click;
            CheckBox invNormal = AddLabelAndCheckBox("Use inverse normal:", pol.getUseInverseNormal(), misc);
            invNormal.Click += InvNormal_Click;

            StretchingTreeViewItem common = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(common);

            MM.StopTransaction(mtr);
        }

        private void InvNormal_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsPolygon().setUseInverseNormal(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Filled_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsPolygon().setFilled(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void ShowPoint_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPolygonData pol = GeomId.openAsPolygon();
            OdTvPointArray pnts = new OdTvPointArray();
            pol.getPoints(pnts);

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
                    pol.setPoints(pnts);
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

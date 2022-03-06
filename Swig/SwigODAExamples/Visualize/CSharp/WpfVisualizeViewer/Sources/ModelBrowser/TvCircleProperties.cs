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
    class TvCircleProperties : TvBaseGeometryProperties
    {
        public TvCircleProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvCircleData circ = GeomId.openAsCircle();
            int row = 0;
            TextBox[] center = AddPoint3D("Center", circ.getCenter(), MainGrid, new[] {row, 0, row++, 1});
            foreach (var p in center)
                p.LostKeyboardFocus += Center_LostKeyboardFocus;
            TextBox radius = AddLabelAndTextBox("Radius:", circ.getRadius().ToString(), MainGrid, new[] {row, 0, row++, 1});
            radius.LostKeyboardFocus += Radius_LostKeyboardFocus;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] {row++, 0});
            TextBox[] normal = AddVector3D("Normal", circ.getNormal(), misc);
            foreach (var p in normal)
                p.LostKeyboardFocus += Normal_LostKeyboardFocus;
            CheckBox filled = AddLabelAndCheckBox("Filled:", circ.getFilled(), misc);
            filled.Click += Filled_Click;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] {row, 0});
            GetProperties(cmn);
            MM.StopTransaction(mtr);
        }

        private void Filled_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsCircle().setFilled(cb.IsChecked == true);
            Update();
            MM.StopTransaction(mtr);
        }

        private void Normal_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvCircleData circ = GeomId.openAsCircle();
            OdGeVector3d newVec = SetVectorCoordByType(circ.getNormal(), (CoordinateType)tb.Tag, tb.Text);
            if (circ.getNormal() != newVec)
            {
                circ.setNormal(newVec);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Radius_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvCircleData circ = GeomId.openAsCircle();
            if (!circ.getRadius().Equals(double.Parse(tb.Text)))
            {
                circ.setRadius(double.Parse(tb.Text));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Center_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvCircleData circ = GeomId.openAsCircle();
            OdGePoint3d newPt = SetPointCoordByType(circ.getCenter(), (CoordinateType)tb.Tag, tb.Text);
            if (circ.getCenter() != newPt)
            {
                circ.setCenter(newPt);
                Update();
            }
            MM.StopTransaction(mtr);
        }
    }
}

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
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvInfiniteLineProperties : TvBaseGeometryProperties
    {
        public TvInfiniteLineProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInfiniteLineData iline = GeomId.openAsInfiniteLine();
            int row = 0;
            TextBox[] fPt = AddPoint3D("First point", iline.getFirst(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in fPt)
                p.LostKeyboardFocus += FirstPoint_LostKeyboardFocus;
            TextBox[] sPt = AddPoint3D("Second point", iline.getSecond(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in sPt)
                p.LostKeyboardFocus += SecondPoint_LostKeyboardFocus;

            List<string> list = new List<string>() { "Ray", "Line" };
            ComboBox type = AddLabelAndComboBox("Type of line", list, (int) iline.getType(), MainGrid, new[] {row, 0, row++, 1});
            type.SelectionChanged += Type_SelectionChanged;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);
            MM.StopTransaction(mtr);

        }

        private void Type_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if(cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsInfiniteLine().setType((OdTvInfiniteLineData.Type) cb.SelectedIndex);
            Update();
            MM.StopTransaction(mtr);
        }

        private void SecondPoint_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInfiniteLineData iline = GeomId.openAsInfiniteLine();
            OdGePoint3d newPt = SetPointCoordByType(iline.getSecond(), (CoordinateType) tb.Tag, tb.Text);
            if (iline.getSecond() != newPt)
            {
                iline.setSecond(newPt);
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void FirstPoint_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvInfiniteLineData iline = GeomId.openAsInfiniteLine();
            OdGePoint3d newPt = SetPointCoordByType(iline.getFirst(), (CoordinateType)tb.Tag, tb.Text);
            if (iline.getFirst() != newPt)
            {
                iline.setFirst(newPt);
                Update();
            }
            MM.StopTransaction(mtr);
        }
    }
}

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

using System.Globalization;
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvSphereProperties : TvBaseGeometryProperties
    {
        private enum PointType
        {
            Center,
            Axis,
            PrimeMeridian
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

        public TvSphereProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvSphereData sphere = GeomId.openAsSphere();
            int row = 0;
            TextBox[] center = AddPoint3D("Center", sphere.getCenter(), MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in center)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Center);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox rad = AddLabelAndTextBox("Radius:", sphere.getRadius().ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            rad.LostKeyboardFocus += Radius_LostKeyboardFocus;

            OdGeVector3d axis = new OdGeVector3d(), prMer = new OdGeVector3d();
            sphere.getBasis(axis, prMer);
            TextBox[] axisBoxs = AddVector3D("Axis", axis, MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in axisBoxs)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.Axis);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            TextBox[] prMeridianBoxs = AddVector3D("Prime meridian", prMer, MainGrid, new[] { row, 0, row++, 1 });
            foreach (var p in prMeridianBoxs)
            {
                p.Tag = new NodeData((CoordinateType)p.Tag, PointType.PrimeMeridian);
                p.LostKeyboardFocus += Point_LostKeyboardFocus;
            }

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);
            MM.StopTransaction(mtr);

        }

        private void Radius_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvSphereData sphere = GeomId.openAsSphere();
            if (!sphere.getRadius().Equals(double.Parse(tb.Text)))
            {
                sphere.setRadius(double.Parse(tb.Text));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        private void Point_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvSphereData sphere = GeomId.openAsSphere();
            NodeData data = (NodeData)tb.Tag;

            switch (data.PType)
            {
                case PointType.Center:
                    OdGePoint3d newCenter = SetPointCoordByType(sphere.getCenter(), data.CoordType, tb.Text);
                    if (newCenter != sphere.getCenter())
                        sphere.setCenter(newCenter);
                    break;
                case PointType.Axis:
                    {
                        OdGeVector3d axis = new OdGeVector3d(), prMer = new OdGeVector3d();
                        sphere.getBasis(axis, prMer);
                        OdGeVector3d newV = SetVectorCoordByType(axis, data.CoordType, tb.Text);
                        if (axis != newV)
                            sphere.setBasis(newV, prMer);
                        break;
                    }
                case PointType.PrimeMeridian:
                {
                    OdGeVector3d axis = new OdGeVector3d(), prMer = new OdGeVector3d();
                    sphere.getBasis(axis, prMer);
                    OdGeVector3d newV = SetVectorCoordByType(prMer, data.CoordType, tb.Text);
                    if (prMer != newV)
                        sphere.setBasis(axis, newV);
                    break;
                }
            }

            Update();
            MM.StopTransaction(mtr);
        }
    }
}

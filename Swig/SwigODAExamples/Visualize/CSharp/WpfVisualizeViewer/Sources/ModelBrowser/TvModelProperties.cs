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
using System.Windows;
using Teigha.Visualize;
using MessageBox = System.Windows.Forms.MessageBox;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvModelProperties : BasePaletteProperties
    {
        private OdTvModelId _modelId;

        public TvModelProperties(OdTvModelId modelId, int countOfChild, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            _modelId = modelId;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvModel model = _modelId.openObject();
            int row = 0;
            AddLabelAndTextBox("Name:", model.getName(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of entities:", countOfChild.ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            Button btn = AddLabelAndButton("Show statistic", "...", MainGrid, new[] { row, 0, row, 1 });
            btn.Click += ShowStatBtn_Click;
            MM.StopTransaction(mtr);
        }

        private void ShowStatBtn_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvModel model = _modelId.openObject();
            OdTvGeometryStatistic stat = model.getStatistic();

            StackPanel panel = new StackPanel { HorizontalAlignment = HorizontalAlignment.Stretch, VerticalAlignment = VerticalAlignment.Stretch };

            bool isEmpty = true;

            if (stat.getCount(OdTvGeometryStatistic.Types.kEntity) > 0 || stat.getCount(OdTvGeometryStatistic.Types.kLight) > 0
                || stat.getCount(OdTvGeometryStatistic.Types.kInsert) > 0)
            {
                isEmpty = false;
                GroupBox gb = new GroupBox { Header = "Entity objects" };
                Grid grid = CreateGrid(2, 3);
                panel.Children.Add(gb);
                int row = 0;
                if (stat.getCount(OdTvGeometryStatistic.Types.kEntity) > 0)
                    AddLabelAndTextBox("Number of entities:", stat.getCount(OdTvGeometryStatistic.Types.kEntity).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kLight) > 0)
                    AddLabelAndTextBox("Number of lights:", stat.getCount(OdTvGeometryStatistic.Types.kLight).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kInsert) > 0)
                    AddLabelAndTextBox("Number of inserts:", stat.getCount(OdTvGeometryStatistic.Types.kInsert).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                gb.Content = grid;
            }

            ulong sum = 0;
            for (uint i = (uint)OdTvGeometryStatistic.Types.kPolyline; i < (uint)OdTvGeometryStatistic.Types.kPoints; i++)
                sum += stat.getCount((OdTvGeometryStatistic.Types)i);

            if (sum > 0)
            {
                isEmpty = false;
                GroupBox gb = new GroupBox { Header = "Geometry objects" };
                Grid grid = CreateGrid(2, 20);
                panel.Children.Add(gb);
                gb.Content = grid;
                int row = 0;
                if (stat.getCount(OdTvGeometryStatistic.Types.kPolyline) > 0)
                    AddLabelAndTextBox("Number of polylines:", stat.getCount(OdTvGeometryStatistic.Types.kPolyline).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kCircle) > 0)
                    AddLabelAndTextBox("Number of circles:", stat.getCount(OdTvGeometryStatistic.Types.kCircle).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kCircleWedge) > 0)
                    AddLabelAndTextBox("Number of circle wedges:", stat.getCount(OdTvGeometryStatistic.Types.kCircleWedge).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kCircularArc) > 0)
                    AddLabelAndTextBox("Number of circle arcs:", stat.getCount(OdTvGeometryStatistic.Types.kCircularArc).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kEllipse) > 0)
                    AddLabelAndTextBox("Number of ellipses:", stat.getCount(OdTvGeometryStatistic.Types.kEllipse).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kEllipticArc) > 0)
                    AddLabelAndTextBox("Number of elliptic arcs:", stat.getCount(OdTvGeometryStatistic.Types.kEllipticArc).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kPolygon) > 0)
                    AddLabelAndTextBox("Number of polygons:", stat.getCount(OdTvGeometryStatistic.Types.kPolygon).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kText) > 0)
                    AddLabelAndTextBox("Number of text:", stat.getCount(OdTvGeometryStatistic.Types.kText).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kShell) > 0)
                    AddLabelAndTextBox("Number of shells:", stat.getCount(OdTvGeometryStatistic.Types.kShell).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kSphere) > 0)
                    AddLabelAndTextBox("Number of spheres:", stat.getCount(OdTvGeometryStatistic.Types.kSphere).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kCylinder) > 0)
                    AddLabelAndTextBox("Number of cylinders:", stat.getCount(OdTvGeometryStatistic.Types.kCylinder).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kGeomInsert) > 0)
                    AddLabelAndTextBox("Number of inserts:", stat.getCount(OdTvGeometryStatistic.Types.kGeomInsert).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kSubEntity) > 0)
                    AddLabelAndTextBox("Number of sub entities:", stat.getCount(OdTvGeometryStatistic.Types.kSubEntity).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kNurbs) > 0)
                    AddLabelAndTextBox("Number of nurbs:", stat.getCount(OdTvGeometryStatistic.Types.kNurbs).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kRasterImage) > 0)
                    AddLabelAndTextBox("Number of raster images:", stat.getCount(OdTvGeometryStatistic.Types.kRasterImage).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kInfiniteLine) > 0)
                    AddLabelAndTextBox("Number of infinite lines:", stat.getCount(OdTvGeometryStatistic.Types.kInfiniteLine).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kMesh) > 0)
                    AddLabelAndTextBox("Number of meshes:", stat.getCount(OdTvGeometryStatistic.Types.kMesh).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kPointCloud) > 0)
                    AddLabelAndTextBox("Number of point clouds:", stat.getCount(OdTvGeometryStatistic.Types.kPointCloud).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kGrid) > 0)
                    AddLabelAndTextBox("Number of grids:", stat.getCount(OdTvGeometryStatistic.Types.kGrid).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kColoredShape) > 0)
                    AddLabelAndTextBox("Number of colored shapes:", stat.getCount(OdTvGeometryStatistic.Types.kColoredShape).ToString(), grid, new[] { row, 0, row++, 1 }, true);
            }

            if (stat.getCount(OdTvGeometryStatistic.Types.kFace) > 0 || stat.getCount(OdTvGeometryStatistic.Types.kPoints) > 0)
            {
                isEmpty = false;
                GroupBox gb = new GroupBox { Header = "Geometry info" };
                Grid grid = CreateGrid(2, 2);
                gb.Content = grid;
                panel.Children.Add(gb);
                int row = 0;
                if (stat.getCount(OdTvGeometryStatistic.Types.kPoints) > 0)
                    AddLabelAndTextBox("Number of points:", stat.getCount(OdTvGeometryStatistic.Types.kPoints).ToString(), grid, new[] { row, 0, row++, 1 }, true);
                if (stat.getCount(OdTvGeometryStatistic.Types.kFace) > 0)
                    AddLabelAndTextBox("Number of faces:", stat.getCount(OdTvGeometryStatistic.Types.kFace).ToString(), grid, new[] { row, 0, row++, 1 }, true);
            }

            if (isEmpty)
            {
                MessageBox.Show("Model statistic", "Model is empty.", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Information);
                MM.StopTransaction(mtr);
                return;
            }

            CreateDialog("Model statistic", new Size(300, 300), panel).ShowDialog();

            MM.StopTransaction(mtr);
        }
    }
}

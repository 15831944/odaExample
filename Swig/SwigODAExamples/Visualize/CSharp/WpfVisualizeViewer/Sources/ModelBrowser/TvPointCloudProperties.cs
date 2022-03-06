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
    class TvPointCloudProperties : TvBaseGeometryProperties
    {
        private enum TypeOfPropety
        {
            Points,
            Colors,
            Normals
        }

        private TypeOfPropety _type;
        private int CountOfLoadedObjects = 200;
        private bool isChanged = false;
        private UIElement currentPanel;
        private int _countOfLoadedObjects = 0;
        // need for elements wothout child
        private bool _isScrollableControl = false;

        private OdTvPointArray _pointsArr;
        private OdTvPointArray _bufPointsArr;
        private OdInt32Array _intArr;
        private OdTvRGBColorDefArray _colorArr;
        private OdTvRGBColorDefArray _bufColorArr;
        private OdTvVectorArray _vecArr;
        private OdTvVectorArray _bufVecArr;

        public TvPointCloudProperties(OdTvGeometryDataId id, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(id, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPointCloudData cloud = GeomId.openAsPointCloud();
            int row = 0;
            AddLabelAndTextBox("Number of points:", cloud.getPointsCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            TextBox pSize = AddLabelAndTextBox("Point size:", cloud.getPointSize().ToString(), MainGrid, new[] {row, 0, row++, 1});
            pSize.LostKeyboardFocus += PSize_LostKeyboardFocus;
            Button pnts = AddLabelAndButton("Points", "...", MainGrid, new[] {row, 0, row++, 1});
            pnts.Click += ShowVertices_Click;
            _colorArr = new OdTvRGBColorDefArray();
            cloud.getPointColorsViaRange(0, cloud.getPointsCount(), _colorArr);
            Button colors = AddLabelAndButton("Points colors", "...", MainGrid, new[] { row, 0, row++, 1 }, _colorArr.Count == 0);
            colors.Click += ShowVerticesColors_Click;
            _colorArr = null;
            _vecArr = new OdTvVectorArray();
            cloud.getPointNormalsViaRange(0, cloud.getPointsCount(), _vecArr);
            Button normals = AddLabelAndButton("Points normals", "...", MainGrid, new[] { row, 0, row++, 1 }, _vecArr.Count == 0);
            normals.Click += ShowVertexNormals_Click;
            _vecArr = null;

            StretchingTreeViewItem common = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(common);
            MM.StopTransaction(mtr);
        }

        protected override void ScrollDialog_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            ScrollViewer sv = sender as ScrollViewer;
            if (sv == null)
                return;

            double max = _isScrollableControl ? sv.ScrollableHeight : _countOfLoadedObjects * 26;
            double cur = sv.VerticalOffset;
            if ((cur / max * 100) >= 90)
            {
                switch (_type)
                {
                    case TypeOfPropety.Points:
                        LoadPoints();
                        break;
                    case TypeOfPropety.Colors:
                        LoadVerticesColors();
                        break;
                    case TypeOfPropety.Normals:
                        LoadVertexNormals();
                        break;
                }
            }
        }

        private void PSize_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if(tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPointCloudData cloud = GeomId.openAsPointCloud();
            if (cloud.getPointSize() != int.Parse(tb.Text))
            {
                cloud.setPointSize(int.Parse(tb.Text));
                Update();
            }
            MM.StopTransaction(mtr);
        }

        #region Vertices

        private void ShowVertices_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPointCloudData cloud = GeomId.openAsPointCloud();
            _pointsArr = cloud.getParam();
            _intArr = new OdInt32Array();
            _bufPointsArr = new OdTvPointArray();

            if (!CheckCountOfObject(_pointsArr.Count))
            {
                _pointsArr.Clear();
                _bufPointsArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.Points;

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };
            _isScrollableControl = true;
            LoadPoints();
            if (CreateDialog("Vertices", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                cloud.editPointsViaList(_intArr, _bufPointsArr);
                Update();
            }
            _pointsArr.Clear();
            _bufPointsArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadPoints()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _pointsArr.Count)
                    return;
                StretchingTreeViewItem itm = AddTreeItem("Vertex_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
                itm.Tag = _countOfLoadedObjects;
                itm.Items.Add(null);
                itm.Expanded += Vertex_Expanded;
            }
        }

        private void Vertex_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            TextBox[] pnt = GetXyz(itm, _pointsArr[(int)itm.Tag]);
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
            OdGePoint3d newPt = SetPointCoordByType(_pointsArr[ind], type, tb.Text);
            if (!_intArr.Contains(ind) && newPt != _pointsArr[ind])
            {
                _bufPointsArr.Add(newPt);
                _intArr.Add(ind);
                if (!isChanged) isChanged = true;
            }
            else if (newPt != _pointsArr[ind])
                _bufPointsArr[_intArr.IndexOf(ind)] = newPt;
        }

        #endregion

        #region Vertices colors

        private void ShowVerticesColors_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPointCloudData cloud = GeomId.openAsPointCloud();
            _intArr = new OdInt32Array();
            _colorArr = new OdTvRGBColorDefArray();
            _bufColorArr = new OdTvRGBColorDefArray();
            cloud.getPointColorsViaRange(0, cloud.getPointsCount(), _colorArr);
            if (_colorArr.Count == 0)
                _colorArr.resize((uint)cloud.getPointsCount());

            if (!CheckCountOfObject(_colorArr.Count))
            {
                _colorArr.Clear();
                _bufColorArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.Colors;

            currentPanel = CreateGrid(2, 0);
            _isScrollableControl = false;
            LoadVerticesColors();

            if (CreateDialog("Vertices colors", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                cloud.setPointColorsViaList(_intArr, _bufColorArr);
                Update();
            }
            _colorArr.Clear();
            _bufColorArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadVerticesColors()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _colorArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(26) });
                OdTvRGBColorDef old = _colorArr[_countOfLoadedObjects];
                byte r, g, b;
                old.getColor(out r, out g, out b);
                Colorpicker vColor = AddColorDef("Vertex_" + _countOfLoadedObjects, new OdTvColorDef(r, g, b),
                    new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 }, grid);
                vColor.ComboBox.Margin = new Thickness(0, 0, 0, 2);
                vColor.Tag = _countOfLoadedObjects;
                vColor.ColorChanged += VColor_ColorChanged;
            }
        }

        private void VColor_ColorChanged(object sender, OdTvColorDef newColor)
        {
            Colorpicker cp = sender as Colorpicker;
            int ind = (int)cp.Tag;
            byte r, g, b;
            newColor.getColor(out r, out g, out b);
            if (!_intArr.Contains(ind))
            {
                _intArr.Add(ind);
                _bufColorArr.Add(new OdTvRGBColorDef(r, g, b));
                if (!isChanged) isChanged = true;
            }
            else
                _bufColorArr[_intArr.IndexOf(ind)] = new OdTvRGBColorDef(r, g, b);
        }

        #endregion

        #region Vertices normals

        private void ShowVertexNormals_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvPointCloudData cloud = GeomId.openAsPointCloud();
            _vecArr = new OdTvVectorArray();
            _intArr = new OdInt32Array();
            _bufVecArr = new OdTvVectorArray();
            cloud.getPointNormalsViaRange(0, cloud.getPointsCount(), _vecArr);
            if (_vecArr.Count == 0)
            {
                _vecArr.resize((uint)cloud.getPointsCount());
                for (int i = 0; i < cloud.getPointsCount(); i++)
                    _vecArr[i] = OdGeVector3d.kIdentity;
            }

            if (!CheckCountOfObject(_vecArr.Count))
            {
                _vecArr.Clear();
                _intArr.Clear();
                _bufVecArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.Normals;

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };
            _isScrollableControl = true;
            LoadVertexNormals();
            if (CreateDialog("Vertices normals", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                cloud.setPointNormalsViaList(_intArr, _bufVecArr);
                Update();
            }
            _vecArr.Clear();
            _intArr.Clear();
            _bufVecArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadVertexNormals()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _vecArr.Count)
                    return;

                StretchingTreeViewItem itm = AddTreeItem("Vertex_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
                itm.Tag = _countOfLoadedObjects;
                itm.Items.Add(null);
                itm.Expanded += VertexNormal_Expanded;
            }
        }

        private void VertexNormal_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            TextBox[] pnt = GetXyz(itm, _vecArr[(int)itm.Tag]);
            foreach (var p in pnt)
            {
                p.LostKeyboardFocus += VertexNormal_LostKeyboardFocus;
                p.Margin = new Thickness(0, 0, 0, 2);
            }
        }

        private void VertexNormal_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            Grid grid = (Grid)tb.Parent;
            StretchingTreeViewItem parent = (StretchingTreeViewItem)grid.Parent;
            int ind = (int)parent.Tag;
            CoordinateType type = (CoordinateType)tb.Tag;
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufVecArr.Add(SetVectorCoordByType(_vecArr[ind], type, tb.Text));
            }
            else
                _bufVecArr[_intArr.IndexOf(ind)] = SetVectorCoordByType(_bufVecArr[_intArr.IndexOf(ind)], type, tb.Text);
        }

        #endregion

    }
}

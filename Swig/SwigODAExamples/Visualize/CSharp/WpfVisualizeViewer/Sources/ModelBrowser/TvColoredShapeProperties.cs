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
    class TvColoredShapeProperties : TvBaseGeometryProperties
    {
        private enum TypeOfPropety
        {
            Points,
            Colors,
            Faces
        }

        private TypeOfPropety _type;
        private int CountOfLoadedObjects = 200;
        private bool isChanged = false;
        private UIElement currentPanel;
        private int _countOfLoadedObjects = 0;
        // need for elements wothout child
        private bool _isScrollableControl = false;

        private OdTvPointArray _pointsArr;
        private OdInt32Array _intArr;
        private OdTvRGBColorDefArray _colorArr;

        public TvColoredShapeProperties(OdTvGeometryDataId id, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(id, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvColoredShapeData shape = GeomId.openAsColoredShape();
            int row = 0;
            AddLabelAndTextBox("Number of points:", shape.getVerticesCount().ToString(), MainGrid, new[] {row, 0, row++, 1}, true);

            Button pnts = AddLabelAndButton("Points", "...", MainGrid, new[] { row, 0, row++, 1 });
            pnts.Click += ShowVertices_Click;

            Button faces = AddLabelAndButton("Faces", "...", MainGrid, new[] { row, 0, row++, 1 });
            faces.Click += ShowFaces_Click;

            Button colors = AddLabelAndButton("Points colors", "...", MainGrid, new[] { row, 0, row++, 1 }, _colorArr.Count == 0);
            colors.Click += ShowVerticesColors_Click;
            _colorArr = null;

            CheckBox drawCont = AddLabelAndCheckBox("Draw contour", shape.getDrawContour(), MainGrid, new[] {row, 0, row++, 1});
            drawCont.Click += DrawCont_Click;

            StretchingTreeViewItem common = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(common);
            MM.StopTransaction(mtr);
        }

        private void DrawCont_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsColoredShape().setDrawContour(cb.IsChecked == true);
            Update();
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
                    case TypeOfPropety.Faces:
                        LoadFaces();
                        break;
                }
            }
        }

        #region Vertices

        private void ShowVertices_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvColoredShapeData shape = GeomId.openAsColoredShape();
            _pointsArr = new OdTvPointArray();
            OdInt32Array intArr = new OdInt32Array();
            shape.get(_pointsArr, intArr);

            if (!CheckCountOfObject(_pointsArr.Count))
            {
                _pointsArr.Clear();
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
                shape.set(_pointsArr, intArr);
                Update();
            }
            _pointsArr.Clear();
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
            if (newPt != _pointsArr[ind])
            {
                _pointsArr[ind] = newPt;
                if (!isChanged) isChanged = true;
            }
        }

        #endregion

        #region Vertices colors

        private void ShowVerticesColors_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvColoredShapeData shape = GeomId.openAsColoredShape();
            _colorArr = new OdTvRGBColorDefArray();
            shape.getVertexColors(_colorArr);
            if (_colorArr.Count == 0)
                _colorArr.resize(shape.getVerticesCount());

            if (!CheckCountOfObject(_colorArr.Count))
            {
                _colorArr.Clear();
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
                shape.setVertexColors(_colorArr);
                Update();
            }
            _colorArr.Clear();
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
            OdTvRGBColorDef newColorRgb = new OdTvRGBColorDef(r,g,b);
            if (_colorArr[ind] != newColorRgb)
            {
                _colorArr[ind] = newColorRgb;
                if (!isChanged) isChanged = true;
            }
        }

        #endregion

        #region Faces

        private void ShowFaces_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvColoredShapeData shape = GeomId.openAsColoredShape();
            OdTvPointArray points = new OdTvPointArray();
            _intArr = new OdInt32Array();
            shape.get(points, _intArr);

            if (!CheckCountOfObject(_intArr.Count))
            {
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.Faces;

            currentPanel = CreateGrid(2, 0);
            _isScrollableControl = false;
            LoadFaces();

            if (CreateDialog("Faces", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                shape.set(points, _intArr);
                Update();
            }
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFaces()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _intArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(26) });
                TextBox txtBox = AddLabelAndTextBox("Face_" + _countOfLoadedObjects, _intArr[_countOfLoadedObjects].ToString(),
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                txtBox.Margin = new Thickness(0, 0, 0, 2);
                txtBox.Tag = _countOfLoadedObjects;
                txtBox.LostKeyboardFocus += Face_LostKeyboardFocus;
            }
        }

        private void Face_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            int ind = (int)tb.Tag;
            if (_intArr[ind] != int.Parse(tb.Text))
            {
                _intArr[ind] = int.Parse(tb.Text);
                if (!isChanged) isChanged = true;
            }
        }
        #endregion


    }
}


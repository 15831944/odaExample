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
using System.Windows;
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvNurbsProperties : TvBaseGeometryProperties
    {
        private enum TypeOfPropety
        {
            Points,
            Weights,
            Knots,
            Degree,
            Start,
            End
        }

        private TypeOfPropety _type;

        private OdTvPointArray _pointArr;
        private OdGeDoubleArray _doubleArr;
        private int CountOfObjectsForLoad = 200;
        private bool isChanged = false;
        private int _countOfLoadedObjects = 0;
        private UIElement currentPanel;
        private bool _isScrollableControl;

        public TvNurbsProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            int row = 0;
            TextBox degree = AddLabelAndTextBox("Degree:", nurbs.getDegree().ToString(), MainGrid, new[] {row, 0, row++, 1});
            degree.Tag = TypeOfPropety.Degree;
            degree.LostKeyboardFocus += TextTypeProperty_LostKeyboardFocus;
            Button pnts = AddLabelAndButton("Points", "...", MainGrid, new[] { row, 0, row++, 1 });
            pnts.Click += ShowPoints_Click;
            Button weights = AddLabelAndButton("Weights", "...", MainGrid, new[] { row, 0, row++, 1 });
            weights.Click += ShowWeights_Click;
            Button knots = AddLabelAndButton("Knots", "...", MainGrid, new[] { row, 0, row++, 1 });
            knots.Click += ShowKnots_Click;

            double dstart, dend;
            nurbs.getStartEnd(out dstart, out dend);
            TextBox start = AddLabelAndTextBox("Start:", dstart.ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            start.Tag = TypeOfPropety.Start;
            start.LostKeyboardFocus += TextTypeProperty_LostKeyboardFocus;
            TextBox end = AddLabelAndTextBox("End:", dend.ToString(CultureInfo.InvariantCulture), MainGrid, new[] { row, 0, row++, 1 });
            end.Tag = TypeOfPropety.End;
            end.LostKeyboardFocus += TextTypeProperty_LostKeyboardFocus;

            StretchingTreeViewItem misc = AddTreeItem("Misc", MainGrid, new[] { row++, 0 });
            bool bFilled;
            TextBox thickness = AddLabelAndTextBox("Thickness:", nurbs.getThickness(out bFilled).ToString(CultureInfo.InvariantCulture), misc);
            thickness.LostKeyboardFocus += Thickness_LostKeyboardFocus;
            CheckBox filled = AddLabelAndCheckBox("Filled:", bFilled, misc);
            filled.Click += Filled_Click;

            StretchingTreeViewItem cmn = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(cmn);
            MM.StopTransaction(mtr);

        }

        private void TextTypeProperty_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            switch ((TypeOfPropety)tb.Tag)
            {
                case TypeOfPropety.Degree:
                    if (nurbs.getDegree() != uint.Parse(tb.Text))
                        nurbs.set(uint.Parse(tb.Text), nurbs.getControlPoints(), nurbs.getWeights(), nurbs.getKnots());
                    break;
                case TypeOfPropety.Start:
                {
                    double start, end;
                    nurbs.getStartEnd(out start, out end);
                    if (!start.Equals(double.Parse(tb.Text)))
                        nurbs.setStartEnd(double.Parse(tb.Text), end);
                    break;
                }
                case TypeOfPropety.End:
                {
                    double start, end;
                        nurbs.getStartEnd(out start, out end);
                    if (!end.Equals(double.Parse(tb.Text)))
                        nurbs.setStartEnd(start, double.Parse(tb.Text));
                    break;
                }
            }
            Update();
            MM.StopTransaction(mtr);
        }

        private void Thickness_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            bool bFilled;
            if (!nurbs.getThickness(out bFilled).Equals(double.Parse(tb.Text)))
            {
                nurbs.setThickness(double.Parse(tb.Text));
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
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            bool bFilled;
            nurbs.setThickness(nurbs.getThickness(out bFilled), cb.IsChecked == true);
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
                    case TypeOfPropety.Weights:
                        LoadWeights();
                        break;
                    case TypeOfPropety.Knots:
                        LoadKnots();
                        break;
                }
            }
        }

        #region Points

        private void ShowPoints_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            _pointArr = nurbs.getControlPoints();

            if (!CheckCountOfObject(_pointArr.Count))
            {
                _pointArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };
            _type = TypeOfPropety.Points;
            _isScrollableControl = true;
            LoadPoints();

            if (CreateDialog("Nurbs points", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                nurbs.set(nurbs.getDegree(), _pointArr, nurbs.getWeights(), nurbs.getKnots());
                Update();
            }
            _pointArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadPoints()
        {
            for (int i = 0; i < CountOfObjectsForLoad; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _pointArr.Count)
                    return;
                StretchingTreeViewItem itm = AddTreeItem("Point_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
                itm.Tag = _countOfLoadedObjects;
                itm.Items.Add(null);
                itm.Expanded += Point_Expanded;
            }
        }

        private void Point_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            TextBox[] pnt = GetXyz(itm, _pointArr[(int)itm.Tag]);
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
            OdGePoint3d newPt = SetPointCoordByType(_pointArr[ind], type, tb.Text);
            if (newPt != _pointArr[ind])
            {
                _pointArr[ind] = newPt;
                if (!isChanged) isChanged = true;
            }
        }
        #endregion

        #region Weights

        private void ShowWeights_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            _doubleArr = nurbs.getWeights();

            if (!CheckCountOfObject(_doubleArr.Count))
            {
                _doubleArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.Weights;

            currentPanel = CreateGrid(2, 0);
            _isScrollableControl = false;
            LoadWeights();

            if (CreateDialog("Nurbs weights", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                nurbs.set(nurbs.getDegree(), nurbs.getControlPoints(), _doubleArr, nurbs.getKnots());
                Update();
            }
            _doubleArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadWeights()
        {
            for (int i = 0; i < CountOfObjectsForLoad; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _doubleArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(26) });
                TextBox txtBox = AddLabelAndTextBox("Radius_" + _countOfLoadedObjects, _doubleArr[_countOfLoadedObjects].ToString(CultureInfo.InvariantCulture),
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                txtBox.Margin = new Thickness(0, 0, 0, 2);
                txtBox.Tag = _countOfLoadedObjects;
                txtBox.LostKeyboardFocus += Weights_LostKeyboardFocus;
            }
        }

        private void Weights_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            int ind = (int)tb.Tag;
            if (!_doubleArr[ind].Equals(double.Parse(tb.Text)))
            {
                _doubleArr[ind] = double.Parse(tb.Text);
                if (!isChanged) isChanged = true;
            }
        }
        #endregion

        #region Knots

        private void ShowKnots_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvNurbsData nurbs = GeomId.openAsNurbs();
            _doubleArr = nurbs.getKnots();

            if (!CheckCountOfObject(_doubleArr.Count))
            {
                _doubleArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.Knots;

            currentPanel = CreateGrid(2, 0);
            _isScrollableControl = false;
            LoadKnots();

            if (CreateDialog("Nurbs knots", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                nurbs.set(nurbs.getDegree(), nurbs.getControlPoints(), nurbs.getWeights(), _doubleArr);
                Update();
            }
            _doubleArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadKnots()
        {
            for (int i = 0; i < CountOfObjectsForLoad; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _doubleArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(26) });
                TextBox txtBox = AddLabelAndTextBox("Radius_" + _countOfLoadedObjects, _doubleArr[_countOfLoadedObjects].ToString(CultureInfo.InvariantCulture),
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                txtBox.Margin = new Thickness(0, 0, 0, 2);
                txtBox.Tag = _countOfLoadedObjects;
                txtBox.LostKeyboardFocus += Radius_LostKeyboardFocus;
            }
        }

        private void Radius_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            int ind = (int)tb.Tag;
            if (!_doubleArr[ind].Equals(double.Parse(tb.Text)))
            {
                _doubleArr[ind] = double.Parse(tb.Text);
                if (!isChanged) isChanged = true;
            }
        }
        #endregion

    }
}

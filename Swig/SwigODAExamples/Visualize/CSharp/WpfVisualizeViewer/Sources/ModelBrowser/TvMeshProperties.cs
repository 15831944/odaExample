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
using System.Windows.Media;
using Teigha.Core;
using Teigha.Visualize;
using Button = System.Windows.Controls.Button;
using CheckBox = System.Windows.Controls.CheckBox;
using ComboBox = System.Windows.Controls.ComboBox;
using HorizontalAlignment = System.Windows.HorizontalAlignment;
using TextBox = System.Windows.Controls.TextBox;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties.GeometryProperties
{
    class TvMeshProperties : TvBaseGeometryProperties
    {
        private enum TypeOfPropety
        {
            Points,
            EdgeColors,
            EdgeLayers,
            EdgeLinetypes,
            EdgleVisibilities,
            FaceColors,
            FaceLayers,
            FaceNormals,
            FaceMappers,
            FaceMaterials,
            FaceTranparencies,
            FaceVisibilities,
            VerticesColors,
            MapperCoordinates,
            VerticesNormals
        }

        private TypeOfPropety _type;
        private int CountOfLoadedObjects = 200;
        private bool isChanged = false;
        private UIElement currentPanel;
        private int _countOfLoadedObjects = 0;

        // need for elements wothout child
        private bool _isScrollableControl = false;
        private int _scrollHeight = 0;

        // temp arrays
        private OdTvPointArray _pointArr;
        private OdTvVectorArray _vectorArr;
        private OdTvVectorArray _bufVectorArr;
        private OdInt32Array _intArr;
        private OdTvColorDefArray _colorDefArr;
        private OdTvColorDefArray _bufColorDefArray;
        private OdTvLayerDefArray _layerDefArr;
        private OdTvLayerDefArray _bufLayerDefArr;
        private OdTvLinetypeDefArray _ltDefArr;
        private OdTvLinetypeDefArray _bufLtDefArr;
        private OdTvVisibilityDefArray _visDefArr;
        private OdTvVisibilityDefArray _bufVisDefArr;
        private OdTvMapperDefArray _mapDefArr;
        private OdTvMapperDefArray _bufMapDefArr;
        private OdTvMaterialDefArray _matDefArr;
        private OdTvMaterialDefArray _bufMatDefArr;
        private OdTvTransparencyDefArray _transpDefArr;
        private OdTvTransparencyDefArray _bufTranspDefArr;
        private OdTvPoint2dArray _point2dArr;
        private OdTvPoint2dArray _bufPoint2dArr;
        private OdTvRGBColorDefArray _rgbDefArr;
        private OdTvRGBColorDefArray _bufRgbArr;

        public TvMeshProperties(OdTvGeometryDataId geomId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
          : base(geomId, devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            int row = 0;
            AddLabelAndTextBox("Number of rows:", Mesh.getRowsCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of columns:", Mesh.getColumnsCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of edges:", Mesh.getEdgesCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of faces:", Mesh.getFacesCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of vertices:", Mesh.getVerticesCount().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);

            List<string> orientList = new List<string>() { "NoOrientation", "CounterClockwise", "Clockwise" };
            ComboBox vOrient = AddLabelAndComboBox("Vertex orientation:", orientList, (int)Mesh.getVertexOrientation(), MainGrid, new[] { row, 0, row++, 1 });
            vOrient.SelectionChanged += VOrient_SelectionChanged;

            _colorDefArr = new OdTvColorDefArray();
            _layerDefArr = new OdTvLayerDefArray();
            _ltDefArr = new OdTvLinetypeDefArray();
            _visDefArr = new OdTvVisibilityDefArray();
            _vectorArr = new OdTvVectorArray();
            _mapDefArr = new OdTvMapperDefArray();
            _matDefArr = new OdTvMaterialDefArray();
            _transpDefArr = new OdTvTransparencyDefArray();
            _point2dArr = new OdTvPoint2dArray();
            _rgbDefArr = new OdTvRGBColorDefArray();

            Button vbtn = AddLabelAndButton("Mesh points:", "...", MainGrid, new[] { row, 0, row++, 1 });
            vbtn.Click += ShowVertices_Click;
            Mesh.getEdgeColorsViaRange(0, (int)Mesh.getEdgesCount(), _colorDefArr);
            Button eCol = AddLabelAndButton("Edges colors:", "...", MainGrid, new[] { row, 0, row++, 1 }, _colorDefArr.Count == 0);
            _colorDefArr.Clear();
            eCol.Click += ShowEdgesColors_Click;
            Mesh.getEdgeLayersViaRange(0, (int)Mesh.getEdgesCount(), _layerDefArr);
            Button eLay = AddLabelAndButton("Edges layers:", "...", MainGrid, new[] { row, 0, row++, 1 }, _layerDefArr.Count == 0);
            eLay.Click += ShowEdgesLayers_Click;
            _layerDefArr.Clear();
            Mesh.getEdgeLinetypesViaRange(0, (int)Mesh.getEdgesCount(), _ltDefArr);
            Button eLt = AddLabelAndButton("Edges linetypes:", "...", MainGrid, new[] { row, 0, row++, 1 }, _ltDefArr.Count == 0);
            eLt.Click += ShowEdgesLinetypes_Click;
            Mesh.getEdgeVisibilitiesViaRange(0, (int)Mesh.getEdgesCount(), _visDefArr);
            Button eVis = AddLabelAndButton("Edges visibilities:", "...", MainGrid, new[] { row, 0, row++, 1 }, _visDefArr.Count == 0);
            eVis.Click += ShowEdgesVisibility_Click;
            Mesh.getFaceColorsViaRange(0, (int)Mesh.getFacesCount(), _colorDefArr);
            Button fCol = AddLabelAndButton("Faces colors:", "...", MainGrid, new[] { row, 0, row++, 1 }, _colorDefArr.Count == 0);
            fCol.Click += ShowFacesColors_Click;
            _colorDefArr.Clear();
            Mesh.getFaceLayersViaRange(0, (int)Mesh.getFacesCount(), _layerDefArr);
            Button fLay = AddLabelAndButton("Faces layers:", "...", MainGrid, new[] { row, 0, row++, 1 }, _layerDefArr.Count == 0);
            fLay.Click += ShowFacesLayers_Click;
            _layerDefArr.Clear();
            Mesh.getFaceNormalsViaRange(0, (int)Mesh.getFacesCount(), _vectorArr);
            Button fNorm = AddLabelAndButton("Faces normals:", "...", MainGrid, new[] { row, 0, row++, 1 }, _vectorArr.Count == 0);
            fNorm.Click += ShowFaceNormals_Click;
            _vectorArr.Clear();
            Mesh.getFaceMappersViaRange(0, (int)Mesh.getFacesCount(), _mapDefArr);
            Button fMap = AddLabelAndButton("Faces mappers:", "...", MainGrid, new[] { row, 0, row++, 1 }, _mapDefArr.Count == 0);
            fMap.Click += ShowFaceMappers_Click;
            _mapDefArr.Clear();
            Mesh.getFaceMaterialsViaRange(0, (int)Mesh.getFacesCount(), _matDefArr);
            Button fMat = AddLabelAndButton("Faces materials:", "...", MainGrid, new[] { row, 0, row++, 1 }, _matDefArr.Count == 0);
            fMat.Click += ShowFacesMaterials_Click;
            _matDefArr.Clear();
            Mesh.getFaceTransparencyViaRange(0, (int)Mesh.getFacesCount(), _transpDefArr);
            Button fTr = AddLabelAndButton("Faces transparencies:", "...", MainGrid, new[] { row, 0, row++, 1 }, _transpDefArr.Count == 0);
            fTr.Click += ShowFaceTransparencies_Click;
            _transpDefArr.Clear();
            Mesh.getFaceVisibilitiesViaRange(0, (int)Mesh.getFacesCount(), _visDefArr);
            Button fVis = AddLabelAndButton("Faces visibilities:", "...", MainGrid, new[] { row, 0, row++, 1 }, _visDefArr.Count == 0);
            fVis.Click += ShowFacesVisibility_Click;
            _visDefArr.Clear();
            Mesh.getVertexMappingCoordsViaRange(0, (int)Mesh.getVerticesCount(), _point2dArr);
            Button mapCord = AddLabelAndButton("Mapper coordinates:", "...", MainGrid, new[] { row, 0, row++, 1 }, _point2dArr.Count == 0);
            mapCord.Click += ShowMapperCoord_Click;
            _point2dArr.Clear();
            Mesh.getVertexColorsViaRange(0, (int)Mesh.getVerticesCount(), _rgbDefArr);
            Button vCol = AddLabelAndButton("Vertices colors:", "...", MainGrid, new[] { row, 0, row++, 1 }, _rgbDefArr.Count == 0);
            vCol.Click += ShowVerticesColors_Click;
            _rgbDefArr.Clear();
            Button vNorm = AddLabelAndButton("Vertices normals:", "...", MainGrid, new[] { row, 0, row++, 1 });
            vNorm.Click += ShowVertexNormals_Click;


            StretchingTreeViewItem common = AddTreeItem("Common properties", MainGrid, new[] { row, 0 });
            GetProperties(common);

            MM.StopTransaction(mtr);
        }

        private void VOrient_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            GeomId.openAsMesh().setVertexOrientation((OrientationType)cb.SelectedIndex);
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
                    case TypeOfPropety.EdgeColors:
                        LoadEdgesColors();
                        break;
                    case TypeOfPropety.EdgeLayers:
                        LoadEdgesLayers();
                        break;
                    case TypeOfPropety.EdgeLinetypes:
                        LoadEdgesLinetypes();
                        break;
                    case TypeOfPropety.EdgleVisibilities:
                        LoadEdgesVisibilities();
                        break;
                    case TypeOfPropety.FaceColors:
                        LoadFacesColors();
                        break;
                    case TypeOfPropety.FaceLayers:
                        LoadFacesLayers();
                        break;
                    case TypeOfPropety.FaceNormals:
                        LoadFaceNormals();
                        break;
                    case TypeOfPropety.FaceMappers:
                        LoadFaceMappers();
                        break;
                    case TypeOfPropety.FaceMaterials:
                        LoadFacesMaterials();
                        break;
                    case TypeOfPropety.FaceTranparencies:
                        LoadFaceTransparencies();
                        break;
                    case TypeOfPropety.FaceVisibilities:
                        LoadFacesVisibilities();
                        break;
                    case TypeOfPropety.VerticesColors:
                        LoadVerticesColors();
                        break;
                    case TypeOfPropety.MapperCoordinates:
                        LoadMapperCoords();
                        break;
                    case TypeOfPropety.VerticesNormals:
                        LoadVertexNormals();
                        break;
                }
            }
        }

        #region Vertices

        private void ShowVertices_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData mesh = GeomId.openAsMesh();
            _pointArr = new OdTvPointArray();
            uint rows, cols;
            mesh.getParam(out rows, out cols, _pointArr);

            if (!CheckCountOfObject(_pointArr.Count))
            {
                _pointArr.Clear();
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
            if (CreateDialog("Mesh vertices", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                mesh.setParam(rows, cols, _pointArr);
                Update();
            }
            _pointArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadPoints()
        {
            if (_countOfLoadedObjects >= _pointArr.Count)
                return;
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                StretchingTreeViewItem itm = AddTreeItem("Point_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
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

        #region Edge colors

        private void ShowEdgesColors_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _colorDefArr = new OdTvColorDefArray();
            _bufColorDefArray = new OdTvColorDefArray();
            Mesh.getEdgeColorsViaRange(0, (int)Mesh.getEdgesCount(), _colorDefArr);
            if (_colorDefArr.Count == 0)
            {
                _colorDefArr.resize(Mesh.getEdgesCount());
            }

            if (!CheckCountOfObject(_colorDefArr.Count))
            {
                _colorDefArr.Clear();
                _bufColorDefArray.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.EdgeColors;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadEdgesColors();

            if (CreateDialog("Mesh edges colors", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setEdgeColorsViaList(_intArr, _bufColorDefArray);
                Update();
            }
            _colorDefArr.Clear();
            _bufColorDefArray.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadEdgesColors()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _colorDefArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });

                Colorpicker eColor = AddColorDef("Edge_" + _countOfLoadedObjects, _colorDefArr[_countOfLoadedObjects],
                    new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 }, grid);
                eColor.ComboBox.Margin = new Thickness(0, 0, 0, 2);
                eColor.Tag = _countOfLoadedObjects;
                eColor.ColorChanged += EColor_ColorChanged;
            }
        }

        private void EColor_ColorChanged(object sender, OdTvColorDef newColor)
        {
            Colorpicker cp = sender as Colorpicker;
            int ind = (int)cp.Tag;
            if (_colorDefArr[ind] != newColor)
            {
                if (!_intArr.Contains(ind))
                {
                    _intArr.Add(ind);
                    _bufColorDefArray.Add(newColor);
                }
                else
                    _bufColorDefArray[_intArr.IndexOf(ind)] = newColor;
                if (!isChanged) isChanged = true;
            }
        }

        #endregion

        #region Edge layers

        private void ShowEdgesLayers_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _layerDefArr = new OdTvLayerDefArray();
            _bufLayerDefArr = new OdTvLayerDefArray();
            Mesh.getEdgeLayersViaRange(0, (int)Mesh.getEdgesCount(), _layerDefArr);
            if (_layerDefArr.Count == 0)
            {
                _layerDefArr.resize(Mesh.getEdgesCount());
                for (int i = 0; i < (int)Mesh.getEdgesCount(); i++)
                    _layerDefArr[i] = new OdTvLayerDef();
            }

            if (!CheckCountOfObject(_layerDefArr.Count))
            {
                _layerDefArr.Clear();
                _bufLayerDefArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.EdgeLayers;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadEdgesLayers();

            if (CreateDialog("Mesh edge layers", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setEdgeLayersViaList(_intArr, _bufLayerDefArr);
                Update();
            }
            _layerDefArr.Clear();
            _bufLayerDefArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadEdgesLayers()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _layerDefArr.Count)
                    return;
                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                ComboBox eLayer = AddLayerDef("Edge_" + _countOfLoadedObjects, _layerDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                eLayer.Margin = new Thickness(0, 0, 0, 2);
                eLayer.Tag = _countOfLoadedObjects;
                eLayer.SelectionChanged += ELayer_SelectionChanged;
            }
        }

        private void ELayer_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            int ind = (int)cb.Tag;
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufLayerDefArr.Add(GetLayerDef(cb.SelectedItem.ToString()));
            }
            else
                _bufLayerDefArr[_intArr.IndexOf(ind)] = GetLayerDef(cb.SelectedItem.ToString());
        }

        #endregion

        #region Edge linetypes

        private void ShowEdgesLinetypes_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _ltDefArr = new OdTvLinetypeDefArray();
            _bufLtDefArr = new OdTvLinetypeDefArray();
            Mesh.getEdgeLinetypesViaRange(0, (int)Mesh.getEdgesCount(), _ltDefArr);
            if (_ltDefArr.Count == 0)
            {
                _ltDefArr.resize(Mesh.getEdgesCount());
                for (int i = 0; i < (int)Mesh.getEdgesCount(); i++)
                    _ltDefArr[i] = new OdTvLinetypeDef();
            }

            if (!CheckCountOfObject(_ltDefArr.Count))
            {
                _ltDefArr.Clear();
                _bufLtDefArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.EdgeLinetypes;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadEdgesLinetypes();

            if (CreateDialog("Mesh edge linetypes", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setEdgeLinetypesViaList(_intArr, _bufLtDefArr);
                Update();
            }
            _ltDefArr.Clear();
            _bufLtDefArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadEdgesLinetypes()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= (_ltDefArr).Count)
                    return;
                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                ComboBox eLt = AddLinetypeDef("Edge_" + _countOfLoadedObjects, _ltDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                eLt.Margin = new Thickness(0, 0, 0, 2);
                eLt.Tag = _countOfLoadedObjects;
                eLt.SelectionChanged += ELinetype_SelectionChanged;
            }
        }

        private void ELinetype_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            int ind = (int)cb.Tag;
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufLtDefArr.Add(GetLinetypeDef(cb.SelectedItem.ToString()));
            }
            else
                _bufLtDefArr[_intArr.IndexOf(ind)] = GetLinetypeDef(cb.SelectedItem.ToString());
        }

        #endregion

        #region Edge visibility

        private void ShowEdgesVisibility_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _visDefArr = new OdTvVisibilityDefArray();
            _bufVisDefArr = new OdTvVisibilityDefArray();
            Mesh.getEdgeVisibilitiesViaRange(0, (int)Mesh.getEdgesCount(), _visDefArr);
            if (_visDefArr.Count == 0)
            {
                _visDefArr.resize(Mesh.getEdgesCount());
                for (int i = 0; i < Mesh.getEdgesCount(); i++)
                    _visDefArr[i] = new OdTvVisibilityDef();
            }

            if (!CheckCountOfObject(_visDefArr.Count))
            {
                _visDefArr.Clear();
                _bufVisDefArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.EdgleVisibilities;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadEdgesVisibilities();

            if (CreateDialog("Mesh edge visibilities", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setEdgeVisibilitiesViaList(_intArr, _bufVisDefArr);
                Update();
            }
            _visDefArr.Clear();
            _bufVisDefArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadEdgesVisibilities()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= (_visDefArr).Count)
                    return;
                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                CheckBox eVis = AddVisibilityDef("Edge_" + _countOfLoadedObjects, _visDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                eVis.Margin = new Thickness(0, 0, 0, 2);
                eVis.Tag = _countOfLoadedObjects;
                eVis.Click += EVis_Click;
            }
        }

        private void EVis_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            int ind = (int)cb.Tag;
            if (!_intArr.Contains(ind))
            {
                _intArr.Add(ind);
                _bufVisDefArr.Add(new OdTvVisibilityDef(cb.IsChecked == true));
                if (!isChanged) isChanged = true;
            }
            else
                _bufVisDefArr[_intArr.IndexOf(ind)] = new OdTvVisibilityDef(cb.IsChecked == true);
        }

        #endregion

        #region Face colors

        private void ShowFacesColors_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _colorDefArr = new OdTvColorDefArray();
            _bufColorDefArray = new OdTvColorDefArray();
            Mesh.getFaceColorsViaRange(0, (int)Mesh.getFacesCount(), _colorDefArr);
            if (_colorDefArr.Count == 0)
                _colorDefArr.resize(Mesh.getFacesCount());

            if (!CheckCountOfObject(_colorDefArr.Count))
            {
                _colorDefArr.Clear();
                _bufColorDefArray.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceColors;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadFacesColors();

            if (CreateDialog("Mesh faces colors", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceColorsViaList(_intArr, _bufColorDefArray);
                Update();
            }
            _colorDefArr.Clear();
            _bufColorDefArray.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFacesColors()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _colorDefArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });

                Colorpicker fColor = AddColorDef("Face_" + _countOfLoadedObjects, _colorDefArr[_countOfLoadedObjects],
                    new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 }, grid);
                fColor.ComboBox.Margin = new Thickness(0, 0, 0, 2);
                fColor.Tag = _countOfLoadedObjects;
                fColor.ColorChanged += FColor_ColorChanged;
            }
        }

        private void FColor_ColorChanged(object sender, OdTvColorDef newColor)
        {
            Colorpicker cp = sender as Colorpicker;
            int ind = (int)cp.Tag;
            if (_colorDefArr[ind] != newColor)
            {
                if (!_intArr.Contains(ind))
                {
                    _intArr.Add(ind);
                    _bufColorDefArray.Add(newColor);
                }
                else
                    _bufColorDefArray[_intArr.IndexOf(ind)] = newColor;
                if (!isChanged) isChanged = true;
            }
        }

        #endregion

        #region Face layers

        private void ShowFacesLayers_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _layerDefArr = new OdTvLayerDefArray();
            _bufLayerDefArr = new OdTvLayerDefArray();
            Mesh.getFaceLayersViaRange(0, (int)Mesh.getFacesCount(), _layerDefArr);
            if (_layerDefArr.Count == 0)
            {
                _layerDefArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < (int)Mesh.getFacesCount(); i++)
                    _layerDefArr[i] = new OdTvLayerDef();
            }

            if (!CheckCountOfObject(_layerDefArr.Count))
            {
                _layerDefArr.Clear();
                _bufLayerDefArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceLayers;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadFacesLayers();

            if (CreateDialog("Mesh face layers", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceLayersViaList(_intArr, _bufLayerDefArr);
                Update();
            }
            _layerDefArr.Clear();
            _bufLayerDefArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFacesLayers()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _layerDefArr.Count)
                    return;
                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                ComboBox fLayer = AddLayerDef("Face_" + _countOfLoadedObjects, _layerDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                fLayer.Margin = new Thickness(0, 0, 0, 2);
                fLayer.Tag = _countOfLoadedObjects;
                fLayer.SelectionChanged += FLayer_SelectionChanged;
            }
        }

        private void FLayer_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            int ind = (int)cb.Tag;
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufLayerDefArr.Add(GetLayerDef(cb.SelectedItem.ToString()));
            }
            else
                _bufLayerDefArr[_intArr.IndexOf(ind)] = GetLayerDef(cb.SelectedItem.ToString());
        }

        #endregion

        #region Face normals

        private void ShowFaceNormals_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _vectorArr = new OdTvVectorArray();
            _intArr = new OdInt32Array();
            _bufVectorArr = new OdTvVectorArray();
            Mesh.getFaceNormalsViaRange(0, (int)Mesh.getFacesCount(), _vectorArr);
            if (_vectorArr.Count == 0)
            {
                _vectorArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < Mesh.getFacesCount(); i++)
                    _vectorArr[i] = OdGeVector3d.kIdentity;
            }

            if (!CheckCountOfObject(_vectorArr.Count))
            {
                _vectorArr.Clear();
                _intArr.Clear();
                _bufVectorArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceNormals;

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };
            _isScrollableControl = true;
            LoadFaceNormals();
            if (CreateDialog("Mesh face normals", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceNormalsViaList(_intArr, _bufVectorArr);
                Update();
            }
            _vectorArr.Clear();
            _intArr.Clear();
            _bufVectorArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFaceNormals()
        {
            if (_countOfLoadedObjects >= _vectorArr.Count)
                return;
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                StretchingTreeViewItem itm = AddTreeItem("Face_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
                itm.Tag = _countOfLoadedObjects;
                itm.Items.Add(null);
                itm.Expanded += FaceNormal_Expanded;
            }
        }

        private void FaceNormal_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            TextBox[] pnt = GetXyz(itm, _vectorArr[(int)itm.Tag]);
            foreach (var p in pnt)
            {
                p.LostKeyboardFocus += FaceNormal_LostKeyboardFocus;
                p.Margin = new Thickness(0, 0, 0, 2);
            }
        }

        private void FaceNormal_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
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
                _bufVectorArr.Add(SetVectorCoordByType(_vectorArr[ind], type, tb.Text));
            }
            else
                _bufVectorArr[_intArr.IndexOf(ind)] = SetVectorCoordByType(_bufVectorArr[_intArr.IndexOf(ind)], type, tb.Text);
        }

        #endregion

        #region Face mappers

        private void ShowFaceMappers_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _mapDefArr = new OdTvMapperDefArray();
            _intArr = new OdInt32Array();
            _bufMapDefArr = new OdTvMapperDefArray();
            Mesh.getFaceMappersViaRange(0, (int)Mesh.getFacesCount(), _mapDefArr);
            if (_mapDefArr.Count == 0)
            {
                _mapDefArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < Mesh.getFacesCount(); i++)
                    _mapDefArr[i] = new OdTvMapperDef();
            }

            if (!CheckCountOfObject(_mapDefArr.Count))
            {
                _mapDefArr.Clear();
                _intArr.Clear();
                _bufMapDefArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceMappers;

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };
            _isScrollableControl = true;
            LoadFaceMappers();
            if (CreateDialog("Mesh face mappers", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceMappersViaList(_intArr, _bufMapDefArr);
                Update();
            }
            _mapDefArr.Clear();
            _intArr.Clear();
            _bufMapDefArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFaceMappers()
        {
            if (_countOfLoadedObjects >= _mapDefArr.Count)
                return;
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                StretchingTreeViewItem itm = AddTreeItem("Face_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
                if (_mapDefArr[_countOfLoadedObjects].getType() == OdTvMapperDef.MapperType.kDefault)
                    itm.Foreground = new SolidColorBrush(Colors.Gray);
                itm.Tag = _countOfLoadedObjects;
                itm.Items.Add(null);
                itm.Expanded += FaceMapper_Expanded;
            }
        }

        private void FaceMapper_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            int ind = (int)itm.Tag;
            AddMapper(_mapDefArr[ind], itm);
        }

        private void AddMapper(OdTvMapperDef mapper, StretchingTreeViewItem parent)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            List<string> autoTrList = new List<string>() { "None", "Object", "Model" };
            ComboBox autoTr = AddLabelAndComboBox("Auto transform:", autoTrList, mapper.autoTransform().ToString().Remove(0, 1), parent);
            autoTr.Tag = mapper;
            autoTr.SelectionChanged += AutoTr_SelectionChanged;
            List<string> projList = new List<string>() { "Planar", "Box", "Cylinder", "Sphere" };
            ComboBox proj = AddLabelAndComboBox("Projection:", projList, (int)mapper.projection(), parent);
            proj.Tag = mapper;
            proj.SelectionChanged += Proj_SelectionChanged;
            List<TextBox> matrix = AddMatrix("Transform", mapper.transform(), parent);
            MM.StopTransaction(mtr);
        }

        private void Proj_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            OdTvMapperDef map = (OdTvMapperDef)cb.Tag;
            Grid grid = (Grid)cb.Parent;
            int ind = (int)((StretchingTreeViewItem)grid.Parent).Tag;
            map.setProjection((OdTvMapperDef.Projection)cb.SelectedIndex);
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufMapDefArr.Add(map);
            }
        }

        private void AutoTr_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            if (cb == null)
                return;
            OdTvMapperDef map = (OdTvMapperDef)cb.Tag;
            Grid grid = (Grid)cb.Parent;
            int ind = (int)((StretchingTreeViewItem)grid.Parent).Tag;
            int newInd = cb.SelectedIndex == 0 ? 1 : cb.SelectedIndex == 1 ? 2 : 4;
            map.setAutoTransform((OdTvMapperDef.AutoTransform)newInd);
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufMapDefArr.Add(map);
            }
        }

        #endregion

        #region Face materials

        private void ShowFacesMaterials_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _matDefArr = new OdTvMaterialDefArray();
            _bufMatDefArr = new OdTvMaterialDefArray();
            Mesh.getFaceMaterialsViaRange(0, (int)Mesh.getFacesCount(), _matDefArr);
            if (_matDefArr.Count == 0)
            {
                _matDefArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < (int)Mesh.getFacesCount(); i++)
                    _matDefArr[i] = new OdTvMaterialDef();
            }

            if (!CheckCountOfObject(_matDefArr.Count))
            {
                _matDefArr.Clear();
                _bufMatDefArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceMaterials;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadFacesMaterials();

            if (CreateDialog("Mesh face matrials", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceMaterialsViaList(_intArr, _bufMatDefArr);
                Update();
            }
            _matDefArr.Clear();
            _bufMatDefArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFacesMaterials()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _matDefArr.Count)
                    return;
                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                ComboBox fMat = AddMatrialDef("Face_" + _countOfLoadedObjects, _matDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                fMat.Margin = new Thickness(0, 0, 0, 2);
                fMat.Tag = _countOfLoadedObjects;
                fMat.SelectionChanged += FMat_SelectionChanged;
            }
        }

        private void FMat_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            int ind = (int)cb.Tag;
            if (!_intArr.Contains(ind))
            {
                if (!isChanged) isChanged = true;
                _intArr.Add(ind);
                _bufMatDefArr.Add(GetMaterialDef(cb.SelectedItem.ToString()));
            }
            else
                _bufMatDefArr[_intArr.IndexOf(ind)] = GetMaterialDef(cb.SelectedItem.ToString());
        }

        #endregion

        #region Face transparencies

        private void ShowFaceTransparencies_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _transpDefArr = new OdTvTransparencyDefArray();
            _bufTranspDefArr = new OdTvTransparencyDefArray();
            Mesh.getFaceTransparencyViaRange(0, (int)Mesh.getFacesCount(), _transpDefArr);
            if (_transpDefArr.Count == 0)
            {
                _transpDefArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < Mesh.getFacesCount(); i++)
                    _transpDefArr[i] = new OdTvTransparencyDef();
            }

            if (!CheckCountOfObject(_transpDefArr.Count))
            {
                _intArr.Clear();
                _transpDefArr.Clear();
                _bufTranspDefArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceTranparencies;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadFaceTransparencies();

            if (CreateDialog("Mesh face transparencies", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceTransparencyViaList(_intArr, _bufTranspDefArr);
                Update();
            }
            _intArr.Clear();
            _transpDefArr.Clear();
            _bufTranspDefArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFaceTransparencies()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _transpDefArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                TextBox txtBox = AddTransparencyDef("Face_" + _countOfLoadedObjects, _transpDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                txtBox.Margin = new Thickness(0, 0, 0, 2);
                txtBox.Tag = _countOfLoadedObjects;
                txtBox.LostKeyboardFocus += FaceTranspareny_LostKeyboardFocus;
            }
        }

        private void FaceTranspareny_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
        {
            TextBox tb = sender as TextBox;
            if (tb == null)
                return;
            int ind = (int)tb.Tag;
            if (!_intArr.Contains(ind))
            {
                _intArr.Add(ind);
                _bufTranspDefArr.Add(new OdTvTransparencyDef(double.Parse(tb.Text)));
                if (!isChanged) isChanged = true;
            }
            else
                _bufTranspDefArr[_intArr.IndexOf(ind)] = new OdTvTransparencyDef(double.Parse(tb.Text));
        }

        #endregion

        #region Face visibilities

        private void ShowFacesVisibility_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _visDefArr = new OdTvVisibilityDefArray();
            _bufVisDefArr = new OdTvVisibilityDefArray();
            Mesh.getFaceVisibilitiesViaRange(0, (int)Mesh.getFacesCount(), _visDefArr);
            if (_visDefArr.Count == 0)
            {
                _visDefArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < Mesh.getFacesCount(); i++)
                    _visDefArr[i] = new OdTvVisibilityDef();
            }

            if (!CheckCountOfObject(_visDefArr.Count))
            {
                _visDefArr.Clear();
                _bufVisDefArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.FaceVisibilities;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadFacesVisibilities();

            if (CreateDialog("Mesh face visibilities", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setFaceVisibilitiesViaList(_intArr, _bufVisDefArr);
                Update();
            }
            _visDefArr.Clear();
            _bufVisDefArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadFacesVisibilities()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= (_visDefArr).Count)
                    return;
                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                CheckBox fVis = AddVisibilityDef("Face_" + _countOfLoadedObjects, _visDefArr[_countOfLoadedObjects],
                    grid, new[] { _countOfLoadedObjects, 0, _countOfLoadedObjects, 1 });
                fVis.HorizontalAlignment = HorizontalAlignment.Right;
                fVis.Tag = _countOfLoadedObjects;
                fVis.Click += FVis_Click;
            }
        }

        private void FVis_Click(object sender, RoutedEventArgs e)
        {
            CheckBox cb = sender as CheckBox;
            int ind = (int)cb.Tag;
            if (!_intArr.Contains(ind))
            {
                _intArr.Add(ind);
                _bufVisDefArr.Add(new OdTvVisibilityDef(cb.IsChecked == true));
                if (!isChanged) isChanged = true;
            }
            else
                _bufVisDefArr[_intArr.IndexOf(ind)] = new OdTvVisibilityDef(cb.IsChecked == true);
        }

        #endregion

        #region Mapper coordinates

        private void ShowMapperCoord_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _point2dArr = new OdTvPoint2dArray();
            _bufPoint2dArr = new OdTvPoint2dArray();
            _intArr = new OdInt32Array();
            Mesh.getVertexMappingCoordsViaRange(0, (int)Mesh.getFacesCount(), _point2dArr);
            if (_point2dArr.Count == 0)
            {
                _point2dArr.resize(Mesh.getFacesCount());
                for (int i = 0; i < Mesh.getFacesCount(); i++)
                    _point2dArr[i] = new OdGePoint2d();
            }

            if (!CheckCountOfObject(_point2dArr.Count))
            {
                _intArr.Clear();
                _point2dArr.Clear();
                _bufPoint2dArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.MapperCoordinates;

            currentPanel = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                Margin = new Thickness(2, 2, 0, 2)
            };
            _isScrollableControl = true;
            LoadMapperCoords();
            if (CreateDialog("Mesh mapper coordinates", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setVertexMappingCoordsViaList(_intArr, _bufPoint2dArr);
                Update();
            }
            _intArr.Clear();
            _point2dArr.Clear();
            _bufPoint2dArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadMapperCoords()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _point2dArr.Count)
                    return;

                StretchingTreeViewItem itm = AddTreeItem("Point_" + _countOfLoadedObjects, (StretchingTreeView)currentPanel);
                itm.Tag = _countOfLoadedObjects;
                itm.Items.Add(null);
                itm.Expanded += MapperCoord_Expanded;
            }
        }

        private void MapperCoord_Expanded(object sender, RoutedEventArgs e)
        {
            StretchingTreeViewItem itm = sender as StretchingTreeViewItem;
            if (itm == null)
                return;
            itm.Items.Clear();
            TextBox[] pnt = GetXy(itm, _point2dArr[(int)itm.Tag]);
            foreach (var p in pnt)
            {
                p.LostKeyboardFocus += MapperCoord_LostKeyboardFocus;
                p.Margin = new Thickness(0, 0, 0, 2);
            }
        }

        private void MapperCoord_LostKeyboardFocus(object sender, System.Windows.Input.KeyboardFocusChangedEventArgs e)
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
                _intArr.Add(ind);
                _bufPoint2dArr.Add(SetPointCoordByType(_point2dArr[ind], type, tb.Text));
                if (!isChanged) isChanged = true;
            }
            else
                _bufPoint2dArr[_intArr.IndexOf(ind)] = SetPointCoordByType(_bufPoint2dArr[_intArr.IndexOf(ind)], type, tb.Text);

            e.Handled = true;
        }

        #endregion

        #region Vertices colors

        private void ShowVerticesColors_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _intArr = new OdInt32Array();
            _rgbDefArr = new OdTvRGBColorDefArray();
            _bufRgbArr = new OdTvRGBColorDefArray();
            Mesh.getVertexColorsViaRange(0, (int)Mesh.getVerticesCount(), _rgbDefArr);
            if (_rgbDefArr.Count == 0)
                _rgbDefArr.resize(Mesh.getVerticesCount());

            if (!CheckCountOfObject(_rgbDefArr.Count))
            {
                _rgbDefArr.Clear();
                _bufRgbArr.Clear();
                _intArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.VerticesColors;

            currentPanel = CreateGrid(2, 0);
            _scrollHeight = 26;
            _isScrollableControl = false;
            LoadVerticesColors();

            if (CreateDialog("Mesh vertices colors", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setVertexColorsViaList(_intArr, _bufRgbArr);
                Update();
            }
            _rgbDefArr.Clear();
            _bufRgbArr.Clear();
            _intArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadVerticesColors()
        {
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
                if (_countOfLoadedObjects >= _rgbDefArr.Count)
                    return;

                Grid grid = (Grid)currentPanel;
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(_scrollHeight) });
                OdTvRGBColorDef old = _rgbDefArr[_countOfLoadedObjects];
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
                _bufRgbArr.Add(new OdTvRGBColorDef(r, g, b));
                if (!isChanged) isChanged = true;
            }
            else
                _bufRgbArr[_intArr.IndexOf(ind)] = new OdTvRGBColorDef(r, g, b);
        }

        #endregion

        #region Vertices normals

        private void ShowVertexNormals_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvMeshData Mesh = GeomId.openAsMesh();
            _vectorArr = new OdTvVectorArray();
            _intArr = new OdInt32Array();
            _bufVectorArr = new OdTvVectorArray();
            Mesh.getVertexNormalsViaRange(0, (int)Mesh.getVerticesCount(), _vectorArr);
            if (_vectorArr.Count == 0)
            {
                _vectorArr.resize(Mesh.getVerticesCount());
                for (int i = 0; i < Mesh.getVerticesCount(); i++)
                    _vectorArr[i] = OdGeVector3d.kIdentity;
            }

            if (!CheckCountOfObject(_vectorArr.Count))
            {
                _vectorArr.Clear();
                _intArr.Clear();
                _bufVectorArr.Clear();
                _countOfLoadedObjects = 0;
                MM.StopTransaction(mtr);
                return;
            }

            _type = TypeOfPropety.VerticesNormals;

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
            if (CreateDialog("Mesh Vertex normals", new Size(300, 300), currentPanel).ShowDialog() == true && isChanged)
            {
                Mesh.setVertexNormalsViaList(_intArr, _bufVectorArr);
                Update();
            }
            _vectorArr.Clear();
            _intArr.Clear();
            _bufVectorArr.Clear();
            _countOfLoadedObjects = 0;
            MM.StopTransaction(mtr);
        }

        private void LoadVertexNormals()
        {
            if (_countOfLoadedObjects >= _vectorArr.Count)
                return;
            for (int i = 0; i < CountOfLoadedObjects; i++, _countOfLoadedObjects++)
            {
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
            TextBox[] pnt = GetXyz(itm, _vectorArr[(int)itm.Tag]);
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
                _bufVectorArr.Add(SetVectorCoordByType(_vectorArr[ind], type, tb.Text));
            }
            else
                _bufVectorArr[_intArr.IndexOf(ind)] = SetVectorCoordByType(_bufVectorArr[_intArr.IndexOf(ind)], type, tb.Text);
        }

        #endregion

    }
}

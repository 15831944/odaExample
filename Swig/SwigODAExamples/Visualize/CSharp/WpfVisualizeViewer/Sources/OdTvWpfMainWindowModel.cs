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
using System.IO;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.ModelBrowser;
using WpfVisualizeViewer.Misc;
using HorizontalAlignment = System.Windows.HorizontalAlignment;
using OpenFileDialog = Microsoft.Win32.OpenFileDialog;
using SaveFileDialog = Microsoft.Win32.SaveFileDialog;
using Microsoft.Win32;

namespace WpfVisualizeViewer
{
    public class OdTvWpfMainWindowModel
    {
        private MemoryManager MM = MemoryManager.GetMemoryManager();

        private bool _fileIsExist = false;
        public bool FileIsExist
        {
            get { return _fileIsExist; }
            set
            {
                _fileIsExist = value;
                MainWindow.AciveRect.Visibility = _fileIsExist ? Visibility.Visible : Visibility.Collapsed;
                if (_fileIsExist)
                {
                    MainWindow.Title = Path.GetFileName(_tvWpfView.FilePath);
                    MainWindow.NavigationPanel.Visibility = Visibility.Visible;
                    NavigationMenuCommand_Clicked();
                }
                else
                {
                    MainWindow.Title = "WPF Visualize Viewer";
                    MainWindow.PropertiesPalette.IsDeviceExist = _fileIsExist;
                }

                if(TvObjectExplorer == null)
                    TvObjectExplorer = MainWindow.ModelBrowser;
                if(TvPropertiesPalette == null)
                    TvPropertiesPalette = MainWindow.PropertiesPalette;

            }
        }

        private bool _isNavigation = false;
        public bool IsNavigation
        {
            get { return _isNavigation; }
            set
            {
                _isNavigation = value;
                MainWindow.NavigationPanel.Visibility = _isNavigation ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isView;
        public bool IsView
        {
            get { return _isView; }
            set
            {
                _isView = value;
                MainWindow.ViewPanel.Visibility = _isView ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isProjection = false;
        public bool IsProjection
        {
            get { return _isProjection; }
            set
            {
                _isProjection = value;
                MainWindow.ProjectionPanel.Visibility = _isProjection ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isStyle = false;
        public bool IsStyle
        {
            get { return _isStyle; }
            set
            {
                _isStyle = value;
                MainWindow.StylePanel.Visibility = _isStyle ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isMarkup;
        public bool IsMarkup
        {
            get { return _isMarkup; }
            set
            {
                _isMarkup = value;
                MainWindow.MarkupPanel.Visibility = _isMarkup ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isRegen;
        public bool IsRegen
        {
            get { return _isRegen; }
            set
            {
                _isRegen = value;
                MainWindow.RegenPanel.Visibility = _isRegen ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isSectioning;
        public bool IsSectioning
        {
            get { return _isSectioning; }
            set
            {
                _isSectioning = value;
                MainWindow.SectioningPanel.Visibility = _isSectioning ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        private bool _isPanels;
        public bool IsPanels
        {
            get { return _isPanels; }
            set
            {
                _isPanels = value;
                MainWindow.PanelsPanel.Visibility = _isPanels ? Visibility.Visible : Visibility.Collapsed;
            }
        }

        public OdTvWpfMainWindow MainWindow = System.Windows.Application.Current.MainWindow as OdTvWpfMainWindow;
        public TvTreeModelBrowser TvObjectExplorer;
        public TvPropertiesPalette TvPropertiesPalette;
        private OdTvWpfView _tvWpfView = null;
        private WindowsFormsHost _winHost = null;

        public OdTvWpfView WpfView
        {
            get { return _tvWpfView; }
        }

        private ResourceDictionary _resources = App.Current.Resources;

        public double CurrentPropertiesWidth = 230;

        private static int _numSaveFile = 0;

        [Flags]
        public enum AppearanceOptions
        {
            FPSEnabled = 1,
            WCSEnabled = 2,
            UseAnimation = 4
        }

        private AppearanceOptions _appearanceOpt = AppearanceOptions.UseAnimation;

        public AppearanceOptions AppearanceOpt
        {
            get { return _appearanceOpt; }
            set
            {
                _appearanceOpt = value;
                if (_tvWpfView != null)
                {
                    _tvWpfView.OnOffFPS((_appearanceOpt & AppearanceOptions.FPSEnabled) == AppearanceOptions.FPSEnabled);
                    _tvWpfView.OnOffWCS((_appearanceOpt & AppearanceOptions.WCSEnabled) == AppearanceOptions.WCSEnabled);
                    _tvWpfView.OnOffAnimation((_appearanceOpt & AppearanceOptions.UseAnimation) == AppearanceOptions.UseAnimation);
                }
            }
        }

        private double _zoomStep = 2;
        public double ZoomStep
        {
            get { return _zoomStep; }
            set
            {
                _zoomStep = value;
                if (_tvWpfView != null)
                    _tvWpfView.SetZoomStep(_zoomStep);
            }
        }

        internal void ClearDevices()
        {
            if (_tvWpfView != null)
                _tvWpfView.ClearDevices();
        }

        private void AddView()
        {
            _winHost = new WindowsFormsHost();
            _tvWpfView = new OdTvWpfView(this);
            _winHost.Child = _tvWpfView;
            _winHost.VerticalAlignment = VerticalAlignment.Stretch;
            _winHost.HorizontalAlignment = HorizontalAlignment.Stretch;
            MainWindow.RenderArea.Children.Add(_winHost);
        }

        internal void ClearRenderArea()
        {
            if (FileIsExist)
            {
                _tvWpfView.ClearDevices();
                OdTvFactoryId factId = TV_Globals.odTvGetFactory();
                factId.clearDatabases();
                MainWindow.PropertiesPalette.PropertiesPaletteList.Children.Clear();
                MainWindow.ModelBrowser.ModelBrowser.Items.Clear();
                MainWindow.RenderArea.Children.RemoveAt(MainWindow.RenderArea.Children.Count - 1);
                _tvWpfView = null;
                FileIsExist = false;
            }
        }

        #region Appearance commands

        private void PlayNavRectAnimation(int right)
        {
            var animation = new ThicknessAnimation();
            animation.From = MainWindow.AciveRect.Margin;
            animation.To = new Thickness(MainWindow.AciveRect.Margin.Left, MainWindow.AciveRect.Margin.Top, right, MainWindow.AciveRect.Margin.Bottom);
            animation.Duration = TimeSpan.FromSeconds(0.15);
            MainWindow.AciveRect.BeginAnimation(FrameworkElement.MarginProperty, animation);
        }

        private void ResetMenuFlags()
        {
            IsNavigation = false;
            IsView = false;
            IsProjection = false;
            IsStyle = false;
            IsMarkup = false;
            IsRegen = false;
            IsSectioning = false;
            IsPanels = false;
            if (_tvWpfView != null)
                _tvWpfView.OnAppearSectioningPanel(false);
        }

        // navigation menu switched command
        private RelayCommand _navMenuCommand;
        public RelayCommand NavigationMenuCommand
        {
            get { return _navMenuCommand ?? (_navMenuCommand = new RelayCommand(param => NavigationMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void NavigationMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsNavigation = true;
            PlayNavRectAnimation(600);
        }

        // View menu switched command
        private RelayCommand _viewmenuCommand;
        public RelayCommand ViewMenuCommand
        {
            get { return _viewmenuCommand ?? (_viewmenuCommand = new RelayCommand(param => ViewMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void ViewMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsView = true;
            PlayNavRectAnimation(500);
        }

        // Projection menu switched command
        private RelayCommand _projMenuCommand;
        public RelayCommand ProjMenuCommand
        {
            get { return _projMenuCommand ?? (_projMenuCommand = new RelayCommand(param => ProjMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void ProjMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsProjection = true;
            PlayNavRectAnimation(400);
        }

        // Style menu switched command
        private RelayCommand _styleMenuCommand;
        public RelayCommand StyleMenuCommand
        {
            get { return _styleMenuCommand ?? (_styleMenuCommand = new RelayCommand(param => StyleMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void StyleMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsStyle = true;
            PlayNavRectAnimation(300);
        }

        // Markup menu switched command
        private RelayCommand _markupMenuCommand;
        public RelayCommand MarkupMenuCommand
        {
            get { return _markupMenuCommand ?? (_markupMenuCommand = new RelayCommand(param => MarkupMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void MarkupMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsMarkup = true;
            PlayNavRectAnimation(200);
        }

        // Regen menu switched command
        private RelayCommand _regenMenuCommand;
        public RelayCommand RegenMenuCommand
        {
            get { return _regenMenuCommand ?? (_regenMenuCommand = new RelayCommand(param => RegenMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void RegenMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsRegen = true;
            PlayNavRectAnimation(100);
        }

        // Regen menu switched command
        private RelayCommand _sectioningMenuCommand;
        public RelayCommand SectioningMenuCommand
        {
            get { return _sectioningMenuCommand ?? (_sectioningMenuCommand = new RelayCommand(param => SectioningMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void SectioningMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsSectioning = true;
            PlayNavRectAnimation(0);
            if (_tvWpfView != null)
                _tvWpfView.OnAppearSectioningPanel(true);
        }

        // Panels menu switched command
        private RelayCommand _panelsMenuCommand;
        public RelayCommand PanelsMenuCommand
        {
            get { return _panelsMenuCommand ?? (_panelsMenuCommand = new RelayCommand(param => PanelsMenuCommand_Clicked(), param => FileIsExist)); }
        }

        private void PanelsMenuCommand_Clicked()
        {
            ResetMenuFlags();
            IsPanels = true;
            PlayNavRectAnimation(-100);
        }

        // OnOffTreeBrowserCommand command
        private RelayCommand _OnOffTreeBrowserCommand;
        public RelayCommand OnOffTreeBrowserCommand
        {
            get
            {
                if (_OnOffTreeBrowserCommand != null)
                    return _OnOffTreeBrowserCommand;
                else
                    return (_OnOffTreeBrowserCommand = new RelayCommand(param => OnOffModelBrowser(param)));
            }
        }

        private void OnOffModelBrowser(object param)
        {
            bool isEnabled = (bool)param;
            if (isEnabled == true && _tvWpfView != null && _tvWpfView.TvDatabaseId != null)
                MainWindow.ModelBrowser.Initialize(_tvWpfView.TvDatabaseId, _tvWpfView);
            if (isEnabled == false)
            {
                MainWindow.TreeColumn.MinWidth = 0;
                MainWindow.TreeColumn.Width = GridLength.Auto;
                MainWindow.MainGrid.Children.Remove(MainWindow.TreeGrid);
                MainWindow.MainGrid.Children.Remove(MainWindow.TreeSplitter);
            }
            else
            {
                MainWindow.TreeColumn.MinWidth = 220;
                MainWindow.TreeColumn.Width = GridLength.Auto;
                MainWindow.MainGrid.Children.Add(MainWindow.TreeGrid);
                MainWindow.MainGrid.Children.Add(MainWindow.TreeSplitter);
            }
        }

        private RelayCommand _onOffPropertiesPaletteCommand;
        public RelayCommand OnOffPropertiesPaletteCommand
        {
            get
            {
                if (_onOffPropertiesPaletteCommand != null)
                    return _onOffPropertiesPaletteCommand;
                else
                    return (_onOffPropertiesPaletteCommand = new RelayCommand(param => OnOffPropertiesPalette(param)));
            }
        }

        private void OnOffPropertiesPalette(object param)
        {
            bool isEnabled = (bool)param;
            if (isEnabled == false)
            {
                MainWindow.PropertiesColumn.MinWidth = 0;
                MainWindow.PropertiesColumn.Width = GridLength.Auto;
                MainWindow.MainGrid.Children.Remove(MainWindow.PropertiesGrid);
                MainWindow.MainGrid.Children.Remove(MainWindow.PropertiesSplitter);
            }
            else
            {
                MainWindow.PropertiesColumn.MinWidth = 250;
                MainWindow.PropertiesColumn.Width = GridLength.Auto;
                MainWindow.MainGrid.Children.Add(MainWindow.PropertiesGrid);
                MainWindow.MainGrid.Children.Add(MainWindow.PropertiesSplitter);
            }
        }

        #endregion

        #region File commands
        // Open command
        private RelayCommand _openCommand;
        public RelayCommand OpenCommand
        {
            get
            {
                if (_openCommand != null)
                    return _openCommand;
                else
                    return (_openCommand = new RelayCommand(param => OpenCommand_Clicked()));
            }
        }

        private void OpenCommand_Clicked()
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Open Design Visualize Stream|*.vsf|" +
                         "DWG files|*.dwg|" +
                         "OBJ files|*.obj|" +
                         "STL files|*.stl|" +
                         "All Supported files|*.vsf;*.dwg;*.obj;*.stl";

            RegistryKey key = Registry.CurrentUser.OpenSubKey("WpfVisualizeViewer_OpenDialogIndex", true);
            if(key == null)
            {
                key = Registry.CurrentUser.CreateSubKey("WpfVisualizeViewer_OpenDialogIndex");
                key.SetValue("Index", 1);
            }
            dlg.FilterIndex = (int)key.GetValue("Index");

            if (dlg.ShowDialog() != true)
                return;

            key.SetValue("Index", dlg.FilterIndex);
            key.Close();

            if (_tvWpfView == null)
                AddView();
            MainWindow.PropertiesPalette.IsDeviceExist = false;
            _tvWpfView.LoadFile(dlg.FileName);
            _tvWpfView.Focus();
        }

        // New command
        private RelayCommand _newCommand;
        public RelayCommand NewCommand
        {
            get
            {
                if (_newCommand != null)
                    return _newCommand;
                else
                    return (_newCommand = new RelayCommand(param => NewCommand_Clicked()));
            }
        }

        private void NewCommand_Clicked()
        {
            if (_tvWpfView == null)
                AddView();
            _tvWpfView.CreateNewFile();
            _tvWpfView.Focus();
        }

        // Save command
        private RelayCommand _saveCommand;
        public RelayCommand SaveCommand
        {
            get
            {
                if (_saveCommand != null)
                    return _saveCommand;
                else
                    return (_saveCommand = new RelayCommand(param => SaveCommand_Clicked(), param => FileIsExist));
            }
        }

        private void SaveCommand_Clicked()
        {
            if (_tvWpfView.FilePath.Length > 0 && File.Exists(_tvWpfView.FilePath) && System.IO.Path.GetExtension(_tvWpfView.FilePath) == ".vsf")
                _tvWpfView.SaveFile(_tvWpfView.FilePath);
            else
                SaveAsCommand_Clicked();
        }

        // Save as command
        private RelayCommand _saveAsCommand;
        public RelayCommand SaveAsCommand
        {
            get { return _saveAsCommand ?? (_saveAsCommand = new RelayCommand(param => SaveAsCommand_Clicked(), param => FileIsExist)); }
        }

        private void SaveAsCommand_Clicked()
        {
            SaveFileDialog dlg = new SaveFileDialog
            {
                DefaultExt = ".vsf",
                Filter = "Open Design Visualize Stream|*.vsf"
            };

            if (_tvWpfView.FilePath.Length > 0)
            {
                string name = Path.GetFileName(_tvWpfView.FilePath);
                string ext = Path.GetExtension(_tvWpfView.FilePath);
                dlg.FileName = name.Remove(name.Length - ext.Length);
            }
            else
                dlg.FileName = "VisualizeStream_" + _numSaveFile++;

            if (dlg.ShowDialog() != true)
                return;

            if (dlg.FileName.Length > 0)
                _tvWpfView.SaveFile(dlg.FileName);
        }

        // Export to pdf command
        private RelayCommand _export2dPdfCommand;
        public RelayCommand Export2dPdfCommand
        {
            get { return _export2dPdfCommand ?? (_export2dPdfCommand = new RelayCommand(param => Export2dCommand_Clicked(), param => FileIsExist)); }
        }

        private void Export2dCommand_Clicked()
        {
            ExportToPdf(true);
        }

        private RelayCommand _export3dPdfCommand;
        public RelayCommand Export3dPdfCommand
        {
            get { return _export3dPdfCommand ?? (_export3dPdfCommand = new RelayCommand(param => Export3dCommand_Clicked(), param => FileIsExist)); }
        }

        private void Export3dCommand_Clicked()
        {
            ExportToPdf(false);
        }

        private void ExportToPdf(bool is2D)
        {
            SaveFileDialog dlg = new SaveFileDialog
            {
                Filter = "PDF Files(*.pdf)|*.pdf"
            };

            string fileName = Path.GetFileName(_tvWpfView.FilePath);
            if (fileName != null)
            {
                fileName = fileName.Remove(fileName.Length - Path.GetExtension(fileName).Length);
                dlg.FileName = fileName;
            }
            else
                return;

            if (dlg.ShowDialog() != true)
                return;

            if (dlg.FileName.Length > 0)
                _tvWpfView.ExportToPdf(dlg.FileName, is2D);

            _tvWpfView.Focus();
        }

        #endregion

        #region Navigation commands

        public void UncheckDraggersBtns()
        {
            MainWindow.PanBtn.IsChecked = false;
            MainWindow.OrbitBtn.IsChecked = false;
        }

        // pan command
        private RelayCommand _panCommand;
        public RelayCommand PanCommand
        {
            get { return _panCommand ?? (_panCommand = new RelayCommand(param => PanCommand_Clicked(), param => FileIsExist)); }
        }

        private void PanCommand_Clicked()
        {
            MainWindow.OrbitBtn.IsChecked = false;

            if (MainWindow.PanBtn.IsChecked == true)
                _tvWpfView.Pan();
            else
                _tvWpfView.FinishDragger();
        }

        // orbit command
        private RelayCommand _orbitCommand;
        public RelayCommand OrbitCommand
        {
            get { return _orbitCommand ?? (_orbitCommand = new RelayCommand(param => OrbitCommand_Clicked(), param => FileIsExist)); }
        }

        private void OrbitCommand_Clicked()
        {
            MainWindow.PanBtn.IsChecked = false;
            if (MainWindow.OrbitBtn.IsChecked == true)
                _tvWpfView.Orbit();
            else
                _tvWpfView.FinishDragger();
        }

        // zoom in command
        private RelayCommand _zoomCommand;
        public RelayCommand ZoomCommand
        {
            get { return _zoomCommand ?? (_zoomCommand = new RelayCommand(param => ZoomCommand_Clicked(param), param => FileIsExist)); }
        }

        private void ZoomCommand_Clicked(object param)
        {
            switch (param.ToString())
            {
                case "Zoom In":
                    _tvWpfView.Zoom(OdTvWpfView.ZoomType.ZoomIn);
                    break;
                case "Zoom Out":
                    _tvWpfView.Zoom(OdTvWpfView.ZoomType.ZoomOut);
                    break;
                case "Zoom Extents":
                    _tvWpfView.Zoom(OdTvWpfView.ZoomType.ZoomExtents);
                    break;
            }
        }

        #endregion

        #region Markups commands

        // rect markup
        private RelayCommand _markupCommand;
        public RelayCommand MarkupCommand
        {
            get { return _markupCommand ?? (_markupCommand = new RelayCommand(param => MarkupCommand_Clicked(param), param => FileIsExist)); }
        }

        private void MarkupCommand_Clicked(object param)
        {
            switch (param.ToString())
            {
                case "Rectangle":
                    _tvWpfView.DrawRectMarkup();
                    break;
                case "Circle":
                    _tvWpfView.DrawCircMarkup();
                    break;
                case "Handle":
                    _tvWpfView.DrawHandleMarkup();
                    break;
                case "Cloud":
                    _tvWpfView.DrawCloudMarkup();
                    break;
                case "Text":
                    _tvWpfView.DrawTextMarkup();
                    break;
                case "Save":
                    _tvWpfView.SaveMarkup();
                    break;
                case "Load":
                    _tvWpfView.LoadMarkup();
                    break;
            }
        }

        #endregion

        #region View settings

        // render mode commands
        private RelayCommand _renderModeCommand;
        public RelayCommand RenderModeCommand
        {
            get { return _renderModeCommand ?? (_renderModeCommand = new RelayCommand(param => RenderModeCommand_Clicked(param), param => FileIsExist)); }
        }

        private void RenderModeCommand_Clicked(object param)
        {
            switch (param.ToString())
            {
                case "2D Wireframe":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.k2DOptimized);
                    break;
                case "3D Wireframe":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.kWireframe);
                    break;
                case "HiddenLine":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.kHiddenLine);
                    break;
                case "Shaded":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.kFlatShaded);
                    break;
                case "Gouraud shaded":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.kGouraudShaded);
                    break;
                case "Shaded with edges":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.kFlatShadedWithWireframe);
                    break;
                case "Gouraud shaded with edges":
                    _tvWpfView.SetRenderMode(OdTvGsView.RenderMode.kGouraudShadedWithWireframe);
                    break;
            }
            _tvWpfView.Focus();
        }

        public void SetRenderModeButton(OdTvGsView.RenderMode mode)
        {
            MainWindow.Wireframe2DBtn.IsChecked = false;
            MainWindow.Wireframe3DBtn.IsChecked = false;
            MainWindow.HiddenLineBtn.IsChecked = false;
            MainWindow.ShadedBtn.IsChecked = false;
            MainWindow.GouraudShadedBtn.IsChecked = false;
            MainWindow.ShadedWithEdgesBtn.IsChecked = false;
            MainWindow.GouraudShadedWithEdgesBtn.IsChecked = false;
            switch (mode)
            {
                case OdTvGsView.RenderMode.k2DOptimized:
                    MainWindow.Wireframe2DBtn.IsChecked = true;
                    break;
                case OdTvGsView.RenderMode.kWireframe:
                    MainWindow.Wireframe3DBtn.IsChecked = true;
                    break;
                case OdTvGsView.RenderMode.kHiddenLine:
                    MainWindow.HiddenLineBtn.IsChecked = true;
                    break;
                case OdTvGsView.RenderMode.kFlatShaded:
                    MainWindow.ShadedBtn.IsChecked = true;
                    break;
                case OdTvGsView.RenderMode.kGouraudShaded:
                    MainWindow.GouraudShadedBtn.IsChecked = true;
                    break;
                case OdTvGsView.RenderMode.kFlatShadedWithWireframe:
                    MainWindow.ShadedWithEdgesBtn.IsChecked = true;
                    break;
                case OdTvGsView.RenderMode.kGouraudShadedWithWireframe:
                    MainWindow.GouraudShadedWithEdgesBtn.IsChecked = true;
                    break;
            }
            _tvWpfView.Focus();
        }


        // background color command
        private RelayCommand _bgCommand;
        public RelayCommand BackgroundCommand
        {
            get { return _bgCommand ?? (_bgCommand = new RelayCommand(param => BackgroundCommand_Clicked(), param => FileIsExist)); }
        }

        private void BackgroundCommand_Clicked()
        {
            ColorDialog dlg = new ColorDialog();
            if (dlg.ShowDialog() == DialogResult.OK)
                _tvWpfView.SetBackgroundColor(dlg.Color);
            _tvWpfView.Focus();
        }

        // regen commands
        private RelayCommand _regenCommand;
        public RelayCommand RegenCommand
        {
            get { return _regenCommand ?? (_regenCommand = new RelayCommand(param => RegenCommand_Clicked(param), param => FileIsExist)); }
        }

        private void RegenCommand_Clicked(object param)
        {
            switch (param.ToString())
            {
                case "RegenAll":
                    _tvWpfView.Regen(OdTvGsDevice.RegenMode.kRegenAll);
                    break;
                case "RegenVisible":
                    _tvWpfView.Regen(OdTvGsDevice.RegenMode.kRegenVisible);
                    break;
                case "RegenView":
                    _tvWpfView.Regen();
                    break;
            }
            _tvWpfView.Focus();
        }

        // View commands
        private RelayCommand _viewCommand;
        public RelayCommand ViewCommand
        {
            get { return _viewCommand ?? (_viewCommand = new RelayCommand(param => ViewCommand_Clicked(param), param => FileIsExist)); }
        }

        private void ViewCommand_Clicked(object param)
        {
            switch (param.ToString())
            {
                case "Top":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kTop);
                    break;
                case "Bottom":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kBottom);
                    break;
                case "Left":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kLeft);
                    break;
                case "Right":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kRight);
                    break;
                case "Front":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kFront);
                    break;
                case "Back":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kBack);
                    break;
                case "SW Isometric":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kSW);
                    break;
                case "SE Isometric":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kSE);
                    break;
                case "NE Isometric":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kNE);
                    break;
                case "NW Isometric":
                    _tvWpfView.Set3DView(OdTvExtendedView.e3DViewType.kNW);
                    break;
            }
            _tvWpfView.Focus();
        }

        // Projection commands
        private RelayCommand _projCommand;
        public RelayCommand ProjectionCommand
        {
            get { return _projCommand ?? (_projCommand = new RelayCommand(param => ProjectionCommand_Clicked(param), param => FileIsExist)); }
        }

        private void ProjectionCommand_Clicked(object param)
        {
            switch (param.ToString())
            {
                case "Isometric":
                    MainWindow.PerspectiveBtn.IsChecked = false;
                    MainWindow.IsometricBtn.IsChecked = true;
                    _tvWpfView.SetProjectionType(OdTvGsView.Projection.kParallel);
                    break;
                case "Perspective":
                    MainWindow.IsometricBtn.IsChecked = false;
                    MainWindow.PerspectiveBtn.IsChecked = true;
                    _tvWpfView.SetProjectionType(OdTvGsView.Projection.kPerspective);
                    break;
            }
            _tvWpfView.Focus();
        }

        #endregion

        #region Sectioning commands

        // regen commands
        private RelayCommand _sectioningCommand;
        public RelayCommand SectioningCommand
        {
            get { return _sectioningCommand ?? (_sectioningCommand = new RelayCommand(param => SectioningCommand_Clicked(param), param => FileIsExist)); }
        }

        private void SectioningCommand_Clicked(object param)
        {
            if (_tvWpfView == null)
                return;
            switch (param.ToString())
            {
                case "CuttingPlaneShow":
                    {
                        _tvWpfView.ShowCuttingPlanes();
                        string img = _tvWpfView.SectioningOptions.IsShown ? "CuttingPlane" : "CuttingPlaneOff";
                        MainWindow.CuttingPlaneShowImg.Source = System.Windows.Application.Current.Resources[img] as BitmapImage;
                        break;
                    }
                case "AddCuttingPlaneX":
                    {
                        OdGeVector3d eyeDir = _tvWpfView.GetEyeDirection();
                        double xDot = eyeDir.dotProduct(OdGeVector3d.kXAxis);
                        if (Math.Abs(xDot).Equals(0d))
                            xDot = 1d;

                        OdGeVector3d axis = new OdGeVector3d(OdGeVector3d.kXAxis);
                        axis *= -xDot;
                        axis = axis.normalize();
                        AddCuttingPlane(axis);
                        break;
                    }
                case "AddCuttingPlaneY":
                    {
                        OdGeVector3d eyeDir = _tvWpfView.GetEyeDirection();
                        double yDot = eyeDir.dotProduct(OdGeVector3d.kYAxis);
                        if (Math.Abs(yDot).Equals(0d))
                            yDot = 1d;

                        OdGeVector3d axis = new OdGeVector3d(OdGeVector3d.kYAxis);
                        axis *= -yDot;
                        axis = axis.normalize();
                        AddCuttingPlane(axis);
                        break;
                    }
                case "AddCuttingPlaneZ":
                    {
                        OdGeVector3d eyeDir = _tvWpfView.GetEyeDirection();
                        double zDot = eyeDir.dotProduct(OdGeVector3d.kZAxis);
                        if (Math.Abs(zDot).Equals(0d))
                            zDot = 1d;

                        OdGeVector3d axis = new OdGeVector3d(OdGeVector3d.kZAxis);
                        axis *= -zDot;
                        axis = axis.normalize();
                        AddCuttingPlane(axis);
                        break;
                    }
                case "FillCuttingPlane":
                    {
                        _tvWpfView.ShowSectioningOptions();
                        break;
                    }
                case "RemoveCuttingPlane":
                    {
                        _tvWpfView.RemoveCuttingPlanes();
                        break;
                    }
            }
            _tvWpfView.Focus();
        }

        private void AddCuttingPlane(OdGeVector3d axis)
        {
            OdTvResult res = OdTvResult.tvOk;
            if (!_tvWpfView.AddCuttingPlane(axis, res))
            {
                if(res == OdTvResult.tvOk)
                {
                    System.Windows.Forms.MessageBox.Show("There are can not be more than " + OdTvWpfView.OD_TV_CUTTING_PLANE_MAX_NUM + " cutting planes", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }
        }

        #endregion

        #region ModelBrowserCommads

        private RelayCommand _itemClickCommand;
        public RelayCommand ItemClickCommand
        {
            get { return _itemClickCommand ?? (_itemClickCommand = new RelayCommand(param => ItemClickCommand_Clicked(param))); }
        }

        private void ItemClickCommand_Clicked(object param)
        {
            TvTreeItem itm = param as TvTreeItem;
            if (itm == null || _tvWpfView == null)
                return;
            _tvWpfView.AddBoldItem(itm);
            TvPropertiesPalette.FillObjectParameters(itm);

            if(itm.NodeData.Type == TvBrowserItemType.Entity)
            {
                OdTvEntityId enId = itm.NodeData.EntityId;
                if(_tvWpfView != null && ( enId.getType() == OdTvEntityId.EntityTypes.kEntity
                                        || enId.getType() == OdTvEntityId.EntityTypes.kInsert ))
                {
                    _tvWpfView.AddEntityToSet(enId);
                }
                    
            }
        }

        #endregion

    }
}

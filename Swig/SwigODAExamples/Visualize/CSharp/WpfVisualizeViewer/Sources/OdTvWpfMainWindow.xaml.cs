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
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using Teigha.Visualize;
using System.Windows.Media.Imaging;

namespace WpfVisualizeViewer
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class OdTvWpfMainWindow : Window
    {
        public static OdTvWpfMainWindowModel ViewModel = null;

        public static bool IsClosing { get; private set; }

        public OdTvWpfMainWindow()
        {
            IsClosing = false;

            try
            {
                TeighaActivate();
                TV_Globals.odTvInitialize();
            }
            catch(Exception ex)
            {
                MessageBox.Show("Ñan not activate the product!\n" + ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK);
            }

            ViewModel = new OdTvWpfMainWindowModel();
            DataContext = ViewModel;

            InitializeComponent();

            ViewModel.FileIsExist = false;
            this.Closing += OdTvWpfMainWindow_Closing;
            this.KeyDown += OdTvWpfMainWindow_KeyDown;
            this.KeyUp += OdTvWpfMainWindow_KeyUp;

            ContextMenu menu = new ContextMenu()
            {
                Background = new SolidColorBrush(Colors.White)
            };
            MenuItem openItm = new MenuItem() {Header = "Open", Height = 30};
            openItm.Icon = new Image
            {
                Source = Application.Current.Resources["OpenImg"] as BitmapImage
            };
            menu.Items.Add(openItm);
            openItm.Command = ViewModel.OpenCommand;
            MenuItem saveItm = new MenuItem() { Header = "Save", Height = 30 };
            saveItm.Icon = new Image
            {
                Source = Application.Current.Resources["SaveImg"] as BitmapImage
            };
            menu.Items.Add(saveItm);
            saveItm.Command = ViewModel.SaveCommand;
            MenuItem saveAsItm = new MenuItem() { Header = "SaveAs", Height = 30 };
            saveAsItm.Icon = new Image
            {
                Source = Application.Current.Resources["SaveAsImg"] as BitmapImage
            };
            menu.Items.Add(saveAsItm);
            saveAsItm.Command = ViewModel.SaveAsCommand;
            menu.Items.Add(new Separator());
            MenuItem pdf2dItm = new MenuItem() {Header = "Export to 2D PDF", Height = 30};
            pdf2dItm.Icon = new Image
            {
                Source = Application.Current.Resources["PdfImg"] as BitmapImage
            };
            pdf2dItm.Command = ViewModel.Export2dPdfCommand;
            menu.Items.Add(pdf2dItm);
            MenuItem pdf3dItem = new MenuItem() {Header = "Export to 3D PDF", Height = 30};
            pdf3dItem.Icon = new Image
            {
                Source = Application.Current.Resources["PublishImg"] as BitmapImage
            };
            pdf3dItem.Command = ViewModel.Export3dPdfCommand;
            menu.Items.Add(pdf3dItem);
            menu.Items.Add(new Separator());
            MenuItem closeItm = new MenuItem() {Header = "Close", Height = 30};
            menu.Items.Add(closeItm);
            closeItm.Click += Close_Click;

            DropMenuBtn.DropDown = menu;
        }

        private void OdTvWpfMainWindow_KeyUp(object sender, KeyEventArgs e)
        {
            if (ViewModel.WpfView != null)
                ViewModel.WpfView.KeyUpEvent(sender, e);
        }

        private void OdTvWpfMainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if(ViewModel.WpfView != null)
                ViewModel.WpfView.KeyDownEvent(sender, e);
        }

        private void TeighaActivate()
        {
            Teigha.Core.Globals.odActivate(ActivationData.userInfo, ActivationData.userSignature);
        }

        private void TeighaDeactivate()
        {
            Teigha.Core.Globals.odCleanUpStaticData();
        }

        // Clear all devices before close, need for correct finish odTvUninitialize()
        private void OdTvWpfMainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (ViewModel != null && ViewModel.FileIsExist)
            {
                ViewModel.IsNavigation = false;
                ViewModel.IsView = false;
                ViewModel.IsProjection = false;
                ViewModel.IsStyle = false;
                ViewModel.IsMarkup = false;
                ViewModel.IsSectioning = false;
                ViewModel.IsRegen = false;
                ViewModel.IsPanels = false;
                ViewModel.ClearRenderArea();
                IsClosing = false;
                e.Cancel = true;
            }
            else
            {
                IsClosing = true;
                if(ViewModel != null)
                    ViewModel.ClearDevices();
                e.Cancel = false;
            }
        }

        ~OdTvWpfMainWindow()
        {
            try
            {
                TV_Globals.odTvUninitialize();
                TeighaDeactivate();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ñan not deactivate the product!\n" + ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK);
            }
        }

        // Exit click event
        private void Close_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void PropertiesSplitter_OnMouseMove(object sender, MouseEventArgs e)
        {
            GridSplitter gs = sender as GridSplitter;
            if (gs == null || !gs.IsDragging)
                return;
            ViewModel.CurrentPropertiesWidth = PropertiesColumn.ActualWidth;
        }

        private void PropertiesSplitter_OnDragCompleted(object sender, DragCompletedEventArgs e)
        {
            ViewModel.CurrentPropertiesWidth = PropertiesColumn.ActualWidth;
        }
    }
}

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
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Teigha.Visualize;
using WpfVisualizeViewer.Misc;

namespace WpfVisualizeViewer
{
    /// <summary>
    /// Interaction logic for CuttingPlaneOptionsDialog.xaml
    /// </summary>
    public partial class CuttingPlaneOptionsDialog : Window
    {

        private Colorpicker _fillColor = null;
        private Colorpicker _fillPatternColor = null;
        private OdTvWpfView _wpfView = null;

        public CuttingPlaneOptionsDialog(OdTvWpfView wpfView)
        {
            InitializeComponent();

            _wpfView = wpfView;
            FillControls();
        }

        private void FillControls()
        {
            FillingEnabled.IsChecked = _wpfView.SectioningOptions.IsFilled;
            // add fill color combobox
            _fillColor = new Colorpicker(BasePaletteProperties.GetColorDefFromUInt(_wpfView.SectioningOptions.FillingColor), null);
            _fillColor.VerticalAlignment = VerticalAlignment.Center;
            _fillColor.HorizontalAlignment = HorizontalAlignment.Stretch;
            Grid.SetColumn(_fillColor, 1);
            Grid.SetRow(_fillColor, 1);
            CutPlaneFillingGrid.Children.Add(_fillColor);
            // fill alpha
            AlphaTextBox.Text = BasePaletteProperties.GetAlphaFromColor(_wpfView.SectioningOptions.FillingColor).ToString();

            // add fill pattern color combobox
            FillingPatternEnabled.IsChecked = _wpfView.SectioningOptions.FillingPatternEnabled;
            FillPatternStyleCombobox.SelectedIndex = (int)_wpfView.SectioningOptions.FillingPaternStyle;
            _fillPatternColor = new Colorpicker(BasePaletteProperties.GetColorDefFromUInt(_wpfView.SectioningOptions.FillingPatternColor), null);
            _fillPatternColor.VerticalAlignment = VerticalAlignment.Center;
            _fillPatternColor.HorizontalAlignment = HorizontalAlignment.Stretch;
            Grid.SetColumn(_fillPatternColor, 1);
            Grid.SetRow(_fillPatternColor, 2);
            CutPlaneFillingPatternGrid.Children.Add(_fillPatternColor);
        }

        private void WriteOptions()
        {
            _wpfView.SectioningOptions.IsFilled = FillingEnabled.IsChecked ?? false;
            _wpfView.SectioningOptions.FillingColor = BasePaletteProperties.ColorToUInt(_fillColor.SelectedColor, Int32.Parse(AlphaTextBox.Text));
            _wpfView.SectioningOptions.FillingPatternEnabled = FillingPatternEnabled.IsChecked ?? false;
            _wpfView.SectioningOptions.FillingPaternStyle = (OdTvGsView.CuttingPlaneFillStyle)FillPatternStyleCombobox.SelectedIndex;
            _wpfView.SectioningOptions.FillingPatternColor = BasePaletteProperties.ColorToUInt(_fillPatternColor.SelectedColor);
            _wpfView.SectioningOptions.SaveToRegister();
            _wpfView.ApplySectioningOptions();
        }

        private void OkBtn_Click(object sender, RoutedEventArgs e)
        {
            WriteOptions();
            Close();
        }

        private void CloseBtn_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void ApplyBtn_Click(object sender, RoutedEventArgs e)
        {
            WriteOptions();
        }
    }
}

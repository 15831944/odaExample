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
using Teigha.Core;
using Teigha.Visualize;
using WpfVisualizeViewer.Misc;
using Microsoft.Win32;
using System.Windows.Media;

namespace WpfVisualizeViewer.Draggers
{
    public class OdTvSectioningOptions
    {
        public static int ODTV_CUTTING_PLANES_MAX_NUM = 5;
        public bool IsNeedSaveSettings { get; set; }
        public bool IsShown { get; set; }
        public bool IsFilled { get; set; }
        public uint FillingColor { get; set; }
        public bool FillingPatternEnabled { get; set; }
        public OdTvGsView.CuttingPlaneFillStyle FillingPaternStyle { get; set; }
        public uint FillingPatternColor { get; set; }

        private const string SECTIONING_OPTIONS_SUBKEY = "WpfVisualizeViewer_SectioningOptions";
        private const string FILL_KEY = "FILL";
        private const string FILLING_COLOR_KEY = "FillingColor";
        private const string FILLING_PATTERN_ENABLED_KEY = "FillingPatternEnabled";
        private const string FILLING_PATTERN_STYLE_KEY = "FillingPatternStyle";
        private const string FILLING_PATTERN_COLOR_KEY = "FillingPatternColor";

        public OdTvSectioningOptions()
        {
            IsNeedSaveSettings = true;
            IsShown = true;

            RegistryKey key = Registry.CurrentUser.OpenSubKey(SECTIONING_OPTIONS_SUBKEY, true);
            if (key == null)
            {
                key = Registry.CurrentUser.CreateSubKey(SECTIONING_OPTIONS_SUBKEY);
                key.SetValue(FILL_KEY, true);
                Color fillColor = new Color();
                fillColor.R = 255;
                fillColor.G = 0;
                fillColor.B = 0;
                fillColor.A = 255;
                key.SetValue(FILLING_COLOR_KEY, BasePaletteProperties.ColorToUInt( fillColor ) );
                key.SetValue(FILLING_PATTERN_ENABLED_KEY, true);
                key.SetValue(FILLING_PATTERN_STYLE_KEY, (int)OdTvGsView.CuttingPlaneFillStyle.kCheckerboard);
                key.SetValue(FILLING_PATTERN_COLOR_KEY, BasePaletteProperties.ColorToUInt(new OdTvColorDef(0, 0, 255)));
            }

            IsFilled = Convert.ToBoolean(key.GetValue(FILL_KEY));
            FillingColor = Convert.ToUInt32(key.GetValue(FILLING_COLOR_KEY));
            FillingPatternEnabled = Convert.ToBoolean(key.GetValue(FILLING_PATTERN_ENABLED_KEY));
            FillingPaternStyle = (OdTvGsView.CuttingPlaneFillStyle)Convert.ToInt32(key.GetValue(FILLING_PATTERN_STYLE_KEY));
            FillingPatternColor = Convert.ToUInt32(key.GetValue(FILLING_PATTERN_COLOR_KEY));
        }

        public void SaveToRegister()
        {
            RegistryKey key = Registry.CurrentUser.OpenSubKey(SECTIONING_OPTIONS_SUBKEY, true);
            if (key == null)
                key = Registry.CurrentUser.CreateSubKey(SECTIONING_OPTIONS_SUBKEY);
            key.SetValue(FILL_KEY, IsFilled);
            key.SetValue(FILLING_COLOR_KEY, FillingColor);
            key.SetValue(FILLING_PATTERN_ENABLED_KEY, FillingPatternEnabled);
            key.SetValue(FILLING_PATTERN_STYLE_KEY, (int)FillingPaternStyle);
            key.SetValue(FILLING_PATTERN_COLOR_KEY, FillingPatternColor);
        }
    }
}

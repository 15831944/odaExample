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
using System.Windows.Media;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvDatabaseProperties : BasePaletteProperties
    {
        public TvDatabaseProperties(OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            if (devId == null || renderArea == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            TvDatabaseInfo dbInfo = renderArea.DatabaseInfo;
            int row = 0;
            if (dbInfo.Type == TvDatabaseInfo.ProfilingType.Import)
            {
                AddLabelAndTextBox("Loading:", (dbInfo.ImportTime / 1000d) + "s", MainGrid, new[] { row, 0, row++, 1 }, true);

                StretchingTreeViewItem itm = AddImportNode((dbInfo.getVectorizingTime() / 1000d) + "s", MainGrid, new[] { row, 0, row++, 1 });
                AddLabelAndTextBox("TV API:", (dbInfo.TvCreationTime / 1000d) + "s", itm, true);
            }
            else if (dbInfo.Type == TvDatabaseInfo.ProfilingType.FromFile)
                AddLabelAndTextBox("Load:", (dbInfo.ImportTime / 1000d) + "s", MainGrid, new[] { row, 0, row++, 1 }, true);
            else
            {
                StretchingTreeViewItem itm = AddImportNode((dbInfo.getVectorizingTime() / 1000d) + "s", MainGrid, new[] { row, 0, row++, 1 });
                AddLabelAndTextBox("TV API:", (dbInfo.TvCreationTime / 1000d) + "s", itm, true);
            }

            AddLabelAndTextBox("Vectorization:", (dbInfo.FirstUpdateTime / 1000d) + "s", MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Total:", (dbInfo.TotalTime / 1000d) + "s", MainGrid, new[] { row, 0, row++, 1 }, true);

            if (dbInfo.Type == TvDatabaseInfo.ProfilingType.Import ||
                dbInfo.Type == TvDatabaseInfo.ProfilingType.FromFile)
            {
                AddLabelAndTextBox("Type:", "Model file", MainGrid, new[] { row, 0, row++, 1 }, true);
                AddLabelAndTextBox("Filename:", dbInfo.FilePath, MainGrid, new[] { row, 0, row, 1 }, true);
            }
            else if (dbInfo.Type == TvDatabaseInfo.ProfilingType.BuiltIn)
                AddLabelAndTextBox("Type:", "Built-in model", MainGrid, new[] { row, 0, row, 1 }, true);
            else
                AddLabelAndTextBox("Type:", "Custom model", MainGrid, new[] { row, 0, row, 1 }, true);

            MM.StopTransaction(mtr);
        }

        StretchingTreeViewItem AddImportNode(string text, Grid grid, int[] arr)
        {
            Label lbl = new Label { Content = "Import:" };
            TextBox tb = new TextBox
            {
                Text = text,
                IsReadOnly = true,
                VerticalAlignment = VerticalAlignment.Stretch,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Center,
                Margin = new Thickness(-10, 0, 0, 3)
            };

            Grid.SetColumn(lbl, 0);
            Grid.SetColumn(tb, 1);

            StretchingTreeViewItem tItm = new StretchingTreeViewItem { Header = CreateGridWithElements(2, lbl, tb)
                , BorderThickness = new Thickness(0) };

            StretchingTreeView tree = new StretchingTreeView()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                HorizontalContentAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Stretch,
                VerticalContentAlignment = VerticalAlignment.Stretch,
                BorderThickness = new Thickness(0),
                Background = new SolidColorBrush(new Color() { A = 255, R = 248, G = 248, B = 248 })
            };

            tree.Items.Add(tItm);
            Grid.SetRow(tree, arr[0]);
            Grid.SetColumn(tree, arr[1]);
            Grid.SetColumnSpan(tree, 3);
            MainGrid.Children.Add(tree);

            return tItm;
        }
    }
}

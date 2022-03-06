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
using System.Windows.Controls;
using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    class TvRasterImageProperties : BasePaletteProperties
    {
        private OdTvRasterImageId _imgId;

        public TvRasterImageProperties(OdTvRasterImageId imgId, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            _imgId = imgId;
            OdTvRasterImage img = _imgId.openObject();
            int row = 0;
            AddLabelAndTextBox("Filename:", img.getSourceFileName(), MainGrid, new[] {row, 0, row++, 1}, true);
            AddLabelAndTextBox("Type:", img.getType().ToString().Remove(0, 1), MainGrid, new[] {row, 0, row++, 1}, true);
            AddLabelAndCheckBox("Load status:", img.isLoaded(), MainGrid, new[] {row, 0, row++, 1}, true);
            AddLabelAndTextBox("Format:", img.getFormat().ToString().Remove(0, 1), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Alignment:", img.getAlignment().ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            StretchingTreeViewItem itm = AddTreeItem("Size", MainGrid, new[] {row, 0, row, 1});
            Grid grid = CreateGrid(2, 2);
            itm.Items.Add(grid);
            AddLabelAndTextBox("X:", img.getSize().x.ToString(CultureInfo.InvariantCulture), grid, new[] {0, 0, 0, 1}, true);
            AddLabelAndTextBox("Y:", img.getSize().y.ToString(CultureInfo.InvariantCulture), grid, new[] { 1, 0, 1, 1 }, true);
            MM.StopTransaction(mtr);
        }
    }
}

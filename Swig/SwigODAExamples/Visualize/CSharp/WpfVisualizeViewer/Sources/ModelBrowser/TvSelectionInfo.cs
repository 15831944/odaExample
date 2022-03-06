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
    class TvSelectionInfo : BasePaletteProperties
    {
        public TvSelectionInfo(OdTvSelectionSet sSet, OdTvGsDeviceId devId, OdTvWpfView renderArea)
            : base(devId, renderArea)
        {
            if (devId == null || renderArea == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            int row = 0;
            uint nEntities = 0;
            uint nGeometryData = 0;
            uint nFaces = 0;
            uint nEdges = 0;

            // get selection set iterator
            OdTvSelectionSetIterator it = sSet.getIterator();
            for (; !it.done(); it.step())
            {
                if(!it.getEntity().isNull())
                {
                    if (it.getGeometryData().isNull())
                        nEntities++;
                    else
                    {
                        OdUInt32Array indFaces = new OdUInt32Array();
                        it.getFaces(indFaces);

                        OdUInt32Array indEdges = new OdUInt32Array();
                        it.getEdges(indEdges);

                        if (indFaces.Count == 0 && indEdges.Count == 0)
                            nGeometryData++;
                        else
                        {
                            nFaces += (uint)indFaces.Count;
                            nEdges += (uint)indEdges.Count;
                        }
                    }
                }
            }

            AddLabelAndTextBox("Number of entities:", nEntities.ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of geometries:", nGeometryData.ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of faces:", nFaces.ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);
            AddLabelAndTextBox("Number of edges:", nEdges.ToString(), MainGrid, new[] { row, 0, row++, 1 }, true);

            MM.StopTransaction(mtr);
        }

    }
}



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
using System.Text;
using Teigha.Core;
using Teigha.Visualize;

namespace OdExVisualizeFormatsConverterSwig
{
  public class OdExVisualizeObjToDwgConverter : OdExVisualizeConverterBase
  {
    public OdExVisualizeObjToDwgConverter(String inFilePath, String outFilePath) : base(inFilePath, outFilePath)
    { }

    protected override OdTvBaseImportParams CreateImportParams(string filePath)
    {
      string ext = System.IO.Path.GetExtension(filePath);
      if (String.Compare(ext, ".obj", true) != 0)
        throw new OdError("Input file is not obj");

      OdTvObjImportParams importParams = new OdTvObjImportParams();

      //Parameters by default
      uint iDefaultColor = importParams.getDefaultColor();
      bool bBrepFlipUVCoordinates = false;
      bool bCalculateNormals = true;
      bool bImportBrepAsBrep = true;
      bool bNeedCDATree = false;
      bool bNeedCollectPropertiesInCDA = false;

      importParams.setFilePath(filePath);
      importParams.setDefaultColor(iDefaultColor);
      importParams.setBrepFlipUVCoordinates(bBrepFlipUVCoordinates);
      importParams.setCalculateNormals(bCalculateNormals);
      importParams.setImportBrepAsBrep(bImportBrepAsBrep);
      importParams.setNeedCDATree(bNeedCDATree);
      importParams.setNeedCollectPropertiesInCDA(bNeedCollectPropertiesInCDA);

      return importParams;
    }

    protected override OdTvBaseExportParams CreateExportParams(OdTvDatabase currentDatabase, string filePath)
    {
      string ext = System.IO.Path.GetExtension(filePath);
      if (String.Compare(ext, ".dwg", true) != 0)
        throw new OdError("Output file is not dwg");

      OdTvDwgExportParams exportParams = new OdTvDwgExportParams();
      exportParams.setFilePath(filePath);

      OdTvGsViewId viewId;
      OdTvModelId modelId;
      GetFirstViewModel(currentDatabase, out viewId, out modelId);

      exportParams.setView(viewId);
      exportParams.setModel(modelId);
      return exportParams;
    }

    private void GetFirstViewModel(OdTvDatabase db, out OdTvGsViewId viewId, out OdTvModelId modelId)
    {
      List<Tuple<String, OdTvGsDeviceId>> devices = GetDevices(db);
      if (devices.Count == 0)
        throw new OdError("Not have gs-devices");

      OdTvGsDeviceId firstDevId = devices[0].Item2;

      List<Tuple<String, OdTvGsViewId>> views = GetViews(firstDevId);
      if (views.Count == 0)
        throw new OdError("Not have gs-views");

      OdTvGsViewId firstViewId = views[0].Item2;

      List<Tuple<String, OdTvModelId>> models = GetModels(firstViewId);
      if (models.Count == 0)
        throw new OdError("Not have gs-models");

      OdTvModelId firstModelId = models[0].Item2;

      viewId = firstViewId;
      modelId = firstModelId;
    }

    private List<Tuple<String, OdTvGsDeviceId>> GetDevices(OdTvDatabase pDb)
    {
      List<Tuple<String, OdTvGsDeviceId>> devices = new List<Tuple<string, OdTvGsDeviceId>>();
      for (OdTvDevicesIterator pIt = pDb.getDevicesIterator(); !pIt.done(); pIt.step())
      {
        OdTvGsDeviceId devId = pIt.getDevice();
        OdTvGsDevice pDev = devId.openObject();
        String devName = pDev.getName();
        if (devName[0] != '$')
        {
          devices.Add(new Tuple<string, OdTvGsDeviceId>(devName, devId));
        }
      }
      return devices;
    }

    private List<Tuple<String, OdTvGsViewId>> GetViews(OdTvGsDeviceId devId)
    {
      List<Tuple<String, OdTvGsViewId>> views = new List<Tuple<string, OdTvGsViewId>>();

      OdTvGsDevice pDev = devId.openObject();
      for (int i = 0; i < pDev.numViews(); i++)
      {
        OdTvGsViewId viewId = pDev.viewAt(i);
        if (viewId.isNull())
          continue;
        OdTvGsView pView = viewId.openObject();
        String viewName = pView.getName();
        if (viewName[0] != '$')
        {
          views.Add(new Tuple<string, OdTvGsViewId>(viewName, viewId));
        }
      }
      return views;
    }

    private List<Tuple<String, OdTvModelId>> GetModels(OdTvGsViewId viewId)
    {
      List<Tuple<String, OdTvModelId>> models = new List<Tuple<string, OdTvModelId>>();
      OdTvGsView pView = viewId.openObject();
      for (int i = 0; i < pView.numModels(); i++)
      {
        OdTvModelId modelId = pView.modelAt(i);
        if (modelId.isNull())
          continue;
        OdTvModel pModel = modelId.openObject();
        String modelName = pModel.getName();
        if (modelName[0] != '$')
          models.Add(new Tuple<string, OdTvModelId>(modelName, modelId));
      }
      return models;
    }
  }
}
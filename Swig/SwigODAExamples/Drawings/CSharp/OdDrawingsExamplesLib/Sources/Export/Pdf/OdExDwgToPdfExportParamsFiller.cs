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
using Teigha.TD;
using OdKernelExamplesMgdLib.Export.Pdf;
using OdDrawingsExamplesMgdLib.ExDbLayout;

namespace OdDrawingsExamplesMgdLib.Export.Pdf
{
  public class OdExDwgToPdfExportParamsFiller : OdExPdfExportParamsFiller
  {
    protected override OdExPdfExportConvertFromType ConvertFromType()
    {
      return OdExPdfExportConvertFromType.Dwg;
    }

    protected override void FillLayoutList(OdRxObject database, OdRxObject rxHostApp)
    {
      OdStringArray layouts = new OdStringArray();
      OdRxObjectPtrArray databases = new OdRxObjectPtrArray();

      OdDbDatabaseCollection m_pDbCollection = TD_Db.oddbDatabaseCollection();
      if (this.AllLayouts)
      {
        if (MultipleDatabases && m_pDbCollection != null && m_pDbCollection.count() > 1)
        {
          for (OdRxIterator it = m_pDbCollection.newIterator(); !it.done(); it.next())
          {
            OdDbLayoutExamples.fillListForDb(OdDbDatabase.cast(it.getObject()), layouts, databases, MultipleDatabases, false);
          }
        }
        else
        {
          OdDbDatabase db = OdDbDatabase.cast(database);
          if (db == null)
            throw new Exception("OdDbDatabase is NULL");

          OdDbLayoutExamples.fillListForDb(db, layouts, databases, MultipleDatabases, false);
        }
      }
      else
      {
        if (MultipleDatabases && m_pDbCollection != null && m_pDbCollection.count() > 1)
        {
          for (OdRxIterator it = m_pDbCollection.newIterator(); !it.done(); it.next())
          {
            OdDbBlockTableRecord pLayoutBlock = OdDbDatabase.cast(it.getObject()).getActiveLayoutBTRId().safeOpenObject() as OdDbBlockTableRecord;
            OdDbLayout pLayout = pLayoutBlock.getLayoutId().safeOpenObject(OpenMode.kForWrite) as OdDbLayout;
            layouts.Add(pLayout.getLayoutName());
            databases.Add(it.getObject());
          }
        }
        else
        {
          OdDbDatabase db = OdDbDatabase.cast(database);
          if (db == null)
            throw new Exception("OdDbDatabase is NULL");

          OdDbBlockTableRecord pLayoutBlock = db.getActiveLayoutBTRId().safeOpenObject() as OdDbBlockTableRecord;
          OdDbLayout pLayout = pLayoutBlock.getLayoutId().safeOpenObject(OpenMode.kForWrite) as OdDbLayout;
          layouts.Add(pLayout.getLayoutName());
        }
      }

      this.LayoutList = layouts;
      this.Databases = databases;

      OdDbDatabase m_pDb = OdDbDatabase.cast(database);

      OdDbHostAppServices _serv = OdDbHostAppServices.cast(rxHostApp);

      OdDbPlotSettingsValidator pValidator = null;      

      OdDbDictionary pLayoutDict = null;
      if (databases.Count == 0)
        pLayoutDict = OdDbDictionary.cast(m_pDb.getLayoutDictionaryId().safeOpenObject());

      for (int f = 0; f < layouts.Count; ++f)
      {
        if (databases.Count > 0)
        {
          OdDbDatabase pDb = OdDbDatabase.cast( databases[f] );
          pLayoutDict = OdDbDictionary.cast(pDb.getLayoutDictionaryId().safeOpenObject());
        }
        OdDbObjectId id = pLayoutDict.getAt(layouts[f]);
        if (id.isNull())
          continue;
        OdDbLayout pLayout = OdDbLayout.cast( pLayoutDict.getAt(layouts[f]).safeOpenObject(OpenMode.kForWrite));
        String printer = pLayout.getPlotCfgName();

        if (printer != "DWG To PDF.pc3" && printer != "Custom Device")
        {
          double dW, dH;
          pLayout.getPlotPaperSize(out dW, out dH);
          OdDbPlotSettings.PlotPaperUnits units = pLayout.plotPaperUnits();
          if (pValidator == null)
            pValidator = _serv.plotSettingsValidator();
          if ( !(pValidator == null) )
          {
            String mediaName = pLayout.getCanonicalMediaName();
            OdResult res = pValidator.setPlotCfgName(OdDbPlotSettings.cast(pLayout), "DWG To PDF.pc3", mediaName);
          }
        }
      }
      
    }

    public static OdExPdfExportParamsFiller CreateDefault()
    {
      OdExPdfExportParamsFiller result = new OdExDwgToPdfExportParamsFiller();
      OdExPdfExportParamsFiller.FillDefalut(result);
      return result;
    }
  }
}
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

namespace OdPdfExportWithPrcSwigMgd.Samples
{
  public class OdPdfPrcFilterExample : OdPdfExportWithPrcExample
  {
    #region Interface
    public override String Description => "Export part of geometry to PRC view and part to PDF page";
    #endregion

    #region Impl
    public override void Execute(OdDbHostAppServices svcs, String pdfPath)
    {
      MemoryTransaction mStartTrans = MemoryManager.GetMemoryManager().StartTransaction();

      /******************************************************************/
      /* Create a Pdf export module                                     */
      /******************************************************************/
      OdRxModule mod = Globals.odrxDynamicLinker().loadApp("TD_PdfExport");
      PdfExportModule pdf_export_module = new PdfExportModule(OdRxModule.getCPtr(mod).Handle, false);

      Globals.odrxDynamicLinker().loadApp("OdPrcModule");
      Globals.odrxDynamicLinker().loadApp("OdDwg2PrcExport");

      /******************************************************************/
      /* Create a database and load the drawing into it.                */
      /******************************************************************/

      OdDbDatabase pDb = fillDatabase(svcs);

      /****************************************************************/
      /* Initialize the conversion parameters                         */
      /****************************************************************/
      using (PDFExportParams _params = new PDFExportParams())
      {
        fillPdfExportParams(_params, pDb, pdfPath);

        OdPdfExport exporter = pdf_export_module.create();
        UInt32 errCode = exporter.exportPdf(_params);

        PrcLayerFilter.UninitRx();

        if (errCode != 0)
        {
          String errMes = exporter.exportPdfErrorCode(errCode);
          Console.WriteLine(String.Format("\nexportPdf error returned: 0x{0}. \n {1}", errCode.ToString("x"), errMes));
        }
      }

      MemoryManager.GetMemoryManager().StopTransaction(mStartTrans);
    }

    public class PrcLayerFilter : OdPrcContextForPdfExport
    {
      public PrcLayerFilter() : this(new IntPtr(), false)
      {

      }

      public PrcLayerFilter(OdRxObject pObject) : base(OdRxObject.getCPtr(pObject).Handle, false)
      {

      }
      public PrcLayerFilter(IntPtr cPtr, bool cMemoryOwn) : base(cPtr, cMemoryOwn)
      {
      }

      public override bool shouldExportAsPRC(OdGiDrawable pDrawable, OdGiPathNode entity, OdGsClientViewInfo pView, out UInt32 viewportidx)
      {
        viewportidx = 0;

        OdDbEntity pEnt = OdDbEntity.cast(pDrawable);
        if (pEnt == null)
          return false; // to PDF

        if (pEnt.layer() == FRAME_LAYER)
          return false; // to pdf

        return true;
      }

      public static void InitRx(OdRxObject instance)
      {
        OdPrcContextForPdfExport.desc().addX(OdPrcContextForPdfExport.desc(), instance);
      }

      public static void UninitRx()
      {
        OdPrcContextForPdfExport.desc().delX(PrcLayerFilter.desc());
      }
    };

    private static String FRAME_LAYER = "Frame";

    private static void fillPdfExportParams(PDFExportParams _params, OdDbDatabase pDb, String pdfPath)
    {
      _params.setDatabase(pDb);
      _params.setVersion(PDFExportParams.PDFExportVersions.kPDFv1_6);
      _params.setOutput(Globals.odrxSystemServices().createFile(pdfPath, FileAccessMode.kFileWrite,
          FileShareMode.kShareDenyNo, FileCreationDisposition.kCreateAlways));

      _params.setExportFlags(PDFExportParams.PDFExportFlags.kDefault);

      _params.setTitle("Batch PDF File");
      _params.setAuthor("OdPdfExportWithPrcSwigMgd");
      _params.setCreator("Open Design Alliance");
      _params.setPRCMode(PDFExportParams.PRCSupport.kAsBrep);

      OdPrcContextForPdfExport pContext = new PrcLayerFilter(Helpers.odCreatePrcDefaultContextForTD());
      PrcLayerFilter.InitRx(pContext);
      _params.setPRCContext(pContext);

      /****************************************************************/
      /* Initialize the conversion parameters: Layouts                */
      /****************************************************************/

      _params.layouts().Add("Model");
      _params.pageParams().resize(1);
    }

    private static OdDbDatabase fillDatabase(OdDbHostAppServices svcs)
    {
      OdDbDatabase pDb = svcs.createDatabase();

      fillDatabaseWithSeveralEntities(pDb);
      addFrame(pDb);

      return pDb;
    }

    private static OdDbObjectId addLayer(OdDbDatabase pDb, String name)
    {
      /**********************************************************************/
      /* Open the layer table                                               */
      /**********************************************************************/
      OdDbLayerTable pLayers = pDb.getLayerTableId().safeOpenObject(OpenMode.kForWrite) as OdDbLayerTable;

      /**********************************************************************/
      /* Create a layer table record                                        */
      /**********************************************************************/
      OdDbLayerTableRecord pLayer = OdDbLayerTableRecord.createObject();

      /**********************************************************************/
      /* Layer must have a name before adding it to the table.              */
      /**********************************************************************/
      pLayer.setName(name);

      /**********************************************************************/
      /* Add the record to the table.                                       */
      /**********************************************************************/
      return pLayers.add(pLayer);
    }

    private static void fillpoly(OdDbPolyline pPoly, double x, double y, double x2, double y2)
    {
      pPoly.addVertexAt(0, new OdGePoint2d(x, y));
      pPoly.addVertexAt(0, new OdGePoint2d(x, y2));
      pPoly.addVertexAt(0, new OdGePoint2d(x2, y2));
      pPoly.addVertexAt(0, new OdGePoint2d(x2, y));
      pPoly.addVertexAt(0, new OdGePoint2d(x, y));
    }

    private static void addFrame(OdDbDatabase pDb)
    {
      OdDbBlockTableRecord pRecord = pDb.getModelSpaceId().safeOpenObject(OpenMode.kForWrite) as OdDbBlockTableRecord;
      OdDbObjectId layer = addLayer(pDb, FRAME_LAYER);

      OdDbPolyline pPoly = OdDbPolyline.createObject();
      fillpoly(pPoly, -2, -2, 3, 3);
      pPoly.setLayer(layer);
      pRecord.appendOdDbEntity(pPoly);

      pPoly = OdDbPolyline.createObject();
      fillpoly(pPoly, -3, -3, 4, 4);
      pPoly.setLayer(layer);
      pRecord.appendOdDbEntity(pPoly);

      pPoly = OdDbPolyline.createObject();
      fillpoly(pPoly, -2.5, -2.5, 3.5, 3.5);
      pPoly.setLayer(layer);
      pRecord.appendOdDbEntity(pPoly);

      pPoly = OdDbPolyline.createObject();
      fillpoly(pPoly, -1.9, -1.9, 2.9, 2.9);
      pPoly.setColorIndex(5);
      pRecord.appendOdDbEntity(pPoly);
    }

    private static void fillDatabaseWithSeveralEntities(OdDbDatabase pDb)
    {
      // box
      OdDb3dSolid pSolid;
      pSolid = OdDb3dSolid.createObject();
      pSolid.setDatabaseDefaults(pDb);
      pSolid.createBox(1.0, 1.0, 1.0);

      OdCmColor red = new OdCmColor();
      red.setRGB(255, 0, 0);
      pSolid.setColor(red);

      OdDbBlockTableRecord pRecord = pDb.getModelSpaceId().safeOpenObject(OpenMode.kForWrite) as OdDbBlockTableRecord;
      pRecord.appendOdDbEntity(pSolid);

      // cylinder
      pSolid = OdDb3dSolid.createObject();
      pSolid.setDatabaseDefaults(pDb);
      pSolid.createFrustum(2.0, 0.5, 0.5, 0.5);

      OdCmColor green = new OdCmColor();
      green.setRGB(0, 255, 0);
      pSolid.setColor(green);

      OdGeMatrix3d mx = new OdGeMatrix3d();
      mx.setToTranslation(new OdGeVector3d(2.0, 0.0, 0.0));
      pSolid.transformBy(mx);

      pRecord.appendOdDbEntity(pSolid);

      // cone
      pSolid = OdDb3dSolid.createObject();
      pSolid.setDatabaseDefaults(pDb);
      pSolid.createFrustum(2.0, 0.5, 0.5, 0);

      OdCmColor blue = new OdCmColor();
      blue.setRGB(0, 0, 255);
      pSolid.setColor(blue);

      mx.setToTranslation(new OdGeVector3d(0.0, 2.0, 0.0));
      pSolid.transformBy(mx);

      pRecord.appendOdDbEntity(pSolid);

      // torus
      pSolid = OdDb3dSolid.createObject();
      pSolid.setDatabaseDefaults(pDb);
      pSolid.createTorus(1.0, 0.2);

      OdCmColor magenta = new OdCmColor();
      magenta.setRGB(255, 0, 255);
      pSolid.setColor(magenta);

      mx.setToRotation(45, OdGeVector3d.kXAxis);
      pSolid.transformBy(mx);
      mx.setToRotation(45, OdGeVector3d.kYAxis);
      pSolid.transformBy(mx);

      pRecord.appendOdDbEntity(pSolid);
    }
    #endregion
  }
}

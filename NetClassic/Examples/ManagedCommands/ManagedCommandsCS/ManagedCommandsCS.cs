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

using Teigha;
using Teigha.Runtime; // for CommandMethod and CommandFlags
using Teigha.DatabaseServices;
using Teigha.Geometry;
using Teigha.UserIO;
using Teigha.GraphicsInterface;

namespace ManagedCommands
{

  public class ManagedCommandsCS
  {
    // variables to save between commands
    static Entity drawable;

    ~ManagedCommandsCS()
    {
      if (drawable != null)
      {
        drawable.Dispose();
        drawable = null;
      }
    }

    // -------------------------------------------------------- Commands --------------------------------------------------------

    /* Add DBText to current drawing. */
    [CommandMethod("Managed commands C#", "AddSomeText", CommandFlags.Modal)]
    public static void AddDbText()
    {
      try
      {
        Database db = HostApplicationServices.WorkingDatabase;
        using (Transaction tr = db.TransactionManager.StartTransaction())
        {
          DBText text = new DBText();
          text.TextString = "Created using ODA .NET for .dwg files";
          text.Height = 0.2;
          text.Position = new Point3d(0, 0, 0);
          using (BlockTable bt = (BlockTable)tr.GetObject(db.BlockTableId, OpenMode.ForRead))
          {
            using (BlockTableRecord ms = (BlockTableRecord)bt[BlockTableRecord.ModelSpace].GetObject(OpenMode.ForWrite))
            {
              ms.AppendEntity(text);
              tr.AddNewlyCreatedDBObject(text, true);
            }
          }
          tr.Commit();
        }
        db = null;
      }
      finally
      {
      }
    }

    /* Check if file has geoData; if has, try to pick geoPt from it. */
    [CommandMethod("Managed commands C#", "SampleCommandGeoData", CommandFlags.Modal)]
    public static void GeoData()
    {
      Teigha.Runtime.Module res = Teigha.Runtime.SystemObjects.DynamicLinker.LoadModule("OdGeoData", false, false);

      Database db = HostApplicationServices.WorkingDatabase;
      Editor ed = Editor.Current;
      GeoLocationData geoData = new GeoLocationData();

      ObjectId msId = SymbolUtilityServices.GetBlockModelSpaceId(db);
      ObjectId gdid = new ObjectId();
      Boolean hasGeoData = false;
      try
      {
        gdid = db.GeoDataObject;
        hasGeoData = true;
      }
      catch (Teigha.Runtime.Exception ex)
      {
        ed.WriteMessage("\nException thrown " + ex.Message);
      }

      if (hasGeoData)
      {
        using (Transaction tr = db.TransactionManager.StartTransaction())
        {
          geoData = tr.GetObject(gdid, OpenMode.ForWrite) as GeoLocationData;
          PromptPointResult ptRes;
          PromptPointOptions pPtOps = new PromptPointOptions("");
          //pPtOps.AllowNone = true;
          pPtOps.Message = "Select a point";
          ptRes = Editor.Current.GetPoint(pPtOps);
          if (ptRes.Status == PromptStatus.Cancel || ptRes.Status == PromptStatus.None)
            return;
          Point3d wcsPt = ptRes.Value;
          Point3d geoPt = geoData.TransformToLonLatAlt(wcsPt);
          if (geoPt.X == 0.0)
            ed.WriteMessage("\nError: geoPt should not be 0.0");
          else
            ed.WriteMessage("\ngeoPt=" + geoPt);
          tr.Commit();
        }
      }
      else
        ed.WriteMessage("\nDrawing does not have GeoLocationData");
    }

    /* Create transient object over selected object. */
    [CommandMethod("Managed commands C#", "SampleCommandTransient_1_Start", CommandFlags.Modal)]
    public static void TransientStart()
    {
      Database db = HostApplicationServices.WorkingDatabase;
      Editor ed = Editor.Current;

      ed.WriteMessage("Choose an object; there will be drawn transient green shape above it.");
      PromptSelectionResult selection = ed.GetSelection();
      if (selection.Status != PromptStatus.OK)
      {
        ed.WriteMessage("Have not selected properly, canceling.");
        return;
      }

      using (TransientManager manager = TransientManager.CurrentTransientManager)
      {
        using (Transaction tr = db.TransactionManager.StartTransaction())
        {
          ObjectId objIdSelected = selection.Value[0].ObjectId;
          using (DBObject objSelected = tr.GetObject(objIdSelected, OpenMode.ForWrite))
          {
            drawable = objSelected.Clone() as Entity;
            drawable.ColorIndex = 3; // green
            manager.AddTransient(drawable, TransientDrawingMode.DirectShortTerm, 128, new IntegerCollection());
            manager.UpdateTransient(drawable, new IntegerCollection());
          }
          tr.Commit();
        }
      }
    }

    /* Clear previously created transient object. */
    [CommandMethod("Managed commands C#", "SampleCommandTransient_2_Finish", CommandFlags.Modal)]
    public static void TransientFinish()
    {
      Database db = HostApplicationServices.WorkingDatabase;
      Editor ed = Editor.Current;

      using (TransientManager manager = TransientManager.CurrentTransientManager)
      {
        manager.EraseTransient(drawable, new IntegerCollection());
        manager.EraseTransients(TransientDrawingMode.DirectShortTerm, 128, new IntegerCollection());
      }
    }

    /* Find all block references, check if they have clipping, log clipping data. */
    [CommandMethod("Managed commands C#", "SampleCommandClipBoundary", CommandFlags.Modal)]
    public static void TestCommandClipBoundary()
    {
      // open file, open block table record, iterate over all entities
      Database database = HostApplicationServices.WorkingDatabase;
      TransactionManager tm = database.TransactionManager;
      using (Transaction tr = tm.StartTransaction())
      {
        using (BlockTableRecord btr = (BlockTableRecord)tm.GetObject(database.CurrentSpaceId, OpenMode.ForWrite))
        {
          foreach (ObjectId objId in btr)
          {
            BlockReference blR = tr.GetObject(objId, OpenMode.ForWrite) as BlockReference;
            if (blR == null)
              continue;

            // when found block reference, check if it has extension dictionary
            ObjectId extDictId = blR.ExtensionDictionary;
            if (extDictId.IsNull)
              continue;

            using (DBDictionary extDict = (DBDictionary)tr.GetObject(extDictId, OpenMode.ForRead))
            {
              if (!extDict.Contains("ACAD_FILTER")) // extension dictionary should have another dictionary ACAD_FILTER
                continue;

              using (DBDictionary filterDict = (DBDictionary)tr.GetObject(extDict.GetAt("ACAD_FILTER"), OpenMode.ForRead) as DBDictionary)
              {
                if (!filterDict.Contains("SPATIAL")) // filter dictionary should have spatial filter object
                  continue;

                // the block has been clipped if we found SpatialFilter
                Editor.Current.WriteMessage("Found clipping on block reference:");
                using (Teigha.DatabaseServices.Filters.SpatialFilter spaFilter =
                  (Teigha.DatabaseServices.Filters.SpatialFilter)tr.GetObject(filterDict.GetAt("SPATIAL"), OpenMode.ForWrite)
                  as Teigha.DatabaseServices.Filters.SpatialFilter)
                {
                  Teigha.DatabaseServices.Filters.SpatialFilterDefinition spaFilterDef = spaFilter.Definition;
                  using (Point2dCollection polylineData = spaFilterDef.GetPoints()) // should contain clipping boundary
                  {
                    foreach (Point2d point in polylineData)
                    {
                      Editor.Current.WriteMessage(point.ToString());
                    }
                  }
                }
              }
            }
          }
        }
        tr.Commit();
      }
    }

    /* Check some properties of a layer. */
    [CommandMethod("Managed commands C#", "SampleCommandLayerProperties", CommandFlags.Modal)]
    public static void LayerProperties()
    {
      Database db = HostApplicationServices.WorkingDatabase;
      TransactionManager tm = db.TransactionManager;
      using (Transaction tr = tm.StartTransaction())
      {
        bool isLayerWithDesiredProperties = false;

        using (LayerTable layerTable = (LayerTable)tr.GetObject(db.LayerTableId, OpenMode.ForRead, false))
        {
          if (layerTable.Has("Roads-Existing"))
          {
            using (LayerTableRecord layer = (LayerTableRecord)tr.GetObject(layerTable["Roads-Existing"], OpenMode.ForRead))
            {
              using (LinetypeTableRecord linetypeTR = (LinetypeTableRecord)tr.GetObject(layer.LinetypeObjectId, OpenMode.ForRead))
              {
                if (linetypeTR.Name == "Continuous")
                {
                  Teigha.Colors.Color layerColor = layer.Color;
                  if (layerColor.ColorValue == Teigha.Colors.Color.FromColor(System.Drawing.Color.White).ColorValue)
                  {
                    isLayerWithDesiredProperties = true;
                  }
                }
              }
            }
          }
        }

        Editor.Current.WriteMessage("Found layer with desired properties: " + isLayerWithDesiredProperties);

        tr.Commit();
      }
    }

    /* Draw a star at a given coordinates point */
    [CommandMethod("Managed commands C#", "DrawStar", CommandFlags.Modal)]
    public static void DrawStar()
    {
      PromptPointResult pointPrompt = Editor.Current.GetPoint(new PromptPointOptions("Pick middle point of star:"));
      if (pointPrompt.Status != PromptStatus.OK)
      {
        return;
      }
      Point3d middlePoint = pointPrompt.Value;
      int sizeOfStar = 3;

      Database db = HostApplicationServices.WorkingDatabase;
      TransactionManager tm = db.TransactionManager;
      using (Transaction tr = tm.StartTransaction())
      {
        // star has 5 corners; angle between them is 72 deg (1,25664 rad)
        Point3d[] m_pts = new Point3d[] {
          // 1
          new Point3d(
            middlePoint.X - Math.Abs(Math.Cos(Math.PI/2 + 1.25664 * 2) * sizeOfStar),
            middlePoint.Y - Math.Abs(Math.Sin(Math.PI/2 + 1.25664 * 2) * sizeOfStar),
            middlePoint.Z),
          // 2
          new Point3d(middlePoint.X, middlePoint.Y + sizeOfStar, middlePoint.Z),
          // 3
          new Point3d(
            middlePoint.X + Math.Abs(Math.Cos(Math.PI/2 - 1.25664 * 2) * sizeOfStar),
            middlePoint.Y - Math.Abs(Math.Sin(Math.PI/2 - 1.25664 * 2) * sizeOfStar),
            middlePoint.Z),
          // 4
          new Point3d(
            middlePoint.X - Math.Abs(Math.Cos(Math.PI/2 + 1.25664) * sizeOfStar),
            middlePoint.Y + Math.Abs(Math.Sin(Math.PI/2 + 1.25664) * sizeOfStar),
            middlePoint.Z),
          // 5
          new Point3d(middlePoint.X + Math.Abs(Math.Cos(Math.PI/2 - 1.25664) * sizeOfStar),
            middlePoint.Y + Math.Abs(Math.Sin(Math.PI/2 - 1.25664) * sizeOfStar),
            middlePoint.Z),
          // 1
          new Point3d(
            middlePoint.X - Math.Abs(Math.Cos(Math.PI/2 + 1.25664 * 2) * sizeOfStar),
            middlePoint.Y - Math.Abs(Math.Sin(Math.PI/2 + 1.25664 * 2) * sizeOfStar),
            middlePoint.Z),
        };
        Line line1 = new Line(m_pts[0], m_pts[1]);
        line1.Color = Teigha.Colors.Color.FromRgb(255, 0, 0);
        Line line2 = new Line(m_pts[1], m_pts[2]);
        line2.Color = Teigha.Colors.Color.FromRgb(255, 0, 0);
        Line line3 = new Line(m_pts[2], m_pts[3]);
        line3.Color = Teigha.Colors.Color.FromRgb(255, 0, 0);
        Line line4 = new Line(m_pts[3], m_pts[4]);
        line4.Color = Teigha.Colors.Color.FromRgb(255, 0, 0);
        Line line5 = new Line(m_pts[4], m_pts[0]);
        line5.Color = Teigha.Colors.Color.FromRgb(255, 0, 0);
        using (BlockTable bt = (BlockTable)tr.GetObject(db.BlockTableId, OpenMode.ForWrite, false))
        {
          using (BlockTableRecord btr = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite, false))
          {
            btr.AppendEntity(line1);
            btr.AppendEntity(line2);
            btr.AppendEntity(line3);
            btr.AppendEntity(line4);
            btr.AppendEntity(line5);
            tr.AddNewlyCreatedDBObject(line1, true);
            tr.AddNewlyCreatedDBObject(line2, true);
            tr.AddNewlyCreatedDBObject(line3, true);
            tr.AddNewlyCreatedDBObject(line4, true);
            tr.AddNewlyCreatedDBObject(line5, true);
          }
        }
        tr.Commit();
      }
    }
  } // ManagedCommandsCS

  public class Create3dSolidsClass // there can be more than one class with command methods inside one dll module
  {
    static ObjectId addLayer(Database db, String name)
    {
      TransactionManager tm = db.TransactionManager;
      using (LayerTable layerTable = (LayerTable)tm.GetObject(db.LayerTableId, OpenMode.ForWrite, false))
      {
        using (LayerTableRecord newXRec = new LayerTableRecord())
        {
          newXRec.Name = name;
          return layerTable.Add(newXRec);
        }
      }
    }

    [CommandMethod("Managed commands C#", "Create3dSolids", CommandFlags.Modal)]
    public static void Create3dSolidsSampleCommand()
    {
      Database db = HostApplicationServices.WorkingDatabase;

      TransactionManager tm = db.TransactionManager;
      using (Transaction ta = tm.StartTransaction())
      {
        using (BlockTableRecord btr = (BlockTableRecord)db.CurrentSpaceId.GetObject(OpenMode.ForWrite))
        {
          Solid3d solSphere = new Solid3d();
          solSphere.CreateSphere(5);
          btr.AppendEntity(solSphere);
          tm.AddNewlyCreatedDBObject(solSphere, true);
          solSphere.TransformBy(Matrix3d.Displacement(new Vector3d(30, 0, 0)));

          Solid3d solBox = new Solid3d();
          solBox.CreateBox(3, 4, 5);
          btr.AppendEntity(solBox);
          tm.AddNewlyCreatedDBObject(solBox, true);
          solBox.SetLayerId(addLayer(db, "Layer Box"), true);
          solBox.TransformBy(Matrix3d.Displacement(new Vector3d(20, 0, 0)));

          Solid3d solTorus = new Solid3d();
          solTorus.CreateTorus(7, 5);
          btr.AppendEntity(solTorus);
          tm.AddNewlyCreatedDBObject(solTorus, true);
          solTorus.ColorIndex = 5;
          solTorus.SetLayerId(addLayer(db, "Layer Torus"), false);
          solTorus.TransformBy(Matrix3d.Displacement(new Vector3d(10, 0, 0)));

          Solid3d solCone = new Solid3d();
          solCone.CreateFrustum(5, 2, 4, 1);
          btr.AppendEntity(solCone);
          tm.AddNewlyCreatedDBObject(solCone, true);
          solCone.ColorIndex = 7;
          solCone.SetLayerId(addLayer(db, "Layer Cone"), false);
        }
        ta.Commit();
      }
      db = null;
    }
  }

}

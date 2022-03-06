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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Teigha.Runtime;
using Teigha.DatabaseServices;
using Teigha.Geometry;
using Teigha.Aec.Arch.DatabaseServices;

namespace OdArchExMgd
{

  public partial class MainForm : Form
  {
    // --------------------------------------- form fields ----------------------------------------

    Services appServices; // necessary for ODA product activation
    Database db; // current database

    // ------------------------- initialization and deinitialization ------------------------------

    public MainForm()
    {
      InitializeCustomComponent();
      InitializeComponent();
    }

    public void InitializeCustomComponent()
    {
      ActivateAndInitializeODA();

      SystemObjects.DynamicLinker.LoadApp("TD_Gs", false, false);

      if (!Services.Current.LoadArchitecture())
      {
        MessageBox.Show("Could not load architecture modules.", "OdArchExMgd", MessageBoxButtons.OK);
        this.Close();
      }


    }

    void ActivateAndInitializeODA()
    {
      Services.odActivate(ActivationData.userInfo, ActivationData.userSignature);
      appServices = new Services();
    }

    private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
    {
      appServices.Dispose();
    }

    // -------------------------------- buttons processing ------------------------------------

    private void drawAllButton_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.RestoreDirectory = true;
      saveFileDialog.FileName = "OdArchExMgd.dwg";

      if (saveFileDialog.ShowDialog() == DialogResult.OK)
      {
        Database db = CreateAndInitializeDatabaseWithDefaultContent();
        DrawHouse(db);
        db.SaveAs(saveFileDialog.FileName, DwgVersion.Current);
      }
    }

    // ---------------------------------- helping functions ---------------------------------------

    Database CreateAndInitializeDatabaseWithDefaultContent()
    {
      Database db = new Database();
      Teigha.Aec.InitAECApp.InitDisplaySystem(db);
      return db;
    }

    void DrawHouse(Database db)
    {
      using (Transaction tr = db.TransactionManager.StartTransaction())
      {
        ObjectId wsId = AddWallStyle(db, tr);

        ObjectId wallId1 = AddWallAndTransform(db, wsId, new Point3d(0, 0, 0), new Point3d(0, 110, 0), tr);
        ObjectId wallId2 = AddWallAndTransform(db, wsId, new Point3d(0, 110, 0), new Point3d(110, 110, 0), tr);
        ObjectId wallId3 = AddWallAndTransform(db, wsId, new Point3d(110, 110, 0), new Point3d(110, 0, 0), tr);
        ObjectId wallId4 = AddWallAndTransform(db, wsId, new Point3d(110, 0, 0), new Point3d(0, 0, 0), tr);

        ObjectId windowId01 = AddWindow(db, wallId1, 10, 10, tr);
        ObjectId windowId02 = AddWindow(db, wallId1, 60, 10, tr);
        ObjectId windowId03 = AddWindow(db, wallId1, 10, 60, tr);
        ObjectId windowId04 = AddWindow(db, wallId1, 60, 60, tr);

        ObjectId windowId05 = AddWindow(db, wallId2, 10, 10, tr);
        ObjectId windowId06 = AddWindow(db, wallId2, 60, 10, tr);
        ObjectId windowId07 = AddWindow(db, wallId2, 10, 60, tr);
        ObjectId windowId08 = AddWindow(db, wallId2, 60, 60, tr);

        ObjectId windowId09 = AddWindow(db, wallId3, 10, 10, tr);
        ObjectId windowId10 = AddWindow(db, wallId3, 60, 10, tr);
        ObjectId windowId11 = AddWindow(db, wallId3, 10, 60, tr);
        ObjectId windowId12 = AddWindow(db, wallId3, 60, 60, tr);

        tr.Commit();
      }
    }

    ObjectId AddWallStyle(Database db, Transaction tr)
    {
      // all properties with "used" like SetCleanupRadiusUsed - there is no
      WallStyle wallStyle = new WallStyle();
      wallStyle.Description = "Wall style description";
      wallStyle.DictRecordDescription = "Dialog caption";
      wallStyle.Width = 4;
      // SetBaseHeight - there is no
      // JustificationType is with wall not with wallstyle
      wallStyle.DontCleanup = false;
      wallStyle.CleanupRadius = 4;
      // SetFloorLineOffset - there is no
      // SetRoofLineOffset - there is no

      ObjectId wsId = ObjectId.Null;
      //DictionaryWallStyle wallStyleDictionary = new DictionaryWallStyle(db); // DictionaryWallStyle is not wrapped
      //if (wallStyleDictionary.Has(wallStyleName, tr))
      //{
      //  return wallStyleDictionary.GetAt(wallStyleName);
      //}
      //wallStyleDictionary.AddNewRecord(wallStyleName, wallStyle);
      wsId = wallStyle.ObjectId;
      //tr.AddNewlyCreatedDBObject(wallStyle, true);

      return wsId;
    }

    ObjectId AddWallAndTransform(Database db, ObjectId wsId, Point3d startPoint, Point3d endPoint, Transaction tr)
    {
      Wall wall = new Wall();
      wall.SetDatabaseDefaults(db);

      wall.JustificationType = 0; // AECDefs::ewjLeft
      wall.Set(startPoint, endPoint);
      wall.Description = "A Wall";

      WallCutLine wcl = new WallCutLine(0); // AECWallCutLine::eTop
      wall.RoofLine = wcl;
      //wall.StyleId = wsId; // cant for now

      ObjectId wallId;
      using (BlockTable bt = (BlockTable)tr.GetObject(db.BlockTableId, OpenMode.ForRead))
      {
        using (BlockTableRecord modelSpace = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite))
        {
          wallId = modelSpace.AppendEntity(wall);
        }
      }
      wall.TransformBy(Matrix3d.Identity);
      return wallId;
    }

    ObjectId AddWindow(Database db, ObjectId wallId, double offsetAlongX, double offsetAlongZ, Transaction tr)
    {
      Window window = new Window();
      ObjectId windowId;
      using (BlockTable bt = (BlockTable)tr.GetObject(db.BlockTableId, OpenMode.ForRead))
      {
        using (BlockTableRecord modelSpace = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite))
        {
          windowId = modelSpace.AppendEntity(window);
        }
      }

      window.Rise = 10;
      window.Width = 40;
      window.Height = 40;

      window.OpenPercent = 20;
      // SetMeasureTo - there is no
      window.LeafWidth = 10;

      if (!wallId.IsNull)
      {
        window.AttachWallAnchor(wallId);
        
        // there is no
        //AECDbAnchorEntToCurvePtr pAnchor = pWindow->GetAnchor().openObject(OdDb::kForWrite);
        //pAnchor->GetXParams()->SetOffset(dOffsetAlongX);
        //pAnchor->GetZParams()->SetOffset(dOffsetAlongZ);
      }

      return windowId;
    }
  } // MainForm

}

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
using System.Windows.Forms;
using Teigha.DatabaseServices;
using Teigha.Geometry;
using Teigha.Runtime;
using Teigha.UserIO;

namespace CDevGuideExamplesProject.BooleanPEEx
{
  public class BooleanPEEx
  {

    /// <summary>
    /// This sample demonstrates how to use protocol extension in .net code for completing boolean operation on a region.
    /// Currently boolean operations are still under develop, so to get the BooleanPEAttach functionality, you should uncomment it in the sources of ExCustObjs project.
    /// See instruction in https://jira.opendesign.com/browse/NETCLASSIC-432 for details.
    /// In Drawing\Examples\ExCustObjs\DbCmdDef.h uncomment 121 and 122 lines(BooleanPEAttach and BooleanPEDetach declaration);
    /// In Drawing\Examples\ExCustObjs\ExModelerCmds.cpp change the 783 line form "#if 0" to "#if 1" (uncomment BooleanPEAttach and BooleanPEDetach definitions);
    /// Rebuild ExCustObjs.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public BooleanPEEx(String path)
    {
      DialogResult result = MessageBox.Show(
        "This sample requires recompiled ExCustObjs with uncommented command BooleanPEAttach. Do you want to continue?",
        "Requirement",
        MessageBoxButtons.YesNo,
        MessageBoxIcon.Information,
        MessageBoxDefaultButton.Button1,
        MessageBoxOptions.DefaultDesktopOnly);

      if (result == DialogResult.No)
        return;

      List<Handle> li = new List<Handle>();
      Module m1 = SystemObjects.DynamicLinker.LoadModule("ModelerGeometry", false, false);
      Module m2 = SystemObjects.DynamicLinker.LoadModule("ExCustObjs", false, false); // this module should be recompiled with uncommented BooleanPEAttach command
      using (Database db = new Database())
      {
        HostApplicationServices.WorkingDatabase = db; // editor is using WorkingDatabase to pass it to native commands
        Editor.Current.Command("BooleanPEAttach");

        using (Transaction trans = db.TransactionManager.StartTransaction())
        {
          using (BlockTableRecord btr = trans.GetObject(db.CurrentSpaceId, OpenMode.ForWrite) as BlockTableRecord)
          {
            Circle circle1 = new Circle(new Point3d(0, 0, 0), new Vector3d(0, 0, 1), 5);
            Circle circle2 = new Circle(new Point3d(15, 15, 0), new Vector3d(0, 0, 1), 5);

            DBObjectCollection dbObjectCollection = new DBObjectCollection();
            dbObjectCollection.Add(circle1);
            dbObjectCollection.Add(circle2);

            btr.AppendEntity(circle1);
            trans.AddNewlyCreatedDBObject(circle1, true);
            btr.AppendEntity(circle2);
            trans.AddNewlyCreatedDBObject(circle2, true);

            using (DBObjectCollection regionCollection = Region.CreateFromCurves(dbObjectCollection))
            {
              if (regionCollection.Count > 0)
              {
                using (Region region = regionCollection[0] as Region)
                {
                  for (int i = 0; i < regionCollection.Count; i++)
                  {
                    if (i > 0)
                    {
                      try
                      {
                        region.BooleanOperation(BooleanOperationType.BoolUnite, regionCollection[i] as Region);
                      }
                      catch(Teigha.Runtime.Exception ex)
                      {
                        MessageBox.Show(
                          ex.Message,
                          "Exception thrown",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Information
                        );
                      }
                    }
                  }
                  btr.AppendEntity(region);
                  trans.AddNewlyCreatedDBObject(region, true);
                }
              }
            }
          }
          trans.Commit();
        }
        Editor.Current.Command("BooleanPEDetach");
        db.SaveAs(path + "BooleanPEEx.dwg", DwgVersion.Current);
      }
      SystemObjects.DynamicLinker.UnloadModule("ExCustObjs", false);
      SystemObjects.DynamicLinker.UnloadModule("ModelerGeometry", false);
    }
  }
}

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

using Teigha.Runtime;
using Teigha.DatabaseServices;
using Teigha.Geometry;


namespace CDevGuideExamplesProject
{
  public class BindXrefsEx
  {
    //const String path1a = "c:\\AL-01-20-010.dwg";
    //const String path1aa = "X-01-PITCH.dwg";
    //const String path1aa = "AL-01-20-010.dwg";
    //const String path2a = "c:\\ArcEx2.dwg";
    const String path1a = "master.dwg";
    //const String path2a = "D:\\Sample\\xref\\masterBind.dwg";

    public BindXrefsEx(string path)
    {
      using (Database db = new Database(false, false))
      {
        TransactionManager tm = db.TransactionManager;
        using (Transaction ta = tm.StartTransaction())
        {
          db.ReadDwgFile(path + path1a, FileOpenMode.OpenForReadAndAllShare, false, "", false);
          //db.ReadDwgFile(path + path1aa, FileOpenMode.OpenForReadAndAllShare, false, "", false);

          ObjectIdCollection xrefCollection = new ObjectIdCollection();

          using (BlockTable bt = (BlockTable)db.BlockTableId.GetObject(OpenMode.ForWrite)) //.Open(OpenMode.ForRead))
          {
            foreach (ObjectId id in bt)
            {
              using (BlockTableRecord pBlock = (BlockTableRecord)id.GetObject(OpenMode.ForWrite))
              {
                XrefStatus status = pBlock.XrefStatus;
                if (pBlock.XrefStatus != XrefStatus.NotAnXref)
                {
                  switch (status)
                  {
                    case Teigha.DatabaseServices.XrefStatus.Unresolved:
                      {
                        ObjectIdCollection xrefCollectTmp = new ObjectIdCollection();
                        xrefCollectTmp.Add(id);
                        try
                        {
                          db.ReloadXrefs(xrefCollectTmp);
                          xrefCollection.Add(id);
                        }
                        catch (Teigha.Runtime.Exception ex)
                        {
                          if (ex.Message == "eFileNotFound")
                          {
                            continue;
                          }
                        }
                      }
                      break;
                    case Teigha.DatabaseServices.XrefStatus.Resolved:
                      xrefCollection.Add(id);
                      break;
                    case Teigha.DatabaseServices.XrefStatus.FileNotFound:
                    case Teigha.DatabaseServices.XrefStatus.Unreferenced:
                    case Teigha.DatabaseServices.XrefStatus.Unloaded:
                      try
                      {
                        db.DetachXref(pBlock.Id);
                      }
                      catch (Teigha.Runtime.Exception ex)
                      {
                        if (ex.Message == "eXRefDependent")
                        {
                          continue;
                        }
                      }
                      break;
                    default:
                      break;
                  }
                  //                  db.ReloadXrefs(xrefCollection);
                }
              }
            }
            try
            {
              db.ReloadXrefs(xrefCollection);
              db.BindXrefs(xrefCollection, true);
            }
            catch (Teigha.Runtime.Exception ex)
            {
              System.Console.WriteLine("The block cannot be bound");
              System.Console.WriteLine("{0}", ex.Message);
            }
          }

          ta.Commit();
          //ta.Abort();
        }
        db.SaveAs(path + "masterBind.dwg", DwgVersion.Current);
      }
    }
  }
}
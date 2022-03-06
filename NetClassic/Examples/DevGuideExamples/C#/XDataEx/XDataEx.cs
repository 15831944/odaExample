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

using Teigha.DatabaseServices;

namespace CDevGuideExamplesProject.XDataEx
{
  public class XDataEx
  {

    /// <summary>
    /// The sample does not draw any figure, but changes values in dictionary.
    /// It is possible to attach XData to certain object, or to XRecord and place it in global dictionary.
    /// Here shown second variant.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    public XDataEx(String path)
    {
      using (Database db = new Database(true, true))
      {
        TransactionManager tm = db.TransactionManager;
        using (Transaction tr = tm.StartTransaction())
        {
          using (BlockTableRecord btr = (BlockTableRecord)db.CurrentSpaceId.GetObject(OpenMode.ForWrite))
          {

            // *******************************************
            // Add data as Xrecord into global dictionary
            // *******************************************

            // open general NamedObjectsDictionary, in which we will put our values for all document
            using (DBDictionary namedDict = (DBDictionary)db.NamedObjectsDictionaryId.GetObject(OpenMode.ForWrite))
            {
              // create Xrecord; it is database object with xdata, which we can store in dictionary
              // if need to create more complicated structure without too many objects in main NamedObjecDictionary,
              // add another DBDictionary, and add more xrecords to that dictionary
              // for now our structure is simpler
              using (Xrecord pXRec = new Xrecord())
              {

                // create result buffer and add there typed values
                ResultBuffer resbuf = new ResultBuffer();
                resbuf.Add(new TypedValue((int)DxfCode.ExtendedDataAsciiString, "This is some text."));

                // add the result buffer to the Xrecord
                pXRec.Data = resbuf;

                // add the Xrecord to the global namedObjectsDictionary
                namedDict.SetAt("The record with our values", pXRec);
              }

              // read back and show on console
              Xrecord readBackXrecord = namedDict.GetAt("The record with our values").GetObject(OpenMode.ForRead) as Xrecord;
              ResultBuffer readBackResBuf = readBackXrecord.Data;
              Console.WriteLine("XData:");
              // step through the ResBuf chain
              foreach (TypedValue typVal in readBackResBuf)
              {
                Console.WriteLine(typVal.TypeCode.ToString());
                Console.WriteLine(typVal.Value.ToString());
              }
            }

            // *******************************************
            // Add data as XData appended to circle
            // *******************************************

            // register in our database an app name to be able to write xdata
            using (RegAppTable regappTable = (RegAppTable)db.RegAppTableId.GetObject(OpenMode.ForWrite))
            {
              using (RegAppTableRecord regAppRecord = new RegAppTableRecord())
              {
                regAppRecord.Name = "Here is application name";
                regappTable.Add(regAppRecord);
                tr.AddNewlyCreatedDBObject(regAppRecord, true);
              }
            }

            // add a circle
            ObjectId circleId;
            using (Circle circleWithXData = new Circle(Teigha.Geometry.Point3d.Origin, Teigha.Geometry.Vector3d.ZAxis, 1))
            {
              circleWithXData.SetDatabaseDefaults(db);
              circleId = btr.AppendEntity(circleWithXData);
            }

            // append xdata to circle
            using (DBObject circle = circleId.GetObject(OpenMode.ForWrite))
            {
              using (ResultBuffer rb = new ResultBuffer(
                new TypedValue(1001, "Here is application name"), // for xdata first should be app name, same as we registered
                new TypedValue(1000, "Extended Data for ODA app"),
                new TypedValue(1000, "Write the data here"))
              )
              {
                rb.Add(new TypedValue((int)DxfCode.ExtendedDataAsciiString, "One more value added using another way."));
                circle.XData = rb;
              }
            }

          }
          tr.Commit();
        }
        db.SaveAs(path + "XDataEx.dwg", DwgVersion.Current);
      }
    }
  }
}

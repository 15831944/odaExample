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
using System.Collections;
using System.Collections.Generic;
using Teigha;
using Teigha.DatabaseServices;
using Teigha.Geometry;

namespace OdaMgdApp
{

  public class GripOverruleWithDotsOnMove : GripOverrule
  {

    static public GripOverruleWithDotsOnMove overrule;

    Database currentDb;
    Teigha.GraphicsSystem.View activeView;

    // dictionary that stores all grip points/data from all selected entities;
    // key is unique parameters for entity (like hashcode, or full name of entity type and geometric extents of it),
    // value is array of grippoints/gripdata of this entity
    // objectid is not used because maybe it may be null at this moment
    static Dictionary<string, Point3dCollection> gripsDictionary = new Dictionary<string, Point3dCollection>();
    static Dictionary<string, GripDataCollection> gripsDataDictionary = new Dictionary<string, GripDataCollection>();
    
    static Dictionary<string, Point3dCollection> greenDotsPositionsDict = new Dictionary<string, Point3dCollection>();

    //static Dictionary<string, List<DBPoint>> greenDotsDict = new Dictionary<string, List<DBPoint>>();
     //greenDots = new List<DBPoint>();

    public GripOverruleWithDotsOnMove(Database db, Teigha.GraphicsSystem.View v)
    {
      currentDb = db;
      activeView = v;
    }

    private string GetKey(Entity e)
    {
      return e.GetHashCode().ToString(); // e.GetType().FullName + e.GeometricExtents.ToString();
    }

    // saving grip points from entity is done when we are requesting all grip points;
    // so we do not need to "get" then again when it will be used in future
    private void SaveGripPoints(Entity e, Point3dCollection grips)
    {
      string key = GetKey(e);

      // if this entity had grips before, clear
      if (gripsDictionary.ContainsKey(key))
      {
        Point3dCollection gripPointsForClear = gripsDictionary[key];
        using (gripPointsForClear)
        {
          gripPointsForClear.Clear();
        }
        gripsDictionary.Remove(key);
      }

      // add to dictionary with grippoints
      gripsDictionary.Add(key, grips);
    }

    private void SaveGripData(Entity e, GripDataCollection grips)
    {
      string key = GetKey(e);

      // if this entity had grips before, clear
      if (gripsDataDictionary.ContainsKey(key))
      {
        GripDataCollection gripPointsForClear = gripsDataDictionary[key];

        // in our code this collection is already cleared at this point
        // in acad pure sample - no
        // probably because of grips.Clear() in gripmanager
        // todo think if we need this here or in GripManager
        //using (gripPointsForClear)
        //{
        //  gripPointsForClear.Clear();
        //}

        gripsDataDictionary.Remove(key);
      }

      // add to dictionary with gripdata
      gripsDataDictionary.Add(key, grips);
    }

    private Point3dCollection LoadGripPoints(Entity e)
    {
      Point3dCollection grips = null;
      string key = GetKey(e);
      if (gripsDictionary.ContainsKey(key))
      {
        grips = gripsDictionary[key];
      }
      return grips;
    }

    private GripDataCollection LoadGripData(Entity e)
    {
      GripDataCollection grips = null;
      string key = GetKey(e);
      if (gripsDataDictionary.ContainsKey(key))
      {
        grips = gripsDataDictionary[key];
      }
      return grips;
    }

    public override void GetGripPoints(
      Entity e,
      Point3dCollection grips,
      IntegerCollection snaps,
      IntegerCollection geomIds
    )
    {
      base.GetGripPoints(e, grips, snaps, geomIds);
      SaveGripPoints(e, grips);
    }

    Point3d GetMiddlePointOfEntity(Entity entity)
    {
      Point3d p = entity.GeometricExtents.MinPoint + (entity.GeometricExtents.MaxPoint - entity.GeometricExtents.MinPoint) / 2;
      return p; 
    }

    public override void GetGripPoints(
      Entity entity,
      GripDataCollection grips,
      double curViewUnitSize,
      int gripSize,
      Vector3d curViewDir,
      GetGripPointsFlags bitFlags
    )
    {
      // call to base getGrip may throw not implemented; we will process it in grip manager by using another GetGripPoints method in this case
      base.GetGripPoints(entity, grips, curViewUnitSize, gripSize, curViewDir, bitFlags);

      GripWithDotsData element = new GripWithDotsData(GetMiddlePointOfEntity(entity));
      // here can add any another info about this gripPoint with our custom data
      grips.Add(element);

      string key = GetKey(entity);
      greenDotsPositionsDict[key] = new Point3dCollection();
      greenDotsPositionsDict[key].Add(element.GripPoint);
    }

    public override void MoveGripPointsAt(
      Entity e,
      IntegerCollection indices,
      Vector3d offset
    )
    {
      //Point3dCollection savedGripPoints = LoadGripPoints(e);
      //Point3dCollection savedGripPoints = greenDotsPositionsDict[GetKey(e)];
      //if (savedGripPoints != null)
      //{
      //  // cycle over all points which were moved
      //  foreach (int i in indices)
      //  {
      //    using (DBPoint dot = new DBPoint(savedGripPoints[i]))
      //    {
      //      dot.Color = Teigha.Colors.Color.FromRgb(0, 255, 200);
      //      //activeView.Add(dot);
      //    }
      //  }
      //  // end of cycle
      //}

      base.MoveGripPointsAt(e, indices, offset);
    }

    public override void MoveGripPointsAt(
      Entity entity,
      GripDataCollection gripDataCol,
      Vector3d offset,
      MoveGripPointsFlags bitFlags
    )
    {
      Point3dCollection savedGripPoints = greenDotsPositionsDict[GetKey(entity)];
      Point3d pp = savedGripPoints[savedGripPoints.Count - 1];
      pp = pp + offset;
      savedGripPoints.Add(pp);

      // cycle over all points which were moved
      foreach (Point3d p in savedGripPoints)
      {
        // GripData pointData = savedGripData[i];
        using (DBPoint dot = new DBPoint(p))
        {
          dot.Color = Teigha.Colors.Color.FromRgb(0, 255, 200);
          activeView.Add(dot);
        }
      }

      base.MoveGripPointsAt(entity, gripDataCol, offset, bitFlags);
    }

  } // gripoverrule class

  public class GripWithDotsData : GripData
  {
    //public ObjectId ObjectId { get; set; }
    //public Point3d StartPoint { get; set; }
    //public Point3d EndPoint { get; set; }
    //public Point3d DragPoint { get; set; }
    //public int EndIndex { get; set; }

    //public Vector3d LineVector
    //{
    //  get { return (EndPoint - StartPoint).GetNormal(); }
    //}

    //public Point3d Point
    //{
    //  get { return EndIndex == 0 ? StartPoint : EndPoint; }
    //}

    public GripWithDotsData(Point3d pointOfGrip)
    {
      GripPoint = pointOfGrip;
    }

    protected override void DeleteUnmanagedObject()
    {
      //Console.Beep(400, 400);
      base.DeleteUnmanagedObject();
    }

    //public CoordinateSystem3d GlyphCoordinates(Vector3d viewDirection)
    //{
    //  viewDirection = viewDirection.GetNormal();
    //  Vector3d lineVector = LineVector;
    //  Vector3d xAxis = lineVector.CrossProduct(viewDirection).GetNormal();
    //  return new CoordinateSystem3d(DragPoint, xAxis, lineVector);
    //}

    public override bool ViewportDraw(Teigha.GraphicsInterface.ViewportDraw viewDraw, ObjectId entityId, DrawType type, Point3d? imageGripPoint, int gripSizeInPixels)
    {
      using (Circle circle = new Circle(GripPoint, new Vector3d(0, 0, 1), gripSizeInPixels/10.0))
      {
        viewDraw.Geometry.Draw(circle);
      }

      return true;

      //Vector3d viewDirection = viewDraw.Viewport.ViewDirection;
      //Point2d unit = viewDraw.Viewport.GetNumPixelsInUnitSquare(DragPoint);
      //double scale = gripSizeInPixels / unit.X;
      //double wide = scale;
      //double high = wide * 4.0;
      //CoordinateSystem3d glyphCoords = GlyphCoordinates(viewDirection);
      //Point3dCollection polygon = new Point3dCollection();
      //Point3d glyphOrigin;
      //if (!viewDraw.IsDragging)
      //  glyphOrigin = Point;
      //else
      //  glyphOrigin = glyphCoords.Origin - (glyphCoords.Yaxis * (high / 2.0));
      //polygon.Add(glyphOrigin - (glyphCoords.Xaxis * wide));
      //polygon.Add(glyphOrigin + (glyphCoords.Xaxis * wide));
      //polygon.Add(glyphOrigin + (glyphCoords.Yaxis * high));
      //polygon.Add(polygon[0]);
      //Teigha.GraphicsInterface.FillType fillType = viewDraw.SubEntityTraits.FillType;
      //try
      //{
      //  viewDraw.SubEntityTraits.FillType = Teigha.GraphicsInterface.FillType.FillAlways;
      //  viewDraw.Geometry.Polygon(polygon);
      //  if (type == DrawType.DragImageGrip)
      //  {
      //    using (Circle circle = new Circle(DragPoint, LineVector, 100.0))
      //    {
      //      viewDraw.Geometry.Draw(circle);
      //    }
      //  }
      //}
      //finally
      //{
      //  viewDraw.SubEntityTraits.FillType = fillType;
      //}
      //return true;
    }

  } // end class GripWithDotsData

}

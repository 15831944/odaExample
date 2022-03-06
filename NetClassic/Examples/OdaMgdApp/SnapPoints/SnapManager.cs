/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
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
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

using System;
using Teigha;
using Teigha.DatabaseServices;
using Teigha.GraphicsSystem;
using Teigha.Runtime;
using Teigha.GraphicsInterface;
using Teigha.Geometry;
using Teigha.Colors;

namespace OdaMgdApp
{

  // contains array of 13 boolean, each corresponding to value of ObjectSnapModes enum
  public class SelectedSnapModes
  {
    bool[] modes;

    public SelectedSnapModes(bool defaultValue)
    {
      modes = new bool[13];
      for (int i = 0; i < 13; i++)
      {
        modes[i] = defaultValue;
      }
    }

    public bool isModeSelectedByIndex(int index)
    {
      return modes[index-1];
    }

    public void setModeByIndex(int index, bool value)
    {
      modes[index - 1] = value;
    }
  }

  public class SnapManager_OdaMgdApp
  {
    // settings per application
    public static SelectedSnapModes selectedSnapModes;
    public static double hitRadius;

    // settings per drawing
    DrawingForm form;
    MarkForSnapPoint mark;
    Point3d previouslyChosenPoint;

    public SnapManager_OdaMgdApp(DrawingForm form)
    {
      this.form = form;
      mark = null;
      previouslyChosenPoint = new Point3d(0.0, 0.0, 0.0);
    }

    // Returns not-modified point of entity if cursor is not near a snap point,
    // returns entity snap point instead of cursor point if it is close enough and appropriate type of snap point was activated.
    public Point3d MakePointSnappedIfNeeded(Point3d convertedPointCoordinates, double screenX, double screenY)
    {
      Point3d resultingPoint = convertedPointCoordinates;

      using (Transaction tr = form.Database.TransactionManager.StartTransaction())
      {
        using (View view = form.helperDevice.ActiveView)
        {
          ObjectIdCollection entitiesCollection = PickEntitiesAtCurrentScreenPoint(view, screenX, screenY);

          if (entitiesCollection.Count > 0)
            resultingPoint = ProcessSnapPointsOfEntities(tr, entitiesCollection, convertedPointCoordinates, screenX, screenY, view);
          else
            resultingPoint = convertedPointCoordinates;

          EraseGraphicsAtOldSnapPointIfNeeded(view, screenX, screenY);
        }
        tr.Commit();
      }

      previouslyChosenPoint = resultingPoint;
      return resultingPoint;
    }

    ObjectIdCollection PickEntitiesAtCurrentScreenPoint(View view, double screenX, double screenY)
    {
      ObjectIdCollection entitiesCollection = new ObjectIdCollection();
      view.Select(
        new Point2dCollection(new Point2d[] { new Point2d(screenX - 1.0, screenY - 1.0), new Point2d(screenX + 1.0, screenY + 1.0) }),
        new SR(entitiesCollection, form.Database.CurrentSpaceId),
        Teigha.GraphicsSystem.SelectionMode.Point // todo maybe use Crossing?
      );
      return entitiesCollection;
    }

    // For each entity, get snap points of selected modes;
    // check if each snap point is close enough to cursor, and if close - apply it.
    Point3d ProcessSnapPointsOfEntities(
      Transaction tr,
      ObjectIdCollection entitiesCollection,
      Point3d convertedPointCoordinates,
      double screenX,
      double screenY,
      View view
    )
    {
      Point3d result = convertedPointCoordinates;
      Point3dCollection snapPoints = new Point3dCollection();
      bool foundAPoint = false;

      foreach (ObjectId objId in entitiesCollection)
      {
        using (Entity entity = tr.GetObject(objId, OpenMode.ForRead) as Entity)
        {
          if (entity != null)
          {
            try
            {
              for (int i = 1; i <= 13; i++) // there are 13 snap modes, their values inside enum are from 1 to 13
              {
                if (selectedSnapModes.isModeSelectedByIndex(i)) // get snap points only for activated modes
                  entity.GetObjectSnapPoints(
                    (ObjectSnapModes)i,
                    0,
                    convertedPointCoordinates,
                    new Point3d(),//previouslyChosenPoint, should influence perpendicular mode
                    view.WorldToDeviceMatrix, // todo check matrix type
                    snapPoints,
                    null
                  );

                // if found closest entity point, break at once; if no - continue checking other points
                if (snapPoints.Count > 0 && ComparePickPointWithEntityPoints(view, snapPoints, screenX, screenY, convertedPointCoordinates, out result))
                {
                  if (mark == null)
                  {
                    // draw new mark
                    mark = new MarkForSnapPoint(result, new Point2d(screenX, screenY), view.WorldToDeviceMatrix, (ObjectSnapModes)i);
                    view.Add(mark);
                  }
                  else
                  {
                    // change existing mark
                    mark.position = result;
                    mark.screenPosition = new Point2d(screenX, screenY);
                    mark.worldToDevice = view.WorldToDeviceMatrix;
                    mark.mode = (ObjectSnapModes)i;
                  }
                  view.Device.Update();
                  foundAPoint = true;
                  break;
                }
              }
            }
            catch(Teigha.Runtime.Exception ex) // for some entities getting snap points is not implemented; its fine, just ignore them
            {
              if (ex.ErrorStatus == ErrorStatus.NotImplementedYet || ex.ErrorStatus == ErrorStatus.NotApplicable)
                continue;
              else
                throw;
            }
          }
        }

        if (foundAPoint)
          break; // only first entity found will be displayed and counted
      }

      return result;
    }

    // Check if distance from entity point is less than active radius of snap point;
    // if less, return true, and set resultPoint to one of the entity snap points;
    // if not, return false, and set resultPoint to pickedPoint.
    bool ComparePickPointWithEntityPoints(View view, Point3dCollection entitySnapPoints, double screenX, double screenY, Point3d pickedPoint, out Point3d resultPoint)
    {
      Point2d[] entitySnapPointsConvertedToScreen = new Point2d[entitySnapPoints.Count];
      Point3d temp;
      using (AbstractViewPE pVpPE = new AbstractViewPE(view))
      {
        for (int i = 0; i < entitySnapPoints.Count; i++)
        {
          temp = entitySnapPoints[i].TransformBy(view.WorldToDeviceMatrix);
          entitySnapPointsConvertedToScreen[i] = new Point2d(temp.X, temp.Y);
        }
      }

      for (int i = 0; i < entitySnapPointsConvertedToScreen.Length; i++)
      {
        if ((entitySnapPointsConvertedToScreen[i] - new Point2d(screenX, screenY)).Length <= hitRadius)
        {
          resultPoint = entitySnapPoints[i];
          return true;
        }
      }

      resultPoint = pickedPoint;
      return false;
    }

    void EraseGraphicsAtOldSnapPointIfNeeded(View view, double screenX, double screenY)
    {
      // if point was marked as snap and now should not be marked anymore, delete its drawing
      if ((mark != null) && (mark.screenPosition - new Point2d(screenX, screenY)).Length > hitRadius)
      {
        view.Erase(mark);
        mark.Dispose();
        mark = null;
        view.Device.Update();
      }
    }

    public void ClearDrawables()
    {
      View view = form.helperDevice.ActiveView;
      if (mark != null)
      {
        view.Erase(mark);
        mark.Dispose();
        mark = null;
      }
    }

    public void Uninit()
    {
      ClearDrawables();
    }
  }

}

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

namespace OdaMgdApp
{

  class MarkForSnapPoint : DrawableImp
  {
    public Point3d position;
    public Point2d screenPosition;
    public Matrix3d worldToDevice;
    double sizeOfMark = 5.0;
    public ObjectSnapModes mode;

    public MarkForSnapPoint(Point3d position, Point2d screenPosition, Matrix3d worldToDevice, ObjectSnapModes mode)
    {
      this.position = position;
      this.screenPosition = screenPosition;
      this.worldToDevice = worldToDevice;
      this.mode = mode;
    }

    protected override void SubViewportDraw(ViewportDraw vd)
    {
      using (Teigha.GraphicsInterface.Viewport vp = vd.Viewport)
      {
        Point2d ptDim = vp.GetNumPixelsInUnitSquare(position); // coef of transform for size of drawable mark
        Vector3d v = new Vector3d(sizeOfMark / ptDim.X, 0.0, 0.0);
        v = v.TransformBy(vp.WorldToEyeTransform);
        double sizeOfMarkInScreen = v.Length;

        Point3d convertedPosition = position.TransformBy(vp.WorldToEyeTransform);

        Point3d[] markPoints;
        ViewportGeometry vpg = vd.Geometry;

        switch (mode)
        {
          case ObjectSnapModes.ModeEnd:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeMid:
            {
              // circle
              vd.SubEntityTraits.FillType = FillType.FillNever;
              CircularArc3d arc = new CircularArc3d(convertedPosition, new Vector3d(0, 0, 1), sizeOfMarkInScreen);
              PointOnCurve3d[] pointsOnCurve = arc.GetSamplePoints(20);
              Point3dCollection points3d = new Point3dCollection();
              foreach (PointOnCurve3d p in pointsOnCurve)
              {
                points3d.Add(p.Point);
              }
              vpg.PolygonEye(points3d);
              break;
            }
          case ObjectSnapModes.ModeCenter:
            {
              // circle
              vd.SubEntityTraits.FillType = FillType.FillNever;
              CircularArc3d arc = new CircularArc3d(convertedPosition, new Vector3d(0, 0, 1), sizeOfMarkInScreen);
              PointOnCurve3d[] pointsOnCurve = arc.GetSamplePoints(20);
              Point3dCollection points3d = new Point3dCollection();
              foreach (PointOnCurve3d p in pointsOnCurve)
              {
                points3d.Add(p.Point);
              }
              vpg.PolygonEye(points3d);
              break;
            }
          case ObjectSnapModes.ModeNode:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeQuad:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeIntersection:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeIns:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModePerpendicular:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeTangent:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeNear:
            // star 5 corners
            markPoints = new Point3d[] {
              // 1
              new Point3d(
                convertedPosition.X - Math.Abs(Math.Cos(Math.PI/2 + 1.25664 * 2) * sizeOfMarkInScreen),
                convertedPosition.Y - Math.Abs(Math.Sin(Math.PI/2 + 1.25664 * 2) * sizeOfMarkInScreen),
                convertedPosition.Z),
              // 2
              new Point3d(convertedPosition.X, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              // 3
              new Point3d(
                convertedPosition.X + Math.Abs(Math.Cos(Math.PI/2 - 1.25664 * 2) * sizeOfMarkInScreen),
                convertedPosition.Y - Math.Abs(Math.Sin(Math.PI/2 - 1.25664 * 2) * sizeOfMarkInScreen),
                convertedPosition.Z),
              // 4
              new Point3d(
                convertedPosition.X - Math.Abs(Math.Cos(Math.PI/2 + 1.25664) * sizeOfMarkInScreen),
                convertedPosition.Y + Math.Abs(Math.Sin(Math.PI/2 + 1.25664) * sizeOfMarkInScreen),
                convertedPosition.Z),
              // 5
              new Point3d(convertedPosition.X + Math.Abs(Math.Cos(Math.PI/2 - 1.25664) * sizeOfMarkInScreen),
                convertedPosition.Y + Math.Abs(Math.Sin(Math.PI/2 - 1.25664) * sizeOfMarkInScreen),
                convertedPosition.Z),
              // 1
              new Point3d(
                convertedPosition.X - Math.Abs(Math.Cos(Math.PI/2 + 1.25664 * 2) * sizeOfMarkInScreen),
                convertedPosition.Y - Math.Abs(Math.Sin(Math.PI/2 + 1.25664 * 2) * sizeOfMarkInScreen),
                convertedPosition.Z),
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeApparentIntersection:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeParallel:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          case ObjectSnapModes.ModeStartpoint:
            // square
            markPoints = new Point3d[] {
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y - sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X + sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z),
              new Point3d(convertedPosition.X - sizeOfMarkInScreen, convertedPosition.Y + sizeOfMarkInScreen, convertedPosition.Z)
            };
            vd.SubEntityTraits.FillType = FillType.FillNever;
            vpg.PolygonEye(new Point3dCollection(markPoints));
            break;

          default:
            break;
        }
      }
    }
  }

}

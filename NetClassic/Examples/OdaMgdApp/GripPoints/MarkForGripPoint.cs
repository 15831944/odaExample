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
using System.Text;
using Teigha;
using Teigha.DatabaseServices;
using Teigha.GraphicsSystem;
using Teigha.Runtime;
using Teigha.GraphicsInterface;
using Teigha.Geometry;

namespace OdaMgdApp
{

  public class MarkForGripPoint : DrawableImp
  {
    GripData.DrawType m_status;
    bool m_bInvisible;
    bool m_bShared;
    Point3d m_point;
    GripData m_pData;
    FullSubentityPath m_entPath;
    GripManager_OdaMgdApp m_gripManager;
    
    public MarkForGripPoint()
    {
      m_status = GripData.DrawType.WarmGrip;
      m_bInvisible = false;
      m_bShared = false;
      m_point = Point3d.Origin;
      m_entPath = new FullSubentityPath();
      m_gripManager = null;
      m_pData = null;
    }
        
    public MarkForGripPoint(ObjectId id, GripData pData, Point3d pt, GripManager_OdaMgdApp pOwner)
    {
      m_status = GripData.DrawType.WarmGrip;
      m_bInvisible = false;
      m_bShared = false;
      m_point = pt;
      m_pData = pData;
      ObjectId[] arrId = new ObjectId[1];
      arrId[0] = id;
      m_entPath = new FullSubentityPath(arrId, SubentityId.Null);
      m_gripManager = pOwner;
    }

    public MarkForGripPoint(ObjectId id, Point3d pt, GripManager_OdaMgdApp pOwner)
    {
      m_status = GripData.DrawType.WarmGrip;
      m_bInvisible = false;
      m_bShared = false;
      m_point = pt;
      ObjectId[] arrId = new ObjectId[1];
      arrId[0] = id;
      m_entPath = new FullSubentityPath(arrId, SubentityId.Null);
      m_gripManager = pOwner;
      m_pData = null;
    }

    public MarkForGripPoint(FullSubentityPath entPath, GripData pData, Point3d pt, GripManager_OdaMgdApp pOwner)
    {
      m_status = GripData.DrawType.WarmGrip;
      m_bInvisible = false;
      m_bShared = false;
      m_point = pt;
      m_pData = pData;
      m_entPath = entPath;
      m_gripManager = pOwner;
    }

    public bool HasFullSubentityPath(out FullSubentityPath pPath)
    {
      pPath = m_entPath;
      return m_entPath.SubentId.IndexPtr != (IntPtr)0 && m_entPath.SubentId.Type != SubentityType.Null;
    }

    protected override int SubSetAttributes(DrawableTraits traits)
    {
      int i = AttributesFlags.DrawableIsInvisible.GetHashCode();
      if (Invisible == true)
        return AttributesFlags.DrawableIsInvisible.GetHashCode();

      if (traits is SubEntityTraits)
      {
        SubEntityTraits entTraits = (SubEntityTraits)traits;
        switch (Status)
        {
          case GripData.DrawType.WarmGrip:
            entTraits.TrueColor = m_gripManager.GRIPCOLOR;
            break;
          case GripData.DrawType.HotGrip:
          case GripData.DrawType.DragImageGrip:
            entTraits.TrueColor = m_gripManager.GRIPHOT;
            break;
          case GripData.DrawType.HoverGrip:
            entTraits.TrueColor = m_gripManager.GRIPHOVER;
            break;
        }
      }
      return AttributesFlags.DrawableNone.GetHashCode();
    }

    protected override void SubViewportDraw(ViewportDraw vd)
    {
      Point3d ptComputed = new Point3d();
      Point3d? pDrawAtDrag = null;
      if (ComputeDragPoint(ref ptComputed))
        pDrawAtDrag = ptComputed;

      // if grip point has custom mark, draw custom mark
      if (null != Data)
      {
        Data.CallViewportDraw(vd, entityId, Status, pDrawAtDrag, m_gripManager.GRIPSIZE);
      }
      // otherwise grip point is standard, draw standard mark
      else
      {
        Teigha.GraphicsInterface.Viewport pViewport = vd.Viewport;

        // next part causes situation when grip points during rotation are "flying" above its object (NETCLASSIC-472)
        //if (m_gripManager.Model == null || m_gripManager.Model.RenderType.GetHashCode() < 2/*Teigha.GraphicsSystem.RenderType.kDirect*/)
        //{
        //  // Commented since renderTypes implemented, so no need to translate objects for kDirect renderType
        //  Vector3d vpDirection = pViewport.ViewDirection;
        //  Point3d vpOrigin = pViewport.CameraLocation;
        //  Vector3d vecTmp = ptComputed - vpOrigin;
        //  double ptLength = vecTmp.DotProduct(vpDirection);
        //  ptComputed -= vpDirection * ptLength;
        //}

        Point2d ptDim = pViewport.GetNumPixelsInUnitSquare(m_point);
        Vector3d v = new Vector3d(m_gripManager.GRIPSIZE / ptDim.X, 0.0, 0.0);
        v = v.TransformBy(pViewport.WorldToEyeTransform);
        double dGripSize = v.Length;

        Point3d ptOnScreen = ptComputed.TransformBy(pViewport.WorldToEyeTransform);

        vd.SubEntityTraits.FillType = FillType.FillAlways;
        Point3dCollection ptColl = new Point3dCollection();
        ptColl.Add(new Point3d(ptOnScreen.X - dGripSize, ptOnScreen.Y - dGripSize, ptOnScreen.Z));
        ptColl.Add(new Point3d(ptOnScreen.X + dGripSize, ptOnScreen.Y - dGripSize, ptOnScreen.Z));
        ptColl.Add(new Point3d(ptOnScreen.X + dGripSize, ptOnScreen.Y + dGripSize, ptOnScreen.Z));
        ptColl.Add(new Point3d(ptOnScreen.X - dGripSize, ptOnScreen.Y + dGripSize, ptOnScreen.Z));
        vd.Geometry.PolygonEye(ptColl);
      }
    }

    bool ComputeDragPoint(ref Point3d ptOverride)
    {
      ptOverride = new Point3d(Point.X, Point.Y, Point.Z);
      if (null != Data)
      {
        if (Status == GripData.DrawType.DragImageGrip)
        {
          if (Data.DrawAtDragImageGripPoint)
          {
            ptOverride = ptOverride + (m_gripManager.LastPoint - m_gripManager.BasePoint);
            return true;
          }
        }
      }
      return false;
    }

    public GripData.DrawType Status
    { 
      get { return m_status; }
      set { m_status = value; }
    }

    public bool Invisible
    {
      get { return m_bInvisible; }
      set { m_bInvisible = value; }
    }

    public bool Shared
    {
      get { return m_bShared; }
      set { m_bShared = value; }
    }

    public Point3d Point
    {
      get { return m_point; }
    }

    public GripData Data
    {
      get { return m_pData; }
    }

    public ObjectId entityId
    {
      get
      {
        ObjectId[] idArr = m_entPath.GetObjectIds();
        return idArr[idArr.Length - 1];
      }
    }

    public FullSubentityPath SubentPath
    {
      get { return m_entPath; }
    }
  };

  public class GripMarkCollection : CollectionBase
  {
    //strongly typed accessor
    public MarkForGripPoint this[int index]
    {
      get
      {
        return (MarkForGripPoint)this.List[index];
      }
      set
      {
        this.List[index] = value;
      }
    }

    public void Add(MarkForGripPoint grData)
    {
      this.List.Add(grData);
    }
  }

}

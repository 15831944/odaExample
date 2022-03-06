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

  public class MarkForDragPoint : DrawableImp
  {
    FullSubentityPath subentPath;
    Entity m_pCloneEnt;
    GripManager_OdaMgdApp m_gripManager;

    public MarkForDragPoint()
    {
      m_gripManager = null;
    }

    public void Uninit()
    {
      if (m_pCloneEnt != null)
      {
        m_pCloneEnt.Dispose();
        m_pCloneEnt = null;
      }     
      m_gripManager = null;
    }

    public MarkForDragPoint(ObjectId id, GripManager_OdaMgdApp pOwner)
    {
      ObjectId[] arrId = new ObjectId[1];
      arrId[0] = id;
      subentPath = new FullSubentityPath(arrId, SubentityId.Null);
      m_gripManager = pOwner;
    }

    public MarkForDragPoint(FullSubentityPath entPath, GripManager_OdaMgdApp pOwner)
    {
      subentPath = entPath;
      m_gripManager = pOwner;
    }

    protected override int SubSetAttributes(DrawableTraits traits)
    {
      if (null == m_pCloneEnt)
      {
        return AttributesFlags.DrawableIsInvisible.GetHashCode();
      }
      else
      {
        int iRet = m_pCloneEnt.SetAttributes(traits);
        if (traits is SubEntityTraits)
        {
          SubEntityTraits pEntityTraits = (SubEntityTraits)traits;
          pEntityTraits.FillType = FillType.FillNever;
          return iRet;
        }
      }
      return AttributesFlags.DrawableNone.GetHashCode();
    }

    protected override void SubViewportDraw(ViewportDraw vd)
    {
      if (null != m_pCloneEnt)
      {
        m_pCloneEnt.ViewportDraw(vd);
      }
    }

    protected override bool SubWorldDraw(WorldDraw pWorldDraw)
    {
      if (null != m_pCloneEnt)
      {
        return m_pCloneEnt.WorldDraw(pWorldDraw);
      }
      return true;
    }

    public ObjectId EntityId()
    { 
      ObjectId[] Ids = subentPath.GetObjectIds();
      return Ids[Ids.Length-1];
    }

    public void CloneEntity()
    {
      if (m_pCloneEnt != null)
      {
        m_pCloneEnt.Dispose();
        m_pCloneEnt = null;
      }

      ObjectId entId = EntityId();
      using (Transaction tr = entId.Database.TransactionManager.StartTransaction())
      {
        using (DBObject dbObj = entId.GetObject(OpenMode.ForRead))
        {
          if (dbObj is Entity && null != m_gripManager)
          {
            Entity ent = (Entity)dbObj;
            if (ent.CloneMeForDragging)
            {
              m_pCloneEnt = (Entity)ent.Clone();
            }

            if (null != m_pCloneEnt)
            {
              m_pCloneEnt.DisableUndoRecording(true);
              m_pCloneEnt.SetPropertiesFrom(ent);
            }
          }
        }
        tr.Commit();
      }
    }

    bool LocateActiveGrips(out IntegerCollection aIndices )
    {
      GripMarkCollection grDataCol;
      if (EntPath())
        grDataCol = m_gripManager.GetSubentGripData(m_gripManager.GripDataDict[EntityId()], subentPath).MarksCollection;
      else
        grDataCol = m_gripManager.GripDataDict[EntityId()].MarksCollection;

      bool bExMethod = true;
      aIndices = new IntegerCollection();
      int i = 0;
      foreach (MarkForGripPoint dat in grDataCol)
      {
        if (null == dat.Data)
          bExMethod = false;

        if (GripData.DrawType.DragImageGrip == dat.Status)
          aIndices.Add(i);
        i++;
      }
      return bExMethod;
    }

    bool EntPath()
    {
      return (subentPath.SubentId.IndexPtr != (IntPtr)0 && subentPath.SubentId.Type != SubentityType.Null);
    }

    bool EntPath(out FullSubentityPath pPath)
    {
      pPath = subentPath;
      return EntPath();
    }

    public void CloneEntity(Point3d ptMoveAt)
    {

      // todo think maybe to call getgrippoints instead of dictionary in locateActiveGrips?

      CloneEntity();
      if (null == m_pCloneEnt)
        return;

      IntegerCollection activeGripsIndexes;
      bool bExMethod = LocateActiveGrips(out activeGripsIndexes);
      Vector3d vOffset = ptMoveAt - m_gripManager.BasePoint;

      if (bExMethod)
      {
        using (GripDataCollection cloneDataColl = new GripDataCollection())
        {

          if (EntPath())
          {
            m_pCloneEnt.GetGripPointsAtSubentityPath(
              subentPath,
              cloneDataColl,
              m_gripManager.activeViewUnitSize(),
              m_gripManager.GRIPSIZE,
              m_gripManager.activeViewDirection(),
              GetGripPointsFlags.GripPointsOnly
            );

            IntPtr[] gripDataIntPtrArr = new IntPtr[activeGripsIndexes.Count];
            int index = 0;

            foreach (int i in activeGripsIndexes)
            {
              if (i < cloneDataColl.Count)
              {
                gripDataIntPtrArr[index++] = cloneDataColl[i].AppData;
              }
            }

            FullSubentityPath[] aPaths = new FullSubentityPath[1];
            aPaths[0] = subentPath;
            m_pCloneEnt.MoveGripPointsAtSubentityPaths(aPaths, gripDataIntPtrArr, vOffset, 0);
            m_pCloneEnt.SetSubentityGripStatus(GripStatus.GripsToBeDeleted, subentPath);

          }
          else
          {

            m_pCloneEnt.GetGripPoints(
              cloneDataColl,
              m_gripManager.activeViewUnitSize(),
              m_gripManager.GRIPSIZE,
              m_gripManager.activeViewDirection(),
              GetGripPointsFlags.GripPointsOnly
            );

            GripDataCollection gripDataActivePoints = new GripDataCollection();
            foreach (int i in activeGripsIndexes)
            {
              if (i < cloneDataColl.Count)
              {
                gripDataActivePoints.Add(cloneDataColl[i]);
              }
            }

            m_pCloneEnt.MoveGripPointsAt(gripDataActivePoints, vOffset, MoveGripPointsFlags.Osnapped);
            m_pCloneEnt.SetGripStatus(GripStatus.GripsToBeDeleted);
          }

        }
      }
      else
      {
        m_pCloneEnt.MoveGripPointsAt(activeGripsIndexes, vOffset);
        m_pCloneEnt.SetGripStatus(GripStatus.GripsToBeDeleted);
      }
      if (m_gripManager.Model != null)
      {
        m_gripManager.Model.OnModified(this, null);
      }
      else
        m_gripManager.Device.Invalidate();
    }


    public void MoveEntity(Point3d ptMoveAt)
    {
      // todo think maybe to call getgrippoints instead of dictionary in locateActiveGrips?
      IntegerCollection aIndices;
      bool bExMethod = LocateActiveGrips(out aIndices);
      Vector3d vOffset = ptMoveAt - m_gripManager.BasePoint;

      ObjectId entId = EntityId();
      using (Transaction tr = entId.Database.TransactionManager.StartTransaction())
      {
        using (DBObject dbObj = entId.GetObject(OpenMode.ForWrite))
        {
          if (dbObj is Entity)
          {
            Entity ent = (Entity)dbObj;
            GripMarkCollection grDataCol = EntPath() ? m_gripManager.GetSubentGripData(m_gripManager.GripDataDict[entId], subentPath).MarksCollection :
                                                         m_gripManager.GripDataDict[entId].MarksCollection;

            if (bExMethod)
            {
              if (EntPath())
              {
                IntPtr[] aIds = new IntPtr[aIndices.Count];
                int index = 0;
                foreach (int i in aIndices)
                {
                  if (i < grDataCol.Count)
                  {
                    aIds[index++] = grDataCol[i].Data.AppData;
                  }
                }
                FullSubentityPath[] aPaths = new FullSubentityPath[1];
                aPaths[0] = subentPath;
                ent.MoveGripPointsAtSubentityPaths(aPaths, aIds, vOffset, 0);
              }
              else
              {
                GripDataCollection dataCollection = new GripDataCollection();
                foreach (int i in aIndices)
                {
                  if (i < grDataCol.Count)
                  {
                    dataCollection.Add(grDataCol[i].Data);
                  }
                }
                ent.MoveGripPointsAt(dataCollection, vOffset, MoveGripPointsFlags.Osnapped);
              }
            }
            else
            {
              ent.MoveGripPointsAt(aIndices, vOffset);
            }

          }
        }
        tr.Commit();
      }
    }


    public void notifyDragStarted()
    {
      ObjectId entId = EntityId();
      using (Transaction tr = entId.Database.TransactionManager.StartTransaction())
      {
        using (DBObject dbObj = entId.GetObject(OpenMode.ForRead))
        {
          if (dbObj is Entity)
          {
            Entity ent = (Entity)dbObj;
            ent.SetDragStatus(DragStatus.DragStart);
          }
        }
        tr.Commit();
      }
    }

    public void notifyDragEnded()
    {
      ObjectId entId = EntityId();
      using (Transaction tr = entId.Database.TransactionManager.StartTransaction())
      {
        using (DBObject dbObj = entId.GetObject(OpenMode.ForRead))
        {
          if (dbObj is Entity)
          {
            Entity ent = (Entity)dbObj;
            ent.SetDragStatus(DragStatus.DragEnd);
          }
        }
        tr.Commit();
      }
    }

    public void notifyDragAborted()
    {
      using (DBObject dbObj = EntityId().GetObject(OpenMode.ForRead))
      {
        if (dbObj is Entity)
        {
          Entity ent = (Entity)dbObj;
          ent.SetDragStatus(DragStatus.DragAbort);
        }
      }
    }
  };

  public class DragMarkCollection : CollectionBase
  {
    //strongly typed accessor
    public MarkForDragPoint this[int index]
    {
      get
      {
        return (MarkForDragPoint)this.List[index];
      }
      set
      {
        this.List[index] = value;
      }
    }

    public void Add(MarkForDragPoint grData)
    {
      this.List.Add(grData);
    }
  }

}

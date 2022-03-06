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
using Teigha.Colors;

namespace OdaMgdApp
{

  public class GripManager_OdaMgdApp
  {
    LayoutHelperDevice m_layoutHelperDevice;
    Model m_model;

    int m_GRIPSIZE;
    int m_GRIPOBJLIMIT;
    EntityColor m_GRIPCOLOR;
    EntityColor m_GRIPHOVER;
    EntityColor m_GRIPHOT;
    GripMarkCollection m_hoverGripsColl;
    DragMarkCollection m_aDrags;

    Point3d m_ptBasePoint;
    Point3d m_ptLastPoint;
    Dictionary<ObjectId, GripDataExtended> m_gripDataDict;

    GripMarkCollection aActiveKeys;

    public bool IsLineOverruleActive = false;
    public bool IsImageOverruleActive = false;
    public bool IsUniversalOverruleActive = false;

    public GripManager_OdaMgdApp()
    {
      m_hoverGripsColl = new GripMarkCollection();
      m_ptBasePoint = Point3d.Origin;
      m_ptLastPoint = Point3d.Origin;
      m_gripDataDict = new Dictionary<ObjectId, GripDataExtended>();
      m_aDrags = new DragMarkCollection();
    }

    public void Init(LayoutHelperDevice pDevice, Model gsModule, Database pDb)
    {
      m_layoutHelperDevice = pDevice;
      m_model = gsModule;

      HostApplicationServices pAppSvcs = HostApplicationServices.Current;
      m_GRIPSIZE = pAppSvcs.GRIPSIZE;
      m_GRIPOBJLIMIT = pAppSvcs.GRIPOBJLIMIT;
      m_GRIPCOLOR = new EntityColor(ColorMethod.ByAci, pAppSvcs.GRIPCOLOR);
      m_GRIPHOVER = new EntityColor(ColorMethod.ByAci, pAppSvcs.GRIPHOVER);
      m_GRIPHOT = new EntityColor(ColorMethod.ByAci, pAppSvcs.GRIPHOT);
    }

    public void Uninit()
    {
      m_layoutHelperDevice = null;
      m_model = null;
      m_hoverGripsColl = null;
      m_gripDataDict = null;
      m_aDrags = null;
    }

    public Point3d BasePoint
    {
      get { return m_ptBasePoint; }
    }

    public Point3d LastPoint
    {
      get { return m_ptLastPoint; }
    }

    public int GRIPSIZE
    {
      get { return m_GRIPSIZE; }
    }

    public int GRIPOBJLIMIT
    {
      get { return m_GRIPOBJLIMIT; }
    }

    public EntityColor GRIPCOLOR
    {
      get { return m_GRIPCOLOR; }
    }

    public EntityColor GRIPHOVER
    {
      get { return m_GRIPHOVER; }
    }

    public EntityColor GRIPHOT
    {
      get { return m_GRIPHOT; }
    }

    public Model Model
    {
      get { return m_model; }
    }

    public Device Device
    {
      get { return m_layoutHelperDevice; }
    }

    public Dictionary<ObjectId, GripDataExtended> GripDataDict
    {
      get { return m_gripDataDict; }
    }


    public bool OnMouseMove(int x, int y)
    {
      return StartHover(x, y);
    }

    // start/restart hover operation
    // returns true if any grips were found (and need redrawing), false otherwise
    public bool StartHover(int x, int y)
    {
      bool needUpdate = EndHover();
      GripMarkCollection grMarkCol = new GripMarkCollection();
      LocateGripsAt(x, y, ref grMarkCol, true);

      if (grMarkCol.Count != 0)
      {
        m_hoverGripsColl = grMarkCol;
        foreach (MarkForGripPoint mark in m_hoverGripsColl)
        {
          if (mark.Status == GripData.DrawType.WarmGrip)
          {
            mark.Status = GripData.DrawType.HoverGrip;

            if (m_model != null)
              m_model.OnModified(mark, null);
            else
              m_layoutHelperDevice.Invalidate();
          }
        }
        needUpdate = true;
      }
      return needUpdate;
    }

    // returns true if there were any hover grips, false otherwise
    public bool EndHover()
    {
      if (0 == m_hoverGripsColl.Count)
        return false;

      foreach (MarkForGripPoint gr in m_hoverGripsColl)
      {
        if (GripData.DrawType.HoverGrip == gr.Status)
        {
          gr.Status = GripData.DrawType.WarmGrip;
          if (m_model != null)
            m_model.OnModified(gr, null);
          else
            m_layoutHelperDevice.Invalidate();
        }
      }

      m_hoverGripsColl.Clear();
      return true;
    }

    // checks grip points which are already displayed on the screen and saved in grip data for grip points existence at given x y
    public void LocateGripsAt(int x, int y, ref GripMarkCollection resGripMarkCol, bool bFindGripPoint)
    {
      if (m_gripDataDict.Count == 0)
        return;

      Point3d ptFirst = new Point3d();
      Tolerance tol = new Tolerance(1E-4, 1E-4);
      foreach (KeyValuePair<ObjectId, GripDataExtended> grData in m_gripDataDict)
      {
        LocateGripsInCollection(x, y, ref resGripMarkCol, grData.Value.MarksCollection, ptFirst, tol, bFindGripPoint);
        foreach (GripDataSubentity exgrData in grData.Value.DataSubentCollection)
        {
          LocateGripsInCollection(x, y, ref resGripMarkCol, exgrData.MarksCollection, ptFirst, tol, bFindGripPoint);
        }
      }
    }

    void LocateGripsInCollection(
      int x,
      int y,
      ref GripMarkCollection resGripMarkCol,
      GripMarkCollection marksFromGripDataToCheck,
      Point3d ptFirst,
      Tolerance tol,
      bool bFfindGripPoint
    )
    {
      foreach (MarkForGripPoint mark in marksFromGripDataToCheck)
      {
        if (bFfindGripPoint)
        {
          Point3d ptCurrent = mark.Point;
          if (resGripMarkCol.Count == 0)
          {
            // First grip is obtained by comparing
            // grip point device position with cursor position.
            using (Teigha.GraphicsSystem.View pView = m_layoutHelperDevice.ActiveView)
            {
              Point3d ptDC = ptCurrent.TransformBy(pView.WorldToDeviceMatrix);

              double dDeltaX = Math.Abs(x - ptDC.X);
              double dDeltaY = Math.Abs(y - ptDC.Y);
              bool bOk = (dDeltaX <= m_GRIPSIZE) && (dDeltaY <= m_GRIPSIZE);
              if (bOk)
              {
                ptFirst = ptCurrent;
                resGripMarkCol.Add(mark);
              }
            }
          }
          else
          {
            if (ptCurrent.IsEqualTo(ptFirst, tol))
            {
              resGripMarkCol.Add(mark);
            }
          }
        }
        else
        {
          resGripMarkCol.Add(mark);
        }
      }
    }

    public bool OnMouseDown(int x, int y)
    {
      EndHover();

      GripMarkCollection aKeys = new GripMarkCollection();
      LocateGripsAt(x, y, ref aKeys, true);
      if (aKeys.Count > 0)
      {
        //if ( bShift )  TODO
        {
          bool bMakeHot = true;
          foreach (KeyValuePair<ObjectId, GripDataExtended> grData in m_gripDataDict)
          {
            foreach (MarkForGripPoint exgrData in grData.Value.MarksCollection)
            {
              if (GripData.DrawType.HotGrip == exgrData.Status)
              {
                bMakeHot = false;
                break;
              }
            }

            foreach (GripDataSubentity grDatSub in grData.Value.DataSubentCollection)
            {
              foreach (MarkForGripPoint exgrData in grDatSub.MarksCollection)
              {
                if (GripData.DrawType.HotGrip == exgrData.Status)
                {
                  bMakeHot = false;
                  break;
                }
              }
              if (bMakeHot == false)
                break;
            }

            if (bMakeHot == false)
              break;
          }
          if (bMakeHot)
          {
            foreach (MarkForGripPoint exgrData in aKeys)
            {
              exgrData.Status = GripData.DrawType.HotGrip;
            }
          }

          aActiveKeys = new GripMarkCollection();
          locateGripsByStatus(GripData.DrawType.HotGrip, ref aActiveKeys);
          if (aActiveKeys.Count == 0)
          {
            // Valid situation.
            // If trigger grip performed entity modification and returned eGripHotToWarm
            // then nothing is to be done cause entity modification will cause reactor to regen grips.
            return false;
          }

          foreach (MarkForGripPoint exgrData in aActiveKeys)
          {
            exgrData.Status = GripData.DrawType.DragImageGrip;
          }

          foreach (KeyValuePair<ObjectId, GripDataExtended> grData in m_gripDataDict)
          {
            bool bActive = false;
            foreach (MarkForGripPoint exgrData in grData.Value.MarksCollection)
            {
              if (GripData.DrawType.DragImageGrip == exgrData.Status)
              {
                bActive = true;
                m_aDrags.Add(new MarkForDragPoint(grData.Key, this));
              }
            }
            foreach (GripDataSubentity grDatSub in grData.Value.DataSubentCollection)
            {
              foreach (MarkForGripPoint exgrData in grDatSub.MarksCollection)
              {
                if (GripData.DrawType.DragImageGrip == exgrData.Status)
                {
                  bActive = true;
                  m_aDrags.Add(new MarkForDragPoint(exgrData.SubentPath, this));
                }
              }
              if (bActive == true)
              {
                break;
              }
            }
          }

          using (Teigha.GraphicsSystem.View pView = m_layoutHelperDevice.ActiveView)
          {
            foreach (MarkForDragPoint grDrag in m_aDrags)
            {
              grDrag.notifyDragStarted();
              grDrag.CloneEntity();
              pView.Add(grDrag);
            }
          }

          m_ptBasePoint = aKeys[0].Point;
          m_ptLastPoint = m_ptBasePoint;
        }
      }
      else
      {
        return false;
      }
      return true;
    }

    public GripDataSubentity GetSubentGripData(GripDataExtended ext, FullSubentityPath entPath)
    {
      int i = 0;
      foreach (GripDataSubentity subData in ext.DataSubentCollection)
      {
        if (subData.EntPath == entPath)
          return ext.DataSubentCollection[i];
        ++i;
      }
      return ext.DataSubentCollection[0];
    }

    public void setValue( Point3d ptValue )
    {
      foreach (MarkForDragPoint grDrag in m_aDrags)
      {
        grDrag.CloneEntity(ptValue);
      }
      m_ptLastPoint = ptValue;
    }

    public double activeViewUnitSize()
    {
      Vector3d v;
      using (Teigha.GraphicsSystem.View pView = m_layoutHelperDevice.ActiveView)
      {
        Point2d ptDim; // getNumPixelsInUnitSquare
        {
          Extents2d ext = pView.Viewport;
          ptDim = new Point2d(Math.Abs(((double)ext.MaxPoint.X - ext.MinPoint.X) / pView.FieldWidth),
                              Math.Abs(((double)ext.MaxPoint.Y - ext.MinPoint.Y) / pView.FieldHeight));
        }
        v = new Vector3d(GRIPSIZE / ptDim.X, 0, 0);
        v = v.TransformBy(pView.ViewingMatrix);
      }      
      return v.Length / GRIPSIZE;
    }

    public Vector3d activeViewDirection()
    {
      using (Teigha.GraphicsSystem.View pView = m_layoutHelperDevice.ActiveView)
      {
        Vector3d vec = pView.Position - pView.Target;
        return vec.GetNormal();
      }  
    }

    void removeEntityGrips(Entity ent, ObjectId id,  bool bFireDone)
    {
      GripDataExtended grDataExt;
      if (m_gripDataDict.TryGetValue(id, out grDataExt))
      {
        ent.SetGripStatus(GripStatus.GripsToBeDeleted);
        foreach (MarkForGripPoint gr in grDataExt.MarksCollection)
        {
          hideGrip(gr);
          if (gr.Data != null)
          {
            gr.Data.OnGripStatusChanged(id, GripData.Status.GripEnd);
          }
        }
        grDataExt.MarksCollection = null;
        int sz = grDataExt.DataSubentCollection.Count;
        for (int iSz = 0; iSz < sz; iSz++)
        {
          foreach (MarkForGripPoint grData in grDataExt.DataSubentCollection[iSz].MarksCollection)
          {
            hideGrip(grData);
          }
        }
        m_gripDataDict.Remove(id);
      }
      ent.Unhighlight();

      if (bFireDone)
      {
        ent.SetGripStatus(GripStatus.GripsDone);
      }

      grDataExt = null;
    }

    public void removeEntityGrips( ObjectId id, bool bFireDone )
    {
      using (Transaction tr = id.Database.TransactionManager.StartTransaction())
      {
        using (Entity ent = (Entity)id.GetObject(OpenMode.ForRead, false, true))
        {
          removeEntityGrips(ent, id, bFireDone);
        }
        tr.Commit();
      }
    }

    void updateEntityGrips( ObjectId id )
    {
      using (Transaction tr = id.Database.TransactionManager.StartTransaction())
      {
        try
        {
          using (Entity ent = (Entity)id.GetObject(OpenMode.ForRead))
          {
            try // grip points are implemented not for all entities
            {
              removeEntityGrips(ent, id, false);
              GripMarkCollection exGrDataColl = new GripMarkCollection();
              GripDataCollection grips = new GripDataCollection();
              if (ent.GetGripPoints(grips, activeViewUnitSize(), GRIPSIZE, activeViewDirection(), GetGripPointsFlags.GripPointsOnly))
              {
                foreach (GripData gr in grips)
                {
                  exGrDataColl.Add(new MarkForGripPoint(id, gr, gr.GripPoint, this));
                }
                grips.Clear();
                grips = null;
              }
              else
              {
                Point3dCollection gripsPts = new Point3dCollection();
                ent.GetGripPoints(gripsPts, null, null);
                foreach (Point3d pt in gripsPts)
                {
                  exGrDataColl.Add(new MarkForGripPoint(id, pt, this));
                }
              }

              if (null != exGrDataColl)
              {
                GripDataExtended dExt = new GripDataExtended();
                foreach (MarkForGripPoint grDat in exGrDataColl)
                {
                  FullSubentityPath entPath;
                  if (grDat.HasFullSubentityPath(out entPath))
                  {
                    bool bFound = false;
                    GripDataSubentCollection grSubColl = dExt.DataSubentCollection;
                    for (int j = 0; j < grSubColl.Count; j++)
                    {
                      if (grSubColl[j].EntPath == entPath)
                      {
                        bFound = true;
                        grSubColl[j].MarksCollection.Add(grDat);
                        break;
                      }
                    }
                    if (!bFound)
                    {
                      GripDataSubentity se = new GripDataSubentity();
                      se.EntPath = entPath;
                      se.MarksCollection.Add(grDat);
                      dExt.DataSubentCollection.Add(se);
                    }
                  }
                  else
                  {
                    if (dExt.MarksCollection == null)
                      dExt.MarksCollection = new GripMarkCollection();
                    dExt.MarksCollection.Add(grDat);
                  }
                }

                m_gripDataDict.Add(id, dExt);

                foreach (MarkForGripPoint grData in exGrDataColl)
                {
                  showGrip(grData);
                }
              }
            }
            catch (System.Exception)
            {
              // just skip non-supported entities
            }
            ent.Highlight();
          }
        }
        catch (System.Exception)
        {
          using (Entity ent = (Entity)id.GetObject(OpenMode.ForRead, false, true))//looked entity
          {
            ent.Highlight();
          }
        }
        tr.Commit();
      }
    }

    void showGrip( MarkForGripPoint pGrip)
    {
      int nViews = m_layoutHelperDevice.NumViews;
      for (int i = 0; i < nViews; i++)
        m_layoutHelperDevice.ViewAt( i ).Add(pGrip);
    }

    void hideGrip(MarkForGripPoint pGrip)
    {
      int nViews = m_layoutHelperDevice.NumViews;
      for (int i = 0; i < nViews; i++)
        m_layoutHelperDevice.ViewAt( i ).Erase(pGrip);
    }

    public void UpdateSelection(ObjectIdCollection selected)
    {
      ObjectIdCollection aNew = new ObjectIdCollection();
      foreach (ObjectId id in selected)
      {
        if(!m_gripDataDict.ContainsKey(id))
        {
          updateEntityGrips(id);
        }
      }

      updateInvisibleGrips();
    }

    void locateGripsByStatus( GripData.DrawType eStatus, ref GripMarkCollection aResult )
    {
      foreach (KeyValuePair<ObjectId, GripDataExtended> grData in m_gripDataDict)
      {
        foreach (MarkForGripPoint exgrDat in grData.Value.MarksCollection)
        {
          if (exgrDat.Status == eStatus)
          {
            aResult.Add(exgrDat);
          }
        }

        foreach (GripDataSubentity exgrData in grData.Value.DataSubentCollection)
        {
          foreach (MarkForGripPoint exgrDat in exgrData.MarksCollection)
          {
            if (exgrDat.Status == eStatus)
            {
              aResult.Add(exgrDat);
            }
          }
        }
      }
    }

    public bool MoveAllSelected(int x, int y)
    {
      EndHover();

      GripMarkCollection aKeys = new GripMarkCollection();
      LocateGripsAt(x, y, ref aKeys, false);
      if (aKeys.Count > 0)
      {
        aActiveKeys = new GripMarkCollection();
        locateGripsByStatus(GripData.DrawType.WarmGrip, ref aActiveKeys);
        if (aActiveKeys.Count == 0)
        {
          return false;
        }
        foreach (MarkForGripPoint exgrData in aActiveKeys)
        {
          exgrData.Status = GripData.DrawType.DragImageGrip;
        }


        foreach (KeyValuePair<ObjectId, GripDataExtended> grData in m_gripDataDict)
        {
          bool bActive = false;
          foreach (MarkForGripPoint exgrData in grData.Value.MarksCollection)
          {
            bActive = true;
            m_aDrags.Add(new MarkForDragPoint(grData.Key, this));
          }
          foreach (GripDataSubentity grDatSub in grData.Value.DataSubentCollection)
          {
            foreach (MarkForGripPoint exgrData in grDatSub.MarksCollection)
            {
              bActive = true;
              m_aDrags.Add(new MarkForDragPoint(exgrData.SubentPath, this));
            }
            if (bActive)
              break;
          }
        }

        using (Teigha.GraphicsSystem.View pView = m_layoutHelperDevice.ActiveView)
        {
          foreach (MarkForDragPoint grDrag in m_aDrags)
          {
            grDrag.notifyDragStarted();
            grDrag.CloneEntity();
            pView.Add(grDrag);
          }
        }

        m_ptBasePoint = aKeys[0].Point;
        m_ptLastPoint = m_ptBasePoint;
      }
      else
      {
        return false;
      }
      return true;
    }
    
    void updateInvisibleGrips()
    {
      GripMarkCollection aOverall = new GripMarkCollection();
      foreach (KeyValuePair<ObjectId, GripDataExtended> grDataDc in m_gripDataDict)
      {        
        foreach (MarkForGripPoint grData in grDataDc.Value.MarksCollection)
        {
          aOverall.Add(grData);
        }
        foreach (GripDataSubentity grDataSub in grDataDc.Value.DataSubentCollection)
        {
          foreach (MarkForGripPoint grData in grDataSub.MarksCollection)
          {
            aOverall.Add(grData);
          }
        }
      }

      int iSize = aOverall.Count;
      for (int i = 0; i < iSize; i++)
      {
        MarkForGripPoint grData = aOverall[i];
        grData.Invisible = false;
        grData.Shared = false;

        IntegerCollection aEq = new IntegerCollection();
        aEq.Add( i );

        Point3d ptIni = grData.Point;

        int iNext = i + 1;
        Tolerance tc = new Tolerance(1E-6, 1E-6);
        while (iNext < iSize)
        {
          Point3d ptCur = aOverall[ iNext ].Point;
          if (ptIni.IsEqualTo(ptCur, tc))
          {
            aEq.Add( iNext );
            iNext++;
          }
          else
            break;
        }

        if (aEq.Count >= 2)
        {
          int iVisible = 0;
          int jSize = aEq.Count;
          for (int j = 0; j < jSize; j++)
          {
            MarkForGripPoint pGrip = aOverall[aEq[j]];

            bool bOk = true;
            if (pGrip.Data != null)
            {
              if (pGrip.Data.SkipWhenShared)
                bOk = false;
            }

            if (bOk)
            {
              iVisible = j;
              break;
            }
          }

          for (int j = 0; j < jSize; j++)
          {
            MarkForGripPoint pGrip = aOverall[aEq[j]];
            pGrip.Shared = true;
            pGrip.Invisible = (j != iVisible);
          }
        }
      }
    }



    public void DragFinal(Point3d ptFinal, bool bOk)
    {
      using (Teigha.GraphicsSystem.View pView = m_layoutHelperDevice.ActiveView)
      {
        foreach (MarkForDragPoint grDrag in m_aDrags)
        {
          if (bOk)
          {
            grDrag.MoveEntity(ptFinal);
            grDrag.notifyDragEnded();
          }
          else
            grDrag.notifyDragAborted();
          pView.Erase(grDrag);
          updateEntityGrips(grDrag.EntityId());
          grDrag.Uninit();
        }
      }   

      m_aDrags.Clear();

      if (bOk)
        updateInvisibleGrips();

      if (aActiveKeys != null)
      {
        foreach (MarkForGripPoint exgrData in aActiveKeys)
        {
          exgrData.Status = GripData.DrawType.WarmGrip;
        }
      }
      aActiveKeys = null;
    }

    public void StartOverruling()
    {
    }

    public void StopOverruling()
    {
    }

    public void StartLineOverruling()
    {
      if (!IsLineOverruleActive)
      {
        ObjectOverrule.AddOverrule(RXClass.GetClass(typeof(Teigha.DatabaseServices.Line)), LineOverrule.overrule, true);
        IsLineOverruleActive = true;
        ObjectOverrule.Overruling = IsLineOverruleActive || IsImageOverruleActive || IsUniversalOverruleActive;
      }
    }

    public void StopLineOverruling()
    {
      if (IsLineOverruleActive)
      {
        ObjectOverrule.RemoveOverrule(RXClass.GetClass(typeof(Teigha.DatabaseServices.Line)), LineOverrule.overrule);
        IsLineOverruleActive = false;
        ObjectOverrule.Overruling = IsLineOverruleActive || IsImageOverruleActive || IsUniversalOverruleActive;
      }
    }

    public void StartImageOverruling()
    {
      if (!IsImageOverruleActive)
      {
        ObjectOverrule.AddOverrule(RXClass.GetClass(typeof(Teigha.DatabaseServices.RasterImage)), RasterImageOverrule.overrule, true);
        IsImageOverruleActive = true;
        ObjectOverrule.Overruling = IsLineOverruleActive || IsImageOverruleActive || IsUniversalOverruleActive;
      }
    }

    public void StopImageOverruling()
    {
      if (IsImageOverruleActive)
      {
        ObjectOverrule.RemoveOverrule(RXClass.GetClass(typeof(Teigha.DatabaseServices.RasterImage)), RasterImageOverrule.overrule);
        IsImageOverruleActive = false;
        ObjectOverrule.Overruling = IsLineOverruleActive || IsImageOverruleActive || IsUniversalOverruleActive;
      }
    }

    public void StartUniversalOverruling(Database db)
    {
      if (!IsUniversalOverruleActive)
      {

        if (m_layoutHelperDevice != null)
        {
          GripOverruleWithDotsOnMove.overrule = new GripOverruleWithDotsOnMove(db, m_layoutHelperDevice.ActiveView);
          ObjectOverrule.AddOverrule(RXClass.GetClass(typeof(Entity)), GripOverruleWithDotsOnMove.overrule, true);
        }

        IsUniversalOverruleActive = true;
        ObjectOverrule.Overruling = IsLineOverruleActive || IsImageOverruleActive || IsUniversalOverruleActive;
      }
    }

    public void StopUniversalOverruling()
    {
      if (IsUniversalOverruleActive && GripOverruleWithDotsOnMove.overrule != null)
      {
        ObjectOverrule.RemoveOverrule(RXClass.GetClass(typeof(Entity)), GripOverruleWithDotsOnMove.overrule);
        IsUniversalOverruleActive = false;
        ObjectOverrule.Overruling = IsLineOverruleActive || IsImageOverruleActive || IsUniversalOverruleActive;
      }
    }

  }

}

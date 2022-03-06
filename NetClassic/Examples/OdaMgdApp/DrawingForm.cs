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
using System.IO;

using Teigha;
using Teigha.DatabaseServices;
using Teigha.UserIO;
using Teigha.GraphicsSystem;
using Teigha.Runtime;
using Teigha.GraphicsInterface;
using Teigha.Geometry;
using OdaMgdApp.Jig;
using System.Diagnostics;

namespace OdaMgdApp
{

  /* This form displays a DWG file. */
  public partial class DrawingForm : Form
  {

    // --------------------------------------- form fields ----------------------------------------

    LayoutManager layoutManager = null; // for work with layouts and events
    Graphics graphics = null; // for drawing dwg image; for drawing exception text in case of exception during Paint
    GsModule gsModule = null;
    Device graphicsDevice = null;
    public LayoutHelperDevice helperDevice = null;
    OrbitTracker orbitTracker; // for drawing rotation
    OrbitCtrl orbitControl; // for drawing rotation
    public ObjectIdCollection selected = new ObjectIdCollection();
    public bool selectingBySelector = false; // if there is selection by selector in progress; set and reset by Selector of Editor
    Point2d startSelPoint, endSelPoint;
    RectFram selRect; // for selection
    bool isDollying = false; // if the drawing is currently being moved by dolly
    public UserInputState currentUserInputState = UserInputState.NotActive; // if the program currently expects input from user
    bool selectingForBmpExport = false;
    Teigha.GraphicsSystem.View areaView = null; // view of the area view

    private delegate void CreateLineDelegate(Database db);

    // ------------------------------------ properties --------------------------------------------

    public Panel DrawingPanel
    {
      get { return this.drawingPanel; }
    }

    public Database Database { get; private set; } // database of drawing which is currently displayed

    public GripManager_OdaMgdApp GripManager { get; private set; } // for work with grip points

    public MouseMode MouseMode { get; set; } // current mouse interaction mode

    public ControlButtonState PanelState { get; set; } // state of the buttons on the tools panel

    public SnapManager_OdaMgdApp SnapManager { get; private set; } // for work with snap points

    // ------------------------- initialization and deinitialization ------------------------------

    public DrawingForm(String path, bool partialMode, AuditInfo appAudit)
    {
      InitializeComponent();
      InitializeCustomComponents();
      OpenDrawing(path, partialMode, appAudit);
    }

    void InitializeCustomComponents()
    {
      this.drawingPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.drawingPanel_Paint);
      this.MouseWheel += new MouseEventHandler(drawingForm_MouseWheel);

      GripManager = new GripManager_OdaMgdApp();
      SnapManager = new SnapManager_OdaMgdApp(this);
      MouseMode = MouseMode.Quiescent;
      orbitTracker = new OrbitTracker();
      PanelState = new ControlButtonState();
      PanelState.Wire2dState = true; // this mode is active by default when new drawing is opened
    }

    // ------------------------------- form events processing -------------------------------------

    private void drawingPanel_Paint(object sender, PaintEventArgs e)
    {
      try
      {
        Stopwatch stopWatch = new Stopwatch();
        stopWatch.Start();

        helperDevice.Update();

        stopWatch.Stop();
        TimeSpan ts = stopWatch.Elapsed;
        ((MainForm)this.MdiParent).SetRedrawTimeDisplay(ts.TotalMilliseconds + " ms");
      }
      catch (System.Exception ex)
      {
        graphics.DrawString(ex.ToString(), new Font("Arial", 16), new SolidBrush(Color.Black), new PointF(150.0F, 150.0F));
      }
    }

    // events from mdi parent are passed to mdi child, not to components of it like drawingPanel
    void drawingForm_MouseWheel(object sender, MouseEventArgs e)
    {
      if (helperDevice == null) return;

      using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
      {
        // camera position in world coordinates
        Point3d pos = pView.Position;
        // TransformBy() returns a transformed copy
        pos = pos.TransformBy(pView.WorldToDeviceMatrix);
        int vx = (int)pos.X;
        int vy = (int)pos.Y;
        vx = e.X - vx;
        vy = e.Y - vy;
        // we move point of view to the mouse location, to create an illusion of scrolling in/out there
        dolly(pView, -vx, -vy);
        // note that we essentially ignore delta value (sign is enough for illustrative purposes)
        pView.Zoom(e.Delta > 0 ? 1.0 / 0.9 : 0.9);
        dolly(pView, vx, vy);
        helperDevice.Update();
      }
    }

    private void DrawingForm_KeyDown(object sender, KeyEventArgs e)
    {
      switch (e.KeyCode)
      {
        case Keys.Escape:
          if (currentUserInputState == UserInputState.InProgress)
          {
            currentUserInputState = UserInputState.NotActive;
          }
          if (selectingBySelector)
          {
            ((UserIO.Editor_OdaMgdApp)Editor.Current).SelectionDone(false);
          }
          if (selectingForBmpExport)
          {
            selectingForBmpExport = false;
            updateSelection();
            currentUserInputState = UserInputState.Cancelled;
          }
          disableCommand();
          if (helperDevice != null)
            helperDevice.Invalidate();
          drawingPanel.Invalidate();
          break;
        case Keys.Enter:
          if (selectingBySelector)
          {
            ((UserIO.Editor_OdaMgdApp)Editor.Current).SelectionDone(true);
          }
          break;
        case Keys.Oemplus:
          break;
        case Keys.OemMinus:
          break;
        case Keys.Delete:
          erase();
          break;
      }
    }

    private void DrawingForm_FormClosing(object sender, FormClosingEventArgs e)
    {
      if (PanelState.AreaViewInDrawingState)
        deactivateAreaViewInDrawing();

      if (((MainForm)this.MdiParent).ActiveDrawingForm == this)
        ((MainForm)this.MdiParent).ActiveDrawingFormClosing();

      SnapManager.Uninit();
      SnapManager = null;
      if (ObjectOverrule.Overruling)
        GripManager.StopOverruling();
      EraseSelectionRectangle();
      GripManager.Uninit();
      GripManager = null;
      if (graphics != null)
      {
        graphics.Dispose();
        graphics = null;
      }
      if (helperDevice != null)
      {
        helperDevice.Dispose();
        helperDevice = null;
      }
      if (Database != null)
      {
        Database.Dispose();
        Database = null;
      }
      if (graphicsDevice != null)
      {
        graphicsDevice.Dispose();
        graphicsDevice = null;
      }
      if (gsModule != null)
      {
        gsModule.Dispose();
        gsModule = null;
      } 
    }

    public void DrawingForm_Move(object sender, System.EventArgs e)
    {
      ((MainForm)this.MdiParent).UpdateAreaView();
    }

    public void drawingPanel_MouseMove(object sender, MouseEventArgs e)
    {
      switch (MouseMode)
      {
        case MouseMode.Quiescent:
          {
            if (GripManager != null && GripManager.OnMouseMove(e.X, e.Y))
              helperDevice.Update();
            break;
          }
        case MouseMode.DragDrop:
          {
            if (GripManager != null)
            {
              Point3d currentPoint = toEyeToWorld(e.X, e.Y);
              currentPoint = SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
              GripManager.setValue(currentPoint);
              helperDevice.Update();
            }
            break;
          }
        case MouseMode.ZoomWindow:
        case MouseMode.Selection:
          {
            selRect.setValue(toEyeToWorld(e.X, e.Y));
            helperDevice.Update();
            break;
          }
        case MouseMode.Orbit:
          {
            orbitTracker.setValue(toEyeToWorld(e.X, e.Y));
            helperDevice.Update();
            break;
          }
        case MouseMode.Dolly:
          {
            if (isDollying)
            {
              using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
              {
                dolly(pView, (int)(e.X - startSelPoint.X), (int)(e.Y - startSelPoint.Y));
                startSelPoint = new Point2d(e.X, e.Y);
                helperDevice.Update();
              }
            }
            break;
          }
        default:
          break;
      }
    }

    public void drawingPanel_MouseUp(object sender, MouseEventArgs e)
    {
      switch (MouseMode)
      {
        case MouseMode.Orbit:
          {
            orbitTracker.reset();
            break;
          }
        case MouseMode.Dolly:
          {
            isDollying = false;
            break;
          }
        default:
          break;
      }
    }

    public void drawingPanel_MouseDown(object sender, MouseEventArgs e)
    {
      Parent.Focus();
      if (GripManager == null) // situation during closing form or other strange situation
        return;

      switch (MouseMode)
      {
        case MouseMode.Quiescent:
          {
            if (GripManager.OnMouseDown(e.X, e.Y))
            {
              MouseMode = MouseMode.DragDrop;
            }
            else
            {
              if (selectingForBmpExport)
              {
                selRect = new RectFram(toEyeToWorld(e.X, e.Y));
                selRect.Add(Aux.activeTopView(Database, helperDevice));
                startSelPoint = new Point2d(e.X, e.Y);
                helperDevice.Update();
                MouseMode = MouseMode.Selection;
              }
              else
              {
                //select one object
                using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
                {
                  ObjectIdCollection tmpColl = new ObjectIdCollection();
                  pView.Select(new Point2dCollection(new Point2d[] { new Point2d(e.X - 1, e.Y - 1), new Point2d(e.X + 1, e.Y + 1) }),
                    new SR(tmpColl, Database.CurrentSpaceId), Teigha.GraphicsSystem.SelectionMode.Crossing);

                  if (tmpColl.Count > 0)
                  {
                    if (selected.Count > 0)
                    {
                      foreach (ObjectId objId in tmpColl)
                      {
                        if (selected.Contains(objId))
                        {
                          GripManager.MoveAllSelected(e.X, e.Y);
                          MouseMode = MouseMode.DragDrop;
                          return;
                        }
                      }
                      foreach (ObjectId objId in tmpColl)
                      {
                        selected.Add(objId);
                      }
                    }
                    else
                    {
                      selected = tmpColl;
                    }
                    updateSelection();
                  }
                  else
                  {
                    selRect = new RectFram(toEyeToWorld(e.X, e.Y));
                    selRect.Add(Aux.activeTopView(Database, helperDevice));
                    startSelPoint = new Point2d(e.X, e.Y);
                    helperDevice.Update();
                    MouseMode = MouseMode.Selection;
                  }
                }
              }
            }
            break;
          }
        case MouseMode.Selection:
          {
            if (selectingForBmpExport)
            {
              endSelPoint = new Point2d(e.X, e.Y);
              selectingForBmpExport = false;
              updateSelection();
              currentUserInputState = UserInputState.Done;
            }
            else
            {
              using (Transaction tr = Database.TransactionManager.StartTransaction())
              {
                using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
                {
                  pView.Select(
                    new Point2dCollection(new Point2d[] { startSelPoint, new Point2d(e.X, e.Y) }),
                    new SR(
                      selected,
                      blockToSearch(new ObjectId(new IntPtr(pView.ClientViewInfo.ViewportObjectId)))
                      ),
                    startSelPoint.X < e.X ? Teigha.GraphicsSystem.SelectionMode.Window : Teigha.GraphicsSystem.SelectionMode.Crossing
                  );
                  updateSelection();
                }
                tr.Commit();
              }
            }
            MouseMode = MouseMode.Quiescent;
            break;
          }
        case MouseMode.DragDrop:
          {
            using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
            {
              Point3d currentPoint = toEyeToWorld(e.X, e.Y);
              currentPoint = SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
              GripManager.DragFinal(currentPoint, true);
              SnapManager.ClearDrawables();
              helperDevice.Update();
            }
            MouseMode = MouseMode.Quiescent;
            break;
          }
        case MouseMode.Orbit:
          {
            orbitTracker.init(helperDevice.ActiveView, toEyeToWorld(e.X, e.Y));
            break;
          }
        case MouseMode.Dolly:
          {
            startSelPoint = new Point2d(e.X, e.Y);
            isDollying = true;
            break;
          }
        default:
          break;
      }
    }

    private void drawingPanel_MouseClick(object sender, MouseEventArgs e)
    {
      if (MouseMode == MouseMode.ZoomWindow)
      {
        using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
        {
          if (Aux.SelectWindowPrint)
          {
            using (Teigha.GraphicsSystem.View pViewTmp = helperDevice.ActiveView)
            {
              using (AbstractViewPE pVpPE = new AbstractViewPE(pViewTmp))
              {
                Point3d pt1 = selRect.BasePoint.TransformBy(pVpPE.WorldToEye);
                Point3d pt2 = toEyeToWorld(e.X, e.Y).TransformBy(pVpPE.WorldToEye);
                SetWindowPrint(pt1, pt2);
                helperDevice.Update();
              }
            }
            Aux.SelectWindowPrint = false;
            PageSetup();
          }
          else
            ZoomWindow(selRect.BasePoint, toEyeToWorld(e.X, e.Y));
          EraseSelectionRectangle();
          helperDevice.Update();
          MouseMode = MouseMode.Quiescent;
        }
      }
      if (MouseMode == MouseMode.Zoom)
      {
        MouseMode = MouseMode.ZoomWindow;
        selRect = new RectFram(toEyeToWorld(e.X, e.Y));
        selRect.Add(Aux.activeTopView(Database, helperDevice));
      }
    }

    // ---------------------------------- helping functions ---------------------------------------

    public void OpenDrawing(String sFilePath, bool bPartialMode, AuditInfo aiAppAudit)
    {
      if (layoutManager != null)
      {
        layoutManager.LayoutSwitched -= new Teigha.DatabaseServices.LayoutEventHandler(reinitGraphDevice);
        HostApplicationServices.WorkingDatabase = null;
        layoutManager = null;
      }

      bool bLoaded = true;
      Database = new Database(sFilePath == null, false);

      if (sFilePath != null)
      {
        try
        {
          String sExt = Path.GetExtension(sFilePath);
          sExt = sExt.ToUpper();

          if (aiAppAudit != null)
          {
            FileStreamBuf strBuf = new FileStreamBuf(Path.GetFileName(sFilePath));
            Database.ReadDwgFile(strBuf.UnmanagedObject, false, "", aiAppAudit, bPartialMode);
          }
          else
          {
            if (sExt.EndsWith(".DWG"))
            {
              Database.ReadDwgFile(sFilePath, FileOpenMode.OpenForReadAndAllShare, false, "", bPartialMode);
            }
            else if (sExt.EndsWith(".DXF"))
            {
              Database.DxfIn(sFilePath, "");
            }
          }
        }
        catch (System.Exception ex)
        {
          MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
          bLoaded = false;
        }
      }

      if (bLoaded)
      {
        HostApplicationServices.WorkingDatabase = Database;

        layoutManager = LayoutManager.Current;
        layoutManager.LayoutSwitched += new Teigha.DatabaseServices.LayoutEventHandler(reinitGraphDevice);

        //String str = HostApplicationServices.Current.FontMapFileName;

        this.Text = String.Format("[{0}]", sFilePath == null ? "New File" : sFilePath);

        initializeGraphics();
        Invalidate();

        // initialize universal overrule with device when drawing is loaded if this overrule was activated before
        if (GripManager.IsUniversalOverruleActive && GripOverruleWithDotsOnMove.overrule == null)
        {
          GripOverruleWithDotsOnMove.overrule = new GripOverruleWithDotsOnMove(Database, helperDevice.ActiveView);
          ObjectOverrule.AddOverrule(RXClass.GetClass(typeof(Entity)), GripOverruleWithDotsOnMove.overrule, true);
        }
      }
    }

    private void reinitGraphDevice(object sender, Teigha.DatabaseServices.LayoutEventArgs e)
    {
      disableCommand();
      graphics.Dispose();
      helperDevice.Dispose();
      initializeGraphics();
    }

    void disableCommand()
    {
      switch (MouseMode)
      {
        case MouseMode.DragDrop:
          {
            using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
            {
              GripManager.DragFinal(new Point3d(), false);
              Regenerate();
            }
            break;
          }
        case MouseMode.Selection:
          EraseSelectionRectangle();
          break;
        case MouseMode.Orbit:
          if (orbitControl != null)
          {
            using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
            {
              pView.Erase(orbitControl);
              orbitTracker.reset();
              orbitControl = null;
            }
            PanelState.OrbitState = false;
          }
          break;
      }
      MouseMode = MouseMode.Quiescent;
      
      foreach (ObjectId id in selected)
      {
        GripManager.removeEntityGrips(id, true);
      }
      selected.Clear();

      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);
    }

    public void Regenerate()
    {
      if (helperDevice != null)
        helperDevice.Model.Invalidate(InvalidationHint.kInvalidateAll);
      drawingPanel.Invalidate();
    }

    void EraseSelectionRectangle()
    {
      if (selRect != null)
        Aux.activeTopView(Database, helperDevice).Erase(selRect);
      selRect = null;
    }

    // helper function transforming parameters from screen to world coordinates
    void dolly(Teigha.GraphicsSystem.View pView, int x, int y)
    {
      Vector3d vec = new Vector3d(-x, -y, 0.0);
      vec = vec.TransformBy((pView.ScreenMatrix * pView.ProjectionMatrix).Inverse());
      pView.Dolly(vec);
    }

    void initializeGraphics()
    {
      try
      {
        if (helperDevice != null)
          helperDevice.Dispose();
        helperDevice = null;
        if (graphicsDevice != null)
          graphicsDevice.Dispose();
        graphicsDevice = null;

        if (gsModule == null)
          // load some predefined rendering module (may be also "WinDirectX" or "WinOpenGL")
          gsModule = (GsModule)SystemObjects.DynamicLinker.LoadModule("WinOpenGL.txv", false, true);

        graphics = Graphics.FromHwnd(drawingPanel.Handle);

        // create graphics device
        graphicsDevice = gsModule.CreateDevice();

        // setup device properties
        using (Dictionary props = graphicsDevice.Properties)
        {
          if (props.Contains("WindowHWND")) // Check if property is supported
            props.AtPut("WindowHWND", new RxVariant(drawingPanel.Handle)); // hWnd necessary for DirectX device
          if (props.Contains("WindowHDC")) // Check if property is supported
            props.AtPut("WindowHDC", new RxVariant(graphics.GetHdc())); // hWindowDC necessary for Bitmap device
          if (props.Contains("DoubleBufferEnabled")) // Check if property is supported
            props.AtPut("DoubleBufferEnabled", new RxVariant(true));
          if (props.Contains("EnableSoftwareHLR")) // Check if property is supported
            props.AtPut("EnableSoftwareHLR", new RxVariant(true));
          if (props.Contains("DiscardBackFaces")) // Check if property is supported
            props.AtPut("DiscardBackFaces", new RxVariant(true));

          // setup paperspace viewports or tiles
          ContextForDbDatabase ctx = new ContextForDbDatabase(Database);
          ctx.UseGsModel = true;

          helperDevice = LayoutHelperDevice.SetupActiveLayoutViews(graphicsDevice, ctx);
          Aux.preparePlotstyles(Database, ctx);

          GripManager.Init(helperDevice, helperDevice.Model, Database);
        }
        // set palette
        helperDevice.SetLogicalPalette(Device.DarkPalette);
        // set output extents
        resize();
      }
      catch (System.Exception ex)
      {
        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
      }
    }

    void resize()
    {
      if (helperDevice != null)
      {
        //Rectangle r = drawingPanel.Bounds;
        //r.Offset(-drawingPanel.Location.X, -drawingPanel.Location.Y);
        // HDC assigned to the device corresponds to the whole client area of the panel
        //helperDevice.OnSize(r);
        helperDevice.OnSize(drawingPanel.Size);
        helperDevice.Update();
      }
    }

    void changeActiveViewMode(Teigha.GraphicsSystem.RenderMode rndMode)
    {
      helperDevice.ActiveView.Mode = rndMode;
      helperDevice.Model.Invalidate(InvalidationHint.kInvalidateAll);
    }

    private void drawingPanel_Resize(object sender, EventArgs e)
    {
      resize();
    }

    public void ZoomExtents()
    {
      using (Transaction tr = Database.TransactionManager.StartTransaction())
      {
        using (DBObject pVpObj = Aux.active_viewport_id(Database).GetObject(OpenMode.ForWrite))
        {
          // using protocol extensions we handle PS and MS viewports in the same manner
          AbstractViewportData pAVD = new AbstractViewportData(pVpObj);
          Teigha.GraphicsSystem.View pView = pAVD.GsView;
          // do actual zooming - change GS view
          zoom_extents(pView, pVpObj);
          // save changes to database
          pAVD.SetView(pView);
          pAVD.Dispose();
          pVpObj.Dispose();
          helperDevice.Update();
        }
        tr.Commit();
      }
    }

    void zoom_extents(Teigha.GraphicsSystem.View pView, DBObject pVpObj)
    {
      // here protocol extension is used again, that provides some helpful functions
      using (AbstractViewPE pVpPE = new AbstractViewPE(pView))
      {
        BoundBlock3d bbox = new BoundBlock3d();
        bool bBboxValid = pVpPE.GetViewExtents(bbox);

        // paper space overall view
        if (pVpObj is Teigha.DatabaseServices.Viewport && ((Teigha.DatabaseServices.Viewport)pVpObj).Number == 1)
        {
          if (!bBboxValid || !(bbox.GetMinimumPoint().X < bbox.GetMaximumPoint().X && bbox.GetMinimumPoint().Y < bbox.GetMaximumPoint().Y))
          {
            bBboxValid = get_layout_extents(Database, pView, ref bbox);
          }
        }
        else if (!bBboxValid) // model space viewport
        {
          bBboxValid = get_layout_extents(Database, pView, ref bbox);
        }

        if (!bBboxValid)
        {
          // set to somewhat reasonable (e.g. paper size)
          if (Database.Measurement == MeasurementValue.Metric)
          {
            bbox.Set(Point3d.Origin, new Point3d(297.0, 210.0, 0.0)); // set to papersize ISO A4 (portrait)
          }
          else
          {
            bbox.Set(Point3d.Origin, new Point3d(11.0, 8.5, 0.0)); // ANSI A (8.50 x 11.00) (landscape)
          }
          bbox.TransformBy(pView.ViewingMatrix);
        }

        pVpPE.ZoomExtents(bbox);
      }
    }

    bool get_layout_extents(Database db, Teigha.GraphicsSystem.View pView, ref BoundBlock3d bbox)
    {
      BlockTable bt = (BlockTable)db.BlockTableId.GetObject(OpenMode.ForRead);
      BlockTableRecord pSpace = (BlockTableRecord)bt[BlockTableRecord.PaperSpace].GetObject(OpenMode.ForRead);
      Layout pLayout = (Layout)pSpace.LayoutId.GetObject(OpenMode.ForRead);
      Extents3d ext = new Extents3d();
      if (pLayout.GetViewports().Count > 0)
      {
        bool bOverall = true;
        foreach (ObjectId id in pLayout.GetViewports())
        {
          if (bOverall)
          {
            bOverall = false;
            continue;
          }
          Teigha.DatabaseServices.Viewport pVp = (Teigha.DatabaseServices.Viewport)id.GetObject(OpenMode.ForRead);
        }
        ext.TransformBy(pView.ViewingMatrix);
        bbox.Set(ext.MinPoint, ext.MaxPoint);
      }
      else
      {
        ext = pLayout.Extents;
      }
      bbox.Set(ext.MinPoint, ext.MaxPoint);
      return ext.MinPoint != ext.MaxPoint;
    }

    void erase()
    {
      using (Transaction tr = Database.TransactionManager.StartTransaction())
      {
        foreach (ObjectId id in selected)
        {
          using (Entity ent = (Entity)id.GetObject(OpenMode.ForWrite))
          {
            using (LayerTableRecord ltr = (LayerTableRecord)ent.LayerId.GetObject(OpenMode.ForRead))
            {
              if (!ltr.IsLocked)
              {
                GripManager.removeEntityGrips(id, true);
                ent.Erase();
              }
            }
          }
        }
        tr.Commit();
      }
      selected.Clear();
      Regenerate();
    }

    public Point3d toEyeToWorld(int x, int y)
    {
      using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
      {
        Point3d wcsPt = new Point3d(x, y, 0.0);
        wcsPt = wcsPt.TransformBy((pView.ScreenMatrix * pView.ProjectionMatrix).Inverse());
        wcsPt = new Point3d(wcsPt.X, wcsPt.Y, 0.0);
        using (AbstractViewPE pVpPE = new AbstractViewPE(pView))
        {
          return wcsPt.TransformBy(pVpPE.EyeToWorld);
        }
      }
    }

    public void updateSelection()
    {
      EraseSelectionRectangle();
      GripManager.UpdateSelection(selected);
      helperDevice.Update();
    }

    ObjectId blockToSearch(ObjectId vpId)
    {
      using (DBObject pDbObj = vpId.GetObject(OpenMode.ForRead))
      {
        if (pDbObj is Teigha.DatabaseServices.Viewport)
        {
          Teigha.DatabaseServices.Viewport pVp = (Teigha.DatabaseServices.Viewport)pDbObj;
          return pVp.Number == 1 ? SymbolUtilityServices.GetBlockPaperSpaceId(Database) : SymbolUtilityServices.GetBlockModelSpaceId(Database);
        }
        return SymbolUtilityServices.GetBlockModelSpaceId(Database);
      }
    }

    private void SetWindowPrint(Point3d pt1, Point3d pt2)
    {
      TransactionManager tm = Database.TransactionManager;
      using (Transaction ta = tm.StartTransaction())
      {
        using (BlockTableRecord blTableRecord = (BlockTableRecord)Database.CurrentSpaceId.GetObject(OpenMode.ForRead))
        {
          using (Layout pLayObj = (Layout)blTableRecord.LayoutId.GetObject(OpenMode.ForWrite))
          {
            PlotSettings ps = (PlotSettings)pLayObj;
            PlotSettingsValidator plotSettingVal = PlotSettingsValidator.Current;
            Extents2d ext = new Extents2d(pt1.X, pt1.Y, pt2.X, pt2.Y);
            plotSettingVal.SetPlotWindowArea(ps, ext);
          }
        }
        ta.Commit();
      }
    }

    private void ZoomWindow(Point3d pt1, Point3d pt2)
    {
      using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
      {
        using (AbstractViewPE pVpPE = new AbstractViewPE(pView))
        {
          pt1 = pt1.TransformBy(pVpPE.WorldToEye);
          pt2 = pt2.TransformBy(pVpPE.WorldToEye);
          Vector3d eyeVec = pt2 - pt1;

          if (((eyeVec.X < -1E-10) || (eyeVec.X > 1E-10)) && ((eyeVec.Y < -1E-10) || (eyeVec.Y > 1E-10)))
          {
            Point3d newPos = pt1 + eyeVec / 2.0;
            pView.Dolly(newPos.GetAsVector());
            double wf = pView.FieldWidth / Math.Abs(eyeVec.X);
            double hf = pView.FieldHeight / Math.Abs(eyeVec.Y);
            pView.Zoom(wf < hf ? wf : hf);
            helperDevice.Update();
          }
        }
      }
    }

    public void Zoom()
    {
      EraseSelectionRectangle();
      MouseMode = MouseMode.Zoom;
    }

    public void PageSetup()
    {
      TransactionManager tm = Database.TransactionManager;
      using (Transaction ta = tm.StartTransaction())
      {
        using (DBObject pVpObj = Aux.active_viewport_id(Database).GetObject(OpenMode.ForWrite))
        {
          AbstractViewportData pAVD = new AbstractViewportData(pVpObj);
          pAVD.SetView(helperDevice.ActiveView);
        }

        using (BlockTableRecord blTableRecord = (BlockTableRecord)Database.CurrentSpaceId.GetObject(OpenMode.ForRead))
        {
          using (Layout pLayObj = (Layout)blTableRecord.LayoutId.GetObject(OpenMode.ForWrite))
          {
            PlotSettings ps = (PlotSettings)pLayObj;
            Print.PageSetup pageSetupDlg = new Print.PageSetup(ps);
            if (pageSetupDlg.ShowDialog() == DialogResult.OK)
            {
              ta.Commit();
              if (Aux.SelectWindowPrint)
                Zoom();
            }
            else
            {
              ta.Abort();
            }
          }
        }
      }
    }

    public void Dolly()
    {
      if (PanelState.DollyState)
      {
        if (MouseMode == MouseMode.Quiescent)
        {
          MouseMode = MouseMode.Dolly;
        }
        else
        {
          PanelState.DollyState = false;
          ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);
        }
      }
      else
      {
        MouseMode = MouseMode.Quiescent;
      }
    }

    public void Orbit()
    {
      if (PanelState.OrbitState)
      {
        if (MouseMode == MouseMode.Quiescent && Database.TileMode)
        {
          MouseMode = MouseMode.Orbit;
          orbitControl = new OrbitCtrl();
          using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
          {
            orbitControl.Add(pView);
          }
        }
        else
        {
          PanelState.OrbitState = false;
          ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);
        }
      }
      else
      {
        if (orbitControl != null)
        {
          using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
          {
            pView.Erase(orbitControl);
            orbitControl = null;
            orbitTracker.reset();
            MouseMode = MouseMode.Quiescent;
          }
        }
      }
      helperDevice.Update();
    }

    public void ApplyViewChanges()
    {
      using (Transaction tr = Database.TransactionManager.StartTransaction())
      {
        using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
        {
          ClientViewInfo viewInfo = pView.ClientViewInfo;
          ObjectId viewportId = new ObjectId(new IntPtr(pView.ClientViewInfo.ViewportObjectId));
          using (AbstractViewPE pVp = new AbstractViewPE(tr.GetObject(viewportId, OpenMode.ForWrite)))
          {
            Point3d target = pView.Target;
            Vector3d vectorDir = pView.Position - target;
            Vector3d upVector = pView.UpVector;
            double fieldWidth = pView.FieldWidth;
            double fieldHeight = pView.FieldHeight;
            bool isPerspective = pView.IsPerspective;
            double lensLength = pView.LensLength;

            if (vectorDir.IsZeroLength())
            {
              vectorDir = (pView.ViewingMatrix.Inverse()).CoordinateSystem3d.Zaxis;//pView->viewingMatrix().inverse().getCsZAxis();
              if (vectorDir.IsZeroLength())
                vectorDir = Vector3d.ZAxis;
              //else
              //vectorDir.normalize();
            }

            if (!pVp.Target.IsEqualTo(target) ||
                !pVp.Direction.IsEqualTo(vectorDir) ||
                !pVp.UpVector.IsEqualTo(upVector) ||
                !pVp.FieldWidth.Equals(fieldWidth) ||
                !pVp.FieldHeight.Equals(fieldHeight) ||
                !pVp.IsPerspective != isPerspective ||
                !pVp.LensLength.Equals(lensLength)
               ) // and check force auto regen if needed
            {
              Vector2d viewOffset = new Vector2d();
              if (pVp.Direction.IsEqualTo(vectorDir) &&
                  pVp.UpVector.IsEqualTo(upVector) &&
                  !isPerspective &&
                  pVp.IsPerspective)
              {
                Vector3d vecX = upVector.CrossProduct(vectorDir.GetNormal());
                viewOffset = pVp.ViewOffset;
                Point3d previousTarget = pVp.Target - vecX * viewOffset.X - upVector * viewOffset.Y;
                double viewOffsetX = vecX.DotProduct(target - previousTarget);
                double viewOffsetY = upVector.DotProduct(target - previousTarget);
                viewOffset = new Vector2d(viewOffsetX, viewOffsetY);
              }

              pVp.SetView(target, vectorDir, upVector, fieldWidth, fieldHeight, isPerspective, viewOffset);
              pVp.LensLength = lensLength;

              // Auto regen
              //if (!theApp.disableAutoRegen() && requireAutoRegen(pView))
              //  const_cast<CDwgViewer*>(this)->OnViewerRegen();
            }
          }
        }
        tr.Commit();
      }
    }

    public void Wire2dViewMode(bool changeMode)
    {
      PanelState.Wire2dState = true;
      PanelState.Wire3dState = false;
      PanelState.HiddenState = false;
      PanelState.FlatShadedState = false;
      PanelState.GouraudShadedState = false;
      PanelState.FlatShadedEdState = false;
      PanelState.GouraudShadedEdState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.Optimized2D);
        helperDevice.Update();
      }
    }

    public void Wire3dViewMode(bool changeMode)
    {
      PanelState.Wire2dState = false;
      PanelState.Wire3dState = true;
      PanelState.HiddenState = false;
      PanelState.FlatShadedState = false;
      PanelState.GouraudShadedState = false;
      PanelState.FlatShadedEdState = false;
      PanelState.GouraudShadedEdState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.Wireframe);
        helperDevice.Update();
      }
    }

    public void HiddenViewMode(bool changeMode)
    {
      PanelState.Wire2dState = false;
      PanelState.Wire3dState = false;
      PanelState.HiddenState = true;
      PanelState.FlatShadedState = false;
      PanelState.GouraudShadedState = false;
      PanelState.FlatShadedEdState = false;
      PanelState.GouraudShadedEdState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.HiddenLine);
        helperDevice.Update();
      }
    }

    public void FlatShadedViewMode(bool changeMode)
    {
      PanelState.Wire2dState = false;
      PanelState.Wire3dState = false;
      PanelState.HiddenState = false;
      PanelState.FlatShadedState = true;
      PanelState.GouraudShadedState = false;
      PanelState.FlatShadedEdState = false;
      PanelState.GouraudShadedEdState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.FlatShaded);
        helperDevice.Update();
      }
    }

    public void GouraudShadedViewMode(bool changeMode)
    {
      PanelState.Wire2dState = false;
      PanelState.Wire3dState = false;
      PanelState.HiddenState = false;
      PanelState.FlatShadedState = false;
      PanelState.GouraudShadedState = true;
      PanelState.FlatShadedEdState = false;
      PanelState.GouraudShadedEdState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.GouraudShaded);
        helperDevice.Update();
      }
    }

    public void FlatShadedEdViewMode(bool changeMode)
    {
      PanelState.Wire2dState = false;
      PanelState.Wire3dState = false;
      PanelState.HiddenState = false;
      PanelState.FlatShadedState = false;
      PanelState.GouraudShadedState = false;
      PanelState.FlatShadedEdState = true;
      PanelState.GouraudShadedEdState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.FlatShadedWithWireframe);
        helperDevice.Update();
      }
    }

    public void GouraudShadedEdViewMode(bool changeMode)
    {
      PanelState.Wire2dState = false;
      PanelState.Wire3dState = false;
      PanelState.HiddenState = false;
      PanelState.FlatShadedState = false;
      PanelState.GouraudShadedState = false;
      PanelState.FlatShadedEdState = false;
      PanelState.GouraudShadedEdState = true;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

      if (changeMode)
      {
        changeActiveViewMode(Teigha.GraphicsSystem.RenderMode.GouraudShadedWithWireframe);
        helperDevice.Update();
      }
    }

    public void SetActiveViewModeButtons()
    {
      switch (helperDevice.ActiveView.Mode)
      {
        case Teigha.GraphicsSystem.RenderMode.Optimized2D:
          Wire2dViewMode(false);
          break;
        case Teigha.GraphicsSystem.RenderMode.Wireframe:
          Wire3dViewMode(false);
          break;
        case Teigha.GraphicsSystem.RenderMode.HiddenLine:
          HiddenViewMode(false);
          break;
        case Teigha.GraphicsSystem.RenderMode.FlatShaded:
          FlatShadedViewMode(false);
          break;
        case Teigha.GraphicsSystem.RenderMode.GouraudShaded:
          GouraudShadedViewMode(false);
          break;
        case Teigha.GraphicsSystem.RenderMode.FlatShadedWithWireframe:
          FlatShadedEdViewMode(false);
          break;
        case Teigha.GraphicsSystem.RenderMode.GouraudShadedWithWireframe:
          GouraudShadedEdViewMode(false);
          break;
        default:
          Wire2dViewMode(false);
          break;
      }
    }

    public void Block()
    {
      if (helperDevice != null)
      {
        using (Transaction tr = Database.TransactionManager.StartTransaction())
        {
          using (BlockTable bt = (BlockTable)Database.BlockTableId.GetObject(OpenMode.ForRead))
          {
            BlockInsert blIns = new BlockInsert(bt);
            if (DialogResult.OK == blIns.ShowDialog(this))
            {
              Regenerate();
            }
          }
          tr.Commit();
        }
      }
    }

    public void ExportImage()
    {
      ImExport.Image_export(Database, helperDevice, drawingPanel.Width, drawingPanel.Height);
    }

    public void Line()
    {
      if (!PanelState.DrawLineButtonState)
      {
        PanelState.DrawLineButtonState = true;
        this.BeginInvoke(new CreateLineDelegate(CreateLine), Database);
        ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);
      }
    }

    void CreateLine(Database db)
    {
      // to create line we need to specify start point and end point;
      // during mousemove temporary line will be drawn (jig)

      using (Teigha.GraphicsSystem.View pView = helperDevice.ActiveView)
      {
        TransactionManager tm = db.TransactionManager;
        using (Transaction tr = tm.StartTransaction())
        {
          List<Line> linesToBeRemovedFromView = new List<Line>();
          using (BlockTableRecord btr = (BlockTableRecord)db.CurrentSpaceId.GetObject(OpenMode.ForWrite))
          {
            bool cancel = false;
            Point3d nextStartPoint = new Point3d();
            bool nextLine = false;
            while (!cancel)
            {
              Line line = new Line(nextStartPoint, nextStartPoint);
              line.SetDatabaseDefaults(db);
              LineJig lineJig = new LineJig(this, drawingPanel, pView, line, cancel, nextLine);
              cancel = lineJig.DoActions();
              nextStartPoint = line.EndPoint;
              if (!cancel)
              {
                btr.AppendEntity(line);
                linesToBeRemovedFromView.Add(line);
              }
              else
                line.Dispose();
              drawingPanel.Refresh();
              nextLine = true;
            }
          }
          tr.Commit();
          foreach (Line l in linesToBeRemovedFromView)
          {
            pView.Erase(l);
            l.Dispose();
          }
        }
      }

      PanelState.DrawLineButtonState = false;
      ((MainForm)this.MdiParent).SetControlButtonsState(PanelState);

    } // CreateLine

    public UserInputState LoopTillUserInput()
    {
      while (currentUserInputState == UserInputState.InProgress)
        Application.DoEvents();

      return currentUserInputState;
    }

    public void SelectAndExportToAnotherDwg()
    {
      PromptSelectionResult selected = Editor.Current.GetSelection();

      if (selected.Status == PromptStatus.OK)
      {
        using (Database newDb = new Database(true, true))
        {
          using (ObjectIdCollection identifiers = new ObjectIdCollection(selected.Value.GetObjectIds()))
          {
            using (Transaction tr = newDb.TransactionManager.StartTransaction())
            {
              BlockTable bt = (BlockTable)(tr.GetObject(newDb.BlockTableId, OpenMode.ForWrite));
              ObjectId modelSpaceId = bt[BlockTableRecord.ModelSpace];

              ApplyViewChanges();

              IdMapping idMap = new IdMapping();
              Database.WblockCloneObjects(identifiers, modelSpaceId, idMap, DuplicateRecordCloning.Replace, false);

              ViewportTableRecord viewportOfNewDb = (ViewportTableRecord)newDb.CurrentViewportTableRecordId.GetObject(OpenMode.ForWrite);
              AbstractViewPE abstractViewportPE = new AbstractViewPE(viewportOfNewDb);
              abstractViewportPE.ZoomExtents();

              tr.Commit();
            }
          }

          PromptSaveFileOptions saveFileOptions = new PromptSaveFileOptions("Enter file name to save:");
          saveFileOptions.InitialFileName = "Exported selection.dwg";
          PromptFileNameResult fileNameForSave = Editor.Current.GetFileNameForSave(saveFileOptions);
          if (fileNameForSave.Status == PromptStatus.OK)
          {
            newDb.SaveAs(fileNameForSave.StringResult, DwgVersion.Current);
            ((MainForm)ParentForm).WriteTextAndHistoryText("Exported to " + fileNameForSave.StringResult);
          }
          else if (fileNameForSave.Status == PromptStatus.Error)
            MessageBox.Show("Could not get parameters for saving file.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
      }

      foreach (ObjectId id in selected.Value.GetObjectIds())
      {
        GripManager.removeEntityGrips(id, true);
      }

      if (helperDevice != null)
        helperDevice.Update();
    }

    public void SelectAndExportToBmp() // also see Export_Import.ExportBitmap from File -> Export -> Save Bitmap
    {
      Teigha.GraphicsSystem.GsModule graphicsModule = (Teigha.GraphicsSystem.GsModule)SystemObjects.DynamicLinker.LoadModule("WinBitmap.txv", false, true);
      if (graphicsModule == null)
      {
        MessageBox.Show("Could not load graphics module.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        return;
      }

      Teigha.GraphicsSystem.Device bitmapDevice = graphicsModule.CreateBitmapDevice();
      using (Dictionary props = bitmapDevice.Properties)
      {
        props.AtPut("BitPerPixel", new RxVariant(24));
      }

      ContextForDbDatabase ctx = new ContextForDbDatabase(Database);
      ctx.PaletteBackground = System.Drawing.Color.Black;
      LayoutHelperDevice bitmapHelperDevice = LayoutHelperDevice.SetupActiveLayoutViews(bitmapDevice, ctx);
      bitmapHelperDevice.SetLogicalPalette(helperDevice.LogicalPalette);

      selectingForBmpExport = true;
      ((MainForm)ParentForm).WriteTextAndHistoryText("Select area for bmp export:");
      currentUserInputState = UserInputState.InProgress;
      while (currentUserInputState == UserInputState.InProgress)
      {
        Application.DoEvents();
      }

      if (currentUserInputState != UserInputState.Cancelled)
      {
        // with us coordinates on y are counted from another side
        Size windowSizes = helperDevice.GetSize();
        Rectangle rect = new Rectangle(
          (int)startSelPoint.X,
          windowSizes.Height - (int)endSelPoint.Y, // so should minus here y from window height
          (int)(endSelPoint.X - startSelPoint.X),
          (int)(endSelPoint.Y - startSelPoint.Y)
        );

        bitmapHelperDevice.OnSize(rect);
        bitmapHelperDevice.BackgroundColor = System.Drawing.Color.Black;
        bitmapHelperDevice.Update();

        Teigha.GraphicsSystem.View pView = helperDevice.ActiveView;

        Bitmap bitmap = pView.GetSnapshot(rect);

        PromptSaveFileOptions saveFileOptions = new PromptSaveFileOptions("Enter file name to save:");
        saveFileOptions.InitialFileName = "Exported selection.bmp";
        PromptFileNameResult fileNameForSave = Editor.Current.GetFileNameForSave(saveFileOptions);
        if (fileNameForSave.Status == PromptStatus.OK)
        {
          bitmap.Save(fileNameForSave.StringResult);
          ((MainForm)ParentForm).WriteTextAndHistoryText("Exported to " + fileNameForSave.StringResult);
        }
        else if (fileNameForSave.Status == PromptStatus.Error)
          MessageBox.Show("Could not get parameters for saving file.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        else if (fileNameForSave.Status == PromptStatus.Cancel)
          Editor.Current.WriteMessage("Export cancelled.");

        bitmap.Dispose();
        pView.Dispose();
      }

      bitmapHelperDevice.Dispose();
      ctx.Dispose();
      bitmapDevice.Dispose();
      graphicsModule.Dispose();
    }

    public void activateAreaViewInDrawing()
    {
      Teigha.GraphicsSystem.View mainView = helperDevice.ActiveView;
      Model model;

      // by cloning current view
      /*
      areaView = mainView.CloneView(true, true);
      areaView.ViewportBorderVisibility = true;
      ViewportBorderProperties borders = new ViewportBorderProperties(Color.FromKnownColor(System.Drawing.KnownColor.White), 1);
      areaView.ViewportBorderProperties = borders;
      graphicsDevice.Add(areaView);

      using (AbstractViewPE avPE = new AbstractViewPE(areaView))
      {
        avPE.SetViewport(new Point2d(0.75, 0.75), new Point2d(0.99, 0.99));
      }

      using (Transaction tr = Database.TransactionManager.StartTransaction())
      {
        using (BlockTable bt = (BlockTable)tr.GetObject(Database.BlockTableId, OpenMode.ForWrite, false))
        {
          using (BlockTableRecord btr = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite, false))
          {
            model = mainView.GetModel(btr);
          }
        }
        tr.Commit();
      }

      model.Invalidate(InvalidationHint.kInvalidateAll);
      graphicsDevice.Update();*/

      // end by cloning

      // by setting all parameters manually

      areaView = graphicsDevice.CreateView(mainView.ClientViewInfo);
      areaView.ViewportBorderVisibility = true;
      ViewportBorderProperties borders = new ViewportBorderProperties(Color.FromKnownColor(System.Drawing.KnownColor.White), 1);
      areaView.ViewportBorderProperties = borders;
      //areaView.Background = new Teigha.DatabaseServices.Background();
      graphicsDevice.Add(areaView);

      using (Transaction tr = Database.TransactionManager.StartTransaction())
      {
        using (BlockTable bt = (BlockTable)tr.GetObject(Database.BlockTableId, OpenMode.ForWrite, false))
        {
          using (BlockTableRecord btr = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite, false))
          {
            model = mainView.GetModel(btr); // possible to use another model
            areaView.Add(btr, model);
          }
        }
        tr.Commit();
      }

      areaView.SetView(
        mainView.Position,
        mainView.Target,
        mainView.UpVector,
        mainView.FieldWidth,
        mainView.FieldHeight,
        mainView.IsPerspective ? Teigha.GraphicsSystem.Projection.Perspective : Teigha.GraphicsSystem.Projection.Parallel
        );

      using (AbstractViewPE avPE = new AbstractViewPE(areaView))
      {
        avPE.SetViewport(new Point2d(0.75, 0.75), new Point2d(1, 1));
      }

      model.Invalidate(InvalidationHint.kInvalidateAll);
      helperDevice.Update();

      // end manually

      ((MainForm)this.MdiParent).AreaViewOnPanelMenu.Checked = true;
      PanelState.AreaViewInDrawingState = true;
    }

    public void deactivateAreaViewInDrawing()
    {
      for(int i = 0; i < graphicsDevice.NumViews; i++)
      {
        if (graphicsDevice.ViewAt(i) == areaView)
        {
          graphicsDevice.Erase(i);
        }
      }
      areaView.Dispose();
      areaView = null;
      PanelState.AreaViewInDrawingState = false;
      ((MainForm)this.MdiParent).AreaViewOnPanelMenu.Checked = false;

      helperDevice.Invalidate(); // if not to call this, part of the border may stay on the drawing
      helperDevice.Update();
    }

  } // DrawingForm

  // true - checked, false - unchecked
  public class ControlButtonState
  {
    public bool DollyState { get; set; }
    public bool OrbitState { get; set; }
    public bool DrawStyleState { get; set; }
    public bool Wire2dState { get; set; }
    public bool Wire3dState { get; set; }
    public bool HiddenState { get; set; }
    public bool FlatShadedState { get; set; }
    public bool FlatShadedEdState { get; set; }
    public bool GouraudShadedState { get; set; }
    public bool GouraudShadedEdState { get; set; }
    public bool DrawLineButtonState { get; set; }// = false;
    public bool AreaViewInDrawingState { get; set; }
  }

  public enum UserInputState
  {
    InProgress,
    Done,
    NotActive,
    Cancelled
  }

}

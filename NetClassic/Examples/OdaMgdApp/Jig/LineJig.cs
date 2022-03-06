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

using System.Windows.Forms;
using Teigha.DatabaseServices;
using Teigha.Geometry;

namespace OdaMgdApp.Jig
{

  class LineJig : CustomFormEventHandler
  {
    bool startPointPicked, endPointPicked;
    bool cancel;
    Teigha.GraphicsSystem.View activeView;
    Line line;

    public LineJig(Form targetForm, Panel targetPanel, Teigha.GraphicsSystem.View activeView, Line line, bool cancel, bool isStartPointPreset)
      : base (targetPanel, targetForm)
    {
      this.targetForm = targetForm;
      this.targetPanel = targetPanel;
      this.activeView = activeView;
      this.line = line;
      this.cancel = cancel;
      startPointPicked = isStartPointPreset;
      if (isStartPointPreset)
        activeView.Add(line);
      endPointPicked = false;
    }

    protected override void Init()
    {
      base.Init();
      targetPanel.MouseDown -= ((DrawingForm)targetForm).drawingPanel_MouseDown;
      targetPanel.MouseMove -= ((DrawingForm)targetForm).drawingPanel_MouseMove;
      targetPanel.MouseUp -= ((DrawingForm)targetForm).drawingPanel_MouseUp;
    }

    protected override void Deinit()
    {
      base.Deinit();
      targetPanel.MouseDown += ((DrawingForm)targetForm).drawingPanel_MouseDown;
      targetPanel.MouseMove += ((DrawingForm)targetForm).drawingPanel_MouseMove;
      targetPanel.MouseUp += ((DrawingForm)targetForm).drawingPanel_MouseUp;
    }

    public bool DoActions()
    {
      Init();
      while (!cancel && !endPointPicked)
      {
        Application.DoEvents();
      }
      Deinit();
      return cancel;
    }

    protected override void OnMouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button == MouseButtons.Left)
      {
        if (cancel)
        {
          return;
        }
        else if (!startPointPicked)
        {
          startPointPicked = true;
          Point3d currentPoint = ((DrawingForm)targetForm).toEyeToWorld(e.X, e.Y);
          currentPoint = ((DrawingForm)targetForm).SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
          line.StartPoint = currentPoint;
          activeView.Add(line);
        }
        else
        {
          Point3d currentPoint = ((DrawingForm)targetForm).toEyeToWorld(e.X, e.Y);
          currentPoint = ((DrawingForm)targetForm).SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
          line.EndPoint = currentPoint;
          endPointPicked = true;
        }
      }
      else if (e.Button == MouseButtons.Right) // we cancel drawing line on enter, escape and right click
      {
        cancel = true;
        activeView.Erase(line);
      }
    }

    protected override void OnMouseMove(object sender, MouseEventArgs e)
    {
      Point3d currentPoint = ((DrawingForm)targetForm).toEyeToWorld(e.X, e.Y);
      currentPoint = ((DrawingForm)targetForm).SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
      line.EndPoint = currentPoint;
      ((DrawingForm)targetForm).helperDevice.Update();
    }

    protected override void OnKeyPress(object sender, KeyPressEventArgs e)
    {
      if (e.KeyChar == (char)Keys.Escape || e.KeyChar == (char)Keys.Enter) // we cancel drawing line on enter, escape and right click
      {
        cancel = true;
        activeView.Erase(line);
      }
    }
  }

}

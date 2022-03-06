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
using System.Windows.Forms;
using Teigha.DatabaseServices;
using Teigha.Geometry;
using Teigha.UserIO;

namespace OdaMgdApp.UserIO
{

  public class PointPicker
  {
    public bool cancel;
    public bool picked;
    public PromptPointResult promptPointResult;
    DrawingForm targetForm;
    Panel targetPanel;

    public void InitPointPicker(DrawingForm targetForm)
    {
      cancel = false;
      picked = false;
      promptPointResult = new PromptPointResult();
      this.targetForm = targetForm;
      this.targetPanel = targetForm.DrawingPanel;
      targetPanel.MouseDown -= targetForm.drawingPanel_MouseDown;
      targetPanel.MouseMove -= targetForm.drawingPanel_MouseMove;
      targetPanel.MouseUp -= targetForm.drawingPanel_MouseUp;
      targetPanel.MouseClick += OnMouseDown;
      targetPanel.MouseMove += OnMouseMove;
      targetForm.KeyPress += OnKeyPress;
    }

    public void DeinitPointPicker()
    {
      targetPanel.MouseClick -= OnMouseDown;
      targetPanel.MouseMove -= OnMouseMove;
      targetForm.KeyPress -= OnKeyPress;
      targetPanel.MouseDown += targetForm.drawingPanel_MouseDown;
      targetPanel.MouseMove += targetForm.drawingPanel_MouseMove;
      targetPanel.MouseUp += targetForm.drawingPanel_MouseUp;
      ((MainForm)targetForm.MdiParent).WriteText("");
    }

    public void OnMouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button == MouseButtons.Left)
      {
        if (cancel)
        {
          return;
        }
        Point3d currentPoint = targetForm.toEyeToWorld(e.X, e.Y);
        currentPoint = targetForm.SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
        promptPointResult.Value = currentPoint;
        promptPointResult.Status = PromptStatus.OK;
        picked = true;
      }
      else if (e.Button == MouseButtons.Right)
      {
        promptPointResult.Status = PromptStatus.Cancel;
        cancel = true;
      }
    }

    public void OnMouseMove(object sender, MouseEventArgs e)
    {
      Point3d currentPoint = targetForm.toEyeToWorld(e.X, e.Y);
      currentPoint = targetForm.SnapManager.MakePointSnappedIfNeeded(currentPoint, e.X, e.Y);
      ((MainForm)targetForm.MdiParent).WriteText("Picking point, current position: " + currentPoint.ToString());
    }

    public void OnKeyPress(object sender, KeyPressEventArgs e)
    {
      if (e.KeyChar == (char)Keys.Escape || e.KeyChar == (char)Keys.Enter)
      {
        promptPointResult.Status = PromptStatus.Cancel;
        cancel = true;
      }
    }
  }

}

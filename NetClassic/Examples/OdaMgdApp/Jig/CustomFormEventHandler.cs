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

namespace OdaMgdApp.Jig
{
  abstract class CustomFormEventHandler
  {
    protected Panel targetPanel; // panel, mouse events on which we handle
    protected Form targetForm; // form, keyboard events on which we handle

    public CustomFormEventHandler(Panel targetPanel, Form targetForm)
    {
      this.targetPanel = targetPanel;
      this.targetForm = targetForm;
    }

    protected virtual void Init()
    {
      targetPanel.MouseClick += OnMouseDown;
      targetPanel.MouseMove += OnMouseMove;
      targetForm.KeyPress += OnKeyPress;
    }

    protected virtual void Deinit()
    {
      targetPanel.MouseClick -= OnMouseDown;
      targetPanel.MouseMove -= OnMouseMove;
      targetForm.KeyPress -= OnKeyPress;
    }

    protected abstract void OnMouseDown(object sender, MouseEventArgs e);
    protected abstract void OnMouseMove(object sender, MouseEventArgs e);
    protected abstract void OnKeyPress(object sender, KeyPressEventArgs e);
  }
}

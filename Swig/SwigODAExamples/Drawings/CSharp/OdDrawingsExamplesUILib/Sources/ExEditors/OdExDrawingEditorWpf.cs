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

using OdKernelExamplesMgdLib;
using OdKernelExamplesMgdLib.ExView;
using System.Windows;
using System.Windows.Controls;

namespace OdDrawingsExamplesMgdLib.ExEditors
{
  public class OdExDrawingEditorWpf : OdExDrawingEditor, OdExViewFunctionalityInterface
  {
    private Control m_targetControl;
    private bool m_bShiftPress = false;

    public OdExDrawingEditorWpf(Control TargetControl) : base()
    {
      m_targetControl = TargetControl;
    }

    public void InitEvents()
    {
      m_targetControl.MouseDown += M_targetControl_MouseDown;
      m_targetControl.MouseMove += M_targetControl_MouseMove;
      m_targetControl.MouseUp += M_targetControl_MouseUp;
      m_targetControl.KeyDown += M_targetControl_KeyDown;
      m_targetControl.KeyUp += M_targetControl_KeyUp;
    }

    public void UnInitEvents()
    {
      m_targetControl.MouseDown -= M_targetControl_MouseDown;
      m_targetControl.MouseMove -= M_targetControl_MouseMove;
      m_targetControl.MouseUp -= M_targetControl_MouseUp;
      m_targetControl.KeyDown -= M_targetControl_KeyDown;
      m_targetControl.KeyUp -= M_targetControl_KeyUp;
    }

    private void M_targetControl_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
    {
      if (e.Key == System.Windows.Input.Key.LeftShift ||
        e.Key == System.Windows.Input.Key.RightShift)
        m_bShiftPress = true;
    }

    private void M_targetControl_KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
    {
      if (e.Key == System.Windows.Input.Key.LeftShift ||
        e.Key == System.Windows.Input.Key.RightShift)
        m_bShiftPress = false;
    }

    private void M_targetControl_MouseDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
    {
      Point pos = e.GetPosition(m_targetControl);
      this.OnMouseDown((int)pos.X, (int)pos.Y, m_bShiftPress);
    }

    private void M_targetControl_MouseMove(object sender, System.Windows.Input.MouseEventArgs e)
    {
      Point pos = e.GetPosition(m_targetControl);
      this.OnMouseMove((int)pos.X, (int)pos.Y, m_bShiftPress);
    }

    private void M_targetControl_MouseUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
    {
      Point pos = e.GetPosition(m_targetControl);
      this.OnMouseUp((int)pos.X, (int)pos.Y);
    }
  }
}
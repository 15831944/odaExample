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
using System.Text;
using Microsoft.Win32;
using System.Windows.Forms;

using Teigha;
using Teigha.DatabaseServices;
using Teigha.Runtime;
using Teigha.Geometry;
using Teigha.GraphicsInterface;

namespace OdaMgdApp
{

  class HostAppServ : ODASampleCommon.HostApplicationServicesExample
  {
    NewProgressMeter pMeter;

    public HostAppServ(ProgressBar pbar)
    {
      pMeter = new NewProgressMeter(pbar);
    }

    public override bool GetPassword(String fileName, PasswordOptions options, out String pass)
    {
      PasswordDlg pwdDlg = new PasswordDlg();
      pwdDlg.TextFileName.Text = fileName;
      if (pwdDlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
      {
        pass = pwdDlg.password.Text;
        return true;
      }
      pass = String.Format("");
      return false;
    }

    public override Teigha.Runtime.ProgressMeter NewProgressMeter()
    {
      return pMeter;
    }

    public override String BitmapDevice(RXObject viewObj, Database database, BitmapDeviceFlags flag)
    {
      return "WinOpenGL.txv";
    }
  };

  class NewProgressMeter : Teigha.Runtime.ProgressMeter
  {
    ProgressBar m_pbar;
    public NewProgressMeter(ProgressBar pbar)
    {
      m_pbar = pbar;
    }

    public override void SetLimit(int max)
    {
      m_pbar.Maximum = max;
    }

    public override void MeterProgress()
    {
      if (m_pbar.IsHandleCreated)
        m_pbar.BeginInvoke((MethodInvoker)delegate { m_pbar.PerformStep(); });
    }

    public override void Start()
    {
    }

    public override void Start(String str)
    {
    }

    public override void Stop()
    {
    }
  };

  class LayoutPaper : LayoutPaperPE
  {
    public LayoutPaper()
    {
    }

    public override bool DrawPaper(Layout layout, WorldDraw worldDraw, Point3dCollection points)
    {
      worldDraw.Geometry.Polygon(points);
      return true;
    }

    public override bool DrawBorder(Layout layout, WorldDraw worldDraw, Point3dCollection points)
    {
      worldDraw.Geometry.Polygon(points);
      return true;
    }

    public override bool DrawMargins(Layout layout, WorldDraw worldDraw, Point3dCollection points)
    {
      if ((points[0] == points[1]) || (points[1] == points[2]))
        return true;

      int nDashes = 15, i;
      WorldGeometry wGeom = worldDraw.Geometry;
      Point3dCollection dash1 = new Point3dCollection();
      Point3dCollection dash2 = new Point3dCollection();
      Vector3d step = (points[1] - points[0]) / (nDashes * 2 + 1);
      dash1.Add(points[0]);
      dash2.Add(points[2]);
      dash1.Add(points[0]);
      dash2.Add(points[2]);

      Teigha.GraphicsInterface.Polyline pl = new Teigha.GraphicsInterface.Polyline(dash1, new Vector3d(), new IntPtr(0));
      for (i = 0; i <= nDashes; ++i)
      {
        dash1[1] = dash1[0] + step;
        pl.Points = dash1;
        wGeom.Polyline(pl);
        dash1[0] = dash1[1] + step;
        dash2[1] = dash2[0] - step;
        pl.Points = dash2;
        wGeom.Polyline(pl);
        dash2[0] = dash2[1] - step;
      }

      nDashes = (int)(((points[2] - points[1]).Length / step.Length) - 1) / 2;
      step = (points[2] - points[1]) / (nDashes * 2 + 1);
      dash1[0] = points[1];
      dash2[0] = points[3];
      for (i = 0; i <= nDashes; ++i)
      {
        dash1[1] = dash1[0] + step;
        pl.Points = dash1;
        wGeom.Polyline(pl);
        dash1[0] = dash1[1] + step;
        dash2[1] = dash2[0] - step;
        pl.Points = dash2;
        wGeom.Polyline(pl);
        dash2[0] = dash2[1] - step;
      }

      /////////
      /*for(i=0; i<=nDashes; ++i)
      {
        dash1[1] = dash1[0] + step;
        geom.polyline(2, dash1);
        dash1[0] = dash1[1] + step;
        dash2[1] = dash2[0] - step;
        geom.polyline(2, dash2);
        dash2[0] = dash2[1] - step;
      }
      nDashes = int((points[2] - points[1]).length() / step.length() - 1) / 2;
      step = (points[2] - points[1]) / (nDashes * 2 + 1);
      dash1[0] = points[1];
      dash2[0] = points[3];
      for(i=0; i<=nDashes; ++i)
      {
        dash1[1] = dash1[0] + step;
        geom.polyline(2, dash1);
        dash1[0] = dash1[1] + step;
        dash2[1] = dash2[0] - step;
        geom.polyline(2, dash2);
        dash2[0] = dash2[1] - step;
      }*/

      return true;
    }
  }

}

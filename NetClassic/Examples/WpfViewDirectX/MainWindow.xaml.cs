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
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Interop;
using System.Drawing;
using Teigha;
using Teigha.DatabaseServices;
using Teigha.GraphicsSystem;
using Teigha.Runtime;
using Teigha.GraphicsInterface;
using Teigha.Geometry;

namespace WpfViewDirectX
{

  /// <summary>
  /// Interaction logic for MainWindow.xaml
  /// </summary>
  public partial class MainWindow : Window
  {
    Teigha.Runtime.Services services;
    Database database = null;
    LayoutManager lm;

    public MainWindow()
    {
      InitializeComponent();
      foreach (MenuItem topLevelMenu in MainMenu.Items)
      {
        foreach (MenuItem itemMenu in topLevelMenu.Items)
        {
          itemMenu.Click += new RoutedEventHandler(MenuItem_Click);
        }
      }

      String strPath = Environment.GetEnvironmentVariable("PATH");
      String strPathModules = ""; // System.Environment.CurrentDirectory;
      Environment.SetEnvironmentVariable("PATH", strPathModules + ";" + strPath);

      Teigha.Runtime.Services.odActivate(ActivationData.userInfo, ActivationData.userSignature);
      services = new Teigha.Runtime.Services();
    }

    protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
    {
      drawControl.Deinitialize();

      if (database != null)
        database.Dispose();

      services.Dispose();
    }

    private void fileOpen(String sFilePath)
    {
      drawControl.Reinitialize();

      if (database != null)
        database.Dispose();

      if (lm != null)
      {
        lm.LayoutSwitched -= new Teigha.DatabaseServices.LayoutEventHandler(reinitGraphDevice);
        HostApplicationServices.WorkingDatabase = null;
        lm = null;
      }

      bool bLoaded = true;
      database = new Database(false, false);

      try
      {
        String sExt = sFilePath.Substring(sFilePath.Length - 4);
        sExt = sExt.ToUpper();
        if (sExt.EndsWith(".DWG"))
        {
          database.ReadDwgFile(sFilePath, FileOpenMode.OpenForReadAndAllShare, false, "");
        }
        else if (sExt.EndsWith(".DXF"))
        {
          database.DxfIn(sFilePath, "");
        }
      }
      catch (System.Exception ex)
      {
        MessageBox.Show(ex.Message);
        bLoaded = false;
      }

      if (bLoaded)
      {
        this.Title = String.Format("WpfViewDirectXApp - [{0}]", sFilePath);

        drawControl.Initialize(database);
      }
    }

    private void reinitGraphDevice(object sender, Teigha.DatabaseServices.LayoutEventArgs e)
    {
      drawControl.Deinitialize();
      drawControl.Initialize(database);
    }

    private void MenuItem_Click(object sender, RoutedEventArgs e)
    {
      MenuItem mItem = e.Source as MenuItem;
      if (mItem.IsEnabled)
      {
        String sHeader = mItem.Header as String;
        if ("_Open" == sHeader)
        {
          database = new Database(false, false);
          System.Windows.Forms.OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();
          openFileDialog.Filter = "dwg files|*.dwg|dxf files|*.dxf";
          openFileDialog.DefaultExt = "dwg";
          openFileDialog.RestoreDirectory = true;

          if (System.Windows.Forms.DialogResult.OK == openFileDialog.ShowDialog())
          {
            fileOpen(openFileDialog.FileName);
            MenuItem mPar = mItem.Parent as MenuItem;
            MenuItemSave.IsEnabled   = true;
            MenuItemSaveAs.IsEnabled = true;
          }
        }//if ("_Open" == sHeader)
        if ("_Exit" == sHeader)
        {
          this.Close();
        }
        if (database != null)
        {
          if ("_Save" == sHeader)
          {
            if (database != null)
              database.Save();
          }
          if ("_SaveAs" == sHeader)
          {
            System.Windows.Forms.SaveFileDialog saveAsFileDialog = new System.Windows.Forms.SaveFileDialog();
            saveAsFileDialog.Filter = "dwg R24 file format(*.dwg)|*.dwg|dwg R24 file format(*.dwg)|*.dwg|dwg R21 file format(*.dwg)|*.dwg|dwg R18 file format(*.dwg)|*.dwg|dwg R15 file format(*.dwg)|*.dwg|dwg R14 file format(*.dwg)|*.dwg|dwg R13 file format(*.dwg)|*.dwg|dwg R12 file format(*.dwg)|*.dwg";
            saveAsFileDialog.DefaultExt = "dwg";
            saveAsFileDialog.RestoreDirectory = true;

            if (System.Windows.Forms.DialogResult.OK == saveAsFileDialog.ShowDialog())
            {
              int version = saveAsFileDialog.FilterIndex % 7;              
              DwgVersion vers = DwgVersion.Current;
              if (0 == version)
                vers = DwgVersion.vAC12;
              else
              {
                if (1 == version)
                  vers = DwgVersion.vAC24;
                else
                {
                  if (2 == version)
                    vers = DwgVersion.vAC21;
                  else
                  {
                    if (3 == version)
                      vers = DwgVersion.vAC18;
                    else
                    {
                      if (4 == version)
                        vers = DwgVersion.vAC15;
                      else if (5 == version)
                        vers = DwgVersion.vAC14;
                    }
                  }
                }
              }//else if (0 == version)
              if (Math.Truncate((double)saveAsFileDialog.FilterIndex / 7) == 0)
                database.SaveAs(saveAsFileDialog.FileName, vers);
              else
                database.DxfOut(saveAsFileDialog.FileName, 16, vers);
            }//if (System.Windows.Forms.DialogResult.OK == saveAsFileDialog.ShowDialog())
          }//if ("_SaveAs" == sHeader)
        }//if (database != null)
      }//if (mItem.IsEnabled)
    }

    public static ObjectId ActiveViewPortId(Database database)
    {
      if (database.TileMode)
      {
        return database.CurrentViewportTableRecordId;
      }
      else
      {

        using (BlockTableRecord paperBTR = (BlockTableRecord)database.CurrentSpaceId.GetObject(OpenMode.ForRead))
        {
          using (Layout layout = (Layout)paperBTR.LayoutId.GetObject(OpenMode.ForRead))
          {
            return layout.CurrentViewportId;
          }
        }
      }
    }





    public void Dolly(View pView, int x, int y)
    {

      // helper function transforming parameters from screen to world coordinates

      Vector3d vector = new Vector3d(-x, -y, 0.0);

      vector = vector.TransformBy((pView.ScreenMatrix * pView.ProjectionMatrix).Inverse());

      pView.Dolly(vector);
    }



    //Zoom In / Zoom Out functionality

    private void Window_MouseWheel(object sender, MouseWheelEventArgs parameter)
    {
      try
      {

        System.Windows.Point pointToWindow = Mouse.GetPosition(parameter.MouseDevice.Captured);

        int delta = (parameter as MouseWheelEventArgs).Delta;

        using (Transaction tr = database.TransactionManager.StartTransaction())
        {
          using (DBObject pVpObj = ActiveViewPortId(database).GetObject(OpenMode.ForWrite))
          {
            using (AbstractViewportData pAVD = new AbstractViewportData(pVpObj))
            {
              using (View pView = pAVD.GsView)
              {

                // camera position in world coordinates

                Point3d positionCamera = pView.Position;

                // TransformBy() returns a transformed copy

                positionCamera = positionCamera.TransformBy(pView.WorldToDeviceMatrix);

                double vx = pointToWindow.X - positionCamera.X;

                double vy = pointToWindow.Y - positionCamera.Y;

                Dolly(pView, (int)-vx, (int)-vy);

                pView.Zoom(delta > 0 ? 1.0 / 0.9 : 0.9);

                Dolly(pView, (int)vx, (int)vy);

                pAVD.SetView(pView);

              }
            }
          }
          tr.Commit();
        }

        drawControl.Resize();
      }
      catch (System.Exception ex)
      {
        MessageBox.Show("Error on Zoom: " + ex.Message, "Error");
      }
    }
  } // class MainWindow

} // namespace WpfViewDirectX

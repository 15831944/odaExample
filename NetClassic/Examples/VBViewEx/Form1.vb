'/////////////////////////////////////////////////////////////////////////////// 
'// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
'// All rights reserved. 
'// 
'// This software and its documentation and related materials are owned by 
'// the Alliance. The software may only be incorporated into application 
'// programs owned by members of the Alliance, subject to a signed 
'// Membership Agreement and Supplemental Software License Agreement with the
'// Alliance. The structure and organization of this software are the valuable  
'// trade secrets of the Alliance and its suppliers. The software is also 
'// protected by copyright law and international treaty provisions. Application  
'// programs incorporating this software must include the following statement 
'// with their copyright notices:
'//   
'//   This application incorporates Open Design Alliance software pursuant to a license 
'//   agreement with Open Design Alliance.
'//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
'//   All rights reserved.
'//
'// By use of this software, its documentation or related materials, you 
'// acknowledge and accept the above terms.
'///////////////////////////////////////////////////////////////////////////////
Imports System
Imports System.Drawing
Imports System.Windows.Forms
Imports Teigha
Imports Teigha.DatabaseServices
Imports Teigha.Geometry
Imports Teigha.GraphicsInterface
Imports Teigha.GraphicsSystem

Public Class Form1
  Private m_services As Teigha.Runtime.Services
  Private m_currentDatabase As Teigha.DatabaseServices.Database

  Private m_graphics As System.Drawing.Graphics
  Private m_hdcPtr As IntPtr
  Private m_graphichsDevice As Teigha.GraphicsSystem.Device
  Private m_helperDevice As Teigha.GraphicsSystem.LayoutHelperDevice

  Public Enum FuncionalityMode
    None
    Pan
    Rotation
  End Enum

  Private Sub SetFunctionalityMode(mode As FuncionalityMode)
    m_funcMode = mode
  End Sub

  Private m_funcMode As FuncionalityMode
  Private m_zoomFunc As OdExZoomFunctionality
  Private m_panFunc As OdExPanFuncionality
  Private m_rotationFunc As OdExRotationFunctionality

  Public Sub New()
    Teigha.Runtime.Services.odActivate(ActivationData.userInfo, ActivationData.userSignature)
    m_services = New Teigha.Runtime.Services()

    Teigha.Runtime.SystemObjects.DynamicLinker.LoadApp("GripPoints", False, False)
    Teigha.Runtime.SystemObjects.DynamicLinker.LoadApp("ExDynamicBlocks", False, False)

    InitializeComponent()

  End Sub

  Private Sub OpenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenToolStripMenuItem.Click
    If (DialogResult.OK = openFileDialog.ShowDialog()) Then

      If (m_currentDatabase IsNot Nothing) Then
        UnInitializeGraphics()
        CloseDatabase()
      End If

      Dim bLoaded As Boolean = True
      m_currentDatabase = New Database(False, False)

      If (openFileDialog.FilterIndex = 1) Then
        Try
          m_currentDatabase.ReadDwgFile(openFileDialog.FileName, FileOpenMode.OpenForReadAndAllShare, False, "", False)
        Catch ex As Exception
          MessageBox.Show(ex.Message)
          bLoaded = False
        End Try
      Else
        Try
          m_currentDatabase.DxfIn(openFileDialog.FileName, "")
        Catch ex As Exception
          MessageBox.Show(ex.Message)
          bLoaded = False
        End Try
      End If

      If (bLoaded) Then
        HostApplicationServices.WorkingDatabase = m_currentDatabase
        InitializeGraphics()
      End If
    End If
  End Sub

  Private Sub CloseDatabase()
    If (Not (m_currentDatabase Is Nothing)) Then
      m_currentDatabase.Dispose()
    End If
  End Sub

  Private Sub Form1_FormClosed(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles MyBase.FormClosed
    UnInitializeGraphics()
    CloseDatabase()
    m_services.Dispose()
  End Sub

  Private Function CreateGsDevice() As Teigha.GraphicsSystem.Device
    Dim gsModule As GsModule = CType(Teigha.Runtime.SystemObjects.DynamicLinker.LoadModule("WinGDI.txv", False, True), GsModule)

    Dim graphichsDevice As Teigha.GraphicsSystem.Device = gsModule.CreateDevice()

    Dim gsProperties As Teigha.Runtime.Dictionary = graphichsDevice.Properties

    If gsProperties.Contains("WindowHWND") Then
      gsProperties.AtPut("WindowHWND", New Teigha.Runtime.RxVariant(CType(GetDrawingPanelHandle(), Integer)))
    End If
    If gsProperties.Contains("WindowHDC") Then
      gsProperties.AtPut("WindowHDC", New Teigha.Runtime.RxVariant(CType(m_hdcPtr, Integer)))
    End If
    If gsProperties.Contains("DoubleBufferEnabled") Then
      gsProperties.AtPut("DoubleBufferEnabled", New Teigha.Runtime.RxVariant(True))
    End If
    If gsProperties.Contains("EnableSoftwareHLR") Then
      gsProperties.AtPut("EnableSoftwareHLR", New Teigha.Runtime.RxVariant(True))
    End If
    If gsProperties.Contains("DiscardBackFaces") Then
      gsProperties.AtPut("DiscardBackFaces", New Teigha.Runtime.RxVariant(True))
    End If

    Return graphichsDevice
  End Function

  Private Sub InitGrapicsHDC()
    m_graphics = Graphics.FromHwnd(DrawingPanel.Handle)
    m_hdcPtr = m_graphics.GetHdc()
  End Sub

  Private Sub UnInitGrapicsHDC()
    If (m_graphics Is Nothing) Then
      Return
    End If
    m_graphics.ReleaseHdc(m_hdcPtr)
    m_graphics.Dispose()
  End Sub

  Function GetDrawingPanelHandle() As IntPtr
    Return DrawingPanel.Handle
  End Function

  Function CreateGiContext() As ContextForDbDatabase
    Dim ctx As ContextForDbDatabase = New ContextForDbDatabase(m_currentDatabase)
    ctx.UseGsModel = True
    Return ctx
  End Function

  Private Sub InitializeGraphics()
    Try
      InitGrapicsHDC()

      m_graphichsDevice = CreateGsDevice()

      Dim giCtx As ContextForDbDatabase = CreateGiContext()

      m_helperDevice = LayoutHelperDevice.SetupActiveLayoutViews(m_graphichsDevice, giCtx)

      m_helperDevice.SetLogicalPalette(Device.DarkPalette)

      ResizeDev()

      UpdateDevice()

      m_zoomFunc = New OdExZoomFunctionality(m_helperDevice.ActiveView)
      m_panFunc = New OdExPanFuncionality(m_helperDevice.ActiveView)
      m_rotationFunc = New OdExRotationFunctionality(m_helperDevice.ActiveView)

    Catch ex As Exception
      MessageBox.Show(ex.ToString())
    End Try
  End Sub

  Private Sub UnInitializeGraphics()
    UnInitGrapicsHDC()
    If (Not (m_helperDevice Is Nothing)) Then
      m_helperDevice.Dispose()
      m_graphichsDevice.Dispose()
    End If
  End Sub

  Private Sub DrawingPanel_Paint(ByVal sender As System.Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles DrawingPanel.Paint
    If (Not (m_helperDevice Is Nothing)) Then
      Try
        UpdateDevice()
      Catch ex As Exception
        m_graphics.DrawString(ex.ToString(), New Font("Arial", 16), New SolidBrush(Color.Black), New PointF(150.0F, 150.0F))
      End Try
    End If
  End Sub

  Private Sub Form1_Resize(ByVal sender As System.Object, ByVal e As EventArgs) Handles MyBase.SizeChanged
    If (m_helperDevice Is Nothing) Then
      Return
    End If
    ResizeDev()
  End Sub

  Private Sub ResizeDev()
    If (Not (m_helperDevice Is Nothing)) Then
      Dim rect As Rectangle = DrawingPanel.Bounds
      rect.Offset(-DrawingPanel.Location.X, -DrawingPanel.Location.Y)
      'HDC assigned to the device corresponds to the whole client area of the panel
      m_helperDevice.OnSize(rect)
      UpdateDevice()
    End If

  End Sub

  Private Sub UpdateDevice()
    m_helperDevice.Update()
  End Sub

  Private Sub Regenerate()
    If (m_helperDevice Is Nothing) Then
      Return
    End If

    m_helperDevice.Model.Invalidate(InvalidationHint.kInvalidateAll)
    UpdateDevice()
  End Sub

  Private Sub InsertBlockToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles InsertBlockToolStripMenuItem.Click
    If (m_currentDatabase Is Nothing) Then
      Return
    End If

    If (DialogResult.OK = openFileDialog.ShowDialog()) Then
      Dim blockDb As New Database(False, False)

      Try
        blockDb.ReadDwgFile(openFileDialog.FileName, IO.FileShare.Read, False, Nothing)
      Catch ex As Exception
        MessageBox.Show(ex.Message)
      End Try

      Dim objId As ObjectId
      objId = m_currentDatabase.Insert(New String("TestInsertBlock"), blockDb, True)

      Dim tr As Transaction = m_currentDatabase.TransactionManager.StartTransaction()
      Dim btr As BlockTableRecord = m_currentDatabase.CurrentSpaceId.GetObject(DatabaseServices.OpenMode.ForWrite)
      Dim bref_ins As BlockReference = New BlockReference(New Point3d(0, 0, 0), objId)
      btr.AppendEntity(bref_ins)

      btr.Dispose()
      blockDb.Dispose()
      bref_ins.Dispose()
      tr.Commit()
      tr.Dispose()

      UpdateDevice()
    End If
  End Sub

  Private Sub SaveAsToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveAsToolStripMenuItem.Click
    If (Not (m_currentDatabase Is Nothing)) Then
      If (DialogResult.OK = saveAsFileDialog.ShowDialog()) Then
        m_currentDatabase.SaveAs(saveAsFileDialog.FileName, DwgVersion.Current)
      End If
    End If
  End Sub

  Private Sub RegenerateToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RegenerateToolStripMenuItem.Click
    Regenerate()
  End Sub

  Private Sub Form1_WheelDelta(sender As Object, e As MouseEventArgs) Handles Me.MouseWheel
    If (Not (m_helperDevice Is Nothing)) Then
      m_zoomFunc.OnZoom(e.X, e.Y, e.Delta)
      UpdateDevice()
    End If
  End Sub

  Private Sub Form1_MouseDown(sender As Object, e As MouseEventArgs) Handles DrawingPanel.MouseDown
    If (Not (m_helperDevice Is Nothing)) Then
      If (m_funcMode = FuncionalityMode.Pan) Then
        m_panFunc.OnStartPan(e.X, e.Y)
      ElseIf (m_funcMode = FuncionalityMode.Rotation) Then
        m_rotationFunc.OnStartRotationHandler(e.X, e.Y)
      End If
    End If
  End Sub

  Private Sub Form1_MouseUp(sender As Object, e As MouseEventArgs) Handles DrawingPanel.MouseUp
    If (Not (m_helperDevice Is Nothing)) Then
      If (m_funcMode = FuncionalityMode.Pan) Then
        m_panFunc.OnFinishPan()
      ElseIf (m_funcMode = FuncionalityMode.Rotation) Then
        m_rotationFunc.OnFinishRotationHandler()
      End If
    End If
  End Sub

  Private Sub Form1_MouseMove(sender As Object, e As MouseEventArgs) Handles DrawingPanel.MouseMove
    If (Not (m_helperDevice Is Nothing)) Then
      If (m_funcMode = FuncionalityMode.Pan) Then
        m_panFunc.OnMovePan(e.X, e.Y)
        UpdateDevice()
      ElseIf (m_funcMode = FuncionalityMode.Rotation) Then
        m_rotationFunc.OnMoveRotationHandler(e.X, e.Y)
        UpdateDevice()
      End If
    End If
  End Sub

  Private Sub ViewMenu_ItemCheckedChangedHandler(sender As Object, e As EventArgs) Handles PanToolStripMenuItem.CheckedChanged, RotationToolStripMenuItem.CheckedChanged
    Dim btn As ToolStripMenuItem = CType(sender, ToolStripMenuItem)
    If (btn.Checked) Then
      If btn Is RotationToolStripMenuItem Then
        PanToolStripMenuItem.Checked = False
        SetFunctionalityMode(FuncionalityMode.Rotation)
      ElseIf btn Is PanToolStripMenuItem Then
        RotationToolStripMenuItem.Checked = False
        SetFunctionalityMode(FuncionalityMode.Pan)
      Else
        Throw New NotImplementedException()
      End If
    Else
      SetFunctionalityMode(FuncionalityMode.None)
    End If
  End Sub

End Class


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
Imports System.Windows.Forms
Imports Teigha
Imports Teigha.Geometry
Imports Teigha.GraphicsSystem

Public Class OdExZoomFunctionality : Inherits OdExViewFunctionalityBase
  Public Sub New(targetView As GraphicsSystem.View)
    MyBase.New(targetView)
  End Sub

  Public Sub OnZoom(xMouse As Integer, yMouse As Integer, wheelDelta As Integer)
    If (m_TargetView Is Nothing) Then
      Return
    End If

    Dim correctScreenPoint As Point2d = New Point2d(Convert.ToDouble(xMouse), Convert.ToDouble(yMouse))
    Dim worldPoint As Point3d = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(m_TargetView, correctScreenPoint)

    OnZoomActiveView(Convert.ToDouble(wheelDelta) / 120)

    OnMoveToCenterZoom(correctScreenPoint, worldPoint)
  End Sub

  Private Sub OnZoomActiveView(steps As Double)
    Dim view As GraphicsSystem.View = m_TargetView
    If (view.IsPerspective) Then
      Dim position As Point3d = view.Position
      Dim target As Point3d = view.Target
      Dim direction As Vector3d = target - position
      Dim upVector As Vector3d = view.UpVector
      Dim Width As Double = view.FieldWidth()
      Dim Height As Double = view.FieldHeight()

      'calculate an appropriate offset using real size of the frame
      If (Width < Height) Then
        steps *= Width / 2.0
      Else
        steps *= Height / 2.0
      End If

      direction *= steps

      position += direction
      target += direction

      view.SetView(position, target, upVector, Width, Height, GraphicsSystem.Projection.Perspective)
    Else
      view.Zoom(Math.Pow(1.11, steps))
    End If
  End Sub

  Private Sub OnMoveToCenterZoom(correctScreenPoint As Point2d, worldPoint As Point3d)
    Dim view As GraphicsSystem.View = m_TargetView

    'get New screen point of the same world point
    Dim worldToDevice As Matrix3d = view.WorldToDeviceMatrix()
    Dim newScreenPoint As Point3d = worldToDevice * worldPoint

    'get world points on the focal plane
    Dim movingPoint As Point3d = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(view, New Point2d(newScreenPoint.X, newScreenPoint.Y))
    Dim destinationPoint As Point3d = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(view, correctScreenPoint)

    Dim position As Point3d = view.Position
    Dim target As Point3d = view.Target
    Dim upVector As Vector3d = view.UpVector
    Dim Width As Double = view.FieldWidth()
    Dim Height As Double = view.FieldHeight()
    Dim isPerspective As Boolean = view.IsPerspective()

    'shift the camera so points coincide
    Dim offset As Vector3d = destinationPoint - movingPoint
    position -= offset
    target -= offset

    Dim projection As GraphicsSystem.Projection = If(isPerspective, GraphicsSystem.Projection.Perspective, GraphicsSystem.Projection.Parallel)

    view.SetView(position, target, upVector, Width, Height, projection)
  End Sub

End Class

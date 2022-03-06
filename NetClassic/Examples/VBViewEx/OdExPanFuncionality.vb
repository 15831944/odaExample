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
Imports Teigha
Imports Teigha.Geometry

Public Class OdExPanFuncionality : Inherits OdExViewFunctionalityBase

  Dim m_started As Boolean
  Dim m_pos As Point3d
  Dim m_prevPt As Point3d

  Public Sub New(targetView As GraphicsSystem.View)
    MyBase.New(targetView)
  End Sub

  Public Sub OnStartPan(xPos As Integer, yPos As Integer)
    If (m_TargetView Is Nothing Or m_started) Then
      Return
    End If
    m_pos = m_TargetView.Position()

    'remember the difference between click point in WCS And camera current position
    m_prevPt = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(m_TargetView, New Point2d(xPos, yPos)) - m_pos.GetAsVector()

    m_started = True
  End Sub

  Public Sub OnMovePan(xPos As Integer, yPos As Integer)
    If (m_TargetView Is Nothing Or Not m_started) Then
      Return
    End If

    'calculate click point in WCS
    Dim ptScreen As Point2d = New Point2d(xPos, yPos)
    Dim pt As Point3d = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(m_TargetView, ptScreen)

    'obtain delta for dolly
    Dim v As Point3d = m_prevPt - (pt - m_pos)
    Dim delta As Vector3d = v.GetAsVector()

    'transform delta to eye
    delta = delta.TransformBy(m_TargetView.ViewingMatrix())

    'perform camera moving
    m_TargetView.Dolly(delta.X, delta.Y, delta.Z)

    'remember the difference between click point in WCS And camera previous position
    m_prevPt = pt - m_pos.GetAsVector()

    'remember camera current position
    m_pos = m_TargetView.Position()

  End Sub

  Public Sub OnFinishPan()
    m_started = False
  End Sub

End Class

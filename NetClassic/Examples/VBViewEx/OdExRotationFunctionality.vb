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
Imports Teigha
Imports Teigha.DatabaseServices
Imports Teigha.Geometry

Public Class OdExRotationFunctionality : Inherits OdExViewFunctionalityBase

  Dim m_started As Boolean
  Dim m_viewCenter As Point3d
  Dim m_prevPt As Point3d
  Dim m_D As Double

  Public Sub New(targetView As GraphicsSystem.View)
    MyBase.New(targetView)
  End Sub

  Public Sub OnStartRotationHandler(xPos As Integer, yPos As Integer)
    If (m_TargetView Is Nothing Or m_started) Then
      Return
    End If
    'calculate click point in WCS
    Dim pt As Point3d = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(m_TargetView, New Point2d(xPos, yPos))

    'transfer Point to the eye coordinate system
    m_prevPt = m_TargetView.ViewingMatrix() * pt

    'calculate mouse move to rotation angle conversion coefficient in base of viewport dc size
    Dim pt1, pt2 As Point2d
    OdExGsDeviceHelpers.GetViewDcCorners(m_TargetView, pt1, pt2)
    Dim dX As Double = pt2.X - pt1.X
    Dim dY As Double = pt2.Y - pt1.Y
    Dim r As Double = Math.Min(dX, dY)
    m_D = r

    Dim pVpPE As AbstractViewPE = New AbstractViewPE(m_TargetView)

    Dim extents As BoundBlock3d = New BoundBlock3d()
    Dim bBboxValid As Boolean = pVpPE.GetViewExtents(extents)

    Dim m_viewCenter As Point3d = extents.center()
    m_viewCenter.TransformBy(pVpPE.EyeToWorld())

    m_started = True
  End Sub

  Public Sub OnMoveRotationHandler(xPos As Integer, yPos As Integer)
    If (m_TargetView Is Nothing Or (Not m_started)) Then
      Return
    End If

    'calculate click point in WCS
    Dim ptScreen As Point2d = New Point2d(xPos, yPos)
    Dim pt As Point3d = OdExGsDeviceHelpers.GetWorldCoordinateByScreen(m_TargetView, ptScreen)

    'transfer point to the eye coordinate system
    Dim ptView As Point3d = m_TargetView.ViewingMatrix() * pt

    'calculate the angles for the rotation about appropriate axes
    Dim distX As Double = ptView.X - m_prevPt.X 'around vertical
    Dim distY As Double = ptView.Y - m_prevPt.Y  'around horizontal

    distX *= -Math.PI / m_D
    distY *= Math.PI / m_D

    'perform camera orbiting
    OdExGsDeviceHelpers.Orbit(m_TargetView, distY, distX, m_viewCenter)

    'store previous click point
    m_prevPt = ptView
  End Sub

  Public Sub OnFinishRotationHandler()
    m_started = False
  End Sub

End Class

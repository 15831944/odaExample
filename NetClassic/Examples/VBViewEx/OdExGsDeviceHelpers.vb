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
Imports Microsoft.VisualBasic
Imports System
Imports System.Collections
Imports System.Collections.Generic
Imports System.Data
Imports System.Drawing
Imports System.Diagnostics
Imports System.Windows.Forms
Imports Teigha
Imports Teigha.DatabaseServices
Imports Teigha.Export_Import
Imports Teigha.Geometry
Imports Teigha.GraphicsInterface
Imports Teigha.GraphicsSystem

Public Class OdExGsDeviceHelpers
  Public Shared Function GetWorldCoordinateByScreen(view As GraphicsSystem.View, screenPoint As Point2d) As Point3d
    'directions, origin, etc
    Dim target As Point3d = view.Target
    Dim direction As Vector3d = target - view.Position
    Dim yVector As Vector3d = view.UpVector
    Dim xVector As Vector3d = direction.CrossProduct(yVector).GetNormal()

    Dim center, stepX, stepY As Point3d
    center = New Point3d(target.X, target.Y, target.Z)
    stepX = target + xVector
    stepY = target + yVector

    Dim matrix As Matrix3d = view.WorldToDeviceMatrix()
    stepX = stepX.TransformBy(matrix)
    stepY = stepY.TransformBy(matrix)
    center = center.TransformBy(matrix)

    'make the calculation
    Dim result As Point3d
    Dim x, y As Double
    x = (screenPoint.X - center.X) / (stepX.X - center.X)
    y = (screenPoint.Y - center.Y) / (stepY.Y - center.Y)

    result = target + (xVector * x) + (yVector * y)

    Return result
  End Function

  Public Shared Sub GetViewDcCorners(pView As GraphicsSystem.View, ByRef lower_left As Point2d, ByRef upper_right As Point2d)
    Dim targetPt As Point3d = pView.ViewingMatrix() * pView.Target()
    Dim halfFieldWidth As Double = pView.FieldWidth() / 2.0
    Dim halfFieldHeight As Double = pView.FieldHeight() / 2.0
    lower_left = New Point2d(targetPt.X - halfFieldWidth, targetPt.Y - halfFieldHeight)
    upper_right = New Point2d(targetPt.X + halfFieldWidth, targetPt.Y + halfFieldHeight)
  End Sub

  Public Shared Sub Orbit(pView As GraphicsSystem.View, xOrbit As Double, yOrbit As Double, pt As Point3d)
    Dim delta As Vector3d = New Vector3d()

    'Dim v As Point3d = pView.Target()
    'Dim target As Vector3d = v.GetAsVector()
    'delta = pt.GetAsVector() - target
    'delta.TransformBy(pView.ViewingMatrix())

    'the rotation should be performed around the 'pt'.
    'That's why at first we should move the camera with purpose make target equal to the 'pt.
    'Then we should perform the rotation And finally we should to move the camera in opposite direction
    pView.Dolly(delta)
    pView.Orbit(xOrbit, yOrbit)
    pView.Dolly(-delta)
  End Sub
End Class

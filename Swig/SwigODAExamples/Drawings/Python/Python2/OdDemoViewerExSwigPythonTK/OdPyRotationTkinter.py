#######################################################################################
# Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
# All rights reserved. 
# 
# This software and its documentation and related materials are owned by 
# the Alliance. The software may only be incorporated into application 
# programs owned by members of the Alliance, subject to a signed 
# Membership Agreement and Supplemental Software License Agreement with the
# Alliance. The structure and organization of this software are the valuable  
# trade secrets of the Alliance and its suppliers. The software is also 
# protected by copyright law and international treaty provisions. Application  
# programs incorporating this software must include the following statement 
# with their copyright notices:
#   
#   This application incorporates Open Design Alliance software pursuant to a license 
#   agreement with Open Design Alliance.
#   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
#   All rights reserved.
#
# By use of this software, its documentation or related materials, you 
# acknowledge and accept the above terms.
#######################################################################################

from ODA_Kernel import *
from ODA_Drawings import *
from OdPyGraphicsHelpers import *

class OdPyRotationTkinter(OdPyHelpers.OnSuccessEvent):
    gsView = None
    targetFrame = None

    def __init__(self,targetFrame, layoutHelper):
        OdPyHelpers.OnSuccessEvent.__init__(self)
        self.gsView = layoutHelper.activeView()
        self.targetFrame = targetFrame
        pass

    def __del__(self):
        self.gsView = None

    StartRotationHandlerBindId = None
    MoveRotationHandlerBindId = None
    EndRotationHandlerBindId = None

    def InitEvents(self):
        self.StartRotationHandlerBindId = self.targetFrame.bind("<Button-1>",self.OnStartRotationHandler)
        self.MoveRotationHandlerBindId = self.targetFrame.bind("<B1-Motion>",self.OnMoveRotationHandler)
        self.EndRotationHandlerBindId = self.targetFrame.bind("<ButtonRelease-1>",self.OnEndRotationHandler)
        pass

    def UnInitEvents(self):
        if(self.StartRotationHandlerBindId != None):
            self.targetFrame.unbind("<Button-1>",self.StartRotationHandlerBindId)
        if(self.MoveRotationHandlerBindId != None):
            self.targetFrame.unbind("<B1-Motion>",self.MoveRotationHandlerBindId)
        if(self.EndRotationHandlerBindId != None):
            self.targetFrame.unbind("<ButtonRelease-1>",self.EndRotationHandlerBindId)
        self.StartRotationHandlerBindId = self.MoveRotationHandlerBindId = self.EndRotationHandlerBindId = None
        pass

    def OnStartRotationHandler(self,event):
        # calculate click point in WCS
        pt = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.gsView, OdGePoint2d(event.x, event.y))

        # transfer point to the eye coordinate system
        self.m_prevPt = Mul_GeMatrix3d_GePoint3d(self.gsView.viewingMatrix(), pt)

        # calculate mouse move to rotation angle conversion coefficient in base of viewport dc size
        pt1,pt2 = OdPyRotationTkinter.GetViewDcCorners(self.gsView)
        pt2.x -= pt1.x
        pt2.y -= pt1.y
        r = min(pt2.x, pt2.y)
        self.m_D = r

        extents = OdGeBoundBlock3d()
        self.gsView.viewExtents(extents)
        self.m_viewCenter = extents.center()
        self.m_viewCenter.transformBy(self.gsView.eyeToWorldMatrix())
        pass

    def OnMoveRotationHandler(self,event):
        # calculate click point in WCS
        ptScreen = OdGePoint2d(event.x, event.y)
        pt = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.gsView, ptScreen)

        # transfer point to the eye coordinate system
        ptView = Mul_GeMatrix3d_GePoint3d(self.gsView.viewingMatrix(), pt);
  
        # calculate the angles for the rotation about appropriate axes
        distX = ptView.x - self.m_prevPt.x; # around vertical
        distY = ptView.y - self.m_prevPt.y; # around horizontal

        distX *= -OdaPI / self.m_D;
        distY *= OdaPI / self.m_D;
  
        # perform camera orbiting
        OdPyRotationTkinter.Orbit(self.gsView, distY, distX, self.m_viewCenter);

        # store previous click point
        self.m_prevPt = ptView;

        self.OnSuccess()
        pass

    @staticmethod
    def GetViewDcCorners(pView):
        targetPt = Mul_GeMatrix3d_GePoint3d(pView.viewingMatrix() , pView.target())
        halfFieldWidth = pView.fieldWidth() / 2.0;
        halfFieldHeight = pView.fieldHeight() / 2.0;
        lower_left = OdGePoint2d()
        upper_right = OdGePoint2d()
        lower_left.x = targetPt.x - halfFieldWidth;
        lower_left.y = targetPt.y - halfFieldHeight;
        upper_right.x = targetPt.x + halfFieldWidth;
        upper_right.y = targetPt.y + halfFieldHeight;
        return lower_left, upper_right

    @staticmethod
    def Orbit(pView,xOrbit,yOrbit,pt):
        delta = OdGeVector3d()

        if (pt):
          v = pView.target()
          target = v.asVector()
          delta = pt.asVector() - target
          delta.transformBy(pView.viewingMatrix())

        # the rotation should be performed around the 'pt'.
        # That's why at first we should move the camera with purpose make target equal to the 'pt.
        # Then we should perform the rotation and finally we should to move the camera in opposite direction
        pView.dolly(delta);
        pView.orbit(xOrbit, yOrbit);
        pView.dolly(-delta);
        pass

    def OnEndRotationHandler(self,event):
        pass

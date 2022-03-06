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

class OdPyPanTkinter(OdPyHelpers.OnSuccessEvent):
    gsView = None
    targetFrame = None

    def __init__(self,targetFrame, layoutHelper):
        OdPyHelpers.OnSuccessEvent.__init__(self)
        self.gsView = layoutHelper.activeView()
        self.targetFrame = targetFrame
        pass

    def __del__(self):
        self.gsView = None

    StartPanHandlerBindId = None
    MovePanHandlerBindId = None
    EndPanHandlerBindId = None

    def InitEvents(self):
        self.StartPanHandlerBindId = self.targetFrame.bind("<Button-1>",self.OnStartPanHandler)
        self.MovePanHandlerBindId = self.targetFrame.bind("<B1-Motion>",self.OnMovePanHandler)
        self.EndPanHandlerBindId = self.targetFrame.bind("<ButtonRelease-1>",self.OnEndPanHandler)
        pass

    def UnInitEvents(self):
        if(self.StartPanHandlerBindId != None):
            self.targetFrame.unbind("<Button-1>",self.StartPanHandlerBindId)
        if(self.MovePanHandlerBindId != None):
            self.targetFrame.unbind("<B1-Motion>",self.MovePanHandlerBindId)
        if(self.EndPanHandlerBindId != None):
            self.targetFrame.unbind("<ButtonRelease-1>",self.EndPanHandlerBindId)
        self.StartPanHandlerBindId = self.MovePanHandlerBindId = self.EndPanHandlerBindId = None
        pass

    def OnStartPanHandler(self,event):
        #remember camera current position
        self.m_pos = self.gsView.position()

        #remember the difference between click point in WCS and camera current position
        self.m_prevPt = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.gsView, OdGePoint2d(event.x, event.y)) - self.m_pos.asVector()
        pass

    def OnMovePanHandler(self,event):
        # calculate click point in WCS
        ptScreen = OdGePoint2d(event.x, event.y)
        pt = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.gsView,ptScreen)
        
        #obtain delta for dolly
        v = self.m_prevPt - (pt - self.m_pos)
        delta = v.asVector()
           
        # transform delta to eye
        delta = delta.transformBy(self.gsView.viewingMatrix())
        
        # perform camera moving
        self.gsView.dolly(delta.x, delta.y, delta.z);
        
        # remember the difference between click point in WCS and camera previous position
        self.m_prevPt = pt - self.m_pos.asVector(); 
        
        # remember camera current position
        self.m_pos = self.gsView.position();

        self.OnSuccess()
        pass

    def OnEndPanHandler(self,event):
        pass
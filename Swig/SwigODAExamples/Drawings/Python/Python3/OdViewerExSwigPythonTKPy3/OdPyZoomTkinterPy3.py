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

from ODA_Kernel_Py3 import *
from ODA_Drawings_Py3 import *
from OdPyGraphicsHelpersPy3 import *

class OdPyZoomTkinter(OdPyHelpers.OnSuccessEvent):
    def __init__(self,targetFrame,layoutHelper):
        OdPyHelpers.OnSuccessEvent.__init__(self)
        self.LayoutHelper = layoutHelper
        self.targetFrame = targetFrame
        pass

    ZoomHandlerBindId = None

    def InitEvents(self):
        self.ZoomHandlerBindId = self.targetFrame.bind_all("<MouseWheel>", self.__OnMouseWhellHandler__)
        pass

    def UnInitEvents(self):
        if(self.ZoomHandlerBindId != None):
            self.targetFrame.unbind("<MouseWheel>",self.ZoomHandlerBindId)
        pass

    def OnZoomIn(self):
        self.__OnCenterZoom__(isZoomIn=True)

    def OnZoomOut(self):
        self.__OnCenterZoom__(isZoomIn=False)

    def OnZoomToExtents(self):
        #Do ZoomToExtents
        result_state, pView = OdDbDatabase_cast(self.LayoutHelper.userGiContext().database()).activeViewportId().openObject()
        #pView = self.pGsView
        pViewPE = OdDbAbstractViewportData_cast(pView)
        pViewPE.zoomExtents(pView)
        self.OnSuccess()
        pass

    ZoomStepOnClick = 1

    def __OnCenterZoom__(self,isZoomIn):
        xCenter = self.targetFrame.winfo_x() + self.targetFrame.winfo_width()/2
        yCenter = self.targetFrame.winfo_y() + self.targetFrame.winfo_height()/2
        v_zoom_state = 1 if isZoomIn else -1
        self.__OnZoom__(xCenter,yCenter,v_zoom_state*self.ZoomStepOnClick*120)

    def __OnMouseWhellHandler__(self,event):
        if(self.LayoutHelper == None):
            return
        xMouseLoc = event.x
        yMouseLoc = event.y
        wheelDelta = event.delta
        self.__OnZoom__(xMouseLoc,yMouseLoc,wheelDelta)
        pass

    def __OnZoom__(self,xMouseLoc,yMouseLoc,wheelDelta):
        correctScreenPoint = OdGePoint2d(xMouseLoc, yMouseLoc);
        worldPoint = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.LayoutHelper.activeView(), correctScreenPoint);

        self.__OnZoomActiveView__(wheelDelta / 120);

        self.__OnMoveToCenterZoom__(correctScreenPoint,worldPoint)
        
        self.OnSuccess()
        pass

    def __OnZoomActiveView__(self,steps):
        if(self.LayoutHelper == None):
            return
        OdPyGraphicsHelpers.ZoomActiveView(self.LayoutHelper, steps)
        pass

    def __OnMoveToCenterZoom__(self,correctScreenPoint,worldPoint):
        view = self.LayoutHelper.activeView();
        
        #Get new screen point of the same world point
        worldToDevice = view.worldToDeviceMatrix();
        newScreenPoint = Mul_GeMatrix3d_GePoint3d(worldToDevice, worldPoint);
        
        #Get world points on the focal plane
        movingPoint = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.LayoutHelper.activeView(), OdGePoint2d(newScreenPoint.x, newScreenPoint.y))
        destinationPoint = OdPyGraphicsHelpers.GetWorldCoordinateByScreen(self.LayoutHelper.activeView(), correctScreenPoint)
        
        position = view.position()
        target = view.target()
        upVector = view.upVector()
        width = view.fieldWidth()
        height = view.fieldHeight()
        isPerspective = view.isPerspective()
        
        #Shift the camera so points coincide
        offset = destinationPoint - movingPoint;
        position -= offset;
        target -= offset;
        
        projectionType = None
        if isPerspective:
           projectionType = OdGsView.kPerspective 
        else:
           projectionType = OdGsView.kParallel
        
        view.setView(position, target, upVector, width, height, projectionType)
        pass

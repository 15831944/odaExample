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

from ODA_PyMemManager_Py3 import *
from ODA_Kernel_Py3 import *
from ODA_Drawings_Py3 import *
from tkinter import *
from OdPyGraphicsHelpersPy3 import *
from OdPyPanTkinterPy3 import *
from OdPyZoomTkinterPy3 import *
from OdPyRotationTkinterPy3 import *
import PIL

class OdLogoCanvasTkinter(Canvas):
    def __init__(self,master=None, cnf={}, **kw):
        Canvas.__init__(self,master,cnf,**kw)
        self.InitLogo()
        pass

    def InitLogo(self):
        relPath_toExampleResources = OdPyHelpers.GetDrawingAppResourcesPath(r'OdViewerExSwigPythonTKPy3\OdViewerExSwigPythonTKPy3_Resources');
        appResPathFolder = OdPyHelpers.GetDrawingAppResourcesPath(relPath_toExampleResources)
        oda_logo_path = OdPyHelpers.PathCombine(appResPathFolder,r'OdaBackground.png')
        python_logo_path = OdPyHelpers.PathCombine(appResPathFolder,r'pythonLogo.png')
        self.OriginalImage_oda_logo = PIL.Image.open(oda_logo_path).resize((600, 120), PIL.Image.ANTIALIAS)
        self.OriginalImage_python_logo = PIL.Image.open(python_logo_path).resize((427, 126), PIL.Image.ANTIALIAS)
        self.currentImage_oda_logo = PIL.ImageTk.PhotoImage(self.OriginalImage_oda_logo)
        self.currentImage_python_logo = PIL.ImageTk.PhotoImage(self.OriginalImage_python_logo)
        self.canvas_img_oda_logo = None
        self.canvas_img_python_logo = None
        self.prevW = 0
        self.prevH = 0
        self.LogoInitialized = True
        pass

    def Clear(self):
        self.delete("all")
        self.LogoInitialized = False

    def UpdateLogo(self):
        if(not self.LogoInitialized):
            self.InitLogo()
        currW = self.winfo_width()
        currH = self.winfo_height()

        if(self.canvas_img_oda_logo == None):
            xPosCenter = currW / 2 - 20 
            yPosCenter = currH / 2 - 20
            self.canvas_img_oda_logo = self.create_image(xPosCenter,yPosCenter - 100,image=self.currentImage_oda_logo)
            self.canvas_img_python_logo = self.create_image(xPosCenter,yPosCenter + 30,image=self.currentImage_python_logo)
        else:
            xOffset = (currW - self.prevW) / 2;
            yOffset = (currH - self.prevH) / 2;
            xOffset = 1 if xOffset == 0 and currW != self.prevW else xOffset
            yOffset = 1 if yOffset == 0 and currH != self.prevH else yOffset
            self.move(self.canvas_img_oda_logo,xOffset,yOffset)
            self.move(self.canvas_img_python_logo,xOffset,yOffset)

        self.prevW = self.winfo_width()
        self.prevH = self.winfo_height()
        pass

class OdVectorizeFrameTKinter_Py3(OdLogoCanvasTkinter):
    #Root Memory Transaction
    VectorizeRootTransaction = None;

    #Layout helper
    LayoutHelper = None;

    #Dwg Database
    Database = None;

    def __init__(self,master=None, cnf={}, **kw):
        OdLogoCanvasTkinter.__init__(self,master,cnf,**kw)
        #Init events
        self.InitEvents()
        self.InitLogo()
        pass

    def InitAddititionalFunctional(self):
        self.ZoomFunctional = OdPyZoomTkinter(self,self.LayoutHelper)
        self.ZoomFunctional.InitEvents()
        self.ZoomFunctional.OnSuccess_Bind(self.OnRegenerateView)

        self.PanFunctional = OdPyPanTkinter(self,self.LayoutHelper)
        self.PanFunctional.OnSuccess_Bind(self.OnRegenerateView)

        self.RotationFunctional = OdPyRotationTkinter(self,self.LayoutHelper)
        self.RotationFunctional.OnSuccess_Bind(self.OnRegenerateView)
        pass

    def UnInitAddititionalFunctional(self):
        if(self.PanFunctional != None):
            self.PanFunctional.OnSuccess_Unbind(self.OnRegenerateView)
            self.PanFunctional.UnInitEvents()

        if(self.ZoomFunctional != None):
            self.ZoomFunctional.OnSuccess_Unbind(self.OnRegenerateView)
            self.ZoomFunctional.UnInitEvents()

        if(self.RotationFunctional != None):
            self.RotationFunctional.OnSuccess_Unbind(self.OnRegenerateView)
            self.RotationFunctional.UnInitEvents()

        pass

    OdaViewInitialized = False

    def InitVectorizeComponent(self,pDatabase):
        self.Database = pDatabase

        #Start Root Memory Transaction
        self.VectorizeRootTransaction = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()

        #Get Component HWND
        hwnd = self.winfo_id()

        #Create OdGsDevice
        pDevice = OdPyGraphicsHelpers.CreateGsDevice(hwnd)

        #Create Gi Context for OdDbDatabse
        ctx = OdPyGraphicsHelpers.CreateContextForDbDatabase(pDatabase)

        #Create Layout Helper
        self.LayoutHelper = OdPyGraphicsHelpers.CreateLayoutHelper(pDevice,ctx)

        #Init actual frame size to OdGsDevice
        self.UpdateViewSize()

        #Init ZoomToExtents, Pan & etc
        self.InitAddititionalFunctional()

        self.OdaViewInitialized = True

        self.OnRegenerateView();

        #Do zoom to extents by default on start
        self.OnZoomToExtents()

        pass

    def UnInitVectorizeComponent(self):
        if(not self.OdaViewInitialized):
            return

        #Uninit ZoomToExtents, Pan & etc
        self.UnInitAddititionalFunctional()

        #Stop Root Memory Transaction
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(self.VectorizeRootTransaction)

        self.OdaViewInitialized = False
        pass


    def InitEvents(self):
        self.bind("<Configure>",self.OnUpdateViewHandler)

    # Set actual frame size to OdGsDevice
    def UpdateViewSize(self):
        xMin = self.winfo_x()
        xMax = self.winfo_x() + self.winfo_width()
        yMin = self.winfo_y() - 34
        yMax = self.winfo_y() + self.winfo_height() - 34
        self.LayoutHelper.onSize(OdGsDCRect(xMin, xMax, yMax, yMin))

    def OnUpdateViewHandler(self,event):
       if(self.OdaViewInitialized):
         #Clear logo if created ODA view
         OdLogoCanvasTkinter.Clear(self)
         #Update deafult ui components
         OdLogoCanvasTkinter.update(self)
         #Update actual frame size to OdGsDevice
         self.UpdateViewSize()
         #Update OdGsView
         self.LayoutHelper.update()
       else:
           #Update Welcome Logo
           self.UpdateLogo()
       pass

    def OnRegenerateView(self):
        #Do Regenerate view
        self.OnUpdateViewHandler(None)

    def OnZoomToExtents(self):
        #Do ZoomToExtents
        if(self.ZoomFunctional == None):
            return
        self.ZoomFunctional.OnZoomToExtents()
        pass

    def OnZoomIn(self):
        #Do ZoomIn
        if(self.ZoomFunctional == None):
            return
        self.ZoomFunctional.OnZoomIn()
        pass

    def OnZoomOut(self):
        #Do ZoomIn
        if(self.ZoomFunctional == None):
            return
        self.ZoomFunctional.OnZoomOut()
        pass

    def OnPan(self,enable):
        #Do Pan
        if(self.PanFunctional == None):
            return
        if(enable):
            self.PanFunctional.InitEvents()
        else:
            self.PanFunctional.UnInitEvents()
        pass

    def OnRotation(self,enable):
        #Do Rotation
        if(self.RotationFunctional == None):
            return
        if(enable):
            self.RotationFunctional.InitEvents()
        else:
            self.RotationFunctional.UnInitEvents()
        pass

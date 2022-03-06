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

from ODA_PyMemManager import *
from ODA_Kernel import *
from ODA_Drawings import *
from OdDemoViewerExSwigPythonTK_ExAppServices import *
from OdVectorizeFrameTKinter import *
from OdToolBarTkinter import *

from tkFileDialog import *

import Tkinter
from Tkinter import *

class OdDemoViewerExSwigPythonTK_MainFormViewer(Tk):
    #Root Memory Transaction
    AppRootTransaction = None
    #Root Database Transaction
    DatabaseTransaction = None
    #ODA System Services
    systemServices = None
    #Host Application Services
    hostApp = None
    #Current Opened Database
    pDatabase = None
    #Vectorize component
    vectorizeComponent = None

    #Layout helper
    layoutHelper = None

    def __init__(self):
        Tk.__init__(self)
        self.Inititialize_ODA()
        self.InitMainForm()
        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def on_closing(self):
        self.Dispose()
        self.destroy()

    #Uninit ODA SDK
    def Dispose(self):
        self.DisposeVectorizeComponent()
        self.DisposeActiveDatabaseTransaction()
        self.Uninitialize_ODA()

    def Inititialize_ODA(self):
        #Start Root Memory Transaction
        self.AppRootTransaction = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        #Create ODA System Services
        self.systemServices = SystemServices()
        #Initialize ODA SDK
        odInitialize(self.systemServices)

        #Create Host Application Services
        self.hostApp = UserApplicationServices()

    def Uninitialize_ODA(self):
        #Stop Root Memory Transaction
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(self.AppRootTransaction)
        
        #Unintialize ODA SDK
        odUninitialize()

    #Uninitialize Vectorize Component
    def DisposeVectorizeComponent(self):
        if(self.vectorizeComponent == None):
           return
        self.vectorizeComponent.UnInitVectorizeComponent()
        self.vectorizeComponent = None
        pass

    #Stop Database Memory Transaction
    def DisposeActiveDatabaseTransaction(self):
        if(self.DatabaseTransaction != None):
           ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(self.DatabaseTransaction)

    #Initialize form components
    def InitMainForm(self):
        self.title("ODA Demo Python Viewer")
        self.geometry('800x600')
        self.InitAppIcon()
        self.InitToolBar()
        self.InitVectorizeComponent()
        pass

    def InitPythonLogo(self):
        self.vectorizeComponent.UpdateLogo(True)
        pass

    def InitToolBar(self):
        self.Toolbar = OdToolBarTkinter(self,bd=1, relief=RIDGE)
        self.Toolbar.pack(side=TOP, fill=BOTH)
        self.Toolbar.BindEvent( self.Toolbar.ButtonPan,self.PanClick)
        self.Toolbar.BindEvent( self.Toolbar.ButtonOrbit,self.OrbitClick)
        self.Toolbar.BindEvent( self.Toolbar.ButtonZoomOut,self.ZoomOutClick)
        self.Toolbar.BindEvent( self.Toolbar.ButtonZoomToExtents,self.ZoomToExtentsClick)
        self.Toolbar.BindEvent( self.Toolbar.ButtonZoomIn,self.ZoomInClick)
        self.Toolbar.BindEvent( self.Toolbar.ButtonOpen,self.FileOpenClick)
        self.Toolbar.SetEnable(False)
        pass

    def InitVectorizeComponent(self):
        self.vectorizeComponent = OdVectorizeFrameTKinter(self, bg="gray")
        self.vectorizeComponent.pack(expand=1,side=TOP,fill=BOTH)
        self.vectorizeComponent.correction_y = self.Toolbar.winfo_height()
        pass

    def InitAppIcon(self):
        relPath_toExampleResources = OdPyHelpers.GetDrawingAppResourcesPath(r'OdDemoViewerExSwigPythonTK\OdDemoViewerExSwigPythonTK_Resources');
        appResPathFolder = OdPyHelpers.GetDrawingAppResourcesPath(relPath_toExampleResources)
        logo_path = OdPyHelpers.PathCombine(appResPathFolder,r'odalogo.png')
        img = PIL.Image.open(logo_path)
        self.call('wm', 'iconphoto', self._w, PIL.ImageTk.PhotoImage(file=logo_path))

    #Handler File Open
    def FileOpenClick(self):
        dwgFilePath = askopenfilename()
        if(dwgFilePath):
            #Before open & vectorize new file, need uninitialize previous vectorize data
            if( self.vectorizeComponent != None):
                self.vectorizeComponent.UnInitVectorizeComponent()
            
            #Before open & vectorize new file, need uninitialize previous opened database
            if(self.DatabaseTransaction == None):
                self.DatabaseTransaction = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
            else:
                ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(self.DatabaseTransaction)
                self.DatabaseTransaction = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
            
            #Open database
            self.pDatabase = self.hostApp.readFile(dwgFilePath,True,False,ODA_Kernel.kShareDenyNo,"")

            #Open initialize vectorizer
            self.vectorizeComponent.InitVectorizeComponent(self.pDatabase)

            #Enable toolbar
            self.Toolbar.SetEnable(True)
            #Reset checked button
            self.Toolbar.ButtonOrbit.SetChecked(False)
            self.Toolbar.ButtonPan.SetChecked(False)

    #Handler ZoomToExtents
    def ZoomToExtentsClick(self):
        if(self.vectorizeComponent != None):
            self.vectorizeComponent.OnZoomToExtents()

    #Handler ZoomIn
    def ZoomInClick(self):
        if(self.vectorizeComponent != None):
            self.vectorizeComponent.OnZoomIn()

    #Handler ZoomOut
    def ZoomOutClick(self):
        if(self.vectorizeComponent != None):
            self.vectorizeComponent.OnZoomOut()

    #Handler Pan
    def PanClick(self,state):
        if(state):
            self.Toolbar.ButtonOrbit.SetChecked(not state)
        if(self.vectorizeComponent != None):
            self.vectorizeComponent.OnPan(state)

    #Handler Rotation
    def OrbitClick(self,state):
        if(state):
            self.Toolbar.ButtonPan.SetChecked(not state)
        if(self.vectorizeComponent != None):
            self.vectorizeComponent.OnRotation(state)

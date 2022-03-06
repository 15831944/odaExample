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

import Tkinter
import PIL
from ttk import Separator
from PIL import ImageTk
from OdPyHelpers import *
from OdPyTkinterGuiHelpers import *

class OdToolBarTkinter(Frame):
    def __init__(self, master=None, cnf={}, **kw):
        Frame.__init__(self,master,cnf,**kw)
        self.Init()

    def Init(self):
        relPath_toExampleResources = OdPyHelpers.GetDrawingAppResourcesPath(r'OdDemoViewerExSwigPythonTK\OdDemoViewerExSwigPythonTK_Resources');
        appResPathFolder = OdPyHelpers.GetDrawingAppResourcesPath(relPath_toExampleResources)
        img_orbit = OdPyHelpers.PathCombine(appResPathFolder,r'Cursors\orbit.png')
        img_pan =  OdPyHelpers.PathCombine(appResPathFolder,r'Cursors\pan.png')
        img_zoomMinus = OdPyHelpers.PathCombine(appResPathFolder,r'Zoom\ZoomMinus.png')
        img_zoomToExtents =  OdPyHelpers.PathCombine(appResPathFolder,r'Zoom\ZoomToExtents.png')
        img_zoomPlus =  OdPyHelpers.PathCombine(appResPathFolder,r'Zoom\ZoomPlus.png')
        img_open =  OdPyHelpers.PathCombine(appResPathFolder,r'Menu\open.png')

        self.ButtonOpen = OdToolBarTkinter.CreateAndFillToolButton(self,False,img_open)
        OdToolBarTkinter.CreateToolBarSeparator(self)
        self.ButtonPan = OdToolBarTkinter.CreateAndFillToolButton(self,True,img_pan)
        self.ButtonOrbit = OdToolBarTkinter.CreateAndFillToolButton(self,True,img_orbit)
        OdToolBarTkinter.CreateToolBarSeparator(self)
        self.ButtonZoomOut = OdToolBarTkinter.CreateAndFillToolButton(self,False,img_zoomMinus)
        self.ButtonZoomToExtents = OdToolBarTkinter.CreateAndFillToolButton(self,False,img_zoomToExtents)
        self.ButtonZoomIn = OdToolBarTkinter.CreateAndFillToolButton(self,False,img_zoomPlus)
        OdToolBarTkinter.CreateToolBarSeparator(self)
        pass

    def SetEnable(self,state):
        self.EnableState = state
        self.__UpdateEnableButtons__()
        pass

    def __UpdateEnableButtons__(self):
        if not self.EnableState: 
            btn_st = DISABLED
        else:
            btn_st = NORMAL
        self.ButtonPan.configure(state=btn_st)
        self.ButtonOrbit.configure(state=btn_st)
        self.ButtonZoomOut.configure(state=btn_st)
        self.ButtonZoomToExtents.configure(state=btn_st)
        self.ButtonZoomIn.configure(state=btn_st)
        pass

    def BindEvent(self,targetObj,methodObj):
        if(isinstance(targetObj, OdPyTkinterGuiHelpers.OdPyCheckButton)):
            targetObj.OnButtonCheckedChanged_Bind(methodObj)
        elif(isinstance(targetObj, OdPyTkinterGuiHelpers.OdPyButton)):
            targetObj.OnButtonClick_Bind(methodObj)
        pass

    def UnbindEvent(self,targetObj,methodObj):
        if(isinstance(targetObj, OdPyTkinterGuiHelpers.OdPyCheckButton)):
            targetObj.OnButtonCheckedChanged_Unbind(methodObj)
        elif(isinstance(targetObj, OdPyTkinterGuiHelpers.OdPyButton)):
            targetObj.OnButtonClick_Unbind(methodObj)
        pass

    @staticmethod
    def CreateToolBarSeparator(toolbar):
        separator = Separator(toolbar, orient = Tkinter.VERTICAL)
        separator.pack(side=LEFT, fill='y', padx=1)
        pass

    @staticmethod
    def CreateAndFillToolButton(target_toolbar,checkedButton,img_abs_path):
        img = OdToolBarTkinter.OpenAndPrepareImage(img_abs_path)
        button = OdToolBarTkinter.CreateToolButton(target_toolbar,img,checkedButton)
        return button

    @staticmethod
    def OpenAndPrepareImage(img_path):
        pil_img = PIL.Image.open(img_path)
        pil_img = pil_img.resize((32, 32),  PIL.Image.ANTIALIAS)
        img = PIL.ImageTk.PhotoImage(pil_img)
        return img

    @staticmethod
    def CreateToolButton(targetToolbar,img,isCheckButton):
        if(not isCheckButton):
            button = OdPyTkinterGuiHelpers.OdPyButton(targetToolbar, image = img ,relief=FLAT, compound=LEFT)
        else:
            button = OdPyTkinterGuiHelpers.OdPyCheckButton(targetToolbar, image = img, relief=GROOVE ,compound=LEFT ,indicatoron=0, onvalue=1, offvalue=0)
        button.image = img
        button.pack(side=LEFT, padx=2)
        return button

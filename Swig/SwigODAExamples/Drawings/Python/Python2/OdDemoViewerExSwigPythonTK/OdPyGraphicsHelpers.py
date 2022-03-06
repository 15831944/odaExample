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
from OdPyHelpers import *
from OdPyTkinterGuiHelpers import *

class OdPyGraphicsHelpers():
    @staticmethod
    def GetWorldCoordinateByScreen(view,screenPoint):
        #directions, origin, etc
        target = view.target()
        direction = target - view.position()
        yVector = view.upVector()
        xVector = direction.crossProduct(yVector).normal()

        center = OdGePoint3d(target.x,target.y,target.z)
        stepX = target + xVector
        stepY = target + yVector

        matrix = view.worldToDeviceMatrix()
        stepX.transformBy(matrix)
        stepY.transformBy(matrix)
        center.transformBy(matrix)

        #make the calculation
        x = (screenPoint.x - center.x) / (stepX.x - center.x)
        y = (screenPoint.y - center.y) / (stepY.y - center.y)
        result = target + xVector * x + yVector * y
        return result

    @staticmethod
    def renderModeToVisualStyle(renderMode):
      if(renderMode == OdGsView.kWireframe):
          return "Wireframe"
      if(renderMode == OdGsView.kHiddenLine):
          return "Hidden"
      if(renderMode == OdGsView.kFlatShaded):
          return "Shaded"
      if(renderMode == OdGsView.kGouraudShaded):
          return "kszVSShaded"
      if(renderMode == OdGsView.kFlatShadedWithWireframe):
          return "kszVSShadedWithEdges"
      if(renderMode == OdGsView.kGouraudShadedWithWireframe):
          return "kszVSShadedWithEdges"
      return "2dWireframe"

    @staticmethod
    def CreateLayoutHelper(pGsDevice, pGiCtx):
        layoutHelper = setupActiveLayoutViews(pGsDevice,pGiCtx)
        lightPallet = odcmAcadDarkPalette();
        layoutHelper.setLogicalPalette(lightPallet,256)
        #layoutHelper.setBackgroundColor(OdPyGraphicsHelpers.getIfromRGB(168, 168, 168))
        #SetViewportBorderProperties(hDevice, !bModelSpace, CurPalette[7]);
        view = layoutHelper.activeView()

        rm = OdGsView.kFlatShaded
        #Set render mode
        view.setMode(rm)
        db = pGiCtx.getDatabase()
        if (pGsDevice.properties().has("UseVisualStyles")):
          result_state, dic = db.getVisualStyleDictionaryId().openObject()
          view.setVisualStyle(dic.getAt(OdPyGraphicsHelpers.renderModeToVisualStyle(rm)).AsOdDbStubPointer());
          pass
        return layoutHelper

    @staticmethod
    def ZoomActiveView(hDevice,steps):
        view = hDevice.activeView()

        if (view.isPerspective()):
            position = view.position()
            target = view.target()
            direction = target - position
            upVector = view.upVector()
            width = view.fieldWidth()
            height = view.fieldHeight()

            #calculate an appropriate offset using real size of the frame
            if (width < height):
              steps *= width / 2.0;
            else:
              steps *= height / 2.0;

            direction *= steps;

            position += direction;
            target += direction;

            view.setView(position, target, upVector, width, height, OdGsView.Projection.kPerspective);
        else:
          view.zoom(pow(1.11, steps));
        pass

    @staticmethod
    def CreateContextForDbDatabase(database):
        ctx = OdGiContextForDbDatabase_createObject()
        ctx.enableGsModel(True);
        ctx.setDatabase(database);
        return ctx

    @staticmethod
    def getIfromRGB(red,green,blue):
        RGBint = (red<<16) + (green<<8) + blue
        return RGBint

    @staticmethod
    def CreateGsDevice(hwnd):
        #Load the vectorization module
        pGs = odrxDynamicLinker().loadModule("WinGLES2.txv", False)
        pDevice = pGs.createDevice()
        Properties = pDevice.properties()
        if(Properties):
            if (Properties.has("WindowHWND")): # Check if property is supported
                v_hwnd = PyOdRxVariantValue()
                v_hwnd.setIntPtr(hwnd)
                Properties.putAt("WindowHWND", v_hwnd)
            if (Properties.has("DoubleBufferEnabled")): # Check if property is supported
                v_DoubleBufferEnabled = PyOdRxVariantValue()
                v_DoubleBufferEnabled.setBool(True)
                Properties.putAt("DoubleBufferEnabled", v_DoubleBufferEnabled)
            if (Properties.has("EnableSoftwareHLR")): # Check if property is supported
                v_EnableSoftwareHLR = PyOdRxVariantValue()
                v_EnableSoftwareHLR.setBool(True)
                Properties.putAt("EnableSoftwareHLR", v_EnableSoftwareHLR)
            if (Properties.has("DiscardBackFaces")): # Check if property is supported
                v_DiscardBackFaces = PyOdRxVariantValue()
                v_DiscardBackFaces.setBool(True)
                Properties.putAt("DiscardBackFaces", v_DiscardBackFaces)
            #// Enable scene graph usage onto renderer side
            if (Properties.has("UseSceneGraph")): # Check if property is supported
                v_UseSceneGraph = PyOdRxVariantValue()
                v_UseSceneGraph.setBool(True)
                Properties.putAt("UseSceneGraph", v_UseSceneGraph)
            if (Properties.has("UseVisualStyles")): # Check if property is supported
                v_UseVisualStyles = PyOdRxVariantValue()
                v_UseVisualStyles.setBool(True)
                Properties.putAt("UseVisualStyles", v_UseVisualStyles)
                
        return pDevice

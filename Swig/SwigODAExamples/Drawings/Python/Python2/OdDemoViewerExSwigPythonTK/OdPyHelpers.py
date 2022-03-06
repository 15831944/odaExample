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

import os

class OdPyHelpers:
    class Event(object): 
        def __init__(self): 
            self.__eventhandlers = [] 
  
        def __iadd__(self, handler): 
            self.__eventhandlers.append(handler) 
            return self
  
        def __isub__(self, handler): 
            self.__eventhandlers.remove(handler) 
            return self
  
        def __call__(self, *args, **keywargs): 
            for eventhandler in self.__eventhandlers: 
                eventhandler(*args, **keywargs)

    class OnSuccessEvent:
        #Begin OnSuccess Event
        def __init__(self):
            self.OnSuccess = OdPyHelpers.Event()
        def OnSuccess_Bind(self, objMethod): 
            self.OnSuccess += objMethod 
        def OnSuccess_Unbind(self,objMethod): 
            self.OnSuccess -= objMethod 
        #End OnSuccess Event

    @staticmethod
    def FindPathFromAppWorkingDirectory(rel_path, raiseExceptionIfNotFound = True):
        abs_path = os.path.normpath(os.path.join(os.getcwd(), rel_path))
        is_exist = os.path.exists(abs_path)
        if(not is_exist and raiseExceptionIfNotFound):
            raise Exception('Path not exists: {0}'.format(abs_path))
        if(not raiseExceptionIfNotFound):
            return is_exist,abs_path
        else:
            return abs_path
        pass

    @staticmethod
    def PathCombine(path1,path2,raiseExceptionIfNotFound = True):
        res_path = os.path.normpath(os.path.join(path1, path2))
        is_exist = os.path.exists(res_path)
        if(not is_exist and raiseExceptionIfNotFound):
            raise Exception('Path not exists: {0}'.format(res_path))
        if(not raiseExceptionIfNotFound):
            return is_exist,res_path
        else:
            return res_path
        pass
        return res_path

    @staticmethod
    def GetDrawingAppResourcesPath(relPath_toExampleResources):
        AppResourcesesPath_Rel = os.path.join(r'..\..\Swig\SwigODAExamples\Drawings\Python\Python2', relPath_toExampleResources)
        AppResourcesesPath = OdPyHelpers.FindPathFromAppWorkingDirectory(AppResourcesesPath_Rel)
        return AppResourcesesPath
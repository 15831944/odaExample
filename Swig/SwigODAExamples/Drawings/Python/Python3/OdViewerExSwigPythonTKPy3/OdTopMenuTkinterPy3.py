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

from Tkinter import *

class OdTopMenuTkinter(Menu):
    FileMenu = None

    def __init__(self, master=None, cnf={}, **kw):
        Menu.__init__(self,master,cnf,**kw)

        self.FileMenu = self.Create_FileMenu()
        self.add_cascade(label='File', menu=self.FileMenu)
        pass

    #Initialize File menu
    def Create_FileMenu(self):
        resultMenu = Menu(self,tearoff=0)
        return resultMenu

    def AddButtonCommand(self,menu,commandText,commandHandler):
        menu.add_command(label=commandText , command=commandHandler)

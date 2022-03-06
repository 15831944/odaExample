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
from OdPyHelpers import *

class OdPyTkinterGuiHelpers:
    class OnButtonCheckedChangedEvent:
          #Begin OnButtonCheckedChanged Event
          def __init__(self):
              self.OnButtonCheckedChanged = OdPyHelpers.Event()
          def OnButtonCheckedChanged_Bind(self, objMethod): 
              self.OnButtonCheckedChanged += objMethod 
          def OnButtonCheckedChanged_Unbind(self,objMethod): 
              self.OnButtonCheckedChanged -= objMethod 
          #End OnButtonCheckedChanged Event

    class OdPyCheckButton(Checkbutton,OnButtonCheckedChangedEvent):

        def __init__(self, master=None, **kw):
            Checkbutton.__init__(self, master, **kw)
            OdPyTkinterGuiHelpers.OnButtonCheckedChangedEvent.__init__(self)
            self.checked = BooleanVar(False)
            self.configure(command=self.__CheckedChangedBind__, variable=self.checked)
            pass
        def __CheckedChangedBind__(self):
            self.OnButtonCheckedChanged(self.checked.get())
            pass

        def SetChecked(self,state):
            self.checked.set(state)
            pass

    class OnButtonClickEvent:
          #Begin OnButtonClick Event
          def __init__(self):
              self.OnButtonClick = OdPyHelpers.Event()
          def OnButtonClick_Bind(self, objMethod): 
              self.OnButtonClick += objMethod 
          def OnButtonClick_Unbind(self,objMethod): 
              self.OnButtonClick -= objMethod 
          #End OnButtonClick Event

    class OdPyButton(Button,OnButtonClickEvent):
        def __init__(self, master=None, **kw):
            Button.__init__(self, master, **kw)
            OdPyTkinterGuiHelpers.OnButtonClickEvent.__init__(self)
            self.configure(command=self.__ClickBind__)
            pass
        def __ClickBind__(self):
            self.OnButtonClick()
            pass
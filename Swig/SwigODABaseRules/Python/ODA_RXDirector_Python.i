/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

%{
#include "RxObjectImpl.h"
%}

%define %RXDIRECTOR(CLASS,MODULE_NAME)
%ignore CLASS::CLASS;
%nodefaultctor CLASS;
%feature ("director") CLASS;
%wrapper
%{
//Old Solution:
// This proxy class need for creation by OdRxObjectImpl<T>::createObject() (function working only with class where contains default constructor)
// Because need create class ( CustomSwigDirector_ CLASS ) for execute OdRxObjectImpl<T>::createObject()
// Also, after creation need set a pointer to the wrapped python object , by ((CustomSwigDirector_ CLASS *)result)->InitializeSelfOfDirector(self)
// Method Director::InitializeSelfOfDirector is custom and added in SWIG.
//New Solution (current):
// This proxy class need for creation inheritance classes from OdRxObject
// Enabling operator new() by meanse of macros ODRX_HEAP_OPERATORS(), is allow using constructors in directly.
//In this situation we need use constructor with parameter (PyObject *self), for initialize SWIG director.
class CustomSwigDirector_ ## CLASS ## : public SwigDirector_ ## CLASS
{
public:
  ODRX_HEAP_OPERATORS()
  CustomSwigDirector_ ## CLASS ## (PyObject *self) : SwigDirector_ ## CLASS ## (self)
  {}
  
  virtual void addRef()
  {
  }

  virtual void release()
  {
  }
};
%}

%wrapper
%{
PyObject *_wrap_director_new_ ## CLASS ##(PyObject *self) {
  CLASS* result = new CustomSwigDirector_ ## CLASS ##(self); /*RXDIRECTOR*/ 

  PyObject* resultobj = SWIG_NewPointerObj(result,SWIGTYPE_p_ ## CLASS, SWIG_POINTER_OWN);

  ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
  ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
  tr->AddObject(resultobj);

  return resultobj;
}
%}

%header
%{
extern "C" SWIGINTERN PyObject *_wrap_director_new_ ## CLASS (PyObject *args);
%}

%extend CLASS {
    static PyObject * __new (PyObject * self) 
    {
      return _wrap_director_new_ ## CLASS ##(self);
    }

    %pythoncode
    {
      def __init__(self):
          this = _ ## MODULE_NAME ## .## CLASS ## ___new(self)
          try:
            self.this.append(this)
          except:
            self.this = this
    }
}
%enddef

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

%include "SmartPtr.h"
%define SMART_GENERAL_(PTRTYPE, CTYPE, CSTYPE)
%naturalvar PTRTYPE;

//SMARTPTR IN TYPEMAPS
%typemap(in, canthrow=1) PTRTYPE
%{
  //%typemap(in, canthrow=1) SMART_GENERAL_ PTRTYPE
  {
#if SWIG_VERSION == 0x040002
    if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
#elif SWIG_VERSION == 0x030012
    CTYPE* argp_$input;
    if ((SWIG_ConvertPtr($input,(void **) &argp_$input, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
	$1 = argp_$input;
#else
    #error Not implemented for swig version: SWIG_VERSION 
#endif
  }
%}
%typemap(in, numinputs=0) PTRTYPE& 
%{
  //%typemap(in, canthrow=1) SMART_GENERAL_ PTRTYPE& 
  PTRTYPE tmp_$1;
  $1 = &tmp_$1;
%}

%typemap(arginit) const PTRTYPE& {
   $1 = &PTRTYPE();
}

%typemap(in, canthrow=1) const PTRTYPE&
%{ 
  //%typemap(in, canthrow=1) SMART_GENERAL_ const PTRTYPE&
  {
#if SWIG_VERSION == 0x040002
    if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
#elif SWIG_VERSION == 0x030012
	CTYPE* argp_$input;
    if ((SWIG_ConvertPtr($input,(void **) &argp_$input, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
	*$1 = argp_$input;
#else
    #error Not implemented for swig version: SWIG_VERSION 
#endif
  }
%}
%typemap(in, canthrow=1) CTYPE*, CTYPE&
%{ 
  //%typemap(in, canthrow=1) SMART_GENERAL_ CTYPE*, CTYPE&
  if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
    return NULL;
%}


//SMARTPTR OUT TYPEMAPS
%typemap(out) const PTRTYPE& 
%{
  //%typemap(out) SMART_GENERAL_ const PTRTYPE&
  OdRxClass* _rxClassInfo = ($1)->get()->isA();
  if(_rxClassInfo)
    $result = ($1 == 0) ? 0 : SWIG_NewPointerObj(($1)->detach(), GetPythonTypeInfoFrom(_rxClassInfo, $descriptor(CTYPE*)) , 0);
  else
    $result = ($1 == 0) ? 0 : SWIG_NewPointerObj(($1)->detach(), $descriptor(CTYPE*), 0);
  ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
  ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
  tr->AddObject($result);
%}
%typemap(out) PTRTYPE 
%{
  //%typemap(out) SMART_GENERAL_ PTRTYPE
  if((&$1)->get() == 0)
#if SWIG_VERSION == 0x040002
    $result = SWIG_Py_Void();
#elif SWIG_VERSION == 0x030012
    $result = SWIG_Py_None();
#else
	$result = SWIG_Py_Void();
#endif
  else
  {
    OdRxClass* _rxClassInfo = (&$1)->get()->isA();
    if(_rxClassInfo)
      $result = (&$1 == 0) ? 0 : SWIG_NewPointerObj((&$1)->detach(), GetPythonTypeInfoFrom(_rxClassInfo,$descriptor(CTYPE*)), 0);
    else
      $result = (&$1 == 0) ? 0 : SWIG_NewPointerObj((&$1)->detach(), $descriptor(CTYPE*), 0);
	ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
    ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
    tr->AddObject($result);
  }
%}

%typemap(out) PTRTYPE& 
%{
  //%typemap(out) SMART_GENERAL_ PTRTYPE&
  OdRxClass* _rxClassInfo = ($1)->get()->isA();
  if(_rxClassInfo)
    $result = ($1 == 0) ? 0 : SWIG_NewPointerObj(($1)->detach(), GetPythonTypeInfoFrom(_rxClassInfo, $descriptor(CTYPE*)) , 0);
  else
    $result = ($1 == 0) ? 0 : SWIG_NewPointerObj(($1)->detach(), $descriptor(CTYPE*), 0);
  ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
  ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
  tr->AddObject($result);
%}

%typemap(out) CTYPE* , CTYPE&
%{
  //%typemap(out) SMART_GENERAL_ CTYPE* , CTYPE&
  if (!$1)
#if SWIG_VERSION == 0x040002
    $result = SWIG_Py_Void();
#elif SWIG_VERSION == 0x030012
    $result = SWIG_Py_None();
#else
	$result = SWIG_Py_Void();
#endif
  else 
  {
    OdRxClass* _rxClassInfo = $1->isA();
    if(_rxClassInfo)
        $result = SWIG_NewPointerObj($1, GetPythonTypeInfoFrom(_rxClassInfo,$descriptor(CTYPE*)), 0);
    else
        $result = SWIG_NewPointerObj($1, $descriptor(CTYPE*), 0);
		
	//ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
    //ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
    //tr->AddObject($result);
  }
%}
%typemap(argout) PTRTYPE& { 
  //%typemap(argout) PTRTYPE&
  PyObject *append_res_$1 = NULL;
  OdRxClass* _rxClassInfo = ($1)->get()->isA();
  if(_rxClassInfo)
    append_res_$1 = SWIG_NewPointerObj(($1)->detach(), GetPythonTypeInfoFrom(_rxClassInfo, $descriptor(CTYPE*)), 0);
  else
    append_res_$1 = SWIG_NewPointerObj(($1)->detach(), $descriptor(CTYPE*), 0);
  %append_output(append_res_$1);
  ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
  ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
  tr->AddObject(append_res_$1);
}
%enddef

%define SMART_GENERAL(PTRTYPE, TYPE)
SMART_GENERAL_(PTRTYPE, TYPE, TYPE)
%enddef

%define SMARTPTR_TYPEMAP(TYPE, CSTYPE)
SMART_GENERAL(TYPE, CSTYPE)
%enddef


%define SMARTPTR_TYPEMAP_(PTRTYPE, CTYPE, CSTYPE)
SMART_GENERAL_(PTRTYPE, CTYPE, CSTYPE)
%enddef


%define DECLARE_SMARTPTR(NAME)
SMARTPTR_TYPEMAP(NAME ## Ptr, NAME)
SMARTPTR_TYPEMAP(OdSmartPtr<NAME>, NAME)
%feature("action") NAME::~NAME
{
  arg1->release();
}
%enddef

%define DECLARE_SMARTPTR1(NAME)
DECLARE_SMARTPTR(NAME)
%ignore NAME::NAME;
%enddef

%define DECLARE_SMARTPTR2(NAME)
DECLARE_SMARTPTR(NAME)
%enddef

%define DECLARE_SMARTPTR3(NAME)
DECLARE_SMARTPTR(NAME)
%ignore NAME::NAME;
%enddef


%define DECLARE_SMARTPTR_NESTED(BASE, NAME)
SMARTPTR_TYPEMAP_(BASE::NAME ## Ptr, BASE::NAME, BASE.NAME)
SMARTPTR_TYPEMAP_(OdSmartPtr<BASE::NAME>, BASE::NAME, BASE.NAME)
%feature("action") BASE::NAME::~NAME
{
  arg1->release();
}
%enddef

%define DECLARE_SMARTPTR1_NESTED(BASE, NAME)
DECLARE_SMARTPTR_NESTED(BASE, NAME)
%ignore BASE::NAME::NAME;
%enddef

%define DECLARE_CORE_SMARTPTR1_NESTED(BASE, NAME)
DECLARE_SMARTPTR1_NESTED(BASE, NAME)
%enddef

%define DECLARE_SMARTPTR_UPCAST(NAME)
SMARTPTR_TYPEMAP(NAME ## Ptr, NAME)
SMARTPTR_TYPEMAP(OdSmartPtr<NAME>, NAME)
%feature("action") NAME::~NAME
{
  arg1->release();
}
%enddef

SMARTPTR_TYPEMAP(OdRxObjectPtr, OdRxObject)
%feature("action") OdRxObject::~OdRxObject
{
  arg1->release();
}


%define SIMPLE_CORE_SMARTPTR(NAME)
SMARTPTR_TYPEMAP(NAME ## Ptr, NAME)
SMARTPTR_TYPEMAP(OdSmartPtr<NAME>, NAME)
%feature("action") NAME::~NAME
{
  // SIMPLE_CORE_SMARPTR
  delete arg1;
}
%enddef

%define DECLARE_SMARTPTR_EX(NAME, BASE)
DECLARE_SMARTPTR(NAME)
%feature("action") NAME::~NAME
{
	((BASE*)arg1)->release();
}
%enddef

%define DECLARE_SMARTPTR_WITHNS(NS, NAME)
SMARTPTR_TYPEMAP(NS::NAME ## Ptr, NAME)
SMARTPTR_TYPEMAP(OdSmartPtr<NS::NAME>, NAME)
%feature("action") NS::NAME::~NAME
{
  arg1->release();
}
%enddef


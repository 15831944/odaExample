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

%include "TPtr.h"

%define TPTR_TYPEMAP(PTRTYPE, CTYPE, CSTYPE)
%naturalvar PTRTYPE;
%typemap(ctype,out="void*") CTYPE*, CTYPE&, PTRTYPE, PTRTYPE&, const PTRTYPE&, PTRTYPE const& "void*"
%typemap(in, canthrow=1) PTRTYPE
%{ 
  //%typemap(in, canthrow=1) TPTR PTRTYPE
  {
    if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
  }
%}

%typemap(in, canthrow=1) const PTRTYPE&
%{ 
  //%typemap(in, canthrow=1) TPTR const PTRTYPE&
  {
  if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
  }
%}

%typemap(in, canthrow=1) CTYPE*, CTYPE&
%{ 
  //%typemap(in, canthrow=1) TPTR CTYPE*, CTYPE&
  {
  if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
  }
%}

%typemap(in, canthrow=1) PTRTYPE& 
%{
  //%typemap(in, canthrow=1) TPTR PTRTYPE&
  {
  if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(CTYPE*),SWIG_POINTER_OWN)) == -1)
      return NULL;
  }
%}

%typemap(directorin) CTYPE*
%{
  //%typemap(directorin) CTYPE*
  {
  #error NotImplemented
  }
%}
%typemap(directorin) CTYPE&
%{
  //%typemap(directorin) CTYPE&
  {
  #error NotImplemented
  }
%}

%typemap(directorin) PTRTYPE, PTRTYPE&, const PTRTYPE& 
%{
  //%typemap(directorin) PTRTYPE, PTRTYPE&, const PTRTYPE& 
  {
  #error NotImplemented
  }
%}


%typemap(out) PTRTYPE&, const PTRTYPE& 
%{ 
  //%typemap(out) PTRTYPE&, const PTRTYPE& 
  {
    $result = ($1 == 0) ? 0 : SWIG_NewPointerObj(($1)->detach(),$descriptor(CTYPE*), SWIG_POINTER_OWN);
    ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
    ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
    tr->AddObject($result);
  }
%}
%typemap(out) PTRTYPE 
%{
  //%typemap(out) PTRTYPE
  {
    $result = SWIG_NewPointerObj($1.get(),$descriptor(CTYPE*), SWIG_POINTER_OWN);
    ODA_PyMemoryManager* manager = ODA_PyMemoryManager::Get_MemoryManager();
    ODA_PyMemoryTransaction* tr = manager->GetCurrentTransaction();
    tr->AddObject($result);
  }
%}
%typemap(out) CTYPE* , CTYPE&
%{
  //%typemap(out) CTYPE* , CTYPE&
  {
    $result = SWIG_NewPointerObj($1,$descriptor(CTYPE*), SWIG_POINTER_OWN);
  }
%}
%enddef

%define DECLARE_TPTR(NAME)
TPTR_TYPEMAP(NAME ## Ptr, NAME, NAME)
TPTR_TYPEMAP(TPtr<NAME>, NAME, NAME)
%enddef

%define DECLARE_TPTR_NESTED(BASE, NAME)
TPTR_TYPEMAP(BASE::NAME ## Ptr, BASE::NAME, BASE.NAME)
TPTR_TYPEMAP(TPtr<BASE::NAME>, BASE::NAME, BASE.NAME)
%enddef

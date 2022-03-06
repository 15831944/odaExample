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
%include "OdArray.h"

%ignore OdArray::insert;
%ignore OdArray::at;
%extend OdArray
{
  OdArray::iterator Insert(OdArray::iterator before, T const& value) { return $self->insert(before, value); }
  const T& At(size_type arrayIndex) { return $self->at(arrayIndex); }
}


%define DEF_ODARRAY_BASE(PYTHON_TYPE, CPP_ITEM_TYPE, CPP_ALLOCATOR)
%apply int { OdArray<CPP_ITEM_TYPE , CPP_ALLOCATOR<CPP_ITEM_TYPE > >::size_type }; 
%template(PYTHON_TYPE) OdArray<CPP_ITEM_TYPE , CPP_ALLOCATOR<CPP_ITEM_TYPE > >;
%enddef

%define DEF_ODARRAY_OBJECTS_ALLOCATOR(PYTHON_TYPE, CPP_ITEM_TYPE)
%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) OdArray<CPP_ITEM_TYPE>&, const OdArray<CPP_ITEM_TYPE>&
{
  //%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) for OdArray<CPP_ITEM_TYPE>&
  void *vptr = 0;
  int res = SWIG_ConvertPtr($input, &vptr, $descriptor(OdArray<CPP_ITEM_TYPE , OdObjectsAllocator<CPP_ITEM_TYPE > >*), 0);
  $1 = SWIG_CheckState(res);
}
%typemap(in, canthrow=1) OdArray<CPP_ITEM_TYPE>&, const OdArray<CPP_ITEM_TYPE>&
%{ 
  //%typemap(in, canthrow=1) OdArray<CPP_ITEM_TYPE>&
  {
    if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(OdArray<CPP_ITEM_TYPE , OdObjectsAllocator<CPP_ITEM_TYPE > >*),0)) == -1)
      return NULL;
  }
%}
%typemap(in, canthrow=1) OdArray<CPP_ITEM_TYPE>*
%{ 
  //%typemap(in, canthrow=1) OdArray<CPP_ITEM_TYPE>*
  {
    if ((SWIG_ConvertPtr($input,(void **) &$1, $descriptor(OdArray<CPP_ITEM_TYPE , OdObjectsAllocator<CPP_ITEM_TYPE > >*),0)) == -1)
      return NULL;
  }
%}

%typemap(out) OdArray<CPP_ITEM_TYPE>&, const OdArray<CPP_ITEM_TYPE>&
%{
  //%typemap(out) OdArray<CPP_ITEM_TYPE>&, const OdArray<CPP_ITEM_TYPE>&  
  resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), $descriptor(OdArray<CPP_ITEM_TYPE , OdObjectsAllocator<CPP_ITEM_TYPE > >*), 0);	
%}
DEF_ODARRAY_BASE(PYTHON_TYPE,CPP_ITEM_TYPE,OdObjectsAllocator)
%enddef

%define DEF_ODARRAY_MEMORY_ALLOCATOR(PYTHON_TYPE, CPP_ITEM_TYPE)
DEF_ODARRAY_BASE(PYTHON_TYPE,CPP_ITEM_TYPE,OdMemoryAllocator)
%enddef

%define DEF_ODARRAY_CLRMEMORY_ALLOCATOR(PYTHON_TYPE, CPP_ITEM_TYPE)
DEF_ODARRAY_BASE(PYTHON_TYPE,CPP_ITEM_TYPE,OdClrMemAllocator)
%enddef

%define DEF_ODARRAY_PLAINOBJECTS_ALLOCATOR(PYTHON_TYPE, CPP_ITEM_TYPE)
DEF_ODARRAY_BASE(PYTHON_TYPE,CPP_ITEM_TYPE,OdPlainObjectsAllocator)
%enddef

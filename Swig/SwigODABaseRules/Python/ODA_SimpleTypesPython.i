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

%define INTEGER_SIMPLETYPE(CTYPE)

%typemap(in) CTYPE %{ $1 = (CTYPE)PyInt_AsLong($input); /*in SIMPLETYPE*/%}
%typemap(out) CTYPE %{ $result = PyInt_FromLong($1); /*out SIMPLETYPE*/%}

%typemap(directorout) CTYPE
%{ 
  /*directorout SIMPLETYPE start*/
  int return_value_idx = 0;
  PyObject* collection_item = NULL;
  if (PyTuple_Check($input))
  {
    collection_item = PyTuple_GetItem($input, return_value_idx);
    $result = ($1_ltype)PyInt_AsLong(collection_item);
  }
  else if (PyList_Check($input))
  {
    collection_item = PyList_GetItem($input, return_value_idx);
    $result = ($1_ltype)PyInt_AsLong(collection_item);
  }
  else
    $result = (OdResult)PyInt_AsLong(result);
  /*directorout SIMPLETYPE end*/
%}
%typemap(directorin) CTYPE 
%{
  $input = PyLong_FromLongLong($1); /*directorin SIMPLETYPE*/
%}

%typemap(in) const CTYPE& 
%{
  /*in const SIMPLETYPE& */
  CTYPE tmp_$1 = PyInt_AsLong($input);
  $1 = &tmp_$1; 
%}

%enddef

%define OUT_PARAM_AS_REFERENCE_INTEGER(CTYPE)

%typemap(in,numinputs=0) CTYPE& 
%{
  //%typemap(in) CTYPE&
  {
    $1 = new CTYPE();
  }
%}

%typemap(freearg) CTYPE& ""

%typemap(argout) const CTYPE& ""

%typemap(argout) CTYPE& {
  //%typemap(argout) CTYPE&
  %append_output(PyLong_FromLongLong(long(*$1)));
  delete $1;
}

%enddef

%define ENUM_TYPE(CTYPE)

%typemap(in) CTYPE %{ $1 = (CTYPE)PyInt_AsLong($input); /*in ENUM_TYPE*/%}
%typemap(out) CTYPE %{ $result = PyLong_FromLongLong($1); /*out ENUM_TYPE*/%}

%typemap(directorout) CTYPE
%{ 
  /*directorout ENUM_TYPE start*/
  int return_value_idx = 0;
  PyObject* collection_item = NULL;
  if (PyTuple_Check($input))
  {
    collection_item = PyTuple_GetItem($input, return_value_idx);
    $result = ($1_ltype)PyInt_AsLong(collection_item);
  }
  else if (PyList_Check($input))
  {
    collection_item = PyList_GetItem($input, return_value_idx);
    $result = ($1_ltype)PyInt_AsLong(collection_item);
  }
  else
    $result = (OdResult)PyInt_AsLong(result);
  /*directorout ENUM_TYPE end*/
%}
%typemap(directorin) CTYPE 
%{
  /*directorin ENUM_TYPE*/
    $input = PyLong_FromLongLong($1);
%}
%enddef

ENUM_TYPE(OdResult)
INTEGER_SIMPLETYPE(OdInt16)
INTEGER_SIMPLETYPE(OdInt32)
INTEGER_SIMPLETYPE(OdUInt32)
INTEGER_SIMPLETYPE(BRepBuilderGeometryId)
INTEGER_SIMPLETYPE(OdInt16)
INTEGER_SIMPLETYPE(OdUInt16)
INTEGER_SIMPLETYPE(OdInt8)
INTEGER_SIMPLETYPE(OdUInt8)
INTEGER_SIMPLETYPE(OdInt64)
INTEGER_SIMPLETYPE(OdUInt64)
INTEGER_SIMPLETYPE(OdHWnd)
INTEGER_SIMPLETYPE(OdIntPtr)

OUT_PARAM_AS_REFERENCE_INTEGER(OdInt32)
OUT_PARAM_AS_REFERENCE_INTEGER(int)
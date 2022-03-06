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

//In typemaps
%typemap(in) const OdChar*
%{
  //%typemap(in) const OdChar*
  $1 = (OdChar*)$input;
%}

%typemap(in) const OdChar* const & 
%{
  //%typemap(in) const OdChar* const & 
  $1 = (const OdChar**)$input;
%}

//Out typemaps
%typemap(out) const OdChar* , const OdChar* const &
%{
  //%typemap(out) const OdChar* , const OdChar* const &
#if defined(_NATIVE_WCHAR_T_DEFINED)
  $result = PyString_FromStringAndSize($1, 1);
#else
  $result = PyUnicode_FromWideChar($1,1);
#endif
%}

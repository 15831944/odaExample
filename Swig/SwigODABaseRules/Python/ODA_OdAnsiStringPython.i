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

%naturalvar OdAnsiString;

//In typemaps
%typemap(in) OdAnsiString 
%{ 
  // %typemap(in) OdAnsiString
  {
   #if PY_VERSION_HEX >= 0x03000000
    $1 = OdAnsiString(PyUnicode_AsUTF8($input), CP_UTF_8);
   #else
    $1 = OdAnsiString(PyString_AsString($input), CP_UTF_8);
   #endif
  }
%}
%typemap(in,numinputs=0) OdAnsiString& 
%{
  // %typemap(in) OdAnsiString& 
  {
    $1 = new OdAnsiString();
  }
%}
%typemap(in) const OdAnsiString& 
%{
	// %typemap(in) const OdAnsiString&  
  {
   #if PY_VERSION_HEX >= 0x03000000
    $1 = new OdAnsiString(PyUnicode_AsUTF8($input), CP_UTF_8);
   #else
    $1 = new OdAnsiString(PyString_AsString($input), CP_UTF_8);
   #endif
  }
%}

%typemap(freearg) OdAnsiString& ""

%typemap(freearg) const OdAnsiString&
{
  //%typemap(freearg) const OdAnsiString&
  delete $1;
}

%typemap(argout) const OdAnsiString& ""

%typemap(argout) OdAnsiString& { 
  %append_output(PyString_FromStringAndSize($1->c_str(),$1->getLength()));
  delete $1;                                
}



//Out typemaps
%typemap(out) OdAnsiString 
%{ 
  // %typemap(out) OdAnsiString 
  $result = PyString_FromStringAndSize($1.c_str(), $1.getLength());
%}

%typemap(out) const OdAnsiString& 
%{
  // %typemap(out) const OdAnsiString& 
  $result = PyString_FromStringAndSize($1->c_str(), $1->getLength());
%}



//Typemaps for OUT director
%typemap(directorout) OdAnsiString 
%{
  // %typemap(directorout) OdAnsiString    
   #if PY_VERSION_HEX >= 0x03000000
    $result = PyUnicode_AsUTF8($input);
   #else
    $result = PyString_AsString($input);
   #endif
%}
%typemap(directorout) const OdAnsiString& 
%{
  // %typemap(directorout) const OdAnsiString&  
  #if PY_VERSION_HEX >= 0x03000000
    $result = PyUnicode_AsUTF8($input);
  #else
   $result = PyString_AsString($input);
  #endif
%}



//Typemaps for IN director
%typemap(directorin) const OdAnsiString& 
%{ 
  // %typemap(directorin) const OdAnsiString& 
  $input = PyUnicode_FromWideChar($1.c_str(),$1.getLength());
%}
%typemap(directorin) OdAnsiString 
%{
	// %typemap(directorin) OdAnsiString  
  $input = PyUnicode_FromWideChar($1.c_str(),$1.getLength());
%}
%typemap(directorin)  OdAnsiString& 
%{
  // %typemap(directorin)  OdAnsiString&  
  $input = PyUnicode_FromWideChar($1.c_str(),$1.getLength());
%}

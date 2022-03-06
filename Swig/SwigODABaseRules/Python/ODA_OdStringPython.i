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

%naturalvar OdString;

%typemap(typecheck,precedence=SWIG_TYPECHECK_STRING) OdString, const OdString&
{
  //%typemap(typecheck,precedence=SWIG_TYPECHECK_STRING) OdString, const OdString&
  int res = PyUnicode_Check($input);
  $1 = SWIG_CheckState(res);
}

%typemap(arginit) OdString {
   //%typemap(arginit) OdString 
   $1 = OdString::kEmpty;
}

%typemap(arginit) const OdString& {
   //%typemap(arginit) const OdString&
   $1 = const_cast<OdString*>(&OdString::kEmpty);
}

//In typemaps
%typemap(in) OdString 
%{
  //%typemap(in) OdString 
  {
	// %typemap(directorout) const OdAnsiString&  
    #if PY_VERSION_HEX >= 0x03000000
     $1 = OdString(PyUnicode_AsUTF8($input), CP_UTF_8);
    #else
     $1 = OdString(PyString_AsString($input), CP_UTF_8);
    #endif
  }
%}
%typemap(in,numinputs=0) OdString& 
%{
  //%typemap(in) OdString&
  {
    $1 = new OdString();
  }
%}
%typemap(in) const OdString& 
%{ 
  //%typemap(in) const OdString&
  {
	#if PY_VERSION_HEX >= 0x03000000
     $1 = new OdString(PyUnicode_AsUTF8($input), CP_UTF_8);
    #else
     $1 = new OdString(PyString_AsString($input), CP_UTF_8);
    #endif
  }
%}
%typemap(freearg) const OdString&
{
  //%typemap(freearg) const OdString&
  if($1 != &OdString::kEmpty)
    delete $1;
}
%typemap(freearg) OdString& ""


%typemap(argout) const OdString& ""

%typemap(argout) OdString& { 
  //%typemap(argout) OdString& 
  %append_output(PyUnicode_FromWideChar($1->c_str(),$1->getLength()));
  delete $1;
}

//Out typemaps
%typemap(out) OdString 
%{ 
  //%typemap(out) OdString 
  {
    $result = PyUnicode_FromWideChar($1.c_str(), $1.getLength());
  }
%}
%typemap(out) const OdString& 
%{ 
  //%typemap(out) const OdString&
  {
    $result = PyUnicode_FromWideChar($1->c_str(), $1->getLength());
  }
%}


//Typemaps for OUT director
%typemap(directorout) OdString 
%{ 
  //%typemap(directorout) OdString 
  #if PY_VERSION_HEX >= 0x03000000
     $result = PyUnicode_AsUTF8($input);
  #else
     $result = PyString_AsString($input);
  #endif
%}
%typemap(directorout) const OdString& 
%{ 
  //%typemap(directorout) const OdString&  
  #if PY_VERSION_HEX >= 0x03000000
     $result = PyUnicode_AsUTF8($input);
  #else
     $result = PyString_AsString($input);
  #endif
%}



//Typemaps for IN director
%typemap(directorin) const OdString& 
%{ 
  //%typemap(directorin) const OdString& 
  $input = PyUnicode_FromWideChar($1.c_str(),$1.getLength());
%}
%typemap(directorin) OdString 
%{
  //%typemap(directorin) OdString
  $input = PyUnicode_FromWideChar($1.c_str(),$1.getLength());
%}
%typemap(directorin)  OdString& 
%{ 
  //%typemap(directorin)  OdString& 
  $input = PyUnicode_FromWideChar($1.c_str(),$1.getLength());
%}


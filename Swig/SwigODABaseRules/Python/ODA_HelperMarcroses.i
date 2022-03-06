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

%define Insert_ODA_SwigPythonCastMech()
//Start Insert ODA_SwigPythonCastMech 
%insert("header") "ODA_SwigPythonCastMech.i"
%init %{
  InitClass2SwigPythonTypeInfo();
%}
//End Insert ODA_SwigPythonCastMech 
%enddef

%define Insert_ODA_SwigPythonExceptionsMech()
%wrapper
{
#include <exception>
}
%exception {
    try {
        $action
    } catch(OdError err) {
	  SWIG_Python_Raise(SWIG_NewPointerObj(new OdError(err), SWIGTYPE_p_OdError, SWIG_POINTER_OWN), "Exception", SWIGTYPE_p_OdError); SWIG_fail;
    } catch (std::invalid_argument& e) {
      SWIG_exception_fail(SWIG_ValueError, e.what() ); SWIG_fail;
    } catch (std::domain_error& e) {
      SWIG_exception_fail(SWIG_ValueError, e.what() ); SWIG_fail;
    } catch (std::overflow_error& e) {
      SWIG_exception_fail(SWIG_OverflowError, e.what() ); SWIG_fail;
    } catch (std::out_of_range& e) {
      SWIG_exception_fail(SWIG_IndexError, e.what() ); SWIG_fail;
    } catch (std::length_error& e) {
      SWIG_exception_fail(SWIG_IndexError, e.what() ); SWIG_fail;
    } catch (std::runtime_error& e) {
      SWIG_exception_fail(SWIG_RuntimeError, e.what() ); SWIG_fail;
    } catch (std::exception& e) {
      SWIG_exception_fail(SWIG_SystemError, e.what() ); SWIG_fail;
    } catch(...) {
      SWIG_exception_fail(SWIG_RuntimeError,"Unknown exception"); SWIG_fail;
    }
}

%exceptionclass OdError;
%enddef

%define CHANGE_CTOR(CLASS)
	%feature("action") CLASS::CLASS()
	%{ result = OdRxObjectImpl<CLASS>::createObject().detach(); /*CHANGE_CTOR*/%}
%enddef



%define %SPEC_CREATION(CLASS, BASE)
%feature("action") CLASS::CLASS()
%{ result = OdRxObjectImpl<CLASS, BASE>::createObject().detach(); /*SPEC_CREATION*/%}
%feature("action") CLASS::~CLASS
{
  /*SPEC_CREATION*/
	((BASE*)arg1)->release();
}
%enddef



%define PROTECTED_DTOR_AUX_PYTHON(CSharpName, CppName)
%feature("action") CSharpName::~CSharpName
{
  /*PROTECTED_DTOR_AUX_PYTHON*/
	delete ((CppName*)arg1);
}
%enddef



%define NOT_EQUAL_OPERATOR_WITH_NAMESPACE(NS,STRUCT)
%{
namespace NS{
    static bool operator!=(const STRUCT& p1, const STRUCT &p2)
    {
        return memcmp(&p1, &p2, sizeof(STRUCT)) != 0;
    }
}
%}
%enddef


%define EQUAL_OPERATOR(STRUCT)
%{
static bool operator==(const STRUCT& p1, const STRUCT &p2)
{
	return memcmp(&p1, &p2, sizeof(STRUCT)) == 0;
}
%}
%enddef



%define NOT_EQUAL_OPERATOR(STRUCT)
%{
static bool operator!=(const STRUCT& p1, const STRUCT &p2)
{
	return memcmp(&p1, &p2, sizeof(STRUCT)) != 0;
}
%}
%enddef
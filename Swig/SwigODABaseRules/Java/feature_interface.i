%define DECLARE_INTERFACE_(CTYPE, INTERFACE, IMPL, OWN_FLAG)
%feature("interface", name = "INTERFACE", cptr = #INTERFACE ## "_GetInterfaceCPtr") CTYPE;
%typemap(jstype) CTYPE*, CTYPE& "INTERFACE"
%typemap(jtype, nopgcpp="1") CTYPE*, CTYPE& "long"
%typemap(javadirectorout) CTYPE*, CTYPE& "$javacall." ## #INTERFACE ## "_GetInterfaceCPtr()"
%typemap(javadirectorin) CTYPE*, CTYPE&
%{
	($jniinput == 0) ? null : (INTERFACE)new IMPL($jniinput,false)
%}
%typemap(javain) CTYPE*, CTYPE& "$javainput." ## #INTERFACE ## "_GetInterfaceCPtr()"
%typemap(javaout) CTYPE*, CTYPE&
{ 
  long cPtr = $jnicall;
  return (cPtr == 0) ? null : (INTERFACE)new IMPL(cPtr, OWN_FLAG); 
}
%typemap(directorin,descriptor="L$packagepath/" ## #INTERFACE ## ";") CTYPE*, CTYPE&
%{ $input = 0;
   *(($&1_ltype*)&$input) = &$1; 
%}
SWIG_JAVABODY_PROXY(public, protected, CTYPE)
%typemap(javainterfacecode, declaration="  long $interfacename_GetInterfaceCPtr();\n", cptrmethod="$interfacename_GetInterfaceCPtr") CTYPE %{
  public long $interfacename_GetInterfaceCPtr() {
    return $imclassname.$javaclazzname$interfacename_GetInterfaceCPtr(swigCPtr);
  }
%}
%enddef

%define DECLARE_INTERFACE_RENAME(CTYPE, INTERFACE, IMPL)
%rename (IMPL) CTYPE;
DECLARE_INTERFACE_(CTYPE, INTERFACE, IMPL, true)
%enddef

%define DECLARE_INTERFACE_RENAME_EXPL(CTYPE, INTERFACE, IMPL, OWN_FLAG)
%rename (IMPL) CTYPE;
DECLARE_INTERFACE_(CTYPE, INTERFACE, IMPL, OWN_FLAG)
%enddef

%define DECLARE_INTERFACE(CTYPE, INTERFACE)
DECLARE_INTERFACE_(CTYPE, INTERFACE, CTYPE)
%enddef


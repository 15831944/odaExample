%define DECLARE_INTERFACE_(CTYPE, INTERFACE, IMPL, OWN_FLAG)
%feature("interface", name = "INTERFACE") CTYPE;
%typemap(cstype) CTYPE*, CTYPE& "INTERFACE"
%typemap(csdirectorout) CTYPE*, CTYPE& "$cscall.GetInterfaceCPtr().Handle"
%typemap(csdirectorin) CTYPE*, CTYPE&
%{
	(INTERFACE)new IMPL($iminput,false)
%}
%typemap(csin) CTYPE*, CTYPE& "$csinput.GetInterfaceCPtr()"
%typemap(csout, excode=SWIGEXCODE) CTYPE*, CTYPE&
{
     IMPL ret = new IMPL($imcall,OWN_FLAG); 
     $excode
     return (INTERFACE)ret;
}
%typemap(csinterfacecode, declaration="  [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)]\n  global::System.Runtime.InteropServices.HandleRef GetInterfaceCPtr();\n", cptrmethod="$interfacename_GetInterfaceCPtr") CTYPE %{
  [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)]
  global::System.Runtime.InteropServices.HandleRef $interfacename.GetInterfaceCPtr() {
    return new global::System.Runtime.InteropServices.HandleRef(this, $imclassname.$csclazzname$interfacename_GetInterfaceCPtr(swigCPtr.Handle));
  }
%}
%enddef

%define DECLARE_INTERFACE_RENAME_EXPL(CTYPE, INTERFACE, IMPL, OWN_FLAG)
%rename (IMPL) CTYPE;
DECLARE_INTERFACE_(CTYPE, INTERFACE, IMPL, OWN_FLAG)
%enddef

%define DECLARE_INTERFACE_RENAME(CTYPE, INTERFACE, IMPL)
%rename (IMPL) CTYPE;
DECLARE_INTERFACE_(CTYPE, INTERFACE, IMPL, true)
%enddef

%define DECLARE_INTERFACE(CTYPE, INTERFACE, OWN_FLAG)
DECLARE_INTERFACE_(CTYPE, INTERFACE, CTYPE, OWN_FLAG)
%enddef

%define DECLARE_ABSTRACT(CTYPE, IMPL)
%feature("abstract", impname = "IMPL") CTYPE;
%typemap(csclassmodifiers) CTYPE "public abstract class"
%typemap(csdirectorin) CTYPE*, const CTYPE&
%{
	new IMPL($iminput,false)
%}
%typemap(csout, excode=SWIGEXCODE) CTYPE*, const CTYPE&
{ 
     IMPL ret = new IMPL($imcall,true); 
     $excode
     return ret;
}
%enddef

%define DECLARE_ABSTRACT_NS(CTYPE, IMPL, NAMESPACE)
%feature("abstract", impname = "IMPL") CTYPE;
%typemap(csclassmodifiers) CTYPE "public abstract class"
%typemap(csdirectorin) CTYPE*, const CTYPE&
%{
	new NAMESPACE.IMPL($iminput,false)
%}
%typemap(csout, excode=SWIGEXCODE) CTYPE*, const CTYPE&
{ 
     NAMESPACE.IMPL ret = new NAMESPACE.IMPL($imcall,true); 
     $excode
     return ret;
}
%enddef

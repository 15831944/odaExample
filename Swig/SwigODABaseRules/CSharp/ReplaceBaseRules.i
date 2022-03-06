%define REPLACE_BASE_UNI(INTERNAL_METHOD_NAME,CLASS,BASE)
%typemap(csbase, replace="1") CLASS "$typemap(cstype, BASE)"

%typemap(csinterfaces) CLASS "";
%csmethodmodifiers CLASS::Dispose "public override"

%typemap(csbody) CLASS 
%{
  private Object locker = new Object();
  private HandleRef swigCPtr;

  [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)]
  public $csclassname(IntPtr cPtr, bool cMemoryOwn) : base($imclassname.INTERNAL_METHOD_NAME ## _SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)]
  public static HandleRef getCPtr($csclassname obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }
%}

%pragma(csharp) imclasscode=
%{
  [DllImport(STRINGIZE($dllimport), EntryPoint=STRINGIZE(CSharp_ ## INTERNAL_METHOD_NAME ## _SWIGUpcast))]
  public static extern IntPtr INTERNAL_METHOD_NAME ## _SWIGUpcast(IntPtr jarg1);
%}

%insert(runtime)
%{
extern "C" SWIGEXPORT BASE* SWIGSTDCALL CSharp_ ## INTERNAL_METHOD_NAME ## _SWIGUpcast(CLASS *jarg1)
{ return (BASE*)jarg1; }
%}
%enddef
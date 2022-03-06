/**
Impl_testNativeCall rule need use in every BeginBlock.i of SWIG projects (for: C#,Java,Python & etc) 
It's functional used by test: OdSwigAssemblyValidator.TestConnectionWithNativePartOfWrappers 
**/

%define Impl_testNativeCall()
%insert("wrapper") 
%{ 
  SWIGEXPORT int SWIGSTDCALL testNativeCall() {
    return 10*03*95; //Magic numbers
  }
%}
%enddef

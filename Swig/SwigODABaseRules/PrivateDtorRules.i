#if defined(SWIGCSHARP)
%define PRIVATE_DTOR_WO_THROW_EXCEPTION(CLASS)
#if SWIG_VERSION == 0x040002
%typemap(csdisposing, methodname="Dispose", methodmodifiers="protected", parameters="bool disposing") CLASS {
    //throw new MethodAccessException("C++ destructor does not have public access");
  }
%typemap(csdisposing_derived, methodname="Dispose", methodmodifiers="protected", parameters="bool disposing") CLASS {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          //throw new MethodAccessException("C++ destructor does not have public access");
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      base.Dispose(disposing);
    }
  }
#elif SWIG_VERSION == 0x030012
%typemap(csdestruct, methodname="Dispose", methodmodifiers="public") CLASS
{
    if (swigCPtr.Handle != IntPtr.Zero)
    {
        if (swigCMemOwn)
        {
          lock (locker)//(this)
          {
                if ((swigCPtr.Handle != IntPtr.Zero) && (swigCMemOwn))
                {
                    swigCMemOwn = false;
                    //throw new MethodAccessException("C++ destructor does not have public access");
                }
            }
            swigCMemOwn = false;
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
    }
    GC.SuppressFinalize(this);
}
%typemap(csdestruct_derived, methodname="Dispose", methodmodifiers="public") CLASS
{
    if (swigCPtr.Handle != IntPtr.Zero)
    {
        if (swigCMemOwn)
        {
          lock (locker)//(this)
          {
                if ((swigCPtr.Handle != IntPtr.Zero) && (swigCMemOwn))
                {
                    swigCMemOwn = false;
                    //throw new MethodAccessException("C++ destructor does not have public access");
                }
            }
            swigCMemOwn = false;
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
    }
    GC.SuppressFinalize(this);
	base.Dispose();
}
#endif
%enddef
#endif

#if defined(SWIGJAVA)
%define PRIVATE_DTOR_WO_THROW_EXCEPTION(CLASS)
%typemap(javadestruct, methodname="delete", methodmodifiers="public") CLASS
{
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
      }
      swigCPtr = 0;
    }
}
%enddef
#endif
#if defined(SWIGCSHARP)
%typemap(ctype) (OdUInt32 count, const OdCmColor* colors, const double* values)  "void*"
%typemap(cstype) (OdUInt32 count, const OdCmColor* colors, const double* values) "HatchGradientColors"
%typemap(imtype) (OdUInt32 count, const OdCmColor* colors, const double* values) "IntPtr"
%typemap(csin, pre="IntPtr p_$csinput=$csinput.Marshal();", post="Marshal.FreeCoTaskMem(p_$csinput);") 
  (OdUInt32 count, const OdCmColor* colors, const double* values)  "p_$csinput"
#elif defined(SWIGJAVA)
%typemap(jtype) (OdUInt32 count, const OdCmColor* colors, const double* values)  "long"
%typemap(jstype) (OdUInt32 count, const OdCmColor* colors, const double* values) "HatchGradientColors"
%typemap(jni) (OdUInt32 count, const OdCmColor* colors, const double* values) "jlong"
%typemap(javain) (OdUInt32 count, const OdCmColor* colors, const double* values)  "$javainput"
#endif
%typemap(in) (OdUInt32 count, const OdCmColor* colors, const double* values)
{
  $1 = ((OdCmColorArray*)$input)->size();
  $2 = const_cast<OdCmColor*>(((OdCmColorArray*)$input)->getPtr());
  $3 = const_cast<double*>(((OdGeDoubleArray*)(((void**)$input)+1))->getPtr());
}

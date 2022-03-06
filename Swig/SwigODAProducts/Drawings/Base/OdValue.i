%include "StaticRxObject.h"
%nodefaultdtor OdStaticRxObject<OdRxObject>;
%nodefaultctor OdStaticRxObject<OdRxObject>;
PROTECTED_DTOR_TD(OdStaticRxObject_OdRxObject, OdStaticRxObject<OdRxObject>, OdRxObject)
%template(OdStaticRxObject_OdRxObject) OdStaticRxObject<OdRxObject>;
%rename (AsObjectId) operator OdDbObjectId;
#ifdef SWIGCSHARP
%typemap(imtype) (void*& pBuf, OdInt32& bufferSize) "out IntPtr"
%typemap(cstype) (void*& pBuf, OdInt32& bufferSize) "out byte[]"
%typemap(csin,pre="    IntPtr tmp_$csinput = IntPtr.Zero;",
             post="    $csinput = Teigha.TD.Helpers.UnmarshalByteArray(tmp_$csinput);") 
 (void*& pBuf, OdInt32& bufferSize) "out tmp_$csinput"
%typemap(in) (void*& pBuf, OdInt32& bufferSize)
%{
  void* tmp_$input = 0;
  OdInt32 tmp_$input1 = 0;
  $1 = &tmp_$input;
  $2 = &tmp_$input1;
%}
%typemap(freearg, match="in") (void*& pBuf, OdInt32& bufferSize)
{
  *(void**)$input = ::CoTaskMemAlloc(tmp_$input1 + 4);
  *((OdInt32*)(*(void**)$input)) = tmp_$input1;
  memcpy(((OdInt32*)(*(void**)$input))+1, tmp_$input, tmp_$input1);
}
%typemap(cscode) OdValue
%{
  public static explicit operator String(OdValue v) { return v.AsString(); }
  public static explicit operator Int32(OdValue v) { return v.AsInt32(); }
  public static explicit operator Int64(OdValue v) { return v.AsInt64(); }
  public static explicit operator OdDbObjectId(OdValue v) { return v.AsObjectId(); }
  public static explicit operator double(OdValue v) { return v.AsDouble(); }
%}
#endif
EQUAL_OPERATOR(OdValue)
#ifdef SWIGCSHARP
ODARRAY(OdValueArray, OdValue)
#endif
#ifdef SWIGJAVA
ODARRAY(OdValueArray, core_GobalsJNI, OdValue)
#endif
%template(OdValueArray) OdArray<OdValue>;
#ifdef SWIGJAVA
%rename (assignOdValue) OdValue::operator=(const OdValue& value);
%rename (assignString) OdValue::operator=(const OdString& value);
%rename (assignInt) OdValue::operator=(OdInt32 value);
%rename (assignDouble) OdValue::operator=(double value);
%rename (assignDate) OdValue::operator=(OdInt64 date);
%rename (assignObjectId) OdValue::operator=(const OdDbObjectId& objectId);
%rename (assignResBufPtr) OdValue::operator=(const OdResBufPtr& resBuf);
OUT_PARAM_LONG(void*& pBuf, long)
#endif
%include "OdValue.h"

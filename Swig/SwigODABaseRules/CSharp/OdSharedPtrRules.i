%include "SharedPtr.h"
%include "GetRealClassNameMethodRules.i"

%define SHAREDPTR_TYPEMAP(PTRTYPE, CTYPE, CSTYPE)
%naturalvar PTRTYPE;
%typemap(ctype,out="void*") CTYPE*, CTYPE&, PTRTYPE, const PTRTYPE&, PTRTYPE const& "void*"
%typemap(ctype,out="void**") PTRTYPE& "void**"
%typemap(imtype,out="IntPtr") CTYPE*, CTYPE&, PTRTYPE, const PTRTYPE&, PTRTYPE const& "HandleRef"
%typemap(imtype,out="IntPtr") PTRTYPE& "ref IntPtr"
%typemap(cstype) CTYPE*,CTYPE&, PTRTYPE, const PTRTYPE&, PTRTYPE const& "CSTYPE"
%typemap(cstype) PTRTYPE& "ref CSTYPE"
%typemap(in, canthrow=1) PTRTYPE
%{ 
  PTRTYPE argp_$input = (CTYPE*)$input; 
  $1 = argp_$input; 
%}

%typemap(in, canthrow=1) const PTRTYPE&
%{ 
  PTRTYPE argp_$input = (CTYPE*)$input; 
  $1 = &argp_$input; 
%}

%typemap(in, canthrow=1) CTYPE*, CTYPE&
%{ 
  $1 = (CTYPE*)$input; 
%}

%typemap(in, canthrow=1) PTRTYPE& 
%{
// sharedpointer reference typemap 
  if (!$input) {
     SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "Attempt to dereference null $1_type", 0);
     return $null;
   }
   PTRTYPE tmp_$input = (CTYPE*)*$input;
   $1 = &tmp_$input;
%}

%typemap(argout) PTRTYPE& 
{
  {
	*$input = $1->detach(); /*%typemap(argout) PTRTYPE&*/
  }
}

%typemap(argout) const PTRTYPE& 
{
  {
	$1->detach(); /*%typemap(argout) const PTRTYPE&*/
  }
}

%typemap(directorin) CTYPE*
%{
  // sharedpointer directorin typemap
  $input = (void*)$1;
%}
%typemap(directorin) CTYPE&
%{
  // sharedpointer directorin typemap
  $input = (void*)&$1;
%}
%typemap(directorin) PTRTYPE, PTRTYPE&, const PTRTYPE& 
%{
  // sharedpointer directorin typemap
  $input = (void*)$1.get();
%}
%typemap(out) PTRTYPE&, const PTRTYPE& 
%{ 
// detach1
  *(CTYPE **)&$result = ($1 == 0) ? 0 : ($1)->detach();
%}
%typemap(out) PTRTYPE 
%{
// shared_ptr get
  $result = $1.refCount() == 1 ?  $1.detach() : $1.get();
%}
%typemap(out) CTYPE* , CTYPE&
%{
  // out typemap for OdRxObject*
  $result = $1;
%}
%typemap(directorout, null="PTRTYPE()", optimal="1") PTRTYPE, PTRTYPE&, const PTRTYPE&, CTYPE* ,CTYPE&
%{ 
  // sharedpointer directorout typemap
  if (!$input) {
     SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "Unexpected null return for type $1_type", 0);
     return $null;
   }
   $result = (CTYPE*)$input; 
%}

%typemap(csdirectorout) PTRTYPE, PTRTYPE&, const PTRTYPE& "CSTYPE.getCPtr($cscall).Handle"

%typemap(csdirectorout) CTYPE&, CTYPE*
%{
    // csdirectorout for CTYPE*, CTYPE&
    CSTYPE.getCPtr($cscall).Handle
%}


////////////////////////////
%typemap(csdirectorin, pre="    CSTYPE tmp_$iminput = CSTYPE.createObject();",
post="    $iminput = CSTYPE.getCPtr(tmp_$iminput).Handle;") 
PTRTYPE& "out tmp_$iminput"

%typemap(csdirectorin) PTRTYPE, const PTRTYPE& "new CSTYPE($iminput,true)"

%typemap(csdirectorin) CTYPE*, const CTYPE*, CTYPE& "new CSTYPE($iminput,false)"

////////////////////////////
%typemap(csin) CTYPE*, CTYPE&, PTRTYPE, const PTRTYPE& "CSTYPE.getCPtr($csinput)"

%typemap(csin,pre="IntPtr p_$csinput = CSTYPE.getCPtr($csinput).Handle; /*SHAREDPTR& PRE*/", 
  post="MemoryTransaction mTrans_$csinput = MemoryManager.GetMemoryManager().GetCurrentTransaction();\n if(mTrans_$csinput != null)\n mTrans_$csinput.AddObject(Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), p_$csinput, true)); \n $csinput = Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), p_$csinput, mTrans_$csinput == null); \n /*SHAREDPTR& POST*/") PTRTYPE& "ref p_$csinput"


%typemap(csout, excode=SWIGEXCODE) PTRTYPE, PTRTYPE&, const PTRTYPE&
{ 
      //MemoryManager mMan = MemoryManager.GetMemoryManager();
      //MemoryTransaction mTrans = mMan.GetCurrentTransaction(); // MemoryTransaction #15
	  IntPtr ptr = $imcall;

	  CSTYPE ret = null;
	  //if (null != mTrans)
	  //{
	  //mTrans.AddObject(Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), ptr, true));
		ret = Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), ptr, false);
	  //}
	  //else
	  //{
      //  ret = Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), ptr, true);
	  //}
	  $excode
	  return ret;
}

Extend_method_getRealClassName(CTYPE)

%typemap(csout, excode=SWIGEXCODE) CTYPE*, CTYPE&
{ 
     CSTYPE ret = Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), $imcall, false);
     $excode
     return ret;
}

%typemap(csvarin, excode=SWIGEXCODE) PTRTYPE, const PTRTYPE&
%{
    set {
      $imcall; // csvarin
      $excode
    } 
%}

%typemap(csvarout, excode=SWIGEXCODE) PTRTYPE, const PTRTYPE&
%{
  get {
      CSTYPE ret = Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), $imcall, false);
      $excode
      return ret; //csvarout
    } 
%}

%enddef

%define DECLARE_SHAREDPTR(NAME)
SHAREDPTR_TYPEMAP(NAME ## Ptr, NAME, NAME)
SHAREDPTR_TYPEMAP(OdSharedPtr<NAME>, NAME, NAME)
%enddef

%define DECLARE_SHAREDPTR_UNIVERSAL1(CTYPE, CSTYPE)
SHAREDPTR_TYPEMAP(OdSharedPtr<CTYPE>, CTYPE, CSTYPE)
%enddef

%define DECLARE_SHAREDPTR_NESTED(BASE, NAME)
SHAREDPTR_TYPEMAP(BASE::NAME ## Ptr, BASE::NAME, BASE.NAME)
SHAREDPTR_TYPEMAP(OdSmartPtr<BASE::NAME>, BASE::NAME, BASE.NAME)
%enddef

%define DECLARE_SHAREDPTR_WITHNS(NS, NAME)
SHAREDPTR_TYPEMAP(NS::NAME ## Ptr, NAME, NAME)
SHAREDPTR_TYPEMAP(OdSharedPtr<NS::NAME>, NAME, NAME)
%enddef

%define DECLARE_SHAREDPTR_WITHNS_RENAMED(NS, NAME)
SHAREDPTR_TYPEMAP(NS::NAME ## Ptr, NS::NAME, NS ## _ ## NAME)
SHAREDPTR_TYPEMAP(OdSharedPtr<NS::NAME>, NS::NAME, NS ## _ ## NAME)
%enddef

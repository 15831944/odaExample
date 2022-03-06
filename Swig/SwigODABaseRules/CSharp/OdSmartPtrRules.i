%include "SmartPtr.h"
%include "GetRealClassNameMethodRules.i"

%define SMART_GENERAL_(PTRTYPE, CTYPE, CSTYPE)

Extend_method_getRealClassName(CTYPE)

%naturalvar PTRTYPE;
%typemap(ctype,out="void*") CTYPE*, CTYPE&, PTRTYPE, PTRTYPE&, const PTRTYPE&, PTRTYPE const&, PTRTYPE* "void*"
%typemap(imtype,out="IntPtr") CTYPE*, CTYPE&, PTRTYPE, const PTRTYPE&, PTRTYPE const& "HandleRef"
%typemap(cstype) CTYPE*, CTYPE&, PTRTYPE, const PTRTYPE&, PTRTYPE const&, PTRTYPE* "CSTYPE"

%typemap(ctype,out="void*") PTRTYPE* "void*"
%typemap(imtype,out="IntPtr") PTRTYPE* "HandleRef"
%typemap(cstype) PTRTYPE* "CSTYPE"

%typemap(in, canthrow=1) PTRTYPE
%{
  // in1 
  PTRTYPE argp_$input = (CTYPE*)$input; 
  $1 = argp_$input; 
%}

%typemap(in, canthrow=1) PTRTYPE& 
%{
   // smartpointer reference typemap
  PTRTYPE tmp_$1 = $input == NULL ? (CTYPE*)NULL : (CTYPE*)*((void**)$input);
  $1 = &tmp_$1;
%}

%typemap(in, canthrow=1) const PTRTYPE&
%{ 
  // in2
  PTRTYPE argp_$input = (CTYPE*)$input; 
  $1 = &argp_$input; 
%}

%typemap(in, canthrow=1) CTYPE*, CTYPE&
%{ 
  $1 = (CTYPE*)$input; 
%}

%typemap(cstype, out="CSTYPE") PTRTYPE& "ref CSTYPE /*OUT_PARAM for SMARTPTR*/"
%typemap(imtype, out="IntPtr") PTRTYPE& "ref IntPtr /*OUT_PARAM for SMARTPTR*/"
%typemap(csin, pre=" /*OUT_PARAM for SMARTPTR pre*/   IntPtr tmp_$csinput = $csinput == null ? IntPtr.Zero : CSTYPE.getCPtr($csinput).Handle; \n IntPtr saved_$csinput = tmp_$csinput; \n /*OUT_PARAM for SMARTPTR pre*/", 
  post="if(tmp_$csinput == IntPtr.Zero) $csinput = null; \n if(tmp_$csinput != IntPtr.Zero && tmp_$csinput != saved_$csinput) \n { \n MemoryTransaction mTrans_$csinput = MemoryManager.GetMemoryManager().GetCurrentTransaction();\n if(mTrans_$csinput != null)\n mTrans_$csinput.AddObject(Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), tmp_$csinput, true)); \n $csinput = Teigha.Core.Helpers.odCreateObjectInternal<CSTYPE>(typeof(CSTYPE), tmp_$csinput, mTrans_$csinput == null); \n /*OUT_PARAM for SMARTPTR*/ \n }")
   PTRTYPE& "ref tmp_$csinput /*OUT_PARAM for SMARTPTR*/"


%typemap(freearg, match="in") PTRTYPE& 
{
  *(void**)$input = ($1 == 0) ? 0 : ($1)->detach();
}

%typemap(directorin) PTRTYPE& "// smartpointer reference directorin"

%typemap(directorout) PTRTYPE& "// smartpointer reference directorout"

%typemap(directorin) CTYPE*
%{
  // smartpointer directorin typemap
  $input = (void*)$1;
%}
%typemap(directorin) CTYPE&
%{
  // smartpointer directorin typemap
  $input = (void*)&$1;
%}
%typemap(directorin) PTRTYPE, const PTRTYPE& 
%{
  // smartpointer directorin typemap
  $input = (void*)$1.get();
%}
%typemap(out) const PTRTYPE& 
%{ 
  $result = ($1 == 0) ? 0 : ($1)->detach();
%}
%typemap(out) PTRTYPE 
%{
  $result = (&$1 == 0) ? 0 : $1.detach();
%}
%typemap(out) PTRTYPE* 
%{
  $result = (&$1 == 0) ? 0 : $1->detach();
%}
%typemap(out) CTYPE* , CTYPE&
%{
  // out typemap for OdRxObject*
  $result = $1;
%}
%typemap(directorout, null="PTRTYPE()", optimal="1") PTRTYPE, const PTRTYPE&, CTYPE* ,CTYPE&
%{ 
  // smartpointer directorout typemap
  $result = (CTYPE*)$input;
%}

%typemap(csdirectorout) PTRTYPE, const PTRTYPE& "CSTYPE.getCPtr($cscall).Handle"

%typemap(csdirectorout) CTYPE&, CTYPE*
%{
    // csdirectorout for CTYPE*, CTYPE&
    CSTYPE.getCPtr($cscall).Handle
%}

%typemap(csdirectorin, pre="    CSTYPE tmp_$iminput = CSTYPE.createObject();",
post="    $iminput = CSTYPE.getCPtr(tmp_$iminput).Handle;") 
PTRTYPE& "ref tmp_$iminput"

%typemap(csdirectorin, pre="    CSTYPE tmp_$iminput = CSTYPE.createObject();",
post="    $iminput = CSTYPE.getCPtr(tmp_$iminput).Handle;") 
PTRTYPE* "out tmp_$iminput"

%typemap(csin) CTYPE*, CTYPE&, PTRTYPE, const PTRTYPE& "CSTYPE.getCPtr($csinput)"

%typemap(csin) PTRTYPE* "CSTYPE.getCPtr($csinput)"

%typemap(csout, excode=SWIGEXCODE) PTRTYPE
{//  PTRTYPE
      MemoryManager mMan = MemoryManager.GetMemoryManager();
      MemoryTransaction mTrans = mMan.GetCurrentTransaction(); // MemoryTransaction #17
	  IntPtr ptr = $imcall;

	  CSTYPE ret = null;
	  if (null != mTrans)
	  {
		mTrans.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true));
		ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, false);
	  }
	  else
	  {
		  ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true);
	  }
	  $excode
	  return ret;
}

%typemap(csout, excode=SWIGEXCODE) const PTRTYPE&
{
      MemoryManager mMan = MemoryManager.GetMemoryManager();
      MemoryTransaction mTrans = mMan.GetCurrentTransaction(); // MemoryTransaction #18
	  IntPtr ptr = $imcall;

	  CSTYPE ret = null;
	  if (null != mTrans)
	  {
		mTrans.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true));
		ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, false);
	  }
	  else
	  {
		  ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true);
	  }
	  $excode
	  return ret;
}

%typemap(csout, excode=SWIGEXCODE) PTRTYPE*
{     //  %typemap(csout, excode=SWIGEXCODE) PTRTYPE*
      MemoryManager mMan = MemoryManager.GetMemoryManager();
      MemoryTransaction mTrans = mMan.GetCurrentTransaction();
	  IntPtr ptr = $imcall;

	  CSTYPE ret = null;
	  if (null != mTrans)
	  {
		mTrans.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true));
		ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, false);
	  }
	  else
	  {
		  ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true);
	  }
	  $excode
	  return ret;
}

%typemap(csout, excode=SWIGEXCODE) CTYPE&, CTYPE const&
{ 
     CSTYPE ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$imcall,false);  /*createInt 3_1*/
     $excode
     return ret;
}

%typemap(csout, excode=SWIGEXCODE) CTYPE*
{ 
     CSTYPE ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$imcall,false);  /*createInt 3_2*/
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
%typemap(csvarout, excode=SWIGEXCODE) const PTRTYPE&
%{
  get {
      CSTYPE ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$imcall,false);  /*createInt 4_1*/
      $excode
      return ret; //csvarout
    } 
%}
%typemap(csvarout, excode=SWIGEXCODE) PTRTYPE
%{
  get {
      CSTYPE ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$imcall,false);  /*createInt 4_2*/
      $excode
      return ret; //csvarout
    } 
%}

%typemap(csvarin, excode=SWIGEXCODE) PTRTYPE*
%{
    set {
      $imcall; // csvarin
      $excode
    } 
%}

%typemap(csvarout, excode=SWIGEXCODE) PTRTYPE*
%{
  get {
      CSTYPE ret = (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$imcall,false);  /*createInt 4_3*/
      $excode
      return ret; //csvarout
    } 
%}
%enddef

%define SMART_GENERAL(PTRTYPE, TYPE)
SMART_GENERAL_(PTRTYPE, TYPE, TYPE)
%enddef


%define SPEC_SPTR(TYPE, CSTYPE)
SMART_GENERAL(TYPE, CSTYPE)
%typemap(csdirectorin) TYPE, const TYPE& 
%{
new CSTYPE($iminput,false)
%}

%typemap(csdirectorin) CSTYPE*, const CSTYPE*, CSTYPE& 
%{
new CSTYPE($iminput,false)
%}
%enddef

%define INTERNAL_SPTR(TYPE, CSTYPE)
SMART_GENERAL(TYPE, CSTYPE)
%typemap(csdirectorin) TYPE, const TYPE& 
%{
new CSTYPE ## Internal($iminput,false)
%}

%typemap(csdirectorin) CSTYPE*, const CSTYPE*, CSTYPE& 
%{
new CSTYPE ## _Internal($iminput,false)
%}
%feature("action") NAME::~NAME
{
  arg1->release();
}
%enddef

%define SMARTPTR_TYPEMAP(TYPE, CSTYPE)
SMART_GENERAL(TYPE, CSTYPE)
%typemap(csdirectorin,
pre="bool ownFl$iminput = true;"
"MemoryManager mMan$iminput = MemoryManager.GetMemoryManager();"
"MemoryTransaction mTrans$iminput = mMan$iminput.GetCurrentTransaction(); /* MemoryTransaction #19*/ "
"IntPtr ptr$iminput = $iminput;"

"if (null != mTrans$iminput){"
"mTrans$iminput.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr$iminput, true));"
"ownFl$iminput = false;}"
) const TYPE&
%{
	(CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr$iminput,ownFl$iminput)  /*createInt 5_1*/ // csdirectorin for smart pointer
     //(CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,true)  /*createInt 5_1*/ // csdirectorin for smart pointer
%}
%typemap(csdirectorin,
pre="bool ownFl$iminput = true;"
"MemoryManager mMan$iminput = MemoryManager.GetMemoryManager();"
"MemoryTransaction mTrans$iminput = mMan$iminput.GetCurrentTransaction(); /* MemoryTransaction #20 */"
"IntPtr ptr$iminput = $iminput;"

"if (null != mTrans$iminput){"
"mTrans$iminput.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr$iminput, true));"
"ownFl$iminput = false;}"
) TYPE
%{
	(CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr$iminput,ownFl$iminput)  /*createInt 5_2*/ /* csdirectorin for smart pointer */
     //(CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,true)  /*createInt 5_2*/ /* csdirectorin for smart pointer */
%}

%typemap(csdirectorin) CSTYPE*
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,false)  /*createInt 6_1*/ // csdirectorin for smart pointer
%}
%typemap(csdirectorin) const CSTYPE*
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,false)  /*createInt 6_2*/ // csdirectorin for smart pointer
%}
%typemap(csdirectorin) CSTYPE&
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,false)  /*createInt 6_3*/ // csdirectorin for smart pointer
%}
%enddef


%define SMARTPTR_TYPEMAP_(PTRTYPE, CTYPE, CSTYPE)
SMART_GENERAL_(PTRTYPE, CTYPE, CSTYPE)
%typemap(csdirectorin,
pre="bool ownFl = true;"
"MemoryManager mMan = MemoryManager.GetMemoryManager();"
"MemoryTransaction mTrans = mMan.GetCurrentTransaction(); // MemoryTransaction #22"
"IntPtr ptr = $iminput;"

"if (null != mTrans){"
"mTrans.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true));"
"ownFl = false;}"
) PTRTYPE
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr,ownFl)  /*createInt 7_1*/ // csdirectorin for smart pointer
     //(CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,true)  /*createInt 7_1*/ // csdirectorin for smart pointer
%}
%typemap(csdirectorin,
pre="bool ownFl = true;"
"MemoryManager mMan = MemoryManager.GetMemoryManager();"
"MemoryTransaction mTrans = mMan.GetCurrentTransaction(); // MemoryTransaction #23"
"IntPtr ptr = $iminput;"

"if (null != mTrans){"
"mTrans.AddObject((CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr, true));"
"ownFl = false;}"
) const PTRTYPE&
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),ptr,ownFl)  /*createInt 7_2*/ // csdirectorin for smart pointer
%}

%typemap(csdirectorin) CTYPE*
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,false)  /*createInt 8_1*/ // csdirectorin for smart pointer
%}
%typemap(csdirectorin) const CTYPE*
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,false)  /*createInt 8_2*/ // csdirectorin for smart pointer
%}
%typemap(csdirectorin) CTYPE&
%{
     (CSTYPE)Teigha.Core.Helpers.odrxCreateObjectInternalUniversal(typeof(CSTYPE),$iminput,false)  /*createInt 8_3*/ // csdirectorin for smart pointer
%}
%enddef


%define DECLARE_SMARTPTR(NAME)
SMARTPTR_TYPEMAP(NAME ## Ptr, NAME)
SMARTPTR_TYPEMAP(OdSmartPtr<NAME>, NAME)
%feature("action") NAME::~NAME
{
  arg1->release();
}
%enddef

%define DECLARE_SMARTPTR1(NAME)
DECLARE_SMARTPTR(NAME)
%ignore NAME::NAME;
%enddef

%define DECLARE_SMARTPTR2(NAME)
DECLARE_SMARTPTR(NAME)
%csmethodmodifiers NAME::createObject() "public new"
%enddef

%define DECLARE_SMARTPTR3(NAME)
DECLARE_SMARTPTR(NAME)
%csmethodmodifiers NAME::createObject() "public new"
%ignore NAME::NAME;
%enddef


%define DECLARE_SMARTPTR_NESTED(BASE, NAME)
SMARTPTR_TYPEMAP_(BASE::NAME ## Ptr, BASE::NAME, BASE.NAME)
SMARTPTR_TYPEMAP_(OdSmartPtr<BASE::NAME>, BASE::NAME, BASE.NAME)
%feature("action") BASE::NAME::~NAME
{
  arg1->release();
}
%enddef

%define DECLARE_SMARTPTR1_NESTED(BASE, NAME)
DECLARE_SMARTPTR_NESTED(BASE, NAME)
%ignore BASE::NAME::NAME;
%enddef


%define DECLARE_SMARTPTR_WITHNS(NS, NAME)
SMARTPTR_TYPEMAP_(NS::NAME ## Ptr, NS::NAME, NAME)
SMARTPTR_TYPEMAP_(OdSmartPtr<NS::NAME>, NS::NAME, NAME)
%feature("action") NS::NAME::~NAME
{
  arg1->release();
}
%enddef

%define DECLARE_SMARTPTR_WITHNS_RENAMED(NS, NAME)
SMARTPTR_TYPEMAP_(NS::NAME ## Ptr, NS::NAME, NS ## _ ## NAME)
SMARTPTR_TYPEMAP_(OdSmartPtr<NS::NAME>, NS::NAME, NS ## _ ## NAME)
%feature("action") NS::NAME::~NAME
{
  arg1->release();
}
%enddef

%define DECLARE_SMARTPTR1_WITHNS(NS, NAME)
DECLARE_SMARTPTR_WITHNS(NS, NAME)
%ignore NS::NAME::NAME;
%enddef

%define DECLARE_SMARTPTR1_WITHNS_RENAMED(NS, NAME)
DECLARE_SMARTPTR_WITHNS_RENAMED(NS, NAME)
%ignore NS::NAME::NAME;
%enddef


%define DECLARE_SMARTPTR1_SPEC_BASE_RELEASE(NAME, BASE)
DECLARE_SMARTPTR1(NAME)
%feature("action") NAME::~NAME
{
	((BASE*)arg1)->release();
}
%enddef
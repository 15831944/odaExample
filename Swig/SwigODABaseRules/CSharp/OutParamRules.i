%define OUT_PARAM(EXPR, CTYPE, CSTYPE)
%typemap(ctype, out="void *") EXPR "CTYPE"
%typemap(imtype,out="$typemap(cstype, $*1_ltype)") EXPR "out $typemap(cstype, $*1_ltype)"
%typemap(cstype,out="$typemap(cstype, $*1_ltype)") EXPR "out $typemap(cstype, $*1_ltype)"
%typemap(csin) EXPR "out $csinput"
%typemap(csout, excode=SWIGEXCODE) EXPR 
{
  $typemap(cstype, $*1_ltype) ret = $imcall; /*$typemap(cstype, $*1_ltype)*/
  $excode
  return ret;
} 
%typemap(in) EXPR
%{
  // in for OUT_PARAM
  $1 = ($1_ltype)$input; 
%}
%typemap(directorin) EXPR
%{
  // directorin for OUT_PARAM
  $input = (void*)&$1;
%}
%typemap(csdirectorin) EXPR "out $iminput"
%enddef


%define INOUT_PARAM_OBJ(EXPR, CTYPE, CSTYPE)
%typemap(ctype, out="void *") EXPR, const EXPR "CTYPE*"
%typemap(imtype, out="IntPtr") EXPR, const EXPR "IntPtr"
%typemap(cstype, out="CSTYPE") EXPR "CSTYPE"
%typemap(cstype, out="CSTYPE") const EXPR "CSTYPE"
%typemap(csin) EXPR, const EXPR "CSTYPE.getCPtr($csinput).Handle"
%typemap(in) EXPR, const EXPR
 %{ $1 = (CTYPE)$input; %} 
%typemap(directorout) EXPR, const EXPR
%{ 
  //directorout of INOUT_PARAM_OBJ
  $1 = $input;
%}
%typemap(directorin) EXPR, const EXPR
%{ 
  //directorin of INOUT_PARAM_OBJ
  $input = (void*)&$1;
%}           
%typemap(csdirectorout) EXPR, const EXPR
%{ 
  //csdirectorout of INOUT_PARAM_OBJ
  $cscall
%}
%typemap(csdirectorin) EXPR, const EXPR
%{ 
  //csdirectorin of INOUT_PARAM_OBJ
  new CSTYPE($iminput,true)
%}
%enddef


%define INOUT_PARAM(EXPR, CTYPE, CSTYPE)
%typemap(ctype, out="void *") EXPR "CTYPE"
%typemap(imtype, out="IntPtr") EXPR "ref CSTYPE"
%typemap(cstype, out="CSTYPE") EXPR "ref CSTYPE"
%typemap(csin) EXPR "ref $csinput"
%typemap(in) EXPR
%{ $1 = ($1_ltype)$input; %}
%enddef


%define OUT_PARAM_PTR(EXPR, CTYPE, CSTYPE)
%typemap(ctype, out="void *") EXPR "CTYPE"
%typemap(imtype, out="IntPtr") EXPR "out CSTYPE"
%typemap(cstype, out="CSTYPE") EXPR "out CSTYPE"
%typemap(csin) EXPR "out $csinput"
%typemap(in) EXPR
%{
  // in for OUT_PARAM
  $1 = ($1_ltype)$input; 
%}
%typemap(directorin) EXPR
%{
  // directorin for OUT_PARAM
  $input = (void*)&$1;
%}
%typemap(csdirectorin, 
 pre="    CSTYPE tmp_$iminput = new CSTYPE($iminput,true);",
 post="    $iminput = CSTYPE.getCPtr(tmp_$iminput).Handle;") EXPR "out tmp_$iminput /*csdirectorin of OUT_PARAM_PTR*/" 
%enddef

%define OUT_PARAM_OBJ(EXPR, CTYPE, CSTYPE)
%typemap(ctype, out="void *") EXPR "CTYPE"
%typemap(cstype, out="CSTYPE") EXPR "out $typemap(cstype, $*1_ltype)"
%typemap(imtype, out="IntPtr") EXPR "out IntPtr"
%typemap(csin,pre="IntPtr p_$csinput = IntPtr.Zero; /*OUT_PARAM_OBJ PRE*/", 
  post="MemoryTransaction mTrans_$csinput = MemoryManager.GetMemoryManager().GetCurrentTransaction();\n if(mTrans_$csinput != null)\n mTrans_$csinput.AddObject(Teigha.Core.Helpers.odCreateObjectInternal<$typemap(cstype, $*1_ltype)>(typeof($typemap(cstype, $*1_ltype)), p_$csinput, true)); \n $csinput = Teigha.Core.Helpers.odCreateObjectInternal<$typemap(cstype, $*1_ltype)>(typeof($typemap(cstype, $*1_ltype)), p_$csinput, mTrans_$csinput == null); \n /*OUT_PARAM_OBJ POST*/") EXPR "out p_$csinput"
%typemap(in) EXPR
%{
  // in for OUT_PARAM
  $1 = ($1_ltype)$input; 
%}
%typemap(directorin) EXPR
%{
  // directorin for OUT_PARAM
  $input = (void*)&$1;
%}
%typemap(csdirectorin, 
 pre="    $typemap(cstype, $*1_ltype) tmp_$iminput = new $typemap(cstype, $*1_ltype)($iminput,true);",
 post="    $iminput = $typemap(cstype, $*1_ltype).getCPtr(tmp_$iminput).Handle;") EXPR "out tmp_$iminput /*csdirectorin of OUT_PARAM_PTR*/" 
%enddef

%define OUT_PARAM_OBJ_AS_REF(EXPR, CTYPE, CSTYPE)
%typemap(ctype, out="void *") EXPR "CTYPE"
%typemap(cstype, out="$typemap(cstype, $*1_ltype)") EXPR "ref $typemap(cstype, $*1_ltype)"
%typemap(imtype, out="IntPtr") EXPR "ref IntPtr"
%typemap(csin,pre="IntPtr p_$csinput = $typemap(cstype, $*1_ltype).getCPtr($csinput).Handle; /*OUT_PARAM_OBJ_AS_REF PRE*/", 
  post="if ($typemap(cstype, $*1_ltype).getCPtr($csinput).Handle != p_$csinput)\n { \n typeof($typemap(cstype, $*1_ltype)).GetField(\"swigCMemOwn\", System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.NonPublic).SetValue($csinput, false); \nMemoryTransaction mTrans_$csinput = MemoryManager.GetMemoryManager().GetCurrentTransaction();\n if(mTrans_$csinput != null)\n mTrans_$csinput.AddObject(Teigha.Core.Helpers.odCreateObjectInternal<$typemap(cstype, $*1_ltype)>(typeof($typemap(cstype, $*1_ltype)), p_$csinput, true)); \n $csinput = Teigha.Core.Helpers.odCreateObjectInternal<$typemap(cstype, $*1_ltype)>(typeof($typemap(cstype, $*1_ltype)), p_$csinput, mTrans_$csinput == null); \n } \n /*OUT_PARAM_OBJ_AS_REF POST*/") EXPR "ref p_$csinput"
%typemap(in) EXPR
%{
  // in for OUT_PARAM_OBJ_AS_REF
  $1 = ($1_ltype)$input; 
%}
%typemap(directorin) EXPR
%{
  // directorin for OUT_PARAM_OBJ_AS_REF
  $input = (void*)&$1;
%}
%typemap(csdirectorin, 
 pre="    $typemap(cstype, $*1_ltype) tmp_$iminput = new $typemap(cstype, $*1_ltype)($iminput,true);",
 post="    $iminput = $typemap(cstype, $*1_ltype).getCPtr(tmp_$iminput).Handle;") EXPR "ref tmp_$iminput /*csdirectorin of OUT_PARAM_OBJ_AS_REF*/" 
%enddef


%define IN_PARAM(EXPR, CTYPE, CSTYPE)
  %typemap(ctype, out="void *") EXPR "CTYPE"
  %typemap(imtype, out="IntPtr") EXPR "CSTYPE"
  %typemap(cstype, out="CSTYPE") EXPR "CSTYPE"
  %typemap(csin) EXPR "$csinput"
  %typemap(in) EXPR
  %{ $1 = ($1_ltype)$input; %}
%enddef
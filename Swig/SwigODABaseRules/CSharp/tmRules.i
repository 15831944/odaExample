/*
Rules for using tm structure as System.DateTime.
Provided for only signatures : "tm" , "const tm &" , "tm &".
*/

struct tm
{
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight savings time flag
};

%typemap(cstype) tm , const tm & "System.DateTime"
%typemap(cstype, out="System.DateTime") tm & "ref System.DateTime"

%typemap(csout, excode=SWIGEXCODE) tm , const tm &
{
  tm tmp_ret = new tm($imcall, true);$excode
  if(tmp_ret == null)
    return default(DateTime);
  return new System.DateTime(tmp_ret.tm_year + 1900, tmp_ret.tm_mon + 1, tmp_ret.tm_mday ,tmp_ret.tm_hour, tmp_ret.tm_min ,tmp_ret.tm_sec);
}

%typemap(csin, 
         pre="    tm temp$csinput = new tm(){tm_year = $csinput.Year - 1900,tm_mon = $csinput.Month - 1, tm_mday = $csinput.Day, tm_hour = $csinput.Hour, tm_min = $csinput.Minute, tm_sec = $csinput.Second};"
        ) tm , const tm &
         "$csclassname.getCPtr(temp$csinput)"


%typemap(csin, 
         pre="    tm temp$csinput = new tm(){tm_year = $csinput.Year - 1900,tm_mon = $csinput.Month - 1, tm_mday = $csinput.Day, tm_hour = $csinput.Hour, tm_min = $csinput.Minute, tm_sec = $csinput.Second};",
		post="    $csinput = new System.DateTime(temp$csinput.tm_year + 1900, temp$csinput.tm_mon + 1, temp$csinput.tm_mday ,temp$csinput.tm_hour, temp$csinput.tm_min ,temp$csinput.tm_sec);",
	   cshin="ref $csinput"
        ) tm &
         "$csclassname.getCPtr(temp$csinput)"


%typemap(csvarin, excode=SWIGEXCODE2) tm , const tm & %{
    /* csvarin typemap code tm*/
    set {
      tm temp$csinput = new tm(){tm_year = $csinput.Year - 1900,tm_mon = $csinput.Month - 1, tm_mday = $csinput.Day, tm_hour = $csinput.Hour, tm_min = $csinput.Minute, tm_sec = $csinput.Second};
      $imcall;$excode
    } %}

%typemap(csvarout, excode=SWIGEXCODE2) tm , const tm & %{
    /* csvarout typemap code tm*/
    get {
      global::System.IntPtr cPtr = $imcall;
      tm tmp_ret = (cPtr == global::System.IntPtr.Zero) ? null : new tm(cPtr, $owner);$excode
	  if(tmp_ret == null)
	    return default(DateTime);
      return new System.DateTime(tmp_ret.tm_year + 1900, tmp_ret.tm_mon + 1, tmp_ret.tm_mday ,tmp_ret.tm_hour, tmp_ret.tm_min ,tmp_ret.tm_sec);
    } %}
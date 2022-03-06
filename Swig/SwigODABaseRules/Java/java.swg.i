%fragment("SWIG_JavaIntFromSize_t", "header") {
/* Check for overflow converting to Java int (always signed 32-bit) from (unsigned variable-bit) size_t */
SWIGINTERN jint SWIG_JavaIntFromSize_t(size_t size) {
  static const jint JINT_MAX = 0x7FFFFFFF;
  return (size > (size_t)JINT_MAX) ? -1 : (jint)size;
}
}


%typemap(jboxtype) bool,               const bool &               "Boolean"
%typemap(jboxtype) char,               const char &               "Character"
%typemap(jboxtype) signed char,        const signed char &        "Byte"
%typemap(jboxtype) unsigned char,      const unsigned char &      "Short"
%typemap(jboxtype) short,              const short &              "Short"
%typemap(jboxtype) unsigned short,     const unsigned short &     "Integer"
%typemap(jboxtype) int,                const int &                "Integer"
%typemap(jboxtype) unsigned int,       const unsigned int &       "Long"
%typemap(jboxtype) long,               const long &               "Integer"
%typemap(jboxtype) unsigned long,      const unsigned long &      "Long"
%typemap(jboxtype) long long,          const long long &          "Long"
%typemap(jboxtype) unsigned long long, const unsigned long long & "java.math.BigInteger"
%typemap(jboxtype) float,              const float &              "Float"
%typemap(jboxtype) double,             const double &             "Double"
%typemap(jboxtype) void*,              const void*                "Long"
%typemap(jboxtype) SWIGTYPE "$typemap(jstype, $1_type)"
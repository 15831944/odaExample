#if defined(SWIGJAVA)
%include "Java/java.swg.i"
#endif

#if defined(SWIGCSHARP)
#define OD_SWIGCSHARP
#elif defined(SWIGJAVA)
#define OD_SWIGJAVA
#endif

%ignore PRId64W;
%ignore PRIu64W;
%ignore PRIx64W;
%ignore PRIX64W;

/*SWIGWIN Macros declarated in swig run cmd-line (in CMakeList.txt)*/
/*In future need automate this part of code*/
#define UINT_MAX      0xFFFFFFFFUL
#if defined(PLATFORM_X32)
  #define ULONG_MAX     0xFFFFFFFFUL
#elif defined(PLATFORM_X64)
  #define ULONG_MAX     0xFFFFFFFFFFFFFFFFU
#else
  #error Undefined Platform x32, x64 or etc
#endif

#if defined(SWIGWIN)
  #define _MSC_VER SWIG_MSC_VER
  #define ODA_WINDOWS
#elif defined(SWIGMACOSX)
  #define __APPLE__ 1
  #define __GNUC__
#elif defined (SWIGLINUX)
  #define __linux__ 
#elif defined (SWIGANDROID)
  #define ANDROID   
#else
  #error Undefined Platform SWIGWIN, SWIGMACOSX, SWIGLINUX or etc
#endif
/*In future need automate this part of code*/

#ifdef ODA_WINDOWS
%include <windows.i>
#endif

#if defined(ANDROID) && defined(PLATFORM_X64)
typedef int OdInt32;
typedef unsigned int OdUInt32;
typedef long OdInt64;
typedef unsigned long OdUInt64;
#endif


/**
https://github.com/swig/swig/issues/568
https://github.com/google/or-tools/blob/stable/cmake/doc/swig.md#swig-int64_t-management-stuff
Workaround for compatible for:
typedef int OdInt32;
typedef unsigned int OdUInt32;
typedef long OdInt64;
typedef unsigned long OdUInt64;
**/
//#if defined(__linux__) && defined(PLATFORM_X64)
//  #define SWIGWORDSIZE64
//  #if defined(SWIGCSHARP)
//    #if defined(SWIGWORDSIZE64)
//      %define PRIMITIVE_TYPEMAP(NEW_TYPE, TYPE)
//      %clear NEW_TYPE;
//      %clear NEW_TYPE *;
//      %clear NEW_TYPE &;
//      %clear const NEW_TYPE &;
//      %apply TYPE { NEW_TYPE };
//      %apply TYPE * { NEW_TYPE * };
//      %apply TYPE & { NEW_TYPE & };
//      %apply const TYPE & { const NEW_TYPE & };
//      %enddef // PRIMITIVE_TYPEMAP
//      PRIMITIVE_TYPEMAP(long, long long);
//      PRIMITIVE_TYPEMAP(unsigned long, unsigned long long);
//    #undef PRIMITIVE_TYPEMAP
//    #endif // defined(SWIGWORDSIZE64)
//  #endif // defined(SWIGCSHARP)
//#endif
#if defined(__linux__) && defined(PLATFORM_X64) && defined(SWIGCSHARP)
//Nothing
#elif defined(__APPLE__) && defined(PLATFORM_X64) && defined(SWIGCSHARP)
#define ODCHAR_IS_INT16LE 0
#elif defined(SWIGWIN) && defined(SWIGCSHARP)
%include "OdPlatformSettings.h"
#elif defined(SWIGJAVA)
%include "OdPlatformSettings.h"
#else
%include "OdPlatformSettings.h"
#endif


#if defined(SWIGCSHARP)
#ifdef OD_INTPTR_UNIQUE
#undef OD_INTPTR_UNIQUE
#endif
#endif

#ifdef NO_SHARED_PTR
#undef NO_SHARED_PTR
#endif
#ifdef unique_ptr
#undef unique_ptr
#endif

#undef ODRX_ABSTRACT
#define ODRX_ABSTRACT
#undef ODRX_SEALED
#define ODRX_SEALED
#define sealed
#define ODA_ASSUME(x)
#define OD_TYPENAME3
#undef ODRX_OVERRIDE
#define ODRX_OVERRIDE
#define TD_USING(X)
#define ODRX_USING_HEAP_OPERATORS(X)
#define ODRX_HEAP_OPERATORS()
/*SWIGWIN Macros declarated in swig run cmd-line (in CMakeList.txt)*/
/*In future need automate this part of code*/


%define STRINGIZE(X)
#X
%enddef


#if defined(SWIGJAVA)
// For vararg handling in macros, from swigmacros.swg
#define %arg(Arg...)        Arg
#endif


#if defined(SWIGJAVA)
%rename (lessThan) operator<;
%rename (greaterThan) operator>;
//%rename (lessThanOrEqual) operator<=;
//%rename (greaterThanOrEqual) operator>=;
%rename (multiply) operator*;
%rename (multiplyAssign) operator*=;
%rename (add) operator+;
%rename (addAssign) operator+=;
%rename (subtract) operator-;
%rename (subtractAssign) operator-=;
%rename (divide) operator/;
%rename (divideAssign) operator/=;
%rename (isEqual) operator==;
%rename (isNotEqual) operator!=;
%rename (negation) operator!;
%rename (assign) operator=;
%rename (getItem) operator[];
%rename (asDouble) operator double;
%rename (asString) operator OdString;
%rename (asInt32) operator OdInt32;
%rename (asInt64) operator OdInt64;
%rename (asOdDbStubPointer) operator OdDbStub*; // should be ignored?
#endif

//#if defined(SWIGJAVA)
//%insert("wrapper")
//%{
//  static JNIEnv* curEnv;
//%}
//#endif


//#if defined(SWIGJAVA)
//%include "Java/EnumTypeMapCustom.i"
//#endif


#if defined(SWIGJAVA)
%rename (Wait) *::wait;
#endif


#if defined(SWIGJAVA)
#define ODCOLORREF OdUInt32
#endif


#if defined(SWIGJAVA)
%include "Java/JNI_TEMPLATE_TMAP_Rules.i"
#endif



#if defined(SWIGCSHARP)
#if SWIG_VERSION == 0x040002
#ifndef csdestruct
#define csdestruct csdispose
#endif
#ifndef csdestruct_derived
#define csdestruct_derived csdispose_derived
#endif
#elif SWIG_VERSION == 0x030012
#endif
#elif defined(SWIGJAVA)

#endif

%begin
%{
#include "OdPlatformSettings.h"
%}



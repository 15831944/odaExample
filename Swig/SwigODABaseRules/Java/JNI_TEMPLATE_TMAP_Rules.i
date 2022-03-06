#if defined(SWIGJAVA)
/*
For resolve problem when we have two template rules:
%template(GeMesh_intPair) std::pair<int, int >;
%template(std_pair_int_int) std::pair<int, int >;
So, before "%template() ;" need use JNI_TEMPLATE_T_MAPS macro.
*/
%define JNI_TEMPLATE_T_MAPS(CTYPE, JTYPE)
%typemap(jni)                  CTYPE, CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& "jlong"
%typemap(jstype)               CTYPE, CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& "JTYPE"
%typemap(jtype, nopgcpp = "1") CTYPE, CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& "long"
%typemap(javain)               CTYPE, CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& "JTYPE.getCPtr($javainput)"
%typemap(javadirectorout)      CTYPE, CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& "JTYPE.getCPtr($javacall)"
%typemap(javadirectorin)       CTYPE, CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& "new JTYPE($jniinput, false)"
%typemap(javaout) CTYPE*, CTYPE &, CTYPE &&, const CTYPE*, const CTYPE& {
    return new JTYPE($jnicall, $owner);
}
%typemap(javaout) CTYPE {
    return new JTYPE($jnicall, true);
}
%enddef
#endif
%define Insert_Python3_Comp_Helpers()
%insert("wrapper") 
%{ 
#if PY_VERSION_HEX >= 0x03000000
#define PyString_FromStringAndSize(arg1, arg2) PyUnicode_FromStringAndSize(arg1, arg2)
#endif 
%}
%enddef

%define Extend_method_getRealClassName(CTYPE)
#if defined(SWIGCSHARP)
%csmethodmodifiers CTYPE::getRealClassName "protected"
#elif defined(SWIGJAVA)
%csmethodmodifiers CTYPE::getRealClassName "protected"
#endif
%extend CTYPE
{
    static const char* getRealClassName(void* ptr)
    {
        CTYPE* resolved_ptr = (CTYPE*)ptr;
        const char* type_str = typeid(*resolved_ptr).name();
        return type_str;
    }
}
%enddef
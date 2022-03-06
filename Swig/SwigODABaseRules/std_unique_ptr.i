%define %typemaps_unique_ptr(UniquePtrType)
%feature("novaluewrapper") UniquePtrType;
#ifdef defined(SWIGPYTHON)
#error Not tested

%typemap(out) UniquePtrType %{
  $result = SWIG_NewPointerObj(new $1_ltype(std::move($1)), $&1_descriptor, SWIG_POINTER_OWN);
%}

#elif defined(SWIGCSHARP)

%typemap(out) UniquePtrType, UniquePtrType& %{
 $result = new $1_ltype(std::move($1));
%}
%typemap(out,optimal="1") UniquePtrType& %{
#ifndef ILLEGAL_CONSTRUCTION_COMPILE_ERROR
 #error Illegal construction
#else
 $result = new $1_ltype();
#endif
%}

#elif defined(SWIGJAVA)
 #error NotImplemented
#else
 #error NotImplemented
#endif

#ifdef defined(SWIGPYTHON)
 #error NotImplemented
#elif defined(SWIGCSHARP)
%typemap(in) UniquePtrType %{
    $1 = std::move(*($1_ltype*)$input);
  %}
#elif defined(SWIGJAVA)
 #error NotImplemented
#else
 #error NotImplemented
#endif
%enddef


namespace std
{
template <typename Type> struct unique_ptr;
%feature("novaluewrapper") unique_ptr;
%typemaps_unique_ptr(std::unique_ptr<Type>)
%newobject unique_ptr::release; 
template <typename Type>
  struct unique_ptr {
     typedef Type* pointer;

     explicit unique_ptr( pointer Ptr );
     unique_ptr (unique_ptr&& Right);
     template<class Type2, Class Del2> unique_ptr( unique_ptr<Type2, Del2>&& Right );
     unique_ptr( const unique_ptr& Right) = delete;


     pointer operator-> () const;
     pointer release ();
     void reset (pointer __p=pointer());
     void swap (unique_ptr &__u);
     pointer get () const;
     operator bool () const;

     ~unique_ptr();
  };
}

/*
Example of using:
%template(Name) std::unique_ptr<Type>;
*/

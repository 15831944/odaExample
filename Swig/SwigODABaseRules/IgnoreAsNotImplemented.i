%define IGNORE_AS_NOT_IMPLEMENTED(RETURN_TYPE, FUNC_FULLNAME, ARGS_SIGNATURE, FUNC_ATTRS)
%begin
%{
  RETURN_TYPE FUNC_FULLNAME(ARGS_SIGNATURE) FUNC_ATTRS
  {
    //Not contains C++ implementation for: RETURN_TYPE FUNC_FULLNAME(ARGS_SIGNATURE) FUNC_ATTRS;
    throw OdError("Not contains C++ implementation for: RETURN_TYPE FUNC_FULLNAME(ARGS_SIGNATURE) FUNC_ATTRS;");
  }
%}
%enddef


%define IGNORE_AS_NOT_IMPLEMENTED_4_desc(CLASS_FULLNAME)
%begin
%{
class OdRxClass;
%}
IGNORE_AS_NOT_IMPLEMENTED(%arg(OdRxClass*),%arg(CLASS_FULLNAME::desc),%arg(/*EMPTY*/),%arg(/*EMPTY*/))
%enddef
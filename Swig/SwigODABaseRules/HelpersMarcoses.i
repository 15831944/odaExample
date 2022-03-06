//This fix need if sequence header files incorrect.
//Sequence header files may be not resolve C++ compilation, because for example dependent header-file not obviously inclusion other headers which contains inforamtions of types which we need in dependent h-file.
//May be when we will auto-generate rules, that before include header list we will doing auto-insert forward declarations.
%define FixForwardDeclaration(CTYPE,CTEMPLATE_TYPE)
%begin
%{
class CTYPE;
typedef CTEMPLATE_TYPE ## <CTYPE> CTYPE ## Ptr;
%}
%enddef
%define FixForwardDeclaration_SMARTPTR(CTYPE)
FixForwardDeclaration(CTYPE,OdSmartPtr)
%enddef

%define %SPEC_CREATION(CLASS, BASE)
%feature("action") CLASS::CLASS()
%{ result = OdRxObjectImpl<CLASS, BASE>::createObject().detach(); /*SPEC_CREATION*/%}
%feature("action") CLASS::~CLASS
{
  /*SPEC_CREATION*/
	((BASE*)arg1)->release();
}
%enddef
%include "RxObjectImpl.h"
%define TEMPLATE_FROM_OdRxObjectImpl(TCLASS)
%nodefaultdtor OdRxObjectImpl<TCLASS>;
%nodefaultctor OdRxObjectImpl<TCLASS>;
%ignore OdRxObjectImpl::OdRxObjectImpl;
%template(OdRxObjectImpl_ ## TCLASS) OdRxObjectImpl<TCLASS>;
%enddef
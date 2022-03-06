%include "typemaps.i"
%include "ODA_Python3_CompHelpers.i"

Insert_Python3_Comp_Helpers()

%feature("compactdefaultargs");

%{
#include "ODA_PyMemManagerExportDef.h"
#include "ODA_PyMemoryTransaction.h"
#include "ODA_PyMemoryManager.h"
%}


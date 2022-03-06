/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "ODA_PyMemManagerExportDef.h"
#include <memory>

#if defined(_DEBUG) && defined(SWIG_PYTHON_INTERPRETER_NO_DEBUG)
/* Use debug wrappers with the Python release dll */
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

class ODA_PyMemoryTransaction;
typedef std::shared_ptr<ODA_PyMemoryTransaction> ODA_PyMemoryTransactionPtr;

class PY_MEM_MANAGER_EXPORT  ODA_PyMemoryTransaction
{
public:
  friend class ODA_PyMemoryManager;
  ~ODA_PyMemoryTransaction();

  void AddObject(PyObject* newObj);

  void DeleteObjects();
private:
  ODA_PyMemoryTransaction();

  static ODA_PyMemoryTransactionPtr CreateMemoryTransaction();

  std::shared_ptr<std::vector<PyObject*>> ObjectList;
};


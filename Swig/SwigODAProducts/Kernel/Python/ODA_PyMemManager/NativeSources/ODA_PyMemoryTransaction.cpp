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

#include "ODA_PyMemoryTransaction.h"
#include <map>

void ODA_PyMemoryTransaction::DeleteObjects()
{
  for (int i = ObjectList->size() - 1; i >= 0; i--)
  {
    PyObject* pyObj = ObjectList->at(i);
    if (!PyObject_CallMethod(pyObj, (char *)"__swig_destroy__", (char *)"(O)", (PyObject *)pyObj))
      throw new std::exception("ODA_PyMemoryTransaction::DeleteObjects: cannot execute __swig_destroy__ for PyObject");
    Py_XDECREF(pyObj);
  }
  ObjectList->clear();
}

ODA_PyMemoryTransaction::ODA_PyMemoryTransaction()
{
  ObjectList = std::make_shared<std::vector<PyObject*>>();
}

ODA_PyMemoryTransactionPtr ODA_PyMemoryTransaction::CreateMemoryTransaction() {
  return std::shared_ptr<ODA_PyMemoryTransaction>(new ODA_PyMemoryTransaction());
}

ODA_PyMemoryTransaction::~ODA_PyMemoryTransaction()
{
}

void ODA_PyMemoryTransaction::AddObject(PyObject * newObj)
{
  if (NULL != newObj)
  {
    Py_XINCREF(newObj);
    ObjectList->push_back(newObj);
  }
}

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

#ifndef MGMODULEBASE_INCLUDED_
#define MGMODULEBASE_INCLUDED_

#include "MgdExports.h"
#include "RxObject.h"
#include "RxModule.h"
#include <vector>
#include <vcclr.h>
#include <gcroot.h>
#include "Ed/EdCommandStack.h"
#include "StaticRxObject.h"

using namespace System;

namespace Teigha
{
  namespace Runtime
  {
    ref class DisposableWrapper;
  }
}

class MGD_EXPORT ManagedFactoryBase : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(ManagedFactoryBase);
  virtual gcroot<Teigha::Runtime::DisposableWrapper^> createRCW(OdRxObject* unmanagedPointer, bool autoDelete) = 0;
  virtual bool isManaged() { return false; }
  virtual ~ManagedFactoryBase() {}
};

/** \details
  This class provides connection between native and managed classes.
  When we read an object from the .dwg, we call a native function, so its class comes to us as a cpp class from the native function.
  Now to know, which wrapper class corresponds the native class returned from the native function,
  we use pairs managed-native, which are registered by adding new OdMgObjectFactory<managed,native>() class to _factories vector.
  When we have pointer to native class, and it is inherited in hierarchy from OdRxObject, we can see which casts are registered on this native type,
  and, by using OdMgObjectFactory, get the managed type and create the managed object.
*/
template <typename RCW, typename ImpObj>
class OdMgObjectFactory : public OdStaticRxObject<ManagedFactoryBase>
{
public:
  gcroot<Teigha::Runtime::DisposableWrapper^> createRCW(OdRxObject* unmanagedPointer, bool autoDelete)
  {
    return gcnew RCW(System::IntPtr(static_cast<ImpObj*>(unmanagedPointer)), autoDelete);
  }

  OdMgObjectFactory()
  {
    ImpObj::desc()->addX(ManagedFactoryBase::desc(), this);
  }

  ~OdMgObjectFactory()
  {
    if (ImpObj::desc())
    {
      ImpObj::desc()->delX(ManagedFactoryBase::desc());
    }
  }
};

#define MGD_REGISTER_FACTORY(_mgdClass, _nativeClass) \
  _factories.push_back(new OdMgObjectFactory<_mgdClass, _nativeClass>())

/** \details
  Abstract class representing one managed module of the library, like TD_Mgd, TD_MgdBrep, TD_MgdDbConstraints.
*/
class ManagedModuleBase : public OdRxModule
{
protected:
  std::vector<ManagedFactoryBase*> _factories;

  struct RxModules : public std::vector<OdRxModulePtr>
  {
    RxModules& operator +=(OdRxModulePtr module)
    {
      push_back(module);
      return *this;
    }
  } _modules;

public:
  virtual void initApp() = 0;
  virtual void uninitApp()
  {
    for (unsigned i = 0; i < _factories.size(); ++i)
      delete _factories[i];

    _modules.clear();
  }
};

/*
  If one of the calls to register factory fails, be sure that rxInit was called for this class
  before registration is called. This can happen for classes, which belong to other modules.
  For them module should be loaded before registration of factory is called.
*/
#endif

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

#ifndef _SCENARIO_ENGINE_ENGINE_INITIALIZER_H_
#define _SCENARIO_ENGINE_ENGINE_INITIALIZER_H_

#include "SharedPtr.h"
#include "diagnostics.h"

namespace ScenarioEngine
{
  template<class TAppServices>
  class ScenarioEngineLazyLoad
  {
  public:
    ScenarioEngineLazyLoad()
    {
      odrxInitialize(&svcs);
      odDbRootInitialize();
    }

    virtual ~ScenarioEngineLazyLoad()
    {
      odDbRootUninitialize();
      odrxUninitialize();

      LogMemoryInfoForCurrentProcess();
    }

    TAppServices& getService()
    {
      return svcs;
    }


  private:
    OdStaticRxObject<TAppServices> svcs;
  };
}

namespace ScenarioEngine
{
  template<class TAppServices>
  class ScenarioEngineInitializer
  {
  public:
    ScenarioEngineInitializer()
    {
      odSetAssertFunc(ScenarioAssert);
    }

    virtual ~ScenarioEngineInitializer() 
    {
    }

    TAppServices& getAppService() 
    {
      if (serviceLazyLoad.isNull())
      {
        serviceLazyLoad = new ScenarioEngineLazyLoad<TAppServices>();
        onServiceInited(serviceLazyLoad->getService());
      }

      return serviceLazyLoad->getService();
    }

  protected:
    virtual void onServiceInited(TAppServices& serviceInstance) = 0;

  private:
    static void ScenarioAssert(const char* expression, const char* fileName, int nLineNo)
    {
      OdString message;
      message.format(L"\n!!! Assertion failed: \"%s\"\n    file: %ls, line %d\n", OdString(expression).c_str(), OdString(fileName).c_str(), nLineNo);
      printConsoleString(message);
    }

  private:
    OdSharedPtr<ScenarioEngineLazyLoad<TAppServices> > serviceLazyLoad;
  };
}

#endif

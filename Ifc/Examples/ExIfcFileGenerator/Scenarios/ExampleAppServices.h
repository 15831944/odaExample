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

#ifndef _EXAMPLE_APPSERVICES_H_
#define _EXAMPLE_APPSERVICES_H_

#include "scenario/ScenarioEngineAppServices.h"

namespace ExampleScenario
{
  template<class HostAppServices>
  class ExampleAppServices
    : public ScenarioEngine::AppServices<HostAppServices>
  {
  protected:
    ODRX_USING_HEAP_OPERATORS(HostAppServices);

  public:
    virtual ~ExampleAppServices();

    OdString getFileName() const;
    void setFileName(const OdString& fileName);

  private:
    OdString m_fileName;
  };
}

namespace ExampleScenario
{
  template<class HostAppServices>
  inline ExampleAppServices<HostAppServices>::~ExampleAppServices()
  {
  }

  template<class HostAppServices>
  OdString ExampleAppServices<HostAppServices>::getFileName() const
  {
    return m_fileName;
  }

  template<class HostAppServices>
  void ExampleAppServices<HostAppServices>::setFileName(const OdString& fileName)
  {
    ScenarioEngine::AppServices<HostAppServices>::setDirectory(fileName , m_fileName);
  }
}

#endif //_EXAMPLE_APPSERVICES_H_

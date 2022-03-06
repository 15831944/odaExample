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

#ifndef _DAI_PERF_SCENARIO_H_
#define _DAI_PERF_SCENARIO_H_

#include "TestUtilityAsserts.h"
#include "OdPerfTimer.h"
#include "daiModel.h"
#include "daiEntity.h"
#include "daiRepository.h"
#include "MemoryStream.h"

#define SCHEMA_ENTITIES_MULTIPLIER 100

namespace PerfScenarios
{
  namespace
  {
    void putAttr(OdDAI::ApplicationInstance* pAppInstance, OdDAI::Entity* pEntity, OdRxValue attrValue)
    {
      OdArray<OdDAI::AttributePtr>  attrsArray = pEntity->attributes().getArray();

      for (auto attr : attrsArray)
      {
        if (OdDAI::ExplicitAttribute::cast(attr).isNull())
          continue;
        pAppInstance->putAttr(attr->name(), attrValue);
      }
      OdArray<OdDAI::Entity*> superTypesArray = pEntity->supertypes().getArray();
      for (auto st : superTypesArray)
      {
        putAttr(pAppInstance, st, attrValue);
      }
    }

    void getAttr(OdDAI::ApplicationInstance* pAppInstance, OdDAI::Entity* pEntity, OdRxValue attrValue)
    {
      OdArray<OdDAI::AttributePtr>  attrsArray = pEntity->attributes().getArray();

      for (auto attr : attrsArray)
      {
        if (OdDAI::ExplicitAttribute::cast(attr).isNull())
          continue;
        attrValue = pAppInstance->getAttr(attr->name());
      }
      OdArray<OdDAI::Entity*> superTypesArray = pEntity->supertypes().getArray();
      for (auto st : superTypesArray)
      {
        getAttr(pAppInstance, st, attrValue);
      }
    }
  }

  /** \details
  The base class for performance unit tests.
  */
  class PerfScenarioBase
  {
  public:
    PerfScenarioBase()
    {
    }

    virtual ~PerfScenarioBase()
    {
    }

    virtual bool run() = 0;
  };

  /** \details
  A performance test for checking the creation of explicit atrtibutes for all schema entities.
  */
  class PerfInstancesCreation : public PerfScenarioBase
  {
  public:

    PerfInstancesCreation(OdDAI::Model* pModel, OdPerfTimerBase* pPerfTimer)
      : PerfScenarioBase()
      , m_pModel(pModel)
      , m_pPerfTimer(pPerfTimer)
    {
    }

    bool run() override
    {
      auto entities  = m_pModel->underlyingSchema()->entities();

      m_pPerfTimer->start();

      for (auto it = entities->newIterator(); it->next();)
      {
        for (int i = 0; i < SCHEMA_ENTITIES_MULTIPLIER; ++i)
        {
          OdDAI::EntityPtr pEntity = it->object();
          if (!pEntity->instantiable())
            break;
          m_pModel->appendEntityInstance(m_pModel->createEntityInstance(pEntity->name()));
        }
      }
      m_pPerfTimer->stop();

      return true;
    }

  private:
    OdDAI::ModelPtr m_pModel;
    OdPerfTimerBase* m_pPerfTimer;
  };

  /** \details
  A performance test for checking the creation and filling of explicit atrtibutes for all schema entities.
  */
  class PerfInstancesCreationAndFilling : public PerfScenarioBase
  {
  public:

    PerfInstancesCreationAndFilling(OdDAI::Model* pModel, OdPerfTimerBase* pPerfTimer)
      : PerfScenarioBase()
      , m_pModel(pModel)
      , m_pPerfTimer(pPerfTimer)
    {
    }

    bool run() override
    {
      OdRxValue attrValue;
      auto entities = m_pModel->underlyingSchema()->entities();

      m_pPerfTimer->start();

      for (auto it = entities->newIterator(); it->next();)
      {
        for (int i = 0; i < SCHEMA_ENTITIES_MULTIPLIER; ++i)
        {
          OdDAI::EntityPtr pEntity = it->object();
          if (!pEntity->instantiable())
            break;
          OdDAI::ApplicationInstancePtr pAppInstance = m_pModel->createEntityInstance(pEntity->name());
          if (pAppInstance.isNull())
            break;
          putAttr(pAppInstance, pEntity, attrValue);
          m_pModel->appendEntityInstance(pAppInstance);
        }
      }
      m_pPerfTimer->stop();
      return true;
    }

  private:
    OdDAI::ModelPtr m_pModel;
    OdPerfTimerBase* m_pPerfTimer;
  };

  /** \details
  A performance test for checking the getting data from explicit atrtibutes for all schema entities.
  */
  class PerfInstanceAttributesGetting : public PerfScenarioBase
  {
  public:

    PerfInstanceAttributesGetting(OdDAI::Model* pModel, OdPerfTimerBase* pPerfTimer)
      : PerfScenarioBase()
      , m_pModel(pModel)
      , m_pPerfTimer(pPerfTimer)
    {
    }

    bool run() override
    {
      OdRxValue attrValue;

      auto entities = m_pModel->underlyingSchema()->entities();

      for (auto it = entities->newIterator(); it->next();)
      {
        OdDAI::EntityPtr pEntity = it->object();
        if (!pEntity->instantiable())
          continue;
        OdDAI::ApplicationInstancePtr pAppInstance = m_pModel->createEntityInstance(pEntity->name());
        if (pAppInstance.isNull())
          continue;
        putAttr(pAppInstance, pEntity, attrValue);
        m_pModel->appendEntityInstance(pAppInstance);
      }

      m_pPerfTimer->start();

      for (auto it = m_pModel->newIterator(); !it->done(); it->step())
      {
        for (int i = 0; i < SCHEMA_ENTITIES_MULTIPLIER; ++i)
        {
          OdDAI::ApplicationInstancePtr pAppInstance = it->id().openObject();
          OdDAI::EntityPtr pEntity = m_pModel->getEntityDefinition(pAppInstance->typeName());

          getAttr(pAppInstance, pEntity, attrValue);
        }
      }

      m_pPerfTimer->stop();
      return true;
    }

  private:
    OdDAI::ModelPtr m_pModel;
    OdPerfTimerBase* m_pPerfTimer;
  };

  /** \details
  A performance test for checking the reading repository from the buffer.
  */
  class PerfModelReading : public PerfScenarioBase
  {
  public:
    PerfModelReading(OdDAI::Repository* pRepository, OdStreamBuf* pStream, OdPerfTimerBase* pPerfTimer)
      : PerfScenarioBase()
      , m_pRepository(pRepository)
      , m_pStream(pStream)
      , m_pPerfTimer(pPerfTimer)
    {
    }

    bool run() override
    {
      m_pPerfTimer->start();

      TEST_ASSERT(m_pRepository->readStream(m_pStream) == eOk);

      m_pPerfTimer->stop();
      return true;
    }

  private:
    OdDAI::RepositoryPtr m_pRepository;
    OdStreamBufPtr m_pStream;
    OdPerfTimerBase* m_pPerfTimer;
  };

  /** \details
  A performance test for checking the writing repository to the buffer.
  */
  class PerfModelWriting : public PerfScenarioBase
  {
  public:
    PerfModelWriting(OdDAI::Repository* pRepository, OdPerfTimerBase* pPerfTimer)
      : PerfScenarioBase()
      , m_pRepository(pRepository)
      , m_pPerfTimer(pPerfTimer)
    {
    }

    bool run() override
    {
      OdStreamBufPtr pStream = OdMemoryStream::createNew();

      m_pPerfTimer->start();

      TEST_ASSERT(m_pRepository->writeStream(pStream) == eOk);

      m_pPerfTimer->stop();
      return true;
    }

  private:
    OdDAI::RepositoryPtr m_pRepository;
    OdPerfTimerBase* m_pPerfTimer;
  };
}

#endif //_DAI_PERF_SCENARIO_H_

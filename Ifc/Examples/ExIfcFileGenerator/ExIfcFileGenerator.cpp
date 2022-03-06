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

#define IFC_GEOM_MODULE_ENABLE
#define IFC_FACET_MODELER_MODULE_ENABLE

#include "ExampleScenariosEngine.h"
#include "ScenarioDeclarations.h"

FILE_GENERATOR_METHOD_DATA_DECALRE();

#undef FILE_GENERATOR_SCENARIO_DEF
#define FILE_GENERATOR_SCENARIO_DEF(handler, name, number)  { &handler, OD_T(#name), number },

static FileGeneratorExampleScenario::ScenarioDef scenarios_data[] =
{
  { FileGeneratorExampleScenario::PScenarioFunc(), L"", 0 },
  FILE_GENERATOR_METHOD_DATA_DECALRE()
};

int test_od_main(int argc, test_arg_char* argv[])
{
  std::vector<OdSharedPtr<ScenarioEngine::Scenario> > scenarioCollection;
  FileGeneratorExampleScenario::FileGeneratorDataHandler dataHandler(scenarios_data, sizeof(scenarios_data) / sizeof(scenarios_data[0]));

  scenarioCollection.push_back(ScenarioEngine::ScenarioPtr(new FileGeneratorExampleScenario::FileGeneratorScenarioGetNames(dataHandler)));
  scenarioCollection.push_back(ScenarioEngine::ScenarioPtr(new FileGeneratorExampleScenario::FileGeneratorScenarioRunByNumberWoGeom(dataHandler)));
  scenarioCollection.push_back(ScenarioEngine::ScenarioPtr(new FileGeneratorExampleScenario::FileGeneratorScenarioRunByNameWoGeom(dataHandler)));
  scenarioCollection.push_back(ScenarioEngine::ScenarioPtr(new FileGeneratorExampleScenario::FileGeneratorScenarioRunAllWoGeom(dataHandler)));

  int errorCode = 0;
  switch (runScenarios(scenarioCollection, argc, argv, errorCode))
  {
  case ScenarioEngine::runSuccess:
    {
      return 0;
    }
    break;
  case ScenarioEngine::runFailed:
    {
      return errorCode;
    }
    break;
  case ScenarioEngine::nobodyRun:
    {
      showScenariosInfo(scenarioCollection, L"ExIfcFileGenerator");
      return 10;
    }
    break;
  }

  return -1;
}


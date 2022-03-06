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

#include "OdaCommon.h"
#include "ExIfcTutorial_05.h"
#include "daiUtils/daiUtils.h"

int Tutorial_05(int argc, wchar_t* argv[], const MyServices& svcs)
{
  OdString ifcFileName(argv[2]);

  OdIfcFilePtr pFile = svcs.createDatabase();
  OdResult res = pFile->readFile(ifcFileName);

  if (res == eOk)
  {
    odPrintConsoleString(L"\nFile opened successfully.\n");
  }
  else
  {
    odPrintConsoleString(L"\nFile open error. Press any key to finish...");
    getchar();
    return res;
  }
  
  odPrintConsoleString(L"\nRetreiving property information");

  OdIfcModelPtr pModel = pFile->getModel();

  OdString stepLine;
  OdDAI::ApplicationInstancePtr pInstance;
  OdDAI::InstanceIteratorPtr pIt = pModel->newIterator();
  while (!pIt->done())
  {
    if (pIt->id().isValid())
    {
      stepLine = OdDAI::Utils::getStepLine(pIt->id().openObject()).c_str();
      odPrintConsoleString("\n" + stepLine);
    }
    pIt->step();
  }
  odPrintConsoleString(L"\n\nProcess finished\n");
  return eOk;
}

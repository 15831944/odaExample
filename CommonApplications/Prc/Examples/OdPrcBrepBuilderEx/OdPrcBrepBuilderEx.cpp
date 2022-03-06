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

#include "PrcExamplesCommon.h"
#include "OdModuleNames.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcBrepData.h"
#include "PrcWithTDExamplesCommon.h"
#include "BBExStart.h"
#include "PrcBrepModel.h"

/************************************************************************/
/* Define a module map for statically linked modules:                   */
/************************************************************************/
#ifndef _TOOLKIT_IN_DLL_

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(RasterExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);


ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName, OdPrcModule)
ODRX_END_STATIC_MODULE_MAP()

#endif

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int nRes = 0; // Return value for main

                /**********************************************************************/
                /* Overload OdTimeStamp::getLocalTime internal implementation         */
                /**********************************************************************/
  g_pLocalTimeFunc = getLocalTime;

  /**********************************************************************/
  /* Set customized assert function                                     */
  /**********************************************************************/
  odSetAssertFunc(MyAssert);

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif


                          /**********************************************************************/
                          /* Create a Services object                                           */
                          /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nOdPrcBrepBuilderEx developed using %ls ver %ls",
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  BBCreationMode mode;
  bool bInvalidArgs = (argc != 3);
  if (bInvalidArgs)
  {
    nRes = 1;
  }
  else
  {
    OdString s(argv[1]);
    #define ODPRCBBEXCASE(a, b, c, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) if (s == #a) mode = k##a; else
    #include "ExCases.h"
    bInvalidArgs = true;
  }

  if (bInvalidArgs)
  {
    odPrintConsoleString(L"\n\nusage: nOdPrcBrepBuilderEx <filename>");
    #define ODPRCBBEXCASE(a, b, c, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) odPrintConsoleString(L"\n\t%ls - %ls", OdString(#a).c_str(), OdString(b).c_str());
    #include "ExCases.h"
    odPrintConsoleString(L"\n<filename> - output .prc file\n");

    return nRes;
  }

  /**********************************************************************/
  /* Initialize ODA Platform                                            */
  /**********************************************************************/
  odrxInitialize(&svcs);

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);

  try
  {
    OdString prcName(argv[2]);
    OdPrcFilePtr pFile = createTopologyCommon();
    OdPrcFileStructurePtr pFS = pFile->fileStructures().last();
    OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
    OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pRootPO);
    OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);

    OdGeExtents3d extents(OdGePoint3d::kOrigin, OdGePoint3d(1, 1, 1));
    pPD->boundingBox().box() = extents;
    OdPrcBrepModelPtr pRI = createRI<OdPrcBrepModel>(*pFS, *pPD);
    OdPrcBrepDataPtr pOldData = createBody<OdPrcBrepData>(*pFS, *pTopoContext, *pRI);
    pOldData->boundingBox().box() = extents;
    pOldData->contentBody().setBoundingBoxBehaviour(2);

    OdStreamBufPtr pStreamBuf = svcs.createFile(prcName, (Oda::FileAccessMode)(Oda::kFileWrite), Oda::kShareDenyNo, Oda::kCreateAlways);

    OdPrcFileStructureTree &tree = pFS->fileStructureTree();
    OdPrcObjectIdArray &partArr = tree.partDefinition();
    OdPrcPartDefinitionPtr part = partArr.last().safeOpenObject(kForWrite);

    OdPrcBrepDataPtr pNewData = OdPrcBrepBuilderExStart(mode, svcs, *pFS, extents);
    if (pNewData.isNull())
      throw OdError(eNullObjectPointer);

    const OdPrcConnexPtrArray &connexes = pNewData->connex();
    OdPrcConnexPtrArray::const_iterator it = connexes.begin();
    for (; it != connexes.end(); ++it)
    {
      pOldData->addConnex(*it);
    }

    part->boundingBox().box() = extents;
    pOldData->boundingBox().box() = extents;

    OdPrcBrepModelPtr pBrepModel = part->representationItem().last().openObject(kForWrite);
    ODA_VERIFY(pBrepModel->updateIsClosedFlag() == eOk);

    pFile->writeFile(pStreamBuf);
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch (...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize ODA Platform                                          */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}

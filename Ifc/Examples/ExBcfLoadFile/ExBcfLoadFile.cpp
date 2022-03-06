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
/************************************************************************/
/* This console application loads BCF file.                             */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/* ExBcfLoadFile <folderpath> <filename>                                */
/*                                                                      */
/************************************************************************/

#include "OdaCommon.h"
#include "StaticRxObject.h"

#include "ExIfcHostAppServices.h"
#include "IfcExamplesCommon.h"

#include "BcfSession.h"
#include "BcfDataAccessorXml.h"
#include "BcfArchive.h"
#include "BcfArchiveFolder.h"
#include "BcfTopicFolder.h"
#include "BcfMarkup.h"
#include "BcfHeader.h"
#include "BcfTopic.h"
#include "BcfComment.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

BCF_EXPORT OdResult odBcfInitialize();
BCF_EXPORT OdResult odBcfUninitialize();

//
// Define module map for statically linked modules:
//
#ifndef _TOOLKIT_IN_DLL_
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdBcfModule);
  ODRX_BEGIN_STATIC_MODULE_MAP()                 
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdBcfModuleName, OdBcfModule)
  ODRX_END_STATIC_MODULE_MAP()
#endif

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{

  /**********************************************************************/
  /* Command line parameters description                                */
  /**********************************************************************/
  if(argc < 3)
  {
    odPrintConsoleString(L"\nExBcfLoadFile sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: ExBcfLoadFile <filename> <outfilename> [workfolder]\n");
    odPrintConsoleString(L"\t <filename> - BCF archive to open.\n");
    odPrintConsoleString(L"\t <outfilename> - write BCF file if outfilename is not empty.\n");
    odPrintConsoleString(L"\t [workfolder] - work folder for BCF archive content, optional.\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    return 1;
  }

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif
 
  // create a service
  OdStaticRxObject< MyServices > svcs;

  OdString fileName = argv[1];
  OdString outFileName = argv[2];
  OdString workFolder = argc > 3 ? argv[3] : svcs.getTemporaryPath();

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize BCF                                                     */
  /**********************************************************************/
  odBcfInitialize();

  try
  {
    OdBcf::OdBcfDataAccessorPtr pAccessor = OdBcf::OdBcfDataAccessorXml::createObject(workFolder);
    const OdBcf::OdBcfArchivePtr pArchive = pAccessor->getArchive(fileName);
    OdString rootDir = pArchive->getRootDir()->getFolder();

    //
    // Dump topics
    //
    const OdBcf::OdBcfTopicFolderMap& topicFolders = pArchive->getTopics();
    for (const auto &node : topicFolders)
    {
      OdString strGUID = node.first.toString();
      odPrintConsoleString(L"\nTopicFolder GUID: %s\n", strGUID.c_str());

      OdBcf::OdBcfTopicFolderPtr topicFolder = node.second;

      OdBcf::OdBcfMarkupPtr markup = topicFolder->getMarkup();

      const OdBcf::OdBcfTopicPtr topic = markup->getTopic();
      odPrintConsoleString(L" GUID: %s\n", topic->getGuid().toString().c_str());
      odPrintConsoleString(L" Title: %s\n", topic->getTitle().c_str());
      odPrintConsoleString(L" Author: %s\n", topic->getCreationAuthor().c_str());
      odPrintConsoleString(L" Priority: %s\n", topic->getPriority().c_str());

      const OdBcf::OdBcfCommentArray& comments = markup->getComment();
      if (comments.size() > 0)
      {
        odPrintConsoleString(L" Comments (%d):\n", comments.size());
        for (OdBcf::OdBcfCommentPtr comment : comments)
        {
          // ...
        }
      }

      odPrintConsoleString(L"==================================\n");
    }

    if (!outFileName.isEmpty())
    {
      odPrintConsoleString(L"Writing BCF Project to: %s...", outFileName.c_str());
      if (eOk == pAccessor->putArchive(outFileName, pArchive))
      {
        odPrintConsoleString(L" ok\n");
      }
      else
      {
        odPrintConsoleString(L" failed\n");
      }
    }
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\nError: %ls\n", e.description().c_str());
  }
  catch (...)
  {
    odPrintConsoleString(L"\nUnknown Error.\n");
  }

  /**********************************************************************/
  /* Uninitialize BCF                                                   */
  /**********************************************************************/
  odBcfUninitialize();

  /**********************************************************************/
  /* Uninitialize Runtime Extension environment                         */
  /**********************************************************************/
  odDbRootUninitialize();
  ::odrxUninitialize();

  return 0;
}

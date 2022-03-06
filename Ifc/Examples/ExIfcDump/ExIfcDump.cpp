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
/* This console application make dump of a IFC file.                    */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/* ExIfcDump <source filename/start directory> <target dump filename>   */
/*                                                                      */
/************************************************************************/

#include "OdaCommon.h"
#include "StaticRxObject.h"

#include "daiHeaderSection.h"
#include "daiHeader/daiHeaderEntities.h"
#include "daiEntity.h"
#include "daiHeaderSection.h"

#include "ExIfcDumpEntities.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

ODGI_EXPORT void odgiInitialize();
ODGI_EXPORT void odgiUninitialize();

#include "IfcExamplesCommon.h"
#include "ExIfcHostAppServices.h"

#include "IfcCore.h"
#include "IfcEntityTypes.h"

#include "DynamicLinker.h"
#include "RxInit.h"
#include "RxObjectImpl.h"
#include "RxDynamicModule.h"
#include "diagnostics.h"

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

#define STL_USING_SET
#define STL_USING_MAP
#include "OdaSTL.h"

//
// Define module map for statically linked modules:
//
#ifndef _TOOLKIT_IN_DLL_
  using namespace OdIfc;                                                             \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);                            \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);                     \
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)                 \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdThreadPoolModuleName, OdRxThreadPoolService)      \
  ODRX_END_STATIC_MODULE_MAP()
#endif

FILE* DumpStream;

static void customAssertFunc(const char* expr, const char* fileName, int nLine)
{
  printf(
    "Assertion has occurs:\n"
    " Expression: %s\n"
    " Filename: %s\n"
    " Line number: %d\n",
    expr, fileName, nLine);

  if (DumpStream)
  {
    fprintf(DumpStream, "%s (%s, line: %d)\n", expr, fileName, nLine);
  }
}

enum ExIfcBaseType {
  kGeom,
  kBIM
};

struct ExIfcEntInfo {
  OdString      m_typeName;   // Type name literal by OdIfcEntityType
  OdUInt32      m_ents;       // Total amount of entities of specified type
  OdUInt32      m_entsFiles;  // Total amount of files where specified entity appears
  ExIfcBaseType m_branch;     // Branch of file (BIM/Geometry)
};

class OdFileCollectionStatistics
{
public:

  //
  // Total amount of files
  //
  unsigned int m_numFiles;

  //
  // Amount of files where dumping wasn't finished by different reasons
  //
  unsigned int m_errorFiles;

  //
  // Entities statistics
  //
  std::map<OdIfc::OdIfcEntityType, ExIfcEntInfo> m_ents;

  OdFileCollectionStatistics()
    : m_numFiles(0)
    , m_errorFiles(0)
  {}

  //
  // Write results to the txt file
  //
  void writeToFile()
  {
    fwprintf(DumpStream, L"=========================================\n");
    fwprintf(DumpStream, L"Total files: %i\n", m_numFiles);
    fwprintf(DumpStream, L"Opened succesfully: %i\n", m_numFiles - m_errorFiles);
    fwprintf(DumpStream, L"Unsuccessful: %i\n", m_errorFiles);
    fwprintf(DumpStream, L"=========================================\n");

    //
    // Sort by amount of entities in total
    //
 std::multimap<OdUInt32, ExIfcEntInfo> stats_res;
    std::map<OdIfc::OdIfcEntityType, ExIfcEntInfo>::iterator ents_it = m_ents.begin();
    std::map<OdIfc::OdIfcEntityType, ExIfcEntInfo>::iterator ents_end = m_ents.end();
    while (ents_it != ents_end)
    {
      stats_res.insert(std::pair<OdUInt32, ExIfcEntInfo>(ents_it->second.m_ents, ents_it->second));
      ++ents_it;
    }

    fwprintf(DumpStream, L"Entity type, Branch, # entities, # files\n");
    OdString ifcBranchName;
    std::multimap<OdUInt32, ExIfcEntInfo>::reverse_iterator stats_it = stats_res.rbegin();
    std::multimap<OdUInt32, ExIfcEntInfo>::reverse_iterator stats_end = stats_res.rend();
    while (stats_it != stats_end)
    {
      if (stats_it->second.m_branch == kGeom)
        ifcBranchName = OD_T("GEOM");
      else
        ifcBranchName = OD_T("BIM");

      fwprintf(DumpStream, L"%s, %s, %i, %i\n",
        stats_it->second.m_typeName.c_str(),
        ifcBranchName.c_str(),
        stats_it->second.m_ents,
        stats_it->second.m_entsFiles);

      ++stats_it;
    }
  };

};
OdFileCollectionStatistics stats;

void DumpFile(OdIfcHostAppServices *pHostApp, const OdString &fileName, const OdString& version)
{
  //
  // Dump single file
  //
  try
  {
    fwprintf(DumpStream, L"Dump file: %s\n", fileName.c_str());
    odPrintConsoleString(L"Dump file: %s\n", fileName.c_str());

    if (version.iCompare("ANY"))
    {
      OdDAI::OdHeaderSectionPtr headerSection = pHostApp->getHeaderSection(fileName);
      if (!headerSection.isNull())
      {
        OdSmartPtr<OdDAI::FileSchema> pSchema = headerSection->getEntityByType(OdDAI::kFileSchema);

        if (pSchema.isNull())
        {
          fwprintf(DumpStream, L"File is invalid ... skip\n");
          return;
        }

        OdAnsiStringArray schemasCollection;
        pSchema->getSchemaIdentifiers(schemasCollection);

        if (version.iCompare(schemasCollection.at(0)))
        {
          fwprintf(DumpStream, L"File schema: %s ... skip\n", ((OdString)schemasCollection.at(0)).c_str());
          return;
        }
      }
      else
      {
        fwprintf(DumpStream, L"Error getting header section: %s\n", fileName.c_str());
        odPrintConsoleString(L"Error getting header section: %s\n", fileName.c_str());
        return;
      }
    }

    ++stats.m_numFiles;

    OdIfc::OdIfcEntityPtr pEnt;
    const OdDAI::EntityPtr pDef;
    OdIfcFilePtr pIfcFile = pHostApp->readFile(fileName);
    if (pIfcFile.isNull())
    {
      ++stats.m_errorFiles;
      fwprintf(DumpStream, L"File open error: OdIfcFile wasn't created\n");
      odPrintConsoleString(L"File open error: OdIfcFile wasn't created)\n");
      return;
    }

    OdIfcModelPtr pModel = pIfcFile->getModel();

    if (!pModel.isNull())
    {
      OdDAI::InstanceIteratorPtr it = pModel->newIterator();
      if (!it->done())
      {
        //
        // Collect file entities information
        //
        std::set<OdIfc::OdIfcEntityType> entities_in_file;

        OdIfc::OdIfcEntityType type_id;
        std::map<OdIfc::OdIfcEntityType, ExIfcEntInfo>::iterator stats_it;
        for (; !it->done(); it->step())
        {
          pEnt = it->id().openObject();
          if (pEnt.isNull())
          {
            OdUInt64 _handleVal = it->id().getHandle();
            fwprintf(DumpStream, L"File error: Empty cell for handle #%llu\n", _handleVal);
            odPrintConsoleString(L"File error: Empty cell for handle #%llu\n", _handleVal);
            continue;
          }

          type_id = pEnt->type();
          stats_it = stats.m_ents.find(type_id);

          if (stats_it == stats.m_ents.end())
          {
            ExIfcEntInfo ent;
            ent.m_typeName = pEnt->typeName();
            ent.m_ents = 1;
            ent.m_entsFiles = 0;

            if (pEnt->isKindOf(OdIfc::kIfcRepresentationItem) ||
                pEnt->isKindOf(OdIfc::kIfcProfileDef))
              ent.m_branch = kGeom;
            else
              ent.m_branch = kBIM;

            //
            // Uncomment the line to get entity definition of the entity
            //
            //pDef = pModel->getEntityDefinition(pEnt->typeName());

            stats.m_ents[type_id] = ent;
          }
          else
          {
            ++stats_it->second.m_ents;
          }
          entities_in_file.insert(type_id);
        }

        //
        // Finalize the process, OdIfcFile and underlying header section
        // and Model will be released.
        //
        pIfcFile = NULL;

        {
          std::set<OdIfc::OdIfcEntityType>::iterator it_inf = entities_in_file.begin();
          std::set<OdIfc::OdIfcEntityType>::iterator it_end = entities_in_file.end();
          while (it_inf != it_end)
          {

            std::map<OdIfc::OdIfcEntityType, ExIfcEntInfo>::iterator it = stats.m_ents.find(*it_inf);
            if (it != stats.m_ents.end())
            {
              ++it->second.m_entsFiles;
            }
            ++it_inf;
          }
        }
      }
      else
      {
        ++stats.m_errorFiles;
        fwprintf(DumpStream, L"File open error: empty model)\n");
        odPrintConsoleString(L"File open error: empty model)\n");
      }
    }
    else
    {
      ++stats.m_errorFiles;

      OdString schemaName;
      OdDAI::OdHeaderSectionPtr pHeaderSection = !pIfcFile.isNull() ? pIfcFile->getHeaderSection() : OdDAI::OdHeaderSectionPtr();

      if (!pHeaderSection.isNull())
      {
        OdSmartPtr<OdDAI::FileSchema> pSchema = pHeaderSection->getEntityByType(OdDAI::kFileSchema);

        if (!pSchema.isNull())
        {
          OdAnsiStringArray schemasCollection;
          pSchema->getSchemaIdentifiers(schemasCollection);
          schemaName = !schemasCollection.isEmpty() ? schemasCollection.at(0) : "";
        }
      }

      fwprintf(DumpStream, L"Can not open the file (Unsupported schema: %ls)\n", schemaName.c_str());
      odPrintConsoleString(L"Can not open the file (Unsupported schema: %ls)\n", schemaName.c_str());
    }
  }
  catch (...)
  {
    fwprintf(DumpStream, L"Exception in file '%s'\n", fileName.c_str());
    odPrintConsoleString(L"Exception in file '%s'\n", fileName.c_str());
    ++stats.m_errorFiles;
  }
}

bool isDir(OdString &szSource, bool &upperLevel)
{
  if (szSource.getLength() < 3)
  {
    upperLevel = true;
    return true;
  }
  if (szSource[szSource.getLength()-1] == '.')
  {
    upperLevel = true;
    return true;
  }

  upperLevel = false;
  int len = szSource.getLength();
  int pos = szSource.find(OD_T(".ifc"));
  if (pos < 1)
  {
    pos = szSource.find(OD_T(".IFC"));
    if (pos < 1)
    {
      pos = szSource.reverseFind(OdChar('.'));
      int posSlash = szSource.reverseFind(OdChar('\\'));
      if (pos > posSlash)
      {
        // Unsupported file extension
        upperLevel = true;
        return true;
      }
    }
  }
  return !(pos == len - 4);
}

void WalkAlongDirectories(OdIfcHostAppServices *pHostApp, OdString &dirName, const OdString& version)
{
  OdStringArray res;

  int pos = dirName.reverseFind('\\');
  if (pos != dirName.getLength() - 1)
    dirName += '\\';

  OdString maskPathName = dirName;
  maskPathName += "*.*";

#if defined(_WINRT)
  //TODO
#elif defined(ODA_WINDOWS)

  bool upperLevel = false;

  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = ::FindFirstFile(maskPathName.c_str(), &FindFileData);
  while (hFind != INVALID_HANDLE_VALUE)
  {
    OdString str = dirName + OdString(FindFileData.cFileName);
    res.append(str);
    if (isDir(str, upperLevel) == false)
    {
      DumpFile(pHostApp, str, version);
    }
    else
    if (upperLevel == false)
    {
      fwprintf(DumpStream, L"Dump directory: %s\n", dirName.c_str());
      odPrintConsoleString(L"Dump directory: %s\n", dirName.c_str());

      WalkAlongDirectories(pHostApp, str, version);
    }
    if (0 == ::FindNextFile(hFind, &FindFileData))
      break;
  }
#endif
}

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  ::odSetAssertFunc( customAssertFunc );

  /**********************************************************************/
  /* Command line parameters description                                */
  /**********************************************************************/
  if( argc < 3 || argc > 4)
  {
    odPrintConsoleString(L"\nExIfcDump sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: ExIfcDump <source filename/start directory> <target dump filename> [<schema version>]\n");
    odPrintConsoleString(L"\tsupported schema versions: Ifc2x3, Ifc4, Any\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    STD(cin).get();
    return 1;
  }

  OdString version = "ANY";
  if (argc == 4)
  {
    OdString strVersion = argv[3];
    if (!strVersion.iCompare("IFC2X3"))
      version = "IFC2X3";
    else if (!strVersion.iCompare("IFC4"))
      version = "IFC4";
    else if (strVersion.iCompare("ANY"))
    {
      odPrintConsoleString(L"Unsupported file schema\n");
      STD(cin).get();
      return 1;
    }
  }

  OdString szSource = argv[1], szDump = argv[2]; 

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  DumpStream = fopen( szDump, "w" );
  if( !DumpStream )
  {
    odPrintConsoleString( L"\nThe file %ls has not been opened\n", szDump.c_str() );
    return 1;
  }

  // write a title
  fwprintf( DumpStream, L"Dump of %s\n", szSource.c_str());
  fwprintf( DumpStream, L"\nResult file is %s\n", szDump.c_str());
 
  // create a service
  OdStaticRxObject< MyServices > svcs;

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize( &svcs );
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  try
  {
    /********************************************************************/
    /* Walk along file collection                                       */
    /********************************************************************/
    try
    {
      bool bUpper = false;
      if (isDir(szSource, bUpper))
      {
        if (!bUpper)
          WalkAlongDirectories(&svcs, szSource, version);
      }
      else
      {
        DumpFile(&svcs, szSource, version);
      }
    }
    catch (...)
    {
      ODA_ASSERT(0);
    }

    stats.writeToFile();
    fclose( DumpStream );
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\nODA BimIfc Error: %ls\n", e.description().c_str());
  }
  catch (...)
  {
    odPrintConsoleString(L"\nUnknown Error.\n");
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize Runtime Extension environment                         */
  /**********************************************************************/
  odDbRootUninitialize();
  ::odrxUninitialize();

  return 0;
}

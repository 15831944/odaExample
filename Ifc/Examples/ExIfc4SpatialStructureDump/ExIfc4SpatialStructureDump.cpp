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
/* This console application make dump of a IFC4 file                    */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/* ExIfc4SpatialStructureDump <target dump filename> [<output filename>]*/
/*                                                                      */
/************************************************************************/

#include "ExIfc4SpatialStructureDump.h"

#include "daiHeaderSection.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

ODGI_EXPORT void odgiInitialize();
ODGI_EXPORT void odgiUninitialize();

#include "IfcExamplesCommon.h"
#include "ExIfcHostAppServices.h"

#include "RxDynamicModule.h"

#include "DynamicLinker.h"

#include "OdDbStub.h"
#include <fstream>

#include "Ifc4/Ifc4Entities.h"

#define STL_USING_SET
#define STL_USING_MAP
#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

const OdString preIndent = "|   ";
std::wofstream outFile;

static void customAssertFunc(const char* expr, const char* fileName, int nLine)
{
  printf(
    "Assertion has occurs:\n"
    " Expression: %s\n"
    " Filename: %s\n"
    " Line number: %d\n",
    expr, fileName, nLine);
}

#ifndef _TOOLKIT_IN_DLL_
using namespace OdIfc;                                                             \
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);                              \
ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
  ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
  ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
  ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)                     \
ODRX_END_STATIC_MODULE_MAP()
#endif

void printString(const OdString& str)
{
  odPrintConsoleString(str);

  if (outFile.is_open())
    outFile << str.c_str();
}

OdString getObject(const OdDAIObjectId& obj)
{
  if (!obj)
    return OdString(L"$");
  OdString str = OdString().format(L"#%lu", (OdUInt64)obj->getHandle());
  return str;
}

OdString getObjectsCollection(const OdDAIObjectIds& objects)
{
  OdString str;
  for (const auto& it : objects)
  {
    str += OdString().format(L"#%lu", (OdUInt64)it.getHandle());
    if (&it != &objects.last())
      str += L",";
  }
  return str;
}

OdString getStringAttr(const OdAnsiString& attr)
{
  if (OdDAI::Utils::isUnset(attr))
    return OdString(L"$");
  OdString str;
  str.format(L"\'%s\'", OdString(attr).c_str());
  return str;
}

void printIfcProduct(OdIfc4::IfcProduct* pInst, OdUInt64 handle, int indent)
{
  OdString strData;
  for (int i = 0; i < indent; ++i)
    strData += preIndent;
  strData += OdString().format(L"#%lu= %s(%s,%s,%s,%s,%s,%s,%s);\n", handle, OdString(pInst->typeName().mid(0).makeUpper()).c_str(),
    getStringAttr(pInst->getGlobalId().c_str()).c_str(), getObject(pInst->getOwnerHistory()).c_str(),
    getStringAttr(pInst->getName()).c_str(), getStringAttr(pInst->getDescription()).c_str(),
    getStringAttr(pInst->getObjectType()).c_str(),
    getObject(pInst->getObjectPlacement()).c_str(), getObject(pInst->getRepresentation()).c_str());

  printString(strData);
}

void printIfcProject(OdIfc4::IfcProject* pInst, OdUInt64 handle, int indent)
{
  OdDAIObjectIds representationContexts;
  pInst->getRepresentationContexts(representationContexts);

  OdString strData;
  for (int i = 0; i < indent; ++i)
    strData += preIndent;
  strData += OdString().format(L"#%lu= %s(%s,%s,%s,%s,%s,%s,%s,(%s),%s);\n", handle, OdString(pInst->typeName().mid(0).makeUpper()).c_str(),
    getStringAttr(pInst->getGlobalId().c_str()).c_str(), getObject(pInst->getOwnerHistory()).c_str(),
    getStringAttr(pInst->getName()).c_str(), getStringAttr(pInst->getDescription()).c_str(),
    getStringAttr(pInst->getObjectType()).c_str(), getStringAttr(pInst->getLongName()).c_str(),
    getStringAttr(pInst->getPhase()).c_str(),
    getObjectsCollection(representationContexts).c_str(), getObject(pInst->getUnitsInContext()).c_str());

  printString(strData);
}

void printIfcRelAggregatesData(OdIfc4::IfcRelAggregates* pInst, OdUInt64 handle, int indent)
{
  OdDAIObjectIds relatedObjects;
  pInst->getRelatedObjects(relatedObjects);

  OdString strData;
  for (int i = 0; i < indent; ++i)
    strData += preIndent;
  strData += OdString().format(L"#%lu= %s(%s,%s,%s,%s,%s,(%s));\n", handle, OdString(pInst->typeName().mid(0).makeUpper()).c_str(),
    getStringAttr(pInst->getGlobalId().c_str()).c_str(), getObject(pInst->getOwnerHistory()).c_str(),
    getStringAttr(pInst->getName()).c_str(), getStringAttr(pInst->getDescription()).c_str(),
    getObject(pInst->getRelatingObject()).c_str(), getObjectsCollection(relatedObjects).c_str());

  printString(strData);
}

void printIfcRelContainedInSpatialStructureData(OdIfc4::IfcRelContainedInSpatialStructure* pInst, OdUInt64 handle, int indent)
{
  OdDAIObjectIds relatedObjects;
  pInst->getRelatedElements(relatedObjects);

  OdString strData;
  for (int i = 0; i < indent; ++i)
    strData += preIndent;
  strData += OdString().format(L"#%lu= %s(%s,%s,%s,%s,(%s),%s);\n", handle, OdString(pInst->typeName().mid(0).makeUpper()).c_str(),
    getStringAttr(pInst->getGlobalId().c_str()).c_str(), getObject(pInst->getOwnerHistory()).c_str(),
    getStringAttr(pInst->getName()).c_str(), getStringAttr(pInst->getDescription()).c_str(),
    getObjectsCollection(relatedObjects).c_str(), getObject(pInst->getRelatingStructure()).c_str());

  printString(strData);
}

void printObjectData(OdIfcModel* pModel, OdDAIObjectId obj, int indent)
{
  OdDAI::ApplicationInstancePtr pInst = obj.getNested();

  OdDbHandle handle = obj.getHandle();

  OdIfc4::IfcProductPtr ifcProduct = OdIfc4::IfcProduct::cast(pInst);
  if (!ifcProduct.isNull())
    printIfcProduct(ifcProduct, handle, indent++);
  else
  {
    OdIfc4::IfcProjectPtr ifcProject = OdIfc4::IfcProject::cast(pInst);
    if (!ifcProject.isNull())
      printIfcProject(ifcProject, handle, indent++);
    else
      printString(L"Reading data damper error\n");
  }
    
  bool isFindRelAggregates = false;
  OdDAI::OdDAIObjectIdSet* entityExtent = pModel->getEntityExtent("IFCRELAGGREGATES");
  for (auto it = entityExtent->createIterator(); it->next();)
  {
    it->getCurrentMemberValue() >> obj;
    pInst = obj.getNested();

    OdIfc4::IfcRelAggregatesPtr rel = OdIfc4::IfcRelAggregates::cast(pInst);
    if (rel.isNull())
      continue;
    if (rel->getRelatingObject()->getHandle() != OdUInt64(handle))
      continue;

    printIfcRelAggregatesData(rel, obj.getHandle(), indent++);
    isFindRelAggregates = true;

    OdDAIObjectIds relatedObjects;
    rel->getRelatedObjects(relatedObjects);
    for (const auto& it : relatedObjects)
      printObjectData(pModel, pModel->getEntityInstance(it.getHandle()), indent);
  }

  if (!isFindRelAggregates)
  {
    entityExtent = pModel->getEntityExtent("IFCRELCONTAINEDINSPATIALSTRUCTURE");
    for (auto it = entityExtent->createIterator(); it->next();)
    {
      it->getCurrentMemberValue() >> obj;
      pInst = obj.getNested();

      OdIfc4::IfcRelContainedInSpatialStructurePtr rel = OdIfc4::IfcRelContainedInSpatialStructure::cast(pInst);
      if (rel.isNull())
        continue;
      if (rel->getRelatingStructure().getHandle()!=handle)
        continue;

      printIfcRelContainedInSpatialStructureData(rel, obj.getHandle(), indent++);

      OdDAIObjectIds relatedObjects;
      rel->getRelatedElements(relatedObjects);
      for (const auto& it : relatedObjects)
      {
        printObjectData(pModel, pModel->getEntityInstance(it.getHandle()), indent);
      }
    }
  }
}

void printEntityExtentData(OdIfcModel* pModel, OdDAI::OdDAIObjectIdSet* entityExtent, int indent)
{ 
  OdDAIObjectId obj;
  for (auto it = entityExtent->createIterator(); it->next();)
  {
    it->getCurrentMemberValue() >> obj;
    printObjectData(pModel, obj, indent);
  }
}

void DumpFile(OdIfcHostAppServices* pHostApp, const OdString& fileName)
{
  //
  // Dump file
  //
  try{

    OdIfcFilePtr pIfcFile = pHostApp->readFile(fileName);
    if (pIfcFile.isNull())
    {
      printString(L"File open error: OdIfcFile wasn't created)\n");
      return;
    }

    OdIfcModelPtr pModel = pIfcFile->getModel(sdaiRO);

    if (!pModel.isNull())
    {
      auto entityExtent = pModel->getEntityExtent("IFCPROJECT");

      printEntityExtentData(pModel,entityExtent, 0);
    }
  }
  catch (...)
  {
    odPrintConsoleString(L"Exception in file '%s'\n", fileName.c_str());
  }
}


#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  ::odSetAssertFunc( customAssertFunc );

  //parse commands
  if( argc < 2 )
  {
    odPrintConsoleString(L"\nExIfc4SpatialStructureDump sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: ExIfc4SpatialStructureDump <target dump filename> [<output filename>]\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    STD(cin).get();
    return 1;
  }

  OdString szTargetFileName = argv[1];

  if (argc > 2)
    outFile.open(OdAnsiString(OdString(argv[2])).c_str());

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  // write a title

  // create a service
  OdStaticRxObject< MyServices > svcs;

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  try
  {
    DumpFile(&svcs, szTargetFileName);
  }
  catch (...)
  {
    ODA_ASSERT(0);
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

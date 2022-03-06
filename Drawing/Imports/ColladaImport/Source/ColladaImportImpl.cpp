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
#include "Ed/EdCommandContext.h"
#include "ColladaImportImpl.h"

#include "ColladaDocumentImporter.h"
#include "DbCommandContext.h"



namespace TD_COLLADA_IMPORT{

  ODRX_DECLARE_PROPERTY(Database)
    ODRX_DECLARE_PROPERTY(ColladaPath)
    ODRX_DECLARE_PROPERTY(ImportTextures)
    ODRX_DECLARE_PROPERTY(ConsoleInfo)
    ODRX_DECLARE_PROPERTY(ImportLines)

    ODRX_DEFINE_PROPERTY_OBJECT(Database, ColladaProperties, get_Database, put_Database, OdDbDatabase)
    ODRX_DEFINE_PROPERTY(ColladaPath, ColladaProperties, getString)
    ODRX_DEFINE_PROPERTY(ImportTextures, ColladaProperties, getBool)
    ODRX_DEFINE_PROPERTY(ConsoleInfo, ColladaProperties, getBool)
    ODRX_DEFINE_PROPERTY(ImportLines, ColladaProperties, getBool)

    ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(ColladaProperties);
    ODRX_GENERATE_PROPERTY(Database)
    ODRX_GENERATE_PROPERTY(ColladaPath)
    ODRX_GENERATE_PROPERTY(ImportTextures)
    ODRX_GENERATE_PROPERTY(ConsoleInfo)
    ODRX_GENERATE_PROPERTY(ImportLines)
    ODRX_END_DYNAMIC_PROPERTY_MAP(ColladaProperties);

class ColladaImportCommand : public OdEdCommand
{
public:
  const OdString groupName() const { return OD_T("IMPORTS"); }
  const OdString globalName() const { return OD_T("ColladaIn"); };
  void execute(OdEdCommandContext* pCmdCtx);
};


void ColladaImportCommand::execute(OdEdCommandContext* pCmdCtx)
{
  OdSmartPtr<OdEdUserIO> pIO = pCmdCtx->userIO();
  OdString path = pIO->getFilePath( OD_T("Enter file name:"), OdEd::kGfpForOpen, OD_T("Collada file to load"),
    OD_T("dae"), OdString::kEmpty, OD_T("Design Web Format (*.dae)|*.dae|"));
  if (path.isEmpty())
    return;
 
  OdColladaImportPtr importer = createImporter();
  OdRxDictionaryPtr pProps = importer->properties();
  // Target database
  pProps->putAt(OD_T("Database"), OdDbCommandContextPtr(pCmdCtx)->database());
  // Source Collada(.dae) file
  pProps->putAt(OD_T("ColladaPath"), OdRxVariantValue(path));
  pProps->putAt(OD_T("ImportTextures"), OdRxVariantValue(pIO->getKeyword(OD_T("Enable import of textures [Yes/No] <No>:"), OD_T("Yes No"), 1) == 0));
  pProps->putAt(OD_T("ConsoleInfo"), OdRxVariantValue(pIO->getKeyword(OD_T("Output information at console  [Yes/No] <Yes>:"), OD_T("Yes No"), 0) == 0));
  pProps->putAt(OD_T("ImportLines"), OdRxVariantValue(pIO->getKeyword(OD_T("Enable import of lines [Yes/No] <Yes>:"), OD_T("Yes No"), 0) == 0));
  if (importer->import() != OdColladaImport::success)
  {
    pIO->putString(OD_T("ColladaImport failed!"));
  }
}


class OdColladaImportModule : public ColladaImportModule
{
  OdStaticRxObject<ColladaImportCommand> m_Command;
public:
  virtual void initApp()
  {
#ifndef TD_NOCOMMANDS
    odedRegCmds()->addCommand(&m_Command);
#endif
  }
  virtual void uninitApp()
  {
#ifndef TD_NOCOMMANDS
    odedRegCmds()->removeCmd(m_Command.groupName(), m_Command.globalName());
#endif
  }

  virtual OdColladaImportPtr create()
  {
    return OdRxObjectImpl<OdColladaImportImpl>::createObject();
  }

};
}
using namespace TD_COLLADA_IMPORT;
ODRX_DEFINE_DYNAMIC_MODULE(OdColladaImportModule);



namespace TD_COLLADA_IMPORT{
OdColladaImportImpl::OdColladaImportImpl():
  m_properties(ColladaProperties::createObject())
{
}

OdColladaImport::ImportResult OdColladaImportImpl::import()
{
  m_database = m_properties->get_Database();
  if ( m_database.isNull() ) 
    return OdColladaImport::bad_database;

  m_database->closeInput();  // some problems (with viewport) in case that db was open partially

  DocumentImporter cldImporter(m_properties->get_ColladaPath(), dynamic_cast<OdDbDatabase*>(m_properties->get_Database().get()), 
    m_properties->get_ImportTextures(), m_properties->get_ConsoleInfo(), m_properties->get_ImportLines());
  try
  {
    return cldImporter.import() ? OdColladaImport::success : OdColladaImport::fail;
  }
  catch (...)
  {
    return OdColladaImport::bad_file;
  }
}

OdRxDictionaryPtr OdColladaImportImpl::properties() { return m_properties; }
}

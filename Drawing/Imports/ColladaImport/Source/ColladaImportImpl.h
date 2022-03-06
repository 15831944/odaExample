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
#ifndef _COLLADA_IMPORTIMPL_INCLUDED_
#define _COLLADA_IMPORTIMPL_INCLUDED_

#include "OdaCommon.h"
#include "ColladaImportDef.h"
#include "Gi/GiDrawable.h"
#include "DbDatabase.h"
#include "RxDispatchImpl.h"
#include "RxVariantValue.h"
#include "DbDictionary.h"
#include "RxDynamicModule.h"
#include "StaticRxObject.h"
#include "Ed/EdCommandStack.h"
#include "Ed/EdUserIO.h"
#include "ColladaImport.h"

namespace TD_COLLADA_IMPORT {
class ColladaProperties : public OdRxDispatchImpl<>
{
  OdString m_strPath;
  OdDbDatabasePtr m_database;
  bool m_bImportTextures;
  bool m_bConsoleInfo;
  bool m_bExportLines;
  //OdSmartPtr<OdEdUserIO> m_pUserIO;
  //OdStreamBufPtr m_stream;
public:
  ColladaProperties()  
  {
    m_bImportTextures = false;
    m_bConsoleInfo = false;
    m_bExportLines = false;
  }
  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP( ColladaProperties );
  static OdRxDictionaryPtr createObject();
  
  OdRxObjectPtr get_Database() const   { return m_database.get(); }
  void put_Database( OdRxObject* obj ) { m_database = obj; }
  OdString get_ColladaPath() const     { return m_strPath; }
  void put_ColladaPath( OdString path ){ m_strPath = path; }
  bool get_ImportTextures() const      { return m_bImportTextures; }
  void put_ImportTextures( bool bVal ) { m_bImportTextures = bVal; }
  bool get_ConsoleInfo() const         { return m_bConsoleInfo; }
  void put_ConsoleInfo( bool bVal )    { m_bConsoleInfo = bVal; }
  bool get_ImportLines() const         { return m_bExportLines; }
  void put_ImportLines(bool bVal)      { m_bExportLines = bVal; }
};
typedef OdSmartPtr<ColladaProperties> ColladaPropertiesPtr;

OdRxDictionaryPtr ColladaProperties::createObject()
{
  return OdRxObjectImpl<ColladaProperties, OdRxDictionary>::createObject();
}

class OdColladaImportImpl : public OdColladaImport
{
  OdDbDatabasePtr m_database;

  ColladaPropertiesPtr m_properties;
public:
  OdColladaImportImpl();

  virtual ImportResult import();
  virtual OdRxDictionaryPtr properties();
};
}

#endif // _COLLADA_IMPORTIMPL_INCLUDED_



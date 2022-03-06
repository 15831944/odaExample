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

// IfcExportProperties.h: interface for the OdIfcExportProperties class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _NV2IFC_EXPORTPROPERTIES_H_INCLUDED_
#define _NV2IFC_EXPORTPROPERTIES_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RxDispatchImpl.h"
#include "../BimNv/Include/NwDatabase.h"

#define STL_USING_MAP
#include "OdaSTL.h"

namespace NV_IFC_EXPORT
{
  class OdIfcExportProperties : public OdRxDispatchImpl<>
  {
    OdInt16                      _schemaVersion;
    OdString                     _ifcFilePath;
    std::map<OdString, OdString> _dictionary;
    OdNwDatabasePtr              _db;

  public:
    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdIfcExportProperties);
    
    static OdRxDictionaryPtr createObject();

    const OdInt16 get_SchemaVersion() const { return _schemaVersion; }
    void put_SchemaVersion(OdInt16 ver) { _schemaVersion = ver; }
    const OdString get_IfcFilePath() const { return _ifcFilePath; }
    void put_IfcFilePath(const OdString& path) { _ifcFilePath = path; }
    const OdRxWrapperValue<std::map<OdString, OdString> > get_Dictionary() const { return createRxWrapper(_dictionary); }
    void put_Dictionary(const OdRxWrapper<std::map<OdString, OdString> >* map) { _dictionary = *map; }
    OdRxObjectPtr get_Database() const { return _db.get(); }
    void put_Database(OdRxObject* db) { _db = db; }
  };
  typedef OdSmartPtr<OdIfcExportProperties> OdIfcExportPropertiesPtr;
}


#endif // _NV2IFC_EXPORTPROPERTIES_H_INCLUDED_


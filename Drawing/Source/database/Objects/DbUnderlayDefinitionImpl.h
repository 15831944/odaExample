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


#ifndef __OD_DB_UNDERLAY_DEFINITION_IMPL__
#define __OD_DB_UNDERLAY_DEFINITION_IMPL__

#include "DbUnderlayDefinition.h"
#include "DbObjectImpl.h"
#include "ThreadsCounter.h"

class OdDbUnderlayDefinitionImpl : public OdDbObjectImpl
{
public:
  OdDbUnderlayDefinitionImpl();

  // OdDbObjectImpl overridden
  //
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

public:
  OdString m_sourceFileName, m_itemName;
  OdMutexPtr m_pContentsAccessMutex;
  
  // not stored in DWG
  bool m_bFirstTry,
       m_bLoaded, // user may unload underlay manually to hide message "Missing or invalid reference" only      
       m_bFileError, // will true if a file cannot be accessed 
       m_bNoLoadFlag; // dxf 1000 - load/unload status of underlay, issue #11637

  OdString m_activeFileName;
  OdDbUnderlayItemPtr m_pItem;

  virtual bool loadHostModule() = 0;

  static OdDbUnderlayDefinitionImpl* getImpl(const OdDbUnderlayDefinition *pObj)
  { return (OdDbUnderlayDefinitionImpl*)OdDbSystemInternals::getImpl(pObj);}
};

class OdDbDwfDefinitionImpl : public OdDbUnderlayDefinitionImpl
{
  virtual bool loadHostModule();
};

class OdDbDgnDefinitionImpl : public OdDbUnderlayDefinitionImpl
{
  virtual bool loadHostModule();
};

class OdDbPdfDefinitionImpl : public OdDbUnderlayDefinitionImpl
{
  virtual bool loadHostModule();
};

class OdDbNavisworksDefinitionImpl : public OdDbObjectImpl
{
public:
  OdDbNavisworksDefinitionImpl();

  // OdDbObjectImpl overridden
  //
  void composeForLoad( OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version );

public:
  OdUInt16 m_ver;
  OdString m_sourceFileName;
  bool m_Loaded;
  OdGePoint3d m_p1;
  OdGePoint3d m_p2;
  bool m_HostDWGvisibility;

  // not stored in DWG
  bool m_bFirstTry,
    m_bLoaded, // user may unload underlay manually to hide message "Missing or invalid reference" only      
    m_bFileError, // will true if a file cannot be accessed 
    m_bNoLoadFlag; // dxf 1000 - load/unload status of underlay, issue #11637

  OdString m_activeFileName;
  OdDbUnderlayItemPtr m_pItem;

  //virtual bool loadHostModule();

  static OdDbNavisworksDefinitionImpl* getImpl( const OdDbNavisworksDefinition *pObj )
  {
    return (OdDbNavisworksDefinitionImpl*)OdDbSystemInternals::getImpl( pObj );
  }
};

#endif // __OD_DB_UNDERLAY_DEFINITION_IMPL__

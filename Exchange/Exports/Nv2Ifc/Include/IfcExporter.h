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

// IfcExporter.h: interface for the OdIfcExporter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _NV2IFC_EXPORTER_H_INCLUDED_
#define _NV2IFC_EXPORTER_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcExport.h"
#include "IfcExportProperties.h"
#include "IfcFile.h"
#include "IfcEntityCreator.h"

#define STL_USING_MAP
#include "OdaSTL.h"

class OdGiDrawable;
class OdNwModelItem;
typedef OdSmartPtr<OdNwModelItem> OdNwModelItemPtr;

namespace NV_IFC_EXPORT
{
  class OdIfcExporter : public OdIfcExport
  {
    OdIfcExportPropertiesPtr _properties;
    OdIfcModelPtr            m_pModel;
    OdDAIObjectId            m_subContextId;
    OdDAIObjectId            m_ownerHistoryId;
    bool                     m_useFacilityPart;

  public:
    ODRX_DECLARE_MEMBERS(OdIfcExporter);

    OdIfcExporter();
    virtual ExportResult doExport() ODRX_OVERRIDE;
    virtual OdRxDictionaryPtr properties() ODRX_OVERRIDE;

  private:
    OdDbStub* exportEntity(OdGiDrawable* pEnt, OdIfcModelPtr pModel, OdDbStub* subContextId);
    OdResult initIfcFile(OdIfcFilePtr pDb, OdIfcEntityCreator& creator);
    ExportResult exportGeometry(OdIfcEntityCreator& creator, std::map<OdString, OdString>& dictionary);
    OdResult initHeaderSection(OdIfcFilePtr pDb);
    OdResult getproxyBuildingElementsByRoot(OdIfcEntityCreator& creator, OdNwModelItemPtr pRoot, const std::map<OdString, OdString>& entities, OdDAIObjectIds& proxyElements);
  };
}


#endif // _NV2IFC_EXPORTER_H_INCLUDED_


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


#ifndef VISUALIZE2OBJ_H
#define VISUALIZE2OBJ_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvExport.h"
#include "DbBaseDatabase.h"

/** \details
This class implements the properties of the exported to Obj
*/
class OdTvVisualize2ObjExportProperties : public OdRxDispatchImpl<>
{

public:
  OdTvVisualize2ObjExportProperties();
  virtual ~OdTvVisualize2ObjExportProperties();

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualize2ObjExportProperties);
  static OdRxDictionaryPtr createObject();

};
typedef OdSmartPtr<OdTvVisualize2ObjExportProperties> OdTvVisualize2ObjExportPropertiesPtr;

/** \details
This class is obj exporter (from the Visualize database)
*/
class OdTvVisualize2ObjExport : public OdTvVisualizeExport
{
public:

  OdTvVisualize2ObjExport();

  OdTvResult exportTo(const OdTvDatabaseId& tvDbId, const OdString& fileName) const;
  OdRxDictionaryPtr properties() { return m_properties; }

private:
  OdTvVisualize2ObjExportPropertiesPtr m_properties;

};


/** \details
This class is Obj exporter module implementation
*/
class OdTvVisualize2ObjFilerModule : public OdTvVisualizeExportModule
{
public:
  OdTvVisualizeExportPtr getVisualizeExporter() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // VISUALIZE2OBJ_H


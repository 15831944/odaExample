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

#ifndef VISUALIZE2NWD_H
#define VISUALIZE2NWD_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvExport.h"

class OdTv2NwdCopier;

class OdTvDbEntity;

/** \details
This class implements the properties of the exported to dwg
*/
namespace Visualize2Nwd
{
  class OdTvVisualize2NwdExportProperties : public OdRxDispatchImpl<>
  {
  
  public:
    OdTvVisualize2NwdExportProperties();
    virtual ~OdTvVisualize2NwdExportProperties();
  
    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualize2NwdExportProperties);
    static OdRxDictionaryPtr createObject();
  
    void setEntityForExplode(OdIntPtr pEntity);
    OdIntPtr getEntityForExplode() const;
  
    void setEntitySet(OdIntPtr pEntity);
    OdIntPtr getEntitySet() const;
    OdRxObjectPtrArray* getEntitySetObject() const;
    void setDevice(OdIntPtr device);
    OdIntPtr getDevice() const;
    OdTvGsDeviceId getDeviceTv() const;
  
    void setView(OdIntPtr view);
    OdIntPtr getView() const;
    OdTvGsViewId getViewTv() const;
  
    void setModel(OdIntPtr model);
    OdIntPtr getModel() const;
    OdTvModelId getModelTv() const;
  
    void setExportCallback(OdIntPtr pCallback);
    OdIntPtr getExportCallback() const;
  
    void setConvertNurbsToSpline(bool bValue);
    bool getConvertNurbsToSpline() const;
  
  protected:
    OdTvDbEntity* m_pEntity;                 // Entity to export
    OdRxObjectPtrArray* m_pEntitySet;      // Entity set
    OdTvGsDeviceId m_deviceId;
    OdTvGsViewId m_viewId;
    OdTvModelId m_modelId;
    bool        m_bConvertNurbsToSpline;
    OdTvExportCallbackFunction m_pCallback;// Callback for export
  };
  typedef OdSmartPtr<OdTvVisualize2NwdExportProperties> OdTvVisualize2NwdExportPropertiesPtr;
}

/** \details
This class is nwd exporter (from the Visualize database)
*/
class OdTvVisualize2NwdExport : public OdTvVisualizeExport
{
public:
  OdTvVisualize2NwdExport();
  ~OdTvVisualize2NwdExport();

  OdTvResult exportTo(const OdTvDatabaseId& tvDbId, const OdString& fileName) const;
  OdRxDictionaryPtr properties() { return m_properties; }

private:
  // dwg export properties
  Visualize2Nwd::OdTvVisualize2NwdExportPropertiesPtr m_properties;
  
  // copier object for database copying
  OdTv2NwdCopier* m_pDatabaseCopier;
};


/** \details
This class is nwd exporter module implementation
*/
class OdTvVisualize2NwdFilerModule : public OdTvVisualizeExportModule
{
public:
  OdTvVisualizeExportPtr getVisualizeExporter() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // VISUALIZE2NWD_H

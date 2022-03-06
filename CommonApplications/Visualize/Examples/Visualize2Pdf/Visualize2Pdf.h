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


#ifndef VISUALIZE2PDF_H
#define VISUALIZE2PDF_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvExport.h"
#include "DbBaseDatabase.h"
#include "StaticRxObject.h"
#include "Ed/EdCommandContext.h"
#include "RxDynamicModule.h"
#include "Ed/EdCommandStack.h"

/** \details
This class implements the properties of the exported to pdf
*/
class OdTvVisualize2PdfExportProperties : public OdRxDispatchImpl<>
{

public:

  OdTvVisualize2PdfExportProperties();
  virtual ~OdTvVisualize2PdfExportProperties();

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizePrcFilerProperties);
  static OdRxDictionaryPtr createObject();

  void set3DPdf(bool bIs3DPdf);
  bool is3DPdf() const;

  void setBackgroundColor(OdIntPtr background);
  OdIntPtr getBackgroundColor() const;

  void setDevices(const OdStringArray& devices);
  const OdStringArray& getDevices() const;

  void setPaperSizes(OdDoubleArray paperSizes);
  const OdDoubleArray getPaperSizes() const;

  void setZoomToExtents(bool bVal);
  bool getZoomToExtents() const;

  void setPublishTemplate(OdUInt8 publishTemplate);
  OdUInt8 getPublishTemplate() const;

protected:
  bool                        m_bIs3DPdf;
  ODCOLORREF                  m_backgroundColor;  // Background color. Default: white.
  OdStringArray               m_devices;          // List of devices names
  OdDoubleArray               m_paperSizes;       // Paper sizes
  bool                        m_bZoomToExtents;   // Need zoom to extents
  OdUInt8                     m_iTemplate;        // Template for publish
};
typedef OdSmartPtr<OdTvVisualize2PdfExportProperties> OdTvVisualize2PdfExportPropertiesPtr;


/** \details
This class is pdf exporter (from the Visualize database)
*/
class OdTvVisualize2PdfExport : public OdTvVisualizeExport
{
public:

  OdTvVisualize2PdfExport();

  OdTvResult exportTo(const OdTvDatabaseId& tvDbId, const OdString& fileName) const;
  OdRxDictionaryPtr properties() { return m_properties; }

private:
  OdInt32 exportTo2dPdf(const OdTvDatabaseId& tvDbId, OdDbBaseDatabase* pDb, const OdString& fileName) const;
  OdInt32 exportTo3dPdf(const OdTvDatabaseId& tvDbId, OdDbBaseDatabase* pDb, const OdString& fileName) const;

private:
  OdTvVisualize2PdfExportPropertiesPtr m_properties;

};


#define CMD_DEF_CLASS(CmdName, GroupName)
#define CMD_DEF(CmdName, GroupName) \
class _##CmdName##_cmd : public OdEdCommand \
{ \
public: \
  const OdString groupName() const;\
  const OdString globalName() const;\
  void execute(OdEdCommandContext* pCmdCtx);\
  void setTvDatabase(const OdTvDatabaseId& tvDbId) { m_dbId = tvDbId; }\
private:\
  OdTvDatabaseId m_dbId;\
};
#include "Visualize2PdfCommands.h"
#undef CMD_DEF_CLASS
#undef CMD_DEF

/** \details
This class is pdf exporter module implementation
*/
class OdTvVisualize2PdfFilerModule : public OdTvVisualizeExportModule
{
#define CMD_DEF(CmdName, GroupName) \
  OdStaticRxObject<_##CmdName##_cmd> m_##CmdName##_cmd;
#include "Visualize2PdfCommands.h"
#undef CMD_DEF

public:
  OdTvVisualizeExportPtr getVisualizeExporter() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // VISUALIZE2PDF_H


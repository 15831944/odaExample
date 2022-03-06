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

// ODA Platform
#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxVariantValue.h"

// Visualize SDK
#include "TvFactory.h"
#include "TvImportUserData.h"
#include "TvCoreModulesNames.h"

//PDF export
#include "Visualize2Pdf.h"
#include "DynamicLinker.h"
#include "TvError.h"
#include "PdfExport.h"

// publish
#include "ExStringIO.h"
#include "Ed/EdCommandStack.h"
#include "ExDbCommandContext.h"
#include "PrcModuleNames.h"

using namespace TD_PDF_2D_EXPORT;

bool hasLayoutUserData(const OdTvDatabaseId& tvDbId, OdTvGsDevicePtr pDevice)
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject();
  if (pTvDb.isNull())
    return false;

  if (pDevice.isNull())
    return false;

  bool alreadyExist = false;
  OdTvRegAppId regAppId = pTvDb->registerAppName(OdTvDWGUserData, alreadyExist);
  if (regAppId.isNull())
    return false;

  OdTvByteUserData *pLayoutUserData = dynamic_cast<OdTvByteUserData*>(pDevice->getUserData(regAppId));
  if (!pLayoutUserData)
    return false;

  return true;
}

//***************************************************************************//
// 'OdTvVisualize2PdfFilerProperties' methods implementation
//***************************************************************************//

OdTvVisualize2PdfExportProperties::OdTvVisualize2PdfExportProperties()
{
  m_bIs3DPdf = false;
  m_backgroundColor = ODRGB(255, 255, 255);
  m_iTemplate = (int)kDefault;
}

OdTvVisualize2PdfExportProperties::~OdTvVisualize2PdfExportProperties()
{
}

OdRxDictionaryPtr OdTvVisualize2PdfExportProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualize2PdfExportProperties, OdRxDictionary>::createObject();
}

void OdTvVisualize2PdfExportProperties::set3DPdf(bool bIs3DPdf)
{
  m_bIs3DPdf = bIs3DPdf;
}

bool OdTvVisualize2PdfExportProperties::is3DPdf() const
{
  return m_bIs3DPdf;
}

void OdTvVisualize2PdfExportProperties::setBackgroundColor(OdIntPtr backgroundColor)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(backgroundColor);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_backgroundColor = *pColor;
}

OdIntPtr OdTvVisualize2PdfExportProperties::getBackgroundColor() const
{
  return (OdIntPtr)(&m_backgroundColor);
}

void OdTvVisualize2PdfExportProperties::setDevices(const OdStringArray& devices)
{
  m_devices = devices;
}

const OdStringArray& OdTvVisualize2PdfExportProperties::getDevices() const
{
  return m_devices;
}

void OdTvVisualize2PdfExportProperties::setPaperSizes(OdDoubleArray paperSizes)
{
  m_paperSizes = paperSizes;
}

const OdDoubleArray OdTvVisualize2PdfExportProperties::getPaperSizes() const
{
  return m_paperSizes;
}

void OdTvVisualize2PdfExportProperties::setZoomToExtents(bool bVal)
{
  m_bZoomToExtents = bVal;
}

bool OdTvVisualize2PdfExportProperties::getZoomToExtents() const
{
  return m_bZoomToExtents;
}

void OdTvVisualize2PdfExportProperties::setPublishTemplate(OdUInt8 publishTemplate)
{
  m_iTemplate = (int)publishTemplate;
}

OdUInt8 OdTvVisualize2PdfExportProperties::getPublishTemplate() const
{
  return m_iTemplate;
}

ODRX_DECLARE_PROPERTY(is3D)
ODRX_DECLARE_PROPERTY(BackgroundColor)
ODRX_DECLARE_PROPERTY(Devices)
ODRX_DECLARE_PROPERTY(PaperSizes)
ODRX_DECLARE_PROPERTY(ZoomToExtents)
ODRX_DECLARE_PROPERTY(PublishTemplate)

ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualize2PdfExportProperties);
ODRX_GENERATE_PROPERTY(is3D)
ODRX_GENERATE_PROPERTY(BackgroundColor)
ODRX_GENERATE_PROPERTY(Devices)
ODRX_GENERATE_PROPERTY(PaperSizes)
ODRX_GENERATE_PROPERTY(ZoomToExtents)
ODRX_GENERATE_PROPERTY(PublishTemplate)
ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualize2PdfExportProperties);

ODRX_DEFINE_PROPERTY_METHODS(is3D, OdTvVisualize2PdfExportProperties, is3DPdf, set3DPdf, getBool);
ODRX_DEFINE_PROPERTY_METHODS(BackgroundColor, OdTvVisualize2PdfExportProperties, getBackgroundColor, setBackgroundColor, getIntPtr);
ODRX_DEFINE_PROPERTY_METHODS(Devices, OdTvVisualize2PdfExportProperties, getDevices, setDevices, getStringArray);
ODRX_DEFINE_PROPERTY_METHODS(PaperSizes, OdTvVisualize2PdfExportProperties, getPaperSizes, setPaperSizes, getDoubleArray);
ODRX_DEFINE_PROPERTY_METHODS(ZoomToExtents, OdTvVisualize2PdfExportProperties, getZoomToExtents, setZoomToExtents, getBool);
ODRX_DEFINE_PROPERTY_METHODS(PublishTemplate, OdTvVisualize2PdfExportProperties, getPublishTemplate, setPublishTemplate, getUInt8);

//***************************************************************************//
// 'OdTvVisualize2PdfFiler' methods implementation
//***************************************************************************//

OdTvVisualize2PdfExport::OdTvVisualize2PdfExport()
{
  m_properties = OdTvVisualize2PdfExportProperties::createObject();
}

OdTvResult OdTvVisualize2PdfExport::exportTo(const OdTvDatabaseId& tvDbId, const OdString& fileName) const
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject();
  if (pTvDb.isNull())
    return tvInvalidInput;

  //call method for write the file
  try
  {
    OdDbBaseDatabase* pDb = static_cast<OdDbBaseDatabase*>(pTvDb->getInternalDatabase());
    int errorCode;
    if (!m_properties->is3DPdf())
      errorCode = exportTo2dPdf(tvDbId, pDb, fileName);
    else
      errorCode = exportTo3dPdf(tvDbId, pDb, fileName);

    if (errorCode != 0)
      return tvErrorDuringExport;
  }
  catch (OdTvError& /*e*/)
  {
    return tvInternal;
  }

  return tvOk;
}

OdInt32 OdTvVisualize2PdfExport::exportTo2dPdf(const OdTvDatabaseId& tvDbId, OdDbBaseDatabase* pDb, const OdString& fileName) const
{
  // try to load pdf export module
  OdPdfExportPtr exporter;
  {
    OdPdfExportModulePtr pModule = odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);

    if (pModule.isNull())
      return tvMissingExportModule;
    exporter = pModule->create();
  }

  if (exporter.isNull())
    return tvMissingExportModule;

  //get visualize export properties
  bool                bZoomToExtents = m_properties->getZoomToExtents();
  ODCOLORREF          backgroundColor = *((ODCOLORREF*)m_properties->getBackgroundColor());
  const OdStringArray devices = m_properties->getDevices();
  OdDoubleArray       paperSizes = m_properties->getPaperSizes();

  //check the possibility of not the zoom to extents
  if (!bZoomToExtents)
  {
    if (devices.isEmpty())
      bZoomToExtents = true;
    else
    {
      OdTvDatabasePtr pTvDb = tvDbId.openObject();
      if (!pTvDb.isNull())
      {
        OdTvDevicesIteratorPtr pDevicesIterator = pTvDb->getDevicesIterator();
        if (!pDevicesIterator.isNull()) // here we have O(n^2) but ut us not a problem
        {
          while (!pDevicesIterator->done() && !bZoomToExtents)
          {
            OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
            OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject();
            if( !pTvDevice.isNull() )
            {
              OdString devName = pTvDevice->getName();
              for (OdUInt32 i = 0; i < devices.size(); i++)
              {
                if (devices[i] == devName)
                {
                  if (!hasLayoutUserData(tvDbId, pTvDevice))
                  {
                    bZoomToExtents = true;
                    break;
                  }
                }
              }
            }
            pDevicesIterator->step();
          }
        }
      }
    }
  }

  //prepare and fill pdf export structure
  PDFExportParams params;
  params.setDatabase(pDb);
  params.setOutput(odrxSystemServices()->createFile(fileName, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways));
  params.setExportFlags(PDFExportParams::PDFExportFlags(
                       (PDFExportParams::kSHXTextAsGeometry) |
                       (PDFExportParams::kTTFTextAsGeometry) |
                       (PDFExportParams::kUseHLR) |
                       (PDFExportParams::kFlateCompression) |
                       (bZoomToExtents ? PDFExportParams::kZoomToExtentsMode : 0)));

  params.setUseViewExtents(false);
  params.setImageCropping(true);
  params.setDCTCompression(true);
  params.setDCTQuality(50);
  params.setArchived((PDFExportParams::PDF_A_mode)0);

  params.setForceDisableGsDevice(false);
  params.setTransparentShadedVpBg(false);

  params.setSearchableTextType(PDFExportParams::kNoSearch);
  params.setSolidHatchesExportType(PDFExportParams::kPdfPaths);
  params.setGradientHatchesExportType(PDFExportParams::kBitmap);
  params.setOtherHatchesExportType(PDFExportParams::kDrawing);
  
  params.setGeomDPI(600);
  params.setBWImagesDPI(400);
  params.setColorImagesDPI(400);
  params.setHatchDPI(72);

  //fill parameters from incoming properties
  params.setLayouts(devices);
  params.setBackground(backgroundColor);
  params.pageParams().resize(devices.length());
  for (OdUInt32 i = 0; i < devices.length(); i++)
    params.pageParams()[i].set(paperSizes.at(2 * i), paperSizes.at(2 * i + 1));

  //perform export
  OdUInt32 errorCode = exporter->exportPdf(params);
  
  //release export module
  exporter.release();

  ::odrxDynamicLinker()->unloadModule(OdPdfExportModuleName);
  odrxDynamicLinker()->unloadUnreferenced();

  return errorCode;
}


OdInt32 OdTvVisualize2PdfExport::exportTo3dPdf(const OdTvDatabaseId& tvDbId, OdDbBaseDatabase* pDb, const OdString& fileName) const
{
  {
    OdPdfExportModulePtr pModule = odrxDynamicLinker()->loadApp(OdTvExPdfPublishCmdsModuleName, false);
    if (pModule.isNull())
      return tvMissingExportModule;
  }

  OdString sOutTemplate1(fileName);
  OdSmartPtr<ExStringIO> pStringIO = ExStringIO::create(L"Yes\nTess\n" + sOutTemplate1 + L"\n");

  if(m_properties->getPublishTemplate() == (OdUInt8)OdTvPdfExportParams::kDefault)
  {
    ODA_VERIFY(!::odedRegCmds()->lookupCmd("PUBLISH3DCASE1").isNull());
    OdTvDbCommandContextPtr ctx = ExDbCommandContext::createObject(pStringIO, pDb);
    ::odedRegCmds()->executeCommand("PUBLISH3DCASE1", ctx);
  }
  else if(m_properties->getPublishTemplate() == (OdUInt8)OdTvPdfExportParams::kOpenIfcViewer)
  {
    OdEdCommandPtr pCmd = ::odedRegCmds()->lookupCmd("OpenIfcViewerTemplate");
    ODA_VERIFY(!pCmd.isNull());

    _OpenIfcViewerTemplate_cmd* pTvCmd = dynamic_cast<_OpenIfcViewerTemplate_cmd*>(pCmd.get());
    if (pTvCmd)
    {
      pTvCmd->setTvDatabase(tvDbId);
    }

    OdTvDbCommandContextPtr ctx = ExDbCommandContext::createObject(pStringIO, pDb);
    ::odedRegCmds()->executeCommand("OpenIfcViewerTemplate", ctx);
  }

  ::odrxDynamicLinker()->unloadModule(OdTvExPdfPublishCmdsModuleName);
  odrxDynamicLinker()->unloadUnreferenced();

  return 0;
}

//***************************************************************************//
// 'OdTvVisualize2PdfFilerModule' methods implementation
//***************************************************************************//

#define CMD_DEF_CLASS(CmdName, GroupName) \
  extern void _##CmdName##_func(OdEdCommandContext* pCmdCtx, const OdTvDatabaseId& tvDbId);\
  const OdString _##CmdName##_cmd::globalName() const { return OD_T(#CmdName); }\
  const OdString _##CmdName##_cmd::groupName() const { return GroupName; }

#define CMD_DEF(CmdName, GroupName) \
  extern void _##CmdName##_func(OdEdCommandContext* pCmdCtx, const OdTvDatabaseId& tvDbId);\
  const OdString _##CmdName##_cmd::globalName() const { return OD_T(#CmdName); }\
  const OdString _##CmdName##_cmd::groupName() const { return GroupName; }\
  void _##CmdName##_cmd::execute(OdEdCommandContext* pCmdCtx) { _##CmdName##_func(pCmdCtx, m_dbId); }

#include "Visualize2PdfCommands.h"

#undef CMD_DEF_CLASS
#undef CMD_DEF

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualize2PdfFilerModule);

OdTvVisualizeExportPtr OdTvVisualize2PdfFilerModule::getVisualizeExporter() const
{
  OdTvVisualizeExportPtr pPdfExporter = new OdTvVisualize2PdfExport();
  return pPdfExporter;
}

void OdTvVisualize2PdfFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();

  OdEdCommandStackPtr pCommands = odedRegCmds();
#define CMD_DEF(CmdName, GroupName) \
  pCommands->addCommand(&m_##CmdName##_cmd);
#include "Visualize2PdfCommands.h"
#undef CMD_DEF
}

void OdTvVisualize2PdfFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();

  OdEdCommandStackPtr pCommands = odedRegCmds();
#define CMD_DEF(CmdName, GroupName) \
  pCommands->removeCmd(GroupName, OD_T(#CmdName));
#include "Visualize2PdfCommands.h"
#undef CMD_DEF
}

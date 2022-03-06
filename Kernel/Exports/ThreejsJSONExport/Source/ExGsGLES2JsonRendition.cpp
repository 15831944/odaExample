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
// GLES2 device json server rendition

#include "OdaCommon.h"
#include "Tr/TrVisRenderClient.h"
#include "Tr/TrVisMetafileAnalyzer.h"
#include "ExGsGLES2JsonSharingProvider.h"
#include "ExGsGLES2JsonRendition.h"
#include "JsonMetafileConverter.h"
#include "Tr/TrVisTtfFontsCacheClient.h"

#define OD_GLES2JSON_DROPHLTASCLIENTONLY

#define STL_USING_LIMITS
#include "OdaSTL.h"

#ifdef OD_GLES2JSON_DROPSCD_TEST
#include "ExGsGLES2ShareableClientData.h"

struct DropSCDTest : public OdGLES2JsonServerStub
{
  OdGLES2JsonServer **m_ppWhere;
  OdGLES2JsonServer  *m_pWho;
  static OdTrVecDevice *m_pDevice;

  DropSCDTest(OdGLES2JsonServer **ppWhere)
    : m_ppWhere(ppWhere)
    , m_pWho(*ppWhere)
  {
    *ppWhere = this;
  }
  ~DropSCDTest()
  {
    if (*m_ppWhere != m_pWho)
      *m_ppWhere = m_pWho;
  }

  virtual bool UpdateClientDependentSectionOnly() const { return m_pWho->UpdateClientDependentSectionOnly(); }

  virtual bool DropShareableClientData(IdType /*idType*/, IdSubType /*idSubType*/, OdUInt64 resId, OdTrVisUniqueID* pRegId,
                                       OdUInt32 nBinaryFields, const void ** const pBinaryFields, const OdUInt32* nBinaryFieldsData,
                                       OdUInt32 /*nIdMappings*/ = 0, const IdMapping* pIdMappings = NULL)
  {
    OdUInt8Array pkgr;
    for (OdUInt32 n = 0; n < nBinaryFields; n++)
    {
      if (pBinaryFields[n])
        pkgr.insert(pkgr.end(), (const OdUInt8*)pBinaryFields[n], ((const OdUInt8*)pBinaryFields[n] + nBinaryFieldsData[n]));
    }
    *m_ppWhere = m_pWho;
    if (pkgr.size())
      OdGLES2ShareableClientData::process(m_pWho, resId, pRegId, pkgr.getPtr(), pIdMappings, m_pDevice->clientSettings(), &m_pDevice->outputRect());
    return true;
  }
};

OdTrVecDevice *DropSCDTest::m_pDevice = NULL;
#endif

OdGLES2JsonRendition::OdGLES2JsonRendition()
  : m_pJson()
  , m_pJsonObj()
  , m_mode(kIntermediate)
  , m_pRedir(NULL)
  , m_outputState(OdGLES2JsonServer::kIntermediateState)
  , m_pProcDevice(NULL)
{
  m_overallViewport.setDefault();
  m_pJsonObj = new JsonObjectFormat(m_pJson);
}

OdGLES2JsonRendition::~OdGLES2JsonRendition()
{
  finalizeJsonServerUsage();
}

OdIntPtr OdGLES2JsonRendition::getClientSettings() const
{
  return (OdIntPtr)&m_clientSettings;
}

void OdGLES2JsonRendition::setClientSettings(OdIntPtr pClSet)
{
  m_clientSettings = *(ClientSettings*)pClSet;
}

OdIntPtr OdGLES2JsonRendition::getJsonServer() const
{
  return (OdIntPtr)m_pJson.get();
}

void OdGLES2JsonRendition::setJsonServer(OdIntPtr pJsonServer)
{
  if (m_pJson.get() != (OdGLES2JsonServer*)pJsonServer)
    finalizeJsonServerUsage();
  m_pJson = (OdGLES2JsonServer*)pJsonServer;
  m_pJsonObj->SetJsonServer(m_pJson);
}

OdGLES2JsonServer *OdGLES2JsonRendition::json()
{
  if (m_pJson.isNull()) throw OdError(eNullPtr);
  return m_pJson;
}

const OdGLES2JsonServer *OdGLES2JsonRendition::json() const
{
  if (m_pJson.isNull()) throw OdError(eNullPtr);
  return m_pJson;
}

JsonObjectFormat *OdGLES2JsonRendition::json_obj()
{
  if (m_pJsonObj.isNull()) throw OdError(eNullPtr);
  return m_pJsonObj;
}

const JsonObjectFormat *OdGLES2JsonRendition::json_obj() const
{
  if (m_pJsonObj.isNull()) throw OdError(eNullPtr);
  return m_pJsonObj;
}

void OdGLES2JsonRendition::setIntermediateMode()
{
  m_mode = kIntermediate;
  m_pRedir->setForRecord();
}

void OdGLES2JsonRendition::setGsUpdateMode()
{
  m_mode = kGsUpdate;
  m_pRedir->setForPlay();
}

void OdGLES2JsonRendition::beginDeviceProcessing(OdTrVisRenderClient *pDevice)
{
  ODA_ASSERT(!m_pProcDevice);
  m_pProcDevice = pDevice;
}

void OdGLES2JsonRendition::endDeviceProcessing(OdTrVisRenderClient *
#ifdef ODA_DIAGNOSTICS
  pDevice
#endif
  )
{
  ODA_ASSERT(m_pProcDevice == pDevice);
  m_pProcDevice = NULL;
}

OdTrVisRenderClient *OdGLES2JsonRendition::processingDevice() const
{
  ODA_ASSERT(m_pProcDevice);
  return m_pProcDevice;
}

inline OdGLES2JsonServer::IdType renditionDataType2ServerIdType(OdTrVisRendition::DataType type)
{
  OdGLES2JsonServer::IdType                   idType = OdGLES2JsonServer::kUnknownId;
  switch (type)
  {
    case OdTrVisRendition::kViewportData:    idType = OdGLES2JsonServer::kViewportId;    break;
    case OdTrVisRendition::kMetafileData:    idType = OdGLES2JsonServer::kMetafileId;    break;
    case OdTrVisRendition::kStateBranchData: idType = OdGLES2JsonServer::kHlBranchId;    break;
    case OdTrVisRendition::kTextureData:     idType = OdGLES2JsonServer::kTextureId;     break;
    case OdTrVisRendition::kMaterialData:    idType = OdGLES2JsonServer::kMaterialId;    break;
    case OdTrVisRendition::kProgramData:     idType = OdGLES2JsonServer::kProgramId;     break;
    case OdTrVisRendition::kVisualStyleData: idType = OdGLES2JsonServer::kVisualStyleId; break;
    case OdTrVisRendition::kLayerData:       idType = OdGLES2JsonServer::kLayerId;       break;
    case OdTrVisRendition::kOverlayData:     idType = OdGLES2JsonServer::kOverlayId;     break;
    case OdTrVisRendition::kGroupData:       idType = OdGLES2JsonServer::kGroupId;       break;
    default:                                                                             break;
  }
  return idType;
}

bool OdGLES2JsonRendition::idRegTraverseCallback(OdTrVisRendition::DataType type, OdTrVisId id, OdTrVisUniqueID *pRegId)
{
  OdGLES2JsonServer::IdType idType = renditionDataType2ServerIdType(type);
  if (idType == OdGLES2JsonServer::kUnknownId) return true;
  json()->UnregisterId(id, pRegId, idType);    return true;
}

void OdGLES2JsonRendition::finalizeJsonServerUsage()
{
  if (m_pRedir && m_pJson.get())
  {
    m_pRedir->dropRecords(); // ???
    m_idReg.traverse(this);
    m_idReg.killAll();
  }
}

void OdGLES2JsonRendition::onDeviceUpdateBegin(OdTrVisRenderClient *pDevice)
{
#ifdef OD_GLES2JSON_DROPSCD_TEST
  DropSCDTest::m_pDevice = static_cast<OdTrVecDevice*>(pDevice);
#endif
  OutputState(OdGLES2JsonServer::kIntermediateState, true);

  json_obj()->SetMeataData((float)4.3, "Object", "TeighaObjectExporter");
  setGsUpdateMode();

  beginDeviceProcessing(pDevice);
  if (!updateClientDependentSectionOnly())
    m_pRedir->dropRecords(); // Output all collected between GsUpdate's data
}

void OdGLES2JsonRendition::onDeviceUpdateEnd(OdTrVisRenderClient *pDevice, bool /*bRender*/)
{
  setIntermediateMode();
  OutputState(OdGLES2JsonServer::kIntermediateState);  
  json_obj()->DropObject();

  endDeviceProcessing(pDevice);
}

void OdGLES2JsonRendition::obtainClientSettings(ClientSettings &clientSets)
{
  clientSets = m_clientSettings;
}

OdTrVisSharingProviderClientPtr OdGLES2JsonRendition::createSharingProvider()
{
  return OdRxObjectImpl<OdGLES2JsonSharingProvider, OdTrVisSharingProviderClient>::createObject();
}

OdTrVisRendition::MtHandlerType OdGLES2JsonRendition::mtDataTypeProcessing(DataType &type) const
{
  switch (type)
  {
    case kSurfaceData:
    case kViewportData: case kViewportPropsData:
    case kVpOverrideData: case kVpOverridePropsData:
    case kProgramData:
    case kOverlayData: case kOverlayPropsData:
    return kMtRedirect; // Redirect without Mt handler since not called from Mt
    case kMetafileData: case kMetafilePropsData:
    case kStateBranchData:
    case kTextureData:
    case kMaterialData:
    case kVisualStyleData:
    case kLayerData:
    return kMtGlobal; // Secure by global mutex since all passed through one JsonServer
    default:
      ODA_FAIL();
      return kMtRedirect;
  };
}

// Returns set of bit flags which indicate rendition capabilities/settings
OdUInt32 OdGLES2JsonRendition::queryRenditionCaps(OdUInt32 requestFor) const
{
  OdUInt32 retCaps = kSupportGsStateSaving | kSupportCompositeMetafiles | kSupportVisualStyles | kSupportOverlayBuffers;
  if (GETBIT(requestFor, kUpdateClientSectionOnly))
    SETBIT(retCaps, kUpdateClientSectionOnly,    json()->UpdateClientDependentSectionOnly());
  if (GETBIT(requestFor, kUpdateShareableSectionOnly))
    SETBIT(retCaps, kUpdateShareableSectionOnly, json()->UpdateShareableSectionOnly());
  return retCaps;
}

bool OdGLES2JsonRendition::isSupportCompositeMetafiles() const
{
  ODA_ASSERT(processingDevice());
  return processingDevice()->useCompositeMetafiles();
}
bool OdGLES2JsonRendition::isSupportVisualStyles() const
{
  ODA_ASSERT(processingDevice());
  return processingDevice()->useVisualStyles();
}
bool OdGLES2JsonRendition::isSupportOverlayBuffers() const
{
  ODA_ASSERT(processingDevice());
  return processingDevice()->useOverlays();
}

// Returns Id registrator, or NULL if no registration supported
OdTrVisRendition::IdRegistrator *OdGLES2JsonRendition::idRegistrator() const
{
  return &m_idReg;
}

bool OdGLES2JsonRendition::saveRenditionState(OdGsFiler *pFiler) const
{
  pFiler->wrChar('X');
  // Save client settings
  //if (!::odTrVisSaveClientSettings(pFiler, m_clientSettings))
  //  return false;
  // Save Id mapping
  if (!m_idReg.save(pFiler))
    return false;

  json()->saveState(pFiler);

  // Save overall viewport
  if (!::odTrVisSaveViewportDef(pFiler, m_overallViewport))
    return false;
  return true;
}

bool OdGLES2JsonRendition::loadRenditionState(OdGsFiler *pFiler, OdTrVisIdMap *pIdMap)
{
  if (pFiler->rdChar() != 'X')
    return false;
  // Load client settings
  //if (!::odTrVisLoadClientSettings(pFiler, m_clientSettings))
  //  return false;
  // Load Id mapping
  if (!m_idReg.load(pFiler, pIdMap))
    return false;

  json()->loadState(pFiler, pIdMap);

  // Load overall viewport
  if (!::odTrVisLoadViewportDef(pFiler, m_overallViewport, pIdMap))
    return false;
  return true;
}

void OdGLES2JsonRendition::onSurfaceChanged(const OdTrVisSurfaceDef &pDef)
{
  json_obj()->SetBackColor(pDef.m_backgroundColor);
}

struct json_RegistrationBase
{
  OdGLES2JsonServer *m_pJson;
  OdTrVisUniqueID *m_pRegId;
  OdTrVisRendition::DataType m_dataType;
  OdGLES2JsonServer::IdType m_idType;
  OdTrVisId m_resId;

  json_RegistrationBase(OdGLES2JsonServer *pJson, OdTrXmlRegistratorImpl &idReg, OdTrVisRendition::DataType dataType, OdTrVisId resId, bool idDel = false)
    : m_pJson(pJson)
    , m_pRegId(idReg.get(dataType, resId, idDel))
    , m_dataType(dataType)
    , m_idType(renditionDataType2ServerIdType(dataType))
    , m_resId(resId)
  {
  }
};
struct json_RegisterId : public json_RegistrationBase
{
  json_RegisterId(OdGLES2JsonServer *pJson, OdTrXmlRegistratorImpl &idReg, OdTrVisRendition::DataType dataType, OdTrVisId resId)
    : json_RegistrationBase(pJson, idReg, dataType, resId)
  {
    m_pJson->RegisterId(m_resId, m_pRegId, m_idType);
  }
};
struct json_UnregisterId : public json_RegistrationBase
{
  json_UnregisterId(OdGLES2JsonServer *pJson, OdTrXmlRegistratorImpl &idReg, OdTrVisRendition::DataType dataType, OdTrVisId resId)
    : json_RegistrationBase(pJson, idReg, dataType, resId) { }
  ~json_UnregisterId()
  {
    m_pJson->UnregisterId(m_resId, m_pRegId, m_idType);
  }
};
#define JSON_REGISTERED(dataType, resId) \
  json_RegistrationBase _jsonReg(json(), m_idReg, dataType, resId)
#define JSON_REGISTER(dataType, resId) \
  json_RegisterId _jsonReg(json(), m_idReg, dataType, resId)
#define JSON_UNREGISTER(dataType, resId) \
  json_UnregisterId _jsonReg(json(), m_idReg, dataType, resId)
#define JSON_DROP_REG_ID(pTagName) \
  json()->DropId(pTagName, _jsonReg.m_resId, _jsonReg.m_pRegId, _jsonReg.m_idType)

void OdGLES2JsonRendition::onOverlayAdded(OdTrVisOverlayId overlayId, const OdTrVisOverlayDef &pDef)
{
}

void OdGLES2JsonRendition::onOverlayDeleted(OdTrVisOverlayId overlayId)
{
}

void OdGLES2JsonRendition::onOverlayVisibilityChanged(OdTrVisOverlayId overlayId, bool bVisibility)
{
}

void OdGLES2JsonRendition::onOverlayRenderOrderChanged(OdTrVisOverlayId overlayId, OdInt16 nRenderOrder)
{
}

void OdGLES2JsonRendition::onViewportAdded(OdTrVisViewportId viewportId, const OdTrVisViewportDef &pDef)
{
  JSON_REGISTER(kViewportData, viewportId);
  json_obj()->SetCameraMetafileMode();
}

void OdGLES2JsonRendition::onViewportInserted(OdTrVisViewportId viewportId, int nIndex, const OdTrVisViewportDef &pDef)
{
}

void OdGLES2JsonRendition::onViewportDeleted(OdTrVisViewportId viewportId)
{
}

void OdGLES2JsonRendition::DropViewParams(JsonObjectFormat *pJsonObj, const OdTrVisViewParamsDef &pDef, const OdTrVisId &view_id)
{
  pJsonObj->SetCameraMetafileMatrix(pDef.m_metafileMatrix);

  OdGeVector3d zAxis = (pDef.m_viewBasis.origin() - pDef.m_viewTarget).normalize();
  OdGeVector3d xAxis = zAxis.crossProduct(OdGeVector3d::kYAxis);
  OdGeVector3d yAxis = zAxis.crossProduct(xAxis);
  const OdGeMatrix3d &matrix = OdGeMatrix3d().setCoordSystem(pDef.m_viewBasis.origin(), xAxis, yAxis, zAxis);

  if (pDef.m_bPerspectiveProjection == true)
    pJsonObj->AddPerspectiveCamera(view_id, pDef.m_fieldWidth / pDef.m_fieldHeight, pDef.m_viewingMatrix, pDef.m_frontClip.m_bClipped ? pDef.m_frontClip.m_clipDist : (std::numeric_limits<float>::max)(), pDef.m_backClip.m_bClipped ? pDef.m_backClip.m_clipDist : (std::numeric_limits<float>::min)());
  else
    pJsonObj->AddOrthographicCamera(view_id, pDef.m_fieldWidth, pDef.m_fieldHeight, pDef.m_viewingMatrix, (std::numeric_limits<float>::max)(), (std::numeric_limits<float>::min)());
}

void OdGLES2JsonRendition::onViewportViewParamsModified(OdTrVisViewportId viewportId, const OdTrVisViewParamsDef &pDef)
{
  JSON_REGISTERED(kViewportData, viewportId);//

  DropViewParams(json_obj(), pDef, _jsonReg.m_resId);
}

void OdGLES2JsonRendition::onViewportLineweightsModified(OdTrVisViewportId viewportId, const OdTrVisViewportLineweightsDef &pDef)
{
  json_obj()->RecalcLensWeight(pDef.lineweightsCoef());
  if (pDef.hasLineweightsEnum())
    json_obj()->SetLensWeightByIndx(pDef.m_lineweightsEnum);
}

void OdGLES2JsonRendition::onViewportBackgroundChanged(OdTrVisViewportId viewportId, OdTrVisFlatMetafileContainerPtr pStream, OdTrVisProgramId baseProgramId)
{
}

void OdGLES2JsonRendition::onViewportAmbientLightChanged(OdTrVisViewportId viewportId, const OdTrVisMaterialColor &ambientLight)
{
  json_obj()->AddAmbientLight(viewportId, ambientLight.toCref());
}

void OdGLES2JsonRendition::onViewportDefaultLightsChanged(OdTrVisViewportId viewportId, bool bDefaultLightsOn,
                                                          const OdTrVisLightDef *pLightsList, OdUInt32 nLightsListEntries)
{
  for (OdUInt32 n = 0; n < nLightsListEntries; n++)
  {
    switch (pLightsList[n].m_type)
    {
      case OdTrVisLightDef::kPoint:
        json_obj()->AddPointLight(viewportId, pLightsList[n].m_color.toCref(), pLightsList[n].m_position);
        break;
     case OdTrVisLightDef::kDistant:
       json_obj()->AddDirectionLight(viewportId, pLightsList[n].m_color.toCref(), pLightsList[n].m_direction);
       break;
     case OdTrVisLightDef::kSpot:
       json_obj()->AddSpotLight(viewportId, pLightsList[n].m_color.toCref(), pLightsList[n].m_position, pLightsList[n].m_direction);
       break;
     default:
       break;
    }
  }
}

void OdGLES2JsonRendition::onViewportLightAttached(OdTrVisViewportId viewportId, OdTrVisLightId lightId,
                                                   OdUInt32 nOverrides, const OdTrVisLightDef &pOverrides)
{
  OdTrVisLightDef lightDef = m_lights[lightId];
  lightDef.apply(nOverrides, pOverrides);
  switch (lightDef.m_type)
  {
    case OdTrVisLightDef::kPoint:
      json_obj()->AddPointLight(viewportId, lightDef.m_color.toCref(), lightDef.m_position);
      break;
   case OdTrVisLightDef::kDistant:
     json_obj()->AddDirectionLight(viewportId, lightDef.m_color.toCref(), lightDef.m_direction);
     break;
   case OdTrVisLightDef::kSpot:
     json_obj()->AddSpotLight(viewportId, lightDef.m_color.toCref(), lightDef.m_position, lightDef.m_direction);
     break;
   default:
     break;
  }
}

void OdGLES2JsonRendition::onViewportLightDetached(OdTrVisViewportId viewportId, OdTrVisLightId lightId)
{
}

void OdGLES2JsonRendition::onLightAdded(OdTrVisLightId lightId, const OdTrVisLightDef &pDef)
{
  m_lights[lightId] = pDef;
}

void OdGLES2JsonRendition::onLightModified(OdTrVisLightId lightId, OdUInt32 nKindOfMod, const OdTrVisLightDef &pDef)
{
  m_lights[lightId].apply(nKindOfMod, pDef);
}

void OdGLES2JsonRendition::onLightDeleted(OdTrVisLightId lightId)
{
  m_lights.erase(lightId);
}

void OdGLES2JsonRendition::onOverlayViewParamsOverride(OdTrVisViewportId viewportId, OdTrVisOverlayId overlayId, bool bOverride, const OdTrVisViewParamsDef &pDef)
{
}

void OdGLES2JsonRendition::onOverlayExtentsOverride(OdTrVisViewportId viewportId, OdTrVisOverlayId overlayId, const OdTrVisExtentsDef &pDef)
{
}

void OdGLES2JsonRendition::onMetafileOrderChanged(OdTrVisViewportId viewportId, OdTrVisOverlayId overlayId, OdUInt32 nInvalidFrom, OdUInt32 nInvalidLen,
                                                 const OdTrVisDisplayId *pValidFrom, OdUInt32 nValidLen)
{
  onMetafileOrderChangedImpl(viewportId, overlayId, nInvalidFrom, nInvalidLen, pValidFrom, nValidLen);
}

bool OdGLES2JsonRendition::DropDisplayList(const OdTrVisDisplayId *pDispList, OdUInt32 nListLen, const OdTrVisId &ViewPortId, DDL2ndPassInfo *p2ndPass)
{ 
  for (OdUInt32 n = 0; n < nListLen; n++)
  {
    ODA_ASSERT(pDispList[n] >= kDisplayCodeRange);
    OdTrVisUniqueID *pRegEntry = m_idReg.get(kMetafileData, pDispList[n]);
    if (!p2ndPass || pRegEntry)
    {
      JSON_REGISTERED(kMetafileData, pDispList[n]);
      json_obj()->SetCameraMetafileMatrixToObject(_jsonReg.m_resId);
    }
    else
    {
      if (!p2ndPass->m_bScan)
      {
        p2ndPass->m_bScan = true;
        p2ndPass->m_nTransLast = p2ndPass->m_nTransFirst = n;
      }
      else
        p2ndPass->m_nTransLast = n;
    }
  }
  if (p2ndPass)
    return p2ndPass->m_bScan;
  return false;
}

void OdGLES2JsonRendition::DropDisplayList2ndPass(OdTrVisViewportId viewportId, OdTrVisOverlayId overlayId, OdUInt32 nInvalidFrom,
                                                 const OdTrVisDisplayId *pDispList, OdUInt32 nListLen, DDL2ndPassInfo &p2ndPass)
{
  OdUInt32 nScan = p2ndPass.m_nTransFirst;
  while (nScan <= p2ndPass.m_nTransLast)
  {
    OdUInt32 nScanLast = nScan + 1;
    while (nScanLast <= p2ndPass.m_nTransLast)
    {
      if (m_idReg.get(kMetafileData, pDispList[nScanLast]))
        break;
      nScanLast++;
    }
    onMetafileOrderChangedImpl(viewportId, overlayId, nInvalidFrom + nScan, nScanLast - nScan, pDispList + nScan, nScanLast - nScan, false);
    nScan = nScanLast + 1;
    while (nScan <= p2ndPass.m_nTransLast)
    {
      if (!m_idReg.get(kMetafileData, pDispList[nScan]))
        break;
      nScan++;
    }
  }
}

void OdGLES2JsonRendition::onMetafileOrderChangedImpl(OdTrVisViewportId viewportId, OdTrVisOverlayId overlayId, OdUInt32 nInvalidFrom, OdUInt32 nInvalidLen,
                                                     const OdTrVisDisplayId *pValidFrom, OdUInt32 nValidLen, bool bFirstPass)
{
  JSON_REGISTERED(kViewportData, viewportId);

  DDL2ndPassInfo s2ndPass;
  DropDisplayList(pValidFrom, nValidLen, _jsonReg.m_resId, (bFirstPass) ? &s2ndPass : NULL); 
}

OdTrVisDisplayId OdGLES2JsonRendition::onMetafileAdded(OdTrVisMetafileId metafileId, const OdTrVisMetafileDef &pDef)
{
  JSON_REGISTER(kMetafileData, metafileId);
  OutputState((_jsonReg.m_pRegId) ? OdGLES2JsonServer::kShareableState : OdGLES2JsonServer::kClientOnlyState);
  {
    if (!json()->DropMetafileAdded(*this, metafileId, pDef))
    {
      DropMetadata(pDef.m_pMetafile.get(), _jsonReg.m_resId, /*pDef.m_pMetafile->m_pLayer*/kTrVisNullId); // @@@TODO: layer is separate metafile property now.
    }

#ifdef OD_GLES2JSON_DROPHLTASCLIENTONLY
    if (_jsonReg.m_pRegId && pDef.m_pMetafile->isMetafileHighlighted())
      onMetafileHighlightingChanged(metafileId, true);
#endif
  }
  return (OdTrVisDisplayId)metafileId;
}

void OdGLES2JsonRendition::onMetafileDeleted(OdTrVisMetafileId metafileId)
{
}

void OdGLES2JsonRendition::onMetafileVisibilityChanged(OdTrVisMetafileId metafileId, bool bVisibility)
{
}

void OdGLES2JsonRendition::onMetafileHighlightingChanged(OdTrVisMetafileId metafileId, bool bHighlight)
{
}

void OdGLES2JsonRendition::onMetafileFadingChanged(OdTrVisMetafileId metafileId, bool bFade)
{
}

void OdGLES2JsonRendition::onStateBranchAdded(OdTrVisStateBranchId hlBranchId, const OdTrVisStateBranchDef &pDef)
{
}

void OdGLES2JsonRendition::onStateBranchModified(OdTrVisStateBranchId hlBranchId, const OdTrVisStateBranchDef &pDef,
                                             bool bChildsModified, bool bMarkersModified)
{
}

void OdGLES2JsonRendition::onStateBranchDeleted(OdTrVisStateBranchId hlBranchId)
{
}


void OdGLES2JsonRendition::onTextureAdded(OdTrVisTextureId textureId, const OdTrVisTextureDef &pDef)
{
}

void OdGLES2JsonRendition::onTextureDeleted(OdTrVisTextureId textureId)
{
}

void OdGLES2JsonRendition::onMaterialAdded(OdTrVisMaterialId materialId, const OdTrVisMaterialDef &pDef)
{
  JSON_REGISTER(kMaterialData, materialId);
  OutputState((_jsonReg.m_pRegId) ? OdGLES2JsonServer::kShareableState : OdGLES2JsonServer::kClientOnlyState);

  json_obj()->AddMaterial(_jsonReg.m_resId, JsonMaterials::default_mat_type, pDef.m_diffuseChannel.m_realisticComponent.m_opacityLevel);
  json_obj()->AddMaterialColor(_jsonReg.m_resId, JsonMaterialColor::ambient_color, pDef.m_ambientChannel.m_realisticComponent.m_channelColor.toCref());
  json_obj()->AddMaterialColor(_jsonReg.m_resId, JsonMaterialColor::emessive_color, pDef.m_emissionChannel.m_realisticComponent.m_channelColor.toCref());
  json_obj()->AddMaterialColor(_jsonReg.m_resId, JsonMaterialColor::specular_color, pDef.m_specularChannel.m_realisticComponent.m_channelColor.toCref());
}

void OdGLES2JsonRendition::onMaterialDeleted(OdTrVisMaterialId materialId)
{
}

void OdGLES2JsonRendition::onVisualStyleAdded(OdTrVisVisualStyleId visualStyleId, const OdTrVisVisualStyle &pDef)
{
}

void OdGLES2JsonRendition::onVisualStyleModified(OdTrVisVisualStyleId visualStyleId, const OdTrVisVisualStyle &pDef)
{
}

void OdGLES2JsonRendition::onVisualStyleDeleted(OdTrVisVisualStyleId visualStyleId)
{
}

void OdGLES2JsonRendition::onLayerAdded(OdTrVisLayerId layerId, const OdTrVisLayerDef &pDef)
{
  JSON_REGISTER(kLayerData, layerId);
  json_obj()->AddLayer(_jsonReg.m_resId, /*pDef.m_name*/NULL); // @@@TODO: name is separate layer property now.
}

void OdGLES2JsonRendition::onLayerDeleted(OdTrVisLayerId layerId)
{
}

void OdGLES2JsonRendition::onLayerVpDepPropsOverride(OdTrVisLayerId layerId, OdTrVisViewportId viewportId, bool bOverride, const OdTrVisLayerProps &pProps)
{
}


void OdGLES2JsonRendition::DropStateBranch(const OdTrVisStateBranchDef &pHlBranch, bool bDropChilds, bool bDropMarkers)
{
}

void OdGLES2JsonRendition::DropVisualStyleData(const OdTrVisVisualStyle &pVStyle, bool bDropNonModified)
{
}

void OdGLES2JsonRendition::DropLayerData(const OdTrVisLayerDef &pLayer, bool bDropOwnerId)
{ 
}

void OdGLES2JsonRendition::DropLayerProps(const OdTrVisLayerProps &pLayerProps)
{
}

void OdGLES2JsonRendition::DropMetadata(const OdTrVisFlatMetafileContainer *pMetafile, const OdUInt64 &metafile_reg_id, const OdUInt64 &layer_id)
{
  if (!pMetafile || !pMetafile->size())
    return;

  JsonMetafileConverter metafile_converter;
  bool isNeedToCreateObj = true;

  OdTrVisMetafileParser mfParser(pMetafile, (!processingDevice()->ttfFontsCache()) ? OdTrVisMetafileParser::kSmStandalone : OdTrVisMetafileParser::kSmBasic);
  const OdTrVisMetafileParser::VarState &varState = mfParser.nextStep();
  do
  {
    switch (varState.m_chunk)
    {
      case OdTrVisMetaRecType_Color:
      { OdUInt8 rgba[4]; for (int nVal = 0; nVal < 4; nVal++) { rgba[nVal] = mfParser.nextStep().asUInt8(); }
        metafile_converter.SetRGB(ODRGBA(rgba[0], rgba[1], rgba[2], rgba[3]));
      }
      break;
      case OdTrVisMetaRecType_EnableArray:
      { const OdTrVisMetaRecArrayType type = (OdTrVisMetaRecArrayType)mfParser.nextStep().asUInt8();
        switch (type)
        { case OdTrVisMetaRecArrayType_Color:
            metafile_converter.OrToFacesForm(JsonMetafileConverter::vertex_color);
          break;
          case OdTrVisMetaRecArrayType_Normal:
            metafile_converter.OrToFacesForm(JsonMetafileConverter::vertex_normal);
          break;
          default: break;
        }
        if (type != OdTrVisMetaRecArrayType_Normal2)
          metafile_converter.AddGeometryArrayInd(mfParser.nextStep().asUInt32(), type);
      }
      break;
      case OdTrVisMetaRecType_DisableArray:
      { const OdTrVisMetaRecArrayType type = (OdTrVisMetaRecArrayType)mfParser.nextStep().asUInt8();
        switch (type)
        { case OdTrVisMetaRecArrayType_Color:
            metafile_converter.AndToFacesForm(~JsonMetafileConverter::vertex_color);
          break;
          case OdTrVisMetaRecArrayType_Normal:
            metafile_converter.AndToFacesForm(~JsonMetafileConverter::vertex_normal);
          break;
          default: break;
        }
        if (type != OdTrVisMetaRecArrayType_Normal2)
          metafile_converter.DeleteGeometryArrayByType(type);
      }
      break;
      case OdTrVisMetaRecType_DrawArrays:
      { const OdTrVisGeomPrim type = (OdTrVisGeomPrim)mfParser.nextStep().asUInt8();
        const OdInt32 first = mfParser.nextStep().asInt32();
        const OdInt32 count = mfParser.nextStep().asInt32();
        switch (type)
        {
          case kTrVisPoints: //render points (1 vertex per point).
            metafile_converter.AddPoint(first, count);
          break;
          case kTrVisLines: //render lines
            metafile_converter.AddLine(first, count);
          break;
          case kTrVisLineStrip: //render lines strip
            metafile_converter.AddLineStrip(first, count);
          break;
          case kTrVisTriangles: //render filled triangles(3 vertexes per triangle)
            if (json()->isEnableFaces())
              metafile_converter.AddMesh(first, count);
          break;
          default: break;
        }
        //not implemented for type
        //kTrVisLineLoop - render lines loop
        //kTrVisTriangleStrip - render filled triangles strip
        //kTrVisTriangleFan - render filled triangles fan
      }
      break;
      case OdTrVisMetaRecType_DrawElements:
      { const OdTrVisGeomPrim type = (OdTrVisGeomPrim)mfParser.nextStep().asUInt8();
        const OdInt32 count = mfParser.nextStep().asInt32();
        const OdUInt32 ind = mfParser.nextStep().asUInt32();
        switch (type)
        {
          case kTrVisPoints: //render points (1 vertex per point).
             metafile_converter.AddPoint(0, count, JsonMetafileConverter::buffer_geometry, ind);
          break;
          case kTrVisLines: //render lines
            metafile_converter.AddLine(0, count, JsonMetafileConverter::buffer_geometry, ind);
          break;
          case kTrVisLineStrip: //render lines strip
            metafile_converter.AddLineStrip(0, count, JsonMetafileConverter::buffer_geometry, ind);
          break;
          case kTrVisTriangles: //render filled triangles(3 vertexes per triangle)
            if (json()->isEnableFaces())
              metafile_converter.AddMesh(0, count, JsonMetafileConverter::buffer_geometry, ind);
          break;
          default: break;
        }
        //not implemented for type
        //kTrVisLineLoop - render lines loop
        //kTrVisTriangleStrip - render filled triangles strip
        //kTrVisTriangleFan - render filled triangles fan
      }
      break;
      case OdTrVisMetaRecType_VPoint:
      {
        metafile_converter.AddPoint(mfParser.nextStep().asFVec());
      }
      break;
      case OdTrVisMetaRecType_VLine:
      {
        metafile_converter.AddLine(mfParser.nextStep().asFVec());
      }
      break;
      case OdTrVisMetaRecType_DPoint:
      { float cvt[3]; const OdGePoint3d &pt = mfParser.nextStep().asDPoint3();
        cvt[0] = (float)pt.x; cvt[1] = (float)pt.y; cvt[2] = (float)pt.z;
        metafile_converter.AddPoint(cvt);
      }
      break;
      case OdTrVisMetaRecType_DLine:
      { float cvt[6]; const OdGePoint3d &pt1 = mfParser.nextStep().asDPoint3();
        cvt[0] = (float)pt1.x; cvt[1] = (float)pt1.y; cvt[2] = (float)pt1.z;
        const OdGePoint3d &pt2 = mfParser.nextStep().asDPoint3();
        cvt[3] = (float)pt2.x; cvt[4] = (float)pt2.y; cvt[5] = (float)pt2.z;
        metafile_converter.AddLine(cvt);
      }
      break;
      case OdTrVisMetaRecType_IPoint:
      {
        metafile_converter.AddPoint(mfParser.nextStep().asInt32(), 1);
      }
      break;
      case OdTrVisMetaRecType_ILine:
      { // AMark: this previous solution is wrong since ILine contain two indices - them can't be passed as first and count somehow.
        //const OdInt32 &first = OD_OGL_RDR_READVAL(OdInt32, pMemPtr);
        //const OdInt32 &count = OD_OGL_RDR_READVALOFFSET(OdInt32, pMemPtr, sizeof(OdInt32)) - first + 1;
        //metafile_converter.AddLine(first, count);
        OdInt32 ids[2]; ids[0] = mfParser.nextStep().asInt32(); ids[1] = mfParser.nextStep().asInt32();
      }
      break;
      case OdTrVisMetaRecType_Material:
        metafile_converter.SetMaterial(mfParser.nextStep().asUInt64());
      break;
      case OdTrVisMetaRecType_Lineweight:
      {
        const OdTrVisLwdSetting::LwdType lwdType = (OdTrVisLwdSetting::LwdType)mfParser.nextStep().asUInt8();
        if (OdTrVisLwdSetting::isPs(lwdType))
        {
          metafile_converter.SetLineWeight<double>(lwdType, mfParser.nextStep().asDouble());
        }
        else
        {
          metafile_converter.SetLineWeight<OdInt16>(lwdType, mfParser.nextStep().asInt16());
        }
      }
      break;
      case OdTrVisMetaRecType_TtfText:
      {
        const OdTrVisTtfFontsCacheClient *pCache = processingDevice()->ttfFontsCache();
        if (pCache)
        { // In case if real vectorization device is connected
          OdUInt64 fontKeyA = mfParser.nextStep().asUInt64();
          OdUInt64 fontKeyB = mfParser.nextStep().asUInt64();

          const OdGeMatrix3d &pMtx = mfParser.nextStep().asDMatrix3d();
          const OdGeVector3d &pVec = mfParser.nextStep().asDVec3();
          OdUInt32 nText = mfParser.nextStep().asUInt32();
          const OdUInt32 *pText = (const OdUInt32*)mfParser.nextStep().m_pVar;
          OdTrVisTtfFontsCacheClient::TtfFont pFont = pCache->getFontCache(fontKeyA, fontKeyB);

          if (pFont && nText)
          {
            for (OdUInt32 n = 0; n < nText; n++)
            {
              double sideMult;
              OdTrVisDisplayId mfId = pCache->getCharMetafile(pFont, pText[n], &sideMult);
              OdGeMatrix3d mtrx = pMtx;
              //mtrx.setToProduct(mtrx, OdGeMatrix3d::translation(*pVec * sideMult));
              json_obj()->SetObjectMatrix(mfId, mtrx);
              
              if (isNeedToCreateObj)
                isNeedToCreateObj = false;
            }
          }
        }
        else
        { // In case if there is no connection to real vectorization device
          // . . .
        }
      }
      break;
      case OdTrVisMetaRecType_GeomMarker:
      {
        metafile_converter.SetGeomMark(mfParser.nextStep().asUInt8());
      }
      break;

      default: break;
    }
    mfParser.nextStep(OdTrVisMetafileParser::kOpSkip);
  }
  while (varState.m_chunk != OdTrVisMetaRecType_NTypes);

  if (isNeedToCreateObj)
    metafile_converter.AddObjectsByRootId(json_obj(), pMetafile, metafile_reg_id, layer_id);
}

void OdGLES2JsonRendition::OutputState(OdGLES2JsonServer::OutputState newState, bool bForce)
{
  if ((newState != m_outputState) || bForce)
  {
    m_outputState = newState;
    json()->OnStateChanged(newState);
  }
}

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
#include "RxObject.h"
#include "RxInit.h"

#include "HatchPatternManager.h"

#include "TvFactory.h"
#include "TvFilerTimer.h"
#include "TvModuleNames.h"
#include "TvDatabaseCleaner.h"
#include "TvDatabaseUtils.h"
#include "ColorMapping.h"

#include "Ifc2Visualize.h"
#include "IfcGiContext.h"
#include "IfcAttributesEnum.h"
#include "IfcDeviationParams.h"
#include "IfcModelContext.h"
#include "IfcFile.h"
#include "Entities/IfcProject.h"
#include "daiAggr/daiSet.h"

#include "daiSettings.h"
#include "daiError/daiErrorEvent.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include "RxSystemServices.h"

using namespace OdIfc;
using namespace IFC2Visualize;

#define OdIfcStoreysClassName     L"IfcBuildingStorey"
#define OdIfcBridgePartClassName  L"IfcBridgePart"

OdTv::Units getUnits(OdIfcFilePtr pIfcDatabase, double& addUnitCoefToMeters)
{
  OdTv::Units tvUnits = OdTv::kMeters;
  addUnitCoefToMeters = 1.;

  auto pIfcProject = pIfcDatabase->getProjectId().openObject();
  if (!pIfcProject.isNull())
  {
    OdDAIObjectId unitAssignment;
    if ((pIfcProject->getAttr("unitsincontext") >> unitAssignment))
    {
      auto pUnitAssignment = unitAssignment.openObject();
      if (!pUnitAssignment.isNull())
      {
        OdDAI::Aggr* pUnits;
        if ((pUnitAssignment->getAttr("units") >> pUnits))
        {
          if (pUnits)
          {
            for (auto pIter = pUnits->createConstIterator(); pIter->next();)
            {
              OdDAIObjectId objectId;
              if (!(pIter->getCurrentMember() >> objectId))
              {
                continue;
              }
              if (!objectId.isValid())
              {
                continue;
              }
              OdDAI::ApplicationInstancePtr pEntity = OdDAI::ApplicationInstance::cast(objectId.openObject());
              if (!pEntity.isNull())
              {
                OdAnsiString unitType;
                if ((pEntity->getAttr("unittype") >> unitType))
                {
                  if (unitType == OD_T("LENGTHUNIT"))
                  {
                    if (pEntity->isKindOf("ifcSIUnit"))
                    {
                      OdAnsiString unitPrefix;
                      if ((pEntity->getAttr("prefix") >> unitPrefix))
                      {
                        if (!unitPrefix.isEmpty())
                        {
                          if (unitPrefix == OD_T("MILLI"))
                            tvUnits = OdTv::kMillimeters;
                          else if (unitPrefix == OD_T("CENTI"))
                            tvUnits = OdTv::kCentimeters;
                          else if (unitPrefix == OD_T("MICRO"))
                            tvUnits = OdTv::kMicrometers;
                          else if (unitPrefix == OD_T("KILO"))
                            tvUnits = OdTv::kKilometers;
                          else
                          {
                            if (unitPrefix == OD_T("NANO"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e-9;
                            }
                            else if (unitPrefix == OD_T("PICO"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e-12;
                            }
                            else if (unitPrefix == OD_T("FEMTO"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e-15;
                            }
                            else if (unitPrefix == OD_T("ATTO"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e-18;
                            }
                            else if (unitPrefix == OD_T("DECI"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 0.1;
                            }
                            else if (unitPrefix == OD_T("DECA"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 10.;
                            }
                            else if (unitPrefix == OD_T("HECTO"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 100.;
                            }
                            else if (unitPrefix == OD_T("MEGA"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e6;
                            }
                            else if (unitPrefix == OD_T("GIGA"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e9;
                            }
                            else if (unitPrefix == OD_T("TERA"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e12;
                            }
                            else if (unitPrefix == OD_T("PETA"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e15;
                            }
                            else if (unitPrefix == OD_T("EXA"))
                            {
                              tvUnits = OdTv::kUserDefined;
                              addUnitCoefToMeters = 1.0e18;
                            }
                          }
                        }
                      }
                    }
                    else if (pEntity->isKindOf("ifcConversionBasedUnit"))
                    {
                      OdAnsiString unitName;
                      if ((pEntity->getAttr("name") >> unitName))
                      {
                        if (unitName == OD_T("FOOT"))
                          tvUnits = OdTv::kFeet;
                        else if (unitName == OD_T("INCH"))
                          tvUnits = OdTv::kInches;
                        else if (unitName == OD_T("YARD"))
                          tvUnits = OdTv::kYards;
                        else if (unitName == OD_T("MILE"))
                          tvUnits = OdTv::kMiles;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return tvUnits;
}

//***************************************************************************//
// 'OdTvVisualizePrcFilerProperties' methods implementation
//***************************************************************************//

OdTvVisualizeIfcFilerProperties::OdTvVisualizeIfcFilerProperties()
  : m_flags(0)
  , m_pPalette(0)
  , m_pCallback(NULL)
  , m_minPerCircle(8)
  , m_maxPerCircle(128)
  , m_deviation(0.5)
  , m_modelerType(0)
  , m_isMultithreadLoadEnabled(true)
  , m_countedLoadedThreads(4)
  , m_pHostAppProgressMeter(NULL)
  , m_useDictionaryTypePath(true)
  , m_storeInveseAttributes(false)
  , m_deflateLevel(6)
  , m_readChunkSize(0)
  , m_writeChunkSize(1024)
  , m_pInterruptCallback(0)
{
  m_importRect.xmax = 0;
  m_importRect.xmin = 0;
  m_importRect.ymax = 0;
  m_importRect.ymin = 0;
}

OdRxDictionaryPtr OdTvVisualizeIfcFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeIfcFilerProperties, OdRxDictionary>::createObject();
}

void OdTvVisualizeIfcFilerProperties::setDefaultColor(OdIntPtr pDefColor)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(pDefColor);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getDefaultColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizeIfcFilerProperties::setPalette(OdIntPtr palette)
{
  const ODCOLORREF* pPalette = (const ODCOLORREF*)(palette);

  m_pPalette = pPalette;
}

void OdTvVisualizeIfcFilerProperties::setBgColor(OdIntPtr pDefColor)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(pDefColor);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_bgColor = *pColor;
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getBgColor() const
{
  return (OdIntPtr)(&m_bgColor);
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getPalette() const
{
  return (OdIntPtr)(m_pPalette);
}

void OdTvVisualizeIfcFilerProperties::setDeviation(double deviation)
{
  m_deviation = deviation;
}

double OdTvVisualizeIfcFilerProperties::getDeviation() const
{
  return m_deviation;
}

void OdTvVisualizeIfcFilerProperties::setMinPerCircle(OdUInt16 minPerCircle)
{
  m_minPerCircle = minPerCircle;
}

OdUInt16 OdTvVisualizeIfcFilerProperties::getMinPerCircle() const
{
  return m_minPerCircle;
}

void OdTvVisualizeIfcFilerProperties::setMaxPerCircle(OdUInt16 maxPerCircle)
{
  m_maxPerCircle = maxPerCircle;
}

OdUInt16 OdTvVisualizeIfcFilerProperties::getMaxPerCircle() const
{
  return m_maxPerCircle;
}

OdUInt8 OdTvVisualizeIfcFilerProperties::getModelerType() const
{
  return m_modelerType;
}

void OdTvVisualizeIfcFilerProperties::setModelerType(OdUInt8 type)
{
  m_modelerType = type;
}

void OdTvVisualizeIfcFilerProperties::setHostAppProgressMeter(OdIntPtr pProgressMeter)
{
  m_pHostAppProgressMeter = (OdTvHostAppProgressMeter*)pProgressMeter;
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getHostAppProgressMeter() const
{
  return (OdIntPtr)m_pHostAppProgressMeter;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setMultithreadingEnable(bool isEnabled)
{
  m_isMultithreadLoadEnabled = isEnabled;
}

bool IFC2Visualize::OdTvVisualizeIfcFilerProperties::getMultithreadingEnable() const
{
  return m_isMultithreadLoadEnabled;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setThreadsCount(OdInt16 countThreads)
{
  m_countedLoadedThreads = countThreads;
}

OdInt16 IFC2Visualize::OdTvVisualizeIfcFilerProperties::getThreadsCount() const
{
  return m_countedLoadedThreads;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setUseDictionaryTypePath(bool useDictionaryTypePath)
{
  m_useDictionaryTypePath = useDictionaryTypePath;
}

bool IFC2Visualize::OdTvVisualizeIfcFilerProperties::getUseDictionaryTypePath() const
{
  return m_useDictionaryTypePath;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setStoreInveseAttributes(bool storeInveseAttributes)
{
  m_storeInveseAttributes = storeInveseAttributes;
}

bool IFC2Visualize::OdTvVisualizeIfcFilerProperties::getStoreInveseAttributes() const
{
  return m_storeInveseAttributes;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setDeflateLevel(OdUInt16 deflateLevel)
{
  m_deflateLevel = deflateLevel;
}

OdUInt16 IFC2Visualize::OdTvVisualizeIfcFilerProperties::getDeflateLevel() const
{
  return m_deflateLevel;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setReadChunkSize(OdUInt32 readChunkSize)
{
  m_readChunkSize = readChunkSize;
}

OdUInt32 IFC2Visualize::OdTvVisualizeIfcFilerProperties::getReadChunkSize() const
{
  return m_readChunkSize;
}

void IFC2Visualize::OdTvVisualizeIfcFilerProperties::setWriteChunkSize(OdUInt32 writeChunkSize)
{
  m_writeChunkSize = writeChunkSize;
}

OdUInt32 IFC2Visualize::OdTvVisualizeIfcFilerProperties::getWriteChunkSize() const
{
  return m_writeChunkSize;
}

OdTvVisualizeIfcFilerProperties::~OdTvVisualizeIfcFilerProperties()
{
}

namespace IFC2Visualize {

  ODRX_DECLARE_PROPERTY(Palette)
  ODRX_DECLARE_PROPERTY(DCRect)
  ODRX_DECLARE_PROPERTY(ObjectNaming)
  ODRX_DECLARE_PROPERTY(StoreSourceObjects)
  ODRX_DECLARE_PROPERTY(ClearEmptyObjects)
  ODRX_DECLARE_PROPERTY(RearrangeObjects)
  ODRX_DECLARE_PROPERTY(AppendTransform)
  ODRX_DECLARE_PROPERTY(FeedbackForChooseCallback)
  ODRX_DECLARE_PROPERTY(DefaultEntityColor)
  ODRX_DECLARE_PROPERTY(Deviation)
  ODRX_DECLARE_PROPERTY(MinPerCircle)
  ODRX_DECLARE_PROPERTY(MaxPerCircle)
  ODRX_DECLARE_PROPERTY(NeedCDATree)
  ODRX_DECLARE_PROPERTY(ModelerType)
  ODRX_DECLARE_PROPERTY(NeedCollectPropertiesInCDA)
  ODRX_DECLARE_PROPERTY(UseCustomBgColor)
  ODRX_DECLARE_PROPERTY(BgEntityColor)
  ODRX_DECLARE_PROPERTY(HostAppProgressMeter)
  ODRX_DECLARE_PROPERTY(MultithreadingEnable)
  ODRX_DECLARE_PROPERTY(ThreadsCount)
  ODRX_DECLARE_PROPERTY(UseDictionaryTypePath)
  ODRX_DECLARE_PROPERTY(StoreInveseAttributes)
  ODRX_DECLARE_PROPERTY(DeflateLevel)
  ODRX_DECLARE_PROPERTY(ReadChunkSize)
  ODRX_DECLARE_PROPERTY(WriteChunkSize)
  ODRX_DECLARE_PROPERTY(IsLogOn)
  ODRX_DECLARE_PROPERTY(InterruptCallback)

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeIfcFilerProperties);
    ODRX_GENERATE_PROPERTY(Palette)
    ODRX_GENERATE_PROPERTY(DCRect)
    ODRX_GENERATE_PROPERTY(ObjectNaming)
    ODRX_GENERATE_PROPERTY(StoreSourceObjects)
    ODRX_GENERATE_PROPERTY(ClearEmptyObjects)
    ODRX_GENERATE_PROPERTY(RearrangeObjects)
    ODRX_GENERATE_PROPERTY(AppendTransform)
    ODRX_GENERATE_PROPERTY(FeedbackForChooseCallback)
    ODRX_GENERATE_PROPERTY(DefaultEntityColor)
    ODRX_GENERATE_PROPERTY(Deviation)
    ODRX_GENERATE_PROPERTY(MinPerCircle)
    ODRX_GENERATE_PROPERTY(MaxPerCircle)
    ODRX_GENERATE_PROPERTY(NeedCDATree)
    ODRX_GENERATE_PROPERTY(ModelerType)
    ODRX_GENERATE_PROPERTY(NeedCollectPropertiesInCDA)
    ODRX_GENERATE_PROPERTY(UseCustomBgColor)
    ODRX_GENERATE_PROPERTY(BgEntityColor)
    ODRX_GENERATE_PROPERTY(HostAppProgressMeter)
    ODRX_GENERATE_PROPERTY(MultithreadingEnable)
    ODRX_GENERATE_PROPERTY(ThreadsCount)
    ODRX_GENERATE_PROPERTY(UseDictionaryTypePath)
    ODRX_GENERATE_PROPERTY(StoreInveseAttributes)
    ODRX_GENERATE_PROPERTY(DeflateLevel)
    ODRX_GENERATE_PROPERTY(ReadChunkSize)
    ODRX_GENERATE_PROPERTY(WriteChunkSize)
    ODRX_GENERATE_PROPERTY(IsLogOn)
    ODRX_GENERATE_PROPERTY(InterruptCallback)
  ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeIfcFilerProperties);

  ODRX_DEFINE_PROPERTY_METHODS(Palette, OdTvVisualizeIfcFilerProperties, getPalette, setPalette, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeIfcFilerProperties, getDCRect, setDCRect, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ObjectNaming, OdTvVisualizeIfcFilerProperties, getObjectNaming, setObjectNaming, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizeIfcFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ClearEmptyObjects, OdTvVisualizeIfcFilerProperties, getClearEmptyObjects, setClearEmptyObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(RearrangeObjects, OdTvVisualizeIfcFilerProperties, getRearrangeObjects, setRearrangeObjects, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeIfcFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(FeedbackForChooseCallback, OdTvVisualizeIfcFilerProperties, getFeedbackForChooseCallback, setFeedbackForChooseCallback, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(InterruptCallback, OdTvVisualizeIfcFilerProperties, getInterruptionCallback, setInterruptionCallback, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(DefaultEntityColor, OdTvVisualizeIfcFilerProperties, getDefaultColor, setDefaultColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(Deviation, OdTvVisualizeIfcFilerProperties, getDeviation, setDeviation, getDouble);
  ODRX_DEFINE_PROPERTY_METHODS(MinPerCircle, OdTvVisualizeIfcFilerProperties, getMinPerCircle, setMinPerCircle, getIntPtr)
  ODRX_DEFINE_PROPERTY_METHODS(MaxPerCircle, OdTvVisualizeIfcFilerProperties, getMaxPerCircle, setMaxPerCircle, getIntPtr)
  ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeIfcFilerProperties, getNeedCDATree, setNeedCDATree, getBool)
  ODRX_DEFINE_PROPERTY_METHODS(ModelerType, OdTvVisualizeIfcFilerProperties, getModelerType, setModelerType, getIntPtr)
  ODRX_DEFINE_PROPERTY_METHODS(NeedCollectPropertiesInCDA, OdTvVisualizeIfcFilerProperties, getNeedCollectPropertiesInCDA, setNeedCollectPropertiesInCDA, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(UseCustomBgColor, OdTvVisualizeIfcFilerProperties, getUseCustomBgColor, setUseCustomBgColor, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(BgEntityColor, OdTvVisualizeIfcFilerProperties, getBgColor, setBgColor, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(HostAppProgressMeter, OdTvVisualizeIfcFilerProperties, getHostAppProgressMeter, setHostAppProgressMeter, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(MultithreadingEnable, OdTvVisualizeIfcFilerProperties, getMultithreadingEnable, setMultithreadingEnable, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(ThreadsCount, OdTvVisualizeIfcFilerProperties, getThreadsCount, setThreadsCount, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(UseDictionaryTypePath, OdTvVisualizeIfcFilerProperties, getUseDictionaryTypePath, setUseDictionaryTypePath, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(StoreInveseAttributes, OdTvVisualizeIfcFilerProperties, getStoreInveseAttributes, setStoreInveseAttributes, getBool);
  ODRX_DEFINE_PROPERTY_METHODS(DeflateLevel, OdTvVisualizeIfcFilerProperties, getDeflateLevel, setDeflateLevel, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(ReadChunkSize, OdTvVisualizeIfcFilerProperties, getReadChunkSize, setReadChunkSize, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(WriteChunkSize, OdTvVisualizeIfcFilerProperties, getWriteChunkSize, setWriteChunkSize, getIntPtr);
  ODRX_DEFINE_PROPERTY_METHODS(IsLogOn, OdTvVisualizeIfcFilerProperties, getIsLogOn, setIsLogOn, getBool);
}

void OdTvVisualizeIfcFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizeIfcFilerProperties::setAppendTransform(OdIntPtr pTransform)
{
  const OdTvMatrix* pAppendTransform = (const OdTvMatrix*)(pTransform);

  if (pAppendTransform)
  {
    m_appendTransform = *pAppendTransform;
  }
  else
  {
    m_appendTransform = OdTvMatrix::kIdentity;
  }
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

void OdTvVisualizeIfcFilerProperties::setFeedbackForChooseCallback(OdIntPtr pCallback)
{
  m_pCallback = (OdTvFeedbackForChooseCallback)pCallback;
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getFeedbackForChooseCallback() const
{
  return (OdIntPtr)m_pCallback;
}

void OdTvVisualizeIfcFilerProperties::setInterruptionCallback(OdIntPtr pInterrupt)
{
  m_pInterruptCallback = (OdDAI::InterruptCallback)pInterrupt;
}

OdIntPtr OdTvVisualizeIfcFilerProperties::getInterruptionCallback() const
{
  return (OdIntPtr)m_pInterruptCallback;
}
//***************************************************************************//
// 'OdTvVisualizeIfcFiler' methods implementation
//***************************************************************************//

OdTvVisualizeIfcFiler::OdTvVisualizeIfcFiler()
  : m_properties(OdTvVisualizeIfcFilerProperties::createObject())
{
}

int OdTvVisualizeIfcFiler::getChoosedRepresentationContexts(OdIfcFilePtr pIfcFile, OdTvFilerFeedbackForChooseObject & filerFeedbackForChoose, bool& bCanceled, OdArray<OdIfcEntityType>& composedTypes) const
{
  m_selContexts.clear();

  OdIfcModelPtr pModel = pIfcFile->getModel();

  if (pModel.isNull())
  {
    ODA_ASSERT_ONCE(pModel.get());
    return -1;
  }

  if (!m_properties->has(OD_T("FeedbackForChooseCallback")) ||
    m_properties->getFeedbackForChooseCallback() == NULL)
    return odSelectRepresentationContextsByDefault(pModel);

  OdTvFilerFeedbackItemForChooseArray* pFilerFeedbackForChooseArray = filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr();
  if (pFilerFeedbackForChooseArray == NULL)
    return odSelectRepresentationContextsByDefault(pModel);

  OdDAIObjectIds selContexts;

  OdIfc::OdIfcEntityPtr pProject = pIfcFile->getProjectId().openObject();
  if (!pProject.isNull())
  {
    OdIfcEntityPtr pCtx;
    OdDAIObjectIds contexts;
    pProject->getAttr("representationcontexts") >> contexts;

    if (contexts.size() == 0)
      return odSelectRepresentationContextsByDefault(pModel);

    for (OdDAIObjectIds::iterator it = contexts.begin(), end = contexts.end(); it != end; ++it)
    {
      pCtx = it->openObject();
      if (pCtx->isKindOf(kIfcGeometricRepresentationContext))
      {
        OdAnsiString strContextType;
        if (pCtx->getAttr("contexttype") >> strContextType)
        {
          OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(strContextType,
            (strContextType.compare("Model") == 0 || strContextType.compare("Design") == 0 || strContextType.compare("Plan") == 0) ? true : false);
          pFilerFeedbackForChooseArray->append(filerFeedbackForChoose);
          selContexts.append(*it);

          OdDAIObjectIds hasSubContexts;
          if (pCtx->getAttr("hassubcontexts") >> hasSubContexts && hasSubContexts.size() > 0)
          {
            OdIfcEntityPtr pSubCtx;
            for (OdDAIObjectIds::iterator it = hasSubContexts.begin(), end = hasSubContexts.end(); it != end; ++it)
            {
              pSubCtx = it->openObject();
              if (!pSubCtx.isNull() && pSubCtx->isInstanceOf(kIfcGeometricRepresentationSubContext))
              {
                OdAnsiString strContextIdentifier;
                if (pSubCtx->getAttr("contextidentifier") >> strContextIdentifier)
                {
                  OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(strContextType + "\\" + strContextIdentifier, strContextIdentifier.compare("Body") == 0
                    || strContextIdentifier.compare("Annotation") == 0 ? true : false);
                  pFilerFeedbackForChooseArray->append(filerFeedbackForChoose);
                  selContexts.append(*it);
                }
              }
            }
          }
        }
      }
    }
  }
  else //strange but for safety
    return odSelectRepresentationContextsByDefault(pModel);

  unsigned int size = pFilerFeedbackForChooseArray->size();
  if (size > 0)
  {
    if (m_properties->has(OD_T("FeedbackForChooseCallback")) &&
      m_properties->getFeedbackForChooseCallback() != NULL && size > 1)
    {
      ((OdTvFeedbackForChooseCallback)m_properties->getFeedbackForChooseCallback())(filerFeedbackForChoose);
      if (filerFeedbackForChoose.getFilerFeedbackItemForChooseArrayPtr()->length() == 0)
      {
        bCanceled = true;
        return -1;
      }

      for (unsigned int i = 0; i < size; ++i)
      {
        if (pFilerFeedbackForChooseArray->at(i).m_bChosen)
          m_selContexts.append(selContexts[i]);
        if (pFilerFeedbackForChooseArray->at(i).m_strName.find(L"Annotation") >= 0 && pFilerFeedbackForChooseArray->at(i).m_bChosen)
        {
          if (!composedTypes.contains(kIfcAnnotation))
          {
            composedTypes.append(kIfcAnnotation);
          }
        }
      }
    }
    else
    {
      m_selContexts = selContexts;
    }
  }

  return m_selContexts.size();
}

OdTvDatabaseId OdTvVisualizeIfcFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdStreamBufPtr pStreamBuf = odrxSystemServices()->createFile(filePath);
  if (pStreamBuf.isNull())
  {
    if (rc)
      *rc = tvInvalidFilePath;
    return OdTvDatabaseId();
  }

  return loadFrom(pStreamBuf, pProfileRes, rc);
}

void OdTvVisualizeIfcFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, const OdTvModelId& modelId /*= OdTvModelId()*/) const
{
  OdIfcFilePtr pIfcFile = OdIfcFile::cast(pDatabase);
  if (pIfcFile.isNull())
  {
      ODA_ASSERT_ONCE("Wrong database class!");
      return;
  }

  OdIfcModelPtr pModel = pIfcFile->getModel();
  if (pModel.isNull())
  {
    ODA_ASSERT_ONCE("Can not create CDA tree for empty IfcFile!");
    return;
  }

  ::odrxDynamicLinker()->loadModule(L"RxProperties");

  //Create CDA tree
  OdTvCDATreePtr pTree = OdTvCDATree::createObject();
  if (m_properties->getNeedCollectPropertiesInCDA())
    pTree->createDatabaseHierarchyTree(pIfcFile.get(), true);
  else
  {
    std::set<OdString> props;
    props.insert(OdTvCDAPropNameForGrouping);
    pTree->createDatabaseHierarchyTree(pIfcFile.get(), &props);
  }

  //Add tree to the Tv database
  OdTvResult rc;
  OdTvCDATreeStorageId cdaTreeId = pTvDb->addCDATreeStorage(strTreeName, pTree, &rc);
  if (rc == tvAlreadyExistSameName)
  {
    OdUInt32 i = 1;
    while (rc != tvOk && i < MAX_CDATREENAME_GENERATION_ATTEMPTS)
    {
      OdString str;
      str.format(L"%s_%d", strTreeName.c_str(), i++); //not to fast but it is not a "bottle neck"
      cdaTreeId = pTvDb->addCDATreeStorage(str, pTree, &rc);
    }
  }

  //Add new CDA tree to the appropriate models
  OdTvModelId curModel = modelId;
  if (curModel.isNull())
  {
    OdTvModelsIteratorPtr modelsIterPtr = pTvDb->getModelsIterator();
    if (!modelsIterPtr->done())
    {
      curModel = modelsIterPtr->getModel();
      OdTvModelPtr pModel = curModel.openObject();
      if (!pModel.isNull())
        pModel->setCDATreeStorage(cdaTreeId);
    }
  }
  else
  {
    OdTvModelPtr pModel = curModel.openObject();
    pModel->setCDATreeStorage(cdaTreeId);
  }

  OdTvCDATreeNodePtr pTvNode = pTree->getDatabaseNode();
  if (!pTvNode.isNull())
  {
    const OdRxModelTreeBaseNodePtrArray nodes = pTvNode->getChildren();
    for (OdRxModelTreeBaseNodePtrArray::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
      OdTvCDATreeNodePtr pNode = *it;
      if (pNode.isNull())
        continue;
      pNode->setTvModelId(curModel);
    }
  }

  // formally it is not very fast function due to string comparison. But current implementation find ONLY first occurance of 
  // object with Storeys Class Name. That's why currently it is fast enough
  OdRxModelTreeBaseNodePtr pDbNode = pTree->getDatabaseNode();
  if (!pDbNode.isNull())
    processCDANode(pDbNode.get(), NULL);
}

bool OdTvVisualizeIfcFiler::processCDANode(OdRxModelTreeBaseNode* pNode, OdRxModelTreeBaseNode* pParentNode) const
{
  if (!pNode)
    return true;

  if (pParentNode)
  {
    OdTvCDATreeNodePtr pTvNode = dynamic_cast<const OdTvCDATreeNode*>(pNode);
    OdTvCDATreeNodePtr pTvParentNode = dynamic_cast<const OdTvCDATreeNode*>(pParentNode);
    if (!pTvNode.isNull() && !pTvParentNode.isNull())
    {
      OdString strClassName = getClassNameProperty(pTvNode->getProperties());
      if (!strClassName.isEmpty())
      {
        strClassName = strClassName.right(strClassName.getLength() - strClassName.find(L":") - 2);
        if ( !strClassName.isEmpty() )
        {
          bool bIsStorey = (strClassName == OdIfcStoreysClassName);
          bool bIsBridgePart = false;
          if (!bIsStorey)
            bIsBridgePart =(strClassName == OdIfcBridgePartClassName);
         
          if (bIsStorey || bIsBridgePart)
            pTvParentNode->setNeedGroup(false);

          if(bIsStorey)
            return false;
        }
      }
    }
  }

  const OdRxModelTreeBaseNodePtrArray& childs = pNode->getChildren();
  if (childs.isEmpty())
    return true;

  for (OdRxModelTreeBaseNodePtrArray::const_iterator it = childs.begin(); it != childs.end(); ++it)
  {
    if ( !processCDANode( const_cast<OdRxModelTreeBaseNode*>((*it).get()), pNode) )
      return false;
  }

  return true;
}

OdString OdTvVisualizeIfcFiler::getClassNameProperty(const OdArray<PropertyInfo>& nodeProperties) const
{
  if (nodeProperties.size() == 0)
    return OdString();

  for (OdUInt32 i = 0; i < nodeProperties.size(); i++)
  {
    if (nodeProperties[i].name == OdTvCDAPropNameForGrouping)
      return nodeProperties[i].value.getString();
  }
  return OdString();
}

int OdTvVisualizeIfcFiler::odSelectRepresentationContextsByDefault(OdIfcModelPtr pModel) const
{
  OdDAI::OdDAIObjectIdSet* setContext = pModel->getEntityExtent("IfcGeometricRepresentationContext");
  OdDAI::IteratorPtr nextIterator = setContext ? setContext->createIterator() : OdDAI::IteratorPtr();

  ODA_ASSERT(!nextIterator.isNull() && "pointer cannot be null");
  if (nextIterator.isNull())
  {
    return -1;
  }

  while (nextIterator->next())
  {
    OdDAIObjectId   entityId;
    if (!(nextIterator->getCurrentMember() >> entityId))
    {
      continue;
    }

    OdIfcEntityPtr pEnt = entityId.openObject();

    OdAnsiString strContextType;
    if (pEnt->getAttr("contexttype") >> strContextType)
    {
      m_selContexts.append(entityId);

      OdDAIObjectIds hasSubContexts;
      if (pEnt->getAttr("hassubcontexts") >> hasSubContexts)
      {
        unsigned int s = hasSubContexts.size();
        for (unsigned int i = 0; i < s; ++i)
        {
          OdIfcEntityPtr pSubCtx = hasSubContexts[i].openObject();
          if (!pSubCtx.isNull() && pSubCtx->isInstanceOf(kIfcGeometricRepresentationSubContext))
          {
            OdAnsiString strContextIdentifier;
            if (pSubCtx->getAttr("contextidentifier") >> strContextIdentifier)
            {
              if (strContextIdentifier.compare("Body") == 0)
                m_selContexts.append(hasSubContexts[i]);
            }
          }
        }
      }
    }
  }
  return m_selContexts.size();
}

OdTvGsViewId OdTvVisualizeIfcFiler::getActiveTvView(OdTvGsDeviceId& tvDeviceId, int iActViewViewInd) const
{
  OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject();
  if (!pTvDevice.isNull())
  {
    return pTvDevice->viewAt(iActViewViewInd);
  }
  return OdTvGsViewId();
}

OdTvGsDeviceId OdTvVisualizeIfcFiler::getActiveTvDevice(OdTvDatabaseId& tvDbId, int idDevice) const
{
  OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
  unsigned iDeviceInd = 0;
  if (!pDevicesIterator.isNull() && !pDevicesIterator->done())
  {
    if (iDeviceInd == idDevice)
      return pDevicesIterator->getDevice();

    pDevicesIterator->step();
  }

  return OdTvGsDeviceId();
}

OdTvModelId OdTvVisualizeIfcFiler::import(OdTvDatabaseId &tvDbId, OdStreamBuf* pBuffer, OdIfcFilePtr pIfcFile, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvOk;

  OdTvModelId idModel;

  OdString fileName;
  if (pBuffer)
    fileName = OdTvDatabaseUtils::getFileNameFromPath(pBuffer->fileName());
  else if (!pIfcFile.isNull())
    fileName = OdTvDatabaseUtils::getFileNameFromPath(pIfcFile->getFileName());

  if (fileName.isEmpty())
    fileName = OD_T("StreamBuffData");
  OdString modelName;

  OdTvGsDeviceId activeTvGsDeviceId;
  bool bIsAppend = false;
  if (tvDbId.isNull())
  {
    //
    // Create empty tv database.
    //
    OdTvFactoryId tvFactoryId = odTvGetFactory();
    tvDbId = tvFactoryId.createDatabase();
    OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);
  }
  else
  {
    bIsAppend = true;
    //
    // Check that we are in the real append mode
    //
    {
      OdTvDatabasePtr pTvDb = tvDbId.openObject();
      OdTvDevicesIteratorPtr devicesIteratorPtr = pTvDb->getDevicesIterator();
      while (!devicesIteratorPtr->done())
      {
        activeTvGsDeviceId = devicesIteratorPtr->getDevice();
        if (activeTvGsDeviceId.openObject()->getActive())
          break;
      }
    }

    modelName = OdTvDatabaseUtils::generateModelName(tvDbId, fileName);
  }

  //
  // Check if time profiling is needed
  //
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;
  double internalTiming = 0.;
  double externalTiming = 0.;
  double fileOpenTiming = 0.;
  double composeTiming = 0.;
  double contextSelectionTiming = 0.;
  double CDATiming = 0.;

  OdStaticRxObject<OdTvIfc2VisService> svcs;

  //
  // Start total timing
  //
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  ModelerType modelerType = (ModelerType)m_properties->getModelerType();

  bool bActivated = !pIfcFile.isNull();
  if(!bActivated)
  {
    odIfcInitialize(true, true, modelerType);

    if (m_properties->getIsLogOn())
    {
      OdDAI::SessionPtr pSession = oddaiSession();
      if (pSession.isNull())
        pSession = oddaiCreateSession();
      pSession->startEventRecording();
    }
  }
  else
  {
    odIfcInitModelerGeometry(modelerType);
  }

  //
  // Store visualize device module name
  //

  OdString moduleName;
  try
  {
    //
    // Local smart pointer pIfcDatabase, so we can release it and uninitialize IFC SDK if
    // pIfcFilePtr wasn't provided, and IFC file should be loaded into this module.
    //
    OdIfcFilePtr pIfcDatabase = pIfcFile;

    if (pIfcDatabase.isNull() && pBuffer)
    {
      //
      // No OdIfcFile provided, so file should be loaded and released in this module
      //
      OdDAI::Settings &setting = OdDAI::settings();
      setting.set_ThreadsCount(m_properties->getThreadsCount());
      setting.set_multiThreadingMode(m_properties->getMultithreadingEnable() ?
        OdDAI::MultithreadingMode::MultiThreadPool :
        OdDAI::MultithreadingMode::Single);
      setting.set_hdf5useDictionaryTypePath(m_properties->getUseDictionaryTypePath());
      setting.set_hdf5storeInverseAttributes(m_properties->getStoreInveseAttributes());
      setting.set_hdf5deflateLevel((OdDAI::hdf5DeflateLevel)m_properties->getDeflateLevel());
      setting.set_hdf5readChunkSize(m_properties->getReadChunkSize());
      setting.set_hdf5writeChunkSize(m_properties->getWriteChunkSize());

      OdDbHostAppProgressMeter* pMeter = (OdDbHostAppProgressMeter*)m_properties->getHostAppProgressMeter();
      if (pMeter)
        svcs.setProgressMeter(pMeter);

      timing.startMisc();
      pIfcDatabase = svcs.readFile(pBuffer);
      timing.endMisc();
      fileOpenTiming = timing.getMiscTime();
    }

    if (!pIfcDatabase.isNull())
    {
      //
      // Interrupt total timing for ask what representation contexts should be drawn
      //
      timing.startMisc();
      OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Geometric contexts for import"));
      bool bCanceled = false; 
      OdIfcModelContext context = pIfcDatabase->getContext();
      OdArray<OdIfcEntityType> composedTypes = context.getGeometryComposeTypes();
      int nSelContexts = getChoosedRepresentationContexts(pIfcDatabase, filerFeedbackForChooseObject, bCanceled, composedTypes);

      context.setGeometryComposeTypes(composedTypes);
      pIfcDatabase->setContext(context);
      timing.endMisc();

      if (bCanceled)
      {
        if (rc)
          *rc = tvFilerEmptyInternalDatabase;
        odTvGetFactory().removeDatabase(tvDbId);
        tvDbId.setNull();

        pIfcDatabase = nullptr;

        if(!bActivated)
        {
          // Uninitialize IFC modules
          odIfcUninitialize();
        }

        // Unload everything including Visualize device
        odrxDynamicLinker()->unloadUnreferenced();

        return idModel;
      }

      contextSelectionTiming = timing.getMiscTime();

      if (nSelContexts > 0)
      {
        //
        // Customize OdIfcModelContext
        //
        OdIfcModelContext ifcModelContext = pIfcDatabase->getContext();

        // Deviation params from properties
        OdIfcDeviationParams deviationParams(m_properties->getDeviation(), m_properties->getMinPerCircle(), m_properties->getMaxPerCircle());
        ifcModelContext.setDeviationParams(deviationParams);

        // Default color from properties
        ODCOLORREF* pDefColor = (ODCOLORREF*)m_properties->getDefaultColor();
        OdUInt8 r, g, b;
        r = ODGETRED(*pDefColor);
        g = ODGETGREEN(*pDefColor);
        b = ODGETBLUE(*pDefColor);
        OdCmEntityColor color(r, g, b);
        ifcModelContext.setDefaultEntityColor(color);

        //
        // Get units from IFC model
        //
        double addUnitCoefToMeters;
        OdTv::Units tvUnits = getUnits(pIfcDatabase, addUnitCoefToMeters);

        //
        // Geometry compose
        //
        timing.startMisc();
        pIfcDatabase->setContextSelection(m_selContexts);
        ifcModelContext.setInterruptCallback((OdDAI::InterruptCallback)m_properties->getInterruptionCallback());
        pIfcDatabase->setContext(ifcModelContext);
        pIfcDatabase->composeEntities();
        timing.endMisc();
        composeTiming = timing.getMiscTime();

        OdTvIfcPartialImportNotifier notifier;
        OdDbHostAppProgressMeter* pMeter = (OdDbHostAppProgressMeter*)m_properties->getHostAppProgressMeter();
        if (pMeter)
          pMeter->start(OD_T("Import starting..."));
        notifier.setProgressMeter(pMeter);
        OdDAI::OdDAIObjectIdSet* ids = pIfcDatabase->getModel()->getEntityExtent("IfcProduct");
        notifier.setEntitiesCount(ids->getMemberCount());

        //
        // Vectorizing
        //
        timing.startVectorizing();
        OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
        if (!pGs.isNull())
        {
          moduleName = pGs->moduleName();

          //
          // Create vectorizer device
          //
          OdGsDevicePtr pDevice = pGs->createDevice();

          OdGiContextForIfcDatabasePtr giGontextForIfcDatabase = OdGiContextForIfcDatabase::createObject();
          giGontextForIfcDatabase->setDatabase(pIfcDatabase);
          giGontextForIfcDatabase->enableGsModel(true);

          OdRxDictionaryPtr pProperties = pDevice->properties();
          if (pProperties.get())
          {
            if (pProperties->has(OD_T("DisplayViaGLES2")))
              pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
            if (pProperties->has(OD_T("AllowNonPersistentObjects")))
              pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
#if !defined(__APPLE__)
            if (pProperties->has(OD_T("EnableTiming")))
              pProperties->putAt(OD_T("EnableTiming"), OdRxVariantValue(bUseTimeProfiling));
#endif
            if (pProperties->has(OD_T("TvDatabaseID")))
              pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&tvDbId)));

            if (pProperties->has(OD_T("WriteUserData")))
              pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(true /*m_properties->getStoreSourceObjects()*/));
            if (pProperties->has(OD_T("GenerateEntityNames")))
              pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(true /*m_properties->getObjectNaming()*/));
            if (pProperties->has(OD_T("CompareUnnamedImages")))
              pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));
            if (pProperties->has(OD_T("CompareMaterialsForUniquiness")))
              pProperties->putAt(OD_T("CompareMaterialsForUniquiness"), OdRxVariantValue(false));

            if (!activeTvGsDeviceId.isNull())
            {
              if (pProperties->has(OD_T("IgnoreFlags")))
                pProperties->putAt(OD_T("IgnoreFlags"), OdRxVariantValue(OdUInt16(1)/*DeviceIgnoreFlags::kIgnoreViewInfoFlags*/));
              if (pProperties->has(OD_T("ModelName")))
                pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(modelName));
              if (pProperties->has(OD_T("NamePrefix")))
                pProperties->putAt(OD_T("NamePrefix"), OdRxVariantValue(modelName));
              if (pProperties->has(OD_T("TvDeviceDAM")))
                pProperties->putAt(OD_T("TvDeviceDAM"), OdRxVariantValue((OdIntPtr)(&activeTvGsDeviceId)));

              OdTvGsViewId viewId = activeTvGsDeviceId.openObject()->getActiveView();
              OdString name = viewId.openObject()->getName();
              if (pProperties->has(OD_T("TvViewDAM")))
                pProperties->putAt(OD_T("TvViewDAM"), OdRxVariantValue((OdIntPtr)(&viewId)));
            }

            if (bIsAppend)
            {
              if (pProperties->has(OD_T("DisableSetingExtents")))
                pProperties->putAt(OD_T("DisableSetingExtents"), OdRxVariantValue(true));
            }

            // put device notifier
            if (pProperties->has(OD_T("DeviceNotifier")))
            {
              pProperties->putAt(OD_T("DeviceNotifier"), OdRxVariantValue((OdIntPtr)(&notifier)));
            }
          }

          //
          // Setup the device and view
          //
          OdGsIfcLayoutHelperPtr pLayoutHelper = OdIfcGsManager::setupActiveLayoutViews(pDevice.get(), giGontextForIfcDatabase);
          pLayoutHelper->activeView()->setMode(OdGsView::kGouraudShaded);

          //
          // Set the palette
          //
          const ODCOLORREF* palette = (const ODCOLORREF*)m_properties->getPalette();
          bool bDefaultPalette = false;
          if (palette == 0)
          {
            bDefaultPalette = true;
            palette = odcmAcadPalette(ODRGB(255, 255, 255));
          }

          OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
          pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
          pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

          pDevice->setBackgroundColor(ODRGB(192, 192, 192));
          giGontextForIfcDatabase->setPaletteBackground(ODRGB(192, 192, 192));

          //
          // Call onsize
          //
          OdTvDCRect* pRect = (OdTvDCRect*)m_properties->getDCRect();
          if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
          {
            OdGsDCRect gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
            pDevice->onSize(gsRect);
          }

          //
          // Call draw to the Visualize database
          //
          pLayoutHelper->update();

          if (pProperties->has(OD_T("TvDatabaseID")))
            tvDbId = *(OdTvDatabaseId*)OdRxVariantValue(pProperties->getAt(OD_T("TvDatabaseID")).get())->getIntPtr();
          if (bUseTimeProfiling)
          {
#if !defined(__APPLE__)
            if (pProperties->has(OD_T("TvElapsedTime")))
            {
              internalTiming = OdRxVariantValue(pProperties->getAt(OD_T("TvElapsedTime")).get())->getDouble();
            }
#endif
          }

          //
          // Setup active view
          //
          timing.startMisc();

          if (tvDbId.isValid())
          {
            OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

            OdTvModelId tvCreatedModelId;
            if (activeTvGsDeviceId.isNull())
            {
              int iActViewViewInd = getActiveViewId(pLayoutHelper.get());
              if (iActViewViewInd >= 0)
              {
                //get current tv device
                OdTvGsDeviceId tvDeviceId = getActiveTvDevice(tvDbId, 0);
                OdTvGsViewId tvViewId = getActiveTvView(tvDeviceId, iActViewViewInd);
                if (!tvDeviceId.isNull() && !tvViewId.isNull())
                {
                  OdTvGsViewPtr pActiveTvView = tvViewId.openObject(OdTv::kForWrite);
                  pActiveTvView->setActive(true);

                  // mark other views sibling
                  OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject(OdTv::kForWrite);
                  if (!pTvDevice.isNull())
                  {
                    pTvDevice->setName(OD_T("IFCModel"));
                    for (int i = 0; i < pTvDevice->numViews(); i++)
                    {
                      if (i != iActViewViewInd)
                        continue;

                      OdTvGsViewId viewId = pTvDevice->viewAt(i);
                      if(viewId != tvViewId)
                        pActiveTvView->addSibling(viewId);

                      //set background
                      OdTvGsViewBackgroundId::BackgroundTypes bgType = m_properties->getUseCustomBgColor() ? OdTvGsViewBackgroundId::kSolid : OdTvGsViewBackgroundId::kGradient;
                      if (bgType == OdTvGsViewBackgroundId::kSolid)
                      {
                        ODCOLORREF* pBgColor = (ODCOLORREF*)m_properties->getBgColor();
                        pTvDevice->setBackgroundColor(*pBgColor);
                      }
                      else
                      {
                        OdTvGsViewBackgroundId bkgId = pTvDb->createBackground(OD_T("IFC2VISUALIZE"), bgType);
                        if (!bkgId.isNull())
                        {
                          if (bgType == OdTvGsViewBackgroundId::kGradient)
                          {
                            OdTvGsViewGradientBackgroundPtr pGradientBackground = bkgId.openAsGradientBackground(OdTv::kForWrite);

                            pGradientBackground->setColorTop(OdTvColorDef(33, 108, 170));
                            pGradientBackground->setColorMiddle(OdTvColorDef(109, 158, 200));
                            pGradientBackground->setColorBottom(OdTvColorDef(184, 208, 230));
                            pGradientBackground->setHeight(0.33);
                            pGradientBackground->setHorizon(0.5);
                          }
                          else
                          {
                            ODA_FAIL_M_ONCE("Ifc2Visualize background type not implemented");
                          }

                          pActiveTvView->setBackground(bkgId);
                        }
                      }
                      //set more lighting
                      pActiveTvView->setDefaultLightingIntensity(1.25);

                      // Zoom to extents
                      OdTvPoint minPt, maxPt;
                      pActiveTvView->zoomExtents(minPt, maxPt);
                    }
                  }
                }
              }

              //
              // Store filename to database user data
              //
              OdTvDatabaseUtils::writeFileNameToTvDatabase(tvDbId, fileName);

              //
              // Rename the model (here we suppose that database contain only one model)
              //
              OdTvModelsIteratorPtr pModelsIterator = pTvDb->getModelsIterator();
              if (!pModelsIterator.isNull() && !pModelsIterator->done())
              {
                OdTvModelId modelId = pModelsIterator->getModel();
                OdTvModelPtr pIvModel = modelId.openObject(OdTv::kForWrite);
                if (!pIvModel.isNull())
                {
                  tvCreatedModelId = modelId;
                  pIvModel->setName(fileName);
                  OdTvSelectabilityDef selectability;
                  selectability.setGeometries(true);
                  pIvModel->setSelectability(selectability, true);
                  //set units 
                  pIvModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);
                }
              }

              if (m_properties->getNeedCDATree())
              {
                OdPerfTimerBase* pCDATiming = OdPerfTimerBase::createTiming();
                pCDATiming->start();

                createCommonDataAccessTree(pTvDb, pIfcDatabase, fileName + OD_T(".ifc"));

                pCDATiming->stop();
                CDATiming += pCDATiming->countedSec();
                if (pProfileRes)
                  pProfileRes->setCDATreeCreationTime(OdInt64((CDATiming) * 1000.));
              }
            }
            else
            {
              idModel = pTvDb->findModel(modelName);

              OdTvModelPtr pTvModel = idModel.openObject(OdTv::kForWrite);
              if ( !pTvModel.isNull() )
              {
                tvCreatedModelId = idModel;
                OdTvSelectabilityDef selectability;
                selectability.setGeometries(true);
                pTvModel->setSelectability(selectability, true);
                //set units 
                pTvModel->setUnits(tvUnits, tvUnits == OdTv::kUserDefined ? addUnitCoefToMeters : 1.);

                // Apply transform if needed
                OdTvMatrix* pTransform = (OdTvMatrix*)m_properties->getAppendTransform();
                if (pTransform)
                  pTvModel->setModelingMatrix(*pTransform);
              }

              if (m_properties->getNeedCDATree())
              {
                OdPerfTimerBase* pCDATiming = OdPerfTimerBase::createTiming();
                pCDATiming->start();

                createCommonDataAccessTree(pTvDb, pIfcDatabase, fileName + OD_T(".ifc"), idModel);

                pCDATiming->stop();
                CDATiming += pCDATiming->countedSec();
                if (pProfileRes)
                  pProfileRes->setCDATreeCreationTime(OdInt64((CDATiming) * 1000.));
              }
            }

            //remove alone first level subentities and set shadow parameters
            OdTvModelPtr pTvModel = tvCreatedModelId.openObject(OdTv::kForWrite);
            if (!pTvModel.isNull())
            {
              OdTvEntitiesIteratorPtr pEntitiesIterator = pTvModel->getEntitiesIterator();
              while (!pEntitiesIterator->done())
              {
                OdTvEntityId entityId = pEntitiesIterator->getEntity();
                if (entityId.getType() == OdTvEntityId::kEntity)
                {
                  OdTvEntityPtr pTvEntity = entityId.openObject(OdTv::kForWrite);
                  if ( !pTvEntity.isNull() )
                  {
                    pTvEntity->removeSubEntities(OdTvEntity::kRemoveAlone);
                    pTvEntity->setShadowParameters(true, false);
                  }
                }
                pEntitiesIterator->step();
              }
            }
          }

          //remove empty data if need
          if (tvDbId.isValid() && m_properties->getClearEmptyObjects())
            OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

          timing.endMisc();
          externalTiming += timing.getMiscTime();
        }
        else
        {
          if (rc)
            *rc = tvMissingVisualizeDeviceModule;
        }

        timing.endVectorizing();
      }
      else
      {
      if (rc)
        *rc = tvFilerEmptyContext;
      }
      if (m_properties->getIsLogOn())
      {
        OdDAI::SessionPtr pSession = oddaiSession();
        if (pSession->isRecordingOn())
        {
          OdAnsiString log = getLog(pSession, pIfcDatabase);
          if (!log.isEmpty())
          {
            OdString logName = (pIfcDatabase.isNull() ? fileName : pIfcDatabase->getFileName()) + ".log";
            std::ofstream file((const char*)logName);
            file << log;
            file.close();
          }
        }
      }
    }
    else
    {
      //
      // File open error
      //
      if (rc)
        *rc = tvFilerEmptyInternalDatabase;
    }
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endVectorizing();
  }

  //unload vectorizing device
  if (!moduleName.isEmpty())
    odrxDynamicLinker()->unloadModule(moduleName);

  if (!bActivated)
  {
    //uninitialize IFC modules
    odIfcUninitialize();

    //
    // Here we will unload everything including Visualize device
    //
    odrxDynamicLinker()->unloadUnreferenced();
  }

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime((OdInt64)(fileOpenTiming * 1000.));
    pProfileRes->setMiscTime((OdInt64)(composeTiming * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime() - CDATiming) * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((internalTiming + externalTiming - CDATiming) * 1000.));
#endif
  }

  //set the selectability level
  if (!idModel.isNull())
  {
    OdTvModelPtr pTvModel = idModel.openObject(OdTv::kForWrite);
    OdTvSelectabilityDef selectability;
    selectability.setGeometries(true);
    pTvModel->setSelectability(selectability, true);
  }

  return idModel;
}

OdAnsiString OdTvVisualizeIfcFiler::getLog(OdDAI::SessionPtr& pSession, OdIfcFilePtr pFile) const
{
  if (pFile.isNull())
    return OdAnsiString();

  OdString fileName = pFile->getFileName();
  OdAnsiString logString;
  logString = "********************************************************************************\n";
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  logString += "Date:\t\t\t ";
  logString += std::asctime(&tm);
  logString += "File name:\t\t ";
  logString += fileName;
  logString += "\n";
  logString += "File schema:\t\t ";
  logString += pFile->getModel()->underlyingSchemaName();
  logString += "\n";
  OdIfcHostAppServices* pServices = pFile->getAppServices();
  logString += "Produced by:\t\t ";
  logString += "ODA IFC SDK ";
  logString += pServices->versionString();
  logString += "\n";
  logString += "User:\t\t\t ";
  logString += pServices->getAppUserName(Oda::kUserId);
  logString += "\n";
  logString += "********************************************************************************\n\n" ;
  logString += "--------------------------------------------------------------------------------\n";
  if (!pSession.isNull())
  {
    OdDAI::List<OdDAI::ErrorEventPtr>* errors = nullptr;
    if (pSession->getAttr("errors") >> errors)
    {
      if (errors->getMemberCount() > 0)
      {
        for (int i = 0; i < errors->getMemberCount(); ++i)
        {
          OdDAI::ErrorEventPtr pEvent;
          if (errors->getByIndex(i) >> pEvent)
          {
            OdAnsiString descr = pEvent->description();
            OdAnsiString func = pEvent->functionId();
            logString += descr;
            logString += "<";
            logString += func;
            logString += ">";
            logString += "\n";
          }
        }
      }
      else
        logString += "SUCCESS\n";
    }
  }
  logString += "--------------------------------------------------------------------------------\n";

  return logString;
}

OdTvDatabaseId OdTvVisualizeIfcFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvDatabaseId idDb;
  import(idDb, pBuffer, OdIfcFilePtr(), pProfileRes, rc);
  return idDb;
}

OdTvDatabaseId OdTvVisualizeIfcFiler::loadFrom(OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvDatabaseId tvDbId;
  import(tvDbId, NULL, pDatabase, pProfileRes, rc);
  return tvDbId;
}

OdTvDatabaseId OdTvVisualizeIfcFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeIfcFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdStreamBufPtr pStreamBuf = odrxSystemServices()->createFile(filePath);
  if (pStreamBuf.isNull())
  {
    if (rc)
      *rc = tvInvalidFilePath;
    return OdTvModelId();
  }

  return appendFrom(databaseId, pStreamBuf, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeIfcFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvDatabaseId idTvDb = (OdTvDatabaseId)databaseId;
  return import(idTvDb, pBuffer, OdIfcFilePtr(), pProfileRes, rc);
}

OdTvModelId OdTvVisualizeIfcFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  OdTvDatabaseId tvDbId = databaseId;
  return import(tvDbId, NULL, pDatabase, pProfileRes, rc);
}

int OdTvVisualizeIfcFiler::getActiveViewId(OdGsIfcLayoutHelper* pLayoutHelper) const
{
  if (!pLayoutHelper)
    return -1;

  OdGsViewPtr pActiveView = pLayoutHelper->activeView();

  int num = pLayoutHelper->numViews();
  int iActViewViewInd = 0;
  for (int i = 0; i < num; ++i)
  {
    OdGsView* pView = pLayoutHelper->viewAt(i);

    if (pView == pActiveView.get())
    {
      iActViewViewInd = i;
      break;
    }
  }

  return iActViewViewInd;
}

OdTvGsViewId OdTvVisualizeIfcFiler::getActiveTvView(OdTvDatabaseId& dbId, int iActViewViewInd) const
{
  OdTvDevicesIteratorPtr pDevicesIterator = dbId.openObject()->getDevicesIterator();
  if (!pDevicesIterator.isNull() && !pDevicesIterator->done())
  {
    OdTvGsDevicePtr pTvDevice = pDevicesIterator->getDevice().openObject();
    if (!pTvDevice.isNull())
    {
      return pTvDevice->viewAt(iActViewViewInd);
    }
  }

  return OdTvGsViewId();
}

//***************************************************************************//
// Native properties methods implementation
//***************************************************************************//

OdTvResult OdTvVisualizeIfcFiler::startActionsWithNativeProperties(const OdString& sFilePath, bool bPartial)
{

  if (!m_pIfcFile.isNull())
  {
    if (m_pIfcFile->getFileName() != sFilePath)
      m_pIfcFile.release();
    else
      return tvOk;
  }

  odIfcInitialize(true, true);

  OdTvResult rc = tvOk;
  if (m_pFilerPtr.isNull())
  {
    m_pFilerPtr = new OdTvVisualizeIfcFilerDbSource;
  }

  OdIfcFilePtr pIfcFile = m_pFilerPtr->readFile(sFilePath);
  if (pIfcFile.isNull())
    return tvFilerEmptyInternalDatabase;

  //OdTvVisualizeDwgFilerSourceFromFile dl;
  //if (!dl.initialize(sFilePath, NULL, &rc))

  {
    if (m_pRxPropertiesModule.isNull())
      m_pRxPropertiesModule = ::odrxDynamicLinker()->loadModule(L"RxProperties");

    try
    {
      m_pIfcFile = pIfcFile;
      m_pIfcModel = m_pIfcFile->getModel();
    }
    catch (...)
    {
      return tvFilerEmptyInternalDatabase;
    }
  }

  return rc;
}

bool OdTvVisualizeIfcFiler::isActionsWithNativePropertiesStarted(const OdString& sFilePath)
{
  if (!m_pIfcFile.isNull() && m_pIfcFile->getFileName() == sFilePath)
    return true;
  return false;
}

OdTvResult OdTvVisualizeIfcFiler::endActionsWithNativeProperties()
{
  m_pFilerPtr = NULL;

  m_pIfcModel.release();
  m_pIfcFile.release();
  m_pIfcCoreModule.release();
  m_pRxPropertiesModule.release();

  odIfcUninitialize();

  ::odrxDynamicLinker()->unloadModule(L"RxProperties");
  ::odrxDynamicLinker()->unloadUnreferenced();

  return tvOk;
}

OdRxMemberIteratorPtr OdTvVisualizeIfcFiler::getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc /*= NULL*/)
{
  if (m_pIfcModel.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxMemberIteratorPtr();
  }

  OdRxMemberIteratorPtr pIter;
  if (dbHandle == 0)
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(m_pIfcFile.get());
  else
  {
    OdDAIObjectId id = m_pIfcModel->getEntityInstance(dbHandle);
    if (id.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxMemberIteratorPtr();
    }

    OdDAI::ApplicationInstancePtr pInst = id.openObject();
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(pInst.get());
  }

  if (pIter.isNull())
  {
    if (rc)
      *rc = tvInternal;
    return OdRxMemberIteratorPtr();
  }

  if (rc)
    *rc = tvOk;
  return pIter;
}

OdRxValue OdTvVisualizeIfcFiler::getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly /*= NULL*/, OdTvResult* rc /*= NULL*/)
{
  if (pProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValue();
  }

  if (m_pIfcModel.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValue();
  }

  OdRxObjectPtr pInst;
  if (dbHandle == 0)
    pInst = m_pIfcFile;
  else
  {
    OdDAIObjectId id = m_pIfcModel->getEntityInstance(dbHandle);
    pInst = id.openObject();
  }

  if (pInst.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedObject;
    return OdRxValue();
  }

  OdRxValue value;
  OdResult odRes = pProperty->getValue(pInst, value);
  if (bReadOnly)
    *bReadOnly = pProperty->isReadOnly(pInst);

  if (odRes != eOk)
  {
    if (rc)
      *rc = tvInternal;

    return OdRxValue();
  }

  if (rc)
    *rc = tvOk;

  return value;
}

OdRxValueIteratorPtr OdTvVisualizeIfcFiler::getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly /*= NULL*/, OdTvResult* rc /*= NULL*/)
{
  return OdRxValueIteratorPtr();
}

OdTvResult OdTvVisualizeIfcFiler::setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value)
{
  return tvOk;
}

OdDbBaseDatabase* OdTvVisualizeIfcFiler::getNativeDatabase(OdTvResult* rc) const
{
  if (m_pIfcFile.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return NULL;
  }

  return (OdDbBaseDatabase*)m_pIfcFile.get();
}

//***************************************************************************//
// 'OdTvVisualizeIfcFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeIfcFilerModule);

void OdTvVisualizeIfcFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeIfcFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeIfcFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pDwgFiler = new OdTvVisualizeIfcFiler();

  return pDwgFiler;
}

//***************************************************************************//
// 'OdTvVisualizeIfcFilerDbSource' methods implementation
//***************************************************************************//

OdIfcFilePtr OdTvVisualizeIfcFilerDbSource::readFile(const OdString &file)
{
  return m_svcs.readFile(file);
}


void OdTvIfcPartialImportNotifier::entityVectorizationDone(const OdTvEntityId& entityId)
{
  if (entityId.isNull()) 
    return;
  m_nCurrentObject++;
  if (m_pMeter)
  {
    m_pMeter->meterProgress();
  }

  //TODO
  //Replace this code by the most appropriate.
  //Currently it marks all entities that contains "Proxy" in the name.
  OdTvEntityPtr pEnt = entityId.openObject(OdTv::kForWrite);
  OdString name = pEnt->getName();
  if (!name.isEmpty() && name.find(OD_T("Proxy")) > -1)
  {
    pEnt->setNeedCheckShellsTopology(true);
  }

}

void OdTvIfcPartialImportNotifier::insertVectorizationDone(const OdTvEntityId& insertId)
{
  m_nCurrentObject++;
  if (m_pMeter)
  {
    m_pMeter->meterProgress();
  }
}

OdTvIfcPartialImportNotifier::OdTvIfcPartialImportNotifier()
{
  m_nEntitiesEstimation = 0;
  m_nCurrentObject = 0;
  m_pMeter = NULL;
}

OdTvIfcPartialImportNotifier::~OdTvIfcPartialImportNotifier()
{
}

void OdTvIfcPartialImportNotifier::setEntitiesCount(OdUInt32 nCount)
{
  m_nEntitiesEstimation = nCount;
  if (m_pMeter)
    m_pMeter->setLimit(m_nEntitiesEstimation);
}



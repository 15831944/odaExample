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

#ifndef _WIN32_WCE
#include <sys/stat.h>
#endif

#include <fstream>
#include <cmath>

#include "OdaCommon.h"
#include "RxDynamicModule.h"

#define STL_USING_VECTOR
#define STL_USING_MAP
#define STL_USING_SET
#define STL_USING_STACK
#include "OdaSTL.h"
#include <tuple>

//Ge
#include "Ge/GeMatrix3d.h"

//TvGs
#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"

// Tv
#include "TvGeomCollector.h"
#include "TvFilerTimer.h"
#include "TvDatabaseUtils.h"
#include "TvInsert.h"
#include "TvDatabaseCleaner.h"

// Nw
#include "Nw2Visualize.h"
#include "NwDatabase.h"

#include "NwGeometryEllipticalShape.h"
#include "NwGeometryLineSet.h"
#include "NwGeometryMesh.h"
#include "NwGeometryPointSet.h"
#include "NwGeometryText.h"
#include "NwGeometryTube.h"
#include "NwGeometryExternal.h"
#include "NwVerticesData.h"

#include "NwTextStyle.h"

#include "NwComponent.h"
#include "NwFragment.h"
#include "NwPartition.h"

#include "NwBackgroundElement.h"
#include "NwModel.h"
#include "NwTexture.h"
#include "NwColor.h"
#include "NwUnitUtils.h"
#include "NwDistantLight.h"
#include "NwSpotLight.h"
#include "NwPointLight.h"
#include "NwVariant.h"
#include "NwSheetInfo.h"

#include "NwClipPlaneSet.h"
#include "NwClipPlane.h"
#include "NwViewpoint.h"
#include "ADSKRegistry.h"

#include "Grid/NwGridSystem.h"
#include "Grid/NwGridLine.h"
#include "Grid/NwGridLineSegment.h"
#include "Grid/NwGridLevel.h"
#include "Grid/NwGridSystemElement.h"
#include "Grid/NwGridTypes.h"

//#define DRAW_BOUNDING_BOXES // draw boundind boxes of model items
//#define NW_DRAW_MESH_AS_POINTSET

#define START_TV_NW_TIMER                            \
  if (pTvTimer)                                       \
    pTvTimer->start();

#define END_TV_NW_TIMER                              \
  if (pTvTimer)                                       \
  {                                                   \
    nTotalTvTime += pTvTimer->permanentSec();         \
    pTvTimer->stop();                                 \
  }

static OdString nwSanitizePath(const OdString& path);
static OdString nwExtractFileName(const OdString& path);
static OdString nwExtractFileDir(const OdString& path);
static OdResult findPathToFile(const OdString& sCurrentPath, OdString &sFileToFind);

#if defined(DRAW_BOUNDING_BOXES)
static const bool gDrawBoundingBoxes = true;
#else
static const bool gDrawBoundingBoxes = false;
#endif

class OdTvVisualizeNwFilerSourceFromDb : public OdTvVisualizeNwFilerDbSource
{
  OdDbBaseDatabase *mDatabase;

public:
  OdTvVisualizeNwFilerSourceFromDb(OdDbBaseDatabase *pDatabase) : mDatabase(pDatabase) {};
  virtual OdNwDatabasePtr   getDb() { return mDatabase; };
  virtual bool              odWasInitialized() const { return false; }
  virtual OdString          getFilename()
  {
    OdNwDatabasePtr pDb = mDatabase;
    if (!pDb.isNull())
    {
      OdString fileName = pDb->getFilename();
      if (!fileName.isEmpty())
        return fileName;
    }

    return OD_T("NoNameNwDatabase");
  }
};

class OdTvVisualizeNwFilerSourceFromBuffer : public OdTvVisualizeNwFilerDbSource
{
  OdStaticRxObject<OdTvNw2VisService> svcs;
  OdStreamBuf* mBuffer;

public:
  OdTvVisualizeNwFilerSourceFromBuffer(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes) : mBuffer(pBuffer), m_initTime(0) 
  { initialize(pBuffer, pProfileRes); };
  virtual OdNwDatabasePtr   getDb() 
  { 
    return svcs.readFile(mBuffer);
  };
  virtual bool              odWasInitialized() const { return false; }
  virtual OdString          getFilename()
  {
    if (mBuffer)
    {
      OdString fileName = mBuffer->fileName();
      if (!fileName.isEmpty())
        return fileName;
    }

    return OD_T("NoNameNwDatabase");
  }

protected:
  OdTvVisualizeNwFilerSourceFromBuffer() {};
  void initialize(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes)
  {
    if (!pBuffer)
      return;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    svcs.setTextureDirectoryPath(nwExtractFileDir(pBuffer->fileName()) + OD_T("/"), false);

    //load module
    ::odrxDynamicLinker()->loadModule(OdNwDbModuleName, false);

    timing.endTotal();
    m_initTime = timing.getTotalTime();
  };

protected:
  double         m_initTime;
};

class OdTvVisualizeNwFilerSourceFromFile : public OdTvVisualizeNwFilerDbSource
{
  OdStaticRxObject<OdTvNw2VisService> svcs;
  OdString mFilePath;


protected:
  double         m_initTime;

public:
  OdTvVisualizeNwFilerSourceFromFile(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes) { initialize(filePath, pProfileRes); };
  virtual OdNwDatabasePtr getDb() 
  {
    return svcs.readFile(mFilePath); 
  };
  virtual double          getInitTime() const { return m_initTime; }
  virtual OdString        getFilename()
  {
    //generate name for the stream file
    return OdTvDatabaseUtils::getFileNameFromPath(mFilePath);
  };

protected:
  OdTvVisualizeNwFilerSourceFromFile() {};
  void initialize(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes)
  {
    mFilePath = filePath;

    OdTvFilerTimer timing(needTimer(pProfileRes));
    timing.startTotal();

    svcs.setTextureDirectoryPath(nwExtractFileDir(mFilePath) + OD_T("/"), false);

    //load module
    ::odrxDynamicLinker()->loadModule(OdNwDbModuleName, false);

    timing.endTotal();
    m_initTime = timing.getTotalTime();
  };
};



/** \details
class for storing the information about the opened file
*/
class OdTvViewerDatabaseInfo : public OdTvFilerTimeProfiling
{
public:

  enum Type
  {
    kNew = 0,
    kBuiltIn = 1,
    kFromFile = 2,
    kImport = 4,
    kImportRevisions = 5,
  };

  OdTvViewerDatabaseInfo() : m_iLoadTime(0), m_iVectorizingTime(0), m_iTvCreationTime(0), m_iFirstUpdateTime(0), m_iCDACreationTime(0), m_type(kNew) {}
  ~OdTvViewerDatabaseInfo() {}

  // returns the time of file loading (in milliseconds)
  virtual OdInt64 getImportTime() const { return m_iLoadTime; }

  // returns the total vectorizing time (in milliseconds)
  virtual OdInt64 getVectorizingTime() const { return m_iVectorizingTime; }

  // returns the total tv calling time (in milliseconds)
  virtual OdInt64 getTvTime() const { return m_iTvCreationTime; }

  // returns  the total time of the CDA tree (and properties cache) creation
  virtual OdInt64 getCDATreeCreationTime() const { return m_iCDACreationTime; }

  // returns the misc tv calling time (in milliseconds)
  virtual OdInt64 getMiscTime() const { return m_iMiscTime; }

  // return the time of calling (in milliseconds)
  OdInt64 getFirstUpdateTime() const { return m_iFirstUpdateTime; }

  OdInt64 getTotalTime() const { return m_iLoadTime + m_iVectorizingTime + m_iTvCreationTime + m_iFirstUpdateTime; }

  // set the type
  Type getType() const { return m_type; }

  //set file path
  OdString getFilePath() const { return m_strPath; }

  // set the time of file loading (in milliseconds)
  virtual void setImportTime(OdInt64 time) { m_iLoadTime = time; }

  // set the time of vectorizing (in milliseconds)
  virtual void setVectorizingTime(OdInt64 time) { m_iVectorizingTime = time; }

  // set the time of calling (in milliseconds)
  virtual void setTvTime(OdInt64 time) { m_iTvCreationTime = time; }

  // set the time of calling (in milliseconds)
  void setFirstUpdateTime(OdInt64 time) { m_iFirstUpdateTime = time; }

  //Sets a new time occupied by the CDA tree (and properties cache) creation
  void setCDATreeCreationTime(OdInt64 time) { m_iCDACreationTime = time; }

  // set the misc time (in milliseconds)
  virtual void setMiscTime(OdInt64 time) { m_iMiscTime = time; }

  // set the type
  void setType(Type type) { m_type = type; }

  //set file path
  void setFilePath(const OdString& path) { m_strPath = path; }
private:

  OdInt64   m_iLoadTime;
  OdInt64   m_iVectorizingTime;
  OdInt64   m_iTvCreationTime;
  OdInt64   m_iCDACreationTime;
  OdInt64   m_iFirstUpdateTime;
  OdInt64   m_iMiscTime;
  Type      m_type;
  OdString  m_strPath;
};

//***************************************************************************//
// 'OdTvVisualizeNwFilerProperties' methods implementation
//***************************************************************************//
using namespace NW2Visualize;

OdTvVisualizeNwFilerProperties::OdTvVisualizeNwFilerProperties()
  : OdRxDispatchImpl<>()
  , m_importRect()
  , m_background(ODRGB(0, 0, 0))
  , m_defaultColor(ODRGB(191, 191, 191))
  , m_flags(0)
  , m_appendTransform(OdGeMatrix3d::kIdentity)
  , m_appendDevice()
  , m_pCallback()
{
}

OdRxDictionaryPtr OdTvVisualizeNwFilerProperties::createObject()
{
  return OdRxObjectImpl<OdTvVisualizeNwFilerProperties, OdRxDictionary>::createObject();
}

OdTvVisualizeNwFilerProperties::~OdTvVisualizeNwFilerProperties()
{
}

    ODRX_DECLARE_PROPERTY(DCRect)
    ODRX_DECLARE_PROPERTY(BackgroundColor)
    ODRX_DECLARE_PROPERTY(DefaultNwColor)
    ODRX_DECLARE_PROPERTY(AppendTransform)
    ODRX_DECLARE_PROPERTY(DeviceToAppend)
    ODRX_DECLARE_PROPERTY(NeedCDATree)
    ODRX_DECLARE_PROPERTY(NeedCollectPropertiesInCDA)
    ODRX_DECLARE_PROPERTY(ReplaceByNwc)
    ODRX_DECLARE_PROPERTY(StoreSourceObjects)
    ODRX_DECLARE_PROPERTY(ImportCuttingPlanes)
    ODRX_DECLARE_PROPERTY(FeedbackForChooseCallback)
    ODRX_DECLARE_PROPERTY(ImportGrid)

    ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(OdTvVisualizeNwFilerProperties);
    ODRX_GENERATE_PROPERTY(DCRect)
    ODRX_GENERATE_PROPERTY(BackgroundColor)
    ODRX_GENERATE_PROPERTY(DefaultNwColor)
    ODRX_GENERATE_PROPERTY(AppendTransform)
    ODRX_GENERATE_PROPERTY(DeviceToAppend)
    ODRX_GENERATE_PROPERTY(NeedCDATree)
    ODRX_GENERATE_PROPERTY(NeedCollectPropertiesInCDA)
    ODRX_GENERATE_PROPERTY(ReplaceByNwc)
    ODRX_GENERATE_PROPERTY(StoreSourceObjects)
    ODRX_GENERATE_PROPERTY(ImportCuttingPlanes)
    ODRX_GENERATE_PROPERTY(FeedbackForChooseCallback)
    ODRX_GENERATE_PROPERTY(ImportGrid)
    ODRX_END_DYNAMIC_PROPERTY_MAP(OdTvVisualizeNwFilerProperties);

    ODRX_DEFINE_PROPERTY_METHODS(DCRect, OdTvVisualizeNwFilerProperties, getDCRect, setDCRect, getIntPtr);
    ODRX_DEFINE_PROPERTY_METHODS(BackgroundColor, OdTvVisualizeNwFilerProperties, getBackgroundColor, setBackgroundColor, getIntPtr);
    ODRX_DEFINE_PROPERTY_METHODS(DefaultNwColor, OdTvVisualizeNwFilerProperties, getDefaultNwColor, setDefaultNwColor, getIntPtr);
    ODRX_DEFINE_PROPERTY_METHODS(AppendTransform, OdTvVisualizeNwFilerProperties, getAppendTransform, setAppendTransform, getIntPtr);
    ODRX_DEFINE_PROPERTY_METHODS(DeviceToAppend, OdTvVisualizeNwFilerProperties, getDeviceToAppend, setDeviceToAppend, getIntPtr);
    ODRX_DEFINE_PROPERTY_METHODS(NeedCDATree, OdTvVisualizeNwFilerProperties, getNeedCDATree, setNeedCDATree, getBool);
    ODRX_DEFINE_PROPERTY_METHODS(NeedCollectPropertiesInCDA, OdTvVisualizeNwFilerProperties, getNeedCollectPropertiesInCDA, setNeedCollectPropertiesInCDA, getBool);
    ODRX_DEFINE_PROPERTY_METHODS(ReplaceByNwc, OdTvVisualizeNwFilerProperties, getReplaceByNwc, setReplaceByNwc, getBool);
    ODRX_DEFINE_PROPERTY_METHODS(StoreSourceObjects, OdTvVisualizeNwFilerProperties, getStoreSourceObjects, setStoreSourceObjects, getBool);
    ODRX_DEFINE_PROPERTY_METHODS(ImportCuttingPlanes, OdTvVisualizeNwFilerProperties, getImportCuttingPlanes, setImportCuttingPlanes, getBool);
    ODRX_DEFINE_PROPERTY_METHODS(FeedbackForChooseCallback, OdTvVisualizeNwFilerProperties, getFeedbackForChooseCallback, setFeedbackForChooseCallback, getIntPtr);
    ODRX_DEFINE_PROPERTY_METHODS(ImportGrid, OdTvVisualizeNwFilerProperties, getImportGrid, setImportGrid, getBool);

void OdTvVisualizeNwFilerProperties::setDCRect(OdIntPtr rect)
{
  OdTvDCRect* pRect = (OdTvDCRect*)(rect);
  if (!pRect)
  {
    ODA_ASSERT(false);
  }

  m_importRect = *pRect;
}

OdIntPtr OdTvVisualizeNwFilerProperties::getDCRect() const
{
  return (OdIntPtr)(&m_importRect);
}

void OdTvVisualizeNwFilerProperties::setBackgroundColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_background = *pColor;
}

OdIntPtr OdTvVisualizeNwFilerProperties::getBackgroundColor() const
{
  return (OdIntPtr)(&m_background);
}

void OdTvVisualizeNwFilerProperties::setDefaultNwColor(OdIntPtr ptr)
{
  ODCOLORREF* pColor = (ODCOLORREF*)(ptr);
  if (!pColor)
  {
    ODA_ASSERT(false);
  }
  m_defaultColor = *pColor;
}

OdIntPtr OdTvVisualizeNwFilerProperties::getDefaultNwColor() const
{
  return (OdIntPtr)(&m_defaultColor);
}

void OdTvVisualizeNwFilerProperties::setDeviceToAppend(OdIntPtr pDevice)
{
  OdTvGsDeviceId* pId = (OdTvGsDeviceId*)pDevice;
  if (pId == NULL || pId->isNull())
  {
    m_appendDevice = OdTvGsDeviceId();
  }
  else
  {
    m_appendDevice = *pId;
  }
}

OdIntPtr OdTvVisualizeNwFilerProperties::getDeviceToAppend() const
{
  if (m_appendDevice.isNull()) return NULL;
    return (OdIntPtr)(&m_appendDevice);
}

void OdTvVisualizeNwFilerProperties::setAppendTransform(OdIntPtr pTransform)
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

OdIntPtr OdTvVisualizeNwFilerProperties::getAppendTransform() const
{
  return (OdIntPtr)(&m_appendTransform);
}

//////////////////////////////////////////////////
//NwTexture helper traits-methods
template <NwTextureValueType::Enum> struct NwTextureMapperHelper;
template<>
struct NwTextureMapperHelper<NwTextureValueType::diffuse_path>
{
  static constexpr inline NwTextureValueType::Enum getPath()             { return NwTextureValueType::diffuse_path; }
  static constexpr inline NwTextureValueType::Enum getRasterImage()      { return NwTextureValueType::diffuse_raster_image; }
  static constexpr inline NwTextureValueType::Enum getTransformMapping() { return NwTextureValueType::diffuse_transform_mapping; }
  static constexpr inline NwTextureValueType::Enum getScaleXValue()      { return NwTextureValueType::diffuse_scale_x_value; }
  static constexpr inline NwTextureValueType::Enum getScaleXUnit()       { return NwTextureValueType::diffuse_scale_x_unit; }
  static constexpr inline NwTextureValueType::Enum getScaleYValue()      { return NwTextureValueType::diffuse_scale_y_value; }
  static constexpr inline NwTextureValueType::Enum getScaleYUnit()       { return NwTextureValueType::diffuse_scale_y_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetXValue()     { return NwTextureValueType::diffuse_offset_x_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetXUnit()      { return NwTextureValueType::diffuse_offset_x_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetYValue()     { return NwTextureValueType::diffuse_offset_y_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetYUnit()      { return NwTextureValueType::diffuse_offset_y_unit; }
};
template<>
struct NwTextureMapperHelper<NwTextureValueType::opacity_path>
{
  static constexpr inline NwTextureValueType::Enum getPath()             { return NwTextureValueType::opacity_path; }
  static constexpr inline NwTextureValueType::Enum getRasterImage()      { return NwTextureValueType::opacity_raster_image; }
  static constexpr inline NwTextureValueType::Enum getTransformMapping() { return NwTextureValueType::opacity_transform_mapping; }
  static constexpr inline NwTextureValueType::Enum getScaleXValue()      { return NwTextureValueType::opacity_scale_x_value; }
  static constexpr inline NwTextureValueType::Enum getScaleXUnit()       { return NwTextureValueType::opacity_scale_x_unit; }
  static constexpr inline NwTextureValueType::Enum getScaleYValue()      { return NwTextureValueType::opacity_scale_y_value; }
  static constexpr inline NwTextureValueType::Enum getScaleYUnit()       { return NwTextureValueType::opacity_scale_y_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetXValue()     { return NwTextureValueType::opacity_offset_x_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetXUnit()      { return NwTextureValueType::opacity_offset_x_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetYValue()     { return NwTextureValueType::opacity_offset_y_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetYUnit()      { return NwTextureValueType::opacity_offset_y_unit; }
};
template<>
struct NwTextureMapperHelper<NwTextureValueType::bump_path>
{
  static constexpr inline NwTextureValueType::Enum getPath()             { return NwTextureValueType::bump_path; }
  static constexpr inline NwTextureValueType::Enum getRasterImage()      { return NwTextureValueType::bump_raster_image; }
  static constexpr inline NwTextureValueType::Enum getTransformMapping() { return NwTextureValueType::bump_transform_mapping; }
  static constexpr inline NwTextureValueType::Enum getScaleXValue()      { return NwTextureValueType::bump_scale_x_value; }
  static constexpr inline NwTextureValueType::Enum getScaleXUnit()       { return NwTextureValueType::bump_scale_x_unit; }
  static constexpr inline NwTextureValueType::Enum getScaleYValue()      { return NwTextureValueType::bump_scale_y_value; }
  static constexpr inline NwTextureValueType::Enum getScaleYUnit()       { return NwTextureValueType::bump_scale_y_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetXValue()     { return NwTextureValueType::bump_offset_x_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetXUnit()      { return NwTextureValueType::bump_offset_x_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetYValue()     { return NwTextureValueType::bump_offset_y_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetYUnit()      { return NwTextureValueType::bump_offset_y_unit; }
};
template<>
struct NwTextureMapperHelper<NwTextureValueType::pattern_path>
{
  static constexpr inline NwTextureValueType::Enum getPath()             { return NwTextureValueType::pattern_path; }
  static constexpr inline NwTextureValueType::Enum getRasterImage()      { return NwTextureValueType::pattern_raster_image; }
  static constexpr inline NwTextureValueType::Enum getTransformMapping() { return NwTextureValueType::pattern_transform_mapping; }
  static constexpr inline NwTextureValueType::Enum getScaleXValue()      { return NwTextureValueType::pattern_scale_x_value; }
  static constexpr inline NwTextureValueType::Enum getScaleXUnit()       { return NwTextureValueType::pattern_scale_x_unit; }
  static constexpr inline NwTextureValueType::Enum getScaleYValue()      { return NwTextureValueType::pattern_scale_y_value; }
  static constexpr inline NwTextureValueType::Enum getScaleYUnit()       { return NwTextureValueType::pattern_scale_y_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetXValue()     { return NwTextureValueType::pattern_offset_x_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetXUnit()      { return NwTextureValueType::pattern_offset_x_unit; }
  static constexpr inline NwTextureValueType::Enum getOffsetYValue()     { return NwTextureValueType::pattern_offset_y_value; }
  static constexpr inline NwTextureValueType::Enum getOffsetYUnit()      { return NwTextureValueType::pattern_offset_y_unit; }
};
/////////////////////////////////////////////////

class OdNwMaterialComparator : public OdTvMaterialComparator
{
public:
  OdNwMaterialComparator(const OdNwObjectId& nwRealisticMatId, const OdNwObjectId& nwShadedMatId, OdTvDatabase* pDb)
    : OdTvMaterialComparator()
    , m_nwRealisticMatId(nwRealisticMatId)
    , m_nwShadedMatId(nwShadedMatId)
    , m_pDb(pDb)
  {
    ODA_ASSERT(m_nwRealisticMatId);
    ODA_ASSERT(m_nwShadedMatId);
  }
  virtual bool isEqual(OdTvMaterialPtr pTvMaterial) const
  {
    OdTvMaterialColor tvMatColor;
    OdTvMaterialMap tvMatMap;
    OdResult result = eOk;
    OdNwMaterialPtr pNwRealMat = m_nwRealisticMatId.safeOpenObject();
    OdNwMaterialPtr pNwShadedMat = m_nwShadedMatId.safeOpenObject();

    //1.1) Cmp diffuse color
    pTvMaterial->getDiffuse( tvMatColor, tvMatMap);
    if( !isEqualColor(pNwRealMat->getDiffuse(), tvMatColor, result ) )
      return false;

    //1.2) Cmp second diffuse color
    tvMatColor = pTvMaterial->getSecondaryDiffuse();
    if( !isEqualColor(pNwShadedMat->getDiffuse(), tvMatColor, result ) )
      return false;

    //2) Texture
    OdNwTexturePtr pNwTxt;
    if(pNwRealMat->isA() == OdNwTexture::desc() )
      pNwTxt = pNwRealMat;
    if( !isEqualTexture<NwTextureValueType::diffuse_path>( pNwTxt, tvMatMap ) )
    {
      if( !isEqualTexture<NwTextureValueType::pattern_path>( pNwTxt, tvMatMap ) )
        return false;
    }

    //3.1) Opacity
    double nwOpacity = 0.;
    if(pNwRealMat->getTransparency() > 1 )
    {
      nwOpacity = 1.0 - pNwRealMat->getTransparency() / 100;
    }
    else
    {
      nwOpacity = 1.0 - pNwRealMat->getTransparency();
    }
    double tvOpacity = 0.;
    pTvMaterial->getOpacity( tvOpacity, tvMatMap );
    if( !OdEqual( tvOpacity, nwOpacity ) )
      return false;
    if( !isEqualTexture<NwTextureValueType::opacity_path>( pNwTxt, tvMatMap ) )
      return false;

    //3.2) second opacity
    if(pNwShadedMat->getTransparency() > 1 )
    {
      nwOpacity = 1.0 - pNwShadedMat->getTransparency() / 100;
    }
    else
    {
      nwOpacity = 1.0 - pNwShadedMat->getTransparency();
    }
    tvOpacity = pTvMaterial->getSecondaryOpacity();
    if( !OdEqual( tvOpacity, nwOpacity ) )
      return false;

    //4.1) Ambient
    tvMatColor = pTvMaterial->getAmbient();
    if( !isEqualColor(pNwRealMat->getAmbient(), tvMatColor, result ) )
      return false;

    //4.2) Second ambient
    tvMatColor = pTvMaterial->getSecondaryAmbient();
    if( !isEqualColor(pNwShadedMat->getAmbient(), tvMatColor, result ) )
      return false;

    //5.1) Specular
    double glossFactor = 0.;
    pTvMaterial->getSpecular( tvMatColor, glossFactor );
    if( !isEqualColor(pNwRealMat->getSpecular(), tvMatColor, result ) )
      return false;
    if( result == eOk )
    {
      if( pNwTxt.isNull() )
      {
        if( !OdEqual( glossFactor, pNwRealMat->getShininess() ) )
          return false;
      }
      else
      {
        if( !OdEqual( glossFactor, pNwTxt->getSpecularIntensity() ) )
          return false;
      }
    }

    //5.2) second specular
    tvMatColor = pTvMaterial->getSecondarySpecular();
    if( !isEqualColor(pNwShadedMat->getSpecular(), tvMatColor, result ) )
      return false;

    //6) Emission
    tvMatColor = pTvMaterial->getEmission();
    if( !isEqualColor(pNwRealMat->getEmissive(), tvMatColor, result ) )
      return false;

    //7) Bump
    pTvMaterial->getBump(tvMatMap);
    if (!isEqualTexture<NwTextureValueType::bump_path>(pNwTxt, tvMatMap))
      return false;

    //8) Tint
    if( !pNwTxt.isNull() )
    {
      OdNwColor tintClr;
      result = pNwTxt->getTint(tintClr);
      if (pTvMaterial->getTint(tvMatColor) != pNwTxt->IsUseTintColor())
        return false;
      if( !isEqualColor(tintClr, tvMatColor, result ) )
        return false;
    }

    return true;
  }
private:
  OdNwObjectId m_nwRealisticMatId;
  OdNwObjectId m_nwShadedMatId;
  mutable OdTvDatabase* m_pDb;

  inline bool isEqualColor( const OdNwColor& nwColor, const OdTvMaterialColor& tvColor, OdResult nwResult ) const
  {
    if( nwResult != eOk )
    {
      return tvColor.getMethod() == OdTvMaterialColor::kInherit; //not set
    }

    OdUInt8 nwR, nwG, nwB, tvR, tvG, tvB;
    nwR = ( nwColor.R() * 255.0 );
    nwG = ( nwColor.G() * 255.0 );
    nwB = ( nwColor.B() * 255.0 );

    tvColor.getColor().getColor( tvR, tvG, tvB );

    return nwR == tvR && nwG == tvG && nwB == tvB;
  }

  template <NwTextureValueType::Enum txtMapperType>
  inline bool isEqualTexture( OdNwTexturePtr pNwTxt, const OdTvMaterialMap& matMap ) const
  {
    if( !pNwTxt.isNull() )
    {
      NwModelUnits::Enum DbUnits = m_nwRealisticMatId.database()->getUnits();
      OdString sTextureFName = pNwTxt->getStringValue(NwTextureMapperHelper<txtMapperType>::getPath());
      OdGeMatrix3d uvMapTr;

      if( !sTextureFName.isEmpty() )
      {
        if(matMap.getSourceFileName() != sTextureFName )
          return false;
        OdResult res;
        uvMapTr = pNwTxt->getMatrixValue(NwTextureMapperHelper<txtMapperType>::getTransformMapping(), DbUnits, &res);
        if (res != eOk)
          return false;
      }

      if( sTextureFName.find( (OdChar)'.' ) > 0 )
      {
        OdTvTextureMapper txtMap;
        txtMap.setTransform(uvMapTr);
        if( txtMap != matMap.getMapper() )
          return false;

        OdString sFName = nwExtractFileName( sTextureFName );
        OdTvRasterImageId rasterImageId = m_pDb->findRasterImage( sFName );

        if(matMap.getSourceRasterImage() != rasterImageId )
          return false;
        if(matMap.getSourceFileName() != sTextureFName )
          return false;
      }
      else
      {
        //No texture
        if( !matMap.getSourceFileName().isEmpty() )
          return false;
        if( !matMap.getSourceRasterImage().isNull() )
          return false;
      }
    }
    else
    {
      //No texture
      if( !matMap.getSourceFileName().isEmpty() )
        return false;
      if( !matMap.getSourceRasterImage().isNull() )
        return false;
    }
    return true;
  }
};

void OdTvVisualizeNwFilerProperties::setFeedbackForChooseCallback(OdIntPtr pCallback)
{
  m_pCallback = (OdTvFeedbackForChooseCallback)pCallback;
}

OdIntPtr OdTvVisualizeNwFilerProperties::getFeedbackForChooseCallback() const
{
  return (OdIntPtr)m_pCallback;
}

//***************************************************************************//
// 'OdTvVisualizeNwFiler' methods implementation
//***************************************************************************//

template <NwTextureValueType::Enum txtMapperType>
typename std::enable_if<txtMapperType == NwTextureValueType::pattern_path ||
               txtMapperType == NwTextureValueType::diffuse_path ||
               txtMapperType == NwTextureValueType::bump_path ||
               txtMapperType == NwTextureValueType::opacity_path>::type initTextureMapper(OdNwTexturePtr pNwTxt, OdTvDatabasePtr pTvDb, OdTvMaterialMap& materialMap, OdTvResult& rc)
{
  //add check of textureType

  OdString sTextureFName = pNwTxt->getStringValue(NwTextureMapperHelper<txtMapperType>::getPath());
  OdTvTextureMapper txtMap;
  NwModelUnits::Enum DbUnits = pNwTxt->objectId().database()->getUnits();
  if (!sTextureFName.isEmpty())
  {
    txtMap.setTransform(pNwTxt->getMatrixValue(NwTextureMapperHelper<txtMapperType>::getTransformMapping(), DbUnits));

    if (sTextureFName.find((OdChar)'.') > 0)
    {
      OdString sFName = nwExtractFileName(sTextureFName);
      OdTvRasterImageId rasterImageId = pTvDb->findRasterImage(sFName, &rc);
      if (rc != eOk)
      {
        OdGiRasterImagePtr pRI = pNwTxt->getRasterImageValue(NwTextureMapperHelper<txtMapperType>::getRasterImage());
    
        if (!pRI.isNull())
        {
          OdBinaryData bufData;
          bufData.resize(pRI->pixelHeight() * pRI->scanLineSize());
          pRI->scanLines(const_cast<OdUInt8*>(bufData.asArrayPtr()), 0, pRI->pixelHeight());
    
          if (pRI->numColors() == 0)
          {
            OdTvRasterImage::Format riFrmt;
            if (pRI->pixelFormat().isRGBA())
              riFrmt = OdTvRasterImage::kRGBA;
            else if (pRI->pixelFormat().isRGB())
              riFrmt = OdTvRasterImage::kRGB;
            else if (pRI->pixelFormat().isBGRA())
              riFrmt = OdTvRasterImage::kBGRA;
            else if (pRI->pixelFormat().is16bitBGR())
              riFrmt = OdTvRasterImage::kBGR_16;
            else if (pRI->pixelFormat().isBGR())
              riFrmt = OdTvRasterImage::kBGR;
    
            rasterImageId = pTvDb->createRasterImage(sFName, riFrmt, pRI->pixelWidth(), pRI->pixelHeight(), const_cast<OdUInt8*>(bufData.asArrayPtr()), pRI->scanLinesAlignment(), &rc);
          }
          else if (pRI->numColors() == 2 && pRI->colorDepth() == 1)
          {
            ODCOLORREF color1 = pRI->color(0);
            ODCOLORREF color2 = pRI->color(1);
            bool bInverted = false;
            if (30 * ODGETRED(color1) + 59 * ODGETGREEN(color1) + 11 * ODGETBLUE(color1) >
                30 * ODGETRED(color2) + 59 * ODGETGREEN(color2) + 11 * ODGETBLUE(color2))
              bInverted = false;
            else
              bInverted = true;
    
            rasterImageId = pTvDb->createRasterImage(sFName, pRI->pixelWidth(), pRI->pixelHeight(), const_cast<OdUInt8*>(bufData.asArrayPtr()), bInverted, pRI->scanLinesAlignment(), &rc);
          }
          else
          {
            OdTvRasterImage::Format riFrmt;
            if (pRI->pixelFormat().isRGBA())
              riFrmt = OdTvRasterImage::kRGBA;
            else if (pRI->pixelFormat().isRGB())
              riFrmt = OdTvRasterImage::kRGB;
            else if (pRI->pixelFormat().isBGRA())
              riFrmt = OdTvRasterImage::kBGRA;
            else if (pRI->pixelFormat().is16bitBGR())
              riFrmt = OdTvRasterImage::kBGR_16;
            else if (pRI->pixelFormat().isBGR())
              riFrmt = OdTvRasterImage::kBGR;
    
            OdBinaryData bufPaletteData;
            bufPaletteData.resize(pRI->paletteDataSize());
            pRI->paletteData(const_cast<OdUInt8*>(bufPaletteData.asArrayPtr()));
    
            OdTvRasterImage::BitPerIndex bpi = OdTvRasterImage::kEightBits;
            if (pRI->colorDepth() != 8)
              bpi = OdTvRasterImage::kFourBits;
    
            rasterImageId = pTvDb->createRasterImage(sFName, riFrmt, pRI->paletteDataSize(), const_cast<OdUInt8*>(bufPaletteData.asArrayPtr()), bpi, pRI->pixelWidth(), pRI->pixelHeight(), const_cast<OdUInt8*>(bufData.asArrayPtr()), pRI->scanLinesAlignment(), &rc);
          }
        }
      }
    
      if (!rasterImageId.isNull())
        materialMap.setSourceRasterImage(rasterImageId);
      else
        materialMap.setSourceFileName(sTextureFName);
    }

  }
  materialMap.setMapper(txtMap);
}

OdTvMaterialId OdTvVisualizeNwFiler::importMaterial(const OdTvDatabaseId& tvDbId, const OdNwObjectId& nwRealisticMtlId, const OdNwObjectId& nwShadedMtlId) const
{
  if (!nwRealisticMtlId || !nwShadedMtlId)
    return OdTvMaterialId();
  OdTvResult rc;
  OdTvMaterialId tvMaterialId;
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  OdNwMaterialPtr pNwRealisticMtl = nwRealisticMtlId.safeOpenObject();
  OdNwMaterialPtr pNwShadedMtl = nwShadedMtlId.safeOpenObject();

  OdString mtlNameGen = pNwRealisticMtl->getName() + OdString().format(OD_T("_Generated_%u"), static_cast<OdUInt64>(nwShadedMtlId.getHandle()));

  OdNwMaterialComparator comp(nwRealisticMtlId, nwShadedMtlId, pTvDb.operator->());

  tvMaterialId = pTvDb->findMaterial(&comp, mtlNameGen, &rc);

  if (tvMaterialId.isNull())
    tvMaterialId = pTvDb->createMaterial(mtlNameGen, &rc);

  if (tvMaterialId.isNull())
    return tvMaterialId;

  OdTvMaterialPtr pTvMaterial = tvMaterialId.openObject(OdTv::kForWrite);

  OdNwTexturePtr pNwTxt;
  if (pNwRealisticMtl->isA() == OdNwTexture::desc())
  {
    pNwTxt = pNwRealisticMtl;
    pTvMaterial->setSupportNonTextureMode(true);
  }

  auto getTvColorFromNwColor = [](const OdNwColor& nwClr)
  {
    return OdTvMaterialColor(OdTvColorDef(nwClr.R() * 255.0, nwClr.G() * 255.0, nwClr.B() * 255.0));
  };

  //diffuse
  {
    OdTvMaterialMap tvMaterialMap;
    if (!pNwTxt.isNull())
    {
      if (!pNwTxt->getStringValue(NwTextureValueType::diffuse_path).isEmpty())
        initTextureMapper<NwTextureValueType::diffuse_path>(pNwTxt, pTvDb, tvMaterialMap, rc);
      else if (!pNwTxt->getStringValue(NwTextureValueType::pattern_path).isEmpty())
        initTextureMapper<NwTextureValueType::pattern_path>(pNwTxt, pTvDb, tvMaterialMap, rc);
    }

    //VAS: in texture's object there is double type parameter OdNwTexture::m_DiffuseIntensity which may need to use somehow

    pTvMaterial->setDiffuse(getTvColorFromNwColor(pNwRealisticMtl->getDiffuse()), tvMaterialMap);
  }
  pTvMaterial->setSecondaryDiffuse(getTvColorFromNwColor(pNwShadedMtl->getDiffuse()));

  //opacity
  {
    OdTvMaterialMap tvMaterialMap;
    if (!pNwTxt.isNull() && !pNwTxt->getStringValue(NwTextureValueType::opacity_path).isEmpty())
    {
      initTextureMapper<NwTextureValueType::opacity_path>(pNwTxt, pTvDb, tvMaterialMap, rc);
    }

    if (pNwRealisticMtl->getTransparency() > 1)
      pTvMaterial->setOpacity(1 - pNwRealisticMtl->getTransparency()/100, &tvMaterialMap);
    else
      pTvMaterial->setOpacity(1 - pNwRealisticMtl->getTransparency(), &tvMaterialMap);

    if (pNwShadedMtl->getTransparency() > 1)
      pTvMaterial->setSecondaryOpacity(1 - pNwShadedMtl->getTransparency()/100);
    else
      pTvMaterial->setSecondaryOpacity(1 - pNwShadedMtl->getTransparency());
  }

  //ambient
  //VAS: in texture's object there is double type parameter OdNwTexture::m_ReflectIntensity which may need to use somehow
  //most likely ReflectIntensity is ambient intensity
  pTvMaterial->setAmbient(getTvColorFromNwColor(pNwRealisticMtl->getAmbient()));
  pTvMaterial->setSecondaryAmbient(getTvColorFromNwColor(pNwShadedMtl->getAmbient()));

  //specular
  {
    // NB: check if shininness is gloss factor
    pTvMaterial->setSpecular(getTvColorFromNwColor(pNwRealisticMtl->getSpecular()), pNwRealisticMtl->getShininess());
    if (!pNwTxt.isNull())
      pTvMaterial->setSpecularGloss(pNwTxt->getSpecularIntensity());
  }
  pTvMaterial->setSecondarySpecular(getTvColorFromNwColor(pNwShadedMtl->getSpecular()));

  pTvMaterial->setEmission(getTvColorFromNwColor(pNwRealisticMtl->getEmissive()));

  //bump
  {
    OdTvMaterialMap tvMaterialMap;
    if (!pNwTxt.isNull() && !pNwTxt->getStringValue(NwTextureValueType::bump_path).isEmpty())
    {
      initTextureMapper<NwTextureValueType::bump_path>(pNwTxt, pTvDb, tvMaterialMap, rc);
      tvMaterialMap.setBlendFactor(pNwTxt->getBumpAmount());
    }
    pTvMaterial->setBump(tvMaterialMap);
  }

  //tint
  OdNwColor tempNwColor;
  if (!pNwTxt.isNull() && pNwTxt->getTint(tempNwColor) == eOk)
    pTvMaterial->setTint(getTvColorFromNwColor(tempNwColor), pNwTxt->IsUseTintColor());

  return tvMaterialId;
}

OdTvVisualizeNwFiler::OdTvVisualizeNwFiler() : m_properties(OdTvVisualizeNwFilerProperties::createObject())
{

}

OdTvDatabaseId OdTvVisualizeNwFiler::loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  LoadNwOptions opt(filePath);
  return importFile(opt, pProfileRes, rc);
}

static bool isFileReadable(const OdString& pcFilename)
{
  int mode = Oda::kFileRead;
#if defined(_MSC_VER) && !defined(_WIN32_WCE)
  // SetErrorMode() function is used to avoid the message box
  // if there is no floppy disk in the floppy drive (CR 2122).
  int oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
  bool res = (_waccess(pcFilename,
    (GETBIT(mode, Oda::kFileRead) ? 0x04 : 0x00) |
    (GETBIT(mode, Oda::kFileWrite) ? 0x02 : 0x00)) == 0);
  SetErrorMode(oldErrorMode);
  if (res)
  {
    struct _stat st;
    _wstat(pcFilename, &st);
    if (st.st_mode & _S_IFDIR)
      return false;
  }
  return res;
#elif defined(sgi)
  // Use this version, since try/catch below results in memory leaks on sgi (OdError destructor doesn't get called).
  OdString  sMode = (mode == Oda::kFileRead) ? OD_T("rb") : OD_T("wb");
  FILE* fp = fopen((const char*)pcFilename, (const char*)sMode);
  if (fp)
  {
    fclose(fp);
    return true;
  }
  return false;
#elif defined(__linux__)
  bool res = false;
  if (GETBIT(mode, Oda::kFileRead) != 0x00) {
    std::ifstream ifile(OdAnsiString(pcFilename).c_str());
    res = (bool)ifile;
  }
  if (res && (GETBIT(mode, Oda::kFileWrite) != 0x00)) {
    std::ofstream ofile(OdAnsiString(pcFilename).c_str());
    res = (bool)ofile;
  }
  return res;
#elif defined(__APPLE__)
  struct stat buf;
  return (stat(OdAnsiString(pcFilename).c_str(), &buf) == 0);
#else
  ODA_ASSERT(false);
#endif
}

static OdString nwSanitizePath(const OdString& path)
{
  OdString sToFindSanitized = path;
  sToFindSanitized.replace('\\', '/');    // win to lin
  return sToFindSanitized;
}

static OdString nwExtractFileName(const OdString& path)
{
  // get filename with extension
  OdString sToFindSanitized = nwSanitizePath(path);
  const int lastDelimiter = sToFindSanitized.reverseFind('/');

  if (-1 == lastDelimiter)
    return path;                   // no delimiter

  return sToFindSanitized.mid(lastDelimiter + 1);
}

static OdString nwExtractFileDir(const OdString& path)
{
  // get filename with extension
  OdString sToFindSanitized = nwSanitizePath(path);
  const int lastDelimiter = sToFindSanitized.reverseFind('/');

  if (-1 == lastDelimiter)
    return L"";                   // no folder

  return sToFindSanitized.left(lastDelimiter);
}

static OdResult findPathToFile(const OdString& sCurrentPath, OdString &sFileToFind)
{
  // if original file exists return it
  if (isFileReadable(sFileToFind))
    return eOk;

  // get filename with extension
  OdString sToFindSanitized = nwSanitizePath(sFileToFind);
  const int lastDelimiter = sToFindSanitized.reverseFind('/');


  if (-1 == lastDelimiter)
    return eFileAccessErr;                   // no delimiter - no file

  // At this moment there is no file in current folder
  // gte name ie. test.txt
  OdString sStrippedName = nwExtractFileName(sToFindSanitized);

  if (sStrippedName.isEmpty())
    return eFileAccessErr;

  OdString sFileInCurrentPath = (sCurrentPath);
  if (sFileInCurrentPath.isEmpty()
    || ('/' != sFileInCurrentPath[sFileInCurrentPath.getLength() - 1]))
  {
    sFileInCurrentPath += "/";
  }

  sFileInCurrentPath += sStrippedName;
  const bool bFound = isFileReadable(sFileInCurrentPath);
  if (bFound)
  {
    sFileToFind = sFileInCurrentPath;
  }
  return bFound ? eOk : eFileAccessErr;
}

static OdString convertFormatToNwc(const OdString& pathToFile)
{
  OdString res;

  if (pathToFile.find('.') > 0)
    res = pathToFile.left(pathToFile.reverseFind('.')) + OD_T(".nwc");

  return res;
}

void OdTvVisualizeNwFiler::loadNwf(OdTvDatabaseId tvDbId, OdNwDatabasePtr pNwDb, OdTvFilerTimer &timing, OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  //
  // prepare Visualize timing object
  //
  OdPerfTimerBase* pTvTimer = 0;
  double nTotalTvTime = 0.;
  bool bUseTimeProfiling = (NULL != pProfileRes);
  if (bUseTimeProfiling)
    pTvTimer = OdPerfTimerBase::createTiming();

  START_TV_NW_TIMER

  OdTvGsViewPtr pTvView;
  if (auto nwViewId = pNwDb->getCurrentViewId())
  {
    OdTvGsViewBackgroundId bkgId = setupBackground(pNwDb->getBackgroundElementId(), pTvDb);
    OdString deviceName;
    if (auto nwCurrSheetId = pNwDb->getActiveSheetId())
    {
      OdNwSheetInfoPtr pNwCurrSheet = nwCurrSheetId.safeOpenObject();
      deviceName = pNwCurrSheet->getDisplayName();
    }
    if (deviceName.isEmpty())
      deviceName = OD_T("Window_NW");
    OdTvGsDeviceId tvDeviceId = pTvDb->createDevice(deviceName); // sheet name
    // apply background color
    ODCOLORREF* pColor = (ODCOLORREF*)(m_properties->getBackgroundColor());
    tvDeviceId.openObject(OdTv::kForWrite)->setBackgroundColor(*pColor);

    OdTvGsViewId tvViewId = setupCurrentView(nwViewId, tvDeviceId, OdTvModelId(), bkgId);
    pTvView = tvViewId.openObject(OdTv::kForWrite);
    pTvView->enableDefaultLighting(false);
  }

  //2. Prepare profiling structure
  OdTvViewerDatabaseInfo databaseInfo;
  databaseInfo.setFilePath(pNwDb->getFilename().c_str());
  databaseInfo.setType(OdTvViewerDatabaseInfo::kImport);

  END_TV_NW_TIMER

  OdNwObjectIdArray aModels;
  pNwDb->getModels(aModels);

  OdString strBaseFileDir = nwExtractFileDir(pNwDb->getFilename());
  OdTvModelId lastTvModelId;
  NwModelUnits::Enum databaseUnits = pNwDb->getUnits();
  
  //VAS: since tv database hasn't api method like setUnits and set units for tv db from first tv model - we make such 'hack' for setting units from nwf file for correct work with viewpoint data(wich in wcs with units from nwf)
  //for example there can be case when units for model from nwf will be not eqaul to model from _2Visualize, such as in .ifc files(maybe this is bug of naviswork)
  auto tvTempModelForUnits = pTvDb->createModel(OD_T("tempForUnits"));
  tvTempModelForUnits.openObject()->setUnits([](NwModelUnits::Enum nwUnits)->OdTv::Units
  {
    switch (nwUnits)
    {
    case NwModelUnits::UNITS_METERS:
      return OdTv::kMeters;
      break;
    case NwModelUnits::UNITS_CENTIMETERS:
      return OdTv::kCentimeters;
      break;
    case NwModelUnits::UNITS_MILLIMETERS:
      return OdTv::kMillimeters;
      break;
    case NwModelUnits::UNITS_FEET:
      return OdTv::kFeet;
      break;
    case NwModelUnits::UNITS_INCHES:
      return OdTv::kInches;
      break;
    case NwModelUnits::UNITS_YARDS:
      return OdTv::kYards;
      break;
    case NwModelUnits::UNITS_KILOMETERS:
      return OdTv::kKilometers;
      break;
    case NwModelUnits::UNITS_MILES:
      return OdTv::kMiles;
      break;
    case NwModelUnits::UNITS_MICROMETERS:
      return OdTv::kMicrometers;
      break;
    case NwModelUnits::UNITS_MILS:
      return OdTv::kMils;
      break;
    case NwModelUnits::UNITS_MICROINCHES:
      return OdTv::kMicroInches;
      break;
    default:
      return OdTv::kUserDefined;
      break;
    }
  }(databaseUnits));

  OdInt64 iReadTime = 0.;
  OdInt64 iCdaTime = 0.;
  OdInt64 iTvTime = 0.;

  for (OdNwObjectIdArray::const_iterator it = aModels.begin();
    it != aModels.end(); ++it)
  {
    if (!*it)
      continue;
    OdNwModelPtr pModel = it->safeOpenObject();
    if (!pModel.isNull())
    {
      OdGeMatrix3d trf = pModel->getTransform();
      if (pModel->getUnits() != databaseUnits)
        OdNwUnitUtils::convertMatrix3d(trf, databaseUnits, pModel->getUnits());
      trf(3, 3) = 1.0;  //  element must be 1!
      OdTvDCRect rectDC = *(OdTvDCRect*) m_properties->getDCRect();
      OdString strSubFilePath = pModel->getPath();
      NwModelType::Enum modelType = pModel->getType();
      bool bFileIsFound = (eOk == findPathToFile(strBaseFileDir, strSubFilePath));
      bool bIsChangeToNwc = m_properties->getReplaceByNwc();
      if (modelType != NwModelType::nw_model && (bIsChangeToNwc || !bFileIsFound))
      {
        strSubFilePath = convertFormatToNwc(strSubFilePath);
        bFileIsFound = (eOk == findPathToFile(strBaseFileDir, strSubFilePath));
        if (bFileIsFound)
        {
          modelType = NwModelType::nw_model;
          bIsChangeToNwc = true;
        }
      }
      ODA_ASSERT(bFileIsFound);
      if (bFileIsFound)
      {
        OdTvResult res = tvOk;
        switch (modelType)
        {
        case NwModelType::dwg_model:
        {
          OdTvDwgAppendParams oImportParams;
          oImportParams.setTransform(trf);
          // fill base fields in param
          oImportParams.setFilePath(strSubFilePath.c_str());
          oImportParams.setProfiling(&databaseInfo);
          oImportParams.setDCRect(rectDC);
          oImportParams.setNeedCDATree(m_properties->getNeedCDATree());
          oImportParams.setNeedCollectPropertiesInCDA(m_properties->getNeedCollectPropertiesInCDA());
          lastTvModelId = pTvDb->append(&oImportParams, &res);
        }
        break;
        case NwModelType::revit_model:
        {
          OdTvBimAppendParams oImportParams;
          oImportParams.setTransform(trf);
          oImportParams.setFilePath(strSubFilePath.c_str());
          oImportParams.setProfiling(&databaseInfo);
          oImportParams.setDCRect(rectDC);
          oImportParams.setNeedCDATree(m_properties->getNeedCDATree());
          oImportParams.setNeedCollectPropertiesInCDA(m_properties->getNeedCollectPropertiesInCDA());
          lastTvModelId = pTvDb->append(&oImportParams, &res);
        }
        break;
        case NwModelType::dgn_model:
        {
          OdTvDgnAppendParams oImportParams;
          oImportParams.setTransform(trf);
          oImportParams.setFilePath(strSubFilePath.c_str());
          oImportParams.setProfiling(&databaseInfo);
          oImportParams.setDCRect(rectDC);
          oImportParams.setNeedCDATree(m_properties->getNeedCDATree());
          oImportParams.setNeedCollectPropertiesInCDA(m_properties->getNeedCollectPropertiesInCDA());
          lastTvModelId = pTvDb->append(&oImportParams, &res);
        }
        break;
        case NwModelType::nw_model:
        {
          OdTvNwAppendParams oImportParams;
          oImportParams.setTransform(trf);
          oImportParams.setFilePath(strSubFilePath.c_str());
          oImportParams.setProfiling(&databaseInfo);
          oImportParams.setDCRect(rectDC);
          oImportParams.setNeedCDATree(m_properties->getNeedCDATree());
          oImportParams.setNeedCollectPropertiesInCDA(m_properties->getNeedCollectPropertiesInCDA());
          oImportParams.setReplaceByNwc(bIsChangeToNwc);
          lastTvModelId = pTvDb->append(&oImportParams, &res);
        }
        break;
        case NwModelType::ifc_model:
        {
          OdTvIfcAppendParams oImportParams;
          oImportParams.setTransform(trf);
          oImportParams.setFilePath(strSubFilePath.c_str());
          oImportParams.setProfiling(&databaseInfo);
          //oImportParams.setDCRect(rectDC);
          oImportParams.setNeedCDATree(m_properties->getNeedCDATree());
          oImportParams.setNeedCollectPropertiesInCDA(m_properties->getNeedCollectPropertiesInCDA());
          lastTvModelId = pTvDb->append(&oImportParams, &res);
        }
        break;
        default:
          break;
        }
        ODA_ASSERT(tvOk == res);
      } // if (isFileFound)
    }
    if (!pTvView.isNull() && !lastTvModelId.isNull())
      pTvView->addModel(lastTvModelId);

    iReadTime += databaseInfo.getImportTime();
    iCdaTime += databaseInfo.getCDATreeCreationTime();
    iTvTime += databaseInfo.getTvTime();
  }

  //VAS: remove unnecesary temp model
  pTvDb->removeModel(tvTempModelForUnits);

  // fill time profiling
  if (pProfileRes)
  {
    pProfileRes->setImportTime(iReadTime);
    pProfileRes->setCDATreeCreationTime(iCdaTime);
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64(nTotalTvTime * 1000.) + iTvTime);
#endif
  }
}

void OdTvVisualizeNwFiler::loadNwd(OdTvDatabaseId tvDbId, OdNwDatabasePtr pNwDb, OdTvFilerTimer &timing, OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  // get default color from properties
  ODCOLORREF* pDefColor = (ODCOLORREF*)m_properties->getDefaultNwColor();
  OdUInt8 r, g, b;
  r = ODGETRED(*pDefColor);
  g = ODGETGREEN(*pDefColor);
  b = ODGETBLUE(*pDefColor);

  //
  // prepare Visualize timing object
  //
  OdPerfTimerBase* pTvTimer = 0;
  double nTotalTvTime = 0.;
  bool bUseTimeProfiling = (NULL != pProfileRes);
  if (bUseTimeProfiling)
    pTvTimer = OdPerfTimerBase::createTiming();

  START_TV_NW_TIMER

  //generate model name
  OdString modelName;
  if (auto nwCurrSheetId = pNwDb->getActiveSheetId())
  {
    OdNwSheetInfoPtr pNwCurrSheet = nwCurrSheetId.safeOpenObject();
    modelName = pNwCurrSheet->getDisplayName();
  }
  modelName.replace('.', '_');
  if (modelName.isEmpty())
    modelName = OD_T("model1");

  //create tv model
  OdTvModelId tvModelId = pTvDb->createModel(modelName);

  END_TV_NW_TIMER

  OdTvGeomCollector wd(bUseTimeProfiling);

  OdTvNwSavedAnimationEnumerator savedAnimEnum(pNwDb, pTvDb, tvModelId);
  savedAnimEnum.getMapNwTv().clear();
  savedAnimEnum.enumSelectedModels();
  setupGeometry(pNwDb->getModelItemRootId(), tvModelId, pTvTimer, nTotalTvTime, savedAnimEnum.getMapNwTv());

  OdNwObjectIdArray aLights;
  if (pNwDb->getLightElements(aLights) == eOk)
    setupLights(tvModelId, aLights);

  START_TV_NW_TIMER

  //here we also will create a device and view, becuase we want the Shaded initial mode
  OdTvGsDeviceId tvDeviceId = pTvDb->createDevice(modelName);
  ODCOLORREF* pColor = (ODCOLORREF*)(m_properties->getBackgroundColor());
  tvDeviceId.openObject(OdTv::kForWrite)->setBackgroundColor(*pColor);

  OdTvGsViewBackgroundId bkgId = setupBackground(pNwDb->getBackgroundElementId(), pTvDb);
  OdTvGsViewId viewId = setupCurrentView(pNwDb->getCurrentViewId(), tvDeviceId, tvModelId, bkgId);
  savedAnimEnum.feedAnimation();
  if (m_properties->getImportGrid())
  {
    setupGrid(pNwDb, tvDbId, viewId);
  }

  // get Clipping planes
  if (m_properties->getImportCuttingPlanes() && !gDrawBoundingBoxes)
  {
    if (auto nwClipPlaneSetId = pNwDb->getCurrrentViewClippingPlanesId())
    {
      OdNwClipPlaneSetPtr pClipPlaneSet = nwClipPlaneSetId.safeOpenObject();
      {
        NwClipPlaneSetMode::Enum mode = pClipPlaneSet->getMode(); // CL_PLANES or CL_BOX
      
        bool isEnabled = pClipPlaneSet->isEnabled();
        bool isLinked = pClipPlaneSet->isLinked();
        OdUInt32 index = pClipPlaneSet->getCurrentPlaneIndex();
        OdGeMatrix3d matrix = pClipPlaneSet->getTransform();
      
        if (isEnabled)
        {
          OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
          if (mode == NwClipPlaneSetMode::CL_BOX)
          {
            OdArray<OdGePlane> aPlanes;
            if (pClipPlaneSet->getPlanesForActiveMode(aPlanes) == eOk)
            {
              for (OdUInt32 i = 0; i < 6; ++i)
                pView->addCuttingPlane(aPlanes[i]);
            }
          }
          else
          {
            for (OdInt32 cliPlane = 0; cliPlane < 6; ++cliPlane)
            {
              OdNwClipPlane plane;
              if (eOk == pClipPlaneSet->getClipPlaneByIndex(plane, cliPlane))
              {
                //get pkane state (DEFAULT - switched off or ENABLED - switched on)
                NwClipPlaneState::Enum state = plane.getState();
                if (state == NwClipPlaneState::ENABLED)
                {
                  //get section plane parameters
                  OdGePlane gePlane = plane.getPlane();
                  OdGePoint3d origin;
                  OdGeVector3d axis1, axis2;
                  gePlane.getCoordSystem(origin, axis1, axis2);
      
                  //create Tv Plane and reverse normal since Visualize SDK cut the opposite semispace in comparison with Navisworks
                  OdTvPlane tvPlane(origin, axis1, axis2);
                  tvPlane.reverseNormal();
      
                  OdGeVector3d normal = tvPlane.normal();
                  pView->addCuttingPlane(tvPlane);
                }
              }
            }
          }
        }
      }
    }
  }

  END_TV_NW_TIMER

  timing.startMisc();

  OdTvDatabaseCleaner::cleanTvDatabase(tvDbId);

  timing.endMisc();

  if (m_properties->getNeedCDATree())
  {
    timing.startMisc();

    createCommonDataAccessTree(pTvDb, pNwDb, modelName + OD_T(".nwd"), tvModelId);

    timing.endMisc();

    if (pProfileRes)
      pProfileRes->setCDATreeCreationTime(pProfileRes->getCDATreeCreationTime() + OdInt64((timing.getMiscTime()) * 1000.));
  }

  if (pProfileRes)
  {
#if !defined(__APPLE__)
    pProfileRes->setTvTime(pProfileRes->getTvTime() + OdInt64(nTotalTvTime * 1000.));
#endif
  }
}

OdTvDatabaseId OdTvVisualizeNwFiler::loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  LoadNwOptions opt(pBuffer);
  return importFile(opt, pProfileRes, rc);
}

OdTvDatabaseId OdTvVisualizeNwFiler::loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  LoadNwOptions opt(pDatabase);
  return importFile(opt, pProfileRes, rc);
}


OdTvModelId OdTvVisualizeNwFiler::appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeNwFilerDbSource *pNwDatabaseSource, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvModelId tvModelId;

  if (rc)
    *rc = tvOk;

  OdTvGsDeviceId activeTvGsDeviceId;
  {
    OdTvDatabasePtr pTvDb = databaseId.openObject();
    OdTvDevicesIteratorPtr devicesIteratorPtr = pTvDb->getDevicesIterator();
    while (!devicesIteratorPtr->done())
    {
      activeTvGsDeviceId = devicesIteratorPtr->getDevice();
      if (activeTvGsDeviceId.openObject()->getActive())
        break;
      devicesIteratorPtr->step();
    }
  }

  //get palette, background and device size
  ODCOLORREF background = ODRGB(0, 0, 0);
  OdTvDCRect rect(0, 0, 0, 0);
  OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;

  if (!activeTvGsDeviceId.isNull())
  {
    OdTvGsDevicePtr pTvDevice = activeTvGsDeviceId.openObject();

    background = pTvDevice->getBackgroundColor();
    pTvDevice->getSize(rect);

    int nColors;
    const ODCOLORREF* pPalette = pTvDevice->getLogicalPalette(nColors);
    if (nColors >= 256)
      pPalCpy.insert(pPalCpy.begin(), pPalette, pPalette + 256);
    else
    {
      pPalCpy.insert(pPalCpy.begin(), pPalette, pPalette + nColors);
      pPalCpy.insert(pPalCpy.begin() + nColors, 256 - nColors, ODRGB(0, 0, 0));
    }
  }

  //collcet current models and blocks
  std::set<OdTvGsViewId> foreignViews;
  std::set<OdTvModelId> foreignModels;
  std::set<OdTvBlockId> foreignBlocks;
  OdTvDatabaseUtils::collectViewsModelsAndBlocks(databaseId, foreignViews, foreignModels, foreignBlocks);

  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;
  double internalTiming = 0.;
  double externalTiming = 0;

  //prepare timing object
  OdTvFilerTimer timing(bUseTimeProfiling);
  timing.startTotal();

  // Generate model name
  OdString modelName = OdTvDatabaseUtils::generateModelName(databaseId, pNwDatabaseSource->getFilename());

  //store visualize device module name
  OdString moduleName;
  try
  {
    OdNwDatabasePtr pNwDb = pNwDatabaseSource->getDb();

    if (!pNwDb.isNull())
    {
      timing.startVectorizing();

      //
      // prepare Visualize timing object
      //
      OdPerfTimerBase* pTvTimer = 0;
      double nTotalTvTime = 0.;
      bool bUseTimeProfiling = (NULL != pProfileRes);
      if (bUseTimeProfiling)
        pTvTimer = OdPerfTimerBase::createTiming();

      START_TV_NW_TIMER
      
      //create tv model
      OdTvDatabasePtr pTvDb = databaseId.openObject(OdTv::kForWrite);
      tvModelId = pTvDb->createModel(modelName);
      
      END_TV_NW_TIMER

      OdTvGeomCollector wd(bUseTimeProfiling);
      mapNwObjectId2EntityIdType mapModelItemId2EntityId;
      mapNwObjId2TvIdsType selectedModels;
      setupGeometry(pNwDb->getModelItemRootId(), tvModelId, pTvTimer, nTotalTvTime, selectedModels);

      //OdArray<OdNwCommonLightPtr> aLights;
      //if (pNwDb->getLightElements(aLights) == eOk)
      //  setupLights(tvModelId, aLights);

      START_TV_NW_TIMER

      if (activeTvGsDeviceId.isNull())
      {
        OdTvDatabasePtr bTvDb = databaseId.openObject();
        activeTvGsDeviceId = bTvDb->createDevice(OD_T("Window_NW"));
        ODCOLORREF* pColor = (ODCOLORREF*)(m_properties->getBackgroundColor());
        activeTvGsDeviceId.openObject(OdTv::kForWrite)->setBackgroundColor(*pColor);
      }

      {
        OdTvGsDevicePtr pTvDevice = activeTvGsDeviceId.openObject(OdTv::kForWrite);
        if (pTvDevice->numViews() == 0)
        {
          OdTvGsViewBackgroundId bkgId = setupBackground(pNwDb->getBackgroundElementId(), pTvDb);
          setupCurrentView(pNwDb->getCurrentViewId(), activeTvGsDeviceId, tvModelId, bkgId);
        }
      }

      //VAS: if properties has device for append then need to add model to active view from this device(need to correct work appendFrom functionality)
      if (!m_properties->getTvDeviceToAppend().isNull())
      {
        OdTvGsDevicePtr pTvDeviceToAppend = m_properties->getTvDeviceToAppend().openObject(OdTv::kForWrite);
        if (!pTvDeviceToAppend.isNull())
        {
          OdTvGsViewId viewId = pTvDeviceToAppend->getActiveView();
          if (!viewId.isNull())
          {
            OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
            pView->addModel(tvModelId, rc);
          }
        }
      }

      END_TV_NW_TIMER

      //pTvDevice->update(&rect);

      if (databaseId.isValid())
      {
        timing.startMisc();

        OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
        OdTvDatabaseCleaner::cleanTvDatabaseForAppend(tvDvId, foreignViews, foreignModels, foreignBlocks);

        //apply transform if need 
        OdTvMatrix* pTransfrom = (OdTvMatrix*)m_properties->getAppendTransform();
        if (pTransfrom)
        {
          OdTvDatabaseId& tvDvId = const_cast<OdTvDatabaseId&>(databaseId);
          if (m_properties->getReplaceByNwc())
            OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, modelName, (*pTransfrom) * pNwDb->getModelTransform().invert());
          else
            OdTvDatabaseUtils::applyTransformToTheModel(tvDvId, modelName, *pTransfrom);
        }

        timing.endMisc();
      }

      // save file name to database user data
      OdTvDatabaseUtils::writeFileNameToTvDatabase(databaseId, pNwDatabaseSource->getFilename());

      //initialize cache and switch it to the "write only" mode
      ExGsVisualizeDeviceCache deviceCache;
      deviceCache.m_bApplyCacheData = false;

      externalTiming = timing.getMiscTime();

      timing.endVectorizing();

      if (m_properties->getNeedCDATree())
      {
        timing.startMisc();

        OdTvDatabasePtr pTvDb = databaseId.openObject();
        createCommonDataAccessTree(pTvDb, pNwDb, modelName + OD_T(".nwd"), tvModelId);

        timing.endMisc();

        if (pProfileRes)
          pProfileRes->setCDATreeCreationTime(OdInt64((timing.getMiscTime()) * 1000.));
      }

    }
    else
    {
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

  //unload Dgn modules (try to emulate the OdUninitialized for Nw)
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  timing.endTotal();

  if (pProfileRes)
  {
    pProfileRes->setImportTime(OdInt64((timing.getTotalTime() - timing.getVectorizingTime() + pNwDatabaseSource->getInitTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64(timing.getVectorizingTime() * 1000.));
#if !defined(__APPLE__)
    pProfileRes->setTvTime(OdInt64((internalTiming + externalTiming) * 1000.));
#endif
  }

  return tvModelId;
}

static void addBoundingBoxVisualization(OdTvEntityPtr entity, const OdGeExtents3d& bbox, const OdTvColorDef& color, OdGeMatrix3d trf = OdGeMatrix3d::kIdentity)
{
  entity->setColor(color);

  const OdGePoint3d& minP = bbox.minPoint();
  const OdGePoint3d& maxP = bbox.maxPoint();
  OdTvPoint points_top[4] = { {minP.x, maxP.y, maxP.z}, {minP.x, minP.y, maxP.z}, {maxP.x, minP.y, maxP.z}, {maxP.x, maxP.y, maxP.z} };
  OdTvPoint points_bottom[4] = { {maxP.x, minP.y, minP.z}, {maxP.x, maxP.y, minP.z}, {minP.x, maxP.y, minP.z}, {minP.x, minP.y, minP.z} };
  OdTvPoint points_right[4] = { {minP.x, minP.y, maxP.z}, {minP.x, minP.y, minP.z}, {maxP.x, minP.y, minP.z}, {maxP.x, minP.y, maxP.z} };
  OdTvPoint points_left[4] = { {maxP.x, maxP.y, minP.z}, {maxP.x, maxP.y, maxP.z}, {minP.x, maxP.y, maxP.z}, {minP.x, maxP.y, minP.z} };
  entity->appendPolyline(4, points_top);
  entity->appendPolyline(4, points_bottom);
  entity->appendPolyline(4, points_right);
  entity->appendPolyline(4, points_left);
  if (trf != OdGeMatrix3d::kIdentity)
    entity->setModelingMatrix(trf);
}

static bool isModelItemClipped(const OdNwModelItemPtr& item, const OdGeMatrix3d& clipMatr)
{
  OdGeExtents3d bbox = item->getBoundingBox();
  OdGeMatrix3d invertMatrix = clipMatr;
  bbox.transformBy(invertMatrix.invert());

  static const OdGeExtents3d clipbox (
    OdGePoint3d(-0.5, -0.5, -0.5),
    OdGePoint3d(0.5, 0.5, 0.5));

  return bbox.intersectWith(clipbox) == OdGeExtents3d::kIntersectNot;
}

//VAS: helper function for creating tv object with unique name(layers, blocks, materials, backgrounds)
//T - return type of tv object id
//pFindFunc - pointer to method fo finding tv object id from tv database
//pFindFunc - pointer to method fo creating tv object id from tv database
//pHelpMapWithNextNameIdx - pointer to map with help info like: by name object as key is possible to know next index for objects with same original name
template <class T, T(OdTvDatabase::*pFindFunc)(const OdString&, OdTvResult*), T(OdTvDatabase::*pCreateFunc)(const OdString&, OdTvResult*)>
inline T createTvDbUniqueObject(OdTvDatabasePtr pTvDb, const OdString& nwObjName, std::map<OdString, OdUInt32>* pHelpMapWithNextNameIdx = nullptr)
{
  //VAS: check if tv database already has unique object with such name
  //VAS: for some unknown reasons constructions as 'pTvDb->*pFindFunc' with calling of pointer to function is not work, then we call operator -> directly from pTvDb object
  auto tvObjId = (pTvDb.operator->()->*pFindFunc)(nwObjName, nullptr);

  auto creatTvObj = [&pTvDb, &pHelpMapWithNextNameIdx](const OdString& nwObjName)
  {
    OdTvResult tvRes = tvOk;
    auto tvObjId = (pTvDb.operator->()->*pCreateFunc)(nwObjName, &tvRes);
    if (tvRes == tvInvalidName)
    {
      //it's forrbiden to create tv unique objects(layers, blocks, materials, backgrounds and etc.) with inadmissible control letters, so for correct export need to remove those characters from name
      auto nwNewObjName = nwObjName;
      for (auto ch : { '<', '>', '\\', '/', ':', ';', '?', ',', '*', '|', '=', '\'', ' ', '\"' })
        nwNewObjName.remove(ch);
      tvObjId = createTvDbUniqueObject<T, pFindFunc, pCreateFunc>(pTvDb, nwNewObjName);
    }
    else if (tvRes == tvForbiddenName)//tv database can't contain unique object with name "0"
      tvObjId = createTvDbUniqueObject<T, pFindFunc, pCreateFunc>(pTvDb, OD_T("0_"), pHelpMapWithNextNameIdx);
    return tvObjId;
  };

  if (tvObjId.isNull())
    tvObjId = creatTvObj(nwObjName);
  else
  {
    //VAS: if tv database already has object with such name - try to find new name for object with adding integer number
    OdUInt32 nameIdx = 2;

    if (pHelpMapWithNextNameIdx)
    {
      //VASL for good import time there is good to remember last index for equal block name
      auto itFnd = pHelpMapWithNextNameIdx->find(nwObjName);
      if (itFnd != pHelpMapWithNextNameIdx->end())
      {
        nameIdx = itFnd->second;
      }
    }

    for (;;++nameIdx)
    {
      OdString sTempName = nwObjName + OdString().format(OD_T("_%u"), nameIdx);
      auto tempTvObjId = (pTvDb.operator->()->*pFindFunc)(sTempName, nullptr);
      if (tempTvObjId.isNull())
      {
        tvObjId = creatTvObj(sTempName);
        if (pHelpMapWithNextNameIdx)
        {
          auto itFnd = pHelpMapWithNextNameIdx->find(nwObjName);
          if (itFnd != pHelpMapWithNextNameIdx->end())
            itFnd->second++;
          else
            pHelpMapWithNextNameIdx->insert({nwObjName, std::move(++nameIdx) });
        }
        break;
      }
    }
  }

  return tvObjId;
}

void OdTvVisualizeNwFiler::setupGeometry(const OdNwObjectId& nwModelItemRootId, const OdTvModelId& tvModelId, OdPerfTimerBase* pTvTimer, double& nTotalTvTime, mapNwObjId2TvIdsType &nwId2TvIds) const
{
  if (!nwModelItemRootId)
    return;

  // get default color from properties
  ODCOLORREF* pDefColor = (ODCOLORREF*)m_properties->getDefaultNwColor();
  OdUInt8 r, g, b;
  r = ODGETRED(*pDefColor);
  g = ODGETGREEN(*pDefColor);
  b = ODGETBLUE(*pDefColor);

  OdTvColorDef defaultEntColor = OdTvColorDef(r, g, b);

  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::kForWrite);
  OdTvDatabaseId tvDbId = pTvModel->getDatabase();
  OdTvDatabasePtr pTvDb = tvDbId.openObject(OdTv::kForWrite);

  //VAS: set units for tv model, if its first tv model of this tv database this units will be units for tv database
  pTvModel->setUnits([](NwModelUnits::Enum nwUnits)->OdTv::Units
  {
    switch (nwUnits)
    {
    case NwModelUnits::UNITS_METERS:
      return OdTv::kMeters;
      break;
    case NwModelUnits::UNITS_CENTIMETERS:
      return OdTv::kCentimeters;
      break;
    case NwModelUnits::UNITS_MILLIMETERS:
      return OdTv::kMillimeters;
      break;
    case NwModelUnits::UNITS_FEET:
      return OdTv::kFeet;
      break;
    case NwModelUnits::UNITS_INCHES:
      return OdTv::kInches;
      break;
    case NwModelUnits::UNITS_YARDS:
      return OdTv::kYards;
      break;
    case NwModelUnits::UNITS_KILOMETERS:
      return OdTv::kKilometers;
      break;
    case NwModelUnits::UNITS_MILES:
      return OdTv::kMiles;
      break;
    case NwModelUnits::UNITS_MICROMETERS:
      return OdTv::kMicrometers;
      break;
    case NwModelUnits::UNITS_MILS:
      return OdTv::kMils;
      break;
    case NwModelUnits::UNITS_MICROINCHES:
      return OdTv::kMicroInches;
      break;
    default:
      return OdTv::kUserDefined;
      break;
    }
  }(nwModelItemRootId.database()->getUnits()));

  //OdTvGeomCollector wd(bUseTimeProfiling);

  //map with nw geometries and counters of reusing in model(how much fragments are link with geometry id):
  std::map<OdNwObjectId, OdUInt32> mGeomReusCount;
  //list with geometry model item nodes tuple, where:
  //0 - pointer to geometry model item
  //1 - tv layer id which need to set for entity which will be created by geometry model item
  //2 - boolean flag is this model item has is hidden status by itslef or by parent
  //3 - vector with raw pointers to uint32 counters from mGeomReusCount
  //4 - entity name
  std::list<std::tuple<OdNwModelItemPtr, OdTvLayerId, bool, std::vector<OdUInt32*>, OdString> > lHasGeometryNodes;
  //VAS: go through logical hierarchy tree of nw and let's create flat container from its leaves
  {
    OdTvLayerId tvCurLayerId;
    bool isHiddenBranch = false;
    std::list<OdString> lBranchName;

    auto geomNodeProcess = [&lHasGeometryNodes, &tvCurLayerId, &isHiddenBranch, &mGeomReusCount, &lBranchName](OdNwModelItemPtr pNode)
    {
      //vector with raw pointers to uint32 counters from mGeomReusCount
      std::vector<OdUInt32*> vGeomRefCounts;

      OdNwComponentPtr pGeomComp = pNode->getGeometryComponentId().safeOpenObject();
      OdNwObjectIdArray aFrags;
      if (pGeomComp->getFragments(aFrags) == eOk)
      {
        vGeomRefCounts.reserve(aFrags.size());
        for (auto& fragId : aFrags)
        {
          OdNwFragmentPtr pFrag = fragId.safeOpenObject();
          auto geomId = pFrag->getGeometryId();
          //VAS: check if this geometry id already has in mGeomReusCount map, if yes - then increase counter, if not - add new element in map
          auto resFnd = mGeomReusCount.find(geomId);
          if (resFnd != mGeomReusCount.end())
          {
            ++(resFnd->second);
            vGeomRefCounts.push_back(&resFnd->second);
          }
          else
          {
            auto resIns = mGeomReusCount.insert({ geomId, 1 });
            if (resIns.second)
              vGeomRefCounts.push_back(&resIns.first->second);
          }
        }
      }

      if (!pNode->getDisplayName().isEmpty())
        lBranchName.push_back(pNode->getDisplayName());
      else
        lBranchName.push_back(pNode->getClassDisplayName());

      //VAS: add new element in our flat hierarchy
      lHasGeometryNodes.push_back(std::make_tuple(pNode, tvCurLayerId, isHiddenBranch ? isHiddenBranch : pNode->isHidden(), std::move(vGeomRefCounts),
                                                  [&lBranchName]()
                                                  {
                                                    OdString sEntName;
                                                    for (auto itLBrName = std::next(lBranchName.begin()); itLBrName != lBranchName.end(); ++itLBrName)
                                                    {
                                                      if (itLBrName == std::next(lBranchName.begin()))
                                                        sEntName = *itLBrName;
                                                      else
                                                        sEntName += OD_T(" -> ") + *itLBrName;
                                                    }
                                                    return sEntName;
                                                  }()));

      lBranchName.pop_back();
    };
    auto groupNodeProcess = [&tvCurLayerId, &isHiddenBranch, &pTvDb, &lBranchName](OdNwModelItemPtr pNode, std::function<void(OdNwModelItemPtr)> func)
    {
      //save old is hidden value
      auto isHiddenBranchTempValue = isHiddenBranch;
      //VAS: if OdNwModelItem object is layer - create tv layer object and set it like current layer for nested children tv entities
      if (pNode->getIcon() == NwModelItemIcon::LAYER)
      {
        tvCurLayerId = createTvDbUniqueObject<OdTvLayerId, &OdTvDatabase::findLayer, &OdTvDatabase::createLayer>(pTvDb, pNode->getDisplayName());
        if (!tvCurLayerId.isNull())
        {
          auto pTvLayer = tvCurLayerId.openObject(OdTv::kForWrite);
          pTvLayer->setVisible(isHiddenBranch ? false : !pNode->isHidden());
        }
      }
      else
      {
        //VAS: if OdNwModelItem object has is hidden value - then change current is hidden value
        if (pNode->isHidden())
          isHiddenBranch = true;

        if (!pNode->getDisplayName().isEmpty())
          lBranchName.push_back(pNode->getDisplayName());
        else
          lBranchName.push_back(pNode->getClassDisplayName());
      }

      func(pNode);

      if (pNode->getIcon() != NwModelItemIcon::LAYER)
        lBranchName.pop_back();

      //VAS: return old is hidden value
      isHiddenBranch = isHiddenBranchTempValue;
    };

    std::function<OdResult(const OdNwObjectId&)> getGeometryNodesByRoot = [&getGeometryNodesByRoot, &geomNodeProcess, &groupNodeProcess](const OdNwObjectId& nwRootId)
    {
      OdResult res = eOk;
      OdTvResult tvRes = tvOk;
      OdNwModelItemPtr pRoot = nwRootId.safeOpenObject();
      //VAS: if pRoot is end leaf and has geometry data - add node data to lHasGeometryNodes
      if (pRoot->hasGeometry())
        geomNodeProcess(pRoot);
      else// hasn't geomentry
      {
        groupNodeProcess(pRoot, [&res, &getGeometryNodesByRoot](OdNwModelItemPtr pRoot)
        {
          //VAS: process nested chidlren of model item node
          OdNwObjectIdArray aRootChildren;
          res = pRoot->getChildren(aRootChildren);
          if (res == eOk)
          {
            for (auto& childId : aRootChildren)
            {
              if (!childId)
              {
                res = eNullObjectId;
                break;
              }
          
              res = getGeometryNodesByRoot(childId);
              if (res != eOk)
                break;
            }
          }
        });
      }
    
      return res;
    };
    auto res = getGeometryNodesByRoot(nwModelItemRootId);
    ODA_ASSERT(res == eOk);
  }

  bool alreadyExist = false;
  OdTvRegAppId regAppId = pTvDb->registerAppName(OD_T("ExGsVisualizeDevice"), alreadyExist);

  bool isClipboxEnabled = false;
  OdGeMatrix3d matrix = OdGeMatrix3d::kIdentity;
  OdNwDatabase* pDb = nwModelItemRootId.database();

  if (gDrawBoundingBoxes)
  {
    // visualize current view clipbox
    auto nwClipPlaneSetId = pDb->getCurrrentViewClippingPlanesId();
    OdNwClipPlaneSetPtr pClipPlaneSet = nwClipPlaneSetId.safeOpenObject();
    if (pClipPlaneSet->isEnabled() && NwClipPlaneSetMode::CL_BOX == pClipPlaneSet->getMode())
    {
      matrix = pClipPlaneSet->getTransform();
      isClipboxEnabled = true;
      OdGeExtents3d bbox;
      bbox.addPoint(OdGePoint3d(-0.5, -0.5, -0.5));
      bbox.addPoint(OdGePoint3d(0.5, 0.5, 0.5));

      OdTvEntityId entBBoxId = pTvModel->appendEntity(OD_T("CLIPBOX_BBOX"));
      addBoundingBoxVisualization(entBBoxId.openObject(OdTv::kForWrite),
        bbox, OdTvColorDef(255, 0, 0),
        matrix
      );
    }
  }

  //VAS: multi map with tv block for reused geometries - reused nw geometry id as key and range of pair with tv block id and nw geometry ids from which data this block is created
  std::multimap<OdNwObjectId, std::pair<OdTvBlockId, OdNwObjectIdArray > > mmTvBlocks;

  //VAS: lamda for getting count of reusing of geometry in model(also can be used for checkinig is geometry resued or not)
  auto getGeomReusedCount = [&mGeomReusCount](const OdNwObjectId& nwGeomId)->OdUInt32
  {
    auto resFnd = mGeomReusCount.find(nwGeomId);
    if (resFnd != mGeomReusCount.end())
      return resFnd->second;
    return 0;
  };

  //VAS: because in one tv database there can be only one block with one name - for correct UI interpretation there can be good add blocks with same name and with index(f.e - NwBlock, NwBlock1,NwBlock2 and etc.), for this case - there will be good to conatin next index for block name
  std::map<OdString, OdUInt32> mNextBlockNames;
  mapNwObjectId2EntityIdType oid2tvent;
  std::map<OdNwModelItemPtr, OdTvEntityPtr> nwModelToTvEntity;
  //VAS: go through flat hierarchy and add geometry data to tv database
  for (auto& pHasGeomNode : lHasGeometryNodes)
  {
    if (gDrawBoundingBoxes 
      && isClipboxEnabled 
      && isModelItemClipped(std::get<0>(pHasGeomNode), matrix)) 
    {
      continue;
    }

    auto nwComponentId = std::get<0>(pHasGeomNode)->getGeometryComponentId();
    if (!nwComponentId)
      continue;

    OdNwComponentPtr pComp = nwComponentId.safeOpenObject();
    if (!pComp->getFragmentCount())
      continue;

    //VAS: create tv material by nw material
    auto nwMatId = pComp->getMaterialId();
    OdTvMaterialId tvMatId = importMaterial(pTvModel->getDatabase(), nwMatId, pComp->getOriginalMaterialId());
    OdTvColorDef tvEntClr = defaultEntColor;
    if (nwMatId)
    {
      OdNwColor diffuse = OdNwMaterial::cast(nwMatId.safeOpenObject())->getDiffuse();
      tvEntClr = OdTvColorDef(255.0 * diffuse.R(), 255.0 * diffuse.G(), 255.0 * diffuse.B());
    }

    if (gDrawBoundingBoxes)
    {
      OdGeExtents3d bbox = std::get<0>(pHasGeomNode)->getBoundingBox();

      OdTvEntityId entBBoxId = pTvModel->appendEntity(std::get<4>(pHasGeomNode) + OD_T("_BBOX"));
      addBoundingBoxVisualization(entBBoxId.openObject(OdTv::kForWrite),
        bbox, defaultEntColor);
    }

    //VAS: lambda for adding geometry data from nw geometry into tv entity
    auto appendGeomDataToEntity = [&pTvTimer, &nTotalTvTime, &pTvDb](const OdNwObjectId& nwGeomId, OdTvEntityPtr pTvEntity)
    {
      OdNwGeometryPtr pNwGeom = nwGeomId.safeOpenObject();
     
      OdTvMapperDef tvMatMap = pTvEntity->getMaterialMapper();
      if (pNwGeom->isA() == OdNwGeometryLineSet::desc())
      {
        OdNwGeometryLineSetPtr pGeomertyLineSet = pNwGeom;

        ODA_ASSERT(!pGeomertyLineSet.isNull());
        OdNwVerticesDataPtr pVerticesData = pGeomertyLineSet->getVerticesData();
        OdGePoint3dArray Vertexes = pVerticesData->getVertices();
        OdUInt16Array VertexPerLine = pGeomertyLineSet->getVerticesCountPerLine();
        OdUInt32Array lineColors = pVerticesData->getColors();
        size_t colorsSize = lineColors.size();
        const bool bAppentWithColor = (colorsSize > 0 && Vertexes.size() == colorsSize);

        auto appendColor = [](OdTvGeometryDataPtr& geomData, const OdUInt32 nVertexColor)
        {
          if (!geomData.isNull())
          {
            OdTvColorDef vertexColnVertexColor(
              static_cast <OdUInt8> ((nVertexColor) & 0xFF),        // r
              static_cast <OdUInt8> ((nVertexColor >> 8U) & 0xFF),  // g
              static_cast <OdUInt8> ((nVertexColor >> 16U) & 0xFF)  // b
            );
            geomData->setColor(vertexColnVertexColor);
          }
        };
      
        OdInt32 nCurrentLineVertex = 0;
        std::vector<OdTvGeometryDataId> vTempData;
        for (OdUInt16Array::const_iterator it = VertexPerLine.begin();
          it != VertexPerLine.end(); ++it)
        {
          // vertex count for current line
          const OdInt16 nVertexPerLine = *it;
          OdTvGeometryDataId polylineDataId = pTvEntity->appendPolyline(nVertexPerLine, &Vertexes[nCurrentLineVertex]);
          vTempData.push_back(polylineDataId);
          OdTvGeometryDataPtr polyLineData = polylineDataId.openObject();
          if (bAppentWithColor)
          {
            const OdUInt32 nStartColor = lineColors[nCurrentLineVertex];
            appendColor(polyLineData, nStartColor);
#if defined (_DEBUG)
            // check file for the case of VIS-1861
            for (OdUInt16 nColor = 1; nColor < nVertexPerLine; ++nColor)
            {
              ODA_ASSERT(nStartColor == lineColors[nCurrentLineVertex + nColor]);
            }
#endif
          }

          // shift vertex index to the start position of next line
          nCurrentLineVertex += nVertexPerLine;
        }
      }
      else if (pNwGeom->isA() == OdNwGeometryEllipticalShape::desc())
      {
        START_TV_NW_TIMER
          OdNwGeometryEllipticalShapePtr pGeometryEllipticalShape = pNwGeom;

          // TODO: check this equation!
          auto tvCircleId = pTvEntity->appendCircle(pGeometryEllipticalShape->getOrigin(),
                                                 pGeometryEllipticalShape->getRadius(),
                                                 pGeometryEllipticalShape->getXVector().crossProduct(pGeometryEllipticalShape->getYVector()));
          if (tvCircleId.isValid())
            tvCircleId.openAsCircle()->setFilled(true);

          tvMatMap.setProjection(OdTvMapperDef::kSphere);

        END_TV_NW_TIMER
      }
      else if (pNwGeom->isA() == OdNwGeometryMesh::desc())
      {
#ifdef NW_DRAW_MESH_AS_POINTSET
        START_TV_NW_TIMER
          OdNwGeometryMeshPtr pGeometrMesh = pNwGeom;
          OdArray<OdGePoint3d> vertices = pGeometryMesh->getVertexes();
          entPtr->appendPointCloud(vertices.size(), vertices.asArrayPtr());
        END_TV_NW_TIMER
#endif
              
        START_TV_NW_TIMER
             
        OdNwGeometryMeshPtr pGeometrMesh = pNwGeom;
        OdNwVerticesDataPtr pVerticesData = pGeometrMesh->getVerticesData();
        ODA_ASSERT(!pVerticesData.isNull());

        OdGePoint3dArray vertices = pVerticesData->getVertices();
        
        OdUInt16Array vertexPerFace = pGeometrMesh->getVerticesPerFace();
        OdInt32Array faces;

        OdArray<OdNwTriangleIndexes> prep_faces = pGeometrMesh->getTriangles();
        faces.reserve(4 * prep_faces.size()); // 1 (size=3) + 3 (vertex indices) = 4
        for (OdArray<OdNwTriangleIndexes>::const_iterator itFaces = prep_faces.begin()
          ; itFaces != prep_faces.end(); ++itFaces)
        {
          const OdNwTriangleIndexes& triangulated_face = *itFaces;

          faces.push_back(3); // 3 indexes
          faces.push_back(triangulated_face.pointIndex1);
          faces.push_back(triangulated_face.pointIndex2);
          faces.push_back(triangulated_face.pointIndex3);
        }

        OdTvGeometryDataId shellId = pTvEntity->appendShell(vertices.size(), vertices.asArrayPtr(), faces.size(), faces.asArrayPtr());

        tvMatMap.setProjection(OdTvMapperDef::kBox);

        //set normals to the shell
        OdTvShellDataPtr shellPtr = shellId.openAsShell();

        OdGeVector3dArray aNormals = pVerticesData->getNormals();
        const auto aUVMapping = pVerticesData->getTexCoords();
        if (aNormals.size() == vertices.size())
        {
          shellPtr->setVertexNormalsViaRange(0, (OdInt32)aNormals.size(), aNormals.getPtr());
          if (!aUVMapping.isEmpty())
            shellPtr->setVertexMappingCoordsViaRange(0, (OdInt32)aUVMapping.size(), aUVMapping.getPtr());
        }
        else
        {
          // TODO: Calculate normals by visualize or something else
          ;;
        }

        END_TV_NW_TIMER
      }
      else if (pNwGeom->isA() == OdNwGeometryPointSet::desc())
      {
        START_TV_NW_TIMER
          OdNwGeometryPointSetPtr pGeometryPointSet = pNwGeom;
          OdNwVerticesDataPtr pVerticesData = pGeometryPointSet->getVerticesData();
          ODA_ASSERT(!pVerticesData.isNull());
          OdGePoint3dArray vertices = pVerticesData->getVertices();
          auto ptCloudId = pTvEntity->appendPointCloud(vertices.size(), vertices.asArrayPtr());
        END_TV_NW_TIMER
      }
      else if (pNwGeom->isA() == OdNwGeometryText::desc())
      {
        START_TV_NW_TIMER
        OdNwGeometryTextPtr pGeometrText = pNwGeom;
        OdTvGeometryDataId textId =
          pTvEntity->appendText(pGeometrText->getLeftPoint(), pGeometrText->getText());
        OdTvTextDataPtr pText = textId.openAsText();
        if (!pText.isNull())
        {
          pText->setPosition(pGeometrText->getLeftPoint());
          pText->setRotation(pGeometrText->getRotation());
          pText->setNormal(pGeometrText->getNormal());
          OdNwObjectId nNwStyleId = pGeometrText->getTextStyleId();
          if (nNwStyleId.isValid())
          {
            OdNwTextStylePtr textStyleObj = nNwStyleId.safeOpenObject();

            pText->setWidthFactor(textStyleObj->getFontWeight()); 
            pText->setTextSize(textStyleObj->getFontHeight());

            OdTvTextStyleDef style;
            {
              // append new tv style id
              OdString textStyleIdString = OdString().format(OD_T("textStyle_%llu"), (OdUInt64) nNwStyleId.getHandle());
              OdTvResult rc = OdTvResult::tvOk;
              OdTvTextStyleId tvTextStyleId = pTvDb->findTextStyle(textStyleIdString);
              if (tvTextStyleId.isNull())
              {
                tvTextStyleId  = pTvDb->createTextStyle(textStyleIdString, &rc);
                ODA_ASSERT(OdTvResult::tvOk == rc);
                OdTvTextStylePtr pTvTextStyle = tvTextStyleId.openObject(OdTv::kForWrite);
                pTvTextStyle->setFont(textStyleObj->getTypeFace(), false, textStyleObj->getStyle(), 0, 34);
                pTvTextStyle->setTextSize(textStyleObj->getFontHeight());
                pTvTextStyle->setWidthFactor(textStyleObj->getFontWeight());
              }
              
              style.setTextStyle(tvTextStyleId);
            }

            pText->setTextStyle(style);
          }
        }
        else
        {
          ODA_ASSERT(false);
        }

        END_TV_NW_TIMER
      }
      else if (pNwGeom->isA() == OdNwGeometryTube::desc())
      {
        OdNwGeometryTubePtr pGeometryTube = pNwGeom;
        
        const double radius = pGeometryTube->getRadius();
        OdTvPointArray points; points.reserve(2);
        points.push_back(pGeometryTube->getTopCenter());
        points.push_back(pGeometryTube->getBottomCenter());

        OdTvGeometryDataId tvTubeId;
        if (OdEqual(radius, 0.0))
        {
          tvTubeId = pTvEntity->appendPointCloud(points);
        }
        else
        {
          OdDoubleArray radii; radii.resize(2);
          radii.setAll(radius);

          tvTubeId = pTvEntity->appendCylinder(points, radii, OdTvCylinderData::kNone);
        }
      }
      else if (pNwGeom->isA() == OdNwGeometryExternal::desc())
      {
        OdNwGeometryExternalPtr pGeometryExt = pNwGeom;
        OdGePoint3d topLeft = pGeometryExt->getTopLeft();
        OdGePoint3d bottomRight = pGeometryExt->getBottomRight();

      }
      else
      {
        ODA_ASSERT(false);
      }

      pTvEntity->setMaterialMapper(tvMatMap);
    };

    //VAS: adding tv insert object for case when model item has reused geometry
    auto addTvInsert = [&pTvDb, &pComp, &appendGeomDataToEntity, &getGeomReusedCount, &mmTvBlocks, &mNextBlockNames](const OdString& sTvEntName, std::function<OdTvEntityId(const OdTvBlockId&, const OdString&, const OdGeMatrix3d&)> appendInsert) -> OdTvEntityId
    {
      OdTvResult resCode = tvOk;
      //fragments from components
      OdNwObjectIdArray aCompFrags;
      if (pComp->getFragments(aCompFrags) != eOk)
        return OdTvEntityId();
      OdTvEntityId tvInsId;
      //fragments with reused geometry and equal transformation
      OdNwObjectIdArray aFragsForIns;

      if (aCompFrags.size() > 1)
      {
        //find all fragments with reused geometry and equal transformation
        std::pair<OdGeMatrix3d, bool> entTrf = { OdGeMatrix3d::kIdentity, false};
        bool isOneTrfForAll = true;
        for (auto& nwFragId : aCompFrags)
        {
          if (!nwFragId)
            continue;

          OdNwFragmentPtr pNwFrag = nwFragId.safeOpenObject();

          auto nwGeomId = pNwFrag->getGeometryId();
          //VAS: find if this geometry reused
          if (getGeomReusedCount(nwGeomId))
          {
            //VAS: check fragment transformation for equality so there can be possible to create block with data from those fragments, if not - create block with fragment with most frequency geometry
            if (entTrf.second)
            {
              if (!entTrf.first.isEqualTo(pNwFrag->getTransformation()))
                isOneTrfForAll = false;
            }
            else
              entTrf = { pNwFrag->getTransformation(),true};

            aFragsForIns.push_back(nwFragId);
          }
        }

        if (!isOneTrfForAll)
        {
          //VAS: if our transformation is not one for all - then find fragment with most frequency geometry
          std::pair<OdNwObjectId, OdUInt32> prNwFragWithFrequentGeom = { OdNwObjectId(), 0};
          for (auto& nwFragId : aFragsForIns)
          {
            OdNwFragmentPtr pNwFrag = nwFragId.safeOpenObject();

            auto nwGeomId = pNwFrag->getGeometryId();
            auto geomWithReusFrequency = getGeomReusedCount(nwGeomId);
            if (geomWithReusFrequency > prNwFragWithFrequentGeom.second)
              prNwFragWithFrequentGeom = { nwFragId, geomWithReusFrequency };
          }

          aFragsForIns.clear();
          aFragsForIns.push_back(prNwFragWithFrequentGeom.first);
        }
      }
      else
        aFragsForIns = aCompFrags;

      //VAS: in out nw2visualize we sum all name of node in branch for end nodes with delimeter ' -> ', for insert-block there will be good to divide last name for block(for correct display in cda tree, because visualize display in cda block-name for node)
      auto fndPos = sTvEntName.reverseFind('>');
      auto sInsName = fndPos != -1 ? sTvEntName.left(fndPos - 2) : sTvEntName;
      auto sBlckName = fndPos != -1 ? sTvEntName.right(sTvEntName.getLength() - fndPos - 2) : sTvEntName;

      {
        OdTvBlockId tvBlockId;

        //VAS: aFragsForIns always will be not empty, so get first element data in begin
        OdNwFragmentPtr pNwFrag = aFragsForIns[0].safeOpenObject();

        auto nwGeomId = pNwFrag->getGeometryId();
        //VAS: find all tv blocks which has data from this geometry, after that need to select such blocks that are reused with the same number of fragments as the current insert
        auto resFndBlocksWithRsdGeom = mmTvBlocks.equal_range(nwGeomId);
        for (auto bRng = resFndBlocksWithRsdGeom.first; bRng != resFndBlocksWithRsdGeom.second; ++bRng)
        {
          //VAS: need to check is there is already exist tv block for the geometries from fragments for current insert
          bool isTvBlockExist = true;
          for (auto& tempFrId : aFragsForIns)
          {
            OdNwFragmentPtr pNwTempFrag = tempFrId.safeOpenObject();
            OdNwObjectIdArray::size_type tempIdx;
            if (bRng->second.second.find(pNwTempFrag->getGeometryId(), tempIdx) != true)
            {
              isTvBlockExist = false;
              break;
            }
          }

          if (isTvBlockExist)
          {
            tvBlockId = bRng->second.first;
            break;
          }
        }

        if (tvBlockId.isNull())
        {
          //VAS: create new block for reused geometry
          tvBlockId = createTvDbUniqueObject<OdTvBlockId, &OdTvDatabase::findBlock, &OdTvDatabase::createBlock>(pTvDb, sBlckName, &mNextBlockNames);
          auto pTvBlock = tvBlockId.openObject(OdTv::kForWrite);
          auto tvBlockEntId = pTvBlock->appendEntity(sBlckName + OD_T("_Entity"), &resCode);
          if (resCode == tvOk)
          {
            auto pTvBlockEnt = tvBlockEntId.openObject(OdTv::kForWrite);
            appendGeomDataToEntity(nwGeomId, pTvBlockEnt);

            //VAS: set material data
            pTvBlockEnt->setColor(OdTvColorDef(OdTv::kByBlock));
            pTvBlockEnt->setMaterial(OdTvMaterialDef(OdTv::kByBlock));

            OdNwObjectIdArray aGeomArr;
            aGeomArr.push_back(nwGeomId);

            //VAS: if there more then one fragments for this block - need to add data from them to new block like subentities
            if (aFragsForIns.size() > 1)
            {
              for (OdNwObjectIdArray::size_type i = 1; i < aFragsForIns.size(); i++)
              {
                OdNwFragmentPtr pNwRsdFrag = aFragsForIns[i].safeOpenObject();
                auto nwRsdGeomId = pNwRsdFrag->getGeometryId();
                auto tvBlockEntId = pTvBlock->appendEntity(sBlckName + OdString().format(OD_T("_Entity%u"), i));
                appendGeomDataToEntity(nwRsdGeomId, tvBlockEntId.openObject(OdTv::kForWrite));

                //VAS: set material data
                auto pTvBlockEnt = tvBlockEntId.openObject(OdTv::kForWrite);
                pTvBlockEnt->setColor(OdTvColorDef(OdTv::kByBlock));
                pTvBlockEnt->setMaterial(OdTvMaterialDef(OdTv::kByBlock));

                aGeomArr.push_back(nwRsdGeomId);
              }
            }
            //add new element with pair block-reused geometries
            for (auto& geomId : aGeomArr)
              mmTvBlocks.insert({ geomId, { tvBlockId, aGeomArr } });
          }
        }

        //VAS: create new insert object
        tvInsId = appendInsert(tvBlockId, sInsName, pNwFrag->getTransformation());
      }

      //VAS: if size of aFragsForIns and aCompFrags is not eqaul - then need to add all data from other aCompFrags objects as subentities(entity traits) to insert
      if (aFragsForIns.size() != aCompFrags.size())
      {
        OdUInt32 subEntNum = 0;
        OdNwObjectIdArray::size_type tempIdx = 0;
        for (auto& nwFragId : aCompFrags)
        {
          if (!nwFragId)
            continue;

          if (aFragsForIns.find(nwFragId, tempIdx))
             continue;

          OdNwFragmentPtr pNwFrag = nwFragId.safeOpenObject();

          auto pTvIns = tvInsId.openObjectAsInsert(OdTv::kForWrite);
          OdTvEntityId entId = pTvIns->appendSubEntity(sInsName + OdString().format(OD_T("_SubEnt%u"), subEntNum++));
          OdTvEntityPtr pTvEntity = entId.openObject(OdTv::kForWrite);
          pTvEntity->setColor(OdTvColorDef(OdTv::kByBlock));
          pTvEntity->setMaterial(OdTvMaterialDef(OdTv::kByBlock));
          appendGeomDataToEntity(pNwFrag->getGeometryId(), entId.openObject(OdTv::kForWrite));
          OdGeMatrix3d trMat = pNwFrag->getTransformation();
          pTvEntity->setModelingMatrix(trMat);
        }
      }
      return tvInsId;
    };

    //VAS: adding tv entity object by model item data
    auto addTvEntity = [&pComp, &appendGeomDataToEntity](const OdString& sEntityName, std::function<OdTvEntityId(const OdString&)> appendEntity) -> OdTvEntityId
    {
      OdTvEntityId entId = appendEntity(sEntityName);
      OdTvEntityPtr pTvEntity = entId.openObject(OdTv::kForWrite);

      OdNwObjectIdArray aCompFrags;
      if (pComp->getFragments(aCompFrags) != eOk)
        return OdTvEntityId();

      //VAS: if model item contain more then one fragment - then need to check that all fragments has equal transforms, if not - need to append to this entity subentities with diferent transform in them
      bool divideBySebEnt = false;
      if (aCompFrags.size() > 1)
      {
        std::pair<OdGeMatrix3d, bool> isOneTrfForAll = { OdGeMatrix3d ::kIdentity, true};
        for (auto& nwFragId : aCompFrags)
        {
          if (!nwFragId)
            continue;
          
          OdNwFragmentPtr pNwFrag = nwFragId.safeOpenObject();
          if (isOneTrfForAll.second)
          {
            if (!isOneTrfForAll.first.isEqualTo(pNwFrag->getTransformation()))
            {
              //VAS: if our transform is not lord of transformation, then - "divide and rule"
              divideBySebEnt = true;
              break;
            }
          }
          else//set transform of first fragment as transform for checking
            isOneTrfForAll = { pNwFrag->getTransformation() , true};
        }
      }

      OdUInt32 subEntIdx = 0;
      for (auto& nwFragId : aCompFrags)
      {
        if (!nwFragId)
          continue;

        OdNwFragmentPtr pNwFrag = nwFragId.safeOpenObject();
        OdTvMatrix trMat = pNwFrag->getTransformation();

        if (divideBySebEnt)
        {
          auto tvSubEntId = pTvEntity->appendSubEntity(OdString().format(OD_T("NwSubEntity_%u"), subEntIdx++));
          tvSubEntId.openAsSubEntity(OdTv::kForWrite)->setModelingMatrix(trMat);
          appendGeomDataToEntity(pNwFrag->getGeometryId(), tvSubEntId.openAsSubEntity(OdTv::kForWrite));
        }
        else
        {
          pTvEntity->setModelingMatrix(trMat);
          appendGeomDataToEntity(pNwFrag->getGeometryId(), entId.openObject(OdTv::kForWrite));
        }
      }
      return entId;
    };

    OdTvLayerDef tvLrDef;
    if (!std::get<1>(pHasGeomNode).isNull())
      tvLrDef = OdTvLayerDef(std::get<1>(pHasGeomNode));
    OdTvVisibilityDef tvVisDef = std::get<2>(pHasGeomNode) ? OdTvVisibilityDef::kInvisible : OdTvVisibilityDef::kVisible;

    OdTvEntityId addedEntityId;
    //VAS: if pHasGeomNode has fragments with reused geometry - then need to add data in insert, otherwise - append data in tv entity
    if (std::find_if(std::get<3>(pHasGeomNode).begin(), std::get<3>(pHasGeomNode).end(), [](OdUInt32* pCounter) { return *pCounter > 1; }) != std::get<3>(pHasGeomNode).end())
    {
      addedEntityId =
        addTvInsert(std::get<4>(pHasGeomNode), [this, &pTvModel, &pHasGeomNode, &regAppId, &tvLrDef, &tvVisDef, &tvEntClr, &tvMatId](const OdTvBlockId& tvBlockId, const OdString& sInsName, const OdGeMatrix3d& trf)
                                             {
                                               OdTvResult resCode = tvOk;
                                               //VAS: create new insert object
                                               auto tvInsId = pTvModel->appendInsert(tvBlockId, sInsName, &resCode);
                                               auto pTvIns = tvInsId.openObjectAsInsert(OdTv::kForWrite);

                                               // Add native handle to user data
                                               if (m_properties->getNeedCDATree() || m_properties->getStoreSourceObjects())
                                               {
                                                 OdUInt64 uinic_ID = std::get<0>(pHasGeomNode)->objectId().getHandle();
                                                 OdTvByteUserData* data = new OdTvByteUserData(&uinic_ID, sizeof(OdUInt64), OdTvByteUserData::kCopyOwn, true);
                                                 pTvIns->appendUserData(data, regAppId);
                                               }

                                               pTvIns->setLayer(tvLrDef);
                                               pTvIns->setVisibility(tvVisDef);
                                               pTvIns->setBlockTransform(trf);
                                               pTvIns->setColor(tvEntClr);
                                               pTvIns->setMaterial(tvMatId);

                                               return tvInsId;
                                             });
    }
    else
    {
      addedEntityId =
        addTvEntity(std::get<4>(pHasGeomNode), [this, &pTvModel, &pHasGeomNode, &regAppId, &tvLrDef, &tvVisDef, &tvEntClr, &tvMatId](const OdString& sEntityName)
                                             {
                                               OdTvEntityId entId = pTvModel->appendEntity(sEntityName);
                                               OdTvEntityPtr pTvEntity = entId.openObject(OdTv::kForWrite);
                                               pTvEntity->setLayer(tvLrDef);
                                               pTvEntity->setVisibility(tvVisDef);

                                               // Add native handle to user data
                                               if (m_properties->getNeedCDATree() || m_properties->getStoreSourceObjects())
                                               {
                                                 OdUInt64 uinic_ID = std::get<0>(pHasGeomNode)->objectId().getHandle();
                                                 OdTvByteUserData* data = new OdTvByteUserData(&uinic_ID, sizeof(OdUInt64), OdTvByteUserData::kCopyOwn, true);
                                                 pTvEntity->appendUserData(data, regAppId);
                                               }

                                               pTvEntity->setColor(tvEntClr);
                                               pTvEntity->setMaterial(tvMatId);

                                               return entId;
                                             });
    }
    oid2tvent[std::get<0>(pHasGeomNode)->objectId()] = addedEntityId;
  }

  std::function<std::vector<OdTvEntityId>(OdNwObjectIdArray nwIds)> getTvByNw = [&getTvByNw, &oid2tvent](OdNwObjectIdArray nwIds) -> std::vector<OdTvEntityId>
  {
    std::vector<OdTvEntityId> result;

    for (auto& item : nwIds)
    {
      OdNwModelItemPtr modelItem = item.safeOpenObject();
      if (modelItem->hasGeometry())
      {
        result.push_back(oid2tvent[item]);
      }
      else
      {
        OdNwObjectIdArray children;
        modelItem->getChildren(children);
        std::vector<OdTvEntityId> tvByNw = getTvByNw(children);
        result.insert(result.end(), tvByNw.begin(), tvByNw.end());
      }
    }
    return result;
  };
  // At the begining the map nwId2TvIds consits only keys that are modelId's
  for (auto & mid : nwId2TvIds)
  {
    OdNwObjectIdArray a;
    a.push_back(mid.first); // making array with only one element
    std::vector<OdTvEntityId> animSelectTvIds = getTvByNw(a);
    nwId2TvIds[mid.first] = animSelectTvIds;
  }
}

OdTvGsViewBackgroundId OdTvVisualizeNwFiler::setupBackground(const OdNwObjectId& nwBackGroundId, OdTvDatabasePtr pTvDb) const
{
  OdTvGsViewBackgroundId tvBckId;

  if (nwBackGroundId)
  {
    OdNwBackgroundElementPtr pNwBackGround = nwBackGroundId.safeOpenObject();

    switch(pNwBackGround->getBackgroundType())
    {
      case NwBackgroundType::HORIZON:
      {
        tvBckId = pTvDb->createBackground(OD_T("HorizonColor"), OdTvGsViewBackgroundId::kGradient);
        if (!tvBckId.isNull())
        {
          OdTvGsViewGradientBackgroundPtr pGradientBackground = tvBckId.openAsGradientBackground(OdTv::kForWrite);
          OdNwColor skyColor, skyHorizonColor, groundColor, groundHorizonColor;
          pNwBackGround->getHorizonColor(skyColor, skyHorizonColor, groundHorizonColor, groundColor);
    
          pGradientBackground->setColorTop(OdTvColorDef(ODGETRED(skyColor.ToColor()), ODGETGREEN(skyColor.ToColor()), ODGETBLUE(skyColor.ToColor())));
          pGradientBackground->setColorMiddle(OdTvColorDef(ODGETRED(groundHorizonColor.ToColor()), ODGETGREEN(groundHorizonColor.ToColor()), ODGETBLUE(groundHorizonColor.ToColor())));
          pGradientBackground->setColorBottom(OdTvColorDef(ODGETRED(groundColor.ToColor()), ODGETGREEN(groundColor.ToColor()), ODGETBLUE(groundColor.ToColor())));
          pGradientBackground->setHeight(0.33);
          pGradientBackground->setHorizon(0.5);
        }
        break;
      }
      case NwBackgroundType::GRADUATED:
      {
        tvBckId = pTvDb->createBackground(OD_T("GraduatedColor"), OdTvGsViewBackgroundId::kGradient);
        if (!tvBckId.isNull())
        {
          OdTvGsViewGradientBackgroundPtr pGradientBackground = tvBckId.openAsGradientBackground(OdTv::kForWrite);
          OdNwColor topColor, bottomColor, plainColor;
          pNwBackGround->getGraduatedColor(topColor, bottomColor);
          pNwBackGround->getPlainColor(plainColor);
    
          pGradientBackground->setColorTop(OdTvColorDef(ODGETRED(topColor.ToColor()), ODGETGREEN(topColor.ToColor()), ODGETBLUE(topColor.ToColor())));
          pGradientBackground->setColorMiddle(OdTvColorDef(ODGETRED(plainColor.ToColor()), ODGETGREEN(plainColor.ToColor()), ODGETBLUE(plainColor.ToColor())));
          pGradientBackground->setColorBottom(OdTvColorDef(ODGETRED(bottomColor.ToColor()), ODGETGREEN(bottomColor.ToColor()), ODGETBLUE(bottomColor.ToColor())));
          pGradientBackground->setHeight(0.33);
          pGradientBackground->setHorizon(0.5);
        }
        break;
      }
      case NwBackgroundType::PLAIN:
      {
        tvBckId = pTvDb->createBackground(OD_T("PlainColor"), OdTvGsViewBackgroundId::kSolid);
        if (!tvBckId.isNull())
        {
          OdTvGsViewSolidBackgroundPtr pGradientBackground = tvBckId.openAsSolidBackground(OdTv::kForWrite);
          OdNwColor plainColor;
          pNwBackGround->getPlainColor(plainColor);
    
          pGradientBackground->setColorSolid(OdTvColorDef(ODGETRED(plainColor.ToColor()), ODGETGREEN(plainColor.ToColor()), ODGETBLUE(plainColor.ToColor())));
        }
        break;
      }
      default:
        break;
    }
  }

  return tvBckId;
}

OdTvGsViewId OdTvVisualizeNwFiler::setupCurrentView(const OdNwObjectId& nwCurViewId, const OdTvGsDeviceId& tvDeviceId, const OdTvModelId& tvModelId, const OdTvGsViewBackgroundId& backgroundId) const
{
  OdTvGsDevicePtr pTvDevice = tvDeviceId.openObject(OdTv::kForWrite);

  if (!nwCurViewId)
  {
    OdTvGsViewId tvViewId = pTvDevice->createView(OD_T("View_NW"));
    pTvDevice->addView(tvViewId);

    //setup view
    OdTvGsViewPtr pView = tvViewId.openObject(OdTv::kForWrite);
    if (!tvModelId.isNull())
      pView->addModel(tvModelId);

    pView->setMode(OdTvGsView::kGouraudShaded);
    pView->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);
    pView->setActive(true);

    // since the GS is not setup yet,we can call empty zoomtoextens to mark the view.
    // The action will be performed inside first setupGs
    OdTvPoint minPt, maxPt;
    pView->zoomExtents(minPt, maxPt);
    return tvViewId;
  }

  OdTvGsDevicePtr devicePtr = tvDeviceId.openObject();
  OdNwViewpointPtr pNwCurView = nwCurViewId.safeOpenObject();
  OdString sName = devicePtr->getName();

  OdTvGsViewId tvViewId = pTvDevice->createView(sName.isEmpty() ? OdString(OD_T("View_NW")) : sName);
  pTvDevice->addView(tvViewId);

  //setup view
  OdTvGsViewPtr pView = tvViewId.openObject(OdTv::kForWrite);
  if (!tvModelId.isNull())
    pView->addModel(tvModelId);

  OdTvDatabaseId tvDbId = pTvDevice->getDatabase();
  OdTvVisualStyleId visId;
  OdTvGsView::RenderMode tvRenderMode = OdTvGsView::k2DOptimized;
  switch (pNwCurView->getRenderStyle())
  {
  case NwModeType::FULL_RENDER:
    visId = tvDbId.openObject()->findVisualStyle(OD_T("Realistic"));
    tvRenderMode = OdTvGsView::kGouraudShaded;
    break;
  case NwModeType::SHADED:
    visId = tvDbId.openObject()->findVisualStyle(OD_T("Shaded"));
    tvRenderMode = OdTvGsView::kGouraudShaded;
    break;
  case NwModeType::WIREFRAME:
    visId = tvDbId.openObject()->findVisualStyle(OD_T("Wireframe"));
    tvRenderMode = OdTvGsView::kWireframe;
    break;
  case NwModeType::HIDDEN_LINE:
    visId = tvDbId.openObject()->findVisualStyle(OD_T("Hidden"));
    tvRenderMode = OdTvGsView::kHiddenLine;
    break;
  }
  pView->setMode(tvRenderMode);

  if (!visId.isNull())
    pView->setVisualStyle(visId);

  // calculate target point
  OdGeMatrix3d matrix = pNwCurView->getRotation().getMatrix();

  OdGeVector3d targetVector = OdGeVector3d::kZAxis;
  targetVector.transformBy(matrix);

  // there are files with zero focaldistance 
  if (pNwCurView->hasFocalDistance())
    targetVector *= pNwCurView->getFocalDistance();

  OdGePoint3d targetPoint = (pNwCurView->getPosition() - targetVector);

  double fieldWidth = 1.;
  double fieldHeight = 1.;
  OdTvGsView::Projection tvProjection = OdTvGsView::kParallel;

  switch (pNwCurView->getProjection())
  {
    case NwViewType::PERSPECTIVE:
    {
      tvProjection = OdTvGsView::kPerspective;

      double focalLen = pNwCurView->hasFocalDistance() ? pNwCurView->getFocalDistance() : 1;

      fieldWidth = std::tan(pNwCurView->getHeightField()/2)  * 2 * focalLen * pNwCurView->getViewAspect();
      fieldHeight = std::tan(pNwCurView->getHeightField() / 2) * 2 *focalLen;
      break;
    }
    case NwViewType::ORTHOGRAPHIC:
    {
      tvProjection = OdTvGsView::kParallel;
      fieldWidth = pNwCurView->getHeightField() * pNwCurView->getViewAspect();
      fieldHeight = pNwCurView->getHeightField();
      break;
    }
  }

  pView->setAdjustLensLength(true);
  pView->setView(pNwCurView->getPosition(), targetPoint, pNwCurView->getWorldUpVector(), fieldHeight, fieldWidth, tvProjection);
  pView->setActive(true);
  pView->setDefaultLightingIntensity(1.);
  if (!backgroundId.isNull())
    pView->setBackground(backgroundId);

  return tvViewId;
}

void OdTvVisualizeNwFiler::setupLights(const OdTvModelId& tvModelId, const OdNwObjectIdArray& aNwLights) const
{
  for (OdUInt32 i = 0; i < aNwLights.size(); ++i)
  {
    if (!aNwLights[i])
      continue;
    OdNwCommonLightPtr pLight = aNwLights[i].safeOpenObject();
    if (pLight.isNull())
      continue;
    OdString sName = pLight->getName();
    OdTvModelPtr pModel = tvModelId.openObject(OdTv::kForWrite);
    OdTvEntityId tvLightId = pModel->appendLight(sName.isEmpty() ? OdString().format(OD_T("Light_%d"), i) : sName);
    OdTvLightPtr pTvLight = tvLightId.openObjectAsLight(OdTv::kForWrite);
    pTvLight->setOn(pLight->isLightOn());
    {
      if (pLight->getValue(NwLightValueType::light_filter_color).type() == OdNwVariant::kColor)
        pTvLight->setLightColor(pLight->getDiffuse().Multiply(pLight->getValue(NwLightValueType::light_filter_color).getColor()).ToColor());
      else
        pTvLight->setLightColor(pLight->getDiffuse().ToColor());
      pTvLight->setIntensity(pLight->getValue(NwLightValueType::light_intensity_value).getDouble());
    }
    if (pLight->isKindOf(OdNwDistantLight::desc()))
    {
      OdNwDistantLightPtr pDistLight = pLight;
      pTvLight->setLightType(OdTvLight::kDistantLight);
      pTvLight->setLightDirection(pDistLight->getDirection());
    }
    else if (pLight->isKindOf(OdNwPointLight::desc()))
    {
      OdNwPointLightPtr pPointLight = pLight;
      pTvLight->setLightType(OdTvLight::kPointLight);
      pTvLight->setPosition(pPointLight->getPosition());
    }
    else if (pLight->isKindOf(OdNwSpotLight::desc()))
    {
      OdNwSpotLightPtr pSpotLight = pLight;
      pTvLight->setLightType(OdTvLight::kSpotLight);
      pTvLight->setPosition(pSpotLight->getPosition());
      pTvLight->setLightDirection(pSpotLight->getDirection());
      pTvLight->setHotspotAndFalloff(pSpotLight->getDropoffRate(), pSpotLight->getCutoffAngle());
    }
  }
}

OdTvDatabaseId OdTvVisualizeNwFiler::generate(OdTvFilerTimeProfiling* pProfileRes) const
{
  OdTvDatabaseId tvDbId;

  // does nothing
  return tvDbId;
}

OdTvModelId OdTvVisualizeNwFiler::appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeNwFilerSourceFromFile dl(filePath, pProfileRes);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeNwFiler::appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeNwFilerSourceFromBuffer dl(pBuffer, pProfileRes);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvModelId OdTvVisualizeNwFiler::appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc) const
{
  OdTvVisualizeNwFilerSourceFromDb dl(pDatabase);
  return appendFrom(databaseId, &dl, pProfileRes, rc);
}

OdTvResult OdTvVisualizeNwFiler::startActionsWithNativeProperties(const OdString& sFilePath, bool bPartial)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() != sFilePath)
    m_pDatabaseForNativeProp.release();
  else if (!m_pDatabaseForNativeProp.isNull())
    return tvOk;

  OdTvResult rc = tvOk;
  const_cast<OdTvVisualizeNwFiler*>(this)->m_pDl = new OdTvVisualizeNwFilerSourceFromFile(sFilePath, NULL);

  {
    if (m_pRxPropertiesModule.isNull())
      m_pRxPropertiesModule = ::odrxDynamicLinker()->loadModule(L"RxProperties");

    if (m_pNwPropertiesModule.isNull())
      m_pNwPropertiesModule = ::odrxDynamicLinker()->loadModule(L"NwProperties");

    if (m_pNwDatabaseModule.isNull())
      m_pNwDatabaseModule = ::odrxDynamicLinker()->loadModule(OdNwDbModuleName);
    
    try
    {
      m_pDatabaseForNativeProp = m_pDl->getDb();
    }
    catch (...)
    {
      return tvFilerEmptyInternalDatabase;
    }

  }

  return rc;
}

bool OdTvVisualizeNwFiler::isActionsWithNativePropertiesStarted(const OdString& sFilePath)
{
  if (!m_pDatabaseForNativeProp.isNull() && m_pDatabaseForNativeProp->getFilename() == sFilePath)
    return true;

  return false;
}

OdTvResult OdTvVisualizeNwFiler::endActionsWithNativeProperties()
{
  if (!m_pDatabaseForNativeProp.isNull())
    m_pDatabaseForNativeProp.release();

  if (!m_pNwPropertiesModule.isNull())
  {
    m_pRxPropertiesModule.release();
    m_pNwPropertiesModule.release();
    m_pNwDatabaseModule.release();
    ::odrxDynamicLinker()->unloadModule(L"RxProperties");
    ::odrxDynamicLinker()->unloadModule(L"NwProperties");
    ::odrxDynamicLinker()->unloadModule(OdNwDbModuleName);
    ::odrxDynamicLinker()->unloadUnreferenced();

    if (m_pDl)
    {
      delete m_pDl;
      m_pDl = NULL;
    }
  }

  return tvOk;
}

OdRxMemberIteratorPtr OdTvVisualizeNwFiler::getNativePropertiesIterator(OdUInt64 dbHandle, OdTvResult* rc)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxMemberIteratorPtr();
  }

  OdRxMemberIteratorPtr pIter;
  if (dbHandle == 0)
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(m_pDatabaseForNativeProp);
  else
  {
    OdNwObjectId objectId = m_pDatabaseForNativeProp->getObjectId(dbHandle);
    if (objectId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxMemberIteratorPtr();
    }
    pIter = OdRxMemberQueryEngine::theEngine()->newMemberIterator(objectId.openObject());
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
OdRxValue OdTvVisualizeNwFiler::getNativePropertyValue(OdUInt64 dbHandle, const OdRxPropertyPtr& pProperty, bool* bReadOnly, OdTvResult* rc)
{
  if (pProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValue();
  }

  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValue();
  }

  OdRxObjectPtr pElement;
  if (dbHandle == 0)
    pElement = m_pDatabaseForNativeProp;
  else
  {
    OdNwObjectId objectId = m_pDatabaseForNativeProp->getObjectId(dbHandle);
    pElement = objectId.openObject();
  }

  if (pElement.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedObject;
    return OdRxValue();
  }

  OdRxValue value;
  OdResult odRes = pProperty->getValue(pElement, value);
  if (bReadOnly)
    *bReadOnly = pProperty->isReadOnly(pElement);

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
OdRxValueIteratorPtr OdTvVisualizeNwFiler::getNativeCollectionPropertyIterator(OdUInt64 dbHandle, const OdRxCollectionPropertyPtr& pCollectionProperty, bool* bReadOnly, OdTvResult* rc)
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return OdRxValueIteratorPtr();
  }

  if (pCollectionProperty.isNull())
  {
    if (rc)
      *rc = tvInvalidInput;
    return OdRxValueIteratorPtr();
  }

  OdRxValueIteratorPtr pValIter;
  if (dbHandle == 0)
  {
    pValIter = pCollectionProperty->newValueIterator(m_pDatabaseForNativeProp);

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(m_pDatabaseForNativeProp);
  }
  else
  {
    OdNwObjectId objectId = m_pDatabaseForNativeProp->getObjectId(dbHandle);
    if (objectId.isNull())
    {
      if (rc)
        *rc = tvNativePropMissedObject;
      return OdRxValueIteratorPtr();
    }
    pValIter = pCollectionProperty->newValueIterator(objectId.openObject());

    if (bReadOnly)
      *bReadOnly = pCollectionProperty->isReadOnly(objectId.openObject());
  }


  if (rc)
    *rc = tvOk;

  return pValIter;
}

OdTvResult OdTvVisualizeNwFiler::setNativePropertyValue(OdUInt64 dbHandle, OdRxPropertyPtr& pProperty, const OdRxValue& value)
{
  if (pProperty.isNull())
    return tvInvalidInput;

  if (m_pDatabaseForNativeProp.isNull())
    return tvNativePropMissedDatabase;

  OdRxObjectPtr pElement;
  if (dbHandle == 0)
    pElement = m_pDatabaseForNativeProp;
  else
  {
    OdNwObjectId objectId = m_pDatabaseForNativeProp->getObjectId(dbHandle);
    pElement = objectId.openObject();
  }

  if (pElement.isNull())
    return tvNativePropMissedObject;

  pProperty->setValue(pElement, value);

  return tvOk;
}

OdDbBaseDatabase* OdTvVisualizeNwFiler::getNativeDatabase(OdTvResult* rc) const
{
  if (m_pDatabaseForNativeProp.isNull())
  {
    if (rc)
      *rc = tvNativePropMissedDatabase;
    return NULL;
  }

  return (OdDbBaseDatabase*)m_pDatabaseForNativeProp.get();
}

void OdTvVisualizeNwFiler::createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, const OdTvModelId& modelId) const
{
  ::odrxDynamicLinker()->loadModule(L"NwProperties");

  //Create CDA tree
  OdTvCDATreePtr pTree = OdTvCDATree::createObject();
  pTree->createDatabaseHierarchyTree(pDatabase, m_properties->getNeedCollectPropertiesInCDA());

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
  if (!modelId.isNull())
  {
    OdTvModelPtr pModel = modelId.openObject();
    pModel->setCDATreeStorage(cdaTreeId);

    OdTvCDATreeNodePtr pTvNode = pTree->getDatabaseNode();
    if (!pTvNode.isNull())
    {
      const OdRxModelTreeBaseNodePtrArray nodes = pTvNode->getChildren();
      for (OdRxModelTreeBaseNodePtrArray::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
      {
        OdTvCDATreeNodePtr pNode = *it;
        if (pNode.isNull())
          continue;
        pNode->setTvModelId(modelId);
      }
    }
  }

  //mark all nodes that it is not need group nodes
  OdRxModelTreeBaseNodePtr pDbNode = pTree->getDatabaseNode();
  if (!pDbNode.isNull())
    OdTvDatabaseUtils::markCDANode(pDbNode.get());

  ::odrxDynamicLinker()->unloadModule(L"NwProperties");
}

OdTvDatabaseId OdTvVisualizeNwFiler::importFile(const LoadNwOptions& opt, OdTvFilerTimeProfiling* pProfileRes /*= NULL*/, OdTvResult* rc /*= NULL*/) const
{
  if (rc)
    *rc = tvOk;

  //
  // prepare Nw Importer timing object
  //
  OdTvFilerTimer timing(NULL != pProfileRes);
  timing.startTotal();

  // load Nw database
  OdStaticRxObject<OdTvNw2VisService> svcs;

  OdRxModulePtr pBimNvModule;
  try
  {
    pBimNvModule = ::odrxDynamicLinker()->loadModule(OdNwDbModuleName, false);
  }
  catch (...)
  {
    if (rc)
      *rc = tvInternal;

    timing.endTotal();
  }

  OdNwDatabasePtr pNwDb;

  switch (opt.m_type)
  {
  case LoadNwOptions::kFilePath:
  {
    OdString textureFolder = GetRegistryADSKLocation(OdNw::RegistryADSKLocation::TextureLibrary);
    if (0 == textureFolder.iCompare(L"/") || 0 == textureFolder.iCompare(L"\\")) // if no assets in windows or it is unix
      textureFolder = nwExtractFileDir(opt.m_filePath) + OD_T("/");
    svcs.setTextureDirectoryPath(textureFolder, false);
    pNwDb = svcs.readFile(opt.m_filePath);
    break;
  }
  case LoadNwOptions::kDatabase:
    pNwDb = OdNwDatabase::cast(opt.m_pDatabase);
    break;
  case LoadNwOptions::kBuffer:
    pNwDb = svcs.readFile(opt.m_pBuffer);
    break;
  }

  if (pNwDb.isNull())
  {
    if (rc)
      *rc = tvFilerEmptyInternalDatabase;

    timing.endTotal();
    return OdTvDatabaseId();
  }

  // create tv database
  OdTvFactoryId tvFactoryId = odTvGetFactory();
  OdTvDatabaseId tvDbId = tvFactoryId.createDatabase();

  OdNwObjectIdArray aSheets;
  OdResult resSheet = pNwDb->getSheets(aSheets);
  ODA_ASSERT(resSheet == eOk);

  OdTvFilerFeedbackForChooseObject filerFeedbackForChooseObject(OD_T("Choose sheets for import"));
  OdTvFilerFeedbackItemForChooseArray* pFilerFeedbackForChooseArray = filerFeedbackForChooseObject.getFilerFeedbackItemForChooseArrayPtr();

  for (auto sheetId : aSheets)
  {
    if (!sheetId)
      continue;

    OdString sSheetName = OdNwSheetInfo::cast(sheetId.safeOpenObject())->getDisplayName();
    OdTvFilerFeedbackItemForChoose filerFeedbackForChoose(sSheetName);
    filerFeedbackForChoose.m_bChosen = true;
    pFilerFeedbackForChooseArray->append(filerFeedbackForChoose);
  }
  timing.endTotal();
  double nTotal = timing.getTotalTime();

  if (m_properties->getFeedbackForChooseCallback() != NULL && aSheets.size() > 1)
  {
    ((OdTvFeedbackForChooseCallback)m_properties->getFeedbackForChooseCallback())(filerFeedbackForChooseObject);
    if (filerFeedbackForChooseObject.getFilerFeedbackItemForChooseArrayPtr()->length() == 0)
    {
      pBimNvModule.release();
      ::odrxDynamicLinker()->unloadModule(OdNwDbModuleName);
      timing.endTotal();
      return tvDbId;
    }

    timing.startTotal();
    timing.startVectorizing();

    for (auto sheetId : aSheets)
    {
      if (!sheetId)
        continue;

      OdNwSheetInfoPtr pNwSheetInfo = sheetId.safeOpenObject();

      if (!filerFeedbackForChooseObject.find(OdTvFilerFeedbackItemForChoose(pNwSheetInfo->getDisplayName(), true)))
        continue;

      OdString sSheetName = pNwSheetInfo->getSheetId();
      pNwDb->setActiveSheet(sSheetName);
      pNwDb->isComposite()
        ? loadNwf(tvDbId, pNwDb, timing, pProfileRes)
        : loadNwd(tvDbId, pNwDb, timing, pProfileRes);
    }
    timing.endVectorizing();

  }
  else
  {
    timing.startTotal();
    // load all sheets
    timing.startVectorizing();
    for (auto sheetId : aSheets)
    {
      if (!sheetId)
        continue;

      OdNwSheetInfoPtr pNwSheetInfo = sheetId.safeOpenObject();

      OdString sSheetName = pNwSheetInfo->getSheetId();
      pNwDb->setActiveSheet(sSheetName);
      pNwDb->isComposite()
        ? loadNwf(tvDbId, pNwDb, timing, pProfileRes)
        : loadNwd(tvDbId, pNwDb, timing, pProfileRes);
    }
    timing.endVectorizing();
  }

  timing.endTotal();
  nTotal += timing.getTotalTime();

  if (pProfileRes)
  {
    OdInt64 iReadTime = pProfileRes->getImportTime();
    pProfileRes->setImportTime(iReadTime + OdInt64((nTotal - timing.getVectorizingTime()) * 1000.));
    pProfileRes->setVectorizingTime(OdInt64((timing.getVectorizingTime()) * 1000.) - pProfileRes->getCDATreeCreationTime() - pProfileRes->getTvTime() - iReadTime);
  }

  pNwDb = NULL;
  pBimNvModule.release();
  ::odrxDynamicLinker()->unloadModule(OdNwDbModuleName);
  //here we will unload all including Visualize device
  odrxDynamicLinker()->unloadUnreferenced();

  return tvDbId;

}

void OdTvVisualizeNwFiler::setupGrid(OdNwDatabasePtr pNwDb, OdTvDatabaseId tvDbId, OdTvGsViewId viewId) const
{
  OdNwGridSystemElementPtr grsysel = pNwDb->getGridSystemElement();
  if (grsysel.isNull())
    return;

  OdArray<OdNwGridSystemPtr> grsysList;
  if (grsysel->getGridSystemList(grsysList) != eOk)
  {
    return;
  }
  OdTvGsViewPtr pTvView = viewId.openObject(OdTv::OpenMode::kForWrite);
  OdTvResult gridModelRes;
  OdTvModelId tvModelId = tvDbId.openObject(OdTv::kForWrite)->createModel("grid", OdTvModel::Type::kMain, false, &gridModelRes);
  if (gridModelRes != tvOk)
  {
    return;
  }
  OdTvModelPtr pTvModel = tvModelId.openObject(OdTv::OpenMode::kForWrite);

  pTvView->addModel(tvModelId);
  struct gridLineType {
    OdGePoint3d a, b, c;
    NwGridLineSegmentType::Enum type;
    OdString caption;
  };
  typedef std::vector<gridLineType> gridType;
  struct gridLevelType {
    OdGePoint3d level;
    OdString name;
    gridType grid;
  };

  typedef std::vector<gridLevelType> drawDatagridLevelListType;
  drawDatagridLevelListType drawDataGridLevelList;

  OdTvResult textStyleRes;
  OdTvTextStyleId tvTextStyleId = tvDbId.openObject(OdTv::kForWrite)->createTextStyle(OD_T("gridTextStyle"), &textStyleRes);
  if (textStyleRes != tvOk)
  {
    return;
  }
  OdTvTextStylePtr pTvTextStyle = tvTextStyleId.openObject(OdTv::kForWrite);

  OdString typeface = L"Algerian";
  OdInt16 charset = 0;
  OdInt16 family = 34;
  bool bold = false;
  bool italic = false;
  pTvTextStyle->setFont(typeface, bold, italic, charset, family);
  pTvTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
  pTvTextStyle->setTextSize(2.5);

  OdTvResult titleEntityRes;
  OdTvEntityId tvTitleId = pTvModel->appendEntity(OD_T("Title"), &titleEntityRes);
  if (titleEntityRes != eOk)
  {
    return;
  }
  OdTvEntityPtr pTvTitle = tvTitleId.openObject(OdTv::kForWrite);
  pTvTitle->setColor(OdTvColorDef(255, 255, 255));
  pTvTitle->setTextStyle(tvTextStyleId);
  pTvTitle->setAutoRegen(true);

  for (int i = 0; i < grsysList.size(); i++)
  {
    gridType grid;
    OdArray<OdNwGridLinePtr> gridLineList;
    if (grsysList[i]->getGridLineList(gridLineList) != eOk)
    {
      continue;
    }
    for (int j = 0; j < gridLineList.size(); ++j)
    {
      gridLineType gridLine;
      gridLine.caption = gridLineList[j]->getName();
      
      OdArray<OdNwGridLineSegmentPtr> gridLineSegList;
      if (gridLineList[j]->getGridLineSegmentList(gridLineSegList) != eOk)
      {
        continue;
      }
      for (int k = 0; k < gridLineSegList.size(); k++)
      {
        gridLine.type = gridLineSegList[k]->getType();
        if (gridLineSegList[k]->getType() == NwGridLineSegmentType::Enum::LINE)
        {
          OdGePoint2dArray pl = gridLineSegList[k]->getPrimPointList();
          gridLine.a = OdGePoint3d(pl[0].x, pl[0].y, 0);
          gridLine.b = OdGePoint3d(pl[1].x, pl[1].y, 0);
        }
        else if (gridLineSegList[k]->getType() == NwGridLineSegmentType::Enum::CIRCLE)
        {
          OdGePoint2dArray pl = gridLineSegList[k]->getPrimPointList();
          gridLine.a = OdGePoint3d(pl[2].x, pl[2].y, 0);
          gridLine.b = OdGePoint3d(pl[1].x, pl[1].y, 0);
          gridLine.c = OdGePoint3d(pl[0].x, pl[0].y, 0);
        }
        grid.push_back(gridLine);
      }
    }

    OdArray<OdNwGridLevelPtr> gridLevelList;
    if (grsysList[i]->getGridLevelList(gridLevelList) != eOk)
    {
      continue;
    }

    for (int m = 0; m < gridLevelList.size(); ++m)
    {
      OdTvResult gridLevelEntityRes;
      OdTvEntityId tvGridLevelEntityId = tvModelId.openObject(OdTv::kForWrite)->appendEntity(gridLevelList[m]->getName(), &gridLevelEntityRes);
      if (gridLevelEntityRes != tvOk)
      {
        continue;
      }
      auto pTvGridLevelEntity = tvGridLevelEntityId.openObject(OdTv::OpenMode::kForWrite);
      pTvGridLevelEntity->setColor(OdTvColorDef(255, 0, 0), OdTvGeometryData::kAll);
      for (auto & l : grid)
      {
        if (l.type == NwGridLineSegmentType::Enum::LINE)
        {
          l.a.z = gridLevelList[m]->getLevel();
          l.b.z = gridLevelList[m]->getLevel();
          pTvGridLevelEntity->appendPolyline(l.a, l.b);
          OdTvResult captionTextRes;
          OdTvGeometryDataId captBeg = pTvTitle->appendText(l.a, l.caption, &captionTextRes);
          if (captionTextRes != tvOk)
          {
            continue;
          }
          OdTvTextDataPtr textPtr = captBeg.openAsText();
          textPtr->setNonRotatable(true);

          OdTvGeometryDataId tvCaptEnd = pTvTitle->appendText(l.b, l.caption, &captionTextRes);
          if (captionTextRes != tvOk)
          {
            continue;
          }
          tvCaptEnd.openAsText()->setNonRotatable(true);
        }
        else if (l.type == NwGridLineSegmentType::Enum::CIRCLE)
        {
          l.a.z = gridLevelList[m]->getLevel();
          l.b.z = gridLevelList[m]->getLevel();
          l.c.z = gridLevelList[m]->getLevel();
          double r = std::sqrt(std::pow(l.a.x - l.c.x, 2) + std::pow(l.a.y - l.c.y, 2));
          double xb0a = (l.a.x - l.c.x) / r;

          double anga = OD_ACOS(xb0a);

          double anga_deg = OdaToDegree(anga);
          double angn = OdaToRadian(anga_deg - 5);
          double xn = r * cos(angn) + l.c.x;
          double yn = r * sin(angn) + l.c.y;

          OdTvPoint startPoint(l.a.x, l.a.y, gridLevelList[m]->getLevel());
          OdTvPoint middlePoint(xn, yn, gridLevelList[m]->getLevel());
          OdTvPoint endPoint(l.b.x, l.b.y, gridLevelList[m]->getLevel());
          OdTvResult tvCircleArcRes;
          OdTvGeometryDataId tvCircleArcId = pTvGridLevelEntity->appendCircleArc(startPoint, middlePoint, endPoint, &tvCircleArcRes);
          if (tvCircleArcRes != tvOk)
          {
            continue;
          }
          OdTvResult tvArcCaptionRes;
          OdTvGeometryDataId tvArcCaption = pTvTitle->appendText(l.a, l.caption, &tvArcCaptionRes);
          if (tvArcCaptionRes != tvOk)
          {
            return;
          }
          tvArcCaption.openAsText()->setNonRotatable(true);
        }
      }
    }
  }
}

//***************************************************************************//
// 'OdTvVisualizeRcsFilerModule' methods implementation
//***************************************************************************//

ODRX_DEFINE_DYNAMIC_MODULE(OdTvVisualizeNwFilerModule);

void OdTvVisualizeNwFilerModule::initApp()
{
  // initialize the Visualize SDK
  odTvInitialize();
}

void OdTvVisualizeNwFilerModule::uninitApp()
{
  // Uninitialize the Visualize SDK
  odTvUninitialize();
}

OdTvVisualizeFilerPtr OdTvVisualizeNwFilerModule::getVisualizeFiler() const
{
  OdTvVisualizeFilerPtr pFiler = new OdTvVisualizeNwFiler();

  return pFiler;
}

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

#ifndef __OD_GS_VISUALIZE_VECTORIZER__
#define __OD_GS_VISUALIZE_VECTORIZER__

#include "TD_PackPush.h"

#include "Gs/GsBaseInclude.h"
#include "Gs/GsBaseMaterialView.h"
#include "GsVisualizeGeometry.h"
#include "TvFactory.h"
#include <map>
#include <set>
#include "RxDispatchImpl.h"
#include "RxVariantValue.h"
#include "DbObjectId.h"
#include "GsVisualizeEntityPool.h"
#include "../Kernel/Extensions/ExRender/CommonDeviceProps.h"
#include "ThreadsCounter.h"
#include "Gs/GsDbRootLinkage.h"
#include "RxObject.h"

class OdGiRasterImage;
class ExGsVisualizeMetafile;

//Implement this inrefrace and give it to device using property "DeviceNotifier"
//to catch device notifications
class ExGsVisualizeDeviceNotifier
{
public:
  //entities
  virtual void entityVectorizationDone( const OdTvEntityId& entityId ) = 0;
  virtual void insertVectorizationDone( const OdTvEntityId& insertId ) = 0;
  virtual void lightVectorizationDone( const OdTvEntityId& lightId ) = 0;

  virtual void entityRemoved( const OdTvEntityId& entityId ) = 0;
  virtual void insertRemoved( const OdTvEntityId& insertId ) = 0;
  virtual void lightRemoved( const OdTvEntityId& insertId ) = 0;

  //view
  virtual void viewCreated( const OdTvGsViewId& viewId ) = 0;
  virtual void viewModified( const OdTvGsViewId& viewId ) = 0;

  //Table records
  virtual void layerCreated( const OdTvLayerId& layerId ) = 0;
  virtual void layerModified( const OdTvLayerId& layerId ) = 0;

  virtual void materialCreated( const OdTvMaterialId& materialId ) = 0;

  virtual void imageCreated( const OdTvRasterImageId& iamgeId ) = 0;

  virtual void blockCreated( const OdTvBlockId& blockId ) = 0;
  virtual void blockVectorizationBegin( const OdTvBlockId& blockId ) = 0;
  virtual void blockVectorizationDone( const OdTvBlockId& blockId ) = 0;

  virtual void linetypeCreated( const OdTvLinetypeId& linetypeId ) = 0;

  virtual void textStyleCreated( const OdTvTextStyleId& textStyleId ) = 0;

  //Models
  virtual void modelCreated( const OdTvModelId& modelId ) = 0;
  virtual void modelActivated( const OdTvModelId& modelId ) = 0;

  //update
  virtual void updateBegins() = 0;
  virtual void updateEnds() = 0;

  //Optional methods
  virtual void viewportEntityCreated( const OdTvEntityId&, const OdGiDrawable* ) {}
  virtual void tvDeviceCreated(const OdTvGsDeviceId&) {}
};

struct ExGsTextStyleCacheData
{
  OdString m_name;
  OdString m_typeface;
  OdString m_fileName;
  int m_charset;
  int m_family;
  OdUInt8 m_flags; //1 = italic, 2 = bold
  double m_dObliquingAngle;

  ExGsTextStyleCacheData() :
    m_name( L"" ),
    m_typeface( L"" ),
    m_fileName( L"" ),
    m_charset( 0 ),
    m_family( 0 ),
    m_flags( 0 ),
    m_dObliquingAngle( 0 )
  {
  };

  void setItalic( bool bSet ) { SETBIT( m_flags, 1, bSet ); }
  void setBold( bool bSet ) { SETBIT( m_flags, 2, bSet ); }

  bool operator< ( const ExGsTextStyleCacheData& data ) const
  {
    if( m_name < data.m_name ) return true;
    if( m_name > data.m_name ) return false;

    if( m_typeface < data.m_typeface ) return true;
    if( m_typeface > data.m_typeface ) return false;

    if( m_fileName < data.m_fileName ) return true;
    if( m_fileName > data.m_fileName ) return false;

    if( m_charset < data.m_charset ) return true;
    if( m_charset > data.m_charset ) return false;

    if( m_family < data.m_family ) return true;
    if( m_family > data.m_family ) return false;

    if( m_flags < data.m_flags ) return true;
    if( m_flags > data.m_flags ) return false;

    if( m_dObliquingAngle < data.m_dObliquingAngle ) return true;
    if( m_dObliquingAngle > data.m_dObliquingAngle ) return false;

    return false;
  }
};

//This structure provides device cache sharing
struct ExGsVisualizeDeviceCache
{
  bool m_bApplyCacheData; // if false device will not replace its cache by this data and will use this structure only for writing
  std::map< OdDbStub*, OdTvLayerId > m_cachedLayers;
  std::map< OdDbStub*, OdTvLinetypeId > m_cachedLinetypes;
  std::map< OdDbStub*, OdTvMaterialId > m_cachedMaterials;
  std::map< OdString, OdTvRasterImageId > m_cachedImages;
  std::map< ExGsTextStyleCacheData, OdTvTextStyleId > m_cachedTextStyles;
  std::set< OdDbStub* > m_cachedVectorizedBlocks;
  std::map< OdDbStub*, OdTvVisualStyleId > m_cachedVisualStyles;
  std::map< OdDbStub*, OdTvGsViewBackgroundId > m_cachedBackgrounds;
  OdUInt32 m_uniqNumber;
};

enum DeviceIgnoreFlags
{
  kIgnoreViewInfoFlags = 1 << 0,
  kIgnoreFaceFillPattern = 1 << 1,
  kIgnoreViewBackClipping = 1 << 2,
  kIgnoreViewFrontClipping = 1 << 3,
  kIgnoreViewClippingRegion = 1 << 4,
  kIgnoreEdgesColors        = 1 << 5
};

class ExGsVisualizeDeviceProperties :  public OdCommonDeviceProps//public OdRxDispatchImpl<>
{
protected:
  enum VisualizeDeviceProperty
  {
    kDisplayViaGLES2 = 1,
    kAllowNonPersistent = 1 << 1,
    kReuseEmptyEntities = 1 << 2,
    kEnableTiming = 1 << 3,
    kWriteUserData = 1 << 4,
    kFullRegenDependentVectorization = 1 << 5,
    kConvertIndexedColors = 1 << 6,
    kGenerateEntityNames = 1 << 7,
    kPerModelViews = 1 << 8,
    kCompareUnnamedImages = 1 << 9,
    kDisableEntitiesRemoving = 1 << 10,
    kUseVisualStyles = 1 << 11,
    kUseSceneGraph = 1 << 12,
    kEnableViewDependentEntities = 1 << 13,
    kLightGlyphDisplay = 1 << 14,
    kSuppoprtBrepDraw = 1 << 15,
    kDisableEntityCaching = 1 << 16,
    kWriteFontFilePath = 1 << 17,
    kIgnoreColoredShapes = 1 << 18,
    kCompareMaterialsForUniquiness = 1 << 19,
    kSupportGeometryInLight = 1 << 20,
    kDisableNonEntityLineweightTransformation = 1 << 21,
    kDisableSetingExtents = 1 << 22,
    kExplodeAnonymousBlocks = 1 <<23
  };
public:
  ExGsVisualizeDeviceProperties();
  virtual ~ExGsVisualizeDeviceProperties();

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(ExGsVisualizeDeviceProperties);

  void setHWND(OdIntPtr hWND) { m_hWnd = hWND; }
  OdIntPtr getHWND() const { return m_hWnd; }

  void setDisplayViaGLES2( bool d ) { SETBIT( m_deviceProps, kDisplayViaGLES2, d ); }
  bool getDisplayViaGLES2() const { return GETBIT( m_deviceProps, kDisplayViaGLES2 ); }

  void setNotifier( OdIntPtr ptr ) { m_pNotifier = (ExGsVisualizeDeviceNotifier*)(ptr); }
  OdIntPtr getNotifier() const { return (OdIntPtr)(m_pNotifier); }

  void setAllowNonPersistent( bool b ) { SETBIT( m_deviceProps, kAllowNonPersistent, b ); }
  bool getAllowNonPersistent() const { return GETBIT( m_deviceProps, kAllowNonPersistent ); }

  void setReuseEmptyEntities( bool b ) { SETBIT( m_deviceProps, kReuseEmptyEntities, b ); }
  bool getReuseEmptyEntities() const { return GETBIT( m_deviceProps, kReuseEmptyEntities ); }

  void setEnableTiming( bool b ) { SETBIT( m_deviceProps, kEnableTiming, b ); timingSet(); }
  bool getEnableTiming() const { return GETBIT( m_deviceProps, kEnableTiming ); }

  void setWriteUserData( bool b ) { SETBIT( m_deviceProps, kWriteUserData, b ); }
  bool getWriteUserData() const { return GETBIT( m_deviceProps, kWriteUserData ); }

  void setFullRegenDependentVectorization( bool b ) {SETBIT( m_deviceProps, kFullRegenDependentVectorization, b ); }
  bool getFullRegenDependentVectorization() const { return GETBIT( m_deviceProps, kFullRegenDependentVectorization ); }

  void setDisableEntityCaching( bool b ) { SETBIT( m_deviceProps, kDisableEntityCaching, b ); }
  bool getDisableEntityCaching() const { return GETBIT( m_deviceProps, kDisableEntityCaching ); }

  void setCustomDeviation( double d )
  {
    m_dCustomDeviation = d;
    m_bIsCustomDeviation = true;
  }

  double getCustomDeviation() const
  {
    if( !m_bIsCustomDeviation ) return 0.;
    return m_dCustomDeviation;
  }

  void setConvertIndexedColors( bool b ) { SETBIT( m_deviceProps, kConvertIndexedColors, b ); }
  bool getConvertIndexedColors() const { return GETBIT( m_deviceProps, kConvertIndexedColors ); }

  void setModelName( const OdString& str ) { m_strModelName = str; }
  OdString getModelName() const { return m_strModelName; }

  void setCustomFontFolder(const OdString& str) { m_strCustomFontFolder = str; }
  OdString getCustomFontFolder() const { return m_strCustomFontFolder; }

  void setFacetResForBrep(double d) {m_dFacetResForBrep = d;}
  double getFacetResForBrep() const {return m_dFacetResForBrep; }

  enum GeometryInterceptionPosition
  {
    kAutomatically = 0,
    kAtConveyorBegin = 1,
    kAtConveyorEnd = 2
  };

  void setGeometryInterceptionPosition( OdInt8 pos )
  {
    if( pos == 1 ) m_geomPosition = kAtConveyorBegin;
    else if( pos == 2 ) m_geomPosition = kAtConveyorEnd;
    else m_geomPosition = kAutomatically;
  }

  OdInt8 getGeometryInterceptionPosition() const
  {
    return (OdInt8)( m_geomPosition );
  }

  bool getGenerateEntityNames() const { return GETBIT( m_deviceProps, kGenerateEntityNames ); }
  void setGenerateEntityNames( bool b ) { SETBIT( m_deviceProps, kGenerateEntityNames, b ); }

  bool getPerModelViews() const { return GETBIT( m_deviceProps, kPerModelViews ); }
  void setPerModelViews( bool b ) { SETBIT( m_deviceProps, kPerModelViews, b ); }

  bool getCompareUnnamedImages() const { return GETBIT( m_deviceProps, kCompareUnnamedImages ); }
  void setCompareUnnamedImages( bool b ) { SETBIT( m_deviceProps, kCompareUnnamedImages, b ); }

  bool getDisableEntitiesRemoving() const { return GETBIT( m_deviceProps, kDisableEntitiesRemoving ); }
  void setDisableEntitiesRemoving( bool b ) { SETBIT( m_deviceProps, kDisableEntitiesRemoving, b ); }

  bool getUseVisualStyles() const { return GETBIT( m_deviceProps, kUseVisualStyles ); }
  void setUseVisualStyles( bool b ) { SETBIT( m_deviceProps, kUseVisualStyles, b ); }

  bool getUseSceneGraph() const { return GETBIT( m_deviceProps, kUseSceneGraph ); }
  void setUseSceneGraph( bool b ) { SETBIT( m_deviceProps, kUseSceneGraph, b ); }

  bool getEnableViewDependentEntities() const { return GETBIT( m_deviceProps, kEnableViewDependentEntities ); }
  void setEnableViewDependentEntities( bool b ) { SETBIT( m_deviceProps, kEnableViewDependentEntities, b ); }

  void setNamePrefix( const OdString& str ) { m_strPrefix = str; }
  OdString getNamePrefix() const { return m_strPrefix; }

  bool ignoreViewInfoFlags() const { return GETBIT( m_ignoreFlags, kIgnoreViewInfoFlags ); }
  bool ignoreFaceFillPattern() const { return GETBIT( m_ignoreFlags, kIgnoreFaceFillPattern ); }
  bool ignoreViewBackClipping() const { return GETBIT( m_ignoreFlags, kIgnoreViewBackClipping ); }
  bool ignoreViewFrontClipping() const { return GETBIT( m_ignoreFlags, kIgnoreViewFrontClipping ); }
  bool ignoreViewClippingRegion() const { return GETBIT( m_ignoreFlags, kIgnoreViewClippingRegion ); }
  bool ignoreEdgesColors() const { return GETBIT(m_ignoreFlags, kIgnoreEdgesColors); }

  OdUInt16 getIgnoreFlags() const { return m_ignoreFlags; }
  void setIgnoreFlags( OdUInt16 flg ) { m_ignoreFlags = flg; }

  void setByBlockLayerName( const OdString& str ) { m_byBlockLayerName = str; }
  OdString getByBlockLayerName() const { return m_byBlockLayerName; }

  void setWriteFontFilePath( bool b ) { SETBIT(m_deviceProps, kWriteFontFilePath, b); }
  bool getWriteFontFilePath() const { return GETBIT(m_deviceProps, kWriteFontFilePath); }

  bool getLightGlyphDisplay() const { return GETBIT(m_deviceProps, kLightGlyphDisplay); }
  void setLightGlyphDisplay(bool b) { SETBIT(m_deviceProps, kLightGlyphDisplay, b); }

  bool getSuppoprtBrepDraw() const { return GETBIT(m_deviceProps, kSuppoprtBrepDraw); }
  void setSuppoprtBrepDraw(bool b) { SETBIT(m_deviceProps, kSuppoprtBrepDraw, b); }

  bool getCompareMaterialsForUniquiness() const { return GETBIT(m_deviceProps, kCompareMaterialsForUniquiness); }
  void setCompareMaterialsForUniquiness(bool b) { SETBIT(m_deviceProps, kCompareMaterialsForUniquiness, b); }

  bool getIgnoreColoredShape() const { return GETBIT(m_deviceProps, kIgnoreColoredShapes); }
  void setIgnoreColoredShape(bool b) { SETBIT(m_deviceProps, kIgnoreColoredShapes, b); }

  bool getSupportGeometryInLight() const { return GETBIT( m_deviceProps, kSupportGeometryInLight ); }
  void setSupportGeometryInLight( bool b ) { SETBIT( m_deviceProps, kSupportGeometryInLight, b ); }

  bool getDisableNonEntityLineweightTransformation() const { return GETBIT( m_deviceProps, kDisableNonEntityLineweightTransformation ); }
  void setDisableNonEntityLineweightTransformation( bool b ) { SETBIT( m_deviceProps, kDisableNonEntityLineweightTransformation, b ); }

  bool getDisableSetingExtents() const { return GETBIT(m_deviceProps, kDisableSetingExtents); }
  void setDisableSetingExtents(bool b) { SETBIT(m_deviceProps, kDisableSetingExtents, b); }

  bool getExplodeAnonymousBlocks() const { return GETBIT( m_deviceProps, kExplodeAnonymousBlocks ); }
  void setExplodeAnonymousBlocks( bool b ) { SETBIT( m_deviceProps, kExplodeAnonymousBlocks, b ); }

protected:
  OdIntPtr  m_hWnd;
  ExGsVisualizeDeviceNotifier*  m_pNotifier;
  double    m_dCustomDeviation;
  OdString  m_strModelName;
  OdString  m_strCustomFontFolder;
  OdString  m_strPrefix;
  GeometryInterceptionPosition m_geomPosition;
  bool m_bIsCustomDeviation;
  OdUInt32 m_deviceProps;
  OdUInt16 m_ignoreFlags;
  double m_dFacetResForBrep;

  OdString m_byBlockLayerName;

  virtual void timingSet() {}
};

class ExGsVisualizeDevice;

class ExGsVisualizeDeviceSelfReference : public OdRxObject
{
  ExGsVisualizeDevice* m_pDevice;
public:
  ExGsVisualizeDeviceSelfReference()
  {
    m_pDevice = NULL;
  };
  void setDevice( ExGsVisualizeDevice* device ) 
  {
    m_pDevice = device;
  }
  ExGsVisualizeDevice* device() { return m_pDevice; }
};

class OdTvMutexPtr
{
public:
  OdTvMutexPtr();
  virtual ~OdTvMutexPtr();
  OdMutex* get();
  void setMutex(OdMutex* pMutex);
  OdMutex* getMutex() const;

private:
  void create();
  void clear();

private:
  bool m_bGotMutex;
  static OdMutex s_mt;
  OdMutex* m_ptr;
};

/*
  List of specific device properties:
  1)DisplayViaGLES2 - if enabled, TvDevice will be setted up as WinGLES2 device with setted HWND and will perform draw
  2)DeviceNotifier - if setted corresponding notified methods will be called
  3)AllowNonPersistentObjects - if enabled, non-persistent objects (e.g. grip points) will be vectorized
  4)ReuseEmptyEntities - if enabled, instead of removing TvEntities device will clear them and reuse them instead of creating new entities
  5)EnableTiming - if enabled, device will measure time for OdTv calls
  6)WriteUserData - if enabled, each high-level OdTvEntity will have UserData with corresponding Drawable Handle
  7)FullRegenDependentVectorization - if enabled, regen-type dependent entities will be vectorized twice: for wireframe (lines) and render (triangles)
  8)TvDatabaseID - if setted, device will use this OdTvdatabase instead of creating new one. Get will return database id
  9)TvElapsedTime - set does nothing. Get returns time for OdTv calls or 0. if EnableTiming was disabled
  10)CustomDeviation - sets custom deviation
  11)ConvertIndexedColor - if enabled, indexed colors will be converted to RGB if palette is set
  12)GeometryInterceptionPosition - specify geometry interception position in conveyor:
    0 - kAutomatically - vectorizer will start interseption at conveyor begin, but it can move interception position to the end and back if it need
    1 - kAtConveyorBegin - vectorizer always will use interseption at conveyor begin
    2 - kAtConveyorEnd - vectorizer always will use interseption at conveyor end
    All other values will be treated as 0
  13) GenerateEntityNames - if enabled, resulting TvEntities will have names taken from Drawable description
  14) ModelName - if is not empty, device will create model for Model space using specified name
  15) DeviceCache - getter write device cache in structure ExGsVisualizeDeviceCache, setter replace device cache by structure content if ExGsVisualizeDeviceCache::m_bApplyCacheData is true,
    else device only keep structure pointer for getter
    WARNING: since cache based on object ids, using different databases in devices that share cache data will cause crush
    NOTE: ExGsVisualizeDeviceCache should be allocated on client side. To read cache from device you must
      1) allocate ExGsVisualizeDeviceCache
      2) set ExGsVisualizeDeviceCache::m_bApplyCacheData to false
      3) set DeviceCache property using this structure
      4) read DeviceCache property
    To set cache to the device:
      1) change ExGsVisualizeDeviceCache::m_bApplyCacheData to true
      2) set DeviceCache property
  16) PerModelViews - if this option enabled each view will show its own model (BIM-specific case)
  17) CompareUnnamedImages - if enabled, unnamed image will be compared with cached images to prevent creation copies of single image. If disabled, each unnamed image will create new OdTvRasterImage
  18) DisableEntitiesRemoving - if enabled, created TvEntities will not be removed when asociated GS metafiles removing
  19) EnableViewDependentEntities - if enabled, device will create view-dependent entities when it need
  20) CustomFontFolder - allows to specify custom folder for fonts
  21) NamePrefix - allows to specify prefix to generated object names except Model, View and Device
  22) TvDeviceDAM - special for Database Agreegated Mode. Allow to specify OdTvGsDevice. If it is not a null, ExGsVisualizeDevice will not create and setup OdTvGsDevice by itself
  23) TvViewDAM - special for Database Agreegated Mode. Allow to specify OdTvGsView. If it is not a null, ExGsVisualizeDevice will not create and setup OdTvGsView. It is also will use specified view
    for all GsViews
  24) IgnoreFlags - allow to specify device ignoring flags which can be the combination of the folowing
  enum DeviceIgnoreFlags
  {
    kIgnoreViewInfoFlags = 1 << 0, - if enabled, ViewInfo flags will have no effect on model, so it will be ModelSpace
    kIgnoreFaceFillPattern = 1 << 1, - if enabled, no OdTvHatchPatternDef will be added to the shells 
    kIgnoreViewBackClipping = 1 << 2, - if enabled, view will ignore back clipping
    kIgnoreViewFrontClipping = 1 << 3, - if enabled, view will ignore front clipping
    kIgnoreViewClippingRegion = 1 << 4 - if enabled, view will ignore clipping region
    kIgnoreEdgesColors        = 1 << 5 - if enabled, egde's colors will ignored
  };
  25) ByBlockLayerName - specifies layer, that will be setuped as "ByBlock". "0" by default, can be empty string
  26) DisableGsCache - switchs device to "No GS Cache" mode
  27) LightGlyphDisplay - if true, the glyph for the light should be displayed
  28) SuppoprtBrepDraw - if true, the device will support the draw of the BREP
  29) DisableEntityCaching - if true, VisualizeGeometry will not cache currently used entity for faster access (unloading case)
  30) WriteFontFilePath - if true, Font File Path will be written in text style user data
  31) CompareMaterialsForUniquiness - if true, Materials will be checked for uniquiness (currently only for Ifc2Visualize and will return first not null material)
  32) IgnoreColoredShapes - if true, the colored shape will not used (shell always will be used instead)
  33) SupportGeometryInLight - if true, Light sources also will generate entities to store additional geometry
  34) DisableNonEntityLineweightTransformation - if true, non-entity (Layer) lineweight will not be transformed using "lineweight to pixels"
  35) DisableSetingExtents - if true, vectorization extents will not be set to the entites
  36) ExplodeAnonymousBlocks - if true, anonymous blocks will be exploded during the vectorization
*/

class ExGsVisualizeDevice : public OdGsBaseVectorizeDevice, public ExGsVisualizeDeviceProperties
{
protected:
  ExGsVisualizeDevice();
  virtual ~ExGsVisualizeDevice();

  void internalUpdate( OdGsDCRect* pUpdatedRect );
public:

  static OdGsDevicePtr createObject();

  void update(OdGsDCRect* pUpdatedRect);

  OdGsViewPtr createView(const OdGsClientViewInfo* pInfo = 0, 
                         bool bEnableLayerVisibilityPerView = false);

  OdRxDictionaryPtr properties() { return this; }

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(ExGsVisualizeDevice);

  void setTvDatabaseID( OdIntPtr ptr );
  OdIntPtr getTvDatabaseID() const;

  void setDeviceCache( OdIntPtr ptr );
  OdIntPtr getDeviceCache() const;

  void setOdTvTime( double ) {};
  double getOdTvTime() const;

  void setTvDeviceDAM( OdIntPtr ptr );
  OdIntPtr getTvDeviceDAM() const;

  void setTvViewDAM( OdIntPtr ptr );
  OdIntPtr getTvViewDAM() const;

  void setDatabaseAccessMutex(OdIntPtr ptr);
  OdIntPtr getDatabaseAccessMutex() const;

  bool isViewDAMMode( OdTvGsViewId* pViewId = NULL ) const;

  virtual void onSize(const OdGsDCRect& outputRect);

  virtual ExGsVisualizeDeviceNotifier* deviceNotifier() { return m_pNotifier; }

protected:
  OdTvDatabaseId    m_dbId;
  OdTvModelId       m_modelId;

  OdTvGsDeviceId    m_tvDeviceId;

  OdTvRegAppId      m_appId;
  void              createTvDatabase();
  void              createTvDevice();
  bool              m_bTvDeviceInited;
  void              initTvDevice();
  void              syncTvViews();

  //models
  OdTvModelId       m_modelSpaceModel;
  OdTvModelId       m_paperOnlyModel;
  typedef std::map< long , OdTvModelId >  ModelsMap;
  ModelsMap         m_paperSpaceModels;
  typedef std::map< OdGsView*, OdTvModelId > ViewModelsMap;
  ViewModelsMap     m_perViewModels;
  OdTvGsViewId      m_tvViewDAM;
public:
  OdTvModelId       getTvModelId();
  OdTvDatabaseId    getTvDatabaseId();
  OdTvGsDeviceId    getTvDeviceId() const { return m_tvDeviceId; }
  OdTvRegAppId      getTvAppId() const { return m_appId; }

  OdTvTextStyleId        getTvTextStyleId( const OdGiTextStyle*, double* pObliquingAngle = NULL );
  OdTvRasterImageId      getTvImageId( const OdGiRasterImage*, const OdGiSubEntityTraitsData* pTraits = NULL );
  OdTvBlockId            getTvBlockId( OdDbStub* );
  OdTvLayerId            getTvLayer( OdDbStub*, OdGiLinetypeTraits* pLineTypeTraits = NULL );
  void                   modifyLayer( const OdString& str, OdGiDrawable *pDrawable );
  OdTvLinetypeId         getTvLineType( OdDbStub*, OdUInt32& flags, OdGiLinetypeTraits* );
  OdTvMaterialId         getTvMaterial( OdDbStub*, OdUInt32& flags );
  OdTvVisualStyleId      getTvVisualStyle( OdDbStub* );
  OdTvGsViewBackgroundId getTvBackground( OdDbStub* );

  template< class T >void setObjectUserData( T pObjectPtr, OdDbStub* id );

  void              setModelForView( OdGsClientViewInfo, OdGsView* );

  OdRxObjectPtr getSelfReference() const { return m_pSelfReference;}

  void deleteTvEntity( OdTvEntityId, bool isInsert, bool isLight = false );
  bool reuseEmptyEntity( OdTvModelId modelId, OdTvEntityId& entityId, bool isInsert );
  void removeCachedEmptyEntities();

  bool isBlockVectoprized( OdDbStub* );
  void setBlockVectorized( OdDbStub* );
protected:
  //names map
  typedef std::map< OdDbStub*, OdString > NamesMap;
  NamesMap m_generatedNames;
  OdUInt32 m_uniqNumber;
  OdString generateUniqName( const OdString& prefix = L"Generated_" );

  std::set< OdDbStub* > m_vectorizedBlocks;

  OdRxObjectPtr m_pSelfReference;

  bool supportPartialUpdate() const { return false; }

  void applyModificationsOnLayer( OdTvLayerId layerId, OdGiLayerTraits* pTraits, OdUInt32 flags, OdGiLinetypeTraits* pLineTypeTraits = NULL );

  ExGsVisualizeEntityPool m_emptyEntities;

  ExGsVisualizeTimer *m_pTimer;
  double m_dVectorizersTime;
  virtual void timingSet();

public:
  void addVectorizerTime( double sec );

protected:
  OdGiDrawablePtr openDrawable( OdDbStub* );

public:
  bool isCustomDeviation() const { return m_bIsCustomDeviation; }
protected:
  const ODCOLORREF* m_currentPalette;
public:
  const ODCOLORREF* currentPalette() const { return m_currentPalette; }

protected:
  std::map< OdDbStub*, OdTvLayerId > m_cachedLayers;
  std::map< OdDbStub*, OdTvLinetypeId > m_cachedLinetypes;
  std::map< OdDbStub*, OdTvMaterialId > m_cachedMaterials;
  std::map< OdString, OdTvRasterImageId > m_cachedImages;
  std::map< ExGsTextStyleCacheData, OdTvTextStyleId > m_cachedTextStyles;
  std::map< OdDbStub*, OdTvVisualStyleId > m_cachedVisualStyles;
  std::map< OdDbStub*, OdTvGsViewBackgroundId > m_cachedBackgrounds;
  ExGsVisualizeDeviceCache* m_pDeviceCache;

  class ExGsVisualizeDeviceHelper
  {
  protected:
    ExGsVisualizeDevice* m_pDevice;
    OdUInt32 m_nAttempts;
  public:
    ExGsVisualizeDeviceHelper( ExGsVisualizeDevice*, OdUInt32 );
    ~ExGsVisualizeDeviceHelper();

    OdTvLayerId createLayer( const OdString&, OdTvDatabasePtr );
    OdTvMaterialId createMaterial( const OdString&, OdTvDatabasePtr );
    OdTvTextStyleId createTextStyle( const OdString&, OdTvDatabasePtr );
    OdTvModelId createModel( const OdString&, OdTvDatabasePtr );
    OdTvVisualStyleId createVisualStyle( const OdString&, OdTvDatabasePtr, OdTvVisualStyleId );
    OdTvGsViewBackgroundId createBackground( const OdString&, OdTvGsViewBackgroundId::BackgroundTypes, OdTvDatabasePtr );
  };

  ExGsVisualizeDeviceHelper* m_pHelper;

  OdTvRasterImageId findUnnamedImage( const OdGiRasterImage* );

  //MT support
  OdTvMutexPtr m_databaseAccessMutex;
//VS support
  bool isTheSameVisualStyles( OdTvVisualStyleId tvVS, const OdGiVisualStyle* pVS );
public:
  OdTvMutexPtr& databaseAccessMutex() { return m_databaseAccessMutex; }
protected:
  OdString fixFilePath( const OdString& file, OdDbBaseHostAppServices::FindFileHint hint = OdDbBaseHostAppServices::kDefault );
  OdTvColorDef getTvColorDefFromCmEntityColor(const OdCmEntityColor& cmColor);
  void getOdTvMaterialMapFromOdGiMaterialMap(const OdGiMaterialMap& giMatMap, OdTvMaterialMap& tvMatMap, OdInt16& mapperProj, OdInt16& mapperAutoTrans);

public:
//Data replacement
  void pushZeroLayerReplacement( OdTvLayerId layerId );
  void popZeroLayerReplacement();

protected:
  OdStack<OdTvLayerId> m_zeroLayerStack;
};

typedef OdSmartPtr< ExGsVisualizeDevice > ExGsVisualizeDevicePtr;

class ExGsVisualizeView;

class ExGsVisualizeVectorizer : public OdGsBaseMaterialVectorizer
{
public:
  //ODRX_USING_HEAP_OPERATORS(OdGsBaseMaterialVectorizer);
  ODRX_HEAP_OPERATORS();
public:
  ExGsVisualizeVectorizer();
  virtual ~ExGsVisualizeVectorizer();

protected:
  virtual void beginViewVectorization();
  virtual void endViewVectorization();

  virtual void affectTraits(const OdGiSubEntityTraitsData* pSource,
      OdGiSubEntityTraitsData& destination) const;

protected:
  //Expoloded (Anonimous) data processing
  inline ExGsVisualizeDevice* getExGsVisualizeDevice(){ return (ExGsVisualizeDevice*)( view().device() ); }
  void pushLayerZero();
  void popLayerZero();

public:

  void draw(const OdGiDrawable*);
  virtual bool doDraw(OdUInt32 drawableFlags, const OdGiDrawable* pDrawable);

  bool regenAbort() const;

  double deviation(const OdGiDeviationType, const OdGePoint3d&) const;

  void updateViewport();

  void onTraitsModified();

  virtual void ownerDrawDc(
    const OdGePoint3d& origin,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdGiSelfGdiDrawable* pDrawable,
    bool dcAligned = true,
    bool allowClipping = false);

  //Geometry
  void pushModelTransform(const OdGeMatrix3d& xfm);
  void pushModelTransform(const OdGeVector3d& normal);
  void popModelTransform();

  //Clip boundaries
  void pushClipBoundary(OdGiClipBoundary* pBoundary);
  void pushClipBoundary(OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* pClipInfo);
  void popClipBoundary();

  void polygonEye(OdUInt32 numVertices, const OdGePoint3d* vertexList);
  virtual void xline(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint);
  virtual void ray(const OdGePoint3d& basePoint, const OdGePoint3d& throughPoint);

  virtual bool brep(const OdGiBrep& brep);

  virtual OdGiRegenType regenType() const;

  OdGiLinetypeTraits* getLineTypeTraits();
protected:
  ExGsVisualizeGeometry* m_pGeom;
  OdGiRegenType m_regenTypeOverride;
  bool          m_bRegenTypeOverriden;

  class RegenTypeChanger
  {
  public:
    RegenTypeChanger( ExGsVisualizeVectorizer* pVec , OdGiRegenType type )
    {
      m_oldRT = pVec->m_regenTypeOverride;
      m_oldRTFlag = pVec->m_bRegenTypeOverriden;

      m_RTFlag = &(pVec->m_bRegenTypeOverriden);
      m_RT = &(pVec->m_regenTypeOverride);

      *m_RTFlag = true;
      *m_RT = type;
    }
    ~RegenTypeChanger()
    {
      *m_RTFlag = m_oldRTFlag;
      *m_RT = m_oldRT;
    }
  protected:
    bool* m_RTFlag;
    OdGiRegenType* m_RT;
    OdGiRegenType m_oldRT;
    bool m_oldRTFlag;
  };

  OdUInt32  m_nNestingLevel;

  class NLCounter
  {
  protected:
    OdUInt32* m_pLevel;
  public:
    NLCounter( ExGsVisualizeVectorizer* pVec )
    {
      m_pLevel = &(pVec->m_nNestingLevel);
      (*m_pLevel)++;
    }
    ~NLCounter()
    {
      (*m_pLevel)--;
    }
    bool isNested() const
    {
      return *m_pLevel != 1;
    }
  };

  OdTvEntityId createNewTvEntity( const OdString& name = L"" );
  OdTvEntityId createNewTvInsert( OdTvBlockId blockId, const OdString& name = L"" );
  OdTvBlockId m_curBlockId;
  OdRxObject* m_pCurMetafile;
  void createLightEntity( const OdGiDrawable* pDrawable );
public: //Metafiles
  OdRxObjectPtr newGsMetafile();
  void beginMetafile(OdRxObject* pMetafile);
  void endMetafile(OdRxObject* pMetafile);
protected:
  friend class ExGsVisualizeMetafile;
  enum EntityType
  {
    kTypeEntity = 0,
    kTypeInsert = 1,
    kTypeLight = 2
  };
  void setCurrentMetafileEntity( OdTvEntityId id, EntityType type = kTypeEntity );

  OdGiConveyorEmbranchmentPtr m_pConveyorInjection;
  void createConveyorInjection();
  void removeConveyorInjection();

  bool m_bVectorizationBegins;
  bool isIgnore() const;
public://attributes
  void startAttributesSegment();
  void processAttributesSegment( bool bFromBlockRef = true );
protected:
  ExGsVisualizeTimer *m_pTimer;
public:
  void setTiming( bool bEnable );
  bool isGeometryNeedTransform() const { return m_bGeomInUse; }
protected:
  bool m_bGeomInUse;
  void setGeometryNeedTransform( bool b = true ) { m_bGeomInUse = b; }
  enum GeometryConveyorPosition
  {
    kConveyorBegin,
    kConveyorEnd
  };
  GeometryConveyorPosition m_geometryPosition;
  OdGiEmptyGeometry m_emptyGeometry;
  void switchGeometryPosition( GeometryConveyorPosition to = kConveyorBegin );
  bool m_bCanSetPositionBegin;
public:
  bool isGeometryInterseptionAtEnd() const { return m_geometryPosition == kConveyorEnd; }
  bool isGeometryInterseptionAtBegin() const { return m_geometryPosition == kConveyorBegin; }

  void setDisableEntityCaching( bool b )
  {
    if( m_pGeom ) m_pGeom->setDisableEntityCaching( b );
  }
protected:
  struct BlockInsertDescr
  {
    OdArray< OdTvEntityId > m_array;
    OdUInt32 m_processingInsert;
    BlockInsertDescr()
    {
      m_processingInsert = 0;
    }
  };
  OdStack<BlockInsertDescr> m_insertStack;
  bool m_bNeedConvertByBlockColor;

  struct ClipBoundaryDef
  {
    OdGiClipBoundary         CB;
    OdGiAbstractClipBoundary* pAbsCB;
    BlockInsertDescr* pBlcDescr;

    ClipBoundaryDef()
    {
      pAbsCB = NULL;
    }

    ClipBoundaryDef( OdGiClipBoundary cb, OdGiAbstractClipBoundary* absCb, BlockInsertDescr* pBlc )
    {
      CB = cb;
      if( absCb )
      {
        pAbsCB = absCb->clone();
      }
      else
      {
        pAbsCB = NULL;
      }
      pBlcDescr = pBlc;
    }

    ~ClipBoundaryDef()
    {
      if( pAbsCB ) delete pAbsCB;
      pAbsCB = NULL;
    }

    ClipBoundaryDef( const ClipBoundaryDef& def )
    {
      CB = def.CB;
      if( def.pAbsCB )
      {
        pAbsCB = def.pAbsCB->clone();
      }
      else
      {
        pAbsCB = NULL;
      }
      pBlcDescr = def.pBlcDescr;
    }
  };

  OdStack<ClipBoundaryDef> m_clipBoundariesStack;
public:
  OdUInt8 getSpecificFillingMode( const OdGiSubEntityTraitsData& traits );
  double getVectorizerTime() const
  {
    if( !m_pTimer ) return 0.0;
    return m_pTimer->time();
  }
protected:
  bool isViewportDependentEntity();

  void obtainVectorizerExtents( OdGeExtents3d& );
  void resetVectorizerExtents( OdGeExtents3d& accumedExtents, const OdGeExtents3d& entExtents = OdGeExtents3d::kInvalid );

  OdDbBaseBlockRefPE* m_pCurBlockRefPE;
  bool m_bProcessedAttributesSegment;

  bool m_bAlreadyAskedForModes;

  bool m_bForceInsertViewDependent;
};

typedef OdSharedPtr<ExGsVisualizeVectorizer> ExGsVisualizeVectorizerPtr;

class ExGsVisualizeView : public OdGsBaseVectorizeView, public OdGsModelReactor
{
  OdGiClipBoundary                    m_eyeClip;
//  ExGsVisualizeVectorizerPtr          m_pVect;
  OdArray<ExGsVisualizeVectorizerPtr> m_vectorizersAllocated;
  OdArray<ExGsVisualizeVectorizerPtr> m_vectorizersUsed;
protected:

  virtual OdGsBaseVectorizer* getVectorizer(bool bDisplay);
  virtual void releaseVectorizer(OdGsBaseVectorizer* pVect);

  ExGsVisualizeDevice* device()
  { 
    return (ExGsVisualizeDevice*)OdGsBaseVectorizeView::device(); 
  }

  ExGsVisualizeView();

  virtual ~ExGsVisualizeView();

  friend class ExGsVisualizeDevice;

  static OdGsViewPtr createObject()
  {
    return OdRxObjectImpl<ExGsVisualizeView,OdGsView>::createObject();
  }

  /**********************************************************************/
  /* To know when to set traits                                         */
  /**********************************************************************/
  //void setEntityTraits();

public:
 /* void ownerDrawDc(
    const OdGePoint3d& origin,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdGiSelfGdiDrawable* pDrawable,
    bool bDcAligned,
    bool bAllowClipping);*/

  virtual void clearLinetypeCache(){}
  virtual OdUInt32 numVectorizers() const;

  void syncTvView();

  static OdTvGsView::RenderMode fromGsMode( OdGsView::RenderMode );

  virtual void update();

  virtual bool add(OdGiDrawable* pSceneGraph, OdGsModel* pModel);
  //model reactors
  virtual bool onModified(OdGsModel *pModel, OdGiDrawable *pModified, OdGiDrawable *pParent);
  virtual bool onModified(OdGsModel *pModel, OdGiDrawable *pModified, OdDbStub *parentID);

  virtual void setLineweightEnum(int numLineweights, const OdUInt8* lineweights);

  virtual void setViewportClipRegion(int numContours, const int* numVertices, const OdGePoint2d* vertices);
  virtual void setViewportClipRegion(int numContours, int const* numVertices, OdGsDCPoint const* vertices);

  OdTvGsViewId getTvViewId();

protected:
  OdTvGsViewId      m_tvViewId;
  static int        m_nViewCounter;
  static OdString   generateViewName();

  typedef std::set< OdGsModel* > ModelsSet;
  ModelsSet         m_reactingModels;

  ExGsVisualizeTimer *m_pTimer;
  OdTvMutexPtr m_databaseAccessMutex;
public:
  void setTimer( ExGsVisualizeTimer* timer ) { m_pTimer = timer; }
protected:
  OdGiDrawablePtr openDrawable( OdDbStub* );
  //data for TvView initialization
  enum TvViewInitialization
  {
    kNone = 0,
    kSetLineweightEnum = 1 << 0,
    kSetClipRegion = 1 << 1
  };
  OdUInt8 m_viewIntializationFlags;
  OdUInt8Array m_forTvLineWeightEnum;

  enum AdditionalViewFlag
  {
    kIndexedLineWeight = 1,
    kFrozenLayersChanged = 2,
    kInitializeTvView = 4,
    kForceDisableDefaultLight = 8
  };
  OdUInt8 m_additionalViewFlags;

  struct ClipRegionInfo
  {
    OdArray< OdUInt32 > m_vertexNums;
    OdArray< OdGePoint2d> m_pts;
  };
  ClipRegionInfo m_ClipRegionInfo;

  bool needUpdateFrozenLayers() const { return GETBIT( m_additionalViewFlags, kFrozenLayersChanged ); }
  void setNeedUpdateFrozenLayers( bool bSet ) { SETBIT( m_additionalViewFlags, kFrozenLayersChanged, bSet ); }
  void syncFrozenLayers();

  bool isInitializeTvView() const { return GETBIT( m_additionalViewFlags, kInitializeTvView ); }
  void setInitializeTvView( bool bSet ) { SETBIT( m_additionalViewFlags, kInitializeTvView, bSet ); }

  void syncVisualStyles();
  void syncBackgrounds();

  void syncViewportTraits();

public:
  bool isIndexedLineWeight() const { return GETBIT( m_additionalViewFlags, kIndexedLineWeight ); }
  void setIndexedLineWeight( bool bSet ) { SETBIT( m_additionalViewFlags, kIndexedLineWeight, bSet ); }

  //OdGsViewImpl accessors
  void implPropagateLayerChanges();
  void implGetRootNode();

  //Frozen layers support
  virtual void freezeLayer(OdDbStub* layerID);
  virtual void thawLayer(OdDbStub* layerID);
  virtual void clearFrozenLayers();

  virtual void enableDefaultLighting(bool bEnable, DefaultLightingType lightType = kTwoLights);
}; // end ExGsVisualizeView

#include "TD_PackPop.h"

#endif // __OD_GS_BITMAP_VECTORIZER__

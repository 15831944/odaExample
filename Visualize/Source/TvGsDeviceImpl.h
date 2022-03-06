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

#ifndef _ODTV_GSDEVICEIMPL_H_INCLUDED_
#define _ODTV_GSDEVICEIMPL_H_INCLUDED_

#include "TvDatabaseImpl.h"
#include "TvGsViewImpl.h"
#include "GsBaseLayoutHelper.h"
#include "GsDeviceForTv.h"
#include "TvGsDevice.h"
#include "TvDataLink.h"
#include "TvGiContextForDatabase.h"
#include "TvUserDataImpl.h"
#include "TvPartialViewing.h"
#include "Tr/sg/TrRndSgTaskScheduler.h"

#include "DbDatabaseReactor.h"
#include "OdPerfTimer.h"
#define STL_USING_MAP
#define STL_USING_SET
#include "OdaSTL.h"
#include "RxDispatchImpl.h"

/** \details
    Path for devices
*/
#define OdTvGDIDevice       L"WinGDI.txv"
#define OdTvOpenGLDevice    L"WinOpenGL.txv"
#define OdTvDirectXDevice   L"WinDirectX.txv"
#define OdTvBitmapDevice    L"WinBitmap.txv"
#define OdTvGLES2Device     L"WinGLES2.txv"
#define OdTvMetalDevice     L"WinMetal.txv"

/** \details
Default lineweight configuration
*/
#define DEFAULT_LW_CAPSTYLE  OdTvGsDevice::kLesRound
#define DEFAULT_LW_JOINSTYLE OdTvGsDevice::kLjsRound

/** \details
The structure for storing viewport parameters, which will be used in layout helper during export through PE
*/
struct ViewportInfo
{
  bool              m_bActive;        // indicate that parameters was set and should be used
  OdInt32           m_iParentViewId;  // index of the parent view

  OdTvPoint2d       m_wcsLowerLeft;   //WCS lower-left point of the viewport.
  OdTvPoint2d       m_wcsUpperRight;  //WCS upper-right point of the viewport.

  OdUInt32Array     m_numPtsInContours; //A quantity of points in contours.
  OdTvPoint2dArray  m_wcsCountoursPts;  //An array of points that form contours.

  ViewportInfo() : m_bActive(false), m_iParentViewId(-1){};
};

/** \details
    Method for constructing the device module path
*/
bool GetDeviceModulePath(OdString& devicePath, OdTvGsDevice::Name device, OdString* strVectorizerName);

class OdGsDeviceForTvImpl;
typedef OdSmartPtr<OdGsDeviceForTvImpl> OdGsDeviceForTvImplPtr;

/** \details
Implements scheduler for the scene graph creation
*/
class OdTvTimedScheduler : public OdTrRndSgSceneGraphTaskScheduler
{
public:

  OdPerfTimerBase*        m_pTimer;
  OdUInt32                m_timerLimit;
  bool                    m_bDelaySceneGraphProc;

  OdTvTimedScheduler()
  {
    m_pTimer = OdPerfTimerBase::createTiming();
    m_timerLimit = 0;
    m_bDelaySceneGraphProc = false;
  }

  ~OdTvTimedScheduler()
  {
    OdPerfTimerBase::destroyTiming(m_pTimer);
  }

  // Prevent entire queue processing if timing limit reached.
  virtual bool beginQueueProcessing()
  {
    if (m_bDelaySceneGraphProc)
      return false;
    else if (m_timerLimit > 0 && m_pTimer->permanentMSec() >= m_timerLimit)
      return false;

    return true;
  }

  // Break queue processing if timing limit reached.
  virtual ProcessType beginTaskProcessing(TaskType /*taskType*/)
  {
    if (m_bDelaySceneGraphProc)
      return kBreakProcess;
    else if (m_timerLimit > 0 && m_pTimer->permanentMSec() >= m_timerLimit)
      return kBreakProcess;

    return kProcessTask;
  }
};
typedef OdSmartPtr<OdTvTimedScheduler> OdTvTimedSchedulerPtr;

typedef OdTvTimedScheduler OdTvSceneGraphTimedScheduler;
typedef OdSmartPtr<OdTvSceneGraphTimedScheduler> OdTvSceneGraphTimedSchedulerPtr;


/** \details
We will use this structure only for the compatibility with common interface. 
But we will use additional methods after casting
*/
struct OdTvGsLayoutHelperIntCache : public OdStaticRxObject<OdGsCache>
{
  //array of the models
  OdArray<OdGsModelPtr> m_mainGsModels;
  OdArray<OdGsModelPtr> m_directGsModels;
  OdArray<OdGsModelPtr> m_backgroundZGsModels;

  //connection between tv models and gs models
  std::map< OdTvModelImpl*, OdGsModel* > m_tvGsModelMap;
  std::set< OdGsModel* > m_freeGsModels;

  OdGiContext *m_pCtx; // Initial GiContext (don't call methods, this ptr could be deleted)
  OdRefCounter m_nRefs;
 
  // gcc build
  ODRX_HEAP_OPERATORS();
  // OdGsCache overrides
  OdGsModel* model() const 
  {
    if (m_mainGsModels.empty())
      return NULL;

    return const_cast<OdGsModel*>(m_mainGsModels[0].get());
  }
  void setDrawableNull() { }
  bool extents(OdGeExtents3d& /*extents*/) const { return false; }
  //

  //own methods
  const OdArray<OdGsModelPtr>* getModels(OdTvModel::Type type) const;
  void                         addGsModel(OdGsModel* pGsModel, OdTvModel::Type type);
  bool                         isCompatible(OdGsDevicePtr& pDevice);
  OdGsModel*                   notifyRemoveTvModel(OdTvModelImpl* pDbModel);
  OdGsModel*                   getGsModel(OdTvModelImpl* pDbModel);
};


/** \details
    Class for the connection between device and reactors
*/
class OdTvGsLayoutHelperInt : public OdGsBaseLayoutHelperInt<OdTvDbDatabase, OdTvDbObject>, OdStaticRxObject<OdTvDbDatabaseReactor>
{
  static OdGiDrawablePtr openDrawable(OdDbStub* id);

  // OdTvDbDatabaseReactor overridden
  virtual void objectAppended(const OdTvDbDatabase* pDb, const OdTvDbObject* pObj);
  virtual void objectModified(const OdTvDbDatabase* pDb, const OdTvDbObject* pObj);
  virtual void objectErased(const OdTvDbDatabase* pDb, const OdTvDbObject* pObj, bool bErased);

  //own methods
  bool isNeedRejectReactors(const OdTvDbDatabase* pDb);
  bool isNeedSimulateUnerased(OdTvDbDatabase* pDb);
  void addGsModel(OdGsModel* pGsModel, OdTvModel::Type type);
  OdGsModel* getFirstAppropriateModelForNotification();

public:
  ODRX_HEAP_OPERATORS();

  virtual void init(OdGsDevice* pUnderlyingDevice, OdGsDeviceForTv* pOverlayDevice);
  virtual void goodbye(const OdTvDbDatabase* pDb);
  
  void        freeOverlayingDevice();
  OdGsModel*  getGsModel(OdTvModelImpl* pDbModel);
  OdTvResult  regen(OdTvGsDevice::RegenMode regenMode);
  void        regenView(OdGsView* pView);
  void        removeGsModel(OdGsModel* pGsModel);

  OdTvGsLayoutHelperInt();
  virtual ~OdTvGsLayoutHelperInt();

private:
  OdGsDeviceForTv* m_pOverlayingDevice;
  bool             m_bHasCompatibleCache;

  //array of the models
  OdList< OdGsModelPtr > m_mainGsModels;
  OdList< OdGsModelPtr > m_directGsModels;
  OdList< OdGsModelPtr > m_backgroundZGsModels;

  std::set< OdGsModel* >  m_gsModels;
};

/** \details
This class is an implementation of the device properties storage
*/

class OdTvDeviceProperties : public OdRxDispatchImpl<>
{
  enum BooleanProps
  {
    kDoubleBufferEnabled = 1 << 0,
    kBlocksCache = 1 << 1,
    kEnableMultithread = 1 << 2,
    kEnableSoftwareHLR = 1 << 3,
    kDiscardBackFaces = 1 << 4,
    kUseTTFCache = 1 << 5,
    kUseDynamicSubEntHlt = 1 << 6,
    kForcePartialUpdate = 1 << 7,
    kClearScreen = 1 << 8,
    kUseVisualStyles = 1 << 9,
    kUseOverlayBuffers = 1 << 10,
    kUseSceneGraph = 1 << 11,
    kUseCompositeMetafiles = 1 << 12,
    kCreateGLContext = 1 << 13,
    kDelaySceneGraphProc = 1 << 14,
    kFXAAEnable = 1 << 15,
    kFXAA2dEnable = 1 << 16,
    kSSAOEnable = 1 << 17,
    kGPUSelectionEnable = 1 << 18,
    kSSAODynamicRadius = 1 << 19
  };

public:
  OdTvDeviceProperties();
  virtual ~OdTvDeviceProperties();

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvDeviceProperties);
  static OdRxDictionaryPtr createObject();

  virtual void dwgInFields(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  void setupGsDeviceProperties(OdRxDictionaryPtr pProperties, bool bIsOpenGLDevice) const;

  void setDoubleBufferEnabled(bool bVal);
  bool getDoubleBufferEnabled() const;

  void setBlocksCache(bool bVal);
  bool getBlocksCache() const;

  void setEnableMultithread(bool bVal);
  bool getEnableMultithread() const;

  void setMaxRegenThreads(OdInt16 iVal);
  OdInt16 getMaxRegenThreads() const;

  void setEnableSoftwareHLR(bool bVal);
  bool getEnableSoftwareHLR() const;

  void setDiscardBackFaces(bool bVal);
  bool getDiscardBackFaces() const;

  void setUseTTFCache(bool bVal);
  bool getUseTTFCache() const;

  void setUseDynamicSubEntHlt(bool bVal);
  bool getUseDynamicSubEntHlt() const;

  void setForcePartialUpdate(bool bVal);
  bool getForcePartialUpdate() const;

  void setClearScreen(bool bVal);
  bool getClearScreen() const;

  void setUseLutPalette(OdInt32 iVal);
  OdInt32 getUseLutPalette() const;

  void setUseVisualStyles(bool bVal);
  bool getUseVisualStyles() const;

  void setUseOverlayBuffers(bool bVal);
  bool getUseOverlayBuffers() const;

  void setAlternativeHlt(OdUInt32 iVal);
  OdUInt32 getAlternativeHlt() const;

  void setAlternativeHltColor(OdUInt32 iVal);
  OdUInt32 getAlternativeHltColor() const;

  void setUseSceneGraph(bool bVal);
  bool getUseSceneGraph() const;

  void setDelaySceneGraphProc(bool bVal);
  bool getDelaySceneGraphProc() const;

  void setUseCompositeMetafiles(bool bVal);
  bool getUseCompositeMetafiles() const;

  void setGeometryShaderUsage(OdUInt32 iVal);
  OdUInt32 getGeometryShaderUsage() const;

  void setCreateGLContext(bool bVal);
  bool getCreateGLContext() const;

  void setBlendingMode(OdUInt32 iVal);
  OdUInt32 getBlendingMode() const;

  void setAntiAliasingLevel(double dVal);
  double getAntiAliasingLevel() const;

  void setAntiAliasingLevelExt(double dVal);
  double getAntiAliasingLevelExt() const;

  void setFXAAEnable(bool bVal);
  bool getFXAAEnable() const;

  void setFXAAQuality(OdUInt32 dVal);
  OdUInt32 getFXAAQuality() const;

  void setFXAA2dEnable(bool bVal);
  bool getFXAA2dEnable() const;

  void setShadowRenderMode( OdUInt32 nVal );
  OdUInt32 getShadowRenderMode() const;

  void setVsmShadowsAmount( double dVal );
  double getVsmShadowsAmount() const;

  void setShadowMapSoftnessOverride( OdUInt32 nVal );
  OdUInt32 getShadowMapSoftnessOverride() const;

  void setShadowMapSizeOverride( OdUInt32 nVal );
  OdUInt32 getShadowMapSizeOverride() const;

  void setSSAOEnable(bool bVal);
  bool getSSAOEnable() const;

  void setSSAOLoops(OdUInt32 iVal);
  OdUInt32 getSSAOLoops() const;

  void setSSAORadius(double dVal);
  double getSSAORadius() const;

  void setSSAOPower(double dVal);
  double getSSAOPower() const;

  void setSSAOBlurRadius(OdUInt32 iVal);
  OdUInt32 getSSAOBlurRadius() const;

  void setSSAODynamicRadius(bool bVal);
  bool getSSAODynamicRadius() const;

  void setGPUSelectionEnable(bool bVal);
  bool getGPUSelectionEnable() const;

  void setSceneGraphCachesMode(OdUInt32 iVal);
  OdUInt32 getSceneGraphCachesMode() const;

protected:
  OdUInt32               m_flags; // Different options
  OdInt16                m_iMaxRegenThreads;
  OdInt32                m_iUseLutPalette;
  OdUInt32               m_iAlternativeHlt;
  OdUInt32               m_iAlternativeHltColor;
  OdUInt32               m_iGeometryShaderUsage;
  OdUInt32               m_iBlendingMode;
  double                 m_dAntiAliasingLevel;
  double                 m_dAntiAliasingLevelExt;
  OdUInt32               m_iFXAAQuality;

  OdUInt32               m_iShadowRenderMode;
  double                 m_dVsmShadowsAmount;
  OdUInt32               m_iShadowMapSoftnessOverride;
  OdUInt32               m_iShadowMapSizeOverride;

  OdUInt32               m_iSSAOLoops;
  double                 m_dSSAORadius;
  double                 m_dSSAOPower;
  OdUInt32               m_iSSAOBlurRadius;

  OdUInt32               m_iSceneGraphCachesMode;
};
typedef OdSmartPtr<OdTvDeviceProperties> OdTvDevicePropertiesPtr;


/** \details
    This class is an implementation of the wrapper over the Gs Device which is also connected with 
    reactors functionality through the 'OdTvGsLayoutHelperInt'

    \remarks 
    Here we need a predefinition for correctness of the 'createObject' object
*/
class OdGsDeviceForTvImpl : public OdGsBaseLayoutHelperImpl<OdGsDeviceForTv, OdTvGsLayoutHelperInt>
{
protected:
  OdGsDeviceForTvImpl();
  virtual ~OdGsDeviceForTvImpl();
  ODRX_HEAP_OPERATORS();

public:

  struct PlotSettings
  {
    bool    m_bEnglishMeasurement;
    bool    m_bPrintLineweights;
    bool    m_bPaperUnitsInches;
    bool    m_bScaleLineWeights;
    double  m_dLayoutScale;
  };

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Returns the smart pointer to the raster image object

  \remark this method is valid only for the bitmap device
  */
  OdGiRasterImagePtr getRasterImage(OdTvResult* rc);
  
  /** \details
    Marks for refresh the specified region of the GUI window of this Device object.
     
    \param screenRect [in]  Rectangular area.
    
    \remarks
    If screenRect is not specified, the entire GUI window is marked for refresh.
  */
  OdTvResult invalidateWrap();

  OdTvResult invalidateWrap(const OdTvDCRect &screenRect);

  /** \details
    Returns true if and only if the GUI window for this Device object is showing the correct image.

    \remarks
    This implies the follow:
    * No part of GUI area is flagged for refresh.
    * All rasterizations are complete
    * The rendering pipeline has been flushed.
  */
  bool isValidWrap(OdTvResult* rc = NULL) const;

  /** \details
    Updates the GUI window for this Device object.
    
    \param pUpdatedRect [out]  Pointer to the a rectangle to receive the region updated by this function.

    \remarks
    This function call is propagated to all OdGsView objects owned by this Device object,
    thus displaying the correct image on the GUI window of this Device object.
  */
  OdTvResult updateWrap(OdTvSceneGraphTimedScheduler* pScheduler, OdTvDCRect* pUpdatedRect = 0);

  /** \details
    Notification function called whenever the size of the GUI window for this Device object has changed.
    
    \param outputRect [in]  New size of the output rectangle in device coordinates (pixels).

    \remarks
    This function should not be called if this Device object has a width and/or height of 0, .
  */
   OdTvResult onSizeWrap(const OdTvDCRect& outputRect);

  /** \details
    Returns device surface output rectangle.

    \param outputRect [out]  Obtains size of the output rectangle in device coordinates (pixels).
  */
  OdTvResult getSizeWrap(OdTvDCRect& outputRect) const;

  /** \details
    Regen the contents of device according to regeneration mode
    
    \param regenMode [in]  Regeneration mode.
  */
  OdTvResult regen(OdTvGsDevice::RegenMode regenMode);


  /** \details
    Notification function called whenever the OS screen resolution and/or color depth have changed.
    
    \param bitsPerPixel [in]  Color depth.
    \param xPixels [in]  X pixels.
    \param yPixels [in]  Y pixels.
  
    \remarks
    This function is called after the operation.  
  */
  OdTvResult onDisplayChangeWrap(int bitsPerPixel, int xPixels, int yPixels);

  /** \details
    Creates a new OdTvGsView object, and associates it with this Device object.
        
    \returns
    Returns an Id to the newly created object.
  */
  OdTvGsViewId createViewWrap(const OdString& name, bool bNeedSaveInFile, OdTvResult* rc = NULL);

  /** \details
    Inserts the specified view object to the tail in this Device object.
    
    \param viewId [in]  Id of the OdTvGsView object.
  */
  OdTvResult addViewGs(const OdTvGsViewId& viewId);

  /** \details
    Inserts the specified view object to the specified position in this Device object.

    \param viewIndex [in]  View index.
    \param viewId [in]  Id of the OdTvGsView object.
  */
  OdTvResult insertViewGs(int viewIndex, const OdTvGsViewId& viewId);

  /** \details
    Erases the specified View object.
    \param viewId[in]  Id of the OdTvGsView object.
    \param viewIndex [in]  View index.
    \returns
    Returns true if and only if successful.
  */
  bool eraseViewWrap(const OdTvGsViewId& viewId, OdTvResult* rc = NULL);
  bool eraseViewWrap(int viewIndex, OdTvResult* rc = NULL);

  /** \details
  Removes the specified View object from the Device object
  \param viewId[in]  Id of the OdTvGsView object.
  \returns
  Returns true if and only if successful.
  */
  bool removeViewWrap(const OdTvGsViewId& viewId, OdTvResult* rc = NULL);

  /** \details
    Erases all views associated with this Device object.
  */
  OdTvResult eraseAllViewsWrap();

  /** \details
    Returns the number of views associated with this Device object.
  */
  int numViewsWrap(OdTvResult* rc = NULL) const;

  /** \details
    Returns the specified OdTvGsView object associated with this Device object.
    \param viewIndex [in]  View index.
  */
  OdTvGsViewId viewAtWrap(int viewIndex, OdTvResult* rc = NULL);

  /** \details
    Sets the Background Color of the GUI window of this Device object.
    \param backgroundColor [in]  Background color.
  */
  bool setBackgroundColorWrap(ODCOLORREF backgroundColor);

  /** \details
    Returns the Background Color of the GUI window of this Device object.
  */
  ODCOLORREF getBackgroundColorWrap(OdTvResult* rc = NULL);

  /** \details
    Sets the logical pallete to be used by this Device object.
    
    \param logicalPalette [in]  Logical palette.
    \param numColors [in]  Number of colors in palette.
    
    \remarks
    The logical pallete is used in the case of indexed colors
  */
  OdTvResult setLogicalPaletteWrap(const ODCOLORREF* logicalPalette, int numColors);

  /** \details
    Returns the logical pallete used by this Device object.

    \param numColors [out]  Number of colors in palette.
  */
  const ODCOLORREF* getLogicalPaletteWrap(int &numColors, OdTvResult* rc = NULL) const;

  /** \details
      Sets a boolean property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  bool property value to set.
  */
  OdTvResult setOption(OdTvGsDevice::Options opt, bool bVal);

  /** \details
      Sets an short integer property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  int property value to set.
  */
  OdTvResult setOption(OdTvGsDevice::Options opt, OdInt16 nVal);

  /** \details
      Sets an integer property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  int property value to set.
  */
  OdTvResult setOption(OdTvGsDevice::Options opt, OdInt32 nVal);

  /** \details
      Sets a double property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  double property value to set.
  */
  OdTvResult setOption(OdTvGsDevice::Options opt, double dVal);

  /** \details
  Sets a double property of the device.

  \param prop [in]  Property to set.
  \param nVal [in]  OdUInt32 property value to set.
  */
  OdTvResult setOption(OdTvGsDevice::Options opt, OdUInt32 nVal);

   /** \details
      Gets a boolean property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  bool property value to get.
  */
  OdTvResult getOption(OdTvGsDevice::Options opt, bool& bVal);

  /** \details
      Gets a short integer property of the device.

      \param prop [in]  Property to get.
      \param dVal [in]  int property value to get.

      \remarks
      If the requested option has another type or is absent the error returned while the reference to the value doesn't change

  */
  OdTvResult getOption(OdTvGsDevice::Options opt, OdInt16& nVal);

  /** \details
      Gets a integer property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  int property value to get.
  */
  OdTvResult getOption(OdTvGsDevice::Options opt, OdInt32& nVal);

  /** \details
      Gets a double property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  double property value to get.
  */
  OdTvResult getOption(OdTvGsDevice::Options opt, double& dVal);

  /** \details
  Gets a double property of the device.

  \param prop [in]  Property to set.
  \param nVal [in]  OdUInt32 property value to get.
  */
  OdTvResult getOption(OdTvGsDevice::Options opt, OdUInt32& nVal);

  /** \details
   Gets a OdIntPtr property of the device.

   \param prop [in]  Property to set.
   \param pVal [in]  OdIntPtr property value to get.
  */
  OdTvResult getOption(OdTvGsDevice::Options opt, OdIntPtr& pVal);

//////////////////////////////////////////////////////////////////////////////////////////////////////
//OdGsDeviceForTvImpl own methods 
/////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
 // base create method
  */
  static OdGsDeviceForTvImplPtr createObject(OdGsDevice* pUnderlyingDevice);

  /** \details
  // calculate line weight scale for plotting
  */
  double calcLwScaleForPlotting(const OdGeMatrix3d& worldToScreen);
  
  /** \details
  set plot settings
  */
  void setPlotSettings(PlotSettings* pSettings);

 /** \details
  simple wrap method
    
  \remarks
  Need to make the class non-abstract
  */
  void update(OdGsDCRect* pUpdatedRect);

  /** \details
  setassociated db object
  */
  void setDbObject(const OdTvDbObjectId& id) { m_dbObjectId = id; }

  /** \details
  get associated db object
  */
  OdTvDbObjectId dbObject() const { return m_dbObjectId;}

  /** \details
    empty method
    
    \remarks
    Just for the interface compatibility with the database objects
  */
  void setOpenMode(OdTv::OpenMode mode);

  /** \details
    remeber/retrun the user context for deleting them in destructor
    
  */
  void rememberUserGiContext(OdGiContext* pCtx, bool bOwned = false) { m_pUserContext = pCtx; m_bOwnedOverContext = bOwned; }
  OdGiContext* getUserGiContext() const {return const_cast<OdGiContext*>(m_pUserContext.get());}

  /** \details
    react on the database delete  
  */
  void transferGoodBye();

  /** \details
    return the appropriate model.
  */
  OdGsModel*  getGsModel(OdTvModelImpl* pDbModel);

  /** \details
  Called inside regen active view functionality
  */
  void regenView(OdGsView* pView);

  /** \details
  return the begin of the views array
  */
  OdTvEntityIdContainerIterator beginViews();

  /** \details
  return the end of the views array
  */
  OdTvEntityIdContainerIterator endViews();

  /** \details
  Set the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be setted.
  \param uValue [in]  Lineweight style value.
  */
  OdTvResult setLineWeightConfiguration(OdTvGsDevice::LineWeightStyle styleEntry, OdUInt8 uValue);

  /** \details
  Returns the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be returned.

  \remarks
  For kPointLineWeight style, 0 will be returned if point lineweight is disabled or 1 will be returned if enabled.
  For kLineCapStyle style, entry will be returned as a member of the OdPs::LineEndStyle enumeration.
  For kLineJoinStyle style, entry will be returned as a member of the OdPs::LineJoinStyle enumeration.
  */
  OdUInt8 getLineWeightConfiguration(OdTvGsDevice::LineWeightStyle styleEntry) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  /** \details
  Add viewport info for the viewport with the given ID
  */
  void addViewportObjectInfo(OdUInt32 viewId, const ViewportInfo& vInfo);

  /** \details
  Notify device about Gs model frred
  */
  void notifyDevicesGsModelFreed(OdGsModel* pGsModel);

  /** \details
  Sets a new value of the perform line smoothing flag, which determines whether anti-aliasing is performed while rendering (if true) or not (if false).
  */
  OdTvResult setLineSmoothing(bool bLS);

  /** \details
  Retrieves the current value of the line smoothing flag, which determines whether anti-aliasing is performed while rendering (if true) or not (if false).
  */
  bool getLineSmoothing(OdTvResult* rc = 0) const;

  /** \details
  Add/remove scheduler to/from device
  */
  OdTvResult updateScheduler(OdTvSceneGraphTimedScheduler* pScheduler, bool bNeedAdd);

private:

  /** \details
    Set property value to the device
    
    \remarks
    This flag helps to control the deletiob state of the object.
  */
  template <class T> 
  OdTvResult setDeviceOption(OdTvGsDevice::Options opt, T& value);

  /** \details
    Get property value from the device
    
    \remarks
    This flag helps to control the deletiob state of the object.
  */
  template <class T> 
  OdTvResult getDeviceOption(OdTvGsDevice::Options opt, T& value);

private:

  OdTvDbObjectId                  m_dbObjectId;         // Id of the associated Db object (OdTvGsDeviceImpl)
  OdSmartPtr<OdGiContext>       m_pUserContext;       // device context
  bool                          m_bOwnedOverContext;  // flag, indicate that this device context should be deleted together with device
  OdArray<ViewportInfo>         m_viewInfos;          // information about the viewports (special type of tv gs view). Non-empty only for export with PE
  PlotSettings*                 m_pPlotSettings;      // some information which will be used for export with PE
};


/** \details
This class is the DB implementation of the object owner over device 'OdGsDeviceForTvImpl'.
This object is the analogy of the OdTvDbLayout
Here it is important to note that 'assertWriteEnabled' not need here.
*/
class OdTvGsDeviceImpl : public OdTvDbObject, public OdTvXDataStorage
{
  OdTvGsDeviceImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvGsDeviceImpl);

  virtual ~OdTvGsDeviceImpl();

  /** \details
  Returns the gs device nme
  */
  OdTvGsDevice::Name getGsDeviceName(OdTvResult* rc = NULL);

  /** \details
  Returns true if this device is bitmap device
  */
  bool getIsBitmap() const;

  /** \details
  Setup the device object if it was created as "non-setup". Otherwise will do nothing

  \param wnd_handle        [in]  Operating system window handle
  \param wndRect           [in]  Window rectangle
  \param device            [in]  Device (GLES2, OpenGL etc)
  \param strVectorizerName [in]  Path toe the device module (only for the case of device == kCustom)

  */
  OdTvResult setupGs(OSWindowHandle wnd_handle, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0);

  /** \details
  Setup the device object if it was created as "non-setup". Otherwise will do nothing

  \param wnd_handle        [in]  Operating system window handle
  \param wnd_context       [in]  Window GL context
  \param device            [in]  Device (GLES2, OpenGL etc)
  \param strVectorizerName [in]  Path to the device module (only for the case of device == kCustom)

  */
  OdTvResult setupGsWithContext(OSWindowGLContext wnd_context, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0);

  /** \details
  Setup the bitmap device object if it was created as "non-setup". Otherwise will do nothing

  \param x,y               [in]  Output image dimension
  \param device            [in]  Device (GLES2, OpenGL etc)
  \param strVectorizerName [in]  Path to the device module (only for the case of device == kCustom)

  */
  OdTvResult setupGsBitmap(long x, long y, OdTvGsDevice::Name device, OdString* strVectorizerName = 0);

  /** \details
  Unload the gs (vectorizer) part for the device object
  */
  OdTvResult unloadGs();

  /** \details
  Sets the name of this Device object

  \param name [in]  Name.

  \returns
  Returns tvOk if successful, or an internal error if fial
  */
  OdTvResult setName(const OdString& name);

  /** \details
  Returns the name of this db device object object.
  */
  OdString getName() const;

  /** \details
  Set the underlaying tv gs device
  */
  void setUnderlyingTvDevice(OdGsDeviceForTvImpl* pTvDeviceImpl) { m_pUnderlayTvGsDeviceImpl = pTvDeviceImpl; }

  /** \details
  Get the underlaying tv gs device
  */
  OdGsDeviceForTvImplPtr getUnderlyingTvDevice() const
  {
    return m_pUnderlayTvGsDeviceImpl;
  }

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Sets the logical palette to be used by this Device object.

  \param logicalPalette [in]  Logical palette.
  \param numColors [in]  Number of colors in palette.

  \remarks
  The logical palette is used in the case of indexed colors
  */
  void setLogicalPalette(const ODCOLORREF* logicalPalette, int numColors);

  /** \details
  Returns the logical palette used by this Device object.

  \param numColors [out]  Number of colors in palette.
  */
  const ODCOLORREF* getLogicalPalette(int &numColors) const;

  /** \details
  Sets the background color for this Device object.
  \param backgroundColor [in]  Background color.
  */
  void setBackgroundColor(ODCOLORREF backgroundColor);

  /** \details
  Returns the background color for this Device object.
  */
  ODCOLORREF getBackgroundColor();

  /** \details
  Marks that this device is bitmap device or not
  */
  void setIsBitmap(bool bIsBitmap);

  /** \details
  Set On/off FPS displaying for the device
  */
  OdTvResult setShowFPS(bool bShow, bool bInternal = false);

  /** \details
  Get On/off FPS displaying for the device
  */
  bool getShowFPS(OdTvResult* rc = 0) const;

  /** \details
  Set the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be setted.
  \param uValue [in]  Lineweight style value.
  */
  OdTvResult setLineWeightConfiguration(OdTvGsDevice::LineWeightStyle styleEntry, OdUInt8 uValue);

  /** \details
  Returns the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be returned.

  \remarks
  For kPointLineWeight style, 0 will be returned if point lineweight is disabled or 1 will be returned if enabled.
  For kLineCapStyle style, entry will be returned as a member of the OdPs::LineEndStyle enumeration.
  For kLineJoinStyle style, entry will be returned as a member of the OdPs::LineJoinStyle enumeration.
  */
  OdUInt8 getLineWeightConfiguration(OdTvGsDevice::LineWeightStyle styleEntry) const;

  /** \details
  Set the true if device must be is active
  */
  OdTvResult setActive(bool bIsActive);

  /** \details
  Returns true if current device is active
  */
  bool getActive(OdTvResult* rc = NULL) const;

  /** \details
  Set the true if device should work in background partial view mode
  Relevant only if the database was opened in partial load mode.
  Enables special mode while the loading of the objects happens in a separate background thread
  */
  OdTvResult setBackgroundPartialView(bool bIsInBackground);

  /** \details
  Returns true if this device is in background partial view mode
  */
  bool getBackgroundPartialView(OdTvResult* rc = NULL) const;

  /** \details
  Returns true if this device is in background partial view mode and partial loading task is in progress
  */
  bool getBackgroundPartialViewingInProgress(OdTvResult* rc = NULL) const;

  /** \details
  Disables partial viewing
  */
  void disablePartialViewing();

  /** \details
  Updates the GUI window for this Device object.
  */
  OdTvResult update(OdTvDCRect* pUpdatedRect = 0, bool bSkipPartialRequest = false);

  /** \details
  Assigns the OdTvRegenAbort to the device
  */
  OdTvResult setRegenAbort(OdTvRegenAbort* pRegenAbort);

  /** \details
  Returns the assigned OdTvRegenAbort instance
  */
  OdTvRegenAbort* getRegenAbort(OdTvResult* rc = NULL) const;

  /** \details
  Notification function called whenever the size of the GUI window for this Device object has changed.

  \param outputRect [in]  New size of the output rectangle in device coordinates (pixels).

  \remarks
  This function should not be called if this Device object has a width and/or height of 0, .
  */
  virtual OdTvResult onSize(const OdTvDCRect& outputRect);

  /** \details
  Sets a new value of the perform line smoothing flag, which determines whether anti-aliasing is performed while rendering (if true) or not (if false).
  */
  OdTvResult setLineSmoothing(bool bLS);

  /** \details
  Retrieves the current value of the line smoothing flag, which determines whether anti-aliasing is performed while rendering (if true) or not (if false).
  */
  bool getLineSmoothing(OdTvResult* rc = 0) const;

  /** \details
  Specifies the time frame within one 'update' call after which the scene graph building operations should be interrupted.
  */
  OdTvResult setSceneGraphCreationInteruptTime(OdUInt32 mSec);

  /** \details
  Specifies that it is need to delay scene graph processing
  */
  OdTvResult setSceneGraphDelayProc(bool bDelay);

  /** \details
  Sets a new TTF Draw mode for the device object.
  */
  OdTvResult setTTFDrawMode(OdTvGsDevice::TTFDrawMode mode, OdUInt32* textQuality = NULL);

  /** \details
  Retrieves the current TTF Draw mode of the device object.
  */
  OdTvGsDevice::TTFDrawMode getTTFDrawMode(OdUInt32* textQuality = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Sets a new highlight style to the device.
  */
  OdTvResult setHighlightStyle(const OdTvHighlightStyleId& highlightStyleId, bool bAutoRegen = true);

  /** \details
  Retrieves the current highlight style for the device.
  */
  OdTvHighlightStyleId getHighlightStyle(OdTvResult* rc = NULL) const;

  /** \details
  Sets an array of used highlight styles to the device. Different objects can be highlighted with styles from this array.
  */
  OdTvResult setHighlightStyles(const OdArray<OdTvHighlightStyleId>& styles, bool bAutoRegen = true);
  
  /** \details
  Retrieves the array of highlight styles for the device. Different objects can be highlighted with styles from this array.
  */
  OdArray<OdTvHighlightStyleId> getHighlightStyles(OdTvResult* rc = NULL) const;

  //METHODS FOR THE INTERNAL USING
  OdTvEntityIdContainerIterator beginViews();
  OdTvEntityIdContainerIterator endViews();
  OdTvEntityIdContainerConstIterator beginViewsConst() const;
  OdTvEntityIdContainerConstIterator endViewsConst() const;
  void removeView(OdTvDbObjectId viewId);
  void appendView(OdTvDbObjectId viewId);
  void clearViews();
  void changeViewPosDueToAdd(OdTvDbObjectId viewId);

  void setGsDeviceName(OdTvGsDevice::Name deviceName) { m_deviceName = deviceName; }
  void setTvDatabase(OdTvDatabaseId dbId) { m_tvDbId = dbId; }

  OdTvGsViewId  createView(const OdString& name, bool bNeedSaveInFile, OdTvResult* rc);
  OdTvResult    addView(const OdTvGsViewId& viewId);
  OdTvResult    insertView(int viewIndex, const OdTvGsViewId& pView);
  bool          eraseView(const OdTvGsViewId& viewId, OdTvResult* rc = NULL);
  bool          eraseView(int viewIndex, OdTvResult* rc = NULL);
  bool          removeView(const OdTvGsViewId& viewId, OdTvResult* rc = NULL);
  OdTvResult    eraseAllViews();
  int           numViews(OdTvResult* rc) const;
  OdTvGsViewId  viewAt(int viewIndex, OdTvResult* rc = NULL);
  OdTvGsViewId  viewAt(const OdTvPoint2d &pt, OdTvResult* rc = NULL);
  OdTvGsViewId  getActiveView(OdTvResult* rc = NULL);

  OdRxDictionaryPtr properties() { return m_devicePropertiesPtr; }

  /** \details
  This method is for using from other ODA Platform projects (Cloud)
  Make it virtual for using from other internal ODA Platform modules without exporting

  void* device is the third-party device, inherited from OdGsDevice
  */
  virtual OdTvResult setupGsFromExternal(void* device);

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  /** \details
  Returns pointer to Data Manager Context, may be NULL
  */
  OdTvGsDeviceDataManagerContext* dataManagerContext()
  {
    return m_pDataManagerContext.get();
  }
  /** \details
  Checks whether underlying views are invalid
  */
  bool isUnderlyingViewsInvalid( bool bSkipInternal = true );

private:

  /** \details
  Retrieve the number of views that should be save in file
  */
  unsigned int getNumOfSavedViews() const;

  /** \details
  Add or remove temporary view and model for FPS show
  */
  void updateFPSTemporaryGeometry(bool bShow);

  

private:

  OdTvEntityIdContainer         m_views;              // array of views (OdTvGsViewImpl)
  OdGsDeviceForTvImplPtr        m_pUnderlayTvGsDeviceImpl;
  OdTvGsDevice::Name            m_deviceName;
  ODTVPALETTE                   m_logPalette;         // palette
  ODCOLORREF                    m_backgroundColor;
  bool                          m_bIsBitmap;    // marks that this device is bitmap device(createBitmapDevice)

  bool                          m_bUnloadGsState; // real time flag

  OdPerfTimerBase*                m_pTimer;         //real time parameter
  OdTvSceneGraphTimedSchedulerPtr m_pScheduler;      //scene graph scheduler (real time not for save)
  OdMutexPtr                      m_pSchedulerMutex;

  //FPS stuff (real time)
  bool                          m_bIsFPSOn;   //should be FPS displayed or not
  OdTvGsViewId                  m_FPSView;
  OdTvModelId                   m_FPSModel;
  OdTvGeometryDataId            m_FPSValue;
  OdTvDatabaseId                m_tvDbId;

  //Lineweight configuration
  OdUInt8              m_uPointLineWeight;
  OdUInt8              m_uLineCapStyle;
  OdUInt8              m_uLineJoinStyle;

  //Device properties
  OdTvDevicePropertiesPtr m_devicePropertiesPtr;

  // Partial vieving manager context
  OdTvGsDeviceDataManagerContextPtr m_pDataManagerContext;

  // active flag
  bool                 m_bActive;

  // working in background in the case of partial viewing
  bool                 m_bInBackgroundPartialView;

  // Pointer to the regenAbort functor
  OdTvRegenAbort*      m_pRegenAbort;

  //Anti-aliasing state
  bool                m_bAntiAliasingOn;

  bool                m_bUpdating;

  // TTF Draw mode
  OdTvGsDevice::TTFDrawMode m_ttfDrawMode;
  OdUInt32                  m_uTxtQuality;

  OdArray<OdTvHighlightStyleId>  m_highlightStyles;
};

typedef OdSmartPtr<OdTvGsDeviceImpl> OdTvGsDeviceImplPtr;


/** \details
    This is an wrapper of the interface class for OdTvGsDevice object.

    \remarks
    The purpose of this class is to connect the internal device object with an interface object
*/
  
class OdTvGsDeviceWrapper : public OdTvGsDevice
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvGsDevice, OdTvGsDeviceImpl)

  friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Returns the gs device nme
  */
  virtual OdTvGsDevice::Name getGsDeviceName(OdTvResult* rc = NULL);

  /** \details
  Sets the name for the device

  \param sName [in]  Entity name
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the name of the device
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Returns true if this device is bitmap device
  */
  virtual bool isBitmap(OdTvResult* rc = NULL) const;

  /** \details
  Setup the device object if it was created as "non-setup". Otherwise will do nothing

  \param wnd_handle        [in]  Operating system window handle
  \param wndRect           [in]  Window rectangle
  \param device            [in]  Device (GLES2, OpenGL etc)
  \param strVectorizerName [in]  Path toe the device module (only for the case of device == kCustom)

  */
  virtual OdTvResult setupGs(OSWindowHandle wnd_handle, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0);

  /** \details
  Setup the device object if it was created as "non-setup". Otherwise will do nothing

  \param wnd_handle        [in]  Operating system window handle
  \param wnd_context       [in]  Window GL context
  \param device            [in]  Device (GLES2, OpenGL etc)
  \param strVectorizerName [in]  Path to the device module (only for the case of device == kCustom)

  */
  virtual OdTvResult setupGsWithContext(OSWindowGLContext wnd_context, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0);

  /** \details
  Setup the bitmap device object if it was created as "non-setup". Otherwise will do nothing

  \param x,y               [in]  Output image dimension
  \param device            [in]  Device (GLES2, OpenGL etc)
  \param strVectorizerName [in]  Path to the device module (only for the case of device == kCustom)

  */
  virtual OdTvResult setupGsBitmap(long x, long y, OdTvGsDevice::Name device, OdString* strVectorizerName = 0);

  /** \details
  Returns true if the gs part of the device is loaded
  */
  virtual bool isGsLoaded(OdTvResult* rc = NULL);

  /** \details
  Unload the gs (vectorizer) part for the device object
  */
  virtual OdTvResult unloadGs();

  /** \details
  Returns the smart pointer to the raster image object

  \remark this method is valid only for the bitmap device
  */
  virtual OdGiRasterImagePtr getRasterImage(OdTvResult* rc = NULL);

  /** \details
    Marks for refresh the specified region of the GUI window of this Device object.
     
    \param screenRect [in]  Rectangular area.
    
    \remarks
    If screenRect is not specified, the entire GUI window is marked for refresh.
  */
  virtual OdTvResult invalidate();

  virtual OdTvResult invalidate(const OdTvDCRect &screenRect);

  /** \details
    Returns true if and only if the GUI window for this Device object is showing the correct image.

    \remarks
    This implies the follow:
    * No part of GUI area is flagged for refresh.
    * All rasterizations are complete
    * The rendering pipeline has been flushed.
  */
  virtual bool isValid(OdTvResult* rc = NULL) const;

  /** \details
    Updates the GUI window for this Device object.
    
    \param pUpdatedRect [out]  Pointer to the a rectangle to receive the region updated by this function.
    \param bSkipPartialRequest [in]  If true, Partial viewing will be disabled for this call

    \remarks
    This function call is propagated to all OdGsView objects owned by this Device object,
    thus displaying the correct image on the GUI window of this Device object.
  */
  virtual OdTvResult update(OdTvDCRect* pUpdatedRect = 0, bool bSkipPartialRequest = false );

  /** \details
    Notification function called whenever the size of the GUI window for this Device object has changed.
    
    \param outputRect [in]  New size of the output rectangle in device coordinates (pixels).

    \remarks
    This function should not be called if this Device object has a width and/or height of 0, .
  */
  virtual OdTvResult onSize(const OdTvDCRect& outputRect);

  /** \details
    Returns device surface output rectangle.

    \param outputRect [out]  Obtains size of the output rectangle in device coordinates (pixels).
  */
  virtual OdTvResult getSize(OdTvDCRect& outputRect) const;


  /** \details
    Notification function called whenever the OS screen resolution and/or color depth have changed.
    
    \param bitsPerPixel [in]  Color depth.
    \param xPixels [in]  X pixels.
    \param yPixels [in]  Y pixels.
  
    \remarks
    This function is called after the operation.  
  */
  virtual OdTvResult onDisplayChange(int bitsPerPixel, int xPixels, int yPixels);

  /** \details
    Creates a new OdTvGsView object, and associates it with this Device object.
        
    \returns
    Returns an Id to the newly created object.
  */
  virtual OdTvGsViewId createView(const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL);

  /** \details
    Inserts the specified view object to the tail in this Device object.
    
    \param viewId [in]  Id of the OdTvGsView object.
  */
  virtual OdTvResult addView(const OdTvGsViewId& viewId);

  /** \details
    Inserts the specified view object to the specified position in this Device object.

    \param viewIndex [in]  View index.
    \param viewId [in]  Id of the OdTvGsView object.
  */
  virtual OdTvResult insertView(int viewIndex, const OdTvGsViewId& viewId);

  /** \details
    Erases the specified View object.
    \param viewId[in]  Id of the OdTvGsView object.
    \param viewIndex [in]  View index.
    \returns
    Returns true if and only if successful.
  */
  virtual bool eraseView(const OdTvGsViewId& viewId, OdTvResult* rc = NULL);
  virtual bool eraseView(int viewIndex, OdTvResult* rc = NULL);

  /** \details
  Removes the specified View object from the Device object
  \param viewId[in]  Id of the OdTvGsView object.
  \returns
  Returns true if and only if successful.
  */
  virtual bool removeView(const OdTvGsViewId& viewId, OdTvResult* rc = NULL);

  /** \details
    Erases all views associated with this Device object.
  */
  virtual OdTvResult eraseAllViews();

  /** \details
    Returns the number of views associated with this Device object.
  */
  virtual int numViews(OdTvResult* rc = NULL) const;

  /** \details
    Returns the specified OdTvGsView object associated with this Device object.
    \param viewIndex [in]  View index.
  */
  virtual OdTvGsViewId viewAt(int viewIndex, OdTvResult* rc = NULL);

  /** \details
  Returns the specified OdTvGsView object associated with this Device object.
  \param pt [in]  Point of view.
  */
  virtual OdTvGsViewId viewAt(const OdTvPoint2d &pt, OdTvResult* rc = NULL);

  /** \details
  Returns the active OdTvGsView object associated with this Device object.
  If there is no active views - this metod returns empty view
  */
  virtual OdTvGsViewId getActiveView(OdTvResult* rc = NULL);

  /** \details
    Sets the Background Color of the GUI window of this Device object.
    \param backgroundColor [in]  Background color.
  */
  virtual OdTvResult setBackgroundColor(ODCOLORREF backgroundColor);

  /** \details
    Returns the Background Color of the GUI window of this Device object.
  */
  virtual ODCOLORREF getBackgroundColor(OdTvResult* rc = NULL);

  /** \details
    Sets the logical pallete to be used by this Device object.
    
    \param logicalPalette [in]  Logical palette.
    \param numColors [in]  Number of colors in palette.
    
    \remarks
    The logical pallete is used in the case of indexed colors
  */
  virtual OdTvResult setLogicalPalette(const ODCOLORREF* logicalPalette, int numColors);

  /** \details
    Returns the logical pallete used by this Device object.

    \param numColors [out]  Number of colors in palette.
  */
  virtual const ODCOLORREF* getLogicalPalette(int &numColors, OdTvResult* rc = NULL) const;

  /** \details
    Regen the contents of device according to regeneration mode
    
    \param regenMode [in]  Regeneration mode.
  */
  virtual OdTvResult regen(RegenMode regenMode);

  /** \details
      Sets a boolean property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  bool property value to set.
  */
  virtual OdTvResult setOption(Options opt, bool bVal);

  /** \details
      Sets an short integer property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  int property value to set.
  */
  virtual OdTvResult setOption(Options opt, OdInt16 nVal);

  /** \details
      Sets an integer property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  int property value to set.
  */
  virtual OdTvResult setOption(Options opt, OdInt32 nVal);

  /** \details
      Sets a double property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  double property value to set.
  */
  virtual OdTvResult setOption(Options opt, double dVal);

  /** \details
  Sets a double property of the device.

  \param prop [in]  Property to set.
  \param nVal [in]  OdUInt32 property value to set.
  */
  virtual OdTvResult setOption(Options opt, OdUInt32 nVal);

   /** \details
      Gets a boolean property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  bool property value to get.
  */
  virtual OdTvResult getOption(Options opt, bool& bVal);

  /** \details
      Gets a short integer property of the device.

      \param prop [in]  Property to get.
      \param dVal [in]  int property value to get.

      \remarks
      If the requested option has another type or is absent the error returned while the reference to the value doesn't change

  */
  virtual OdTvResult getOption(Options opt, OdInt16& nVal);

  /** \details
      Gets a integer property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  int property value to get.
  */
  virtual OdTvResult getOption(Options opt, OdInt32& nVal);

  /** \details
      Gets a double property of the device.

      \param prop [in]  Property to set.
      \param dVal [in]  double property value to get.
  */
  virtual OdTvResult getOption(Options opt, double& dVal);

  /** \details
  Gets a double property of the device.

  \param prop [in]  Property to set.
  \param nVal [in]  OdUInt32 property value to get.
  */
  virtual OdTvResult getOption(Options opt, OdUInt32& nVal);

  /** \details
  Gets a OdIntPtr property of the device.

  \param prop [in]  Property to set.
  \param pVal [in]  OdIntPtr property value to get.
  */
  virtual OdTvResult getOption(Options opt, OdIntPtr& pVal);

  /** \details
  Set On/off FPS displaying for the device

  */
  virtual OdTvResult setShowFPS(bool bShow);

  /** \details
  Get On/off FPS displaying for the device

  */
  virtual bool getShowFPS(OdTvResult* rc = 0) const;

  /** \details
  Set the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be setted.
  \param uValue [in]  Lineweight style value.
  */
  virtual OdTvResult setLineWeightConfiguration(LineWeightStyle styleEntry, OdUInt8 uValue);

  /** \details
  Returns the lineweight display style configuration.

  \param styleEntry [in]  Lineweight style entry for which the current setting will be returned.

  \remarks
  For kPointLineWeight style, 0 will be returned if point lineweight is disabled or 1 will be returned if enabled.
  For kLineCapStyle style, entry will be returned as a member of the LineEndStyle enumeration.
  For kLineJoinStyle style, entry will be returned as a member of the LineJoinStyle enumeration.
  */
  virtual OdUInt8 getLineWeightConfiguration(LineWeightStyle styleEntry, OdTvResult* rc = NULL) const;

  /** \details
  Set the true if device must be is active
  */
  virtual OdTvResult setActive(bool bIsActive);

  /** \details
  Returns true if current device is active
  */
  virtual bool getActive(OdTvResult* rc = NULL) const;

  /** \details
  Set the true if device should work in background partial view mode
  Relevant only if the database was opened in partial load mode.
  Enables special mode while the loading of the objects happens in a separate background thread
  */
  virtual OdTvResult setBackgroundPartialView(bool bIsInBackground);

  /** \details
  Returns true if this device is in background partial view mode
  */
  virtual bool getBackgroundPartialView(OdTvResult* rc = NULL) const;

  /** \details
  Returns true if this device is in background partial view mode and partial loading task is in progress
  */
  virtual bool getBackgroundPartialViewingInProgress(OdTvResult* rc = NULL) const;

  /** \details
  Assigns the OdTvRegenAbort to the device
  */
  virtual OdTvResult setRegenAbort(OdTvRegenAbort* pRegenAbort);

  /** \details
  Returns the assigned OdTvRegenAbort instance
  */
  virtual OdTvRegenAbort* getRegenAbort(OdTvResult* rc = NULL) const;

  /** \details
  Sets a new value of the perform line smoothing flag, which determines whether anti-aliasing is performed while rendering (if true) or not (if false).
  */
  virtual OdTvResult setLineSmoothing(bool bLS);

  /** \details
  Retrieves the current value of the line smoothing flag, which determines whether anti-aliasing is performed while rendering (if true) or not (if false).
  */
  virtual bool getLineSmoothing(OdTvResult* rc = 0) const;

  /** \details
  Specifies the time frame within one 'update' call after which the scene graph building operations should be interrupted.
  */
  virtual OdTvResult setSceneGraphCreationInteruptTime(OdUInt32 mSec);

  /** \details
  Sets a new TTF Draw mode for the device object.
  */
  virtual OdTvResult setTTFDrawMode(TTFDrawMode mode, OdUInt32* textQuality = NULL);

  /** \details
  Retrieves the current TTF Draw mode of the device object.
  */
  virtual TTFDrawMode getTTFDrawMode(OdUInt32* textQuality = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Sets a new highlight style to the device.
  */
  virtual OdTvResult setHighlightStyle(const OdTvHighlightStyleId& highlightStyleId, bool bAutoRegen = true);

  /** \details
  Retrieves the current highlight style for the device.
  */
  virtual OdTvHighlightStyleId getHighlightStyle(OdTvResult* rc = NULL) const;

  /** \details
  Sets an array of used highlight styles to the device. Different objects can be highlighted with styles from this array.
  */
  virtual OdTvResult setHighlightStyles(const OdArray<OdTvHighlightStyleId>& styles, bool bAutoRegen = true);

  /** \details
  Retrieves the array of highlight styles for the device. Different objects can be highlighted with styles from this array.
  */
  virtual OdArray<OdTvHighlightStyleId> getHighlightStyles(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
};


/** \details
This is an implementation of the iterator class for the devices
*/
class ODTV_EXPORT OdTvDevicesIteratorImpl : public OdTvDevicesIterator
{
  friend class OdTvDatabaseImpl;
public:

  virtual ~OdTvDevicesIteratorImpl();

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the device currently referenced by this Iterator object.
  */
  virtual OdTvGsDeviceId getDevice(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified device.
  \param objectId [in]  Linetype ID.
  */
  virtual OdTvResult seek(const OdTvGsDeviceId& Deviced);

  /** \details
  Methods for creating the object
  */
  static OdTvDevicesIteratorPtr createObject(OdTvDbDictionaryIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvDevicesIteratorImpl();
  OdTvDevicesIteratorImpl(OdTvDbDictionaryIterator* pDbIterator);

  // Db iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};


#endif // _ODTV_GSDEVICEIMPL_H_INCLUDED_

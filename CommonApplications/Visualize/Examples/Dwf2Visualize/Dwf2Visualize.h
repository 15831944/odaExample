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

#ifndef _TV_DWF2VISUALIZE_H_
#define _TV_DWF2VISUALIZE_H_

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"
#include "RxObject.h"
#include "StaticRxObject.h"
#include "ExSystemServices.h"
#include "TvVisualizeFiler.h"

//SEA
#include "GsVisualizeVectorizer.h"

#include "DwfHostAppServices.h"
#include "DwfDatabase.h"
#include "DwfGsLayoutHelper.h"
#include "DwfObjectImpl.h"

namespace DWF2Visualize
{
/** \details
This class implements the properties of the dwf loader
*/
class OdTvVisualizeDwfFilerProperties : public OdRxDispatchImpl<>
{
  enum ParamFlags
  {
    kObjectNaming = 1,                  // Give the names for the tv entities according to the file objects name (like AcDbCircle etc). If object names exist
    kStoreSource = 2,                   // Store source objects (OdDbEntities)
    kClearEmptyObjects = 4,             // Clear empty objects
    kConvertIndexedToRGB = 16,          // Converted indexed colors to RGB during import
  };

public:
  OdTvVisualizeDwfFilerProperties();
  ~OdTvVisualizeDwfFilerProperties() ODRX_OVERRIDE_DESTRUCTOR;

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeDwfFilerProperties);
  static OdRxDictionaryPtr createObject();

  void      setBackgroundColor(OdIntPtr pBackgroundColor);
  OdIntPtr  getBackgroundColor() const;

  void      setPalette(OdIntPtr palette); //palette should have 256 colors
  OdIntPtr  getPalette() const;

  void      setDCRect(OdIntPtr rect);   //should be pointer to OdTvDCRect
  OdIntPtr  getDCRect() const;

  void setObjectNaming(bool bSet) { SETBIT(m_flags, kObjectNaming, bSet); }
  bool getObjectNaming() const { return GETBIT(m_flags, kObjectNaming); }

  void setStoreSourceObjects(bool bSet) { SETBIT(m_flags, kStoreSource, bSet); }
  bool getStoreSourceObjects() const { return GETBIT(m_flags, kStoreSource); }

  void setClearEmptyObjects(bool bSet) { SETBIT(m_flags, kClearEmptyObjects, bSet); }
  bool getClearEmptyObjects() const { return GETBIT(m_flags, kClearEmptyObjects); }

  void setFeedbackForChooseCallback(OdIntPtr pCallback);
  OdIntPtr getFeedbackForChooseCallback() const;

  void      setAppendTransform(OdIntPtr pTransform);
  OdIntPtr  getAppendTransform() const;

  void      setConvertIndexedToRGB(bool b) { SETBIT(m_flags, kConvertIndexedToRGB, b); }
  bool      getConvertIndexedToRGB() const { return GETBIT(m_flags, kConvertIndexedToRGB); }

protected:

  ODCOLORREF                     m_background;        // Background color. Default: black
  const ODCOLORREF*              m_pPalette;          // Palette to be used. If NULL, one of two default palettes will be used depending on background color. Should have 256 colors
  OdTvDCRect                     m_importRect;        // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
  OdUInt16                       m_flags;             // Different options
  OdTvFeedbackForChooseCallback  m_pCallback;         // Callback for choose
  OdTvMatrix                     m_appendTransform;   // Transform for the append
};
typedef OdSmartPtr<OdTvVisualizeDwfFilerProperties> OdTvVisualizeDwfFilerPropertiesPtr;
}


/** \details
This class is an interface for the internal helper objects used inside the import process
*/
class OdTvVisualizeDwfFilerSource
{
public:
  virtual ~OdTvVisualizeDwfFilerSource() {};
  virtual OdDwfDatabasePtr getDb() = 0;
  virtual OdString getFilename() = 0;
  virtual double getInitTime() { return 0.0; }
};


/** \details
This class is dwf loader (to the Visualize database)
*/
class OdTvVisualizeDwfFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeDwfFiler();
  OdRxDictionaryPtr properties() ODRX_OVERRIDE { return m_properties; }
  OdTvDatabaseId loadFrom(OdDbBaseDatabase*   pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvDatabaseId loadFrom(OdStreamBuf*        pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvDatabaseId loadFrom(const OdString&     filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const ODRX_OVERRIDE;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;

private:
  OdTvDatabaseId loadFrom(OdTvVisualizeDwfFilerSource *pDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

  OdTvModelId appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizeDwfFilerSource *pDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  void        setupTvViews(OdDwfViewPtr pDwfView, OdDwfGsLayoutHelperPtr pLayoutHelper, OdTvGsDeviceId idTVDevice, const ODCOLORREF& borderColor, OdTv::Units units,
                           double userDefCoefToMeters, OdString* pNewModelName = NULL) const;
  int         getActiveViewId(OdDwfGsLayoutHelperPtr pLayoutHelper, bool bPaperSpace, int& iPaperViewId) const;
  void        setViewBorderProperties(OdGsDevice* pDevice, const ODCOLORREF& color) const;
  void        getChoosedSpaces(OdDwfDatabasePtr pDbDatabase, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled) const;
  void        setViewAndModelNames(const OdTvGsViewId& viewId, const OdString& deviceName, const OdGsClientViewInfo& viewInfo, OdTv::Units units,
                                   double userDefCoefToMeters, OdString* pNewModelName = NULL) const;
  void        setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, bool bUseTimeProfiling,
                                            const OdString& modelSpaceName, const OdString& strDwfPath, const DWF2Visualize::OdTvVisualizeDwfFilerPropertiesPtr& importProperties,
                                            const ExGsVisualizeDeviceCache& deviceCache, OdTvGsDeviceId& tvDeviceIdForAppend, bool bHavePaperSpace) const;
private:
  DWF2Visualize::OdTvVisualizeDwfFilerPropertiesPtr m_properties;
};


/** \details
This class is dwf loader module implementation
*/
class OdTvVisualizeDwfFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const ODRX_OVERRIDE;

  void initApp() ODRX_OVERRIDE;
  void uninitApp() ODRX_OVERRIDE;
};

/** \details
This class is service for getting database for dwf file
*/
class OdTvDwfServices : public ExSystemServices, public OdDwfHostAppServices
{
public:
  OdTvDwfServices()
  {}
};

#include "TD_PackPop.h"

#endif

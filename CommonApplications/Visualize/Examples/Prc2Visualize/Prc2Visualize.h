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

#ifndef _TV_PRC2VISUALIZE_H_
#define _TV_PRC2VISUALIZE_H_


#include "TD_PackPush.h"

#include "RxDispatchImpl.h"
#include "RxObject.h"

#include "DbGsManager.h"

#include "PrcCommon.h"
#include "ExSystemServices.h"
#include "ExPrcHostAppServices.h"
#include "PrcFile.h"

#include "OdFileBuf.h"
#include "GiGs/PrcGsManager.h"

#include "TvVisualizeFiler.h"

namespace PRC2Visualize {
  /** \details
  This class implements the properties of the prc loader
  */
  class OdTvVisualizePrcFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kObjectNaming = 1,        // Give the names for the tv entities according to the file objects name (like AcDbCircle etc). If object names exist
      kStoreSource = 2,         // Store source objects (OdDbEntities)
      kClearEmptyObjects = 4,   // Clear empty objects
      kRearrangeObjects = 8,    // Rearrange objects
      kImportBrepAsBrep = 16    // import brep as OdTvBrepData
    };

  public:
    OdTvVisualizePrcFilerProperties();
    virtual ~OdTvVisualizePrcFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizePrcFilerProperties);
    static OdRxDictionaryPtr createObject();

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

    void setRearrangeObjects(bool bSet) { SETBIT(m_flags, kRearrangeObjects, bSet); }
    bool getRearrangeObjects() const { return GETBIT(m_flags, kRearrangeObjects); }

    void setImportBrepAsBrep(bool bSet) { SETBIT(m_flags, kImportBrepAsBrep, bSet); }
    bool getImportBrepAsBrep() const { return GETBIT(m_flags, kImportBrepAsBrep); }

    void      setBrepFacetRes(double dFacetRes);
    double    getBrepFacetRes() const;

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

  protected:

    const ODCOLORREF*       m_pPalette;               // Palette to be used. If NULL, one of two default palettes will be used depending on background color. Should have 256 colors
    OdTvDCRect              m_importRect;             // Output rectangle. Used for correct import of some specific objects (OLE image, camera). The normal way is to set the output window size
    OdUInt8                 m_flags;                  // Different options
    OdTvMatrix              m_appendTransform;        // Transform for the append
    double                  m_dFACETRES;              // Facet res value (between from 0.01 to 10.0)

  };
  typedef OdSmartPtr<OdTvVisualizePrcFilerProperties> OdTvVisualizePrcFilerPropertiesPtr;
}

/** \details
This class is an interface for the internal helper objects used inside the import process
*/
class OdTvVisualizePrcFilerDbSource
{
public:
  virtual ~OdTvVisualizePrcFilerDbSource() {};
  virtual OdPrcFilePtr      getDb() = 0;
  virtual OdString          getFilename() = 0;
  virtual double            getInitTime() const { return 0; }
  virtual bool              odWasInitialized() const { return true; }
};

/** \details
This class is prc loader (to the Visualize database)
*/
class OdTvVisualizePrcFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizePrcFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:

  OdTvDatabaseId  loadFrom(OdTvVisualizePrcFilerDbSource *pPrcDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvModelId     appendFrom(const OdTvDatabaseId& databaseId, OdTvVisualizePrcFilerDbSource *pPrcDatabaseSource, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  int             getActiveViewId(OdGsPrcLayoutHelper* pLayoutHelper) const;
  OdTvGsViewId    getActiveTvView(OdTvDatabaseId& dbId, int iActViewViewInd) const;

private:
  PRC2Visualize::OdTvVisualizePrcFilerPropertiesPtr m_properties;
};

/** \details
This class is prc loader module implementation
*/
class OdTvVisualizePrcFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};

class TvRxSystemServicesImpl : public OdRxSystemServices
{
public:
  TvRxSystemServicesImpl() {};

  OdInt64 getFileCTime(const OdString& filename) { return 0; };
  OdInt64 getFileMTime(const OdString& filename) { return 0; };
  OdInt64 getFileSize(const OdString& filename) { return 0; };

  OdString formatMessage(unsigned int formatId, va_list* argList = 0) { return OD_T(""); };

  /** \details
  Returns the system code page.

  \remarks
  On Windows platforms system code page is initialized based on computer's
  Regional Settings. On other platforms with CP_UNDEFINED.
  It can be altered by setSystemCodePage()
  */
  OdCodePageId systemCodePage() const { return CP_UNDEFINED; };

  OdResult getEnvVar(const OdString &varName, OdString &value)
  {
    return eNotImplemented;
  };

  OdResult setEnvVar(const OdString &varName, const OdString &newValue)
  {
    return eNotImplemented;
  };
};

/** \details
This class is service for getting database for prc file
*/
class OdTvPrc2VisService : public OdPrcHostAppServices, public OdDbHostAppProgressMeter, public TvRxSystemServicesImpl
{
public:
  virtual void start(const OdString& displayString = OdString::kEmpty) { };
  virtual void stop() { };
  virtual void meterProgress() { };
  virtual void setLimit(int max) { };

  virtual OdHatchPatternManager* patternManager() { return NULL; }

protected:
  ODRX_USING_HEAP_OPERATORS(TvRxSystemServicesImpl);

};

#include "TD_PackPop.h"

#endif

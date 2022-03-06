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

#ifndef _TV_VSF2VISUALIZE_H_
#define _TV_VSF2VISUALIZE_H_

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"
#include "RxObject.h"
#include "StaticRxObject.h"
#include "ExSystemServices.h"
#include "TvVisualizeFiler.h"
#include "DbBaseHostAppServices.h"

namespace VSF2Visualize
{
  /** \details
  This class implements the properties of the vsf loader
  */
  class OdTvVisualizeVsfFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kMtImport = 1   // Import file in multi-threading mode.
    };
  public:
    OdTvVisualizeVsfFilerProperties();
    ~OdTvVisualizeVsfFilerProperties() ODRX_OVERRIDE_DESTRUCTOR;

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeVsfFilerProperties);
    static OdRxDictionaryPtr createObject();

    void setMTImport( bool bSet ) { SETBIT( m_flags, kMtImport, bSet ); }
    bool getMTImport() const { return GETBIT( m_flags, kMtImport ); }

    void      setAppendTransform( OdIntPtr pTransform );
    OdIntPtr  getAppendTransform() const;

    void      setDeviceToAppend( OdIntPtr pDevice );
    OdIntPtr  getDeviceToAppend() const;
    OdTvGsDeviceId getTvDeviceToAppend() const { return m_appendDevice; }

    void setFeedbackForChooseCallback( OdIntPtr pCallback );
    OdIntPtr getFeedbackForChooseCallback() const;
  protected:
    OdUInt8                        m_flags;             // Different options
    OdTvMatrix                     m_appendTransform;   // Transform for the append
    OdTvGsDeviceId                 m_appendDevice;      //Device that will receive appended data
    OdTvFeedbackForChooseCallback  m_pCallback;         // Callback for choose
  };
  typedef OdSmartPtr<OdTvVisualizeVsfFilerProperties> OdTvVisualizeVsfFilerPropertiesPtr;
}


/** \details
This class is vsf loader (to the Visualize database)
*/
class OdTvVisualizeVsfFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeVsfFiler();
  OdRxDictionaryPtr properties() ODRX_OVERRIDE { return m_properties; }
  OdTvDatabaseId loadFrom(OdStreamBuf*        pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvDatabaseId loadFrom(const OdString&     filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvDatabaseId loadFrom( OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL ) const ODRX_OVERRIDE;
  OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const ODRX_OVERRIDE;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const ODRX_OVERRIDE;
  OdTvModelId    appendFrom( const OdTvDatabaseId& databaseId, OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL ) const ODRX_OVERRIDE;

private:
  VSF2Visualize::OdTvVisualizeVsfFilerPropertiesPtr m_properties;
  OdTvModelId append( const OdTvDatabaseId& dstDatabaseId, const OdTvDatabaseId& srcDatabaseId, OdTvFilerTimeProfiling* pProfileRes, OdTvResult* rc ) const;
  void        getChoosedSpaces( const OdTvDatabaseId& srcDatabaseId, OdTvFilerFeedbackForChooseObject& filerFeedbackForChoose, bool& bCanceled ) const;
};


/** \details
This class is vsf loader module implementation
*/
class OdTvVisualizeVsfFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const ODRX_OVERRIDE;

  void initApp() ODRX_OVERRIDE;
  void uninitApp() ODRX_OVERRIDE;
};

/** \details
This class is service for getting database for vsf file
*/
class OdTvVsfServices : public ExSystemServices, public OdDbBaseHostAppServices
{
public:
  OdTvVsfServices()
  {}
};

#include "TD_PackPop.h"

#endif

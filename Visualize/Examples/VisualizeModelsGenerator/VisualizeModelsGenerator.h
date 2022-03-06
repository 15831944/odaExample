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


#ifndef VISUALIZEMODELSGENERATOR_H
#define VISUALIZEMODELSGENERATOR_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvVisualizeFiler.h"

/** \details
This class implements the properties of the generator of the sample models
*/
class OdTvVisualizeSampleModelsFilerProperties : public OdRxDispatchImpl<>
{
public:
  OdTvVisualizeSampleModelsFilerProperties();
  virtual ~OdTvVisualizeSampleModelsFilerProperties();

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeSampleModelsFilerProperties);
  static OdRxDictionaryPtr createObject();

  void     setSampleID(OdUInt16 ID) { m_sampleId = ID; }
  OdIntPtr getSampleID() const { return m_sampleId; }

  void     setResourceFolder(const OdString& str) { m_strResourceFolder = str; }
  OdString getResourceFolder() const { return m_strResourceFolder; }

protected:

  OdUInt16 m_sampleId;              //Id of the sample model wchich will created inside 'generate' method
  OdString m_strResourceFolder;     //Path to the folder with the resource files 
};
typedef OdSmartPtr<OdTvVisualizeSampleModelsFilerProperties> OdTvVisualizeSampleModelsFilerPropertiesPtr;


/** \details
This class is a generator of the sample models (to the Visualize database)
*/
class OdTvVisualizeSampleModelsFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeSampleModelsFiler();

  OdRxDictionaryPtr properties() { return m_properties; }
  OdTvDatabaseId loadFrom(OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvDatabaseId loadFrom(OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvDatabaseId loadFrom(const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase *pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf        *pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString    &filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:
  OdTvVisualizeSampleModelsFilerPropertiesPtr m_properties;
};


/** \details
This class is acis loader module implementation
*/
class OdTvVisualizeSampleModelsFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // VISUALIZEMODELSGENERATOR_H


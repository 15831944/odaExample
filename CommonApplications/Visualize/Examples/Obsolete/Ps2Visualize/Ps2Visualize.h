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


#ifndef PS2VISUALIZE_H
#define PS2VISUALIZE_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvVisualizeFiler.h"

/** \details
This class implements the properties of the parasolid loader
*/
class OdTvVisualizeParasolidFilerProperties : public OdRxDispatchImpl<>
{
public:
  OdTvVisualizeParasolidFilerProperties();
  virtual ~OdTvVisualizeParasolidFilerProperties();

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeParasolidFilerProperties);
  static OdRxDictionaryPtr createObject();

  void     setDefaultColor(OdIntPtr pDefColor);
  OdIntPtr getDefaultColor() const;

protected:

  ODCOLORREF m_defaultColor;    // default color which is set to the entity
};
typedef OdSmartPtr<OdTvVisualizeParasolidFilerProperties> OdTvVisualizeParasolidFilerPropertiesPtr;


/** \details
This class is parasolid loader (to the Visualize database)
*/
class OdTvVisualizeParasolidFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeParasolidFiler();

  OdRxDictionaryPtr properties() { return m_properties; }
  OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  OdTvResult appendFrom(const OdTvDatabaseId& databaseId, const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL) const;

private:
  OdTvVisualizeParasolidFilerPropertiesPtr m_properties;
};


/** \details
This class is parasolid loader module implementation
*/
class OdTvVisualizeParasolidFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // PS2VISUALIZE_H


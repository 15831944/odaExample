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


#ifndef ACIS2VISUALIZE_H
#define ACIS2VISUALIZE_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvVisualizeFiler.h"

namespace Acis2Visualize {

  /** \details
  This class implements the properties of the acis loader
  */
  class OdTvVisualizeAcisFilerProperties : public OdRxDispatchImpl<>
  {
  public:
    OdTvVisualizeAcisFilerProperties();
    virtual ~OdTvVisualizeAcisFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeAcisFilerProperties);
    static OdRxDictionaryPtr createObject();

    void setDefaultColor(OdIntPtr pDefColor);
    OdIntPtr getDefaultColor() const;

    void setFacetRes(double dFacetRes);
    double getFacetRes() const;

    void setImportBrepAsBrep(bool bImportBrepAsBrep);
    bool getImportBrepAsBrep() const;

    void      setDCRect(OdIntPtr rect);   //should be pointer to OdTvDCRect
    OdIntPtr  getDCRect() const;

  protected:
    bool       m_bImportBrepAsBrep; // Import brep as brep flag.
    double     m_dFACETRES;         // Facet res value (between from 0.01 to 10.0)
    ODCOLORREF m_defaultColor;      // default color which is set to the entity
    OdTvDCRect m_importRect;        // Output rectangle.
  };
  typedef OdSmartPtr<OdTvVisualizeAcisFilerProperties> OdTvVisualizeAcisFilerPropertiesPtr;
}

/** \details
This class is acis loader (to the Visualize database)
*/
class OdTvVisualizeAcisFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeAcisFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:
  Acis2Visualize::OdTvVisualizeAcisFilerPropertiesPtr m_properties;
};

/** \details
This class is acis loader module implementation
*/
class OdTvVisualizeAcisFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // ACIS2VISUALIZE_H


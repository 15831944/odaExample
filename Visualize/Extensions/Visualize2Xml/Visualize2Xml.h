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

#ifndef VISUALIZE2XML_H
#define VISUALIZE2XML_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvExport.h"
#include "DbBaseDatabase.h"

namespace Visualize2Xml
{
  /** \details
  This class implements the properties of the exported to Obj
  */
  class OdTvVisualize2XmlExportProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kBinary = 1,                  // It is need to export to the binay xml
      kComposite = 2,               // It is need to use composite metafiles
    };

  public:
    OdTvVisualize2XmlExportProperties();
    virtual ~OdTvVisualize2XmlExportProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualize2XmlExportProperties);
    static OdRxDictionaryPtr createObject();

    void setDevice(OdIntPtr device);
    OdIntPtr getDevice() const;
    OdTvGsDeviceId getTvDevice() const;

    void setIsBinary(bool bSet) { SETBIT(m_flags, kBinary, bSet); }
    bool getIsBinary() const { return GETBIT(m_flags, kBinary); }

    void setIsComposite(bool bSet) { SETBIT(m_flags, kComposite, bSet); }
    bool getIsComposite() const { return GETBIT(m_flags, kComposite); }

    void setScreenWidth(OdUInt32 width) { m_screenWidth = width; }
    OdUInt32 getScreenWidth() const { return m_screenWidth; }

    void setScreenHeight(OdUInt32 height) { m_screenHeight = height; }
    OdUInt32 getScreenHeight() const { return m_screenHeight; }

  protected:
    OdUInt16                       m_flags;             // Different options
    OdTvGsDeviceId                 m_deviceId;
    OdUInt32                       m_screenWidth;
    OdUInt32                       m_screenHeight;

  };
  typedef OdSmartPtr<OdTvVisualize2XmlExportProperties> OdTvVisualize2XmlExportPropertiesPtr;
}

/** \details
This class is Xml exporter (from the Visualize database)
*/
class OdTvVisualize2XmlExport : public OdTvVisualizeExport
{
public:
  OdTvVisualize2XmlExport();
  ~OdTvVisualize2XmlExport();

  OdTvResult exportTo(const OdTvDatabaseId& tvDatabaseId, const OdString& fileName) const;
  
  OdRxDictionaryPtr properties() 
  { 
    return m_properties; 
  }

private:
  Visualize2Xml::OdTvVisualize2XmlExportPropertiesPtr m_properties;
};


/** \details
This class is Xml exporter module implementation
*/
class OdTvVisualize2XmlFilerModule : public OdTvVisualizeExportModule
{
public:
  OdTvVisualizeExportPtr getVisualizeExporter() const;

  void initApp();
  void uninitApp();
};

#include "TD_PackPop.h"

#endif // VISUALIZE2XML_H


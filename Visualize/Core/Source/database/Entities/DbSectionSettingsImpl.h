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

#ifndef _DBSECTIONSETTINGSIMPL_INCLUDED_
#define _DBSECTIONSETTINGSIMPL_INCLUDED_

#include "DbSection.h"
#include "DbEntityImpl.h"

#define GEOMETRY_SETTINGS_CONTAINER \
  SETTING(m_bVisibility, bool, visibility, setVisibility)\
  SETTING2(m_pColor, OdTvCmColor, color, const OdTvCmColor&,setColor)\
  SETTING(m_dLinetypeScale, double, linetypeScale, setLinetypeScale)\
  SETTING2(m_sPlotStyleName, OdString, plotStyleName, const OdString&, setPlotStyleName)\
  SETTING2(m_sLayerName, OdString, layer, const OdString&, setLayer)\
  SETTING2(m_sLinetypeName, OdString, linetype, const OdString&, setLinetype)\
  SETTING(m_nLineWeight, OdDb::LineWeight, lineWeight, setLineWeight)\
  SETTING(m_nFaceTransparency, int, faceTransparency, setFaceTransparency)\
  SETTING(m_nEdgeTransparency, int, edgeTransparency, setEdgeTransparency)\
  SETTING(m_bHatchVisibility, bool, hatchVisibility, setHatchVisibility)\
  SETTING(m_dHatchAngle, double, hatchAngle, setHatchAngle)\
  SETTING(m_dHatchSpacing, double, hatchSpacing, setHatchSpacing)\
  SETTING(m_dHatchScale, double, hatchScale, setHatchScale)\
  SETTING(m_bHiddenLine, bool, hiddenLine, setHiddenLine)\
  SETTING(m_bDivisionLines, bool, divisionLines, setDivisionLines)


class OdTvDbSectionSettingsImpl : public OdTvDbObjectImpl
{
public:
  struct TypeSettings
  {
    OdTvDbSectionSettings::SectionType m_SectionType;
    OdTvDbSectionSettings::Generation m_nGenerationOptions;
    OdTvDbObjectIdArray m_pSourceObjects;
    OdTvDbObjectId m_pDestinationBlock;
    OdString m_sDestinationFile;
    struct GeometrySettings
    {
      GeometrySettings()
      {
        m_nGeometryType     = OdTvDbSectionSettings::kIntersectionBoundary;
        m_nPatternType      = OdTvDbHatch::kUserDefined;
        m_bVisibility       = false;
        m_nLineWeight       = OdDb::kLnWtByLayer;
        m_dLinetypeScale    = 1;
        m_nFaceTransparency = 0;
        m_nEdgeTransparency = 0;
        m_bHatchVisibility  = false;
        m_dHatchAngle       = 0;
        m_dHatchSpacing     = 1;
        m_dHatchScale       = 1;
        m_bHiddenLine       = false;
        m_bDivisionLines    = true;
        m_sLinetypeName     = OD_T("Continuous");
        m_sPlotStyleName    = OD_T("ByColor");
        m_sLayerName        = OD_T("0");
      }
      OdResult dxfIn(OdTvDbDxfFiler* pFiler);
      void dxfOut(OdTvDbDxfFiler* pFiler)const;
      OdResult dwgIn(OdTvDbDwgFiler* pFiler);
      void dwgOut(OdTvDbDwgFiler* pFiler, OdTvDbSectionSettings::SectionType st) const;
      OdTvDbSectionSettings::Geometry m_nGeometryType;
      OdTvDbHatch::HatchPatternType m_nPatternType;
      OdString m_sPatternName;
#define SETTING2(varname, gettype, getName, settype, setName) gettype varname;
#define SETTING(varname, type, getName, setName) SETTING2(varname, type, getName, type, setName)
      GEOMETRY_SETTINGS_CONTAINER
#undef SETTING2
#undef SETTING
    };
    typedef std::map<OdTvDbSectionSettings::Geometry,GeometrySettings> GeometrySettingsMap;
    GeometrySettingsMap m_pGeometrySettings;
    TypeSettings() : m_SectionType(OdTvDbSectionSettings::k2dSection), 
      m_nGenerationOptions(OdTvDbSectionSettings::Generation(OdTvDbSectionSettings::kDestinationNewBlock|OdTvDbSectionSettings::kSourceAllObjects)){}
    OdResult dxfIn(OdTvDbDxfFiler* pFiler);
    void dxfOut(OdTvDbDxfFiler* pFiler)const;
    OdResult dwgIn(OdTvDbDwgFiler* pFiler);
    void dwgOut(OdTvDbDwgFiler* pFiler)const;
  };
  OdTvDbSectionSettingsImpl();
private:
  OdTvDbSectionSettings::SectionType m_nCurrentSectionType;

  typedef std::map<OdTvDbSectionSettings::SectionType,TypeSettings> TypeSettingsMap;
  TypeSettingsMap m_pTypeSettings;
  //Default type settings
  TypeSettingsMap m_pDefTypeSettings;
  TypeSettings& settings(OdTvDbSectionSettings::SectionType st, OdTvDbSectionSettings::Geometry nGeometry, bool bForSet = true)
  {
    bool bUseDefDettings = false;
    TypeSettingsMap::iterator it = m_pTypeSettings.find(st);
    if (it == m_pTypeSettings.end())
    {
      if (bForSet)
      {
        m_pTypeSettings[st].m_SectionType = st;
      }
      bUseDefDettings = true;
    }
    else if (nGeometry > 0)
    {
      std::map<OdTvDbSectionSettings::Geometry, OdTvDbSectionSettingsImpl::TypeSettings::GeometrySettings>::iterator itt = it->second.m_pGeometrySettings.find(nGeometry);
      if (itt == it->second.m_pGeometrySettings.end())
      {
        bUseDefDettings = true;
      }
    }
    if (bUseDefDettings)
    {
      if (bForSet)
      {
        if (nGeometry)
        {
          for (int i = 0; i < 5; i++)
          {
            if (nGeometry & (0x1 << i))
            {
              m_pTypeSettings[st].m_pGeometrySettings[OdTvDbSectionSettings::Geometry(0x1 << i)] = m_pDefTypeSettings[st].m_pGeometrySettings[OdTvDbSectionSettings::Geometry(0x1 << i)];
            }
          }
        }
      }
      else
      {
        TypeSettings& sc = m_pDefTypeSettings[st];
        sc.m_SectionType = st;
        return sc;
      }
    }
    TypeSettings& sc = m_pTypeSettings[st];
    sc.m_SectionType = st;
    return sc;
  }
  static OdTvDbSectionSettingsImpl* getImpl(const OdTvDbSectionSettings* pObj)
  { return (OdTvDbSectionSettingsImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  //It set default values for Geometryes in SectionType 
  void init(OdTvDbSectionSettings::SectionType nSecType);
  friend class OdTvDbSectionSettings;
};

#endif // _DBSECTIONSETTINGSIMPL_INCLUDED_

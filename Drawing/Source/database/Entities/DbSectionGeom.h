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
#ifndef SOLID_GEOM_CACHE_H_
#define SOLID_GEOM_CACHE_H_

#include "ModelerGeometry.h"
#include "DbSection.h"
#include "TPtr.h"

class SolidCacheItem;
typedef TPtr<SolidCacheItem> SolidCacheItemPtr;

class SolidCacheItem
{
public:
  SolidCacheItem(): m_nRefCounter(1), m_zMin(0), m_zMax(0){}
  bool isEmpty() const { return m_solid.isNull(); }
  double zMin() const { return m_zMin; }
  double zMax() const { return m_zMax; }
  OdModelerGeometryPtr geom() { return m_solid; }

  void set(OdModelerGeometry& solid, double zMin, double zMax)
  {
    m_solid = &solid;
    m_zMin = zMin;
    m_zMax = zMax;
  }

  void invalidate()
  {
    if(m_solid.get())
    {
      m_solid = NULL;
      m_zMin = m_zMax = 0;
    }
  }

  void addRef() { ++m_nRefCounter; }
  void release();

  static SolidCacheItemPtr create();

protected:
  ~SolidCacheItem(){}

public:
  SolidCacheItemPtr m_next;

private:
  OdRefCounter m_nRefCounter;
  OdModelerGeometryPtr m_solid;
  double m_zMin;//kBoundary, limit along the vertical direction
  double m_zMax;//kBoundary, limit along the vertical direction
};

class SolidCache
{
public:
  SolidCache(){}
  SolidCacheItemPtr get()
  {
      if(m_top.get())
      {
          SolidCacheItemPtr pRes = m_top;
          m_top = m_top->m_next;
          pRes->m_next = NULL;
          return pRes;
      }
      return SolidCacheItem::create();
  }

  void set(SolidCacheItem* ptr)
  {
      if(m_top)
          ptr->m_next = m_top;
      m_top = ptr;
  }

  void invalidate()
  {
      for(SolidCacheItem* ptr = m_top; ptr; ptr = ptr->m_next)
          ptr->invalidate();
  }

  void clear()
  {
      m_top = NULL;
  }

protected:
  SolidCacheItemPtr m_top;
};

SolidCacheItemPtr getLiveSectionSolidCache(const OdDbSection* pSect);
void setLiveSectionSolidCache(const OdDbSection* pSect, SolidCacheItem& item);

class SolidCacheItemLocker
{
public:
    SolidCacheItemLocker(const OdDbSection& s): m_section(s){}
    ~SolidCacheItemLocker()
    {
        if(m_item.get())
            setLiveSectionSolidCache(&m_section, *m_item);
    }

public:
    const OdDbSection& m_section;
    SolidCacheItemPtr m_item;
};


///////////////////////////////////////////////////////////////////////
class SectArgs
{
public:
  SectArgs(const OdDbSection* pSect, bool bForceLiveSection, 
    OdArray<OdDbEntityPtr>& intBoundaryEnts, OdArray<OdDbEntityPtr>& intFillEnts,
    OdDbEntityPtrArray& backgroundEnts, OdDbEntityPtrArray& foregroundEnts):
          m_section(pSect)
        , m_backgroundEnts(backgroundEnts)
        , m_foregroundEnts(foregroundEnts)
        , m_intBoundaryEnts(intBoundaryEnts)
        , m_intFillEnts(intFillEnts)
        , m_bBackground(false)
        , m_bForeground(false)
        , m_bIntBoundary(false)
        , m_bIntFill(false)
        , m_bUsePlane(false)
      {
        m_backgroundEnts.clear();
        m_foregroundEnts.clear();
        m_intBoundaryEnts.clear();
        m_intFillEnts.clear();

        m_settings = m_section->getSettings(OdDb::kForRead);
        ODA_ASSERT(m_settings.get());
        m_type = bForceLiveSection ? OdDbSectionSettings::kLiveSection :
          m_settings->currentSectionType();

        m_bIntBoundary = ((m_type != OdDbSectionSettings::k3dSection) ||
          m_settings->visibility(m_type, OdDbSectionSettings::kIntersectionBoundary));
        m_bBackground = ((m_type != OdDbSectionSettings::k2dSection) || 
          m_settings->visibility(m_type, OdDbSectionSettings::kBackgroundGeometry));
        m_bForeground = m_settings->visibility(m_type, OdDbSectionSettings::kForegroundGeometry);
        m_bIntFill = m_settings->hatchVisibility(m_type, OdDbSectionSettings::kIntersectionFill);
      }

public:
  OdDbSectionSettings::SectionType type() const { return m_type; }
  const OdDbSectionSettings* settings() const { return m_settings; }
  const OdDbSection* section() const { return m_section; }

  OdDbEntity *sectionEntity() { return m_sectionEnt.get(); }
  const OdDbEntity *sectionEntity() const { return m_sectionEnt.get(); }
  void setSectionEntity(const OdDbEntity *pEntity) { m_sectionEnt = pEntity; }

  void applySettings(OdDbSectionSettings::Geometry nGeometry, OdDbEntityPtrArray& ents)
  {
    for(unsigned i = 0; i < ents.size(); ++i)
    {
      ents[i]->setDatabaseDefaults(m_settings->database());
      if (sectionEntity())
        ents[i]->setPropertiesFrom(sectionEntity());
      ents[i]->setColor(m_settings->color(type(), nGeometry));
      if(type() != OdDbSectionSettings::kLiveSection)
      {
        OdDbObjectId id = OdDbSymUtil::getLayerId(m_settings->layer(type(), nGeometry), m_settings->database());
        if(id)
          ents[i]->setLayer(id);
        OdString str = m_settings->plotStyleName(type(), nGeometry);
        if(str.getLength())
          ents[i]->setPlotStyleName(str);
      }
      OdDbObjectId id = OdDbSymUtil::getLinetypeId(m_settings->linetype(type(), nGeometry), m_settings->database());
      if(id)
        ents[i]->setLinetype(id);
      ents[i]->setLinetypeScale(m_settings->linetypeScale(type(), nGeometry));
      ents[i]->setLineWeight(m_settings->lineWeight(type(), nGeometry));
    }
  }

  void applySettingsToForeground()
  { applySettings(OdDbSectionSettings::kForegroundGeometry, m_foregroundEnts); }
  void applySettingsToBackground()
  { applySettings(OdDbSectionSettings::kBackgroundGeometry, m_backgroundEnts); }

public:
  OdDbEntityPtrArray& m_backgroundEnts;
  OdDbEntityPtrArray& m_foregroundEnts;
  OdDbEntityPtrArray& m_intBoundaryEnts;
  OdDbEntityPtrArray& m_intFillEnts;
  OdDbEntityPtrArray m_sectionEnts;

  bool m_bBackground;
  bool m_bForeground;
  bool m_bIntBoundary;
  bool m_bIntFill;
  bool m_bUsePlane; //It uses for testing objects by plane branch for "jog plain section" if the object and the section do not have any intersection.

protected:
  const OdDbSection* m_section;
  OdDbSectionSettingsPtr m_settings;
  OdDbSectionSettings::SectionType m_type;
  OdDbEntityPtr m_sectionEnt;
};

#endif // SOLID_GEOM_CACHE_H_

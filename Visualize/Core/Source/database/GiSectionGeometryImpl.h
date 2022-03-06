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

#ifndef __OD_GI_SECTION_GEOMETRY_MAP_IMPL_H__
#define __OD_GI_SECTION_GEOMETRY_MAP_IMPL_H__

#include "Gi/GiSectionGeometry.h"
#include "ThreadsCounter.h"

class OdGiSectionGeometryImpl: public OdGiSectionGeometry
{
public:
    OdGiSectionGeometryImpl(): OdGiSectionGeometry(){}
    bool init(OdGiDrawable& section, const OdGiDrawable& drawable,
              const OdGeMatrix3d& tf, OdGiSectionGeometryManager& manager);
protected:
    OdMutexPtr m_mt;
};

class OdTvDbStubPath
{
public:
  OdTvDbStubPath(){}
  OdTvDbStubPath(OdDbStubPtrArray& ids): m_ids(ids){}
  OdTvDbStubPath(const OdTvDbStubPath& c): m_ids(c.m_ids){}
  const OdDbStubPtrArray& get() { return m_ids; }
  int compare(const OdTvDbStubPath& c) const
  {
      unsigned i = 0;
      unsigned n = m_ids.size() < c.m_ids.size() ? m_ids.size() : c.m_ids.size();
      for(; i < n; ++i)
      {
        if(m_ids.getAt(i) < c.m_ids.getAt(i))
          return -1;
        if(m_ids.getAt(i) > c.m_ids.getAt(i))
          return 1;
      }
      if(c.m_ids.size() > n)
        return -1;
      return m_ids.size() > n ? 1 : 0;
  }
  bool operator < (const OdTvDbStubPath& c) const { return compare(c) < 0; }

protected:
  OdDbStubPtrArray m_ids;
};

class OdGiSectionMapImpl
{
public:
    ~OdGiSectionMapImpl()
    {
      for(_mmapId::iterator it1 = m_mapId.begin(); it1 != m_mapId.end(); ++it1)
        delete it1->second;
      m_mapId.clear();
      for(_mmapPath::iterator it2 = m_mapPath.begin(); it2 != m_mapPath.end(); ++it2)
        delete it2->second;
      m_mapPath.clear();
    }
    OdGiSectionGeometryImpl* getAt(const OdGiPathNode* path, OdGiDrawable& section, 
      const OdGiDrawable& drawable, const OdGeMatrix3d& tf, OdGiSectionGeometryManager& manager);

protected:
    class MapValue
    {
    public:
        MapValue(): m_geom(NULL){}
        ~MapValue();
        OdGiSectionGeometryImpl* getGeom()
        {
          TD_AUTOLOCK_P_DEF(m_mt);
          return m_geom;
        }
        void setGeom(OdGiSectionGeometryImpl* pGeom)
        {
          //m_mt is already locked by this thread when calling the function
          m_geom = pGeom;
        }

    public:
        OdMutexPtr m_mt;
    protected:
        OdGiSectionGeometryImpl* m_geom;
    };
    typedef std::map<const OdDbStub*, MapValue*> _mmapId;
    typedef std::map<OdTvDbStubPath, MapValue*> _mmapPath;

protected:
     OdGiSectionGeometryImpl* getAtIdMap(const OdDbStub* id, OdGiDrawable& section,
         const OdGiDrawable& drawable, const OdGeMatrix3d& tf, OdGiSectionGeometryManager& manager);
     OdGiSectionGeometryImpl* getAtPathMap(const OdTvDbStubPath& path, OdGiDrawable& section,
         const OdGiDrawable& drawable, const OdGeMatrix3d& tf, OdGiSectionGeometryManager& manager);
protected:
    _mmapId m_mapId;
    _mmapPath m_mapPath;
    OdMutexPtr m_mtMapId;
    OdMutexPtr m_mtMapPath;
};

class OdGiSectionGeometryMapImpl: public OdGiSectionGeometryMap
{
public:
  OdGiSectionGeometry* getAt(OdGiDrawable& section, const OdGiPathNode* path,
      const OdGiDrawable& drawable, const OdGeMatrix3d& tf);
  void clear()
  {
      for(_mmap::iterator it = m_map.begin(); it != m_map.end(); ++it)
        delete it->second;
      m_map.clear();
      for(_mmapTransient::iterator itt = m_mapTransient.begin(); itt != m_mapTransient.end(); ++itt)
        delete itt->second;
      m_mapTransient.clear();
  }
  ~OdGiSectionGeometryMapImpl()
  {
      clear();
  }
  static OdGiSectionGeometryMapPtr createObject(OdGiSectionGeometryManager& manager);

protected:
  OdGiSectionGeometryMapImpl(): m_manager(NULL) {}
  OdGiSectionGeometryManager& manager() { ODA_ASSERT(m_manager); return *m_manager; }

protected:
  typedef std::map<const OdDbStub*, OdGiSectionMapImpl*> _mmap;
  typedef std::map<const OdGiDrawable*, OdGiSectionMapImpl*> _mmapTransient;

protected:
  _mmap m_map;
  _mmapTransient m_mapTransient;
  OdGiSectionGeometryManager* m_manager;
  OdMutexPtr m_mt;
};

class OdGiSectionGeometryManagerImpl : public OdGiSectionGeometryManager
{
  public:
  ODRX_DECLARE_MEMBERS(OdGiSectionGeometryManagerImpl);
    virtual OdDbStub* getLiveSection(const OdDbStub* layoutId, OdDbStub*& sectionSettingsId) const;
    virtual OdGiDrawablePtr createLiveSection(OdDbBaseDatabase *pDb, OdDbStub *visualStyleId,
                                              const OdGePoint3dArray &points, const OdGeVector3d &verticalDir,
                                              const double *dTop = NULL, const double *dBottom = NULL) const;
    virtual bool isLiveSection(const OdGiDrawable* pDrawable) const;
    virtual bool generateSectionGeometry(OdGiDrawable& section,
                                         const OdGiDrawable& drawable,
                                         const OdGeMatrix3d& xform,
                                         OdGiSectionGeometry& geom,
                                         bool* bHasForeground) const;
    virtual OdGiSectionGeometryMapPtr createSectionGeometryMap();
    virtual int classifyExtentsRelativelySection(const OdGiDrawable* pDrawable, const OdGeExtents3d& ext) const;
};

#endif //__OD_GI_SECTION_GEOMETRY_MAP_IMPL_H__

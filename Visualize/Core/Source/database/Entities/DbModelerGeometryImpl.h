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

#ifndef _ODDB_MODELERGEOMETRY_IMPL_INCLUDED_
#define _ODDB_MODELERGEOMETRY_IMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "../wrWiresCache.h"
#include "../wrSilhouettesCache.h"
#include <ModelerGeometry.h>
#include <OdVector.h>
#include <RxDLinkerReactor.h>
#include "OdErrorWithId.h"
#include "BrepRenderModes.h"
#include "NextCodeDefs.h"

class OdTvDbRegion;
class OdTvDbRevolveOptions;
class OdTvDbSweepOptions;
class OdTvDbLoftOptions;
class OdTvDbBlendOptions;
class OdTvDbAsciiDxfFilerImpl;

class OdEmptyAcisError : public OdError_WithId
{
public:
  OdEmptyAcisError(OdTvDbObjectId id)
    : OdError_WithId( eEmptyAcisFile
                    , id.isNull() ? ((OdDbStub*)OdTvDbObjectId::kNull) : ((OdDbStub*)id)
                    , id.isNull() ? OdString::kEmpty : id.safeOpenObject()->isA()->name())
  {
  }
};

#define writeAcisDataCatched(a,b,c) try\
{\
OdTvDbModelerGeometryImpl::writeAcisData(a,b,c);\
}\
catch (const OdError& e)\
{\
  if (e.code() == eEmptyAcisFile)\
  {\
    throw OdEmptyAcisError(objectId());\
  }\
  throw e;\
}

#define writeSubEntityCatched(a,b,c) try\
{\
  OdTvDbSurfaceImpl::writeSubEntity(a,b,c);\
}\
  catch (const OdError& e)\
{\
  if (e.code() == eEmptyAcisFile)\
{\
  throw OdEmptyAcisError(objectId());\
}\
  throw e;\
}

#define writeSubEntityCatchedDxf(a,b,c,d,f) try\
{\
  OdTvDbSurfaceImpl::writeSubEntity(a,b,c,d,f);\
}\
  catch (const OdError& e)\
{\
  if (e.code() == eEmptyAcisFile)\
{\
  throw OdEmptyAcisError(objectId());\
}\
  throw e;\
}

// AC27 support
class OdTvDbRevisionGuid : public OdGUID // used in Model-Doc feature to reference body geometry revision
{
public:
  OdTvDbRevisionGuid() {};

  OdTvDbRevisionGuid(const OdString& value) 
  { 
    *this = value; 
  }

  OdTvDbRevisionGuid& operator=(const OdString& str)
  {
    //{786AB7A0-4570-4177-8FC3-83E9B77207DE}

    if (str.getLength() != 38 || 
      !(str[0] == '{' && str[9] == '-' && str[14] == '-' && str[19] == '-' && str[24] == '-'  && str[37] == '}'))
    {
      throw OdError(eInvalidInput);
    }

    OdUInt32 data32 = (OdUInt32)(OdUInt64)OdDbHandle(OdString(&str.c_str()[1], 8));
    OdUInt16 data16_1 = (OdUInt16)(OdUInt64)OdDbHandle(OdString(&str.c_str()[10], 4));
    OdUInt16 data16_2 = (OdUInt16)(OdUInt64)OdDbHandle(OdString(&str.c_str()[15], 4));
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i)
    {
      data8[i] =  (OdUInt8)(OdUInt64)OdDbHandle(OdString(&str.c_str()[20 + i*2 + (i < 2 ? 0 : 1)], 2));
    }
    setGUIDdata(data32, data16_1, data16_2, data8);
    return *this;
  }

  static void createGuid(OdTvDbRevisionGuid &newGuid) {
    newGuid = odrxSystemServices()->createGuid();
  }

  OdString ascii() const 
  {
    //{786AB7A0-4570-4177-8FC3-83E9B77207DE}
//     OdString str;
//     str.format(L"{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
//       (unsigned long)m_data1,
//       (unsigned)m_data2,
//       (unsigned)m_data3,
//       (unsigned)m_data4[0], (unsigned)m_data4[1], (unsigned)m_data4[2], (unsigned)m_data4[3],
//       (unsigned)m_data4[4], (unsigned)m_data4[5], (unsigned)m_data4[6], (unsigned)m_data4[7]);
//     return str;
    return toString(StringFormat::Braces);
  }

  OdResult dxfInRaw(OdTvDbDxfFiler* pFiler) 
  { // Model-Doc way
    NEXT_CODE(90);
    OdUInt32 data32 = pFiler->rdInt32();
    NEXT_CODE(70);
    OdUInt16 data16_1 = pFiler->rdInt16();
    NEXT_CODE(70);
    OdUInt16 data16_2 = pFiler->rdInt16();
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i)
    {
      NEXT_CODE(280);
      data8[i] = pFiler->rdInt8();
    }
    setGUIDdata(data32, data16_1, data16_2, data8);
    return eOk;
  }

  void dxfOutRaw(OdTvDbDxfFiler* pFiler) const 
  { // Model-Doc way
     const OdUInt8 *RevGUIDData = data();
     pFiler->wrInt32(90, *reinterpret_cast<const OdUInt32*>(RevGUIDData));
     pFiler->wrInt16(70, *reinterpret_cast<const OdUInt16*>(RevGUIDData + 4));
     pFiler->wrInt16(70, *reinterpret_cast<const OdUInt16*>(RevGUIDData + 6));
     for (int i = 0; i < 8; ++i)
       pFiler->wrInt8(280, RevGUIDData[8 + i]);
  }

  void dwgIn(OdTvDbDwgFiler* pFiler)
  {
    OdUInt32 data32 = pFiler->rdInt32();
    OdUInt16 data16_1 = pFiler->rdInt16();
    OdUInt16 data16_2 = pFiler->rdInt16();
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i)
      data8[i] = pFiler->rdInt8();
    setGUIDdata(data32, data16_1, data16_2, data8);
  }

  void dwgOut(OdTvDbDwgFiler* pFiler) const
  {
    const OdUInt8 *RevGUIDData = data();
    pFiler->wrInt32(*reinterpret_cast<const OdUInt32*>(RevGUIDData));
    pFiler->wrInt16(*reinterpret_cast<const OdUInt16*>(RevGUIDData + 4));
    pFiler->wrInt16(*reinterpret_cast<const OdUInt16*>(RevGUIDData + 6));
    for (int i = 0; i < 8; ++i)
      pFiler->wrInt8(RevGUIDData[8 + i]);
  }
};

struct OdRevisionGuid : public OdTvDbRevisionGuid
{
  bool     m_bIsSet;

  OdRevisionGuid():m_bIsSet(false)
  {
  }

  OdRevisionGuid(const OdChar* value) 
  { 
    *this = value; 
  }

  void dxfIn(OdTvDbDxfFiler* pFiler)
  {
    int nGC = pFiler->nextItem();
    if (nGC == 290)
    {
      m_bIsSet = pFiler->rdBool();
    }
    else
    {
      m_bIsSet = false;
      ODA_FAIL_M_ONCE("Unexpected group while reading OdRevisionGuid");
    }
    nGC = pFiler->nextItem();
    if (nGC == 2)
    {
      OdTvDbRevisionGuid::operator=(pFiler->rdString());
    }
    else
    {
      OdUInt8 data8[8] = { 0 };
      setGUIDdata(0, 0, 0, data8);
      ODA_FAIL_M_ONCE("Unexpected group while reading OdRevisionGuid");
    }
  }

  void dxfOut(OdTvDbDxfFiler* pFiler) const
  {
    pFiler->wrBool(290, m_bIsSet);
    pFiler->wrString(2, ascii());
  }

  void dwgIn(OdTvDbDwgFiler* pFiler)
  {
    m_bIsSet = pFiler->rdBool();
    OdTvDbRevisionGuid::dwgIn(pFiler);
  }

  void dwgOut(OdTvDbDwgFiler* pFiler) const
  {
    pFiler->wrBool(m_bIsSet);
    OdTvDbRevisionGuid::dwgOut(pFiler);
  }

  //at the moment we are not using bSet=false. E.a. it always set to true. But in near future it can be changed
  void setGuid(OdRevisionGuid newGuid, bool bSet)
  {
    if (m_bIsSet != bSet || !(*this == newGuid))
    {
      *this = newGuid;
      m_bIsSet = bSet;
    }
  }

  void generateDifferent()
  {
    OdRevisionGuid newGuid;
    createGuid(newGuid);
    setGuid(newGuid, m_bIsSet);
  }


  void enable(bool bEnable)
  {
    if (bEnable)
    {
      OdRevisionGuid newGuid;
      createGuid(newGuid);
      setGuid(newGuid, bEnable);
    }
    else
    {
      setGuid(*this, bEnable);
    }
  }
};

DBENT_EXPORT OdRxClassPtr odrxGetModelerToolsService();
DBENT_EXPORT OdRxClassPtr odrxGetModelerGeometryCreatorService();

class OdModelerInitInfo: public OdMutex, protected OdStaticRxObject<OdRxDLinkerReactor>
{
public:
  OdModelerInitInfo(): m_bModuleLoaded(0), m_pModule(NULL) {}
  ~OdModelerInitInfo();
  bool isLoaded() const { return m_bModuleLoaded != 0; }
  void setLoaded(const OdRxModule *pModule);
  void setUnloaded();
  const OdRxModule *module() const { return m_pModule; }
  static OdModelerInitInfo& instance() { return s_instance; }

protected:
  virtual void rxAppWillBeUnloaded(OdRxModule* pModule);

  static OdModelerInitInfo s_instance;
  OdVolatile m_bModuleLoaded;
  const OdRxModule *m_pModule;
};

namespace OdTvDbModelerThreads
{
  // ODA_MT_DB_1_BEGIN
  //Container of thread ids to initialize on demand
  //TODO: thread-safety when general case of concurrent modeler initialization is possible (not only from Gs MT threads)
  struct ThreadId
  {
    unsigned m_id;
    bool m_bStarted;

    ThreadId(): m_id(0), m_bStarted(false){}
  };

  class ThreadsGroup
  {
  public:
    ThreadsGroup(unsigned nThreads, const unsigned* aThreads);
    ~ThreadsGroup();
    unsigned size() const { return m_nThreads; }
    ThreadId& at(unsigned i) { return m_aThreads[i]; }

    ThreadId* find(unsigned threadId);
    void getAsArray(OdVector<unsigned, OdMemoryAllocator<unsigned> >& ar);
    int countNotStarted();
  protected:
    ThreadId* m_aThreads;
    unsigned m_nThreads;
  };

  class ThreadIds
  {
  public:
    ~ThreadIds();
    void add(unsigned nThreads, const unsigned* aThreads);
    void remove(unsigned nThreads, const unsigned* aThreads);
    ThreadId* findCurrent();
    void checkThreadStarted(OdRxClass* pToolsService = NULL);
    void initModelerInThreads();
    bool isEmpty();
    static ThreadIds& instance() { return s_instance; }
    void uninit();

  protected:
    OdVector<ThreadsGroup*, OdMemoryAllocator<ThreadsGroup*> > m_data;
    volatile int m_nThreadsToStartModeler;
    OdMutex m_mt;
    static ThreadIds s_instance;
  };
};

bool saveEmptyAllowed(const OdTvDbObject *pModeler, OdTvDbFiler::FilerType filerType);
bool saveEmptyAllowed(const OdTvDbObjectImpl *pModeler, OdTvDbFiler::FilerType filerType);
bool doAcisAudit(const OdTvDbObjectImpl *pModeler, OdTvDbFiler::FilerType filerType);

class DBENT_EXPORT OdTvDbModelerGeometryImpl : public OdTvDbEntityImpl
{
  mutable OdModelerGeometryPtr m_pModelerGeom;

  // Caches
  bool                 m_bHasPoint;
  OdGePoint3d          m_point;          // solid\body center
  wrSilhouetteCache    m_silhouettes;    // silhouette cache
  wrWiresCache         m_WireCache;      // isoline cache
  OdModelerGeometryPtr m_pEdgesAcisData; // Nurb curves store as acis
  OdGeCurve3dPtrArray  m_NurbCurves;     // Nurb curves store as Ge
  // AC27 support
  OdInt32 m_unknownCounter;
  bool m_bEmbedded;

  bool restoreGuidInfo(OdTvResBufPtr pXData);

public:
  static OdTvDbModelerGeometryImpl* getImpl(const OdTvDbObject *pObj)
  { return (OdTvDbModelerGeometryImpl*)OdTvDbSystemInternals::getImpl(pObj);}
  bool isEmbedded() {return m_bEmbedded;}
  void setEmbedded(bool bEmbedded)  {m_bEmbedded = bEmbedded;}
private:
  OdRevisionGuid m_revisionGuid; // Guid  will be changed with new, after each modification in Acad

public:
  OdRevisionGuid revisionGuid() const { return m_revisionGuid; }

  // material cache - unknown features (new in 2007)
  struct OdTvDbMGMaterials
  {
    OdUInt32              nMaterialIdLow;
    OdUInt32              nMaterialIdHigh;
    OdTvDbHardPointerId    MaterialHP;

    OdUInt64 materialId() const { return nMaterialIdLow + (((OdUInt64)nMaterialIdHigh)<<32); }
  };

  class MaterialMap : public OdArray<OdTvDbMGMaterials>
  {
  public:
    void add(OdTvDbObjectId id)
    {
      OdTvDbMGMaterials tmp;
      tmp.MaterialHP = id;
      tmp.nMaterialIdLow = (OdUInt64)id->getHandle() & 0xFFFFFFFF;
      tmp.nMaterialIdHigh = ((OdUInt64)id->getHandle()) >> 32;
      append(tmp);
    }
    bool hasMaterialId(OdUInt64 id, OdTvDbObjectId *pMat = 0, OdUInt32* index = 0) const
    {
      for(OdUInt32 f=0; f<size(); ++f)
      {
        if (getAt(f).materialId() == id)
        {
          if (pMat)
          {
            *pMat = getAt(f).MaterialHP;
          }
          if (index)
          {
            *index = f;
          }
          return true;
        }
      }
      return false;
    }
  };

public:
  virtual void getMaterialMap(OdUInt64Array &materials) const;
private:
  void mergeMaterialMapWithSAT();
  void applyMaterialMapToSAT();

private:
  bool        m_MaterialsSinchronized; //see comments about performance in subSlowMaterials_17099_AR
  MaterialMap m_Materials;

  bool hasTrueColors() const;

  static void dxfSATreading_unicode(OdTvDbDxfFiler* pFiler, OdMemoryStreamPtr pLoadedData);
  static void dxfSATreading_ansi(OdTvDbAsciiDxfFilerImpl* pFiler, OdMemoryStreamPtr pLoadedData);

  // Make Wire public so that wrSilhouette can use it below (Solaris).
public:
  static bool isReallyAnsi(const OdAnsiString &storage);

  static void dwgIn(wrWire *pWire, OdTvDbDwgFiler* pFiler);
  static void dwgOut(const wrWire *pWire, OdTvDbDwgFiler* pFiler, const OdGeMatrix3d* xMat);
  static void dwgIn(wrSilhouette *pSil, OdTvDbDwgFiler* pFiler);
  static void dwgOut(const wrSilhouette *pSil, OdTvDbDwgFiler* pFiler, const OdGeMatrix3d* xMat);

  OdModelerGeometryPtr getModeler(OdTvDbAuditInfo* pAuditInfo = NULL, bool bEnableAcisAudit = false) const;

  virtual void setMaterial(OdTvDbObjectId id, bool /*doSubents*/ = true);
  virtual void setMaterialMapper(const OdGiMapper* mapper);

  virtual OdResult setColorIndex(OdUInt16 colorInd, bool doSubents = true);
  virtual OdResult setColor(const OdTvCmColor& clr, bool doSubents = true);
  virtual OdResult setColorId(OdTvDbObjectId clrId, bool doSubents = true);

  static void writeSAT(OdTvDbDwgFiler* pFiler, OdStreamBuf* pStorage);
private:
  static OdStreamBufPtr readSAB(OdTvDbDwgFiler* pFiler);
  static void writeSAB(OdTvDbDwgFiler* pFiler, OdStreamBuf* pStorage);

  OdModelerGeometryPtr &getEdgesStore(OdTvDbAuditInfo* pAuditInfo = NULL, bool bEnableAcisAudit = false);

  void fillNurbCurvesArray();
  void drawCachedWires(OdGiCommonDraw& pCD, OdArray<wrWire> &Wires);

protected:

  virtual void invalidateCache()
  {
    m_WireCache.invalidateCache();
    m_silhouettes.invalidateCache();
    m_pEdgesAcisData = 0;
    m_NurbCurves.setPhysicalLength(0);
    m_bHasPoint = false;
  }

public:
  // OdTvDbObjectImpl overridden
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);


  static OdModelerGeometryPtr createModelerGeometryImpl(OdStreamBuf* pStreamIn, bool bStandardSaveFlag = true, OdTvDbAuditInfo* pAuditInfo = NULL, bool bEnableAcisAudit = false);
  
  OdResult explode( OdRxObjectPtrArray& entitySet ) const;
  OdResult transformBy( const OdGeMatrix3d& xform );
  
  OdResult acisOut(OdStreamBuf* pStream, AfTypeVer typeVer, OdTvDbAuditInfo *pAuInfo = NULL, bool bAcisAudit = false)
  {
    if (getModeler(pAuInfo, bAcisAudit).get())
      return m_pModelerGeom->out(pStream, typeVer);
    return eOk;
  }

  OdResult acisIn(OdStreamBuf* pIn, AfTypeVer *typeVer = NULL, OdTvDbAuditInfo *pAuInfo = NULL, bool bAcisAudit = false)
  {
    if (getModeler(pAuInfo, bAcisAudit).get())
    {
      invalidateCache();
      return m_pModelerGeom->in(pIn, typeVer);
    }
    return eOk;
  }

  void brep(OdBrBrep& brep) const;
  bool getFaceMesh(GeMesh::OdGeTrMesh& mesh, OdGsMarker iFace, const wrTriangulationParams& triangulationParams) const;

  TOOLKIT_EXPORT static OdModelerGeometryPtr readAcisData(OdTvDbDxfFiler* pFiler);
  TOOLKIT_EXPORT static void writeAcisData(OdTvDbDxfFiler* pFiler, OdModelerGeometry* pAcisData, bool saveEmptyAllowed, bool bEnableAcisAudit = false);
  static OdStreamBufPtr readSAT(OdTvDbDwgFiler* pFiler);

  OdTvDbModelerGeometryImpl();
  ~OdTvDbModelerGeometryImpl();

  bool isNull() const { return m_pModelerGeom.isNull(); }

  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  void dxfOutFields(OdTvDbDxfFiler* pFiler);

  virtual void composeForLoad(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void readDsAcisData();

  friend class OdTvDbModelerGeometry;

  void drawOrderedEdges(OdGiWorldDraw* pWd);
  bool worldDraw(OdGiWorldDraw* pWd);
  void viewportDraw(OdGiViewportDraw* pVd);
  virtual OdResult setBody( const void* g );
  virtual void *body() const;
  void saveAs(OdGiWorldDraw* pWd, OdDb::DwgVersion ver);

  virtual void createBox( double xLen, double yLen, double zLen );
  virtual void createFrustum( double height, double xRadius, double yRadius, double topXRadius );
  virtual void createSphere( double radius );
  virtual void createTorus( double majorRadius, double minorRadius );
  virtual void createWedge( double xLen, double yLen, double zLen );

  virtual OdResult extrude(const OdTvDbRegion* region, double height, double taper, bool isSolid = true);
  virtual OdResult revolve(const OdTvDbRegion* region, const OdGePoint3d& axisPoint, const OdGeVector3d& axisDir, double angleOfRevolutionbool, bool isSolid = true);
  virtual OdResult extrudeAlongPath(const OdTvDbRegion* region, const OdTvDbCurve* path, double taperAngle = 0.0, bool isSolid = true);
  virtual OdResult imprintEntity(const OdTvDbEntity *pEntity);

  virtual OdResult getPlane(OdGePlane& regionPlane) const;

  virtual OdResult createExtrudedObject ( OdTvDbEntity* pSweepEnt,
                                          const OdGeVector3d& directionVec,
                                          OdTvDbSweepOptions& sweepOptions,
                                          bool isSolid = true, 
                                          bool bHistoryEnabled = false);

  virtual OdResult createLoftedObject(
    OdTvDbEntityPtrArray& crossSectionCurves,
    OdTvDbEntityPtrArray& guideCurves,
    OdTvDbEntity* pPathCurve, 
    OdTvDbLoftOptions& loftOptions,
    bool isSolid = true);

  virtual OdResult createBlendObject(
    OdTvDbEntityPtrArray& blendedEdges, OdTvDbBlendOptions& loftOptions,
    bool isSolid = true);

  //virtual OdResult createLoftedObjectByCoedges(
  //  OdTvDbEntityPtrArray& crossSectionCurves,
  //  OdTvDbEntityPtrArray& guideCurves,
  //  OdTvDbEntity* pPathCurve,
  //  OdTvDbLoftOptions& loftOptions,
  //  bool isSolid = true);

  virtual OdResult createRevolvedObject ( OdTvDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    double revAngle, double startAngle,
    OdTvDbRevolveOptions& revolveOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false);

  virtual OdResult createSweptObject ( OdTvDbEntity* pSweepEnt,
    OdTvDbEntity* pPathEnt,
    OdTvDbSweepOptions& sweepOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false);

  virtual OdResult copySubEntity(const OdDbSubentId &subentId, OdTvDbEntityPtr &newEntity) const;
  virtual OdResult taperFaces(const OdArray<OdDbSubentId *> &faceSubentIds, const OdGePoint3d &basePoint, 
                              const OdGeVector3d &draftVector, double draftAngle);
  virtual OdResult removeFaces(const OdArray<OdDbSubentId *> &faceSubentIds);
  virtual OdResult offsetFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double offsetDistance);
  virtual OdResult shellBody(const OdArray<OdDbSubentId *> &faceSubentIds, double offsetDistance);
  virtual OdResult transformFaces(const OdArray<OdDbSubentId *> &faceSubentIds, const OdGeMatrix3d &matrix);

  virtual OdResult getSubentPathsAtGsMarker(OdDb::SubentType type,
                                            OdGsMarker gsMark, 
                                            const OdGePoint3d& pickPoint,
                                            const OdGeMatrix3d& viewXform, 
											OdTvDbFullSubentPathArray& subentPaths, 
											const OdTvDbObjectIdArray* pEntAndInsertStack = 0) const;

  virtual OdResult getGsMarkersAtSubentPath(const OdTvDbFullSubentPath& subPath, 
                                            OdGsMarkerArray& gsMarkers) const;

  virtual OdUInt32 numChanges() const;

  virtual OdDbSubentId internalSubentId(void* ent) const;
  virtual void* internalSubentPtr(const OdDbSubentId& id) const;

  virtual OdResult setSubentColor(const OdDbSubentId &subentId, const OdTvCmColor &color);
  virtual OdResult getSubentColor(const OdDbSubentId &subentId, OdTvCmColor &color) const;
  virtual OdResult setSubentMaterial(const OdDbSubentId &subentId, OdTvDbObjectId matId);
  virtual OdResult getSubentMaterial(const OdDbSubentId &subentId, OdUInt64& numId) const;
  virtual OdResult setSubentMaterialMapper( const OdDbSubentId &subentId, 
                                            OdGeMatrix3d &mx, 
                                            OdUInt8 &projection, 
                                            OdUInt8 &tiling, 
                                            OdUInt8 &autoTransform);
  virtual OdResult getSubentMaterialMapper( const OdDbSubentId &subentId,
                                            OdGeMatrix3d &mx, 
                                            OdUInt8 &projection, 
                                            OdUInt8 &tiling, 
                                            OdUInt8 &autoTransform) const;

  virtual OdResult chamferEdges(const OdArray<OdDbSubentId *> &edgeSubentIds,
                                const OdDbSubentId& baseFaceSubentId, 
                                double baseDist, 
                                double otherDist);

  virtual OdResult filletEdges( const OdArray<OdDbSubentId *> &edgeSubentIds,
                                const OdGeDoubleArray& radius, 
                                const OdGeDoubleArray& startSetback, 
                                const OdGeDoubleArray& endSetback);

  virtual OdResult booleanOper(OdDb::BoolOperType operation, OdTvDbModelerGeometryImpl *pModelerPar);
  virtual OdResult booleanOper(OdDb::BoolOperType operation, const void *pModelerPar, OdTvDbEntityPtrArray& intersectionEntities);

  virtual OdResult createFrom(const OdTvDbEntity* pEntity);

  virtual OdResult createSectionObjects(const OdGePlane& sectionPlane, OdTvDbEntityPtrArray& sectionObjects) const;

  virtual OdResult createInterferenceObjects( OdTvDbEntityPtrArray& interferenceObjects,
                                              OdTvDbEntityPtr pEntity, 
                                              unsigned int flags ) const;

  virtual OdResult extrudeFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double height, double taper);
  virtual OdResult extrudeFacesAlongPath(const OdArray<OdDbSubentId *> &faceSubentIds, const OdTvDbCurve* path);

  virtual OdResult generateSectionGeometry( const OdTvDbSection*      pSection,
                                            OdTvDbEntityPtrArray&     sourceEntArr,
                                            OdArray<OdTvDbEntityPtr>& intBoundaryEnts,
                                            OdArray<OdTvDbEntityPtr>& intFillEnts,
                                            OdArray<OdTvDbEntityPtr>& backgroundEnts,
                                            OdArray<OdTvDbEntityPtr>& foregroundEnts,
                                            OdArray<OdTvDbEntityPtr>& curveTangencyEnts,
                                            bool                    bIsSetProperties);

  virtual OdResult trimSurface( const OdTvDbObjectIdArray& toolIds,
                                const OdTvDbObjectIdArray& toolCurveIds, 
                                const OdGeVector3dArray& projVectors,
                                const OdGePoint3d&       pickPoint, 
                                const OdGeVector3d&      viewVector,
                                bool                     bAutoExtend,
                                bool                     bAssociativeEnabled);

  virtual OdResult projectOnToEntity( const OdTvDbEntity*   pEntityToProject,
                                      const OdGeVector3d& projectionDirection,
                                      OdTvDbEntityPtrArray& projectedEntities ) const;

  virtual OdResult createSculptedSolid(OdTvDbEntityPtrArray& limitingBodies,
                                       const OdGeIntArray& limitingFlags);

  virtual OdResult rayTest( const OdGePoint3d&      rayBasePoint, 
                            const OdGeVector3d&     rayDir,
                            double                  rayRadius, 
                            OdArray<OdDbSubentId> & subEntIds, 
                            OdGeDoubleArray&        parameters) const;

  virtual OdResult offsetBody(double offsetDistance);
  //virtual OdResult offsetBody(OdTvDbEntity* pOffsetEnt, double offsetDistance);
  

  virtual OdResult createFilletSurface (OdTvDbSurfacePtr&      surf1,
                                        const OdGePoint3d&   pickPt1,
                                        OdTvDbSurfacePtr&      surf2,
                                        const OdGePoint3d&   pickPt2,
                                        double               dRadius,
                                        OdDb::FilletTrimMode trimMode,
                                        const OdGeVector3d&  projDir);

  virtual OdResult extendEdges( OdTvDbFullSubentPathArray& edgesId,
                                double                   dExtDist, 
                                EdgeExtensionType        extOption );

  virtual OdResult getObjectMesh( const OdTvDbFaceterSettings *faceter,
    OdGePoint3dArray& vertexArray, 
    OdInt32Array& faceArray,
    OdGiFaceData*& faceData);

  virtual OdResult getPerimeter(double& regionPerimeter) const;
  virtual OdResult getArea(double& dArea) const;
  virtual OdResult createCachedCurves(OdGeCurve3dPtrArray& pCurves);
  virtual OdResult convertTo(const OdGePoint3dArray &arrVertexes, const OdInt32Array &arrEdges, const OdInt32Array &arrFaces, OdGiFaceData &fd,
                             OdBoolArray &arrFacesColors, OdBoolArray &arrFacesMaterials, OdTvDbEntity* pEntity);

  OdResult getEdgeSubentityGeometry(OdArray<OdUInt32> indexesOfEdgeCalculation, OdGeCurve3d*& pEdgeCurve);
  OdResult restoreAttributes(OdTvDbObject *oldObject /*ACIS::File *pOldAcisData*/);
  virtual OdResult  addSubentitySpecialSettings(const OdDbSubentId subentId, OdArray<OdUInt32>& retArray, OdUInt32 idx);
  OdRevisionGuid& getRevGUID() { return m_revisionGuid; };
protected:
  bool worldDrawIsolines(OdGiWorldDraw* pWd, OdUInt32 nDatabaseIsolines);
  bool drawCachedSilhouettes(OdGiViewportDraw* pWd);
  void drawWires(OdGiWorldDraw* pWd, OdUInt32 geomType, bool drawIsolines, bool extentsMode);

  // support differences between 3dSolid and SURFACE rendering implementation
  virtual OdUInt32 isolinesMode() const { return BrepRenderModes::kIsolines; }
  virtual const OdModelerGeometry::NumIsolines * numIsolines() const { return 0; }

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler);

  bool m_bStandardSaveFlag;

  OdUInt32 m_uiCounterChanges;
  virtual void modified()
  {
    ++m_uiCounterChanges;
    if (this->isDBRO())
    {
      if (isModifiedGraphics())
      {
        m_revisionGuid.m_bIsSet ? m_revisionGuid.generateDifferent() : m_revisionGuid.enable(true);
      }
    }
  }

  virtual OdResult modified(OdResult res)
  {
    if (eOk == res)
    {
      ++m_uiCounterChanges;
      if (this->isDBRO())
      {
        if (isModifiedGraphics())
        {
          m_revisionGuid.m_bIsSet ? m_revisionGuid.generateDifferent() : m_revisionGuid.enable(true);
        }
      }
    }
    return res;
  }

public:
  virtual OdResult getBoundingBox(OdGeExtents3d &box);
  
  virtual OdResult generateSectionGeometry( SectArgs& sectArgs, OdTvDbEntity *pEnt, bool* bHasForeground );

  friend class OdTvDbEmbeddedASMEntPropsPE;
};


inline bool OdTvDbModelerGeometryImpl::isReallyAnsi(const OdAnsiString &storage) {
  // This method was added to fix cr10090 (see ConversionSatToUnicode_10090_IS).
  // wrAnsiString incorrectly saves chars with codes >=128. (It must be saved as two bytes)
  const char *pCur = storage.c_str();
  const char *pEnd = pCur + storage.getLength();
  while(pCur != pEnd) {
    // see OdCharMapper::unicodeToUtf8
    if ((unsigned char)(*pCur) >= 0x80)
      return false;
    ++pCur;
  }
  return true;
}

#endif // _ODDB_MODELERGEOMETRY_IMPL_INCLUDED_

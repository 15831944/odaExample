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

class OdDbRegion;
class OdDbRevolveOptions;
class OdDbSweepOptions;
class OdDbLoftOptions;
class OdDbBlendOptions;
class OdDbAsciiDxfFilerImpl;

class OdEmptyAcisError : public OdError_WithId
{
public:
  OdEmptyAcisError(OdDbObjectId id)
    : OdError_WithId( eEmptyAcisFile
                    , id.isNull() ? ((OdDbStub*)OdDbObjectId::kNull) : ((OdDbStub*)id)
                    , id.isNull() ? OdString::kEmpty : id.safeOpenObject()->isA()->name())
  {
  }
};

// AC27 support
class OdDbRevisionGuid : public OdGUID // used in Model-Doc feature to reference body geometry revision
{
public:
  OdDbRevisionGuid() {};

  OdDbRevisionGuid(const OdString& value) 
  { 
    *this = value; 
  }

  OdDbRevisionGuid& operator=(const OdString& str)
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

  static void createGuid(OdDbRevisionGuid &newGuid) {
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

  OdResult dxfInRaw(OdDbDxfFiler* pFiler) 
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

  void dxfOutRaw(OdDbDxfFiler* pFiler) const 
  { // Model-Doc way
     const OdUInt8 *RevGUIDData = data();
     pFiler->wrInt32(90, *reinterpret_cast<const OdUInt32*>(RevGUIDData));
     pFiler->wrInt16(70, *reinterpret_cast<const OdUInt16*>(RevGUIDData + 4));
     pFiler->wrInt16(70, *reinterpret_cast<const OdUInt16*>(RevGUIDData + 6));
     for (int i = 0; i < 8; ++i)
       pFiler->wrInt8(280, RevGUIDData[8 + i]);
  }

  void dwgIn(OdDbDwgFiler* pFiler)
  {
    OdUInt32 data32 = pFiler->rdInt32();
    OdUInt16 data16_1 = pFiler->rdInt16();
    OdUInt16 data16_2 = pFiler->rdInt16();
    OdUInt8 data8[8];
    for (int i = 0; i < 8; ++i)
      data8[i] = pFiler->rdInt8();
    setGUIDdata(data32, data16_1, data16_2, data8);
  }

  void dwgOut(OdDbDwgFiler* pFiler) const
  {
    const OdUInt8 *RevGUIDData = data();
    pFiler->wrInt32(*reinterpret_cast<const OdUInt32*>(RevGUIDData));
    pFiler->wrInt16(*reinterpret_cast<const OdUInt16*>(RevGUIDData + 4));
    pFiler->wrInt16(*reinterpret_cast<const OdUInt16*>(RevGUIDData + 6));
    for (int i = 0; i < 8; ++i)
      pFiler->wrInt8(RevGUIDData[8 + i]);
  }
};

struct OdRevisionGuid : public OdDbRevisionGuid
{
  bool     m_bIsSet;

  OdRevisionGuid():m_bIsSet(false)
  {
  }

  OdRevisionGuid(const OdChar* value) 
  { 
    *this = value; 
  }

  void dxfIn(OdDbDxfFiler* pFiler)
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
      OdDbRevisionGuid::operator=(pFiler->rdString());
    }
    else
    {
      OdUInt8 data8[8] = { 0 };
      setGUIDdata(0, 0, 0, data8);
      ODA_FAIL_M_ONCE("Unexpected group while reading OdRevisionGuid");
    }
  }

  void dxfOut(OdDbDxfFiler* pFiler) const
  {
    pFiler->wrBool(290, m_bIsSet);
    pFiler->wrString(2, ascii());
  }

  void dwgIn(OdDbDwgFiler* pFiler)
  {
    m_bIsSet = pFiler->rdBool();
    OdDbRevisionGuid::dwgIn(pFiler);
  }

  void dwgOut(OdDbDwgFiler* pFiler) const
  {
    pFiler->wrBool(m_bIsSet);
    OdDbRevisionGuid::dwgOut(pFiler);
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

namespace OdDbModelerThreads
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
    ThreadIds() : m_nThreadsToStartModeler(0) {}
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

bool saveEmptyAllowed(const OdDbObject *pModeler, OdDbFiler::FilerType filerType);
bool saveEmptyAllowed(const OdDbObjectImpl *pModeler, OdDbFiler::FilerType filerType);
bool doAcisAudit(const OdDbObjectImpl *pModeler, OdDbFiler::FilerType filerType);

class DBENT_EXPORT OdDbModelerGeometryImpl : public OdDbEntityImpl
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

  bool restoreGuidInfo(OdResBufPtr pXData);

public:
  static OdDbModelerGeometryImpl* getImpl(const OdDbObject *pObj)
  { return (OdDbModelerGeometryImpl*)OdDbSystemInternals::getImpl(pObj);}
  bool isEmbedded() {return m_bEmbedded;}
  void setEmbedded(bool bEmbedded)  {m_bEmbedded = bEmbedded;}
private:
  OdRevisionGuid m_revisionGuid; // Guid  will be changed with new, after each modification in Acad

public:
  OdRevisionGuid revisionGuid() const { return m_revisionGuid; }

  // material cache - unknown features (new in 2007)
  struct OdDbMGMaterials
  {
    OdUInt32              nMaterialIdLow;
    OdUInt32              nMaterialIdHigh;
    OdDbHardPointerId    MaterialHP;

    OdDbMGMaterials()
      : nMaterialIdLow(0)
      , nMaterialIdHigh(0)
    {}
    OdUInt64 materialId() const { return nMaterialIdLow + (((OdUInt64)nMaterialIdHigh)<<32); }
  };

  class MaterialMap : public OdArray<OdDbMGMaterials>
  {
  public:
    void add(OdDbObjectId id)
    {
      OdDbMGMaterials tmp;
      tmp.MaterialHP = id;
      tmp.nMaterialIdLow = (OdUInt64)id->getHandle() & 0xFFFFFFFF;
      tmp.nMaterialIdHigh = ((OdUInt64)id->getHandle()) >> 32;
      append(tmp);
    }
    bool hasMaterialId(OdUInt64 id, OdDbObjectId *pMat = 0, OdUInt32* index = 0) const
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

  static void dxfSATreading_unicode(OdDbDxfFiler* pFiler, OdMemoryStreamPtr pLoadedData);
  static void dxfSATreading_ansi(OdDbAsciiDxfFilerImpl* pFiler, OdMemoryStreamPtr pLoadedData);

  // Make Wire public so that wrSilhouette can use it below (Solaris).
public:
  static bool isReallyAnsi(const OdAnsiString &storage);

  static void dwgIn(wrWire *pWire, OdDbDwgFiler* pFiler);
  static void dwgOut(const wrWire *pWire, OdDbDwgFiler* pFiler, const OdGeMatrix3d* xMat);
  static void dwgIn(wrSilhouette *pSil, OdDbDwgFiler* pFiler);
  static void dwgOut(const wrSilhouette *pSil, OdDbDwgFiler* pFiler, const OdGeMatrix3d* xMat);

  OdModelerGeometryPtr getModeler(OdDbAuditInfo* pAuditInfo = NULL, bool bEnableAcisAudit = false) const;

  virtual void setMaterial(OdDbObjectId id, bool /*doSubents*/ = true);
  virtual void setMaterialMapper(const OdGiMapper* mapper);

  virtual OdResult setColorIndex(OdUInt16 colorInd, bool doSubents = true);
  virtual OdResult setColor(const OdCmColor& clr, bool doSubents = true);
  virtual OdResult setColorId(OdDbObjectId clrId, bool doSubents = true);

  static void writeSAT(OdDbDwgFiler* pFiler, OdStreamBuf* pStorage);
private:
  static OdStreamBufPtr readSAB(OdDbDwgFiler* pFiler);
  static void writeSAB(OdDbDwgFiler* pFiler, OdStreamBuf* pStorage);

  OdModelerGeometryPtr &getEdgesStore(OdDbAuditInfo* pAuditInfo = NULL, bool bEnableAcisAudit = false);

  void fillNurbCurvesArray();
  void drawCachedWires(OdGiCommonDraw& pCD, OdArray<wrWire> &Wires);

  void writeAcisDataCatched(OdDbDxfFiler* pFiler, OdModelerGeometry* pAcisData, bool saveEmptyAllowed) const
  {
    try
    {
      writeAcisData(pFiler, pAcisData, saveEmptyAllowed);
    }
    catch (const OdError& e)
    {
      if (e.code() == eEmptyAcisFile)
      {
        throw OdEmptyAcisError(objectId());
      }
      throw e;
    }
  }

protected:
  void initRevisionGuid()
  {
    if (!m_revisionGuid.m_bIsSet)
    {
      m_revisionGuid.enable(true);
    }
  }

  virtual void invalidateCache()
  {
    m_WireCache.invalidateCache();
    m_silhouettes.invalidateCache();
    m_pEdgesAcisData = 0;
    m_NurbCurves.setPhysicalLength(0);
    m_bHasPoint = false;
  }

  static OdResult setVisualPropsToSubent(const OdDbModelerGeometryImpl *pBody);
  void resetColorAndMaterial();

public:
  // OdDbObjectImpl overridden
  virtual void audit(OdDbAuditInfo* pAuditInfo);


  static OdModelerGeometryPtr createModelerGeometryImpl(OdStreamBuf* pStreamIn, bool bStandardSaveFlag = true, OdDbAuditInfo* pAuditInfo = NULL, bool bEnableAcisAudit = false);
  
  OdResult explode( OdRxObjectPtrArray& entitySet ) const;
  OdResult transformBy( const OdGeMatrix3d& xform );
  
  OdResult acisOut(OdStreamBuf* pStream, AfTypeVer typeVer, OdDbAuditInfo *pAuInfo = NULL, bool bAcisAudit = false) const
  {
    if (getModeler(pAuInfo, bAcisAudit).get())
      return m_pModelerGeom->out(pStream, typeVer);
    return eOk;
  }

  OdResult acisIn(OdStreamBuf* pIn, AfTypeVer *typeVer = NULL, OdDbAuditInfo *pAuInfo = NULL, bool bAcisAudit = false)
  {
    if (getModeler(pAuInfo, bAcisAudit).get())
    {
      invalidateCache();
      if (pIn)
        return modified(m_pModelerGeom->in(pIn, typeVer));
      return m_pModelerGeom->in(pIn, typeVer);
    }
    return eOk;
  }

  void brep(OdBrBrep& brep) const;
  bool getFaceMesh(GeMesh::OdGeTrMesh& mesh, OdGsMarker iFace, const wrTriangulationParams& triangulationParams) const;

  TOOLKIT_EXPORT static OdModelerGeometryPtr readAcisData(OdDbDxfFiler* pFiler);
  TOOLKIT_EXPORT static void writeAcisData(OdDbDxfFiler* pFiler, OdModelerGeometry* pAcisData, bool saveEmptyAllowed, bool bEnableAcisAudit = false);
  static OdStreamBufPtr readSAT(OdDbDwgFiler* pFiler);

  OdDbModelerGeometryImpl();
  ~OdDbModelerGeometryImpl();

  bool isNull() const { return m_pModelerGeom.isNull(); }

  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler);

  virtual void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  friend class OdDbModelerGeometry;

  void drawOrderedEdges(OdGiWorldDraw* pWd);
  bool worldDraw(OdGiWorldDraw* pWd);
  void viewportDraw(OdGiViewportDraw* pVd);
  virtual OdResult setBody(const void* g);
  virtual void* body() const;
  void saveAs(OdGiWorldDraw* pWd, OdDb::DwgVersion ver);

  virtual void createBox( double xLen, double yLen, double zLen );
  virtual void createFrustum( double height, double xRadius, double yRadius, double topXRadius );
  virtual void createSphere( double radius );
  virtual void createTorus( double majorRadius, double minorRadius );
  virtual void createWedge( double xLen, double yLen, double zLen );

  virtual OdResult extrude(const OdDbRegion* region, double height, double taper, bool isSolid = true);
  virtual OdResult revolve(const OdDbRegion* region, const OdGePoint3d& axisPoint, const OdGeVector3d& axisDir, double angleOfRevolutionbool, bool isSolid = true);
  virtual OdResult extrudeAlongPath(const OdDbRegion* region, const OdDbCurve* path, double taperAngle = 0.0, bool isSolid = true);
  virtual OdResult imprintEntity(const OdDbEntity *pEntity);

  virtual OdResult getPlane(OdGePlane& regionPlane) const;

  virtual OdResult createExtrudedObject ( OdDbEntity* pSweepEnt,
                                          const OdGeVector3d& directionVec,
                                          OdDbSweepOptions& sweepOptions,
                                          bool isSolid = true, 
                                          bool bHistoryEnabled = false);

  virtual OdResult createLoftedObject(
    OdDbEntityPtrArray& crossSectionCurves,
    OdDbEntityPtrArray& guideCurves,
    OdDbEntity* pPathCurve, 
    OdDbLoftOptions& loftOptions,
    bool isSolid = true);

  virtual OdResult createBlendObject(
    OdDbEntityPtrArray& blendedEdges, OdDbBlendOptions& loftOptions,
    bool isSolid = true);

  //virtual OdResult createLoftedObjectByCoedges(
  //  OdDbEntityPtrArray& crossSectionCurves,
  //  OdDbEntityPtrArray& guideCurves,
  //  OdDbEntity* pPathCurve,
  //  OdDbLoftOptions& loftOptions,
  //  bool isSolid = true);

  virtual OdResult createRevolvedObject ( OdDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    double revAngle, double startAngle,
    OdDbRevolveOptions& revolveOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false);

  virtual OdResult createSweptObject ( OdDbEntity* pSweepEnt,
    OdDbEntity* pPathEnt,
    OdDbSweepOptions& sweepOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false);

  virtual OdResult copySubEntity(const OdDbSubentId &subentId, OdDbEntityPtr &newEntity) const;
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
											OdDbFullSubentPathArray& subentPaths, 
											const OdDbObjectIdArray* pEntAndInsertStack = 0) const;

  virtual OdResult getGsMarkersAtSubentPath(const OdDbFullSubentPath& subPath, 
                                            OdGsMarkerArray& gsMarkers) const;

  virtual OdUInt32 numChanges() const;

  virtual OdDbSubentId internalSubentId(void* ent) const;
  virtual void* internalSubentPtr(const OdDbSubentId& id) const;

  virtual OdResult setSubentColor(const OdDbSubentId &subentId, const OdCmColor &color);
  virtual OdResult getSubentColor(const OdDbSubentId &subentId, OdCmColor &color) const;
  virtual OdResult setSubentMaterial(const OdDbSubentId &subentId, OdDbObjectId matId);
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

  virtual OdResult booleanOper(OdDb::BoolOperType operation, OdDbModelerGeometryImpl* pOtherBody,
    OdModelerGeometry::geomType typeThis, OdModelerGeometry::geomType typeOther);
  virtual OdResult booleanOper(OdDb::BoolOperType operation, const OdDbModelerGeometryImpl* pOtherBody,
    OdModelerGeometry::geomType typeThis, OdModelerGeometry::geomType typeOther, OdModelerGeometryPtr& pResult, OdDbEntityPtrArray* intersectionEntities = NULL) const;

  virtual OdResult createFrom(const OdDbEntity* pEntity);

  virtual OdResult createSectionObjects(const OdGePlane& sectionPlane, OdDbEntityPtrArray& sectionObjects) const;

  virtual OdResult extrudeFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double height, double taper);
  virtual OdResult extrudeFacesAlongPath(const OdArray<OdDbSubentId *> &faceSubentIds, const OdDbCurve* path);

  virtual OdResult generateSectionGeometry( const OdDbSection*      pSection,
                                            OdDbEntityPtrArray&     sourceEntArr,
                                            OdArray<OdDbEntityPtr>& intBoundaryEnts,
                                            OdArray<OdDbEntityPtr>& intFillEnts,
                                            OdArray<OdDbEntityPtr>& backgroundEnts,
                                            OdArray<OdDbEntityPtr>& foregroundEnts,
                                            OdArray<OdDbEntityPtr>& curveTangencyEnts,
                                            bool                    bIsSetProperties);

  virtual OdResult trimSurface( const OdDbObjectIdArray& toolIds,
                                const OdDbObjectIdArray& toolCurveIds, 
                                const OdGeVector3dArray& projVectors,
                                const OdGePoint3d&       pickPoint, 
                                const OdGeVector3d&      viewVector,
                                bool                     bAutoExtend,
                                bool                     bAssociativeEnabled);

  virtual OdResult projectOnToEntity( const OdDbEntity*   pEntityToProject,
                                      const OdGeVector3d& projectionDirection,
                                      OdDbEntityPtrArray& projectedEntities ) const;

  virtual OdResult rayTest( const OdGePoint3d&      rayBasePoint, 
                            const OdGeVector3d&     rayDir,
                            double                  rayRadius, 
                            OdArray<OdDbSubentId> & subEntIds, 
                            OdGeDoubleArray&        parameters) const;

  virtual OdResult offsetBody(double offsetDistance);
  //virtual OdResult offsetBody(OdDbEntity* pOffsetEnt, double offsetDistance);
  

  virtual OdResult createFilletSurface (OdDbSurfacePtr&      surf1,
                                        const OdGePoint3d&   pickPt1,
                                        OdDbSurfacePtr&      surf2,
                                        const OdGePoint3d&   pickPt2,
                                        double               dRadius,
                                        OdDb::FilletTrimMode trimMode,
                                        const OdGeVector3d&  projDir);

  virtual OdResult extendEdges( OdDbFullSubentPathArray& edgesId,
                                double                   dExtDist, 
                                EdgeExtensionType        extOption );

  virtual OdResult getObjectMesh( const OdDbFaceterSettings *faceter,
    OdGePoint3dArray& vertexArray, 
    OdInt32Array& faceArray,
    OdGiFaceData*& faceData);

  virtual OdResult getPerimeter(double& regionPerimeter) const;
  virtual OdResult getArea(double& dArea) const;
  virtual OdResult createCachedCurves(OdGeCurve3dPtrArray& pCurves);
  virtual OdResult convertTo(const OdGePoint3dArray &arrVertexes, const OdInt32Array &arrEdges, const OdInt32Array &arrFaces, OdGiFaceData &fd,
                             OdBoolArray &arrFacesColors, OdBoolArray &arrFacesMaterials, OdDbEntity* pEntity);

  OdResult getEdgeSubentityGeometry(OdArray<OdUInt32> indexesOfEdgeCalculation, OdGeCurve3d*& pEdgeCurve);
  OdResult restoreAttributes(OdDbObject *oldObject /*ACIS::File *pOldAcisData*/);
  virtual OdResult  addSubentitySpecialSettings(const OdDbSubentId subentId, OdArray<OdUInt32>& retArray, OdUInt32 idx);
  OdRevisionGuid& getRevGUID() { return m_revisionGuid; };
protected:
  bool worldDrawIsolines(OdGiWorldDraw* pWd, OdUInt32 nDatabaseIsolines);
  bool drawCachedSilhouettes(OdGiViewportDraw* pWd);
  void drawWires(OdGiWorldDraw* pWd, OdUInt32 geomType, bool drawIsolines, bool extentsMode);

  // support differences between 3dSolid and SURFACE rendering implementation
  virtual OdUInt32 isolinesMode() const { return BrepRenderModes::kIsolines; }
  virtual const OdModelerGeometry::NumIsolines * numIsolines() const { return 0; }

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler);

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
  
  virtual OdResult generateSectionGeometry(SectArgs& sectArgs, OdDbEntity *pEnt, bool* bHasForeground);

  friend class OdDbEmbeddedASMEntPropsPE;
};


inline bool OdDbModelerGeometryImpl::isReallyAnsi(const OdAnsiString &storage) {
  // This method was added to fix cr10090 (see ConversionSatToUnicode_10090_IS).
  // wrAnsiString incorrectly saves chars with codes >=128. (It must be saved as two bytes)
  const char *pCur = storage.c_str();
  const char *pEnd = pCur + storage.getLength();
  while (pCur != pEnd) {
    // see OdCharMapper::unicodeToUtf8
    if ((unsigned char)(*pCur) >= 0x80)
      return false;
    ++pCur;
  }
  return true;
}


class OdDbDwgCopyFilerForCloneModelerGeometry : public OdDbDwgCopyFilerForClone
{
  static const int modelersSize = 2;
  OdModelerGeometryPtr m_modeler[modelersSize];
  int m_modelerCursor;

public:
  OdDbDwgCopyFilerForCloneModelerGeometry() : m_modelerCursor(0) {}

  OdModelerGeometry* getModeler() {
    if (m_modelerCursor == modelersSize)
      return NULL;
    return m_modeler[m_modelerCursor++].detach();
  }
  bool canPush() {
    return m_modelerCursor < modelersSize;
  }
  bool pushModeler(OdModelerGeometry* pModeler) {
    m_modeler[m_modelerCursor].attach(pModeler);
    return !m_modeler[m_modelerCursor++].isNull();
  }

public:
  //
  template <class T>
  static void copyFromImpl(T* self, const OdRxObject* pSource)
  {
    T* pSrc = T::cast(pSource);
    if (!pSrc)
      return self->T::copyFrom(pSource);

    //Following code is the copy of OdDbObject::copyFrom() where 
    //OdDbDwgCopyFilerForClone is replaced with OdDbDwgCopyFilerForCloneModelerGeometry.
    //That allows to copy modeler (ACIS) data directly by API call and avoid costly
    //output/input to/from SAT stream. See OdDbAcisIO::writeAcisData()/readAcisData().
    OdDbObjectImpl* pImpl = OdDbSystemInternals::getImpl(self);
    OdDbObjectImpl* pSrcImpl = OdDbSystemInternals::getImpl(pSrc);
    OdDbDatabase* pDb = pImpl->database();
    OdDbDatabase* pSrcDb = pSrcImpl->database();
    if (pSrcDb)
    {
      if (!pDb)
      {
        pImpl->setDatabase(pSrcDb);
        pDb = pSrcDb;
      }
      else if (pDb != pSrcDb)
      {
        throw OdError(eWrongDatabase);
      }
    }

    OdStaticRxObject<OdDbDwgCopyFilerForCloneModelerGeometry> filer;
    filer.setDatabaseRef(pDb);
    bool equalSrcDest = (self->isA() == pSrc->isA());
    if (equalSrcDest)
      pSrc->dwgOut(&filer);
    else
    { //only copy data if source != destination
      pSrcImpl->dwgOutXData(&filer);
      pSrc->T::dwgOutFields(&filer);
    }
    filer.m_modelerCursor = 0;
    filer.rewind();
    // copyFrom() leaves reactors untouched #16799
    OdDbObjectIdArray savedReactors(pImpl->m_Reactors);
    if (equalSrcDest)
      self->dwgIn(&filer);
    else
    {
      pImpl->dwgInXData(&filer);
      self->T::dwgInFields(&filer);
    }
    pImpl->m_Reactors = savedReactors;
    pSrcImpl->fire_copied(pSrc, self);
  }
};

#endif // _ODDB_MODELERGEOMETRY_IMPL_INCLUDED_

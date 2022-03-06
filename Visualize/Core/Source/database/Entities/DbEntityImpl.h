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

#ifndef _ODDBENTITYIMPL_INCLUDED_
#define _ODDBENTITYIMPL_INCLUDED_

#include "../DbSystemInternals.h"
#include "DbEntity.h"

#include "../Tables/DbLinetypeTableImpl.h"
#include "../PlotStyleRef.h"
#include "Ge/GeMatrix3d.h"
#include "DbHostAppServices.h"
#include "CmColor.h"
#include "TPtr.h"

class OdTvDbCurveImpl;
class OdTvResBuf;
class OdTvDbBlockReference;
class OdTvDbObjectContextData;
typedef OdSmartPtr<OdTvDbObjectContextData> OdTvDbObjectContextDataPtr;

#define ODIMPL_DEFINE_WCS_OCS_POINT(Name) \
  OdGePoint3d m_##Name;\
  \
  void toWcs##Name()\
  {\
    if (normal() != OdGeVector3d::kZAxis)\
    {\
      m_##Name.transformBy(OdGeMatrix3d::planeToWorld(normal()));\
    }\
  }\
  \
  OdGePoint3d ocs##Name() const\
  {\
    OdGePoint3d res##Name(m_##Name);\
    if (normal() != OdGeVector3d::kZAxis)\
    {\
      res##Name.transformBy(OdGeMatrix3d::worldToPlane(normal()));\
    }\
    return res##Name;\
  }

class OdEntityStub
{
public:
  OdEntityStub()
    : prevId(0)
    , nextId(0) {}

  OdTvDbObjectId prevId;
  OdTvDbObjectId nextId;
};
typedef OdSharedPtr<OdEntityStub> OdEntityStubPtr;

class TOOLKIT_EXPORT OdTvDbEntityImpl : public PlotStyleRef<OdTvDbObjectImpl>
{
protected:
  static OdTvDbEntityImpl* getImpl(const OdTvDbEntity *pObj)
  { return (OdTvDbEntityImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  // Data members
  double            m_dLinetypeScale;
  OdCmEntityColor   m_color;
  OdTvDbObjectId      m_colorDefId;
  OdTvCmTransparency  m_transparency;
  OdInt8            m_nLineweightIndex;

  virtual OdResult setColorIndex(OdUInt16 colorInd, bool doSubents = true);
  virtual OdResult setColor(const OdTvCmColor& clr, bool doSubents = true);
  virtual OdResult setColorId(OdTvDbObjectId clrId, bool doSubents = true);

private:
  OdInt8            m_nPlotStyleNameType;
  enum
  {
    kShadowsNotReceive = 1,
    kShadowsNotCast    = 2,
    kInvisible         = 4,
    kMaterialFlags     = 8+16,
    kMaterialMapper    = 32,
    kLSModChecked      = 64,
    kLSModXDataPresent = 128,
    kEntXDataFlags     = kMaterialMapper | kLSModChecked | kLSModXDataPresent,

    kNotSavedToTfFlags = kMaterialMapper
  };
  OdUInt8           m_entFlags;


// Run-time flags
  enum
  {
    kRtInvisible     = 1,
    kRtLinetypeScaleSet = 2,
    kRtColorSet = 4,
    kRtTransparencySet = 8,
    kRtLineweightSet = 16,
    kRtPlotStyleNameTypeSet = 32,
    kRtThicknessSet = 64,

    kRtAllPropsSet =  kRtLinetypeScaleSet 
                    | kRtColorSet
                    | kRtTransparencySet
                    | kRtLineweightSet
                    | kRtPlotStyleNameTypeSet
                    | kRtThicknessSet
  };
  OdUInt8           m_entRtFlags;

  mutable OdTvDbObjectId m_LayerId;
  OdBinaryData      m_grData;

  OdTvDbObjectId      m_visualStyles[3];

  // Supports loading of R15 dwg
  // (entities in container are placed as linked list)
  // 
  OdEntityStubPtr m_pEntityStub;
public:
  void attachEntityStub(const OdTvDbObjectId& prev, const OdTvDbObjectId& next);
  void attachEntityStub(const OdEntityStubPtr& pEntityStub);
  OdEntityStubPtr detachEntityStub();
  bool hasEntityStub() const { return !m_pEntityStub.isNull(); }

  // Supports partial loading of R15 dwg
  // 
  bool subErasePermanently() { return m_pEntityStub.isNull(); }
  static OdTvDbObjectId getNextEntId(const OdTvDbEntity* pEnt);
  static OdTvDbObjectId getPrevEntId(const OdTvDbEntity* pEnt);

  // Supports storing of GrData in proxy entities
  // 
  virtual OdUInt8* getGrDataBuffer(OdUInt32 nLen)
  {
    m_grData.resize(nLen);
    return m_grData.asArrayPtr();
  }
  virtual const OdUInt8* getGrData(OdUInt32& nLen) const
  {
    nLen = m_grData.length();
    return m_grData.getPtr();
  }
  virtual void createGrData(const OdTvDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);

  OdTvDbEntityImpl();
  ~OdTvDbEntityImpl();

  // OdTvDbObjectImpl overriden
  //
  virtual void setModified(bool v);
  virtual bool isEntity() const { return true; }

  ///////////////////////////////////////
  void setInvisible(bool value) { SETBIT(m_entFlags, kInvisible, value); }
  bool isInvisible() const { return GETBIT(m_entFlags, kInvisible); }

  void setTempInvisible(bool value) { SETBIT(m_entRtFlags, kRtInvisible, value); }
  bool isTempInvisible() const { return GETBIT(m_entRtFlags, kRtInvisible); }

  void setCastShadows(bool value) { SETBIT(m_entFlags, kShadowsNotCast, !value); }
  bool castShadows() const { return !GETBIT(m_entFlags, kShadowsNotCast); }

  void setReceiveShadows(bool value) { SETBIT(m_entFlags, kShadowsNotReceive, !value); }
  bool receiveShadows() const { return !GETBIT(m_entFlags, kShadowsNotReceive); }

  OdUInt8 shadowsFlags() const {return (OdUInt8)(m_entFlags & 3);}
  void    setShadowsFlags(int val)  {m_entFlags &= ~3; m_entFlags |= (val & 3);}

  OdUInt8 materialFlags() const {return (OdUInt8)((m_entFlags & kMaterialFlags) >> 3);}
  void    setMaterialFlags(int val)  {m_entFlags &= ~kMaterialFlags; m_entFlags |= ((val << 3) & kMaterialFlags);}

  OdDb::PlotStyleNameType plotStyleNameType() const
  {
    return (OdDb::PlotStyleNameType) ((m_nPlotStyleNameType > 0) ? m_nPlotStyleNameType : OdDb::kPlotStyleNameByLayer);
  }
  void setPlotStyleNameType(OdDb::PlotStyleNameType n)
  {
    SETBIT(m_entRtFlags, kRtPlotStyleNameTypeSet, true);
    m_nPlotStyleNameType = (OdInt8)n;
  }

  OdTvDbObjectId layerId() const;
  OdString layerName() const;
  void setLayerId(OdTvDbObjectId id); // this one does not check that id is in the same DB
  virtual void setLayer(OdTvDbObjectId id, bool doSubents = true);

  void setLinetypeWithCheck(const OdString& name, OdTvDbAuditInfo * pAudit);

  virtual double thickness() const {return 0.;}
  virtual void setThickness(double) {}

  virtual void setPropertiesFrom(const OdTvDbEntityImpl* pEntity, bool doSubents = true);

  virtual void setPlotStyleName(OdDb::PlotStyleNameType,
    OdTvDbObjectId newId = OdTvDbObjectId::kNull, bool doSubents = true);
  virtual void setLinetypeScale(double val, bool doSubents = true);
  virtual void setVisibility(OdDb::Visibility newVal, bool doSubents = true);
  virtual void setLineWeight(OdDb::LineWeight newVal, bool doSubents = true);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual void correctTextCoding(){}

  //  dxf data read function
  OdResult dxfReadData(OdTvDbDxfFiler* pFiler, int nCode, OdBinaryData *pData = NULL);

  void audit(OdTvDbAuditInfo* pAuditInfo);

  static OdTvDbObjectPtr BreakToBlock(OdTvDbEntityPtr pEnt, OdDb::DwgVersion ver, bool todatabase = true);
  OdTvDbObjectContextDataPtr getCurrentContextData(const OdTvDbObject*) const;
  OdTvDbObjectContextDataManager* m_pContextDataManager;
  OdTvDbObjectContextDataManager* contextDataManager() const {return m_pContextDataManager;}
  void createContextDataManager();
  bool decomposeAnnotations(OdTvDbObject*, OdDb::SaveType format, OdDb::DwgVersion version); // TODO: ANNO_CHANGE
  virtual void restoreAnnotativeLayer(OdTvDbObject* pObj, bool addFullContext);
  virtual void copyDefaultContext(OdTvDbObject* pObj);
  // to be called at the end of the composeForLoad()
  void syncDefaultAnnotationContextData(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual bool isAnnotativeForRendering() const { return isAnnotative(); }

///////////////////////////////////////////////////////////////////
  virtual OdTvDbObjectId materialId() const
  {
    if (m_MaterialId.isNull())
    {
      if (OdTvDbDatabase* pDb = database())
      {
        OdTvDbObjectId id;
        switch (materialFlags())
        {
        case 0: // -- bylayer
          id = pDb->byLayerMaterialId();
          break;
        case 1: // -- byblock
          id = pDb->byBlockMaterialId();
          break;
        case 2: // -- global
          id = pDb->globalMaterialId();
          break;
        /* case 3: // -- byId */
        }
        if (id.database() == pDb) // in case of xref database we should not store this id
          m_MaterialId = id;
        return id;
      }
    }
    return m_MaterialId;
  }

  bool hasByLayerMaterial() const
  { return (m_MaterialId.isNull() && materialFlags() == 0)
        || m_MaterialId == database()->byLayerMaterialId();}

  bool hasByBlockMaterial() const
  { return (m_MaterialId.isNull() && materialFlags() == 1)
        || m_MaterialId == database()->byBlockMaterialId();}

  bool hasGlobalMaterial() const
  { return (m_MaterialId.isNull() && materialFlags() == 2)
        || m_MaterialId == database()->globalMaterialId();}

  virtual void setMaterial(OdTvDbObjectId id, bool doSubents = true);

  class GiMapperTObj : public OdGiMapper
  { OdRefCounter m_refCounter;
    public: GiMapperTObj() : m_refCounter(0) {}
    void addRef() { ++m_refCounter; }
    void release() { if (!(--m_refCounter)) delete this; }
    OdGiMapper *giMapperPtr() { return this; }
  }; typedef TPtr<GiMapperTObj> GiMapperTPtr;
  GiMapperTPtr m_pMapper;
  const OdGiMapper* materialMapper();
  virtual void setMaterialMapper(const OdGiMapper* mapper);

  void setDgnLSModifiersImpl(const OdTvDbEntity *pEnt, OdGiSubEntityTraits *pTraits) const;
  void setDgnLSModifiers(const OdTvDbEntity *pEnt, OdGiSubEntityTraits *pTraits) const
  {
    if (GETBIT(m_entFlags, kLSModChecked) && !GETBIT(m_entFlags, kLSModXDataPresent))
      return;
    setDgnLSModifiersImpl(pEnt, pTraits);
  }

  OdTvDbObjectId visualStyleId(OdTvDbEntity::VisualStyleType vstype) const
  {
    return m_visualStyles[vstype];
  }
  virtual OdResult setVisualStyle(OdTvDbObjectId visualStyleId, OdTvDbEntity::VisualStyleType vstype, bool doSubents);

  virtual bool isAnnotative() const;
  
  virtual void copyXDataDuringExplode(OdTvDbEntity* pEnt, OdTvResBuf* xd);

  friend class OdTvDbEntity;
  friend class OdGiDrawableTraits;
  friend class OdTvDbBlockTableRecordImpl;
  friend class OdTvDbBlockTableRecord;
  friend class OdTvDbAlignedDimensionImpl;
  friend class OdPolylineBaseImpl;
  friend class OdTvEntityContainer;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
  friend class OdTvDwgFileWriter;
  friend class OdLayerIndexMap;
  friend class OdTvDb3PointAngularDimensionImpl;
  friend class ColorNameDxfLoadResolver;
  friend class OdTvDbHatchImpl;
  friend class DxfLoadResolverForCPConvertion;
  friend class OdTvDbEntityWithGrDataPEImpl;
  friend class OdTvDb2dPolyline;
  friend class OdTvDbPolygonMesh;
  friend class OdTvDbPolyFaceMesh;
  friend class OdTvDb3dPolyline;
  friend class OdTvDbGeoPositionMarker;
  friend struct OdTvDbEntityTfPE; 
}; 


TOOLKIT_EXPORT OdGeVector3d checkNormal(const OdGeVector3d&, OdTvDbAuditInfo *, OdTvDbObjectId);


class OdTvDb2dEntityImpl
{
protected:
  OdGeVector3d m_vNormal;
  double       m_dThickness;

public:
  OdTvDb2dEntityImpl()
    : m_vNormal(OdGeVector3d::kZAxis)
    , m_dThickness(0.)
  {}

  const OdGeVector3d& normal() const          { return m_vNormal; }
  void setNormal(const OdGeVector3d& normalv)
  {
    double dLen = normalv.length();
    if (dLen <= OdGeContext::gTol.equalVector())
    {
      throw OdError(eInvalidInput);
    }
    m_vNormal = normalv / dLen;
  }

  void setNormalWithCheck(const OdGeVector3d& v, OdTvDbAuditInfo * pA, OdTvDbObjectId id)
  { m_vNormal = checkNormal(v, pA, id);}

  virtual OdResult transformBy(const OdGeMatrix3d& xform) 
  { 
    OdGeVector3d vNewNormal(m_vNormal);
    vNewNormal.transformBy(xform);
    double dLen = vNewNormal.length();
    m_dThickness *= dLen;
    if (!OdZero(dLen))
    {
      m_vNormal = vNewNormal / dLen;
    }
    return eOk;
  };

  void audit(OdTvDbAuditInfo* pAuditInfo, OdTvDbObject * pObj);
};

TOOLKIT_EXPORT void odtvdbCreateContextDataManagerForEntity(OdTvDbEntity* ent);

#endif // _ODDBENTITYIMPL_INCLUDED_

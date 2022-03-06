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

class OdDbCurveImpl;
class OdResBuf;
class OdDbBlockReference;
class OdDbObjectContextData;
typedef OdSmartPtr<OdDbObjectContextData> OdDbObjectContextDataPtr;

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

  OdDbObjectId prevId;
  OdDbObjectId nextId;
};
typedef OdSharedPtr<OdEntityStub> OdEntityStubPtr;

class TOOLKIT_EXPORT OdDbEntityImpl : public PlotStyleRef<OdDbObjectImpl>
{
protected:
  static OdDbEntityImpl* getImpl(const OdDbEntity *pObj)
  { return (OdDbEntityImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  // Data members
  double            m_dLinetypeScale;
  OdCmEntityColor   m_color;
  OdDbObjectId      m_colorDefId;
  OdCmTransparency  m_transparency;
  OdInt8            m_nLineweightIndex;

  virtual OdResult setColorIndex(OdUInt16 colorInd, bool doSubents = true);
  virtual OdResult setColor(const OdCmColor& clr, bool doSubents = true);
  virtual OdResult setColorId(OdDbObjectId clrId, bool doSubents = true);

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

  mutable OdDbObjectId m_LayerId;
  OdBinaryData      m_grData;

  OdDbObjectId      m_visualStyles[3];

  // Supports loading of R15 dwg
  // (entities in container are placed as linked list)
  // 
  OdEntityStubPtr m_pEntityStub;
public:
  void attachEntityStub(const OdDbObjectId& prev, const OdDbObjectId& next);
  void attachEntityStub(const OdEntityStubPtr& pEntityStub);
  OdEntityStubPtr detachEntityStub();
  bool hasEntityStub() const { return !m_pEntityStub.isNull(); }

  // Supports partial loading of R15 dwg
  // 
  bool subErasePermanently() { return m_pEntityStub.isNull(); }
  static OdDbObjectId getNextEntId(const OdDbEntity* pEnt);
  static OdDbObjectId getPrevEntId(const OdDbEntity* pEnt);

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
  virtual void createGrData(const OdDbEntity* pEnt, OdBinaryData& data, OdDb::DwgVersion ver);

  OdDbEntityImpl();
  ~OdDbEntityImpl();

  // OdDbObjectImpl overriden
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

  OdDbObjectId layerId() const;
  OdString layerName() const;
  void setLayerId(OdDbObjectId id); // this one does not check that id is in the same DB
  virtual void setLayer(OdDbObjectId id, bool doSubents = true);

  void setLinetypeWithCheck(const OdString& name, OdDbAuditInfo * pAudit);

  virtual double thickness() const {return 0.;}
  virtual void setThickness(double) {}

  virtual void setPropertiesFrom(const OdDbEntityImpl* pEntity, bool doSubents = true);

  virtual void setPlotStyleName(OdDb::PlotStyleNameType,
    OdDbObjectId newId = OdDbObjectId::kNull, bool doSubents = true);
  virtual void setLinetypeScale(double val, bool doSubents = true);
  virtual void setVisibility(OdDb::Visibility newVal, bool doSubents = true);
  virtual void setLineWeight(OdDb::LineWeight newVal, bool doSubents = true);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual void correctTextCoding(){}

  //  dxf data read function
  OdResult dxfReadData(OdDbDxfFiler* pFiler, int nCode, OdBinaryData *pData = NULL);

  void audit(OdDbAuditInfo* pAuditInfo);

  static OdDbObjectPtr BreakToBlock(OdDbEntityPtr pEnt, OdDb::DwgVersion ver, bool todatabase = true);
  OdDbObjectContextDataPtr getCurrentContextData(const OdDbObject*) const;
  OdDbObjectContextDataManager* m_pContextDataManager;
  OdDbObjectContextDataManager* contextDataManager() const {return m_pContextDataManager;}
  void createContextDataManager();
  bool decomposeAnnotations(OdDbObject*, OdDb::SaveType format, OdDb::DwgVersion version); // TODO: ANNO_CHANGE
  virtual void restoreAnnotativeLayer(OdDbObject* pObj, bool addFullContext);
  virtual void copyDefaultContext(OdDbObject* pObj);
  // to be called at the end of the composeForLoad()
  void syncDefaultAnnotationContextData(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual bool isAnnotativeForRendering() const { return isAnnotative(); }

///////////////////////////////////////////////////////////////////
  virtual OdDbObjectId materialId() const
  {
    if (m_MaterialId.isNull())
    {
      if (OdDbDatabase* pDb = database())
      {
        OdDbObjectId id;
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

  virtual void setMaterial(OdDbObjectId id, bool doSubents = true);

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

  void setDgnLSModifiersImpl(const OdDbEntity *pEnt, OdGiSubEntityTraits *pTraits) const;
  void setDgnLSModifiers(const OdDbEntity *pEnt, OdGiSubEntityTraits *pTraits) const
  {
    if (GETBIT(m_entFlags, kLSModChecked) && !GETBIT(m_entFlags, kLSModXDataPresent))
      return;
    setDgnLSModifiersImpl(pEnt, pTraits);
  }

  OdDbObjectId visualStyleId(OdDbEntity::VisualStyleType vstype) const
  {
    return m_visualStyles[vstype];
  }
  virtual OdResult setVisualStyle(OdDbObjectId visualStyleId, OdDbEntity::VisualStyleType vstype, bool doSubents);

  virtual bool isAnnotative() const;
  
  virtual void copyXDataDuringExplode(OdDbEntity* pEnt, OdResBuf* xd);

  friend class OdDbEntity;
  friend class OdGiDrawableTraits;
  friend class OdDbBlockTableRecordImpl;
  friend class OdDbBlockTableRecord;
  friend class OdDbAlignedDimensionImpl;
  friend class OdPolylineBaseImpl;
  friend class OdEntityContainer;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
  friend class OdDwgFileWriter;
  friend class OdLayerIndexMap;
  friend class OdDb3PointAngularDimensionImpl;
  friend class ColorNameDxfLoadResolver;
  friend class OdDbHatchImpl;
  friend class DxfLoadResolverForCPConvertion;
  friend class OdDbEntityWithGrDataPEImpl;
  friend class OdDb2dPolyline;
  friend class OdDbPolygonMesh;
  friend class OdDbPolyFaceMesh;
  friend class OdDb3dPolyline;
  friend class OdDbGeoPositionMarker;
  friend struct OdDbEntityTfPE; 
}; 


TOOLKIT_EXPORT OdGeVector3d checkNormal(const OdGeVector3d&, OdDbAuditInfo *, OdDbObjectId);


class OdDb2dEntityImpl
{
protected:
  OdGeVector3d m_vNormal;
  double       m_dThickness;

public:
  OdDb2dEntityImpl()
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

  void setNormalWithCheck(const OdGeVector3d& v, OdDbAuditInfo * pA, OdDbObjectId id)
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

  void audit(OdDbAuditInfo* pAuditInfo, OdDbObject * pObj);
};

TOOLKIT_EXPORT void oddbCreateContextDataManagerForEntity(OdDbEntity* ent);

#endif // _ODDBENTITYIMPL_INCLUDED_

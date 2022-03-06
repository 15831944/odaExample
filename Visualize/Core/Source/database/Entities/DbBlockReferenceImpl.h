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

#ifndef _ODDBBLOCKREFIMPL_INCLUDED_
#define _ODDBBLOCKREFIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "EntityContainer.h"
#include "DbBlockReference.h"
#include "DbSystemInternals.h"
#include "Ge/GeScale3d.h"
#include "Ge/GeVector3d.h"
#include "DbObjectContextDataManager.h"
#include "DbBlockTableRecord.h"

class OdTvDbBlkRefObjectContextData;
class OdBlob;
class OdTvDbIdMappingImpl;

bool odtvdbTransformThenAppendEntities(OdBlob& entityIds, OdTvDbBlockTableRecord* pOwnerBlock,
                                            const OdGeMatrix3d& xform, OdBlob* pResIds = 0, OdTvDbIdMappingImpl* pIdMap = 0, OdGeVector3d* pNormal = 0);

class TOOLKIT_EXPORT OdTvDbBlockReferenceImpl : public OdTvEntitySeqEndContainer, public OdTvDbEntityImpl
{
  static OdTvDbBlockReferenceImpl* getImpl(const OdTvDbBlockReference *pObj)
  { return (OdTvDbBlockReferenceImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  //static const double m_dInsertTolerance;
public:
  ODIMPL_DEFINE_WCS_OCS_POINT(Position);

  OdGeScale3d       m_Scale;
  double            m_dAngle;
  OdGeVector3d      m_vNormal;
  const OdGeVector3d& normal() const  {return m_vNormal;}
  friend class OdTvDbBlockRepresentationContext;
  OdRxObjectPtr m_pRepresentationContext; // representation data for NDBRO dynamic block
  OdTvDbBlockTableRecordPtr m_pNDBROBlock;
private:
  OdTvDbHardPointerId m_BlockRecordId;
  bool              m_bIdAddedToBlock;
public:
  OdTvDbBlockReferenceImpl();

  const OdTvDbHardPointerId& getBlockRecordId() const { return m_BlockRecordId; };
  void setBlockRecordId(OdTvDbObjectId id);

  virtual void setNumRows(OdUInt16 n);
  virtual void setNumCols(OdUInt16 n);
  virtual void setRowSpacing(double sp);
  virtual void setColSpacing(double sp);

  OdGeMatrix3d blockTransform(OdTvDbBlkRefObjectContextData* ctx = 0) const;
  virtual bool applyClipBoundary(OdGiCommonDraw* pWd, OdGiGeometry& geom) const;
  OdTvDbBlockTableRecordPtr getBlock() const
  { 
    return m_pNDBROBlock.isNull() ? 
      OdTvDbBlockTableRecordPtr(m_BlockRecordId.openObject()) : m_pNDBROBlock;
  }
  bool getAttribsFollow() const { return !firstSubEntId().isNull() || !getSeqEndId().isNull(); }

protected:
  // Overriden from OdTvEntityContainer
  //
  const OdTvDbObjectImpl* dbObjectImpl() const { return this; }
  bool isValidSubentityClass(OdRxClass* pClass) const;

  // Overriden from OdTvEntitySeqEndContainer
  //
  virtual bool seqendShouldPresent()
  {
    return !firstSubEntId().isNull();
  }
  void addSeqEndIfNotPresent()
  {
    if (getAttribsFollow())
    {
      OdTvEntitySeqEndContainer::addSeqEndIfNotPresent();
    }
  }
  virtual void setSubentsColorIndex(OdUInt16 colorInd);
  virtual void setSubentsColor(const OdTvCmColor& color);
  virtual void setSubentsTransparency(const OdTvCmTransparency& trans);
  virtual void setSubentsDatabaseDefaults(OdTvDbDatabase *pDb);
  virtual void setSubentsColorId(OdTvDbObjectId clrId);
  virtual void setSubentsLayer(OdTvDbObjectId layer);
  virtual void setSubentsLinetype(OdTvDbObjectId l);
  virtual void setSubentsMaterial(OdTvDbObjectId m);
  virtual void setSubentsVisualStyle(OdTvDbObjectId visualStyleId, OdTvDbEntity::VisualStyleType vstype);
  virtual void setSubentsPlotStyleName(OdDb::PlotStyleNameType PSNType, OdTvDbObjectId newId);
  virtual void setSubentsMaterialMapper(const OdGiMapper* mapper);
  virtual void setSubentsLinetypeScale(double linetypeScale);
  virtual void setSubentsVisibility(OdDb::Visibility visibility);
  virtual void setSubentsLineWeight(OdDb::LineWeight lineWeight);
  virtual void setSubentsPropertiesFrom(const OdTvDbEntity* pSource);
  
  void transformAnnotationData(const OdGeMatrix3d& xform);
  void copyFromContextData(OdTvDbObject* ,OdTvDbObjectContextData* pData, OdTvDbObjectContextData* pDataDef);
  void draw(OdGiCommonDraw* pWd, OdGiGeometry& geom, const OdTvDbObject* pObject = 0);
  virtual OdTvEntityContainer* entContainer() ODRX_OVERRIDE { return this; }
  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;
  virtual void audit(OdTvDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;
  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
  virtual void recvPropagateModify(OdTvDbObject* pOwner, const OdTvDbObject* pSubObj) ODRX_OVERRIDE;
  virtual bool isAnnotative() const ODRX_OVERRIDE;
  virtual OdResult getTransformedCopy(const OdTvDbBlockReference* pObj, const OdGeMatrix3d& mat, OdTvDbEntityPtr& pCopy) const;
  virtual void restoreAnnotativeLayer(OdTvDbObject* pObj, bool addFullContext) ODRX_OVERRIDE;
  void drawUnresolved(OdTvDbBlockTableRecordPtr pBR, OdGiGeometry& geom);

private:
  void fixScale(OdTvDbAuditInfo* pAuditInfo);

  friend class OdTvDbBlockReference;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDbMLeaderImpl;
  friend class OdTvDbLeaderImpl;
  friend bool odtvdbTransformThenAppendEntities(OdBlob& entityIds, OdTvDbBlockTableRecord* pOwnerBlock, 
    const OdGeMatrix3d& xform, OdBlob* pResIds, OdTvDbIdMappingImpl* pIdMap, OdGeVector3d* pNormal);
  friend TOOLKIT_EXPORT void odtvdbComposeAnnotativeObjects(OdTvDbDatabase* pDb);
  friend struct OdTvDbBlockReferenceTfPE;
  friend OdResult exExplodeBlockRefGeometry(const OdTvDbBlockReference* pRef, OdRxObjectPtrArray& entitySet);
};

#endif // _ODDBBLOCKREFIMPL_INCLUDED_

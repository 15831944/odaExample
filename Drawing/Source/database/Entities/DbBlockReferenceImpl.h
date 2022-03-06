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

class OdDbBlkRefObjectContextData;
class OdBlob;
class OdDbIdMappingImpl;

bool oddbTransformThenAppendEntities(OdBlob& entityIds, OdDbBlockTableRecord* pOwnerBlock,
                                            const OdGeMatrix3d& xform, OdBlob* pResIds = 0, OdDbIdMappingImpl* pIdMap = 0, OdGeVector3d* pNormal = 0);

class TOOLKIT_EXPORT OdDbBlockReferenceImpl : public OdEntitySeqEndContainer, public OdDbEntityImpl
{
  static OdDbBlockReferenceImpl* getImpl(const OdDbBlockReference *pObj)
  { return (OdDbBlockReferenceImpl*)OdDbSystemInternals::getImpl(pObj);}

  //static const double m_dInsertTolerance;
public:
  ODIMPL_DEFINE_WCS_OCS_POINT(Position);

  OdGeScale3d       m_Scale;
  double            m_dAngle;
  OdGeVector3d      m_vNormal;
  const OdGeVector3d& normal() const  {return m_vNormal;}
  friend class OdDbBlockRepresentationContext;
  OdRxObjectPtr m_pRepresentationContext; // representation data for NDBRO dynamic block
  OdDbBlockTableRecordPtr m_pNDBROBlock;
private:
  OdDbHardPointerId m_BlockRecordId;
  bool              m_bIdAddedToBlock;
public:
  OdDbBlockReferenceImpl();

  const OdDbHardPointerId& getBlockRecordId() const { return m_BlockRecordId; };
  void setBlockRecordId(OdDbObjectId id);

  virtual void setNumRows(OdUInt16 n);
  virtual void setNumCols(OdUInt16 n);
  virtual void setRowSpacing(double sp);
  virtual void setColSpacing(double sp);

  OdGeMatrix3d blockTransform(OdDbBlkRefObjectContextData* ctx = 0) const;
  virtual bool applyClipBoundary(OdGiCommonDraw* pWd, OdGiGeometry& geom) const;
  OdDbBlockTableRecordPtr getBlock() const
  { 
    return m_pNDBROBlock.isNull() ? 
      OdDbBlockTableRecordPtr(m_BlockRecordId.openObject()) : m_pNDBROBlock;
  }
  bool getAttribsFollow() const { return !firstSubEntId().isNull() || !getSeqEndId().isNull(); }

protected:
  // Overriden from OdEntityContainer
  //
  const OdDbObjectImpl* dbObjectImpl() const { return this; }
  bool isValidSubentityClass(OdRxClass* pClass) const;

  // Overriden from OdEntitySeqEndContainer
  //
  virtual bool seqendShouldPresent()
  {
    return !firstSubEntId().isNull();
  }
  void addSeqEndIfNotPresent()
  {
    if (getAttribsFollow())
    {
      OdEntitySeqEndContainer::addSeqEndIfNotPresent();
    }
  }
  virtual void setSubentsColorIndex(OdUInt16 colorInd);
  virtual void setSubentsColor(const OdCmColor& color);
  virtual void setSubentsTransparency(const OdCmTransparency& trans);
  virtual void setSubentsDatabaseDefaults(OdDbDatabase *pDb);
  virtual void setSubentsColorId(OdDbObjectId clrId);
  virtual void setSubentsLayer(OdDbObjectId layer);
  virtual void setSubentsLinetype(OdDbObjectId l);
  virtual void setSubentsMaterial(OdDbObjectId m);
  virtual void setSubentsVisualStyle(OdDbObjectId visualStyleId, OdDbEntity::VisualStyleType vstype);
  virtual void setSubentsPlotStyleName(OdDb::PlotStyleNameType PSNType, OdDbObjectId newId);
  virtual void setSubentsMaterialMapper(const OdGiMapper* mapper);
  virtual void setSubentsLinetypeScale(double linetypeScale);
  virtual void setSubentsVisibility(OdDb::Visibility visibility);
  virtual void setSubentsLineWeight(OdDb::LineWeight lineWeight);
  virtual void setSubentsPropertiesFrom(const OdDbEntity* pSource);
  
  void transformAnnotationData(const OdGeMatrix3d& xform);
  void copyFromContextData(OdDbObject* ,OdDbObjectContextData* pData, OdDbObjectContextData* pDataDef);
  void draw(OdGiCommonDraw* pWd, OdGiGeometry& geom, const OdDbObject* pObject = 0);
  virtual OdEntityContainer* entContainer() ODRX_OVERRIDE { return this; }
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;
  virtual void audit(OdDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
  virtual void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj) ODRX_OVERRIDE;
  virtual bool isAnnotative() const ODRX_OVERRIDE;
  virtual OdResult getTransformedCopy(const OdDbBlockReference* pObj, const OdGeMatrix3d& mat, OdDbEntityPtr& pCopy) const;
  virtual void restoreAnnotativeLayer(OdDbObject* pObj, bool addFullContext) ODRX_OVERRIDE;
  void drawUnresolved(OdDbBlockTableRecordPtr pBR, OdGiGeometry& geom);

private:
  void fixScale(OdDbAuditInfo* pAuditInfo);

  friend class OdDbBlockReference;
  friend class OdDwgR12FileLoader;
  friend class OdDbMLeaderImpl;
  friend class OdDbLeaderImpl;
  friend bool oddbTransformThenAppendEntities(OdBlob& entityIds, OdDbBlockTableRecord* pOwnerBlock, 
    const OdGeMatrix3d& xform, OdBlob* pResIds, OdDbIdMappingImpl* pIdMap, OdGeVector3d* pNormal);
  friend TOOLKIT_EXPORT void oddbComposeAnnotativeObjects(OdDbDatabase* pDb);
  friend struct OdDbBlockReferenceTfPE;
  friend OdResult exExplodeBlockRefGeometry(const OdDbBlockReference* pRef, OdRxObjectPtrArray& entitySet);
};

#endif // _ODDBBLOCKREFIMPL_INCLUDED_

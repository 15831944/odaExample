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

#ifndef _DbBlocksActionsImpl_h_Included_
#define _DbBlocksActionsImpl_h_Included_

#include "DbObjectImpl.h"
#include "DbEvalGraph.h"
#include "DbEvalGraphImpl.h"
#include "IntArray.h"
#include "Ge/GePoint2dArray.h"
#include "DbBlockElementImpl.h"
#include "DbEntity.h"

class OdTvDbBlockActionImpl : public OdTvDbBlockElementImpl
{
  friend class OdTvDbBlockAction;
protected:
  OdTvDbEvalNodeIdArray m_pElementsSelectionSet;
  OdArray<OdTvDbSoftPointerId> m_pSelection;
  OdGePoint3d m_pPosition;
  // used in derived actions
  void applyXYScaleType(OdGeVector3d &offset, OdTvDbBlockAction::OdTvDbBlockActionXYType xytype);
  void filterNodesSelection(const OdArray<OdTvDbSoftPointerId> &selection, OdTvDbBlockRepresentationContext* rep, const OdGeMatrix3d& m, OdTvDbObjectIdArray &ia) const;
  bool transformSelection( const OdArray<OdTvDbSoftPointerId>& selection, OdTvDbBlockRepresentationContext*, const OdGeMatrix3d& m ) const;
  bool transformSelection( OdTvDbBlockRepresentationContext*, const OdGeMatrix3d& m ) const;
public:
  OdTvDbBlockActionImpl(){}
  OdTvDbBlockParameterPtr getAssociatedParameter( OdDb::OpenMode mode = OdDb::kForRead ) const;
  OdTvDbEvalNodeId drivingParameterNodeId(OdTvDbEvalGraph*)const;
  OdTvDbObjectIdArray selectionSet() const;
  DECLARE_GET_IMPL(OdTvDbBlockAction);
};

class OdTvDbBlockAngleOffsetActionImpl : public OdTvDbBlockActionImpl
{
protected:
  // used in derived actions
  double m_dDistanceMultiplier;
  double m_dAngleOffset;
  double m_dUpdatedAngleOffset;
  void applyOffsets(OdGeVector3d &offset);
  OdTvDbEvalNodeIdArray m_Selelection2;
public:
  OdResult transformBy( const OdGeMatrix3d& m );
  void dwgInDoubles(OdTvDbDwgFiler* pFiler);
  void dwgOutDoubles(OdTvDbDwgFiler* pFiler) const;
  void dxfInDoubles(OdTvDbDxfFiler* pFiler, OdTvDbBlockAction::OdTvDbBlockActionXYType& nXYScaleType);
  void dxfOutDoubles(OdTvDbDxfFiler* pFiler, OdTvDbBlockAction::OdTvDbBlockActionXYType nXYScaleType) const;
  virtual bool hasInstanceData() const;
  virtual OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis)const;
  virtual bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*&, bool bRequireEvaluate);
  OdTvDbBlockAngleOffsetActionImpl() : m_dDistanceMultiplier(1.0), 
    m_dAngleOffset(0.0), m_dUpdatedAngleOffset(0.0) {}

};
class OdTvDbBlockMoveActionImpl : public OdTvDbConnectionPointsImpl<2, OdTvDbBlockAngleOffsetActionImpl>
{
  friend class OdTvDbBlockMoveAction;
  OdTvDbBlockAction::OdTvDbBlockActionXYType m_nXYScaleType;
public:
  OdTvDbBlockMoveActionImpl();
  virtual bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockMoveAction);
};

struct OdTvDbBlockStretchEntityItem
{
  OdTvDbSoftPointerId m_pId;
  OdIntArray m_pStretchPointIndices;
  OdTvDbBlockStretchEntityItem() : m_pId(0){}
};

struct OdTvDbBlockStretchNodeItem
{
  OdTvDbEvalNodeId m_nId;
  OdIntArray m_pStretchPointIndices;
  OdTvDbBlockStretchNodeItem() : m_nId(0){}
};

class OdTvDbBlockStretchActionImpl : public OdTvDbConnectionPointsImpl<2, OdTvDbBlockAngleOffsetActionImpl>
{
  friend class OdTvDbBlockStretchAction;
protected:
  OdArray<OdTvDbBlockStretchEntityItem> m_pEntitySelection;
  OdArray<OdTvDbBlockStretchNodeItem> m_pNodeSelection;
  bool selectionhasNode(OdTvDbEvalNodeId id);
  OdGePoint2dArray m_StretchFrame;
  OdTvDbBlockAction::OdTvDbBlockActionXYType m_nXYScaleType;
public:
  OdTvDbBlockStretchActionImpl();
  virtual bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockStretchAction);
};

class OdTvDbBlockActionWithBasePtImpl : public OdTvDbConnectionPointsImpl<2, OdTvDbBlockActionImpl>
{
  friend class OdTvDbBlockActionWithBasePt;
protected:
  OdGePoint3d m_pBasePoint;
  bool m_bIndependent;
  OdGePoint3d m_pOffset;
  OdGePoint3d m_pCurrentBasePoint;
  virtual OdTvResBufPtr saveInstanceData(const OdTvDbObject* pThis)const;
  virtual bool loadInstanceData(OdTvDbObject* pThis, const OdTvResBuf*&, bool bRequireEvaluate);
  virtual OdResult transformBy( const OdGeMatrix3d& );
  virtual void moveStretchPointsAt( const OdIntArray& ia , const OdGeVector3d& v) ODRX_OVERRIDE;
  void updateBasePoint();
public:
  OdTvDbBlockActionWithBasePtImpl();
  DECLARE_GET_IMPL(OdTvDbBlockActionWithBasePt);
};

class OdTvDbBlockScaleActionImpl : public OdTvDbConnectionPointsImpl<3, OdTvDbBlockActionWithBasePtImpl>
{
  friend class OdTvDbBlockScaleAction;
public:
  OdTvDbBlockScaleActionImpl();
  OdInt8 m_nXYScaleType;// can be moved to derived classes to reduce a bit used memory.
  virtual bool evaluate(const OdTvDbEvalContext* ctx);
  virtual bool hasInstanceData() const;
  DECLARE_GET_IMPL(OdTvDbBlockScaleAction);
};

class OdTvDbBlockRotateActionImpl : public OdTvDbConnectionPointsImpl<1, OdTvDbBlockActionWithBasePtImpl>
{
  friend class OdTvDbBlockRotateAction;
public:
  OdTvDbBlockRotateActionImpl();
  virtual bool historyRequired() const { return true; }
  virtual bool hasInstanceData() const { return true; }
  virtual bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockRotateAction);
};

class OdTvDbBlockFlipActionImpl : public OdTvDbConnectionPointsImpl<4, OdTvDbBlockActionImpl>
{
  friend class OdTvDbBlockFlipAction;
public:
  OdTvDbBlockFlipActionImpl();
  bool historyRequired() const { return true; }
  bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockFlipAction);
};

class OdTvDbBlockArrayActionImpl : public OdTvDbConnectionPointsImpl<4, OdTvDbBlockActionImpl>
{
  friend class OdTvDbBlockArrayAction;
protected:
  double m_dRowOffset;
  double m_dColumnOffset;
  void makeOffsetCopies( OdTvDbBlockRepresentationContext* rep, OdTvDbEntityPtrArray& res, const OdGeVector3d& ofs )const;
  static void eraseOldClones(OdTvDbBlockTableRecord* repBlock);
  static void shiftEntities( const OdTvDbEntityPtrArray& res, const OdGeVector3d& v );
public:
  OdTvDbBlockArrayActionImpl();
  bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockArrayAction);
};

class OdTvDbBlockParameter;

class OdTvDbBlockLookupActionImpl : public OdTvDbBlockActionImpl
{
  friend class OdTvDbBlockLookupAction;
protected:
  OdUInt32 m_nRows, m_nCols;
  OdStringArray m_pTableValues;
public:
  struct ColumnInfo
  {
    OdTvDbEvalNodeId m_nParameterId;
    int m_nResType;
    int m_nType; // unit type?
    bool m_bLookupProperty; // or input property
    OdString m_sUnmatched;
    bool m_bNotReadonly; // allows reverse lookup
    OdString m_sConnection;
    ColumnInfo() : m_nParameterId(0)
      , m_nResType(0)
      , m_nType(0)
      , m_bLookupProperty(true)
      , m_bNotReadonly(true){}
  };
protected:
  OdArray<ColumnInfo> m_pColumns;
  bool m_bUnk1;
  OdIntArray findCurrentState( const OdTvDbBlockParameter* ) const;
  bool isParameterStateValid(OdTvDbBlockParameter* pp, int N, const OdIntArray& states);
  int findParameter(OdTvDbEvalNodeId paramId);
public:
  OdString lookup(OdTvDbEvalNodeId paramId) const; // direct lookup, used for non-modified blocks
  OdTvDbBlockLookupActionImpl() : OdTvDbBlockActionImpl()
    , m_bUnk1(false), m_nRows(0), m_nCols(0) {}
  virtual OdTvResBufPtr getConnectionValue (const OdString& name) const;
  virtual bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockLookupAction);
};

class OdTvDbBlockPolarStretchActionImpl : public OdTvDbConnectionPointsImpl<6, OdTvDbBlockAngleOffsetActionImpl>
{
  friend class OdTvDbBlockPolarStretchAction;
protected:
  OdTvDbBlockPolarStretchActionImpl();
  OdGePoint2dArray m_StretchFrame;
  OdArray<OdTvDbSoftPointerId> m_pRotateSelection;
  OdArray<OdTvDbBlockStretchEntityItem> m_pEntitySelection;
  OdArray<OdTvDbBlockStretchNodeItem> m_pNodeSelection;
public:
  virtual bool historyRequired() const { return true; }
  virtual bool evaluate( const OdTvDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdTvDbBlockPolarStretchAction);
};

#endif // _DbBlocksActionsImpl_h_Included_

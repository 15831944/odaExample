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

class OdDbBlockActionImpl : public OdDbBlockElementImpl
{
  friend class OdDbBlockAction;
protected:
  OdDbEvalNodeIdArray m_pElementsSelectionSet;
  OdArray<OdDbSoftPointerId> m_pSelection;
  OdGePoint3d m_pPosition;
  // used in derived actions
  void applyXYScaleType(OdGeVector3d &offset, OdDbBlockAction::OdDbBlockActionXYType xytype);
  void filterNodesSelection(const OdArray<OdDbSoftPointerId> &selection, OdDbBlockRepresentationContext* rep, const OdGeMatrix3d& m, OdDbObjectIdArray &ia) const;
  bool transformSelection( const OdArray<OdDbSoftPointerId>& selection, OdDbBlockRepresentationContext*, const OdGeMatrix3d& m ) const;
  bool transformSelection( OdDbBlockRepresentationContext*, const OdGeMatrix3d& m ) const;
public:
  OdDbBlockActionImpl(){}
  OdDbBlockParameterPtr getAssociatedParameter( OdDb::OpenMode mode = OdDb::kForRead ) const;
  OdDbEvalNodeId drivingParameterNodeId(OdDbEvalGraph*)const;
  OdDbObjectIdArray selectionSet() const;
  void setSelectionSet(const OdDbObjectIdArray& selectionSet);
  DECLARE_GET_IMPL(OdDbBlockAction);
};

class OdDbBlockAngleOffsetActionImpl : public OdDbBlockActionImpl
{
protected:
  // used in derived actions
  double m_dDistanceMultiplier;
  double m_dAngleOffset;
  double m_dUpdatedAngleOffset;
  void applyOffsets(OdGeVector3d &offset);
  OdDbEvalNodeIdArray m_Selelection2;
public:
  OdResult transformBy( const OdGeMatrix3d& m );
  void dwgInDoubles(OdDbDwgFiler* pFiler);
  void dwgOutDoubles(OdDbDwgFiler* pFiler) const;
  void dxfInDoubles(OdDbDxfFiler* pFiler, OdDbBlockAction::OdDbBlockActionXYType& nXYScaleType);
  void dxfOutDoubles(OdDbDxfFiler* pFiler, OdDbBlockAction::OdDbBlockActionXYType nXYScaleType) const;
  virtual bool hasInstanceData() const;
  virtual OdResBufPtr saveInstanceData(const OdDbObject* pThis)const;
  virtual bool loadInstanceData(OdDbObject* pThis, const OdResBuf*&, bool bRequireEvaluate);
  OdDbBlockAngleOffsetActionImpl() : m_dDistanceMultiplier(1.0), 
    m_dAngleOffset(0.0), m_dUpdatedAngleOffset(0.0) {}

};
class OdDbBlockMoveActionImpl : public OdDbConnectionPointsImpl<2, OdDbBlockAngleOffsetActionImpl>
{
  friend class OdDbBlockMoveAction;
  OdDbBlockAction::OdDbBlockActionXYType m_nXYScaleType;
public:
  OdDbBlockMoveActionImpl();
  virtual bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockMoveAction);
};

struct OdDbBlockStretchEntityItem
{
  OdDbSoftPointerId m_pId;
  OdIntArray m_pStretchPointIndices;
  OdDbBlockStretchEntityItem() : m_pId(0){}
};

struct OdDbBlockStretchNodeItem
{
  OdDbEvalNodeId m_nId;
  OdIntArray m_pStretchPointIndices;
  OdDbBlockStretchNodeItem() : m_nId(0){}
};

class OdDbBlockStretchActionImpl : public OdDbConnectionPointsImpl<2, OdDbBlockAngleOffsetActionImpl>
{
  friend class OdDbBlockStretchAction;
protected:
  OdArray<OdDbBlockStretchEntityItem> m_pEntitySelection;
  OdArray<OdDbBlockStretchNodeItem> m_pNodeSelection;
  bool selectionhasNode(OdDbEvalNodeId id);
  OdGePoint2dArray m_StretchFrame;
  OdDbBlockAction::OdDbBlockActionXYType m_nXYScaleType;
public:
  OdDbBlockStretchActionImpl();
  virtual bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockStretchAction);
};

class OdDbBlockActionWithBasePtImpl : public OdDbConnectionPointsImpl<2, OdDbBlockActionImpl>
{
  friend class OdDbBlockActionWithBasePt;
protected:
  OdGePoint3d m_pBasePoint;
  bool m_bIndependent;
  OdGePoint3d m_pOffset;
  OdGePoint3d m_pCurrentBasePoint;
  virtual OdResBufPtr saveInstanceData(const OdDbObject* pThis)const;
  virtual bool loadInstanceData(OdDbObject* pThis, const OdResBuf*&, bool bRequireEvaluate);
  virtual OdResult transformBy( const OdGeMatrix3d& );
  virtual void moveStretchPointsAt( const OdIntArray& ia , const OdGeVector3d& v) ODRX_OVERRIDE;
  void updateBasePoint();
public:
  OdDbBlockActionWithBasePtImpl();
  DECLARE_GET_IMPL(OdDbBlockActionWithBasePt);
};

class OdDbBlockScaleActionImpl : public OdDbConnectionPointsImpl<3, OdDbBlockActionWithBasePtImpl>
{
  friend class OdDbBlockScaleAction;
public:
  OdDbBlockScaleActionImpl();
  OdInt8 m_nXYScaleType;// can be moved to derived classes to reduce a bit used memory.
  virtual bool evaluate(const OdDbEvalContext* ctx);
  virtual bool hasInstanceData() const;
  DECLARE_GET_IMPL(OdDbBlockScaleAction);
};

class OdDbBlockRotateActionImpl : public OdDbConnectionPointsImpl<1, OdDbBlockActionWithBasePtImpl>
{
  friend class OdDbBlockRotateAction;
public:
  OdDbBlockRotateActionImpl();
  virtual bool historyRequired() const { return true; }
  virtual bool hasInstanceData() const { return true; }
  virtual bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockRotateAction);
};

class OdDbBlockFlipActionImpl : public OdDbConnectionPointsImpl<4, OdDbBlockActionImpl>
{
  friend class OdDbBlockFlipAction;
public:
  OdDbBlockFlipActionImpl();
  bool historyRequired() const { return true; }
  bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockFlipAction);
};

class OdDbBlockArrayActionImpl : public OdDbConnectionPointsImpl<4, OdDbBlockActionImpl>
{
  friend class OdDbBlockArrayAction;
protected:
  double m_dRowOffset;
  double m_dColumnOffset;
  void makeOffsetCopies( OdDbBlockRepresentationContext* rep, OdDbEntityPtrArray& res, const OdGeVector3d& ofs )const;
  static void eraseOldClones(OdDbBlockTableRecord* repBlock);
  static void shiftEntities( const OdDbEntityPtrArray& res, const OdGeVector3d& v );
public:
  OdDbBlockArrayActionImpl();
  bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockArrayAction);
};

class OdDbBlockParameter;

class OdDbBlockLookupActionImpl : public OdDbBlockActionImpl
{
  friend class OdDbBlockLookupAction;
protected:
  OdUInt32 m_nRows, m_nCols;
  OdStringArray m_pTableValues;
public:
  struct ColumnInfo
  {
    OdDbEvalNodeId m_nParameterId;
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
  OdIntArray findCurrentState( const OdDbBlockParameter* ) const;
  bool isParameterStateValid(OdDbBlockParameter* pp, int N, const OdIntArray& states);
  int findParameter(OdDbEvalNodeId paramId);
public:
  OdString lookup(OdDbEvalNodeId paramId) const; // direct lookup, used for non-modified blocks
  OdDbBlockLookupActionImpl() : OdDbBlockActionImpl()
    , m_bUnk1(false), m_nRows(0), m_nCols(0) {}
  virtual OdResBufPtr getConnectionValue (const OdString& name) const;
  virtual bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockLookupAction);
};

class OdDbBlockPolarStretchActionImpl : public OdDbConnectionPointsImpl<6, OdDbBlockAngleOffsetActionImpl>
{
  friend class OdDbBlockPolarStretchAction;
protected:
  OdDbBlockPolarStretchActionImpl();
  OdGePoint2dArray m_StretchFrame;
  OdArray<OdDbSoftPointerId> m_pRotateSelection;
  OdArray<OdDbBlockStretchEntityItem> m_pEntitySelection;
  OdArray<OdDbBlockStretchNodeItem> m_pNodeSelection;
public:
  virtual bool historyRequired() const { return true; }
  virtual bool evaluate( const OdDbEvalContext* ctx );
  DECLARE_GET_IMPL(OdDbBlockPolarStretchAction);
};

#endif // _DbBlocksActionsImpl_h_Included_

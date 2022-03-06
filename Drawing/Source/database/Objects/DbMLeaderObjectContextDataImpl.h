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

#ifndef _ODDBMLEADEROJECTCONTEXTDATAIMPL_H_INCLUDED_
#define _ODDBMLEADEROJECTCONTEXTDATAIMPL_H_INCLUDED_

#include "DbObjectContextDataImpl.h" //#include "DbObjectContextData.h"
#include "DbMLeaderStyle.h"
#include "DbMLeader.h"
#include "DbMLeaderBreaks.h"

class OdDbMLeaderImpl;

//////////////////////////////////////////////////////////////////////////
// ML_Leader
//////////////////////////////////////////////////////////////////////////

struct ML_Leader  // LeaderLine
{
  ML_Leader()
    : m_dLandingDistance( 0.0 )
    , m_LeaderLineIndex( 0 )
    , m_ParentLeaderIndex( 0 )
    , m_LeaderType(OdDbMLeaderStyle::kStraightLeader)
    , m_LineWeight(OdDb::kLnWtByBlock)
    , m_ArrowSize(0.)
    , m_overrideFlag(0)
  {
    m_LineColor.setColorMethod(OdCmEntityColor::kByBlock);
    m_Points.resize( 0 );
  }

  double              m_dLandingDistance;
  OdGePoint3dArray    m_Points;
  OdArray<OdDbMLeaderBreaks::BreakInfo>  m_BreakInfo;
  OdInt32             m_LeaderLineIndex;
  OdInt32             m_ParentLeaderIndex;

  // AC24 support
  OdInt16             m_LeaderType;   // OdDbMLeaderStyle::LeaderType
  OdCmColor           m_LineColor;
  OdDbObjectId        m_LineTypeId;
  OdInt32             m_LineWeight;   // OdDb::LineWeight
  OdDouble            m_ArrowSize;
  OdDbObjectId        m_ArrowSymbolId;
  OdUInt32            m_overrideFlag;

  bool isOverride(OdDbMLeader::LeaderLineOverrideType flag) const
  { 
    return GETBIT(m_overrideFlag, (1<<flag));
  }

  void setLeaderType(OdDbMLeaderStyle::LeaderType leaderLineType)
  {
    m_LeaderType = (OdInt16)leaderLineType;
    SETBIT(m_overrideFlag, (1 << OdDbMLeader::kOverrideLeaderType), leaderLineType != OdDbMLeaderStyle::kStraightLeader);
  }
  void setLineColor(const OdCmColor& leaderLineColor)
  {
    m_LineColor = leaderLineColor;
    SETBIT(m_overrideFlag, (1 << OdDbMLeader::kOverrideLineColor), !leaderLineColor.isByBlock());
  }
  void setLineTypeId(OdDbObjectId leaderLineTypeId)
  {
    m_LineTypeId = leaderLineTypeId;
    SETBIT(m_overrideFlag, (1 << OdDbMLeader::kOverrideLineTypeId), !leaderLineTypeId.isNull());
  }
  void setLineWeight(OdDb::LineWeight leaderLineWeight)
  {
    m_LineWeight = leaderLineWeight;
    SETBIT(m_overrideFlag, (1 << OdDbMLeader::kOverrideLineWeight), leaderLineWeight != OdDb::kLnWtByBlock);
  }
  void setArrowSymbolId(OdDbObjectId arrowSymbolId)
  {
    m_ArrowSymbolId = arrowSymbolId;
    SETBIT(m_overrideFlag, (1 << OdDbMLeader::kOverrideArrowSymbolId), !arrowSymbolId.isNull());
  }
  void setArrowSize(double arrowSize)
  {
    m_ArrowSize = arrowSize;
    SETBIT(m_overrideFlag, (1 << OdDbMLeader::kOverrideArrowSize), arrowSize != 0.0);
  }
};
typedef OdArray<ML_Leader>      CLeaderArray;

//////////////////////////////////////////////////////////////////////////
// ML_Leader
//////////////////////////////////////////////////////////////////////////

// TODO as more nearest notation
#define m_LastLeaderPoint m_ConnectionPoint
#define m_BaseVector m_vDirection

struct ML_LeaderRoot  // Leader
{
  bool                m_isLastLeaderPoint; // m_bIsValidContent;
  bool                m_isBaseVector; // m_bool_2
  OdGePoint3d         m_ConnectionPoint; // m_LastLeaderPoint // Left/Right Leader bind point
  OdGeVector3d        m_vDirection; // m_BaseVector // Direction vector (dogleg direction)

  OdGePoint3dArray    m_BreakStartPoints;
  OdGePoint3dArray    m_BreakEndPoints;
  OdInt32             m_LeaderIndex;
  double              m_dLandingDistance;
  CLeaderArray        m_LeaderLines;
  OdInt16             m_AttachmentDirection;  // OdDbMLeaderStyle::TextAttachmentDirection

  ML_LeaderRoot()
    : m_isLastLeaderPoint(false)
    , m_isBaseVector(false)
    , m_LeaderIndex(0)
    , m_dLandingDistance(0.0)
    , m_AttachmentDirection(OdDbMLeaderStyle::kAttachmentHorizontal)
  {}
};
typedef OdArray<ML_LeaderRoot>  CLeaderRootArray;

//////////////////////////////////////////////////////////////////////////
// CMLContent
//////////////////////////////////////////////////////////////////////////

class CMLContent
{
public:
  OdUInt16      m_ContentType;
  OdGePoint3d   m_Location;
  OdGeVector3d  m_vNormal;
  double        m_dRotation;

  explicit CMLContent( OdUInt16 in_ContentType ) : m_dRotation( 0.0 )
  {
    m_ContentType = in_ContentType;
    m_vNormal = OdGeVector3d::kZAxis;
  }

  virtual void copyFrom( CMLContent* in_pContent )
  {
    m_ContentType = in_pContent->m_ContentType;
    m_Location = in_pContent->m_Location;
    m_vNormal = in_pContent->m_vNormal;
    m_dRotation = in_pContent->m_dRotation;
  }
  virtual ~CMLContent() {};
};

//////////////////////////////////////////////////////////////////////////
// OdDbMLeaderAnnotContextImpl
//////////////////////////////////////////////////////////////////////////

class OdDbMLeaderAnnotContextImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  CLeaderRootArray  m_LeaderRoot;

  double            m_dScaleOverall;
  OdGePoint3d       m_ContentBasePoint;
  double            m_dTextHeight;
  double            m_dArrowHeadSize;
  double            m_dLandingGap;
  OdUInt16          m_StyleLeftAttachment;
  OdUInt16          m_StyleRightAttachment;
  OdUInt16          m_TextAlignType;
  OdUInt16          m_AttachmentType;
  bool              m_bContentsText;
  bool              m_bContentsBlock;

  OdGePlane         m_Plane;
  OdGePoint3d       m_BasePoint;      // origin
  OdGeVector3d      m_BaseDirection;  // U vector
  OdGeVector3d      m_BaseVertical;   // V vector

  bool              m_NormalReversed;
  OdUInt16          m_ContentType;

  OdInt16           m_StyleTopAttachment;        // OdDbMLeaderStyle::TextAttachmentType
  OdInt16           m_StyleBottomAttachment;     // OdDbMLeaderStyle::TextAttachmentType

private:
  CMLContent*       m_pContent;
public:
  void updatePlane();
  void clearContent();
  CMLContent* newContent( CMLContent* inPContent );
  CMLContent* newContent( OdDbMLeaderStyle::ContentType inContentType );
  CMLContent* getContent( OdDbMLeaderStyle::ContentType inContentType );
  CMLContent* getContent() const { return m_pContent; }
  bool hasContent();
  void setScale(const OdDbObject* pObj, OdDbMLeaderImpl* pMLeaderImpl,
                double scale, bool bAdjustBlockLocation = false);
  void copyFrom(const OdDbMLeaderAnnotContextImpl* pFrom);

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  //virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
  //virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
  // #5862
  OdResult dxfInFields(OdDbDxfFiler* pFiler, bool bSkipBracketLines = false);
  void dxfOutFields(OdDbDxfFiler* pFiler, bool bSkipBracketLines = false) const;

  OdDbMLeaderAnnotContextImpl();
  virtual ~OdDbMLeaderAnnotContextImpl();

  void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};
typedef OdDbMLeaderAnnotContextImpl*  OdDbMLeaderAnnotContextImplPtr;

//////////////////////////////////////////////////////////////////////////
// OdDbMLeaderObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbMLeaderObjectContextDataImpl : public OdDbMLeaderAnnotContextImpl
{
public:
  static OdDbMLeaderObjectContextDataImpl* getImpl(const OdDbMLeaderObjectContextData* pObj)
  { return (OdDbMLeaderObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbMLeaderObjectContextDataImpl() : OdDbMLeaderAnnotContextImpl()
  {
  }

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;

  friend class OdDbMLeader;
};

#endif  // _ODDBMLEADEROJECTCONTEXTDATAIMPL_H_INCLUDED_

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

#ifndef _ODDBOJECTCONTEXTDATAIMPL_H_INCLUDED_
#define _ODDBOJECTCONTEXTDATAIMPL_H_INCLUDED_

#include "DbObjectContextData.h"
#include "DbMTextImpl.h"
#include "DbBlockReferenceImpl.h"
#include "UInt32Array.h"
#include "DbHatchImpl.h"
#include "DbDimensionImpl.h"
#include "DbAlignedDimensionImpl.h"
#include "Db2LineAngularDimensionImpl.h"
#include "DbDiametricDimensionImpl.h"
#include "DbOrdinateDimensionImpl.h"
#include "DbRadialDimensionImpl.h"
#include "DbRadialDimensionLargeImpl.h"
#include "DbFcfImpl.h"
#include "DbBlockTableRecord.h"
#include "DbMLeaderStyle.h"
#include "DbMLeader.h"
#include "DbMLeaderBreaks.h"

class OdTvDbMLeaderImpl;

class TOOLKIT_EXPORT OdTvDbObjectContextDataImpl : public OdTvDbObjectImpl
{
public:
  OdTvDbObjectContextDataImpl() : m_nVersion(3), m_bFileToExtensionDictionary(true), m_bModified(false), m_bDefault(false){}
  mutable OdInt16 m_nVersion;
  bool m_bFileToExtensionDictionary; 
  bool m_bModified;
  bool m_bDefault;
  OdTvDbObjectContextPtr m_pContext;
  static OdTvDbObjectContextDataImpl* getImpl(const OdTvDbObjectContextData* pObj)
  { return (OdTvDbObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdInt16 getOutVersion(OdTvDbFiler*);
};

class TOOLKIT_EXPORT OdTvDbAnnotScaleObjectContextDataImpl : public OdTvDbObjectContextDataImpl
{
public:
  OdTvDbHardPointerId m_pScale;
  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  static OdTvDbAnnotScaleObjectContextDataImpl* getImpl(const OdTvDbAnnotScaleObjectContextData* pObj)
  { return (OdTvDbAnnotScaleObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbMTextObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbMTextObjectContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  OdMTextRendererData m_RenderData;
  OdColumnsData m_ColumnsData;
  static OdTvDbMTextObjectContextDataImpl* getImpl(const OdTvDbMTextObjectContextData* pObj)
  { return (OdTvDbMTextObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbTextObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbTextObjectContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  static OdTvDbTextObjectContextDataImpl* getImpl(const OdTvDbTextObjectContextData* pObj)
  { return (OdTvDbTextObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbTextObjectContextDataImpl()
    : m_HorizontalMode(0)
    , m_dAngle(0)
  {
  }

  OdUInt16 m_HorizontalMode;
  double m_dAngle;
  OdGePoint2d m_Alignment;
  OdGePoint2d m_Position;

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbMTextAttributeObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbMTextAttributeObjectContextDataImpl : public OdTvDbTextObjectContextDataImpl
{
public:
  static OdTvDbMTextAttributeObjectContextDataImpl* getImpl(const OdTvDbMTextAttributeObjectContextData* pObj)
  { return (OdTvDbMTextAttributeObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbMTextAttributeObjectContextDataImpl()
  {
  }

  OdTvDbMTextObjectContextDataPtr m_mTextCD;
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbBlkRefObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbBlkRefObjectContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  static OdTvDbBlkRefObjectContextDataImpl* getImpl(const OdTvDbBlkRefObjectContextData* pObj)
  { return (OdTvDbBlkRefObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbBlkRefObjectContextDataImpl()
    : m_dRotation(0.)
  { }

  OdGePoint3d m_positionInEcs;
  double      m_dRotation;
  OdGeScale3d m_ScaleFactors;
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbHatchScaleContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbHatchScaleContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  static OdTvDbHatchScaleContextDataImpl* getImpl(const OdTvDbHatchScaleContextData* pObj)
  { return (OdTvDbHatchScaleContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbHatchScaleContextDataImpl()
    : m_dPatternScale(1.)
    , m_bIsCacheValid(false)
    , m_vPatternBaseAngle(OdGeVector3d::kXAxis)
  {
  }

  virtual ~OdTvDbHatchScaleContextDataImpl()
  {
    clearBoundary();
  }

  OdHatchPattern m_HatchDefLineList;
  double         m_dPatternScale;
  OdGeVector3d   m_vPatternBaseAngle;

  OdTvDbHatchImpl::LoopList m_LoopsList;

  OdGePoint2dArray m_startPts;
  OdGePoint2dArray m_endPts;
  bool m_bIsCacheValid;

  void clearBoundary();
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
//  OdTvDbHatchViewContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbHatchViewContextDataImpl: public OdTvDbHatchScaleContextDataImpl 
{
public:
  static OdTvDbHatchViewContextDataImpl* getImpl(const OdTvDbHatchViewContextData* pObj)
  { return (OdTvDbHatchViewContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbHatchViewContextDataImpl()
    : m_dAngle(0.)
    , m_bBool(false)
  {
  }

  OdTvDbSoftPointerId m_VPid;
  OdGeVector3d      m_vTarget;
  double            m_dAngle;
  bool              m_bBool;

  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*) ODRX_OVERRIDE;
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const ODRX_OVERRIDE;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbDimensionObjectContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  static OdTvDbDimensionObjectContextDataImpl* getImpl(const OdTvDbDimensionObjectContextData* pObj)
  { return (OdTvDbDimensionObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbDimensionObjectContextDataImpl()
    : m_Bool1(false)
    , m_bDefTextLocation(false)
    , m_bDimsoxd(false)
    , m_bDimtofl(false)
    , m_bDimtix(false)
    , m_Bool6(false)
    , m_bFlipSecondArrow(false)
    , m_bFlipFirstArrow(false)
    , m_dTextRotation(0.)
    , m_Dimatfit(0)
    , m_Dimtmove(0)
    , m_nFlags(0)
  {
  }
  OdTvDbBlockTableRecordPtr m_pNDBRDimBlock;
  OdTvDbHardPointerId       m_BlockRecordId;
  bool        m_Bool1
            , m_bDefTextLocation
            , m_bDimsoxd
            , m_bDimtofl
            , m_bDimtix
            , m_Bool6
            , m_bFlipSecondArrow
            , m_bFlipFirstArrow;
  OdGePoint2d m_TextLocation;
  double      m_dTextRotation;
  OdInt16     m_Dimatfit;
  OdInt16     m_Dimtmove;
  // 1 - m_bDimtofl 1-off
  // 2 - dimsoxd 1-off 
  // 4 - Dimatfit 1-used
  // 8 - Dimtex 1-used
  // 16 - Dimtmove 1-used
  OdUInt8     m_nFlags; 

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbAlignedDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbAlignedDimensionObjectContextDataImpl : public OdTvDbDimensionObjectContextDataImpl
{
public:
  static OdTvDbAlignedDimensionObjectContextDataImpl* getImpl(const OdTvDbAlignedDimensionObjectContextData* pObj)
  { return (OdTvDbAlignedDimensionObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbAlignedDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_Point;
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDb2LineAngularDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbAngularDimensionObjectContextDataImpl : public OdTvDbDimensionObjectContextDataImpl
{
public:
  static OdTvDbAngularDimensionObjectContextDataImpl* getImpl(const OdTvDbAngularDimensionObjectContextData* pObj)
  { return (OdTvDbAngularDimensionObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbAngularDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_Point;
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbDiametricDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbDiametricDimensionObjectContextDataImpl : public OdTvDbDimensionObjectContextDataImpl
{
public:
  static OdTvDbDiametricDimensionObjectContextDataImpl* getImpl(const OdTvDbDiametricDimensionObjectContextData* pObj)
  { return (OdTvDbDiametricDimensionObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbDiametricDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_chordPoint, m_farChordPoint;

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbOrdinateDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbOrdinateDimensionObjectContextDataImpl : public OdTvDbDimensionObjectContextDataImpl
{
public:
  static OdTvDbOrdinateDimensionObjectContextDataImpl* getImpl(const OdTvDbOrdinateDimensionObjectContextData* pObj)
  { return (OdTvDbOrdinateDimensionObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbOrdinateDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_Origin, m_LeaderEndPoint;
  
  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbRadialDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbRadialDimensionObjectContextDataImpl : public OdTvDbDimensionObjectContextDataImpl
{
public:
  static OdTvDbRadialDimensionObjectContextDataImpl* getImpl(const OdTvDbRadialDimensionObjectContextData* pObj)
  { return (OdTvDbRadialDimensionObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbRadialDimensionObjectContextDataImpl()
  {

  }
  OdGePoint3d m_chordPoint;

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbRadialDimensionLargeObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbRadialDimensionLargeObjectContextDataImpl: public OdTvDbRadialDimensionObjectContextDataImpl 
{
public:
  static OdTvDbRadialDimensionLargeObjectContextDataImpl* getImpl(const OdTvDbRadialDimensionLargeObjectContextData* pObj)
  { return (OdTvDbRadialDimensionLargeObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbRadialDimensionLargeObjectContextDataImpl()
  {

  }
  OdGePoint3d m_OverrideCenter, m_JogPoint;

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbFcfObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbFcfObjectContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  static OdTvDbFcfObjectContextDataImpl* getImpl(const OdTvDbFcfObjectContextData* pObj)
  { return (OdTvDbFcfObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdGePoint3d m_Point;
  OdGeVector3d m_XDir;

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
};

//////////////////////////////////////////////////////////////////////////

struct ML_Leader  // LeaderLine
{
  ML_Leader()
    : m_dLandingDistance( 0.0 )
    , m_LeaderLineIndex( 0 )
    , m_ParentLeaderIndex( 0 )
    , m_LeaderType(OdTvDbMLeaderStyle::kStraightLeader)
    , m_LineWeight(OdDb::kLnWtByBlock)
    , m_ArrowSize(0.)
    , m_overrideFlag(0)
  {
    m_LineColor.setColorMethod(OdCmEntityColor::kByBlock);
    m_Points.resize( 0 );
  }

  double              m_dLandingDistance;
  OdGePoint3dArray    m_Points;
  OdArray<OdTvDbMLeaderBreaks::BreakInfo>  m_BreakInfo;
  OdInt32             m_LeaderLineIndex;
  OdInt32             m_ParentLeaderIndex;

  // AC24 support
  OdInt16             m_LeaderType;   // OdTvDbMLeaderStyle::LeaderType
  OdTvCmColor           m_LineColor;
  OdTvDbObjectId        m_LineTypeId;
  OdInt32             m_LineWeight;   // OdDb::LineWeight
  OdDouble            m_ArrowSize;
  OdTvDbObjectId        m_ArrowSymbolId;
  OdUInt32            m_overrideFlag;

  bool isOverride(OdTvDbMLeader::LeaderLineOverrideType flag) const
  { 
    return GETBIT(m_overrideFlag, (1<<flag));
  }

  void setLeaderType(OdTvDbMLeaderStyle::LeaderType leaderLineType)
  {
    m_LeaderType = (OdInt16)leaderLineType;
    SETBIT(m_overrideFlag, (1 << OdTvDbMLeader::kOverrideLeaderType), leaderLineType != OdTvDbMLeaderStyle::kStraightLeader);
  }
  void setLineColor(const OdTvCmColor& leaderLineColor)
  {
    m_LineColor = leaderLineColor;
    SETBIT(m_overrideFlag, (1 << OdTvDbMLeader::kOverrideLineColor), !leaderLineColor.isByBlock());
  }
  void setLineTypeId(OdTvDbObjectId leaderLineTypeId)
  {
    m_LineTypeId = leaderLineTypeId;
    SETBIT(m_overrideFlag, (1 << OdTvDbMLeader::kOverrideLineTypeId), !leaderLineTypeId.isNull());
  }
  void setLineWeight(OdDb::LineWeight leaderLineWeight)
  {
    m_LineWeight = leaderLineWeight;
    SETBIT(m_overrideFlag, (1 << OdTvDbMLeader::kOverrideLineWeight), leaderLineWeight != OdDb::kLnWtByBlock);
  }
  void setArrowSymbolId(OdTvDbObjectId arrowSymbolId)
  {
    m_ArrowSymbolId = arrowSymbolId;
    SETBIT(m_overrideFlag, (1 << OdTvDbMLeader::kOverrideArrowSymbolId), !arrowSymbolId.isNull());
  }
  void setArrowSize(double arrowSize)
  {
    m_ArrowSize = arrowSize;
    SETBIT(m_overrideFlag, (1 << OdTvDbMLeader::kOverrideArrowSize), arrowSize != 0.0);
  }
};
typedef OdArray<ML_Leader>      CLeaderArray;

//////////////////////////////////////////////////////////////////////////

struct ML_LeaderRoot  // Leader
{
  bool                m_bIsValidContent;
  bool                m_bool_2;
  OdGePoint3d         m_ConnectionPoint;    // Left/Right Leader bind point
  OdGeVector3d        m_vDirection;         // Direction vector (dogleg direction)
  OdGePoint3dArray    m_BreakStartPoints;
  OdGePoint3dArray    m_BreakEndPoints;
  OdInt32             m_LeaderIndex;
  double              m_dLandingDistance;
  CLeaderArray        m_LeaderLines;
  OdInt16             m_AttachmentDirection;  // OdTvDbMLeaderStyle::TextAttachmentDirection

  ML_LeaderRoot()
    : m_bIsValidContent(false)
    , m_bool_2(false)
    , m_LeaderIndex(0)
    , m_dLandingDistance(0.0)
    , m_AttachmentDirection(OdTvDbMLeaderStyle::kAttachmentHorizontal)
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
// OdTvDbMLeaderAnnotContextImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbMLeaderAnnotContextImpl : public OdTvDbAnnotScaleObjectContextDataImpl
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

  OdInt16           m_StyleTopAttachment;        // OdTvDbMLeaderStyle::TextAttachmentType
  OdInt16           m_StyleBottomAttachment;     // OdTvDbMLeaderStyle::TextAttachmentType

private:
  CMLContent*       m_pContent;
public:
  void updatePlane();
  void clearContent();
  CMLContent* newContent( CMLContent* inPContent );
  CMLContent* newContent( OdTvDbMLeaderStyle::ContentType inContentType );
  CMLContent* getContent( OdTvDbMLeaderStyle::ContentType inContentType );
  CMLContent* getContent() const { return m_pContent; }
  bool hasContent();
  void setScale(double scale, 
                OdTvDbMLeaderImpl* pMLeaderImpl = NULL,
                bool bAdjustBlockLocation = false);
  void copyFrom(const OdTvDbMLeaderAnnotContextImpl* pFrom);

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  //virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  //virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  // #5862
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler, bool bSkipBracketLines = false);
  void dxfOutFields(OdTvDbDxfFiler* pFiler, bool bSkipBracketLines = false) const;

  OdTvDbMLeaderAnnotContextImpl();
  virtual ~OdTvDbMLeaderAnnotContextImpl();

  void composeForLoad(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};
typedef OdTvDbMLeaderAnnotContextImpl*  OdTvDbMLeaderAnnotContextImplPtr;

//////////////////////////////////////////////////////////////////////////
// OdTvDbMLeaderObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbMLeaderObjectContextDataImpl : public OdTvDbMLeaderAnnotContextImpl
{
public:
  static OdTvDbMLeaderObjectContextDataImpl* getImpl(const OdTvDbMLeaderObjectContextData* pObj)
  { return (OdTvDbMLeaderObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbMLeaderObjectContextDataImpl() : OdTvDbMLeaderAnnotContextImpl()
  {
  }

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;

  friend class OdTvDbMLeader;
};


//////////////////////////////////////////////////////////////////////////
// OdTvDbLeaderObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdTvDbLeaderObjectContextDataImpl : public OdTvDbAnnotScaleObjectContextDataImpl
{
public:
  static OdTvDbLeaderObjectContextDataImpl* getImpl(const OdTvDbLeaderObjectContextData* pObj)
  { return (OdTvDbLeaderObjectContextDataImpl*)OdTvDbSystemInternals::getImpl(pObj); }

  OdTvDbLeaderObjectContextDataImpl() : m_HooklineOnXDir(false)
  {
  }

  OdGePoint3dArray  m_Points;
  OdGeVector3d      m_TextOffset;
  OdGeVector3d      m_OffsetToBlkInsPt;
  OdGeVector3d      m_vXDir;
  bool              m_HooklineOnXDir;   // Hook line direction flag

  virtual OdResult dwgInContextData(OdTvDbDwgFiler*);
  virtual void dwgOutContextData(OdTvDbDwgFiler*) const;
  friend class OdTvDbLeader;
};


#endif  // _ODDBOJECTCONTEXTDATAIMPL_H_INCLUDED_

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

#ifndef _ODDBMLEADERIMPL_INCLUDED_
#define _ODDBMLEADERIMPL_INCLUDED_

#include "DbMLeader.h"
#include "DbSystemInternals.h"
#include "DbEntityImpl.h"
#include "OdList.h"
#include "DbMLeaderStyle.h"
#include "DbMLeaderStyleImpl.h"
#include "DbMlineImpl.h"
#include "DbObjectContextDataImpl.h"

class OdTvDbMLeaderImpl;

struct ML_Label
{
  OdTvDbObjectId        m_AttribDefId;
  OdString            m_String;
  OdUInt16            m_uiIndex;
  double              m_Width;

  ML_Label() : m_uiIndex(0), m_Width(0.0) {}
};
typedef OdArray<ML_Label>       CLabelArray;

/* \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ */

class MLContent_Text : public CMLContent
{
public:
//  OdUInt16          m_TextAlignmentType;
  OdString          m_TextLable;
  OdTvDbObjectId      m_TextStyleId;
  OdGeVector3d      m_vDirection;
  double            m_BoundaryWidth;
  double            m_BoundaryHeight;
  double            m_LineSpacingFactor;
  OdUInt16          m_LineSpacingStyle;
  OdInt16           m_TextAngle;
  OdTvCmColor         m_TextColor;
  OdUInt16          m_AlignmentType;
  OdUInt16          m_FlowDirection;

  bool              m_TextFrameEnabled;

  OdTvCmColor         m_BGFillColor;
  double            m_BGScaleFactor;
  OdTvCmTransparency  m_BGTransparency;
  bool              m_BGFillEnable;
  bool              m_BGMaskFillOn;

  OdUInt16          m_ColumnType;
  bool              m_TextAutoHeight;
  double            m_ColumnWidth;
  double            m_ColumnGutter;
  bool              m_ColumnFlowReversed;
  OdGeDoubleArray   m_ColumnSizes;
  bool              m_WordBreak;
  bool              m_UnknownBool_4;

  virtual void copyFrom( MLContent_Text* in_pContent )
  {
    CMLContent::copyFrom( in_pContent );
    m_TextLable = in_pContent->m_TextLable;
    m_TextStyleId = in_pContent->m_TextStyleId;
    m_vDirection = in_pContent->m_vDirection;
    m_BoundaryWidth = in_pContent->m_BoundaryWidth;
    m_BoundaryHeight = in_pContent->m_BoundaryHeight;
    m_LineSpacingFactor = in_pContent->m_LineSpacingFactor;
    m_LineSpacingStyle = in_pContent->m_LineSpacingStyle;
    m_TextAngle = in_pContent->m_TextAngle;
    m_TextColor = in_pContent->m_TextColor;
    m_AlignmentType = in_pContent->m_AlignmentType;
    m_FlowDirection = in_pContent->m_FlowDirection;

    m_TextFrameEnabled = in_pContent->m_TextFrameEnabled;

    m_BGFillColor = in_pContent->m_BGFillColor;
    m_BGScaleFactor = in_pContent->m_BGScaleFactor;
    m_BGTransparency = in_pContent->m_BGTransparency;
    m_BGFillEnable = in_pContent->m_BGFillEnable;
    m_BGMaskFillOn = in_pContent->m_BGMaskFillOn;

    m_ColumnType = in_pContent->m_ColumnType;
    m_TextAutoHeight = in_pContent->m_TextAutoHeight;
    m_ColumnWidth = in_pContent->m_ColumnWidth;
    m_ColumnGutter = in_pContent->m_ColumnGutter;
    m_ColumnFlowReversed = in_pContent->m_ColumnFlowReversed;
    m_ColumnSizes = in_pContent->m_ColumnSizes;
    m_WordBreak = in_pContent->m_WordBreak;
    m_UnknownBool_4 = in_pContent->m_UnknownBool_4;
  }

  MLContent_Text();
  virtual ~MLContent_Text();
};

class MLContent_Block : public CMLContent
{
public:
  OdTvDbObjectId      m_BlockId;
  OdGeScale3d       m_Scale;
  OdTvCmColor         m_BlockColor;
  OdGeMatrix3d      m_BlockXfm;

  virtual void copyFrom( MLContent_Block* in_pContent )
  {
    CMLContent::copyFrom( in_pContent );
    m_BlockId = in_pContent->m_BlockId;
    m_Scale = in_pContent->m_Scale;
    m_BlockColor = in_pContent->m_BlockColor;
    m_BlockXfm = in_pContent->m_BlockXfm;
  }
  MLContent_Block();
  virtual ~MLContent_Block();
};

struct ML_ArrowHeadPool
{
  bool          m_isDefault;
  OdTvDbObjectId  m_ArrowHeadId;

  ML_ArrowHeadPool(): m_isDefault(0){};
};
typedef OdArray<ML_ArrowHeadPool> CArrowHeadPool;

class OdTvDbMLeaderImpl : public OdTvDbEntityImpl
{
public:
  static OdTvDbMLeaderImpl* getImpl(const OdTvDbMLeader *pObj)
  { return (OdTvDbMLeaderImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  OdTvDbMLeaderAnnotContextImpl m_content;

  CLabelArray       m_Labels;
  CArrowHeadPool    m_ArrowHeadPool;
  OdUInt16          m_StyleContentType;
  OdUInt32          m_OverrideFlags;
  OdTvDbObjectId      m_LeaderStyleId;
  OdInt16           m_LeaderLineType;
  OdTvCmColor         m_LeaderColor;

  OdTvDbObjectId      m_LeaderLineTypeId;
  OdInt32           m_LeaderLineWeight;
  bool              m_bDoglegEnabled;
  bool              m_bHorisontalLanding;
  bool              m_bLandingEnabled;
  double            m_dLandingDistance;

  OdTvDbObjectId      m_ArrowHeadId;
  double            m_dArrowHeadSize_default;

  OdTvDbObjectId      m_StyleTextStyleId;
  OdUInt16          m_StyleTextAngle;
  OdUInt16          m_StyleTextAlignmentType; // m_UnkUInt16
  OdTvCmColor         m_StyleTextColor;
  bool              m_StyleTextFrameEnabled;
  OdTvDbObjectId      m_StyleBlockId;
  OdTvCmColor         m_StyleBlockColor;
  OdGeScale3d       m_StyleBlockScale;
  double            m_dBlockRotation;

  bool              m_TextDirectionNegative;
  double            m_StyleBlockRotation;
  OdUInt16          m_StyleAttachmentType;
  OdUInt16          m_IPEAlign;
  //OdUInt32        m_UnknownUInt32;

  OdTvDbObjectId      m_DefaultLeaderStyleId;

  bool              m_bIsAnnotative;
  bool              m_bCheckForAcadAnnoBug;
  OdUInt16          m_Justification;

  double            m_Scale;

  OdInt16           m_AttachmentDirection;  // OdTvDbMLeaderStyle::TextAttachmentDirection

  bool              m_bExtendLeaderToText;

  enum RecomputeFlags {
    kRecomp_All = 0, 
    // TODO kRecomp_None = 0, kRecomp_All = (| of all flags except kRecompSkip_...)
    //kRecomp_.. 
    kRecomp_IsDragging = 1,
    kRecompSkip_AutoSwitchDogleg = 2,
    kRecomp_AutoSwitchedIfSkip = 4, // used if kRecompSkip_AutoSwitchDogleg is on only
    //kRecomp_.. 
    kRecompSkip_All = 0x1000,   // for tests only
    kSkipAcadRenderBug = 0x2000 // for tests only
  };
  OdUInt32          m_RecomputeFlags; // this runtime flags will be cleared by next recompute // CORE-10758

  bool m_bSetMTextInvoked;

  static OdInt16    m_version;

  //OdArray<OdTvDbMLeaderAnnotContextImpl> m_annotContexts;

  OdTvDbMLeaderImpl();
  ~OdTvDbMLeaderImpl();

  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format,
                                      OdDb::DwgVersion version);
  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format,
                                    OdDb::DwgVersion version);
  //virtual void copyFromContextData(OdTvDbObject *pObj, OdTvDbObjectContextData* pData, OdTvDbObjectContextData* pDataDef); // CORE-13795

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbMLeaderAnnotContextImpl* content = NULL);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbMLeaderAnnotContextImpl* content = NULL) const;
  virtual void audit(OdTvDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;

  void decomposeToR21(OdTvDbMLeaderAnnotContextImpl* pContext);
  void composeFromR21(OdTvDbMLeaderAnnotContextImpl* pContext, OdUInt16 prevLeftAttach, OdUInt16 prevRightAttach);

  /*Services*/

  OdTvDbMLeaderAnnotContextImpl* getContextData( const OdTvDbObject* obj, const OdTvDbObjectContextData* in_Ctx );
  OdTvDbMLeaderAnnotContextImpl* getCurContextData0( const OdTvDbObject* obj, OdGiCommonDraw* pWd = NULL );
  OdTvDbMLeaderAnnotContextImpl* getCurContextData( const OdTvDbObject* obj, OdGiCommonDraw* pWd = NULL );

  const CMLContent* getContent(OdTvDbMLeaderStyle::ContentType inContentType)
  {
    return m_content.getContent(inContentType);
  }
  CMLContent* getContent() const 
  { 
    return m_content.getContent(); 
  }

  void setContentType(const OdTvDbObject* pObj, OdTvDbMLeaderStyle::ContentType contentType);

  void drawArrowHead( 
      const OdTvDbMLeaderAnnotContextImpl* pCurContext,
      OdGiGeometry* inGeometry,
      OdGiSubEntityTraits* inTraits,
      OdGiContext* inContext,
      OdGiRegenType regenType,
      const double& dSize, 
      OdGePoint3dArray& Points,
      const int inLeaderIndex );

  void getLeaderGeomExtents( 
    const OdTvDbMLeaderAnnotContextImpl* pCurContext,
    OdGeExtents3d& out_extents, bool bIncludeArrowHeads = false );

  void getArrowHeadGeomExtents(
      const OdTvDbMLeaderAnnotContextImpl* pCurContext,
      const OdGePoint3dArray& Points,
      const int inLeaderIndex,
      OdGeExtents3d& out_extents );

  bool drawForExtents( 
    const OdTvDbMLeaderAnnotContextImpl* pCurContext,
    OdGiWorldDraw* pWd );

  void setOverride( 
    OdUInt32 propertyType,
    bool isOverride );

  bool isOverride( OdUInt32 propertyType );

  OdTvDbMLeaderStylePtr MLeaderStyleForMLeaderOverrides(const OdTvDbObject* pObj);

  void setPlane(
    OdTvDbMLeaderAnnotContextImpl* pCurContext,
    const OdGePlane& plane);

  CLeaderRootArray::iterator addLeader(
    OdTvDbMLeaderAnnotContextImpl* pCurContext,
    int& lederIndex );
  
  void fixLeaderLines(CLeaderArray &toLeftTop, OdTvDbMLeaderAnnotContextImpl* pCurContext, const OdGeVector3d& vDirection);
  
  void removeLeader(
    OdTvDbMLeaderAnnotContextImpl* pCurContext,
    int leaderIndex );

  void connectionPoint(
    OdTvDbMLeaderAnnotContextImpl* pCurContext,
    const OdGeVector3d& vect,
    OdGePoint3d& point );

  void getLeaderIndexes(
    const OdTvDbMLeaderAnnotContextImpl* pCurContext,
    OdIntArray& leaderIndexes);

  void getLeaderLineIndexes(
    const OdTvDbMLeaderAnnotContextImpl* pCurContext,
    OdIntArray& leaderLineIndexes );

  void getLeaderLineIndexes(
    const OdTvDbMLeaderAnnotContextImpl* pCurContext,
    int leaderIndex,
    OdIntArray& leaderLineIndexes );
  void getLeaderLineArrayPtr(
    OdTvDbMLeaderAnnotContextImpl* pCurContext,
    OdArray<struct ML_Leader *>& leaderPtrArray );

  ML_Leader* getLeaderLineForComposeForLoad(OdTvDbMLeaderAnnotContextImpl* pCurContext, int lineIndex);

  void setTextLocation( OdTvDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d location );
  void setBlockLocation( OdTvDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d location );

  OdResult addLeaderLine(
      OdTvDbMLeaderAnnotContextImpl* pCurContext,
      const OdGePoint3d& inPoint, 
      int& leaderLineIndex);

  OdResult getLastVertex(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pCurContext,
                         CLeaderRootArray::iterator& root, CLeaderArray::iterator& line,
                         OdGePoint3d& point) const;
  OdResult setLastVertex(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pCurContext,
                         CLeaderRootArray::iterator& root, CLeaderArray::iterator& line, 
                         const OdGePoint3d& point);
  static int numVertices(OdTvDbMLeaderAnnotContextImpl* pCurContext, CLeaderRootArray::iterator& root, CLeaderArray::iterator& line);

  OdTvDbMTextPtr mtext(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pCurContext, 
                     bool addUnderline = true);
  OdTvDbMTextPtr mtext(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pCurContext,
                     MLContent_Text* pTextContent, bool addUnderline = true);
  void setMText(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pContext, 
                const OdTvDbMText* pMText, OdTvDbMLeaderAnnotContextImpl* pCurContext = NULL);
  
  void adjustContextToKeepConnectionPoint(const OdTvDbObject* pObj, const OdTvDbObjectContext& ctx);
  void adjustContextToKeepConnectionPoint(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pContext);
  void adjustContextToKeepConnectionPoint(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pContext,
                                          MLContent_Text* pTextContent, CLeaderRootArray::iterator& pRoot,
                                          const OdGeVector3d& vShiftOffset);

  OdResult updateContentScale( OdTvDbMLeaderObjectContextData* );
  bool setTextAngleType(const OdTvDbObject* pObj, OdTvDbMLeaderStyle::TextAngleType textAngleType);
  void setTextAlignmentType(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pCurContext, 
                            OdTvDbMLeaderStyle::TextAlignmentType textAlignmentType);

  bool CheckGsMarker( const OdTvDbObject* pObj, OdGsMarker gsMark );
  OdResult DeleteSubentPath( OdTvDbObject* pObj,  const OdTvDbFullSubentPathArray& paths );
  OdTvDbEntityPtr subentPtr( const OdTvDbObject* pObj, const OdTvDbFullSubentPath& path );

  void draw( const OdTvDbObject* pObj, OdGiCommonDraw* pWD, OdGiGeometry& geom );

  OdTvDbBlockReferencePtr createBlockReference(OdTvDbMLeaderAnnotContextImpl* pCurContext, OdTvDbMLeaderStyle* pMLeaderStyle);

  OdResult transformBy( const OdTvDbObject* pObj, const OdGeMatrix3d& xform );

  void setDoglegLength(const OdTvDbObject* pObj, int leaderIndex, double doglegLength );

  void resetStyle(const OdTvDbObject* pObj, bool isInternalCall = false, 
                  OdTvDbObjectId prevStyleId = OdTvDbObjectId::kNull); // bool bAdjustTextLocation = false); 
  void applyMLEADERSCALE(const OdTvDbObject* pObj, OdTvDbDatabase* pDb);

  void labelsFromBlock(OdTvDbObjectId blockId);
  bool isAnnotative() const
  { 
    return m_bIsAnnotative;
  }
  
  void recompute();
  bool recompute(OdTvDbMLeaderAnnotContextImpl* pCurContext, OdUInt32 flags = kRecomp_All); // return true if switched

  OdGeExtents3d getBlockExtents(OdTvDbMLeaderAnnotContextImpl* pCurContext);

  void getAttachmentPoints(OdTvDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d& p1, OdGePoint3d& p2);
  void drawUnderlines(const OdTvDbObject* pObj, OdGiGeometry& pGeom, OdGiCommonDraw* pWD, OdTvDbMText* mText, OdTvDbMLeaderAnnotContextImpl* pContextData, MLContent_Text* pTextContent, OdTvDbMLeaderStyle* pMLeaderStyle);
  bool getContentCenter(OdTvDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d& center);
  OdGeVector3d getContentDirection(OdTvDbMLeaderAnnotContextImpl* pCurContext);
  OdGeVector3d getActiveConnectionPoint(OdTvDbMLeaderAnnotContextImpl* pCtx, OdGePoint3d& cp);
  void moveContentAtAttachmentPoint(const OdTvDbObject* pObj, OdTvDbMLeaderAnnotContextImpl* pCurContext, const OdGePoint3d& point, const OdGeVector3d& direction, ML_LeaderRoot* pRoot = NULL);
  void adjustTextLocationForUnknownReason(OdTvDbMLeaderAnnotContextImpl* pCtx);
  void updateLabels();
  friend class OdTvDbMLeader;
  friend class OdTvDbMLeaderObjectContextData;
  friend struct OdTvDbMLeaderBreaks;
  friend class OdTvDbMLeaderAnnotContextImpl;
  friend OdUInt32 OdTvDbMLeader_setRecomputeFlags(OdTvDbMLeader* pMLeader, OdUInt32 flags);
};

#endif  // _ODDBMLEADERIMPL_INCLUDED_


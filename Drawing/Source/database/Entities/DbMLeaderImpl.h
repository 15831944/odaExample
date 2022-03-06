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
#include "DbMLeaderObjectContextDataImpl.h"

class OdDbMLeaderImpl;

struct ML_Label
{
  OdDbObjectId        m_AttribDefId;
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
  OdDbObjectId      m_TextStyleId;
  OdGeVector3d      m_vDirection;
  double            m_BoundaryWidth;
  double            m_BoundaryHeight;
  double            m_LineSpacingFactor;
  OdUInt16          m_LineSpacingStyle;
  OdInt16           m_TextAngle;
  OdCmColor         m_TextColor;
  OdUInt16          m_AlignmentType;
  OdUInt16          m_FlowDirection;

  bool              m_TextFrameEnabled;

  OdCmColor         m_BGFillColor;
  double            m_BGScaleFactor;
  OdCmTransparency  m_BGTransparency;
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
  OdDbObjectId      m_BlockId;
  OdGeScale3d       m_Scale;
  OdCmColor         m_BlockColor;
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
  OdDbObjectId  m_ArrowHeadId;

  ML_ArrowHeadPool(): m_isDefault(0){};
};
typedef OdArray<ML_ArrowHeadPool> CArrowHeadPool;

class OdDbMLeaderImpl : public OdDbEntityImpl
{
public:
  static OdDbMLeaderImpl* getImpl(const OdDbMLeader *pObj)
  { return (OdDbMLeaderImpl*)OdDbSystemInternals::getImpl(pObj);}

  OdDbMLeaderAnnotContextImpl m_content;

  CLabelArray       m_Labels;
  CArrowHeadPool    m_ArrowHeadPool;
  OdUInt16          m_StyleContentType;
  OdUInt32          m_OverrideFlags;
  OdDbObjectId      m_LeaderStyleId;
  OdInt16           m_LeaderLineType;
  OdCmColor         m_LeaderColor;

  OdDbObjectId      m_LeaderLineTypeId;
  OdInt32           m_LeaderLineWeight;
  bool              m_bDoglegEnabled;
  bool              m_bHorisontalLanding;
  bool              m_bLandingEnabled;
  double            m_dLandingDistance;

  OdDbObjectId      m_ArrowHeadId;
  double            m_dArrowHeadSize_default;

  OdDbObjectId      m_StyleTextStyleId;
  OdUInt16          m_StyleTextAngle;
  OdUInt16          m_StyleTextAlignmentType; // m_UnkUInt16
  OdCmColor         m_StyleTextColor;
  bool              m_StyleTextFrameEnabled;
  OdDbObjectId      m_StyleBlockId;
  OdCmColor         m_StyleBlockColor;
  OdGeScale3d       m_StyleBlockScale;
  double            m_dBlockRotation;

  bool              m_TextDirectionNegative;
  double            m_StyleBlockRotation;
  OdUInt16          m_StyleAttachmentType; // TODO // OdDbMLeaderStyle::BlockConnectionType m_StyleBlockConnectionType;
  OdUInt16          m_IPEAlign;
  //OdUInt32        m_UnknownUInt32;

  OdDbObjectId      m_DefaultLeaderStyleId;

  bool              m_bIsAnnotative; // TODO bool m_bEnableAnnotationScale;
  bool              m_bCheckForAcadAnnoBug;
  OdUInt16          m_Justification;

  double            m_Scale;

  OdInt16           m_AttachmentDirection;  // OdDbMLeaderStyle::TextAttachmentDirection

  bool              m_bExtendLeaderToText;

  enum RecomputeFlags {
    kRecomp_All = 0, 
    // TODO kRecomp_None = 0, kRecomp_All = (| of all flags except kRecompSkip_...)
    //kRecomp_.. 
    kRecomp_IsDragging = 1,
    kRecompSkip_AutoSwitchDogleg = 2,    // 1 << 1
    kRecomp_AutoSwitchedIfSkip = 4,      // 1 << 2  // used if kRecompSkip_AutoSwitchDogleg is on only
    kRecomp_AcadUcsSetTextDoglegBug = 8, // 1 << 3
    kRecomp_AcadUcsSetVertexBug = 16,    // 1 << 4
    //kRecomp_.. 
    kRecompSkip_All = 0x1000,   // for tests only
    kSkipAcadRenderBug = 0x2000 // for tests only
  };
  OdUInt32          m_RecomputeFlags; // this runtime flags will be cleared by next recompute // CORE-10758

  bool m_bSetMTextInvoked;

  static OdInt16    m_version;

  //OdArray<OdDbMLeaderAnnotContextImpl> m_annotContexts;

  OdDbMLeaderImpl();
  ~OdDbMLeaderImpl();

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format,
                                      OdDb::DwgVersion version);
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format,
                                    OdDb::DwgVersion version);
  //virtual void copyFromContextData(OdDbObject *pObj, OdDbObjectContextData* pData, OdDbObjectContextData* pDataDef); // CORE-13795

  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler, OdDbMLeaderAnnotContextImpl* content = NULL);
  virtual void dxfOutFields(OdDbDxfFiler* pFiler, OdDbMLeaderAnnotContextImpl* content = NULL) const;
  virtual void audit(OdDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;

  void decomposeToR21(OdDbMLeaderAnnotContextImpl* pContext);
  void composeFromR21(OdDbMLeaderAnnotContextImpl* pContext, OdUInt16 prevLeftAttach, OdUInt16 prevRightAttach);

  /*Services*/

  OdDbMLeaderAnnotContextImpl* getContextData( const OdDbObject* obj, const OdDbObjectContextData* in_Ctx );
  OdDbMLeaderAnnotContextImpl* getCurContextData0( const OdDbObject* obj, OdGiCommonDraw* pWd = NULL );
  OdDbMLeaderAnnotContextImpl* getCurContextData( const OdDbObject* obj, OdGiCommonDraw* pWd = NULL );

  const CMLContent* getContent(OdDbMLeaderStyle::ContentType inContentType)
  {
    return m_content.getContent(inContentType);
  }
  CMLContent* getContent() const 
  { 
    return m_content.getContent(); 
  }

  void setContentType(const OdDbObject* pObj, OdDbMLeaderStyle::ContentType contentType);

  void drawArrowHead( 
      const OdDbMLeaderAnnotContextImpl* pCurContext,
      OdGiGeometry* inGeometry,
      OdGiSubEntityTraits* inTraits,
      OdGiContext* inContext,
      OdGiRegenType regenType,
      const double& dSize, 
      OdGePoint3dArray& Points,
      const int inLeaderIndex );

  void getLeaderGeomExtents( 
    const OdDbMLeaderAnnotContextImpl* pCurContext,
    OdGeExtents3d& out_extents, bool bIncludeArrowHeads = false );

  void getArrowHeadGeomExtents(
      const OdDbMLeaderAnnotContextImpl* pCurContext,
      const OdGePoint3dArray& Points,
      const int inLeaderIndex,
      OdGeExtents3d& out_extents );

  bool drawForExtents( 
    const OdDbMLeaderAnnotContextImpl* pCurContext,
    OdGiWorldDraw* pWd );

  void setOverride( 
    OdUInt32 propertyType,
    bool isOverride );

  bool isOverride( OdUInt32 propertyType );

  OdDbMLeaderStylePtr MLeaderStyleForMLeaderOverrides(const OdDbObject* pObj);

  void setPlane(
    OdDbMLeaderAnnotContextImpl* pCurContext,
    const OdGePlane& plane);

  CLeaderRootArray::iterator addLeader(
    OdDbMLeaderAnnotContextImpl* pCurContext,
    int& lederIndex );
  
  void fixLeaderLines(CLeaderArray &toLeftTop, OdDbMLeaderAnnotContextImpl* pCurContext, const OdGeVector3d& vDirection);
  
  void removeLeader(
    OdDbMLeaderAnnotContextImpl* pCurContext,
    int leaderIndex );

  void connectionPoint(
    OdDbMLeaderAnnotContextImpl* pCurContext,
    const OdGeVector3d& vect,
    OdGePoint3d& point );

  void getLeaderIndexes(
    const OdDbMLeaderAnnotContextImpl* pCurContext,
    OdIntArray& leaderIndexes);

  void getLeaderLineIndexes(
    const OdDbMLeaderAnnotContextImpl* pCurContext,
    OdIntArray& leaderLineIndexes );

  void getLeaderLineIndexes(
    const OdDbMLeaderAnnotContextImpl* pCurContext,
    int leaderIndex,
    OdIntArray& leaderLineIndexes );
  void getLeaderLineArrayPtr(
    OdDbMLeaderAnnotContextImpl* pCurContext,
    OdArray<struct ML_Leader *>& leaderPtrArray );

  ML_Leader* getLeaderLineForComposeForLoad(OdDbMLeaderAnnotContextImpl* pCurContext, int lineIndex);

  void setTextLocation(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d location);
  void setBlockLocation(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d location, bool bAdjustConnectionPoint = false);

  OdResult addLeaderLine(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext,
                         const OdGePoint3d& inPoint, int& leaderLineIndex);

  OdResult getLastVertex(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext,
                         CLeaderRootArray::iterator& root, CLeaderArray::iterator& line,
                         OdGePoint3d& point) const;
  OdResult setLastVertex(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext,
                         CLeaderRootArray::iterator& root, CLeaderArray::iterator& line, 
                         const OdGePoint3d& point);
  static int numVertices(OdDbMLeaderAnnotContextImpl* pCurContext, CLeaderRootArray::iterator& root, CLeaderArray::iterator& line);

  OdDbMTextPtr mtext(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext, 
                     bool addUnderline = true);
  OdDbMTextPtr mtext(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext,
                     MLContent_Text* pTextContent, bool addUnderline = true);
  void setMText(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pContext, 
                const OdDbMText* pMText, OdDbMLeaderAnnotContextImpl* pCurContext = NULL);
  
  void adjustContextToKeepConnectionPoint(const OdDbObject* pObj, const OdDbObjectContext& ctx);
  void adjustContextToKeepConnectionPoint(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pContext);
  void adjustContextToKeepConnectionPoint(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pContext,
                                          MLContent_Text* pTextContent, CLeaderRootArray::iterator& pRoot,
                                          const OdGeVector3d& vShiftOffset);

  OdResult updateContentScale( OdDbMLeaderObjectContextData* );
  bool setTextAngleType(const OdDbObject* pObj, OdDbMLeaderStyle::TextAngleType textAngleType);
  void setTextAlignmentType(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext, 
                            OdDbMLeaderStyle::TextAlignmentType textAlignmentType);

  bool CheckGsMarker( const OdDbObject* pObj, OdGsMarker gsMark );
  OdResult DeleteSubentPath( OdDbObject* pObj,  const OdDbFullSubentPathArray& paths );
  OdDbEntityPtr subentPtr( const OdDbObject* pObj, const OdDbFullSubentPath& path );

  void draw( const OdDbObject* pObj, OdGiCommonDraw* pWD, OdGiGeometry& geom );

  OdDbBlockReferencePtr createBlockReference(OdDbMLeaderAnnotContextImpl* pCurContext, OdDbMLeaderStyle* pMLeaderStyle);

  OdResult transformBy(const OdDbObject* pObj, const OdGeMatrix3d& xform, bool bIgnoreMirrText);

  void setDoglegLength(const OdDbObject* pObj, int leaderIndex, double doglegLength );

  void resetStyle(const OdDbObject* pObj, bool isInternalCall = false, 
                  OdDbObjectId prevStyleId = OdDbObjectId::kNull); // bool bAdjustTextLocation = false); 
  void applyMLEADERSCALE(const OdDbObject* pObj, OdDbDatabase* pDb);

  void labelsFromBlock(OdDbObjectId blockId);
  bool isAnnotative() const
  { 
    return m_bIsAnnotative;
  }
  
  void recompute(const OdDbObject* pObj);
  bool recompute(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext, OdUInt32 flags = kRecomp_All); // return true if switched

  OdGeExtents3d getBlockExtents(OdDbMLeaderAnnotContextImpl* pCurContext);

  void getAttachmentPoints(OdDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d& p1, OdGePoint3d& p2);
  void drawUnderlines(const OdDbObject* pObj, OdGiGeometry& pGeom, OdGiCommonDraw* pWD, OdDbMText* mText, OdDbMLeaderAnnotContextImpl* pContextData, MLContent_Text* pTextContent, OdDbMLeaderStyle* pMLeaderStyle);
  bool getContentCenter(OdDbMLeaderAnnotContextImpl* pCurContext, OdGePoint3d& center);
  OdGeVector3d getContentDirection(OdDbMLeaderAnnotContextImpl* pCurContext);
  OdGeVector3d getActiveConnectionPoint(OdDbMLeaderAnnotContextImpl* pCtx, OdGePoint3d& cp);
  void moveContentAtAttachmentPoint(const OdDbObject* pObj, OdDbMLeaderAnnotContextImpl* pCurContext, const OdGePoint3d& point, const OdGeVector3d& direction, ML_LeaderRoot* pRoot = NULL);
  void adjustTextLocationForUnknownReason(OdDbMLeaderAnnotContextImpl* pCtx);
  void updateLabels();
  friend class OdDbMLeader;
  friend class OdDbMLeaderObjectContextData;
  friend struct OdDbMLeaderBreaks;
  friend class OdDbMLeaderAnnotContextImpl;
  friend OdUInt32 OdDbMLeader_setRecomputeFlags(OdDbMLeader* pMLeader, OdUInt32 flags);
};

#endif  // _ODDBMLEADERIMPL_INCLUDED_


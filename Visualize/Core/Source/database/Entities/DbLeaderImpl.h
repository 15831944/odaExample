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

#ifndef _ODDBLEADERIMPL_INCLUDED_
#define _ODDBLEADERIMPL_INCLUDED_

#include "DbCurveImpl.h"
#include "DimStyleRef.h"
#include "DbSystemInternals.h"
#include "DbLeader.h"
#include "DbObjectContextDataImpl.h"
#include "DbObjectContextDataManager.h"

class OdTvDbLeaderImpl : public DimStyleRef<OdTvDbCurveImpl>
{
  static OdTvDbLeaderImpl* getImpl(const OdTvDbLeader *pObj)
  { return (OdTvDbLeaderImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  double              m_dAnnoHeight;
  double              m_dAnnoWidth;
//  OdGePoint3dArray    m_Points;                 // << Annot Scale dependent
  OdInt16             m_ColorForByBlock;
//  OdGeVector3d        m_TextOffset;             // << Annot Scale dependent
//  OdGeVector3d        m_OffsetToBlkInsPt;       // << Annot Scale dependent
  OdTvDbHardPointerId   m_AnnoId;
  virtual void copyFromContextData(OdTvDbObject*, OdTvDbObjectContextData* pData, OdTvDbObjectContextData* );

  const OdGeVector3d& normal() const { return m_vNormal;}
//  const OdGeVector3d& xDir() const   { return m_vXDir;}
  void getPlane(OdGePlane& plane) const
  { plane.set(m_ptOrigin, m_vNormal); }
  void setPlane(
      OdTvDbLeaderObjectContextDataImpl* pContext,
      const OdGePlane& plane);

  OdResult evaluateLeader(
      OdTvDbLeaderObjectContextDataImpl* pContext,
      const OdTvDbObject* annoObj,
      OdTvDbLeader* leader );

private:
  OdGePoint3d         m_ptOrigin;
//  OdGeVector3d        m_vXDir;                  // << Annot Scale dependent
  OdGeVector3d        m_vNormal;

  OdUInt8             m_AnnoType;
  bool                m_bSplinePath;
  bool                m_ArrowheadOn;
//  bool                m_HooklineOnXDir;         // << Annot Scale dependent
  bool                m_HasHookLine;

  OdTvDbLeaderObjectContextDataImpl m_defaultContext; // makes us to have default context even if the entity is not annotative

public:
  OdTvDbLeaderImpl();

  OdTvDbLeader::AnnoType annoType() const {return OdTvDbLeader::AnnoType(m_AnnoType);}
  void setAnnoType(OdTvDbLeader::AnnoType v)   {m_AnnoType = (OdUInt8)v;}

  bool hasSplinePath() const  {return m_bSplinePath;}
  void setSplinePath(bool v)  {m_bSplinePath = v;}

  bool hasArrowhead() const   {return m_ArrowheadOn;}
  void setArrowhead(bool v)   {m_ArrowheadOn = v;}

//  bool isHookLineOnXDir() const {return m_HooklineOnXDir;}
//  void setHookLineOnXDir(bool v) {m_HooklineOnXDir = v;}

  bool hasHookLine() const {return m_HasHookLine;}
  void setHookLine(bool v) {m_HasHookLine = v;}

  virtual void composeForLoad  (OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void audit(OdTvDbAuditInfo* pAuditInfo);
  void updateHookLine(
      OdTvDbLeaderObjectContextDataImpl* pContext );

  OdGePoint3d lastVertex(
      const OdTvDbLeaderObjectContextDataImpl* pContext ) const;
  OdGePoint3d vertexAt(
      const OdTvDbLeaderObjectContextDataImpl* pContext, 
      int nIndex) const;
  void removeLastVertex(
      OdTvDbLeaderObjectContextDataImpl* pContext );
  void setAnnotation(
      OdTvDbLeaderObjectContextDataImpl* pContext,
      OdTvDbObjectId annoId);

private:
  OdTvDbLeaderObjectContextDataImpl* getCurContextData(const OdTvDbObject* pObj);
  OdTvDbLeaderObjectContextDataImpl* getCurContextData(const OdTvDbObject* pObj, OdGiCommonDraw* pWd, double& scale, bool& bSupportsCurrentScale);
  void draw(const OdTvDbObject* pObj, OdGiCommonDraw* pWd, OdGiGeometry& geom);

  static double getDimSize( const OdTvDbDimStyleTableRecord& dimStData );
  void updatePointArrayForHook( 
    OdGiCommonDraw* pWd,
      OdTvDbLeaderObjectContextDataImpl* pContext,
      const OdTvDbDimStyleTableRecord& dimStData, 
      const double& dSize, 
      OdGePoint3dArray& Points, 
      bool bSupportsCurrentScale) const;
  OdTvCmColor setLeaderColor( 
      const OdTvDbDimStyleTableRecord& dimStData, 
      OdGiSubEntityTraits& inTraits ) const;
  OdDb::LineWeight setLeaderLineWidht(
      const OdTvDbDimStyleTableRecord& dimStData, 
      OdGiSubEntityTraits& inTraits)const;

  void drawArrowHead( 
    OdGiGeometry& geom,
    OdGiSubEntityTraits& traits,
    OdGiContext* inContext,
    const OdTvDbDimStyleTableRecord& dimStData, 
    const double& dSize, 
    const OdTvCmColor& color, 
    const OdGePoint3dArray& Points ) const;
  void adjustStartPointByArrow( const OdTvDbDimStyleTableRecord& dimStData,const double& dSize, OdGePoint3dArray& Points )const;
  void getExtents( 
      const OdTvDbLeaderObjectContextDataImpl* pContext,
      OdGeExtents3d& extents ) const;
  bool drawForExtents( 
    const OdTvDbLeaderObjectContextDataImpl* pContext,
    OdGiWorldDraw* pWD ) const;
  static bool excludeDuplicatePoints( OdGePoint3dArray& Points );
  bool createNurbs(
      OdTvDbLeaderObjectContextDataImpl* pContext,
      OdGePoint3dArray& Points, 
      OdGeNurbCurve3d& NurbCurve ) const;
  void drawMTextBox(
      OdTvDbLeaderObjectContextDataImpl* pContext,
      OdGiGeometry& geom,
      const OdTvDbDimStyleTableRecord& dimStData ) const;
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  friend class OdTvDbLeader;
  friend class OdTvDbLeaderWatcherPE;
  friend class OdTvDbLeaderObjectContextData;
  friend DBENT_EXPORT void odDbSetLeaderAnnoType(OdTvDbLeader& leader, int/*OdTvDbLeader::AnnoType*/ val);
  friend DBENT_EXPORT void odDbSetLeaderHookLine(OdTvDbLeader&, bool hasHookline);
};

#endif // _ODDBLEADERIMPL_INCLUDED_

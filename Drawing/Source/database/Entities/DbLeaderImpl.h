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

class OdDbLeaderImpl : public DimStyleRef<OdDbCurveImpl>
{
  static OdDbLeaderImpl* getImpl(const OdDbLeader *pObj)
  { return (OdDbLeaderImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  double              m_dAnnoHeight;
  double              m_dAnnoWidth;
//  OdGePoint3dArray    m_Points;                 // << Annot Scale dependent
  OdInt16             m_ColorForByBlock;
//  OdGeVector3d        m_TextOffset;             // << Annot Scale dependent
//  OdGeVector3d        m_OffsetToBlkInsPt;       // << Annot Scale dependent
  OdDbHardPointerId   m_AnnoId;
  virtual void copyFromContextData(OdDbObject*, OdDbObjectContextData* pData, OdDbObjectContextData* );

  const OdGeVector3d& normal() const { return m_vNormal;}
//  const OdGeVector3d& xDir() const   { return m_vXDir;}
  void getPlane(OdGePlane& plane) const
  { plane.set(m_ptOrigin, m_vNormal); }
  void setPlane(
      OdDbLeaderObjectContextDataImpl* pContext,
      const OdGePlane& plane);

  OdResult evaluateLeader(
      OdDbLeaderObjectContextDataImpl* pContext,
      const OdDbObject* annoObj,
      OdDbLeader* leader );

private:
  OdGePoint3d         m_ptOrigin;
//  OdGeVector3d        m_vXDir;                  // << Annot Scale dependent
  OdGeVector3d        m_vNormal;

  OdUInt8             m_AnnoType;
  bool                m_bSplinePath;
  bool                m_ArrowheadOn;
//  bool                m_HooklineOnXDir;         // << Annot Scale dependent
  bool                m_HasHookLine;

  OdDbLeaderObjectContextDataImpl m_defaultContext; // makes us to have default context even if the entity is not annotative

public:
  OdDbLeaderImpl();

  OdDbLeader::AnnoType annoType() const {return OdDbLeader::AnnoType(m_AnnoType);}
  void setAnnoType(OdDbLeader::AnnoType v)   {m_AnnoType = (OdUInt8)v;}

  bool hasSplinePath() const  {return m_bSplinePath;}
  void setSplinePath(bool v)  {m_bSplinePath = v;}

  bool hasArrowhead() const   {return m_ArrowheadOn;}
  void setArrowhead(bool v)   {m_ArrowheadOn = v;}

//  bool isHookLineOnXDir() const {return m_HooklineOnXDir;}
//  void setHookLineOnXDir(bool v) {m_HooklineOnXDir = v;}

  bool hasHookLine() const {return m_HasHookLine;}
  void setHookLine(bool v) {m_HasHookLine = v;}

  virtual void composeForLoad  (OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void audit(OdDbAuditInfo* pAuditInfo);
  void updateHookLine(
      OdDbLeaderObjectContextDataImpl* pContext );

  OdGePoint3d lastVertex(
      const OdDbLeaderObjectContextDataImpl* pContext ) const;
  OdGePoint3d vertexAt(
      const OdDbLeaderObjectContextDataImpl* pContext, 
      int nIndex) const;
  void removeLastVertex(
      OdDbLeaderObjectContextDataImpl* pContext );
  void setAnnotation(
      OdDbLeaderObjectContextDataImpl* pContext,
      OdDbObjectId annoId);

private:
  OdDbLeaderObjectContextDataImpl* getCurContextData(const OdDbObject* pObj);
  OdDbLeaderObjectContextDataImpl* getCurContextData(const OdDbObject* pObj, OdGiCommonDraw* pWd, double& scale, bool& bSupportsCurrentScale);
  void draw(const OdDbObject* pObj, OdGiCommonDraw* pWd, OdGiGeometry& geom);

  static double getDimSize( const OdDbDimStyleTableRecord& dimStData );
  void updatePointArrayForHook( 
    OdGiCommonDraw* pWd,
      OdDbLeaderObjectContextDataImpl* pContext,
      const OdDbDimStyleTableRecord& dimStData, 
      const double& dSize, 
      OdGePoint3dArray& Points, 
      bool bSupportsCurrentScale) const;
  OdCmColor setLeaderColor( 
      const OdDbDimStyleTableRecord& dimStData, 
      OdGiSubEntityTraits& inTraits ) const;
  OdDb::LineWeight setLeaderLineWidht(
      const OdDbDimStyleTableRecord& dimStData, 
      OdGiSubEntityTraits& inTraits)const;

  void drawArrowHead( 
    OdGiGeometry& geom,
    OdGiSubEntityTraits& traits,
    OdGiContext* inContext,
    const OdDbDimStyleTableRecord& dimStData, 
    const double& dSize, 
    const OdCmColor& color, 
    const OdGePoint3dArray& Points ) const;
  void adjustStartPointByArrow( const OdDbDimStyleTableRecord& dimStData,const double& dSize, OdGePoint3dArray& Points )const;
  void getExtents( 
      const OdDbLeaderObjectContextDataImpl* pContext,
      OdGeExtents3d& extents ) const;
  bool drawForExtents( 
    const OdDbLeaderObjectContextDataImpl* pContext,
    OdGiWorldDraw* pWD ) const;
  static bool excludeDuplicatePoints( OdGePoint3dArray& Points );
  bool createNurbs(
      OdDbLeaderObjectContextDataImpl* pContext,
      OdGePoint3dArray& Points, 
      OdGeNurbCurve3d& NurbCurve ) const;
  void drawMTextBox(
      OdDbLeaderObjectContextDataImpl* pContext,
      OdGiGeometry& geom,
      const OdDbDimStyleTableRecord& dimStData ) const;
  OdResult dwgInFields(OdDbDwgFiler* pFiler);

  friend class OdDbLeader;
  friend class OdDbLeaderWatcherPE;
  friend class OdDbLeaderObjectContextData;
  friend DBENT_EXPORT void odDbSetLeaderAnnoType(OdDbLeader& leader, int/*OdDbLeader::AnnoType*/ val);
  friend DBENT_EXPORT void odDbSetLeaderHookLine(OdDbLeader&, bool hasHookline);
};

#endif // _ODDBLEADERIMPL_INCLUDED_

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

#ifndef OD_TV_GEOMCOLLECTOR_H
#define OD_TV_GEOMCOLLECTOR_H

// ODA Visualize Viewer
#include "TvEntity.h"

// ODA Platform
#include "Gi/GiDummyGeometry.h"
#include "Ge/GeCircArc3d.h"
#include "OdPerfTimer.h"

typedef OdStack<OdGeMatrix3d> OdTvMatrix3dStack;

class  OdTvGeomCollector : public OdGiWorldDraw_Dummy
{
public:
  OdTvGeomCollector(bool bWithTiming);
  ~OdTvGeomCollector();

  void setTvEntity(OdTvEntityId entityId);
  void setTvEntity(OdTvGeometryDataId entityId);

  //traints
  void setTrueColor(const OdCmEntityColor& color);

  // transform
  void pushModelTransform(const OdGeMatrix3d& xMat);
  void popModelTransform();

  //geometry
  void polyline(OdInt32 nbPoints, const OdGePoint3d* pVertexList, const OdGeVector3d* pNormal, OdGsMarker lBaseSubEntMarker);
  void nurbs(const OdGeNurbCurve3d& nurbsCurve);
  void circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal);
  void circle(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint);
  void circularArc(const OdGePoint3d& center, double radius, const OdGeVector3d& normal, const OdGeVector3d& startVector, double sweepAngle, OdGiArcType arcType = kOdGiArcSimple);
  void circularArc(const OdGePoint3d& firstPoint, const OdGePoint3d& secondPoint, const OdGePoint3d& thirdPoint, OdGiArcType arcType = kOdGiArcSimple);
  void ellipArc(const OdGeEllipArc3d& ellipArc, const OdGePoint3d* endPointsOverrides = 0, OdGiArcType arcType = kOdGiArcSimple);

  void shell(OdInt32 numVertices, const OdGePoint3d* vertexList, OdInt32 faceListSize, const OdInt32* faceList,
             const OdGiEdgeData* pEdgeData = 0, const OdGiFaceData* pFaceData = 0, const OdGiVertexData* pVertexData = 0);

  void polypoint(OdInt32 numPoints, const OdGePoint3d* pointList, const OdCmEntityColor* pColors, const OdCmTransparency* pTransparency, const OdGeVector3d* pNormals = NULL, const OdGsMarker* pSubEntMarkers = NULL, OdInt32 nPointSize = 0);

  //set/get
  OdTvResult setTargetDisplayMode(OdTvGeometryData::TargetDisplayMode targetMode);
  OdTvGeometryData::TargetDisplayMode getTargetDisplayMode(OdTvResult*rc = NULL) const;

  void setColorForByLayer(const OdCmEntityColor& color);

  double getTotalTime() const;
private:

  void applyTraitsAndTransform(const OdTvGeometryDataId& geomId);
  void getNumberOfShellFacesAndEdges(OdInt32 faceListSize, const OdInt32* faceList, OdInt32& nFace, OdInt32& nEdge) const;
  void fillVisibilities(OdInt32 nVisibilities, OdUInt8* pVisibilities, OdTvVisibilityDefArray& visibilities);
  void fillColors(OdInt32 nColors, OdCmEntityColor* pColors, OdTvColorDefArray& colors);
  OdTvEntityPtr open() const;
private:

  //stgatilov TODO: make entity and subentity IDs interchangeable
  //or simply accept OdTvEntityPtr here
  //for now we have to store sort-of "union" of two unrelated ID-s here =(
  OdTvEntityId                             m_tvEntity;
  OdTvGeometryDataId                       m_tvSubEntity;

  OdTvMatrix3dStack                        m_xModelStack;
  OdCmEntityColor                          m_CurColor;
  OdCmEntityColor                          m_ColorForByLayer;
  OdTvGeometryData::TargetDisplayMode      m_targetDisplayMode;

  OdPerfTimerBase*                         m_timer;
  double                                   m_totalTime;
};


#endif //OD_TV_GEOMCOLLECTOR_H

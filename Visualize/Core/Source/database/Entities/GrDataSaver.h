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

// Routine for save/transformBy proxy graphics

#ifndef _OD_GR_DATA_SAVER_
#define _OD_GR_DATA_SAVER_

#include "FlatFiler.h"
#include "Gi/GiBaseVectorizer.h"
#include "Gi/GiSubEntityTraitsDataSaver.h"
#include "Gi/GiGeometrySimplifier.h"
#include "Gi/GiStack.h"
#include "StaticRxObject.h"
#include "GiContextForDbDatabase.h"

#define odPrimsHaveColors(a)       (a & 0x0001L)
#define odPrimsHaveLayers(a)       (a & 0x0002L)
#define odPrimsHaveLinetypes(a)    (a & 0x0004L)
#define odPrimsHaveMarkers(a)      (a & 0x0020L)
#define odPrimsHaveVisibilities(a) (a & 0x0040L)
#define odPrimsHaveNormals(a)      (a & 0x0080L)
#define odPrimsHaveOrientation(a)  (a & 0x0400L)

enum GrEntType
{
  kGrExtents            = 1,
  kGrCircle             = 2,
  kGrCircle3pt          = 3,
  kGrCircularArc        = 4,
  kGrCircularArc3pt     = 5,
  kGrPolyline           = 6,
  kGrPolygon            = 7,
  kGrMesh               = 8,
  kGrShell              = 9,
  kGrText               = 10,
  kGrText2              = 11,
  kGrXline              = 12,
  kGrRay                = 13,
  kGrSubentColor        = 14,
                      //= 15, ?
  kGrSubentLayer        = 16,
                      //= 17, ?
  kGrSubentLinetype     = 18,
  kGrSubentMarker       = 19,
  kGrSubentFillon       = 20,
                      //= 21, ?
  kGrSubentTruecolor    = 22,
  kGrSubentLnweight     = 23,
  kGrSubentLtscale      = 24,
  kGrSubentThickness    = 25,
  kGrSubentPlstName     = 26,
  kGrPushClip           = 27,
  kGrPopClip            = 28,
  kGrPushModelTransform = 29,
  kGrPushModelTransform2= 30,
  kGrPopModelTransform  = 31,
  kGrPolylineWithNormal = 32,
  kGrLwPolyline         = 33,

  kGrSubentMaterial     = 34,
  kGrSubentMapper       = 35,

  kGrUnicodeText        = 36,
  kGrUnknown            = 37,
  kGrUnicodeText2       = 38,

  kGrPushPositionXform2d= 39,
  kGrPushScaleXform2d   = 40,
  kGrPushOrientXform    = 41,
  kGrBGRA32Image        = 42,
  kGrRowOfDots          = 43,
  kGrEllipArc           = 44,
  //                    = 45, ?
  kGrPushPositionXform3d= 46,
  kGrPushScaleXform3d   = 47,
  kGrPolyPolygon        = 48,
  kGrPolyline2          = 49,
  kGrPolyPolyline       = 50,
  kGrSubentTransparency = 51,

  kGrLast
};

#define evenNum(num) (num+(num&1))
#define alignedStrLength(len) (len+4-(len&3))

void drawEntityBounds(const OdGiDrawable* pDrawable,
                      OdGiWorldDraw* pWd,
                      OdTvDbDatabase* pDb);

class OdTvGrDataSaver : public OdGiBaseVectorizer
                    , public OdTvFlatFiler
                    , public OdTvGiContextForDbDatabase
                    , public OdGiGeometrySimplifier
{
protected:
  ODRX_USING_HEAP_OPERATORS(OdGiBaseVectorizer);

public:
  OdTvGrDataSaver();
  void init(OdStreamBuf* pBuf, OdTvDbDatabase* pDb, OdDb::DwgVersion ver = OdDb::kDHL_CURRENT);
  OdUInt32 numObjects();
  void save(const OdTvDbEntity* pEnt);
  void saveGraphics(const OdTvDbEntity* pEnt);

  //
  // OdGiBaseVectorizer overrides
  //
  OdGiRegenType regenType() const;
  void draw(const OdGiDrawable* pDrawable);
  void setExtents(const OdGePoint3d *pNewExtents);

  void pushModelTransform(const OdGeMatrix3d& xMat);
  void pushModelTransform(const OdGeVector3d& vNormal);
  void popModelTransform();
  void pushClipBoundary(OdGiClipBoundary* pBoundary);
  void pushClipBoundary(OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* pClipInfo);
  void popClipBoundary();
  
  // For drawing various primitives.
  //
  void circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal);

  void circle(const OdGePoint3d&, const OdGePoint3d&, const OdGePoint3d&);
  
  void circularArc(const OdGePoint3d& center,
    double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    double sweepAngle,
    OdGiArcType arcType = kOdGiArcSimple);
  
  void circularArc(const OdGePoint3d& start,
    const OdGePoint3d& point,
    const OdGePoint3d& end,
    OdGiArcType arcType = kOdGiArcSimple);
  
  void polyline(OdInt32 nbPoints,
    const OdGePoint3d* pVertexList,
    const OdGeVector3d* pNormal = 0,
    OdGsMarker lBaseSubEntMarker = -1);
  
  void polygon(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
  
  void pline(const OdGiPolyline& lwBuf, OdUInt32 i, OdUInt32 numSegs);

  void mesh(OdInt32 rows,
    OdInt32 columns,
    const OdGePoint3d* pVertexList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0
    );
  
  void shell(OdInt32 nbVertex,
    const OdGePoint3d* pVertexList,
    OdInt32 faceListSize,
    const OdInt32* pFaceList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0);
  
  void text(const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    double height,
    double width,
    double oblique,
    const OdString& msg);
  
  void text(const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    const OdChar* msg, OdInt32 length, bool raw,
    const OdGiTextStyle* pTextStyle);
  
  void xline(const OdGePoint3d&, const OdGePoint3d&);
  
  void ray(const OdGePoint3d&, const OdGePoint3d&);

  // Set properties of drawn objects.
  //
  void setSelectionMarker(OdGsMarker markerId);
  void onTraitsModified();

  // Write properties of drawn objects.
  //
  void wrColor(OdUInt16 color);
  void wrTrueColor(const OdCmEntityColor& cmColor);
  void wrLayer(OdDbStub* layerId);
  void wrLineType(OdDbStub* linetypeId);
  void wrFillType(OdGiFillType fillType);
  void wrLineWeight(OdDb::LineWeight lw);
  void wrLineTypeScale(double dScale = 1.0);
  void wrThickness(double dThickness);
  void wrPlotStyleName(OdDb::PlotStyleNameType, OdDbStub* = 0);
  void wrMaterial(OdDbStub* materialId);
  void wrMapper(const OdGiMapper* pMapper);

  //
  // OdGiGeometrySimplifier  overrides
  //
  void polylineOut(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
  void polygonOut(OdInt32 numPoints, const OdGePoint3d* vertexList, const OdGeVector3d* pNormal = 0);

  TD_USING(OdGiGeometrySimplifier::polylineOut);
  TD_USING(OdGiGeometrySimplifier::polygonOut);

  OdDb::DwgVersion dwgVersion() { return m_version; }

private:
  OdUInt32 m_numObjects;
  OdDb::DwgVersion m_version;
  // Copy of previous traits data
  OdGiSubEntityTraitsDataSaver m_prevTraitsData;

  void wrText(const char* data, OdInt32 length);
  void wrMatrix3d(const OdGeMatrix3d& matr);
  void wrObjectId(const OdTvDbObjectId& id);
  void wrOdString(const OdString& s);

  void calculateSizeFlags(OdUInt32& edgeFlags, OdUInt32& faceFlags, OdUInt32& vertexFlags, OdUInt32& size, 
    const OdGiEdgeData* pEdgeData, const OdGiFaceData* pFaceData, const OdGiVertexData* pVertexData,
    OdUInt32 nNumEdges, OdUInt32 nNumFaces, OdUInt32 nNumVertices);

  void writeFaceEdgeVertexData(OdUInt32 edgeFlags, OdUInt32 faceFlags, OdUInt32 vertexFlags, 
    const OdGiEdgeData* pEdgeData, const OdGiFaceData* pFaceData, const OdGiVertexData* pVertexData,
    OdUInt32 nNumEdges, OdUInt32 nNumFaces, OdUInt32 nNumVertices);

  //// Note--the "using" clause below causes a strange bus error on HP, so please use
  //// this inline version instead.
  //OdTvDbDatabase* database() const { return OdGiDefaultContext::database(); }
  ////using OdGiDefaultContext::database;
  //OdTvDbDatabase* database() const { return m_pDb; }
  //OdTvDbDatabase* m_pDb;
};

class OdTvGrDataTransformer : public OdStaticRxObject<OdTvGrDataSaver>
{
protected:
  OdGeMatrix3d m_xform;
  
public:
  OdTvGrDataTransformer(){}
  OdTvGrDataTransformer(const OdGeMatrix3d& xform);

  // For drawing various primitives.
  //
  void circle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal);
  
  void circle(const OdGePoint3d&, const OdGePoint3d&, const OdGePoint3d&);
  
  void circularArc(const OdGePoint3d& center,
    double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    double sweepAngle,
    OdGiArcType arcType = kOdGiArcSimple);
  
  void circularArc(const OdGePoint3d& start,
    const OdGePoint3d& point,
    const OdGePoint3d& end,
    OdGiArcType arcType = kOdGiArcSimple);
  
  void polyline(OdInt32 nbPoints,
    const OdGePoint3d* pVertexList,
    const OdGeVector3d* pNormal = 0,
    OdGsMarker lBaseSubEntMarker = -1);
  
  void polygon(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
  
  void pline(const OdGiPolyline& lwBuf, OdUInt32 i, OdUInt32 numSegs);

  void mesh(OdInt32 rows,
    OdInt32 columns,
    const OdGePoint3d* pVertexList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0
    );
  
  void shell(OdInt32 nbVertex,
    const OdGePoint3d* pVertexList,
    OdInt32 faceListSize,
    const OdInt32* pFaceList,
    const OdGiEdgeData* pEdgeData = 0,
    const OdGiFaceData* pFaceData = 0,
    const OdGiVertexData* pVertexData = 0);
  
  void text(const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    double height,
    double width,
    double oblique,
    const OdString& msg);
  
  void text(const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    const OdChar* msg, OdInt32 length, bool raw,
    const OdGiTextStyle* pTextStyle);
  
  void xline(const OdGePoint3d&, const OdGePoint3d&);
  
  void ray(const OdGePoint3d&, const OdGePoint3d&);
  
  /* deferred
  void pushClipBoundary(OdGiClipBoundary* pBoundary);
  void popClipBoundary();
  */
  void setExtents(const OdGePoint3d *pNewExtents);
};

class OdTvGrDataSaverR14 : public OdTvGrDataTransformer 
{
  OdGiStack<OdGeMatrix3d>  m_xModelStack;

public:
  OdTvGrDataSaverR14() : OdTvGrDataTransformer() {}
  OdTvGrDataSaverR14(const OdGeMatrix3d& xform) : OdTvGrDataTransformer(xform) {}

  void pushModelTransform(const OdGeMatrix3d& xMat)
  {
    OdGeMatrix3d* pNew = m_xModelStack.push();
    *pNew = m_xform;
    m_xform.setToProduct(m_xform, xMat);
  }
  void pushModelTransform(const OdGeVector3d& vNormal)
  {
    pushModelTransform(OdGeMatrix3d::planeToWorld(vNormal));
  }
  void popModelTransform()
  {
    m_xform = *m_xModelStack.top();
    m_xModelStack.pop();
  }

};
#endif

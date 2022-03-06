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

// GiDrawObjectForExplode.h: interface for the OdGiDrawObjectForExplode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GIDRAWOBJECTFOREXPLODE_INCLUDED_)
#define _GIDRAWOBJECTFOREXPLODE_INCLUDED_

#include "Gi/GiBaseVectorizer.h"
#include "OdList.h"
#include "StaticRxObject.h"
#include "GiContextForDbDatabase.h"
#include "Gi/GiGeometrySimplifier.h"

class OdDbPolyFaceMesh;
class OdDbEntity;
typedef OdSmartPtr<OdDbEntity> OdDbEntityPtr;

class DBENT_EXPORT OdGiDrawObjectForExplode : public OdGiBaseVectorizer
                               , public OdGiContextForDbDatabase
                               , public OdGiGeometrySimplifier
{
  OdDbObjectId m_pCVport;
public:

  OdGiDrawObjectForExplode();
  virtual OdResult explode(const OdDbEntity* pEnt, OdRxObjectPtrArray& entitySet);
  virtual void worldDrawEntity(const OdDbEntity* pEnt);
  virtual OdDbStub* viewportObjectId() const ODRX_OVERRIDE;
  virtual void setViewportObjectId(OdDbStub*);
  // OdGiBaseVectorizer overrides
  //
  OdGiRegenType regenType() const;
  void setRegenType(OdGiRegenType rT);
  virtual void draw(const OdGiDrawable* pDrawable);

  virtual void polyline(OdInt32 nbPoints,
    const OdGePoint3d* pVertexList,
    const OdGeVector3d* pNormal = NULL,
    OdGsMarker lBaseSubEntMarker = -1);
  virtual void polygon(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
  virtual void pline(const OdGiPolyline& lwBuf, OdUInt32 fromIndex = 0, OdUInt32 numSegs = 0);
  virtual void xline(const OdGePoint3d&,  const OdGePoint3d&);
  virtual void ray(const OdGePoint3d&, const OdGePoint3d&);
  virtual void text(
    const OdGePoint3d& position,
    const OdGeVector3d& normal, 
    const OdGeVector3d& direction,
    double height, 
    double width, 
    double oblique, 
    const OdString& msg);
  // Explodes the text() primitive as a single OdDbMText entity
  virtual void text(
    const OdGePoint3d& position,
    const OdGeVector3d& normal, 
    const OdGeVector3d& direction,
    const OdChar* msg, 
    OdInt32 length, 
    bool raw, 
    const OdGiTextStyle* pTextStyle);

  // OdGiGeometrySimplifier overrides
  //
  virtual void circleProc(
    const OdGePoint3d& center, double radius, const OdGeVector3d& normal, const OdGeVector3d* pExtrusion = 0);

  virtual void circleProc(
    const OdGePoint3d&, const OdGePoint3d&, const OdGePoint3d&, const OdGeVector3d* pExtrusion = 0);

  virtual void circularArcProc(
    const OdGePoint3d& center,
    double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    double sweepAngle,
    OdGiArcType arcType = kOdGiArcSimple, const OdGeVector3d* pExtrusion = 0);

  virtual void circularArcProc(
    const OdGePoint3d& start,
    const OdGePoint3d& point,
    const OdGePoint3d& end,
    OdGiArcType arcType = kOdGiArcSimple, const OdGeVector3d* pExtrusion = 0);

  virtual void meshProc(OdInt32 rows,
                OdInt32 columns,
                const OdGePoint3d* pVertexList,
                const OdGiEdgeData* pEdgeData = NULL,
                const OdGiFaceData* pFaceData = NULL,
                const OdGiVertexData* pVertexData = NULL);

  virtual void shellProc(OdInt32 nbVertex,
          const OdGePoint3d* pVertexList,
          OdInt32 faceListSize,
          const OdInt32* pFaceList,
          const OdGiEdgeData* pEdgeData = NULL,
          const OdGiFaceData* pFaceData = NULL,
          const OdGiVertexData* pVertexData = NULL);

  virtual void polylineOut(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
  virtual void facetOut(const OdInt32* p3Vertices, const OdInt32* pEdgeIndices, const OdGeVector3d* pNormal);

  // Acad does not use clip boundary for explode (CR 3238)
  virtual void pushClipBoundary(OdGiClipBoundary* pBoundary);
  virtual void pushClipBoundary(OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* pClipInfo);
  virtual void popClipBoundary();

  TD_USING(OdGiBaseVectorizer::text);
  TD_USING(OdGiGeometrySimplifier::polylineOut);

  virtual void getEntityArray(OdRxObjectPtrArray& entitySet) const;
protected:
  ODRX_USING_HEAP_OPERATORS(OdGiBaseVectorizer);
  virtual void addEntity(OdDbEntityPtr pEnt, bool needTransform = false);

  virtual void addTransformedCopy(OdDbEntityPtr pEnt);

  virtual OdDbObjectId getStyleForDbText(const OdGiTextStyle& textStyle);
  virtual OdDbObjectId createStyleForDbText(const OdGiTextStyle& textStyle);
  // Explodes the text() primitive as a set of simple OdDbText entities
  // Used for MText explode and saving to R12 format.
  void textToDbText(
    const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    const OdChar* pMsg,
    OdInt32 length,
    bool raw,
    const OdGiTextStyle* pStyle);

  virtual bool isClipping() const;
  OdGiViewport& viewport() const ODRX_OVERRIDE;
  void setViewport(OdGiViewport*);
private:
  OdDbEntityPtr makeCircle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal);
  OdDbEntityPtr makePolyline(OdInt32 nbPoints, const OdGePoint3d* pVertexList, const OdGeVector3d* pNormal);
  OdDbEntityPtr makePolygon(OdInt32 nbPoints, const OdGePoint3d* pVertexList);

  OdList<OdDbObjectPtr> m_entityList;
  const OdGiEdgeData* m_pEdgeData;
  OdDbPolyFaceMesh* m_pPolyFaceMesh;
  OdGiRegenType     m_regenType;
  OdGiViewport*     m_viewport;
  TD_USING(OdGiGeometrySimplifier::triangleOut);

  bool setCurrTraitsTo(OdDbEntity* pEnt);
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeGeometry
// Finds (and  creates if not found) appropriate text styles
// for exploded DbText entries.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeGeometry : public OdGiDrawObjectForExplode
{
protected:
  ODRX_USING_HEAP_OPERATORS(OdGiDrawObjectForExplode);
public:
  // OdGiDrawObjectForExplode overrides
  //
  virtual OdDbObjectId getStyleForDbText(const OdGiTextStyle& textStyle);
  virtual OdDbObjectId getStyleForDbDimension(const OdGiTextStyle& textStyle);

  virtual void draw(const OdGiDrawable* pDrawable);
  virtual void pline(const OdGiPolyline& lwBuf, OdUInt32 fromIndex = 0, OdUInt32 numSegs = 0) ODRX_OVERRIDE;

  // #10543 : explodeGeometry() must take clip boundary into account
  virtual void pushClipBoundary(OdGiClipBoundary* pBoundary);
  virtual void pushClipBoundary(OdGiClipBoundary* pBoundary, OdGiAbstractClipBoundary* pClipInfo);
  virtual void popClipBoundary();
  virtual bool forceSortents() const {return true;}

protected:
  virtual bool isClipping() const;
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeAsR12
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeAsR12 : public OdGiDrawObjectForExplode
{
protected:
  ODRX_USING_HEAP_OPERATORS(OdGiDrawObjectForExplode);
public:
  // OdGiDrawObjectForExplode  overrides
  //
  void worldDrawEntity(const OdDbEntity* pEnt);
  virtual void pline(const OdGiPolyline& lwBuf, OdUInt32 fromIndex = 0, OdUInt32 numSegs = 0);
  virtual void xline(const OdGePoint3d&,  const OdGePoint3d&);
  virtual void ray(const OdGePoint3d&, const OdGePoint3d&);
  virtual void text(
    const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    const OdChar* pMsg,
    OdInt32 length,
    bool raw,
    const OdGiTextStyle* pStyle);
  virtual OdDbObjectId getStyleForDbText(const OdGiTextStyle& textStyle);
  virtual OdDbObjectId createStyleForDbText(const OdGiTextStyle& textStyle);
  void ellipArcProc(const OdGeEllipArc3d& ellipArc,
                                          const OdGePoint3d* endPointsOverrides,
                                          OdGiArcType arcType,
                                          const OdGeVector3d* pExtrusion);
  void nurbsProc(const OdGeNurbCurve3d& nurbs);
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeBlockRefGeometry
//
// Skips OdDbAttributeDefinition entities while exploding.
// Applies BlockReference's traits to exploded entities.
// The effectiveTraits(), affectTraits() of OdGiBaseVectorizer are not used here as:
//   - color book name get lost,
//   - linetype ByBlock is not used (it is processed in OdGsBaseVectorizeView::affect2dTraits).
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeBlockRefGeometry : public OdGiDrawObjectForExplodeGeometry
{
public:
  OdGiDrawObjectForExplodeBlockRefGeometry();

  bool setCurrTraitsTo(OdDbEntity* pEnt);

  // OdGiBaseVectorizer overridden
  //
  OdUInt32 setAttributes(const OdGiDrawable* pDrawable);
  virtual bool layerVisible(OdDbStub* layerId) const;

  // OdGiDrawObjectForExplode overridden
  //
  void addTransformedCopy(OdDbEntityPtr pEnt);
  void draw(const OdGiDrawable* pDrawable);
  virtual void setViewportObjectId(OdDbStub*);
protected:
  virtual bool isClipping() const;
private:
  OdDbObjectId _blockLayerId;
  OdDbObjectId _blockLinetypeId;
  OdDbObjectId _blockMaterialId;
  OdDb::LineWeight _blockLineWeight;
  OdCmColor _blockColor;
  OdDb::Visibility _blockVisibility;

  OdDbObjectId _layerZeroId;
  OdDbObjectId _linetypeByBlockId;
  OdDbObjectId _linetypeByLayerId;
  OdDbObjectId _materialByBlockId;
  OdDbObjectId _materialByLayerId;

  bool _avoidClipping;

  OdDbObjectIdArray m_arrFrozenLayers;
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeDimension
// Skips OdDbPoint entities while exploding.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeDimension : public OdGiDrawObjectForExplodeBlockRefGeometry
{
public:
  // OdGiDrawObjectForExplode overridden
  //
  void draw(const OdGiDrawable* pDrawable);
protected:
  virtual bool isClipping() const;
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeLeader
// Draws nurbs as a OdDbSpline entity.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeLeader : public OdGiDrawObjectForExplode
{
public:
  //void nurbsProc(const OdGeNurbCurve3d& nurbs);
  void nurbs(const OdGeNurbCurve3d& nurbsCurve);
private:
  OdDbEntityPtr makeSpline(const OdGeNurbCurve3d& nurbs);
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeMText
// Uses:
// - OdDbText entity while exploding via 'text with style' primitive,
// - TextStyleId from MText entity.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeMText : public OdGiDrawObjectForExplode
{
public:
  void setTextStyle(const OdDbObjectId& textStyleId)
  {
    m_textStyleId = textStyleId;
  }

  // Overridden
  virtual void text(
    const OdGePoint3d& position,
    const OdGeVector3d& normal,
    const OdGeVector3d& direction,
    const OdChar* pMsg,
    OdInt32 length,
    bool raw,
    const OdGiTextStyle* pStyle);
  virtual OdDbObjectId getStyleForDbText(const OdGiTextStyle& textStyle);
protected:
  OdDbObjectId m_textStyleId;
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeMTextGeometry
// Finds (and  creates if not found) appropriate text styles
// for exploded DbText entries.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeMTextGeometry : public OdGiDrawObjectForExplodeMText
{
public:
  // Overridden
  virtual OdDbObjectId getStyleForDbText(const OdGiTextStyle& textStyle);
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodePolylineGeometry
// Subdivides polylines into set of line segments.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodePolylineGeometry : public OdGiDrawObjectForExplodeGeometry
{
public:
  OdGiDrawObjectForExplodePolylineGeometry();

  virtual void polyline(OdInt32 nbPoints,
    const OdGePoint3d* pVertexList,
    const OdGeVector3d* pNormal = NULL,
    OdGsMarker lBaseSubEntMarker = -1);
  virtual void polygon(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
  virtual void pline(const OdGiPolyline& lwBuf, OdUInt32 fromIndex = 0, OdUInt32 numSegs = 0);
  virtual void shellProc(OdInt32 nbVertex, const OdGePoint3d* pVertexList,
          OdInt32 faceListSize, const OdInt32* pFaceList, const OdGiEdgeData* pEdgeData = NULL,
          const OdGiFaceData* pFaceData = NULL, const OdGiVertexData* pVertexData = NULL);

  virtual void polylineOut(OdInt32 nbPoints, const OdGePoint3d* pVertexList);
protected:
  OdGeMatrix3d getModelToWorldTransform() const;
private:
  void makeLines(OdInt32 nbPoints, const OdGePoint3d* pVertexList, const OdGeVector3d* pNormal, bool bNeedTransform);
  void addLine(const OdGePoint3d &pt0, const OdGePoint3d &pt1, bool bNeedTransform);
  bool m_bPreventTransform;
};

//----------------------------------------------------------
//
// OdGiDrawObjectForExplodeViewportGeometry
// Enables analytic curves clipping for viewport geometry.
//
//----------------------------------------------------------
class OdGiDrawObjectForExplodeViewportGeometry : public OdGiDrawObjectForExplodeBlockRefGeometry
{
public:
  OdGiDrawObjectForExplodeViewportGeometry();

  void ellipArcProc(const OdGeEllipArc3d& ellipArc, const OdGePoint3d* endPointsOverrides, OdGiArcType arcType, const OdGeVector3d* pExtrusion);
};

#endif // !defined(_GIDRAWOBJECTFOREXPLODE_INCLUDED_)

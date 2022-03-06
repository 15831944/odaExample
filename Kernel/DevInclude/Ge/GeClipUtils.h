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

#ifndef __OD_GE_CLIP_UTILS__
#define __OD_GE_CLIP_UTILS__ 

// GeClipUtils - Some useful functions for clipping
#include "GePoint3dArrayArray.h"
#include "GePoint2dArrayArray.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeLineSeg2dArray.h"
#include "Ge/GeMatrix3d.h"
#include "Int32Array.h"

class OdGeVector3d;
class OdGePlane;
class OdGeMatrix3d;

#include "TD_PackPush.h"

namespace OdGeClipUtils
{
  // intersects the structure of simple polygons inPolyPoly with the half-space
  // basePoint + normal * t
  // t >= 0
  // result polygons will be appended to outPolyPoly array
  // return value: true - polygons was clipped, i. e. we DO return not original 
  // polygons
  // false - we returns original polygons (they're whole inside good half-space)
  GE_TOOLKIT_EXPORT bool clipSimplePolyPolygonByHalfSpace(const OdGePoint3dArrayArray& inPolyPoly, 
    OdGePoint3dArrayArray& outPolyPoly, 
    const OdGePoint3d& basePoint, 
    const OdGeVector3d& normal, 
    const OdGeTol& tol);
  
  // same as prev, but in plane
  GE_TOOLKIT_EXPORT bool clipSimplePolyPolygonByHalfPlane(
    const OdGePoint2dArrayArray& inPolyPoly, 
    OdGePoint2dArrayArray& outPolyPoly, 
    const OdGePoint2d& basePoint, 
    const OdGeVector2d& normal, 
    const OdGeTol& tol);

  // intersects the simple polygon inPoly with the half-space
  // basePoint + normal * t
  // t >= 0
  // result polygons will be appended to outPolyPoly array
  // return value: true - polygon was clipped, i. e. we DO return not original 
  // polygon
  // false - we return original polygon (it is whole inside good half-space)
  GE_TOOLKIT_EXPORT bool clipSimplePolygonByHalfSpace(const OdGePoint3dArray& inPoly, 
    OdGePoint3dArrayArray& outPolyPoly,
    const OdGePoint3d& basePoint, 
    const OdGeVector3d& normal, 
    const OdGeTol& tol);
  
  // same with prev, function, but in 2D
  GE_TOOLKIT_EXPORT bool clipSimplePolygonByHalfPlane(const OdGePoint2dArray& inPoly, 
    OdGePoint2dArrayArray& outPolyPoly,
    const OdGePoint2d& basePoint, 
    const OdGeVector2d& normal, 
    const OdGeTol& tol);

  // intersects the convex polygon verts with the half-plane
  // basePoint + normal * t
  // t >= 0
  // inPoly  -- in polygon
  // outPoly -- out polygon
  GE_TOOLKIT_EXPORT void clipConvexPolygonByHalfPlane(const OdGePoint2d* pInPolyPts,
    OdUInt32 nbInPolyPts,
    OdGePoint2dArray& outPoly,
    const OdGePoint2d& basePoint,
    const OdGeVector2d& normal,
    const OdGeTol& tol);

  // intersects the convex polygon verts with the half-space 
  // basePoint + normal * t
  // t >= 0
  // inPoly  -- in polygon
  // outPoly -- out polygon
  GE_TOOLKIT_EXPORT void clipConvexPolygonByHalfSpace(const OdGePoint3dArray& inPoly,
    OdGePoint3dArray& outPoly,
    const OdGePoint3d& basePoint,
    const OdGeVector3d& normal,
    const OdGeTol& tol);
  
  // intersects the line segment [pt1, pt2] with the half-space 
  // borderPlane + normal * t
  // t >= 0
  // return value:
  // true - line segment was clipped (that we return isn't original line segmant)
  // false - we DO return original segment
  GE_TOOLKIT_EXPORT bool clipLineSeg(OdGePoint3d& pt1, 
    OdGePoint3d& pt2, 
    const OdGePoint3d& basePoint, 
    const OdGeVector3d& normal, 
    const OdGeTol& tol);
  
  // Tests if point pt belongs to polygon vertexes
  // return value:
  // 0 - point does NOT belong to polygon
  // 1 - point DOES belong to polygon
  // 2 - point lies on the polygon's border
  GE_TOOLKIT_EXPORT int isPointBelongPoly(const OdGePoint2d& pt, 
    const OdGePoint2d* pPoly, 
    OdUInt32 nbPolyPts,
    const OdGeTol& tol);
  
  // intersects line segment and simple polygon
  // ab              - input line segment
  // ocsClip         - input polygon
  // prismClippedOcs - output array of resulting segments
  // tolerance       - required tolerance
  // return value:
  // true  - if line segment was clipped
  // false - if line segment is whole inside clip boundary.
  GE_TOOLKIT_EXPORT bool clipLineSegByPolygon(const OdGeLineSeg2d& ab,
    const OdGePoint2dArray& ocsClip,
    OdGeLineSeg2dArray& prismClippedOcs,
    const OdGeTol& tolerance);

  // Gets the section of infinite prism by inputPolyPlane.
  // world2Plane is passed as argument to decrease repeated calculations
  // [in]  pPoints, nbPoints defines prism
  // [out] ocsClipPoly -- resulting section
  GE_TOOLKIT_EXPORT void getPrismSection(const OdGePoint2d* pPoints,
    OdUInt32 nbPoints,
    OdGePoint2dArray& ocsClipPoly, 
    const OdGePlane& inputPolyPlane,
    const OdGeMatrix3d& world2Plane);

  // Gets the section of possibly finite prism by inputPolyPlane.
  // world2Plane is passed as argument to decrease repeated calculations
  // [in]  pPoints, nbPoints defines prism
  // [out] ocsClipPoly -- resulting section
  GE_TOOLKIT_EXPORT void getTruncatedPrismSection(const OdGePoint2d* pPoints,
    OdUInt32 nbPoints,
    OdGePoint2dArray& ocsClipPoly, 
    const OdGePlane& inputPolyPlane,
    const OdGeMatrix3d& world2Plane,
    bool bClipLowerZ,
    double dLowerZ,
    bool bClipUpperZ,
    double dUpperZ,
    const OdGeTol& tolerance);

  // Checks is polygon has self-intersections.
  GE_TOOLKIT_EXPORT bool isPolygonSelfItersections(const OdGePoint2d* pPoints, OdUInt32 nbPoints, const OdGeTol& tol = OdGeContext::gTol);
  GE_TOOLKIT_EXPORT bool isPolygonSelfItersections(const OdGePoint3d* pPoints, OdUInt32 nbPoints, const OdGeTol& tol = OdGeContext::gTol);
  // Fixes polygon self-intersections and modifies input points array by intersection points
  GE_TOOLKIT_EXPORT OdUInt32 fixPolygonSelfIntersections(OdGePoint3dArray& pPoints, OdUInt32 nStartId, OdUInt32 nbPoints, const OdGeTol& tol = OdGeContext::gTol, const OdGeVector3d& vrNormal = OdGeVector3d::kZAxis, bool bCalculateNormal = false );
  // Fixes polygon self-intersections and returns result as 2d points array.
  GE_TOOLKIT_EXPORT OdUInt32 fixPolygonSelfIntersections(const OdGePoint2d* pPoints, OdUInt32 nbPoints,
    OdInt32Array &nCounts, OdGePoint2dArray &nPoints);
  // Fixes polygon self-intersections and returns result as transformed 3d points array.
  GE_TOOLKIT_EXPORT OdUInt32 fixPolygonSelfIntersections(const OdGePoint2d* pPoints, OdUInt32 nbPoints,
    OdInt32Array &nCounts, OdGePoint3dArray &nPoints, const OdGeMatrix3d &mtx);
  // Clip closed polyline by simple polygon
  GE_TOOLKIT_EXPORT bool clipClosedPolylineBySimplePolygon(const OdGePoint2d* pPline, OdUInt32 nbPline,
    const OdGePoint2d* pPoly, OdUInt32 nbPoly, OdGePoint2dArray& outPline);
  // intersects line segment and a number of polygons (border and holes)
  GE_TOOLKIT_EXPORT void clipLineSegByFace(const OdGeLineSeg2d& seg, const OdGePoint2dArrayArray& aPtPt, OdGeLineSeg2dArray& aSeg, const OdGeTol& tol);

  // find intersection of edge and triangle
  //[in]: 
  //  pPointsTriangle       - triangle points
  //  ptEdge1               - first point of the edge
  //  ptEdge2               - second point of the edge
  //  tol                   - required tolerance
  //[out]:
  //  outPt                 - found point (valid if [return value] == 1)
  //  lambda                - coeffcient in the parametric line equation for the founded point (shoud be inside[0;1])
  //[optional in]: 
  //  pPlaneNormal          - normal to the plane of the triangle
  //  D                     - 4 coefficient to the plane of the triangle
  //[return value]
  //  0 - edge and triangle doesn't intersect (also can lays in parallel planes) or lays at the same plane
  //  1 - there is one intersection point
  GE_TOOLKIT_EXPORT int getIntersectionOfEdgeAndTriangle3d( const OdGePoint3d* pPointsTriangle, const OdGePoint3d& ptEdge1, const OdGePoint3d& ptEdge2, const OdGeTol& tol,
                                                            OdGePoint3d& outPt, double& lambda, const OdGeVector3d* pPlaneNormal = NULL, double D = 0. );

  // find intersection of two triangles
  //[in]: 
  //  pPointsTriangleA          - first triangle points
  //  pPointsTriangleB          - second triangle points
  //  tol                       - required tolerance
  //[out]:
  //  outPtA                    - first found point (valid if [return value] >= 1)
  //  outPtB                    - second found point (valid if [return value] == 2)
  //[optional in]: 
  //  pPlaneNormalA             - normal to the plane of the triangle A
  //  D_A                       - 4 coefficient to the plane of the triangle A 
  //  pPlaneNormalB             - normal to the plane of the triangle B
  //  D_B                       - 4 coefficient to the plane of the triangle B
  //[return value]
  //  0 - triangles doesn't intersect (also can lays in parallel planes) or lays at the same plane
  //  1 - there is only one intersection point
  //  2 - there are two intersection points
  //  3 - there are two intersection points but these points are the triangle's vertices (means that there is a touching, not intersecting)
  GE_TOOLKIT_EXPORT int getIntersectionOfTriangles3d( const OdGePoint3d* pPointsTriangleA, const OdGePoint3d* pPointsTriangleB, const OdGeTol& tol,
                                                      OdGePoint3d& outPtA, OdGePoint3d& outPtB, const OdGeVector3d* pPlaneNormalA = NULL, double D_A = 0.,
                                                      const OdGeVector3d* pPlaneNormalB = NULL, double D_B = 0. );
  /**\details
  Checks the presence of intersection between two triangles according to the Tomas Moller algorithm (1997).
  \param pPointsTriangleA [in]    First triangle vertices.
  \param pPointsTriangleB [in]    Second triangle vertices.
  \param tol [in]                 Required tolerance.
  \param pPlaneNormalA [in]       Normal to the plane of the triangle A.
  \param D_A [in]                 The fourth coefficient of the triangle's A plane equation.
  \param pPlaneNormalB [in]       Normal to the plane of the triangle B.
  \param D_B [in]                 The fourth coefficient of the triangle's B plane equation.
  \param bComplanar [out]         Whether the triangles are complanar.
  \param pPtIntersect1 [out]      First endpoint of the line of intersection (valid only if bComplanar = false).
  \param pPtIntersect2 [out]      Second endpoint of the line of intersection (valid only if bComplanar = false).
  \param bStrictComplanar [in]    Strict or fast complanar triangles comparison.
  \returns Returns result of comparation: -1 - triangles doesn't inersect, 1 - triangles intersect, 0 - triangles touching, but may be 1 if pPtIntersect1 or pPtIntersect2 are NULL.
  \remarks
  In penetration depth calculation depth between two intersecting coplanar triangles are 0 (in 3D space we always can move one of triangles in normal direction for the infinity small value),
  so we provide fast complanar triangles comparison (without touch detection) and strict complanar triangles comparison (which distinguishes intersection (overlaping) and touching).
  */       
  GE_TOOLKIT_EXPORT int getCollisonOfTriangles3d(const OdGePoint3d* pPointsTriangleA, const OdGePoint3d* pPointsTriangleB,
                                                  const OdGeVector3d* pPlaneNormalA, double D_A, const OdGeVector3d* pPlaneNormalB, double D_B,
                                                  bool& bComplanar, OdGePoint3d* pPtIntersect1 = NULL, OdGePoint3d* pPtIntersect2 = NULL, bool bStrictComplanar = true );

  // check collison of two triangles (a little bit more fast method which did not take into account touching)
  //[in]: 
  //  pPointsTriangleA          - first triangle points
  //  pPointsTriangleB          - second triangle points
  //  tol                       - required tolerance
  //  pPlaneNormalA             - normal to the plane of the triangle A
  //  D_A                       - 4 coefficient to the plane of the triangle A 
  //  pPlaneNormalB             - normal to the plane of the triangle B
  //  D_B                       - 4 coefficient to the plane of the triangle B
  //[return value]
  //  false - triangles doesn't collide
  //  true - triamgles collide
  GE_TOOLKIT_EXPORT bool getCollisonOfTriangles3dEx(const OdGePoint3d* pPointsTriangleA, const OdGePoint3d* pPointsTriangleB, const OdGeTol& tol,
                                                    const OdGeVector3d* pPlaneNormalA, double D_A, const OdGeVector3d* pPlaneNormalB, double D_B);

  // calculates the penetration depth of two triangles in 3D if they intersect
  //[in]: 
  //  pPointsTriangleA          - first triangle vertices
  //  pPointsTriangleB          - second triangle vertices
  //  tol                       - required tolerance
  //  pPlaneNormalA             - normal to the plane of the triangle A
  //  D_A                       - the fourth coefficient of the triangle's A plane equation
  //  pPlaneNormalB             - normal to the plane of the triangle B
  //  D_B                       - the fourth coefficient of the triangle's B plane equation
  //[return value]
  //[return value]
  //  Penetration depth between two triangles. If triangles don't intersect this method returns -1
  //  If the returned value is -2, there is a error in the input data
  GE_TOOLKIT_EXPORT double getPenetrationDepthOfTriangles3d(const OdGePoint3d* pPointsTriangleA, const OdGePoint3d* pPointsTriangleB,
                                                            const OdGeVector3d* pPlaneNormalA, double D_A, const OdGeVector3d* pPlaneNormalB, double D_B);

  // get plane parameters for the triangle
  //[in]: 
  //  pPointsTriangle           - 3 points of the triangle
  //[out]:
  //  planeNormal              - normal to the plane
  //  D                         - d parameter of the palne
  //[return value]
  //  nothing
  GE_TOOLKIT_EXPORT void getPlaneFromTriangle(const OdGePoint3d* pPointsTriangle, OdGeVector3d& planeNormal, double& D);

  // calculates the closest points between two line segments.
  // Implementation based on the paper "On fast computation of distance between line segments" by Vladimir J. Lumelsky, 1985
  //[in]:
  //  originA                   - first point of a line segment A.
  //  vectA                     - vector that defines the line direction and second point of a line segment A.
  //  originB                   - first point of a line segment B.
  //  vectB                     - vector that defines the line direction and second point of a line segment B.
  //[out]:
  //  ptA                       - closest point at a line segment A
  //  ptB                       - closest point at a line segment B
  //  vect                      - direction vector for closest points
  //[return value]
  //  Closest points between two line segments.
  GE_TOOLKIT_EXPORT void getClosestPointsOfLineSegs3d(const OdGePoint3d& originA, const OdGeVector3d& vectA, const OdGePoint3d& originB, const OdGeVector3d& vectB,
                                                     OdGePoint3d& ptA, OdGePoint3d& ptB, OdGeVector3d& vect);


  // calculates the closest points between two triangles, and returns the distance between them.
  //[in]: 
  //  pPointsTriangleA          - first triangle points
  //  pPlaneNormalA             - normal to the plane of the triangle A
  //  pPointsTriangleB          - second triangle points
  //  pPlaneNormalB             - normal to the plane of the triangle B
  //[out]:
  //  ptClosestA (optional)      - closest point from triangle A
  //  ptClosestB (optional)      - closest point from triangle B
  //[return value]
  //  Distance between two triangles.
  //  If the returned value is negative, there is a error in the input data
  //  ptClosestA and ptClosestB will be filled only if the returned value is positive (there is no intersection and input data is correct)
  GE_TOOLKIT_EXPORT double getDistanceOfTriangles3d(const OdGePoint3d* pPointsTriangleA, const OdGeVector3d* pPlaneNormalA,
                                                    const OdGePoint3d* pPointsTriangleB, const OdGeVector3d* pPlaneNormalB,
                                                    OdGePoint3d* ptClosestA = NULL, OdGePoint3d* ptClosestB = NULL);
  /** \details
  Checks shapes collision using GJK and calculates MTV length (penetration depth) using EPA
  \param nPtsA [in] First shape poins count
  \param pPointsA [in] Point of first shape
  \param nPtsB [in] Second shape points count
  \param pPointsB [in] Point of second shape
  \param bRunEPA [in] If true, runs EPA if collision detected. Otherwise only detects collisions without calculating MTV
  \param tolerance [in] Calculation tolerance
  \returns Returns penetration depth (length of MTV) if collision detected or -1.0 if no collision detected
  \remarks
  This method may use only GJK for detecting collision. In this case bRunEPA should be FALSE. Return value: -1.0 - no collisions, 1.0 - collision detected.
  */
  GE_TOOLKIT_EXPORT double getPenetrationDepth_GJK_EPA( OdUInt32 nPtsA, const OdGePoint3d* pPointsA, OdUInt32 nPts2, const OdGePoint3d* pPointsB, bool bRunEPA = true, const OdGeTol& tolerance = OdGeTol() );
} // OdGeClipUtils

#include "TD_PackPop.h"

#endif // __OD_GE_CLIP_UTILS__

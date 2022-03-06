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

#ifndef _DBMPOLYGON_H_INCLUDED_
#define _DBMPOLYGON_H_INCLUDED_

#include "DbHatch.h"


class OdTvDbCircle;
class OdTvDb2dPolyline;
class OdTvDbPolyline;
class OdTvDbMPolygonCrossing;
typedef OdArray<OdTvDbMPolygonCrossing,OdPlainObjectsAllocator<OdTvDbMPolygonCrossing> > OdTvDbMPolygonCrossingArray;
typedef OdArray<OdGePoint2dArray> OdGePoint2dArrayArray;
class OdTvDbMPolygonNode;

const double OdTvDbMPolygonCrossingFuzz = 1E-6;

#ifdef MPOLYGON_EXPORTS
# define MPOLYGON_EXPORT            OD_TOOLKIT_EXPORT
#else
# define MPOLYGON_EXPORT            OD_TOOLKIT_IMPORT
#endif

/** \details
    This class processes one or more closed polygons as a single polygon.
    Corresponding C++ library: AcMPolygonObj15
    
    \sa
    TD_Db
   
    <group OdTvDb_Classes>
*/
class MPOLYGON_EXPORT OdTvDbMPolygon : public OdTvDbEntity {
public:
  OdTvDbMPolygon();
  virtual ~OdTvDbMPolygon();

  ODDB_DECLARE_MEMBERS(OdTvDbMPolygon);

  virtual OdTvDbHatchPtr hatch();
  virtual OdTvDbHatchPtr hatch() const;

  virtual double elevation() const;
  virtual void setElevation(double elevation);

  virtual OdGeVector3d normal() const;
  virtual void setNormal(const OdGeVector3d& normal);

  virtual OdResult evaluateHatch(bool bUnderestimateNumLines = false);

  virtual OdTvDbHatch::HatchPatternType patternType() const;

  virtual OdString patternName() const;

  virtual void setPattern(OdTvDbHatch::HatchPatternType patType,
    const OdString& patName);

  virtual double patternAngle() const;
  virtual void setPatternAngle(double angle);

  virtual double patternSpace() const;
  virtual void setPatternSpace(double space);

  virtual double patternScale() const;
  virtual void setPatternScale(double scale);

  virtual bool patternDouble() const;
  virtual void setPatternDouble(bool isDouble);

  virtual int numPatternDefinitions() const;
  virtual void getPatternDefinitionAt(int index, 
    double& angle,
    double& baseX,
    double& baseY,
    double& offsetX,
    double& offsetY,
    OdGeDoubleArray& dashes)
    const;

  void setGradientAngle(double angle);
  void setGradientShift( float shiftValue );
  void setGradientOneColorMode( bool oneColorMode );
  void setGradientColors( unsigned int count, 
    const OdTvCmColor* colors,
    const double* values );
  void setGradient(OdTvDbHatch::GradientPatternType gradType,
    const OdString& gradName);


  virtual OdTvCmColor patternColor() const;
  virtual void setPatternColor(const OdTvCmColor& pc);

  /** \details
    Returns the area of this entity.

    \param area        [out]   Receives the area.
    \param areaViaHatch [in]   Set true, if need calculate area like a hatch(used before version 20.3).
    \returns
    Returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getArea(double& area, bool areaViaHatch = false) const;

  virtual OdGeVector2d getOffsetVector() const;

  virtual OdResult appendLoopFromBoundary(const OdTvDbCircle* pCircle,
    bool excludeCrossing = true, double tol = OdTvDbMPolygonCrossingFuzz);
  virtual OdResult appendLoopFromBoundary(const OdTvDbPolyline* pPoly,
    bool excludeCrossing = true, double tol = OdTvDbMPolygonCrossingFuzz);
  virtual OdResult appendLoopFromBoundary(const OdTvDb2dPolyline* pPoly,
    bool excludeCrossing = true, double tol = OdTvDbMPolygonCrossingFuzz);

  /** \details
    Returns the number of loops in the closed polygon.
  */
  virtual int numMPolygonLoops() const;

  virtual OdResult getMPolygonLoopAt(int loopIndex, OdGePoint2dArray& vertices,
    OdGeDoubleArray& bulges) const;

  /** \details
    Appends a polygon loop.
    
    \param vertices        [in] An array of vertices.
    \param bulges          [in] An array of bulge values for loops.
    \param excludeCrossing [in] Set true to disable creating a polygon if there are crosses between loops.
    \param tol             [in] Measurement accuracy tolerance.

    \returns eAmbiguousInput if excludeCrossing is true and there are crosses between loops;
      eOk if a polygon appended successfuly.
  */
  virtual OdResult appendMPolygonLoop(const OdGePoint2dArray& vertices,
    const OdGeDoubleArray& bulges, bool excludeCrossing = true,
    double tol = OdTvDbMPolygonCrossingFuzz);

  virtual OdResult insertMPolygonLoopAt(int loopIndex, 
    const OdGePoint2dArray& vertices, const OdGeDoubleArray& bulges, 
    bool excludeCrossing = true, double tol = OdTvDbMPolygonCrossingFuzz);

  virtual OdResult removeMPolygonLoopAt(int loopIndex);

  /** \details
    Declares the loop directions.
  */
  enum loopDir {
    kExterior   = 0,   // Loop direction is counter-clockwise
    kInterior   = 1,   // Loop direction is clockwise
    kAnnotation = 2    // Text
  };

  /** \details
    Gets the direction of the specified loop in the closed polygon.
    Returns eOk if successful, or eInvalidInput if loop index is out of range.

    \param lindex [in]  Loop index as an Ingeter value in the range 0 to numMPolygonLoops()-1.
    \param dir [out]  Reference to a variable in which the loop direction must be saved.
  */
  virtual OdResult getLoopDirection(int lindex, OdTvDbMPolygon::loopDir& dir) const;

  /** \details
    Sets the direction for the specified loop in the closed polygon.
    Returns eOk if successful, or eInvalidInput if loop index is out of range.

    \param lindex [in]  Loop index as an Ingeter value in range 0 to numMPolygonLoops()-1.
    \param dir [in]  Loop direction.
  */
  virtual OdResult setLoopDirection(int lindex, OdTvDbMPolygon::loopDir dir);

  /** \details
    Determines whether the specified point in WCS is on the specified loop of the polygon.

    \param worldPt [in] Point in WCS.
    \param loop    [in] The loop index.
    \param tol     [in] Measurement accuracy tolerance.

    \returns True if the specified point is on the specified loop of the polygon; false otherwise.
  */
  virtual bool isPointOnLoopBoundary(const OdGePoint3d& worldPt, int loop,
    double tol = OdTvDbMPolygonCrossingFuzz) const;
  
  /** \details
    The function projects worldPt to the polygon plane, then if the point is on some boundary, 
    indices of these boundaries are added to the loopsArray and the function returns, 
    otherwise it finds innermost loop containing the point and adds its index to the loopsArray before returning. 
    
    \returns The function returns loopsArray.size().
  */
  virtual int isPointInsideMPolygon(const OdGePoint3d& worldPt, OdGeIntArray& loopsArray,
    double tol = OdTvDbMPolygonCrossingFuzz) const;

  /** \details
  Returns a index of the parent loop, related to the specified loop.

  \param curLoop [in] The specified loop index
  \returns Non-negative index if the loop is found,
  or -1 if the specified loop does not have a parent loop,
  or -2 if the specified loop does not exist,
  or -3 if the specified loop intersects with a possible outer loop
  */
  virtual int getParentLoop(int curLoop) const;

  /** \details
  Creates a nesting tree of nodes. Where the nodes represent the nesting of the loops.

  \param loopNode [out] set pointer to root node of tree
  \returns eOk if creating tree is successful.
  \remarks
    - Return eOk if count loops in OdTvDbMPolygon is zero.
    - To avoid memory leak need use OdTvDbMPolygon::deleteMPolygonTree(loopNode).
    - If loops in OdTvDbMPolygon was changed, need get new tree by OdTvDbMPolygon::getMPolygonTree(loopNode).
  */
  virtual OdResult getMPolygonTree(OdTvDbMPolygonNode*& loopNode) const;

  /** \details
  Recursive delete tree created by OdTvDbMPolygon::getMPolygonTree(OdTvDbMPolygonNode*&)

  \param loopNode [in] pointer to root of tree
  */
  virtual void deleteMPolygonTree(OdTvDbMPolygonNode* loopNode) const;

  /** \details
  Find within pick box the closest loop from OdTvDbMPolygon to input 3d point within pick box.

  \param worldPt [in] 3d point of world coordinate
  \returns index of closest loop.
  \remarks
    - Return -1 if no one loop into pick box
    - Around of point created a pick box. Size of pick box get from system variable PICKBOX.
    - If two loop at the same distance from the point will be returned loop with lower index.
    - If two loop within pick box - return more closest to worldPt
  */
  virtual int getClosestLoopTo(const OdGePoint3d& worldPt) const;

  /** \details
  Perimeter calculation by adding the length of all borders.

  \returns perimeter of the OdTvDbMPolygon.
  \remarks Annotation boundaries not taken into account
  */
  virtual double getPerimeter() const;


  /** \details
  Checks the direction of the loops and changes to the correct one. The directivity check is based on the resulting tree from getMPolygonTree. 
  Where the depth of the tree indicates the direction of the loop (even values are counterclockwise, not even clockwise). 
  If in MPolygon are loops that are not displayed (invalid), they will be marked again as valid (and will be drawn) if they do not intersect with others.
  Also check for intersections of the displayed loops(valid). Intersected loops marks as invalid, and there will be not draw.

  \returns eOk if check and changes is successful, or eInvalidInput if getMPolygonTree not generate tree. 
  */
  virtual OdResult balanceTree();

  /** \details
  Checks if there are loops that are not drawn(invalid). Do not check loops that are draw(valid) for intersection or direction.

  \returns true if all loops are draw, or return false if MPolygon has loops that not draw (invalid).
  \remarks use balanceDisplay/balanceTree to check and mark valid and invalid loops(loops that be draw or not draw).
  */
  virtual bool isBalanced() const;

  /** \details
  Checks loops for intersection and direction. If the cycle is placed at an even level of the tree, and the direction is clockwise, it will be marked as invalid (it will not be displayed).
To change direction to the right, use balanceTree. If the cycle intersects with another cycle, the cycle with a higher index will be marked as invalid (do not draw).
Loops that have been marked as invalid but have the correct direction and no intersections will be marked as valid and will be drawn again.

  \returns eOk if check and changes is successful, or eInvalidInput if getMPolygonTree not generate tree. 
  */
  virtual OdResult balanceDisplay();


  /** \details
  Create loops from entities for empty OdTvDbMPolygon. Every ObjectId must be one closed loop.
    \param ids             [in]  array of entities objects ids.
    \param rejectedObjs    [out] return indices of objectId from array ids that led to errors creating loops
    \param excludeCrossing [in]  Set true to disable creating a polygon if there are crosses between loops.
    \param tol             [in]  Measurement accuracy tolerance.
  \returns eAmbiguousInput if excludeCrossing is true and there are crosses between loops or if OdTvDbMPolygon has loops;
           eInvalidInput if ids array is empty or has rejected objects
           eOk if a polygon appended successfully.
  \note        if there is at least one rejected objectId a loops will not be added.
               OdTvDbMPolygon should not contain loops.
  */
  virtual OdResult createLoopsFromBoundaries(const OdTvDbObjectIdArray &ids,
                                             OdIntArray &rejectedObjs,
                                             bool excludeCrossing = true, double tol = OdTvDbMPolygonCrossingFuzz);

  /** \details
  Create loops from for empty OdTvDbMPolygon.
    \param vertices        [in]  An array of vertices array.
    \param bulges          [in]  An array of bulge value array.
    \param rejectedObjs    [out] return indices of objectId from array ids that led to errors creating loops
    \param excludeCrossing [in]  Set true to disable creating a polygon if there are crosses between loops.
    \param tol             [in]  Measurement accuracy tolerance.
  \returns eAmbiguousInput if excludeCrossing is true and there are crosses between loops or if OdTvDbMPolygon has loops;
           eInvalidInput if ids array is empty or has rejected objects
           eOk if a polygon appended successfully.
  \note        if there is at least one rejected objectId a loops will not be added.
               OdTvDbMPolygon should not contain loops.
  */
  virtual OdResult createLoops(const OdGePoint2dArrayArray &vertices,
                               const OdArray<OdGeDoubleArray> &bulges, OdIntArray &rejectedObjs,
                               bool excludeCrossing = true, double tol = OdTvDbMPolygonCrossingFuzz);

  /* Not implemented


  
  

  
  

  
  

  //virtual OdResult getLoopAtGsMarker(OdGsMarker gsMark, int &loop) const;
  virtual void getChildLoops(int curLoop, OdGeIntArray& selectedLoopIndexes) const;
  
  

  // Mpolyon loop crossing and inside methods.
  //

  virtual OdResult loopCrossesItself(bool& crosses, bool findAll,
    OdTvDbMPolygonCrossingArray& crossingsArray,
    const OdGePoint2dArray& vertexPts, 
    const OdGeDoubleArray& vertexBulges, 
    double tol = OdTvDbMPolygonCrossingFuzz) const;

  virtual bool loopCrossesItself(const OdGePoint2dArray& vertexPts, 
    const OdGeDoubleArray& vertexBulges, 
    double tol = OdTvDbMPolygonCrossingFuzz) const;

  virtual OdResult loopCrossesMPolygon(bool& crosses, bool findAll,
    OdTvDbMPolygonCrossingArray& crossingsArray,
    const OdGePoint2dArray& testVertexPts, 
    const OdGeDoubleArray& testVertexBulges, 
    double tol = OdTvDbMPolygonCrossingFuzz) const;

  virtual bool selfCrosses(const OdGePoint2dArray& vertexPts, 
    const OdGeDoubleArray& vertexBulges,
    double tol = OdTvDbMPolygonCrossingFuzz) const;

  virtual bool includesTouchingLoops(double tol = OdTvDbMPolygonCrossingFuzz) const;

  //virtual OdResult subGetClassID(void* pClsid) const;

  virtual OdResult   intersectWith(
    const OdTvDbEntity*   ent,
    OdDb::Intersect     intType,
    OdGePoint3dArray&   points,
    OdGsMarker            thisGsMarker  = 0,
    OdGsMarker            otherGsMarker = 0)
    const;

  virtual OdResult   intersectWith(
    const OdTvDbEntity*   ent,
    OdDb::Intersect     intType,
    const OdGePlane&    projPlane,
    OdGePoint3dArray&   points,
    OdGsMarker            thisGsMarker  = 0,
    OdGsMarker            otherGsMarker = 0)
    const;

  virtual OdResult   getOsnapPoints(
    OdDb::OsnapMode       osnapMode,
    OdGsMarker              gsSelectionMark,
    const OdGePoint3d&    pickPoint,
    const OdGePoint3d&    lastPoint,
    const OdGeMatrix3d&   viewXform,
    OdGePoint3dArray&        snapPoints,
    OdTvDbIntArray&     geomIds) const;

  virtual OdResult getGripPoints(OdGePoint3dArray&     gripPoints,
    OdTvDbIntArray&  osnapModes,
    OdTvDbIntArray&  geomIds) const;

  virtual OdResult moveGripPointsAt(const OdTvDbIntArray& indices,
    const OdGeVector3d& offset);

  virtual OdResult getStretchPoints(OdGePoint3dArray& stretchPoints) const;

  virtual OdResult moveStretchPointsAt( const OdTvDbIntArray& indices,
    const OdGeVector3d& offset);

  
  
  
  */


  /** \details
    Breaks the polygon into a set of polylines.
  */
  virtual OdResult subExplode(
    OdRxObjectPtrArray& entitySet) const;

  virtual OdResult subTransformBy( 
    const OdGeMatrix3d& xfn );

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual bool subWorldDraw(
    OdGiWorldDraw* pWd) const;

  virtual void subSetDatabaseDefaults(
    OdTvDbDatabase* pDb, 
    bool doSubents);

  virtual void saveAs(
    OdGiWorldDraw* pWd,
    OdDb::DwgVersion ver ) const;
};

typedef OdSmartPtr<OdTvDbMPolygon> OdTvDbMPolygonPtr;

class OdTvDbMPolygonNode {
public:
  // Constructor
  OdTvDbMPolygonNode();

public:
  OdTvDbMPolygonNode * mParent;
  OdArray<OdTvDbMPolygonNode *> mChildren;
  OdInt32 mLoopIndex;                   // MPolygon loop index.
};

inline
OdTvDbMPolygonNode::OdTvDbMPolygonNode()
  : mLoopIndex(-1), mParent(NULL)
{
}

#endif // _DBMPOLYGON_H_INCLUDED_

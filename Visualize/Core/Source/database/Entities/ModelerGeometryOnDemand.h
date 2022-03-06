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

#ifndef _MODELERGEOMETRYONDEMAND_INCLUDED_
#define _MODELERGEOMETRYONDEMAND_INCLUDED_

#include "DummyModelerGeometry.h"


class OdModelerGeometryOnDemand : public OdDummyModelerGeometry
{
  OdModelerGeometryPtr        *m_pModelerToSwitch;
  bool m_bStandardSaveFlag;
  bool m_bEnableAcisAudit;
  OdTvDbAuditInfo               *m_pAuditInfo;

  OdModelerGeometryPtr switchToModeler() const;

protected:
  OdModelerGeometryOnDemand();

public:  
  ODRX_DECLARE_MEMBERS(OdModelerGeometryOnDemand);

  virtual void forcedSwitching() { switchToModeler(); }

  static OdSmartPtr<OdModelerGeometryOnDemand> createObject(OdModelerGeometryPtr &pModelerToSwitch, OdTvDbAuditInfo* pAuditInfo, bool bStandardSaveFlag, bool bEnableAcisAudit);

  virtual OdResult in(OdStreamBuf* pStreamIn, AfTypeVer *typeVer, bool bStandardSaveFlag = true);
  virtual OdResult out(OdStreamBuf* pStreamOut, AfTypeVer typeVer, bool bStandardSaveFlag = true) const;

  virtual bool brep(OdBrBrep& ) const;

  virtual bool setFACETRES(double);

  virtual bool worldDraw(OdGiCommonDraw* , OdUInt32, const OdModelerGeometry::NumIsolines *);
  virtual bool getTransformation(OdGeMatrix3d& m);
  virtual OdResult getCachedSilhouettes(OdGeCurve3dPtrArray*);
  virtual bool drawSilhouettes(OdGiViewportDraw* );
  virtual bool explode(OdTvDbEntityPtrArray& ) const;
  virtual void transformBy( const OdGeMatrix3d& xform );

  virtual void createBox( double xLen, double yLen, double zLen );
  virtual void createFrustum( double height, double xRadius, double yRadius, double topXRadius );
  virtual void createSphere( double radius );
  virtual void createTorus( double majorRadius, double minorRadius );
  virtual void createWedge( double xLen, double yLen, double zLen );

  virtual OdResult extrude(const OdTvDbRegion* region, double height, double taper, bool isSolid = true );
  virtual OdResult revolve(const OdTvDbRegion* region, const OdGePoint3d& axisPoint, const OdGeVector3d& axisDir, double angleOfRevolution, bool isSolid = true);

  virtual void ClearMaterialAttributes(const OdArray<OdDbSubentId>* aSubents = NULL);
  virtual void ClearMaterialMapperAttributes();
  virtual MaterialState hasMaterials() const;

  virtual void ClearColorAttributes();
  virtual bool hasTrueColorAttributes() const;
  virtual OdResult getPlane(OdGePlane& regionPlane) const;

  virtual bool setMMPerUnit(double dVal);
  virtual bool getMMPerUnit(double &dVal) const;

  virtual geomType bodyType() const;
  virtual OdResult booleanOper(OdTvDbDatabase* database, OdDb::BoolOperType operation, OdModelerGeometryPtr pModelerPar);
  virtual OdResult booleanOper(OdDb::BoolOperType operation, const OdSmartPtr<OdModelerGeometry> pModelerPar, OdTvDbEntityPtrArray& intersectionEntities);

  virtual OdResult getArea(double& regionArea) const;
  virtual OdResult clear( );
  virtual OdResult getPerimeter(double&) const;
  virtual OdResult getAreaProp( const OdGePoint3d& origin, const OdGeVector3d& xAxis,
    const OdGeVector3d& yAxis, double& perimeter,
    double& area, OdGePoint2d& centroid,
    double momInertia[2], double& prodInertia,
    double prinMoments[2], OdGeVector2d prinAxes[2],
    double radiiGyration[2], OdGePoint2d& extentsLow,
    OdGePoint2d& extentsHigh ) const;

  virtual OdResult extrudeAlongPath(const OdTvDbRegion* region, const OdTvDbCurve* path, double taperAngle = 0.0, bool isSolid = true);
  virtual OdResult imprintEntity(const OdTvDbEntity *pEntity);

  virtual OdResult checkInterference(const OdTvDb3dSolid* otherSolid,
    bool createNewSolid, 
    bool& solidsInterfere,
    OdTvDb3dSolidPtr &commonVolumeSolid)
    const;

  virtual OdResult getMassProp(double& volume,
    OdGePoint3d& centroid,
    double momInertia[3],
    double prodInertia[3],
    double prinMoments[3],
    OdGeVector3d prinAxes[3], 
    double radiiGyration[3],
    OdGeExtents3d& extents) const;

  virtual OdResult getSection(const OdGePlane& plane, OdTvDbRegionPtr &sectionRegion, OdTvDbEntityPtrArray* pSectionObjects = NULL) const;

  virtual OdResult getSlice(const OdGePlane& plane, bool bGetNegHalfToo, OdTvDb3dSolidPtr &pNegHalfSolid);
  virtual OdResult getSlice(OdTvDbSurface* pSurface,  bool bGetNegHalfToo, OdTvDb3dSolidPtr &pNegHalfSolid);

  virtual OdResult sliceByPlane(const OdGePlane& slicePlane, OdTvDbSurfacePtr& pNegHalfSurface, OdTvDbSurfacePtr& pNewSurface, bool bNotModifyItself);
  virtual OdResult sliceBySurface(const OdTvDbSurfacePtr pSlicingSurface, OdTvDbSurfacePtr& pNegHalfSurface, OdTvDbSurfacePtr& pNewSurface, bool bNotModifyItself);

  virtual OdResult cleanBody();
  //virtual OdResult offsetBody(OdTvDbEntity* pOffsetEnt, double offsetDistance);
  virtual OdResult offsetBody(double offsetDistance);

  virtual OdResult separateBody(OdTvDb3dSolidPtrArray &newSolids);

  virtual OdResult createExtrudedObject ( OdTvDbEntity* pSweepEnt,
                                          const OdGeVector3d& directionVec,
                                          OdTvDbSweepOptions& sweepOptions,
                                          bool isSolid = true,
                                          bool bHistoryEnabled = false);

  virtual OdResult createLoftedObject (
    OdTvDbEntityPtrArray& crossSectionCurves,
    OdTvDbEntityPtrArray& guideCurves,
    OdTvDbEntity* pPathCurve, 
    OdTvDbLoftOptions& loftOptions,
    bool isSolid = true);

  virtual OdResult createBlendObject(
    OdTvDbEntityPtrArray& blendedEdges,
    OdTvDbBlendOptions& loftOptions,
    bool isSolid = true);
    //virtual OdResult createLoftedObjectByCoedges(
    //  OdTvDbEntityPtrArray& crossSectionCurves,
    //  OdTvDbEntityPtrArray& guideCurves,
    //  OdTvDbEntity* pPathCurve,
    //  OdTvDbLoftOptions& loftOptions,
    //  bool isSolid = true);

  virtual OdResult createPyramid(double height, int sides,
    double radius, double topRadius = 0.0 );

  virtual OdResult createRevolvedObject ( OdTvDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    double revAngle, double startAngle,
    OdTvDbRevolveOptions& revolveOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false);

  virtual OdResult createSweptObject ( OdTvDbEntity* pSweepEnt,
    OdTvDbEntity* pPathEnt,
    OdTvDbSweepOptions& sweepOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false);

  // Loft options utility functions
  virtual OdResult checkCrossSectionCurves (
    OdTvDbEntityPtrArray& crossSectionCurves,
    bool& allOpen, bool& allClosed, bool& allPlanar,
    bool displayErrorMessages = false );

  virtual OdResult checkGuideCurves ( OdTvDbEntityPtrArray& guideCurves,
    bool displayErrorMessages = false );

  virtual OdResult checkPathCurve ( OdTvDbEntity *pPathCurve,
    bool displayErrorMessages = false );

  // Sweep options utility functions
  virtual OdResult  checkSweepCurve ( OdTvDbEntity *pSweepEnt,
    OdDb::Planarity& planarity, OdGePoint3d& pnt, OdGeVector3d& vec,
    bool& closed, double& approxArcLen, bool displayErrorMessages = false );

  virtual OdResult  checkSweepPathCurve ( OdTvDbEntity *pPathEnt,    bool displayErrorMessages = false );

  // Revolve options utility functions
  virtual OdResult checkRevolveCurve(
    OdTvDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    bool& closed,
    bool& endPointsOnAxis,
    bool& planar,
    bool displayErrorMessages = false);

  virtual OdResult createFrom ( const OdTvDbEntity* pFromEntity );
  virtual OdResult convertToRegion ( OdTvDbEntityPtrArray& regions );
  virtual OdResult thicken(double thickness, bool bBothSides, OdTvDb3dSolidPtr& pSolid) const;

  virtual OdResult intersectWith(const OdTvDbEntity* pEnt, OdDb::Intersect intType,
    OdGePoint3dArray& points, OdGsMarker thisGsMarker, OdGsMarker otherGsMarker) const;

  virtual OdResult intersectWith( const OdTvDbEntity* ent, OdDb::Intersect intType, const OdGePlane& projPlane,
    OdGePoint3dArray& points, OdGsMarker thisGsMarker, OdGsMarker otherGsMarker ) const;

  virtual OdResult copySubEntity(const OdDbSubentId &subentId, OdTvDbEntityPtr &newEntity) const;
  virtual OdResult taperFaces(const OdArray<OdDbSubentId *> &faceSubentIds, const OdGePoint3d &basePoint, 
                              const OdGeVector3d &draftVector, double draftAngle);
  virtual OdResult removeFaces(const OdArray<OdDbSubentId *> &faceSubentIds);
  virtual OdResult offsetFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double offsetDistance);
  virtual OdResult shellBody(const OdArray<OdDbSubentId *> &faceSubentIds, double offsetDistance);
  virtual OdResult transformFaces(const OdArray<OdDbSubentId *> &faceSubentIds, const OdGeMatrix3d &matrix);

  virtual OdResult getSubentPathsAtGsMarker(OdDb::SubentType type,
                                            OdGsMarker gsMark, 
                                            const OdGePoint3d& pickPoint,
                                            const OdGeMatrix3d& viewXform, 
                                            OdTvDbFullSubentPathArray& subentPaths, 
                                            const OdTvDbObjectIdArray* pEntAndInsertStack = 0) const;

  virtual OdResult getGsMarkersAtSubentPath(const OdTvDbFullSubentPath& subPath, 
                                            OdGsMarkerArray& gsMarkers) const;

  virtual OdDbSubentId internalSubentId(void* ent) const;
  virtual void* internalSubentPtr(const OdDbSubentId& id) const;

  virtual bool getNurbCurvesCache(OdGeCurve3dPtrArray &nurbs) const;

  virtual OdResult setSubentPath(OdBrEntity & /*pInpEnt*/, OdTvDbFullSubentPath& /*subpath*/);

  virtual OdResult setBody(const void * pBody);
  virtual void * body( ) const;

  virtual OdResult setSubentColor(const OdDbSubentId &subentId, const OdTvCmColor &color);
  virtual OdResult getSubentColor(const OdDbSubentId &subentId, OdTvCmColor &color) const;
  virtual OdResult setSubentMaterial(const OdDbSubentId &subentId, OdTvDbObjectId matId);
  virtual OdResult getSubentMaterial(const OdDbSubentId &subentId, OdUInt64& numId) const;
  virtual OdResult setSubentMaterialMapper( const OdDbSubentId &subentId, 
                                            OdGeMatrix3d &mx, 
                                            OdUInt8 &projection, 
                                            OdUInt8 &tiling, 
                                            OdUInt8 &autoTransform);
  virtual OdResult getSubentMaterialMapper( const OdDbSubentId &subentId,
                                            OdGeMatrix3d &mx, 
                                            OdUInt8 &projection, 
                                            OdUInt8 &tiling, 
                                            OdUInt8 &autoTransform) const;

  virtual OdResult chamferEdges(const OdArray<OdDbSubentId *> &edgeSubentIds,
                                const OdDbSubentId& baseFaceSubentId, 
                                double baseDist, 
                                double otherDist);

  virtual OdResult filletEdges( const OdArray<OdDbSubentId *> &edgeSubentIds,
                                const OdGeDoubleArray& radius, 
                                const OdGeDoubleArray& startSetback, 
                                const OdGeDoubleArray& endSetback);

  virtual OdResult createSectionObjects(const OdGePlane& sectionPlane, OdTvDbEntityPtrArray& sectionObjects) const;

  virtual OdResult createInterferenceObjects( OdTvDbEntityPtrArray& interferenceObjects,
                                              OdTvDbEntityPtr pEntity, 
                                              unsigned int flags ) const;
 
  virtual OdResult extrudeFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double height, double taper);
  
  virtual OdResult extrudeFacesAlongPath(const OdArray<OdDbSubentId *> &faceSubentIds, const OdTvDbCurve* path);

  virtual OdResult ChangeFacesDoubleSidedParam(bool isDoubleSided);

  virtual OdResult convertToNurbSurface(OdTvDbNurbSurfacePtrArray& nurbSurfaceArray);
  
  virtual OdResult get( int& iUDegree, int& iVDegree, bool& bRational, int& iUNumControlPoints, int& iVNumControlPoints,
                        OdGePoint3dArray& ctrlPtsArr, OdGeDoubleArray& weights, 
                        OdGeKnotVector& uKnots, OdGeKnotVector& vKnots) const;

  virtual OdResult set( int iUDegree, int iVDegree, bool bRational, int iUNumControlPoints, int iVNumControlPoints,
                        const OdGePoint3dArray& ctrlPtsArr, const OdGeDoubleArray& weights, 
                        const OdGeKnotVector& uKnots, const OdGeKnotVector& vKnots);

  virtual OdResult getNumberOfControlPointsInU(int& iCount) const;
  virtual OdResult getNumberOfControlPointsInV(int& iCount) const;

  virtual OdResult getNumberOfKnotsInU(int& iCount) const;
  virtual OdResult getNumberOfKnotsInV(int& iCount) const;

  virtual OdResult getUKnots(OdGeKnotVector& knots) const;
  virtual OdResult getVKnots(OdGeKnotVector& knots) const;

  virtual OdResult getDegreeInU(int& iDegree) const;
  virtual OdResult getDegreeInV(int& iDegree) const;

  virtual OdResult isClosedInU(bool& bIsClosed) const;
  virtual OdResult isClosedInV(bool& bIsClosed) const;

  virtual OdResult isPeriodicInU(bool& bIsPeriodic) const;
  virtual OdResult isPeriodicInV(bool& bIsPeriodic) const;

  virtual OdResult getPeriodInU(double& dPeriod) const;
  virtual OdResult getPeriodInV(double& dPeriod) const;

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos) const;

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos, OdGeVector3d& uDeriv, OdGeVector3d& vDeriv) const;

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos, OdGeVector3d& uDeriv, OdGeVector3d& vDeriv,
                            OdGeVector3d& uuDeriv, OdGeVector3d& uvDeriv, OdGeVector3d& vvDeriv) const;

  virtual OdResult evaluate(double dU, double dV, int iDerivDegree, OdGePoint3d& point, OdGeVector3dArray& derivatives) const;

  virtual OdResult isRational(bool& bIsRational) const;

  virtual OdResult isPlanar(bool& bIsPlanar, OdGePoint3d& ptOnSurface, OdGeVector3d& normal) const;

  virtual OdResult isPointOnSurface(const OdGePoint3d& point, bool& bOnSurface) const;

  virtual OdResult getNormal(double dU, double dV, OdGeVector3d& normal) const;

  virtual OdResult getNumberOfSpansInU(int& iSpan) const;
  virtual OdResult getNumberOfSpansInV(int& iSpan) const;

  virtual OdResult getIsolineAtU(double dNumberSegments, OdTvDbCurvePtrArray& lineSegments) const;
  virtual OdResult getIsolineAtV(double dNumberSegments, OdTvDbCurvePtrArray& lineSegments) const;

  virtual OdResult InsertKnot(double dVal, int iUorV);

  virtual OdResult InsertControlPointsAtU(double dVal, const OdGePoint3dArray& vCtrlPts, const OdGeDoubleArray& vWeights);
  virtual OdResult InsertControlPointsAtV(double dVal, const OdGePoint3dArray& vCtrlPts, const OdGeDoubleArray& vWeights);

  virtual OdResult RemoveControlPointsAtU(int iIndex);
  virtual OdResult RemoveControlPointsAtV(int iIndex);

  virtual OdResult rebuild(int iUDegree, int iVDegree, int iNumUCtrlPts, int iNumVCtrlPts, bool bRestore);

  virtual OdResult modifyPositionAndTangent(double dU, double dV, const OdGePoint3d& point, const OdGeVector3d* uDeriv, const OdGeVector3d* vDeriv);

  virtual OdResult getParameterOfPoint(const OdGePoint3d& point, double& dU, double& dV) const;

  virtual OdResult getControlPoints(int& iUCount, int& iVCount, OdGePoint3dArray& points) const;

  virtual OdResult setControlPoints(int iUCount, int iVCount, const OdGePoint3dArray& points);

  virtual OdResult getControlPointAndWeight(int iUIndex, int iVIndex, OdGePoint3d& point, double& weight, bool& bIsRational) const;

  virtual OdResult setControlPointAndWeight(int iUIndex, int iVIndex, const OdGePoint3d& point, double weight);

  virtual OdResult generateSectionGeometry( const OdTvDbSection*      pSection,
                                            OdTvDbEntityPtrArray&     sourceEntArr,
                                            OdArray<OdTvDbEntityPtr>& intBoundaryEnts,
                                            OdArray<OdTvDbEntityPtr>& intFillEnts,
                                            OdArray<OdTvDbEntityPtr>& backgroundEnts,
                                            OdArray<OdTvDbEntityPtr>& foregroundEnts,
                                            OdArray<OdTvDbEntityPtr>& curveTangencyEnts,
                                            bool                    bIsSetProperties);

  virtual OdResult setColorToSubents(OdTvCmColor const& color);

  virtual OdResult setMaterialToSubents(OdTvDbObjectId materialId);

  virtual OdResult setMaterialResolver(const OdMaterialResolver *pResolver);

  virtual OdResult setMaterialMapperToSubents(OdGeMatrix3d &mx, OdUInt8 &projection,
                                              OdUInt8 &tiling, OdUInt8 &autoTransform);

  virtual OdResult trimSurface( const OdTvDbObjectIdArray& toolIds,
                                const OdTvDbObjectIdArray& toolCurveIds, 
                                const OdGeVector3dArray& projVectors,
                                const OdGePoint3d&       pickPoint, 
                                const OdGeVector3d&      viewVector,
                                bool                     bAutoExtend,
                                bool                     bAssociativeEnabled );

  virtual OdResult projectOnToEntity( const OdTvDbEntity*   pEntityToProject,
                                      const OdGeVector3d& projectionDirection,
                                      OdTvDbEntityPtrArray& projectedEntities ) const;

  virtual OdResult createSculptedSolid(OdTvDbEntityPtrArray& limitingBodies,
                                       const OdGeIntArray& limitingFlags);

  virtual OdResult rayTest( const OdGePoint3d&      rayBasePoint, 
                            const OdGeVector3d&     rayDir,
                            double                  rayRadius, 
                            OdArray<OdDbSubentId> & subEntIds, 
                            OdGeDoubleArray&        parameters) const;

  virtual OdResult createFilletSurface (OdTvDbSurfacePtr&      surf1,
                                        const OdGePoint3d&   pickPt1,
                                        OdTvDbSurfacePtr&      surf2,
                                        const OdGePoint3d&   pickPt2,
                                        double               dRadius,
                                        OdDb::FilletTrimMode trimMode,
                                        const OdGeVector3d&  projDir);

  virtual OdResult extendEdges( OdTvDbFullSubentPathArray& edgesId,
                                double                   dExtDist, 
                                EdgeExtensionType        extOption );

  virtual OdResult getObjectMesh( const OdTvDbFaceterSettings *faceter,
    OdGePoint3dArray& vertexArray, 
    OdInt32Array& faceArray,
    OdGiFaceData*& faceData );

  virtual OdResult createCachedCurves(OdGeCurve3dPtrArray& pCurve);

  virtual OdResult restoreAttributes( OdModelerGeometry* oldmodeler ) { return eNotImplemented; }
  virtual OdResult  addSubentitySpecialSettings(const OdDbSubentId subentId, OdArray<OdUInt32>& retArray, OdUInt32 idx) { return eNotImplemented;}

  virtual OdResult getBoundingBox(OdGeExtents3d &box);

  virtual OdResult convertTo(const OdGePoint3dArray &arrVertexes, const OdInt32Array &arrEdges, const OdInt32Array &arrFaces, OdGiFaceData &fd,
    OdBoolArray &arrFacesColors, OdBoolArray &arrFacesMaterials, OdTvDbEntity* pEntity);


  // for internal use only
  virtual OdResult generateSectionGeometry( SectArgs& sectArgs, OdTvDbEntity *pEnt, bool* bHasForeground );

  virtual bool getFaceMesh(GeMesh::OdGeTrMesh& mesh, OdGsMarker iFace, const wrTriangulationParams& triangulationParams);

  virtual OdResult auditAcisData(OdTvDbAuditInfo* pInfo, const OdRxObject* pObj);
  virtual void enableAcisAudit(bool bEnableAcisAudit);
  virtual OdResult getSectionViewInfo(const OdArray<OdTvDbEntityPtr>& pEnts, const OdGePoint3dArray& pPoints, const OdGeVector3d& normal, OdArray<OdTvDbEntityPtr>& backgroundEnts, OdArray<OdTvDbEntityPtr>& intHatchEnts, OdArray<OdTvDbEntityPtr>& intBoundaryEnts, OdArray<OdTvDbEntityPtr>& curveVisibilityEdges, SectionType sectType = kFull_ST, OdEdgeTypeFlags edgeVis = kTangent);

  virtual OdResult getHlrCurves(OdEdgeHLREdgeVisitor& edgeVisitor,
                                const OdGeVector3d& viewDir,
                                const OdTvDbEntityPtrArray& entities,
                                const OdGeMatrix3dArray* xforms = NULL,
                                OdEdgeTypeFlags edgeType = kTangent);

};

typedef OdSmartPtr<OdModelerGeometryOnDemand> OdModelerGeometryOnDemandPtr;

#endif //_MODELERGEOMETRYONDEMAND_INCLUDED_

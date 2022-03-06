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

#ifndef DbImpAssoc2dConstraintGroup_INCLUDED_
#define DbImpAssoc2dConstraintGroup_INCLUDED_ /*!DOM*/


#include "DbConstraintsExports.h"
#include "DbImpAssocAction.h"
#include "OdConstraintGroupNode.h"
#include "OdConstrainedGeometry.h"
#include "OdGeomConstraint.h"
#include "OdConstraintGroupNodeImpl.h"
#include "OdExplicitConstr.h"
#include "DbAssoc2dConstraintGroup.h"

#include "Ge/GePlane.h"
#define STL_USING_MAP
#include "OdaSTL.h"

class OdTvDbAssocGeomDependency;

#include "TD_PackPush.h"

/*!DOM*/
typedef std::map<OdConstraintGroupNodeId, OdTvDbAssoc2dConstraintGroup::SolutionStatus> OdConstraintStatusMap;

/** \details
  This class represents the custom implementation of the planar constraint group.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssoc2dConstraintGroup : public OdTvDbImpAssocAction
{
  typedef OdTvDbAssoc2dConstraintGroup::SolutionStatus SolutionStatus;
public:
  /** \details
    Gets an implementation of the planar constraint group node.
  */
  static OdConstraintGroupNodeImpl* getConstraintGroupNodeImpl(OdConstraintGroupNode *node)
  {
    return node->m_pImpl;
  }
  static OdConstraintGroupNodeImpl* getConstraintGroupNodeImpl(const OdConstraintGroupNode *node)
  {
    return const_cast<OdConstraintGroupNodeImpl*>(node->m_pImpl);
  }

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssoc2dConstraintGroup();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssoc2dConstraintGroup();

  /** \details
    Sets the work plane to associate it with this planar constraint group.
  */
  OdResult setWorkPlane(const OdGePlane& plane);

  /** \details
    Returns the work plane associated with this planar constraint group.
  */
  const OdGePlane& getWorkPlane() const;

  /** \details
    Applies the transformation matrix for this planar constraint group.
  */
  OdResult transformActionBy(OdTvDbAssocAction* thisAction, const OdGeMatrix3d& xform);

#if 0
  /** \details
    Returns the remaining degree of freedom of this planar constraint group.
  */
  int getDOF() const;
#endif

  /** \details
    Returns the solution status of this planar constraint group.
  */
  SolutionStatus solutionStatus(const OdTvDbAssoc2dConstraintGroup* pGroup, 
    bool bAlsoCheckForConstraints = true) const;

  /** \details
    Returns the evaluation status of a given constrain geometry.
  */
  SolutionStatus geometryStatus(const OdTvDbAssoc2dConstraintGroup* pGroup, 
    const OdConstrainedGeometry* pConsGeom) const;

  /** \details
    Returns the evaluation status of a given constraint.
  */
  SolutionStatus constraintStatus(const OdTvDbAssoc2dConstraintGroup* pGroup,
    const OdGeomConstraint* pConstraint) const;

  /** \details
    Adds a constrain geometry to this planar constraint group.
  */
  OdResult addConstrainedGeometry(const OdTvDbFullSubentPath& subentPath, OdConstrainedGeometry*& pConsGeom, OdTvDbAssoc2dConstraintGroup *pGroup);

  /** \details
    Removes and erases an existing constrain geometry from this planar constraint group.
  */
  OdResult deleteConstrainedGeometry(const OdTvDbObjectId& geomDependencyId);
  OdResult deleteConstrainedGeometry(const OdTvDbObjectIdArray& aDestDepToRemove);


  /** \details
    Gets a pointer to the corresponding internally held the constrain geometry.
  */
  OdResult getConstrainedGeometry(const OdTvDbFullSubentPath& fullSubentPath,
                                  OdConstrainedGeometry*&   pConsGeom,
                                  bool bCreateArcLineMid = false);

  /** \details
    Gets a pointer to the corresponding internally held the constrain geometry.
  */
  OdResult getConstrainedGeometry(const OdTvDbAssocGeomDependency* pGeomDependency,
                                  OdConstrainedGeometry*&   pConsGeom,
                                  OdConstrainedImplicitPoint::ImplicitPointType* pPtType = NULL,
                                  int defPtIndex = -1,
                                  bool bCreateArcLineMid = false);

  /** \details
    Gets all constrain geometry objects of this planar constraint group, including the implicit points 
    associated with corresponding constrain curves.
  */
  OdResult getConstrainedGeometries(OdArray<OdConstrainedGeometry*>& aConstGeom) const;


  /** \details
    Creates and adds a geometrical constraint to this planar constraint group.
  */
  OdResult addGeometricalConstraint(OdTvDbObjectId actionId,
                                    OdGeomConstraint::GeomConstraintType type, 
                                    const OdTvDbFullSubentPathArray& aPaths,
                                    OdGeomConstraint** ppNewConstraint = NULL,
                                    const OdGeMatrix3d* pUCSCoord = NULL);

  OdResult addGeometricalConstraint(OdTvDbObjectId actionId,
                                    OdGeomConstraint::GeomConstraintType type,
                                    const OdArray<OdConstrainedGeometry*>& apConsGeoms,
                                    OdGeomConstraint** ppNewConstraint = NULL,
                                    const OdGeMatrix3d* pUCSCoord = NULL);

  /** \details
    Checks whether the planar constraint group is empty.
  */
  bool isEmpty() const;

  /** \details
    Creates and adds a distance constraint to this planar constraint group 
    using two given constrain geometry objects.
  */
  OdResult addDistanceConstraint(OdTvDbAssoc2dConstraintGroup *pGroup,
                                 OdConstrainedGeometry* pConsGeom1,
                                 OdConstrainedGeometry* pConsGeom2,
                                 OdDistanceConstraint::DirectionType directionType,
                                 OdTvDbObjectId valueDependencyId,
                                 OdTvDbObjectId dimDependencyId, // May be null
                                 const OdGeVector3d* pFixedDirection = NULL,
                                 const OdConstrainedLine* pDirectionLine = NULL,
                                 OdDistanceConstraint** ppNewDisConstraint = NULL);

  /** \details
    Creates and adds an angle constraint to this planar constraint group 
    using two given constrain lines.
  */
  OdResult addAngleConstraint(OdTvDbAssoc2dConstraintGroup *pGroup,
                              OdConstrainedLine* pConsLine1,
                              OdConstrainedLine* pConsLine2,
                              OdAngleConstraint::SectorType sectorType,
                              OdTvDbObjectId valueDependencyId,
                              OdTvDbObjectId dimDependencyId, // May be null
                              OdAngleConstraint** ppNewAngConstraint = NULL);

  /** \details
    Creates and adds an three-points angle constraint to this planar constraint group 
    using three given constrain points.
  */
  OdResult add3PointAngleConstraint(OdTvDbAssoc2dConstraintGroup *pGroup,
                                    OdConstrainedPoint* pConsPoint1,
                                    OdConstrainedPoint* pConsPoint2,
                                    OdConstrainedPoint* pConsPoint3,
                                    OdAngleConstraint::SectorType sectorType,
                                    OdTvDbObjectId valueDependencyId,
                                    OdTvDbObjectId dimDependencyId, // May be null
                                    Od3PointAngleConstraint** ppNewAngConstraint = NULL);

  /** \details
    Creates and adds an radius or diameter constraint to this planar constraint group 
    using a given constrain geometry.
  */
  OdResult addRadiusDiameterConstraint(OdTvDbAssoc2dConstraintGroup *pGroup,
                                       OdConstrainedGeometry* pConsGeom,
                                       OdRadiusDiameterConstraint::RadiusDiameterConstrType type,
                                       OdTvDbObjectId valueDependencyId,
                                       OdTvDbObjectId dimDependencyId, // May be null
                                       OdRadiusDiameterConstraint** ppNewRadDiaConstraint = NULL);

  /** \details
    Deletes the nodes of the constraint group.
  */
  OdResult deleteNodes(OdArray<OdGeomConstraint*> &iaConstraints, OdArray<OdConstrainedGeometry*> &iaGeometries);

  /** \details
    Deletes the constraint geometries.
  */
  OdResult deleteGeometries(OdArray<OdConstrainedGeometry*> &ioaGeometries);

  /** \details
    Deletes the constraint help parameters.
  */
  OdResult deleteHelpParameters(OdArray<OdHelpParameter*> &ioaHelpParameters, OdConstraintGroupNodeId id);

  /** \details
    Deletes the constraints.
  */
  OdResult deleteConstraints(OdArray<OdGeomConstraint*> &iaConstraints,
                             OdArray<OdConstrainedGeometry*> &ioaGeometries);

  /** \details
    Deletes an existing geometry constrain object held by this planar constraint group.
  */
  OdResult deleteConstraint(OdGeomConstraint* pGeomConst);

  /** \details
    Returns all geometry constrain objects in this planar constraint group, 
    including topological and dimensional constraints.
  */
  OdResult getConstraints(OdArray<OdGeomConstraint*>& apConstraints) const;


#if 0
  /** \details
    Defines the constraints which can be added to an under-constrained model.
  */
  OdResult autoConstrain(const OdTvDbFullSubentPathArray& aPaths,
                         const OdGeTol& tol,
                         OdAutoConstrainEvaluationCallback* pCallback);
#endif
  /** \details
    Gets all associated geometry dependency which are connected by the planar constraint group.
  */
  OdResult getAllConnectedGeomDependencies(const OdTvDbObjectIdArray& srcGeomDependencyIds,
                                           OdTvDbObjectIdArray& allConnectedGeomDependencyIds) const;

  /** \details
    Returns a pointer to this planar constraint group.
  */
  OdConstraintGroupNode* getGroupNodePtr(const OdConstraintGroupNodeId nodeId) const;

  /** \details
    Sets state of corresponding nodeId.
  */
  void setStatusNode(OdConstraintGroupNodeId nodeId, SolutionStatus status) const
  {
    m_statusNodes[nodeId] = status;
  }

  /** \details
    Sets state of this planar constraint group.
  */
  void setStatusGroup(SolutionStatus status) const
  {
    m_groupState = status;
  }

#if 0
  /** \details
    Regenerate the dimension system.
  */
  void regenDimensionSystem();

  /** \details
     This is the notification call of the corresponding method of the parent class 
     which owns this action to inform the constraint group that the dependent entity 
     given by the geometry dependency has been mirrored.
  */
  OdResult geometryMirrored(OdTvDbAssocGeomDependency* pGeomDependency);
#endif

  /** \details
    Evaluates this planar constraint group.
  */
  virtual void evaluate(OdTvDbAssocAction *pAction, OdTvDbAssocEvaluationCallback* pEvaluationCallback);

  /** \details
     This is the notification call of the corresponding postProcessAfterDeepClone() method 
     of the parent class that owns this action.
  */
  virtual OdResult postProcessAfterDeepClone(OdTvDbAssocAction *pAction, OdTvDbIdMapping& idMap);

  /** \details
  */
  OdResult addMoreObjectsToDeepClone(const OdTvDbAssocAction *pThisAction, OdTvDbIdMapping & idMap,
    OdTvDbObjectIdArray & additionalObjectsToClone) const;

  /** \details
    Moves the constraint geometry.
  */
  OdResult moveConstrainedGeometry(const OdTvDbFullSubentPath& subentPath,
                                   OdTvDbAssocGeomDependency * pExistingDep,
                                   OdTvDbAssoc2dConstraintGroup *pGroup);

  /** \details
     This is the notification call of the corresponding method 
     of the parent class that owns this action.
  */
  void onAddConstrainedGeometry(const OdTvDbFullSubentPath& subentPath, OdConstrainedGeometry* pConsGeom);

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbAssocAction *pSelf, OdTvDbDwgFiler* pFiler);

  /** \details
    Reads the .dwg file data of this object for 2010 version. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dwgInNodes2010(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId, OdUInt32 ver);

  /** \details
    Reads the .dwg file data of this object for 2013 version. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dwgInNodes2013(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Writes the .dwg file data of this object for 2010 version. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void dwgOutNodes2010(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Writes the .dwg file data of this object for 2013 version. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void dwgOutNodes2013(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Reads the .dxf file data of this object for 2010 version. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dxfInNodes2010(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Reads the .dxf file data of this object for 2013 version. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dxfInNodes2013(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Writes the .dxf file data of this object for 2010 version. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void dxfOutNodes2010(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Writes the .dxf file data of this object for 2013 version. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void dxfOutNodes2013(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  void composeForLoad( OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo );

  //remove in full version
  OdResult updateDatabaseObjects(OdTvDbAssoc2dConstraintGroup *pGroup);
  void audit(OdTvDbAssoc2dConstraintGroup* pGroup, OdTvDbAuditInfo* pAuditInfo);

  /*!DOM*/
  virtual bool isRelevantDependencyChange(const OdTvDbAssocDependency* pDependency) const;

  /** \details
    Updates geometry cache corresponding to the specified dependency and set its status to kIsUpToDateAssocStatus. 

    \param pDependency [in]  Pointer to the dependency object owning this implementation object.
  */
  virtual void evaluateDependency(OdTvDbAssocDependency* pDependency);
protected:
  /*!DOM*/
  OdTvDbObjectId findGeometryCorrespodingToDimension(const OdTvDbAssocDependency* pDimDep) const;
  /*!DOM*/
  OdGePlane               m_plane;
  /*!DOM*/
  OdConstraintGroupNodeId m_seedId;
  /*!DOM*/
  typedef std::map<OdConstraintGroupNodeId, OdConstraintGroupNodePtr> OdConstraintGroupNodeMap;
  /*!DOM*/
  OdConstraintGroupNodeMap m_mapNodes;
  /*!DOM*/
  mutable OdConstraintStatusMap m_statusNodes;
  /*!DOM*/
  mutable SolutionStatus m_groupState;
  /*!DOM*/
  bool          m_Unk_Bool;
  /*!DOM*/
  OdTvDbObjectId  m_Unk_ObjId;
private:
  /*!DOM*/
  void postReadWork();
  /*!DOM*/
  bool isConstraintOfThisTypeExist(const OdArray<OdGeomConstraint*> aConstr,
                                   const OdRxClass* pObjType,
                                   OdGeomConstraint** ppConstraint);
  /*!DOM*/
  OdResult getConstraintGroupNodeObjects(OdArray<OdConstraintGroupNodePtr>& aResObj, OdRxClass* pObjType);
  /*!DOM*/
  bool findDatumLine(OdConstrainedDatumLine** ppDatumLine, const OdGeVector3d& dir);
  /*!DOM*/
  OdResult tieNode(OdConstraintGroupNodePtr node, OdTvDbObjectId actionId);
  /*!DOM*/
  OdResult removeNode(OdConstraintGroupNode* pNode);
  /*!DOM*/
  void tieGeomsAndCnstr3(OdGeomConstraint *pCnstr,
                         OdConstrainedGeometry* pGeomF,
                         OdConstrainedGeometry* pGeomS,
                         OdConstrainedGeometry* pGeomT = NULL);
  /*!DOM*/
  void tieDimAndCnstr(OdExplicitConstraint *pCnstr,
                      OdTvDbObjectId valueDependencyId,
                      OdTvDbObjectId dimDependencyId,
                      OdTvDbAssoc2dConstraintGroup *pGroup);
  /*!DOM*/
  void tieGeomsAndCnstr(OdConstrainedGeometry* pGeomF, OdConstrainedGeometry* pGeomS, OdGeomConstraint *pCnstr);
  /*!DOM*/
  void tieGeomsAndCnstrWithHeplPrm(OdConstrainedGeometry* pGeomF, OdConstrainedGeometry* pGeomS,
                                   OdGeomConstraint *pCnstr, OdHelpParameter *pHelpPrmF, OdHelpParameter *pHelpPrmS);

  /*!DOM*/
  OdGeomConstraint* addHorizontalConstraint(OdConstrainedGeometry* pGeomF,
                                            OdTvDbObjectId actionId,
                                            const OdGeVector3d& axis = OdGeVector3d::kXAxis);

  /*!DOM*/
  OdGeomConstraint* addHorizontalConstraint(OdConstrainedGeometry* pGeomF,
                                            OdConstrainedGeometry* pGeomS,
                                            OdTvDbObjectId actionId,
                                            const OdGeVector3d& axis = OdGeVector3d::kXAxis);

  /*!DOM*/
  OdGeomConstraint* addVerticalConstraint(OdConstrainedGeometry* pGeomF,
                                          OdTvDbObjectId actionId,
                                          const OdGeVector3d& axis = OdGeVector3d::kYAxis);

  /*!DOM*/
  OdGeomConstraint* addVerticalConstraint(OdConstrainedGeometry* pGeomF,
                                          OdConstrainedGeometry* pGeomS,
                                          OdTvDbObjectId actionId,
                                          const OdGeVector3d& axis = OdGeVector3d::kYAxis);

  /*!DOM*/
  OdGeomConstraint* addParallelConstraint(OdConstrainedGeometry* pGeomF,
                                          OdConstrainedGeometry* pGeomS,
                                          OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addPerpendicularConstraint(OdConstrainedGeometry* pGeomF,
                                               OdConstrainedGeometry* pGeomS,
                                               OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addNormalConstraint(OdConstrainedGeometry* pGeomF,
                                        OdConstrainedGeometry* pGeomS,
                                        OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addColinearConstraint(OdConstrainedGeometry* pGeomF,
                                          OdConstrainedGeometry* pGeomS,
                                          OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addCoincidentConstraint(OdConstrainedGeometry* pGeomF,
                                          OdConstrainedGeometry* pGeomS,
                                          OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addConcentricConstraint(OdConstrainedGeometry* pGeomF,
                                            OdConstrainedGeometry* pGeomS,
                                            OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addTangentConstraint(OdConstrainedGeometry* pGeomF,
                                         OdConstrainedGeometry* pGeomS,
                                         OdHelpParameter* pHelpParamF,
                                         OdHelpParameter* pHelpParamS,
                                         OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addEqualRadiusConstraint(OdConstrainedGeometry* pGeomF,
                                             OdConstrainedGeometry* pGeomS,
                                             OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addEqualLengthConstraint(OdConstrainedGeometry* pGeomF,
                                             OdConstrainedGeometry* pGeomS,
                                             OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addSymmetricConstraint(OdConstrainedGeometry* pGeomF,
                                           OdConstrainedGeometry* pGeomS,
                                           OdConstrainedGeometry* pGeomLine,
                                           OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addFixConstraint(OdConstrainedGeometry* pGeom, OdTvDbObjectId actionId);

  /*!DOM*/
  OdGeomConstraint* addG2SmoothConstraint(OdConstrainedGeometry* pGeomF,
                                          OdConstrainedGeometry* pGeomS,
                                          OdTvDbObjectId actionId);

  //need for composite constraints

  /*!DOM*/
  OdGeomConstraint* addEqualCurvatureConstraint(OdConstrainedGeometry* pGeomF,
                                                OdConstrainedGeometry* pGeomS,
                                                OdHelpParameter* pHelpParamF,
                                                OdHelpParameter* pHelpParamS,
                                                OdTvDbObjectId actionId);

  /*!DOM*/
  OdHelpParameter* createHelpParameter(OdConstrainedImplicitPoint *pPoint, OdTvDbObjectId actionId);

  //common code for vert/horz cnstr

  /*!DOM*/
  OdGeomConstraint* addVertHorzConstraint(OdConstrainedGeometry* pGeomF,
                                          OdTvDbObjectId actionId,
                                          const OdRxClass *desc,
                                          const OdGeVector3d dir,
                                          const OdString name);

  /*!DOM*/
  OdGeomConstraint* addVertHorzConstraint(OdConstrainedGeometry* pGeomF,
                                          OdConstrainedGeometry* pGeomS,
                                          OdTvDbObjectId actionId,
                                          const OdRxClass *desc,
                                          const OdGeVector3d dir,
                                          const OdString name);

  /*!DOM*/
  OdConstrainedGeometry* addConstrainedGeometry(OdTvDbAssocGeomDependencyPtr pGeomDep);
  /*!DOM*/
  OdConstrainedGeometry* addPoint(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addCircle(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addArc(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addBoundedLine(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addRay(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addXLine(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addEllipse(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addEllipseArc(OdTvDbObjectId geomDepId);
  /*!DOM*/
  OdConstrainedGeometry* addSpline(OdTvDbObjectId geomDepId, const OdGeNurbCurve3d& spline);
  /*!DOM*/
  OdConstrainedRigidSet* getRigidSet(OdTvDbObjectId geomDepId, bool createIfNotExists = false);
  /*!DOM*/
  bool addGeometryToRigidSet(OdConstrainedRigidSet& rigidSet, OdConstrainedGeometry& geom);

  /*!DOM*/
  OdConstrainedImplicitPoint* addImplicitPoint(OdConstrainedCurve *pCurve, OdConstrainedImplicitPoint::ImplicitPointType type, int index = -1);

  /*!DOM*/
  static void updateDependentOnObjects(OdTvDbAssocAction *p2dConstraintGroup);
};

#include "TD_PackPop.h"

#endif


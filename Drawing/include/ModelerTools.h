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
// ModelerTools.h : auxilary functionality of geometry modeler

// Copyright © Menhirs NV. All rights reserved.

//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

#ifndef _OD_MODELERTOOLS_INCLUDED_
#define _OD_MODELERTOOLS_INCLUDED_

//#include "BricsysChanges.h"
#include "ModelerGeometry.h"

#include "TD_PackPush.h"

typedef void (*MainHistStreamFunc)(void*);


/** \details
    This class defines the interface for classes that
    provide the services for ACIS SAT and SAB data.

    Corresponding C++ library: ModelerGeometry
    <group Other_Classes>
*/
class DBENT_EXPORT OdModelerTools: public OdRxObject
{
protected:
    OdModelerTools() {}
public:  
    ODRX_DECLARE_MEMBERS(OdModelerTools);

    /** \details
      Delete the modeler bulletins.
    */
    virtual OdResult deleteModelerBulletins() = 0;

    /** \details
      Should be called from the main stream to start ACIS thread-safety mode.
      Prepares separate history streams for each thread, turns the thread-safety mode on.
      Returns false if no modeler geometry exist.
    */
    virtual void beginThreadSafetyMode(unsigned nThreads, const unsigned* aThreads) = 0;

    /** \details
      Should be called from the main stream to end ACIS thread-safety mode.
      Merges separate history streams into the main history, turns the thread-safety mode off.
    */
    virtual void endThreadSafetyMode(unsigned nThreads, const unsigned* aThreads) = 0;

    /** \details
      Should be called from a thread function to start modeler in this particular thread.
      Substitutes default history stream by unique one for the given thread.
    */
    virtual bool startThread() = 0;

    /** \details
      Should be called from a thread function to stop modeler in this particular thread.
      Restores default history stream for the given thread.
    */
    virtual bool stopThread() = 0;

    /** \details
      Checks if the modeler is started in this particular thread.
    */
    virtual bool isThreadStarted() const = 0;

    /** \details
      Checks topology and geometry correctness of given entity.
      Results are returned as text in parameter 'report'.
    */
    virtual OdResult check3dSolid(const OdDb3dSolid&, OdString& report) = 0;

    /** \details
    Executes given function when history stream is set to a main one
    */
    virtual void executeInMainHistoryStream(MainHistStreamFunc func, void* data) = 0;

  /** \details
    Creates OdDbHatch entities from OdDbRegion or OdDbSurface (planar).

    \param geom   [in]  The source entities.
    \param aHatch [out] Receives a result hateches.
    \returns eOk if successful, or an appropriate error code if not.

    \remarks
    The newly created *hatches* are non- *database* -resident. It is up to the caller to either add them
    to an OdDbDatabase or to delete them.
  */
  virtual OdResult createHatchFromModelerGeometry(const OdDbEntity& geom, OdDbEntityPtrArray& aHatch) = 0;

  //DOM-IGNORE-BEGIN
  virtual bool getAdeskTrueCol(void* pEntity, unsigned long& color) = 0;
  virtual bool getAdeskCol(void* pEntity, unsigned long& color) = 0;
  virtual int setTestMode(int testMode) = 0;
  //DOM-IGNORE-END

  /** \details
    Calculates closest points on the given modeler geometry objects or their subentities.
    Matrices toWc1, toWc2 define transformations applied to given objects before calculations.

    \param obj1       [in]  The first modeler geometry object.
    \param subId1     [in]  The first object subentity (may be null).
    \param toWc1      [in]  Transformation from ECS of the first object to WCS.
    \param obj2       [in]  The second modeler geometry object.
    \param subId2     [in]  The second object subentity (may be null).
    \param toWc2      [in]  Transformation from ECS of the second object to WCS.
    \param nearestPt1 [out] Closest point on first object in WCS.
    \param nearestPt2 [out] Closest point on second object in WCS.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getClosestPoints(const OdModelerGeometry& obj1, 
    const OdDbSubentId& subId1, const OdGeMatrix3d& toWc1,
    const OdModelerGeometry& obj2, const OdDbSubentId& subId2, const OdGeMatrix3d& toWc2,
    OdGePoint3d& nearestPt1, OdGePoint3d& nearestPt2) = 0;

  /** \details
    Calculates closest points on the given modeler geometry object (or its subentity) and the given curve.
    Matrix toWc defines transformations applied to modeler geometry object before calculations.

    \param obj        [in]  The modeler geometry object.
    \param subId      [in]  The Object subentity (may be null).
    \param toWc       [in]  Transformation from ECS of the modeler geometry object to WCS.
    \param curve      [in]  The curve (defined in WCS).
    \param nearestPt1 [out] Receives a closest point on first object in WCS.
    \param nearestPt2 [out] Receives a closest point on second object in WCS.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getClosestPoints(const OdModelerGeometry& obj, const OdDbSubentId& subId, 
    const OdGeMatrix3d& toWc, const OdGeCurve3d& curve, 
    OdGePoint3d& nearestPt1, OdGePoint3d& nearestPt2) = 0;

  /** \details
    Calculates point on the given modeler geometry object (or its subentity) closest to the given point.
    Matrix toWc defines transformations applied to the modeler geometry object before calculations.

    \param obj       [in]  The modeler geometry object.
    \param subId     [in]  The object subentity (may be null).
    \param toWc      [in]  Transformation from ECS of the modeler geometry object to WCS.
    \param ptWc      [in]  Input point (defined in WCS).
    \param nearestPt [out] Receives a closest point on the object in WCS.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getClosestPoints(const OdModelerGeometry& obj, const OdDbSubentId& subId, 
    const OdGeMatrix3d& toWc, const OdGePoint3d& inPt, OdGePoint3d& nearestPt) = 0;

  /** \details
    Calculates closest points on the given modeler geometry object (or its subentity)
    and the given wireframe (set of straight line segments). Wireframe is defined
    as set of points and array of pairs {(s0, e0),...,(sn, en)},
    where si - index of start point of i-th wireframe edge, 
          ei - index of end point of i-th wireframe edge.
    Matrix toWc defines transformations applied to the modeler geometry object before calculations.

    \param obj        [in]  The modeler geometry object.
    \param subId      [in]  The object subentity (may be null).
    \param toWc       [in]  Transformation from ECS of the modeler geometry object to WCS.
    \param pts2       [in]  Vertices of input wireframe (defined in WCS).
    \param edges2     [in]  Edges of input wireframe.
    \param nearestPt1 [out] Receives a closest point on first object in WCS.
    \param nearestPt2 [out] Receives a closest point on second object in WCS.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getClosestPoints(const OdModelerGeometry& obj1, const OdDbSubentId& subId1,
    const OdGeMatrix3d& toWc1,const OdGePoint3dArray& pts2, const OdInt32Array& edges2,
    OdGePoint3d& nearestPt1, OdGePoint3d& nearestPt2) = 0;

  /** \details
    Copies given modeler geometry object and transform copy by passed matrix.

    \param srcModeler    [in]  The modeler geometry object.
    \param mtx           [in]  Additional transformation.
    \param pCloneModeler [out] Cloned and transformed modeler geometry object.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult cloneAndXform(const OdModelerGeometry& srcModeler, const OdGeMatrix3d& mtx,
    OdModelerGeometryPtr& pCloneModeler) = 0;

  /** \details
    Calculates the maximum point on the given modeler geometry object along a certain direction.

    \param object    [in]  The modeler geometry object.
    \param direction [in]  The direction along which the extreme point is to be calculated.
    \param maxPoint  [out] Receives an extreme point on object along the direction in WCS.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getMaxPoint(const OdModelerGeometry& object,
    const OdGeVector3d& direction, OdGePoint3d& maxPoint) = 0;

  /** \details
    Calculates the extreme points on the given modeler geometry object along a certain direction.

    \param object    [in]  The modeler geometry object.
    \param direction [in]  The direction along which the extreme points are to be calculated.
    \param minPoint  [out] Receives an extreme point on object along the direction in opposite sense in WCS.
    \param maxPoint  [out] Receives an extreme point on object along the direction in WCS.
    \returns eOk if successful, or an appropriate error code if not.
  */
  virtual OdResult getExtremePoints(const OdModelerGeometry& object,
    const OdGeVector3d& direction, OdGePoint3d& minPoint, OdGePoint3d& maxPoint) = 0;
};


/** \details
  The typified smart pointer for the /modeler tools/ object. This template 
  class is specialization of the OdSmartPtr class for the OdModelerTools class.

  \sa
  <link smart_pointers, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdModelerTools> OdModelerToolsPtr;

#include "TD_PackPop.h"

#endif //_OD_MODELERTOOLS_INCLUDED_

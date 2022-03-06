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

#ifndef DbAssocActionBody_INCLUDED_
#define DbAssocActionBody_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbObject.h"
#include "DbAssocAction.h"
#include "DbAssocDependency.h"
#include "DbEntity.h"

#include "TD_PackPush.h"

/** \details
  This class is abstract base class for deriving custom action body.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT ODRX_ABSTRACT OdTvDbAssocActionBody : public OdTvDbObject
{
public: 
  ODRX_DECLARE_MEMBERS(OdTvDbAssocActionBody);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocActionBody();

  //explicit AcTvDbAssocActionBody(AcTvDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocActionBody();

  /** \details
    Returns an object ID of the parent action. 
  */
  OdTvDbObjectId parentAction() const { return ownerId(); }

  /** \details
    Returns the current status of this action. 
  */
  OdTvDbAssocStatus status() const;

  /** \details
    Sets the status for this action. 
  */
  OdResult setStatus(OdTvDbAssocStatus newStatus, 
                      bool           notifyOwningNetwork = true,
                      bool           setInOwnedActions   = false);

  /** \details
    Returns the logically owning association network, or kNull if it is the topmost. 
  */
  OdTvDbObjectId owningNetwork() const;

  /** \details
    Gets the dependencies of this action. The default implementation obtains all dependencies 
    owned by the base action class.
  */
  OdResult getDependencies(bool readDependenciesWanted, 
                           bool writeDependenciesWanted,
                           OdTvDbObjectIdArray& dependencyIds) const; 

  /** \details
    Adds a dependency for this action. The default implementation calls the corresponding method 
    of the parent class that owns this action.
  */
  OdResult addDependency(const OdTvDbObjectId& dependencyId, 
                         bool  setThisActionAsOwningAction = true); 

  /** \details
    Removes a dependency from this action. 
  */
  OdResult removeDependency(const OdTvDbObjectId& dependencyId, 
                            bool          alsoEraseIt);

  /** \details
    Clears all dependencies from this action. 
  */
  OdResult removeAllDependencies(bool alsoEraseThem);

  /** \details
    Evaluates those dependencies of the action that need to be evaluated
    by caling OdTvDbAssocDependency::evaluate(). Just a shortcut to OdTvDbAssocAction method.
  */
  OdResult evaluateDependencies();

  /** \details
    Checks whether the system is evaluating an action or a network of actions.
  */
  bool isActionEvaluationInProgress() const;

  /** \details
    Returns the current association evaluation callback set instance, or NULL if no action evaluation 
    is in progress.
  */
  OdTvDbAssocEvaluationCallback* currentEvaluationCallback() const;
  
  /** \details
    Creates ODDbAssocAction and ODDbAssocActionBody
    of the required class, makes the action own the action body and posts 
    both to the database of the given objectId.     
  */
  static OdResult createActionAndActionBodyAndPostToDatabase( OdRxClass* pActionBodyClass, const OdTvDbObjectId& objectId, OdTvDbObjectId& createdActionId, OdTvDbObjectId& createdActionBodyId);
public: 
  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::evaluate() method).
  */
  virtual void evaluateOverride() = 0;

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::getDependencies() method).

    \remarks Not implemented
  */
  OdResult getDependenciesOverride(bool readDependenciesWanted, 
                                   bool writeDependenciesWanted,
                                   OdTvDbObjectIdArray& dependencyIds) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::getDependentObjects() method).

    \remarks Not implemented
  */
  OdResult getDependentObjectsOverride(bool readDependenciesWanted,
                                       bool writeDependenciesWanted,
                                       OdTvDbObjectIdArray& objectIds) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::removeAllDependencies() method).

    \remarks Not implemented
  */
  virtual OdResult removeAllDependenciesOverride(bool alsoEraseThem)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::isOwnedDependency() method).

    \remarks Not implemented
  */
  virtual OdResult isOwnedDependencyOverride(const OdTvDbAssocDependency* pDependency, 
                                             bool& isOwnedDependency) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::isExternalDependency() method).

    \remarks Not implemented
  */
  virtual OdResult isExternalDependencyOverride(const OdTvDbAssocDependency* pDependency, 
                                                      bool& isExternalDependency) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::hasDependencyCachedValue() method).

    \remarks Not implemented
  */
  virtual OdResult hasDependencyCachedValueOverride(const OdTvDbAssocDependency* pDependency,
                                                             bool& hasDepCachedValue) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::isRelevantDependencyChange() method).

    \remarks Not implemented
  */
  virtual OdResult isRelevantDependencyChangeOverride(const OdTvDbAssocDependency* pDependency,
                                                      bool& isRelevantDepChange) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::areDependenciesOnTheSameThing() method).

    \remarks Not implemented
  */
  virtual OdResult areDependenciesOnTheSameThingOverride(const OdTvDbAssocDependency* pDependency1,
                                                         const OdTvDbAssocDependency* pDependency2,
                                                         bool& areDependentOnSameThing) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::areDependenciesEqual() method).

    \remarks Not implemented
  */
  virtual OdResult areDependenciesEqualOverride(const OdTvDbAssocDependency* pDependency1,
                                                const OdTvDbAssocDependency* pDependency2,
                                                bool& areEqual) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::evaluateDependency() method).

    \remarks Not implemented
  */
  virtual OdResult evaluateDependencyOverride(OdTvDbAssocDependency* pDependency)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::dependentObjectCloned() method).

    \remarks Not implemented
  */
  virtual OdResult dependentObjectClonedOverride(const OdTvDbAssocDependency* pDependency, 
                                                 const OdTvDbObject*          pDbObj, 
                                                 const OdTvDbObject*          pNewObj);

  /** \details
    Method is called by the corresponding method of the parent action which owns this action body.

    \sa
    OdTvDbAssocAction::addMoreObjectsToDeepClone()

    \remarks Not implemented
  */
  virtual OdResult addMoreObjectsToDeepCloneOverride(OdTvDbIdMapping& idMap, 
                                                     OdTvDbObjectIdArray& additionalObjectsToClone) const;

  /** \details
    Method is called by the corresponding method of the parent action which owns this action body.

    \sa
    OdTvDbAssocAction::postProcessAfterDeepClone()

    \remarks Not implemented
  */
  virtual OdResult postProcessAfterDeepCloneOverride(OdTvDbIdMapping& idMap) 
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::postProcessAfterDeepCloneCancel() method).

    \remarks Not implemented
  */
  virtual OdResult postProcessAfterDeepCloneCancelOverride(OdTvDbIdMapping& idMap)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::ownedDependencyStatusChanged() method).

    \remarks Not implemented
  */
  virtual OdResult ownedDependencyStatusChangedOverride(OdTvDbAssocDependency* pOwnedDependency, 
                                                        OdTvDbAssocStatus      previousStatus)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::isEqualTo() method).

    \remarks Not implemented
  */
  virtual OdResult isEqualToOverride(const OdTvDbAssocAction* pOtherAction, bool& isEqual) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::evaluationPriority() method).

    \remarks Not implemented
  */
  virtual OdResult evaluationPriorityOverride(OdTvDbAssocEvaluationPriority& priority) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::getDependentActionsToEvaluate() method).

    \remarks Not implemented
  */
  virtual OdResult getDependentActionsToEvaluateOverride(OdTvDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::transformActionBy() method).

    \remarks Not implemented
  */
  virtual OdResult transformActionByOverride(const OdGeMatrix3d&)
  { return eNotImplemented; }

  /** \details
    Method is called by the corresponding method of the parent action which owns this action
    (see OdTvDbAssocAction::dragStatus() method).

    \remarks Not implemented
  */
  virtual OdResult dragStatusOverride(const OdDb::DragStat status)
  { return eNotImplemented; }

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  
  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  OdResult getValueParam( const OdString& paramName,
                          OdTvDbEvalVariant& value,
                          OdString& expression,
                          OdString& evaluatorId,
                          int valueIndex = 0) const; 


  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  OdResult setValueParam( const OdString& paramName,
                          const OdTvDbEvalVariant& value,
                          const OdString& expression,
                          const OdString& evaluatorId,
                          OdString& errorMessage,
                          bool silentMode,
                          int valueIndex = 0);

  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;

  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  OdValue::UnitType valueParamUnitType(const OdString& paramName) const;

  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  OdResult setValueParamUnitType(const OdString& paramName, OdValue::UnitType unitType);
  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  OdResult addParam( const OdString& paramName, 
                     OdRxClass* pParamClass, 
                     OdTvDbObjectId& paramId, 
                     int& paramIndex);
  /** \details
    Just a shortcut to OdTvDbAssocAction method.
  */
  void ownedValueParamNames(OdStringArray& paramNames) const;

  virtual OdStringArray compareWith(const OdTvDbObjectId bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;
protected:
  /*!DOM*/
  friend class OdTvDbImpAssocAction;
  /*!DOM*/
  class OdTvDbImpAssocActionBody* m_pImpObj;
};
/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocActionBody class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocActionBody> OdTvDbAssocActionBodyPtr;


#include "TD_PackPop.h"
#endif


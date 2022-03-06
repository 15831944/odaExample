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

#ifndef DbImpAssocNetwork_INCLUDED_
#define DbImpAssocNetwork_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbImpAssocAction.h"

#include "TD_PackPush.h"

/** \details
  This class represents the custom implementation of the network of associated actions.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocNetwork : public OdTvDbImpAssocAction
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  explicit OdTvDbImpAssocNetwork();

  /** \details
    \returns array of object IDs of owned by this network.
  */
  OdTvDbObjectIdArray getActions() const;

  /** \details
    \returns array of the actions marked to be evaluated.
  */
  OdTvDbObjectIdArray getActionsToEvaluate() const;

  /** \details
    Reports the actions, dependencies and objects that need to be evaluated.
    \param pThisNetwork [in] associative network object owning this implementation object.
    \param pActionsToEvaluateCallback [in,callback] callback interface to report objects that need to be evaluated.
  */
  virtual void getDependentActionsToEvaluate(const OdTvDbAssocAction* pThisNetwork, OdTvDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const;

  /** \details
    Adds the associated action to be owned by this network using its ID.
    \param thisNetwork [in] associative network object owning this implementation object.
    \param actionId [in] object ID of the action to add to network object.
    \param alsoSetAsDatabaseOwner [in] if true this network object will be set also as database owner of the action.
  */
  OdResult addAction(OdTvDbAssocNetwork* thisNetwork, const OdTvDbObjectId& actionId, bool alsoSetAsDatabaseOwner);

  /** \details
    Removes the associated action from this network using its ID.
    \param thisNetwork [in] associative network object owning this implementation object.
    \param actionId [in] object ID of the action to bee removed.
    \param alsoEraseIt [in] if true the action will be erased.
  */
  OdResult removeAction(OdTvDbAssocNetwork* thisNetwork, const OdTvDbObjectId& actionId, bool alsoEraseIt);

#if 0 // TODO: Nothing complex but needs time

  /** \details
    Adds an array of associated actions to be owned by this network.
  */
  OdResult addActions(const OdTvDbObjectIdArray& actionIds, bool alsoSetAsDatabaseOwner);

  /** \details
    Removes an array of associated actions from this network.
  */
  OdResult removeAllActions(bool alsoEraseThem);
#endif

  /** \details
    This method is called from the setStatus(..., true) method of the associated action and 
    notifies the network owing the action that the status has just been changed.
    \param pThisNetwork [in] associative network object owning this implementation object.
    \param pOwnedAction [in] the action owned by the network object which status is Changed.
    \param previousStatus [in] previous value of dependency status
  */
  OdResult ownedActionStatusChanged(OdTvDbObject* pThisNetwork, OdTvDbAssocAction* pOwnedAction, OdTvDbAssocStatus previousStatus);

  /** \details
    Reads the .dwg file data of this object. 

    \param pThisNetwork [in] associative network object owning this implementation object.
    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  OdResult dwgInFields(OdTvDbAssocAction *pThisNetwork, OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
    \param thisNetworkObjectId [in] object ID of associative network owning this implementation object
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId thisNetworkObjectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    \param thisNetworkObjectId [in] object ID of associative network owning this implementation object
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId thisNetworkObjectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
    \param thisNetworkObjectId [in] object ID of associative network owning this implementation object
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId thisNetworkObjectId) const;

  /** \details
    Sets the status of the network of associated actions.
    \param thisNetwork [in] associative network object owning this implementation object.
    \param newStatus [in] new value of assoc.status to set.
    \param notifyOwningNetwork [in] tels to call owning network's ownedActionStatusChanged.
    \param setInOwnedActions [in] tels to set the same status to owned actions if any.
  */
  OdResult setStatus(OdTvDbObject* thisNetwork,
                     OdTvDbAssocStatus newStatus,
                     bool notifyOwningNetwork,
                     bool setInOwnedActions);

  /** \details
    Evaluates the network of associated actions.
    \param pThisNetwork [in] associative network owning this implementation object
    \param pEvaluationCallback [in,callback] evaluation callback.
  */
  virtual void evaluate(OdTvDbAssocAction *pThisNetwork, OdTvDbAssocEvaluationCallback* pEvaluationCallback);

  /** \details
    \param pThisNetwork [in] action owning this implementation object
    \param pAuditInfo [in] context object for current audit operation.
    \sa
    * OdTvDbObject::audit()
  */
  virtual void audit(OdTvDbObject* pThisNetwork, OdTvDbAuditInfo* pAuditInfo);

  /** \details
    This callback appends this action to the specified owner object
    at the end of the deep and/or wblock clone operation.

    \param pThisNetwork [in] associative network owning this implementation object
    \param idPair [in]  Original-to-clone ID mapping record for this clone.
    \param pOwner [in]  Pointer to the owner object.
    \param idMap [in] id mapping object being used in of current cloning operation.

    \sa
    * OdTvDbAssocAction::appendToOwner()
  */
  virtual void appendToOwner(OdTvDbAssocAction* pThisNetwork, OdTvDbIdPair& idPair, OdTvDbObject* owner, OdTvDbIdMapping& idMap);

  /** \details
    \returns the evaluation priority of this associative network object.
  */
  virtual OdTvDbAssocEvaluationPriority evaluationPriority() const;
private:
  /*!DOM*/
  void auditEvaluationQueue(OdTvDbObject* pObj, OdTvDbAuditInfo* pAuditInfo);
  /*!DOM*/
  OdTvDbObjectIdArray       m_actions;
  /*!DOM*/
  OdArray<bool>           m_isOwnedAction;
protected:
  /*!DOM*/
  OdUInt32 m_maxChildActionIdx;
  /*!DOM*/
  virtual void fixStatusConsistency(OdTvDbAssocAction* self);
  /*!DOM*/
  bool m_fixStatusConsistency;

  /*!DOM*/
  friend void odaaFixStatusConsistencyOnce(OdTvDbAssocNetwork* action);
  /*!DOM*/
  friend void odaaEnableStatusConsistencyCheck(OdTvDbAssocNetwork* network, bool doIt);
private:
  /*!DOM*/
  OdTvDbObjectIdArray       m_actionsToEvaluate;

};

/*!DOM*/
void odaaEnableStatusConsistencyCheck(OdTvDbAssocNetwork* network, bool doIt = true);
/*!DOM*/
void odaaFixStatusConsistencyOnce(OdTvDbAssocNetwork* action);

#include "TD_PackPop.h"

#endif

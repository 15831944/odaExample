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

#ifndef DbAssocNetworkDeepCloneAux_INCLUDED_
#define DbAssocNetworkDeepCloneAux_INCLUDED_ /*!DOM*/

#include "TD_PackPush.h"

#define STL_USING_MAP
#define STL_USING_SET
#include "OdaSTL.h"

#include "DbIdMapping.h"
#include "DbObjectId.h"
#include "OdLinkedArray.h"
#include "DbObjectIterator.h"
#include "DbObjectReactor.h"
#include "OdHashSet.h"
#include "OdHashMap.h"
#include "OdPlatformSettings.h"
#include "DbBlockTableRecord.h"


class OdTvDbAssocAction;
class OdTvDbAssocNetwork;
class OdTvDbAssocDependency;
class OdTvDbAssocVariable;
typedef OdLinkedArray<OdTvDbObjectId> OdTvDbObjectIdLinkedArray;
typedef std::map<OdString, OdTvDbObjectId> OdString2IdMap;
typedef std::map<OdString, OdString> OdString2OdStringMap;

//DOM-IGNORE-BEGIN

class OdTvDbAssocVarCloneCtx
{
public:
  struct DataEntry
  {
    OdString m_srcName;
    OdString m_dstName;
    bool m_isCloned;
  };

  OdTvDbAssocVarCloneCtx() {}
  void addDestVariables(OdTvDbAssocNetwork* network);
  void addSourceVariables(OdTvDbAssocVariable* variable);

  bool addSourceVariable(const OdString& name);
  bool addDestVariable(const OdString& name);
  void recordVariableClone(const OdString& srcName, const OdString& dstName);

  const DataEntry* getEntryBySourceName(const OdString& srcName) const;
  const DataEntry* getEntryByDestName(const OdString& dstName) const;

  int destVariableCount() const;
  int clonedVariableCount() const;

private:
  typedef OdArray<DataEntry> Data;
  typedef std::map<OdString, Data::size_type> OdString2IdxMap;

  Data m_data;
  OdString2IdxMap m_forwardIndex;
  OdString2IdxMap m_invertedIndex;
};

//DOM-IGNORE-END

typedef OdHashSet<OdDbStub*, OdHashSet_PtrHasher<OdDbStub> > OdTvDbStubPtrHashSet;

/** \details
  This class implements the context object for assoc networks deep clone operations.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class OdTvDbAssocNetCloneCtx : public OdTvDbObjectReactor
{
protected:
  typedef OdHashMap<OdTvDbAssocNetwork*, OdTvDbAssocVarCloneCtx, OdHashSet_PtrHasher<OdTvDbAssocNetwork> > NetworkVariableIndex;
  OdTvDbIdMappingPtr idMap;
  OdTvDbStubPtrHashSet dependentOnObjectsCloned;
  OdTvDbStubPtrHashSet actionsToClone;
  OdTvDbObjectIdLinkedArray actionsToAppend;
  OdTvDbObjectIdLinkedArray actionsCloned;
  NetworkVariableIndex variableIndices;
  OdTvDbObjectId explodingBlockReferenceId;
  mutable OdGeMatrix3d actionXform;
  mutable bool bApplyTransform;
  OdTvDbAssocNetCloneCtx() { bApplyTransform = false; }
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocNetCloneCtx);

  /** \details
    Registries the deep clone reactor.
  */
  static void createAssocNetworkCloneReactors();

  /** \details
    Unregisters the deep clone reactor.
  */
  static void deleteAssocNetworkCloneReactors();

  /** \details
    Attaches new context data associating it with given OdTvDbDatabase
  */
  static void attach(OdTvDbIdMapping& idMap);

  /** \details
    Gets internal data associated with given database
  */
  static OdSmartPtr<OdTvDbAssocNetCloneCtx> fromDatabase(OdTvDbDatabase* destDb);

  /** \details
    Gets internal data associated with given database
  */
  static OdSmartPtr<OdTvDbAssocNetCloneCtx> internal_fromDb(OdTvDbDatabase* destDb);

  /** \details
    Detaches this context data associated with given database
  */
  static bool detach(OdTvDbDatabase* destDb);

  /** \details
    Gets IdMapping associated with current clone operation
  */
  OdTvDbIdMapping& idMapping();

  OdTvDbObjectIdLinkedArray& clonedActions();

  OdTvDbAssocVarCloneCtx& varCloneContext(OdTvDbAssocNetwork* destNetwork);

  void onBlockCloned(const OdTvDbBlockTableRecord& originalBlock);
  void onDependentObjectCloned(const OdTvDbObject& originalObject);

  /** \details
    Remembers an action from source database that was cloned.
  */
  void onActionCloned(const OdTvDbAssocAction* action);

  virtual void setActionTransform(const OdGeMatrix3d& transform);

  bool doApplyTransform() const { return bApplyTransform; }

  const OdGeMatrix3d& actionTransform() const;

  /** Description
    Calls addMoreObjectToDeepClone() for actions whose dependent-on objects were cloned .
  */
  void addMoreObjectsToDeepClone();

  /** Description
    Relinks dependency lists on cloned DB-objects that is be broken by deep clone operation when not all actions
    depended on a object were cloned.
  */
  void relinkDependenciesOnObjects();

  /** Description
    Appends cloned actions to its owners.
  */
  void appendActionsToOwners();

  /** Description
    Calls one of OdTvDbObject's methods on 'original', either deepClone() or wblockClone() depending on destination dabase value.
    if it's equal to original then deepClone() is callen and if it's not then calls wblockClone().
  */
  static bool cloneObject(OdTvDbIdMapping& idMap, const OdTvDbObject* original, OdTvDbObject* destOwner, OdTvDbObjectPtr* pClone = 0);

  static void lookupDestinationBlock(OdTvDbIdMapping& idMap, OdTvDbAssocAction* action, OdTvDbBlockTableRecordPtr& destBlock);

  static OdTvDbObjectPtr lookupActionCloneOwner(OdTvDbIdMapping& idMap, OdTvDbEntity* destActionEntity);

  static OdTvDbObjectPtr lookupActionCloneOwner(OdTvDbIdMapping& idMap, OdTvDbBlockTableRecord* destBlock);

  static OdTvDbObjectPtr lookupActionCloneOwner(OdTvDbIdMapping& idMap, OdTvDbAssocAction* action);
};

typedef OdSmartPtr<OdTvDbAssocNetCloneCtx> OdTvDbAssocNetCloneCtxPtr;


inline OdTvDbIdMapping& OdTvDbAssocNetCloneCtx::idMapping() { return *idMap; }

inline OdTvDbObjectIdLinkedArray& OdTvDbAssocNetCloneCtx::clonedActions() { return actionsCloned; }

inline OdTvDbAssocNetCloneCtxPtr OdTvDbAssocNetCloneCtx::fromDatabase(OdTvDbDatabase* destDb) {
  return static_cast<OdTvDbAssocNetCloneCtx*>(OdTvDbObjectReactor::findReactor(destDb, ::odrxGetClassDesc(L"OdTvDbAssocNetCloneCtx")));
}

inline OdTvDbAssocNetCloneCtxPtr OdTvDbAssocNetCloneCtx::internal_fromDb(OdTvDbDatabase* destDb) {
  return static_cast<OdTvDbAssocNetCloneCtx*>(OdTvDbObjectReactor::findReactor(destDb, OdTvDbAssocNetCloneCtx::desc()));
}

inline const OdGeMatrix3d& OdTvDbAssocNetCloneCtx::actionTransform() const {
  return actionXform;
}

inline void OdTvDbAssocNetCloneCtx::setActionTransform(const OdGeMatrix3d& xform) {
  actionXform = xform;
  bApplyTransform = !xform.isEqualTo(OdGeMatrix3d::kIdentity, OdGeTol(OdGeContext::gZeroTol));
}


inline OdTvDbObjectId odtvdbTranslate(OdTvDbObjectId id, OdTvDbIdMapping &idMap) {
  OdTvDbIdPair idPair(id);
  if(idMap.compute(idPair))
    return idPair.value();
  return OdTvDbObjectId::kNull;
}

inline OdTvDbObjectId odtvdbTranslateCloned(OdTvDbObjectId id, OdTvDbIdMapping &idMap) {
  OdTvDbIdPair idPair(id);
  if (idMap.compute(idPair) && idPair.isCloned())
    return idPair.value();
  return OdTvDbObjectId::kNull;
}


#include "TD_PackPop.h"

#endif

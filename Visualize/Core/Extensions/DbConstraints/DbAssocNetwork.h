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

#ifndef DbAssocNetwork_INCLUDED_
#define DbAssocNetwork_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAssocAction.h"

#include "TD_PackPush.h"

/** \details
  This class represents the network of associated actions.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocNetwork : public OdTvDbAssocAction
{
public: 
    ODRX_DECLARE_MEMBERS(OdTvDbAssocNetwork);

    /** \details
      Constructor creates an instance of this class.
    */
    explicit OdTvDbAssocNetwork();

    /** \details
      \returns array of object IDs of owned actions.
    */
    OdTvDbObjectIdArray getActions() const;

    /** \details
      Adds the action to be owned by this network using its ID.
      \param actionId [in] object ID of the action to add to network object
      \param alsoSetAsDatabaseOwner [in] if true this network object will be set also as database owner of the action.
    */
    OdResult addAction(const OdTvDbObjectId& actionId, bool alsoSetAsDatabaseOwner);

    /** \details
      Removes the associated action from this network using its ID.
      \param actionId [in] object ID of the action to bee removed
      \param alsoEraseIt [in] if true the action will be erased.
    */
    OdResult removeAction(const OdTvDbObjectId& actionId, bool alsoEraseIt);

    /** \details
      \returns array of actions marked to be evaluated.
    */
    OdTvDbObjectIdArray getActionsToEvaluate() const;

    /** \details
      After loading from file, performs necessary actions which require accessing other Database objects.
      For example, processing round-trip data.

      \param format [in]  File type.
      \param version [in]  Drawing version of file loaded.
      \param pAuditInfo [in]  Pointer to an OdTvDbAuditInfo object. Can be Null. Not Null if drawing is being loaded in Recover mode.
      If so, audit() will be called later.
      \sa
      * OdTvDbObject::composeForSave()
    */
    virtual void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

    /** \details
      Determines the behavior for custom objects when saving to .dwg or .dxf file.
      \param ver [in]  Drawing version to save as.
      \param replaceId [out]  Object ID of the object replacing this object.
      \param exchangeXData [out]  Set to true if and only if this function did not add XData to the replacement object.
      \sa
      * OdTvDbObject::decomposeForSave()
    */
    virtual OdTvDbObjectPtr decomposeForSave(OdDb::DwgVersion ver, OdTvDbObjectId& replaceId, bool& exchangeXData);

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
      \param pOwnedAction [in] action object owned by this network that is changes.
      \param previousStatus [in] the assoc.status of the action before it is changed.
    */
    OdResult ownedActionStatusChanged(OdTvDbAssocAction* pOwnedAction, OdTvDbAssocStatus previousStatus);

    /** \details
      Returns an object ID of the associated network owned by the given database. 
      It optionally creates a new instance if it does not exist yet. 
    */
    static OdTvDbObjectId getInstanceFromDatabase(OdTvDbDatabase*   pDatabase,
                                                bool            createIfDoesNotExist,
                                                const OdString& dictionaryKey = L"");

    /** \details
      Returns an object ID of the associated network owned by the extension dictionary 
      of the given object. It optionally creates a new sub-dictionary and a new network 
      if they do not exist yet.
      \param owningObjectId [in] object ID of the object to take assoc.network from.
      \param createIfDoesNotExist [in] tells to create network if one is not exists.
      \param addToTopLevelNetwork [in] tells to add the link to created network to top level network.
      \param dictionaryKey [in] tells to use this non-standard dictionary key to add created network.
    */
    static OdTvDbObjectId getInstanceFromObject(const OdTvDbObjectId& owningObjectId,
                                              bool                createIfDoesNotExist,
                                              bool                addToTopLevelNetwork = true,
                                              const OdString&     dictionaryKey        = L"");

    /** \details
      Removes the network and sub-dictionary which owns it from the extension dictionary of the object. 
      \param owningObjectId [in] object ID of the object to take assoc.network from.
      \param alsoEraseIt [in] tells to erase removed network.
      \param dictionaryKey [in] non-standard dictionary key where to lookup network to remove.
    */
    static OdResult removeInstanceFromObject(const OdTvDbObjectId& owningObjectId,
                                             bool                alsoEraseIt,
                                             const OdString&     dictionaryKey = L"");

    /** \details
      Removes the network and sub-dictionary which owns it from the named object dictionary of the database. 
      \param owningObjectId [in] object ID of the object to take assoc.network from.
      \param alsoEraseIt [in] tells to erase removed network.
      \param dictionaryKey [in] non-standard dictionary key where to lookup network to remove.
    */
    static OdResult removeInstanceFromDatabase(OdTvDbDatabase*   pDatabase,
                                               bool            alsoEraseIt,
                                               const OdString& dictionaryKey = L"");

    /** \details
      \sa OdTvDbObject::subDeepClone()
    */
    virtual OdTvDbObjectPtr subDeepClone(OdTvDbIdMapping& idMap, OdTvDbObject* owner, bool primary) const;

    /** \details
      \sa OdTvDbObject::subWblockClone()
    */
    virtual OdTvDbObjectPtr subWblockClone(OdTvDbIdMapping& idMap, OdTvDbObject* owner, bool primary) const;

    /** \details
      \sa OdTvDbObject::subErase()
    */
    virtual OdResult subErase(bool erasing);

};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocNetwork class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocNetwork> OdTvDbAssocNetworkPtr;

#include "TD_PackPop.h"

#endif

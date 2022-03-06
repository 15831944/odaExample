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

#ifndef DbAssocArrayActionBody_INCLUDED_
#define DbAssocArrayActionBody_INCLUDED_ /*!DOM*/

#include "DbAssocParamBasedActionBody.h"
#include "DbAssocArrayParameters.h"

#include "TD_PackPush.h"

/** \details
  This class represents an array of associated actions which can be evaluated to manage or locate the items.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocArrayActionBody : public OdTvDbAssocParamBasedActionBody
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocArrayActionBody);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocArrayActionBody(bool createImpObj = true);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbAssocArrayActionBody();

  /** \details
    Returns a pointer to the array of parameters for writing.
  */
  const OdTvDbAssocArrayParametersPtr parameters() const;
  
  /** \details
    Returns a pointer to the array of parameters for writing.
  */
  OdTvDbAssocArrayParametersPtr& parameters();


  virtual void composeForLoad(OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

  /** \details
    Provides the standard audit protocol.
  */
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);

  /** \details
    Switches the erase/unerase status for an item at given index.
  */
  OdResult deleteItem(const OdTvDbItemLocator& index, bool bErase = true);
  
  /** \details
    Performs a relative transformation to the item at the given index.
  */
  OdResult transformItemBy(const OdTvDbItemLocator& index,
                           const OdGeMatrix3d& xform);

  /** \details
    Gets the indices of all items which are owned by this array.
  */
  void getItems(OdArray<OdTvDbItemLocator>& indices, 
                bool skipErased = true) const;
  
  /** \details
    Gets the item at the given subent path.
  */
  const OdTvDbAssocArrayItemPtr getItemAt(const OdTvDbItemLocator& index, 
                                      OdTvDbFullSubentPath& path) const;
                                      
  /** \details
    Gets the item at the given subent path.
  */                                    
  const OdTvDbAssocArrayItemPtr getItemAt(const OdTvDbItemLocator& index) const;

  /** \details
    Gets the item at the given subent path.
  */
  const OdTvDbAssocArrayItemPtr getItemAt(const OdTvDbFullSubentPath& path) const;

  /** \details
    This is the notification call of the corresponding evaluate() method 
    of the parent class that owns this action body.
  */
  virtual void evaluateOverride();
  
  /** \details
    Gets the object ID of the associated array which this action controlls.
  */
  virtual OdTvDbObjectId getArrayEntity() const;
  
  /** \details
    Checks whether an item of an associated array can be controlled either by created action 
    or by another action which modifies this item.
  */
  virtual bool controlsItem(const OdTvDbItemLocator &index) const;

  /** \details
    Applies the transformation matrix to the array.
  */
  virtual OdResult transformBy(const OdGeMatrix3d& xform);
  
  /** \details
    Returns the transformation matrix.
  */
  virtual OdGeMatrix3d getTransform() const;

  /** \details
    Returns an array of object IDs of source entities for this action.
  */
  OdTvDbObjectIdArray getSourceEntities() const;

  /** \details
    Adds an entity specified by a given object ID to the list of source items and 
    updates each item in the array which this action controlls.
  */
  OdResult addSourceEntity(OdTvDbObjectId entity, 
                           const OdGePoint3d& basePoint);

  /** \details
    Removes an entity specified by a given object ID from the list of source items and 
    updates each item in the array which this action controlls.
  */
  OdResult removeSourceEntity(OdTvDbObjectId entity);

  /** \details
    Sets the base point for source objects.
  */
  OdResult setSourceBasePoint(const OdTvDbVertexRef& basePoint);

  /** \details
    Gets the base point of source objects.
  */
  OdResult getSourceBasePoint(OdTvDbVertexRef& vertexRef,
                              OdGePoint3d& position) const;
  /** \details
    Checks that the entity is an associative array.
  */
  static bool isAssociativeArray(const OdTvDbEntity* pEntity);
  /** \details
    Get object ID of array action body manage this item.
  */
  static OdTvDbObjectId getControllingActionBody(const OdTvDbEntity* pEntity,
                                               const OdTvDbItemLocator* pItemIndex = NULL);
  /** \details
    Removes associativity. Each array item is extracted as individual items. 
  */
  static OdResult explode(OdTvDbEntity* pEntity, OdTvDbObjectIdArray& newIds );
  /** \details
    Removes item transformation.
  */
  static OdResult resetArrayItems(OdTvDbObjectId arrayEntityId,
                                  const OdArray<OdTvDbItemLocator>& indices, 
                                  bool resetAll = false);
  /** \details
    Get list of indexes for input list of FullSubentPath of items.
  */
  static OdResult getArrayItemLocators(const OdTvDbFullSubentPathArray& subents, 
                                       OdArray<OdTvDbItemLocator>& indices);
  /** \details
    Creates associative array: action, action body, dependencies etc.
  */
  static OdResult createInstance( const OdTvDbObjectIdArray& sourceEntites, 
                                  OdTvDbVertexRef& basePoint, 
                                  const OdTvDbAssocArrayParametersPtr &pParameters, 
                                  OdTvDbObjectId& arrayId, 
                                  OdTvDbObjectId& actionBodyId);
  /** \details
    Returns an object ID of the owning block table record for source items.
  */
  OdTvDbObjectId getArraySourceBTR() const;

  /** \details
     This is the notification call of the corresponding method 
     of the parent class that owns this action body.
  */
  virtual OdResult dragStatusOverride(const OdDb::DragStat status);

  virtual OdResult postProcessAfterDeepCloneOverride(OdTvDbIdMapping& idMap);

  virtual OdResult isRelevantDependencyChangeOverride(const OdTvDbAssocDependency* pDependency, bool& isRelevantDepChange) const override;

};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocArrayActionBody class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocArrayActionBody> OdTvDbAssocArrayActionBodyPtr;

///** { Secret } */ // TODO
void DBCONSTRAINTS_EXPORT odrxAssocArrayAdjustLocation(OdTvDbObjectId arrayId, const OdTvDbAssocArrayParametersPtr& pParameters);

///** { Secret } */
enum AssocArraySkipOdaSpecificFlags {
  kSkip_None = 0,
  kSkip_TransformToZero = 1,
  kSkip_EraseSourceEntities = 2,

  kSkip_Default = kSkip_None
};
///** { Secret } */
OdUInt32 DBCONSTRAINTS_EXPORT OdTvDbAssocArrayActionBody_setSkipNextFlags(OdUInt32 flags); // for tests only

#include "TD_PackPop.h"

#endif


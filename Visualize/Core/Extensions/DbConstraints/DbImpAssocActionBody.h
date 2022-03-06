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
#ifndef DbImpAssocActionBody_INCLUDED_
#define DbImpAssocActionBody_INCLUDED_ /*!DOM*/

#include "DbConstraintsExports.h"
#include "DbAssocGlobal.h"
#include "DbAssocArrayParameters.h"
#include "DbObject.h"
#include "SharedPtr.h"
#include "DbEvalVariant.h"
#include "DbAssocAction.h"
#include "TD_PackPush.h"
#include "DbViewport.h"

// attention : there is no accordant OdTvDbValueParam

/** \details
  This class represents the custom implementation of the value parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpValueParam 
{
public:
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpValueParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpValueParam();

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

  const OdString& name() const {return m_sName;}
  void setName(const OdString& sName) {m_sName = sName;}

  OdValue::UnitType unitType() const {return m_UnitType;}
  void setUnitType(OdValue::UnitType val) {m_UnitType = val;}

  OdTvDbEvalVariantPtr value() const {return m_value;}
  void setValue(const OdTvDbEvalVariant& Val);

  OdTvDbObjectId controlledObjectDepId() const {return m_ControlledObjectDepId;}
  void setControlledObjectDepId(OdTvDbObjectId id) {m_ControlledObjectDepId = id;}

  OdTvDbObjectIdArray inputVariablesIds() const {return m_InputVariablesIds;}
  void setInputVariablesIds(OdTvDbObjectIdArray vars) {m_InputVariablesIds = vars;}

  virtual OdStringArray compareWith(const OdTvDbImpValueParam *paramIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;
protected:
  /*!DOM*/
  OdString m_sName;
  /*!DOM*/
  OdValue::UnitType m_UnitType;
  /*!DOM*/
  OdTvDbEvalVariantPtr m_value;
  /*!DOM*/
  OdTvDbObjectId      m_ControlledObjectDepId;
  OdTvDbObjectIdArray m_InputVariablesIds;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbImpValueParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSharedPtr<OdTvDbImpValueParam> OdTvDbImpValueParamPtr;


/** \details
  This class represents the custom implementation of the action body.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocActionBody
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocActionBody();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocActionBody();

  virtual OdResult dependentObjectClonedOverride(OdTvDbAssocActionBody* thisBody,
    const OdTvDbAssocDependency* dependency, const OdTvDbObject* original, const OdTvDbObject* clone);

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
    Base implementation of the corresponding 'Override' method of the OdTvDbAssocActionBody
    which owns this implementation object.

    \sa
    OdTvDbAssocActionBody::addMoreObjectsToDeepCloneOverride()
    OdTvDbAssocAction::addMoreObjectsToDeepClone()

    \returns eNotImplemented by default
  */
  virtual OdResult addMoreObjectsToDeepCloneOverride(const OdTvDbAssocActionBody* thisBody,
    OdTvDbIdMapping& idMap, OdTvDbObjectIdArray& additionalObjectsToClone) const { return eNotImplemented; }

  /** \details
    Creates action and action body, add it to db.
  */
  static OdResult createActionAndActionBodyAndPostToDatabase( OdRxClass* pActionBodyClass, const OdTvDbObjectId& objectId, 
    OdTvDbObjectId& createdActionId, OdTvDbObjectId& createdActionBodyId);

  virtual OdStringArray compareWith(OdTvDbImpAssocActionBody *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;

  OdTvDbObjectIdArray m_arrParams;
  OdArray<OdTvDbImpValueParamPtr> m_arrValueParams;
protected:
  OdUInt32 m_dwgVersion;

  OdTvDbEntityPtr checkAccompanying(OdTvDbObjectId parentActionId, OdTvDbAssocAction* pAction);
  /** \details
  Gets the object ID of the associated array which this action controlls.
  */
  virtual OdTvDbObjectId getArrayEntity(OdTvDbObjectId parentActionId) const;
  OdTvDbObjectId entityInsert(OdTvDbObjectId parentActionId) const { return getArrayEntity(parentActionId); }
  //static void transformPositionByViewPort(OdTvDbViewportPtr& pViewport, OdGePoint3d& blPosition);

  friend class OdTvDbImpAssocAction;
  friend class OdTvDbImpSmartCenterActionBody;
  friend class OdTvDbCenterMarkActionBody;
  
  //OdTvDbObjectIdArray m_arrParams;
};


/** \details
  This class represents the custom implementation of the associated parameter of the action body.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocParamBasedActionBody : public OdTvDbImpAssocActionBody
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocParamBasedActionBody();
  OdTvDbImpAssocParamBasedActionBody(bool notparent);
  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocParamBasedActionBody();

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
  OdTvDbObjectId& assocDependencyID() { return m_assocDependencyID; }
  virtual OdStringArray compareWith(OdTvDbImpAssocActionBody *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;

protected:
  /*!DOM*/
  friend class OdTvDbImpAssocAction;
  /*!DOM*/
  //OdTvDbObjectIdArray m_arrParams;
  /*!DOM*/
  //OdArray<OdTvDbImpValueParamPtr> m_arrValueParams;
private:
  OdUInt32 m_undefined1;
  OdUInt32 m_undefined2;
  OdUInt32 m_undefined3;
  OdUInt32 m_undefined4;
  OdTvDbObjectId m_assocDependencyID;
  bool m_notParent;
};

/** \details
  This class represents the custom implementation of the array of the associated parameter of the action body.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayActionBody : public OdTvDbImpAssocParamBasedActionBody
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayActionBody();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayActionBody();

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

  void composeForLoad( OdTvDbObject *pObject, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

  /** \details
    Provides the standard audit protocol.
  */
  virtual void audit( OdTvDbObject* pObj, OdTvDbAuditInfo* pAuditInfo );

  /** \details
    This is the notification call of the corresponding evaluate() method 
    of the parent class that owns this action body.
  */
  virtual void evaluateOverride( OdTvDbObjectId parentActionId );

  /** \details
    Returns a pointer to the array of parameters for writing.
  */
  const OdTvDbAssocArrayParametersPtr parameters() const;
  
  /** \details
    Returns a pointer to the array of parameters for writing.
  */
  OdTvDbAssocArrayParametersPtr& parameters();
  /** \details
    Switches the erase/unerase status for an item at given index.
  */
  OdResult deleteItem(const OdTvDbItemLocator& index, bool bErase);  
  /** \details
    Gets the item at the given subent path.
  */
  const OdTvDbAssocArrayItem* getItemAt( const OdTvDbItemLocator& index,
                                       OdTvDbFullSubentPath& path,
                                       OdTvDbObjectId arrayId ) const;
  /** \details
    Performs a relative transformation to the item at the given index.
  */
  OdResult transformItemBy(const OdTvDbItemLocator& index, const OdGeMatrix3d& xform);
  /** \details
    Gets the indices of all items which are owned by this array.
  */
  void getItems(OdArray<OdTvDbItemLocator>& indices, bool skipErased) const;
  /** \details
    Gets the item at the given subent path.
  */
  const OdTvDbAssocArrayItem* getItemAt(const OdTvDbFullSubentPath& path) const;
  /** \details
    Creates associative array: action, action body, dependencies etc.
  */
  static OdResult createInstance( const OdTvDbObjectIdArray& sourceEntites, 
                                  OdTvDbVertexRef& basePoint, 
                                  const OdTvDbAssocArrayParametersPtr &pParameters, 
                                  OdTvDbObjectId& arrayId, 
                                  OdTvDbObjectId& actionBodyId);
  /** \details
    Get object ID of array action body manage this item.
  */
  static OdTvDbObjectId getControllingActionBody( const OdTvDbEntity* pEntity, 
                                                const OdTvDbItemLocator* pItemIndex = NULL );
  /** \details
    Checks that the entity is an associative array.
  */
  static bool isAssociativeArray( const OdTvDbEntity* pEntity );
  /** \details
    Removes item transformation.
  */
  static OdResult resetArrayItems( OdTvDbObjectId arrayEntityId,
                                   const OdArray<OdTvDbItemLocator>& indices, 
                                   bool resetAll = false);
  /** \details
    Removes associativity. Each array item is extracted as individual items. 
  */
  static OdResult explode( OdTvDbEntity* pEntity, OdTvDbObjectIdArray& newIds );

  /** \details
    Applies the transformation matrix to the array.
  */
  OdResult transformBy(const OdGeMatrix3d& xform);
  /** \details
    Returns the transformation matrix.
  */
  OdGeMatrix3d getTransform() const;
  /** \details
    Returns an object ID of the owning block table record for source items.
  */
  OdTvDbObjectId getArraySourceBTR( OdTvDbObjectId parentActionId ) const;

  /** \details
    Gets the object ID of the associated array which this action controlls.
  */
  virtual OdTvDbObjectId getArrayEntity( OdTvDbObjectId parentActionId ) const;

  /** \details
    Checks whether an item of an associated array can be controlled either by created action 
    or by another action which modifies this item.
  */
  virtual bool controlsItem(const OdTvDbItemLocator& index) const;
  /** \details
    Returns an array of object IDs of source entities for this action.
  */
  OdTvDbObjectIdArray getSourceEntities( OdTvDbObjectId parentActionId ) const;
  /** \details
    Adds an entity specified by a given object ID to the list of source items and 
    updates each item in the array which this action controlls.
  */
  OdResult addSourceEntity( OdTvDbObjectId entity, const OdGePoint3d& basePoint, OdTvDbObjectId parentActionId );
  /** \details
    Removes an entity specified by a given object ID from the list of source items and 
    updates each item in the array which this action controlls.
  */
  OdResult removeSourceEntity( OdTvDbObjectId entity, OdTvDbObjectId parentActionId );
  /** \details
    Sets the base point for source objects.
  */
  OdResult setSourceBasePoint( const OdTvDbVertexRef& basePoint, const OdTvDbObjectId &parentActionId );

  /** \details
    Gets the base point of source objects.
  */
  OdResult getSourceBasePoint( OdTvDbVertexRef& vertexRef, OdGePoint3d& position ) const;

  static OdResult getArrayItemLocators( const OdTvDbFullSubentPathArray& subents, OdArray<OdTvDbItemLocator>& indices );
  
  OdResult addMoreObjectsToDeepCloneOverride( const OdTvDbAssocActionBody *pBody,
                                              OdTvDbIdMapping& idMap, 
                                              OdTvDbObjectIdArray& additionalObjectsToClone) const;

  OdTvDbBlockTableRecordPtr getSourceBTR( const OdTvDbObjectId &parentActionId ) const;
  OdTvDbBlockTableRecordPtr getSourceBTR( const OdTvDbObjectId &parentActionId );

protected:
  /*!DOM*/
  OdTvDbAssocArrayParametersPtr m_pParams; 
  /* Transformation matrix of the array.*/
  OdGeMatrix3d m_matrix;

  inline OdResult getItem( OdTvDbAssocArrayItemPtr &pItem, const OdTvDbItemLocator& index ) const;
};

class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayModifyActionBody : public OdTvDbImpAssocArrayActionBody
{
public:
  
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayModifyActionBody();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayModifyActionBody();

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

  void composeForLoad( OdTvDbObject *pObject, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

  /** \details
    Get indices of overridden items.
  */
  OdResult getOverridenItems( OdArray<OdTvDbItemLocator> &indices ) const;
  
  /** \details
    Set indices of overridden items.
  */
  OdResult setOverridenItems( const OdArray<OdTvDbItemLocator> &indices);

  /** \details
    Checks whether an item of an associated array can be controlled either by created action 
    or by another action which modifies this item.
  */
  virtual bool controlsItem(const OdTvDbItemLocator& index) const;
  
  /** \details
    Modify array: add new action, action body, dependencies etc.
  */
  static OdResult createInstance( OdTvDbObjectId arrayId, 
                                  const OdArray<OdTvDbItemLocator> &indices,
                                  const OdTvDbObjectIdArray &subEnt,
                                  OdTvDbVertexRef &basePoint,
                                  OdTvDbObjectId& actionBodyId);

  /** \details
    This is the notification call of the corresponding evaluate() method 
    of the parent class that owns this action body.
  */
  virtual void evaluateOverride( OdTvDbObjectId parentActionId );

  /** \details
    Gets the object ID of the associated array which this action controlls.
  */
  virtual OdTvDbObjectId getArrayEntity( OdTvDbObjectId parentActionId ) const;

  virtual OdResult addMoreObjectsToDeepCloneOverride(const OdTvDbAssocActionBody* thisBody,
    OdTvDbIdMapping& idMap, OdTvDbObjectIdArray& additionalObjectsToClone) const;

private:

  OdArray<OdTvDbItemLocator> m_indices;

  void restoreSrcPosition( OdTvDbAssocAction* pParentAction );
 
};


#include "TD_PackPop.h"

#endif

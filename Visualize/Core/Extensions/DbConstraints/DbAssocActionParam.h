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

#ifndef DbAssocActionParam_INCLUDED_
#define DbAssocActionParam_INCLUDED_ /*!DOM*/

#include "DbAssocAction.h"
#include "DbCompoundObjectId.h"
#include "DbGeomRef.h"

#include "TD_PackPush.h"

/** \details
  This class implements the action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocActionParam : public OdTvDbObject
{
public:     
  ODRX_DECLARE_MEMBERS(OdTvDbAssocActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocActionParam(bool createImpObj = true);

  /** \details
    Destructor destroys an instance of this class.
  */
  ~OdTvDbAssocActionParam();

  /** \details
    Returns the parameter name.
  */
  const OdString& name() const;

  /** \details
    Sets the parameter name.
  */
  virtual OdResult setName(const OdString& newName);

  /** \details
    Makes empty the parameter.
  */
  virtual OdResult makeParamEmpty(bool alsoEraseOwnedObjects);

  /** \details
    Makes constant the parameter.
  */
  virtual OdResult makeParamConstant();

  /** \details
    Applies the transformation matrix to the constraint geometry.
  */
  virtual OdResult transformConstantGeometry(const OdGeMatrix3d& transform);

  /** \details
    Returns an object ID of the parent action. 
  */
  OdTvDbObjectId parentAction() const;

  /** \details
    Detaches the dependencies of this action. 
  */
  virtual OdResult detachDependencies();

  /** \details
    Gets the dependencies of this action. 
  */
  virtual OdResult getDependencies(bool readDependenciesWanted, 
                                   bool writeDependenciesWanted,
                                   OdTvDbObjectIdArray& dependencyIds) const;

  /** \details
    Gets an array of IDs of the compound object for this action. 
  */
  OdResult getCompoundObjectIds(bool readDependenciesWanted, 
                                bool writeDependenciesWanted,
                                OdArray<OdTvDbCompoundObjectId>& compoundObjectIds) const;

  /** \details
    Returns the current status of this action. 
  */
  OdTvDbAssocStatus status(bool alsoCheckDependencies) const;

  /** \details
    Sets the status for this action. 
  */
  OdResult setStatus(OdTvDbAssocStatus newStatus, 
                     bool notifyParentAction = true, 
                     bool setInOwnedParams = false);

  /** \details
    Audits the associative data sets. 
  */
  virtual void auditAssociativeData(OdTvDbAssocStatus& parentActionHandling);

  //virtual void collectPersSubentNamingDataOverride(OdTvDbPersStepIdArray& stepIds, 
  //                                                 OdTvDbPersSubentIdArray& persSubentIds) const;
  //virtual void clonePersSubentNamingDataOverride(OdTvDbAssocPersSubentManagerCloner* pCloner);

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
  Gets the compounded object.
  */
  OdResult getObject(OdTvDbCompoundObjectId& object) const;

  /** \details
    Deprecated.
  */
  OdResult getObject(OdTvDbCompoundObjectId* object) const {
    return getObject(*object);
  }

  /** \details
  Sets the compounded object.
  */
  OdResult setObject( //OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId& object,
    bool isReadDependency = true,
    bool isWriteDependency = false);

  /** \details
  Sets the compounded object.
  */
  OdResult setObjectOnly(const OdTvDbCompoundObjectId& object,
    bool isReadDependency, // = true
    bool isWriteDependency // = false
    );

  /** \details
    Deprecated.
  */
  OdResult setObjectOnly(const OdTvDbCompoundObjectId* object,
    bool isReadDependency, // = true
    bool isWriteDependency // = false
    )
  {
    return setObjectOnly(*object, isReadDependency, isWriteDependency);
  }

  /** \details
    Deprecated.
  */
  OdResult setObject( //OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId* object,
    bool isReadDependency = true,
    bool isWriteDependency = false)
  {
    return setObject(*object, isReadDependency, isWriteDependency);
  }

  virtual OdStringArray compareWith(const OdTvDbObjectId paramIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;
protected:
  /*!DOM*/
  class OdTvDbImpAssocActionParam* m_pImpObj;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocActionParam> OdTvDbAssocActionParamPtr;


/** \details
  This class implements the body action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocAsmBodyActionParam : public OdTvDbAssocActionParam 
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocAsmBodyActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocAsmBodyActionParam(bool createImpObj = true);

  /** \details
    Sets the body for this action.
  */
  virtual OdResult setBody(const OdTvDbEntity* pAsmEntity, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);
  
  /** \details
    Sets the body for this action.
  */
  virtual OdResult setBody(OdTvDbObjectId asmEntityId, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);
  
  /** \details
    Sets the body for this action.
  */
  virtual OdResult setBody(void* pAsmBody, bool makeCopy); 

  /** \details
    Returns the body or its duplicate from this action.
  */
  virtual void* body(bool makeCopy) const;

  /** \details
    Gets an ID of the compounded object this action.
  */
  OdResult getDependentOnCompoundObject(OdTvDbCompoundObjectId& compoundId) const;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocAsmBodyActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocAsmBodyActionParam> OdTvDbAssocAsmBodyActionParamPtr;


/** \details
  This class implements the compounded action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocCompoundActionParam : public OdTvDbAssocActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocCompoundActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocCompoundActionParam(bool createImpObj = true);

  /** \details
    Removes all parameters and optional erases them.
  */
  virtual OdResult removeAllParams(bool alsoEraseThem);

  /** \details
    Returns the number of parameters.
  */
  int paramCount() const;

  /** \details
    Returns the object ID of owned parameters.
  */
  const OdTvDbObjectIdArray& ownedParams() const;

  /** \details
    Adds a parameter using an object ID and index.
  */
  OdResult addParam(const OdTvDbObjectId& paramId, int& paramIndex);

  /** \details
    Removes the parameter using its object ID and optional erases it.
  */
  OdResult removeParam(const OdTvDbObjectId& paramId, bool alsoEraseIt); 

  /** \details
    Returns an array of object ID of parameters using the parameter name.
  */
  OdTvDbObjectIdArray paramsAtName(const OdString& paramName) const;

  /** \details
    Returns an object ID of the parameter using its name and index.
  */
  OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;

  /** \details
    Returns an object ID of the parameter using its index.
  */
  OdTvDbObjectId paramAtIndex(int paramIndex) const;

  /** \details
  Creates and adds a new parameter.
  */
  OdResult addChildParam(const OdTvDbObjectId actionId, const OdString& paramName, OdRxClass* pParamClass, const OdTvDbObjectId anchorId, OdTvDbObjectId& paramId, int& paramIndex);
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocCompoundActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocCompoundActionParam> OdTvDbAssocCompoundActionParamPtr;


/** \details
  This class implements the edge action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocEdgeActionParam : public OdTvDbAssocActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocEdgeActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocEdgeActionParam(bool createImpObj = true);

  /** \details
    Sets the edge reference.
  */
  virtual OdResult setEdgeRef(const OdTvDbEdgeRef& edgeRef, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

  /** \details
    Gets the edge reference.
  */
  virtual OdResult getEdgeRef(OdArray<OdTvDbEdgeRef>& edgeRefs) const;

  /** \details
    Sets the edge subentity geometry.
  */
  virtual OdResult setEdgeSubentityGeometry(const OdGeCurve3d* pNewEdgeCurve);

  /** \details
    Gets an ID of the compounded object this action.
  */
  OdResult getDependentOnCompoundObject(OdTvDbCompoundObjectId& compoundId) const;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocEdgeActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocEdgeActionParam> OdTvDbAssocEdgeActionParamPtr;


/** \details
  This class implements the face action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocFaceActionParam : public OdTvDbAssocActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocFaceActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocFaceActionParam(bool createImpObj = true);

  /** \details
    Sets the face reference.
  */
  virtual OdResult setFaceRef(const OdTvDbFaceRef& faceRef, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

  /** \details
    Gets the face reference.
  */
  virtual OdResult getFaceRef(OdArray<OdTvDbFaceRef>& faceRefs) const;

  /** \details
    Sets the face subentity geometry.
  */
  virtual OdResult setFaceSubentityGeometry(const OdGeSurface* pNewFaceSurface);

  /** \details
    Gets an ID of the compounded object this action.
  */
  OdResult getDependentOnCompoundObject(OdTvDbCompoundObjectId& compoundId) const;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocFaceActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocFaceActionParam> OdTvDbAssocFaceActionParamPtr;


/** \details
This class implements the face action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocTrimmingBodyActionParam  : public OdTvDbAssocFaceActionParam
{
public:
	ODRX_DECLARE_MEMBERS(OdTvDbAssocTrimmingBodyActionParam);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbAssocTrimmingBodyActionParam(bool createImpObj = true);

};

/** \details
The typified smart pointer. This template class is specialization of the OdSmartPtr class
for the OdTvDbAssocFaceActionParam class.

\sa
<link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocTrimmingBodyActionParam> OdTvDbAssocTrimmingBodyActionParamPtr;
/** \details
  This class implements the object action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocObjectActionParam : public OdTvDbAssocActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocObjectActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocObjectActionParam(bool createImpObj = true);

  /** \details
    Gets the compounded object.
  */
  OdResult getObject(OdTvDbCompoundObjectId* object) const;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocObjectActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocObjectActionParam> OdTvDbAssocObjectActionParamPtr;


/** \details
  This class implements the vertex action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocVertexActionParam : public OdTvDbAssocActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocVertexActionParam);

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocVertexActionParam(bool createImpObj = true);

  /** \details
    Sets the vertex reference.
  */
  virtual OdResult setVertexRef(const OdTvDbVertexRef& vertexRef, bool isReadDependency = true, bool isWriteDependency = false, int dependencyOrder = 0);

  /** \details
    Gets the vertex reference.
  */
  OdResult getVertexRef(OdTvDbVertexRef& vertexRef) const;

  /** \details
    Gets an array of vertex references.
  */
  virtual OdResult getVertexRef(OdArray<OdTvDbVertexRef>& vertexRefs) const;

  /** \details
    Sets the vertex subentity geometry.
  */
  virtual OdResult setVertexSubentityGeometry(const OdGePoint3d& newPosition);

  /** \details
    Gets an ID of the compounded object this action.
  */
  OdResult getDependentOnCompoundObject(OdTvDbCompoundObjectId& compoundId) const;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocVertexActionParam class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocVertexActionParam> OdTvDbAssocVertexActionParamPtr;

/////////////////////////////////////////////////////////////////////////////////////////////////////

/** \details
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocPointRefActionParam : public OdTvDbAssocCompoundActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocPointRefActionParam);

  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbAssocPointRefActionParam(bool createImpObj = true);
};

typedef OdSmartPtr<OdTvDbAssocPointRefActionParam> OdTvDbAssocPointRefActionParamPtr;

/** \details
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocOsnapPointRefActionParam : public OdTvDbAssocPointRefActionParam
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbAssocOsnapPointRefActionParam);

  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbAssocOsnapPointRefActionParam(bool createImpObj = true);

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
  Gets the compounded object.
  */

  void setOsnapMode(OdDb::OsnapMode mode);
  void setParam(double param);
};

typedef OdSmartPtr<OdTvDbAssocOsnapPointRefActionParam> OdTvDbAssocOsnapPointRefActionParamPtr;

/** \details
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbAssocPathActionParam : public OdTvDbAssocCompoundActionParam
{
public:
	ODRX_DECLARE_MEMBERS(OdTvDbAssocPathActionParam);

	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbAssocPathActionParam(bool createImpObj = true);
};

typedef OdSmartPtr<OdTvDbAssocPathActionParam> OdTvDbAssocPathActionParamPtr;
#include "TD_PackPop.h"

#endif // DbAssocActionParam_INCLUDED_

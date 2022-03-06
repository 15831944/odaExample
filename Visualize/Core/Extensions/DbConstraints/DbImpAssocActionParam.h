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

#ifndef DbImpAssocActionParam_INCLUDED_
#define DbImpAssocActionParam_INCLUDED_ /*!DOM*/

#include "ModelerGeometry.h"
#include "DbConstraintsExports.h"
#include "DbAssocGlobal.h"
#include "DbGeomRef.h"
//#include "DbEntity.h"

#include "TD_PackPush.h"

/** \details
  This class represents the custom implementation of the associated action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocActionParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  virtual OdStringArray compareWith(OdTvDbImpAssocActionParam *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT)  const;
protected:
  /*!DOM*/
  friend class OdTvDbAssocActionParam;

  /*!DOM*/
  OdString m_sName;
  /*!DOM*/
  OdTvDbAssocStatus m_status;
};

//////////////////////////////////////////////////////////////////////////

/** \details
  This class represents the custom implementation of the associated single dependency action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocSingleDependencyActionParam : public OdTvDbImpAssocActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocSingleDependencyActionParam();
  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocSingleDependencyActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  virtual OdTvDbObjectId dependentOnObjectId() const;

  OdResult detachDependencies( OdTvDbObjectId PerentActionId );

  /** \details
  Gets the compounded object.
  */
  virtual OdResult getObject(OdTvDbCompoundObjectId& object) const;

  /** \details
  Deprecated.
  */
  virtual OdResult getObject(OdTvDbCompoundObjectId* object) const {
    return getObject(*object);
  }

  /** \details
  Sets the compounded object.
  */
  virtual OdResult setObject(OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId& object,
    bool isReadDependency = true,
    bool isWriteDependency = false);

  /** \details
  Deprecated.
  */
  virtual OdResult setObject(OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId* object,
    bool isReadDependency = true,
    bool isWriteDependency = false)
  {
    return setObject(actionId, *object, isReadDependency, isWriteDependency);
  }

  /** \details
  Sets the compounded object. Without creating additional dependency (see OdTvDbImpAssocSingleDependencyActionParam::setObject)
  */
  OdResult setObjectOnly(OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId& object,
    bool isReadDependency /*= true*/,
    bool isWriteDependency /*= false*/);

  /** \details
  Deprecated.
  */
  OdResult setObjectOnly(OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId* object,
    bool isReadDependency /*= true*/,
    bool isWriteDependency /*= false*/)
  {
    return setObjectOnly(actionId, *object, isReadDependency, isWriteDependency);
  }

  virtual OdStringArray compareWith(OdTvDbImpAssocActionParam *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT)  const;
protected:
  /*!DOM*/
  friend class OdTvDbAssocActionParam;
  /*!DOM*/
  OdTvDbObjectId m_DependencyId;
};

//////////////////////////////////////////////////////////////////////////

/** \details
  This class represents the custom implementation of the associated compounded action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocCompoundActionParam : public OdTvDbImpAssocActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocCompoundActionParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocCompoundActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;
  /** \details
  Creates and adds a new parameter.
  */
  OdResult addChildParam(const OdTvDbObjectId actionId, const OdTvDbObjectId thisObjectId, const OdString& paramName, OdRxClass* pParamClass, const OdTvDbObjectId anchorId, OdTvDbObjectId& paramId, int& paramIndex);
  /** \details
  Returns an array of object IDs that refer to all owned action parameters with the given name.
  */
  OdTvDbObjectIdArray paramsAtName(const OdString& paramName) const;

  /** \details
  Returns an owned action parameter specified by its name and optional index for parameters with the same name.
  */
  OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;

  virtual OdStringArray compareWith(OdTvDbImpAssocActionParam *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT)  const;
protected:
  /*!DOM*/
  friend class OdTvDbAssocCompoundActionParam;
  /*!DOM*/
  OdUInt16 m_Unknown1;                          // 0
  OdUInt16 m_Unknown2;                          // 0
  OdUInt16 m_UseAdditionalAnchors;                          // 0
  /*!DOM*/
  OdTvDbObjectIdArray m_ActionParams;
  bool m_usingInheritor;
  OdTvDbObjectId m_AnchorId1;
  OdTvDbObjectId m_AnchorId2;
  OdUInt16 m_Unknown3;
  OdTvDbObjectId m_AnchorId3;
};

// TODO
// class OdTvDbImpAssocBlendSurfaceActionBody
// class OdTvDbImpAssocBoolOperActionBody
// class OdTvDbImpAssocCloneAndPositionEntityActionBody
// class OdTvDbImpAssocEdgeFilletChamferActionBody
// class OdTvDbImpAssocExtendSurfaceActionBody
// class OdTvDbImpAssocExtrudedSurfaceActionBody
// class OdTvDbImpAssocFilletSurfaceActionBody
// class OdTvDbImpAssocImpliedSurfaceOrSolidActionBody
// class OdTvDbImpAssocLegacySurfaceActionBody
// class OdTvDbImpAssocLoftedSurfaceActionBody
// class OdTvDbImpAssocLoftedSurfaceBaseActionBody
// class OdTvDbImpAssocNetworkSurfaceActionBody
// class OdTvDbImpAssocOffsetSurfaceActionBody
// class OdTvDbImpAssocPatchSurfaceActionBody
// class OdTvDbImpAssocPathBasedSurfaceActionBody
// class OdTvDbImpAssocPlaneSurfaceActionBody
// class OdTvDbImpAssocPositionEntityActionBody
// class OdTvDbImpAssocRevolvedSurfaceActionBody
// class OdTvDbImpAssocSetObjectPropertyActionBody
// class OdTvDbImpAssocSurfaceActionBody
// class OdTvDbImpAssocSweptSurfaceActionBody
// class OdTvDbImpAssocTrimSurfaceActionBody

//////////////////////////////////////////////////////////////////////////

/** \details
  This class represents the custom implementation of the associated object of single dependency action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocObjectActionParam : public OdTvDbImpAssocSingleDependencyActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocObjectActionParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocObjectActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;
protected:
  /*!DOM*/
  friend class OdTvDbAssocObjectActionParam;
  /*!DOM*/
  bool m_isBase;
};

//////////////////////////////////////////////////////////////////////////

/** \details
  This class represents the custom implementation of the associated vertex of single dependency action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocVertexActionParam : public OdTvDbImpAssocSingleDependencyActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocVertexActionParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocVertexActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;


  OdResult getVertexRef(OdArray<OdTvDbVertexRef>& vertexRefs) const;
  OdResult getVertexRef(OdTvDbVertexRef& vertexRef) const;

  virtual OdResult setVertexRef( const OdTvDbVertexRef& vertexRef, bool isReadDependency, bool isWriteDependency, int dependencyOrder, OdTvDbObjectId actionId);

protected:
  /*!DOM*/
  friend class OdTvDbAssocVertexActionParam;
  /*!DOM*/
  OdTvDbVertexRef m_vertexRef;
};

//////////////////////////////////////////////////////////////////////////

/** \details
  This class represents the custom implementation of the associated edge of single dependency action parameter.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocEdgeActionParam : public OdTvDbImpAssocSingleDependencyActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocEdgeActionParam();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocEdgeActionParam();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  OdResult getEdgeRef(OdArray<OdTvDbEdgeRef>& edgeRefs) const;

  OdResult setEdgeRef( const OdTvDbEdgeRef& edgeRef, bool isReadDependency, /* = true */ bool isWriteDependency, /* = false */ int dependencyOrder, OdTvDbObjectId actionId); // = 0

  OdResult setEdgeSubentityGeometry(const OdGeCurve3d* pNewEdgeCurve);

  OdResult getDependentOnCompoundObject(OdTvDbCompoundObjectId& compoundId) const;

  /** \details
  Gets the compounded object.
  */
  virtual OdResult getObject(OdTvDbCompoundObjectId* object) const;

  /** \details
  Sets the compounded object.
  */
  virtual OdResult setObject(OdTvDbObjectId actionId,
    const OdTvDbCompoundObjectId& object,
    bool isReadDependency = true,
    bool isWriteDependency = false);

  virtual OdStringArray compareWith(OdTvDbImpAssocActionParam *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT)  const;
protected:
  /*!DOM*/
  friend class OdTvDbAssocEdgeActionParam;
  friend class OdTvDbAssocViewSymbolActionParam;
  /*!DOM*/
  OdTvDbEdgeRef m_edgeRef;
  OdTvDbObjectId m_UnkownId;
};

//////////////////////////////////////////////////////////////////////////

/** \details
This class represents the custom implementation of the associated compounded action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocPointRefActionParam : public OdTvDbImpAssocCompoundActionParam
{
public:
  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbImpAssocPointRefActionParam();

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocPointRefActionParam();
};


//////////////////////////////////////////////////////////////////////////

/** \details
This class represents the custom implementation of the associated compounded action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocOsnapPointRefActionParam : public OdTvDbImpAssocPointRefActionParam
{
public:
  /** \details
  Constructor creates an instance of this class.
  */
  OdTvDbImpAssocOsnapPointRefActionParam();

  /** \details
  Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocOsnapPointRefActionParam();
  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

  /** \details
  Reads the .dxf file data of this object.

  \param pFiler [in]  Filer object from which data are read.

  \remarks
  Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

  /** \details
  Writes the .dxf file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;

  void setOsnapMode(OdDb::OsnapMode mode)
  {
    m_OsnapMode = mode;
  }

  void setParam(double param)
  {
    m_NearPointParam = param;
  }

  virtual OdStringArray compareWith(OdTvDbImpAssocActionParam *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT)  const;

private:
  OdInt32 m_UnknownParam1;                          // 0
  OdDb::OsnapMode m_OsnapMode;                          // 0
  double m_NearPointParam;
};
//////////////////////////////////////////////////////////////////////////

/** \details
This class represents the custom implementation of the associated compounded action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocPathActionParam : OdTvDbImpAssocCompoundActionParam
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpAssocPathActionParam();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpAssocPathActionParam();

	/** \details
	Reads the .dwg file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dwg file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

	/** \details
	Reads the .dxf file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dxf file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;
	/** \details
	Creates and adds a new parameter.
	*/
	//OdResult addChildParam(const OdTvDbObjectId actionId, const OdTvDbObjectId thisObjectId, const OdString& paramName, OdRxClass* pParamClass, const OdTvDbObjectId anchorId, OdTvDbObjectId& paramId, int& paramIndex);
	///** \details
	//Returns an array of object IDs that refer to all owned action parameters with the given name.
	//*/
	//OdTvDbObjectIdArray paramsAtName(const OdString& paramName) const;

	///** \details
	//Returns an owned action parameter specified by its name and optional index for parameters with the same name.
	//*/
	//OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;
  virtual OdStringArray compareWith(OdTvDbImpAssocActionParam *bodyIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT)  const;
protected:
	/*!DOM*/
	friend class OdTvDbAssocPathActionParam;
	/*!DOM*/
	OdUInt32 m_UnknownPathActionParam1;                          // 0
};


//////////////////////////////////////////////////////////////////////////

/** \details
This class represents the custom implementation of the associated compounded action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocAsmBodyActionParam : OdTvDbImpAssocActionParam
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpAssocAsmBodyActionParam();
	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpAssocAsmBodyActionParam();

	/** \details
	Reads the .dwg file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dwg file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

	/** \details
	Reads the .dxf file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dxf file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;
	/** \details
	Creates and adds a new parameter.
	*/
	//OdResult addChildParam(const OdTvDbObjectId actionId, const OdTvDbObjectId thisObjectId, const OdString& paramName, OdRxClass* pParamClass, const OdTvDbObjectId anchorId, OdTvDbObjectId& paramId, int& paramIndex);
	///** \details
	//Returns an array of object IDs that refer to all owned action parameters with the given name.
	//*/
	//OdTvDbObjectIdArray paramsAtName(const OdString& paramName) const;

	///** \details
	//Returns an owned action parameter specified by its name and optional index for parameters with the same name.
	//*/
	//OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;
protected:
	/*!DOM*/
	friend class OdTvDbAssocAsmBodyActionParam;
private:
	/*!DOM*/
	OdUInt32 m_UnknownPathActionParam1;
  OdModelerGeometryPtr m_pModelerGeom;
	OdTvDbImpAssocSingleDependencyActionParam *m_pSingleDependencyActionParam;
};

/** \details
This class represents the custom implementation of the associated compounded action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocFaceActionParam : public OdTvDbImpAssocActionParam
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpAssocFaceActionParam();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpAssocFaceActionParam();

	/** \details
	Reads the .dwg file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dwg file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

	/** \details
	Reads the .dxf file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dxf file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;
	/** \details
	Creates and adds a new parameter.
	*/
	//OdResult addChildParam(const OdTvDbObjectId actionId, const OdTvDbObjectId thisObjectId, const OdString& paramName, OdRxClass* pParamClass, const OdTvDbObjectId anchorId, OdTvDbObjectId& paramId, int& paramIndex);
	///** \details
	//Returns an array of object IDs that refer to all owned action parameters with the given name.
	//*/
	//OdTvDbObjectIdArray paramsAtName(const OdString& paramName) const;

	///** \details
	//Returns an owned action parameter specified by its name and optional index for parameters with the same name.
	//*/
	//OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;
protected:
	/*!DOM*/
	friend class OdTvDbAssocFaceActionParam;
	/*!DOM*/
private:
	OdUInt32 m_UnknownPathActionParam1;                 
	OdUInt32 m_UnknownPathActionParam2;
	OdTvDbImpAssocAsmBodyActionParam *m_pAsmBodyActionParam;
};

/** \details
This class represents the custom implementation of the associated compounded action parameter.

Library: Source code provided.
<group Contraint_Classes>
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocTrimmingBodyActionParam : public OdTvDbImpAssocFaceActionParam
{
public:
	/** \details
	Constructor creates an instance of this class.
	*/
	OdTvDbImpAssocTrimmingBodyActionParam();

	/** \details
	Destructor destroys an instance of this class.
	*/
	virtual ~OdTvDbImpAssocTrimmingBodyActionParam();

	/** \details
	Reads the .dwg file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dwg file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dwgOutFields(OdTvDbDwgFiler* pFiler, OdTvDbObjectId objectId) const;

	/** \details
	Reads the .dxf file data of this object.

	\param pFiler [in]  Filer object from which data are read.

	\remarks
	Returns the filer status.
	*/
	virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId);

	/** \details
	Writes the .dxf file data of this object.

	\param pFiler [in]  Pointer to the filer to which data are written.
	*/
	virtual void dxfOutFields(OdTvDbDxfFiler* pFiler, OdTvDbObjectId objectId) const;
	/** \details
	Creates and adds a new parameter.
	*/
	//OdResult addChildParam(const OdTvDbObjectId actionId, const OdTvDbObjectId thisObjectId, const OdString& paramName, OdRxClass* pParamClass, const OdTvDbObjectId anchorId, OdTvDbObjectId& paramId, int& paramIndex);
	///** \details
	//Returns an array of object IDs that refer to all owned action parameters with the given name.
	//*/
	//OdTvDbObjectIdArray paramsAtName(const OdString& paramName) const;

	///** \details
	//Returns an owned action parameter specified by its name and optional index for parameters with the same name.
	//*/
	//OdTvDbObjectId paramAtName(const OdString& paramName, int index = 0) const;
protected:
	/*!DOM*/
	friend class OdTvDbAssocTrimmingBodyActionParam;
	/*!DOM*/
private:
	OdUInt16 m_unknownTrimmingBodyParam1;
	OdInt8 m_unknownTrimmingBodyParam2;
};
#include "TD_PackPop.h"

#endif // DbImpAssocActionParam_INCLUDED_

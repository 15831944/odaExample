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




#ifndef OD_DBDIMASSOC_H
#define OD_DBDIMASSOC_H

#include "TD_PackPush.h"

#include "DbSubentId.h"
#include "DbHandle.h"
#include "DbObject.h"

class OdTvDbDwgFiler;
class OdTvDbDxfFiler;
class OdGePoint3d;
class OdTvDbIdMapping;


/** \details
    This class uniquely defines Xref subentities within an OdTvDbDatabase instance.  

    \remarks
    Each OdTvDbXrefFullSubentPath object consists of a OdDbSubentId object,
    an ordered array of Object IDs, and an ordered array of entity handles. 
    The SubentId consists the index and subentType
    of the object. The array of Object IDs, and the array of handles, define the path to the 
    subentity from the outermost entity (in PaperSpace or ModelSpace) 
    to the entity containing the subentity.
    
    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbXrefFullSubentPath : public OdTvDbFullSubentPath
{
public:
  /** \details
    Returns a reference to the embedded OdHandleArray object in this XrefFullSubentPath object.
    
    \param objectIds [out]  Receives the array reference.
  */
  OdHandleArray& xrefObjHandles();
  const OdHandleArray& xrefObjHandles()const;

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  void dwgIn(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
    
  */
  void dwgOut(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Writes the DXF format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
    \param groupCodeOffset [in]  Group code offset.
  */
  void dxfOut(OdTvDbDxfFiler* pFiler, OdInt groupCodeOffset = 0) const;
private:
  OdHandleArray m_XrefObjHandles;
};

class OdTvDbOsnapPointRef;
class OdTvDbViewport;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbOsnapPointRef object pointers.
*/
typedef OdSmartPtr<OdTvDbOsnapPointRef> OdTvDbOsnapPointRefPtr;
//typedef OdArray<OdTvDbFullSubentPath> OdTvDbFullSubentPathArray;

/** \details
    This class defines a point reference between a dimension and
	its corresponding object.

    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbPointRef : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbPointRef);

  virtual OdResult evalPoint(OdGePoint3d& pnt_wcs) = 0;
  virtual OdResult getEntities(OdTvDbFullSubentPathArray& ents, bool getLastPtRef = true) const = 0;
  virtual bool isGeomErased() const = 0;
  virtual bool isXrefObj(OdTvDbObjectIdArray& ids1, OdTvDbObjectIdArray& ids2, bool isMainObj = true) const = 0;
  virtual OdResult updateXrefSubentPath() = 0;
  virtual OdResult updateSubentPath(OdTvDbIdMapping& idMap) = 0;

  virtual void dwgOutFields(OdTvDbDwgFiler* filer) const = 0;
  virtual void dwgInFields(OdTvDbDwgFiler* filer) = 0;
  virtual void dxfOutFields(OdTvDbDxfFiler* filer) const = 0;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* filer) = 0;

  virtual void updateDueToMirror(bool inMirror = false) = 0;

/** \details
  Calculates transformation combined from OdTvDbViewport's MS2PS and BlockReference transformations
*/
  static bool calcTransform(const OdTvDbObjectIdArray& ids, OdGeMatrix3d& A_Ecs2Wcs);

  /** \details
  Returns matrix to convert MS coordinates to PS for given OdTvDbViewport entity
  */
  static OdGeMatrix3d mswcsToPswcs(const OdTvDbViewport* pVPort);
/*
  static OdResult  dwgInFields(OdTvDbDwgFiler* filer, OdTvDbDatabase* pDb, OdTvDbPointRef*& pPointRef);
  static OdResult  dwgOutFields(OdTvDbDwgFiler* filer, OdTvDbDatabase* pDb, const OdTvDbPointRef* pPointRef);
  static OdResult  dxfInFields(OdTvDbDxfFiler* filer, OdTvDbDatabase* pDb, OdTvDbPointRef*& pPointRef);
  static OdResult  dxfOutFields(OdTvDbDxfFiler* filer, OdTvDbDatabase* pDb, const OdTvDbPointRef* pPointRef);
  static OdTvDbEntityPtr subentPtr(const OdTvDbFullSubentPath& objPath, bool& isCloned, bool& reverseArc, bool& isStandAloneArc);
  static OdGeMatrix3d wcsToDcsMatrix(const OdTvDbViewport* pVPort);
*/
};

/** \details

    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbOsnapPointRef : public OdTvDbPointRef
{
public:
  OdTvDbOsnapPointRef();

  ODRX_DECLARE_MEMBERS(OdTvDbOsnapPointRef);

  /** \details
    Returns the object snap mode for this OsnapPointRef object.
    \remarks
    osnapMode() returns one of the following:
    
    <table>
    Name                      Value   Description 
    OdDb::kOsModeEnd          1       End Point
    OdDb::kOsModeMid          2       Mid Point
    OdDb::kOsModeCen          3       Center
    OdDb::kOsModeNode         4       Node
    OdDb::kOsModeQuad         5       Quadrant
    OdDb::kOsModeIntersec     6       Intersection
    OdDb::kOsModeIns          7       Insertion point
    OdDb::kOsModePerp         8       Perpendicular
    OdDb::kOsModeTan          9       Tangent
    OdDb::kOsModeNear         10      Nearest
    OdDb::kOsModeApint        11      Apparent intersection
    OdDb::kOsModePar          12      Parallel
    OdDb::kOsModeStart        13      Start Point 
    </table>
 
  */
  OdDb::OsnapMode osnapType() const;
  /** \details
    Sets the object snap mode for this OsnapPointRef object.
 
    \remarks
    osnapMode must be one of the following:
    
    <table>
    Name                      Value   Description 
    OdDb::kOsModeEnd          1       End Point
    OdDb::kOsModeMid          2       Mid Point
    OdDb::kOsModeCen          3       Center
    OdDb::kOsModeNode         4       Node
    OdDb::kOsModeQuad         5       Quadrant
    OdDb::kOsModeIntersec     6       Intersection
    OdDb::kOsModeIns          7       Insertion point
    OdDb::kOsModePerp         8       Perpendicular
    OdDb::kOsModeTan          9       Tangent
    OdDb::kOsModeNear         10      Nearest
    OdDb::kOsModeApint        11      Apparent intersection
    OdDb::kOsModePar          12      Parallel
    OdDb::kOsModeStart        13      Start Point
    </table>
  */
  void setOsnapType(OdDb::OsnapMode osnapMode);

  /** \details
    Returns a reference to the OdTvDbXrefFullSubentPath of the main entity for the OsnapPointRef object. 
  */
  OdTvDbXrefFullSubentPath& mainEntity();
  /** \details
    Returns a reference to the OdTvDbXrefFullSubentPath of the intersecting entity for the OsnapPointRef object. 
  */
  OdTvDbXrefFullSubentPath& intersectEntity();

  void getIdPath(OdTvDbFullSubentPath& idPath) const;
  void setIdPath(const OdTvDbFullSubentPath& idPath);

  void getIntIdPath(OdTvDbFullSubentPath& intIdPath) const;
  void setIntIdPath(const OdTvDbFullSubentPath& intIdPath);

  /** \details
    Returns the near Osnap value for this OsnapPointRef object.
  */
  double nearPointParam() const;

  /** \details
    Returns the near Osnap value for this OsnapPointRef object.
    \param nearOsnap [in]  Near Osnap value.
  */
  void setNearPointParam(double nearOsnap);

  /** \details
    Returns a reference to the Osnap point for this OsnapPointRef object.
  */
  OdGePoint3d point() const;
  void setPoint(const OdGePoint3d& pt);

  /** \details
    Returns the last OsnapPointRef for this OsnapPointRef object.
  */
  const OdTvDbOsnapPointRef* lastPointRef() const;
  
  /** \details
    Returns the last OsnapPointRef for this OsnapPointRef object.
  */
  OdTvDbOsnapPointRef* lastPointRef();

  /** \details
    Sets the last OsnapPointRef for this OsnapPointRef object.
    \param pOsnapPointRef [in]  Pointer to the last OsnapPointRef object.
  */
  void setLastPointRef(OdTvDbOsnapPointRefPtr pOsnapPointRef);

  virtual bool isGeomErased() const;
  virtual bool isXrefObj(OdTvDbObjectIdArray& ids1, OdTvDbObjectIdArray& ids2, bool isMainObj = true) const;
  virtual OdResult updateXrefSubentPath();
  virtual OdResult updateSubentPath(OdTvDbIdMapping& idMap);
  virtual OdResult evalPoint(OdGePoint3d &pt);
  virtual OdResult getEntities(OdTvDbFullSubentPathArray& ents, bool getLastPtRef = true) const;
  virtual void updateDueToMirror(bool inMirror = false);

  void getXrefHandles(OdHandleArray& xrefHandles) const;
  void setXrefHandles(const OdHandleArray& xrefHandles);
  void getXrefIntHandles(OdHandleArray& xrefHandles) const;
  void setXrefIntHandles(const OdHandleArray& xrefHandles);

  /** \details
    Reads the .dwg file format data of this object from the specified file.
       
    \param pFiler [in]  Pointer to the filer from which the data are to be read.
  */
  void dwgInFields(OdTvDbDwgFiler* pFiler);
  /** \details
    Writes the .dwg file format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  /** \details
    Writes the DXF format data of this object to the specified filer. 
    
    \param pFiler [in]  Pointer to the filer to which the data are to be written.
  */
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  OdResult dxfInFields(OdTvDbDxfFiler* filer);
private:
  OdDb::OsnapMode        m_OsnapMode;
  OdTvDbXrefFullSubentPath m_MainEntity;
  OdTvDbXrefFullSubentPath m_IntersectEntity;
  double                 m_dNearOsnap;
  OdGePoint3d            m_OsnapPoint;
  OdTvDbOsnapPointRefPtr   m_pLastPointRef;
  bool                   m_bUpdateDueToMirror;
};

/** \details
    This class represents Associative Dimension objects in an OdTvDbDatabase instance.

    Corresponding C++ library: TD_Db
    
    <group OdTvDb_Classes>
*/
class DBDIM_EXPORT OdTvDbDimAssoc : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbDimAssoc);

  OdTvDbDimAssoc();

  enum { kMaxPointRefs = 4 };
  
  enum PointType 
  {
    kXline1Point          = 0,
    kXline2Point          = 1,
    kOriginPoint          = 0,
    kDefiningPoint        = 1,
    kXline1Start          = 0,
    kXline1End            = 1,
    kXline2Start          = 2,
    kXline2End            = 3,
    kVertexPoint          = 2,
    kChordPoint           = 0,
    kCenterPoint          = 1,
    kFarChordPoint        = 1,
    kOverrideCenterPoint  = 2,
    kAngLineStart         = 2,
    kJogPoint             = 3,
    kAngLineEnd           = 3,
    kLeaderPoint          = 0
  };

  enum RotatedDimType
  {
    kUnknown       = 0,
    kParallel      = 1,
    kPerpendicular = 2
  };

  enum AssocFlags 
  {
    kFirstPointRef     = (1<<0),
    kSecondPointRef    = (1<<1),
    kThirdPointRef     = (1<<2),
    kFourthPointRef    = (1<<3)
  };

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler) ODRX_OVERRIDE;
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const ODRX_OVERRIDE;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler) ODRX_OVERRIDE;
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const ODRX_OVERRIDE;

  /** \details
    Returns the Object ID of the Dimension entity associated with this Associative Dimension object (DXF 330).
  */
  OdTvDbObjectId dimObjId() const;

  /** \details
    Sets the Object ID of the Dimension entity associated with this Associative Dimension object (DXF 330).
    \param dimId [in]  Dimension Object ID.
  */
  void setDimObjId(const OdTvDbObjectId& dimId);

  /** \details
    Returns the associativity flag of this Associative Dimension object (DXF 90).
  */
  OdInt32 assocFlag() const;

  /** \details
    Returns the associativity flag of the specified Osnap Point Reference for this Associative Dimension object.
  */
  bool assocFlag(int pointIndex) const;

  void setAssocFlag(int assocFlag);
  // Sets the index of point reference being used and establishes or clears the association flag. 
  void setAssocFlag(int pointIndex, bool flagValue);

  /** \details
    Returns the specified Osnap Point Reference for this Associative Dimension object.
    
    \param pointIndex [in]  Point index. The value should be 0, 1, 2, 3 or from the PointType enum 
    
    \remarks
    pointIndex must be one of the following:
   
  */
  OdTvDbOsnapPointRefPtr pointRef(int pointIndex) const;

  /** \details
    Sets the specified Osnap Point Reference for this Associative Dimension object.
    
    \param pointIndex [in]  Point index. The value should be 0, 1, 2, 3 or from the PointType enum 
    \param pOsnapPointRef [in]  SmartPointer to the Osnap Point Reference.
  */
  void setPointRef(int pointIndex, OdTvDbOsnapPointRefPtr pOsnapPointRef);

  /** \details
  Returns the rotated dimension type of this Associative Dimension object (DXF 71).

  \remarks
  rotatedDimType() returns one of the following:

  <table>
  Name              Value
  kParallel         1
  kPerpendicular    2
  </table>
  */
  RotatedDimType rotatedDimType() const;

  /** \details
  Sets the rotated dimension type of this Associative Dimension object (DXF 71).

  \remarks
  rotatedDimType must be one of the following:

  <table>
  Name              Value
  kParallel         1
  kPerpendicular    2
  </table>
  */
  void setRotatedDimType(RotatedDimType dimType);

  void addToPointRefReactor();
  void addToDimensionReactor(bool isAdd = true);

  OdResult removePointRef(int ptType);
  OdResult updateDimension(bool update = true, bool skipReactors = false);
  void removeAssociativity(bool force = true);
  
  /** \details
  Returns the trans-space flag of this Associative Dimension object (DXF 70).
  */
  bool isTransSpatial() const;
  /** \details
  Sets the trans-space flag of this Associative Dimension object (DXF 70).
  \param transSpace [out]  Trans-space flag.
  */
  void setTransSpatial(bool value);
  

  OdResult post(OdTvDbObjectId dimId, OdTvDbObjectId& dimAssocId, bool isActive = true);
  OdResult getDimAssocGeomIds(OdTvDbObjectIdArray& geomIds) const;
  bool isAllGeomErased() const;
  
  virtual void modifiedGraphics(const OdTvDbObject* pObj) ODRX_OVERRIDE;
  virtual void copied(const OdTvDbObject* pObj, const OdTvDbObject* pNewObj) ODRX_OVERRIDE;
  virtual void erased(const OdTvDbObject *pObj, bool erasing = true) ODRX_OVERRIDE;
  virtual void openedForModify(const OdTvDbObject* pObject) ODRX_OVERRIDE;

  virtual OdTvDbObjectPtr subWblockClone(OdTvDbIdMapping& idMap, OdTvDbObject* pOwner, bool bPrimary) const ODRX_OVERRIDE;
  virtual OdTvDbObjectPtr subDeepClone(OdTvDbIdMapping& idMap, OdTvDbObject* pOwner, bool bPrimary) const ODRX_OVERRIDE;

protected:
  OdResult setPointRefReactor(int ptType, bool isAdd = true);
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDimAssoc object pointers.
*/
typedef OdSmartPtr<OdTvDbDimAssoc> OdTvDbDimAssocPtr;

//
// Inlines
//

inline
OdHandleArray& OdTvDbXrefFullSubentPath::xrefObjHandles()
{ 
  return m_XrefObjHandles; 
}

inline
const OdHandleArray& OdTvDbXrefFullSubentPath::xrefObjHandles() const
{ 
  return m_XrefObjHandles; 
}

inline
OdDb::OsnapMode OdTvDbOsnapPointRef::osnapType() const
{
  return m_OsnapMode;
}

inline
void OdTvDbOsnapPointRef::setOsnapType(OdDb::OsnapMode osnapMode)
{
  m_OsnapMode = osnapMode;
}

inline
OdTvDbXrefFullSubentPath& OdTvDbOsnapPointRef::mainEntity()
{
  return m_MainEntity;
}

inline
OdTvDbXrefFullSubentPath& OdTvDbOsnapPointRef::intersectEntity()
{
  return m_IntersectEntity;
}

inline
double OdTvDbOsnapPointRef::nearPointParam() const
{
  return m_dNearOsnap;
}

inline
void OdTvDbOsnapPointRef::setNearPointParam(double nearOsnap)
{
  m_dNearOsnap = nearOsnap;
}

inline
OdGePoint3d OdTvDbOsnapPointRef::point() const
{
  return m_OsnapPoint;
}
inline
void OdTvDbOsnapPointRef::setPoint(const OdGePoint3d& pt)
{
  m_OsnapPoint = pt;
}

inline
const OdTvDbOsnapPointRef* OdTvDbOsnapPointRef::lastPointRef() const
{
  return m_pLastPointRef;
}
inline
OdTvDbOsnapPointRef* OdTvDbOsnapPointRef::lastPointRef()
{
  return m_pLastPointRef;
}

inline
void OdTvDbOsnapPointRef::setLastPointRef(OdTvDbOsnapPointRefPtr pOsnapPointRef)
{
  m_pLastPointRef = pOsnapPointRef;
}

#include "TD_PackPop.h"

#endif // OD_DBDIMASSOC_H


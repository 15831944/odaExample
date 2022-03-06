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

#ifndef _DBSSET_H_
#define _DBSSET_H_

#include "Ge/GePoint3d.h"
#include "DbDatabase.h"
#include "DbObjectId.h"
#include "DbObject.h"
#include "DbObjectIterator.h"
#include "ResBuf.h"
#include "DbSubentId.h"
#include "SSet.h"

//class OdTvDbSelectionSet;
//class OdTvDbBlockTableRecord;


/** \details
    This class is the abstract base class for all selection filters.

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT ODRX_ABSTRACT OdTvDbSelectionFilter : public OdRxObject
{
protected:
  OdTvDbSelectionFilter();
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSelectionFilter);

  virtual bool accept(const OdTvDbObjectId& entityId) const = 0;
};

typedef OdSmartPtr<OdTvDbSelectionFilter> OdTvDbSelectionFilterPtr;


class OdTvDbParametrizedSF;
typedef OdSmartPtr<OdTvDbParametrizedSF> OdTvDbParametrizedSFPtr;

/** \details
    This class represents selection filter defined by ResBuf chain.

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT ODRX_ABSTRACT OdTvDbParametrizedSF : public OdTvDbSelectionFilter
{
protected:
  OdTvDbParametrizedSF();
public:
  static OdTvDbParametrizedSFPtr createObject(const OdTvResBuf* pSpec, const OdTvDbDatabase* pDb);

  virtual void setSpecification(const OdTvResBuf* /*pSpec*/, const OdTvDbDatabase* /*pDb*/ = 0) {}
  virtual OdTvResBufPtr specification() const { return OdTvResBufPtr(); }
  virtual const OdTvDbDatabase* database() const { return 0; }
};


/** \details
  This class implements iterators for OdTvDbSelectionSet objects.

  \remarks

  Instances are returned by OdTvDbSelectionSet::newIterator().

  <group OdTvDb_Classes>
*/
//class ODRX_ABSTRACT TOOLKIT_EXPORT OdTvDbSelectionSetIterator : public OdRxObject
class ODRX_ABSTRACT TOOLKIT_EXPORT OdTvDbSelectionSetIterator : public OdSelectionSetIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSelectionSetIterator);

  /** \details
      Returns the Object ID of the entity at the current position specified by
      this Iterator object.
  */
  virtual OdTvDbObjectId objectId() const = 0;
  
protected:
  OdTvDbSelectionSetIterator();
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbSelectionSetIterator object pointers.
*/
typedef OdSmartPtr<OdTvDbSelectionSetIterator>  OdDbSelectionSetIteratorPtr;

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbSelectionSet object pointers.
*/
typedef OdSmartPtr<OdTvDbSelectionSet>  OdDbSelectionSetPtr;

/** \details
    This class represents Selection Sets in a client application.

    \remarks
    Only entities from an OdTvDbDatabase object's ModelSpace or PaperSpace may be
    added to a Selection Set.

    <group OdTvDb_Classes>
*/
class ODRX_ABSTRACT TOOLKIT_EXPORT OdTvDbSelectionSet : public OdSelectionSet
{
protected:
  OdTvDbSelectionSet();
public:
  ODRX_DECLARE_MEMBERS(OdTvDbSelectionSet);

  /** \details
    Creates a SelectionSet object for the specified database. 
    \param pDb [in]  Pointer to the database object for which to create the SelectionSet object.
    \returns
    Returns a SmartPointer to the new SelectionSet object.
  */
  static OdDbSelectionSetPtr createObject(const OdTvDbDatabase *pDb);
  
  virtual const OdTvDbDatabase* database() const = 0;

  /** \details
      Returns an Iterator object that provides access to the entities in this Selection Set.
  */
  //virtual OdSelectionSetIteratorPtr newIterator() const = 0; 

  virtual OdTvDbObjectIdArray objectIdArray() const = 0;

  // operations on the selection set 

  /** \details
    Filter selection only.  

    \param pDb [in]  Pointer to the database object for which to create the SelectionSet object.
    \param pFilter [in] object of type OdTvDbSelectionFilter or pointer to a OdTvResBuf chain defining the filter.
  */
  static OdDbSelectionSetPtr select(const OdTvDbDatabase *pDb, const OdRxObject* pFilter = 0);

  /** \details
    Filter selection only.  

    \param vpId [in]  id of OdTvDbViewportTableRecord  record or OdTvDbViewport entity in which to select.
    \param nPoints [in]  Number of points into selection shape.
    \param wcsPts [in]  Selection shape as set of World Coordinate Space points.
    \param mode [in]  Selection mode.
    \param sm [in]  Subentities selection mode.
    \param pFilter [in] object of type OdTvDbSelectionFilter or pointer to a OdTvResBuf chain defining the filter.
  */
  static OdDbSelectionSetPtr select(
    const OdTvDbObjectId& vpId,
    int nPoints,
    const OdGePoint3d* wcsPts,
    OdDbVisualSelection::Mode mode = OdDbVisualSelection::kCrossing,
    OdUInt32 sm = OdDbVisualSelection::kDisableSubents,
    const OdRxObject* pFilter = 0);

  /** \details
    Returns the number of entities in this group.
  */
  //virtual OdUInt32 numEntities() const = 0;

  /** \details
    Appends the specified entity to this SelectionSet object.  

    \param entityId [in]  Object ID of the OdTvDbEntity. 
    \param method [in] Selection method to associate with object
  */
  TD_USING(OdSelectionSet::append);
  //virtual void append(OdDbStub* entityId, OdDbSelectionMethod* pMethod = 0) = 0;
  
  virtual void append(const OdTvDbObjectId& entityId, OdDbSelectionMethod* pMethod = 0) = 0;

  /** \details
    Appends the specified entity to this SelectionSet object.  

    \param entityIds [in]  Array of Object IDs of the OdTvDbEntity's.
    \param pMethod [in] Selection method to associate with objects.
  */
  virtual void append(const OdTvDbObjectIdArray& entityIds, OdDbSelectionMethod* pMethod = 0);


  //virtual void append(const OdDbBaseFullSubentPath& subent, OdDbSelectionMethod* pMethod = 0) = 0;
  
  /** \details
    Appends the specified subentity to this SelectionSet object.  

    \param subent [in]  Subentity path to append.
    \param pMethod [in] Selection method to associate with objects  
  */
  virtual void append(const OdTvDbFullSubentPath& subent, OdDbSelectionMethod* pMethod = 0) = 0;

  /** \details
    Appends the specified entity to this SelectionSet object.  

    \param pSSet [in]  Other selection set to copy entities from. 
  */
  virtual void append(const OdSelectionSet* pSSet);

  /** \details
    Removes the specified entity from this SelectionSet object.  

    \param entityId [in]  Object ID of the OdTvDbEntity. 
  */
  TD_USING(OdSelectionSet::remove);
  //virtual void remove(OdDbStub* entityId) = 0;
  
  /** \details
    Removes the specified entity from this SelectionSet object.  

    \param entityId [in]  Object ID of the OdTvDbEntity. 
  */
  virtual void remove(const OdTvDbObjectId& entityId) = 0;

  /** \details
    Removes the specified entity from this SelectionSet object.  

    \param entityIds [in]  Array Object ID of the OdTvDbEntity. 
  */
  virtual void remove(const OdTvDbObjectIdArray& entityIds);


  //virtual void remove(const OdDbBaseFullSubentPath& subent) = 0;
  
  /** \details
  Removes the specified subentity from this SelectionSet object.  

  \param subent [in]  Subentity path to remove. 
  */
  virtual void remove(const OdTvDbFullSubentPath& subent) = 0;

  /** \details
  Removes the specified entity from this SelectionSet object.  

  \param pSSet [in]  Object ID of the OdTvDbEntity. 
  */
  virtual void remove(const OdSelectionSet* pSSet);

  /** \details
    Returns true if and only if the specified entity is a member
    of this SelectionSet object.
    \param entityId [in]  Object ID of the OdTvDbEntity. 
  */
  TD_USING(OdSelectionSet::isMember);
  //virtual bool isMember(OdDbStub* entityId) const = 0;
  
  /** \details
    Returns true if and only if the specified subentity is a member
    of this SelectionSet object.
    \param entityId [in]  Subentity path. 
  */
  virtual bool isMember(const OdTvDbObjectId& entityId) const = 0;


  //virtual bool isMember(const OdDbBaseFullSubentPath& subent) const = 0;
  
  /** \details
    Returns true if and only if the specified subentity is a member
    of this SelectionSet object.
    \param entityId [in]  Subentity path. 
  */
  virtual bool isMember(const OdTvDbFullSubentPath& subent) const = 0;

  TD_USING(OdSelectionSet::method);
  //virtual OdDbSelectionMethodPtr method(OdDbStub* entityId) const = 0;
  
  /** \details
    Returns the selection method for the given subentity.
    
    \param entityId [in]  Subentity path.
  */
  virtual OdDbSelectionMethodPtr method(const OdTvDbObjectId& entityId) const = 0;

  /** \details
  Returns the number of subentities selected inside the entity with the given id.
  (analogous to acedSSSubentLength)
  \param entityId [in]  entity id for the parent of the subentity

  \remarks
  Returns true if and only if not at the end of the list.
  */
  virtual OdUInt32 subentCount(const OdTvDbObjectId& entityId) const = 0;

  /** \details
  Returns the given subentity path inside the entity with the given id.
  (analogous to acedSSSubentName)
  \param entityId [in]  entity id for the parent of the subentity
  \param i [in]  index of the subentity.
  \param path [out]  Path to the subentity.

  \returns
  Returns true if and only if "i" is valid index in the subentities array.
  */
  virtual bool getSubentity(const OdTvDbObjectId& entityId, OdUInt32 i, OdTvDbFullSubentPath& path) const = 0;
  
  /** \details
    Returns the selection method for the given subentity.
  */
  virtual OdDbSelectionMethodPtr method(const OdTvDbFullSubentPath& subent) const = 0;
};

#endif //_DBSSET_H_

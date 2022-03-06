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


#ifndef _NW_SSET_H_
#define _NW_SSET_H_

#include "SSet.h"
#include "NwExport.h"
#include "NwSubentId.h"
#include "NwObject.h"
#include "Gs/Gs.h"

class OdNwDatabase;
class OdNwSelectionSet;

/** \details
  This template class is a specialization of the OdArray class for
  OdNwObjectId object pointers.
*/
typedef OdArray<OdNwObjectId, OdMemoryAllocator<OdNwObjectId> > OdNwObjectIdArray;

/** \details
  This class represents selection filters.

  <group OdNw_Classes>
*/
class ODRX_ABSTRACT NWDBEXPORT OdNwSelectionFilter : public OdRxObject
{
protected:
  //DOM-IGNORE-BEGIN
  OdNwSelectionFilter();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSelectionFilter);
  //DOM-IGNORE-END

  /** \details
    Indicates whether an entity with the specified object ID meets the
    requirements of this selection filter.
    \param entityId [in] Entity object ID.
    \returns True if the entity with the specified object ID meets the
    requirements of this selection filter; false otherwise.
  */
  virtual bool accept(const OdNwObjectId& entityId) const = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSelectionFilter object pointers.
*/
typedef OdSmartPtr<OdNwSelectionFilter> OdNwSelectionFilterPtr;


/** \details
  This class represents selection set iterators.

  <group OdNw_Classes>
*/
class ODRX_ABSTRACT NWDBEXPORT OdNwSelectionSetIterator : public OdSelectionSetIterator
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSelectionSetIterator);
  //DOM-IGNORE-END

  /** \details
    Returns the object ID of the entity at the current position specified by
    this iterator object.
    \returns Object ID of the entity at the current position.
  */
  virtual OdNwObjectId objectId() const = 0;

protected:
  //DOM-IGNORE-BEGIN
  OdNwSelectionSetIterator();
  //DOM-IGNORE-END
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSelectionSetIterator object pointers.
*/
typedef OdSmartPtr<OdNwSelectionSetIterator>  OdNwSelectionSetIteratorPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwSelectionSet object pointers.
*/
typedef OdSmartPtr<OdNwSelectionSet>  OdNwSelectionSetPtr;

/** \details
  This class represents selection sets in an ODA based application.

  \remarks
  Only entities from an OdNwDatabase object can be added to a Selection Set.
*/
class ODRX_ABSTRACT NWDBEXPORT OdNwSelectionSet : public OdSelectionSet
{
protected:
  //DOM-IGNORE-BEGIN
  OdNwSelectionSet();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSelectionSet);
  //DOM-IGNORE-END

  /** \details
    Creates a selection set object for the specified database.
    \param pDb [in] Pointer to the database object for which to create the selection set object.
    \returns Smart pointer to the created selection set object.
  */
  static OdNwSelectionSetPtr createObject(const OdNwDatabase *pDb);

  /** \details
    Returns the database wich this selection set object is associated with.
    \returns Pointer to the database.
  */
  virtual const OdNwDatabase* database() const = 0;

  /**
    Returns an Iterator object that provides access to the entities in this Selection Set.
  */
  //virtual OdSelectionSetIteratorPtr newIterator() const = 0;

  /** \details
    Filter selection only.
    \param vpId    [in] Viewport object ID.
    \param nPoints [in] Number of selection points.
    \param wcsPts  [in] Selection points/
    \param mode    [in] Visual selection mode.
    \param sm      [in] Subentities selection mode.
    \param pFilter [in] Object of type OdNwSelectionFilter or pointer to a OdResBuf chain defining the filter.
    \returns Smart pointer to the selection set object.
    \remarks
    Valid values of the mode parameter are specified by the OdDbVisualSelection
    enumeration and must be one of the following: kPoint, kBox, kWindow,
    kCrossing, kFence, kWPoly, kCPoly.
  */
  static OdNwSelectionSetPtr select(const OdNwObjectId& vpId,
                                    int nPoints,
                                    const OdGePoint3d* wcsPts,
                                    OdDbVisualSelection::Mode mode = OdDbVisualSelection::kCrossing,
                                    OdDbVisualSelection::SubentSelectionMode sm = OdDbVisualSelection::kDisableSubents,
                                    const OdRxObject* pFilter = 0);

  //TD_USING(OdSelectionSet::append);
  /** \details
    Appends the specified entity to this selection set object.

    \param entityId [in] Object ID of the OdNwModelItem.
    \param method   [in] Selection method to associate with the object.
  */
  virtual void append(const OdNwObjectId& entityId, OdDbSelectionMethod* pMethod = 0) = 0;

  /** \details
    Appends the specified entities to this selection set object.

    \param entityIds [in] Array of object IDs of the OdDgEntity's.
    \param method    [in] Selection method to associate with objects.
  */
  virtual void append(const OdNwObjectIdArray& entityIds, OdDbSelectionMethod* pMethod = 0);

  /** \details
    Appends the specified subentity to this selection set object.

    \param subent [in] Subentity path to the subentity to append.
    \param method [in] Selection method to associate with the object.
  */
  virtual void append(const OdNwFullSubentPath& subent, OdDbSelectionMethod* pMethod = 0) = 0;

  /** \details
    Appends the specified entity to this selection set object.

    \param pSSet [in] Other selection set to copy entities from.
  */
  virtual void append(const OdSelectionSet* pSSet);

  /** \details
    Removes the specified entity from this selection set object.

    \param entityId [in] Object ID of the OdNwObject.
  */
  virtual void remove(const OdNwObjectId& entityId) = 0;

  /** \details
    Removes the specified entity from this selection set object.

    \param entityIds [in] Array of OdNwObject object IDs.
  */
  virtual void remove(const OdNwObjectIdArray& entityIds);

  /** \details
    Removes the specified subentity from this selection set object.

    \param subent [in] Subentity path to the subentity to remove.
  */
  virtual void remove(const OdNwFullSubentPath& subent) = 0;

  /** \details
    Removes the specified entity from this selection set object.

    \param pSSet [in] Object ID of the OdNwObject.
  */
  virtual void remove(const OdSelectionSet* pSSet);

  /**
    Returns true if and only if the specified subentity is a member of this
    selection set object.
    \param subent [in] Subentity path.
  */
  //virtual bool isMember(const OdBmFullSubentPath& subent) const = 0;

  //TD_USING(OdSelectionSet::method);
  //virtual OdDbSelectionMethodPtr method(const OdDgElementId& entityId) const = 0;

  /**
    Returns the given subentity path inside the entity with the given ID.
    (analogous to acedSSSubentName)
    \param entityId [in] Entity id for the parent of the subentity.
    \param i        [in] Index of the subentity.
    \param path    [out] Path to the subentity.

    \returns
    Returns true if and only if "i" is a valid index in the subentities array.
  */
  //virtual bool getSubentity(const OdDgElementId& entityId, OdUInt32 i,
  //                          OdDgFullSubentPath& path) const;

  /**
    Returns the selection method for the given subentity.
  */
  //virtual OdDbSelectionMethodPtr method(const OdDgFullSubentPath& subent) const;
};

#endif //_NW_SSET_H_

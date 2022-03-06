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


#ifndef _NW_DBSUBENT_H
#define _NW_DBSUBENT_H /*!DOM*/

#include "DbBaseSubentId.h"
#include "NwObject.h"
//#include "NwObjectIdArray.h"

//typedef OdArray<OdNwObjectId> OdNwObjectIdArray;

/** \details
  This class uniquely defines subentities within in an OdNwDatabase instance.

  \remarks
  Each OdNwFullSubentPath object consists of an OdDbSubentId object and an
  ordered array of Object IDs. The SubentId consists of the index and subentType
  of the object. The array of Object IDs defines the path to the subentity from
  the outermost entity (in PaperSpace or ModelSpace) to the entity containing
  the subentity.

  Corresponding C++ library: TNW_Db

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwFullSubentPath : public OdDbBaseFullSubentPath
{
public:
  /** \details
    Default constructor for objects of the OdNwFullSubentPath class.
  */
  OdNwFullSubentPath()
  {
  }

  /** \details
    Constructor for objects of the OdNwFullSubentPath class.
    \param index [in] Subentity marker.
  */
  OdNwFullSubentPath(OdGsMarker index)
    : OdDbBaseFullSubentPath(OdDb::kNullSubentType, index)
  {
  }

  /** \details
    Constructor for objects of the OdNwFullSubentPath class.
    \param entId [in] Entity ID.
    \param subId [in] Subentity ID.
  */
  OdNwFullSubentPath(OdNwObjectId entId, OdDbSubentId subId)
    : OdDbBaseFullSubentPath(entId, subId)
  {
  }

  /** \details
    Constructor for objects of the OdNwFullSubentPath class.
    \param entId [in] Entity ID.
    \param index [in] Subentity marker.
  */
  OdNwFullSubentPath(OdNwObjectId entId, OdGsMarker index)
    : OdDbBaseFullSubentPath(entId, OdDb::kNullSubentType, index)
  {
  }

  /** \details
    Constructor for objects of the OdNwFullSubentPath class.
    \param objectIds [in] Array of object IDs.
    \param subId     [in] Subentity ID.
  */
  OdNwFullSubentPath(OdNwObjectIdArray objectIds, OdDbSubentId subId)
    : OdDbBaseFullSubentPath(*reinterpret_cast<OdDbStubPtrArray*>(&objectIds), subId)
  {
  }

  /** \details
    Constructor for objects of the OdNwFullSubentPath class.
    \param objectIds [in] Array of object IDs.
    \param subId     [in] Subentity ID.
  */
  OdNwFullSubentPath(OdDbStubPtrArray objectIds, OdDbSubentId subId)
    : OdDbBaseFullSubentPath(objectIds, subId)
  {
  }

  /** \details
    Gets a reference to the embedded OdNwObjectIdArray object in this
    FullSubentPath object.
    \param objectIdsArg [out] Embedded OdNwObjectIdArray object in this FullSubentPath object.
  */
  void objectIds(OdNwObjectIdArray& objectIdsArg) const
  {
    objectIdsArg = *reinterpret_cast<const OdNwObjectIdArray*>(&m_ObjectIds);
  }

  /** \details
    Assignment operator. Assignes another OdNwFullSubentPath object to this
    OdNwFullSubentPath object.
    \param fullSubentPath [in] OdNwFullSubentPath object to assign to this OdNwFullSubentPath object.
    \returns This OdNwFullSubentPath object.
  */
  OdNwFullSubentPath& operator =(const OdNwFullSubentPath& fullSubentPath)
  {
    OdDbBaseFullSubentPath::operator=(fullSubentPath);
    return *this;
  }

  /** \details
    Comparison operator. Compares this OdNwFullSubentPath object with another
    OdNwFullSubentPath object.
    \param fullSubentPath [in] OdNwFullSubentPath object to compare with this OdNwFullSubentPath object.
    \returns True if compared objects are equal; false otherwise.
  */
  bool operator==(const OdNwFullSubentPath& fullSubentPath) const
  {
    return OdDbBaseFullSubentPath::operator==(fullSubentPath);
  }

  /** \details
    Returns a reference to the embedded OdNwObjectIdArray object in this
    FullSubentPath object.
    \returns Embedded OdNwObjectIdArray object in this FullSubentPath object.
  */
  const OdNwObjectIdArray& objectIds() const
  {
    return *reinterpret_cast<const OdNwObjectIdArray*>(&m_ObjectIds);
  }

  /** \details
    Returns a reference to the embedded OdNwObjectIdArray object in this
    FullSubentPath object.
    \returns Embedded OdNwObjectIdArray object in this FullSubentPath object.
  */
  OdNwObjectIdArray& objectIds()
  {
    return *reinterpret_cast<OdNwObjectIdArray*>(&m_ObjectIds);
  }

  /**
    Returns a reference to, or a copy of, the embedded OdDbSubentId object in
    this FullSubentPath object.
  */
  /*const OdDbSubentId subentId() const
  {
    return m_SubentId;
  }

  OdDbSubentId& subentId()
  {
    return m_SubentId;
  }*/
};

/** \details
  This template class is a specialization of the OdArray class for
  OdNwFullSubentPath object pointers.
*/
typedef OdArray<OdNwFullSubentPath> OdNwFullSubentPathArray;

#endif // _NW_DBSUBENT_H



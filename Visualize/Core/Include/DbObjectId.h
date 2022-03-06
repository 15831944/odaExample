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


#ifndef _ODDBOBJECTID_INCLUDED_
#define _ODDBOBJECTID_INCLUDED_ /* {Secret } */

#include "DbExport.h"
#include "DbHandle.h"
#include "OdError.h"
#include "TD_PackPush.h"

class OdTvDbDatabase;
class OdTvDbObject;
class OdRxClass;

template <class T> class OdSmartPtr;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbObject object pointers.
*/
typedef OdSmartPtr<OdTvDbObject> OdTvDbObjectPtr;

class OdDbStub;
class OdTvDbStubExt;

/** \details
  
    <group TD_Namespaces>
*/
namespace OdDb
{
  enum OpenMode
  {
    kNotOpen           = -1,  // Object is not open.
    kForRead           = 0,   // Object is open for reading.
    kForWrite          = 1,   // Object is open for reading and/or writing.
    kForNotify         = 2    // Object is open for notify.
  };
}

/** \details
    This class implements memory-resident ObjectId objects for OdTvDbDatabase objects.  

    \remarks
    Database objects reference
    other database objects using ObjectId objects, and a database object pointer
    can always be obtained from a valid ObjectId objects. The effect of this mechanism is
    that database objects do not have to reside in memory unless they are explicitly
    being examined or modified by the user.  
    
    The user must explicitly open an object
    before reading or writing to it, and should release it when the operation
    is completed.  This functionality allows the Drawings to support partial loading of 
    a database, where ObjectId objects exist for all objects in the database, but 
    the actual database objects need not be loaded until they are accessed.  
    It also allows database objects that are not in use to be swapped out of memory, 
    and loaded back in when they are accessed.  ObjectId objects are not written out to a 
    DWG/DXF file.  If a reference must be preserved to a database object that has been 
    serialized, the object's database handle (OdDbHandle) should be used.

    \sa
    * OdDbHandle
    * OdTvDbObject

    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectId
{
public:
  /** \remarks
    This function guarantees that isNull() will 
    return true if it is the first operation applied to this instance.
  */
  OdTvDbObjectId () : m_Id (0) { }

  /** \details
    For internal use only. 
  */

  /*!DOM*/
  OdTvDbObjectId (
    OdDbStub* objectId) : m_Id (objectId) { }

  /** \details
    The null ObjectId object.
  */
  TOOLKIT_EXPORT_STATIC static const OdTvDbObjectId kNull;

  /** \details
    Returns true and only if this ObjectId object is null.
  */
  bool isNull () const { return m_Id == 0; }

  /** \details
    Sets this Object ID to null.
  */
  void setNull () { m_Id = 0; }

  /** \details
    Returns true and only if this ObjectId object references a valid object.
  */
  bool isValid () const;

  // VS2015 requires to create copy constructor explicity
#if defined(_MSC_VER) && (_MSC_VER > 1800)
  OdTvDbObjectId(const OdTvDbObjectId& objectId) = default;
  OdTvDbObjectId& operator = (const OdTvDbObjectId& objectId) = default;
#endif

  /*!DOM*/

  OdTvDbObjectId& operator = (
    OdDbStub* objectId) { m_Id = objectId; return *this; }

  bool operator < (
    const OdTvDbObjectId& objectId) const;

  bool operator > (
    const OdTvDbObjectId& objectId) const;

  bool operator >= (
    const OdTvDbObjectId& objectId) const;

  bool operator <= (
    const OdTvDbObjectId& objectId) const;

  bool operator == (
    const OdTvDbObjectId& objectId) const;

  bool operator != (
    const OdTvDbObjectId& objectId) const;

  bool operator ! () const { return isNull(); }

  /** \details
    For internal use only.
  */
  
  /*!DOM*/
  inline operator OdDbStub* () const { return (OdDbStub*)m_Id; }

  /** \details
    For internal use only. 
  */
  
  /*!DOM*/
  inline OdTvDbStubExt* operator -> () const { return (OdTvDbStubExt*)m_Id; }

  /** \details
    Returns the database with which this ObjectId object is associated.
    
    \remarks
    Returns NULL if this ObjectId object is not associated with any database.
  */
  OdTvDbDatabase* database () const;

  /** \details
    Returns the original database with which this ObjectId object is associated.
    
    \remarks
    If the object associated with this ObjectId object has been redirected to
    a host database from an Xref database, this function returns
    a pointer to the Xref database. 
    
    Otherwise, it returns a pointer to the database with which this ObjectId object is associated.
  */
  OdTvDbDatabase* originalDatabase () const;

  /** \details
    If this ObjectId object has been redirected from another database (possibly an Xref), this function
    returns the actual ObjectId object for that database.
  */
  void convertToRedirectedId ();

  /** \details
    Returns true if and only if the object associated with this ObjectId object is erased.
  */
  bool isErased () const;

  /** \details
    Returns true if and only if this object associated with this ObjectId object is erased, or any of its ownership hierarchy
    have been erased.
  */
  bool isEffectivelyErased () const;

  /** \details
    For internal use only. 
  */
  
  /*!DOM*/
  bool objectLeftOnDisk () const;

  /** \details
    Returns the database handle of the object referenced by this ObjectId object.
    
    \remarks
    Returns NULL if no database object is referenced by this ObjectId object.

    If this ObjectId object has been redirected from another database (possibly an Xref), this function
    returns the handle for this database.
  */
  const OdDbHandle& getHandle () const;

  /** \details
    Returns the database handle of the object referenced by this ObjectId object.
    
    \remarks
    Returns NULL if no database object is referenced by this ObjectgId object.

    If this ObjectId object has been redirected from another database (possibly an Xref), this function
    returns the handle for the original database.
  */
  const OdDbHandle& getNonForwardedHandle () const;

  /** \details
    Opens the database object associated with this ObjectId object, in the specified mode.

    \param pObj [out]  Smart pointer to opened object
    \param openMode [in]  Mode in which to open the object.
    \param openErasedOne [in]  If and only if true, erased objects will be opened.

    \returns
    Returns eOk if successful, otherwise an Error Code.
    
    openMode must be one of the following:
    
    <table>
    Name                Value     Description
    OdDb::kForRead      0         Object is open for reading.
    OdDb::kForWrite     1         Object is open for reading and/or writing.
    OdDb::kForNotify    2         Object is open for notify.
    </table>
    
  */
  OdResult openObject (
    OdTvDbObjectPtr& pObj,
    OdDb::OpenMode openMode = OdDb::kForRead, 
    bool openErasedOne = false) const;
  /** \details
    Opens the database object associated with this ObjectId object, in the specified mode.

    \param openMode [in]  Mode in which to open the object.
    \param openErasedOne [in]  If and only if true, erased objects will be opened.

    \returns
    Returns a SmartPointer to the opened object if successful, otherwise a null SmartPointer.
    
    \remarks
    openMode must be one of the following:
    
    <table>
    Name                Value     Description
    OdDb::kForRead      0         Object is open for reading.
    OdDb::kForWrite     1         Object is open for reading and/or writing.
    OdDb::kForNotify    2         Object is open for notify.
    </table>
    
  */
  OdTvDbObjectPtr openObject (
    OdDb::OpenMode openMode = OdDb::kForRead, 
    bool openErasedOne = false) const;
  /** \details
    Opens the database object associated with this ObjectId object, in the specified mode, or throws and exception if unsucessful.

    \param openMode [in]  Mode in which to open the object.
    \param openErasedOne [in]  If and only if true, erased objects will be opened.

    \returns
    Returns a SmartPointer to the opened object.
    
    \remarks
    openMode must be one of the following:
    
    <table>
    Name                Value     Description
    OdDb::kForRead      0         Object is open for reading.
    OdDb::kForWrite     1         Object is open for reading and/or writing.
    OdDb::kForNotify    2         Object is open for notify.
    </table>

    Throws:
    
    <table>
    Exception           Cause
    eNullObjectId       This ObjectId object is null.
    ePermanentlyErased  Not opened and openErasedOne == 1
    eWasErased          Not opened and openErasedOne == 0
    </table>
    
  */
    OdTvDbObjectPtr safeOpenObject (
    OdDb::OpenMode openMode = OdDb::kForRead, 
    bool openErasedOne = false) const;

  /** \details
    Binds the specified object.
    
    \param pObj [in]  Pointer to the object to bind.
  */
  void bindObject (
    OdTvDbObject* pObj);

  OdRxClass* objectClass() const;

protected:
  friend class OdDbStub;
  OdDbStub* m_Id;
};

/*class TOOLKIT_EXPORT OdDbObjectId : public OdTvDbObjectId
{

};*/

/** \details
    This class is a specialization of OdTvDbObjectId indicating a hard owner relationship.

    \remarks
    An OdTvDbHardOwnershipId reference to another object is used when the owner requires the owned
    object, and the owned object cannot exist on its own.
    
    An OdTvDbHardOwnershipId reference to an object dictates that the owned object is written to 
    .dwg and .dxf files whenever the owner object is written.
    
    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbHardOwnershipId : public OdTvDbObjectId
{
public:

  OdTvDbHardOwnershipId () {}

  OdTvDbHardOwnershipId (
    const OdTvDbObjectId& objectId) : OdTvDbObjectId (objectId) {}

  /*!DOM*/
  OdTvDbHardOwnershipId (
    OdDbStub* objectId) : OdTvDbObjectId (objectId) {}

  OdTvDbHardOwnershipId& operator = (
    const OdTvDbObjectId& objectId) { OdTvDbObjectId::operator= (objectId); return *this; }


  /*!DOM*/
  OdTvDbHardOwnershipId& operator = (
    OdDbStub* objectId) { m_Id = objectId; return *this; }

  bool operator != (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  /*!DOM*/
  bool operator != (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  bool operator == (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator== (objectId); }

  /*!DOM*/
  bool operator == (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator== (objectId); }
};

/** \details
    This class is a specialization of OdTvDbObjectId indicating a soft owner relationship.

    \remarks
    An OdTvDbSoftOwnershipId reference to another object is used when the owner does not requires the owned
    object, and the owned object cannot exist on its own.

    An OdTvDbSoftOwnershipId reference to an object dictates that the owned object is written to 
    .dwg and .dxf files whenever the owner object is written.
    
    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbSoftOwnershipId : public OdTvDbObjectId
{
public:

  OdTvDbSoftOwnershipId () {}

  OdTvDbSoftOwnershipId (
    const OdTvDbObjectId& objectId) : OdTvDbObjectId (objectId) {}

  /*!DOM*/
  OdTvDbSoftOwnershipId (
    OdDbStub* objectId) : OdTvDbObjectId (objectId) {}

  OdTvDbSoftOwnershipId& operator = (
    const OdTvDbObjectId& objectId) { OdTvDbObjectId::operator= (objectId); return *this; }

  /*!DOM*/
  OdTvDbSoftOwnershipId& operator = (
    OdDbStub* objectId) { m_Id = objectId; return *this; }
    
  bool operator != (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  /*!DOM*/
  bool operator != (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  bool operator == (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator== (objectId); }

  /*!DOM*/
  bool operator == (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator== (objectId); }

};

/** \details
    This class is a specialization of OdTvDbObjectId indicating a hard pointer relationship.

    \remarks
    An OdTvDbHardPointerId reference to another object is used when one object depends on the existance of another, but
    both are owned by other objects.

    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbHardPointerId : public OdTvDbObjectId
{
public:

  OdTvDbHardPointerId () {}

  OdTvDbHardPointerId (
    const OdTvDbObjectId& objectId) : OdTvDbObjectId (objectId) {}

  /*!DOM*/
  OdTvDbHardPointerId (
    OdDbStub* objectId) : OdTvDbObjectId (objectId) {}

  OdTvDbHardPointerId& operator = (
    const OdTvDbHardPointerId& objectId) { OdTvDbObjectId::operator= (objectId); return *this; }

  OdTvDbHardPointerId& operator = (
    const OdTvDbObjectId& objectId) { OdTvDbObjectId::operator= (objectId); return *this; }

  /*!DOM*/
  OdTvDbHardPointerId& operator = (
    OdDbStub* objectId) { m_Id = objectId; return *this; }

  bool operator != (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  /*!DOM*/
  bool operator != (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  bool operator == (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator== (objectId); }

  /*!DOM*/
  bool operator == (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator== (objectId); }
};

/** \details
    This class is a specialization of OdTvDbObjectId indicating a soft pointer relationship.

    \remarks
    An OdTvDbSoftPointerId reference another object is used when neither object depends on the existance of the other.

    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbSoftPointerId : public OdTvDbObjectId
{
public:
  OdTvDbSoftPointerId () {}

  OdTvDbSoftPointerId (
    const OdTvDbObjectId& objectId) : OdTvDbObjectId (objectId) {}

  /*!DOM*/
  OdTvDbSoftPointerId (
    OdDbStub* objectId) : OdTvDbObjectId (objectId) {}

  OdTvDbSoftPointerId& operator = (
    const OdTvDbSoftPointerId& objectId) { OdTvDbObjectId::operator= (objectId); return *this; }

  OdTvDbSoftPointerId& operator = (
    const OdTvDbObjectId& objectId) { OdTvDbObjectId::operator= (objectId); return *this; }

  /*!DOM*/
  OdTvDbSoftPointerId& operator = (
    OdDbStub* objectId) { m_Id = (OdDbStub*)objectId; return *this; }

  bool operator != (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  /*!DOM*/
  bool operator != (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator!= (objectId); }

  bool operator == (
    const OdTvDbObjectId& objectId) const { return OdTvDbObjectId::operator== (objectId); }
  /*!DOM*/
  bool operator == (
    OdDbStub* objectId) const { return OdTvDbObjectId::operator== (objectId); }

};

#include "TD_PackPop.h"

#endif //_ODDBOBJECTID_INCLUDED_



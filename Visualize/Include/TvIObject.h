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

#ifndef _ODTV_COUNTEDOBJECT_H_INCLUDED_
#define _ODTV_COUNTEDOBJECT_H_INCLUDED_

#include "TD_PackPush.h"
#include "OdHeap.h"

#include "Tv.h"
#include "TvUserData.h"

class OdTvDatabaseId;

/** \details
  The base abstract interface class for Visualize SDK inserted objects.
*/
class OdTvIObject
{
//DOM-IGNORE-BEGIN
  template <class T> friend class OdTvSmartPtr;

  /** \details
    Creates an instance of the Visualize SKD object as a copy of an existing one (copy constructor). 
  */
  OdTvIObject(const OdTvIObject&);

  /** \details
    Assignment operator is prohibited.
    
    \returns Returns the reference to the object modified after the assignment operation.
  */
  OdTvIObject& operator = (const OdTvIObject&);

  /** \details
    Declares the method for incrementing the reference counter in objects derived from this class.
  */
  virtual void addRef() = 0;

  /** \details
    Declares the method for decrementing the reference counter in objects derived from this class.
  */
  virtual void release() = 0;

  /** \details
    Returns the value of the reference counter, that is, the number of references to an instance of this class.
  */
  virtual long numRefs() const = 0;

protected:
  /** \details
    Protects derived OdRxObject objects from direct use of new and delete operators. 
  */
  ODRX_HEAP_OPERATORS();
//DOM-IGNORE-END
  
public:
  /** \details
    Creates a new object with default content.
  */
  OdTvIObject(){}

  /** \details
    Destroys the object. 
  */
  virtual ~OdTvIObject(){}
};



/** \details
  The base class for the typified smart pointer to a Visualize SDK interface object.
*/
class ODTV_EXPORT OdTvBaseIObjectPtr
{
//DOM-IGNORE-BEGIN
protected:
  OdTvIObject* m_pObject;
  
  /** \details
    Creates a new smart pointer to the Visualize SDK interface object with default parameters. 
  */
  OdTvBaseIObjectPtr() : m_pObject(0) {}

  /** \details
    Creates a new smart pointer with a raw-pointer to a Visualize SDK interface object. 
    
    \param pSource [in] A raw pointer to a Visualize SDK interface object.
  */
  explicit OdTvBaseIObjectPtr(const OdTvIObject *pSource) : m_pObject(const_cast<OdTvIObject*>(pSource)) {}

  /** \details
    Throws an exception with a specified error code. 
    
    \param iCode [in] An error code represented with the <link OdTvResult, OdTvResult> value.
  */
  void odTvThrow(OdTvResult iCode) const;
//DOM-IGNORE-END

public:
  
  /** \details
    Retrieves whether the smart pointer is NULL or not. 
    
    \returns Returns true if the smart pointer is NULL; otherwise the method returns false. 
  */
  bool isNull() const { return m_pObject == 0; }
};

/** \details
  The template base class that provides the base implementation of a smart pointer to an instance of a class derived from the <link OdTvIObject, OdTvIObject> class.
  
  \remarks 
  The class throws an exception for the -> operator if the pointer to an object is NULL.
*/
template <class T> class OdTvSmartPtr : public OdTvBaseIObjectPtr
{
//DOM-IGNORE-BEGIN
protected:

  /** \details
    Increments the reference counter of the referenced object.
  */
  void internalAddRef()
  {
    if(m_pObject)
      m_pObject->addRef();
  }
  
  /** \details
    Assigns the pointer of the specified object to the smart pointer.  
    
    \param pObject [in]  Pointer to the specified object to be assigned.
    \remarks
    The reference counter of the specified object is incremented.
    If this SmartPointer is currently referencing another object, that object 
    is released prior to the assignment.  
  */
  void assign(const T* pObject)
  {
    if (m_pObject != pObject) // Prevent deleting object if nRefs=1
    {
      release();
      m_pObject = const_cast<T*>(pObject);
      internalAddRef();
    }
  }

  /** \details
    Returns the raw pointer to the referenced object.
    
    \remarks
    This class maintains the reference to the referenced object.
    The reference counter of the referenced object is not changed.
  */
  T* get() const { return static_cast<T*>(m_pObject); }
//DOM-IGNORE-END

public:

  /** \details
    Creates a new smart pointer to an instance of a class derived from the <link OdTvIObject, OdTvIObject> class with default parameters.
  */
  OdTvSmartPtr()
     : OdTvBaseIObjectPtr()
  {
  }

  /** \details
    Creates a new smart pointer to an instance of a class derived from the <link OdTvIObject, OdTvIObject> class with default parameters.
    
    \param pObject [in] A raw pointer to the object to be assigned with the new smart pointer.
    \remarks
    If the pObject parameter is specified, the smart pointer is set to the address of the specified object. 
    If the pObject is not specified, the smart pointer is set to NULL.
    If the OdRxObjMod parameter is specified, the reference counter of the specified object is not incremented. 
  */
  OdTvSmartPtr(const T* pObject, OdRxObjMod)
      :  OdTvBaseIObjectPtr(pObject)
  {
  }

  /** \details
    Creates a new smart pointer to an instance of a class derived from the <link OdTvIObject, OdTvIObject> class as a copy of an existing smart pointer (copy constructor).
    
    \param pObject [in] A smart pointer object to be copied.
  */
  OdTvSmartPtr(const OdTvSmartPtr& pObject)
    : OdTvBaseIObjectPtr (pObject.get())
  {
    internalAddRef();
  }
  
  /** \details
    Destroys the smart pointer to an instance of a class derived from the <link OdTvIObject, OdTvIObject> class.
  */
  ~OdTvSmartPtr()
  {
    release();
  }
      
  /** \details
    The assignment operator for the smart pointer object that increments the reference counter of the referenced object and saves its address in the smart pointer.
    
    \param pObject [in] A left operand of the assignment operation.
    \returns Returns the reference to the smart pointer object modified after the assignment operation.
    \remarks
    If the smart pointer is currently referencing another object, the assignment operator releases the referenced object before the assignment operation.  
  */
  OdTvSmartPtr& operator = (const OdTvSmartPtr& pObject)
  {
    assign(static_cast<const T*>(pObject.get()));
    return *this;
  }

  /** \details
    The de-referencing operator for the smart pointer object. 
    
    \returns Returns the raw pointer to the referenced object.
    \remarks
    The operator does not change the quantity of references to the referenced object.
    The operator throws the tvNullObjectPtr exception if the smart pointer does not refer to an object. 
  */
  T* operator ->()
  {
    if ( m_pObject == NULL )
      odTvThrow(tvNullObjectPtr);
    return static_cast<T*>(m_pObject);
  }

  /** \details
    The de-referencing operator for the smart pointer object. 
    
    \returns Returns the raw pointer to the referenced object. The object referred to by the pointer can not be modified. 
    \remarks
    The operator does not change the quantity of references to the referenced object.
    The operator throws the tvNullObjectPtr exception if the smart pointer does not refer to an object. 
  */
  const T* operator ->() const
  {
    if ( m_pObject == NULL )
      odTvThrow(tvNullObjectPtr);
    return static_cast<const T*>(m_pObject);
  }

  /** \details
    Releases the smart pointer reference to the referenced object.
    
    \remarks
    Decrements the reference counter of the referenced object. 
    When the reference count reaches zero, the referenced object is deleted and the smart pointer is set to the NULL value.
  */
  void release()
  {
    if (m_pObject)
    {
      m_pObject->release();
      m_pObject = 0;
    }
  }
};


/** \details
The base interface class for an identifier of an object link.
*/
class ODTV_EXPORT OdTvLinkId
{
public:

  /** \details
  Creates a new link object identifier with default parameters.
  */
  OdTvLinkId() : m_pMiscIdData(0), m_pLink(0) {}

  /** \details
  Creates a new link object identifier as a copy of an existing (copy constructor).
  \param linkId [in] A link object identifier to be copied.
  */
  OdTvLinkId(const OdTvLinkId& linkId);

  /** \details
  Destroys the link object identifier;
  */
  ~OdTvLinkId();

  /** \details
  Retrieves whether the link object identifier is NULL or not.
  \returns Returns true if the link object identifier is NULL; otherwise returns false.
  */
  bool isNull() const { return m_pLink == 0; }

  /** \details
    Resets the link object identifier. After resetting, the identifier value is equal to NULL.
  */
  void setNull();

  /** \details
    Checks whether the link object specified with the identifier refers to a valid object or not.
    
    \returns Returns true if the link object refers to a valid object; otherwise returns false.
  */
  bool isValid() const;

  /** \details
  The assignment operator for the link object identifier.
  \param linkId [in] A link object identifier as a left operand of the assignment operation.
  \returns Returns the reference to the link object identifier modified after the assignment operation.
  */
  OdTvLinkId& operator = (const OdTvLinkId& linkId);

  /** \details
  The less than operator for the identifier of a link object.
  \param linkId [in] A left operand for comparing.
  \returns Returns true if the identifier is less than the identifier specified with the objectId parameter; otherwise returns false.
  */
  bool operator < (const OdTvLinkId& linkId) const;

  /** \details
  The greater than operator for the identifier of a link object.
  \param linkId [in] A left operand for comparing.
  \returns Returns true if the identifier is greater than the identifier specified with the objectId parameter; otherwise returns false.
  */
  bool operator > (const OdTvLinkId& linkId) const;

  /** \details
  The greater than or equal to operator for the identifier of a link object.
  \param linkId [in] A left operand for comparing.
  \returns Returns true if the identifier is greater than or equal to the identifier specified with the objectId parameter; otherwise returns false.
  */
  bool operator >= (const OdTvLinkId& linkId) const;

  /** \details
  The less than or equal to operator for the identifier of a link object.
  \param linkId [in] A left operand for comparing.
  \returns Returns true if the identifier is less than or equal to the identifier specified with the objectId parameter; otherwise returns false.
  */
  bool operator <= (const OdTvLinkId& linkId) const;

  /** \details
  The equal operator for the identifier of a link object.
  \param linkId [in] A left operand for comparing.
  \returns Returns true if the identifier is equal to the identifier specified with the objectId parameter; otherwise returns false.
  */
  bool operator == (const OdTvLinkId& linkId) const;

  /** \details
  The non-equal operator for the identifier of a link object.
  \param linkId [in] A left operand for comparing.
  \returns Returns true if the identifier is not equal to the identifier specified with the objectId parameter; otherwise returns false.
  */
  bool operator != (const OdTvLinkId& linkId) const;

  //DOM-IGNORE-BEGIN
protected:
  // pointer to object's link
  void*             m_pLink;
  // pointer to miscallenious
  void*             m_pMiscIdData;
  //DOM-IGNORE-END
};

/** \details
  The base abstract interface class for objects with user custom data support.
*/
class OdTvIObjectWithXdata : public OdTvIObject
{
public:

  /** \details
    Appends new user data to the object. 
    
    \param pUserData [in] A raw pointer to the user data. 
    \param id        [in] An identifier of the registered application that should process the user data. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the user data was successfully appended, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult appendUserData(OdTvUserData* pUserData, const OdTvRegAppId& id) = 0;

  /** \details
    Retrieves the current user data from the object for a specified application. 
    
    \param id [in] An identifier of the registered application that should process the user data.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a raw pointer to the user data. 
    \remarks 
    If the rc parameter is not null and the user data was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvUserData* getUserData(const OdTvRegAppId& id, OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the quantity of the user data instances that the object contains.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of user data instances. 
    \remarks 
    If the rc parameter is not null and the user data instances quantity was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getUserDataCount(OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the list of registered applications associated with the user data instances that the object contains. 
    
    \param ids [out] A placeholder for an array of registered application identifiers. The method fills this array and returns it to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the array of application identifiers was successfully filled and returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getUserDataApps(OdTvRegAppIdArray& ids) = 0;

  /** \details
    Removes all user data associated with a specified registered application.
    
    \param id [in] An identifier of a registered application.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If all instances of user data associated with the specified application were successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeUserData(const OdTvRegAppId& id) = 0;

  /** \details
    Removes all user data that the object contains.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If all instances of user data were successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clearUserData() = 0;
};


/** \details
  The abstract interface class for an object that supports database handles.
*/
class OdTvHandledIObject : public OdTvIObjectWithXdata
{
public:

  /** \details 
    Retrieves the current database handle associated with the object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the handle of the database associated with the object.
    \remarks 
    If the rc parameter is not null and the database handle value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt64 getDatabaseHandle(OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the native database handle associated with the object. Valid for the objects received during using of the Visualize import extension.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the handle at the native database associated with the object or -1 if such handle is not stored in the object's user data
    \remarks
    If the rc parameter is not null and the database handle value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt64 getNativeDatabaseHandle(OdTvResult* rc = NULL) = 0;

  /** \details 
    Retrieves the current database identifier associated with the object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the database associated with the object.
    \remarks 
    If the rc parameter is not null and the database identifier was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvDatabaseId getDatabase(OdTvResult* rc = NULL) = 0;
};

#include "TD_PackPop.h"


#endif // _ODTV_H_INCLUDED_


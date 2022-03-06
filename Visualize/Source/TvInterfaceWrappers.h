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

#ifndef _ODTV_INTERFACEWRAPPERS_H_INCLUDED_
#define _ODTV_INTERFACEWRAPPERS_H_INCLUDED_

#include "TD_PackPush.h"

/** \details
Memory checker
*/
void newWrapper();
void deleteWrapper();
#ifdef _DEBUG
  //#define ODTV_MEMORYCHECK
#endif

/** \details

    This class needs for internal using since we need the public 'get' method and 'operator =' with the simple pointer to the object.
    These methods needs for using in interface wrappers functionality
*/
template <class T> class OdTvSmartPtrInternal : public OdTvSmartPtr<T>
{  
public:

   /** \details
    Assigns the pointer of specified object to the smart pointer.  
  */
  void assign(const T* pObject)
  {
    OdTvSmartPtr<T>::assign(pObject);
  }

  /** \details
    Releases the smart pointer reference to the referenced object. 
  */
  void release()
  {
    OdTvSmartPtr<T>::release();
  }

  /** \details
  Returns the raw pointer to the referenced object.

  \remarks
  This class maintains the reference to the referenced object.
  The reference counter of the referenced object is not changed.
  */
  T* get() const
  {
    return OdTvSmartPtr<T>::get();
  }

  /** \details
    Constructors for the typified smart pointer.
  */

  OdTvSmartPtrInternal()
     : OdTvSmartPtr<T>()
  {
  }

  OdTvSmartPtrInternal(const T* pObject, OdRxObjMod rxObjMod)
     : OdTvSmartPtr<T> (pObject, rxObjMod)
  {
  }
      
  OdTvSmartPtrInternal(const OdTvSmartPtr<T>& pObject)
    : OdTvSmartPtr<T> (pObject)
  {
  }
  
  /** \details
    Destructor for the typified smart pointer.
 
    \remarks
    Decrements the reference counter of the referenced object. When the reference count reaches zero, the referenced object is deleted.
  */
  ~OdTvSmartPtrInternal()
  {
    release();
  }
      
  /** \remarks
    The assignment operator increments the reference counter of the referenced object and saves its address in the smart pointer.
     If the smart pointer is currently referencing to another object, that assignment operator releases the referenced object prior 
     to the assignment.  

  */
  OdTvSmartPtrInternal& operator = (const OdTvSmartPtrInternal& pObject)
  {
    assign(static_cast<const T*>(pObject.get()));
    return *this;
  }

  OdTvSmartPtrInternal& operator = (const T* pObject)
  {
    assign(pObject);
    return *this;
  }

#ifdef ODA_GCC_2_95
  /** \details
    Returns the raw pointrer to the referenced object.
    
    \remarks
    The class maintains the reference to the referenced object.
    The reference counter of the referenced object is not changed.
  */
  operator T*() const
  {
    return const_cast<T*>(static_cast<const T*>(m_pObject));
  }
  
#else
  /** \details
    Returns the raw pointer the  referenced object.
    
    \remarks
    This SmartPointer maintains its reference to the referenced object.
    
    The reference counter of the referenced object is not changed.
  */
  operator T*()
  {
    return static_cast<T*>(this->m_pObject);
  }
  
  operator const T*() const
  {
    return static_cast<const T*>(this->m_pObject);
  }

#endif
};



/** \details
    Declares the simple checking for wrappers methods
*/

#define ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER                          \
  if ( m_pObjectImpl.isNull() )                                       \
  {                                                                   \
    return tvNullObjectPtr;                                          \
  }


/** \details
    Declares the second simple checking for wrappers methods
*/
#define ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER_1(ret)                    \
  if ( m_pObjectImpl.isNull() )                                        \
  {                                                                    \
    if ( rc )                                                          \
      *rc = tvNullObjectPtr;                                          \
    return ret;                                                        \
  }                                                                     


/** \details
    Declares the common variables and methods for all wrapper objects
*/

#define ODTV_DEFINE_WRAPPERS_MEMBERS_DECL(ClassName)                                                 \
private:                                                                                             \
  /** \details Smart pointer to the database object*/                                                \
  ClassName##ImplPtr m_pObjectImpl;                                                                  \
  /** \details Counter for using inside smart pointer*/                                              \
  OdRefCounter m_nRefCounter;                                                                        \
  /** \details Indicates that this object stored in the pool*/                                       \
  bool m_bOwnByPool;                                                                                 \
  /** \details Assignment operator prohibited. */                                                    \
  ClassName##Wrapper& operator = (const ClassName##Wrapper&);                                        \
  /** \details Constructor.*/                                                                        \
  ClassName##Wrapper(bool bForPool, ClassName##Impl* pImpl);                                         \
  /** \details Destructor*/                                                                          \
  ~ClassName##Wrapper();                                                                             \
                                                                                                     \
public:                                                                                              \
  /** \details assign the database object */                                                         \
  void assign(ClassName##Impl* pImpl);                                                               \
  /** \details Releases the reference to the database object.  */                                    \
  void releaseImpl();                                                                                \
  /** \details Increments the reference counter. */                                                  \
  void addRef();                                                                                     \
  /** \details Decrements the reference counter, checks the reference counter, and remove*/          \
     /*the instance when the reference counter reaches zero or the database object reference*/       \
     /*when the reference counter reaches one*/                                                      \
  void release();                                                                                    \
  /** \details Checks that the object already has associated dagtabase object */                     \
  bool isBusy() const;                                                                               \
  /** \details Returns the number of references to an instance of this class.*/                      \
  long numRefs() const;                                                                              \
  /** \details It is the pseudo-constructor that creates an instance of this class*/                 \
     /* and returns the typified smart pointer to it.*/                                              \
  static OdTvSmartPtr<ClassName> createObject(bool bForPool, ClassName##Impl* pImpl = NULL);                                                                                                                                        


/** \details
    Implements the common methods for all wrapper objects
*/
#define ODTV_DEFINE_WRAPPERS_MEMBERS_IMPL(ClassName)                                                        \
/** \details Constructor */                                                                                 \
ClassName##Wrapper::ClassName##Wrapper(bool bForPool, ClassName##Impl* pImpl)                               \
{                                                                                                           \
  m_nRefCounter = 1;                                                                                        \
  m_bOwnByPool = bForPool;                                                                                  \
  if ( pImpl )                                                                                              \
    m_pObjectImpl = pImpl;                                                                                  \
  newWrapper();                                                                                             \
}                                                                                                           \
/** \details Destructor */                                                                                  \
ClassName##Wrapper::~ClassName##Wrapper()                                                                   \
{                                                                                                           \
  m_nRefCounter = 0;                                                                                        \
  deleteWrapper();                                                                                          \
}                                                                                                           \
/** \details assign the database object */                                                                  \
void ClassName##Wrapper::assign(ClassName##Impl* pImpl)                                                     \
{                                                                                                           \
  if ( pImpl )                                                                                              \
    m_pObjectImpl = pImpl;                                                                                  \
}                                                                                                           \
/** \details Releases the reference to the database object.  */                                             \
void ClassName##Wrapper::releaseImpl()                                                                      \
{                                                                                                           \
  if ( !m_pObjectImpl.isNull() )                                                                            \
  {                                                                                                         \
    m_pObjectImpl.release();                                                                                \
  }                                                                                                         \
}                                                                                                           \
/** \details Increments the reference counter. */                                                           \
void ClassName##Wrapper::addRef()                                                                           \
{                                                                                                           \
  ++m_nRefCounter;                                                                                          \
}                                                                                                           \
/** \details Decrements the reference counter, checks the reference counter, and remove*/                   \
     /*the instance when the reference counter reaches zero or the database object reference*/              \
     /*when the reference counter reaches one*/                                                             \
void ClassName##Wrapper::release()                                                                          \
{                                                                                                           \
  ODA_ASSERT((m_nRefCounter > 0));                                                                          \
  if (!(--m_nRefCounter))                                                                                   \
  {                                                                                                         \
    if (!m_bOwnByPool)                                                                                      \
      releaseImpl();                                                                                        \
    delete this;                                                                                            \
  }                                                                                                         \
  else if ( m_nRefCounter == 1 && m_bOwnByPool) /*we should  release the database object*/                  \
    releaseImpl();                                                                                          \
}                                                                                                           \
/** \details Returns the number of references to an instance of this class.*/                               \
bool ClassName##Wrapper::isBusy() const { return numRefs() > 1; }                                           \
/** \details Returns the number of references to an instance of this class.*/                               \
long ClassName##Wrapper::numRefs() const { return m_nRefCounter; }                                          \
/** \details It is the pseudo-constructor that creates an instance of this class*/                          \
     /* and returns the typified smart pointer to it.*/                                                     \
OdTvSmartPtr<ClassName> ClassName##Wrapper::createObject(bool bForPool, ClassName##Impl* pImpl)             \
{                                                                                                           \
  return OdTvSmartPtr<ClassName>(static_cast<ClassName*>(new ClassName##Wrapper(bForPool,pImpl)), kOdRxObjAttach);  \
}



/** \details
    Declares the common variables and methods for all geometrical data wrapper objects
*/

#define ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_DECL(ClassName)                                          \
private:                                                                                              \
  /** \details Smart pointer to the geo data object*/                                                 \
  ClassName##ImplPtr m_pObjectImpl;                                                                   \
  /** \details Smart pointer to the parent entity*/                                                   \
  OdTvEntityImplPtr m_pParentEntity;                                                                  \
  /** \details Counter for using inside smart pointer*/                                               \
  OdRefCounter m_nRefCounter;                                                                         \
  /** \details Indicates that this object stored in the pool*/                                        \
  bool m_bOwnByPool;                                                                                  \
  /** \details Assignment operator prohibited. */                                                     \
  ClassName##Wrapper& operator = (const ClassName##Wrapper&);                                         \
  /** \details Constructor.*/                                                                         \
  ClassName##Wrapper(bool bForPool, ClassName##Impl* pImpl, const OdTvDbObjectId& parentEntityId);      \
  /** \details Destructor*/                                                                           \
  ~ClassName##Wrapper();                                                                              \
                                                                                                      \
public:                                                                                               \
  /** \details assign the database object */                                                          \
  void assign(ClassName##Impl* pImpl);                                                                \
  /** \details assign the parent entity object */                                                     \
  void assignEntity(const OdTvDbObjectId& parentEntityId);                                              \
  /** \details Releases the reference to the database object.  */                                     \
  void releaseImpl();                                                                                 \
  /** \details Increments the reference counter. */                                                   \
  void addRef();                                                                                      \
  /** \details Decrements the reference counter, checks the reference counter, and remove*/           \
     /*the instance when the reference counter reaches zero or the database object reference*/        \
     /*when the reference counter reaches one*/                                                       \
  void release();                                                                                     \
  /** \details Checks that the object already has associated dagtabase object */                      \
  bool isBusy() const;                                                                                \
  /** \details Returns the number of references to an instance of this class.*/                       \
  long numRefs() const;                                                                               \
  /** \details It is the pseudo-constructor that creates an instance of this class*/                  \
     /* and returns the typified smart pointer to it.*/                                               \
  static OdTvSmartPtr<ClassName> createObject(bool bForPool, ClassName##Impl* pImpl, const OdTvDbObjectId& parentEntityId); \
  /** \details Need for control modifiying of the object*/                                            \
  void doBeforeChange();                                                                              \
  void doAfterChange();           


/** \details
    Implements the common methods for all geometrical data wrapper objects
*/
#define ODTV_DEFINE_GEODATA_WRAPPERS_MEMBERS_IMPL(ClassName)                                                \
/** \details Constructor */                                                                                 \
ClassName##Wrapper::ClassName##Wrapper(bool bForPool, ClassName##Impl* pImpl, const OdTvDbObjectId& parentEntityId) \
{                                                                                                           \
  m_nRefCounter = 1;                                                                                        \
  m_bOwnByPool = bForPool;                                                                                  \
  if ( pImpl )                                                                                              \
    m_pObjectImpl = pImpl;                                                                                  \
  if ( parentEntityId.isValid() )                                                                           \
    m_pParentEntity = parentEntityId.openObject(OdDb::kForRead);                                            \
  newWrapper();                                                                                             \
}                                                                                                           \
/** \details Destructor */                                                                                  \
ClassName##Wrapper::~ClassName##Wrapper()                                                                   \
{                                                                                                           \
  m_nRefCounter = 0;                                                                                        \
  deleteWrapper();                                                                                          \
}                                                                                                           \
/** \details assign the database object */                                                                  \
void ClassName##Wrapper::assign(ClassName##Impl* pImpl)                                                     \
{                                                                                                           \
  if ( pImpl )                                                                                              \
    m_pObjectImpl = pImpl;                                                                                  \
}                                                                                                           \
/** \details assign the parent entity object */                                                             \
void ClassName##Wrapper::assignEntity(const OdTvDbObjectId& parentEntityId)                                   \
{                                                                                                           \
  if ( parentEntityId.isValid() )                                                                           \
    m_pParentEntity = parentEntityId.openObject(OdDb::kForRead);                                            \
}                                                                                                           \
/** \details Releases the reference to the database object.  */                                             \
void ClassName##Wrapper::releaseImpl()                                                                      \
{                                                                                                           \
  if ( !m_pObjectImpl.isNull() )                                                                            \
  {                                                                                                         \
    m_pObjectImpl.release();                                                                                \
  }                                                                                                         \
  if ( !m_pParentEntity.isNull() )                                                                          \
  {                                                                                                         \
    m_pParentEntity.release();                                                                              \
  }                                                                                                         \
}                                                                                                           \
/** \details Increments the reference counter. */                                                           \
void ClassName##Wrapper::addRef()                                                                           \
{                                                                                                           \
  ++m_nRefCounter;                                                                                          \
}                                                                                                           \
/** \details Decrements the reference counter, checks the reference counter, and remove*/                   \
     /*the instance when the reference counter reaches zero or the database object reference*/              \
     /*when the reference counter reaches one*/                                                             \
void ClassName##Wrapper::release()                                                                          \
{                                                                                                           \
  ODA_ASSERT((m_nRefCounter > 0));                                                                          \
  if (!(m_nRefCounter - 1) )  /*MT support*/                                                                \
  {                                                                                                         \
    if (!m_bOwnByPool)                                                                                      \
      releaseImpl();                                                                                        \
    --m_nRefCounter;                                                                                        \
    delete this;                                                                                            \
    return;                                                                                                 \
  }                                                                                                         \
  else if ( (m_nRefCounter -1 ) == 1 && m_bOwnByPool) /*we should  release the database object*/            \
  {                                                                                                         \
    releaseImpl();                                                                                          \
  }                                                                                                         \
  --m_nRefCounter;                                                                                          \
}                                                                                                           \
/** \details Returns the number of references to an instance of this class.*/                               \
bool ClassName##Wrapper::isBusy() const { return numRefs() > 1; }                                           \
/** \details Returns the number of references to an instance of this class.*/                               \
long ClassName##Wrapper::numRefs() const { return m_nRefCounter; }                                          \
/** \details It is the pseudo-constructor that creates an instance of this class*/                          \
     /* and returns the typified smart pointer to it.*/                                                     \
OdTvSmartPtr<ClassName> ClassName##Wrapper::createObject(bool bForPool, ClassName##Impl* pImpl, const OdTvDbObjectId& parentEntityId)                           \
{                                                                                                           \
  return OdTvSmartPtr<ClassName>(static_cast<ClassName*>(new ClassName##Wrapper(bForPool, pImpl,parentEntityId)), kOdRxObjAttach);  \
}                                                                                                            \
void ClassName##Wrapper::doBeforeChange()                                                                    \
{                                                                                                            \
  if ( m_pParentEntity->isReadEnabled() )                                                                    \
  {                                                                                                          \
    m_pParentEntity->upgradeOpen();                                                                          \
  }                                                                                                          \
}                                                                                                            \
void ClassName##Wrapper::doAfterChange()                                                                     \
{                                                                                                            \
  /* mark first parent with gs-node as modified object*/                                                     \
  odTvNotifyFirstParentWithGsNode(m_pParentEntity->objectId());                                             \
}

#define BEFORE_CHANGE                                       \
  bool isNotify = false;                                    \
  OdDbDatabaseTvPtr pDb = m_pParentEntity->database();      \
  if (!pDb.isNull() && !pDb->getSilentMode())               \
  {                                                         \
    doBeforeChange();                                       \
    isNotify = true;                                        \
  }                                                         

#define AFTER_CHANGE                                        \
  if (isNotify)                                             \
    doAfterChange();                                        


/** \details
    Declares the common variables and methods for all wrapper objects
*/

#define ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(IClassName, DBClassName)                                               \
private:                                                                                                            \
  /** \details Smart pointer to the wrapped DB object*/                                                             \
  DBClassName##Ptr m_pObjectImpl;                                                                                   \
  /** \details Counter for using inside smart pointer*/                                                             \
  OdRefCounter m_nRefCounter;                                                                                       \
  /** \details Indicates that this object stored in the pool*/                                                      \
  bool m_bOwnByPool;                                                                                                \
  /** \details Assignment operator prohibited. */                                                                   \
  IClassName##Wrapper& operator = (const IClassName##Wrapper&);                                                     \
  /** \details Constructor.*/                                                                                       \
  IClassName##Wrapper(bool bForPool, const OdTvDbObjectId& wrappedObjId, OdDb::OpenMode mode = OdDb::kForRead);       \
  /** \details Destructor*/                                                                                         \
  ~IClassName##Wrapper();                                                                                           \
                                                                                                                    \
public:                                                                                                             \
  /** \details assign the database object */                                                                        \
  void assign(const OdTvDbObjectId& wrappedObjId, OdDb::OpenMode mode = OdDb::kForRead);                              \
  /** \details Releases the reference to the database object.  */                                                   \
  void releaseWrappedDbObj();                                                                                       \
  /** \details Increments the reference counter. */                                                                 \
  void addRef();                                                                                                    \
  /** \details Decrements the reference counter, checks the reference counter, and remove*/                         \
     /*the instance when the reference counter reaches zero or the database object reference*/                      \
     /*when the reference counter reaches one*/                                                                     \
  void release();                                                                                                   \
  /** \details Checks that the object already has associated dagtabase object */                                    \
  bool isBusy() const;                                                                                              \
  /** \details Returns the number of references to an instance of this class.*/                                     \
  long numRefs() const;                                                                                             \
  /** \details It is the pseudo-constructor that creates an instance of this class*/                                \
     /* and returns the typified smart pointer to it.*/                                                             \
  static OdTvSmartPtr<IClassName> createObject(bool bForPool, const OdTvDbObjectId& wrappedObjId, OdDb::OpenMode mode = OdDb::kForRead);


/** \details
    Implements the common methods for all wrapper objects
*/
#define ODTV_DEFINE_WRAPPERS_DB_MEMBERS_IMPL(IClassName)                                                                        \
/** \details Constructor */                                                                                                     \
IClassName##Wrapper::IClassName##Wrapper(bool bForPool, const OdTvDbObjectId& wrappedObjId, OdDb::OpenMode mode)                  \
{                                                                                                                               \
  m_nRefCounter = 1;                                                                                                            \
  m_bOwnByPool = bForPool;                                                                                                      \
  if ( wrappedObjId.isValid() )                                                                                                 \
    m_pObjectImpl = wrappedObjId.openObject(mode);                                                                              \
  newWrapper();                                                                                                                 \
}                                                                                                                               \
/** \details Destructor */                                                                                                      \
IClassName##Wrapper::~IClassName##Wrapper()                                                                                     \
{                                                                                                                               \
  m_nRefCounter = 0;                                                                                                            \
  deleteWrapper();                                                                                                              \
}                                                                                                                               \
/** \details assign the database object */                                                                                      \
void IClassName##Wrapper::assign(const OdTvDbObjectId& wrappedObjId, OdDb::OpenMode mode)                                         \
{                                                                                                                               \
  if ( wrappedObjId.isValid() )                                                                                                 \
    m_pObjectImpl = wrappedObjId.openObject(mode);                                                                              \
}                                                                                                                               \
/** \details Releases the reference to the database object.  */                                                                 \
void IClassName##Wrapper::releaseWrappedDbObj()                                                                                 \
{                                                                                                                               \
  if ( !m_pObjectImpl.isNull() )                                                                                                \
  {                                                                                                                             \
    m_pObjectImpl.release();                                                                                                    \
  }                                                                                                                             \
}                                                                                                                               \
/** \details Increments the reference counter. */                                                                               \
void IClassName##Wrapper::addRef()                                                                                              \
{                                                                                                                               \
  ++m_nRefCounter;                                                                                                              \
}                                                                                                                               \
/** \details Decrements the reference counter, checks the reference counter, and remove*/                                       \
     /*the instance when the reference counter reaches zero or the database object reference*/                                  \
     /*when the reference counter reaches one*/                                                                                 \
void IClassName##Wrapper::release()                                                                                             \
{                                                                                                                               \
  ODA_ASSERT((m_nRefCounter > 0));                                                                                              \
  if (!(m_nRefCounter - 1) )  /*MT support*/                                                                                    \
  {                                                                                                                             \
    if (!m_bOwnByPool)                                                                                                          \
      releaseWrappedDbObj();                                                                                                    \
    --m_nRefCounter;                                                                                                            \
    delete this;                                                                                                                \
    return;                                                                                                                     \
  }                                                                                                                             \
  else if ( (m_nRefCounter -1 ) == 1 && m_bOwnByPool) /*we should  release the database object*/                                \
  {                                                                                                                             \
    releaseWrappedDbObj();                                                                                                      \
  }                                                                                                                             \
  --m_nRefCounter;                                                                                                              \
}                                                                                                                               \
/** \details Returns the number of references to an instance of this class.*/                                                   \
bool IClassName##Wrapper::isBusy() const { return numRefs() > 1; }                                                              \
/** \details Returns the number of references to an instance of this class.*/                                                   \
long IClassName##Wrapper::numRefs() const { return m_nRefCounter; }                                                             \
/** \details It is the pseudo-constructor that creates an instance of this class*/                                              \
     /* and returns the typified smart pointer to it.*/                                                                         \
OdTvSmartPtr<IClassName> IClassName##Wrapper::createObject(bool bForPool, const OdTvDbObjectId& wrappedObjId, OdDb::OpenMode mode) \
{                                                                                                                               \
  return OdTvSmartPtr<IClassName>(static_cast<IClassName*>(new IClassName##Wrapper(bForPool, wrappedObjId, mode)), kOdRxObjAttach); \
}


/** \details
Implements the reference counter stuff for the iterators implementation
*/
#define ODTV_WRAPPERS_REFERENCE_MEMBERS()                                                                            \
/** \details   */                                                                                                               \
/*Declares the method incrementing the reference counter in objects derived from this class.*/                                  \
/**/                                                                                                                            \
void addRef()                                                                                                                   \
{                                                                                                                               \
  ++m_nRefCounter;                                                                                                              \
}                                                                                                                               \
/** \details*/                                                                                                                  \
/*Declares the method decrementing the reference counter in objects derived from this class.*/                                  \
/**/                                                                                                                            \
void release()                                                                                                                  \
{                                                                                                                               \
  if (m_nRefCounter == 1)                                                                                                       \
  {                                                                                                                             \
    delete this;                                                                                                                \
  }                                                                                                                             \
  else                                                                                                                          \
    --m_nRefCounter;                                                                                                            \
}                                                                                                                               \
/** \details*/                                                                                                                  \
/*Returns the value of the reference counter, that is, the number of references to an instance of this class.*/                 \
/**/                                                                                                                            \
long numRefs() const                                                                                                            \
{                                                                                                                               \
  return m_nRefCounter;                                                                                                         \
}

/** \details
Implements the custom user data stuff
*/
#define ODTV_DEFINE_XDATA_DECL(prefix)                                                                   \
/** \details */                                                                                          \
/*Append the user data to the entity*/                                                                   \
/**/                                                                                                     \
prefix OdTvResult appendUserData(OdTvUserData* pUserData, const OdTvRegAppId& id);                       \
/** \details*/                                                                                           \
/*Get user data*/                                                                                        \
/**/                                                                                                     \
prefix OdTvUserData* getUserData(const OdTvRegAppId& id, OdTvResult* rc = NULL);                         \
/** \details*/                                                                                           \
/*Get the count of the user data */                                                                      \
/**/                                                                                                     \
prefix OdUInt32 getUserDataCount(OdTvResult* rc = NULL);                                                 \
/** \details */                                                                                          \
/*All registered apps for which the user data is set*/                                                   \
/**/                                                                                                     \
prefix OdTvResult getUserDataApps(OdTvRegAppIdArray& ids);                                               \
/** \details */                                                                                          \
/*Removes user data */                                                                                   \
/**/                                                                                                     \
prefix OdTvResult removeUserData(const OdTvRegAppId& id);                                                \
/** \details*/                                                                                           \
/*Removes all user data */                                                                               \
/**/                                                                                                     \
prefix OdTvResult clearUserData();

/** \details
Implements the custom user data stuff
*/
#define ODTV_DEFINE_XDATA_WRAPPER_DEF(IClassName)                                                           \
OdTvResult IClassName##Wrapper::appendUserData(OdTvUserData* pUserData, const OdTvRegAppId& id)             \
{                                                                                                           \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER;                                                                      \
  return m_pObjectImpl->appendUserData(pUserData, id);                                                      \
}                                                                                                           \
OdTvUserData* IClassName##Wrapper::getUserData(const OdTvRegAppId& id, OdTvResult* rc)                      \
{                                                                                                           \
  OdTvUserData* pUserData = NULL;                                                                           \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER_1(pUserData);                                                         \
  if (rc)                                                                                                   \
    *rc = tvOk;                                                                                             \
                                                                                                            \
  return m_pObjectImpl->getUserData(id);                                                                    \
}                                                                                                           \
OdUInt32 IClassName##Wrapper::getUserDataCount(OdTvResult* rc)                                              \
{                                                                                                           \
  OdUInt32 nUserData = 0;                                                                                   \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER_1(nUserData);                                                         \
  if (rc)                                                                                                   \
    *rc = tvOk;                                                                                             \
                                                                                                            \
  return m_pObjectImpl->getUserDataCount();                                                                 \
}                                                                                                           \
OdTvResult IClassName##Wrapper::getUserDataApps(OdTvRegAppIdArray& ids)                                     \
{                                                                                                           \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER;                                                                      \
  m_pObjectImpl->getUserDataApps(ids);                                                                      \
                                                                                                            \
  return tvOk;                                                                                              \
}                                                                                                           \
OdTvResult IClassName##Wrapper::removeUserData(const OdTvRegAppId& id)                                      \
{                                                                                                           \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER;                                                                      \
  m_pObjectImpl->removeUserData(id);                                                                        \
                                                                                                            \
  return tvOk;                                                                                              \
}                                                                                                           \
OdTvResult IClassName##Wrapper::clearUserData()                                                             \
{                                                                                                           \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER;                                                                      \
  m_pObjectImpl->clearUserData();                                                                           \
                                                                                                            \
  return tvOk;                                                                                              \
}                                                                                                           \

/** \details
  Implements OdTvHandledIObject abstract method
*/
#define ODTV_DEFINE_HANDLED_OBJECT_DECL(prefix)                                                             \
public:                                                                                                     \
/** \details */                                                                                             \
/*Get DB object handle*/                                                                                    \
/**/                                                                                                        \
prefix OdUInt64 getDatabaseHandle(OdTvResult* rc = NULL);                                                   \
/** \details */                                                                                             \
/*Get native DB object handle*/                                                                             \
/**/                                                                                                        \
prefix OdUInt64 getNativeDatabaseHandle(OdTvResult* rc = NULL);                                             \
/** \details */                                                                                             \
/*Get database of this object*/                                                                             \
/**/                                                                                                        \
prefix OdTvDatabaseId getDatabase(OdTvResult* rc = NULL);

/** \details
  Implements OdTvHandledIObject abstract method
*/
#define ODTV_DEFINE_HANDLED_OBJECT_DEF(IClassName)                                                          \
OdUInt64 IClassName##Wrapper::getDatabaseHandle(OdTvResult* rc)                                             \
{                                                                                                           \
  OdUInt64 handle = 0;                                                                                      \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER_1(handle);                                                            \
  if (rc)                                                                                                   \
    *rc = tvOk;                                                                                             \
                                                                                                            \
  return (OdUInt64)m_pObjectImpl->getDbHandle();                                                            \
}                                                                                                           \
OdUInt64 IClassName##Wrapper::getNativeDatabaseHandle(OdTvResult* rc)                                       \
{                                                                                                           \
  OdUInt64 handle = 0;                                                                                      \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER_1(handle);                                                            \
  if (rc)                                                                                                   \
    *rc = tvOk;                                                                                             \
                                                                                                            \
  OdTvDatabaseId dbId = getDatabase();                                                                      \
  if (!dbId.isNull() && !m_pObjectImpl.isNull())                                                            \
  {                                                                                                         \
    bool alreadyExist = false;                                                                              \
    OdTvRegAppId appId = dbId.openObject()->registerAppName(L"ExGsVisualizeDevice", alreadyExist);          \
                                                                                                            \
    OdTvUserData* usrData = m_pObjectImpl->getUserData(appId);                                              \
    if (usrData)                                                                                            \
    {                                                                                                       \
      OdTvByteUserData *pUserData = dynamic_cast<OdTvByteUserData*>(usrData);                               \
      if (pUserData)                                                                                        \
      {                                                                                                     \
        OdUInt64 pData = *((OdUInt64*)pUserData->getData());                                                \
        odSwap8Bytes(&pData);                                                                               \
        return (OdInt64)pData;                                                                              \
      }                                                                                                     \
    }                                                                                                       \
  }                                                                                                         \
  return -1;                                                                                                \
}                                                                                                           \
OdTvDatabaseId IClassName##Wrapper::getDatabase(OdTvResult* rc)                                             \
{                                                                                                           \
  OdTvDatabaseId dbId;                                                                                      \
  if ( !m_pObjectImpl.isNull() )                                                                            \
  {                                                                                                         \
    OdTvDbDatabase* pDbDatabase = m_pObjectImpl->database();                                                \
    if (pDbDatabase)                                                                                        \
    {                                                                                                       \
      OdTvFactoryImplPtr factoryImplPtr = odTvGetFactoryImpl();                                             \
      if (!factoryImplPtr.isNull())                                                                         \
      {                                                                                                     \
        OdTvDatabaseImpl* pTvDatabase = factoryImplPtr->getTvDatabase(pDbDatabase);                         \
        if (pTvDatabase)                                                                                    \
        {                                                                                                   \
          OdTvLinkIdAccess<OdTvDatabaseImpl>::objectSet(&dbId, pTvDatabase);                                \
          if (rc)                                                                                           \
            *rc = tvOk;                                                                                     \
        }                                                                                                   \
        else                                                                                                \
        {                                                                                                   \
          if (rc)                                                                                           \
            *rc = tvInternal;                                                                               \
        }                                                                                                   \
      }                                                                                                     \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
      if (rc)                                                                                               \
        *rc = tvModelHasErrorDatabase;                                                                      \
    }                                                                                                       \
  }                                                                                                         \
  else                                                                                                      \
  {                                                                                                         \
    if (rc)                                                                                                 \
      *rc = tvNullObjectPtr;                                                                                \
  }                                                                                                         \
  return dbId;                                                                                              \
}                                                                                                           \

/** \details
Implements OdTvSerializableIObject abstract method
*/
#define ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(prefix)                                                        \
public:                                                                                                     \
prefix OdTvResult read(OdRxObject* pFiler);                                                                 \
prefix OdTvResult write(OdRxObject* pFiler);

/** \details
Implements OdTvSerializableIObject abstract method
*/
#define ODTV_DEFINE_SERIALIZABLE_OBJECT_DEF(IClassName)                                                     \
OdTvResult IClassName##Wrapper::read(OdRxObject* pFiler)                                                    \
{                                                                                                           \
ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER;                                                                        \
OdTvDbDwgFiler* pDwgFiler = dynamic_cast<OdTvDbDwgFiler*>(pFiler);                                              \
if (pDwgFiler)                                                                                              \
m_pObjectImpl->dwgInFields(pDwgFiler);                                                                      \
else                                                                                                        \
return tvMissingFiler;                                                                                      \
return tvOk;                                                                                                \
}                                                                                                           \
OdTvResult IClassName##Wrapper::write(OdRxObject* pFiler)                                                   \
{                                                                                                           \
  ODTV_DEFINE_WRAPPERS_CHEC_IN_MEMBER;                                                                      \
  OdTvDbDwgFiler* pDwgFiler = dynamic_cast<OdTvDbDwgFiler*>(pFiler);                                            \
  if (pDwgFiler)                                                                                            \
    m_pObjectImpl->dwgOutFields(pDwgFiler);                                                                 \
  return tvOk;                                                                                              \
}

#include "TD_PackPop.h"
#endif // _ODTV_INTERFACEWRAPPERS_H_INCLUDED_


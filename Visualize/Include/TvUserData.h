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

#ifndef _ODTVUSERDATA_H_INCLUDED_
#define _ODTVUSERDATA_H_INCLUDED_

#include "Tv.h"

/** \details
  The abstract interface class for custom user data manipulations in Visualize SDK.
  
  \remarks
  OdTvUserData is a data container that can be associated with any Visualize SDK object.
  The addRef() method  is called when the data is set to the object.
  The release() method is called when the data is unset from the object or when the Visualize SDK object is released.
  The numRefs() method returns the number of references.
  It is prohibited to call these methods from the user side; such a call leads to an application crash.
  If the addRef() and release() methods in an inherited class have empty implementations, you should delete the data yourself.
  \sa
  <link tv_working_with_features_xdata, Work with User Data>
*/
class ODTV_EXPORT OdTvUserData
{
public:

  /** \details
    Creates a new custom user data object with default parameters.
  */
  OdTvUserData() {}

  /** \details
    Destroys the custom user data object. 
  */
  virtual ~OdTvUserData() {}

  //DOM-IGNORE-BEGIN
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Increments the reference counter for objects derived from the custom user data class.
  */
  virtual void addRef() = 0;

  /** \details
    Decrements the reference counter for objects derived from the custom user data class.
  */
  virtual void release() = 0;
};


/** \details
  The base interface class that implements custom user data storage with support for reference counting and object deletion when the number of reference becomes equal to zero.

  \remarks
  The memory for this object should be allocated through internal ODA Software memory allocation, 
  therefore you should not overload new or delete operators for any classes inherited from this class.
  \sa
  <link tv_working_with_features_xdata, Work with User Data>
*/
class ODTV_EXPORT OdTvUserDataOwnedByObj : public OdTvUserData
{
public:

  /** \details
    Creates a new custom user data storage object.
  */
  OdTvUserDataOwnedByObj();

  /** \details
    Destroys the existing custom user data storage object.
  */
  virtual ~OdTvUserDataOwnedByObj() {}

  /** \details
    Increments the reference counter for objects derived from the custom user data class.
  */
  virtual void addRef();

  /** \details
    Decrements the reference counter for objects derived from the custom user data class.
  */
  virtual void release();

//DOM-IGNORE-BEGIN
protected:

  int m_nRef;
//DOM-IGNORE-END
};


/** \details
  The base interface class that implements custom binary data storage that can be associated with a Visualize object.

  \remarks
  If a Visualize SDK object becomes the owner of the custom binary data without copying, the memory for the data should be allocated through the 
  <exref target="https://docs.opendesign.com/tkernel/odrxAlloc@size_t.html">::odrxAlloc() function</exref>.
  \sa
  <link tv_working_with_features_xdata, Work with User Data>
*/
class ODTV_EXPORT OdTvByteUserData : public OdTvUserDataOwnedByObj
{
public:

  /** \details 
    Types of ownership.
  */
  enum Ownership
  {
    kDoNotOwn = 0, // The data is not owned.
    kOwn = 1,      // The data is owned without copying.
    kCopyOwn = 2   // The data is owned with copying.
  };

  /** \details
    Creates a new custom binary data object with default parameters.
  */
  OdTvByteUserData();

  /** \details
    Creates a new custom binary data object with specified parameters.
    
    \param pData [in] A pointer to the custom data.
    \param iSize [in] A size of the custom data in bytes.
    \param ownership [in] An ownership type.
    \param bSave [in] A save flag value. If the custom data is saved within the object, the flag value should be equal to true; otherwise it is equal to false (by default).
  */
  OdTvByteUserData(void* pData, OdUInt32 iSize, Ownership ownership = kDoNotOwn, bool bSave = false);

  /** \details
    Destroys the custom binary data object.
  */
  virtual ~OdTvByteUserData();

  /** \details
    Retrieves the current custom binary data.
    
    \returns Returns a raw pointer to the data.
  */
  const void*     getData() const;
  
  /** \details
    Retrieves the current custom binary data size.
    
    \returns Returns the data size in bytes.
  */
  OdUInt32        getSize() const;
  
  /** \details
    Retrieves the current save flag value.
    
    \returns Returns true if the custom binary data should be saved in the owner object; otherwise the method returns false.
  */
  bool            getNeedSave() const;

//DOM-IGNORE-BEGIN
protected:
  void*     m_pData;
  OdUInt32  m_iSize;
  Ownership m_ownership;
  bool      m_bSave;
//DOM-IGNORE-END
};


/** \details
  The base interface class that implements custom binary data storage that can be associated with a Visualize object by using a raw pointer.

  \remarks
  If a Visualize SDK object becomes the owner of the custom binary data without copying, the memory for the data should be allocated through the 
  <exref target="https://docs.opendesign.com/tkernel/odrxAlloc@size_t.html">::odrxAlloc() function</exref>.
  \sa
  <link tv_working_with_features_xdata, Work with User Data>
*/
class ODTV_EXPORT OdTvPointerUserData : public OdTvUserDataOwnedByObj
{
public:

  /** \details
    Creates a custom binary data object with default parameters.
  */
  OdTvPointerUserData();

  /** \details
    Creates a custom binary data object with a specified raw pointer.
    
    \param pData [in] A raw pointer to custom binary data.
  */
  OdTvPointerUserData(void* pData);

  /** \details
    Destroys the custom binary data object.
  */
  virtual ~OdTvPointerUserData();

  /** \details
    Sets new custom binary data.
    
    \param pData [in] A raw pointer to the custom binary data to be set.
  */
  void setData(void* pData);

  /** \details
    Retrieves the current custom binary data.
    
    \returns Returns a raw pointer to the current custom binary data.
  */
  void*     getData() const;

//DOM-IGNORE-BEGIN
protected:
  void*     m_pData;
//DOM-IGNORE-END
};


/** \details
  The interface class for a registered application object identifier that allows access to the information about the registered application.
  Additionally the interface class can get the name of the registered application.
  \sa
  <link tv_working_with_features_xdata, Work with User Data>
*/
class ODTV_EXPORT OdTvRegAppId : public OdTvId
{
public:

  /** \details
    Retrieves the current name of the registered application.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the name of the registered application.
    \remarks 
    If the rc parameter is not null and the application name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  OdString getName(OdTvResult* rc = NULL) const;
};

/** \details
  A data type that represents an array of <link OdTvRegAppId, OdTvRegAppId> objects.
*/
typedef OdVector<OdTvRegAppId, OdMemoryAllocator<OdTvRegAppId> >         OdTvRegAppIdArray;


#endif // _ODTVUSERDATA_H_INCLUDED_


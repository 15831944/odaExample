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



#ifndef _ODDBPAGECONTROLLER_INCLUDED_
#define _ODDBPAGECONTROLLER_INCLUDED_

#include "RxObject.h"
#include "DbExport.h"
#include "DbDatabase.h"

class OdTvDbDatabase;
class OdTvDbObjectId;
class OdStreamBuf;
typedef OdSmartPtr<OdStreamBuf> OdStreamBufPtr;

/** \details

    <group TD_Namespaces>
*/
namespace OdDb
{
  /** \details
      Flags that can be combined together (bit-wise) to describe a desired paging
      behavior.

      \sa
      * OdTvDbPageController
      * OdTvDbDatabase::enqueuePaging
      * OdTvDbDatabase::pageObjects
      * Paging Support
  */
  enum PagingType
  {
    /** \remarks
        Enables unloading of objects in a partially opened OdTvDbDatabase instance.  
        
        Closed objects will be unloaded from memory 
        during the next call to OdTvDbDatabase::pageObjects.  This behavior can be useful in environments
        with limited heap space (such as Windows CE).
    */
    kUnload  = 0x01,  
    /** \remarks
        Enables paging of objects in an OdTvDbDatabase instance.

        Closed Objects will be paged out during the next call to OdTvDbDatabase::pageObjects.  
        Paging will be implemented via a client-supplied OdTvDbPageController instance.
    */
    kPage    = 0x02,
    /** \remarks
        Disables automated object paging enqueuing in OdTvDbObject::release().

        Closed Objects will be paged out during the next call to OdTvDbDatabase::pageObjects.  
        Paging will be implemented via a client-supplied OdTvDbPageController instance.
    */
    kDoNotEnqueuePagingOnClose = 0x04   
  };
}

/** \details
    This class controls the paging support for an OdTvDbDatabase instance.

    \sa
    * Paging Support
    * OdTvDbDatabase::pageObjects

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbPageController : public OdRxObject
{
public:
  typedef OdInt64 Key;

  /** \details
    Returns the paging type for this PageController object.
      
    \remarks
    pagingType() returns a combination of zero or more of the following:
    
    <table>
    Name                              Value   Description
    OdDb::kUnload                     0x01    Enable unloading for objects in a partially opened OdTvDbDatabase instance.  
    OdDb::kPage                       0x02    Enable paging for objects in an OdTvDbDatabase instance.
    OdDb::kDoNotEnqueuePagingOnClose  0x04    Disable automated object paging enqueuing in OdTvDbObject::release.
    </table>

    \sa 
    Paging Support
  */
  virtual int pagingType() const = 0;

  /** \details
    Pages in the specified data.
    
    \remarks
    Returns a SmartPointer to an OdTvDbStreamBuf object containing the specified paged data from a client-supplied data source.
      
    \param key [in]  Paged data key, as returned by write().
  */
  virtual OdStreamBufPtr read(Key key) = 0;

  /** \details
    Pages out data as required to a client-supplied data source.

    \param key [out]  Paged data key, as used by read().
    \param pStreamBuf [in]  Pointer to the StreamBuf object from which the data are to be written.

    \returns
    Returns true if and only if the PageController implementation has successfully paged the data.

    \remarks
    Implementations of this function are expected to write the entire contents of pStreamBuf
    to an external data source, and to set assign a unique value to the key argument that 
    identifies this chunk of paged data.  This key value will be used in a subsequent calls
    to read() to retrieve this specific paged data.
  */
  virtual bool write(Key& key, OdStreamBuf* pStreamBuf) = 0;

  /** \details
    Sets the OdTvDbDatabase instance served by this controller.

    \param pDb [in]  Pointer to the database.
    \remarks
    The method is called by the Drawings during initialization of database paging.
  */
  virtual void setDatabase(OdTvDbDatabase* pDb) = 0;

  /** \details
      Returns the OdTvDbDatabase instance served by this controller.
  */
  virtual OdTvDbDatabase* database() = 0;

  /** \details
    The method is called during unloading/paging of an object,
    before anything else is done.

    \param objectId [in]  Object ID.
    \remarks
    subPage() returns one of the of the following:
    
    <table>
    Name              Description
    eOk               Continue paging.
    eSkipObjPaging    Skip paging of the specified object.
    eStopPaging       Stop paging.
    </table>
      
    \remarks
    The default implementation does nothing but return eOk. This function can be
    overridden in custom classes.
  */
  virtual OdResult subPage(const OdTvDbObjectId& objectId);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbPageController object pointers.
*/
typedef OdSmartPtr<OdTvDbPageController> OdTvDbPageControllerPtr;

/** \details
    Deprecated. Use OdTvDbDatabase::pageObjects instead.
    
    \remarks
    See Paging Support for details.
*/
inline void odDbPageObjects(OdTvDbDatabase* pDb) {
  pDb->pageObjects();
}

#endif // _ODDBPAGECONTROLLER_INCLUDED_




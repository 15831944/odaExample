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

#ifndef DbAssocNetworkLongTransactionReactor_INCLUDED_
#define DbAssocNetworkLongTransactionReactor_INCLUDED_ /*!DOM*/

#include "ApLongTransactions.h"
#include "DbObjectReactor.h"

#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
  This class implements the object modification reactor.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class OdTvDbAssocNetworkObjectModificationReactor : public OdTvDbObjectReactor
{
public:

  ODRX_DECLARE_MEMBERS(OdTvDbAssocNetworkObjectModificationReactor);

  /** \details
    Destructor destroys an instance of this class.
  */
  ~OdTvDbAssocNetworkObjectModificationReactor();

  /** \details
    Adds the reference to this reactor.
  */
  virtual void addRef() {};

  /** \details
    Releases this reactor.
  */
  virtual void release() {};

  /** \details
    Notifies the reactor when the object is erased.
  */
  void erased(const OdTvDbObject* pObject, bool erasing);

  /** \details
    Notifies the reactor when the object is modified.
  */
  void modified(const OdTvDbObject* pObject);

  /** \details
    Appends an object to the workset.
  */
  void appendToWorksetObject(OdTvDbObjectId objId);

  /** \details
    Gets the modified objects of the workset.
  */
  void getModifiedWorksetObjects(OdTvDbObjectIdArray & aResArray);

  /** \details
    Checks whether the workset is empty.
  */
  bool isEmpty();

private:
  /*!DOM*/
  OdTvDbObjectIdArray m_aWorksetObjReactorAttachedTo;
  /*!DOM*/
  OdTvDbObjectIdArray m_aModifiedWorksetObj;
};

/** \details
  The typified smart pointer. This template class is specialization of the OdSmartPtr class 
  for the OdTvDbAssocNetworkObjectModificationReactor class.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbAssocNetworkObjectModificationReactor> OdTvDbAssocNetworkObjectModificationReactorPtr;


/** \details
  This class implements the transaction reactor.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class OdTvDbAssocNetworkLongTransactionReactor: public OdTvApLongTransactionReactor
{
public:

  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbAssocNetworkLongTransactionReactor();

  /** \details
    Destructor destroys an instance of this class.
  */
  ~OdTvDbAssocNetworkLongTransactionReactor();

  /** \details
    Adds the reference to this reactor.
  */
  void addRefReactor();

  /** \details
    Releases this reactor.
  */
  void releaseReactor();

  // OdTvApLongTransactionReactor methods

  /** \details
    Begins the checking out.
  */
  void beginCheckOut(OdTvDbLongTransaction& iTransaction, OdTvDbObjectIdArray& iOriginList);

  /** \details
    Ends the checking out.
  */
  void endCheckOut(OdTvDbLongTransaction& iTransaction);

  /** \details
    Begins the checking in.
  */
  void beginCheckIn(OdTvDbLongTransaction& iTransaction);

  /** \details
    Ends the checking in.
  */
  void endCheckIn(OdTvDbLongTransaction& iTransaction);

  /** \details
    Aborts the transaction.
  */
  void abortLongTransaction(OdTvDbLongTransaction& iTransaction);

private:
  /*!DOM*/
  void showDimensions(OdTvDbObjectId blockId, bool show);

  /*!DOM*/
  OdTvDbAssocNetworkObjectModificationReactorPtr m_pModificationReactor;

  /*!DOM*/
  OdTvDbObjectIdArray m_aOriginEntities;

  /*!DOM*/
  OdTvDbObjectIdArray m_aModifiedWorksetEntities;

  /*!DOM*/
  std::map<OdTvDbObjectId, OdTvDbObjectId> m_WorksetObjectToOriginalMap;

  /*!DOM*/
  typedef std::map<OdTvDbObjectId, OdTvDbObjectIdArray> OdTvDbAssocOriginalObjectReactorsMap;
  OdTvDbAssocOriginalObjectReactorsMap m_OriginalObjectReactorsMap;

  /*!DOM*/
  int m_Counter;
};

#endif

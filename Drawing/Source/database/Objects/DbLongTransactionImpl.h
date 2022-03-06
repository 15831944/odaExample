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

#ifndef _ODDBLONGTRANSACTIONIMPL_INCLUDED_
#define _ODDBLONGTRANSACTIONIMPL_INCLUDED_


#include "DbObjectImpl.h"

typedef std::map<OdDbObjectId,OdUInt8> OdDbIdSet;

class OdDbLongTransactionImpl : public OdDbObjectImpl
{
  int m_type;
  OdDbObjectId m_originBlock;
  OdDbObjectId m_destinationBlock;
  OdDbObjectId m_blkRef;
  OdDbObjectId m_blkRefLayer;
  OdDbIdSet m_ids;
  OdDbIdMappingPtr m_pIdMap;
  OdDbObjectId m_clayer;
public:
  enum OdDbLongTransactionUndo
  {
    kPU_CheckinUndo = 0,
    kPU_CheckinRedo,
    kPU_CheckOutUndo,
    kPU_CheckOutRedo
  };

  enum
  {
    kPrimaryObject  = 0x01,
    kRemoved        = 0x02,
    kNotCloned      = 0x04,
    kAdded          = 0x08,
    kIsChecked      = 0x10,
    kWasInvisible   = 0x20,
    kNewObject      = 0x40
  };
  OdDbLongTransactionImpl() : m_type(0) {}
  static OdDbLongTransactionImpl* getImpl(const OdDbLongTransaction* obj)
  {
    return (OdDbLongTransactionImpl*)OdDbSystemInternals::getImpl(obj);
  }
  void purgeClonedObjects(bool bAborted);
  void hideBlockReference(OdDbObjectId);
  void restoreBlockReference();
  void updateCurrentLayer();
  OdDbObjectIdArray getSortedClones();
  void restoreClonedObjectsVisibility();
  void writeCheckInUndo(OdDbLongTransaction* lt);
  void writeCheckoutUndo(OdDbLongTransaction* lt);
  friend class OdDbLongTransaction;
  friend class OdApLongTransactionManagerImpl;
};

#endif // _ODDBLONGTRANSACTIONIMPL_INCLUDED_

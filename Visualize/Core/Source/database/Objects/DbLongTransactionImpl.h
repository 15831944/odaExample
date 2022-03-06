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

typedef std::map<OdTvDbObjectId,OdUInt8> OdTvDbIdSet;

class OdTvDbLongTransactionImpl : public OdTvDbObjectImpl
{
  int m_type;
  OdTvDbObjectId m_originBlock;
  OdTvDbObjectId m_destinationBlock;
  OdTvDbObjectId m_blkRef;
  OdTvDbObjectId m_blkRefLayer;
  OdTvDbIdSet m_ids;
  OdTvDbIdMappingPtr m_pIdMap;
  OdTvDbObjectId m_clayer;
public:
  enum OdTvDbLongTransactionUndo
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
  OdTvDbLongTransactionImpl() {}
  static OdTvDbLongTransactionImpl* getImpl(const OdTvDbLongTransaction* obj)
  {
    return (OdTvDbLongTransactionImpl*)OdTvDbSystemInternals::getImpl(obj);
  }
  void purgeClonedObjects(bool bAborted);
  void hideBlockReference(OdTvDbObjectId);
  void restoreBlockReference();
  void updateCurrentLayer();
  OdTvDbObjectIdArray getSortedClones();
  void restoreClonedObjectsVisibility();
  void writeCheckInUndo(OdTvDbLongTransaction* lt);
  void writeCheckoutUndo(OdTvDbLongTransaction* lt);
  friend class OdTvDbLongTransaction;
  friend class OdTvApLongTransactionManagerImpl;
};

#endif // _ODDBLONGTRANSACTIONIMPL_INCLUDED_

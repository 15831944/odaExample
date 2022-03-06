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

#ifndef _ODTV_ENTITYITERATORIMPL_H_INCLUDED_
#define _ODTV_ENTITYITERATORIMPL_H_INCLUDED_

#include "OdPlatform.h"
#include "DbObjectIterator.h"
#include "RxObjectImpl.h"
#include "OdLinkedArray.h"
#include "DbObjectId.h"

typedef OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> > OdTvEntityIdContainer;
typedef OdTvEntityIdContainer::iterator OdTvEntityIdContainerIterator;
typedef OdTvEntityIdContainer::const_iterator OdTvEntityIdContainerConstIterator;


class OdTvEntityIterator : public OdRxObjectImpl<OdTvDbObjectIterator>
{
protected:
  OdTvEntityIterator(const OdTvEntityIdContainer* pContainer);

  virtual ~OdTvEntityIterator();
public:
  ODRX_DECLARE_MEMBERS(OdTvEntityIterator);
  static OdRxObjectPtr createObject(const OdTvEntityIdContainer* pContainer);
 
  void start(bool bForward = true, bool bSkipDeleted = true);
  bool done() const;
  OdTvDbObjectId objectId() const;
  OdTvDbEntityPtr entity(OdDb::OpenMode openMode = OdDb::kForRead, bool openErased = false);
  bool seek(OdTvDbObjectId id);
  bool seek(const OdTvDbEntity* pEntity);
  void step(bool bForward = true, bool bSkipDeleted = true);

protected:
  virtual void skipDeleted(bool bForward);

  const OdTvEntityIdContainer* m_pContainer;
  OdTvEntityIdContainerConstIterator m_iter;
};

typedef OdSmartPtr<OdTvEntityIterator> OdTvEntityIteratorPtr;

#endif //_ODTV_ENTITYITERATORIMPL_H_INCLUDED_

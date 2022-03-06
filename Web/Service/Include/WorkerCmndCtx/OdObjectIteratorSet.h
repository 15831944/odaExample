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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "OdaCommon.h"
#include "DbPartialViewing.h"
#include "DbEntity.h"
#include "CloudLibTools.h"
#include <set>
#include <DbObjectIterator.h>

namespace OdWeb {
  typedef OdSmartPtr<OdTvDbObjectIterator> OdObjectIteratorSetPtr;

  class CLOUD_CMDCTX_EXPORT OdObjectIteratorSet : public OdTvDbObjectIterator
  {
  public:
    static OdObjectIteratorSetPtr createObject();

    void add(const OdTvDbObjectId& id);

    bool find(const OdTvDbObjectId& id);

    void erase(const OdTvDbObjectId& id);

    virtual void copyFrom(const OdRxObject* pSource);

    void init();

    virtual void start(bool atBeginning = true, bool skipErased = true);

    virtual bool done() const;

    virtual OdTvDbObjectId objectId() const;

    virtual OdTvDbEntityPtr entity(OdDb::OpenMode openMode = OdDb::kForRead, bool openErasedEntity = false);

    virtual void step(bool forward = true, bool skipErased = true);

    virtual bool seek(OdTvDbObjectId objectId);

    virtual bool seek(const OdTvDbEntity* pEntity);

    void subtract(OdTvDbObjectIteratorPtr& it);

    void add(OdTvDbObjectIteratorPtr& it);

  private:
    typedef std::set<OdTvDbObjectId> OdDbObjectIdSet;

    OdTvDbPartialViewingIndexPtr  m_index;
    OdTvDbPartialViewingFilterPtr m_filter;
    OdDbObjectIdSet             m_set;
    OdDbObjectIdSet::iterator   m_it;
  };
}
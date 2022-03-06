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

#ifndef PAGES_MAP_ENTRY_H__INCLUDED
#define PAGES_MAP_ENTRY_H__INCLUDED

#include "DwgFileController.h"

#define STL_USING_LIST
#include "OdaSTL.h"

#include "SharedPtr.h"

namespace TvIncSaveNamespace
{
  class PagesMapEntry
  {
  public:
    PagesMapEntry()
      : m_id(0)
      , m_size(0)
      , m_offset(0)
    {}

    PagesMapEntry(OdInt32 id, OdUInt32 size, OdUInt64 offset)
      : m_id(id)
      , m_size(size)
      , m_offset(offset)
    {}

    virtual ~PagesMapEntry() {}

    virtual void writeToStream(OdTvDwgFileController* fileController) const;

    OdInt32 getPageId() const;
    void setPageId(OdInt32 pageId);

    OdUInt32 getPageSize() const;
    void setPageSize(OdUInt32 pageSize);

    OdUInt64 getPageOffset() const;
    void setPageOffset(OdUInt64 pageOffset);

    OdInt32  m_id;
    OdUInt32 m_size;
    OdUInt64 m_offset;
  };
  
  class GapsTreeNode;

  class GapsMapEntry : public PagesMapEntry
  {
  public:
    GapsMapEntry()
      : m_pTreeNode(NULL)
    {}

    GapsMapEntry(OdInt32 id, OdUInt32 size, OdUInt64 offset, GapsTreeNode* pTreeNode = NULL)
      : PagesMapEntry(id, size, offset)
    {
      m_pTreeNode = pTreeNode;
    }

    virtual ~GapsMapEntry() {}

    virtual void writeToStream(OdTvDwgFileController* fileController) const;

    GapsTreeNode* m_pTreeNode;
  };

  typedef OdSharedPtr<PagesMapEntry> PagesMapEntryPtr;
  typedef std::list<PagesMapEntryPtr> PagesMapEntryPtrsList;
};

#endif

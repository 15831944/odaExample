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

#ifndef _ODDBCLONEUTILS_INCLUDED_
#define _ODDBCLONEUTILS_INCLUDED_

#include "DbStubExt.h"
#include "DbObjectImpl.h"
#define STL_USING_ALGORITHM
#include "OdaSTL.h"
#include "DbXlateFilerImpl.h"

namespace OdTvDbClone
{
  void wblockCloneTables(OdTvDbIdMapping& idMap);
  void wblockCloneDictionaryItems(OdTvDbIdMapping& idMap, OdTvDbObjectId (OdTvDbDatabase::*pGetNamedObject)(bool) const);
  void xlateOwners(OdTvDbIdMapping& idMap, OdArray<OdTvDbObjectPtr>* pRejectedObjects = 0);
  TOOLKIT_EXPORT void updateSortentsTable(OdTvDbIdMapping& idMap, const OdTvDbObjectId& srcBlockId, const OdTvDbObjectId& dstBlockId);

  template<class T>
  class Clone
  {
    OdTvDbObjectId m_owner;
    OdTvDbIdMapping& m_idMap;
  public:
    Clone(const OdTvDbObjectId& owner, OdTvDbIdMapping& idMap)
      : m_owner(owner)
      , m_idMap(idMap)
    {
    }
    void operator()(const OdTvDbObjectId& id)
    {
      OdTvDbObjectPtr pObj = id.openObject();
      if(pObj.get())
        T::clone(pObj, m_idMap, m_owner);
    }
  };

  inline void xlateObjects(OdTvDbIdMapping& idMap)
  {
    OdArray<OdTvDbObjectPtr> rejectedObjects;
    xlateOwners(idMap, &rejectedObjects);
    OdStaticRxObject<OdTvDbXlateFilerImpl> filer;
    filer.translateIds(idMap);
    OwnerIdUpdateFiler ownerIdFiler(idMap.destDb());
    while(rejectedObjects.size())
    {
      // #4570
      // References in ignored objects  are translated to avoid access of untranslated ids in ignored objects
      // #6675
      // AutoCAD's implementation of wblock/insert methods ignore possible errors in ignored objects
      // E.g. the file attached to the bug has invalid RegApp name and TD fails to insert it while AutoCAD insert it silently.
      try
      {
        filer.translateObjectIds(rejectedObjects.last());
        ownerIdFiler.updateSubObjectsIds(rejectedObjects.last(), OdTvDbObjectId::kNull);
      }
      catch (OdError&)
      {
        OdTvDbSystemInternals::getImpl(rejectedObjects.last())->m_Reactors.resize(0);
      }
      rejectedObjects.last()->objectId()->erasePermanently();
      rejectedObjects.removeLast();
    }
  }

  struct Deep
  {
    static OdTvDbObjectPtr clone(const OdTvDbObject* pObj, OdTvDbIdMapping& idMap, const OdTvDbObjectId& owner)
    {
      return pObj->deepClone(idMap, owner.openObject(), true);
    }
  };
  struct Wblock
  {
    static OdTvDbObjectPtr clone(const OdTvDbObject* pObj, OdTvDbIdMapping& idMap, const OdTvDbObjectId& owner)
    {
      return pObj->wblockClone(idMap, owner.openObject(), true);
    }
  };

  inline void deepCloneObjects(const OdTvDbObjectIdArray& objectIds, OdTvDbObjectId owner, OdTvDbIdMapping& idMap)
  {
    std::for_each(objectIds.begin(), objectIds.end(), Clone<Deep>(owner, idMap));
  }
  inline void wblockCloneObjects(const OdTvDbObjectIdArray& objectIds, OdTvDbObjectId owner, OdTvDbIdMapping& idMap)
  {
    std::for_each(objectIds.begin(), objectIds.end(), Clone<Wblock>(owner, idMap));
  }
}

//#define _TRACE_CLONE_
#ifdef _TRACE_CLONE_
  inline void _traceIdMapping(OdTvDbIdMapping& idMap, const OdString& title)
  {
    ODA_TRACE1("\n%ls", title.c_str());
    ODA_TRACE0("\nOriginal |    Clone | isXlated | isCloned | OwnerOrg | OwnerCln | Class");
    OdTvDbIdMappingIterPtr pIter = idMap.newIterator();
    OdTvDbIdPair obj2obj;
    while(!pIter->done())
    {
      pIter->getMap(obj2obj);
      ODA_TRACE1("\n% 8X | ", obj2obj.key().getNonForwardedHandle());
      ODA_TRACE1("% 8X | ", obj2obj.value().getHandle());
      ODA_TRACE1("%ls | ", obj2obj.isOwnerXlated() ? OD_T("true    ") : OD_T("false   "));
      ODA_TRACE1("%ls | ", obj2obj.isCloned() ? OD_T("true    ") : OD_T("false   "));

      OdTvDbObjectPtr pObj1 = obj2obj.key().openObject(OdDb::kForRead, true);
      OdTvDbObjectPtr pObj2 = obj2obj.value().openObject(OdDb::kForRead, true);

      ODA_TRACE1("% 8X | ", pObj1.isNull() ? OdDbHandle() : pObj1->ownerId().getHandle());
      ODA_TRACE1("% 8X | ", pObj2.isNull() ? OdDbHandle() : pObj2->ownerId().getHandle());

      if (!pObj1.isNull()) { ODA_TRACE1("%ls", pObj1->isA()->name().c_str()); }

      pIter->next();
    }
  }
#else

#define _traceIdMapping(IdMapping, title)

#endif

#define ODA_TRACE_IDMAPPING(IdMapping, title) _traceIdMapping(IdMapping, title)

#endif //_ODDBCLONEUTILS_INCLUDED_




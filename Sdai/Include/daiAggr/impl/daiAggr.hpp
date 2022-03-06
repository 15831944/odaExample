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

#ifndef _DAI_AGGR_BASE_IMPL_H
#define _DAI_AGGR_BASE_IMPL_H

#include <daiUtils/daiUnset.h>

namespace OdDAI
{
  template<typename TInstance>
  TInstance Aggr::instance() const
  {
    TInstance returnValue = dynamic_cast<TInstance>(m_pInstance);
    ODA_ASSERT_ONCE(returnValue != NULL);

    if (returnValue == NULL)
    {
      throw DaiException(sdaiAI_NEXS, "Aggregate instance does not exist.", TD_FUNC);
    }

    return returnValue;
  }

  template<typename TItem>
  inline bool Aggr::isMember(const TItem& itemToCheck) const
  {
    return instance<AggrInstanceCommon<TItem>*>()->isMember(itemToCheck);
  }

  template<class TItem>
  Aggr::operator const OdArray<TItem>* () const
  {
    const OdArray<TItem>* arrayToReturn = NULL;
    getArray<TItem>(arrayToReturn);
    return arrayToReturn;
  }

  template<typename TItem>
  inline bool Aggr::getArray(const OdArray<TItem>*& to) const
  {
    if (isNil())
    {
      return false;
    }

    to  = &instance<const AggrInstanceCommon<TItem>*>()->getArray();
    return true;
  }

  template<typename TItem, class TOtherItem>
  inline bool Aggr::getArrayValues(OdArray<TOtherItem>& to) const
  {
    if (isNil())
    {
      return false;
    }

    return instance<const AggrInstanceCommon<TItem>*>()->template copyToArray<TOtherItem>(to);
  }


  template<typename TItem>
  inline void Aggr::setArray(const OdArray<TItem>& from)
  {
    if (isNil())
    {
      createEmpty();
    }
    return instance<AggrInstanceCommon<TItem>*>()->setArray(from);
  }


  template<typename TItem, class TOtherItem>
  inline void Aggr::setArrayValues(OdArray<TOtherItem>& from)
  {
    if (isNil())
    {
      createEmpty();
    }

    instance<AggrInstanceCommon<TItem>*>()->template copyFromArray<TOtherItem>(from);
  }


  template<typename TItem>
  inline TItem Aggr::generateAggrItem() const
  {
    if (isNil())
    {
      return Utils::getUnset<TItem>();
    }

    return instance<const AggrInstanceCommon<TItem>*>()->generateAggrItem();
  }
}

namespace OdDAI
{
  namespace Utils
  {
    template<class TItem, class TCopyTo>
    inline bool copyTo(const OdDAI::Aggr& from, TCopyTo& to)
    {
        const OdArray<TItem> *aggrArray;
        if (!from.getArray(aggrArray) || aggrArray == NULL)
        {
            return false;
        }

        to = *aggrArray;
        return true;
    }


  }
}

#endif // _DAI_AGGR_BASE_H

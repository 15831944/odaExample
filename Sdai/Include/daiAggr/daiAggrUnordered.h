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

#ifndef _DAI_AGGR_UNORDERED_H
#define _DAI_AGGR_UNORDERED_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiAggr.h"
#include "impl/daiAggrCommonInstance.h"

#include "daiUtils/daiUnset.h"
#include "daiError/daiException.h"

#define STL_USING_ALGORITHM
#include "OdaSTL.h"

namespace OdDAI
{
  /** \details
  Template class for containers defined within a schema.
  */
  class DAI_EXPORT AggrUnordered
    : public Aggr
  {
  public:
    /** \details
    Adds aggregate item.
    \param anItem [in] a OdRxValue to add to unordered aggregate.
    */
    bool Add(const OdRxValue& anItem); 

    /** \details
    Removes aggregate item.
    \param anItem [in] a OdRxValue to remove from unordered aggregate.
    */
    bool Remove(const OdRxValue& anItem);

    /** \details
    Template function adds typed item to unordered aggregate.
    \param anItem [in] a typed value to add to unordered aggregate.
    */
    template<typename TItem>
    bool Add(const TItem& anItem); //

    /** \details
    Template function removes typed item from unordered aggregate.
    \param anItem [in] a typed value to remove from unordered aggregate.
    */
    template<typename TItem>
    bool Remove(const TItem& anItem);

    ////DOM-IGNORE-BEGIN

  protected:
    AggrUnordered(AggrInstance* defaultInstance);

  };
}


namespace OdDAI
{
  template<typename TItem>
  class AggrUnorderedInstance
    : public AggrInstanceCommon<TItem>
    , public UnorderedLogic
  {
  public:
    virtual bool AddOdRxValue(const OdRxValue& value) ODRX_OVERRIDE
    {
      TItem transitValue = this->generateAggrItem();
      return value >> transitValue && Add(transitValue);
    }

    virtual bool RemoveOdRxValue(const OdRxValue& value) ODRX_OVERRIDE
    {
      TItem transitValue = this->generateAggrItem();
      return value >> transitValue && Remove(transitValue);
    }

  public:
    int getLowerBound() const ODRX_OVERRIDE { return 0; }
    int getUpperBound() const ODRX_OVERRIDE { return this->m_itemCollection.size() > 0 ? this->m_itemCollection.size() : -1; }

    virtual UnorderedLogic* unorderedLogic() ODRX_OVERRIDE { return this; }
    virtual OrderedLogic* orderedLogic() ODRX_OVERRIDE { return 0; }

  public:
    virtual bool Add(const TItem& element) = 0;
    virtual bool Remove(const TItem& anItem) = 0;

  protected:
    AggrUnorderedInstance()
      : AggrInstanceCommon<TItem>()
    {
    }

  };
}

namespace OdDAI
{
  inline AggrUnordered::AggrUnordered(AggrInstance* defaultInstance)
    : Aggr(defaultInstance)
  {
  }

  inline bool AggrUnordered::Add(const OdRxValue& anItem)
  {
    return Aggr::instance<AggrInstance*>()->unorderedLogic()->AddOdRxValue(anItem);
  }

  inline bool AggrUnordered::Remove(const OdRxValue& anItem)
  {
    return Aggr::instance<AggrInstance*>()->unorderedLogic()->RemoveOdRxValue(anItem);
  }

  template<typename TItem>
  inline bool AggrUnordered::Add(const TItem& anItem)
  {
    return Aggr::instance<AggrUnorderedInstance<TItem>*>()->Add(anItem);
  }

  template<typename TItem>
  inline bool AggrUnordered::Remove(const TItem& anItem)
  {
    return Aggr::instance<AggrUnorderedInstance<TItem>*>()->Remove(anItem);
  }
}
//DOM-IGNORE-END

#endif // _DAI_AGGR_H

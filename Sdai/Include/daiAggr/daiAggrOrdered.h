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

#ifndef _DAI_AGGR_ORDERED_H
#define _DAI_AGGR_ORDERED_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiAggr.h"
#include "impl/daiAggrCommonInstance.h"
#include "daiAggrMemberAccess.h"

#include "daiUtils/daiUnset.h"
#include "daiError/daiException.h"

#define STL_USING_ALGORITHM
#include "OdaSTL.h"

namespace OdDAI 
{
 
  /** \details
  Class for containers defined within a schema.
  */
  class DAI_EXPORT AggrOrdered 
    : public Aggr
  {
  public:

    /** \details
    Provides aggregate item by index.
    \param index [in] an index item.
    \returns Returns an OdRxValue of aggregate element.
    */
    OdRxValue getByIndex(int  index) const; //

    /** \details
    Puts aggregate item by index.
    \param index [in] an index item to put.
    \param element [in] a value for item set.
    */
    void putByIndex(int  index, const OdRxValue& element); //


    /** \details
    Insert aggregate item to specified position.
    \param index [in] an index item to insert.
    \param element [in] a value for item set.
    */
    void insertByIndex(int  index, const OdRxValue& element); //


    /** \details
    Creates a child aggregate by index.
    \param index [in] an index where aggregate create to.
    \param newAggr [in/out] output parameter. If succeeded it should filled by a pointer of new child agggregate.
    */
    void createAggrInstanceByIndex(int index, Aggr*& newAggr);

    /** \details
    Get value bound.
    \param index [in] an index of value.
    */
    int getValueBoundByIndex(int index); //

    /** \details
    Templated method provides aggregate item by index.
    \param index [in] an index item.
    \returns Returns a typed reference of aggregate element.
    */
    template<class TItem>
    const TItem& getByIndex(int  index) const; //

    /** \details
    Templated method puts aggregate item by index.
    \param index [in] an index item to put.
    \param element [in] a templated value for item set.
    */
    template<class TItem>
    void putByIndex(int  index, const TItem& element); //

    ////DOM-IGNORE-BEGIN

    static bool unsetByIndex(AggrOrdered& aggrToUnset, int  indexToRemove);

  protected:
    AggrOrdered(AggrInstance* defaultInstance);

  };



  template<typename TItem>
  class AggrOrderedInstance
    : public AggrInstanceCommon<TItem>
    , public OrderedLogic
  {
  public:
    virtual OdRxValue getOdRxValueByIndex(int index) const ODRX_OVERRIDE
    {
#ifdef _AGGR_RETURN_PTR
      indexCheck(index);
      unsigned int internalIndex = toInternalIndex(index);
      const OdArray<TItem>& arr = this->m_itemCollection.getCollection();
      return _getCurrentMemberTyped((OdArray<TItem>*)&arr, internalIndex);
#else
      // Temporary OdRxValue contradicts extraction of values by pointer
      // from NonBlittable types as constructor/destructor used inside
      // OdRxValue when out of scope.
      const TItem& transitValue = getByIndex(index);
      if (transitValue == Utils::getUnset<TItem>())
      {
        return OdRxValue();
      }
      return transitValue;
#endif
    }

    virtual void putOdRxValueByIndex(int index, const OdRxValue& value) ODRX_OVERRIDE
    {
      TItem transitValue = this->generateAggrItem();
      if ((value >> transitValue) == true)
      {
        putByIndex(index, transitValue);
      }
    }

    virtual void insertOdRxValueByIndex(int  index,  const OdRxValue& element) override
    {
      throw OdDAI::DaiException(sdaiEX_NSUP, "Expression evaluation not supported ", TD_FUNC);
    }


    virtual int getValueBoundByIndex(int index)  ODRX_OVERRIDE
    {
      return index;
    }

    virtual void createAggrInstanceByIndex(int index, Aggr*& newAggr) ODRX_OVERRIDE
    {
      throw OdDAI::DaiException(sdaiEX_NSUP, "Expression evaluation not supported ", TD_FUNC);
    }

  public:
    virtual OrderedLogic* orderedLogic() ODRX_OVERRIDE { return this; }
    virtual UnorderedLogic* unorderedLogic() ODRX_OVERRIDE { ODA_ASSERT (0 && "cant be here"); return 0; }

  public:
    const TItem& getByIndex(int index) const
    {
      indexCheck(index);
      unsigned int internalIndex = toInternalIndex(index);
      return this->m_itemCollection.size() > internalIndex ? this->m_itemCollection[internalIndex] : OdDAI::Utils::getUnset<TItem>();
    }

    virtual void putByIndex(int index, const TItem& element)
    {
      indexCheck(index);
      unsigned int internalIndex = toInternalIndex(index);

      if (this->m_itemCollection.size() <= internalIndex)
      {
        this->m_itemCollection.resize(internalIndex + 1, OdDAI::Utils::getUnset<TItem>());
      }

      this->m_itemCollection.setValue(internalIndex, element);
    }

  protected:
    
    AggrOrderedInstance()
      : AggrInstanceCommon<TItem>()
    {
    }


    virtual unsigned int toInternalIndex(int outerIndex) const { return static_cast<unsigned int>(outerIndex); }
    virtual int toOuterIndex(unsigned int internalIndex) const { return static_cast<int>(internalIndex); }

    inline void indexCheck(int indexToCheck) const
    {
      if ((this->getLowerBound() > indexToCheck) ||
          (indexToCheck > this->getUpperBound()))
      {
        throw OdDAI::DaiException(sdaiIX_NVLD, "Index invalid ", TD_FUNC);
      }
    }

  };
}

namespace OdDAI
{
  inline AggrOrdered::AggrOrdered(AggrInstance* defaultInstance)
    : Aggr(defaultInstance)
  {
  }

  inline OdRxValue AggrOrdered::getByIndex(int index) const
  {
    return Aggr::instance<AggrInstance*>()->orderedLogic()->getOdRxValueByIndex(index);
  }

  inline void AggrOrdered::putByIndex(int index, const OdRxValue& element)
  {
    Aggr::instance<AggrInstance*>()->orderedLogic()->putOdRxValueByIndex(index, element);
  }

  inline void AggrOrdered::insertByIndex(int index, const OdRxValue& element)
  {
    Aggr::instance<AggrInstance*>()->orderedLogic()->insertOdRxValueByIndex(index, element);
  }

  inline void AggrOrdered::createAggrInstanceByIndex(int index, Aggr *& newAggr)
  {
    Aggr::instance<AggrInstance*>()->orderedLogic()->createAggrInstanceByIndex(index, newAggr);
  }

  inline int AggrOrdered::getValueBoundByIndex(int index)
  {
    return Aggr::instance<AggrInstance*>()->orderedLogic()->getValueBoundByIndex(index);
  }

  template<typename TItem>
  inline const TItem& AggrOrdered::getByIndex(int index) const
  {
    return Aggr::instance<AggrOrderedInstance<TItem>*>()->getByIndex(index);
  }

  template<typename TItem>
  inline void AggrOrdered::putByIndex(int index, const TItem& element)
  {
    Aggr::instance<AggrOrderedInstance<TItem>*>()->putByIndex(index, element);
  }

  inline bool AggrOrdered::unsetByIndex(AggrOrdered& aggrToUnset, int  indexToRemove)
  {
    return  aggrToUnset.instance<AggrInstance*>()->orderedLogic() != NULL &&
            aggrToUnset.instance<AggrInstance*>()->orderedLogic()->removeOdRxValueByIndex(indexToRemove);
  }

}
//DOM-IGNORE-END

#endif // _DAI_AGGR_H

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

#ifndef _DAI_AGGR_BASE_H
#define _DAI_AGGR_BASE_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"
#include "SharedPtr.h"
#include "RxValue.h"

#include "daiBuildOptions.h"
#include "daiObjectId.h"
#include "daiAggrBaseValueType.h"

#include "daiError/daiException.h"

namespace OdDAI
{
  static const unsigned int unorderedDefaultLowerBound = 0;
  static const unsigned int unorderedDefaultUpperBound = static_cast<unsigned int>(-1);

  static const int orderedDefaultLowerBound = 0;
  static const int orderedDefaultUpperBound = unorderedDefaultUpperBound >> 1;

  class OdSpfFilerBase;

  class AggregationType;

  class AggrInstance;
  typedef OdSharedPtr<AggrInstance> AggrInstancePtr;

  class Iterator;
  typedef OdSharedPtr<Iterator> IteratorPtr;

  class ConstIterator;
  typedef OdSharedPtr<ConstIterator> ConstIteratorPtr;

  /** \details
  Defines aggregation types.
  */
  enum AggrType
  {
    /** Array type */
    aggrTypeArray,

    /** Bag type */
    aggrTypeBag,

    /** List type */
    aggrTypeList,

    /** Set type */
    aggrTypeSet,
  };

  class DAI_EXPORT AggrInstance;
  class DAI_EXPORT OrderedLogic;
  class DAI_EXPORT UnorderedLogic;

  template<class TWorkInstance>
  class DAI_EXPORT AggrInstanceDefaultBase;

  template<class TWorkInstance>
  class DAI_EXPORT AggrInstanceDefault;

  template<class TWorkInstance>
  class DAI_EXPORT TypedAggrInstanceDefault;

  template<typename TItem>
  class AggrInstanceCommon;

  template<class TItem>
  class IAggrReader
  {
  public:
    virtual bool skipUntil(const char symbol) = 0;
    virtual bool skipUntilRet(const char symbol) = 0;
    virtual bool rdPrimitive(TItem& readTo, bool commaNeed) = 0;
  };

  template<class TItem>
  class IAggrWriter
  {
  public:
    virtual bool wrChar(const char symbol) = 0;
    virtual bool wrPrimitive(TItem& readTo) = 0;
  };

  /** \details
  A base class for containers defined within a schema.
  */
  class DAI_EXPORT Aggr
  {
  public:

    /** \details
    Non-virtual destructor!
    */
    ~Aggr();

    /** \details
    Creates a new iterator along elements of aggregate.
    \return Returns a shared pointer to the newly created iterator.
    */
    IteratorPtr createIterator();

    /** \details
    Creates a new const iterator along elements of aggregate.
    \return Returns a shared pointer to the newly created const iterator.
    */
    ConstIteratorPtr createConstIterator() const;

    /** \details
    Checks if aggregate is unset.
    \return Returns true if aggregate is unset.
    */
    bool isNil() const;

    /** \details
    Clean the aggregate with deletion of all its content.
    */
    void nullify();

    /** \details
    Returns a value type of aggregate instance elements.
    \returns Returns a value type of aggregate instance elements.
    */
    const OdRxValueType&  type() const;

    /** \details
    Returns a type of aggregate.
    \returns Returns a type of aggregate.
    */
    AggrType aggrType() const;

    /** \details
    Check if aggregate is ordered.
    \returns Returns true if oredered, otherwise returns false.
    */
    bool isOrdered() const;

    /** \details
    Init aggregate. Creates an empty instance inside aggregate.
    \returns Returns true if operation succeeded, in other case function  returns false
    */
    bool createEmpty();


    /** \details
    Provides aggregates lower bound.
    \returns Returns an aggregate lower bound.
    */
    int getLowerBound() const;

    /** \details
    Provides aggregates upper bound.
    \returns Returns an aggregate upper bound.
    */
    int getUpperBound() const;


    /** \details
    Clear the aggregate with deletion of all its content.
    */
    void clear();

    /** \details
    Returns amoung of aggregate elements.
    \returns Returns an amoung of aggregate elements.
    */
    int getMemberCount() const;

    /** \details
    Check if aggreagate contains a member.
    \param itemToCheck [in] an item to check.
    \returns Returns true if aggregate contains a member and false in otherwise.
    */
    bool isMember(const OdRxValue& itemToCheck) const;


    /** \details
    Operator of equal.
    \param right [in] aggregate from right of expression to compare.
    \returns Returns true if aggregates are equal and false in otherwise.
    */
    bool operator == (const Aggr& aggr) const;

    /** \details
    Check aggregate for any elements. 
    \returns Returns true if aggregate is wempty and false in otherwise.
    */
    bool empty() const;

    /** \details
    Make aggregates clone.
    \returns Returns valid pointer to copy of aggregate if success, otherwise return NULL.
    \remarks 
    Use delete to clean returned pointer.
    */
    Aggr* clone(bool withItems = true) const;

    /** \details
    Copy from aggregate.
    \param otherAggr [in] aggregate to copy from.
    \returns Returns true if copy was succeeded, otherwise false
    \remarks
    The copy should work between the same type aggregates. 
    In case with different aggregates types the function should be failed.
    */
    bool copyFromAggr(const Aggr& otherAggr);


    /** \details
    Template check if aggreagate contains a member.
    \param itemToCheck [in] item to check.
    \returns Returns an amoung of aggregate elements.
    */
    template<class TItem>
    bool isMember(const TItem& itemToCheck) const;

    /** \details
    Providing internal OdArray to the outside.
    \returns Returns constant pointer to internal array. If aggregate is empty it can return null.
    */
    template<class TItem>
    operator const OdArray<TItem>* () const;

    /** \details
    Providing internal OdArray to the outside.
    \param to [in/out] should be filled by the constant valid pointer to internal 
    array if aggregate is not empty.
    \returns Returns true if aggregate is not empty and false in other case.
    */
    template<typename TItem>
    bool getArray(const OdArray<TItem>*& to) const;

    template<typename TItem, class TOtherItem>
    bool getArrayValues(OdArray<TOtherItem>& to) const;

    /** \details
    Set OdArray items to aggregate.
    \param from [in] copy items from param to aggregate.
    */
    template<typename TItem>
    void setArray(const OdArray<TItem>& from);

    template<typename TItem, class TOtherItem>
    void setArrayValues(OdArray<TOtherItem>& from);

    bool read(OdSpfFilerBase* readFiler);

    bool write(OdSpfFilerBase* writeFiler);

    static Aggr* CreateAggrByType(const AggregationType* createFrom);
    
    template<typename TItem>
    TItem generateAggrItem() const;

    //DOM-IGNORE-BEGIN

    /** \details
    Temporary method for OdArray compatibility.
    */

    Aggr& operator = (const Aggr& aggr) = delete;
    Aggr(const Aggr& aggr) = delete;

    static void rxUninit();

  protected:
    Aggr(AggrInstance* defaultInstance);

    template<class TInstance>
    TInstance instance() const;

  private:
    AggrInstance*   m_pInstance;

  };
}

#include "impl/daiAggr.hpp"

//DOM-IGNORE-END

#endif // _DAI_AGGR_BASE_H

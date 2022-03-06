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

#ifndef _DAI_LIST_H
#define _DAI_LIST_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"
#include "daiAggrOrdered.h"
#include "daiIteratorCollection.h"
#include "daiConstIteratorCollection.h"

#include "daiUtils/daiCustomCompare.h"
#include <type_traits>

namespace OdDAI
{
  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem>
  class DAI_EXPORT List
    : public AggrOrdered
  {
  public:
    typedef TItem template_type;
    typedef TItem value_type;
    typedef List<TItem> base_type;

  public:
    /**\details
    Creates a new List aggregate.
    */
    List();

    List(const AggregationType* aggregationType);

    /**\details
    Add new item to ordered aggregate by index.
    \param indexAddAfter [in] item index to set after
    \param elementToAdd [in] the new item value 
    */
    void addByIndex(int indexAddAfter, const TItem& elementToAdd);

    /**\details
    Creates a child aggregate, puts it to internal collection and provide it to outside.
    \param indexAddAfter [in] item index to set after
    \param aggrToAdd [in/out] a pointer reference to provide a created aggregate. It may be null if error occured during additiion.
    */
    void addAggregateInstanceByIndex(int indexAddAfter, Aggr*& aggrToAdd);

    /**\details
    Remove existing item from ordered aggregate by index.
    \param indexAddAfter [in] item index to remove
    */
    void removeByIndex(int  ind);

    /**\details
    Gets value bound of value at ordered aggregate by index.
    \param index [in] item index
    */
    int  getValueBoundByIndex(int index);

    
    /** \details
    Equal to operator
    \param right [in] aggregate to compare.
    \returns Returns true if equal, otherwise false.
    */
    bool operator== (const List& right) const;

    /** \details
    Copy assignment operator
    \param right [in] aggregate to copy from.
    \returns Returns the reference to itself.
    */
    List& operator= (const List& right);


    const OdArray<TItem>& getArray() const
    {
      return Aggr::instance<AggrInstanceCommon<TItem>*>()->getArray();
    }


  protected:
    List(AggrInstance* defaultInstance);

    template<typename TItemInst>
    friend class ListInstance;

  };


  typedef List< bool > BoolList;
  typedef OdSharedPtr< BoolList > BoolListPtr;

  typedef List< double > DoubleList;
  typedef OdSharedPtr< DoubleList > DoubleListPtr;

  typedef List< int > IntList;
  typedef OdSharedPtr< IntList > IntListPtr;

  typedef List< OdDAIObjectId > OdDAIObjectIdList;
  typedef OdSharedPtr< OdDAIObjectIdList > OdDAIObjectIdListPtr;

  class OdDAIObjectSDAI;
  typedef List<OdDAIObjectSDAI*> NonPersistentList;
  typedef OdSharedPtr<NonPersistentList> NonPersistentListPtr;

  typedef List< OdAnsiString> OdAnsiStringList;
  typedef OdSharedPtr< OdAnsiStringList > OdAnsiStringListPtr;

  typedef List< WhereRulePtr > WhereRuleList;

}

#include "impl/daiListInstance.hpp"

#endif // _DAI_AGGR_H

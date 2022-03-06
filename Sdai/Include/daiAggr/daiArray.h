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

#ifndef _DAI_ARRAY_H
#define _DAI_ARRAY_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiAggrOrdered.h"
#include "daiIteratorCollection.h"
#include "daiConstIteratorCollection.h"

namespace OdDAI 
{
  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem>
  class DAI_EXPORT Array
    : public AggrOrdered
  {
  public:
    typedef TItem         template_type;
    typedef TItem         value_type;
    typedef Array<TItem>  base_type;

  public:
    /**\details
    Creates a new array aggregate.
    */
    Array();

    Array(const AggregationType* aggregationType);

    /**\details
    Resize the specified array instance.
    */
    void reindex();

    /**\details
    Resize the specified array instance index boundes.
    \param lower [in] new lower index value
    \param upper [in] new upper index value
    */
    void resetIndex(int  lower, int  upper);

    /**\details
    Check item by index for unset value.
    \param indexToTest [in] item index
    \returns Returns true if settled value is not equal unset and false otherwise.
    */
    bool testByIndex(int  indexToTest) const;

    /**\details
    Reset item by index to unset value.
    \param indexToUnset [in] item index
    */
    void unsetValueByIndex(int  indexToUnset);

    /**\details
    Returns upper index, last settled item.
    \param indexToUnset [in] item index
    \returns Returns the last settled item index. If all items are unset, returns lower bound.
    */
    int  getUpperIndex() const;

    /**\details
    Returns lower index, first settled item.
    \param indexToUnset [in] item index
    \returns Returns the first settled item index. If all items are unset, returns lower bound.
    */
    int  getLowerIndex() const;

    /** \details
    Equal to operator
    \param right [in] aggregate to compare.
    \returns Returns true if equal, otherwise false.
    */
    bool operator == (const Array& aggr) const;

    /** \details
    Copy assignment operator
    \param right [in] aggregate to copy from.
    \returns Returns the reference to itself.
    */
    Array& operator= (const Array& right);


    const OdArray<TItem>& getArray() const
    {
      return Aggr::instance<AggrInstanceCommon<TItem>*>()->getArray();
    }
    
    //DOM-IGNORE-BEGIN

  protected:
    Array(AggrInstance* defaultInstance);

    template<typename TItemInst>
    friend class ArrayInstance;

  };

  typedef Array< bool > BoolArray;
  typedef OdSharedPtr< BoolArray > BoolArrayPtr;

  typedef Array< double > DoubleArray;
  typedef OdSharedPtr< DoubleArray > DoubleArrayPtr;

  typedef Array< int > IntArray;
  typedef OdSharedPtr< IntArray > IntArrayPtr;

  typedef Array< OdDAIObjectId > OdDAIObjectIdArray;
  typedef OdSharedPtr< OdDAIObjectIdArray > OdDAIObjectIdArrayPtr;

  typedef Array<OdAnsiString> AnsiStringArray;
  typedef OdSharedPtr<OdAnsiStringArray> AnsiStringArrayPtr;

  typedef Array<Select> SelectArray;
  typedef OdSharedPtr<SelectArray> SelectArrayPtr;

  typedef Array<Enum> EnumArray;
  typedef OdSharedPtr<EnumArray> EnumArrayPtr;
}


#include "impl/daiArrayInstance.hpp"

#endif // _DAI_AGGR_H

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

#ifndef _DAI_SET_H
#define _DAI_SET_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiAggrUnordered.h"
#include "daiIteratorCollection.h"
#include "daiConstIteratorCollection.h"

#define STL_USING_MAP
#include "OdaSTL.h"

namespace OdDAI 
{

  namespace
  {
    template<class TVAlueFind>
    bool customCompare(const TVAlueFind& left, const TVAlueFind& right)
    {
      return left < right;
    }
  }

  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem>
  class DAI_EXPORT Set
    : public AggrUnordered
  {
    friend class Duplicator;
  public:
    typedef TItem template_type;
    typedef TItem value_type;
    typedef Set<TItem> base_type;

  public:
    /**\details
    Creates a new Set aggregate.
    */
    Set();

    Set(const AggregationType* aggregationType);

    /** \details
    Equal to operator
    \param right [in] aggregate to compare.
    \returns Returns true if equal, otherwise false.
    */
    bool operator == (const Set& aggr) const;

    /** \details
    Copy assignment operator
    \param right [in] aggregate to copy from.
    \returns Returns the reference to itself.
    */
    Set& operator= (const Set& right);

    const OdArray<TItem>& getArray() const
    {
      return Aggr::instance<AggrInstanceCommon<TItem>*>()->getArray();
    }
    
    //DOM-IGNORE-BEGIN
  protected:
    Set(AggrInstance* defaultInstance);

    template<typename TItemInst>
    friend class SetInstance;
  };

  typedef Set< bool > BoolSet;
  typedef OdSharedPtr< BoolSet > BoolSetPtr;

  typedef Set< double > DoubleSet;
  typedef OdSharedPtr< DoubleSet > DoubleSetPtr;

  typedef Set< int > IntSet;
  typedef OdSharedPtr< IntSet > IntSetPtr;

  typedef Set< OdDAIObjectId > OdDAIObjectIdSet;
  typedef OdSharedPtr< OdDAIObjectIdSet > OdDAIObjectIdSetPtr;

  typedef Set< OdAnsiString> OdAnsiStringSet;
  typedef OdSharedPtr< OdAnsiStringSet > OdAnsiStringSetPtr;

  typedef Set<OdDAI::Select> SelectSet;
  typedef OdSharedPtr<OdDAI::Select> SelectSetPtr;

}

#include "impl/daiSetInstance.hpp"

#endif // _DAI_AGGR_H

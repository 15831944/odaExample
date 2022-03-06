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

#ifndef _DAI_BAG_H
#define _DAI_BAG_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiAggrUnordered.h"
#include "daiIteratorCollection.h"
#include "daiConstIteratorCollection.h"

namespace OdDAI 
{

  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem>
  class DAI_EXPORT Bag
    : public AggrUnordered
  {
  public:
    typedef TItem template_type;
    typedef TItem value_type;
    typedef Bag<TItem> base_type;

  public:
    Bag();

    Bag(const AggregationType* aggregationType);

    /** \details
    Equal to operator
    \param right [in] aggregate to compare.
    \returns Returns true if equal, otherwise false.
    */
    bool operator == (const Bag& aggr) const;

    /** \details
    Copy assignment operator
    \param right [in] aggregate to copy from.
    \returns Returns the reference to itself.
    */
    Bag& operator= (const Bag& right);


    const OdArray<TItem>& getArray() const
    {
        return Aggr::instance<AggrInstanceCommon<TItem>*>()->getArray();
    }

    //DOM-IGNORE-BEGIN
    
  protected:
    Bag(AggrInstance* defaultInstance);

    template<typename TItemInst>
    friend class BagInstance;

  };


  typedef Bag< bool > BoolBag;
  typedef OdSharedPtr< BoolBag > BoolBagPtr;

  typedef Bag< double > DoubleBag;
  typedef OdSharedPtr< DoubleBag > DoubleBagPtr;

  typedef Bag< int > IntBag;
  typedef OdSharedPtr< IntBag > IntBagPtr;

  typedef Bag< OdDAIObjectId > OdDAIObjectIdBag;
  typedef OdSharedPtr< OdDAIObjectIdBag > OdDAIObjectIdBagPtr;

  typedef Bag< OdAnsiString> OdAnsiStringBag;
  typedef OdSharedPtr< OdAnsiStringBag > OdAnsiStringBagPtr;

}


#include "impl/daiBagInstance.hpp"

//DOM-IGNORE-END

#endif // _DAI_AGGR_H

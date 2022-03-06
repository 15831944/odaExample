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

#ifndef _DAI_CONST_ITERATOR_H
#define _DAI_CONST_ITERATOR_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"
#include "RxValue.h"

#include "daiBuildOptions.h"
#include "daiAggr/daiAggr.h"

namespace OdDAI {

  /** \details
  Abstract class for access to typed const iterator along aggregate.
  */
  class DAI_EXPORT ConstIterator
  {
  public:

    virtual ~ConstIterator() {};

    virtual void beginning() = 0;
    virtual bool next() = 0;  
    virtual bool previous() = 0;

    virtual void end() = 0;

    virtual const OdRxValue getCurrentMember() const = 0;

    virtual int getValueBound() const = 0;
    virtual bool testCurrentMember() const = 0;

    virtual const OdRxValueType& type() const = 0;
  };
  typedef OdSharedPtr<ConstIterator> ConstIteratorPtr;

}


#endif // _DAI_CONST_ITERATOR_H

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

#ifndef _DAI_AGGR_INSTANCE_UTILS_H_
#define _DAI_AGGR_INSTANCE_UTILS_H_

#include "daiAggregationType.h"
#include "daiAggr/impl/daiAggrBaseInstance.h"

namespace OdDAI
{
  namespace utils
  {
    template<class TDefaultInstanceClass>
    OdDAI::AggrInstance& getDefaultInstance(OdDAI::AggregationType* aggregationType)
    {
      const OdDAI::AggrInstance* cachedInstance = aggregationType->getCachedAggrInstance();
      if (cachedInstance)
      {
        return *const_cast<OdDAI::AggrInstance*>(cachedInstance);
      }

      OdDAI::AggrInstancePtr result (new TDefaultInstanceClass(aggregationType));
      aggregationType->setCachedAggrInstance(result);
      return *result;
    }

  }
}

#endif

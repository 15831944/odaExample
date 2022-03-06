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

#ifndef _DAI_AGGR_TYPE_EXTRACTOR_H
#define _DAI_AGGR_TYPE_EXTRACTOR_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiAggregationType.h"
#include "daiEntity.h"
#include "daiExplicitAttribute.h"

namespace OdDAI
{
  namespace utils
  {
    inline const OdDAI::AggregationType* extractTypeByName(OdDAI::Entity* entity, const char* name)
    {
      auto& attributesColleciton = entity->attributes();
      for (const auto& attribute : attributesColleciton.getArray())
      {
        if (attribute->name() != name)
        {
          continue;
        }

        auto explicitAttribute = OdDAI::ExplicitAttribute::cast(attribute);
        auto domain = explicitAttribute->domain();

        if (!domain->isAggregationType())
        {
          ODA_ASSERT(0);
          return nullptr;
        }

        return domain->aggregationType();
      }

      ODA_ASSERT(0);
      return nullptr;
    }

    inline const OdDAI::AggregationType* extractTypeByNameFull(OdDAI::Entity* entity, const char* name)
    {
      auto& attributesColleciton = entity->explicitAttributes();

      for (const auto& attribute : attributesColleciton)
      {
        if (attribute->name() != name)
        {
          continue;
        }

        auto explicitAttribute = OdDAI::ExplicitAttribute::cast(attribute);
        auto domain = explicitAttribute->domain();

        if (!domain->isAggregationType())
        {
          ODA_ASSERT(0);
          return nullptr;
        }

        return domain->aggregationType();
      }

      ODA_ASSERT(0);
      return nullptr;
    }
  }
}

#endif // _DAI_AGGR_TYPE_EXTRACTOR_H

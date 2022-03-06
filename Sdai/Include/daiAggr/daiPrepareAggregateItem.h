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

#ifndef _DAI_PREPARE_AGGREGATE_ITEM_H
#define _DAI_PREPARE_AGGREGATE_ITEM_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiEnum.h"
#include "daiSelect.h"


/** A special class for internal use. */
namespace OdDAI
{
  template<typename TItem, class SchemaItemTypeProvider>
  class DAI_EXPORT ListTyped;

  template<typename TItem, class SchemaItemTypeProvider>
  class DAI_EXPORT SetTyped;
}

namespace OdDAI
{
  template<class SchemaItemTypeProvider>
  void  prepareAggregateItem(const ListTyped<OdDAI::Enum, SchemaItemTypeProvider>& aggr, OdDAI::Enum& aggrItem)
  {
    aggrItem = OdDAI::Enum(SchemaItemTypeProvider::SchemaType());
  }

  template<class SchemaItemTypeProvider>
  void  prepareAggregateItem(const ListTyped<OdDAI::Select, SchemaItemTypeProvider>& aggr, OdDAI::Select& aggrItem)
  {
    aggrItem = OdDAI::Select(SchemaItemTypeProvider::SchemaType());
  }


  template<class SchemaItemTypeProvider>
  void  prepareAggregateItem(const SetTyped<OdDAI::Enum, SchemaItemTypeProvider>& aggr, OdDAI::Enum& aggrItem)
  {
    aggrItem = OdDAI::Enum(SchemaItemTypeProvider::SchemaType());
  }

  template<class SchemaItemTypeProvider>
  void  prepareAggregateItem(const SetTyped<OdDAI::Select, SchemaItemTypeProvider>& aggr, OdDAI::Select& aggrItem)
  {
    aggrItem = OdDAI::Select(SchemaItemTypeProvider::SchemaType());
  }

  template <class TAggr, class TAggrItem>
  void  prepareAggregateItem(const TAggr& aggr, TAggrItem& aggrItem)
  {
  }

}

//DOM-IGNORE-END

#endif // _DAI_PREPARE_AGGREGATE_ITEM_H

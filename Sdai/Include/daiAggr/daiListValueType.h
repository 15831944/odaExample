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

#ifndef _DAI_LIST_VALUE_TYPE_H_
#define _DAI_LIST_VALUE_TYPE_H_

#include "daiAggrBaseValueType.h"

namespace OdDAI {
  template<class T> class List;
  class Aggr;
  class Entity;
}

DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<bool>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<int>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<double>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAIObjectId>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdAnsiString>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::Entity*>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::AttributePtr>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::ErrorEventPtr>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::WhereRulePtr>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::Select>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::Enum>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR_PTR(OdDAI::List<OdDAI::Aggr*>, DAI_EXPORT);

DAI_DECLARE_VT_AGGR(OdDAI::List<int>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<double>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAIObjectId>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdAnsiString>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAI::Entity*>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAI::AttributePtr>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAI::ErrorEventPtr>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAI::Select>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAI::Enum>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::List<OdDAI::Aggr*>, DAI_EXPORT);


#endif // _DAI_LIST_VALUE_TYPE_H_


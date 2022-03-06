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

#ifndef _DAI_AGGR_BASE_VALUE_TYPE_H_
#define _DAI_AGGR_BASE_VALUE_TYPE_H_

#include "daiAggrValueTypeDefinitions.h"
#include "SmartPtr.h"

namespace OdDAI {
  class Aggr;
  class Entity;
  class Select;

  class Attribute;
  typedef OdSmartPtr<Attribute> AttributePtr;

  class ErrorEvent;
  typedef OdSmartPtr<ErrorEvent> ErrorEventPtr;

  class WhereRule;
  typedef OdSmartPtr<WhereRule> WhereRulePtr;

  class GlobalRule;
  typedef OdSmartPtr<GlobalRule> GlobalRulePtr;
}

DAI_DECLARE_VT_AGGR(OdDAI::Aggr*, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::Aggr* >, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::Entity*>, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::AttributePtr>, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::ErrorEventPtr>, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::WhereRulePtr>, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::GlobalRulePtr>, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray<OdDAI::Select>, DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray< OdArray< OdDAIObjectId > >,  DAI_EXPORT);
ODRX_DECLARE_VALUE_TYPE(OdArray< OdArray< OdAnsiString  > >, DAI_EXPORT);




#endif // _DAI_AGGR_BASE_VALUE_TYPE_H_

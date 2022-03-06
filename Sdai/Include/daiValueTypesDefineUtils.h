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

#ifndef _DAI_VALUE_TYPES_DEFINE_UTILS_H_
#define _DAI_VALUE_TYPES_DEFINE_UTILS_H_

#include "OdaCommon.h"

#define ODRX_DEFINE_NONBLITTABLE_VALUE_TYPE(valType, g_var, exp_attr)\
static OdRxValueType* g_var = 0; \
exp_attr const OdRxValueType& OdRxValueType::Desc<valType>::value() throw() \
{ \
  if (g_var == 0)  {\
    static OdMutex m;\
    TD_AUTOLOCK(m);\
		g_var = new OdRxNonBlittableType<valType>(__OD_T(#valType), 0); \
  }\
  return *g_var; \
} \
exp_attr void OdRxValueType::Desc<valType>::del() \
{ \
  if (g_var) \
  { \
    ::odrxClassDictionary()->remove(__OD_T(#valType)); \
    delete g_var; \
    g_var = 0; \
  } \
} \
template<> exp_attr OdRxValue::OdRxValue(const valType& val) throw() : m_type(OdRxValueType::Desc<valType>::value()) \
{ \
  initNonBlittable(val); \
} \
template<> bool OdRxNonBlittableType<valType>::subEqualTo(const void* a, const void* b) const \
{ \
  return *(valType*)a == *(valType*)b; \
}

#define ODRX_DEFINE_SUBTOSTRING_DUMMY(valType, exp_attr)\
template<> exp_attr OdString OdRxNonBlittableType< valType >::subToString(const void* instance, OdRxValueType::StringFormat) const\
{\
  if (!instance)\
    throw OdError(L"Empty string instance");\
  return OdString(OD_T("Not implemented yet."));\
}

#define ODRX_DECLARE_VALUE_TYPE_PTR(type, attribute)\
template<> struct OdRxValueType::Desc<type>\
{\
  attribute static const OdRxValueType& value() throw();\
  attribute static void del();\
};\
template<> OdRxValue::OdRxValue(type const&) throw();


#endif // _DAI_VALUE_TYPES_DEFINE_UTILS_H_

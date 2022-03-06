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

#include "RxValue.h"
#include "RxValueType.h"
#include "RxDictionary.h"

#ifndef _DAI_VALUE_TYPE_DEFINITIONS_H_
#define _DAI_VALUE_TYPE_DEFINITIONS_H_

#define DAI_DECLARE_VT_AGGR(type_name, exp_attr)\
  template<> struct OdRxValueType::Desc<type_name>\
  {\
    exp_attr static const OdRxValueType& value() throw();\
    exp_attr static void del();\
  };\
  template<> OdRxValue::OdRxValue(type_name const &) throw();

#define DAI_DECLARE_VT_AGGR_PTR(type_name, exp_attr)\
  template<> struct OdRxValueType::Desc<type_name*>\
  {\
    exp_attr static const OdRxValueType& value() throw();\
    exp_attr static void del();\
  };\
  template<> OdRxValue::OdRxValue(type_name* const &) throw();


#define DEFINE_VALUE_TYPE_VAR_NAME(type) m_g ## type ## Type



////////////////////////////////////////////////////////////////////////////////////
// Define for pointer to aggregate (extract direct pointer to aggregate from SDAI).
////////////////////////////////////////////////////////////////////////////////////

#define DAI_DEFINE_AGGRPTR_TYPE_NO_EQ(type, subtype, g_var, aggrType, exp_attr)\
  static OdRxValueType* g_var = 0;\
  exp_attr const OdRxValueType& OdRxValueType::Desc<type*>::value() throw()\
  {\
    if (g_var == 0){\
      static OdMutex m;\
      TD_AUTOLOCK(m);\
      if (g_var == 0)\
        g_var = new aggrType ## PtrValueTypePOD<type, subtype>(__OD_T(#type), 0);\
    }\
    return *g_var;\
  }\
  \
  exp_attr void OdRxValueType::Desc<type*>::del()\
  {\
    if (g_var)\
    {\
      ::odrxClassDictionary()->remove(__OD_T(#type)); \
      delete g_var;\
      g_var = 0;\
    }\
  }\
  template<> exp_attr OdRxValue::OdRxValue(type* const & val) throw() : m_type(OdRxValueType::Desc<type*>::value()) { initBlittable<sizeof(type*) <= 24>(&val, sizeof(type*)); }

#define DAI_DEFINE_AGGRPTR_VALUE_TYPE(type, subtype, g_var, aggrType, exp_attr)\
  DAI_DEFINE_AGGRPTR_TYPE_NO_EQ(type, subtype, g_var, aggrType, exp_attr)\
  template<> exp_attr bool OdRxValueTypePOD<type*>::subEqualTo(const void* a, const void* b) const{  return *(type**)a == *(type**)b; }



////////////////////////////////////////////////////////////////////////////////////
// Define for aggregate (set attribute for Aggregate with putAttr).
////////////////////////////////////////////////////////////////////////////////////

#define DAI_DEFINE_AGGR_TYPE_NO_EQ(type, subtype, g_var, aggrType, exp_attr)\
static OdRxValueType* g_var = 0;\
exp_attr const OdRxValueType& OdRxValueType::Desc<type>::value() throw()\
{\
  if (g_var == 0){\
    static OdMutex m;\
    TD_AUTOLOCK(m);\
    if (g_var == 0)\
      g_var = new aggrType ## ValueTypePOD<type, subtype>(__OD_T(#type), 0);\
  }\
  return *g_var;\
}\
\
exp_attr void OdRxValueType::Desc<type>::del()\
{\
  if (g_var)\
  {\
    ::odrxClassDictionary()->remove(__OD_T(#type)); \
    delete g_var;\
    g_var = 0;\
  }\
}\
template<> exp_attr OdRxValue::OdRxValue(type const & val) throw() : m_type(OdRxValueType::Desc<type>::value()) { initBlittable<sizeof(type) <= 24>(&val, sizeof(type)); }

#define DAI_DEFINE_AGGR_VALUE_TYPE(type, subtype, g_var, aggrType, exp_attr)\
DAI_DEFINE_AGGR_TYPE_NO_EQ(type, subtype, g_var, aggrType, exp_attr)\
template<> exp_attr bool OdRxValueTypePOD<type>::subEqualTo(const void* a, const void* b) const{  return *(type*)a == *(type*)b; }

////////////////////////////////////////////////////////////////////////////////////
// Define for aggregate (set attribute for Aggregate with putAttr).
////////////////////////////////////////////////////////////////////////////////////


#endif // _DAI_AGGR_VALUE_TYPE_H_

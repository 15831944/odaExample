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

#ifndef _AGGR_VALUE_EXTRACTOR_H_
#define _AGGR_VALUE_EXTRACTOR_H_

#include "daiError/daiException.h"


  // Value exctract util
template<class TSimpleType>
class VArgValueExtractor
{
public:
  VArgValueExtractor(va_list& argumentList, bool autoCloseArgs, bool isPointer)
    : m_argumentList(argumentList)
    , m_autoCloseArgs(autoCloseArgs)
  {
    m_value = va_arg(m_argumentList, TSimpleType);
    if (isPointer && m_value == NULL)
    {
      throw OdDAI::DaiException(sdaiSY_ERR, "Underlying system error", TD_FUNC);
      return;
    }
  }

  ~VArgValueExtractor()
  {
    if (m_autoCloseArgs)
    {
      va_end(m_argumentList);
    }
  }

  const TSimpleType& value() const
  {
    return m_value;
  }

private:
  TSimpleType   m_value;
  bool          m_autoCloseArgs;
  va_list&      m_argumentList;
};

#endif // _DAI_UTILS_H_


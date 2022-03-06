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

#ifndef _DAI_CUSTOM_COMPARE_H_
#define _DAI_CUSTOM_COMPARE_H_

#include "OdaCommon.h"
#include "daiBuildOptions.h"

#include "RxValueType.h"
#include "RxValue.h"

#include "daiUtils/daiUnset.h"

#include "daiPrimitive.h"

class OdRxValue;

namespace OdDAI
{

  class FileDescription;
  class FileName;
  class FileSchema;

  bool DAI_EXPORT operator==(const FileDescription& left, const FileDescription& right);
  bool DAI_EXPORT operator==(const FileName& left, const FileName& right);
  bool DAI_EXPORT operator==(const FileSchema& left, const FileSchema& right);

}

namespace OdDAI
{
  namespace compare
  {
    template<typename TLeft, typename TRight>
    inline bool isEqual(const TLeft& left, const TRight& right)
    {
      ODA_ASSERT(0 && "Error state. Try to implement comparison for this types.");
      return false;
    }

    template<typename SomeType>
    inline bool isEqual(const SomeType& left, const SomeType& right)
    {
      return left == right;
    }

    inline bool isEqual(const double& left, const double& right)
    {
      return !OdCmpDouble(left, right);
    }

    inline bool isEqual(const OdDAI::EnumValueInfo &left, const OdDAI::EnumValueInfo &right)
    {
      return left.value == right.value || odStrCmpA(left.value, right.value) == 0;
    }

    template<>
    inline bool isEqual(const OdRxValue& left, const OdRxValue& right)
    {
      if (left.type() == OdRxValueType::Desc<double>::value() && 
          right.type() == OdRxValueType::Desc<double>::value())
      {
        double leftValue = OdDAI::Utils::getUnset<double>();
        double rightValue = OdDAI::Utils::getUnset<double>();
        return left >> leftValue &&
          right >> rightValue &&
          (isEqual(leftValue, rightValue) || OdDAI::Utils::isUnset(leftValue) == OdDAI::Utils::isUnset(rightValue));
      }

      return left == right;
    }

    template<typename TArrayType>
    bool isEqual(const OdArray<TArrayType>& left, const OdArray<TArrayType>& right)
    {
      if (left.length() != right.length())
      {
        return false;
      }

      for (unsigned int indexElement = 0; indexElement < left.length(); ++indexElement)
      {
        if (!isEqual(left[indexElement], right[indexElement]))
        {
          return false;
        }
      }

      return true;
    }

  }
}

#endif // _DAI_UTILS_H_


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

#ifndef _DAI_VALUE_TYPES_H_
#define _DAI_VALUE_TYPES_H_

#include "OdaCommon.h"
#include "daiValueTypesDefineUtils.h"
#include "RxValue.h"
#include "RxProperty.h"
#include "RxValueTypeUtil.h"
#include "RxAttribute.h"
#include "RxCategory.h"

#include "daiObjectId.h"
#include "daiObjectSDAI.h"
#include "daiPrimitive.h"
#include "daiAggr/daiAggrUtils.h"
#include "daiAggr/daiAggrs.h"
#include "daiAggr/daiList.h"
#include "daiError/daiErrorEvent.h"
#include "daiRules/daiWhereRule.h"
#include "daiRules/daiGlobalRule.h"

FIRSTDLL_EXPORT void odrxSetMemberConstructor(OdRxClass* pClass, OdRxMemberCollectionConstructorPtr pc, void* data = 0);

/** \details
OdRxValueType specialization for 'OdDAIObjectId' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAIObjectId, DAI_EXPORT);

/** \details
OdRxValueType specialization for 'OdArray<OdDAIObjectId>' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAIObjectIds, DAI_EXPORT);


/** \details
OdRxValueType specialization for 'OdDAI::Logical' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::Logical, DAI_EXPORT);

/** \details
OdRxValueType specialization for 'OdDAI::Boolean' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::Boolean, DAI_EXPORT);

/** \details
OdRxValueType specialization for 'OdDAI::EnumValueInfo' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::EnumValueInfo, DAI_EXPORT);

/** \details
OdRxValueType specialization for 'OdDAI::Select::OdSelectKind' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdTCKind, DAI_EXPORT);


/** \details
OdRxValueType specialization for 'OdDAI::AttributePtr' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::AttributePtr, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils {
    template <> inline const AttributePtr& getUnset< AttributePtr >() { static AttributePtr OdAttributePtrUnset; return OdAttributePtrUnset; }
  }
}

/** \details
OdRxValueType specialization for 'OdDAI::ErrorEventPtr' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::ErrorEventPtr, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils {
    template <> inline const ErrorEventPtr& getUnset< ErrorEventPtr >() { static ErrorEventPtr errorEventPtr; return errorEventPtr; }
  }
}

/** \details
OdRxValueType specialization for 'OdDAI::WhereRulePtr' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::WhereRulePtr, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils {
    template <> inline const WhereRulePtr& getUnset< WhereRulePtr >() { static WhereRulePtr WhereRulePtrUnset; return WhereRulePtrUnset; }
  }
}

/** \details
OdRxValueType specialization for 'OdDAI::GlobalRulePtr' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::GlobalRulePtr, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils {
    template <> inline const GlobalRulePtr& getUnset< GlobalRulePtr >() { static GlobalRulePtr GlobalRulePtrUnset; return GlobalRulePtrUnset; }
  }
}

/** \details
OdRxValueType specialization for 'OdDAI::EntityPtr' value type
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::EntityPtr, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils
  {
    template <> inline const OdDAI::EntityPtr& getUnset<OdDAI::EntityPtr>() { static OdDAI::EntityPtr boolUnset;  return boolUnset; }
  }
}


//DOM-IGNORE-BEGIN

/** \details
OdRxValueType specialization for 'OdDAI::ApplicationInstancePtr' value type
\remark
This value type is used for transferring application instance which is instantiated during derived attribute
evaluation. In this case application instance isn't added into model, so it is provided directly using OdRxValue.
This value type is for internal use only.
*/
ODRX_DECLARE_VALUE_TYPE(OdDAI::ApplicationInstancePtr, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils {
    template <> inline const ApplicationInstancePtr& getUnset< ApplicationInstancePtr >() { static ApplicationInstancePtr ApplicationInstancePtrUnset; return ApplicationInstancePtrUnset; }
  }
}

//DOM-IGNORE-END

namespace OdDAI
{
  class DictionaryInstance;
  class Schema;
}

#include "daiAttributeDataBlockValueType.h"
#include "daiSelectValueType.h"
#include "daiEnumValueType.h"

/** \details
OdRxValueType specialization for 'OdDAI::ErrorEventPtr*' value type
*/
ODRX_DECLARE_VALUE_TYPE_PTR(OdDAI::ErrorEventPtr*, DAI_EXPORT);


/** \details
OdRxValueType specialization for 'OdDAI::OdDAIObjectSDAI*' value type
*/
ODRX_DECLARE_VALUE_TYPE_PTR(OdDAI::OdDAIObjectSDAI*, DAI_EXPORT);

/** \details
OdRxValueType specialization for 'OdDAI::DictionaryInstance*' value type
*/
template<> struct OdRxValueType::Desc<OdDAI::DictionaryInstance*>
{
  DAI_EXPORT static const OdRxValueType& value() throw();
  DAI_EXPORT static void del();
};

/** \details
OdRxValueType specialization for 'OdDAI::Schema*' value type
*/
ODRX_DECLARE_VALUE_TYPE_PTR(OdDAI::Schema*, DAI_EXPORT);

/** \details
 OdRxValueType specialization for 'OdDAI::Entity*' value type
 */
ODRX_DECLARE_VALUE_TYPE_PTR(OdDAI::Entity*, DAI_EXPORT);
namespace OdDAI
{
  namespace Utils { 
    template <> inline Entity* const& getUnset<Entity*>() { static Entity* const OdEntityPtrUnset = NULL; return OdEntityPtrUnset; } 
  }
}

#include "daiAggr/daiArrayValueType.h"
#include "daiAggr/daiAggr.h"


inline bool setSelectValue(const int& from, OdDAI::Select* to)
{
  return to && to->setInt32(from);
}

inline bool setSelectValue(const double& from, OdDAI::Select* to)
{
  return to && to->setDouble(from);
}

inline bool setSelectValue(const OdAnsiString& from, OdDAI::Select* to)
{
  return to && to->setString(from);
}

inline bool setSelectValue(const OdDAIObjectId& from, OdDAI::Select* to)
{
  return to && to->setHandle(from);
}


template<class  AggrContainer, typename TArrayValue >
inline bool tryConvertOdArrayToSelectArray(const OdRxValue& from, AggrContainer& to, OdDAI::Select* sampledAggrItem)
{
  if (!sampledAggrItem)
  {
    return false;
  }

  const OdRxValueType& vt = from.type();
  if (vt != OdRxValueType::Desc<OdArray<TArrayValue> >::value())
  {
    return false;
  }

  const OdArray<TArrayValue>* arrSrc = rxvalue_cast<OdArray<TArrayValue>>(&from);

  OdArray<typename AggrContainer::template_type> arrDest;
  unsigned int srcSize = arrSrc->size();

  if (srcSize <= 0)
  {
    return false;
  }
  arrDest.reserve(srcSize);

  for (typename OdArray<TArrayValue>::const_iterator it = arrSrc->begin(), end = arrSrc->end();
        it < end; ++it)
  {
    if (!setSelectValue(*it, sampledAggrItem))
    {
      return false;
    }

    arrDest.append(*((typename AggrContainer::template_type*)sampledAggrItem));
  }

  to.setArray(arrDest);
  return true;
}

  template<typename ValueType, class AggrContainer>
  inline bool extractionOperatorImpl (const OdRxValue& lhs, AggrContainer& aggr)
  {
    const OdRxValueType& vt = lhs.type();

    if (vt == OdRxValueType::Desc< OdArray<ValueType> >::value())
    {
      const OdArray<ValueType>* arr = rxvalue_cast<OdArray< ValueType > >(&lhs);
      aggr.setArray(*arr);
      return true;
    }
    else if (vt == OdRxValueType::Desc<OdArray<OdRxValue> >::value())
    {
      aggr.createEmpty();

      const OdArray<OdRxValue>* arrSrc = rxvalue_cast<OdArray<OdRxValue> >(&lhs);

      OdArray<ValueType> arrDest;

      unsigned int srcSize = arrSrc->size();
      if (srcSize > 0)
      {
        arrDest.reserve(srcSize);

        ValueType selVal = aggr.template generateAggrItem<ValueType>();

        for (OdArray<OdRxValue>::const_iterator it = arrSrc->begin(), end = arrSrc->end();
          it < end; ++it)
        {
          if (((*it) >> selVal) == false)
            return false;
          arrDest.append(selVal);
        }
      }

      aggr.setArray(arrDest);
      return true;
    }
    else
    if (vt == OdRxValueType::Desc<typename AggrContainer::base_type* >::value() ||
        vt == OdRxValueType::Desc<OdDAI::Aggr* >::value())
    {
      OdDAI::Aggr* aggrSource = nullptr;
      if ((lhs >> aggrSource) == false || !aggrSource)
      {
        return false;
      }

      aggr.createEmpty();
      return aggr.copyFromAggr(*aggrSource);
    }
    else
    {
      const OdRxValueType& vt2 = OdRxValueType::Desc<ValueType>::value();
      if (vt2.isSelect())
      {
        OdDAI::Select* selectPtr;
        OdRxValue v = vt2.createValue();
        
        if (v >> selectPtr)
        {
          aggr.createEmpty();

          *selectPtr = aggr.template generateAggrItem<OdDAI::Select>();

          return tryConvertOdArrayToSelectArray<AggrContainer, OdDAIObjectId>(lhs, aggr, selectPtr)||
            tryConvertOdArrayToSelectArray<AggrContainer, int>(lhs, aggr, selectPtr)||
            tryConvertOdArrayToSelectArray<AggrContainer, double>(lhs, aggr, selectPtr)||
            tryConvertOdArrayToSelectArray<AggrContainer, OdAnsiString>(lhs, aggr, selectPtr);
        }

        ODA_ASSERT(0);
      }
    }

    return false;
  }

template<typename ValueType>
inline bool operator >> (const OdRxValue& lhs, OdDAI::Array<ValueType>& aggr)
{
  return extractionOperatorImpl<ValueType, OdDAI::Array<ValueType>>(lhs, aggr);
}

template<typename ValueType>
inline bool operator >> (const OdRxValue& lhs, OdDAI::Bag<ValueType>& aggr)
{
  return extractionOperatorImpl<ValueType, OdDAI::Bag<ValueType>>(lhs, aggr);
}

template<typename ValueType>
inline bool operator >> (const OdRxValue& lhs, OdDAI::List<ValueType>& aggr)
{
  return extractionOperatorImpl<ValueType, OdDAI::List<ValueType>>(lhs, aggr);
}

template<typename ValueType>
inline bool operator >> (const OdRxValue& lhs, OdDAI::Set<ValueType>& aggr)
{
  return extractionOperatorImpl<ValueType, OdDAI::Set<ValueType>>(lhs, aggr);
}


template<typename ValueType>
inline bool operator >> (const OdRxValue& lhs, OdArray< OdArray<ValueType>>& rhs)
{
  OdDAI::List<OdDAI::Aggr*>* listAggr;
  if (lhs >> listAggr)
  {
    return listAggr->getArrayValues<OdDAI::Aggr*, OdArray<ValueType>>(rhs);
  }

  OdDAI::Array<OdDAI::Aggr*>* arrayAggr;
  if (lhs >> arrayAggr)
  {
    return arrayAggr->getArrayValues<OdDAI::Aggr*, OdArray<ValueType>>(rhs);
  }

  return lhs.operator >> (rhs);
}


#include "daiAggr/daiArrayValueType.h"
#include "daiAggr/daiBagValueType.h"
#include "daiAggr/daiListValueType.h"
#include "daiAggr/daiSetValueType.h"

//-----------------------------------------------------------------------------------------

class DAI_EXPORT OdDAIRxHierarchyLevelAttribute : public OdRxHierarchyLevelAttribute
{
public:
  ODRX_DECLARE_MEMBERS(OdDAIRxHierarchyLevelAttribute);
  virtual OdString value(OdRxValue& value);
};
typedef OdSmartPtr<OdDAIRxHierarchyLevelAttribute> OdDAIRxHierarchyLevelAttributePtr;

#include "daiEnumValueType.h"



#endif // _DAI_VALUE_TYPES_H_

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

#ifndef _DAI_CONVERT_H_
#define _DAI_CONVERT_H_

#include "OdaCommon.h"
#include "daiBuildOptions.h"
#include "DbHandle.h"
#include "daiConsts.h"
#include "OdString.h"
#include "sdai.h"
#include "daiLogicalType.h"
#include "daiAggr/daiAggr.h"

/** \details
  Provides a set of functionality for working with DAI.
*/
namespace OdDAI
{
  /** \details
  Contains a set of functionality for working with conversion.
  */
  namespace convert
  {
    template<class TCpp, class TSdai>
    inline void toSdai(const TCpp& valueFrom, TSdai& valueTo)
    {
      valueTo = valueFrom;
    }

    template<>
    inline void toSdai<bool, SdaiBoolean>(const bool& valueFrom, SdaiBoolean& valueTo)
    {
      valueTo = valueFrom ? sdaiTRUE : sdaiFALSE;
    }

    typedef const char* cppcharptr;
    template<>
    inline void toSdai<cppcharptr, SdaiString>(const cppcharptr& valueFrom, SdaiString& valueTo)
    {
      valueTo = reinterpret_cast<SdaiString>(const_cast<char*>(valueFrom));
    }

    template<>
    inline void toSdai<OdAnsiString, SdaiString>(const OdAnsiString& valueFrom, SdaiString& valueTo)
    {
      valueTo = reinterpret_cast<SdaiString>(const_cast<char*>(valueFrom.c_str()));
    }

    template<>
    inline void toSdai<OdDAIObjectId, SdaiInstance>(const OdDAIObjectId& valueFrom, SdaiInstance& valueTo)
    {
      OdDAI::ApplicationInstancePtr entity = valueFrom.openObject();
      valueTo = !entity.isNull() ? reinterpret_cast<SdaiInstance>(entity.get()) : 0;
    }

    template<>
    inline void toSdai<OdDAI::Logical, SdaiLogical>(const OdDAI::Logical& valueFrom, SdaiLogical& valueTo)
    {
      valueTo = static_cast<Logical_>(valueFrom);
    }


    typedef OdDAI::Aggr* cppaggrbaseptr;
    template<>
    inline void toSdai<cppaggrbaseptr, SdaiAggr>(const cppaggrbaseptr& valueFrom, SdaiAggr& valueTo)
    {
      valueTo = reinterpret_cast<SdaiAggr>(const_cast<OdDAI::Aggr*>(valueFrom));
    }
  }



  namespace convert
  {
    template<class TSdai, class TCpp>
    inline void fromSdai(const TSdai& valueFrom, TCpp& valueTo)
    {
      valueTo = valueFrom;
    }

    template<>
    inline void fromSdai<SdaiBoolean, bool>(const SdaiBoolean& valueFrom, bool& valueTo)
    {
      valueTo = valueFrom  != sdaiFALSE;
    }

    typedef const char* cppcharptr;
    template<>
    inline void fromSdai<SdaiString, cppcharptr>(const SdaiString& valueFrom, cppcharptr& valueTo)
    {
      valueTo = reinterpret_cast<SdaiString>(const_cast<char*>(valueFrom));
    }

    template<>
    inline void fromSdai<SdaiInstance, OdDAIObjectId>(const SdaiInstance& valueFrom, OdDAIObjectId& valueTo)
    {
      OdDAI::ApplicationInstance* entityFrom = reinterpret_cast<OdDAI::ApplicationInstance*>(valueFrom);
      if (entityFrom != NULL)
      {
        valueTo = entityFrom->id();
      }
    }

    template<>
    inline void fromSdai<SdaiLogical, OdDAI::Logical>(const SdaiLogical& valueFrom, OdDAI::Logical& valueTo)
    {
      valueTo = static_cast<Logical_>(valueFrom);
    }


    typedef OdDAI::Aggr* cppaggrbaseptr;
    template<>
    inline void fromSdai<SdaiAggr, cppaggrbaseptr>(const SdaiAggr& valueFrom, cppaggrbaseptr& valueTo)
    {
      valueTo = reinterpret_cast<OdDAI::Aggr*>(valueFrom);
    }
  }
}

#endif // _DAI_UTILS_H_


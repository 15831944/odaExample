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

#ifndef _DAI_UNSET_H_
#define _DAI_UNSET_H_

#include "DbHandle.h"
#include "daiConsts.h"
#include "OdString.h"

namespace OdDAI
{
  namespace Utils
  {

    template <class TUnsetable>
    const TUnsetable& getUnset() { ODA_ASSERT_ONCE(0 && "Unknown type. Add getUnset for it."); static TUnsetable unsettled = 0; return unsettled; }

    template <> inline const bool& getUnset<bool>() { static bool boolUnset = false;  return boolUnset; }
    template <> inline const double& getUnset<double>() { return Consts::OdNan; }
    template <> inline const long& getUnset<long>() { return Consts::OdLongUnset; }
    template <> inline const int& getUnset<int>() { return Consts::OdIntUnset; }
    template <> inline const OdString& getUnset<OdString>() { static OdString stringUnset = Consts::OdStringUnset; return stringUnset; }
    template <> inline const OdAnsiString& getUnset<OdAnsiString>() { static OdAnsiString stringUnset = Consts::OdStringUnset; return stringUnset; }
    template <> inline const OdUInt64& getUnset<OdUInt64>() { static OdUInt64 handleValUnset = OdDAIObjectId::kNull.getHandle(); return handleValUnset; }
    template <> inline const OdDbHandle& getUnset<OdDbHandle>() { static OdDbHandle handleUnset = OdDAIObjectId::kNull.getHandle(); return handleUnset; }
    template <> inline const OdDAIObjectId& getUnset<OdDAIObjectId >() { return Consts::OdHandleUnset; }
#ifdef _MSC_VER
    template <> inline const unsigned long& getUnset<unsigned long>() { return Consts::OdULongUnset; }
#endif

    inline bool isUnset(const bool& value) { return value != getUnset<bool>(); }
    inline bool isUnset(const float & value) { return value != value; }
    inline bool isUnset(const double & value) { return value != value; }
    inline bool isUnset(const long value) { return value == Consts::OdLongUnset; }
    inline bool isUnset(const int value) { return value == Consts::OdIntUnset; }
    inline bool isUnset(const OdString & value) { return value.getLength() == Consts::OdStringUnsetLength && value.compare(Consts::OdStringUnset) == 0; }
    inline bool isUnset(const OdAnsiString & value) { return value.getLength() == Consts::OdStringUnsetLength && value.compare(Consts::OdStringUnset) == 0; }
    inline bool isUnset(const char * value) { return strlen(value) == Consts::OdStringUnsetLength && strcmp(value, Consts::OdStringUnset) == 0; }
    inline bool isUnset(const OdUInt64 & value) { return Consts::OdHandleUnset.getHandle() == value; }
    inline bool isUnset(const OdDbHandle & value) { return Consts::OdHandleUnset.getHandle() == (OdUInt64)value; }
    inline bool isUnset(const OdDAIObjectId & value) { return value.isNull() || value.isErased(); }
#ifdef _MSC_VER
    inline bool isUnset(const unsigned long value) { return value == Consts::OdULongUnset; }
#endif
  }


}

#endif // _DAI_UNSET_H_


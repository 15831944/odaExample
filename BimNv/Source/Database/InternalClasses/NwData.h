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

#ifndef __NWDATA_INCLUDED_
#define __NWDATA_INCLUDED_

#include "NwVariant.h"
#include "NwDataType.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "SmartPtr.h"
#include "NwModelUnits.h"

class OdNwProperty;
typedef OdSmartPtr<OdNwProperty> OdNwPropertyPtr;
class OdNwData;
typedef std::shared_ptr<OdNwData> OdNwDataPtr;
typedef std::weak_ptr<OdNwData> OdNwDataWeakPtr;

class NWDBEXPORT OdNwData
{
public:
  OdNwData() = default;
  ~OdNwData() = default;

public:
  //pPropUnits - is model units for double property type
  static OdNwPropertyPtr createPropertyByData(const OdString& name, const OdString& displayName, OdNwDataPtr pRealData, const NwModelUnits::Enum* pPropUnits = nullptr);

public:
  NwDataType::Enum getType() const;
  const OdNwVariant& getValue() const;

public:
  void setType(NwDataType::Enum type);
  template <typename T>
  void setValue(T val)
  {
    m_value = OdNwVariant(val);
  }

protected:
  NwDataType::Enum m_type;
  OdNwVariant m_value;
};

#endif //__NWDATA_INCLUDED_

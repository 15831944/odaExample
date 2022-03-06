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

#ifndef __NWPROPERTY_OVERRIDE_ATTIRBUTE_INCLUDED_
#define __NWPROPERTY_OVERRIDE_ATTIRBUTE_INCLUDED_

#include "NwExport.h"
#include "SmartPtr.h"
#define STL_USING_MEMORY
#define STL_USING_VECTOR
#define STL_USING_UTILITY
#include "OdaSTL.h"

class OdNwName;
typedef OdSmartPtr<OdNwName> OdNwNamePtr;
class OdNwData;
typedef std::shared_ptr<OdNwData> OdNwDataPtr;

class NWDBEXPORT OdNwPropertyOverrideAttribute
{
  using OdNwDataNamePropetry = std::pair<OdNwNamePtr, OdNwDataPtr>;
public:
  OdNwPropertyOverrideAttribute();
  ~OdNwPropertyOverrideAttribute() = default;

public:
  OdNwNamePtr getName() const;
  inline std::vector<OdNwDataNamePropetry>& getProperties() { return m_vProperties; }

public:
  void setName(OdNwNamePtr pName);

protected:
  OdNwNamePtr m_pName;
  std::vector<OdNwDataNamePropetry> m_vProperties;
};

typedef std::shared_ptr<OdNwPropertyOverrideAttribute> OdNwPropertyOverrideAttributePtr;
typedef std::weak_ptr<OdNwPropertyOverrideAttribute> OdNwPropertyOverrideAttributeWeakPtr;

#endif //__NWPROPERTY_OVERRIDE_ATTIRBUTE_INCLUDED_

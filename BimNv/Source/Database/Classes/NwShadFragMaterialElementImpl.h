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

#ifndef __NW_SHAD_FRAG_MATERIAL_ELEMENT_IMPL_H__
#define __NW_SHAD_FRAG_MATERIAL_ELEMENT_IMPL_H__

#include "NwShadFragMaterialElement.h"
#include "NwObjectImpl.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"

class OdNwGraphicAppearance;
typedef OdSmartPtr<OdNwGraphicAppearance> OdNwGraphicAppearancePtr;

class OdNwShadFragMaterialElementImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwShadFragMaterialElement)
public:
  OdNwShadFragMaterialElementImpl();
  virtual ~OdNwShadFragMaterialElementImpl();
  ODRX_DECLARE_MEMBERS(OdNwShadFragMaterialElementImpl);

public:
  static OdNwShadFragMaterialElementImpl* getImpl(const OdNwShadFragMaterialElement* pNwNode);
  static OdNwShadFragMaterialElementImpl* getImpl(const OdRxObject* pRxNode);

public:
  inline std::vector<OdNwGraphicAppearancePtr>& getOverrideAppearance() { return m_vOverrideAppearance; }
  inline std::vector<OdNwObjectIdArray>& getPathLinks() { return m_aPathLinks; }
  OdNwGraphicAppearancePtr getPermanentAppearance() const;
  OdUInt32 getOverridesCount() const;
  OdResult getOverrides(const OdNwObjectId& ownerId, OdUInt32 idx, OdNwObjectIdArray& modelItems, OdNwObjectId& materialId) const;

public:
  void setPermanentAppearance(OdNwGraphicAppearancePtr pAppearance);

protected:
  std::vector<OdNwGraphicAppearancePtr> m_vOverrideAppearance;
  std::vector<OdNwObjectIdArray> m_aPathLinks;
  OdNwGraphicAppearancePtr m_pPermanentAppearance;
};

typedef OdSmartPtr<OdNwShadFragMaterialElementImpl> OdNwShadFragMaterialElementImplPtr;

#endif //__NW_SHAD_FRAG_MATERIAL_ELEMENT_IMPL_H__

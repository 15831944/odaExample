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

#ifndef __NWCATEGORYIMPL_INCLUDED__
#define __NWCATEGORYIMPL_INCLUDED__

#include "NwCategory.h"
#include "NwPropertyValue.h"

typedef std::map<OdString, OdNwPropertyPtr> OdNwPropertiesMap;

class OdNwCategoryImpl : public OdNwModelBaseImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwCategory)
public:
  OdNwCategoryImpl();
  OdNwCategoryImpl(const OdString& name, const OdString& displayName);
  virtual ~OdNwCategoryImpl();
  ODRX_DECLARE_MEMBERS(OdNwCategoryImpl);

public:
  static OdNwCategoryImpl* getImpl(const OdNwCategory* pNwCategory);
  static OdNwCategoryImpl* getImpl(const OdRxObject* pRxCategory);

public:
  inline void setHasStableId(bool hasStableId) { m_bHasStableId = hasStableId; }
  //public implementation's methods
  //Does this category contain any type of stable id ? A stable id can be used to identify the same ModelItem across multiple versions of a Model.A category with a stable id contains only a single property with the value of the id
  inline bool hasStableId() const { return m_bHasStableId; }
  OdUInt64 getInt64StableId() const;
  OdString getStringStableId() const;
  OdResult getProperties(OdNwPropertiesMap& mProperties) const;

public:
  /// removes all stored properties.
  void Clear();

  /// Adds property to this category.
  bool Add(OdNwPropertyPtr pProperty);

  template <class T>
  void Add(const OdString& name, const OdString& displayName, T value)
  {
    Add(OdNwObjectImpl::createNwObject<OdNwProperty>(new OdNwPropertyValue<T>(name, displayName, value)));
  }

protected:
  template <class T>
  void changeName(OdSmartPtr<OdNwPropertyValue<T> > pProperty)
  {
    ODA_ASSERT(pProperty.get());

    // Extend category name by display name to prevent categories loss in case of same name.
    if (!m_bIsNameCorrected)
    {
      m_bIsNameCorrected = true;
      setClassName(getClassName() + OD_T("_") + getClassDisplayName());
    }

    // Categories and properties in nwd can have same names for all entries.
    // Furthermore, properties with same name and display name can have different data types.
    // So such name correction is necessary to prevent loss of properties data in dgn.
    OdInt32 i = 2;
    OdString nameToCheck = getClassName() + OD_T("_") + pProperty->getClassName() + getTypeSuffix(pProperty->m_value);
    OdString name = nameToCheck;
    for (OdNwPropertiesMap::iterator prop_iter = m_mProperties.find(name); prop_iter != m_mProperties.end(); prop_iter = m_mProperties.find(name))
    {
      name = nameToCheck + OdString().format(OD_T("_%d"), i);
      ++i;
    }

    pProperty->setClassName(name);
  }

private:
  template <typename T> OdString getTypeSuffix(T propValue) { return OD_T("_S"); }
  OdString getTypeSuffix(const bool &propValue) { return OD_T("_B"); }
  OdString getTypeSuffix(const double &propValue) { return OD_T("_D"); }
  OdString getTypeSuffix(const float &propValue) { return OD_T("_F"); }
  OdString getTypeSuffix(const OdInt32 &propValue) { return OD_T("_I"); }
  OdString getTypeSuffix(const OdInt8 &propValue) { return OD_T("_I"); }
  OdString getTypeSuffix(const OdUInt32 &propValue) { return OD_T("_I"); }
  OdString getTypeSuffix(const OdUInt8 &propValue) { return OD_T("_I"); }
  OdString getTypeSuffix(const OdUInt64 &propValue) { return OD_T("_L"); }
  OdString getTypeSuffix(const tm &propValue) { return OD_T("_DT"); }
  OdString getTypeSuffix(const OdNwColor &propValue) { return OD_T("_CL"); }
  OdString getTypeSuffix(const OdGePoint3d &propValue) { return OD_T("_P3D"); }
  OdString getTypeSuffix(const OdGePoint2d &propValue) { return OD_T("_P2D"); }

public:
  const OdNwPropertiesMap& getProperties() const;
  OdResult addProperties(const OdString& key, OdNwPropertyPtr pProp);

protected:
  OdNwPropertiesMap m_mProperties;
  bool m_bIsNameCorrected;
  bool m_bHasStableId;
};

typedef OdSmartPtr<OdNwCategoryImpl> OdNwCategoryImplPtr;

#endif //__NWCATEGORYIMPL_INCLUDED__

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

#ifndef __NWMODELITEMNODEIMPL_INCLUDED__
#define __NWMODELITEMNODEIMPL_INCLUDED__

#include "NwModelItemNode.h"
#include "NwModelBaseImpl.h"
#include "OdArray.h"
#define STL_USING_ALGORITHM
#define STL_USING_VECTOR
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "NwExport.h"
#include "NwModelUnits.h"

class OdGeMatrix3d;
typedef std::map<OdString, OdNwCategoryPtr> OdCategoriesMap;
class OdNwAttribute;
typedef OdSmartPtr<OdNwAttribute> OdNwAttributePtr;
class OdNwModelItem;
class OdNwGuidStoreStreamLoader;
typedef std::weak_ptr<OdNwGuidStoreStreamLoader> OdNwGuidStoreStreamLoaderWeakPtr;

class NWDBEXPORT OdNwModelItemNodeImpl : public OdNwModelBaseImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwModelItemNode)
public:
  OdNwModelItemNodeImpl();
  virtual ~OdNwModelItemNodeImpl();
  ODRX_DECLARE_MEMBERS(OdNwModelItemNodeImpl);

public:
  static OdNwModelItemNodeImpl* getImpl(const OdNwModelItemNode* pNwNode);
  static OdNwModelItemNodeImpl* getImpl(const OdRxObject* pRxNode);

  static bool getTransformMatrixCategory(OdNwModelItemNodeImpl* pModelItemImpl, OdGeMatrix3d& trMat);

public:
  OdGUID getInstanceGuid() const;
  OdResult getPropertyCategories(std::map<OdString, OdNwCategoryPtr>&, OdUInt32 categoryTypes) const;
  OdResult getAttributes(OdArray<OdNwAttributePtr>& aAttributes, OdUInt32 categoryTypes) const;
  virtual NwModelUnits::Enum getNodeUnits() const;

  //ItemProperty public methods:
  OdString getClassName() const;
  OdString getClassUserName() const;
  OdString getUserName() const;

  //new objects methods
  inline OdUInt32& getFlags() { return m_flags; }
  inline std::vector<OdNwAttributePtr>& getAttributes() { return m_vAttributes; }
  OdNwModelItem* getPathLink() const;
  inline OdUInt32 getGuidIdx() const { return m_guidIndex; }

  //flags methods:
  inline bool IsOriginalOverrideHideRender() const  { return m_flags & 0x10000; }
  inline bool IsOriginalOverrideForceRender() const { return m_flags & 0x20000; }
  inline bool IsOriginalOverrideIgnoreClip() const  { return m_flags & 0x40000; }
  inline bool IsOriginalOverrideMaterial() const    { return m_flags & 0x80000; }
  inline bool IsOriginalOverrideIgnorePick() const  { return m_flags & 0x100000; }
  inline bool IsGroup() const                       { return m_flags & 0x1000000; }
  inline bool IsGeometry() const                    { return m_flags & 0x2000000; }
  inline bool IsPartition() const                   { return m_flags & 0x4000000; }
  inline bool IsDynamic() const                     { return m_flags & 0x8000000; }
  inline bool IsInsert() const                      { return (m_flags & 0x70000000) == 0x10000000; }
  inline bool IsLayer() const                       { return (m_flags & 0x70000000) == 0x20000000; }
  inline bool IsComposite() const                   { return (m_flags & 0x70000000) == 0x40000000; }
  inline bool IsCollection() const                  { return (m_flags & 0x70000000) == 0x30000000; }

public:
  void setGuidIndex(OdUInt32 index);
  OdResult addAttribute(OdNwAttributePtr pAttr);
  void setPathLink(OdNwModelItem* pPathLink);
  void addPathLinkInstance(OdNwModelItem* pPathLink);
  void setGuidLoader(OdNwGuidStoreStreamLoaderWeakPtr pGuidLoader);
  void setUserName(const OdString& name);
  void setClassName(const OdString& name);
  void setClassUserName(const OdString& dispName);

protected:
  OdUInt32 m_flags;
  OdUInt32 m_guidIndex;
  std::vector<OdNwAttributePtr> m_vAttributes;
  OdNwModelItem* m_pPathLink;
  std::vector<OdNwModelItem*> m_vInstances;
  OdNwGuidStoreStreamLoaderWeakPtr m_pGuidLoader;
};

#endif //__NWMODELITEMNODEIMPL_INCLUDED__

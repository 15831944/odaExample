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

#ifndef __NWMODELITEMIMPL_INCLUDED__
#define __NWMODELITEMIMPL_INCLUDED__

#include "NwModelItem.h"
#include "NwObjectImpl.h"
#include "NwExport.h"

class OdNwModelItemNode;
typedef OdSmartPtr<OdNwModelItemNode> OdNwModelItemNodePtr;
class OdNwRunModelItem;

class NWDBEXPORT OdNwModelItemImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwModelItem)
public:
  OdNwModelItemImpl();
  virtual ~OdNwModelItemImpl();
  ODRX_DECLARE_MEMBERS(OdNwModelItemImpl);

protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const override;

public:
  static OdNwModelItemImpl* getImpl(const OdNwModelItem* pNwNode);
  static OdNwModelItemImpl* getImpl(const OdRxObject* pRxNode);

public:
  //public implementation's methods
  virtual OdGeExtents3d getBoundingBox() const;
  OdResult getAncestors(OdNwObjectIdArray& aAncestors) const;
  OdResult getAncestorsAndSelf(OdNwObjectIdArray& aAncestors) const;
  virtual OdResult getChildren(OdNwObjectIdArray& aChildren) const;
  virtual OdResult getDescendants(OdNwObjectIdArray& aDescendants) const;
  virtual OdResult getDescendantsAndSelf(OdNwObjectIdArray& aDescendants) const;
  virtual bool hasGeometry() const;
  virtual OdNwObjectId getGeometryComponentId() const;
  OdGUID getInstanceGuid() const;
  OdNwModelItemPtr getParent() const;
  OdNwObjectId getParentId() const;
  OdResult getPropertyCategories(std::map<OdString, OdNwCategoryPtr>&) const;
  OdResult getSelectivePropertyCategories(std::map<OdString, OdNwCategoryPtr>& mCategories, OdUInt32 categoryTypes) const;
  OdResult getAttributes(OdArray<OdNwAttributePtr>& aAttributes, OdUInt32 categoryTypes) const;
  OdString getClassDisplayName() const;
  OdString getClassName() const;
  virtual OdString getDisplayName() const;
  NwModelItemIcon::Enum getIcon() const;
  bool isHidden() const;
  bool isRequired() const;

public:
  OdNwModelItemNode* getRealNode() const;

public:
  OdNwObjectId addModelItem(const OdString& sClassName, const OdString& sClassDisplayName, NwModelItemIcon::Enum icon, const OdString& sDisplayName, OdResult* pResCode);
  OdResult setIsHidden(bool value);
protected:
  //set is hidden value for all framents in branch of tree where current node is root
  virtual OdResult subSetIsHidden(bool value);

public:
  virtual void subHighlight(const bool bDoIt, const OdNwFullSubentPath* pPath,
    const bool) const;

  void highlight(const bool bDoIt, const OdNwFullSubentPath* pPath,
    const bool highlightAll) const;

//path link's methods block
public:
  OdNwModelItem*      getHead() const;
  OdNwModelItem*      getFirstChild() const;
  OdNwModelItem*      getNextSibling() const;
  OdNwModelItem*      getChild(OdUInt32 pos) const;
  OdNwRunModelItem*   getFirstRunPath() const;
public:
  void setRealNode(OdNwModelItemNode* pNode);
  void setHead(OdNwModelItem* pHead);
  void setNextInstance(OdNwModelItem* pPathLink);
  void setFirstChild(OdNwModelItem* pPathLink);
  void setNextSibling(OdNwModelItem* pPathLink);
//
private:
  OdNwModelItemNode*   m_pNode;
  OdNwModelItem*       m_pHead;
  OdNwModelItem*       m_pNextInstance;
  OdNwModelItem*       m_pFirstChild;
  OdNwModelItem*       m_pNextSibling;
};

typedef OdSmartPtr<OdNwModelItemImpl> OdNwModelItemImplPtr;

#endif //__NWMODELITEMIMPL_INCLUDED__

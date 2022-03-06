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

#ifndef __NWTREEITEMBUILDER_INCLUDED__
#define __NWTREEITEMBUILDER_INCLUDED__

#include "RxSystemServices.h"
#include "Ge/GeExtents3d.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"

class OdNwTreeItem;
typedef OdSmartPtr<OdNwTreeItem> OdNwTreeItemPtr;
class OdNwObject;
typedef OdSmartPtr<OdNwObject> OdNwObjectPtr;

struct OdNwTreeItemRange
{
  OdNwTreeItemRange()
    : m_boundBox()
    , m_triangCount(0)
    , m_treeItemsCount(0)
    , m_itBgnTreeItem()
    , m_itEndTreeItem()
  {}

  OdGeExtents3d m_boundBox;
  OdUInt32 m_triangCount;
  OdUInt32 m_treeItemsCount;
  std::vector<OdNwObjectPtr>::iterator m_itBgnTreeItem;
  std::vector<OdNwObjectPtr>::iterator m_itEndTreeItem;
};

class OdNwTreeItemBuilder
{
public:
  OdNwTreeItemBuilder(std::vector<OdNwObjectPtr>&& vCurLevelTreeItems);
  ~OdNwTreeItemBuilder();

public:
  OdNwTreeItemPtr build();

  void staticBuild();
  bool sortAndGroupFragments(OdNwTreeItemRange& originalTreeItemRange, OdNwTreeItemRange& resultTreeItemRange);
  void groupFragmentsByCoordParamsToRanges(OdNwTreeItemRange& originalTreeItemRange, OdUInt32 coordIdx, double dCenterCoord, double minDiv, double maxDiv, OdNwTreeItemRange& lowerRange, OdNwTreeItemRange& higherRange, OdNwTreeItemRange& centerRange);

  OdNwTreeItemPtr dynamicBuild();
  void sortAndGroupTreeItems(OdNwTreeItemRange& originalTreeItemRange, OdNwTreeItemRange& resultTreeItemRange, OdUInt32 maxChildrenCount);
  void sortTreeItemRange(OdNwTreeItemRange& boundBox, OdUInt32 coordIdx);
  void splitDynamicGroup(std::vector<OdNwObjectPtr>& tempTreeItemRanges, std::vector<OdNwObjectPtr>::iterator it1stTreeItemRange, std::vector<OdNwObjectPtr>::iterator it2ndTreeItemRange);

  OdNwTreeItemPtr oldBuild();

private:
  std::vector<OdNwObjectPtr> m_vCurLevelTreeItems;
};

#endif //__NWTREEITEMBUILDER_INCLUDED__

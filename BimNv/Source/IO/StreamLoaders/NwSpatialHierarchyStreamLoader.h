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
#ifndef __NW_SPATIALHIERARCHYSTREAMLOADER_H__
#define __NW_SPATIALHIERARCHYSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "TD_PackPush.h"

class OdNwFragmentsStreamLoader;
class OdNwTreeItem;
typedef OdSmartPtr<OdNwTreeItem> OdNwTreeItemPtr;

class OdNwSpatialHierarchyStreamLoader : public OdNwStreamLoader
{
public:
  OdNwSpatialHierarchyStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwSpatialHierarchyStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

public:
  OdNwTreeItemPtr getRootTreeItem() const;

public:
  void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;

protected:
  OdNwTreeItemPtr m_pRootTreeItem;
  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;
  std::weak_ptr<OdNwFragmentsStreamLoader> m_pFragmentsLoader;
};

typedef std::shared_ptr<OdNwSpatialHierarchyStreamLoader> OdNwSpatialHierarchyStreamLoaderPtr;
typedef std::weak_ptr<OdNwSpatialHierarchyStreamLoader> OdNwSpatialHierarchyStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_SPATIALHIERARCHYSTREAMLOADER_H__

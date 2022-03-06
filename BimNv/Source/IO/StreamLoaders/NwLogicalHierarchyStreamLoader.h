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
#ifndef __NW_LOAGICALHIERARCHYSTREAMLOADER_H__
#define __NW_LOAGICALHIERARCHYSTREAMLOADER_H__

#include "NwStreamLoader.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "TD_PackPush.h"

class OdNwPartitionNode;
typedef OdSmartPtr<OdNwPartitionNode> OdNwPartitionNodePtr;
class OdNwObjectReaderManager;
typedef OdSharedPtr<OdNwObjectReaderManager> OdNwObjectReaderManagerPtr;
class OdNwPathLinkMap;
typedef std::shared_ptr<OdNwPathLinkMap> OdNwPathLinkMapPtr;
class OdNwObjectId;

class OdNwLogicalHierarchyStreamContext : public OdNwStreamContext
{
public:
  explicit OdNwLogicalHierarchyStreamContext(const OdNwStreamContext& ctx);
  virtual ~OdNwLogicalHierarchyStreamContext() = default;

  OdNwPartitionNodePtr getRootPartition() const;
  OdNwPathLinkMapPtr getPathLinkMap() const;
  void setRootPartition(OdNwPartitionNodePtr pRoot);

  void setPartitionPropsExist(bool val);
  bool getPartitionPropsExist() const;

protected:
  OdNwPartitionNodePtr m_pRootPartition;
  OdNwPathLinkMapPtr m_pPathLinkMap;
  bool m_bPartitionPropsExist;
};

class OdNwLogicalHierarchyStreamLoader : public OdNwStreamLoader
{
public:
  OdNwLogicalHierarchyStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwLogicalHierarchyStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  OdResult parseStream() override;

  OdNwObjectId getRootNode() const;
  OdNwPathLinkMapPtr getPathLinkMap() const;

  virtual void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;
  inline const std::vector<OdUInt32>& getPartPropsBlocks() { return m_vPartPropsBlocks; }

protected:
  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;

  std::vector<OdUInt32> m_vPartPropsBlocks;
  OdNwObjectReaderManagerPtr m_pReaderMgr;
};

typedef std::shared_ptr<OdNwLogicalHierarchyStreamLoader> OdNwLogicalHierarchyStreamLoaderPtr;
typedef std::weak_ptr<OdNwLogicalHierarchyStreamLoader> OdNwLogicalHierarchyStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_LOAGICALHIERARCHYSTREAMLOADER_H__

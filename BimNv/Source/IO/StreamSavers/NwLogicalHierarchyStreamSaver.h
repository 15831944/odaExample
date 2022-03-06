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
#ifndef __NW_LOGICALHIERARCHYSTREAMSAVER_H__
#define __NW_LOGICALHIERARCHYSTREAMSAVER_H__

#include "NwStreamSaver.h"
#include "NwStreamContext.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "TD_PackPush.h"

class OdNwLogicalHierarchyStreamSaverContext : public OdNwStreamContext
{
public:
  OdNwLogicalHierarchyStreamSaverContext(const OdNwStreamContext& ctx, OdNwObjectPtr pPartition, std::shared_ptr<std::vector<OdInt32> > pPartPropsBlocks);
  virtual ~OdNwLogicalHierarchyStreamSaverContext() = default;

public:
  OdNwObjectPtr getPartition() const;
  inline std::shared_ptr<std::vector<OdInt32> >& getPartPropsBlocks() { return m_pPartPropsBlocks; }

protected:
  OdNwObjectPtr m_pRootPartition;
  std::shared_ptr<std::vector<OdInt32> > m_pPartPropsBlocks;
};

class OdNwLogicalHierarchyStreamSaver : public OdNwStreamSaver
{
public:
  OdNwLogicalHierarchyStreamSaver(const OdNwStreamContextPtr& ctx);
  virtual ~OdNwLogicalHierarchyStreamSaver();
  virtual OdResult saveToStream();
};

typedef std::shared_ptr<OdNwLogicalHierarchyStreamSaver> OdNwLogicalHierarchyStreamSaverPtr;
typedef std::weak_ptr<OdNwLogicalHierarchyStreamSaver> OdNwLogicalHierarchyStreamSaverWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_LOGICALHIERARCHYSTREAMSAVER_H__

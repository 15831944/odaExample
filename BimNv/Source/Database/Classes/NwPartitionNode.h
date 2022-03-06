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

#ifndef __TNW_PARTITIONNODE_H__
#define __TNW_PARTITIONNODE_H__

#include "NwGroupModelItemNode.h"
#include "NwModelUnits.h"

class OdGeVector3d;

class NWDBEXPORT OdNwPartitionNode : public OdNwGroupModelItemNode
{
  ODRX_DECLARE_MEMBERS(OdNwPartitionNode);
  
public:
  OdNwPartitionNode();

public:
  virtual ~OdNwPartitionNode();

public:
  OdString getCreator() const;
  OdString getSourceFileName() const;
  OdGeVector3d getUpVector() const;
  void setUpVector(const OdGeVector3d &);
  OdGeVector3d getNorthVector() const;
  void setNorthVector(const OdGeVector3d &);
  OdGeVector3d getFrontVector() const;
  void setFrontVector(const OdGeVector3d &);
  //return model units which declared in this partition
  NwModelUnits::Enum getModelUnits() const;
  void setModelUnits(NwModelUnits::Enum units);
};

typedef OdSmartPtr<OdNwPartitionNode> OdNwPartitionNodePtr;

#endif //__TNW_PARTITIONNODE_H__

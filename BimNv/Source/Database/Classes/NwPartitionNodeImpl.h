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

#ifndef __NW_PARTITION_NODE_IMPL_H__
#define __NW_PARTITION_NODE_IMPL_H__

#include "NwPartitionNode.h"
#include "NwGroupModelItemNodeImpl.h"
#include "NwColor.h"
#include "Ge/GeExtents2d.h"
#include "NwFormatVersionEx.h"
#include "NwPartitionUsage.h"
#include "NwAngularUnits.h"

class OdNwDatabaseImpl;

class NWDBEXPORT OdNwPartitionNodeImpl : public OdNwGroupModelItemNodeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwPartitionNode)
public:
  OdNwPartitionNodeImpl();
  virtual ~OdNwPartitionNodeImpl();
  ODRX_DECLARE_MEMBERS(OdNwPartitionNodeImpl);

public:
  static OdNwPartitionNodeImpl* getImpl(const OdNwPartitionNode* pNwPart);
  static OdNwPartitionNodeImpl* getImpl(const OdRxObject* pRxPart);

public:
  void setUsage(NwPartitionUsage::Enum val);
  void setModelType(OdUInt32 val);
  void setCompactFragOnce(bool val);
  void setHasMergedDuplicategeometry(bool val);
  void setGlobalAmbient(const OdNwColor& val);
  void setCreator(const OdString& val);
  void setFileFormat(NwFormatVersionEx::Enum val);
  void setModelUnits(NwModelUnits::Enum val);
  void setAngularUnits(NwAngularUnits::Enum val);
  void setUpVector(const OdGeVector3d& val);
  void setNorthVector(const OdGeVector3d& val);
  void setFrontVector(const OdGeVector3d& val);
  void setSortStatus(bool val);
  void setCollateLocal(const OdString& val);
  void setSourceFileName(const OdString& val);
  void set2DTessalationBox(const OdGeExtents2d& val);
  void setHasSchema(bool val);

public:
  NwPartitionUsage::Enum getUsage() const;
  OdUInt32 getModelType() const;
  bool isCompactFragOnce() const;
  bool hasMergedDuplicategeometry() const;
  OdNwColor getGlobalAmbient() const;
  OdString getCreator() const;
  NwFormatVersionEx::Enum getFileFormat() const;
  NwModelUnits::Enum getModelUnits() const;
  NwAngularUnits::Enum getAngularUnits() const;
  OdGeVector3d getUpVector() const;
  OdGeVector3d getNorthVector() const;
  OdGeVector3d getFrontVector() const;
  bool getSortStatus() const;
  OdString getCollateLocal() const;
  OdString getSourceFileName() const;
  OdGeExtents2d get2DTessalationBox() const;
  bool hasSchema() const;

  std::vector<OdNwObjectPtr>& getLights();

  NwModelUnits::Enum getNodeUnits() const override;

public:
//path link generated methods
  OdResult createReadRunPathLinks(OdNwModelItem* pPathLink, OdNwModelItemNodePtr pNode, OdNwDatabaseImpl* pDbImpl);
  OdResult createReadRunPathLinksWithIdx(OdNwModelItem* pPathLink, OdNwModelItemNodePtr pNode, OdUInt32 idx, OdNwDatabaseImpl* pDbImpl);

protected:
  NwPartitionUsage::Enum m_usage;
  OdUInt32 m_modelType;
  bool m_bIsCompactFragOnce;
  bool m_bHasMergedDuplicategeometry;
  OdNwColor m_globalAmbient;
  OdString m_creator;
  NwFormatVersionEx::Enum m_fileFormat;
  NwModelUnits::Enum m_modelUnits;
  NwAngularUnits::Enum m_angularUnits;
  OdGeVector3d m_upVector;
  OdGeVector3d m_northVector;
  OdGeVector3d m_frontVector;
  bool m_bSortStatus;
  OdString m_collateLocal;
  OdString m_sourceFileName;
  OdGeExtents2d m_2DTessalationBox;
  bool m_bHasSchema;
  std::vector<OdNwObjectPtr> m_vLights;
};



#endif //__NW_PARTITION_NODE_IMPL_H__

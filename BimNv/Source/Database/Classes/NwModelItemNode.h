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

#ifndef __TNW_MODELITEMNODE_H__
#define __TNW_MODELITEMNODE_H__

#include "NwModelBase.h"
#include "NwExport.h"
#define STL_USING_MAP
#include "OdaSTL.h"
#include "NwModelUnits.h"

class OdGUID;
class OdNwCategory;
typedef OdSmartPtr<OdNwCategory> OdNwCategoryPtr;
class OdNwPathLink;
typedef OdSmartPtr<OdNwPathLink> OdNwPathLinkPtr;
class OdNwModelItem;
class OdNwAttribute;
typedef OdSmartPtr<OdNwAttribute> OdNwAttributePtr;

/** \details
  This class represents an instance node within the model hierarchy.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwModelItemNode : public OdNwModelBase
{
  ODRX_DECLARE_MEMBERS(OdNwModelItemNode);

public:
  OdNwModelItemNode();
  explicit OdNwModelItemNode(OdNwObjectImpl* pImpl);

public:
  virtual ~OdNwModelItemNode();

public:
  OdString getClassDisplayName() const;
  OdString getClassName() const;
  OdString getDisplayName() const;
  OdGUID getInstanceGuid() const;
  OdResult getPropertyCategories(std::map<OdString, OdNwCategoryPtr>& mCategories, OdUInt32 categoryTypes) const;
  OdResult getAttributes(OdArray<OdNwAttributePtr>& aAttributes, OdUInt32 categoryTypes) const;

  OdNwModelItem* getPathLink() const;
  NwModelUnits::Enum getNodeUnits() const;

public:
  void setUserName(const OdString& name);
  void setClassName(const OdString& name);
  void setClassUserName(const OdString& name);
  void setPathLink(OdNwModelItem* pPathLink);
  void addPathLinkInstance(OdNwModelItem* pPathLink);
};

typedef OdSmartPtr<OdNwModelItemNode> OdNwModelItemNodePtr;

#endif //__TNW_MODELITEMNODE_H__

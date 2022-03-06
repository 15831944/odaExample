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
#ifndef __NW_PROPERTYOVERRIDEELEMENTSTREAMLOADER_H__
#define __NW_PROPERTYOVERRIDEELEMENTSTREAMLOADER_H__

#include "NwStreamLoader.h"
#define STL_USING_LIST
#include "OdaSTL.h"
#include "TD_PackPush.h"

class OdNwObjectId;
class OdNwPropertyOverrideAttribute;
typedef std::shared_ptr<OdNwPropertyOverrideAttribute> OdNwPropertyOverrideAttributePtr;
typedef std::map<OdNwObjectId, OdArray<OdNwPropertyOverrideAttributePtr> > OdNwPropOverAttrMap;

class OdNwPropertyOverrideElementStreamLoader : public OdNwStreamLoader
{
public:
  OdNwPropertyOverrideElementStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwPropertyOverrideElementStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

public:
  const std::pair<OdNwPropOverAttrMap, OdNwPropOverAttrMap>& getPropertyOverride() const;

public:
  virtual void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;

private:
  //VAS: first element is map which link between path link idx from stream and properties, second map also have key which read like path link index, but it can be node which can not be in OdNwPathLinkMap - this case requires further study
  std::pair<OdNwPropOverAttrMap, OdNwPropOverAttrMap> m_pPropOverAttrMaps;
  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;
};

typedef std::shared_ptr<OdNwPropertyOverrideElementStreamLoader> OdNwPropertyOverrideElementStreamLoaderPtr;
typedef std::weak_ptr<OdNwPropertyOverrideElementStreamLoader> OdNwPropertyOverrideElementStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_PROPERTYOVERRIDEELEMENTSTREAMLOADER_H__

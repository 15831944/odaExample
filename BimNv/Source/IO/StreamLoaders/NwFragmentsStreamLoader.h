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
#ifndef __NW_FRAGMENTSSTREAMLOADER_H__
#define __NW_FRAGMENTSSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "NwExport.h"
#include "TD_PackPush.h"

class OdNwComponent;
typedef OdSmartPtr<OdNwComponent> OdNwComponentPtr;
class OdNwFragmentImpl;
class OdNwObjectId;
typedef OdArray<OdNwObjectId, OdMemoryAllocator<OdNwObjectId> > OdNwObjectIdArray;

class OdNwGeometryStreamLoader;
class OdNwSharedNodesStreamLoader;

class NWDBEXPORT OdNwFragmentsStreamLoader : public OdNwStreamLoader
{
public:
  OdNwFragmentsStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwFragmentsStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

protected:
  virtual void processFragment(OdNwFragmentImpl* pFragImpl);
  virtual void postProcessFragments();

public:
  inline OdNwObjectIdArray& getFragments() { return m_aFragments; }

public:
  virtual void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;

protected:
  OdNwObjectIdArray m_aFragments;

  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;
  std::weak_ptr<OdNwGeometryStreamLoader> m_pGeometryLoader;
  std::weak_ptr<OdNwSharedNodesStreamLoader> m_pSharedNodesLoader;
};

typedef std::shared_ptr<OdNwFragmentsStreamLoader> OdNwFragmentsStreamLoaderPtr;
typedef std::weak_ptr<OdNwFragmentsStreamLoader> OdNwFragmentsStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_FRAGMENTSSTREAMLOADER_H__

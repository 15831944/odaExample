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
#ifndef __NW_SAVED_ANIMATIONS_LOADER_H__
#define __NW_SAVED_ANIMATIONS_LOADER_H__

#include "NwStreamLoader.h"
#include "NwObject.h"
#include "NwSavedAnimElement.h"
template <class C>
class OdNwContextHolder : public OdNwStreamContext
{
public:
  OdNwContextHolder(const OdNwStreamContext& ctx)
    : OdNwStreamContext(ctx)
    , m_val()
  {}

  virtual ~OdNwContextHolder() = default;
  C getContext() const
  {
    return m_val;
  }

  void setContext(C val)
  {
    m_val = val;
  }
protected:
  C m_val;
};

class OdNwSavedAnimationsLoader : public OdNwStreamLoader
{
  OdNwSavedAnimElementPtr m_pSavedAnimElement;
  OdNwObjectId m_SavedAnimElementId;
public:
  OdNwSavedAnimationsLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwSavedAnimationsLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;
  virtual void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;
  OdNwObjectId getSavedAnimationElement();
protected:
  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;

};

#endif  //__NW_SAVED_ANIMATIONS_LOADER_H__

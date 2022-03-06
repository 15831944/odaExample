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

#if !defined(_ODDBLAYOUTMANAGERIMPL_INCLUDED_)
#define _ODDBLAYOUTMANAGERIMPL_INCLUDED_


#define LM_FIRE(method, inparams, params) \
  inline void fire_##method inparams \
  { \
    OdArray<OdTvDbLayoutManagerReactorPtr> reactors = _reactors; \
    for (unsigned i = 0; i < reactors.size(); ++i) \
    { \
      if (_reactors.contains(reactors[i]))\
        reactors[i]->method params; \
    } \
  }

class OdTvDbLayoutManagerImpl
{
public:
  static OdTvDbLayoutManagerImpl* getImpl(OdTvDbLayoutManager* lm){ return lm->m_pImpl; }
  OdArray<OdTvDbLayoutManagerReactorPtr> _reactors;

  LM_FIRE(layoutCreated, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(layoutToBeRemoved, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(layoutRemoved, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(abortLayoutRemoved, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(layoutToBeCopied, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(layoutCopied,(const OdString& s1, const OdTvDbObjectId& id1,const OdString& s2, const OdTvDbObjectId& id2),(s1, id1, s2, id2))
  LM_FIRE(abortLayoutCopied, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(layoutToBeRenamed, (const OdString& s1, const OdString& s2, const OdTvDbObjectId& id), (s1, s2, id))
  LM_FIRE(layoutRenamed, (const OdString& s1,const OdString& s2, const OdTvDbObjectId& id), (s1, s2, id))
  LM_FIRE(abortLayoutRename, (const OdString& s1,const OdString& s2, const OdTvDbObjectId& id), (s1, s2, id))
  LM_FIRE(layoutSwitched, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(plotStyleTableChanged, (const OdString& s, const OdTvDbObjectId& id), (s, id))
  LM_FIRE(layoutToBeDeactivated, (const OdString& s, const OdTvDbObjectId& id), (s, id))
};

#endif //#if !defined(_ODDBLAYOUTMANAGERIMPL_INCLUDED_)

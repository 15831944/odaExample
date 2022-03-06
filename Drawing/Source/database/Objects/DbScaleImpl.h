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

#ifndef _DBSCALE_IMPL_H_INCLUDED_
#define _DBSCALE_IMPL_H_INCLUDED_
#include "DbObjectImpl.h"

class OdDbAnnotationScaleImpl
{
public:
  static OdDbAnnotationScaleImpl* getImpl(OdDbAnnotationScale* s){return s->m_pImpl;}
  static const OdDbAnnotationScaleImpl* getImpl(const OdDbAnnotationScale* s){return s->m_pImpl;}
  OdDbAnnotationScaleImpl() : m_bUnitScale(false), m_dPaper(1), m_dDrawing(1), m_bIsTempScale(true){}
  OdString m_sName;
  double m_dPaper;
  double m_dDrawing;
  bool m_bUnitScale;
  bool m_bIsTempScale;
  OdDbObjectId m_ScaleId;
};

class OdDbAnnotationScaleViewImpl : public OdDbAnnotationScaleImpl
{
};

class OdDbAnnotationScaleReactorMgr : public OdRxObject
{
public:
  bool addReactor(OdDbAnnotationScaleReactor* reactor)
  {
    size_t l = m_reactors.length();
    m_reactors.remove(reactor);
    m_reactors.push_back(reactor);
    return m_reactors.length() == l;
  }
  bool removeReactor(OdDbAnnotationScaleReactor* reactor)
  {
    size_t l = m_reactors.length();
    m_reactors.remove(reactor);
    return m_reactors.length() == l;
  }
  void fire_AnnotationScaleChanged(const OdDbDatabase* pDb, const OdDbViewport* pVp, const OdDbAnnotationScale* pNewScale, const bool bInitializing) const
  {
    try
    {
      OdArray<OdDbAnnotationScaleReactor*> reactors(m_reactors); //local copy; list can change during notifications
      for (unsigned i = 0; i < reactors.size(); ++i)
      {
        if (m_reactors.contains(reactors[i]))
          reactors[i]->annotationScaleChanged(pDb, pVp, pNewScale, bInitializing);
      }
    }
    catch (const OdError&) {}
  }
private:
  OdArray<OdDbAnnotationScaleReactor*> m_reactors;
};

OdDbAnnotationScaleReactorMgr* oddbGetAnnotationScaleReactorMgr();

#endif

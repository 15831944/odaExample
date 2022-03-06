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

#ifndef _ODDBVIEWREPSTANDARDIMPL_INCLUDED_
#define _ODDBVIEWREPSTANDARDIMPL_INCLUDED_

#include "DbViewRepStandard.h"
#include "DbObjectImpl.h"

class OdDbViewRepStandardImpl : public OdDbObjectImpl
{
private:
  friend class OdDbViewRepStandard;

  static OdDbViewRepStandardImpl* getImpl(const OdDbViewRepStandard* pObj)
  { 
    return (OdDbViewRepStandardImpl*) OdDbSystemInternals::getImpl(pObj);
  }
  OdDbViewRepStandardImpl();

  OdUInt32 m_synergyVersion; //enum OdDbViewRepStandard::SynergyVersion // 100 // x64
  OdUInt32 m_previewDisplayType; //enum OdDbViewRepStandard::PreviewDisplayType // 0
  OdUInt32 m_circularThreadEdgeDisplayType; // //enum OdDbViewRepStandard::CircularThreadEdgeDisplayType // 1
  OdUInt32 m_sectionThreadEndDisplayType; //enum OdDbViewRepStandard::SectionThreadEndDisplayType // 0
  OdUInt32 m_projectionType; //enum OdDbViewRepStandard::ProjectionType // 1
  OdUInt32 m_dpiResolutionType; //enum OdDbViewRepStandard::DpiResolutionType // 1
};

#endif // _ODDBVIEWREPSTANDARDIMPL_INCLUDED_

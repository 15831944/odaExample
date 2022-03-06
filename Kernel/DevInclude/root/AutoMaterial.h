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

#pragma once

#include "Gi/GiMaterial.h"
#include "Gi/GiCommonDraw.h"

class AutoMaterial
{
  class OdDbStub* m_pStub;
  OdGiMapper      m_Mapper;
  bool            m_bMapper;
  OdGiCommonDraw* m_pWd;
public:
  inline AutoMaterial(OdGiCommonDraw* pWd)
    : m_pStub(nullptr), m_bMapper(false), m_pWd(pWd)
  {
    if (m_pWd)
    {
      m_pStub = pWd->subEntityTraits().material();
      if (pWd->subEntityTraits().mapper())
      {
        m_bMapper = true;
        m_Mapper = *pWd->subEntityTraits().mapper();
      }
    }
  }

  inline ~AutoMaterial()
  {
    if (m_pWd)
    {
      m_pWd->subEntityTraits().setMaterial(m_pStub);
      m_pWd->subEntityTraits().setMapper(m_bMapper ? &m_Mapper : 0);
    }
  }
};

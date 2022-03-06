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


#ifndef __OD_GE_NM_FUNC__
#define __OD_GE_NM_FUNC__ /* {Secret} */

#include "Ge/GeTol.h"

class OdGeCurve3dImpl;

namespace OdGeNmFunc
{
  struct GeGaussData
  {
    double m_tol;
    double m_dStartParam;
    double m_deltaInterval;
    double m_length;
    double m_eps_prev;
    double m_eps;       
    OdUInt32 m_iMaxNumPoints;
    OdUInt32 m_iNumPoints;
    OdUInt32 m_iCurDiv;
    OdUInt16 m_iCurIteration;

    GeGaussData(const double fromParam, const double toParam, const double tol) :
      m_tol(tol),
      m_dStartParam(fromParam),
      m_deltaInterval(toParam - fromParam),
      m_length(0.0),
      m_eps_prev(0.0),
      m_eps(0.0),
      m_iMaxNumPoints(500000),
      m_iNumPoints(0),
      m_iCurDiv(1),
      m_iCurIteration(0)
    {}
  };

  void gauss(const OdGeCurve3dImpl* pGeCurve, double dStartParam, double dMiddleParam, double dEndParam, double& dValue, GeGaussData& geGaussData);
}

#endif // __OD_GE_NM_FUNC__

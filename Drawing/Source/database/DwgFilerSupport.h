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


#ifndef _DWGFILERSUPPORT_INCLUDED_
#define _DWGFILERSUPPORT_INCLUDED_

#include "DbFiler.h"

namespace OdDb
{

  inline double rdThickness(OdDbDwgFiler* pFiler) { return pFiler->rdThickness(); }
  inline OdGeVector3d& rdR13Extrusion(OdDbDwgFiler* pFiler, OdGeVector3d& p);
  inline OdGeVector3d& rdExtrusion(OdDbDwgFiler* pFiler, OdGeVector3d& p) { p = pFiler->rdExtrusion(); return p; }
  inline void wrThickness(OdDbDwgFiler* pFiler, double val) { pFiler->wrThickness(val); }
  inline void wrR13Extrusion(OdDbDwgFiler* pFiler, const OdGeVector3d& p);
  inline void wrExtrusion(OdDbDwgFiler* pFiler, const OdGeVector3d& p) { pFiler->wrExtrusion(p); }

  inline OdGeVector3d& rdR13Extrusion(OdDbDwgFiler* pFiler, OdGeVector3d& p) {
    p = pFiler->rdVector3d();
    if (p.x == 0.0 && p.y == 0.0)
      p.z = (p.z > 0.0) ? 1.0 : -1.0;
    return p;
  }
  inline void wrR13Extrusion(OdDbDwgFiler* pFiler, const OdGeVector3d& p) {
    if (p.x == 0.0 && p.y == 0.0)
      pFiler->wrVector3d(OdGeVector3d(p.x, p.y, (p.z > 0.0) ? 1.0 : -1.0));
    else
      pFiler->wrVector3d(p);
  }
} // namespace OdDb

#endif //_DWGFILERSUPPORT_INCLUDED_

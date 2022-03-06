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


#ifndef __OD_GE_ENVELOP_UTILS__
#define __OD_GE_ENVELOP_UTILS__ /* {Secret} */

#include "Ge/GePoint3d.h"

class OdGeCurve3d;
struct OdGeUvBox;


#include "TD_PackPush.h"

namespace OdGeEnvelopUtils
{

  /** \details
    Helper class to calculate uv-space on infinite surface without uv-curves.
    Handle applicable flag on calling side.
  */
  class GE_TOOLKIT_EXPORT SurfaceEnvelopeHelper
  {
  public:
    SurfaceEnvelopeHelper(const OdGeSurface& surf);
    SurfaceEnvelopeHelper(const OdGeMatrix3d& cs);

    void addCurve(const OdGeCurve3d& curve, OdGeInterval* interval = NULL);
    void addPoint(const OdGePoint3d& point);
    void addPoints(const OdGePoint3d* points, int pointCount);
    void setExtents(const OdGeExtents3d& extents) {
      m_result = extents;
    }

    static void resetEnvelope(OdGeSurface& surf, const OdGeInterval& u);
    void resetEnvelope(OdGeSurface& surf, double extendBound = 1e-2) const;// add explicit call for plane and cone/cyl
    OdGeInterval getZDirParam(const OdGeSurface& surf, double extendBound = 1e-2) const;
    OdGeUvBox getUV(const OdGePlanarEnt& surf, double extendBound = 1e-2) const;

    const OdGeMatrix3d& coordSystem() const {
      return m_cs;
    }
    OdGeExtents3d extents() const {
      return m_result;
    }
    bool isApplicable() const {
      return m_applicable;
    }
    // Don't throw exception. Check flag.
    bool isFailed() const {
      return m_error;
    }

  private:
    OdGeMatrix3d m_cs;
    OdGeExtents3d m_result;

    bool m_applicable;
    bool m_error;
  };

}

#include "TD_PackPop.h"

#endif // __OD_GE_ENVELOP_UTILS__

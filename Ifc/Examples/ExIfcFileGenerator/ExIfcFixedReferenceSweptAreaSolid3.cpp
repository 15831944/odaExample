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

// ExIfcFixedReferenceSweptAreaSolid3.cpp: implementation of the ExIfcFixedReferenceSweptAreaSolid3 class.
//
//////////////////////////////////////////////////////////////////////

#include "ExIfcFixedReferenceSweptAreaSolid3.h"
#include "ExIfcModelFiller.h"

#include "Ge/GeKnotVector.h"

namespace
{
  struct HIncr
  {
    double add;
    double v;

    HIncr(double incr) : v(0.), add(incr) {}
    double next() {
      return v += add;
    }
    double same() {
      return v;
    }
  };
}

OdIfc::OdIfcEntityPtr ExIfcFixedReferenceSweptAreaSolid3::subProcess()
{
  // bit:
  // 0 profile CW/CCW (result for cw and ccw profile should be same).
  // 1 transform path (x axis of profile plane at start point is not perpendicular to path direction).
  // 2 path is nurbs(smooth)/polyline(non-smooth)

  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_FAIL_M_ONCE("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  OdGePoint2dArray profilePoints;
  // profile
  if (m_subCase & 1)
  {
    // CW
    profilePoints.append(OdGePoint2d(m_profileScale, 0.4 * m_profileScale));
    profilePoints.append(OdGePoint2d(-m_profileScale, 0.4 * m_profileScale));
    profilePoints.append(OdGePoint2d(-m_profileScale, -0.4 * m_profileScale));
  }
  else
  {
    // CCW
    profilePoints.append(OdGePoint2d(m_profileScale, 0.4 * m_profileScale));
    profilePoints.append(OdGePoint2d(-m_profileScale, -0.4 * m_profileScale));
    profilePoints.append(OdGePoint2d(-m_profileScale, 0.4 * m_profileScale));
  }

  OdIfc::OdIfcEntityPtr profileDef = m_b->createProfileBuilder()->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "swept_area_profile", profilePoints);

  OdGePoint3dArray curvePoints;
  HIncr h(0.25 * m_curveScale);

  // rot around x-axis
  curvePoints.append(OdGePoint3d(h.same(), m_curveScale, m_curveScale));
  curvePoints.append(OdGePoint3d(h.same(), m_curveScale, -m_curveScale));
  curvePoints.append(OdGePoint3d(h.next(), -m_curveScale, -m_curveScale));
  curvePoints.append(OdGePoint3d(h.next(), -m_curveScale, m_curveScale));
  curvePoints.append(OdGePoint3d(h.next(), m_curveScale, m_curveScale));
  curvePoints.append(OdGePoint3d(h.same(), m_curveScale, -m_curveScale));

  if (m_subCase & 2)
  {
    OdGeMatrix3d mx(OdGeMatrix3d::rotation(0.1 * OdaPI, OdGeVector3d::kYAxis, curvePoints.first()));
    for (OdGePoint3dArray::iterator it = curvePoints.begin(), end = curvePoints.end(); it != end; ++it) {
      it->transformBy(mx);
    }
  }

  OdIfc::OdIfcEntityPtr directrix;
  if (m_subCase & 4)
  {
    const int degree = 3;
    directrix = m_b->createBSpline(degree, curvePoints, false, OdGeKnotVector());
  }
  else
  {
    directrix = m_b->createPolyline(curvePoints);
  }

  OdIfc::OdIfcEntityPtr sweptArea = m_b->createFixedReferenceSweptAreaSolid(profileDef, m_objectPlacement, directrix, OdDAI::Consts::OdNan, OdDAI::Consts::OdNan, OdGeVector3d::kXAxis);
  setStyledItem(sweptArea, "Dark");

  OdAnsiString strBody("Body");
  OdAnsiString strType("SweptSolid");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(sweptArea->id()));
  model->appendEntityInstance(pSR);

  return pSR;
}

ExIfcFixedReferenceSweptAreaSolid3::ExIfcFixedReferenceSweptAreaSolid3(
  const OdGeMatrix3d &objectPlacement,
  double profileScale,
  double curveScale,
  int subCase
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_profileScale(profileScale)
  , m_curveScale(curveScale)
  , m_subCase(subCase)
{}

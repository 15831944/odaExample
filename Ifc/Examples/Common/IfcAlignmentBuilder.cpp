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

#include "ExIfcModelFiller.h"
#include "IfcAlignmentBuilder.h"
#include "IfcEntity.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcAlignmentBuilder, IfcBuilder, RXIMPL_CONSTR);

OdSmartPtr<IfcAlignmentBuilder> IfcAlignmentBuilder::createObject(ExIfcModelFiller *filler, const OdAnsiString &name)
{
  OdSmartPtr<IfcAlignmentBuilder> res = IfcAlignmentBuilder::desc()->create();
  res->setFiller(filler);
  res->m_name = name;
  return res;
}

OdIfc::OdIfcEntityPtr IfcAlignmentBuilder::appendIfcAlignment()
{
  if (!m_alignment.isNull())
  {
    return m_alignment;
  }

  m_alignment = filler()->model()->createEntityInstance("ifcalignment");
  OdIfc::Utils::assignGlobalId(m_alignment);
  m_alignment->putAttr("ownerhistory", OdDAIObjectId(filler()->ownerHistory()->id()));
  m_alignment->putAttr("name", m_name);
  m_alignment->putAttr("predefinedtype", OdAnsiString("NOTDEFINED"));

  filler()->appendRelContainedInSpatialStructure(filler()->site(), m_alignment);

  return m_alignment;
}

OdIfc::OdIfcEntityPtr IfcAlignmentBuilder::createAlignmentHorizontalSegment(const char *predefinedType)
{
  OdIfc::OdIfcEntityPtr segm = filler()->model()->createEntityInstance("ifcalignmenthorizontalsegment");
  segm->putAttr("predefinedtype", predefinedType);
  return segm;
}


OdIfc::OdIfcEntityPtr IfcAlignmentBuilder::appendHorizontalAlignment(const OdGeCurve2dPtrArray &segments)
{
  if (!m_alignmentHorizontal.isNull())
  {
    ODA_ASSERT("IfcAlignmentHorizontal already appended.");
    return m_alignmentHorizontal;
  }

  if (segments.empty())
    return OdIfc::OdIfcEntityPtr();

  m_alignmentHorizontal = filler()->model()->createEntityInstance("ifcalignmenthorizontal");
  OdIfc::Utils::assignGlobalId(m_alignmentHorizontal);
  m_alignmentHorizontal->putAttr("ownerhistory", OdDAIObjectId(filler()->ownerHistory()->id()));
  OdIfc::OdIfcEntityPtr relNestsHorizontal = filler()->appendRelNests(m_alignment, m_alignmentHorizontal);
  relNestsHorizontal->setInverseCounterParts();

  // TODO: Process segments of other types

  OdDAIObjectIds segmentIds;
  for (auto &crv : segments)
  {
    OdGe::EntityId entityId = crv->type();
    if (entityId == OdGe::kPolyline2d)
    {
      //
      // IfcProduct-derived container for segment
      //
      OdIfc::OdIfcEntityPtr alignmentSegment = filler()->model()->createEntityInstance("ifcalignmentsegment");
      OdIfc::Utils::assignGlobalId(alignmentSegment);
      alignmentSegment->putAttr("ownerhistory", OdDAIObjectId(filler()->ownerHistory()->id()));
      filler()->model()->appendEntityInstance(alignmentSegment);

      //
      // Linear segment processing
      //
      OdIfc::OdIfcEntityPtr horizontalSegment = createAlignmentHorizontalSegment("LINE");

      OdGePolyline2d *polyline2d = (OdGePolyline2d*)(crv.get());
      OdIfc::OdIfcEntityPtr pStartPoint = filler()->createCartesianPoint2D(polyline2d->startPoint());
      OdGeVector2d dir = polyline2d->endPoint() - polyline2d->startPoint();

      horizontalSegment->putAttr("startpoint", OdDAIObjectId(pStartPoint->id()));
      horizontalSegment->putAttr("startdirection", dir.angle());
      horizontalSegment->putAttr("startradiusofcurvature", 0.);
      horizontalSegment->putAttr("endradiusofcurvature", 0.);
      horizontalSegment->putAttr("segmentlength", polyline2d->length());
      OdDAIObjectId idHorizontalSegment = filler()->model()->appendEntityInstance(horizontalSegment);

      alignmentSegment->putAttr("designparameters", idHorizontalSegment);
      segmentIds.append(filler()->model()->appendEntityInstance(alignmentSegment));
    }
  }

  OdIfc::OdIfcEntityPtr segmentsRelNests = filler()->addRelNests(m_alignmentHorizontal, segmentIds);
  segmentsRelNests->setInverseCounterParts();

  m_segments = segments;

  return m_alignmentHorizontal;
}


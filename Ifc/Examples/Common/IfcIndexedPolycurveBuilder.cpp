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
#include "IfcProfileBuilder.h"
#include "IfcEntity.h"
#include "daiUtils/daiUnset.h"

using namespace OdIfc;

ODRX_CONS_DEFINE_MEMBERS(IfcIndexedPolycurveBuilder, IfcBuilder, RXIMPL_CONSTR);

OdSmartPtr<IfcIndexedPolycurveBuilder> IfcIndexedPolycurveBuilder::createObject(
  ExIfcModelFiller *filler)
{
  OdSmartPtr<IfcIndexedPolycurveBuilder> res = IfcIndexedPolycurveBuilder::desc()->create();
  res->setFiller(filler);
  return res;
}

IfcIndexedPolycurveBuilder* IfcIndexedPolycurveBuilder::appendLinear(const OdGePoint2d &p)
{
  OdArray<double> coords;
  coords.append(p.x);
  coords.append(p.y);
  m_points.append(coords);

  unsigned int size = m_points.size();
  if (m_points.size() > 1)
  {
    m_segments.append({ SegmentType::Straight, size - 1, 0, size });
  }
  return this;
}

IfcIndexedPolycurveBuilder* IfcIndexedPolycurveBuilder::appendArc(const OdGePoint2d &pOnArc, const OdGePoint2d &p)
{
  OdArray<double> coords;
  coords.append(pOnArc.x);
  coords.append(pOnArc.y);
  m_points.append(coords);

  coords.clear();
  coords.append(p.x);
  coords.append(p.y);
  m_points.append(coords);
  

  unsigned int size = m_points.size();
  if (m_points.size() > 1)
  {
    m_segments.append({ SegmentType::Arc, size - 2, size - 1, size });
  }
  return this;
}

void IfcIndexedPolycurveBuilder::clear()
{
  m_points.clear();
  m_segments.clear();
}

bool IfcIndexedPolycurveBuilder::isEmpty()
{
  return m_points.isEmpty() && m_segments.isEmpty();
}

bool IfcIndexedPolycurveBuilder::isClosed()
{
  const auto& first = m_segments.first();
  const auto& last = m_segments.last();
  return first.startInd == last.endInd;
}

OdIfc::OdIfcEntityPtr IfcIndexedPolycurveBuilder::finish(bool forceWriteSegments, bool close)
{
  if (isEmpty())
    return OdIfc::OdIfcEntityPtr();

  if (close && !isClosed())
  {
    const auto& first = m_segments.first();
    auto& last = m_segments.last();

    OdGePoint2d startPt(m_points.at(first.startInd - 1)[0], m_points.at(first.startInd - 1)[1]);
    OdGePoint2d endPt(m_points.at(last.endInd - 1)[0], m_points.at(last.endInd - 1)[1]);

    if (startPt == endPt)
    {
      if (last.endInd == m_points.size())
        m_points.removeLast();
      last.endInd = first.startInd;
    }
    else
    {
      // Closing by linear segment only
      m_segments.append({ SegmentType::Straight, last.endInd, 0, first.startInd });
    }
  }

  //
  // IfcCartesianPointList2D
  //
  OdIfc::OdIfcEntityPtr cartesianPointList2D = filler()->model()->createEntityInstance("ifccartesianpointlist2d");
  cartesianPointList2D->putAttr("coordlist", m_points);
  OdDAIObjectId idCartesianPointList2D = filler()->model()->appendEntityInstance(cartesianPointList2D);

  //
  // IfcIndexedPolycurve
  //
  OdIfc::OdIfcEntityPtr indexedPolycurve = filler()->model()->createEntityInstance("ifcindexedpolycurve");
  indexedPolycurve->putAttr("points", idCartesianPointList2D);
  OdDAIObjectId idIndexedPolycurve = filler()->model()->appendEntityInstance(indexedPolycurve);

  bool hasArcSegments = false;
  for (unsigned int i = 0; i < m_segments.size(); ++i)
  {
    if (m_segments.at(i).type == SegmentType::Arc)
    {
      hasArcSegments = true;
      break;
    }
  }

  if (hasArcSegments || isClosed() || forceWriteSegments)
  {
    static OdRxSpecifiedValueType linearType(OdRxValueType::Desc<OdArray<int> >::value(), "IFCLINEINDEX");
    static OdRxSpecifiedValueType arcType(OdRxValueType::Desc<OdArray<int> >::value(), "IFCARCINDEX");

    OdArray<OdRxValue> values;

    struct Segments
    {
      SegmentType type = SegmentType::NotDefined;
      OdArray<int> indexes;
    } current;

    for (unsigned int i = 0; i < m_segments.size(); ++i)
    {
      const Segment &segm = m_segments.at(i);

      if (current.type == SegmentType::NotDefined)
      {
        current.indexes.append(segm.startInd);
        current.type = segm.type;
      }
      else
        if (current.type != segm.type || current.type == SegmentType::Arc)
        {
          OdRxValue val(current.type == SegmentType::Straight ? linearType : arcType, current.indexes);
          values.append(val);

          current.indexes.clear();
          current.indexes.append(segm.startInd);
          current.type = segm.type;
        }

      if (segm.type == SegmentType::Arc)
        current.indexes.append(segm.midInd);
      current.indexes.append(segm.endInd);
    }

    OdRxValue val(current.type == SegmentType::Straight ? linearType : arcType, current.indexes);
    values.append(val);
    indexedPolycurve->putAttr("segments", values);
  }

  clear();

  return indexedPolycurve;
}



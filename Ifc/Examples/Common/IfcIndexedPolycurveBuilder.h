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

#ifndef _IFC_INDEXEDPOLYCURVE_BUILDER_H
#define _IFC_INDEXEDPOLYCURVE_BUILDER_H

#include "IfcBuilder.h"
#include "daiConsts.h"

class IfcIndexedPolycurveBuilder : public IfcBuilder
{
  enum class SegmentType {
    NotDefined,
    Straight,
    Arc
  };

  struct Segment {
    SegmentType type;
    unsigned int startInd;
    unsigned int midInd;
    unsigned int endInd;
  };

protected:

  static OdSmartPtr<IfcIndexedPolycurveBuilder> createObject(ExIfcModelFiller *filler);

  OdAnsiString m_name;

  OdArray<OdArray<double> > m_points;
  OdArray<Segment> m_segments;

  IfcIndexedPolycurveBuilder()
  {};

public:

  ODRX_DECLARE_MEMBERS(IfcIndexedPolycurveBuilder);

  void clear();
  bool isEmpty();
  bool isClosed();
  IfcIndexedPolycurveBuilder* appendLinear(const OdGePoint2d &p);
  IfcIndexedPolycurveBuilder* appendArc(const OdGePoint2d &pOnArc, const OdGePoint2d &p);
  OdIfc::OdIfcEntityPtr finish(bool forceWriteSegments, bool close = false);

  friend class IfcModelFiller;
  friend class IfcRepresentationBuilder;
};
typedef OdSmartPtr<IfcIndexedPolycurveBuilder> IfcIndexedPolycurveBuilderPtr;

#endif // _IFC_INDEXEDPOLYCURVE_BUILDER_H

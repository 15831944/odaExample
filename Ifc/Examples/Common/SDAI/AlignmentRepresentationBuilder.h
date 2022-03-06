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

#include "Base.h"
#include "Profile.h"
#include "Alignment.h"

class AlignmentBuilder
{

  SdaiModel m_model;
  SdaiAppInstance m_alignment;

    SdaiAppInstance m_alignmentHorizontal = nullptr;
    SdaiList m_segmentsHorizontal = nullptr;

    SdaiAppInstance m_alignmentVertical = nullptr;
    SdaiAppInstance m_alignmentCant = nullptr;

  bool m_generateRelNests;
  bool m_generateRepresentation;

public:

  AlignmentBuilder(SdaiModel model, SdaiAppInstance alignment, bool generateRelNests, bool generateRepresentation)
    : m_model(model)
    , m_alignment(alignment)
    , m_generateRelNests(generateRelNests)
    , m_generateRepresentation(generateRepresentation)
  {}

  SdaiAppInstance appendAlignmentHorizontal()
  {
    if (m_alignmentHorizontal == nullptr)
    {
      SdaiAppInstance relAggregates = nullptr;
      m_alignmentHorizontal = appendRelAggregates(m_model, m_alignment, "IfcAlignmentHorizontal", relAggregates);
      assignGlobalId(m_alignmentHorizontal);
      m_segmentsHorizontal = sdaiCreateAggrBN(m_alignmentHorizontal, "Segments");
    }
    return m_alignmentHorizontal;
  }

  SdaiAppInstance appendHorizontalSegmentLine(SdaiReal easting, SdaiReal northing, SdaiReal startDirection, SdaiReal segmentLength)
  {
    SdaiAppInstance inst = createHorizontalLineSegment2D(m_model,
      easting, northing, startDirection, segmentLength);

    if (m_generateRelNests)
    {

    }

    if (m_generateRepresentation)
    {

    }
  }

};

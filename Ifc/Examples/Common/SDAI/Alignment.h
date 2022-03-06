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

#include "IfcCore.h"
#include "sdai.h"

SdaiAppInstance createAlignmentSegment(SdaiModel model,

  SdaiAppInstance alignmentSegmentRef);

//
// Horizontal
//

SdaiAppInstance createHorizontalLineSegment2D(SdaiModel model,

  SdaiReal startPointX,
  SdaiReal startPointY,
  SdaiReal startDirection,
  SdaiReal segmentLength
);

SdaiAppInstance createHorizontalCircularArcSegment2D(SdaiModel model,

  SdaiReal startPointX,
  SdaiReal startPointY,
  SdaiReal startDirection,
  SdaiReal segmentLength,
  SdaiReal signedRadius
);

SdaiAppInstance createHorizontalTransitionCurveSegment2D(SdaiModel model,

  SdaiReal startPointX,
  SdaiReal startPointY,
  SdaiReal startDirection,
  SdaiReal segmentLength,
  SdaiReal signedStartRadius,
  SdaiReal signedEndRadius,
  SdaiEnum transitionCurveType
);

//
// Vertical
//

SdaiAppInstance createAlignmentVerticalSegmentLine(SdaiModel model,

  SdaiReal startDistAlong,
  SdaiReal horizontalLength,
  SdaiReal startHeight,
  SdaiReal startGradient,

  SdaiString startTag = NULL, SdaiString endTag = NULL
);

SdaiAppInstance createAlignmentVerticalSegmentCircularArc(SdaiModel model,

  SdaiReal startDistAlong,
  SdaiReal horizontalLength,
  SdaiReal startHeight,
  SdaiReal startGradient,
  SdaiReal endGradient,
  SdaiReal signedRadius,

  SdaiString startTag = NULL, SdaiString endTag = NULL
);

//
// Cant
//

SdaiAppInstance createAlignmentCantSegmentLine(SdaiModel model,

  SdaiReal startDistAlong,
  SdaiReal horizontalLength,
  SdaiReal startCantLeft,
  SdaiReal endCantLeft,
  SdaiReal startCantRight,
  SdaiReal endCantRight,

  SdaiString startTag = NULL, SdaiString endTag = NULL
);

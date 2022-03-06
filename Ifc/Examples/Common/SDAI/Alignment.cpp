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

#include "OdaCommon.h"
#include "Base.h"
#include "Alignment.h"

SdaiAppInstance createAlignmentSegment(SdaiModel model,

  SdaiAppInstance alignmentSegmentRef)
{
  SdaiAppInstance alignmentSegment = sdaiCreateInstanceBN(model, "IfcAlignmentSegment");
  assignGlobalId(alignmentSegment);
  sdaiPutAttrBN(alignmentSegment, "GeometricParameters", sdaiINSTANCE, alignmentSegmentRef);
  return alignmentSegment;
}

SdaiAppInstance createHorizontalLineSegment2D(SdaiModel model,

  SdaiReal startPointX,
  SdaiReal startPointY,
  SdaiReal startDirection,
  SdaiReal segmentLength
)
{
  SdaiAppInstance startPoint = createCartesianPoint2D(model, startPointX, startPointY);
  SdaiAppInstance horizontalSegmentLine = sdaiCreateInstanceBN(model, "IfcAlignmentHorizontalSegment");
  sdaiPutAttrsBN(horizontalSegmentLine, 6,
    "StartPoint", sdaiINSTANCE, startPoint,
    "StartDirection", sdaiREAL, startDirection,
    "StartRadiusOfCurvature", sdaiREAL, 0.,
    "EndRadiusOfCurvature", sdaiREAL, 0.,
    "SegmentLength", sdaiREAL, segmentLength,
    "PredefinedType", sdaiENUM, "LINE"
  );

  return horizontalSegmentLine;
}

SdaiAppInstance createHorizontalCircularArcSegment2D(SdaiModel model,

  SdaiReal startPointX,
  SdaiReal startPointY,
  SdaiReal startDirection,
  SdaiReal segmentLength,
  SdaiReal signedRadius
)
{
  SdaiAppInstance startPoint = createCartesianPoint2D(model, startPointX, startPointY);
  SdaiAppInstance horizontalSegmentCircularArc = sdaiCreateInstanceBN(model, "IfcAlignmentHorizontalSegment");
  sdaiPutAttrsBN(horizontalSegmentCircularArc, 6,
    "StartPoint", sdaiINSTANCE, startPoint,
    "StartDirection", sdaiREAL, startDirection,
    "StartRadiusOfCurvature", sdaiREAL, signedRadius,
    "EndRadiusOfCurvature", sdaiREAL, signedRadius,
    "SegmentLength", sdaiREAL, segmentLength,
    "PredefinedType", sdaiENUM, "CIRCULARARC"
  );

  return horizontalSegmentCircularArc;
}

SdaiAppInstance createHorizontalTransitionCurveSegment2D(SdaiModel model,

  SdaiReal startPointX,
  SdaiReal startPointY,
  SdaiReal startDirection,
  SdaiReal segmentLength,
  SdaiReal signedStartRadius,
  SdaiReal signedEndRadius,
  SdaiEnum transitionCurveType
)
{
  //bool isStartRadiusCCW = signedStartRadius < 0;
  //bool isEndRadiusCCW = signedEndRadius < 0;

  SdaiAppInstance startPoint = createCartesianPoint2D(model, startPointX, startPointY);
  SdaiAppInstance horizontalSegmentTransition = sdaiCreateInstanceBN(model, "IfcAlignmentHorizontalSegment");
  sdaiPutAttrsBN(horizontalSegmentTransition, 6,
    "StartPoint", sdaiINSTANCE, startPoint,
    "StartDirection", sdaiREAL, startDirection,
    "StartRadiusOfCurvature", sdaiREAL, signedStartRadius,
    "EndRadiusOfCurvature", sdaiREAL, signedEndRadius,
    "SegmentLength", sdaiREAL, segmentLength,
    "PredefinedType", sdaiENUM, transitionCurveType
  );

  return horizontalSegmentTransition;
}

//
// Vertical
//

SdaiAppInstance createAlignmentVerticalSegmentLine(SdaiModel model,

  SdaiReal startDistAlong,
  SdaiReal horizontalLength,
  SdaiReal startHeight,
  SdaiReal startGradient,

  SdaiString startTag /* = NULL */, SdaiString endTag /* = NULL */
)
{
  SdaiAppInstance alignmentVerticalSegment = sdaiCreateInstanceBN(model, "IfcAlignmentVerticalSegment");

  if (startTag)
    sdaiPutAttrBN(alignmentVerticalSegment, "StartTag", sdaiSTRING, startTag);
  if (endTag)
    sdaiPutAttrBN(alignmentVerticalSegment, "EndTag", sdaiSTRING, endTag);

  sdaiPutAttrsBN(alignmentVerticalSegment, 6,
    "StartDistAlong", sdaiREAL, startDistAlong,
    "HorizontalLength", sdaiREAL, horizontalLength,
    "StartHeight", sdaiREAL, startHeight,
    "StartGradient", sdaiREAL, startGradient,
    "EndGradient", sdaiREAL, startGradient,
    "PredefinedType", sdaiENUM, "CONSTANTGRADIENT"
  );

  return alignmentVerticalSegment;
}

SdaiAppInstance createAlignmentVerticalSegmentCircularArc(SdaiModel model,

  SdaiReal startDistAlong,
  SdaiReal horizontalLength,
  SdaiReal startHeight,
  SdaiReal startGradient,
  SdaiReal endGradient,
  SdaiReal signedRadius,

  SdaiString startTag /* = NULL */, SdaiString endTag /* = NULL */
)
{
  SdaiAppInstance alignmentVerticalSegment = sdaiCreateInstanceBN(model, "IfcAlignmentVerticalSegment");

  if (startTag)
    sdaiPutAttrBN(alignmentVerticalSegment, "StartTag", sdaiSTRING, startTag);
  if (endTag)
    sdaiPutAttrBN(alignmentVerticalSegment, "EndTag", sdaiSTRING, endTag);

  sdaiPutAttrsBN(alignmentVerticalSegment, 7,
    "StartDistAlong", sdaiREAL, startDistAlong,
    "HorizontalLength", sdaiREAL, horizontalLength,
    "StartHeight", sdaiREAL, startHeight,
    "StartGradient", sdaiREAL, startGradient,
    "EndGradient", sdaiREAL, endGradient,
    "RadiusOfCurvature", sdaiREAL, signedRadius,
    "PredefinedType", sdaiENUM, "CIRCULARARC"
  );

  return alignmentVerticalSegment;
}

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

  SdaiString startTag /* = NULL */, SdaiString endTag /* = NULL */
)
{
  SdaiAppInstance alignmentCantSegmentLine = sdaiCreateInstanceBN(model, "IfcAlignmentCantSegment");

  if (startTag)
    sdaiPutAttrBN(alignmentCantSegmentLine, "StartTag", sdaiSTRING, startTag);
  if (endTag)
    sdaiPutAttrBN(alignmentCantSegmentLine, "EndTag", sdaiSTRING, endTag);

  sdaiPutAttrsBN(alignmentCantSegmentLine, 5,
    "StartDistAlong", sdaiREAL, startDistAlong,
    "HorizontalLength", sdaiREAL, horizontalLength,
    "StartCantLeft", sdaiREAL, startCantLeft,
    "StartCantRight", sdaiREAL, startCantRight,
    "PredefinedType", sdaiENUM,
      (OdEqual(startCantLeft, endCantLeft) && OdEqual(startCantRight, endCantRight) ? "CONSTANTCANT" : "LINEARTRANSITION")
  );

  if (!OdEqual(startCantLeft, endCantLeft))
    sdaiPutAttrBN(alignmentCantSegmentLine, "EndCantLeft", sdaiREAL, endCantLeft);
  if (!OdEqual(startCantRight, endCantRight))
    sdaiPutAttrBN(alignmentCantSegmentLine, "EndCantRight", sdaiREAL, endCantRight);

  return alignmentCantSegmentLine;
}

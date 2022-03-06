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
#include "AlignmentGeometryBuilder.h"
#include "IfcEntity.h"

using namespace OdIfc;

//
// Clothoid
//

double EulerSpiralX(double RL, double l)
{
  //
  //	x = l - l^5 / (40 * RL^2) + l^9 / (3456 * RL^4) - l^13 / (599040 * RL^6)
  //
  double	ll_div_RL = l * l / RL,
    ll_div_RL_0 = 1.,
    ll_div_RL_2 = ll_div_RL * ll_div_RL,
    ll_div_RL_4 = ll_div_RL_2 * ll_div_RL * ll_div_RL,
    ll_div_RL_6 = ll_div_RL_4 * ll_div_RL * ll_div_RL,
    ll_div_RL_8 = ll_div_RL_6 * ll_div_RL * ll_div_RL,
    ll_div_RL_10 = ll_div_RL_8 * ll_div_RL * ll_div_RL,
    ll_div_RL_12 = ll_div_RL_10 * ll_div_RL * ll_div_RL;

  return	l * (ll_div_RL_0 / 1. -
    ll_div_RL_2 / 40. +
    ll_div_RL_4 / 3456. -
    ll_div_RL_6 / 599040. +
    ll_div_RL_8 / 175472640. -
    ll_div_RL_10 / 78033715200. +
    ll_div_RL_12 / 49049763840000.);
}

double EulerSpiralY(double RL, double l)
{
  //
  //	y = l^3 / (6 * RL) - l^7 / (336 * RL^3) + l^11 / (42240 * RL^5) - l^15 / (9676800 * RL^7)
  //
  double	ll_div_RL = l * l / RL,
    ll_div_RL_3 = ll_div_RL * ll_div_RL * ll_div_RL,
    ll_div_RL_5 = ll_div_RL_3 * ll_div_RL * ll_div_RL,
    ll_div_RL_7 = ll_div_RL_5 * ll_div_RL * ll_div_RL,
    ll_div_RL_9 = ll_div_RL_7 * ll_div_RL * ll_div_RL,
    ll_div_RL_11 = ll_div_RL_9 * ll_div_RL * ll_div_RL,
    ll_div_RL_13 = ll_div_RL_11 * ll_div_RL * ll_div_RL;

  return	l * (ll_div_RL / 6. -
    ll_div_RL_3 / 336. +
    ll_div_RL_5 / 42240. -
    ll_div_RL_7 / 9676800. +
    ll_div_RL_9 / 3530096640. -
    ll_div_RL_11 / 1880240947200. +
    ll_div_RL_13 / 1377317368627200.);
}

OdGeVector2d clothoidPosition(double clothoidConstant, double offset)
{
  double RL = clothoidConstant * clothoidConstant;

  return OdGeVector2d(EulerSpiralX(RL, offset),
    (clothoidConstant < 0.) ?
    -EulerSpiralY(RL, offset) : EulerSpiralY(RL, offset));
}

OdGeVector2d clothoidDirection(double clothoidConstant, double offset)
{
  double	RL = clothoidConstant * clothoidConstant,
    eps = 1e-5;

  OdGeVector2d pos1(
    EulerSpiralX(RL, offset - eps),
    (clothoidConstant < 0.) ? -EulerSpiralY(RL, offset - eps) : EulerSpiralY(RL, offset - eps));
  OdGeVector2d pos2(
    EulerSpiralX(RL, offset + eps),
    (clothoidConstant < 0.) ? -EulerSpiralY(RL, offset + eps) : EulerSpiralY(RL, offset + eps));

  return (pos2 - pos1).normal();
}

OdDAI::ApplicationInstancePtr OdAlignmentGeometryBuilder::processHorizontalSegment(const OdDAI::ApplicationInstance *alignmentHorizontalSegment)
{
  //
  // Get semantic values
  //
  OdDAIObjectId idStartPoint;
  alignmentHorizontalSegment->getAttr("startpoint") >> idStartPoint;
  OdDAI::ApplicationInstancePtr cp = idStartPoint.openObject();
  OdArray<double> arrStartPoint;
  cp->getAttr("coordinates") >> arrStartPoint;
  ODA_ASSERT(arrStartPoint.size() == 2);
  OdGePoint2d startPoint(arrStartPoint[0], arrStartPoint[1]);

  double startDirection;
  alignmentHorizontalSegment->getAttr("startdirection") >> startDirection;
  OdGeVector2d startDirectionVector(cos(startDirection), sin(startDirection));

  double startRadiusOfCurvature;
  alignmentHorizontalSegment->getAttr("startradiusofcurvature") >> startRadiusOfCurvature;

  double endRadiusOfCurvature;
  alignmentHorizontalSegment->getAttr("endradiusofcurvature") >> endRadiusOfCurvature;

  double segmentLength;
  alignmentHorizontalSegment->getAttr("segmentlength") >> segmentLength;

  double gravityCenterLineHeight;
  alignmentHorizontalSegment->getAttr("gravitycenterlineheight") >> gravityCenterLineHeight;

  OdAnsiString predefinedType;
  alignmentHorizontalSegment->getAttr("predefinedtype") >> predefinedType;

  //
  // Create geometry
  //
  OdDAI::ApplicationInstancePtr curveSegment = m_model->createEntityInstance("ifccurvesegment");
  OdDAIObjectId idCurveSegment = m_model->appendEntityInstance(curveSegment);
  curveSegment->putAttr("transition", (const char *)"CONTSAMEGRADIENTSAMECURVATURE");

  // Common curve segment placement is just taken from semantic part
  curveSegment->putAttr("placement", OdDAIObjectId(
    createAxis2Placement2d(startPoint, startDirectionVector)->id()
  ));

  OdDAIObjectId parentCurve;
  if (predefinedType.iCompare("LINE") == 0)
  {
    OdDAI::AttributeDataBlock adbSegmentStart;
    adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
    adbSegmentStart.value.setValue(0.);
    curveSegment->putAttr("segmentstart", &adbSegmentStart);

    OdDAI::AttributeDataBlock adbSegmentLength;
    adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
    adbSegmentLength.value.setValue(segmentLength);
    curveSegment->putAttr("segmentlength", &adbSegmentLength);

    OdDAI::ApplicationInstancePtr pnt = createCartesianPoint2d(0., 0.);
    OdDAI::ApplicationInstancePtr orientation = createDirection2d(1., 0.);
    OdDAI::ApplicationInstancePtr dir = createVector(orientation->id(), 1.);
    OdDAI::ApplicationInstancePtr line = m_model->createEntityInstance("ifcline");
    line->putAttr("pnt", OdDAIObjectId(pnt->id()));
    line->putAttr("dir", OdDAIObjectId(dir->id()));
    parentCurve = m_model->appendEntityInstance(line);
  }
  else
    if (predefinedType.iCompare("CIRCULARARC") == 0)
    {
      OdDAI::AttributeDataBlock adbSegmentStart;
      adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
      adbSegmentStart.value.setValue(0.);
      curveSegment->putAttr("segmentstart", &adbSegmentStart);

      OdDAI::AttributeDataBlock adbSegmentLength;
      adbSegmentLength.typePath.putPath("ifcparametervalue");
      adbSegmentLength.value.setValue(segmentLength / startRadiusOfCurvature);
      curveSegment->putAttr("segmentlength", &adbSegmentLength);

      OdDAI::ApplicationInstancePtr circle = m_model->createEntityInstance("ifccircle");
      OdGePoint2d center(0., startRadiusOfCurvature);
      OdGeVector2d refVector = OdGeVector2d(0., -startRadiusOfCurvature).normal();
      circle->putAttr("position", OdDAIObjectId(
        createAxis2Placement2d(center, refVector)->id()
      ));
      circle->putAttr("radius", fabs(startRadiusOfCurvature));
      parentCurve = m_model->appendEntityInstance(circle);
    }
    else
      if (predefinedType.iCompare("CLOTHOID") == 0)
      {
        double clothoidConstant = 0.;

        double offset = 0.;

        OdGePoint2d startPosition;
        OdGeVector2d startDirection;
        
#ifdef _DEBUG
        OdDAIObjectId id = alignmentHorizontalSegment->id();
        if (id.getHandle() == (OdUInt64)189)
        {
          int bp = 1;
        }
#endif

        if (OdEqual(startRadiusOfCurvature, 0.) && !OdEqual(endRadiusOfCurvature, 0.))
        {
          //
          // 1. Straight line to endRadiusOfCurvature
          //
          OdDAI::AttributeDataBlock adbSegmentStart;
          adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
          adbSegmentStart.value.setValue(0.);
          curveSegment->putAttr("segmentstart", &adbSegmentStart);

          OdDAI::AttributeDataBlock adbSegmentLength;
          adbSegmentLength.typePath.putPath("ifcparametervalue");
          adbSegmentLength.value.setValue(segmentLength);
          curveSegment->putAttr("segmentlength", &adbSegmentLength);

          clothoidConstant = (endRadiusOfCurvature < 0 ? -1. : 1.) * sqrt(segmentLength * fabs(endRadiusOfCurvature));
          
          offset = 0.;

          startDirection.set(1., 0).normalize();
          startPosition.set(0., 0.);

#ifdef _DEBUG
          // Tested
          OdGeVector2d testStartDirection = clothoidDirection(clothoidConstant, offset);
          OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
          ODA_ASSERT(startDirection == testStartDirection);
          ODA_ASSERT(startPosition == testStartPosition);
#endif
        }
        else
          if (!OdEqual(startRadiusOfCurvature, 0.) && OdEqual(endRadiusOfCurvature, 0.))
          {
            //
            // 2. startRadiusOfCurvature to straight line
            //
            OdDAI::AttributeDataBlock adbSegmentStart;
            adbSegmentStart.typePath.putPath("ifcparametervalue");
            adbSegmentStart.value.setValue(-segmentLength);
            curveSegment->putAttr("segmentstart", &adbSegmentStart);

            OdDAI::AttributeDataBlock adbSegmentLength;
            adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
            adbSegmentLength.value.setValue(segmentLength); // why segmentLength? straight line should be in 0.
            curveSegment->putAttr("segmentlength", &adbSegmentLength);

            clothoidConstant = (startRadiusOfCurvature < 0 ? 1. : -1.) * sqrt(segmentLength * fabs(startRadiusOfCurvature));
            
            offset = -segmentLength;

            startDirection = clothoidDirection(-clothoidConstant, -segmentLength);
            startPosition = clothoidPosition(clothoidConstant, segmentLength).asPoint();

#ifdef _DEBUG
            // Tested
            OdGeVector2d testStartDirection = clothoidDirection(-clothoidConstant, offset);
            OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
            ODA_ASSERT(startDirection == testStartDirection);
            ODA_ASSERT(startPosition == testStartPosition);
#endif
          }
          else if (startRadiusOfCurvature < 0. && endRadiusOfCurvature < 0.)
          {
            if (startRadiusOfCurvature < endRadiusOfCurvature)
            {
              //
              // 3. Upper left quarter, fabs(radius) to fabs(smaller_radius), opposite direction appears
              //

              //  Calculate clothoidConstant
              //      endRadius * (len + offset) = startRadius * offset
              //      startRadius * offset - endRadius * offset = endRadius * len
              //      offset = (endRadius * len) / (startRadius - endRadius)
              double  offsetLength = (endRadiusOfCurvature * segmentLength) / (startRadiusOfCurvature - endRadiusOfCurvature);
              clothoidConstant = -sqrt(fabs(endRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == -sqrt(fabs(startRadiusOfCurvature) * offsetLength));

              OdDAI::AttributeDataBlock adbSegmentLength;
              adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
              adbSegmentLength.value.setValue(segmentLength);
              curveSegment->putAttr("segmentlength", &adbSegmentLength);

              offset = offsetLength;

              startDirection = -clothoidDirection(-clothoidConstant, offsetLength);
              startPosition = clothoidPosition(clothoidConstant, -offsetLength).asPoint();

#ifdef _DEBUG
              // Tested
              OdGeVector2d testStartDirection = -clothoidDirection(-clothoidConstant, offset);
              OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
              ODA_ASSERT(startDirection == testStartDirection);
              ODA_ASSERT(startPosition == testStartPosition);
#endif
            }
            else
            {
              //
              // 4. Upper left quarter, fabs(radius) to fabs(bigger_radius)
              //

              ODA_ASSERT(startRadiusOfCurvature > endRadiusOfCurvature);
              // abs(startRadius) < abs(endRadius)

              //  Calculate clothoidConstant
              //      startRadius * (len + offset) = endRadius * offset
              //      endRadius * offset - startRadius * offset = startRadius * len
              //      offset = (startRadius * len) / (endRadius - startRadius)
              double  offsetLength = (startRadiusOfCurvature * segmentLength) / (endRadiusOfCurvature - startRadiusOfCurvature);
              clothoidConstant = std::sqrt(std::fabs(startRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(endRadiusOfCurvature) * offsetLength));

              OdDAI::AttributeDataBlock adbSegmentStart;
              adbSegmentStart.typePath.putPath("ifcparametervalue");
              adbSegmentStart.value.setValue(-(segmentLength + offsetLength));
              curveSegment->putAttr("segmentstart", &adbSegmentStart);

              OdDAI::AttributeDataBlock adbSegmentLength;
              adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
              adbSegmentLength.value.setValue(segmentLength);
              curveSegment->putAttr("segmentlength", &adbSegmentLength);

              offset = -(segmentLength + offsetLength);

              startDirection = clothoidDirection(-clothoidConstant, -(segmentLength + offsetLength));
              startPosition = clothoidPosition(clothoidConstant, segmentLength + offsetLength).asPoint();

#ifdef _DEBUG
              // Tested
              OdGeVector2d testStartDirection = clothoidDirection(-clothoidConstant, offset);
              OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
              ODA_ASSERT(startDirection == testStartDirection);
              ODA_ASSERT(startPosition == testStartPosition);
#endif
            }
          }
          else if (startRadiusOfCurvature > 0. && endRadiusOfCurvature > 0.)
          {
            if (startRadiusOfCurvature < endRadiusOfCurvature)
            {
              //  Calculate clothoidConstant
              //      startRadius * (len + offset) = endRadius * offset
              //      endRadius * offset - startRadius * offset = startRadius * len
              //      offset = (startRadius * len) / (endRadius - startRadius)
              double  offsetLength = (startRadiusOfCurvature * segmentLength) / (endRadiusOfCurvature - startRadiusOfCurvature);
              clothoidConstant = std::sqrt(std::fabs(startRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(endRadiusOfCurvature) * offsetLength));

              clothoidConstant = -clothoidConstant;

              //(*pSegmentLength) = -(*pSegmentLength);
              double signedSegmentLength = -segmentLength;

              // Start

              OdDAI::AttributeDataBlock adbSegmentLength;
              adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
              adbSegmentLength.value.setValue(segmentLength);
              curveSegment->putAttr("segmentlength", &adbSegmentLength);

              offset = -offsetLength;

              startDirection = clothoidDirection(-clothoidConstant, -offset);

              startDirection *= -1;
              //matrix._11 = -matrix._11;
              //matrix._12 = -matrix._12;
            }
            else
            {
              ODA_ASSERT(startRadiusOfCurvature > endRadiusOfCurvature);
              //  Calculate clothoidConstant
              //      endRadius * (len + offset) = startRadius * offset
              //      startRadius * offset - endRadius * offset = endRadius * len
              //      offset = (endRadius * len) / (startRadius - endRadius)
              double offsetLength = (endRadiusOfCurvature * segmentLength) / (startRadiusOfCurvature - endRadiusOfCurvature);
              clothoidConstant = std::sqrt(std::fabs(startRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(endRadiusOfCurvature) * offsetLength));

              // Not tested
              OdDAI::AttributeDataBlock adbSegmentStart;
              adbSegmentStart.typePath.putPath("ifcparametervalue");
              adbSegmentStart.value.setValue(-(segmentLength + offsetLength));
              curveSegment->putAttr("segmentstart", &adbSegmentStart);

              OdDAI::AttributeDataBlock adbSegmentLength;
              adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
              adbSegmentLength.value.setValue(segmentLength);
              curveSegment->putAttr("segmentlength", &adbSegmentLength);

              offset = -(segmentLength + offsetLength);

              startDirection = clothoidDirection(-clothoidConstant, -offset);
            }
          }
          else
          {
            ODA_ASSERT(!(startRadiusOfCurvature * endRadiusOfCurvature < 0.));
            clothoidConstant = 1.;
            //offset = 0.;
          }

        //startPosition = clothoidPosition(clothoidConstant, offset).asPoint();

        OdGeMatrix2d matrix;
        matrix.setCoordSystem(OdGePoint2d::kOrigin, startDirection, startDirection.perpVector());
        startPosition.transformBy(matrix);

        OdDAI::ApplicationInstancePtr clothoid = m_model->createEntityInstance("ifcclothoid");

        clothoid->putAttr("position", OdDAIObjectId(
          createAxis2Placement2d(startPosition, startDirection)->id()
        ));

        clothoid->putAttr("clothoidconstant", clothoidConstant);

        parentCurve = m_model->appendEntityInstance(clothoid);
      }
      else
      {
        ODA_ASSERT(0 && "Unsupported curve type");
      }

  ODA_ASSERT(parentCurve.isValid());
  curveSegment->putAttr("parentcurve", parentCurve);

  return curveSegment;
}

OdDAI::ApplicationInstancePtr OdAlignmentGeometryBuilder::processVerticalSegment(const OdDAI::ApplicationInstance *alignmentVerticalSegment)
{
  //
  // Get semantic values
  //
  double startDistAlong;
  alignmentVerticalSegment->getAttr("startdistalong") >> startDistAlong;

  double horizontalLength;
  alignmentVerticalSegment->getAttr("horizontallength") >> horizontalLength;

  double startHeight;
  alignmentVerticalSegment->getAttr("startheight") >> startHeight;

  double startGradient;
  alignmentVerticalSegment->getAttr("startgradient") >> startGradient;
  double startGradientRadians = atan(startGradient);

  double endGradient;
  alignmentVerticalSegment->getAttr("endgradient") >> endGradient;
  double endGradientRadians = atan(endGradient);

  double radiusOfCurvature;
  alignmentVerticalSegment->getAttr("radiusofcurvature") >> radiusOfCurvature;

  OdAnsiString predefinedType;
  alignmentVerticalSegment->getAttr("predefinedtype") >> predefinedType;

  OdGePoint2d startPoint(startDistAlong, startHeight);
  OdGeVector2d startDirectionVector(cos(startGradientRadians), sin(startGradientRadians));

  //
  // Create geometry
  //
  OdDAI::ApplicationInstancePtr curveSegment = m_model->createEntityInstance("ifccurvesegment");
  OdDAIObjectId idCurveSegment = m_model->appendEntityInstance(curveSegment);

  curveSegment->putAttr("transition", (const char *)"CONTSAMEGRADIENTSAMECURVATURE");

  // Common curve segment placement is just taken from semantic part
  curveSegment->putAttr("placement", OdDAIObjectId(
    createAxis2Placement2d(startPoint, startDirectionVector)->id()
  ));

  OdDAIObjectId parentCurve;
  if (predefinedType.iCompare("CONSTANTGRADIENT") == 0)
  {
    OdDAI::AttributeDataBlock adbSegmentStart;
    adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
    adbSegmentStart.value.setValue(0.);
    curveSegment->putAttr("segmentstart", &adbSegmentStart);

    OdDAI::AttributeDataBlock adbSegmentLength;
    adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
    double cosGradient = cos(startGradientRadians);
    adbSegmentLength.value.setValue(horizontalLength / cos(startGradientRadians));
    curveSegment->putAttr("segmentlength", &adbSegmentLength);

    OdDAI::ApplicationInstancePtr pnt = createCartesianPoint2d(0., 0.);
    OdDAI::ApplicationInstancePtr orientation = createDirection2d(1., 0.);
    OdDAI::ApplicationInstancePtr dir = createVector(orientation->id(), 1.);
    OdDAI::ApplicationInstancePtr line = m_model->createEntityInstance("ifcline");
    line->putAttr("pnt", OdDAIObjectId(pnt->id()));
    line->putAttr("dir", OdDAIObjectId(dir->id()));
    parentCurve = m_model->appendEntityInstance(line);
  }
  else
    if (predefinedType.iCompare("CIRCULARARC") == 0)
    {
      double rSign = startGradient > endGradient ? -1. : 1.;

      // From start point
      OdGePoint2d startPt(startDistAlong, startHeight);

      // And start gradient
      OdGeVector2d startGradientVec(cos(startGradientRadians), sin(startGradientRadians));

      // Center point can be calculated
      OdGePoint2d centerPt = startPt + rSign * radiusOfCurvature * startGradientVec.perpVector();

      // We also know end point x
      double endX = startDistAlong + horizontalLength;
      double dX = endX - centerPt.x;

      // And we know arc radius, so can calculate end point's Y
      
      // vertical_offset = sqrt(radius^2 - horizontal_offset^2)
      double dY = sqrt(radiusOfCurvature * radiusOfCurvature - dX * dX);

      // End point's Y
      double endY = centerPt.y - rSign * dY;
      OdGePoint2d endPoint(endX, endY);

      double sA = (startPoint - centerPt).angle();
      double eA = (endPoint - centerPt).angle();
      double arcPar = (eA - sA); // Parameter value 
      double arcLen = fabs(arcPar * radiusOfCurvature); // Just for check

      OdDAI::AttributeDataBlock adbSegmentStart;
      adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
      adbSegmentStart.value.setValue(0.);
      curveSegment->putAttr("segmentstart", &adbSegmentStart);

      OdDAI::AttributeDataBlock adbSegmentLength;
      adbSegmentLength.typePath.putPath("ifcparametervalue");
      adbSegmentLength.value.setValue(arcPar);
      curveSegment->putAttr("segmentlength", &adbSegmentLength);

      OdDAI::ApplicationInstancePtr circle = m_model->createEntityInstance("ifccircle");

      // Possible way as curve local placement isn't taken into account, just parameters are used:
      //#460 = IFCCARTESIANPOINT((0., 0.));
      //#461 = IFCDIRECTION((1., 0.));
      //#462 = IFCAXIS2PLACEMENT2D(#460, #461);

      OdGePoint2d center(0., rSign * radiusOfCurvature);
      OdGeVector2d refVector = OdGeVector2d(0., - rSign * radiusOfCurvature).normal();
      circle->putAttr("position", OdDAIObjectId(
        createAxis2Placement2d(center, refVector)->id()
      ));

      circle->putAttr("radius", fabs(radiusOfCurvature));
      parentCurve = m_model->appendEntityInstance(circle);
    }
  /*
    else
      if (predefinedType.iCompare("PARABOLICARC") == 0)
      {
        OdDAI::AttributeDataBlock adbSegmentStart;
        adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
        adbSegmentStart.value.setValue(0.);
        curveSegment->putAttr("segmentstart", &adbSegmentStart);

        OdDAI::AttributeDataBlock adbSegmentLength;
        adbSegmentLength.typePath.putPath("ifcparametervalue");
        adbSegmentLength.value.setValue(segmentLength / startRadiusOfCurvature);
        curveSegment->putAttr("segmentlength", &adbSegmentLength);

        OdDAI::ApplicationInstancePtr circle = m_model->createEntityInstance("ifccircle");
        OdGePoint2d center(0., startRadiusOfCurvature);
        OdGeVector2d refVector = OdGeVector2d(0., -startRadiusOfCurvature).normal();
        circle->putAttr("position", OdDAIObjectId(
          createAxis2Placement2d(center, refVector)->id()
        ));
        circle->putAttr("radius", fabs(startRadiusOfCurvature));
        parentCurve = m_model->appendEntityInstance(circle);
      }
      else
      if (predefinedType.iCompare("CLOTHOID") == 0)
      {
        double clothoidConstant = 0.;

        double offset = 0.;

        OdGePoint2d startPosition;
        OdGeVector2d startDirection;

        if (OdEqual(startRadiusOfCurvature, 0.) && !OdEqual(endRadiusOfCurvature, 0.))
        {
          //
          // 1. Straight line to endRadiusOfCurvature
          //
          OdDAI::AttributeDataBlock adbSegmentStart;
          adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
          adbSegmentStart.value.setValue(0.);
          curveSegment->putAttr("segmentstart", &adbSegmentStart);

          OdDAI::AttributeDataBlock adbSegmentLength;
          adbSegmentLength.typePath.putPath("ifcparametervalue");
          adbSegmentLength.value.setValue(segmentLength);
          curveSegment->putAttr("segmentlength", &adbSegmentLength);

          clothoidConstant = (endRadiusOfCurvature < 0 ? -1. : 1.) * sqrt(segmentLength * fabs(endRadiusOfCurvature));

          offset = 0.;

          startDirection.set(1., 0).normalize();
          startPosition.set(0., 0.);

#ifdef _DEBUG
          // Tested
          OdGeVector2d testStartDirection = clothoidDirection(clothoidConstant, offset);
          OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
          ODA_ASSERT(startDirection == testStartDirection);
          ODA_ASSERT(startPosition == testStartPosition);
#endif
        }
        else
          if (!OdEqual(startRadiusOfCurvature, 0.) && OdEqual(endRadiusOfCurvature, 0.))
          {
            //
            // 2. startRadiusOfCurvature to straight line
            //
            OdDAI::AttributeDataBlock adbSegmentStart;
            adbSegmentStart.typePath.putPath("ifcparametervalue");
            adbSegmentStart.value.setValue(-segmentLength);
            curveSegment->putAttr("segmentstart", &adbSegmentStart);

            OdDAI::AttributeDataBlock adbSegmentLength;
            adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
            adbSegmentLength.value.setValue(0.); // why segmentLength? straight line should be in 0.
            curveSegment->putAttr("segmentlength", &adbSegmentLength);

            clothoidConstant = (startRadiusOfCurvature < 0 ? 1. : -1.) * sqrt(segmentLength * fabs(startRadiusOfCurvature));

            offset = -segmentLength;

            startDirection = clothoidDirection(-clothoidConstant, -segmentLength);
            startPosition = clothoidPosition(clothoidConstant, segmentLength).asPoint();

#ifdef _DEBUG
            // Tested
            OdGeVector2d testStartDirection = clothoidDirection(-clothoidConstant, offset);
            OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
            ODA_ASSERT(startDirection == testStartDirection);
            ODA_ASSERT(startPosition == testStartPosition);
#endif
          }
          else if (startRadiusOfCurvature < 0. && endRadiusOfCurvature < 0.)
          {
            if (startRadiusOfCurvature < endRadiusOfCurvature)
            {
              //
              // 3. Upper left quarter, fabs(radius) to fabs(smaller_radius), opposite direction appears
              //

              //  Calculate clothoidConstant
              //      endRadius * (len + offset) = startRadius * offset
              //      startRadius * offset - endRadius * offset = endRadius * len
              //      offset = (endRadius * len) / (startRadius - endRadius)
              double  offsetLength = (endRadiusOfCurvature * segmentLength) / (startRadiusOfCurvature - endRadiusOfCurvature);
              clothoidConstant = -sqrt(fabs(endRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == -sqrt(fabs(startRadiusOfCurvature) * offsetLength));

              offset = offsetLength;

              startDirection = -clothoidDirection(-clothoidConstant, offsetLength);
              startPosition = clothoidPosition(clothoidConstant, -offsetLength).asPoint();

#ifdef _DEBUG
              // Tested
              OdGeVector2d testStartDirection = -clothoidDirection(-clothoidConstant, offset);
              OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
              ODA_ASSERT(startDirection == testStartDirection);
              ODA_ASSERT(startPosition == testStartPosition);
#endif
            }
            else
            {
              //
              // 4. Upper left quarter, fabs(radius) to fabs(bigger_radius)
              //

              ODA_ASSERT(startRadiusOfCurvature > endRadiusOfCurvature);
              //  Calculate clothoidConstant
              //      startRadius * (len + offset) = endRadius * offset
              //      endRadius * offset - startRadius * offset = startRadius * len
              //      offset = (startRadius * len) / (endRadius - startRadius)
              double  offsetLength = (startRadiusOfCurvature * segmentLength) / (endRadiusOfCurvature - startRadiusOfCurvature);
              clothoidConstant = std::sqrt(std::fabs(startRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(endRadiusOfCurvature) * offsetLength));

              OdDAI::AttributeDataBlock adbSegmentStart;
              adbSegmentStart.typePath.putPath("ifcparametervalue");
              adbSegmentStart.value.setValue(segmentLength + offsetLength);
              curveSegment->putAttr("segmentstart", &adbSegmentStart);

              OdDAI::AttributeDataBlock adbSegmentLength;
              adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
              adbSegmentLength.value.setValue(segmentLength);
              curveSegment->putAttr("segmentlength", &adbSegmentLength);

              offset = -(segmentLength + offsetLength);

              startDirection = clothoidDirection(-clothoidConstant, -(segmentLength + offsetLength));
              startPosition = clothoidPosition(clothoidConstant, segmentLength + offsetLength).asPoint();

#ifdef _DEBUG
              // Tested
              OdGeVector2d testStartDirection = clothoidDirection(-clothoidConstant, offset);
              OdGePoint2d testStartPosition = clothoidPosition(clothoidConstant, -offset).asPoint();
              ODA_ASSERT(startDirection == testStartDirection);
              ODA_ASSERT(startPosition == testStartPosition);
#endif
            }
          }
          else if (startRadiusOfCurvature > 0. && endRadiusOfCurvature > 0.)
          {
            if (startRadiusOfCurvature < endRadiusOfCurvature)
            {
              //  Calculate clothoidConstant
              //      startRadius * (len + offset) = endRadius * offset
              //      endRadius * offset - startRadius * offset = startRadius * len
              //      offset = (startRadius * len) / (endRadius - startRadius)
              double  offsetLength = (startRadiusOfCurvature * segmentLength) / (endRadiusOfCurvature - startRadiusOfCurvature);
              clothoidConstant = std::sqrt(std::fabs(startRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(endRadiusOfCurvature) * offsetLength));

              clothoidConstant = -clothoidConstant;

              //(*pSegmentLength) = -(*pSegmentLength);
              double signedSegmentLength = -segmentLength;

              offset = -offsetLength;

              startDirection = clothoidDirection(-clothoidConstant, -offset);

              startDirection *= -1;
              //matrix._11 = -matrix._11;
              //matrix._12 = -matrix._12;
            }
            else
            {
              ODA_ASSERT(startRadiusOfCurvature > endRadiusOfCurvature);
              //  Calculate clothoidConstant
              //      endRadius * (len + offset) = startRadius * offset
              //      startRadius * offset - endRadius * offset = endRadius * len
              //      offset = (endRadius * len) / (startRadius - endRadius)
              double offsetLength = (endRadiusOfCurvature * segmentLength) / (startRadiusOfCurvature - endRadiusOfCurvature);
              clothoidConstant = std::sqrt(std::fabs(endRadiusOfCurvature) * (segmentLength + offsetLength));
              ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(startRadiusOfCurvature) * offsetLength));

              offset = -(segmentLength + offsetLength);

              startDirection = clothoidDirection(-clothoidConstant, -offset);
            }
          }
          else
          {
            ODA_ASSERT(!(startRadiusOfCurvature * endRadiusOfCurvature < 0.));
            clothoidConstant = 1.;
            //offset = 0.;
          }

        //startPosition = clothoidPosition(clothoidConstant, offset).asPoint();

        OdGeMatrix2d matrix;
        matrix.setCoordSystem(OdGePoint2d::kOrigin, startDirection, startDirection.perpVector());
        startPosition.transformBy(matrix);

        OdDAI::ApplicationInstancePtr clothoid = m_model->createEntityInstance("ifcclothoid");

        clothoid->putAttr("position", OdDAIObjectId(
          createAxis2Placement2d(startPosition, startDirection)->id()
        ));

        clothoid->putAttr("clothoidconstant", clothoidConstant);

        parentCurve = m_model->appendEntityInstance(clothoid);
      }*/
      else
      {
        ODA_ASSERT(0 && "Unsupported curve type");
      }

  ODA_ASSERT(parentCurve.isValid());
  curveSegment->putAttr("parentcurve", parentCurve);
  return curveSegment;
}

OdDAI::ApplicationInstancePtr OdAlignmentGeometryBuilder::processCantSegment(const OdDAI::ApplicationInstance *alignmentCantSegment, double railHeadDistance, bool last)
{
  if (OdLessOrEqual(railHeadDistance, 0.))
  {
    ODA_ASSERT(0);
    railHeadDistance = 1.;
  }

  //
  // Get semantic values
  //
  double startDistAlong;
  alignmentCantSegment->getAttr("startdistalong") >> startDistAlong;

  double horizontalLength;
  alignmentCantSegment->getAttr("horizontallength") >> horizontalLength;

  double startCantLeft;
  alignmentCantSegment->getAttr("startcantleft") >> startCantLeft;

  double endCantLeft;
  alignmentCantSegment->getAttr("endcantleft") >> endCantLeft;

  double startCantRight;
  alignmentCantSegment->getAttr("startcantright") >> startCantRight;

  double endCantRight;
  alignmentCantSegment->getAttr("endcantright") >> endCantRight;

  double smoothingLength;
  alignmentCantSegment->getAttr("smoothinglength") >> smoothingLength;

  OdAnsiString predefinedType;
  alignmentCantSegment->getAttr("predefinedtype") >> predefinedType;
  
  //
  // Create placement with inclination according to sematic view data
  //
  double halfCant = (startCantLeft + startCantRight) * 0.5;
  OdGePoint3d startPoint(startDistAlong, halfCant, 0);

  OdGeVector3d startDirectionX(horizontalLength, (endCantLeft + endCantRight) * 0.5 - (startCantLeft + startCantRight) * 0.5, 0.);
  startDirectionX.normalize();

  OdGeVector3d startDirectionY(-startDirectionX.y, startDirectionX.x, 0.);
  
  double f = -(startCantLeft - startCantRight);
  OdGeVector3d axis(-f * startDirectionX.y, f * startDirectionX.x, railHeadDistance);
  axis.normalize();

  startDirectionY = axis.crossProduct(startDirectionX);

  //
  // Create geometry
  //
  OdDAI::ApplicationInstancePtr curveSegment = m_model->createEntityInstance("ifccurvesegment");
  OdDAIObjectId idCurveSegment = m_model->appendEntityInstance(curveSegment);

  curveSegment->putAttr("transition", last ?
    (const char *)"DISCONTINUOUS" : (const char *)"CONTSAMEGRADIENTSAMECURVATURE");

  curveSegment->putAttr("placement", OdDAIObjectId(
    createAxis2Placement3d(startPoint, &axis, &startDirectionX)->id()
  ));

  OdDAIObjectId parentCurve;

  if (predefinedType.iCompare("CONSTANTCANT") == 0)
  {
    OdDAI::AttributeDataBlock adbSegmentStart;
    adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
    adbSegmentStart.value.setValue(0.);
    curveSegment->putAttr("segmentstart", &adbSegmentStart);

    OdDAI::AttributeDataBlock adbSegmentLength;
    adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
    adbSegmentLength.value.setValue(horizontalLength);
    curveSegment->putAttr("segmentlength", &adbSegmentLength);

    OdDAI::ApplicationInstancePtr pnt = createCartesianPoint2d(0., 0.);
    OdDAI::ApplicationInstancePtr orientation = createDirection2d(1., 0.);
    OdDAI::ApplicationInstancePtr dir = createVector(orientation->id(), 1.);

    OdDAI::ApplicationInstancePtr line = m_model->createEntityInstance("ifcline");
    line->putAttr("pnt", OdDAIObjectId(pnt->id()));
    line->putAttr("dir", OdDAIObjectId(dir->id()));
    parentCurve = m_model->appendEntityInstance(line);
  }
  else
    if (predefinedType.iCompare("LINEARTRANSITION") == 0)
    {
      OdDAI::AttributeDataBlock adbSegmentStart;
      adbSegmentStart.typePath.putPath("ifcnonnegativelengthmeasure");
      adbSegmentStart.value.setValue(0.);
      curveSegment->putAttr("segmentstart", &adbSegmentStart);

      OdDAI::AttributeDataBlock adbSegmentLength;
      adbSegmentLength.typePath.putPath("ifcnonnegativelengthmeasure");
      adbSegmentLength.value.setValue(horizontalLength);
      curveSegment->putAttr("segmentlength", &adbSegmentLength);

      OdDAI::ApplicationInstancePtr pnt = createCartesianPoint2d(0., 0.);
      OdDAI::ApplicationInstancePtr orientation = createDirection2d(1., 0.);
      OdDAI::ApplicationInstancePtr dir = createVector(orientation->id(), 1.);

      OdDAI::ApplicationInstancePtr line = m_model->createEntityInstance("ifcline");
      line->putAttr("pnt", OdDAIObjectId(pnt->id()));
      line->putAttr("dir", OdDAIObjectId(dir->id()));
      parentCurve = m_model->appendEntityInstance(line);
    }
    // BIQUADRATICPARABOLA
    // NOTE
    // BLOSSCURVE
    // COSINECURVE
    // SINECURVE
    // VIENNESEBEND
    else
    {
      ODA_ASSERT(0 && "Unsupported curve type");
    }

  ODA_ASSERT(parentCurve.isValid());
  curveSegment->putAttr("parentcurve", parentCurve);
  return curveSegment;
}

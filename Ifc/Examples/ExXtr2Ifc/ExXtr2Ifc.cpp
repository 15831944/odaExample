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
#include "StaticRxObject.h"
#include "RxDynamicModule.h"
#include "OdPerfTimer.h"
#include "ExPrintConsole.h"

#include <fstream>
#include <iostream>
#include <cstdlib>

#include "IfcExamplesCommon.h"
#include "AlignmentRepresentationBuilder.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  using namespace OdIfc;                                                             \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4x3_RC4Module);                        \
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4x3RC4ModuleName, OdIfc4x3_RC4Module)          \
  ODRX_END_STATIC_MODULE_MAP()
#endif

//
// XTR Definitions
//

enum class XtrType {

  unknown = 0,

  // Horizontal
  D = 1, // Straight
  C = 2, // Arc
  R = 3, // Transition

  // Vertical
  d = 4, // Straight
  c = 5, // Arc

  // Cant
  Q = 6,

  // Not used
  N
};

XtrType xtr2Type(char c)
{
  switch (c)
  {
    case 'D': return XtrType::D;
    case 'C': return XtrType::C;
    case 'R': return XtrType::R;
    case 'd': return XtrType::d;
    case 'c': return XtrType::c;
    case 'Q': return XtrType::Q;
    case 'N': return XtrType::N;
  }
  return XtrType::unknown;
}

struct XtrHorizontalSegment {
  XtrType type; // D = straight, C = arc, R = transition (clothoid)
  double easting; // StartPoint.x
  double northing; // StartPoint.y
  double azimuth; // Gradians (Gon), conversion to angles of StartDirection needed
  double length; // SegmentLength
  double startRadius; // for arcs and transition curves
  double endRadius; // equals to startRadius in Arc case
};
typedef OdArray<XtrHorizontalSegment> XtrHorizontalSegmentArray;

struct XtrVerticalSegment {
  XtrType type; // d = straight line, c = arc
  double startDistAlong; // Metraege: Cumulation of length in meter from beginning of the alignment to the start point of this segment.It is measured along horizontal alignment.
  double horizontalLength; // Element Length : Projected horizontal length in meter.
  double gradient; // Gradient in ‰(per mill) at the beginning of the element.
  double startRadius; // Vertical Radius.If the segment is a straight line, then Radius is 0. If the segment is a arc, then the Radius is the start radius and end radius.
  double startHeight; // Height at the beginning of the segment in meter.
};
typedef OdArray<XtrVerticalSegment> XtrVerticalSegmentArray;

struct XtrCantSegment
{
  XtrType type; // Q = straight assumed only
  double startDistAlong; // m
  double horizontalLength; // m
  double startCant; // mm, height of left rail minus right rail
  double endCant; // mm, height of left rail minus right rail
  double speed;
};
typedef OdArray<XtrCantSegment> XtrCantSegmentArray;

class XtrData
{
public:

  XtrHorizontalSegmentArray horSegs;
  XtrVerticalSegmentArray vertSegs;
  XtrCantSegmentArray cantSegs;

protected:

  OdResult readHorizontalSegment(const char *in, XtrType type)
  {
    if (type != XtrType::D && type != XtrType::C && type != XtrType::R)
      return eWrongObjectType;

    XtrHorizontalSegment seg;
    seg.type = type;

    OdResult res = eOk;

    char *cursor = strtok(NULL, "\t");
    if (cursor) seg.easting = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.northing = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.azimuth = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.length = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.startRadius = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.endRadius = atof(cursor); else res = eSyntaxError;

    horSegs.append(seg);

    return res;
  }

  OdResult readVerticalSegment(const char *in, XtrType type)
  {
    if (type != XtrType::d && type != XtrType::c)
      return eWrongObjectType;

    XtrVerticalSegment seg;
    seg.type = type;

    OdResult res = eOk;

    char *cursor = strtok(NULL, "\t");
    if (cursor) seg.startDistAlong = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.horizontalLength = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.gradient = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.startRadius = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.startHeight = atof(cursor); else res = eSyntaxError;

    vertSegs.append(seg);

    return res;
  }

  OdResult readCantSegment(const char *in, XtrType type)
  {
    if (type != XtrType::Q)
      return eWrongObjectType;

    XtrCantSegment seg;
    seg.type = type;

    OdResult res = eOk;

    char *cursor = strtok(NULL, "\t");
    if (cursor) seg.startDistAlong = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.horizontalLength = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.startCant = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.endCant = atof(cursor); else res = eSyntaxError;

    cursor = strtok(NULL, "\t");
    if (cursor) seg.speed = atof(cursor); else res = eSyntaxError;

    cantSegs.append(seg);

    return res;
  }


  OdResult readLine(const char *in)
  {
    if (odStrLenA(in) <= 1)
      return eOk;

    char *cursor = strtok(const_cast<char*>(in), "\t");
    if (cursor == NULL || cursor[0] == '@')
      return eOk;

    XtrType type = xtr2Type(cursor[0]);
    switch (type)
    {
    case XtrType::N:
      return eOk; // Skip

      // Horizontal
    case XtrType::D:
    case XtrType::C:
    case XtrType::R:
      return readHorizontalSegment(cursor, type);

    // Vertical
    case XtrType::d:
    case XtrType::c:
      return readVerticalSegment(cursor, type);

    // Cant
    case XtrType::Q:
      return readCantSegment(cursor, type);

    default:
      ODA_ASSERT_ONCE(0 && "XTR Token we haven't seen before!");
    }

    return eSyntaxError;
  }

public:

  OdResult readFile(const OdString &fileName)
  {
    OdResult res = eOk;

    const size_t lineSize = 1024 * 2;
    char line[lineSize] = "";
    int nLine = 0;
    std::ifstream xtrFile(OdAnsiString(fileName).c_str());
    while (xtrFile.getline(line, lineSize))
    {
      ++nLine;

      odPrintConsoleString(L"\n%d: %hs (len: %d)", nLine, line, odStrLenA(line));

      OdResult resLine = readLine(line);
      if (resLine != eOk)
      {
        odPrintConsoleString(L"\nError '%s' when reading line #%d",
          OdError(resLine).description().c_str(), nLine);
        res = resLine;
      }
    }

    return res;
  }
};

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


//
// Representation routines
//

static SdaiString typePathNonNegativeLengthMeasure[] = { "IfcNonNegativeLengthMeasure" };
static SdaiString typePathParameterValue[] = { "IfcParameterValue" };

SdaiAppInstance createIfcLine(SdaiModel model, const SdaiReal seg_length, SdaiADB &adbSegmentStart, SdaiReal &signedSegmentLength, SdaiAppInstance orientation = NULL)
{
  SdaiAppInstance line = sdaiCreateInstanceBN(model, "IfcLine");

  sdaiPutADBTypePath(adbSegmentStart, 1, typePathNonNegativeLengthMeasure);
  sdaiPutADBValue(adbSegmentStart, sdaiREAL, 0.);

  signedSegmentLength = seg_length;

  SdaiAppInstance pnt = createCartesianPoint2D(model, 0., 0.);
  if (orientation == NULL)
    orientation = createDirection2D(model, 1., 0.);
  sdaiPutAttrBN(line, "Pnt", sdaiINSTANCE, pnt);

  SdaiAppInstance dir = createVector(model, orientation, 1.);
  sdaiPutAttrBN(line, "Dir", sdaiINSTANCE, dir);

  return line;
}

SdaiAppInstance createIfcLineGradient(SdaiModel model, const SdaiReal seg_length, SdaiADB &adbSegmentStart, SdaiReal &signedSegmentLength, SdaiReal cosGradient, SdaiReal sinGradient)
{
  SdaiAppInstance line = sdaiCreateInstanceBN(model, "IfcLine");

  sdaiPutADBTypePath(adbSegmentStart, 1, typePathNonNegativeLengthMeasure);
  sdaiPutADBValue(adbSegmentStart, sdaiREAL, 0.);

  signedSegmentLength = seg_length;

  SdaiAppInstance pnt = createCartesianPoint2D(model, 0., 0.);
  SdaiAppInstance orientation = createDirection2D(model, cosGradient, sinGradient);
  sdaiPutAttrBN(line, "Pnt", sdaiINSTANCE, pnt);

  SdaiAppInstance dir = createVector(model, orientation, 1.);
  sdaiPutAttrBN(line, "Dir", sdaiINSTANCE, dir);

  return line;
}

SdaiAppInstance createIfcCircle(SdaiModel model, SdaiReal radius, SdaiReal seg_length, SdaiADB &adbSegmentStart, SdaiReal &signedParameterValue)
{
  SdaiAppInstance circle = sdaiCreateInstanceBN(model, "IfcCircle");

  //sdaiPutADBTypePath(adbSegmentStart, 1, typePathNonNegativeLengthMeasure);
  sdaiPutADBTypePath(adbSegmentStart, 1, typePathParameterValue);
  sdaiPutADBValue(adbSegmentStart, sdaiREAL, 0.);

  //SdaiReal signedLength = radius > -0. ? seg_length : -seg_length; // Signed length isn't convenient
  signedParameterValue = seg_length / radius; // angle in radians is parameter for curve
  //signedParameterValue = signedParameterValue * 180 / OdaPI; // or in degrees

  OdGePoint2d center(0., radius);
  OdGeVector2d refVector = OdGeVector2d(0., -radius).normal();

  SdaiAppInstance location = createCartesianPoint2D(model, center.x, center.y);
  SdaiAppInstance refDirection = createDirection2D(model, refVector.x, refVector.y);
  SdaiAppInstance placement = createAxis2Placement2D(model, location, refDirection);

  sdaiPutAttrBN(circle, "Position", sdaiINSTANCE, placement);
  sdaiPutAttrBN(circle, "Radius", sdaiREAL, fabs(radius));

  return circle;
}

SdaiAppInstance createIfcCircleGradient(SdaiModel model, SdaiReal radius, SdaiReal seg_length, SdaiADB &adbSegmentStart, SdaiReal &signedSegmentLength, SdaiReal gradientRad)
{
  SdaiAppInstance circle = sdaiCreateInstanceBN(model, "IfcCircle");

  sdaiPutADBTypePath(adbSegmentStart, 1, typePathNonNegativeLengthMeasure);
  sdaiPutADBValue(adbSegmentStart, sdaiREAL, 0.);

  OdGeVector2d dirGradient(cos(gradientRad), sin(gradientRad));
  OdGeVector2d perpGradient = dirGradient.perpVector();
  OdGePoint2d center = OdGePoint2d(0, 0) + perpGradient * radius;
  OdGeVector2d refVector = -(perpGradient*radius).normal();

  signedSegmentLength = radius > -0. ? seg_length : -seg_length;

  SdaiAppInstance location = createCartesianPoint2D(model, center.x, center.y);
  SdaiAppInstance refDirection = createDirection2D(model, refVector.x, refVector.y);
  SdaiAppInstance placement = createAxis2Placement2D(model, location, refDirection);

  sdaiPutAttrBN(circle, "Position", sdaiINSTANCE, placement);
  sdaiPutAttrBN(circle, "Radius", sdaiREAL, fabs(radius));

  return circle;
}

SdaiAppInstance createIfcClothoid(SdaiModel model, SdaiReal seg_startRadius, SdaiReal seg_endRadius, SdaiReal seg_length, SdaiADB &adbSegmentStart, SdaiReal &signedSegmentLength)
{
  SdaiAppInstance clothoid = sdaiCreateInstanceBN(model, "IfcClothoid");

  signedSegmentLength = seg_length;

  bool takeStart = fabs(seg_startRadius) > fabs(seg_endRadius);
  SdaiReal sign = takeStart ? OdSign(seg_startRadius) : OdSign(seg_endRadius);
  SdaiReal startRadius = fabs(seg_startRadius);
  SdaiReal endRadius = fabs(seg_endRadius);
  SdaiReal radius = odmax(startRadius, endRadius);
  SdaiReal clothoidConstant = sign * sqrt(radius * seg_length);

  //////////////////////////////////////////////////////////

  OdGeVector2d position(0., 0.);
  OdGeVector2d direction(1., 0.);
  double offset = 0.;

  if (OdZero(seg_startRadius))
  {
    ODA_ASSERT(!OdZero(seg_endRadius));
    clothoidConstant = std::sqrt(std::fabs(seg_endRadius) * seg_length);
    if (seg_endRadius < 0) { clothoidConstant = -clothoidConstant; }

    offset = 0.;
  }
  else
    if (OdZero(seg_endRadius))
    {
      clothoidConstant = std::sqrt(std::fabs(seg_startRadius) * seg_length);
      if (seg_startRadius > 0) { clothoidConstant = -clothoidConstant; }

      offset = -seg_length;

      direction = clothoidDirection(-clothoidConstant, -offset);
    }
    else if (seg_startRadius < 0. && seg_endRadius < 0.)
    {
      if (seg_startRadius < seg_endRadius)
      {
        //  Calculate clothoidConstant
        //      endRadius * (len + offset) = startRadius * offset
        //      startRadius * offset - endRadius * offset = endRadius * len
        //      offset = (endRadius * len) / (startRadius - endRadius)
        double  offsetLength = (seg_endRadius * seg_length) / (seg_startRadius - seg_endRadius);
        clothoidConstant = std::sqrt(std::fabs(seg_endRadius) * (seg_length + offsetLength));
        ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(seg_startRadius) * offsetLength));

        clothoidConstant = -clothoidConstant;

        //(*pSegmentLength) = -(*pSegmentLength);
        signedSegmentLength = -seg_length;

        offset = -offsetLength;

        direction = clothoidDirection(-clothoidConstant, -offset);

        direction *= -1.;
        //matrix._11 = -matrix._11;
        //matrix._12 = -matrix._12;
      }
      else {
        ODA_ASSERT(seg_startRadius > seg_endRadius);
        //  Calculate clothoidConstant
        //      startRadius * (len + offset) = endRadius * offset
        //      endRadius * offset - startRadius * offset = startRadius * len
        //      offset = (startRadius * len) / (endRadius - startRadius)
        double  offsetLength = (seg_startRadius * seg_length) / (seg_endRadius - seg_startRadius);
        clothoidConstant = std::sqrt(std::fabs(seg_startRadius) * (seg_length + offsetLength));
        ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(seg_endRadius) * offsetLength));

        offset = -(seg_length + offsetLength);

        direction = clothoidDirection(-clothoidConstant, -offset);
      }
    }
    else if (seg_startRadius > 0. && seg_endRadius > 0.)
    {
      if (seg_startRadius < seg_endRadius) {
        //  Calculate clothoidConstant
        //      startRadius * (len + offset) = endRadius * offset
        //      endRadius * offset - startRadius * offset = startRadius * len
        //      offset = (startRadius * len) / (endRadius - startRadius)
        double  offsetLength = (seg_startRadius * seg_length) / (seg_endRadius - seg_startRadius);
        clothoidConstant = std::sqrt(std::fabs(seg_startRadius) * (seg_length + offsetLength));
        ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(seg_endRadius) * offsetLength));

        clothoidConstant = -clothoidConstant;

        //(*pSegmentLength) = -(*pSegmentLength);
        signedSegmentLength = -seg_length;

        offset = -offsetLength;

        direction = clothoidDirection(-clothoidConstant, -offset);

        direction *= -1;
        //matrix._11 = -matrix._11;
        //matrix._12 = -matrix._12;
      }
      else
      {
        ODA_ASSERT(seg_startRadius > seg_endRadius);
        //  Calculate clothoidConstant
        //      endRadius * (len + offset) = startRadius * offset
        //      startRadius * offset - endRadius * offset = endRadius * len
        //      offset = (endRadius * len) / (startRadius - endRadius)
        double offsetLength = (seg_endRadius * seg_length) / (seg_startRadius - seg_endRadius);
        clothoidConstant = std::sqrt(std::fabs(seg_endRadius) * (seg_length + offsetLength));
        ODA_ASSERT(clothoidConstant == std::sqrt(std::fabs(seg_startRadius) * offsetLength));

        offset = -(seg_length + offsetLength);

        direction = clothoidDirection(-clothoidConstant, -offset);
      }
    }
    else
    {
      ODA_ASSERT(0);
      clothoidConstant = 1.;
      offset = 0.;
    }

  //////////////////////////////////////////////////////////

  sdaiPutADBTypePath(adbSegmentStart, 1, typePathParameterValue);
  if (!OdZero(offset))
  {
    sdaiPutADBValue(adbSegmentStart, sdaiREAL, offset);
    position = clothoidPosition(clothoidConstant, -offset);

    OdGeMatrix2d matrix;
    matrix.setCoordSystem(OdGePoint2d::kOrigin, direction, direction.perpVector());
    position.transformBy(matrix);
  }
  else
  {
    sdaiPutADBValue(adbSegmentStart, sdaiREAL, 0.);
  }

  SdaiAppInstance location = createCartesianPoint2D(model, position.x, position.y);
  SdaiAppInstance refDirection = createDirection2D(model, direction.x, direction.y);
  SdaiAppInstance placement = createAxis2Placement2D(model, location, refDirection);

  sdaiPutAttrBN(clothoid, "Position", sdaiINSTANCE, placement);
  sdaiPutAttrBN(clothoid, "ClothoidConstant", sdaiREAL, clothoidConstant);

  return clothoid;
}

//
// Main
//

#include "Ge/GeMatrix2d.h"
#include "Ge/GeCircArc2d.h"

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int nRes = 0; // Return value for main

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExXtr2Ifc (XTR file conversion using SDAI) developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc != 3);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: ExXtr2Ifc <XTR filename> <IFC filename>");
    odPrintConsoleString(L"\n<XTR filename> - input XTR file\n");
    odPrintConsoleString(L"\n<IFC filename> - output IFC4X3_RC4 file\n");
    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);

  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize ODA IFC SDK                                             */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  try
  {
    OdString xtrFileName(argv[1]);
    if (!svcs.accessFile(xtrFileName, Oda::kFileRead))
    {
      OdString msg;
      msg.format(L"\nError: Input file '%s' not found.\n", xtrFileName.c_str());
      odPrintConsoleString(msg);
      return 1;
    }

    odPrintConsoleString(L"\nLoading file '%s'.\n", xtrFileName.c_str());

    XtrData xtrData;
    OdResult res = xtrData.readFile(xtrFileName);
    if (res != eOk)
    {
      odPrintConsoleString(L"\n'%s' when reading file '%s'.\n",
        OdError(res).description().c_str(), xtrFileName.c_str());
      return 1;
    }

    SdaiSession session = sdaiOpenSession();
    SdaiRep repo = _sdaiCreateRepository(session, "Xtr2Ifc");

    SdaiSchema schemaIfc4x3 = sdaiGetSchema("IFC4X3_RC4");
    SdaiModel emptyModel = sdaiCreateModel(repo, "Xtr2Ifc_Model", schemaIfc4x3);
    SdaiModel model = sdaiAccessModel(emptyModel, sdaiRW);

    double toM = 1. / 1000.;

    //
    // Footer creation (IfcProject + IfcSite)
    //
    SdaiAppInstance organization = sdaiCreateInstanceBN(model, "IfcOrganization");
    sdaiPutAttrsBN(organization, 2,
      "Name", sdaiSTRING, "Open Design Alliance",
      "Description", sdaiSTRING, "IFC SDK Development"
    );

    SdaiAppInstance person = sdaiCreateInstanceBN(model, "IfcPerson");
    sdaiPutAttrBN(person, "Identification", sdaiSTRING, "ExXtr2Ifc example application");

    SdaiAppInstance personAndOrganization = sdaiCreateInstanceBN(model, "IfcPersonAndOrganization");
    sdaiPutAttrsBN(personAndOrganization, 2,
      "TheOrganization", sdaiINSTANCE, organization,
      "ThePerson", sdaiINSTANCE, person
    );

    SdaiAppInstance application = sdaiCreateInstanceBN(model, "IfcApplication");
    sdaiPutAttrsBN(application, 4,
      "ApplicationDeveloper", sdaiINSTANCE, organization,
      "Version", sdaiSTRING, TD_SHORT_STRING_VER_S,
      "ApplicationFullName", sdaiSTRING, "Example of XTR conversion to IFC using SDAI",
      "ApplicationIdentifier", sdaiSTRING, "ExXtr2Ifc"
    );

    SdaiAppInstance ownerHistory = sdaiCreateInstanceBN(model, "IfcOwnerHistory");
    sdaiPutAttrsBN(ownerHistory, 5,
      "OwningUser", sdaiINSTANCE, personAndOrganization,
      "OwningApplication", sdaiINSTANCE, application,
      "State", sdaiENUM, "READWRITE",
      "ChangeAction", sdaiENUM, "NOTDEFINED",
      "CreationDate", sdaiINTEGER, 0
    );

    SdaiAppInstance nullPt2D = createCartesianPoint2D(model, 0., 0.);
    SdaiAppInstance nullPt3D = createCartesianPoint3D(model, 0., 0., 0.);
    SdaiAppInstance dirZ = createDirection3D(model, 0., 0., 1.);

    SdaiAppInstance origin2D = createAxis2Placement2D(model, nullPt2D);
    SdaiAppInstance context2D = createGeometricRepresentationContext(model, "2D", "Plan", 2, 1e-6, origin2D);

    SdaiAppInstance origin3D = createAxis2Placement3D(model, nullPt3D);
    SdaiAppInstance context3D = createGeometricRepresentationContext(model, "3D", "Model", 3, 1e-6, origin3D);

    SdaiAppInstance unitAssignment = appendUnitAssignment(model);

    OdAnsiString strFilenameFrom(xtrFileName, CP_UTF_8);
    SdaiAppInstance project = sdaiCreateInstanceBN(model, "IfcProject");
    assignGlobalId(project);
    sdaiPutAttrsBN(project, 4,
      "OwnerHistory", sdaiINSTANCE, ownerHistory,
      "Name", sdaiSTRING, "ExXtr2Ifc",
      "Description", sdaiSTRING, strFilenameFrom.c_str(),
      "UnitsInContext", sdaiINSTANCE, unitAssignment
    );
    SdaiSet representationContexts = sdaiCreateAggrBN(project, "RepresentationContexts");
    sdaiAdd(representationContexts, sdaiINSTANCE, context2D);
    sdaiAdd(representationContexts, sdaiINSTANCE, context3D);

    SdaiAppInstance relAggregates = nullptr;

    //
    // Spatial structure (IfcProject <- IfcSite <- IfcRailway <- IfcAlignment)
    //
    relAggregates = nullptr;
    SdaiAppInstance site = appendRelAggregates(model, project, "IfcSite", relAggregates);
    assignGlobalId(site);
    sdaiPutAttrBN(site, "Name", sdaiSTRING, "Railway_Site");

    relAggregates = nullptr;
    SdaiAppInstance railway = appendRelAggregates(model, site, "IfcRailway", relAggregates);
    assignGlobalId(railway);
    sdaiPutAttrBN(railway, "Name", sdaiSTRING, "Railway");



    SdaiAppInstance axis2Placement3d = sdaiCreateInstanceBN(model, "IfcAxis2Placement3D");
    sdaiPutAttrBN(axis2Placement3d, "Location", sdaiINSTANCE, nullPt3D);

    SdaiAppInstance objectPlacement = sdaiCreateInstanceBN(model, "IfcLocalPlacement");
    sdaiPutAttrBN(objectPlacement, "RelativePlacement", sdaiINSTANCE, axis2Placement3d);

    SdaiAppInstance alignment = appendRelContainedInSpatialStructure(model, railway, "IfcAlignment");
    assignGlobalId(alignment);
    sdaiPutAttrsBN(alignment, 3,
      "Name", sdaiSTRING, "Primary Alignment",
      // "Axis", sdaiINSTANCE, ???,
      "ObjectPlacement", sdaiINSTANCE, objectPlacement,
      "PredefinedType", sdaiENUM, "NOTDEFINED"
    );

    bool generateRepresentations = true; // Change to 'false' for semantic view only

    // Q: Should gradient curve be here or this is for IfcSegmentedReferenceCurve?
    /*SdaiAppInstance segmentedReferenceCurve = nullptr;
    SdaiList gradientSegments = nullptr;
    if (generateRepresentations)
    {
      segmentedReferenceCurve = createShapeRepresentation(model, alignment, context3D, "Axis", "IfcSegmentedReferenceCurve");
      gradientSegments = sdaiCreateAggrBN(segmentedReferenceCurve, "Segments");
    }*/

    //
    // Semantic view
    //

    SdaiAppInstance alignmentNests = nullptr;

      //
      // Horizontal Alignment, in meters
      //
      
      SdaiAppInstance alignmentHorizontal = appendRelNests(model, alignment, "IfcAlignmentHorizontal", alignmentNests);
      assignGlobalId(alignmentHorizontal);
      sdaiPutAttrBN(alignmentHorizontal, "Name", sdaiSTRING, "Alignment Horizontal");
      sdaiPutAttrBN(alignmentHorizontal, "ObjectPlacement", sdaiINSTANCE, objectPlacement);

      SdaiAppInstance relNests = sdaiCreateInstanceBN(model, "ifcrelnests");
      assignGlobalId(relNests);
      sdaiPutAttrBN(relNests, "OwnerHistory", sdaiINSTANCE, ownerHistory);
      sdaiPutAttrBN(relNests, "RelatingObject", sdaiINSTANCE, alignmentHorizontal);
      SdaiList nestedHorizontalSegments = sdaiCreateAggrBN(relNests, "RelatedObjects");

        // Representation is IfcCompositeCurve
        SdaiAppInstance compositeCurve = nullptr;
        SdaiList segmentsHorizontalRepr = nullptr;
        if (generateRepresentations)
        {
          compositeCurve = createShapeRepresentation(model, alignmentHorizontal, context3D, "Axis", "Curve2D", "IfcCompositeCurve");
          sdaiPutAttrBN(compositeCurve, "SelfIntersect", sdaiLOGICAL, sdaiFALSE);
          //sdaiPutAttrBN(gradientCurve, "BaseCurve", sdaiINSTANCE, gradientCurve);
          segmentsHorizontalRepr = sdaiCreateAggrBN(compositeCurve, "Segments"); 
        }

      OdGePoint2d startPtPrev;
      OdGePoint2d startPt;

      for (unsigned int i = 0; i < xtrData.horSegs.size(); ++i)
      {
        SdaiAppInstance nestedSegment = sdaiCreateInstanceBN(model, "IfcAlignmentSegment");
        assignGlobalId(nestedSegment);
        sdaiPutAttrBN(nestedSegment, "OwnerHistory", sdaiINSTANCE, ownerHistory);

        XtrHorizontalSegment &seg = xtrData.horSegs.at(i);

        // In XTR:
        // Radius = 0 Represents an infinite radius, ie a straight line
        // Radius > 0 circle center lies to the right of the routing, convex radius for the profiles
        // Radius < 0 circle center is to the left of the alignment, concave radius for the profiles
        // OdGeVector2d::perpVector() goes CCW for, so radius signs should be inversed.
        SdaiReal seg_startRadius = -seg.startRadius;
        SdaiReal seg_endRadius = -seg.endRadius;

        double azimuth = -((9. * seg.azimuth / 10.) - 90.); // Gradians to degrees
      
        SdaiAppInstance inst = NULL;
        if (seg.type == XtrType::D)
        {
          inst = createHorizontalLineSegment2D(model,
            seg.easting, seg.northing, azimuth, seg.length);
        }
        else
        if (seg.type == XtrType::C)
        {
          inst = createHorizontalCircularArcSegment2D(model,
            seg.easting, seg.northing, azimuth, seg.length,
            seg_startRadius);
        }
        else
        if (seg.type == XtrType::R)
        {
          inst = createHorizontalTransitionCurveSegment2D(model,
            seg.easting, seg.northing, azimuth, seg.length,
            seg_startRadius, seg_endRadius,
            "CLOTHOID");
        }

        ODA_ASSERT_ONCE(inst);
        sdaiPutAttrBN(nestedSegment, "DesignParameters", sdaiINSTANCE, inst);
        sdaiPutAggrByIndex(nestedHorizontalSegments, i, sdaiINSTANCE, nestedSegment);

        if (segmentsHorizontalRepr)
        {
          // It's better to operate radians here
          SdaiReal azimuthToRad = azimuth * OdaPI / 180.;

          // TODO: Start Placement creation
          double offsetX = 0.; // 2723135.63806;
          double offsetY = 0.; // 1213636.851160;

          // Common for all segment types:
          SdaiAppInstance location = createCartesianPoint2D(model, seg.easting - offsetX, seg.northing - offsetY); // Q: Can we use same point as in semantic segment?
          SdaiAppInstance refDirection = createDirection2D(model, cos(azimuthToRad), sin(azimuthToRad));
          SdaiAppInstance placement = createAxis2Placement2D(model, location, refDirection); // A placement of segment which is trimmed by SegmentStart attribute

          // Start parameter for curve segment
          SdaiADB adbSegmentStart = sdaiCreateEmptyADB();

          // IfcCurveMeasureSelect doesn't allow negative values, however, but this is needed for 
          // CW case (when signed radius is positive) as IfcCircle is always CCW. So for circles
          // will always use IfcParameterValue, not IfcNonNegativeLengthMeasure.
          double signedSegmentLength = 0;

          // ParentCurve creation
          SdaiAppInstance parentCurve = nullptr;
          switch (seg.type)
          {
            case XtrType::D:
            {
              parentCurve = createIfcLine(model, seg.length, adbSegmentStart, signedSegmentLength);
              break;
            }
            case XtrType::C:
            {
              parentCurve = createIfcCircle(model, seg_startRadius, seg.length, adbSegmentStart, signedSegmentLength);
              break;
            }
            case XtrType::R:
            {
              parentCurve = createIfcClothoid(model, seg_startRadius, seg_endRadius, seg.length, adbSegmentStart, signedSegmentLength);
              break;
            }
          }
          ODA_ASSERT(parentCurve);

          // Final composite curve segment!
          SdaiAppInstance horizontalSegmentRepr = sdaiCreateInstanceBN(model, "IfcCurveSegment");
          
          // 2D, so always CONTSAMEGRADIENTSAMECURVATURE
          sdaiPutAttrBN(horizontalSegmentRepr, "Transition", sdaiENUM, "CONTSAMEGRADIENTSAMECURVATURE");
          sdaiPutAttrBN(horizontalSegmentRepr, "Placement", sdaiINSTANCE, placement);

          sdaiPutAttrBN(horizontalSegmentRepr, "SegmentStart", sdaiADB, adbSegmentStart);
          sdaiDeleteADB(adbSegmentStart);

          SdaiADB adbSegmentLength = sdaiCreateEmptyADB();
          if (seg.type == XtrType::C)
          {
            // Always use IfcParameterValue for circular segments.
            sdaiPutADBTypePath(adbSegmentLength, 1, typePathParameterValue);
          }
          else
          {
            // Positive length can be used for straight and clothoid segments
            sdaiPutADBTypePath(adbSegmentLength, 1, typePathNonNegativeLengthMeasure);
          }

          sdaiPutADBValue(adbSegmentLength, sdaiREAL, signedSegmentLength);
          sdaiPutAttrBN(horizontalSegmentRepr, "SegmentLength", sdaiADB, adbSegmentLength);
          sdaiDeleteADB(adbSegmentLength);

          sdaiPutAttrBN(horizontalSegmentRepr, "ParentCurve", sdaiINSTANCE, parentCurve);

          sdaiPutAggrByIndex(segmentsHorizontalRepr, i, sdaiINSTANCE, horizontalSegmentRepr);
        }
      }

      //
      // Vertical Alignment
      //

      SdaiAppInstance alignmentVertical = appendRelNests(model, alignment, "IfcAlignmentVertical", alignmentNests);
      assignGlobalId(alignmentVertical);
      sdaiPutAttrBN(alignmentVertical, "Name", sdaiSTRING, "Alignment Vertical");
      sdaiPutAttrBN(alignmentVertical, "ObjectPlacement", sdaiINSTANCE, objectPlacement);
      
      relNests = sdaiCreateInstanceBN(model, "ifcrelnests");
      assignGlobalId(relNests);
      sdaiPutAttrBN(relNests, "OwnerHistory", sdaiINSTANCE, ownerHistory);
      sdaiPutAttrBN(relNests, "RelatingObject", sdaiINSTANCE, alignmentVertical);
      SdaiList nestedVerticalSegments = sdaiCreateAggrBN(relNests, "RelatedObjects");

        // Representation is IfcGradientCurve
        SdaiAppInstance gradientCurve = nullptr;
        SdaiList gradientSegmentsRepr = nullptr;
        if (generateRepresentations)
        {
          gradientCurve = createShapeRepresentation(model, alignmentVertical, context3D, "Axis", "Curve3D", "IfcGradientCurve");
          sdaiPutAttrBN(gradientCurve, "BaseCurve", sdaiINSTANCE, compositeCurve);
          sdaiPutAttrBN(gradientCurve, "SelfIntersect", sdaiLOGICAL, sdaiFALSE);
          gradientSegmentsRepr = sdaiCreateAggrBN(gradientCurve, "Segments");
        }

      double gradientCoeff = 1e-3;

      for (unsigned int i = 0; i < xtrData.vertSegs.size(); ++i)
      {
        SdaiAppInstance nestedSegment = sdaiCreateInstanceBN(model, "IfcAlignmentSegment");
        assignGlobalId(nestedSegment);
        sdaiPutAttrBN(nestedSegment, "OwnerHistory", sdaiINSTANCE, ownerHistory);

        XtrVerticalSegment &seg = xtrData.vertSegs.at(i);

        // In XTR:
        // Radius = 0 Represents an infinite radius, ie a straight line
        // Radius > 0, arc segment is convex, center lies below the arc
        // Radius < 0, src segment is concave, center lies above the arc
        // OdGeVector2d::perpVector() goes CCW for, so radius signs should be inversed.
        SdaiReal seg_startRadius = -seg.startRadius;

        double gradientPerMill = seg.gradient * gradientCoeff;

        double gradientRadians = atan(gradientPerMill);
        double cosGradient = cos(gradientRadians);
        double sinGradient = sin(gradientRadians);

        double segmentLength = 0.;

        SdaiInstance inst = NULL;
        if (seg.type == XtrType::d)
        {
          inst = createAlignmentVerticalSegmentLine(model,
            seg.startDistAlong, seg.horizontalLength, seg.startHeight, gradientPerMill);
        }
        else
        if (seg.type == XtrType::c)
        {
          bool isConvex = seg_startRadius < 0;

          double R2 = seg_startRadius * seg_startRadius;
          double G2 = gradientRadians * gradientRadians;

          OdGeVector2d gradientVector(cosGradient, sinGradient);
          OdGeVector2d gradientPerp = gradientVector.perpVector();
          OdGePoint2d s(seg.startDistAlong, seg.startHeight);
          OdGePoint2d c = s + gradientPerp * seg_startRadius;

          // Arc center in (DistAlong, Height) coordinate system
          double Sc = c.x; // seg.startDistAlong + fabs(seg_startRadius) * gradientRadians / sqrt(1. + G2);
          double Zc = c.y; // seg.startHeight - fabs(seg_startRadius) / sqrt(1. + G2);

          double S1 = seg.startDistAlong + seg.horizontalLength;
          double dS = (S1 - Sc); // Direction along horizontal length from center to S1
          double dS2 = dS * dS; // Squared
          double dZ = sqrt(R2 - dS2);
          double Z1 = isConvex ? Zc + dZ : Zc - dZ;
          OdGePoint2d e(S1, Z1);
          OdGeVector2d endGradientVecor = (e - c).perpVector();

          double endGradient = endGradientVecor.angle();// dS / (Z1 - Zc);
          double endGradientPerMill = tan(endGradient);

          //ODA_ASSERT(c == centP);
          double sA = (s - c).angle();
          double eA = (e - c).angle();
          double dA = eA - sA;
          double arcLen = dA * seg_startRadius;
          segmentLength = isConvex ? -arcLen : arcLen;

          inst = createAlignmentVerticalSegmentCircularArc(model,
            seg.startDistAlong, seg.horizontalLength, seg.startHeight,
            gradientPerMill, endGradientPerMill,
            seg_startRadius);
        }

        ODA_ASSERT(inst);
        sdaiPutAttrBN(nestedSegment, "DesignParameters", sdaiINSTANCE, inst);
        sdaiPutAggrByIndex(nestedVerticalSegments, i, sdaiINSTANCE, nestedSegment);

        if (gradientSegmentsRepr)
        {
          SdaiADB adbSegmentStart = sdaiCreateEmptyADB();

          SdaiADB adb = sdaiCreateEmptyADB();
          sdaiPutADBTypePath(adb, 1, typePathNonNegativeLengthMeasure);

#ifndef _USE_AXIS2PLACEMENT2D
          SdaiAppInstance pointByDistanceExpression = sdaiCreateInstanceBN(model, "IfcPointByDistanceExpression");

          sdaiPutADBValue(adb, sdaiREAL, seg.startDistAlong);
          sdaiPutAttrBN(pointByDistanceExpression, "DistanceAlong", sdaiADB, adb);
          sdaiPutAttrBN(pointByDistanceExpression, "OffsetVertical", sdaiREAL, seg.startHeight);
          sdaiPutAttrBN(pointByDistanceExpression, "BasisCurve", sdaiINSTANCE, compositeCurve); 

          SdaiAppInstance axis2Placement = sdaiCreateInstanceBN(model, "IfcAxis2PlacementLinear");
          sdaiPutAttrBN(axis2Placement, "Location", sdaiINSTANCE, pointByDistanceExpression);
#else
          SdaiAppInstance cartesianPointHLandHeight = createCartesianPoint2D(model, seg.startDistAlong, seg.startHeight);
          //SdaiAppInstance refDirection = createDirection2D(model, 1., 0.);

          SdaiAppInstance axis2Placement = sdaiCreateInstanceBN(model, "IfcAxis2Placement2D");
          sdaiPutAttrBN(axis2Placement, "Location", sdaiINSTANCE, cartesianPointHLandHeight);
          //sdaiPutAttrBN(axis2Placement2D, "RefDirection", sdaiINSTANCE, refDirection);
#endif

          SdaiReal signedSegmentLength = 0.;

          // ParentCurve creation
          SdaiAppInstance parentCurve = nullptr;
          switch (seg.type)
          {
            case XtrType::d:
            {
              SdaiReal lineLength = seg.horizontalLength / cosGradient;
              parentCurve = createIfcLineGradient(model, lineLength, adbSegmentStart, signedSegmentLength, cosGradient, sinGradient);
              break;
            }
            case XtrType::c:
            {
              SdaiReal arcLength = segmentLength;
              parentCurve = createIfcCircleGradient(model, seg_startRadius, arcLength, adbSegmentStart, signedSegmentLength, gradientRadians);
              break;
            }
          }
          ODA_ASSERT(parentCurve);

          // Final composite curve segment!
          SdaiAppInstance verticalSegmentRepr = sdaiCreateInstanceBN(model, "IfcCurveSegment");

          // CONTSAMEGRADIENT
          sdaiPutAttrBN(verticalSegmentRepr, "Transition", sdaiENUM, "CONTSAMEGRADIENT");
          sdaiPutAttrBN(verticalSegmentRepr, "Placement", sdaiINSTANCE, axis2Placement);

          sdaiPutAttrBN(verticalSegmentRepr, "SegmentStart", sdaiADB, adbSegmentStart);
          sdaiDeleteADB(adbSegmentStart);

          sdaiPutADBValue(adb, sdaiREAL, signedSegmentLength);
          sdaiPutAttrBN(verticalSegmentRepr, "SegmentLength", sdaiADB, adb);
          sdaiDeleteADB(adb);

          sdaiPutAttrBN(verticalSegmentRepr, "ParentCurve", sdaiINSTANCE, parentCurve);

          sdaiPutAggrByIndex(gradientSegmentsRepr, i, sdaiINSTANCE, verticalSegmentRepr);
        }
      }

      //
      // Cant + Segments, in meters
      //

      double railHeadDistance = 1.5;// 20.;

      SdaiAppInstance alignmentCant = appendRelNests(model, alignment, "IfcAlignmentCant", alignmentNests);
      assignGlobalId(alignmentCant);
      sdaiPutAttrBN(alignmentCant, "Name", sdaiSTRING, "Alignment Cant");
      sdaiPutAttrBN(alignmentCant, "ObjectPlacement", sdaiINSTANCE, objectPlacement);
      sdaiPutAttrBN(alignmentCant, "RailHeadDistance", sdaiREAL, railHeadDistance);
      
      relNests = sdaiCreateInstanceBN(model, "ifcrelnests");
      assignGlobalId(relNests);
      sdaiPutAttrBN(relNests, "OwnerHistory", sdaiINSTANCE, ownerHistory);
      sdaiPutAttrBN(relNests, "RelatingObject", sdaiINSTANCE, alignmentCant);
      SdaiList nestedCantSegments = sdaiCreateAggrBN(relNests, "RelatedObjects");

        // Representation is IfcSegmentedReferenceCurve

        SdaiAppInstance segmentedReferenceCurve = nullptr;
        SdaiList segmentedReferenceCurveSegmentsRepr = nullptr;
        if (generateRepresentations)
        {
          segmentedReferenceCurve = createShapeRepresentation(model, alignmentCant, context3D, "Axis", "Curve3D", "IfcSegmentedReferenceCurve");
          sdaiPutAttrBN(segmentedReferenceCurve, "BaseCurve", sdaiINSTANCE, gradientCurve);
          sdaiPutAttrBN(segmentedReferenceCurve, "SelfIntersect", sdaiLOGICAL, sdaiFALSE);
          segmentedReferenceCurveSegmentsRepr = sdaiCreateAggrBN(segmentedReferenceCurve, "Segments");
        }

      for (unsigned int i = 0; i < xtrData.cantSegs.size(); ++i)
      {
        SdaiAppInstance nestedSegment = sdaiCreateInstanceBN(model, "IfcAlignmentSegment");
        assignGlobalId(nestedSegment);
        sdaiPutAttrBN(nestedSegment, "OwnerHistory", sdaiINSTANCE, ownerHistory);

        XtrCantSegment &seg = xtrData.cantSegs.at(i);

        // The height of left rail minus right rail, mm.
        double startCantLeft = seg.startCant / 2. * toM;
        double startCantRight = startCantLeft - seg.startCant * toM;
        double endCantLeft = seg.endCant / 2. * toM;
        double endCantRight = (endCantLeft - seg.endCant * toM);

        SdaiInstance cantSegment = createAlignmentCantSegmentLine(model,
          seg.startDistAlong, seg.horizontalLength,
          startCantLeft, endCantLeft, startCantRight, endCantRight); // TODO
      
        ODA_ASSERT(cantSegment);
        sdaiPutAttrBN(nestedSegment, "DesignParameters", sdaiINSTANCE, cantSegment);
        sdaiPutAggrByIndex(nestedCantSegments, i, sdaiINSTANCE, nestedSegment);

        if (segmentedReferenceCurveSegmentsRepr)
        {
          // Position along horizontal length
          SdaiAppInstance cartesianPointStart = createCartesianPoint3D(model, seg.startDistAlong, 0., 0.);

          // Inclination axis calculation
          SdaiReal cant = startCantRight - startCantLeft;
          double horizontalSize = sqrt(railHeadDistance * railHeadDistance - cant * cant);
          SdaiReal cosAlpha = horizontalSize / railHeadDistance; // becomes an YoZ plane where Y-dir is negate
          SdaiReal alpha = acos(cosAlpha);
          SdaiReal sinAlpha = sin(alpha);

          // Segment is in XoZ plane, here it is its normal in YoZ plane where Y is negated, Z is upward
          SdaiAppInstance axis = createDirection3D(model, 0., cant < 0 ? -sinAlpha : sinAlpha, cosAlpha);

          // Direction along horizontal alignment plane
          SdaiAppInstance direction = createDirection3D(model, 1., 0., 0.);

          SdaiAppInstance axis2Placement = sdaiCreateInstanceBN(model, "IfcAxis2Placement3D");
          sdaiPutAttrBN(axis2Placement, "Location", sdaiINSTANCE, cartesianPointStart);
          sdaiPutAttrBN(axis2Placement, "Axis", sdaiINSTANCE, axis);
          sdaiPutAttrBN(axis2Placement, "RefDirection", sdaiINSTANCE, direction);

          // ParentCurve creation
          SdaiAppInstance parentCurve = nullptr;
          switch (seg.type)
          {
            case XtrType::Q:
            {
              parentCurve = sdaiCreateInstanceBN(model, "IfcLine");
              SdaiAppInstance pnt = createCartesianPoint2D(model, 0., 0.);
              SdaiAppInstance orientation = createDirection2D(model, 1., 0.);
              SdaiAppInstance dir = createVector(model, orientation, 1.);
              sdaiPutAttrBN(parentCurve, "Pnt", sdaiINSTANCE, pnt);
              sdaiPutAttrBN(parentCurve, "Dir", sdaiINSTANCE, dir);
              break;
            }
          }
          ODA_ASSERT(parentCurve);

          // Final composite curve segment!
          SdaiAppInstance cantSegmentRepr = sdaiCreateInstanceBN(model, "IfcCurveSegment");
          sdaiPutAttrBN(cantSegmentRepr, "Transition", sdaiENUM, "CONTINUOUS");
          sdaiPutAttrBN(cantSegmentRepr, "Placement", sdaiINSTANCE, axis2Placement);

          SdaiADB adb = sdaiCreateEmptyADB();
          sdaiPutADBTypePath(adb, 1, typePathNonNegativeLengthMeasure);
            sdaiPutADBValue(adb, sdaiREAL, 0.); // Local segment beginning parameter
            sdaiPutAttrBN(cantSegmentRepr, "SegmentStart", sdaiADB, adb);
            sdaiPutADBValue(adb, sdaiREAL, seg.horizontalLength); // TODO: Actual length, not horizonta?
            sdaiPutAttrBN(cantSegmentRepr, "SegmentLength", sdaiADB, adb);
          sdaiDeleteADB(adb);

          sdaiPutAttrBN(cantSegmentRepr, "ParentCurve", sdaiINSTANCE, parentCurve);

          sdaiPutAggrByIndex(segmentedReferenceCurveSegmentsRepr, i, sdaiINSTANCE, cantSegmentRepr);
        }
      }

      if (gradientCurve)
        sdaiPutAttrBN(alignment, "Axis", sdaiINSTANCE, gradientCurve);

    //
    // Rail Profile, in meters
    //

    SdaiAppInstance railProfile = appendAsymmetricIShapeProfileDef(model,

      "AREA", "Rail Profile", NULL,

      //
      // For R65/RP65 rail type:
      //

      // EXPLICIT
      /* bottomFlangeWidth */ toM * 150.,
      /* overallDepth */ toM * 180.,
      /* webThickness */ toM * 20.,
      /* bottomFlangeThickness */ toM * 11.2,
      /* topFlangeWidth */ toM * 75.,

      // OPTIONAL
      /* bottomFlangeFilletRadius */ toM * 25.,
      /* topFlangeThickness */ toM * 35.6,
      /* topFlangeFilletRadius */ toM * 15.,
      /* bottomFlangeEdgeRadius */ toM * 4.,
      /* bottomFlangeSlope */ OdDAI::Consts::OdNan, // Skip
      /* topFlangeEdgeRadius */ toM * 3.
      /* topFlangeSlope */ // Not used
    );

    // Axis
    /*
    SdaiAppInstance linearAxisWithInclination = sdaiCreateInstanceBN(model, "IfcLinearAxisWithInclination");
    sdaiPutAttrsBN(linearAxisWithInclination, 2,
      "Directrix", sdaiINSTANCE, alignmentCurve,
      "Inclinating", sdaiINSTANCE, alignment2DCant
    );
    SdaiAppInstance shapeRepresentationAxis = sdaiCreateInstanceBN(model, "IfcShapeRepresentation");
    sdaiPutAttrsBN(shapeRepresentationAxis, 3,
      "ContextOfItems", sdaiINSTANCE, context2D,
      "RepresentationIdentifier", sdaiSTRING, "Axis",
      "RepresentationType", sdaiSTRING, "Curve"
    );
    SdaiSet itemsAxis = sdaiCreateAggrBN(shapeRepresentationAxis, "Items");
    sdaiAdd(itemsAxis, sdaiINSTANCE, linearAxisWithInclination);

    // SweptSolid
    SdaiAppInstance inclinedReferenceSweptAreaSolid = sdaiCreateInstanceBN(model, "IfcInclinedReferenceSweptAreaSolid");
    sdaiPutAttrsBN(inclinedReferenceSweptAreaSolid, 3,
      "SweptArea", sdaiINSTANCE, railProfile,
      "Directrix", sdaiINSTANCE, alignmentCurve,
      "Inclinating", sdaiINSTANCE, alignment2DCant
    );
    SdaiAppInstance shapeRepresentationSweptSolid = sdaiCreateInstanceBN(model, "IfcShapeRepresentation");
    sdaiPutAttrsBN(shapeRepresentationSweptSolid, 3,
      "ContextOfItems", sdaiINSTANCE, context3D,
      "RepresentationIdentifier", sdaiSTRING, "Body",
      "RepresentationType", sdaiSTRING, "SweptSolid"
    );
    SdaiSet itemsSweptSolid = sdaiCreateAggrBN(shapeRepresentationSweptSolid, "Items");
    sdaiAdd(itemsSweptSolid, sdaiINSTANCE, inclinedReferenceSweptAreaSolid);

    // ProductDefinitionShape
    SdaiAppInstance productDefinitionShape = sdaiCreateInstanceBN(model, "IfcProductDefinitionShape");
    SdaiList representations = sdaiCreateAggrBN(productDefinitionShape, "Representations");
    sdaiPutAggrByIndex(representations, 0, sdaiINSTANCE, shapeRepresentationSweptSolid);
    sdaiPutAggrByIndex(representations, 1, sdaiINSTANCE, shapeRepresentationAxis);
    */

    //sdaiPutAttrBN(rail, "Representation", sdaiINSTANCE, productDefinitionShape);

    //
    // Write model to a file
    //

    // Fill header file_description using SDAI
    SdaiInstance headerDescription = _sdaiHeaderDescription(repo);

    SdaiAggr aggrDescription = NULL;
    if (sdaiGetAttrBN(headerDescription, "description", sdaiAGGR, &aggrDescription))
    {
      OdAnsiString strSourceXtr;
      strSourceXtr.format("Source XTR file: %s", OdAnsiString(xtrFileName, CP_UTF_8).c_str());
      sdaiPutAggrByIndex(aggrDescription, 0, sdaiSTRING, strSourceXtr.c_str());

      OdAnsiString strRailHeadDistance;
      strRailHeadDistance.format("RailHeadDistance is: %.2f m", railHeadDistance);
      sdaiPutAggrByIndex(aggrDescription, 1, sdaiSTRING, strRailHeadDistance.c_str());
    }

    // Fill header file_name using SDAI
    SdaiInstance headerName = _sdaiHeaderName(repo);
    SdaiList aggrOrganization = NULL;
    if (sdaiGetAttrBN(headerName, "organization", sdaiAGGR, &aggrOrganization))
    {
      sdaiPutAggrByIndex(aggrOrganization, 0, sdaiSTRING, "Open Design Alliance");
    }

    OdString ifcFileName(argv[2]);
    OdAnsiString outputFileName(ifcFileName, CP_UTF_8);
    _sdaiWriteRepositoryToFile(repo, const_cast<SdaiString>(outputFileName.c_str()));

    sdaiCloseSession(session);
  }
  catch(OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch(...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  odDbRootUninitialize();
  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}

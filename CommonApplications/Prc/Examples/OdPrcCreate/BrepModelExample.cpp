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

#include "PrcCommon.h"

#include "PrcFile.h"
#include "PrcUniqueId.h"
#include "PrcModelFileData.h"
#include "PrcFileStructure.h"
#include "PrcBrepModel.h"
#include "PrcBrepData.h"

#include "PrcEdge.h"
#include "PrcCoEdge.h"
#include "PrcLoop.h"
#include "PrcFace.h"
#include "PrcConnex.h"
#include "PrcShell.h"

#include "PrcSurface.h"
#include "PrcSphere.h"
#include "PrcCylinder.h"
#include "PrcCone.h"
#include "PrcRuledSurface.h"
#include "PrcParabola3d.h"
#include "PrcExtrusionSurface.h"
#include "PrcPolyLine2d.h"
#include "PrcFromCurvesSurface.h"
#include "PrcCircle3d.h"
#include "PrcEllipse3d.h"
#include "PrcLine3d.h"
#include "PrcNurbsCurve3d.h"
#include "Ge/GeNurbCurve3d.h"
#include "Ge/GeKnotVector.h"
#include "Ge/GeSphere.h"
#include "Ge/GeTorus.h"
#include "Ge/GeCone.h"
#include "Ge/GeCylinder.h"
#include "PrcHelixType0Curve.h"
#include "PrcRevolutionSurface.h"
#include "PrcCylindricalSurface.h"
#include "PrcNurbsSurface.h"
#include "PrcTorus.h"
#include "PrcOffsetSurface.h"
#include "PrcTransformedSurface.h"
#include "PrcMath3dLinear.h"
#include "PrcPlane.h"
#include "PrcBlend01Surface.h"
#include "PrcBlend02Surface.h"
#include "PrcIntersectionCurve3d.h"
#include "PrcBlend03Surface.h"
#include "PrcWireEdge.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcMaterialGeneric.h"


// fill params for brep with PRC_TYPE_SURF_Sphere
OdPrcSurfacePtr CreateSphere ()
{
  OdPrcSpherePtr pPrcSphere = OdPrcSphere::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcSphere->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named sphere in srfContent");
    pPrcSphere->setUVParameterization(OdPrcUVParameterization(-OdaPI, OdaPI, -OdaPI/2, OdaPI/2));
    // can add transformation if needed here
    // TBD

    pPrcSphere->setRadius(1);
  }
  return pPrcSphere;
}

OdPrcSurfacePtr createCylinder ()
{
  OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

    pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -OdaPI/2, OdaPI/2));
    // can add transformation if needed here
    // TBD

    pPrcCylinder->setRadius(1);
  }
  return pPrcCylinder;
}

OdPrcSurfacePtr CreateCone ()
{
  OdPrcConePtr pPrcCone = OdPrcCone::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcCone->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named cone in srfContent");

    pPrcCone->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, OdPrcDomain::kUpperInfinite));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    matr *= OdGeMatrix3d::rotation(2.14, OdGeVector3d::kXAxis);
    matr *= OdGeMatrix3d::scaling(0.00018);
    transform.set(matr);
    pPrcCone->setTransformation(&transform);
    // TBD

    pPrcCone->setBottomRadius(10);
    pPrcCone->setSemiAngle(0.5);
  }
  return pPrcCone;
}

OdPrcSurfacePtr CreateRuled ()
{
  OdPrcRuledSurfacePtr pPrcRuledSurface = OdPrcRuledSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcRuledSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named ruled in srfContent");

    pPrcRuledSurface->setUVParameterization(OdPrcUVParameterization(-5,5,-5,5));

    // can add transformation if needed here
    // TBD

    OdPrcParabola3dPtr crvParabola = OdPrcParabola3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvParabola->contentCurve();

      // set name
      crvContent.baseGeometry().name().setName(L"named parabola in crvContent");

      // add some data to params
      OdPrcParameterization curveParams(-7.0, 7.0);
      crvParabola->setParameterization( curveParams );

      // can add transformation if needed here

      // TBD
      crvParabola->setFocalLength(0.4);
      crvParabola->setParameterizationType(0);
    }

    OdPrcParabola3dPtr crvParabola1 = OdPrcParabola3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvParabola1->contentCurve();

      // set name
      crvContent.baseGeometry().name().setName(L"named parabola in crvContent");

      // add some data to params
      OdPrcParameterization curveParams(-7.0, 7.0);
      crvParabola1->setParameterization( curveParams );

      // can add transformation if needed here
      OdPrcTransformation3d transform;
      transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,1)));
      crvParabola1->setTransformation(&transform);

      // TBD
      crvParabola1->setFocalLength(0.5);
      crvParabola1->setParameterizationType(0);
    }
    pPrcRuledSurface->firstCurve() = crvParabola;
    pPrcRuledSurface->secondCurve() = crvParabola1;
  }
  return pPrcRuledSurface;
}

OdPrcSurfacePtr CreateExtrusion ()
{
  OdPrcExtrusionSurfacePtr pPrcExtrusionSurface = OdPrcExtrusionSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcExtrusionSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named extrusion in srfContent");

    pPrcExtrusionSurface->setUVParameterization(OdPrcUVParameterization(0,10,0,10));

    // can add transformation if needed here
    // TBD

    OdPrcPolyLine2dPtr crvPolyLine = OdPrcPolyLine2d::createObject();
    {
      OdPrcContentCurve &crvContent = crvPolyLine->contentCurve();

      // - array of control points defining curve
      double points[] = { 0.0,  0.0, 2.0, -1.0, 1.0, -3.0, 3.0, -1.0,
                          5.0, -3.0, 4.0, -1.0, 6.0,  0.0, 4.0,  0.0,
                          3.0,  2.0, 2.0,  0.0, 0.0,  0.0 };

      crvPolyLine->setPoints(points, sizeof(points)/sizeof(points[0])/2, true);
    }

    pPrcExtrusionSurface->setBaseCurve(crvPolyLine);
    pPrcExtrusionSurface->sweepVector() = OdGeVector3d::kZAxis;
  }
  return pPrcExtrusionSurface;
}

OdPrcSurfacePtr CreateFromCurves ()
{
  OdPrcFromCurvesSurfacePtr pPrcFromCurvesSurface = OdPrcFromCurvesSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcFromCurvesSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named fromCurves in srfContent");

    // can add transformation if needed here
    // TBD

    OdPrcNurbsCurve3dPtr crvNurbs = OdPrcNurbsCurve3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvNurbs->contentCurve();

      // fill nurbs parameters
      // - non-array parameters
      int crvdegree = 2;

      // - array of control points defining curve
      OdGePoint3dArray arrPRCPoints;
      arrPRCPoints.push_back(OdGePoint3d(0.0, -1.0,  -1.0));
      arrPRCPoints.push_back(OdGePoint3d(0.3, -0.5,   0.7));
      arrPRCPoints.push_back(OdGePoint3d(1.0,  1.0,   1.0));
      arrPRCPoints.push_back(OdGePoint3d(1.5, -1.0,  -5.0));

      // - array of knots
      OdGeDoubleArray arrDoublesForKnots;
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(3.0);
      arrDoublesForKnots.push_back(4.0);
      arrDoublesForKnots.push_back(5.0);
      arrDoublesForKnots.push_back(6.0);
      arrDoublesForKnots.push_back(7.0);
      OdGeKnotVector arrPRCKnots (arrDoublesForKnots);

      // - array of weights
      OdGeDoubleArray  arrPRCWeights; // zero or for each control point

      // create OdGe nurb curve
      OdGeNurbCurve3d geCurve;
      geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
      crvNurbs->setFromOdGeCurve(geCurve);
    }

    OdPrcLine3dPtr crvLine = OdPrcLine3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvLine->contentCurve();

      // set name
      crvContent.baseGeometry().name().setName(L"named line in crvContent");

      // add some data to params
      OdPrcParameterization curveParams(0.0, 1.0);
      crvLine->setParameterization( curveParams );

      // can add transformation if needed here
      // TBD
    }

    pPrcFromCurvesSurface->origin() = OdGePoint3d(0.1, 0.2, -0.3);
    pPrcFromCurvesSurface->firstCurve() = crvNurbs;
    pPrcFromCurvesSurface->secondCurve() = crvLine;

    OdPrcUVParameterization parameterization(
      pPrcFromCurvesSurface->firstCurve()->parameterization().interval().minValue(), 
      pPrcFromCurvesSurface->firstCurve()->parameterization().interval().maxValue(),
      pPrcFromCurvesSurface->secondCurve()->parameterization().interval().minValue(), 
      pPrcFromCurvesSurface->secondCurve()->parameterization().interval().maxValue()
      );
    pPrcFromCurvesSurface->setUVParameterization(parameterization);
  }
  return pPrcFromCurvesSurface;
}

OdPrcSurfacePtr CreateRevolution ()
{
  OdPrcRevolutionSurfacePtr pPrcRevolutionSurface = OdPrcRevolutionSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcRevolutionSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named revolution in srfContent");

    pPrcRevolutionSurface->setUVParameterization(OdPrcUVParameterization(0, OdaPI/2, 0, OdaPI/2));

    // can add transformation if needed here
    // TBD

    OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvCircle->contentCurve();

      // set name
      crvContent.baseGeometry().name().setName(L"named circle in crvContent");

      // add some data to params
      OdPrcParameterization curveParams(0, Oda2PI);
      crvCircle->setParameterization( curveParams );

      // can add transformation if needed here
      OdPrcTransformation3d transform;
      OdGeMatrix3d matr;
      matr *= OdGeMatrix3d::rotation(0.57, OdGeVector3d::kXAxis);
      transform.set(matr);
      crvCircle->setTransformation(&transform);
      // TBD
      crvCircle->setRadius(1.0);
    }

    pPrcRevolutionSurface->origin() = OdGePoint3d();
    pPrcRevolutionSurface->x() = OdGeVector3d::kZAxis;
    pPrcRevolutionSurface->y() = OdGeVector3d::kXAxis;
    pPrcRevolutionSurface->setBaseCurve(crvCircle);
  }
  return pPrcRevolutionSurface;
}

OdPrcSurfacePtr CreateCylindrical ()
{
  OdPrcCylindricalSurfacePtr pPrcCylindricalSurface = OdPrcCylindricalSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcCylindricalSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named cylindrical in srfContent");

    pPrcCylindricalSurface->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, OdaPI));

    // can add transformation if needed here
    // TBD

    OdPrcSpherePtr pPrcSphere = OdPrcSphere::createObject();
    {
      OdPrcContentSurface &srfContent  = pPrcSphere->contentSurface();

      // set name
      srfContent.baseGeometry().name().setName(L"named sphere in srfContent");
      pPrcSphere->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, OdaPI));
      // can add transformation if needed here
      // TBD

      pPrcSphere->setRadius(1);
    }

    pPrcCylindricalSurface->setBaseSurface(pPrcSphere);
  }
  return pPrcCylindricalSurface;
}

OdPrcSurfacePtr CreateNURBS ()
{
  OdPrcNurbsSurfacePtr pPrcNurbsSurface = OdPrcNurbsSurface::createObject();
  {
  OdPrcContentSurface &srfContent  = pPrcNurbsSurface->contentSurface();

  // set name
  srfContent.baseGeometry().name().setName(L"named Nurbs in srfContent");

  // can add transformation if needed here
  // TBD

  int degree_in_u = 3;
  int degree_in_v = 3;

  // - array of control points defining curve
  OdGePoint3dArray arrPRCPoints;
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -1.082736, 2.636552));
  arrPRCPoints.push_back(OdGePoint3d(1.362549, -1.082736, 2.636552));
  arrPRCPoints.push_back(OdGePoint3d(-0.608291, -0.705984, 2.263106));
  arrPRCPoints.push_back(OdGePoint3d(-3.123146, 0.692628, 0.473068));
  arrPRCPoints.push_back(OdGePoint3d(-4.468527, 1.811826, -2.305555));
  arrPRCPoints.push_back(OdGePoint3d(-4.751031, 2.062498, -5.010829));
  arrPRCPoints.push_back(OdGePoint3d(-4.460485, 1.805052, -7.712991));
  arrPRCPoints.push_back(OdGePoint3d(-3.114097, 0.683449, -10.489599));
  arrPRCPoints.push_back(OdGePoint3d(-0.594440, -0.706363, -12.264858));
  arrPRCPoints.push_back(OdGePoint3d(1.362549, -1.082736, -12.636552));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -1.082736, -12.636552));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -0.612156, 2.148675));
  arrPRCPoints.push_back(OdGePoint3d(1.449014, -0.612156, 2.148675));
  arrPRCPoints.push_back(OdGePoint3d(-0.348526, -0.300052, 1.791464));
  arrPRCPoints.push_back(OdGePoint3d(-2.696407, 0.880859, 0.095369));
  arrPRCPoints.push_back(OdGePoint3d(-3.978369, 1.838789, -2.497939));
  arrPRCPoints.push_back(OdGePoint3d(-4.248272, 2.053787, -5.010058));
  arrPRCPoints.push_back(OdGePoint3d(-3.970658, 1.832986, -7.519957));
  arrPRCPoints.push_back(OdGePoint3d(-2.687596, 0.872820, -10.110502));
  arrPRCPoints.push_back(OdGePoint3d(-0.336250, -0.300022, -11.793093));
  arrPRCPoints.push_back(OdGePoint3d(1.449014, -0.612156, -12.148675));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -0.612156, -12.148675));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, 0.086907, 0.622159));
  arrPRCPoints.push_back(OdGePoint3d(1.651939, 0.086907, 0.622159));
  arrPRCPoints.push_back(OdGePoint3d(0.260600, 0.252936, 0.346781));
  arrPRCPoints.push_back(OdGePoint3d(-1.697724, 0.964283, -0.973132));
  arrPRCPoints.push_back(OdGePoint3d(-2.832725, 1.594685, -3.018412));
  arrPRCPoints.push_back(OdGePoint3d(-3.073413, 1.738681, -5.007989));
  arrPRCPoints.push_back(OdGePoint3d(-2.825793, 1.590912, -6.995324));
  arrPRCPoints.push_back(OdGePoint3d(-1.689364, 0.958200, -9.039041));
  arrPRCPoints.push_back(OdGePoint3d(0.269174, 0.254236, -10.348068));
  arrPRCPoints.push_back(OdGePoint3d(1.651939, 0.086907, -10.622159));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, 0.086907, -10.622159));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -0.525546, -1.007479));
  arrPRCPoints.push_back(OdGePoint3d(1.748929, -0.525546, -1.007479));
  arrPRCPoints.push_back(OdGePoint3d(0.554405, -0.385123, -1.189754));
  arrPRCPoints.push_back(OdGePoint3d(-1.090275, 0.193590, -2.093077));
  arrPRCPoints.push_back(OdGePoint3d(-2.033066, 0.699427, -3.558721));
  arrPRCPoints.push_back(OdGePoint3d(-2.233148, 0.815043, -5.005757));
  arrPRCPoints.push_back(OdGePoint3d(-2.027386, 0.696525, -6.450222));
  arrPRCPoints.push_back(OdGePoint3d(-1.083239, 0.188581, -7.916059));
  arrPRCPoints.push_back(OdGePoint3d(0.561938, -0.384438, -8.811094));
  arrPRCPoints.push_back(OdGePoint3d(1.748929, -0.525546, -8.992521));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -0.525546, -8.992521));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -1.182808, -1.627834));
  arrPRCPoints.push_back(OdGePoint3d(1.746516, -1.182808, -1.627834));
  arrPRCPoints.push_back(OdGePoint3d(0.549870, -1.016441, -1.792741));
  arrPRCPoints.push_back(OdGePoint3d(-0.977089, -0.398839, -2.583190));
  arrPRCPoints.push_back(OdGePoint3d(-1.793971, 0.095379, -3.810181));
  arrPRCPoints.push_back(OdGePoint3d(-1.965501, 0.206071, -5.004782));
  arrPRCPoints.push_back(OdGePoint3d(-1.789089, 0.092388, -6.198009));
  arrPRCPoints.push_back(OdGePoint3d(-0.971595, -0.402892, -7.424109));
  arrPRCPoints.push_back(OdGePoint3d(0.558280, -1.016608, -8.208032));
  arrPRCPoints.push_back(OdGePoint3d(1.746516, -1.182808, -8.372166));
  arrPRCPoints.push_back(OdGePoint3d(2.340000, -1.182808, -8.372166));

  // - array of knots
  OdGeDoubleArray arrDoublesForKnots_U;
  arrDoublesForKnots_U.push_back(0.0);
  arrDoublesForKnots_U.push_back(0.0);
  arrDoublesForKnots_U.push_back(0.0);
  arrDoublesForKnots_U.push_back(0.0);
  arrDoublesForKnots_U.push_back(0.428571428571429);
  arrDoublesForKnots_U.push_back(1.0);
  arrDoublesForKnots_U.push_back(1.0);
  arrDoublesForKnots_U.push_back(1.0);
  arrDoublesForKnots_U.push_back(1.0);

  OdGeDoubleArray arrDoublesForKnots_V;
  arrDoublesForKnots_V.push_back(0.000000);
  arrDoublesForKnots_V.push_back(0.000000);
  arrDoublesForKnots_V.push_back(0.000000);
  arrDoublesForKnots_V.push_back(0.000000);
  arrDoublesForKnots_V.push_back(0.293235);
  arrDoublesForKnots_V.push_back(0.586471);
  arrDoublesForKnots_V.push_back(0.879706);
  arrDoublesForKnots_V.push_back(1.026324);
  arrDoublesForKnots_V.push_back(1.172941);
  arrDoublesForKnots_V.push_back(1.466177);
  arrDoublesForKnots_V.push_back(1.759412);
  arrDoublesForKnots_V.push_back(2.052647);
  arrDoublesForKnots_V.push_back(2.052647);
  arrDoublesForKnots_V.push_back(2.052647);
  arrDoublesForKnots_V.push_back(2.052647);

  // - array of weights
  OdGeDoubleArray  arrPRCWeights; // zero or for each control point

  // create OdGe nurb curve
  OdGeNurbSurface geSur;
  geSur.set(degree_in_u, degree_in_v, 0, 0, 5, 11, arrPRCPoints, arrPRCWeights, arrDoublesForKnots_U, arrDoublesForKnots_V);
  pPrcNurbsSurface->setFromOdGeSurface(geSur);

  pPrcNurbsSurface->setKnotType(1);
  pPrcNurbsSurface->setSurfaceForm(9);
  }
  return pPrcNurbsSurface;
}

OdPrcSurfacePtr CreateTorus ()
{
  OdPrcTorusPtr pPrcTorus = OdPrcTorus::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcTorus->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named torus_T1 in srfContent");

    pPrcTorus->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, Oda2PI));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    matr *= OdGeMatrix3d::scaling(8);
    matr *= OdGeMatrix3d::rotation(1.02, OdGeVector3d::kXAxis);
    transform.set(matr);
    pPrcTorus->setTransformation(&transform);
    // TBD

    pPrcTorus->setMajorRadius(0.1);
    pPrcTorus->setMinorRadius(0.05);
  }
  return pPrcTorus;
}

OdPrcSurfacePtr CreateAppleTorus ()
{
  OdPrcTorusPtr pPrcTorus = OdPrcTorus::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcTorus->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named torus_T2 in srfContent");

    pPrcTorus->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, Oda2PI));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    matr *= OdGeMatrix3d::scaling(4.);
    matr *= OdGeMatrix3d::rotation(0.91, OdGeVector3d::kXAxis);
    transform.set(matr);
    pPrcTorus->setTransformation(&transform);
    // TBD
    pPrcTorus->setMajorRadius(0.035);
    pPrcTorus->setMinorRadius(0.1);
  }
  return pPrcTorus;
}

OdPrcSurfacePtr CreateOffset ()
{
  OdPrcOffsetSurfacePtr pPrcOffsetSurface = OdPrcOffsetSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcOffsetSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named offset in srfContent");

    pPrcOffsetSurface->setUVParameterization(OdPrcUVParameterization(0, 8, 0, 8));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    OdGeVector3d vec(-1,-5,0);
    matr *= OdGeMatrix3d::scaling(0.6);
    matr *= OdGeMatrix3d::translation(vec);
    matr *= OdGeMatrix3d::rotation(0.91, OdGeVector3d::kXAxis);
    matr *= OdGeMatrix3d::rotation(0.08, OdGeVector3d::kYAxis);
    transform.set(matr);
    pPrcOffsetSurface->setTransformation(&transform);
    // TBD

    OdPrcExtrusionSurfacePtr pPrcExtrusionSurface = OdPrcExtrusionSurface::createObject();
    {
      OdPrcContentSurface &srfContent  = pPrcExtrusionSurface->contentSurface();

      // set name
      srfContent.baseGeometry().name().setName(L"named extrusion in srfContent");

      pPrcExtrusionSurface->setUVParameterization(OdPrcUVParameterization(0,8,0,8));

      // can add transformation if needed here
      // TBD

      OdPrcPolyLine2dPtr crvPolyLine = OdPrcPolyLine2d::createObject();
      {
        OdPrcContentCurve &crvContent = crvPolyLine->contentCurve();

        // - array of control points defining curve
        double crvPoint[] ={0.0 , 0.0,
          3.0 , 0.0,
          3.0 , 3.0,
          0.0 , 3.0,
          0.0 , 1.0,
          2.0 , 1.0,
          2.0 , 2.0,
          1.0 , 2.0,};

        crvPolyLine->setPoints(crvPoint, 8, true);
      }

      pPrcExtrusionSurface->setBaseCurve(crvPolyLine);
      pPrcExtrusionSurface->sweepVector() = OdGeVector3d::kZAxis;
    }

    pPrcOffsetSurface->setBaseSurface(pPrcExtrusionSurface);
    pPrcOffsetSurface->setOffsetDistance(0.5);
  }
  return pPrcOffsetSurface;
}

OdPrcSurfacePtr CreateTransform ()
{
  OdPrcTransformedSurfacePtr pPrcTransform = OdPrcTransformedSurface::createObject();
  {
  OdPrcContentSurface &srfContent  = pPrcTransform->contentSurface();

  // set name
  srfContent.baseGeometry().name().setName(L"named transform in srfContent");

  pPrcTransform->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, Oda2PI));

  // can add transformation if needed here
  // TBD

  OdPrcNurbsSurfacePtr pPrcNurbsSurface = OdPrcNurbsSurface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcNurbsSurface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named Nurbs in srfContent");

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    OdGeMatrix3d mat;
    mat *= OdGeMatrix3d::scaling(0.001);
    transform.set(mat);
    pPrcTransform->setTransformation(&transform);
    // TBD

    int degree_in_u = 3;
    int degree_in_v = 1;

    // - array of control points defining curve
    OdGePoint3dArray arrPRCPoints;
    arrPRCPoints.push_back(OdGePoint3d(-67.157405122098112, -115.9740605375124, 52.466754587977206));
    arrPRCPoints.push_back(OdGePoint3d(-67.157405122098112, 532.6874471602215, 52.46675458797705));
    arrPRCPoints.push_back(OdGePoint3d(-22.817513244788948, -115.9740605375124, 68.795847107498474));
    arrPRCPoints.push_back(OdGePoint3d(-22.817513244788948, 532.6874471602215, 68.795847107498318));
    arrPRCPoints.push_back(OdGePoint3d(81.77936727888752, -115.9740605375124, 107.31583592593033));
    arrPRCPoints.push_back(OdGePoint3d(81.77936727888752, 532.6874471602215, 107.31583592593017));
    arrPRCPoints.push_back(OdGePoint3d(273.91456622393338, -115.97406053751241, 12.862410570275969));
    arrPRCPoints.push_back(OdGePoint3d(273.91456622393338, 532.6874471602215, 12.862410570275813));
    arrPRCPoints.push_back(OdGePoint3d(499.85917617275175, -115.9740605375124, 111.8586489301551));
    arrPRCPoints.push_back(OdGePoint3d(499.85917617275175, 532.6874471602215, 111.85864893015494));
    arrPRCPoints.push_back(OdGePoint3d(765.48500025020871, -115.97406053751241, 7.5526710171279348));
    arrPRCPoints.push_back(OdGePoint3d(765.48500025020871, 532.6874471602215, 7.5526710171277784));
    arrPRCPoints.push_back(OdGePoint3d(948.81236493263509, -115.97406053751241, 47.825357991483571));
    arrPRCPoints.push_back(OdGePoint3d(948.81236493263509, 532.6874471602215, 47.825357991483415));
    arrPRCPoints.push_back(OdGePoint3d(1057.2765945059859, -115.9740605375124, 71.652384431802815));
    arrPRCPoints.push_back(OdGePoint3d(1057.2765945059859, 532.6874471602215, 71.652384431802659));

    // - array of knots
    OdGeDoubleArray arrDoublesForKnots_U;
    arrDoublesForKnots_U.push_back(0.);
    arrDoublesForKnots_U.push_back(0.);
    arrDoublesForKnots_U.push_back(0.);
    arrDoublesForKnots_U.push_back(0.);
    arrDoublesForKnots_U.push_back(1.);
    arrDoublesForKnots_U.push_back(2.);
    arrDoublesForKnots_U.push_back(3.);
    arrDoublesForKnots_U.push_back(4.);
    arrDoublesForKnots_U.push_back(5.);
    arrDoublesForKnots_U.push_back(5.);
    arrDoublesForKnots_U.push_back(5.);
    arrDoublesForKnots_U.push_back(5.);

    OdGeDoubleArray arrDoublesForKnots_V;
    arrDoublesForKnots_V.push_back(0.000000);
    arrDoublesForKnots_V.push_back(0.000000);
    arrDoublesForKnots_V.push_back(6.);
    arrDoublesForKnots_V.push_back(6.);

    // - array of weights
    OdGeDoubleArray  arrPRCWeights; // zero or for each control point

    // create OdGe nurb curve
    OdGeNurbSurface geSur;
    geSur.set(degree_in_u, degree_in_v, 0, 0, 8, 2, arrPRCPoints, arrPRCWeights, arrDoublesForKnots_U, arrDoublesForKnots_V);
    pPrcNurbsSurface->setFromOdGeSurface(geSur);

    pPrcNurbsSurface->setKnotType(1);
    pPrcNurbsSurface->setSurfaceForm(9);
  }

  OdPrcMath3dLinearPtr math_transformation = OdPrcMath3dLinear::createObject();
  {
    OdGeMatrix3d &mat = math_transformation->mat();
    mat *= mat.scaling(10.0);
    OdGeVector3d vec(27,0,0);
    mat *= mat.translation(vec);
    mat *= mat.rotation(0.92,OdGeVector3d::kXAxis);
    mat[0][0] = 0.8;
    mat[1][1] = 1.6;
  }

  pPrcTransform->setBaseSurface(pPrcNurbsSurface);
  pPrcTransform->mathTransformation() = math_transformation;
  }

  return pPrcTransform;
}

OdPrcSurfacePtr CreatePlane ()
{
  OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named plane in srfContent");

    pPrcPlane->setUVParameterization(OdPrcUVParameterization(0,2,0,1));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    transform.set(OdGeMatrix3d::rotation(3.52, OdGeVector3d::kXAxis));
    pPrcPlane->setTransformation(&transform);
    // TBD
  }
  return pPrcPlane;
}

OdPrcSurfacePtr CreateBlend01 ()
{
  OdPrcBlend01SurfacePtr pPrcBlend01Surface = OdPrcBlend01Surface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcBlend01Surface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named blend01 in srfContent");

    pPrcBlend01Surface->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, Oda2PI));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    transform.set(OdGeMatrix3d::rotation(0.57, OdGeVector3d::kXAxis));
    pPrcBlend01Surface->setTransformation(&transform);
    // TBD

    OdPrcNurbsCurve3dPtr crvNurbsCenter = OdPrcNurbsCurve3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvNurbsCenter->contentCurve();

      // fill nurbs parameters
      // - non-array parameters
      int crvdegree = 3;

      // - array of control points defining curve
      OdGePoint3dArray arrPRCPoints;
      arrPRCPoints.push_back(OdGePoint3d(1.0, 0.0, 0.0));
      arrPRCPoints.push_back(OdGePoint3d(1.0, 0.55,  0.0));
      arrPRCPoints.push_back(OdGePoint3d(0.55, 1.0,  0.0));
      arrPRCPoints.push_back(OdGePoint3d(0.0, 1.0,  1.0));

      // - array of knots
      OdGeDoubleArray arrDoublesForKnots;
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(2.0);
      OdGeKnotVector arrPRCKnots (arrDoublesForKnots);

      // - array of weights
      OdGeDoubleArray  arrPRCWeights; // zero or for each control point

      // create OdGe nurb curve
      OdGeNurbCurve3d geCurve;
      geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
      crvNurbsCenter->setFromOdGeCurve(geCurve);
    }

    OdPrcNurbsCurve3dPtr crvNurbsOrigin = OdPrcNurbsCurve3d::createObject();
    {
      OdPrcContentCurve &crvContent = crvNurbsOrigin->contentCurve();

      // fill nurbs parameters
      // - non-array parameters
      int crvdegree = 3;

      // - array of control points defining curve
      OdGePoint3dArray arrPRCPoints;
      arrPRCPoints.push_back(OdGePoint3d(1.1, 0.0, 0.0));
      arrPRCPoints.push_back(OdGePoint3d(1.1, 0.61,  0.0));
      arrPRCPoints.push_back(OdGePoint3d(0.61, 1.1,  0.0));
      arrPRCPoints.push_back(OdGePoint3d(0.0, 1.1,  1.0));

      // - array of knots
      OdGeDoubleArray arrDoublesForKnots;
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(1.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(2.0);
      arrDoublesForKnots.push_back(2.0);
      OdGeKnotVector arrPRCKnots (arrDoublesForKnots);

      // - array of weights
      OdGeDoubleArray  arrPRCWeights; // zero or for each control point

      // create OdGe nurb curve
      OdGeNurbCurve3d geCurve;
      geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
      crvNurbsOrigin->setFromOdGeCurve(geCurve);
    }

    pPrcBlend01Surface->setCenterCurve(crvNurbsCenter);
    pPrcBlend01Surface->setOriginCurve(crvNurbsOrigin);
  }
  return pPrcBlend01Surface;
}

OdPrcSurfacePtr CreateBlend02 ()
{
  OdPrcBlend02SurfacePtr blend02 = OdPrcBlend02Surface::createObject();

  OdPrcContentSurface &srfContent  = blend02->contentSurface();

  // set name
  srfContent.baseGeometry().name().setName(L"named blend02 in srfContent");

  // can add transformation if needed here
  OdPrcTransformation3d transform;
  OdGeMatrix3d mat;
  OdGeVector3d vec(-0.129, -0.045, 0.0);
  mat *= OdGeMatrix3d::scaling(700.0);
  mat *= OdGeMatrix3d::translation(vec);
  mat *= OdGeMatrix3d::rotation(OdaPI/2,OdGeVector3d::kXAxis);
  transform.set(mat);
  blend02->setTransformation(&transform);
  // TBD

  blend02->setUVParameterization(OdPrcUVParameterization(-0.001607154928977807, 0.01195146616849432, 0, 1));

  OdPrcCylinderPtr srfCyl = OdPrcCylinder::createObject();
  {
    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    OdGePoint3d origin(0.1346409306333122,0.05665149759597796,0.05318000000000001);
    OdGeVector3d xAxis(-1,0,0);
    OdGeVector3d yAxis(0,1,0);
    OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
    matr.setCoordSystem(origin,xAxis,yAxis,zAxis);
    transform.set(matr);
    srfCyl->setTransformation(&transform);
    srfCyl->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, OdPrcDomain::kLowerInfinite, OdPrcDomain::kUpperInfinite));
    srfCyl->setRadius(0.007856180355214347);
  }

  OdPrcTorusPtr bound_sur1 = OdPrcTorus::createObject();
  {
    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    OdGePoint3d origin(0.1016940451762275,0.03587310626005076,0.02921);
    OdGeVector3d xAxis(1,0,0);
    OdGeVector3d yAxis(0,1,0);
    OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
    matr.setCoordSystem(origin,xAxis,yAxis,zAxis);
    transform.set(matr);
    bound_sur1->setTransformation(&transform);

    bound_sur1->setUVParameterization(OdPrcUVParameterization(0,Oda2PI,0,Oda2PI));
    bound_sur1->setMajorRadius(0.02921000000000001);
    bound_sur1->setMinorRadius(0.00254); //0.002539
  }

  OdPrcIntersectionCurve3dPtr crvIntersection = OdPrcIntersectionCurve3d::createObject();
  {
    OdPrcContentCurve &crvContent = crvIntersection->contentCurve();

    // set name
    crvContent.baseGeometry().name().setName(L"named intersection in crvContent");

    // add some data to params
    OdPrcParameterization curveParams(-0.001607154928977807, 0.01195146616849428);
    crvIntersection->setParameterization( curveParams );

    // can add transformation if needed here

    // TBD
    OdPrcCylinderPtr surCyl = OdPrcCylinder::createObject();
    OdPrcTorusPtr surTor = OdPrcTorus::createObject();

    OdPrcTransformation3d transform;
    OdGeMatrix3d matr;
    OdGePoint3d origin(0.1346409306333122,0.05665149759597796,0.05318000000000001);
    OdGeVector3d xAxis(-1,0,0);
    OdGeVector3d yAxis(0,1,0);
    OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
    matr.setCoordSystem(origin,xAxis,yAxis,zAxis);
    transform.set(matr);
    surCyl->setTransformation(&transform);

    surCyl->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, OdPrcDomain::kLowerInfinite, OdPrcDomain::kUpperInfinite));
    surCyl->setRadius(0.01039618035521435);

    OdPrcTransformation3d transform1;
    OdGeMatrix3d matr1;
    OdGePoint3d origin1(0.1016940451762275,0.03587310626005076,0.02921);
    OdGeVector3d xAxis1(1,0,0);
    OdGeVector3d yAxis1(0,1,0);
    OdGeVector3d zAxis1 = xAxis1.crossProduct(yAxis1);
    matr1.setCoordSystem(origin1,xAxis1,yAxis1,zAxis1);
    transform1.set(matr1);
    surTor->setTransformation(&transform1);

    surTor->setUVParameterization(OdPrcUVParameterization(0,Oda2PI,0,Oda2PI));
    surTor->setMajorRadius(0.02921000000000001);
    surTor->setMinorRadius(0.005079999999999999);

    crvIntersection->setSurface1(surTor);
    crvIntersection->setSurface2(surCyl);
    crvIntersection->setSurface1Sense(true);
    crvIntersection->setSurface2Sense(false);
    crvIntersection->setIntersectionSense(false);
    crvIntersection->crossingPointsCrvIntersection().resize(8);

    OdUInt8 nCrossingPointFlags = PRC_INTERSECTION_CROSS_POINT_SURFACE1 | PRC_INTERSECTION_CROSS_POINT_SURFACE2 | PRC_INTERSECTION_CROSS_POINT_INSIDE_CURVE_INTERVAL;

    crvIntersection->crossingPointsCrvIntersection()[0].crossingPointPosition().set(0.1341041808452103,0.04626918255341075,0.02762582792403328);
    crvIntersection->crossingPointsCrvIntersection()[0].crossingPointUv1().set(0.3103978254394728,5.966051167063784);
    crvIntersection->crossingPointsCrvIntersection()[0].crossingPointUv2().set(4.764041463982647,0.02555417207596673);
    crvIntersection->crossingPointsCrvIntersection()[0].crossingPointTangent().set(0.3307189013079988,-0.01709766073082449,0.9435744158862954);
    crvIntersection->crossingPointsCrvIntersection()[0].setCrossingPointParameter(-0.001607154928977807);
    crvIntersection->crossingPointsCrvIntersection()[0].setCrossingPointScale(1.000143483648419);
    crvIntersection->crossingPointsCrvIntersection()[0].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[1].crossingPointPosition().set(0.1343734318291666,0.04625875924807728,0.02921);
    crvIntersection->crossingPointsCrvIntersection()[1].crossingPointUv1().set(0.307710025806323,6.283185307179586);
    crvIntersection->crossingPointsCrvIntersection()[1].crossingPointUv2().set(4.738122309398362,0.02397000000000001);
    crvIntersection->crossingPointsCrvIntersection()[1].crossingPointTangent().set(2.591203737317232e-016,-6.669502087194763e-018,1);
    crvIntersection->crossingPointsCrvIntersection()[1].setCrossingPointParameter(2.168404344971009e-019);
    crvIntersection->crossingPointsCrvIntersection()[1].setCrossingPointScale(1);
    crvIntersection->crossingPointsCrvIntersection()[1].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[2].crossingPointPosition().set(0.1341068460463681,0.04626904510958856,0.03078654731335931);
    crvIntersection->crossingPointsCrvIntersection()[2].crossingPointUv1().set(0.3103700654223553,0.3155548357368914);
    crvIntersection->crossingPointsCrvIntersection()[2].crossingPointUv2().set(4.763784759818783,0.0223934526866407);
    crvIntersection->crossingPointsCrvIntersection()[2].crossingPointTangent().set(-0.329121627073357,0.01693037251846447,0.9441357514038816);
    crvIntersection->crossingPointsCrvIntersection()[2].setCrossingPointParameter(0.001598960665494233);
    crvIntersection->crossingPointsCrvIntersection()[2].setCrossingPointScale(1.000343251512573);
    crvIntersection->crossingPointsCrvIntersection()[2].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[3].crossingPointPosition().set(0.1333353720053878,0.04633761943850505,0.03218621630253621);
    crvIntersection->crossingPointsCrvIntersection()[3].crossingPointUv1().set(0.3193993789638551,0.6259523779802445);
    crvIntersection->crossingPointsCrvIntersection()[3].crossingPointUv2().set(4.838302028889195,0.0209937836974638);
    crvIntersection->crossingPointsCrvIntersection()[3].crossingPointTangent().set(-0.6202478501943279,0.07851265255504523,0.7804667627247718);
    crvIntersection->crossingPointsCrvIntersection()[3].setCrossingPointParameter(0.003199180944312005);
    crvIntersection->crossingPointsCrvIntersection()[3].setCrossingPointScale(0.9999042656648364);
    crvIntersection->crossingPointsCrvIntersection()[3].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[4].crossingPointPosition().set(0.1321782193823936,0.04655121941798981,0.03324195681528128);
    crvIntersection->crossingPointsCrvIntersection()[4].crossingPointUv1().set(0.3369276482254578,0.9168548394635812);
    crvIntersection->crossingPointsCrvIntersection()[4].crossingPointUv2().set(4.951548508964415,0.01993804318471873);
    crvIntersection->crossingPointsCrvIntersection()[4].crossingPointTangent().set(-0.8172802565597771,0.1992742425025277,0.5406873019709534);
    crvIntersection->crossingPointsCrvIntersection()[4].setCrossingPointParameter(0.004779920225752403);
    crvIntersection->crossingPointsCrvIntersection()[4].setCrossingPointScale(0.9981746869563218);
    crvIntersection->crossingPointsCrvIntersection()[4].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[5].crossingPointPosition().set(0.130801052426036,0.046990446859571,0.03390171456686072);
    crvIntersection->crossingPointsCrvIntersection()[5].crossingPointUv1().set(0.3648474322366052,1.177278387632713);
    crvIntersection->crossingPointsCrvIntersection()[5].crossingPointUv2().set(5.090703516507586,0.01927828543313928);
    crvIntersection->crossingPointsCrvIntersection()[5].crossingPointTangent().set(-0.8886892161393534,0.3532181381922882,0.2923498314854919);
    crvIntersection->crossingPointsCrvIntersection()[5].setCrossingPointParameter(0.006365978613759895);
    crvIntersection->crossingPointsCrvIntersection()[5].setCrossingPointScale(1.002244619626314);
    crvIntersection->crossingPointsCrvIntersection()[5].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[6].crossingPointPosition().set(0.1288246894375459,0.04803454312639792,0.03426314326305822);
    crvIntersection->crossingPointsCrvIntersection()[6].crossingPointUv1().set(0.4214015261845513,1.467923355389826);
    crvIntersection->crossingPointsCrvIntersection()[6].crossingPointUv2().set(5.306122456986277,0.01891685673694178);
    crvIntersection->crossingPointsCrvIntersection()[6].crossingPointTangent().set(-0.8276313857050265,0.5586316810005534,0.05437770111427561);
    crvIntersection->crossingPointsCrvIntersection()[6].setCrossingPointParameter(0.008635299997827261);
    crvIntersection->crossingPointsCrvIntersection()[6].setCrossingPointScale(1.00523177480844);
    crvIntersection->crossingPointsCrvIntersection()[6].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->crossingPointsCrvIntersection()[7].crossingPointPosition().set(0.1264178276616657,0.05029059015317995,0.03425567263508969);
    crvIntersection->crossingPointsCrvIntersection()[7].crossingPointUv1().set(0.5279319193225527,1.687114677445861);
    crvIntersection->crossingPointsCrvIntersection()[7].crossingPointUv2().set(5.62478739072382,0.01892432736491032);
    crvIntersection->crossingPointsCrvIntersection()[7].crossingPointTangent().set(-0.6117797523107346,0.7908821098969895,-0.01519943773639127);
    crvIntersection->crossingPointsCrvIntersection()[7].setCrossingPointParameter(0.01195146616849432);
    crvIntersection->crossingPointsCrvIntersection()[7].setCrossingPointScale(0.9924163238026075);
    crvIntersection->crossingPointsCrvIntersection()[7].setCrossingPointFlags(nCrossingPointFlags);

    crvIntersection->startLimitPoint() = OdGePoint3d(0.1341041808452103,0.04626918255341075,0.02762582792403328);
    crvIntersection->setStartLimitType(KEPRCIntersectionLimitTypeLimit);
    crvIntersection->endLimitPoint() = OdGePoint3d(0.1264178276616657,0.05029059015317995,0.03425567263508969);
    crvIntersection->setEndLimitType(KEPRCIntersectionLimitTypeLimit);
    crvIntersection->setChordalError(0.0005549915232164794);
    crvIntersection->setAngularError(0.3966089353475057);
    crvIntersection->setParameterizationDefinitionRespected(true);
  }

  blend02->boundSurface0() = bound_sur1;
  blend02->boundSurface1() = srfCyl;
  blend02->boundCurve0() = NULL;
  blend02->boundCurve1() = NULL;
  blend02->setCenterCurve(crvIntersection);
  blend02->cliffSupportingSurface0() = NULL;
  blend02->cliffSupportingSurface1() = NULL;
  blend02->setCenterCurveSens(false);
  blend02->setBoundSurfaceSens0(true);
  blend02->setBoundSurfaceSens1(false);
  blend02->setRadius0(0.00254);
  blend02->setRadius1(-0.00254);
  blend02->setParameterizationType(0);

  return blend02;
}

OdPrcSurfacePtr CreateBlend03 ()
{
  OdPrcBlend03SurfacePtr pPrcBlend03Surface = OdPrcBlend03Surface::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcBlend03Surface->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named blend03 in srfContent");

    pPrcBlend03Surface->setUVParameterization(OdPrcUVParameterization(0.007964017, 0.01745236, 0., 0.0015,false,1000.,1000.,0.,0.));

    // can add transformation if needed here
    OdPrcTransformation3d transform;
    OdGeMatrix3d mat;
    OdGeVector3d vec(-2.311, -0.045, 6.463);
    mat *= OdGeMatrix3d::scaling(1700.0);
    mat *= OdGeMatrix3d::translation(vec);
    transform.set(mat);
    pPrcBlend03Surface->setTransformation(&transform);
    // TBD

    OdDoubleArray arrParam;
    arrParam.push_back(7.964017);
    arrParam.push_back(9.646060);
    arrParam.push_back(11.372563);
    arrParam.push_back(13.077258);
    arrParam.push_back(14.164829);
    arrParam.push_back(15.581163);
    arrParam.push_back(16.964170);
    arrParam.push_back(17.452360);

    OdInt32Array arrMultip;
    arrMultip.push_back(6);
    arrMultip.push_back(3);
    arrMultip.push_back(3);
    arrMultip.push_back(3);
    arrMultip.push_back(3);
    arrMultip.push_back(3);
    arrMultip.push_back(3);
    arrMultip.push_back(6);

    OdGePoint3dArray arrPRCPoints;
    arrPRCPoints.push_back(OdGePoint3d(2.312300, -5.159834, -3.251384));
    arrPRCPoints.push_back(OdGePoint3d(2.312859, -5.159738, -3.249346));
    arrPRCPoints.push_back(OdGePoint3d(2.313448, -5.159232, -3.250630));
    arrPRCPoints.push_back(OdGePoint3d(2.311346, -5.158807, -3.250832));
    arrPRCPoints.push_back(OdGePoint3d(2.312397, -5.159279, -3.249137));
    arrPRCPoints.push_back(OdGePoint3d(2.312452, -5.158120, -3.250088));
    arrPRCPoints.push_back(OdGePoint3d(2.310349, -5.158472, -3.249680));
    arrPRCPoints.push_back(OdGePoint3d(2.311930, -5.159133, -3.248666));
    arrPRCPoints.push_back(OdGePoint3d(2.311434, -5.157744, -3.248942));
    arrPRCPoints.push_back(OdGePoint3d(2.309721, -5.158902, -3.248336));
    arrPRCPoints.push_back(OdGePoint3d(2.311678, -5.159318, -3.248080));
    arrPRCPoints.push_back(OdGePoint3d(2.310814, -5.158191, -3.247595));
    arrPRCPoints.push_back(OdGePoint3d(2.309603, -5.159527, -3.247579));
    arrPRCPoints.push_back(OdGePoint3d(2.311662, -5.159589, -3.247737));
    arrPRCPoints.push_back(OdGePoint3d(2.310717, -5.158854, -3.246833));
    arrPRCPoints.push_back(OdGePoint3d(2.309806, -5.160620, -3.246960));
    arrPRCPoints.push_back(OdGePoint3d(2.311792, -5.160077, -3.247450));
    arrPRCPoints.push_back(OdGePoint3d(2.310957, -5.160023, -3.246205));
    arrPRCPoints.push_back(OdGePoint3d(2.310331, -5.161744, -3.246945));
    arrPRCPoints.push_back(OdGePoint3d(2.312028, -5.160597, -3.247443));
    arrPRCPoints.push_back(OdGePoint3d(2.311517, -5.161231, -3.246184));
    arrPRCPoints.push_back(OdGePoint3d(2.310567, -5.162092, -3.247086));
    arrPRCPoints.push_back(OdGePoint3d(2.312125, -5.160762, -3.247509));
    arrPRCPoints.push_back(OdGePoint3d(2.311764, -5.161607, -3.246323));

    OdDoubleArray arrRail2Angles;
    arrRail2Angles.push_back(1.565043);
    arrRail2Angles.push_back(1.504230);
    arrRail2Angles.push_back(1.451011);
    arrRail2Angles.push_back(1.474211);
    arrRail2Angles.push_back(1.519005);
    arrRail2Angles.push_back(1.566353);
    arrRail2Angles.push_back(1.558732);
    arrRail2Angles.push_back(1.542876);

    OdGeVector3dArray arrTangent;
    arrTangent.push_back(OdGeVector3d(-0.000472, 0.000770, 0.000104));
    arrTangent.push_back(OdGeVector3d(-0.000225, 0.000350, 0.000035));
    arrTangent.push_back(OdGeVector3d(-0.000499, 0.000829, 0.000098));
    arrTangent.push_back(OdGeVector3d(-0.000616, 0.000420, 0.000528));
    arrTangent.push_back(OdGeVector3d(-0.000298, 0.000184, 0.000207));
    arrTangent.push_back(OdGeVector3d(-0.000636, 0.000459, 0.000522));
    arrTangent.push_back(OdGeVector3d(-0.000501, -0.000035, 0.000770));
    arrTangent.push_back(OdGeVector3d(-0.000223, -0.000015, 0.000325));
    arrTangent.push_back(OdGeVector3d(-0.000505, -0.000028, 0.000769));
    arrTangent.push_back(OdGeVector3d(-0.000217, -0.000460, 0.000762));
    arrTangent.push_back(OdGeVector3d(-0.000067, -0.000198, 0.000342));
    arrTangent.push_back(OdGeVector3d(-0.000203, -0.000485, 0.000766));
    arrTangent.push_back(OdGeVector3d(0.000002, -0.000679, 0.000609));
    arrTangent.push_back(OdGeVector3d(0.000036, -0.000298, 0.000280));
    arrTangent.push_back(OdGeVector3d(0.000025, -0.000723, 0.000615));
    arrTangent.push_back(OdGeVector3d(0.000277, -0.000832, 0.000237));
    arrTangent.push_back(OdGeVector3d(0.000140, -0.000378, 0.000111));
    arrTangent.push_back(OdGeVector3d(0.000304, -0.000892, 0.000243));
    arrTangent.push_back(OdGeVector3d(0.000463, -0.000752, -0.000215));
    arrTangent.push_back(OdGeVector3d(0.000193, -0.000355, -0.000101));
    arrTangent.push_back(OdGeVector3d(0.000487, -0.000811, -0.000211));
    arrTangent.push_back(OdGeVector3d(0.000501, -0.000669, -0.000360));
    arrTangent.push_back(OdGeVector3d(0.000202, -0.000321, -0.000167));
    arrTangent.push_back(OdGeVector3d(0.000521, -0.000724, -0.000357));

    OdDoubleArray arrRail2Deriv;
    arrRail2Deriv.push_back(-0.019119);
    arrRail2Deriv.push_back(-0.043426);
    arrRail2Deriv.push_back(-0.010798);
    arrRail2Deriv.push_back(0.034903);
    arrRail2Deriv.push_back(0.043425);
    arrRail2Deriv.push_back(0.016909);
    arrRail2Deriv.push_back(-0.026816);
    arrRail2Deriv.push_back(-0.037386);

    OdGeVector3dArray arrSecondDeriv;
    arrSecondDeriv.push_back(OdGeVector3d(-0.000167, -0.000140, 0.000288));
    arrSecondDeriv.push_back(OdGeVector3d(-0.000089, -0.000071, 0.000112));
    arrSecondDeriv.push_back(OdGeVector3d(-0.000166, -0.000146, 0.000287));
    arrSecondDeriv.push_back(OdGeVector3d(-0.000004, -0.000252, 0.000203));
    arrSecondDeriv.push_back(OdGeVector3d(0.000004, -0.000114, 0.000089));
    arrSecondDeriv.push_back(OdGeVector3d(0.000004, -0.000269, 0.000205));
    arrSecondDeriv.push_back(OdGeVector3d(0.000127, -0.000265, 0.000072));
    arrSecondDeriv.push_back(OdGeVector3d(0.000076, -0.000113, 0.000043));
    arrSecondDeriv.push_back(OdGeVector3d(0.000138, -0.000284, 0.000075));
    arrSecondDeriv.push_back(OdGeVector3d(0.000195, -0.000226, -0.000086));
    arrSecondDeriv.push_back(OdGeVector3d(0.000098, -0.000100, -0.000029));
    arrSecondDeriv.push_back(OdGeVector3d(0.000204, -0.000245, -0.000083));
    arrSecondDeriv.push_back(OdGeVector3d(0.000205, -0.000171, -0.000197));
    arrSecondDeriv.push_back(OdGeVector3d(0.000088, -0.000081, -0.000085));
    arrSecondDeriv.push_back(OdGeVector3d(0.000211, -0.000186, -0.000196));
    arrSecondDeriv.push_back(OdGeVector3d(0.000173, -0.000032, -0.000316));
    arrSecondDeriv.push_back(OdGeVector3d(0.000056, -0.000025, -0.000148));
    arrSecondDeriv.push_back(OdGeVector3d(0.000173, -0.000038, -0.000317));
    arrSecondDeriv.push_back(OdGeVector3d(0.000092, 0.000144, -0.000313));
    arrSecondDeriv.push_back(OdGeVector3d(0.000022, 0.000057, -0.000145));
    arrSecondDeriv.push_back(OdGeVector3d(0.000087, 0.000151, -0.000314));
    arrSecondDeriv.push_back(OdGeVector3d(0.000062, 0.000193, -0.000280));
    arrSecondDeriv.push_back(OdGeVector3d(0.000014, 0.000083, -0.000127));
    arrSecondDeriv.push_back(OdGeVector3d(0.000055, 0.000204, -0.000282));

    OdDoubleArray arrRail2SecondDeriv;
    arrRail2SecondDeriv.push_back(-0.029960);
    arrRail2SecondDeriv.push_back(0.003757);
    arrRail2SecondDeriv.push_back(0.029102);
    arrRail2SecondDeriv.push_back(0.018330);
    arrRail2SecondDeriv.push_back(-0.003814);
    arrRail2SecondDeriv.push_back(-0.030778);
    arrRail2SecondDeriv.push_back(-0.026091);
    arrRail2SecondDeriv.push_back(-0.016805);

    pPrcBlend03Surface->parameters() = arrParam;
    pPrcBlend03Surface->multiplicities() = arrMultip;
    pPrcBlend03Surface->position() = arrPRCPoints;
    pPrcBlend03Surface->rail2AnglesV() = arrRail2Angles;
    pPrcBlend03Surface->tangent() = arrTangent;
    pPrcBlend03Surface->rail2DerivativesV() = arrRail2Deriv;
    pPrcBlend03Surface->secondDerivatives() = arrSecondDeriv;
    pPrcBlend03Surface->rail2SecondDerivatives() = arrRail2SecondDeriv;

    pPrcBlend03Surface->setRail2ParameterV(1.5);
    pPrcBlend03Surface->setTrimVMin(0);
    pPrcBlend03Surface->setTrimVMax(1.5);
  }
  return pPrcBlend03Surface;
}

void CreateConeWithLoops (OdPrcBrepDataPtr brepData)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcConePtr pPrcCone = OdPrcCone::createObject();
      {
        OdGeMatrix3d matr;
        OdGePoint3d orPnt(0.00848600820104306, 0.01503506648794965, 0.0162750000534332);
        OdGeVector3d x(1,0,1.40002853754603e-008);
        OdGeVector3d y(0,-1,0);
        OdGeVector3d z(x.crossProduct(y));
        matr.setCoordSystem(orPnt,x,y,z);
        OdPrcTransformation3d trans;
        trans.set(matr);
        pPrcCone->setTransformation(&trans);
        pPrcCone->setBottomRadius(0.0018);
        pPrcCone->setSemiAngle(0.7853981633974617);
        pPrcCone->setUVParameterization(OdPrcUVParameterization(0,Oda2PI,-0.001799999999999952,12345));

        OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
        {
          OdPrcContentCurve &crvContent = crvCircle->contentCurve();

          // set name
          crvContent.baseGeometry().name().setName(L"named circle in crvContent");

          // add some data to params
          OdPrcParameterization curveParams(0, Oda2PI);
          crvCircle->setParameterization( curveParams );

          // can add transformation if needed here
          OdGeMatrix3d matr;
          OdGePoint3d orPnt(0.008486008203843119,0.01503506648794965,0.0160750000534332);
          OdGeVector3d x(1,0,1.40002853754603e-008);
          OdGeVector3d y(0,-1,0);
          OdGeVector3d z(x.crossProduct(y));
          matr.setCoordSystem(orPnt,x,y,z);
          OdPrcTransformation3d transform;
          transform.set(matr);
          crvCircle->setTransformation(&transform);
          // TBD
          crvCircle->setRadius(0.002);
        }

        OdPrcEdgePtr edge = OdPrcEdge::createObject();
        edge->contentWireEdge().curve() = crvCircle;

        OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
        coEdge->setEdge(edge);
        coEdge->setOrientationWithLoop(kOpposite);
        //coEdge->setOrientationUvWithLoop(kUnknown);

        OdPrcLoopPtr loop = OdPrcLoop::createObject();
        pCurFace->addLoop(loop);
        loop->addCoEdge(coEdge);
        loop->setOrientationWithSurface(kSame);

           
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {
          OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
          {
            OdPrcContentCurve &crvContent = crvCircle->contentCurve();

            // set name
            crvContent.baseGeometry().name().setName(L"named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams(0, Oda2PI);
            crvCircle->setParameterization( curveParams );

            // can add transformation if needed here
            OdGeMatrix3d matr;
            OdGePoint3d orPnt(0.00848600820104306,0.01503506648794965,0.0162750000534332);
            OdGeVector3d x(1,0,1.40002853754603e-008);
            OdGeVector3d y(0,-1,0);
            OdGeVector3d z(x.crossProduct(y));
            matr.setCoordSystem(orPnt,x,y,z);
            OdPrcTransformation3d transform;
            transform.set(matr);
            crvCircle->setTransformation(&transform);
            // TBD
            crvCircle->setRadius(0.0018);
          }

          OdPrcEdgePtr edge = OdPrcEdge::createObject();
          edge->contentWireEdge().curve() = crvCircle;

          OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
          coEdge->setEdge(edge);
          coEdge->setOrientationWithLoop(kSame);
          //coEdge->setOrientationUvWithLoop(kUnknown);

          OdPrcLoopPtr loop = OdPrcLoop::createObject();
          pCurFace->addLoop(loop);
          loop->addCoEdge(coEdge);
          loop->setOrientationWithSurface(kSame);

             
        }
      }

      pCurFace->baseSurface() = pPrcCone;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(false);
  }
}

void FillTopoBrepFace (OdPrcBrepDataPtr brepData, OdPrcSurfacePtr pSurface)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      pCurFace->baseSurface() = pSurface;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(false);
  }
}

void addLineStyleWithMaterialForBrep (OdPrcFileStructure &newStructure)
{
  OdPrcFileStructureGlobals &globalData = newStructure.fileStructureGlobals();
  // - add color
  OdPrcRgbColorArray &colorArr = globalData.colors();
  OdPrcRgbColor color;
  color.set(1,0,0);
  colorArr.push_back(color);
  color.set(0,1,0);
  colorArr.push_back(color);
  color.set(0,0,1);
  colorArr.push_back(color);

  OdPrcMaterialGenericPtr material = OdPrcMaterialGeneric::createObject();
  material->setAmbient(0);
  material->setAmbientAlpha(1);
  material->setDiffuse(1);
  material->setDiffuseAlpha(1);
  material->setEmissive(2);
  material->setEmissiveAlpha(1);
  material->setSpecular(0);
  material->setSpecularAlpha(0);
  material->setShininess(0.5);
  newStructure.addObject(material);

  OdPrcCategory1LineStyle::createByMaterial(material->objectId(), newStructure);
}

void addLineStyleForBrep (OdPrcFileStructure &newStructure, double r, double g, double b)
{
  // - add style
  OdPrcCategory1LineStyle::createByColor(r, g, b, newStructure);
}

void addGraphicDataToBrep (OdPrcFileStructure &newStructure)
{
  OdPrcFileStructureTree &tree = newStructure.fileStructureTree();
  OdPrcObjectIdArray &partArr = tree.partDefinition();
  OdPrcPartDefinitionPtr part = partArr.last().safeOpenObject(kForWrite);
  OdPrcObjectIdArray &itemArr = part->representationItem();
  OdPrcRepresentationItemPtr item = itemArr.last().safeOpenObject(kForWrite);

  item->styleId() = newStructure.fileStructureGlobals().category1LineStyles()[0];
  item->setBehaviourBitField(PRC_GRAPHICS_Show);
}

// main
void brepModelExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // create prc BrepData Model
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructurePtr pFS = pFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pRootPO);
  OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);

  OdGeExtents3d extents(OdGePoint3d(0, 0, 0), OdGePoint3d(1, 1, 1));
  pPD->boundingBox().box() = extents;
  OdPrcBrepModelPtr pBrepModel = createRI<OdPrcBrepModel>(*pFS, *pPD);
  OdPrcBrepDataPtr brepData = createBody<OdPrcBrepData>(*pFS, *pTopoContext, *pBrepModel);
  brepData->boundingBox().box() = extents;
  brepData->contentBody().setBoundingBoxBehaviour(2);

  // Add line style to globals
  if (mode == kBrepObjectMaterial)
  {
    addLineStyleWithMaterialForBrep(*pFS);
  }
  else
  {
    addLineStyleForBrep(*pFS, 1.0f, 0.0f, 0.0f);
  }

  // Add graphic
  addGraphicDataToBrep(*pFS);

  switch (mode)
  {
  case kBrepModelSphere:
    pBrepModel->name().setName(L"Sphere");
    FillTopoBrepFace(brepData,CreateSphere());
  break;
  case kBrepModelCylinder:
    pBrepModel->name().setName(L"Cylinder");
    FillTopoBrepFace(brepData,createCylinder());
  break;
  case kBrepModelCone:
    pBrepModel->name().setName(L"Cone");
    FillTopoBrepFace(brepData,CreateCone());
  break;
  case kBrepModelRuled:
    pBrepModel->name().setName(L"Ruled");
    FillTopoBrepFace(brepData,CreateRuled());
  break;
  case kBrepModelExtrusion:
    pBrepModel->name().setName(L"Extrusion");
    FillTopoBrepFace(brepData,CreateExtrusion());
  break;
  case kBrepModelFromCurves:
    pBrepModel->name().setName(L"FromCurves");
    FillTopoBrepFace(brepData,CreateFromCurves());
  break;
  case kBrepModelRevolution:
    pBrepModel->name().setName(L"Revolution");
    FillTopoBrepFace(brepData,CreateRevolution());
  break;
  case kBrepModelCylindrical:
    pBrepModel->name().setName(L"Cylindrical");
    FillTopoBrepFace(brepData,CreateCylindrical());
  break;
  case kBrepModelNURBS:
    pBrepModel->name().setName(L"NURBS");
    FillTopoBrepFace(brepData,CreateNURBS());
  break;
  case kBrepModelTorusT1:
    pBrepModel->name().setName(L"TorusT1_origin");
    FillTopoBrepFace(brepData,CreateTorus());
  break;
  case kBrepModelTorusT2:
    pBrepModel->name().setName(L"TorusT2_apple");
    FillTopoBrepFace(brepData,CreateAppleTorus());
  break;
  case kBrepModelOffset:
    pBrepModel->name().setName(L"Offset");
    FillTopoBrepFace(brepData,CreateOffset());
  break;
  case kBrepModelTransform:
    pBrepModel->name().setName(L"Transform");
    FillTopoBrepFace(brepData,CreateTransform());
  break;
  case kBrepModelPlane:
    pBrepModel->name().setName(L"Plane");
    FillTopoBrepFace(brepData,CreatePlane());
  break;
  case kBrepModelBlend01:
    pBrepModel->name().setName(L"Blend01");
    FillTopoBrepFace(brepData,CreateBlend01());
  break;
  case kBrepModelBlend02:
    pBrepModel->name().setName(L"Blend02");
    FillTopoBrepFace(brepData,CreateBlend02());
  break;
  case kBrepModelBlend03:
    pBrepModel->name().setName(L"Blend03");
    FillTopoBrepFace(brepData,CreateBlend03());
  break;
  case kBrepModelConeWithLoops:
    pBrepModel->name().setName(L"ConeWithLoops");
    CreateConeWithLoops(brepData);
  break;
  case kBrepObjectMaterial:
    pBrepModel->name().setName(L"PlaneWithMaterial");
    FillTopoBrepFace(brepData,CreatePlane());
    break;
  default:
    ODA_ASSERT(false);
  }

  ODA_VERIFY(pBrepModel->updateIsClosedFlag() == eOk);

  // export prc
  pFile->writeFile(pPrcStream);
}


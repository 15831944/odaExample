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




#ifndef OD_GE_DXF_IO
#define OD_GE_DXF_IO

#include "Ge/GeLibVersion.h"

class OdTvDbDxfFiler;

class OdGeLineSeg2d;
class OdGeCircArc2d;
class OdGeEllipArc2d;
class OdGeNurbCurve2d;
class OdGeSegmentChain2d;

/** \details
    This class reads information from and writes information to a DXF file.

    Corresponding C++ library: TD_DbEntity
    
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbGeEdgesDxfIO
{
public:
/*
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePoint2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeVector2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeMatrix2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeScale2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePoint2dArray& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeVector2dArray& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePoint3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeVector3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeMatrix3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeScale3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePoint3dArray& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeVector3dArray& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeTol& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeInterval& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeKnotVector& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeDoubleArray& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdIntArray& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCurveBoundary& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePosition2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePointOnCurve2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeLine2d& object);
*/

  /** \details
    Writes information to a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be written.
  */
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeLineSeg2d& object);

/*
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeRay2d& object);
*/

  /** \details
    Writes information to a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be written.
  */
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCircArc2d& object);
    
  /** \details
    Writes information to a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be written.
  */
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeEllipArc2d& object);

/*
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeExternalCurve2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCubicSplineCurve2d& object);
*/

  /** \details
    Writes information to a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be written.
  */
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeNurbCurve2d& object);

/*    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCompositeCurve2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeOffsetCurve2d& object);
*/

  /** \details
    Writes information to a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be written.
  */
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeSegmentChain2d& object);

/*
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePosition3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePointOnCurve3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePointOnSurface& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeLine3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeRay3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeLineSeg3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePlane& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeBoundedPlane& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCircArc3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeEllipArc3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCubicSplineCurve3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeNurbCurve3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCompositeCurve3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeOffsetCurve3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGePolyline3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeAugPolyline3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeExternalCurve3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCone& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeEllipCone& object);	// AE 03.09.2003 
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCylinder& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeEllipCylinder& object);	// AE 09.09.2003 
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeTorus& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeExternalSurface& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeOffsetSurface& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeNurbSurface& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler,const OdGeExternalBoundedSurface& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeSphere& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeBoundBlock2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeBoundBlock3d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCurveCurveInt2d& object);
    static
    void outFields(OdTvDbDxfFiler* pFiler, const OdGeCurveCurveInt3d& object);

    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePoint2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeVector2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeMatrix2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeScale2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePoint2dArray& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeVector2dArray& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePoint3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeVector3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeMatrix3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeScale3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePoint3dArray& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeVector3dArray& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeTol& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeInterval& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeKnotVector& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeDoubleArray& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdIntArray& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCurveBoundary& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePosition2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePointOnCurve2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeLine2d& object);
*/

  /** \details
    Reads information from a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be read.
  */
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeLineSeg2d& object);

/*
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeRay2d& object);
*/

  /** \details
    Reads information from a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be read.
  */
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCircArc2d& object);
    
  /** \details
    Reads information from a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be read.
  */
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeEllipArc2d& object);

/*
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeExternalCurve2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCubicSplineCurve2d& object);
*/

  /** \details
    Reads information from a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be read.
  */
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeNurbCurve2d& object);

/*
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCompositeCurve2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeOffsetCurve2d& object);
*/
  
  /** \details
    Reads information from a DXF file.

    \param pFiler [in]  Pointer to the OdTvDbDxfFiler object.
    \param object [in]  OdGe object to be read.
  */
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeSegmentChain2d& object);

/*
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePosition3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePointOnCurve3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePointOnSurface& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeLine3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeRay3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeLineSeg3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePlane& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeBoundedPlane& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCircArc3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeEllipArc3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCubicSplineCurve3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeNurbCurve3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCompositeCurve3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeOffsetCurve3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGePolyline3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeAugPolyline3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeExternalCurve3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCone& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeEllipCone& object);	// AE 03.09.2003 
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCylinder& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeEllipCylinder& object);	// AE 09.09.2003 
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeTorus& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeExternalSurface& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeOffsetSurface& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeNurbSurface& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeExternalBoundedSurface& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeSphere& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeBoundBlock2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeBoundBlock3d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCurveCurveInt2d& object);
    static
    void inFields(OdTvDbDxfFiler* pFiler, OdGeCurveCurveInt3d& object);
*/

  static const OdGeLibVersion  OdGeDxfIOVersion;
};

#endif // OD_GE_DXF_IO


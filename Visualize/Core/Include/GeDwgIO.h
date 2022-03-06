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

#ifndef OD_GE_DWG_IO_H_
#define OD_GE_DWG_IO_H_

#include "Ge/GeLineSeg3d.h"
#include "Ge/GeEllipArc3d.h"
#include "Ge/GeCircArc3d.h"
#include "Ge/GeNurbCurve3d.h"
#include "Ge/GeCompositeCurve3d.h"
//#include "Ge/GeLibVersion.h"

class OdTvDbDwgFiler;

/** \details
    This class reads information from and writes information to a .dwg file.

    Corresponding C++ library: TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdGeDwgIO
{
public:

	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePoint2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeVector2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeMatrix2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeScale2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePoint2dArray& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeVector2dArray& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePoint3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeVector3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeMatrix3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeScale3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePoint3dArray& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeVector3dArray& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeTol& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeInterval& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeKnotVector& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeDoubleArray& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdIntArray& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCurveBoundary& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePosition2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePointOnCurve2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeLine2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeLineSeg2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeRay2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCircArc2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeEllipArc2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeExternalCurve2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCubicSplineCurve2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeNurbCurve2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCompositeCurve2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeOffsetCurve2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeSegmentChain2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePosition3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePointOnCurve3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePointOnSurface& object);
	
  /** \details
    Reads information from a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be read.
  */
  static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeLine3d& object);
	
  //static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeRay3d& object);
	
  /** \details
    Reads information from a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be read.
  */
  static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeLineSeg3d& object);
	
  //static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePlane& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeBoundedPlane& object);
	
  /** \details
    Reads information from a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be read.
  */
  static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCircArc3d& object);
	
  /** \details
    Reads information from a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be read.
  */
  static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeEllipArc3d& object);
	
  //static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCubicSplineCurve3d& object);
	
  /** \details
    Reads information from a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be read.
  */
  static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCompositeCurve3d& object);
  
  //static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeOffsetCurve3d& object);
	
  /** \details
    Reads information from a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be read.
  */
  static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeNurbCurve3d& object);
	
  //static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGePolyline3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeAugPolyline3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeExternalCurve3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCone& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeEllipCone& object);	// AE 03.09.2003 
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCylinder& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeEllipCylinder& object);	// AE 09.09.2003 
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeTorus& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeExternalSurface& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeOffsetSurface& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeNurbSurface& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeExternalBoundedSurface& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeSphere& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeBoundBlock2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeBoundBlock3d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCurveCurveInt2d& object);
	//static OdResult inFields(OdTvDbDwgFiler* pFiler, OdGeCurveCurveInt3d& object);


	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePoint2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeVector2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeMatrix2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeScale2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePoint2dArray& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeVector2dArray& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePoint3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeVector3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeMatrix3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeScale3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePoint3dArray& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeVector3dArray& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeTol& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeInterval& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeKnotVector& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeDoubleArray& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdIntArray& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCurveBoundary& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePosition2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePointOnCurve2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeLine2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeLineSeg2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeRay2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCircArc2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeEllipArc2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeExternalCurve2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCubicSplineCurve2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeNurbCurve2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCompositeCurve2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeOffsetCurve2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeSegmentChain2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePosition3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePointOnCurve3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePointOnSurface& object);
	  
  /** \details
    Writes information to a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be written.
  */
  static void outFields(OdTvDbDwgFiler* pFiler, const OdGeLine3d& object);
	
  //static void outFields(OdTvDbDwgFiler* pFiler, const OdGeRay3d& object);
	
  /** \details
    Writes information to a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be written.
  */
  static void outFields(OdTvDbDwgFiler* pFiler, const OdGeLineSeg3d& object);
	
  //static void outFields(OdTvDbDwgFiler* pFiler, const OdGePlane& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeBoundedPlane& object);
	
  /** \details
    Writes information to a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be written.
  */
  static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCircArc3d& object);
	
  /** \details
    Writes information to a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be written.
  */
  static void outFields(OdTvDbDwgFiler* pFiler, const OdGeEllipArc3d& object);
	
  //static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCubicSplineCurve3d& object);
	
  /** \details
    Writes information to a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be written.
  */
  static void outFields(OdTvDbDwgFiler* pFiler, const OdGeNurbCurve3d& object);
	
  /** \details
    Writes information to a .dwg file.

    \param pFiler [in]  Pointer to the OdTvDbDwgFiler object.
    \param object [in]  OdGe object to be written.
  */
  static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCompositeCurve3d& object);
	
  //static void outFields(OdTvDbDwgFiler* pFiler, const OdGeOffsetCurve3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGePolyline3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeAugPolyline3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeExternalCurve3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCone& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeEllipCone& object);	// AE 03.09.2003 
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCylinder& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeEllipCylinder& object);	// AE 09.09.2003 
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeTorus& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeExternalSurface& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeOffsetSurface& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeNurbSurface& object);
	//static void outFields(OdTvDbDwgFiler* pFiler,const OdGeExternalBoundedSurface& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeSphere& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeBoundBlock2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeBoundBlock3d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCurveCurveInt2d& object);
	//static void outFields(OdTvDbDwgFiler* pFiler, const OdGeCurveCurveInt3d& object);

	//static const OdGeLibVersion  OdGeDwgIOVersion;
};

#endif // OD_GE_DWG_IO_H_


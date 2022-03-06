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

#ifndef _PRCCRVPOLYLINE_2D_INCLUDED_
#define _PRCCRVPOLYLINE_2D_INCLUDED_ 
 

#include "PrcCurve2d.h"

/** \details
<group PRC_Curve_Classes>

Class implements a two-dimensional polyline consisting of a set of lines defined by a sequence of points.
A polyline can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>
  
OdPrcPolyLine2d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method.
*/
class PRC_TOOLKIT OdPrcPolyLine2d : public OdPrcCurve2d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcPolyLine2d)
  //DOM-IGNORE-END

  /** \details
  Destroys the polyline object.
  */
  ~OdPrcPolyLine2d();

  /** \details
  Returns the current array of points which define the polyline.
  */
  virtual const OdGePoint2dArray &points() const;
  
  /** \details
  Sets a new points array to redefine the polyline. 
  
  \param points [in] A new points array to be set.
  \param updateParameterization [in] A flag determining whether the parameterization should be updated. Default value is false.
  
  \returns Returns eOk if points array was successfully set or an appropriate error code in the other case. 
  */
  OdResult setPoints(const OdGePoint2dArray &points, bool updateParameterization = false);
  
  /** \details
  Sets a new points array to redefine the polyline. 
  
  \param points [in] A pointer to a new array of OdGePoiont2d objects to be set as a points array. 
  \param numPoints [in] A points count. 
  \param updateParameterization [in] A flag determining whether the parameterization should be updated. Default value is false.
  
  \returns Returns eOk if the points array was successfully set or an appropriate error code in the other case. 
  */
  OdResult setPoints(const OdGePoint2d *points, OdUInt32 numPoints, bool updateParameterization = false);
  
  /** \details
  Sets a new points array to redefine the polyline. 
  
  \param points [in] A pointer to a new double array to be set as a points array. 
  \param numPoints [in] A points count. 
  \param updateParameterization [in] A flag determining whether the parameterization should be updated. Default value is false.
  
  \returns Returns eOk if the points array was successfully set or an appropriate error code in the other case. 
  */
  OdResult setPoints(const double *points, OdUInt32 numPoints, bool updateParameterization = false);
};
SMARTPTR(OdPrcPolyLine2d);

#endif // _PRCCRVPOLYLINE_2D_INCLUDED_


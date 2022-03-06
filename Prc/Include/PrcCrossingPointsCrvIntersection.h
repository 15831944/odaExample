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

#ifndef _PRCCROSSINGPOINTSCRVINTERSECTION_INCLUDED_
#define _PRCCROSSINGPOINTSCRVINTERSECTION_INCLUDED_ 
 
  
  /** \details 
  <group PRC_Curve_Classes> 
  
  Class representing crossing points data.
  */
class PRC_TOOLKIT OdPrcCrossingPointsCrvIntersection
{
private:
  OdGeVector3d m_crossing_point_tangent;
  OdGePoint2d m_crossing_point_uv_2;
  OdGePoint2d m_crossing_point_uv_1;
  OdGePoint3d  m_crossing_point_position;
  double       m_crossing_point_scale;
  double       m_crossing_point_parameter;
  OdUInt8      m_crossing_point_flags;
public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcCrossingPointsCrvIntersection)
  //DOM-IGNORE-END

  /** \details
  Returns the current crossing point tangent.
  The crossing point tangent is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new crossing point tangent.
  */
  OdGeVector3d &crossingPointTangent();
  
  /** \details
  Returns the current crossing point tangent.
  */
  const OdGeVector3d &crossingPointTangent() const;
  
  /** \details
  Returns the current parametric position on surface 2.
  The parametric position is returned as a reference to an OdGePoint2d object, therefore it can be used to set a new parametric position.
  */
  OdGePoint2d &crossingPointUv2();

  /** \details
  Returns the current parametric position on surface 2.
  */
  const OdGePoint2d &crossingPointUv2() const;

  /** \details
  Returns the current parametric position on surface 1.
  The parametric position is returned as a reference to an OdGePoint2d object, therefore it can be used to set a new parametric position.
  */
  OdGePoint2d &crossingPointUv1();

  /** \details
  Returns the current parametric position on surface 1.
  */
  const OdGePoint2d &crossingPointUv1() const;

  /** \details
  Returns the current crossing point position.
  The crossing point position is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new crossing point position.
  
  \returns Returns a reference to an OdGePoint3d object.
  */
  OdGePoint3d &crossingPointPosition();

  /** \details
  Returns the current crossing point position.
  */
  const OdGePoint3d &crossingPointPosition() const;

  /** \details
  Sets a new crossing point scale value.

  \param crossing_point_scale [in] A new value of the scale.
  */
  void setCrossingPointScale(double crossing_point_scale);

  /** \details
  Returns the current crossing point scale value.
  */
  double crossingPointScale() const;

  /** \details
  Sets a new value of the crossing point parameter.

  \param crossing_point_parameter [in] A new value of the parameter.
  */
  void setCrossingPointParameter(double crossing_point_parameter);

  /** \details
  Returns the current crossing point parameter.
  */
  double crossingPointParameter() const;

  /** \details
  Sets a new value of the crossing point flags.

  \param crossing_point_flags [in] A new value of the flags.
  */
  void setCrossingPointFlags(OdUInt8 crossing_point_flags);

  /** \details
  Returns the current crossing point flags.
  */
  OdUInt8 crossingPointFlags() const;
};

typedef  OdArray<OdPrcCrossingPointsCrvIntersection> OdPrcCrossingPointsCrvIntersectionArray;

#endif // _PRCCROSSINGPOINTSCRVINTERSECTION_INCLUDED_


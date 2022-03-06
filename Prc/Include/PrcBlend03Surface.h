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

#ifndef _PRCSRFBLEND03_INCLUDED_
#define _PRCSRFBLEND03_INCLUDED_ 
 

#include "PrcSurface.h"

/** \details 
<group PRC_Surface_Classes> 

Class stores information about a fillet surface, which is defined by a center curve, two rail curves, and an angle curve.
*/
class PRC_TOOLKIT OdPrcBlend03Surface : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcBlend03Surface)
  //DOM-IGNORE-END

  /** \details
  Destructor of Blend03Surface.
  */
  ~OdPrcBlend03Surface();
  
  /** \details
  Returns the current array of second derivatives. 
  The array of second derivatives is returned as a reference to an OdGeVector3dArray object, therefore it can be used to set new second derivatives.
  */
  OdGeVector3dArray &secondDerivatives();
  
  /** \details
  Returns the current array of second derivatives. 
  */
  const OdGeVector3dArray &secondDerivatives() const;
  
  /** \details
  Returns the current array of tangents.
  The array of tangents is returned as a reference to an OdGeVector3dArray object, therefore it can be used to set new tangents.
  */
  OdGeVector3dArray &tangent();
  
  /** \details
  Returns the current array of tangents.
  */
  const OdGeVector3dArray &tangent() const;
  
  /** \details
  Returns the current array of points.
  The array of points is returned as a reference to an OdGePoint3dArray object, therefore it can be used to set new points.
  */
  OdGePoint3dArray &position();
  
  /** \details
  Returns the current array of points.
  */
  const OdGePoint3dArray &position() const;
  
  /** \details
  Returns the current array of multiplicities.
  The array of multiplicities is returned as a reference to an OdInt32Array object, therefore it can be used to set new multiplicities.
  */
  OdInt32Array &multiplicities();
  
  /** \details
  Returns the current array of multiplicities.
  */
  const OdInt32Array &multiplicities() const;
  
  /** \details
  Returns the current array of rail2 second derivatives. 
  The array of rail2 second derivatives is returned as a reference to an OdGeDoubleArray object, therefore it can be used to set new rail2 second derivatives.
  */
  OdGeDoubleArray &rail2SecondDerivatives();
  
  /** \details
  Returns the current array of rail2 second derivatives. 
  */
  const OdGeDoubleArray &rail2SecondDerivatives() const;
  
  /** \details
  Returns the current array of rail2 V derivatives. 
  The array of rail2 V derivatives is returned as a reference to an OdGeDoubleArray object, therefore it can be used to set new rail2 V derivatives.
  */
  OdGeDoubleArray &rail2DerivativesV();
  
  /** \details
  Returns the current array of rail2 V derivatives. 
  */
  const OdGeDoubleArray &rail2DerivativesV() const;
  
  /** \details
  Returns the current array of rail2 V angles.
  The array of rail2 V angles is returned as a reference to an OdGeDoubleArray object, therefore it can be used to set new rail2 V angles.
  */
  OdGeDoubleArray &rail2AnglesV();
  
  /** \details
  Returns the current array of rail2 V angles.
  */
  const OdGeDoubleArray &rail2AnglesV() const;
  
  /** \details
  Returns the current array of parameters.
  The array of parameters is returned as a reference to an OdGeDoubleArray object, therefore it can be used to set new parameters.
  */
  OdGeDoubleArray &parameters();
  
  /** \details
  Returns the current array of parameters.
  */
  const OdGeDoubleArray &parameters() const;
  
  /** \details
  Sets a new value of the trim V maximum.

  \param trim_v_max [in] A new value of the trim V maximum to be set.
  */
  void setTrimVMax(double trim_v_max);
  
  /** \details
  Returns the current trim V maximum value.
  */
  double trimVMax() const;
  
  /** \details
  Sets a new value of the trim V minimum.

  \param trim_v_min [in] A new value of the trim V minimum.
  */
  void setTrimVMin(double trim_v_min);
  
  /** \details
  Returns the current trim V minimum value.
  */
  double trimVMin() const;
  
  /** \details
  Sets a new value of the rail2 V parameter.

  \param rail2ParameterV [in] A new value of the rail2 V parameter to be set.
  */
  void setRail2ParameterV(double rail2ParameterV);
  
  /** \details
  Returns the current rail2 V parameter value.
  */
  double rail2ParameterV() const;
};
SMARTPTR(OdPrcBlend03Surface);

#endif // _PRCSRFBLEND03_INCLUDED_


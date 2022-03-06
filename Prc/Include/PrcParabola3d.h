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

#ifndef _PRCCRVPARABOLA3d_INCLUDED_
#define _PRCCRVPARABOLA3d_INCLUDED_ 
 

#include "PrcCurve3d.h"

/** \details
<group PRC_Curve_Classes>

Class implements a three-dimensional parabolic curve (parabola). 
A parabola can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>
  
OdPrcParabola3d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method.
*/
class PRC_TOOLKIT OdPrcParabola3d : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcParabola3d)
  //DOM-IGNORE-END

  /** \details
  Destroys the parabola object.
  */
  ~OdPrcParabola3d();
  
  /** \details 
  Sets a new focal length for the parabola. 
  
  \param focal_length [in] A new focal length value to be set.
  */
  void setFocalLength(double focal_length);
  
  /** \details 
  Returns the current focal length for the parabola.
  */
  double focalLength() const;
 
  /** \details 
  Sets a parameterization type for the parabola. 
  
  \param value [in] A new value of the parameterization type to be set.
  
  \returns eOk if the new parameterization type was successfully set; otherwise, the method returns an appropriate error code.
  
  \remarks
  There are two types of parameterization which can be applied to a parabola:
  <table>
    Value  Description
    0     Parameter is an X-axis coordinate (Y-axis is the axis of the parabola).
    1     Parameter is defined by the nominal parameterization formula and is proportional to a Y-axis coordinate (X-axis is the axis of the parabola).
  </table>
  */
  OdResult setParameterizationType(OdUInt8 value);
  
  /** \details 
  Returns ther current parameterization type for the parabola.
  
  \remarks
  There are two types of parameterization which can be applied to a parabola:
  <table>
    Value  Description
    0     Parameter is an X-axis coordinate (Y-axis is the axis of the parabola).
    1     Parameter is defined by the nominal parameterization formula and is proportional to a Y-axis coordinate (X-axis is the axis of the parabola).
  </table>
  */
  OdUInt8 parameterizationType() const;
};
SMARTPTR(OdPrcParabola3d);

#endif // _PRCCRVPARABOLA3d_INCLUDED_


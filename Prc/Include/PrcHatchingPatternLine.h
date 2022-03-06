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

#ifndef _PRCHATCHINGPATTERNLINE_INCLUDED_
#define _PRCHATCHINGPATTERNLINE_INCLUDED_ 
 

/** \details 
<group PRC_Graphic_Classes> 

Class representing one hatch pattern line.
*/
class PRC_TOOLKIT OdPrcHatchingPatternLine
{
private:
  OdGeVector2d  m_offset;
  OdGePoint2d   m_start;
  OdPrcObjectId m_style;
  double        m_angle;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcHatchingPatternLine)
  //DOM-IGNORE-END

  /** \details 
  Returns the current offset vector.
  The offset vector is returned as a reference to an OdGeVector2d object, therefore it can be used to set a new offset vector.
  */
  OdGeVector2d &offset();
  
  /** \details
  Returns the current offset vector.
  */
  const OdGeVector2d &offset() const;
  
  /** \details
  Returns the current start point.
  The start point is returned as a reference to an OdGePoint2d object, therefore it can be used to set a new start point.
  */
  OdGePoint2d &start();
  
  /** \details
  Returns the current start point.
  */
  const OdGePoint2d &start() const;
  
  /** \details
  Returns the current line style.
  The line style is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a new style.
  */
  OdPrcObjectId &style();
  
  /** \details
  Returns the current line style.
  */
  const OdPrcObjectId &style() const;
  
  /** \details
  Sets a new value of the angle.

  \param angle [in] A new value of the angle to be set.
  */
  void setAngle(double angle);
  
  /** \details
  Returns the current angle value.
  */
  double angle() const;
};
typedef OdArray<OdPrcHatchingPatternLine> OdPrcHatchingPatternLineArray;

#endif // _PRCHATCHINGPATTERNLINE_INCLUDED_


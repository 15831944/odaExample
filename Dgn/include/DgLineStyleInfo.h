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



#ifndef __DG_LINESTYLEINFO_HEADER_H__
#define __DG_LINESTYLEINFO_HEADER_H__

#include "TD_PackPush.h"

#include "DgElement.h"

/** \details
    This class represents LineStyleInfo structer 

	Corresponding C++ library: TG_Db

    <group Other_Classes>
*/
class OdDgLineStyleInfo
{
  OdInt32   m_nUnknown01;
  OdUInt32  m_uModifiers;         // Modifiers flags (see mslstyle.h)
  OdUInt32  m_uUnknown02[4];
  double    m_dScale;             // Scale used at placement
  double    m_dShift;             // Shift value (distance or fraction)
  double    m_dStartWidth;        // Start width override
  double    m_dEndWidth;          // End width override

public:
  OdDgLineStyleInfo()
  {
  }
  OdDgLineStyleInfo( OdUInt32 uModifiers, double dScale, double dShift, double dStartWidth, double dEndWidth )
    : m_uModifiers(uModifiers)
    , m_dScale(dScale)
    , m_dShift(dShift)
    , m_dStartWidth(dStartWidth)
    , m_dEndWidth(dEndWidth)
  {
  }
  virtual ~OdDgLineStyleInfo()
  {
  }

  virtual OdUInt32 getModifiers() const
  {
    return m_uModifiers;
  }
  virtual void setModifiers( OdUInt32 modifiers )
  {
    m_uModifiers = modifiers;
  }

  virtual double getScale() const
  {
    return m_dScale;
  }
  virtual void setScale( double scale )
  {
    m_dScale = scale;
  }

  virtual double getShift() const
  {
    return m_dShift;
  }
  virtual void setShift( double shift )
  {
    m_dShift = shift;
  }

  virtual double getStartWidth() const
  {
    return m_dStartWidth;
  }
  virtual void setStartWidth( double startWidth )
  {
    m_dStartWidth = startWidth;
  }

  virtual double getEndWidth() const
  {
    return m_dEndWidth;
  }
  virtual void setEndWidth( double endWidth )
  {
    m_dEndWidth = endWidth;
  }
};


#include "TD_PackPop.h"

#endif /* __DG_LINESTYLEINFO_HEADER_H__ */

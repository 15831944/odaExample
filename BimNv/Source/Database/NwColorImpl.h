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

#ifndef __NWCOLORIMPL_INCLUDED__
#define __NWCOLORIMPL_INCLUDED__

#include "NwColor.h"

class OdNwColorImpl
{
public:
  OdNwColorImpl();
  OdNwColorImpl(float r, float g, float b);
  OdNwColorImpl(float a, float r, float g, float b);
public:
  virtual ~OdNwColorImpl();

public:
  static OdNwColorImpl* getImpl(const OdNwColor& NwColor);

public:
  //public implementation's methods
  float A() const;
  float R() const;
  float G() const;
  float B() const;

  ODCOLORREF ToColor() const;
  OdNwColor Multiply(const OdNwColor& color) const;
  OdNwColor Multiply(ODCOLORREF color) const;

public:
  void setA(float val);
  void setR(float val);
  void setG(float val);
  void setB(float val);

private:
  float m_r;
  float m_g;
  float m_b;
  float m_a;
};

#endif //__NWCOLORIMPL_INCLUDED__

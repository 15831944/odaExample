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

#ifndef OD_IGEXBNDSF_H
#define OD_IGEXBNDSF_H

#include "TD_PackPush.h"

#include "IGeExtSurface.h"

class OdGeExternalSurface;

class OdIGeExternalBoundedSurface : public OdIGeExtSurface
{
public:
  virtual void getBaseSurface(OdGeSurface*& pSurfaceDef) const = 0;
  virtual void getBaseSurface(OdGeExternalSurface& unboundedSurfaceDef) const = 0;
  virtual bool isExternalSurface() const = 0;
  virtual int numContours() const = 0;
  virtual void getContours(int& numContours, OdGeCurveBoundary*& contours) const = 0;
  virtual OdIGeExternalBoundedSurface& set(void* pSurfaceDef, OdGe::ExternalEntityKind surfaceKind, bool makeCopy) = 0;
  virtual OdIGeExternalBoundedSurface& operator =(const OdIGeExternalBoundedSurface& extBoundSurf) = 0;
  virtual OdIGeExternalBoundedSurface& setToOwnSurface() = 0;
};

#include "TD_PackPop.h"

#endif // OD_GEIMPXBNDSF_H

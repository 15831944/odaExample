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
#ifndef IBRELEMENT2DNODETRAVERSER_H_INCLUDED
#define IBRELEMENT2DNODETRAVERSER_H_INCLUDED

#include "ITrTemplate.h"
#include "SmartPtr.h"
class OdIBrElement2d; 
class OdIBrNode;

class OdITrElement2dNode : public OdITraverser<OdIBrElement2d, OdIBrNode>
{
public:
//   virtual OdBrErrorStatus   setElement    (const OdBrMesh2dElement2dTraverser& mesh2dElement2dTraverser) = 0;
//   virtual OdBrErrorStatus   setElement    (const OdBrElement2d& element) = 0;
//   virtual OdBrErrorStatus   getElement    (OdBrElement2d& element) const = 0;
//   virtual OdBrErrorStatus   setNode         (const OdBrNode& node) = 0;
//   virtual OdBrErrorStatus   getNode         (OdBrNode& node) const = 0;

  // TODO
  virtual OdBrErrorStatus   getSurfaceNormal(OdGeVector3d& vector) const /*=0*/ { return odbrNotImplementedYet; }
  virtual OdBrErrorStatus   getParamPoint  (OdGePoint2d& point) const /*=0*/ { return odbrNotImplementedYet; }
};

typedef OdSmartPtr<OdITrElement2dNode> OdITrElement2dNodePtr;

#endif


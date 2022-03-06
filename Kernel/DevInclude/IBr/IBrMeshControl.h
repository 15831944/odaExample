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
#ifndef IBRMESHCONTROL_H_INCLUDED
#define IBRMESHCONTROL_H_INCLUDED

class OdIBrMeshControl
{
public:
  virtual ~OdIBrMeshControl(){}

  virtual OdBrErrorStatus   setMaxSubdivisions(OdUInt32 maxSubs = 0) = 0;
  virtual OdBrErrorStatus   getMaxSubdivisions(OdUInt32& maxSubs) const = 0;
  virtual OdBrErrorStatus   setMaxNodeSpacing(double maxNodeSpace = 0) = 0;
  virtual OdBrErrorStatus   getMaxNodeSpacing(double& maxNodeSpace) const = 0;
  virtual OdBrErrorStatus   setAngTol    (double angTol = 0) = 0;
  virtual OdBrErrorStatus   getAngTol    (double& angTol) const = 0;
  virtual OdBrErrorStatus   setDistTol    (double distTol = 0) = 0;
  virtual OdBrErrorStatus   getDistTol    (double& distTol) const = 0;

protected:
  OdIBrMeshControl() {}
};


#endif

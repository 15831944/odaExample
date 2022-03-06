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

#ifndef __NWSCENESET_INCLUDED_
#define __NWSCENESET_INCLUDED_

#include "NwModelUnits.h"
#include "NwAngularUnits.h"
#include "SharedPtr.h"
#include "Ge/GeVector3d.h"

class OdNwSceneSet
{
public:
  OdNwSceneSet();
  ~OdNwSceneSet() = default;

public:
  void setLinearUnits(NwModelUnits::Enum linearUnits);
  void setAngularUnits(NwAngularUnits::Enum angularv);
  void setUpVector(const OdGeVector3d& up);
  void setNorthVector(const OdGeVector3d& north);
  void setFrontVector(const OdGeVector3d& front);
  void addModel(OdNwObjectId modelId);

public:
  NwModelUnits::Enum getLinearUnits() const;
  NwAngularUnits::Enum getAngularUnits() const;
  OdGeVector3d getUpVector() const;
  OdGeVector3d getNorthVector() const;
  OdGeVector3d getFrontVector() const;
  const OdNwObjectIdArray& getModels() const;

private:
  NwModelUnits::Enum m_linearUnits;
  NwAngularUnits::Enum m_angularUnits;
  OdGeVector3d m_upVector;
  OdGeVector3d m_northVector;
  OdGeVector3d m_frontVector;
  OdNwObjectIdArray m_aModels;
};

typedef OdSharedPtr<OdNwSceneSet> OdNwSceneSetPtr;

#endif //__NWSCENESET_INCLUDED_

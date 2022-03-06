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

#ifndef _INC_DDBRIMPENTITYBASE_3F819553015D_INCLUDED
#define _INC_DDBRIMPENTITYBASE_3F819553015D_INCLUDED

#include "Br/BrEnums.h"
#include "Br/BrMassProps.h"
#include "DbHandle.h"

class OdDbFullSubentPath;
class OdIBrFile;
class OdGePoint3d;
class OdGeLinearEnt3d;
class OdGeBoundBlock3d;
class OdIBrHit;



class OdIBrEntity
{
public:
  virtual ~OdIBrEntity() {}
  virtual bool isEqualTo( const OdIBrEntity* pIBrEntity) const 
  { 
    return this == pIBrEntity; 
  }//= 0;
  virtual bool isNull() const {return false;}//= 0;
  virtual bool isValid() const {return true;}//= 0;
  virtual OdIBrFile * getBrep() { return 0; }
  virtual bool checkEntity() const { return true; }

  virtual OdBrErrorStatus getSubentPath(OdInt32& /*type*/, OdInt32& /*index*/) const { return odbrNotImplementedYet; }

  // Geometric properties
  virtual OdBrErrorStatus getMassProps(OdBrMassProps& massProps,
    const double& dDensity,
    const double& dTolRequired,
    double&       dTolAchieved) const { return odbrNotImplementedYet; }

  virtual OdBrErrorStatus getVolume(double& dVolume,
    const double& dTolRequired,
    double&       dTolAchieved) const { return odbrNotImplementedYet; }

  virtual OdBrErrorStatus getSurfaceArea(double& dArea,
    const double& dTolRequired,
    double&       dTolAchieved) const { return odbrNotImplementedYet; }

  virtual OdBrErrorStatus getPerimeterLength(double& dLength,
    const double& dTolRequired,
    double&       dTolAchieved) const { return odbrNotImplementedYet; }

  virtual OdBrErrorStatus getBoundBlock(OdGeBoundBlock3d& block) const { return odbrNotImplementedYet; }

  virtual OdBrErrorStatus getPointContainment(const OdGePoint3d&      /*point*/,
                                              OdGe::PointContainment& /*containment*/,
                                              OdIBrEntity*&           /*brEntContainer*/,
                                              OdUInt32&               /*subentType*/) const { return odbrNotImplementedYet; }

  virtual OdBrErrorStatus getLineContainment( const OdGeLinearEnt3d& /*line*/,
                                              const OdUInt32&        /*iNumHitsWanted*/,
                                              OdUInt32&              /*iNumHitsFound*/,
                                              OdIBrHit**&            /*brHits*/) const { return odbrNotImplementedYet; }

  virtual OdUInt32 getFlags() const { return kNoFlags; }

  virtual OdBrErrorStatus getGsMarker(OdGsMarker& marker) const { return odbrNotImplementedYet; }
};

#endif /* _INC_DDBRIMPENTITYBASE_3F819553015D_INCLUDED */


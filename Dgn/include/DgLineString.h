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
#ifndef __DG_LINESTRING_H__
#define __DG_LINESTRING_H__

#include "TD_PackPush.h"

#include "DgMultiVertex.h"


//2D subtype of Line String

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLineString2d : public OdDgMultiVertex2d
{

  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLineString2d);

public:
  
  //support of WorldDraw functionality
  bool subWorldDraw( OdGiWorldDraw* pWd ) const;

  virtual OdResult subExplode( OdRxObjectPtrArray& entitySet ) const;
  static OdGePoint2d getBreakLineValue();

};

typedef OdSmartPtr<OdDgLineString2d> OdDgLineString2dPtr;


//3D subtype of Line String

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLineString3d : public OdDgMultiVertex3d
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLineString3d);

public:
  //no additions to the MultiVertex object

  //support of WorldDraw functionality
  bool subWorldDraw( OdGiWorldDraw* pWd ) const;

  virtual OdResult subExplode( OdRxObjectPtrArray& entitySet ) const;
  static OdGePoint3d getBreakLineValue();
};

typedef OdSmartPtr<OdDgLineString3d> OdDgLineString3dPtr;


#include "TD_PackPop.h"

#endif // __DG_LINESTRING_H__

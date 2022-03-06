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
#ifndef __DG_SHAPE_H__
#define __DG_SHAPE_H__

#include "TD_PackPush.h"

#include "DgMultiVertex.h"


//2D subtype of Shape

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgShape2d : public OdDgMultiVertex2d
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgShape2d);
public:

  /** \details
    The flag indicates whether the element is a solid or a hole for closed element types:
      * false is Solid
      * true is Hole
  */
  virtual bool getHoleFlag() const;
  virtual void setHoleFlag( bool bSet );

  virtual bool     isClosed() const;
  virtual bool     isPeriodic() const;

  // OdGiDrawable overridden
  bool subWorldDraw( OdGiWorldDraw* pWd ) const;
  virtual OdResult subExplode( OdRxObjectPtrArray& entitySet ) const;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pDrwTraits) const;

  virtual void        setVertexAt( OdUInt32 ind, const OdGePoint2d& pt );
  virtual OdResult    addVertex( const OdGePoint2d& pt );
  virtual OdResult    insertVertex( OdUInt32 uInsertBefore, const OdGePoint2d& pt );
  virtual void        removeAllVertices();
  virtual void        removeVertexAt( OdUInt32 index );
  virtual void        removeLastVertex();
  virtual OdResult    reverseCurve();
  virtual OdResult    setFromOdGeCurve ( const OdGeCurve2d& geCurve, const OdGeTol& tol = OdGeContext::gTol );
};

typedef OdSmartPtr<OdDgShape2d> OdDgShape2dPtr;


//3D subtype of Shape

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgShape3d : public OdDgMultiVertex3d
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgShape3d);
public:

  /** \details
    The flag indicates whether the element is a solid or a hole for closed element types:
      * false is Solid
      * true is Hole
  */
  virtual bool getHoleFlag() const;
  virtual void setHoleFlag( bool bSet );

  virtual bool     isClosed() const;
  virtual bool     isPeriodic() const;

  // OdGiDrawable overridden
  bool subWorldDraw( OdGiWorldDraw* pWd ) const;
  virtual OdResult subExplode( OdRxObjectPtrArray& entitySet ) const;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pDrwTraits) const;

  virtual void        setVertexAt( OdUInt32 ind, const OdGePoint3d& pt );
  virtual OdResult    addVertex( const OdGePoint3d& pt );
  virtual OdResult    insertVertex( OdUInt32 uInsertBefore, const OdGePoint3d& pt );
  virtual void        removeAllVertices();
  virtual void        removeVertexAt( OdUInt32 index );
  virtual void        removeLastVertex();
  virtual OdResult    reverseCurve();
  virtual OdResult    setFromOdGeCurve ( const OdGeCurve3d& geCurve, OdGeVector3d *normal = NULL, const OdGeTol& tol = OdGeContext::gTol );
};

typedef OdSmartPtr<OdDgShape3d> OdDgShape3dPtr;


#include "TD_PackPop.h"

#endif // __DG_SHAPE_H__

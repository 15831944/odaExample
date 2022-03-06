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

#ifndef _ODTV_GIDRAWABLEPE_H_INCLUDED_
#define _ODTV_GIDRAWABLEPE_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvExtentsSpaceTree.h"
#include "TvEntityImpl.h"

/** \details
    This class is the protocol extension for all graphical objects, both transient and persistent.

    \remarks
    This interface must be implemented in the case of ability to perform selection procedure by drawable itself

    <group OdGi_Classes>
*/
class OdTvGiDrawablePE : public OdGiDrawableSelectPE
{
protected:
  OdTvGiDrawablePE();
public:
  ODRX_DECLARE_MEMBERS(OdTvGiDrawablePE);

  /** \details
  Return true if a drawable can perform selection inside 'pathNode' itself.

  \returns
  Returns true if and only if the drawable can perform selection inside 'pathNode' itself

  \remarks
  The default implementation does nothing and return false. This function can be
  overridden in custom classes.

  \param pathNode         [in]   Currently processing GiDrawable objects graph.
  nMarkersCovered  [out]  Number of markers which is covered by drawables's own selection procedure
  */
  virtual bool canSelect(const OdGiPathNode& pathNode, OdGsMarker& nMarkersCovered) const;

  /** \details
  Runs selection procedure inside pathNode.

  \returns
  Returns nothing.

  \remarks
  The default implementation does nothing. This function can be overridden in custom classes.

  \param pathNode             [in]  Currently processing GiDrawable objects graph.
  pPoly                [in]  A pointer to an array of selection points in the eye coordinate space
  nbPolyPts            [in]  A quantity of selection points
  tol                  [in]  Tolerance
  transformWorldToEye  [in]  Transformation matrix from world coordinate systen to the eye coordinate system
  bNeedEyeDepth        [in]  Indicates that it is need to calculate the depth of the selected sub object in the ECS (eye coordinate system)
  pSelectionReactor    [in]  Selection callback pointer.
  */
  virtual void select(const OdGiPathNode& pathNode, const OdGePoint2d* pPoly, OdUInt32 nbPolyPts, const OdGeTol& tol,
                      const OdGeMatrix3d& transformWorldToEye, bool bNeedEyeDepth, OdGiDrawablePESelectionReactor* pSelectionReactor) const;

};

#include "TD_PackPop.h"

#endif //_ODTV_GIDRAWABLEPE_H_INCLUDED_

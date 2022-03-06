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

#ifndef _PRCCRVCURVE3D_INCLUDED_
#define _PRCCRVCURVE3D_INCLUDED_ 
 

#include "PrcCurve.h"
#include "Ge/GeCurve3d.h"
#include "PrcTransformation3d.h"

class OdPrcCurve3d;
SMARTPTR(OdPrcCurve3d);

/** \details
<group PRC_Curve_Classes>

Class implements a three-dimensional curve.
*/
class PRC_TOOLKIT OdPrcCurve3d : public OdPrcCurve
{
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE_CRV(OdPrcCurve3d)
  //DOM-IGNORE-END

  /** \details
  Returns the current transformation matrix for the curve.
  */
  const OdGeMatrix3d &getGeMatrix3d() const;

  /** \details
  Sets a new transformation for the curve.

  \param trans [in] A pointer to a new transformation object to be set.

  \returns Returns eOk if a new transformation was successfully set or an appropriate error code in the other case.
  */
  OdResult setTransformation(const OdPrcTransformation3d* trans);

  /** \details
  Returns the current transformation for the curve.
  */
  const OdPrcTransformation3d *transformation() const;

  /** \details
  Returns the current curve's 3D flag value. 
  The flag is equal to true if curve is a 3D object or is equal to false in the other case.
  */
  virtual bool is3d() const;

  /** \details
  Returns the current curve data. 
  
  \param pGeCurve [out] A reference to an OdGeCurve3d object pointer to store curve information.
  \param tol [in] Tolerance. Default value is equal to OdGeContext::gTol.
  
  \returns Returns eOk if common curve information was successfully passed back to the calling subroutine or returns an appropriate error code in the other case.
  */
  virtual OdResult getOdGeCurve(OdGeCurve3d*& pGeCurve, const OdGeTol& tol = OdGeContext::gTol) const;
  
  /** \details
  Sets a new instance of the curve data.
  
  \param geCurve [in] A reference to an OdGeCurve3d object containing curve information to be set.
  \param tol [in] Tolerance. Default value is equal to OdGeContext::gTol.
  
  \returns Returns eOk if common curve information was successfully set or an appropriate error code in the other case.
  */
  virtual OdResult setFromOdGeCurve(const OdGeCurve3d& geCurve, const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Creates new 3d curve instance from OdGeCurve3d.
  
    \param geCurve       [in] A reference to an OdGeCurve3d object containing curve information to be set.
    \param pPrcCurve [in/out] Pointer object to which the result will be written.
    \param tol           [in] Tolerance. Default value is equal to OdGeContext::gTol.
    \returns Returns eOk if common curve information was successfully set or an appropriate error code in the other case.
  */
  static OdResult createFromOdGeCurve( const OdGeCurve3d& geCurve, OdPrcCurve3dPtr& pPrcCurve, const OdGeTol& tol = OdGeContext::gTol );
};

#endif // _PRCCRVCURVE3D_INCLUDED_


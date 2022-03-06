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

#ifndef _PRCCRVCURVE2D_INCLUDED_
#define _PRCCRVCURVE2D_INCLUDED_ 
 

#include "PrcCurve.h"
#include "Ge/GeCurve2d.h"
#include "PrcTransformation2d.h"

class OdPrcCurve2d;
SMARTPTR(OdPrcCurve2d);

/** \details
<group PRC_Curve_Classes>

Class implements a two-dimensional curve.
*/
class PRC_TOOLKIT OdPrcCurve2d : public OdPrcCurve
{
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE_CRV(OdPrcCurve2d)
  //DOM-IGNORE-END

  /** \details
  Returns the current transformation matrix for the curve.
  */
    const OdGeMatrix2d &getGeMatrix2d() const;

  /** \details
  Sets a new transformation for the curve.

  \param trans [in] A pointer to the transformation object.

  \returns Returns eOk if the new transformation was successfully set or an appropriate error code in the other case.
  */
  OdResult setTransformation(const OdPrcTransformation2d* trans);

  /** \details
  Returns the  current transformation for the curve.
  */
  const OdPrcTransformation2d *transformation() const;

  /** \details
  Returns the current curve's 3D flag value.
  The flag is equal to true if the curve is a 3D object or is equal to false in the other case.
  */
  virtual bool is3d() const;

  /** \details
  Returns the current curve data.
  
  \param pGeCurve [out] A reference to an OdGeCurve2d object pointer to store curve information.
  \param tol [in] Tolerance. Default value is equal to OdGeContext::gTol.
  
  \returns Returns eOk if common curve information was successfully passed back to the calling subroutine or returns an appropriate error code in the other case.
  */
  OdResult getOdGeCurve(OdGeCurve2d*& pGeCurve, const OdGeTol& tol = OdGeContext::gTol) const;
  
  /** \details
    Sets a new instance of the curve data.
    
    \param geCurve [in] A reference to an OdGeCurve2d object containing curve information to be set.
    \param tol [in] Tolerance. Default value is equal to OdGeContext::gTol.
    
    \returns Returns eOk if common curve information was successfully set or an appropriate error code in the other case.
  */
  OdResult setFromOdGeCurve(const OdGeCurve2d& geCurve, const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Creates new 2d curve instance from OdGeCurve2d.
  
    \param geCurve       [in] A reference to an OdGeCurve2d object containing curve information to be set.
    \param pPrcCurve [in/out] Pointer object to which the result will be written.
    \param tol           [in] Tolerance. Default value is equal to OdGeContext::gTol.
    \returns Returns eOk if common curve information was successfully set or an appropriate error code in the other case.
  */
  static OdResult createFromOdGeCurve( const OdGeCurve2d& geCurve, OdPrcCurve2dPtr& pPrcCurve, const OdGeTol& tol = OdGeContext::gTol );
};

#endif // _PRCCRVCURVE2D_INCLUDED_


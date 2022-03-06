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

#ifndef _PRCTRANSFORMATION2D_INCLUDED_
#define _PRCTRANSFORMATION2D_INCLUDED_ 
 
#include "Ge/GeMatrix2d.h"

/** \details 
<group PRC_Miscellaneous_Classes>

Class represents a 2D transformation defined by a 3x3-sized matrix. 
*/
class PRC_TOOLKIT OdPrcTransformation2d
{
private:
  OdInt8       m_behaviour;
  OdGeMatrix2d m_mat;
  
  OdInt8 calculateBehaviour2d(const OdGeTol& tol = OdGeContext::gTol) const;
  
protected:
  /** \details
  Sets a new behavior for the 2D transformation.

  \param value [in] An new behavior value to be set.
  
  \returns Returns eOk if a new behavior was successfully applied to the 2D transformation entity or an appropriate error code in the other case.
  */
  OdResult setBehaviour(OdInt8 value);

  /** \details
  Returns the current value of the 2D transformation behavior.
  */
  OdInt8 behaviour() const;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcTransformation2d);
  //DOM-IGNORE-END
  
  /** \details
  Returns the current matrix of the 2D transformation.
  */
  const OdGeMatrix2d &getGeMatrix2d() const;

  /** \details
  Sets a new matrix of the 2D transformation.

  \param geMatrix [in] A new matrix to be set.
  \param tol [in] Tolerance. Default value is equal to OdGeContext::gTol.
  
  \returns Returns eOk if a new matrix was successfully applied to the 2D transformation entity or an appropriate error code in the other case.
  */
  OdResult set(const OdGeMatrix2d& geMatrix, const OdGeTol& tol = OdGeContext::gTol);

  /** \details
  Assigns another 2D transformation to this 2D transformation object.
  
  \param trans [in] A reference to another 2D transformation entity to assign. 
  */
  OdPrcTransformation2d& operator= (const OdPrcTransformation2d &trans);

};

#endif // _PRCTRANSFORMATION2D_INCLUDED_

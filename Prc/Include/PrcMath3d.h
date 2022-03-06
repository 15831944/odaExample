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

#ifndef _PRCMATH3D_INCLUDED_
#define _PRCMATH3D_INCLUDED_ 
 

#include "PrcMath.h"

SMARTPTR(OdPrcMath3d);

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Base class for three-dimensional mathematical evaluations.
*/
class PRC_TOOLKIT OdPrcMath3d : public OdPrcMath
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_MATH(OdPrcMath3d);
  //DOM-IGNORE-END

  /** \details
  The base evaluation method which returns the evaluated parameter as a reference to an OdGePoint3d object.

  \param ptBase [in] A parameter to be evaluated.
  */
  virtual OdGePoint3d transformPoint( const OdGePoint3d& ptBase ) const;

  /** \details
  Reads a mathematical evaluation from a specified filer stream.

  \param pStream [in] A pointer to the stream (file stream, memory stream) to read the evaluation from.
  */
  static OdPrcMath3dPtr read(OdPrcCompressedFiler *pStream);
};

#endif // _PRCMATH3D_INCLUDED_


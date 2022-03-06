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

#ifndef _PRCEXTENTSCALCULATOR_INCLUDED_
#define _PRCEXTENTSCALCULATOR_INCLUDED_
 
/** \details
Contains declarations for extents calculation functionality. 
*/
namespace OdPrcExtentsCalculator
{
  /** \details
    Calculates extents for a specified PRC file contents.
    \param pPRCFile [in] A smart pointer to a PRC file object.
    \returns Returns an OdGeExtents3d object that represents three-dimensional extents of the PRC model contents.
  */
  OdGeExtents3d OD_TOOLKIT_EXPORT calculateExtents(OdPrcFilePtr pPRCFile);
}

#endif // _PRCEXTENTSCALCULATOR_INCLUDED_


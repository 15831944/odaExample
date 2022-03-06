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

#ifndef _PRCHATCHINGPATTERN_INCLUDED_
#define _PRCHATCHINGPATTERN_INCLUDED_ 
 

#include "PrcHatchingPatternLine.h"
#include "PrcFillPattern.h"

/** \details 
<group PRC_Graphic_Classes> 

Class stores data for filling hatches with patterns.
*/
class PRC_TOOLKIT OdPrcHatchingPattern : public OdPrcFillPattern
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcHatchingPattern);
  //DOM-IGNORE-END

  /** \details
  Returns the current array of hatch pattern lines.
  The hatch pattern lines array is returned as a reference to an OdPrcHatchingPatternLineArray object, therefore it can be used to set new hatch pattern lines.
  */
  OdPrcHatchingPatternLineArray &hatchingPatternLine();
  
  /** \details
  Returns the current array of hatch pattern lines.
  */
  const OdPrcHatchingPatternLineArray &hatchingPatternLine() const;
};
SMARTPTR(OdPrcHatchingPattern);

#endif // _PRCHATCHINGPATTERN_INCLUDED_


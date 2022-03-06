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

#ifndef _PRCLINEPATTERN_INCLUDED_
#define _PRCLINEPATTERN_INCLUDED_ 
 

#include "PrcBase.h"
SMARTPTR(OdPrcLinePattern);

/** \details 
<group PRC_Graphic_Classes> 

Class stores data for displaying dashes and gaps.
*/
class PRC_TOOLKIT OdPrcLinePattern : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcLinePattern)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of lengths of dashes and gaps.
  The array of lengths of dashes and gaps is returned as a reference to an OdGeDoubleArray object, therefore it can be used to set new lengths.
  */
  OdGeDoubleArray &length();
  
  /** \details
  Returns the current array of lengths of dashes and gaps.
  */
  const OdGeDoubleArray &length() const;
  
  /** \details
  Sets a new phase value for gaps inside the dashes.

  \param phase [in] A new phase value to be set.
  */
  void setPhase(double phase);
  
  /** \details
  Returns the current phase value.
  Phase value determines the offset of gaps inside the dashes.
  */
  double phase() const;
  
  /** \details
  Sets a new value of the real length.
  The real length flag indicates whether the pattern is scaled with the view (if true).

  \param is_real_length [in] A new value of the flag to be set.
  */
  void setIsRealLength(bool is_real_length);
  
  /** \details
  Returns the current value of the real length flag.
  The real length flag indicates whether the pattern is scaled with the view (if true).
  */
  bool isRealLength() const;
};

typedef OdArray<OdPrcLinePattern> OdPrcLinePatternArray;

#endif // _PRCLINEPATTERN_INCLUDED_


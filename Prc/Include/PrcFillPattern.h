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

#ifndef _PRCFILLPATTERN_INCLUDED_
#define _PRCFILLPATTERN_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcBase.h"

SMARTPTR(OdPrcFillPattern);

/** \details 
<group PRC_Graphic_Classes> 

Class stores data of fill patterns.
*/
class PRC_TOOLKIT OdPrcFillPattern : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFillPattern);
  //DOM-IGNORE-END

  /** \details
  Returns the next pattern identifier. The identifier is returned as a reference therefore it can be changed and affects the pattern object. 
  */
  OdPrcObjectId &nextPattern();

  /** \details
  Returns the next pattern identifier.
  */
  const OdPrcObjectId &nextPattern() const;

  /** \details
  Reads a fill pattern from a specified data stream and returns a pointer to an OdPrcFillPattern object.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read data from.
  */
  static OdPrcFillPatternPtr read(OdPrcCompressedFiler *pStream);

  /** \details
  Reads a fill pattern array from a data stream to an array of smart pointers to OdPrcFillPattern objects.

  \param array [out] A reference to an array of two-dimensional display styles.
  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read data from.
  */
  static void readArray(OdPrcFillPatternPtrArray &array, OdPrcCompressedFiler *pStream);
};

#endif // _PRCFILLPATTERN_INCLUDED_


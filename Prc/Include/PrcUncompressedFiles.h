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

#ifndef _PRCUNCOMPRESSEDFILES_INCLUDED_
#define _PRCUNCOMPRESSEDFILES_INCLUDED_ 
 

#include "PrcUncompressedFiler.h"
#include "OdBinaryData.h"

/** \details 
<group PRC_Input_Output_Operations>

Class implements a function of embedding private data in a .prc file. 
*/
class PRC_TOOLKIT OdPrcUncompressedFiles
{
private:
  OdArray<OdBinaryData> m_file_contents;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_UIO(OdPrcUncompressedFiles)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of data embedded in the .prc file.
  Embedded data is returned as a reference to an OdArray object, therefore it can be used to set a new array or modify the existing one.
  */
  OdArray<OdBinaryData> &fileContents();
  
  /** \details
  Returns the current array of data embedded in the .prc file.
  */
  const OdArray<OdBinaryData> &fileContents() const;
};

#endif // _PRCUNCOMPRESSEDFILES_INCLUDED_


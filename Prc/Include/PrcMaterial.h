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

#ifndef _PRCMATERIAL_INCLUDED_
#define _PRCMATERIAL_INCLUDED_ 
 

#include "PrcBase.h"

SMARTPTR(OdPrcMaterial);

/** \details 
<group PRC_Graphic_Classes> 

Class implements operations with a material.
*/
class PRC_TOOLKIT OdPrcMaterial : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcMaterial)
  //DOM-IGNORE-END

  /** \details
  Reads information about a material from a .prc file stream and returns the created material entity identifier.

  \param pStream [in] A pointer to a stream (file stream, memory stream) to read from.
  */
  static OdPrcObjectId read(OdPrcCompressedFiler *pStream);

  /** \details
  Reads information about an array of materials from a .prc file stream and returns the identifiers array for created material entities.

  \param array [out] A reference to an identifiers array for storing identifiers of create material entities.
  \param pStream [in] A pointer to a stream (file stream, memory stream) to read from.
  */
  static void readArray(OdPrcObjectIdArray &array, OdPrcCompressedFiler *pStream);

  /** \details 
  Retrieves the current true color of the material object.
  \returns An OdCmEntityColor object that represents the material true color.
  */
  virtual OdCmEntityColor getTrueColor() const = 0;
};

#endif // _PRCMATERIAL_INCLUDED_


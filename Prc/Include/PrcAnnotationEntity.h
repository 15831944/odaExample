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

#ifndef _PRCANNOTATIONENTITY_INCLUDED_
#define _PRCANNOTATIONENTITY_INCLUDED_ 
 

#include "PrcBaseWithGraphics.h"
#include "PrcUserData.h"

SMARTPTR(OdPrcAnnotationEntity);

/** \details 
<group PRC_Markup_Classes>

Class implements an annotation entity.
*/
class PRC_TOOLKIT OdPrcAnnotationEntity : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcAnnotationEntity)
  //DOM-IGNORE-END
  
  /** \details
    Returns current user defined data.
    User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user data to the annotation.
  */
  OdPrcUserData &userData();

  /** \details
    Returns current user defined data.
  */
  const OdPrcUserData &userData() const;

  /** \details
    Reads annotation data from a specified compressed input stream.

    \param pStream [in] A pointer to an input stream (file or memory stream) to read from.

    \returns Returns an annotation entity identifier (OdPrcObjectId object).
  */ 
  static OdPrcObjectId read(OdPrcCompressedFiler *pStream);
  
  /** \details
    Reads annotation data from a specified compressed input stream.

    \param array [out] A reference to an entity identifiers array to store read information.
    \param pStream [in] A pointer to an input stream (file or memory stream) to read from.
  */
  static void readArray(OdPrcObjectIdArray &array, OdPrcCompressedFiler *pStream);
};

#endif // _PRCANNOTATIONENTITY_INCLUDED_


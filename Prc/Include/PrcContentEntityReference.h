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

#ifndef _PRCCONTENTENTITYREFERENCE_INCLUDED_
#define _PRCCONTENTENTITYREFERENCE_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcBaseWithGraphics.h"
#include "PrcReferenceData.h"

SMARTPTR(OdPrcContentEntityReference);

/** \details 
<group PRC_Miscellaneous_Classes> 

Class defines information about the reference to any entity that can be referenced.
*/
class PRC_TOOLKIT OdPrcContentEntityReference : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcContentEntityReference)
  //DOM-IGNORE-END

  /** \details
  Returns the current reference information.
  The reference information is returned as a reference to an OdPrcReferenceData object, therefore it can be used to set new reference information.
  */
  OdPrcReferenceData &referenceData();
  
  /** \details
  Returns the current reference information.
  */
  const OdPrcReferenceData &referenceData() const;
  
  /** \details
  Returns the current local coordinate system identifier.
  Local coordinate system identifier is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a new identifier.
  */
  OdPrcObjectId &localCoordinateSystem();
  
  /** \details
  Returns the current local coordinate system identifier.
  */
  const OdPrcObjectId &localCoordinateSystem() const;
};

#endif // _PRCCONTENTENTITYREFERENCE_INCLUDED_


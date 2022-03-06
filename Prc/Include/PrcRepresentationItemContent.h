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

#ifndef _PRCREPRESENTATIONITEMCONTENT_INCLUDED_
#define _PRCREPRESENTATIONITEMCONTENT_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcBaseWithGraphics.h"
#include "PrcBaseTessData.h"

/** \details 
<group PRC_Representation_Item_Classes> 

Class representing common data for all representation item entities. 
*/
class PRC_TOOLKIT OdPrcRepresentationItemContent : public OdPrcBaseWithGraphics
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcRepresentationItemContent)
  //DOM-IGNORE-END

  /** \details
  Returns current tessellation data.
  Tessellation data is returned as a reference to an OdPrcBaseTessDataPtr object, therefore it can be used to set new tessellation data.
  */
  OdPrcBaseTessDataPtr &tessellation();
  
  /** \details
  Returns current tessellation data.
  */
  const OdPrcBaseTessDataPtr &tessellation() const;

  /** \details
  Returns an identifier of the local coordinate system.
  The item is returned as a referenece to an OdPrcObjectId therefore it can be used to change the identifier.
  */
  OdPrcObjectId &localCoordinateSystemID();

  /** \details
  Returns an identifier of the local coordinate system.
  */
  const OdPrcObjectId &localCoordinateSystemID() const;
};

#endif // _PRCREPRESENTATIONITEMCONTENT_INCLUDED_


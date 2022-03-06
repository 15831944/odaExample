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

#ifndef _PRCANNOTATIONITEM_INCLUDED_
#define _PRCANNOTATIONITEM_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcAnnotationEntity.h"

class OdPrcCompressedFiler;
  
/** \details 
<group PRC_Markup_Classes> 

Class implements a single annotation item.
*/
class PRC_TOOLKIT OdPrcAnnotationItem : public OdPrcAnnotationEntity
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcAnnotationItem);
  //DOM-IGNORE-END

  /** \details
    Returns current markup data.
    Markup data is returned as a reference to an OdPrcObjectId object, therefore it can be used to set markup data of the annotation item.
  */
  OdPrcObjectId &markup();

  /** \details
    Returns current markup data.
  */
  const OdPrcObjectId &markup() const;

protected:
  virtual OdUInt32 subSetAttributes (OdGiDrawableTraits * traits) const;
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};
SMARTPTR(OdPrcAnnotationItem);

#endif // _PRCANNOTATIONITEM_INCLUDED_


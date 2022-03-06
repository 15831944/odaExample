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

#ifndef _PRCMARKUPS_INCLUDED_
#define _PRCMARKUPS_INCLUDED_ 
 

#include "PrcMarkupLinkedItem.h"
#include "PrcMarkupLeader.h"
#include "PrcMarkup.h"
#include "PrcAnnotationEntity.h"

class OdPrcCompressedFiler;

/** \details 
<group PRC_Markup_Classes> 

Class stores data connected with markups.
*/
class PRC_TOOLKIT OdPrcMarkups
{
private:
  OdPrcObjectIdArray m_annotation_entities;
  OdPrcObjectIdArray m_markups; //OdPrcMarkupPtr
  OdPrcObjectIdArray m_leaders; // OdPrcMarkupLeaderPtr
  OdPrcObjectIdArray m_linked_item; // OdPrcMarkupLinkedItemPtr

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcMarkups)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of annotation entity identifiers.
  The identifiers array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new annotation entity identifiers.
  */
  OdPrcObjectIdArray &annotationEntities();
  
  /** \details
  Returns the current array of annotation entity identifiers.
  */
  const OdPrcObjectIdArray &annotationEntities() const;
  
  /** \details
  Returns the current array of markup identifiers.
  The identifiers array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new markup entity identifiers.
  */
  OdPrcObjectIdArray &markups();
  
  /** \details
  Returns the current array of markup identifiers.
  */
  const OdPrcObjectIdArray &markups() const;
  
  /** \details
  Returns the current array of leader identifiers.
  The identifiers array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new leader entity identifiers.
  */
  OdPrcObjectIdArray &leaders();
  
  /** \details
  Returns the current array of leader identifiers.
  */
  const OdPrcObjectIdArray &leaders() const;
  
  /** \details
  Returns the current array of linked item identifiers.
  The identifiers array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new linked item identifiers.
  */
  OdPrcObjectIdArray &linkedItem();
  
  /** \details
  Returns the current array of linked item identifiers.
  */
  const OdPrcObjectIdArray &linkedItem() const;
};

typedef OdArray<OdPrcMarkups> OdPrcMarkupsArray;

#endif // _PRCMARKUPS_INCLUDED_


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

#ifndef _PRCTOPOITEM_INCLUDED_
#define _PRCTOPOITEM_INCLUDED_ 
 

#include "PrcBaseTopology.h"

SMARTPTR(OdPrcTopoItem);
class OdPrcTopoItemImpl;

/** \details 
<group PRC_Topology_Classes> 

A base class that is used for representing all topological entities. 
*/
class PRC_TOOLKIT OdPrcTopoItem : public OdRxObject
{
protected:
  OdPrcTopoItem(OdPrcTopoItemImpl *pImpl);
  virtual ~OdPrcTopoItem();

  /** \details
  Reads topological entity data from a specified input stream, creates a topological entity, and returns a smart pointer to an OdPrcTopoItem object.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  static OdPrcTopoItemPtr read(OdPrcCompressedFiler *pStream);
  
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_BASE_MEMBERS(OdPrcTopoItem)
  //DOM-IGNORE-END
  
  /** \details
  Reads topological entity data from a specified input stream, creates a topological entity, and returns a smart pointer to an OdPrcTopoItem object.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  static OdPrcTopoItemPtr readPtr(OdPrcCompressedFiler *pStream);

  /** \details
  Writes topological entity data to a specified output stream.

  \param pTopoItem [in] A smart pointer to an OdPrcTopoItem object.
  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  */
  static void writePtr(const OdPrcTopoItem *pTopoItem, OdPrcCompressedFiler *pStream);

};

#endif // _PRCTOPOITEM_INCLUDED_


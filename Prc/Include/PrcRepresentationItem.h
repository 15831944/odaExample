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

#ifndef _PRCREPRESENTATIONITEM_INCLUDED_
#define _PRCREPRESENTATIONITEM_INCLUDED_ 
 

#include "PrcUserData.h"
#include "PrcRepresentationItemContent.h"
class OdPrcBody;
SMARTPTR(OdPrcRepresentationItem);

/** \details 
<group PRC_Representation_Item_Classes> 

An abstract class of representation items. This class is the base for various representation item classes. 
*/
class PRC_TOOLKIT OdPrcRepresentationItem : public OdPrcRepresentationItemContent
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcRepresentationItem)
  //DOM-IGNORE-END

  /** \details
  Returns current user defined data.
  User defined data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user defined data.
  */
  OdPrcUserData &userData();

  /** \details
  Returns current user defined data.
  */
  const OdPrcUserData &userData() const;

  /** \details
  Reads representation item data from a specified input stream, creates a representation item, and returns its identifier.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  static OdPrcObjectId read(OdPrcCompressedFiler *pStream);

  /** \details
  Reads data of representation items from a specified input stream, creates representation items, and creates an array of its identifiers.

  \param array [out] An array of data about representation items.
  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  static void readArray(OdPrcObjectIdArray &array, OdPrcCompressedFiler *pStream);

  /** \details
  Sets a reference to a new representation item's body.

  \param pBody [in] A pointer to an OdPrcBody object to be referenced.
  */
  void setReferenceToBody(const OdPrcBody *pBody);

  /** \details
  Returns the identifier of the current representation item's body.
  */
  OdPrcObjectId getReferenceToBodyId(void) const;

//DOM-IGNORE-BEGIN
protected:
  virtual bool subWorldDraw(OdGiWorldDraw * pWd) const;
//DOM-IGNORE-END
};

#endif // _PRCREPRESENTATIONITEM_INCLUDED_


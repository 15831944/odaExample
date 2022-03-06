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

#ifndef _PRCMARKUPLINKEDITEM_INCLUDED_
#define _PRCMARKUPLINKEDITEM_INCLUDED_ 
 

#include "PrcContentExtendedEntityReference.h"
#include "PrcUserData.h"

SMARTPTR(OdPrcMarkupLinkedItem);

/** \details 
<group PRC_Markup_Classes> 

Class stores data of establishing a cross reference between markup and geometry.
*/
class PRC_TOOLKIT OdPrcMarkupLinkedItem : public OdPrcContentExtendedEntityReference
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcMarkupLinkedItem)
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
  Sets a new value of the deletion flag. 
  The deletion flag indicates whether the leader will be deleted after deleting the referenced entity (if true).

  \param leader_delete_control [in] A new value of the flag to be set.
  */
  void setLeaderDeleteControl(bool leader_delete_control);
  
  /** \details
  Returns the current value of the deletion flag.
  The deletion flag indicates whether the leader will be deleted after deleting the referenced entity (if true).
  */
  bool leaderDeleteControl() const;
  
  /** \details
  Sets a new value of the showing flag. 
  The showing flag indicates whether the leader is shown when the referenced entity is shown. The flag is equal to true if the leader is shown or to false if the leader is not shown.

  \param leader_show_control [in] A new value of the flag to be set.
  */
  void setLeaderShowControl(bool leader_show_control);
  
  /** \details
  Returns the current value the showing flag.
  The showing flag indicates whether the leader is shown when the referenced entity is shown. The flag is equal to true if the leader is shown or to false if the leader is not shown.
  */
  bool leaderShowControl() const;
  
  /** \details
  Sets a new value of the markup deletion flag. 
  The markup deletion flag indicates whether the markup will be deleted after deleting the referenced entity (if true).

  \param markup_delete_control [in] A new value of the flag to be set.
  */
  void setMarkupDeleteControl(bool markup_delete_control);
  
  /** \details
  Returns the current value of the markup deletion flag.
  The markup deletion flag indicates whether the markup will be deleted after deleting the referenced entity (if true).
  */
  bool markupDeleteControl() const;
  
  /** \details
  Sets a new value of the markup showing flag. 
  The markup showing flag indicates whether the markup is shown when the referenced entity is shown. 
  The flag is equal to true if the markup is shown or to false if the markup is not shown.

  \param markup_show_control [in] A new value of the flag to be set.
  */
  void setMarkupShowControl(bool markup_show_control);
  
  /** \details
  Returns the current value of the markup showing flag.
  The markup showing flag indicates whether the markup is shown when the referenced entity is shown. 
  The flag is equal to true if the markup is shown or to false if the markup is not shown.
  */
  bool markupShowControl() const;

protected:
  virtual bool subWorldDraw (OdGiWorldDraw * pWd) const;
};

#endif // _PRCMARKUPLINKEDITEM_INCLUDED_


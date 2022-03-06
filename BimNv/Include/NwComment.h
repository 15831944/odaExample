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

#ifndef __TNW_COMMENT_H__
#define __TNW_COMMENT_H__

#include "NwObject.h"
#include "NwExport.h"
#include "NwCommentStatus.h"

class OdNwCommentImpl;

/** \details
  This class represents a user comment.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwComment
{
public:

  /** \details
    Default constructor. Creates a new OdNwComment object with an empty author
    and body, sets the zero value to CreateDate and ID, and sets the
    NwCommentStatus::NEW status.
  */
  OdNwComment();

  /** \details
    Copy constructor. Creates a new OdNwComment object from the given
    OdNwComment object.

    \param OdNwComment [in] Input OdNwComment object to create a new object from.
  */
  OdNwComment(const OdNwComment&);

  /** \details
    Copy assignment operator.

    \param OdNwComment [in] OdNwComment object to be copied to this object.
  */
  OdNwComment& operator=(const OdNwComment&);

  /** \details
    Destructor. Frees allocated resources.
  */
  ~OdNwComment();

  /** \details
    Gets the author (creator) of the comment.

    \returns String containing the author.
  */
  OdString getAuthor() const;

  /** \details
    Gets the body of the comment.

    \returns String containing the body of the comment.
  */
  OdString getBody() const;

  /** \details
    Gets the date and time at which the comment was created.

    \returns A tm structure value with the comment creation date.
  */
  tm getCreateDate() const;

  /** \details
    Gets the unique comment identifier in the database.

    \returns OdUInt64 value of the comment identifier in the database. Returns 0
    if there is no meaningful ID.
  */
  OdUInt64 getId() const;

  /** \details
    Gets the status of the comment.

    \returns Comment status as an NwCommentStatus::Enum value.

    \remarks
    Status can be one of the following:

    <table>
    Name                             Value     Description
    NwCommentStatus::NEW             0x00      New comment
    NwCommentStatus::ACTIVE          0x01      Active comment
    NwCommentStatus::APPROVED        0x02      Comment is approved
    NwCommentStatus::RESOLVED        0x03      Comment is resolved
    </table>
  */
  NwCommentStatus::Enum getStatus() const;

private:
  //DOM-IGNORE-BEGIN
  friend class OdNwCommentImpl;
  OdSmartPtr<OdNwCommentImpl> m_pImpl;
  //DOM-IGNORE-END
};

#endif //__TNW_COMMENT_H__

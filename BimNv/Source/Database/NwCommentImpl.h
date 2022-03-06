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

#ifndef __NWCOMMENTIMPL_INCLUDED__
#define __NWCOMMENTIMPL_INCLUDED__

#include "NwComment.h"
#include "RxSystemServices.h"
#include "NwObjectImpl.h"

class OdNwCommentImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwComment)
  ODRX_DECLARE_MEMBERS(OdNwCommentImpl);
  OdNwCommentImpl();
public:
  virtual ~OdNwCommentImpl();

public:
  static OdNwCommentImpl* getImpl(const OdNwComment& NwComment);

public:
  OdString getAuthor() const;
  OdString getBody() const;
  tm getCreateDate() const;
  OdUInt64 getId() const;
  NwCommentStatus::Enum getStatus() const;

  void setAuthor(const OdString& author);
  void setBody(const OdString& body);
  void setCreateDate(tm date);
  void setId(OdUInt64 id);
  void setStatus(NwCommentStatus::Enum status);

private:
  OdString m_user;
  OdString m_body;
  tm m_createdate;
  OdUInt64 m_id;
  NwCommentStatus::Enum m_status;
};



#endif //__NWCOMMENTIMPL_INCLUDED__

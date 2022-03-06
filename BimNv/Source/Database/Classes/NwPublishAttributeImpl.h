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

#ifndef __NW_PUBLISH_ATTRIBUTE_IMPL_H__
#define __NW_PUBLISH_ATTRIBUTE_IMPL_H__

#include "NwPublishAttribute.h"
#include "NwAttributeImpl.h"

class OdNwPublishAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwPublishAttribute)
public:
  OdNwPublishAttributeImpl();
  virtual ~OdNwPublishAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwPublishAttributeImpl);

public:
  static OdNwPublishAttributeImpl* getImpl(const OdNwPublishAttribute* pNwPublish);
  static OdNwPublishAttributeImpl* getImpl(const OdRxObject* pRxTrans);
  
public:
  void setTitle(const OdString& val);
  void setSubject(const OdString& val);
  void setAuthor(const OdString& val);
  void setPublisher(const OdString& val);
  void setPublishDate(const tm& val);
  void setExpiryDate(const tm& val);
  void setCopyright(const OdString& val);
  void setPublishedFor(const OdString& val);
  void setComments(const OdString& val);
  void setKeywords(const OdString& val);
  void setPassword(const OdString& val);

public:
  inline OdUInt32& getFlags() { return m_flags; }
  OdString getTitle() const;
  OdString getSubject() const;
  OdString getAuthor() const;
  OdString getPublisher() const;
  tm getPublishDate() const;
  tm getExpiryDate() const;
  OdString getCopyright() const;
  OdString getPublishedFor() const;
  OdString getComments() const;
  OdString getKeywords() const;
  OdString getPassword() const;

  bool hasExpiryDate() const;
  bool hasPassword() const;
  bool displayOnOpen() const;
  bool displayAtPassword() const;
  bool isEdited() const;
  bool canBeResaved() const;
  bool embedRecapAndTextures() const;
  bool embedDbProperties() const;
  bool preventObjectPropertyExport() const;

public:
  OdUInt32 m_flags;
  OdString m_title;
  OdString m_subject;
  OdString m_author;
  OdString m_publisher;
  tm m_publishDate;
  tm m_expiryDate;
  OdString m_copyright;
  OdString m_publishedFor;
  OdString m_comments;
  OdString m_keywords;
  OdString m_password;
};



#endif //__NW_PUBLISH_ATTRIBUTE_IMPL_H__

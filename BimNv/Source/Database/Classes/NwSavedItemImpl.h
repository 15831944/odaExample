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

#ifndef __NWSAVEDITEMIMPL_INCLUDED__
#define __NWSAVEDITEMIMPL_INCLUDED__

#include "NwSavedItem.h"
#include "NwObjectImpl.h"
#include "RxSystemServices.h"

class NWDBEXPORT OdNwSavedItemImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSavedItem)
public:
  ODRX_DECLARE_MEMBERS(OdNwSavedItemImpl);

public:
  OdNwSavedItemImpl();
  virtual ~OdNwSavedItemImpl();

public:
  static OdNwSavedItemImpl* getImpl(const OdNwSavedItem* pNwSI);
  static OdNwSavedItemImpl* getImpl(const OdRxObject* pRxSI);

public:
  OdArray<OdNwComment> getCommentCollection() const;
  OdString getDisplayName() const;
  OdGUID getGuID() const;
  virtual bool isGroup() const;
  OdNwSavedItem* getParent() const;
  OdNwObjectId getParentId() const;
  bool hasSchema() const;

  inline OdArray<OdNwComment>& getCommentCollection() { return m_aComments; }

public:
  void addComment(const OdNwComment& comment);
  void setDisplayName(const OdString& name);
  void setGuID(const OdGUID& guid);
  void setParent(OdNwSavedItem* pParent);
  void setHasSchema(bool val);//VAS:: it's temporary method

protected:
  OdString m_DisplayName;
  OdGUID m_GuID;
  OdNwSavedItem* m_pParent;
  OdArray<OdNwComment> m_aComments;
  bool m_bHasSchema;
};



#endif //__NWSAVEDITEMIMPL_INCLUDED__

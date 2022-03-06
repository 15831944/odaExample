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

#ifndef __NWURL_INCLUDED__
#define __NWURL_INCLUDED__

#include "NwURL.h"
#include "NwObjectImpl.h"

class OdNwURLImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwURL)
public:
  OdNwURLImpl();
  virtual ~OdNwURLImpl();
  ODRX_DECLARE_MEMBERS(OdNwURLImpl);

public:
  static OdNwURLImpl* getImpl(const OdNwURL* pNwURL);
  static OdNwURLImpl* getImpl(const OdRxObject* pRxURL);

public:
  OdString getName() const;
  OdString getURL() const;
  OdNwNamePtr getCategory() const;
  OdGePoint3dArray getAttachmentPoints() const;
  inline OdGePoint3dArray& getAttachmentPoints() { return m_aAttachmentPoints; }

public:
  void setName(const OdString& name);
  void setURL(const OdString& url);
  void setCategory(OdNwNamePtr pCat);

private:
  OdString m_Name;
  OdString m_URL;
  OdNwNamePtr m_pCategory;
  OdGePoint3dArray m_aAttachmentPoints;
};



#endif //__NWURL_INCLUDED__

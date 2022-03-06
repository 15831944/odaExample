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

#ifndef __NWTEXTFONTINFOIMPL_INCLUDED__
#define __NWTEXTFONTINFOIMPL_INCLUDED__

#include "NwTextFontInfo.h"
#include "RxSystemServices.h"
#include "NwObjectImpl.h"

class OdNwTextFontInfoImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwTextFontInfo)
  ODRX_DECLARE_MEMBERS(OdNwTextFontInfoImpl);
  OdNwTextFontInfoImpl();
public:
  virtual ~OdNwTextFontInfoImpl();

public:
  static OdNwTextFontInfoImpl* getImpl(const OdNwTextFontInfo& NwFont);

public:
  //public implementation's methods
  OdString getName() const;
  double getHeight() const;
  bool isItalic() const;

public:
  OdUInt32 getIndex() const;
  OdUInt32 getIsItalic() const;
public:
  void setIndex(OdUInt32 index);
  void setFontName(const OdString& fontName);
  void setHeight(const double& ps);
  void setItalic(OdUInt32 isItalic);

private:
  OdUInt32 m_Index;
  OdString m_FontName;
  double m_Height;
  OdUInt32 m_IsItalic;
};



#endif //__NWTEXTFONTINFOIMPL_INCLUDED__

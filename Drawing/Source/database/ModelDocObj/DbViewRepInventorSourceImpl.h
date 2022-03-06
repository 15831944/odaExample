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

#ifndef _ODDBVIEWREPINVENTORSOURCEIMPL_INCLUDED_
#define _ODDBVIEWREPINVENTORSOURCEIMPL_INCLUDED_

#include "DbViewRepInventorSource.h"
#include "DbViewRepSourceImpl.h"

class OdDbViewRepInventorSourceImpl : public OdDbViewRepSourceImpl 
{
private:
  OdDbViewRepInventorSourceImpl();

  static OdDbViewRepInventorSourceImpl* getImpl(const OdDbViewRepInventorSource* pObj)
  { return (OdDbViewRepInventorSourceImpl*) OdDbSystemInternals::getImpl(pObj); }

  friend class OdDbViewRepInventorSource;

  OdString m_path;
  /*
  OdString m_lod;
  OdString m_weldInstance;
  OdString m_memberName;
  OdString m_positionalName;
  OdString m_presentationView;
  */
  OdString m_unknown1;
  OdString m_unknown2;
  OdString m_unknown3;
  OdString m_unknown4;
  OdString m_unknown5;

  OdUInt32 m_flags;
};

#endif //_ODDBVIEWREPINVENTORSOURCEIMPL_INCLUDED_

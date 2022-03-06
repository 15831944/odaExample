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

// OdR12DwgFiler.h: interface for the OdR12DwgFiler class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ODR12DWGFILER_H__INCLUDED_
#define _ODR12DWGFILER_H__INCLUDED_


#include "FlatFiler.h"
#include "DbFilerController.h"

class OdR12DwgFiler : public OdRxObjectImpl<OdFlatFiler>
{
  OdR12DwgFiler& operator = (OdR12DwgFiler);
  OdDbFilerController*    m_pController;
public:
	void          open(OdStreamBuf* pStream, OdDbFilerController* pController);
  FilerType     filerType() const;

  OdString rdString();

  OdDbFilerController* controller() const;
};

#endif // _ODR12DWGFILER_H__INCLUDED_

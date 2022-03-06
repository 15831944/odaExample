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

#if !defined(ODDWGDIGITALSIGNATURE_H__803FFA4E_5807_4DCA_9DDE_77E90E3FAB82__INCLUDED_)
#define ODDWGDIGITALSIGNATURE_H__803FFA4E_5807_4DCA_9DDE_77E90E3FAB82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TD_PackPush.h"

#include "SharedPtr.h"
#include "UInt32Array.h"

class OdDwgDigitalSignature
{
public:
  OdDwgDigitalSignature();
  ~OdDwgDigitalSignature();

  OdUInt32      m_unk;
  OdUInt32Array m_sectionIds;
  OdBinaryData  m_signature;
};

typedef OdSharedPtr<OdDwgDigitalSignature> OdDwgDigitalSignaturePtr;


inline OdDwgDigitalSignature::OdDwgDigitalSignature()
  : m_unk(0)
{
}

inline OdDwgDigitalSignature::~OdDwgDigitalSignature()
{
}

#include "TD_PackPop.h"

#endif

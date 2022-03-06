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

#ifndef _ODDBATTRDEFIMPL_INCLUDED_
#define _ODDBATTRDEFIMPL_INCLUDED_

#include "DbTextImpl.h"
#include "DbSystemInternals.h"
#include "DbAttributeDefinition.h"
#include "DbAttributeImpl.h"

class OdTvDbAttributeDefinitionImpl : public OdTvDbAttributeImpl //OdTvDbTextImpl
{
  static OdTvDbAttributeDefinitionImpl* getImpl(const OdTvDbAttributeDefinition *pObj)
  { return (OdTvDbAttributeDefinitionImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbAttributeDefinitionImpl() : OdTvDbAttributeImpl()
    , m_version(0) // 0 == AC2010
  {
  }

  OdString m_strPrompt;
  OdUInt8  m_version;
  virtual OdUInt8  getTypeAtrribute() const
  {
    if ( bIsMLineAttribute() )
      return OdTvDbAttributeImpl::kMultiLineAttrDefinition;
    else
      return OdTvDbAttributeImpl::kSingleLine;
  }
  
//  OdString m_strTag;
  //OdInt16  m_FieldWidth;

//  bool     m_bAttDefInvisible;
//  bool     m_bPreset;
//  bool     m_bConstant;
//  bool     m_bVerifiable;

//  OdUInt8 assembleFlags() const;
//  void disassembleFlags(OdUInt8 f);

  // OdTvDbTextImpl overriden
  const OdString& getString() const;

  friend class OdTvDbAttributeDefinition;
};

#endif // _ODDBATTRDEFIMPL_INCLUDED_

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
//
// GlesJsonServerBaseImpl.cpp
//

#include "OdaCommon.h"
#include "GlesJsonServerBaseImpl.h"
#include "OdFakeDbStub.h"

OdGlesJsonServerBaseImpl::OdGlesJsonServerBaseImpl(const OdDbBaseDatabase *pDb) // = NULL
  : OdGLES2JsonServerBaseImpl(pDb)
  , m_bSkipShaders(true)
  , m_useFakeDbStub(false)
  , m_bEncodeTextureHex(false)
{
}

void OdGlesJsonServerBaseImpl::setUseFakeDbStub(bool bVal)
{
  m_useFakeDbStub = bVal;
}

void OdGlesJsonServerBaseImpl::setSkipShaders(bool bSkipShaders)
{
  m_bSkipShaders = bSkipShaders;
}

void OdGlesJsonServerBaseImpl::setEncodeTextureHex(bool bValue)
{
  m_bEncodeTextureHex = bValue;
}

OdStringArray OdGlesJsonServerBaseImpl::getRenderHandles() const
{
  OdStringArray handles;

  for (std::map<OdDbStub*, OdAnsiString>::const_iterator itr = m_mapHandles.begin(); 
       itr != m_mapHandles.end(); itr++)
    handles.push_back(itr->second.c_str());
  return handles;
}

void OdGlesJsonServerBaseImpl::DropDbOwning(const char* pTagName, OdTrVisOwning owningId)
{
  if (!m_useFakeDbStub || (owningId == kTrVisNullId))
    OdGLES2JsonServerBaseImpl::DropDbOwning(pTagName, owningId);
  else
    ident(pTagName, OdAnsiString().format("%" PRIX64, OdTrVisIdToPtr(OdFakeDbStub, owningId)->handle).c_str(), OdGLES2JsonServer::kType); // ident(pTagName, (const char*) pDbStub);

  if (m_useFakeDbStub || (owningId == kTrVisNullId))
    return;
  // collect handles of really usable in render entities
  if (m_mapHandles.find(OdTrVisIdToPtr(OdDbStub, owningId)) == m_mapHandles.end())
    m_mapHandles[OdTrVisIdToPtr(OdDbStub, owningId)] = m_sTmpBuf;
  ODA_ASSERT_ONCE(m_mapHandles[OdTrVisIdToPtr(OdDbStub, owningId)] == m_sTmpBuf);
}

void OdGlesJsonServerBaseImpl::DropBinaryStream(const char* pTagName, const OdUInt8* pData, OdUInt32 nData)
{
  if (m_bEncodeTextureHex)
    OdGLES2JsonServerBaseImpl::DropBinaryStream(pTagName, pData, nData);
  else
  {
    encodeToBase64(pData, nData, m_sTmpBuf);
    ident(pTagName, m_sTmpBuf.c_str(), OdGLES2JsonServer::kType);
  }
}

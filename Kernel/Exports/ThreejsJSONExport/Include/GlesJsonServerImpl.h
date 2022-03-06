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
// GlesJsonServerImpl.h
//

#ifndef OG_GLES_JSON_SERVER_IMPL_H_
#define OG_GLES_JSON_SERVER_IMPL_H_

#include "CloudTools.h"
#include "GlesJsonServerBaseImpl.h"

/** <group ExRender_Classes>
*/
class OdGlesJsonServerImpl : public OdGlesJsonServerBaseImpl
{
  OdStreamBufPtr m_pOutStream;
  int m_indexNextFree;

public:
  OdGlesJsonServerImpl(const OdDbBaseDatabase *pDb = NULL);

  virtual void setOutput(OdStreamBuf * buf);
  // set output path name or format(if %d is present in path)
  virtual bool setOutPathName(const OdString& sPathName,
                              OdUInt64 limitToSplit = OdUInt64(), // if > OdUInt64() then willbe splited by next OnStateChanged
                              int indexNextFree = 0); 
  virtual int flushOut(); // return next free index

  virtual void ident(const char* pTag, const char* pText, const OdGLES2JsonServer::JsonType &);
};

#endif // OG_GLES_JSON_SERVER_IMPL_H_

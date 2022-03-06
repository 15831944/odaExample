  /////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2018, Open Design Alliance (the "Alliance"). 
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
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2019 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#ifndef __NW_OBJ_TRANS_DYNAMIC_WRITER_H__
#define __NW_OBJ_TRANS_DYNAMIC_WRITER_H__

#include "NwStreamSaver.h"
#include "NwObjectWriter.h"
#include "TD_PackPush.h"

class OdNwObjTransDynamicWriter : public OdNwObjectWriter
{
public:
  OdNwObjTransDynamicWriter();
  explicit OdNwObjTransDynamicWriter(OdNwObjectPtr pElement);
  OdResult saveToStream(OdNwObjectWriterManager* stream) override;
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwObjTransDynamicWriter object pointers.
*/
typedef OdSharedPtr<OdNwObjTransDynamicWriter> OdNwObjTransDynamicWriterPtr;

#include "TD_PackPop.h"

#endif // __NW_OBJ_TRANS_DYNAMIC_WRITER_H__

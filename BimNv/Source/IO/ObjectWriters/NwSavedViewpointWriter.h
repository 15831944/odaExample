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
#ifndef __NW_SAVED_VIEWPOINT_WRITER_H__
#define __NW_SAVED_VIEWPOINT_WRITER_H__

#include "NwObjectWriter.h"
#define STL_USING_LIST
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "TD_PackPush.h"

class OdNwObjectWriterManager;
class OdNwRedLine;
typedef OdSmartPtr<OdNwRedLine> OdNwRedLinePtr;
class OdNwElementRecord;
typedef OdSmartPtr<OdNwElementRecord> OdNwElementRecordPtr;

class OdNwSavedViewpointWriter : public OdNwObjectWriter
{
public:
  OdNwSavedViewpointWriter();
  ~OdNwSavedViewpointWriter() override;
  OdResult saveToStream(OdNwObjectWriterManager* stream) override;

public:
  static OdResult writeRedLineList(OdNwObjectWriterManager* stream, OdArray<OdNwRedLinePtr>& lRedLine);
  static OdResult writeRedLineLine(OdNwObjectWriterManager* stream, OdNwRedLinePtr pRedLine);
  static OdResult writeRedLineEllipse(OdNwObjectWriterManager* stream, OdNwRedLinePtr pRedLine);
  static OdResult writeRedLineCloud(OdNwObjectWriterManager* stream, OdNwRedLinePtr pRedLine);
  static OdResult writeRedLineTag(OdNwObjectWriterManager* stream, OdNwRedLinePtr pRedLine);
  static OdResult writeRedLineText(OdNwObjectWriterManager* stream, OdNwRedLinePtr pRedLine);
  static OdResult writeRedLineArrow(OdNwObjectWriterManager* stream, OdNwRedLinePtr pRedLine);
  static OdResult writeElementRecordList(OdNwObjectWriterManager* stream, OdArray<OdNwElementRecordPtr>& lElementRecord);
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwSavedViewpointWriter object pointers.
*/
typedef OdSharedPtr<OdNwSavedViewpointWriter> OdNwSavedViewpointWriterPtr;

#include "TD_PackPop.h"

#endif // __NW_SAVED_VIEWPOINT_WRITER_H__

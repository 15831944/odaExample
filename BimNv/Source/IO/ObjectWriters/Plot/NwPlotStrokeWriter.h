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
#ifndef _NW_PLOTSTROKE_WRITER_H_
#define _NW_PLOTSTROKE_WRITER_H_

#include "NwStreamSaver.h"
#include "NwObjectWriterManager.h"
#include "TD_PackPush.h"

class OdNwObjectWriter;

class OdNwPlotStrokeWriter : public OdNwObjectWriter
{
public:
  OdNwPlotStrokeWriter();
  ~OdNwPlotStrokeWriter() override;
  OdResult saveToStream(OdNwObjectWriterManager* stream) override;
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwPlotStrokeWriter object pointers.
*/
typedef OdSharedPtr<OdNwPlotStrokeWriter> OdNwPlotStrokeWriterPtr;

#include "TD_PackPop.h"

#endif // _NW_PLOTSTROKE_WRITER_H_


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
#ifndef __NW_GEWRITESTREAMCOMMON_H__
#define __NW_GEWRITESTREAMCOMMON_H__

#include "NwWriteStreamCommon.h"
#include "Ge/GeQuaternion.h"

#include "TD_PackPush.h"

// Write
namespace NwStreamCommon
{
  inline void writeFPoint3d(OdStreamBuf& stream, const OdGePoint3d& val)
  {
    ODA_ASSERT(OD_T("writeFPoint3d") && !(stream.tell() % 4));

    OdPlatformStreamer::wrFloat(stream, val.x);
    OdPlatformStreamer::wrFloat(stream, val.y);
    OdPlatformStreamer::wrFloat(stream, val.z);
  }

  inline void writeFVector3d(OdStreamBuf& stream, const OdGeVector3d& val)
  {
    ODA_ASSERT(OD_T("writeFVector3d") && !(stream.tell() % 4));

    OdPlatformStreamer::wrFloat(stream, val.x);
    OdPlatformStreamer::wrFloat(stream, val.y);
    OdPlatformStreamer::wrFloat(stream, val.z);
  }

  inline void writeDPoint2d(OdStreamBuf& stream, const OdGePoint2d& val)
  {
    ODA_ASSERT(OD_T("writeDPoint2d") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, val.x);
    OdPlatformStreamer::wrDouble(stream, val.y);
  }

  inline void writeDPoint3d(OdStreamBuf& stream, const OdGePoint3d& val)
  {
    ODA_ASSERT(OD_T("writeDPoint3d") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, val.x);
    OdPlatformStreamer::wrDouble(stream, val.y);
    OdPlatformStreamer::wrDouble(stream, val.z);
  }

  inline void writeDVector3d(OdStreamBuf& stream, const OdGeVector3d& vector)
  {
    ODA_ASSERT(OD_T("writeDVector3d") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, vector.x);
    OdPlatformStreamer::wrDouble(stream, vector.y);
    OdPlatformStreamer::wrDouble(stream, vector.z);
  }
  
  inline void writeDMatrix3d(OdStreamBuf& stream, const OdGeMatrix3d& mtrx)
  {
    ODA_ASSERT(OD_T("writeDMatrix3d") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, mtrx(0, 0));
    OdPlatformStreamer::wrDouble(stream, mtrx(0, 1));
    OdPlatformStreamer::wrDouble(stream, mtrx(0, 2));

    OdPlatformStreamer::wrDouble(stream, mtrx(1, 0));
    OdPlatformStreamer::wrDouble(stream, mtrx(1, 1));
    OdPlatformStreamer::wrDouble(stream, mtrx(1, 2));

    OdPlatformStreamer::wrDouble(stream, mtrx(2, 0));
    OdPlatformStreamer::wrDouble(stream, mtrx(2, 1));
    OdPlatformStreamer::wrDouble(stream, mtrx(2, 2));

    OdPlatformStreamer::wrDouble(stream, mtrx(0, 3));
    OdPlatformStreamer::wrDouble(stream, mtrx(1, 3));
    OdPlatformStreamer::wrDouble(stream, mtrx(2, 3));
  }
  
  inline void writeQuaternion(OdStreamBuf& stream, const OdGeQuaternion& q)
  {
    ODA_ASSERT(OD_T("writeQuaternion") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, q.x);
    OdPlatformStreamer::wrDouble(stream, q.y);
    OdPlatformStreamer::wrDouble(stream, q.z);
    OdPlatformStreamer::wrDouble(stream, q.w);
  }
}// namespace NwStreamCommon

#include "TD_PackPop.h"

#endif // __NW_GEWRITESTREAMCOMMON_H__

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
#ifndef __NW_GEREADSTREAMCOMMON_H__
#define __NW_GEREADSTREAMCOMMON_H__

#include "NwReadStreamCommon.h"
#include "Ge/GeQuaternion.h"

#include "TD_PackPush.h"

namespace NwStreamCommon
{
  template <bool checkVal> struct helperCheckClassSize;
  template <> struct helperCheckClassSize<true> {};
  template<typename T, size_t doubleCount>
  struct checkClassSize
  {
    helperCheckClassSize<sizeof(T) == doubleCount * sizeof(double)> temp;
  };

  inline OdGePoint3d readFPoint3d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readFPoint3d") && !(stream.tell() % 4));

    float pt3d[3];
    readFloats(stream, 3, pt3d);
    return OdGePoint3d(pt3d[0], pt3d[1], pt3d[2]);
  }

  inline OdGeVector3d readFVector3d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readFVector3d") && !(stream.tell() % 4));

    float v3d[3];
    readFloats(stream, 3, v3d);
    return OdGeVector3d(v3d[0], v3d[1], v3d[2]);
  }

  inline OdGePoint2d readDPoint2d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDPoint2d") && !(stream.tell() % 8));

    OdGePoint2d pt2d;
    checkClassSize<OdGePoint2d, 2>();
    OdPlatformStreamer::rd2Doubles(stream, &pt2d);
    return pt2d;
  }

  inline OdGePoint2d readFPoint2d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readFPoint2d") && !(stream.tell() % 4));

    float pt2d[2];
    readFloats(stream, 2, pt2d);
    return OdGePoint2d(pt2d[0], pt2d[1]);
  }

  inline OdGePoint3d readDPoint3d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDPoint3d") && !(stream.tell() % 8));

    OdGePoint3d pt3d;
    checkClassSize<OdGePoint3d, 3>();
    OdPlatformStreamer::rd3Doubles(stream, &pt3d);
    return pt3d;
  }

  inline OdGeVector3d readDVector3d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDVector3d") && !(stream.tell() % 8));

    OdGeVector3d vec3d;
    checkClassSize<OdGePoint3d, 3>();
    OdPlatformStreamer::rd3Doubles(stream, &vec3d);
    return vec3d;
  }

  inline OdGeMatrix3d readDMatrix3d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDMatrix3d") && !(stream.tell() % 8));

    OdGeMatrix3d matrix = OdGeMatrix3d::kIdentity;

    checkClassSize<OdGeMatrix3d, 16>();
    OdPlatformStreamer::rd3Doubles(stream, matrix.entry);//read matrix(0,0),matrix(0,1),matrix(0,2)
    OdPlatformStreamer::rd3Doubles(stream, matrix.entry[1]);//read matrix(1,0),matrix(1,1),matrix(1,2)
    OdPlatformStreamer::rd3Doubles(stream, matrix.entry[2]);//read matrix(2,0),matrix(2,1),matrix(2,2)
    double mtrx[3];
    OdPlatformStreamer::rd3Doubles(stream, mtrx);
    matrix(0, 3) = mtrx[0];
    matrix(1, 3) = mtrx[1];
    matrix(2, 3) = mtrx[2];
    matrix(3, 3) = 0;

    return matrix;
  }
  
  inline OdGeMatrix3d readDAffineCoords3d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDAffineCoords3d") && !(stream.tell() % 8));
    OdGeMatrix3d matrix = OdGeMatrix3d::kIdentity;

    double aff[12];
    OdPlatformStreamer::rdDoubles(stream, 12, aff);

    matrix.setCoordSystem(OdGePoint3d(aff[0], aff[1], aff[2]),//origin or - matrix(0,3),matrix(1,3),matrix(2,3)
                          OdGeVector3d(aff[3], aff[4], aff[5]),//xAxis or - matrix(0,0),matrix(1,0),matrix(2,0)
                          OdGeVector3d(aff[6], aff[7], aff[8]),//yAxis or - matrix(0,1),matrix(1,1),matrix(2,1)
                          OdGeVector3d(aff[9], aff[10], aff[11]));//zAxis or - matrix(0,2),matrix(1,2),matrix(2,2)
    return matrix;
  }

  inline OdGeMatrix2d readDMatrix2d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDMatrix2d") && !(stream.tell() % 8));
    OdGeMatrix2d matrix = OdGeMatrix2d::kIdentity;

    checkClassSize<decltype(matrix.entry), 9>();
    OdPlatformStreamer::rdDoubles(stream, 9, matrix.entry);

    return matrix;
  }

  inline OdGeMatrix2d readFMatrix2d(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readFMatrix2d") && !(stream.tell() % 8));

    OdGeMatrix2d matrix = OdGeMatrix2d::kIdentity;

    float mtrx[9];
    readFloats(stream, 9, mtrx);

    matrix(0, 0) = mtrx[0];
    matrix(0, 1) = mtrx[1];
    matrix(0, 2) = mtrx[2];

    matrix(1, 0) = mtrx[3];
    matrix(1, 1) = mtrx[4];
    matrix(1, 2) = mtrx[5];

    matrix(2, 0) = mtrx[6];
    matrix(2, 1) = mtrx[7];
    matrix(2, 2) = mtrx[8];

    return matrix;
  }

  inline OdGeQuaternion readQuaternion(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readQuaternion") && !(stream.tell() % 8));

    double q[4];
    OdPlatformStreamer::rdDoubles(stream, 4, q);
    return OdGeQuaternion(q[3], q[0], q[1], q[2]);
  }
} // namespace NwStreamCommon

#include "TD_PackPop.h"

#endif // __NW_GEREADSTREAMCOMMON_H__

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
#ifndef __NW_GRAPHIC_VERTEXSET_READER_H__
#define __NW_GRAPHIC_VERTEXSET_READER_H__

#include "NwObjectReader.h"
#include "NwObjectReaderManager.h"
#include "TD_PackPush.h"

#include "Ge/GePoint3dArray.h"

class OdGePoint3d;

class OdNwGraphicVertexSetReader : public OdNwObjectReader
{
public:
  static OdResult readIndexTable(OdStreamBuf& stream, OdArray<OdUInt32>& indexTable, OdInt32 count);
  static void readBits(OdStreamBuf& stream, const OdArray<OdUInt8>& bitsPerItem, OdInt32 bitSetsCount, OdArray<OdUInt32>& bitsArray, OdInt32 arraySize);
  static void readBits(OdStreamBufPtr pStream, const OdArray<OdUInt8>& bitsPerItem, OdInt32 bitSetsCount, OdArray<OdUInt32>& bitsArray, OdInt32 arraySize);
  static OdResult readVertices(OdStreamBufPtr pStream, OdGePoint3dArray& vertices);
  static OdResult readIndexes(OdStreamBufPtr pStream
    , OdInt32 axesPerPoint
    , OdInt32 vertexCount
    , OdInt32 aFlagFloat
    , OdArray<OdUInt8>& bitsPerItem
    , OdArray<OdUInt32>& bitsArray // arrayUI
    , OdArray<OdUInt32>& indexTable
    , OdArray<float> &arrayF
    , OdInt32& bitSetsCount);

  static OdInt8 readIndex(OdStreamBufPtr pStream, OdUInt16& val);
public:
  OdResult readFromStream(OdNwObjectReaderManager* stream) override;
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwGraphicVertexSetReader object pointers.
*/
typedef OdSharedPtr<OdNwGraphicVertexSetReader> OdNwGraphicVertexSetReaderPtr;

#include "TD_PackPop.h"

#endif // __NW_GRAPHIC_VERTEXSET_READER_H__

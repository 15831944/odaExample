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




// MemoryStream.h: interface for the OdMemoryStreamImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_NW_COMPRESSEDSTREAM_H_INCLUDED_)
#define _NW_COMPRESSEDSTREAM_H_INCLUDED_

#include "NwExport.h"
#include "OdStreamBuf.h"
#include "OdBinaryData.h"
#include "TD_PackPush.h"

class OdNwCompressedStream;
typedef OdSmartPtr<OdNwCompressedStream> OdNwCompressedStreamPtr;

/** \details
    This class defines the interface for compressed paged-memory I/O objects. 

    <group OdNw_Classes>
*/
class NWDBEXPORT OdNwCompressedStream : public OdStreamBuf
{
protected:
  OdNwCompressedStream();

public:
  ODRX_DECLARE_MEMBERS(OdNwCompressedStream);

  /** \details
    Creates a new OdNwCompressedStream object, and returns a SmartPointer to the new object.
    \param pageSize [in]  PageDataSize.
  */
  static OdNwCompressedStreamPtr createNew(OdUInt32 pageDataSize = 0);

  virtual void addCompressedStream(OdUInt64 size, OdBinaryData stream) = 0;
  /** \details
  Sets the PageDataSize for this MemoryStream object.
  \param pageDataSize [in]  PageDataSize.
*/
  virtual void setPageDataSize(OdUInt32 pageDataSize) = 0;
};

#include "TD_PackPop.h"

#endif // !defined(_NW_COMPRESSEDSTREAM_H_INCLUDED_)


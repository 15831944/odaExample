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

#ifndef _PRCRWFILERBASE_INCLUDED_
#define _PRCRWFILERBASE_INCLUDED_ 
 

class OdPrcUncompressedFiler;

#include "PrcToolkitExportDef.h"
#include "PrcFiler.h"
#include "OdStreamBuf.h"
#include "FlatMemStream.h"
#include "UInt8Array.h"
#include "PrcGraphics.h"

SMARTPTR(OdPrcUncompressedFiler);

struct OdPrcSectionExtractor;
class OdPrcLowLevelDumper;
class OdPrcAuditInfo;

/** \details 
<group PRC_Input_Output_Operations> 

Class provides methods for working with uncompressed .prc files.
*/
class PRC_TOOLKIT OdPrcUncompressedFiler : public OdPrcFiler
{
  friend struct OdPrcSectionExtractor;
  friend class  OdPrcLowLevelDumper;

  OdStreamBufPtr m_pBuf;

protected:
  OdPrcUncompressedFiler(OdStreamBufPtr pBuf, OdUInt32 authoring_version);

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcUncompressedFiler)
  //DOM-IGNORE-END
  
  /** \details
    Returns a pointer to the internal buffer.
  */
  virtual OdStreamBuf* internalBuffer();

  /** \details 
  Destroys an uncompressed filer object.
  */
  virtual ~OdPrcUncompressedFiler();
  
  /** \details
  Returns the current position of the file pointer for the internal buffer. 
  */
  virtual OdUInt64 tell();
  
  /** \details
  Returns the length in bytes of the file associated with the filer.
  */
  virtual OdUInt64 length();
  
  /** \details
  Moves the current position of the file pointer for the filer to the specified location.

  \param offset [in] A number of bytes.
  \param seekType [in] A seek type.
  
  \remarks 
  seekType must be one of the following: 
    <table>
      Value                     Value       Description
      OdDb::kSeekFromStart      SEEK_SET    Start of file
      OdDb::kSeekFromCurrent    SEEK_CUR    Current position of file pointer.
      OdDb::kSeekFromEnd        SEEK_END    End of file
    </table>
  */
  virtual OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType seekType);
  
  /** \details
  Creates a new object of this class, fills out its fields, and returns a pointer to it.

  \param pBuf [in] A data input stream.
  \param authoring_version [in] An authoring version.
  \param pAuditInfo [out] A pointer to audit information associated with this object.
  */
  static OdPrcUncompressedFilerPtr create(OdStreamBufPtr pBuf, OdUInt32 authoring_version, OdPrcAuditInfo *pAuditInfo);

  /** \details
  Writes an unsigned integer to the file associated with the filer.

  \param i [in] An integer value for writing.
  \param pName [in] An input name of a field.
  */
  virtual void writeUncompressedUnsignedInteger(OdUInt32 i, const char* pName = 0);
  
  /** \details
  Returns the current value of a field.

  \param pName [in] An input name of a field.
  \returns An unsigned integer.
  */
  virtual OdUInt32 readUncompressedUnsignedInteger(const char* pName = 0);
  
  /** \details
  Returns a block of specific size from the file associated with the filer.

  \param pBuf [out] A pointer to an integer value.
  \param size [in] An integer value of a block size.
  */
  virtual void readUncompressedBlock(OdUInt8 *pBuf, OdUInt32 size);
  
  /** \details
  Writes a block of specific size to the file associated with the filer.

  \param pBuf [in] A constant pointer to a block.
  \param size [in] An integer value of a block size.
  */
  virtual void writeUncompressedBlock(const OdUInt8 *pBuf, OdUInt32 size);
};

#endif //_PRCRWFILERBASE_INCLUDED_


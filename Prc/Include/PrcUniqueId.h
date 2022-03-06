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

#ifndef _PRCUNIQUEID_INCLUDED_
#define _PRCUNIQUEID_INCLUDED_ 
 

#include "PrcUncompressedFiler.h"

/** \details 
<group PRC_Datatypes_Classes> 

Class representing a unique identifier (UID). 
*/
class PRC_TOOLKIT OdPrcUniqueId
{
private:
  OdUInt32 m_Id[4];

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE(OdPrcUniqueId)
  //DOM-IGNORE-END

  /** \details
  A zero value of a unique identifier.
  */
  static OdPrcUniqueId kZero;
  
  /** \details
  Compares the unique identifier with another unique identifier for equality.

  \param uid [in] An unique identifier for equality.
  
  \returns Returns true if unique identifiers are equal or false if they are not equal.
  */
  bool operator == (const OdPrcUniqueId &uid) const;

  /** \details
  Compares two unique identifiers.

  \param uid [in] A unique identifier for comparison.
  
  \returns Returns true if the unique identifier is less than the other identifier passed as a parameter, or false in the other case.
  */
  bool operator < (const OdPrcUniqueId &uid) const;

  /** \details
  Creates a new unique identifier with specified digits.

  \param id0 [in] First digit of a unique identifier.  
  \param id1 [in] Second digit of a unique identifier. 
  \param id2 [in] Third digit of a unique identifier. 
  \param id3 [in] Fourth digit of a unique identifier. 
  */
  OdPrcUniqueId(OdUInt32 id0, OdUInt32 id1, OdUInt32 id2, OdUInt32 id3);

  /** \details
  Sets a new value of the unique identifier with specified digits.

  \param id0 [in] First digit of a unique identifier.  
  \param id1 [in] Second digit of a unique identifier. 
  \param id2 [in] Third digit of a unique identifier. 
  \param id3 [in] Fourth digit of a unique identifier.
  */
  void setID(OdUInt32 id0, OdUInt32 id1, OdUInt32 id2, OdUInt32 id3);

  /** \details
  Returns the current value of a unique identifier.

  \param id0 [in] A reference to the first digit of a unique identifier.  
  \param id1 [in] A reference to the second digit of a unique identifier.
  \param id2 [in] A reference to the third digit of a unique identifier.
  \param id3 [in] A reference to the fourth digit of a unique identifier.
  */
  void getID(OdUInt32 &id0, OdUInt32 &id1, OdUInt32 &id2, OdUInt32 &id3);

  /** \details
  Checks a unique identifier for non-zero value.

  \returns Returns true if a unique identifier is non-zero or false in the other case.
  */
  bool isNonZero() const;

  /** \details
  Generates and returns a unique identifier.
  */
  static OdPrcUniqueId generateUID(void);

  /** \details
  Reads a unique identifier from a stream associated with an uncompressed filer.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  \param pName [in] A pointer to a block name. 
  */
  void prcOut(OdPrcUncompressedFiler *pStream, const char* pName);
  
  /** \details
  Writes a unique identifier to a stream associated with an uncompressed filer.

  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  \param pName [in] A pointer to a block name. 
  */
  void prcIn(OdPrcUncompressedFiler *pStream, const char* pName);

  /** \details
  Writes a unique identifier to a stream associated with a compressed filer.

  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  \param pName [in] A pointer to a block name. 
  */
  void writeCompressed(OdPrcCompressedFiler *pStream, const char* pName);

  /** \details
  Reads a unique identifier from a stream associated with a compressed filer.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  \param pName [in] A pointer to a block name. 
  */
  void readCompressed(OdPrcCompressedFiler *pStream, const char* pName);
};

typedef OdArray<OdPrcUniqueId> OdPrcUniqueIdArray;

#endif // _PRCUNIQUEID_INCLUDED_


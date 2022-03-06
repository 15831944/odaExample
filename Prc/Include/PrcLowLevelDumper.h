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

#ifndef _PRCLOWLEVELDUMPER_INCLUDED_
#define _PRCLOWLEVELDUMPER_INCLUDED_ 
 

#include "PrcUncompressedFiler.h"
#include "PrcCompressedFiler.h"

SMARTPTR(OdPrcUncompressedFilerDumper);

/** \details
  <group PRC_Input_Output_Operations>
  Class implements an uncompressed file dumper.
*/
class PRC_TOOLKIT OdPrcUncompressedFilerDumper : public OdPrcUncompressedFiler
{
  OdPrcUncompressedFilerPtr m_pFilerBase;
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcUncompressedFilerDumper);
  //DOM-IGNORE-END

  /** \details
  Returns an internal buffer from the base filer.
  */
  virtual OdStreamBuf* internalBuffer();

  /** \details
  Sets a new base filer.

  \param pFilerBase [in] A new base filer to be set.
  */
  void setFiler(OdPrcUncompressedFiler *pFilerBase);
  
  /** \details
  Returns the pointer on the current base filer.
  */
  OdPrcUncompressedFiler *getFiler();

  /** \details
  Writes an uncompressed 32-bit unsigned integer value to the filer stream.

  \param i [in] A value to write.
  \param pName [in] A name of a data field.
  */
  virtual void writeUncompressedUnsignedInteger(OdUInt32 i, const char* pName = 0);
  
  /** \details
  Reads an uncompressed 32-bit unsigned integer value from the filer stream and returns it.

  \param pName [in] A name of a data field.
  */
  virtual OdUInt32 readUncompressedUnsignedInteger(const char* pName = 0);

  /** \details
  Reads an uncompressed block from the filer stream.

  \param pBuf [out] A pointer on buffer to store block data.
  \param size [in] Size of block to read.
  */
  virtual void readUncompressedBlock(OdUInt8 *pBuf, OdUInt32 size);
  
  /** \details
  Writes an uncompressed block to the filer stream.

  \param pBuf [in] A pointer to the block data to write.
  \param size [in] A size of the block to write.
  */
  virtual void writeUncompressedBlock(const OdUInt8 *pBuf, OdUInt32 size);
};

SMARTPTR(OdPrcCompressedFilerDumper);

/** \details 
<group PRC_Input_Output_Operations> 
Class implements a compressed file dumper.
*/
class PRC_TOOLKIT OdPrcCompressedFilerDumper : public OdPrcCompressedFiler
{
  OdPrcCompressedFilerPtr m_pFiler;
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcCompressedFilerDumper);
  //DOM-IGNORE-END

  /** \details
  Returns the current position of the file pointer.
  */
  virtual OdUInt64 tell();
  
  /** \details
  Returns the length in bytes of the file associated with this object.
  */
  virtual OdUInt64 length();
  
  /** \details
  Moves the current position of the file pointer to the specified location and returns the new file position.

  \param offset [in] A number of bytes to move.
  \param seekType [in] A seek type, which can be one of the next types:
  
  <table>
    Value  Description
    SEEK_SET  Start of the file
    SEEK_CUR  Current position of the file pointer
    SEEK_END  End of the file
  </table>
  */
  virtual OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType seekType);

  /** \details
  Sets a new filer.

  \param pFiler [in] A pointer to a new filer to be set.
  */
  void setFiler(OdPrcCompressedFiler *pFiler);
  
  /** \details
  Returns the pointer to the current filer.
  */
  OdPrcCompressedFiler *getFiler();

  /** \details
  Saves the current filer position.
  */
  virtual void savePosition();
  
  /** \details
  Restores the saved filer position.
  */
  virtual void restorePosition();

  /** \details
  Writes bits to the filer stream.

  \param numBits [in] A number of bits.
  \param pBuf [in] A bits value.
  */
  virtual void writeBits(OdUInt32 numBits, OdUInt8 pBuf){}
  
  /** \details
  Reads bits from the filer stream.

  \param numBits [in] A number of bits.
  \param pBuf [out] A reference to the value to store bits.
  */
  virtual void readBits(OdUInt32 numBits, OdUInt8 &pBuf);
  
  /** \details
  Writes bits to the filer stream.

  \param numBits [in] A number of bits.
  \param pBuf [in] A value to write bits from.
  */
  virtual void writeBits(OdUInt32 numBits, OdUInt8 *pBuf){}
  
  /** \details
  Reads bits from the filer stream.

  \param numBits [in] A number of bits.

  \param pBuf [out] A pointer to a value to read bits into.
  */
  virtual void readBits(OdUInt32 numBits, OdUInt8 *pBuf);

  /** \details
  Writes a 32-bit unsigned integer value with a variable number of bits.

  \param bit_number [in] A number of bits.
  \param value [in] A 32-bit unsigned integer value to write.
  */
  virtual void writeUnsignedIntegerWithVariableBitNumber(OdUInt32 bit_number, OdUInt32 value){}
  
  /** \details
  Reads a 32-bit unsigned integer value with a variable number of bits of the filer stream and returns it.

  \param num_of_bits [in] A number of bits.
  */
  virtual OdUInt32 readUnsignedIntegerWithVariableBitNumber(OdUInt32 num_of_bits);

  /** \details
  Writes a number of bits occupied by a 32-bit unsigned integer value to the filer stream.

  \param n [in] Input value.
  */
  virtual void writeNumberOfBitsThenUnsignedInteger(OdUInt32 n){}
  
  /** \details
  Reads a number of bits occupied by a 32-bit unsigned integer and returns it.
  */
  virtual OdUInt32 readNumberOfBitsThenUnsignedInteger();

  /** \details
  Writes a 32-bit unsigned integer to the filer stream.

  \param i [in] A 32-bit unsigned integer value to write.
  \param pName [in] A name of a data field.
  */
  virtual void writeUnsignedInteger(OdUInt32 i, const char* pName = 0);
  
  /** \details
  Reads a 32-bit unsigned integer value from the filer stream and returns it.

  \param pName [in] A name of a data field.
  */
  virtual OdUInt32 readUnsignedInteger(const char* pName = 0);

  /** \details
  Writes a 32-bit integer value to the filer stream.

  \param i [in] A 32-bit integer value to write.
  */
  virtual void writeInteger(OdInt32 i){}
  
  /** \details
  Reads a 32-bit integer value from the filer stream and returns it.
  */
  virtual OdInt32 readInteger();

  /** \details
  Writes a double value to the filer stream.

  \param i [in] A double value to write.
  \param pName [in] A name of a data field.
  */
  virtual void writeDouble(double i, const char* pName = 0){}
  
  /** \details
  Reads a double value from the filer stream and returns it.

  \param pName [in] A name of a data field.
  */
  virtual double readDouble(const char* pName = 0);

  /** \details
  Writes a string value to the filer stream.

  \param str [in] A string value to write.

  \param pName [in] A name of a data field.
  */
  virtual void writeString(const OdString &str, const char* pName = 0){}
  
  /** \details
  Reads a string value from the filer stream and returns it.

  \param pName [in] A name of a data field.
  */
  virtual OdString readString(const char* pName = 0);

  /** \details
  Writes a boolean value to the filer stream.

  \param value [in] A boolean value to write.
  \param pName [in] A name of a data field.
  */
  virtual void writeBoolean(bool value, const char* pName = 0){}
  
  /** \details
  Reads a boolean value from the filer stream and returns it.

  \param pName [in] A name of a data field.
  */
  virtual bool readBoolean(const char* pName = 0);

  /** \details
  Writes 2D vector data to the filer stream.

  \param value [in] A 2D vector to write.
  */
  virtual void writeVector2d(const OdGeVector2d &value){}
  
  /** \details
  Reads 2D vector data from the filer stream and returns it.
  */
  virtual OdGeVector2d readVector2d();

  /** \details
  Writes 3D vector data to the filer stream.

  \param value [in] A 3D vector to write.
  */
  virtual void writeVector3d(const OdGeVector3d &value){}
  
  /** \details
  Reads 3D vector data from the filer stream and returns it.
  */
  virtual OdGeVector3d readVector3d();

  /** \details
  Writes 2D point data to the filer stream.

  \param value [in] A 2D point to write.
  */
  virtual void writePoint2d(const OdGePoint2d &value){}
  
  /** \details
  Reads 2D point data from the filer stream and returns it.
  */
  virtual OdGePoint2d readPoint2d();

  /** \details
  Writes 3D point data to the filer stream.

  \param value [in] A 3D point to write.
  */
  virtual void writePoint3d(const OdGePoint3d &value){}
  
  /** \details
  Reads 3D point data from the filer stream and returns it.
  */
  virtual OdGePoint3d readPoint3d();

  /** \details
  Writes a character to the filer stream.

  \param value [in] A character to write.
  */
  virtual void writeCharacter(char value){}
  
  /** \details
  Reads a character from the filer stream and returns it.
  */
  virtual char readCharacter();

  /** \details
  Reads an entity type from the filer stream and returns it.
  
  \param bStepBack [in] The step back flag value. If it is equal to true, the method returns a file pointer to the position where it was before reading entity type data.
  */
  virtual OdUInt32 readEntityType(bool bStepBack = false);
  
  /** \details
  Writes an entity type to the filer stream.

  \param type [in] An entity type to write.
  */
  virtual void writeEntityType(OdUInt32 type){}

  /** \details
  Reads a compressed entity type from the filer stream and returns it.
  
  \param bStepBack [in] The step back flag value. If it is equal to true, the method returns a file pointer to the position where it was before reading entity type data.
  \param isCurveOrSurface [in] A flag value that indicates whether the entity is a curve or a surface (if true).
  */
  virtual OdUInt32 readCompressedEntityType(bool bStepBack, bool *isCurveOrSurface = 0);
  
  /** \details
  Writes an entity type to the filer stream.

  \param isCurveType [in] A flag value that indicates whether the object is a curve or a surface.
  \param type [in] A compressed entity type to write.
  */
  virtual void writeCompressedEntityType(bool isCurveType, OdUInt32 type){}

  /** \details
  Reads a double value with variable number of bits from the filer stream and returns it.
  
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual double readDoubleWithVariableBitNumber(double tolerance, OdUInt32 number_of_bits);
  
  /** \details
  Writes a double value with variable number of bits to the filer stream.

  \param value [in] A double value to write.
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual void writeDoubleWithVariableBitNumber(double value, double tolerance, OdUInt32 number_of_bits);
  
  /** \details
  Reads a 3D point with variable number of bits from the filer stream and returns it.
  
  \param tolerance [in] A tolerance value. 
  \param number_of_bits [in] A number of bits.
  */
  virtual OdGePoint3d readPoint3DWithVariableBitNumber(double tolerance, OdUInt32 number_of_bits);
  
  /** \details
  Writes a 3D point with variable number of bits to the filer stream.

  \param point [in] A 3D point to write.
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual void writePoint3DWithVariableBitNumber(const OdGePoint3d &point, double tolerance, OdUInt32 number_of_bits);

  /** \details
  Reads a compressed array of 32-bit integer values from the filer stream and returns it.
  
  \param points_array [out] A reference to an integer array to store read values.
  */
  virtual void readCompressedIntegerArray ( OdInt32Array &points_array );
  
  /** \details
  Reads an array of characters from the filer stream and returns it.
  
  \param character_array [out] A reference to a character array to store read values.
  \param number_of_bits [in] A number of bits.
  \param bReadCompressStrategy [in] A bits compression strategy.
  */
  virtual void readCharacterArray ( OdInt8Array &character_array, unsigned number_of_bits, CompressedBitStrategy bReadCompressStrategy = kFromStream);
  
  /** \details
  Reads a 32-bit integer value with variable number of bits of the filer stream and returns it.

  \param bit_number [in] A number of bits.
  */
  virtual OdInt32 readIntegerWithVariableBitNumber(OdUInt32 bit_number);
  
  /** \details
  Reads an array of short integer values from the filer stream and returns it.
  
  \param normal_angle_array [out] A reference to a 16-bit integer array to store read values.
  \param number_of_bit [in] A number of bits.
  */
  virtual void readShortArray (OdUInt16Array &normal_angle_array, OdUInt32 number_of_bit);
  
  /** \details
  Reads a compressed array of 32-bit integer values from the filer stream and returns it.
  
  \param integer_array [out] A reference to a 32-bit integer array to store read values.
  \param bReadCompressStrategy [in] A bits compression strategy.
  */
  virtual void readCompressedIndiceArray( OdInt32Array &integer_array, CompressedBitStrategy bReadCompressStrategy=kFromStream);

  /** \details
  Writes a compressed 32-bit integer array to the filer stream.

  \param points_array [in] A 32-bit integer array to write with compression.
  */
  virtual void writeCompressedIntegerArray (const OdInt32Array &points_array ){}
  
  /** \details
  Writes an array of characters to the filer stream.

  \param character_array [in] An array of characters to write.
  \param number_of_bits [in] A number of bits.
  \param bReadCompressStrategy [in] A bit compression strategy.
  */
  virtual void writeCharacterArray (const OdInt8Array &character_array, unsigned number_of_bits, CompressedBitStrategy bReadCompressStrategy = kFromStream){}
  
  /** \details
  Writes a 32-bit integer value with variable number of bits to the filer stream.

  \param value [in] A 32-bit integer value to write.
  \param bit_number [in] A number of bits.
  */
  virtual void writeIntegerWithVariableBitNumber(OdInt32 value, OdUInt32 bit_number){}
  
  /** \details
  Writes an array of short integer values to the filer stream.

  \param normal_angle_array [in] An array of short integer values to write.
  \param number_of_bit [in] A number of bits.
  */
  virtual void writeShortArray (const OdUInt16Array &normal_angle_array, OdUInt32 number_of_bit){}
  
  /** \details
  Writes a compressed array of 32-bit integer values to the filer stream.

  \param integer_array [in] An array of 32-bit integer values to write with compression.
  \param bReadCompressStrategy [in] A bits compression strategy.
  */
  virtual void writeCompressedIndiceArray(const OdInt32Array &integer_array, CompressedBitStrategy bReadCompressStrategy=kFromStream){}
};

SMARTPTR(OdPrcLowLevelDumper);

/** \details 
<group PRC_Input_Output_Operations> 
Class stores data of a low level file dumper.
*/
class PRC_TOOLKIT OdPrcLowLevelDumper : public OdRxObject
{
protected:
  OdPrcCompressedFilerDumperPtr   m_RWFiler;
  OdPrcUncompressedFilerDumperPtr m_RWFilerBase;

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcLowLevelDumper);
  //DOM-IGNORE-END

  /** \details
  Sets a new compressed filer.

  \param pFiler [in] A new filer to be set.
  */
  void setFiler(OdPrcCompressedFiler *pFiler);
  
  /** \details
  Sets a new base uncompressed filer.

  \param pFilerBase [in] A new base uncompressed filer to be set.
  */
  void setFiler(OdPrcUncompressedFiler *pFilerBase);

  /** \details
  Returns the current filer.
  */
  OdPrcFiler *getFiler();
  
  /** \details
  Returns the current compressed filer.
  */
  OdPrcCompressedFiler *getRWFiler();
  
  /** \details
  Returns the current uncompressed base filer.
  */
  OdPrcUncompressedFiler *getRWFilerBase();
};

#endif // _PRCLOWLEVELDUMPER_INCLUDED_


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

#ifndef _PRCRWFILER_INCLUDED_
#define _PRCRWFILER_INCLUDED_ 
 

class OdPrcCompressedFiler;

#include "PrcFiler.h"
#include "OdStreamBuf.h"
#include "FlatMemStream.h"
#include "UInt8Array.h"
#include "PrcObjectId.h"

SMARTPTR(OdPrcCompressedFiler);


/** \details 
<group PRC_Input_Output_Operations>

Abstract class for input/output operations with compressed data.
*/
class PRC_TOOLKIT OdPrcCompressedFiler : public OdPrcFiler
{
protected:

  /** \details 
  Create an instance of a filer for compressed data. 
  \param authoring_version [in] An authoring version of PRC format data. 
  */
  OdPrcCompressedFiler(OdUInt32 authoring_version);

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcCompressedFiler)
  //DOM-IGNORE-END

  /** \details
  Saves the current position in a file.
  */
  virtual void savePosition() = 0;
  
  /** \details
  Restores previously saved position in a file.
  */
  virtual void restorePosition() = 0;

  /** \details
  Writes a set of bits to the file.

  \param numBits [in] A number of bits to write.

  \param pBuf [in] A value to extract bits from.
  */
  virtual void writeBits(OdUInt32 numBits, OdUInt8 pBuf) = 0;
  
  /** \details
  Writes a set of bits to the file.

  \param numBits [in] The number of bits to write.

  \param pBuf [in] A pointer to a value to extract bits from.
  */
  virtual void writeBits(OdUInt32 numBits, OdUInt8 *pBuf)= 0;
  
  /** \details
  Reads a set of bits from a file.

  \param numBits [in] A number of bits.

  \param pBuf [out] A reference to a buffer where to store bit values.
  */
  virtual void readBits(OdUInt32 numBits, OdUInt8 &pBuf) = 0;
  
  /** \details
  Reads a set of bits from a file.

  \param numBits [in] A number of bits.

  \param pBuf [out] A pointer to a buffer to store bit values.
  */
  virtual void readBits(OdUInt32 numBits, OdUInt8 *pBuf) = 0;

  /** \details
  Writes an unsigned integer value with variable number of bits.

  \param bit_number [in] A number of bits.

  \param value [in] An integer value to write.
  */
  virtual void writeUnsignedIntegerWithVariableBitNumber(OdUInt32 bit_number, OdUInt32 value) = 0;
  
  /** \details
  Reads an unsigned integer value with variable number of bits from a file.
  \param num_of_bits [in] A number of bits.
  \returns An unsigned 32-bit integer value that was read.
  */
  virtual OdUInt32 readUnsignedIntegerWithVariableBitNumber(OdUInt32 num_of_bits) = 0;

  /** \details
  Writes to a file the number of bits needed to store an unsigned integer value.

  \param n [in] An unsigned integer value.
  */
  virtual void writeNumberOfBitsThenUnsignedInteger(OdUInt32 n) = 0;
  
  /** \details
  Reads from a file the number of bits needed to store an unsigned integer value.
  */
  virtual OdUInt32 readNumberOfBitsThenUnsignedInteger() = 0;

  /** \details
  Writes an unsigned integer value to a file.

  \param i [in] An unsigned integer value to write.
  \param pName [in] A name of a field. Not used.
  */
  virtual void writeUnsignedInteger(OdUInt32 i, const char* pName = 0) = 0;
  
  /** \details
  Reads an unsigned 32-bit integer value from the file.
  \param pName [in] A raw pointer to the name of the value.
  \returns An unsigned 32-bit integer value that was read.
  */
  virtual OdUInt32 readUnsignedInteger(const char* pName = 0) = 0;

  /** \details
  Writes an integer value to a file.

  \param i [in] An integer value to write.
  */
  virtual void writeInteger(OdInt32 i) = 0;
  
  /** \details
  Reads an integer value from the file and returns it.
  */
  virtual OdInt32 readInteger() = 0;

  /** \details
  Writes a double value to a file.

  \param i [in] A double value to write.
  \param pName [in] A name of a field. Not used.
  */
  virtual void writeDouble(double i, const char* pName = 0) = 0;
  
  /** \details
  Returns a double value from a file.

  \param pName [in] A name of a field. Not used.

  \returns Value as a double value.
  */
  virtual double readDouble(const char* pName = 0) = 0;

  /** \details
  Writes a string value to a file.

  \param str [in] A string value to write.
  \param pName [in] A name of a field. Not used.
  */
  virtual void writeString(const OdString &str, const char* pName = 0) = 0;
  
  /** \details
  Reads a string value from a file and returns it.

  \param pName [in] A name of a field. Not used.
  */
  virtual OdString readString(const char* pName = 0) = 0;

  /** \details
  Writes a boolean value to a file.

  \param value [in] A boolean value to write.
  \param pName [in] A name of a field. Not used.
  */
  virtual void writeBoolean(bool value, const char* pName = 0) = 0;
  
  /** \details
  Reads a boolean value from a file and returns it.

  \param pName [in] A name of a field. Not used.
  */
  virtual bool readBoolean(const char* pName = 0) = 0;
  
  /** \details
  Writes 2D vector data to a file.

  \param value [in] 2D vector data to write.
  */
  virtual void writeVector2d(const OdGeVector2d &value) = 0;
  
  /** \details
  Reads 2D vector data from a file and returns it.
  */
  virtual OdGeVector2d readVector2d() = 0;

  /** \details
  Writes 3D vector data to a file.

  \param value [in] 3D vector data to write.
  */
  virtual void writeVector3d(const OdGeVector3d &value) = 0;
  
  /** \details
  Reads 3D vector data from a file and returns it.

  \returns 3D vector data as an OdGeVector3d object.
  */
  virtual OdGeVector3d readVector3d() = 0;

  /** \details
  Writes 2D point data to a file.

  \param value [in] 2D point data to write.
  */
  virtual void writePoint2d(const OdGePoint2d &value) = 0;
  
  /** \details
  Reads 2D point data from a file and returns it.
  */
  virtual OdGePoint2d readPoint2d() = 0;

  /** \details
  Writes 3D point data to a file.

  \param value [in] 3D point data to write.  
  */
  virtual void writePoint3d(const OdGePoint3d &value) = 0;
  
  /** \details
  Reads 3D point data from a file and returns it.
  */
  virtual OdGePoint3d readPoint3d() = 0;

  /** \details
  Writes a character to a file.

  \param value [in] A character to write.
  */
  virtual void writeCharacter(char value) = 0;
  
  /** \details
  Reads a character from a file and returns it.
  */
  virtual char readCharacter() = 0;

  /** \details
  Reads an entity type from a file and returns it.
  
  \param bStepBack [in] The step back flag value. If it is equal to true, method returns file pointer to the position where it was before reading entity type data.
  */
  virtual OdUInt32 readEntityType(bool bStepBack = false) = 0;
  
  /** \details
  Writes the entity type to a file.

  \param type [in] An entity type to write.
  */
  virtual void writeEntityType(OdUInt32 type) = 0;

  /** \details
  Reads a compressed entity type from a file and returns it.
  
  \param bStepBack [in] The step back flag value. If it is equal to true, method returns file pointer to the position where it was before reading entity type data.
  \param isCurveOrSurface [in] A flag that indicates whether an object is a curve or a surface.
  */
  virtual OdUInt32 readCompressedEntityType(bool bStepBack, bool *isCurveOrSurface = 0) = 0;
  
  /** \details
  Writes an entity type to a file.

  \param isCurveType [in] A flag that indicates whether the object is a curve or a surface.
  \param type [in] A compressed entity type.
  */
  virtual void writeCompressedEntityType(bool isCurveType, OdUInt32 type) = 0;

  /** \details
  Reads a double value with a variable number of bits from a file and returns it.
  
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual double readDoubleWithVariableBitNumber(double tolerance, OdUInt32 number_of_bits) = 0;
  
  /** \details
  Writes a double value with a variable number of bits to a file.

  \param value [in] A double value to write.
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual void writeDoubleWithVariableBitNumber(double value, double tolerance, OdUInt32 number_of_bits) = 0;
  
  /** \details
  Reads a 3D point with a variable number of bits from a file and returns it.
  
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual OdGePoint3d readPoint3DWithVariableBitNumber(double tolerance, OdUInt32 number_of_bits) = 0;
  
  /** \details
  Writes a 3D point with a variable number of bits to a file.

  \param point [in] A 3D point to write.
  \param tolerance [in] A tolerance value.
  \param number_of_bits [in] A number of bits.
  */
  virtual void writePoint3DWithVariableBitNumber(const OdGePoint3d &point, double tolerance, OdUInt32 number_of_bits) = 0;

  /** \details
  Types of bit compression strategy.
  */
  enum CompressedBitStrategy
  {
    /** Stream compression.*/
    kFromStream     = 0,    
    /** Huffman compression algorithm.*/
    kUseHuffman     = 1,    
    /** No compression.*/
    kNoCompression  = 2  
  };
  
  /** \details
  Reads a compressed array of integer values from a file and returns it.
  
  \param points_array [out] A reference to an OdInt32Array object to store the read array.
  */
  virtual void readCompressedIntegerArray ( OdInt32Array &points_array ) = 0;
  
  /** \details
  Reads an array of characters from a file and returns it.
      
  \param character_array [out] A reference to an OdInt8Array object to store the read array.
  \param number_of_bits [in] A number of bits.
  \param bReadCompressStrategy [in] A strategy of bit compression.
  */
  virtual void readCharacterArray ( OdInt8Array &character_array, unsigned number_of_bits, CompressedBitStrategy bReadCompressStrategy = kFromStream) = 0;
  
  /** \details
  Reads an integer value with a variable number of bits from a file and returns it.

  \param bit_number [in] A number of bits.
  */
  virtual OdInt32 readIntegerWithVariableBitNumber(OdUInt32 bit_number) = 0;
  
  /** \details
  Reads an array of short integer values from a file.
  
  \param normal_angle_array [out] Output compressed array of integer values.

  \param number_of_bit [in] Input number of bits.
  */
  virtual void readShortArray (OdUInt16Array &normal_angle_array, OdUInt32 number_of_bit) = 0;
  
  /** \details 
  Reads a compressed array of 32-bit integer values from a file.
  
  \param integer_array [out] A reference to an OdInt32Array object to store the read array.
  \param bReadCompressStrategy [in] A strategy of bits compression.
  */
  virtual void readCompressedIndiceArray( OdInt32Array &integer_array, CompressedBitStrategy bReadCompressStrategy=kFromStream) = 0;

  /** \details
  Writes a compressed array of integer values to a file.

  \param points_array [in] A compressed array of integer values to write.
  */
  virtual void writeCompressedIntegerArray (const OdInt32Array &points_array ) = 0;
  
  /** \details
  Writes an array of characters to a file.

  \param character_array [in] An array of characters to write.
  \param number_of_bits [in] A number of bits.
  \param bReadCompressStrategy [in] A strategy of bits compression.
  */
  virtual void writeCharacterArray (const OdInt8Array &character_array, unsigned number_of_bits, CompressedBitStrategy bReadCompressStrategy = kFromStream) = 0;
  
  /** \details
  Writes an integer value with variable number of bits to a file.

  \param value [in] An integer value to write.
  \param bit_number [in] A number of bits.
  */
  virtual void writeIntegerWithVariableBitNumber(OdInt32 value, OdUInt32 bit_number) = 0;
  
  /** \details
  Writes an array of short integer values to a file.

  \param normal_angle_array [in] An array of short integer values to write.
  \param number_of_bit [in] A number of bits.
  */
  virtual void writeShortArray (const OdUInt16Array &normal_angle_array, OdUInt32 number_of_bit) = 0;
  
  /** \details
  Writes a compressed array of integer values to a file.

  \param integer_array [in] A compressed array of integer values to write.
  \param bReadCompressStrategy [in] A strategy of bits compression.
  */
  virtual void writeCompressedIndiceArray(const OdInt32Array &integer_array, CompressedBitStrategy bReadCompressStrategy=kFromStream) = 0;
};

/** \details
Reads an array of double values from a file.

\param array [out] A reference to an array of double values to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readDoubleArray(OdGeDoubleArray &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of double values from a file.

\param array [out] A reference to an array of double values to store read data.
\param pStream [in] A pointer to an input file stream.
\param num [in] A number of elements to read.
*/
void readDoubleArray(OdGeDoubleArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Reads an array of unsigned 32-bit integer values from a file.

\param array [out] A reference to an array of unsigned 32-bit integer values to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readUInt32Array(OdUInt32Array &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of 32-bit integer values from a file.

\param array [out] A reference to an array of 32-bit integer values to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readInt32Array(OdInt32Array &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of 32-bit integer values from a file.

\param array [out] A reference to an array of 32-bit integer values to store read data.
\param pStream [in] A pointer to an input file stream.
\param num [in] A number of elements to read.
*/
void readInt32Array(OdInt32Array &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Reads an array of strings from a file.

\param array [out] A reference to an array of string values to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readStringArray(OdStringArray &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of 3D vectors from a file.

\param array [out] A reference to an array of 3D vectors to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readVector3dArray(OdGeVector3dArray &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of 3D vectors from a file.

\param array [out] A reference to an array of 3D vectors to store read data.
\param pStream [in] A pointer to an input file stream.
\param num [in] A number of elements.
*/
void readVector3dArray(OdGeVector3dArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Reads an array of 2D points from a file.

\param array [out] A reference to an array of 2D points to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readPoint2dArray(OdGePoint2dArray &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of 2D points from a file.

\param array [out] A reference to an array of 2D points to store read data.
\param pStream [in] A pointer to an input file stream.
\param num [in] A number of elements.
*/
void readPoint2dArray(OdGePoint2dArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Reads an array of 3D points from a file.

\param array [out] A reference to an array of 3D points to store read data.
\param pStream [in] A pointer to an input file stream.
*/
void readPoint3dArray(OdGePoint3dArray &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of 3D points from a file.

\param array [out] A reference to an array of 3D points to store read data.
\param pStream [in] A pointer to an input file stream.
\param num [in] A number of elements.
*/
void readPoint3dArray(OdGePoint3dArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Writes an array of double values to a stream.

\param array [in] An array of double values to write.
\param pStream [in] A pointer to an output stream.
*/
void writeDoubleArray(const OdGeDoubleArray &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of double values to a stream.

\param array [in] An array of double values to write.
\param pStream [in] A pointer to an output stream.
\param num [in] A number of elements.
*/
void writeDoubleArray(const OdGeDoubleArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Writes an array of unsigned 32-bit integer values to a stream.

\param array [in] An array of unsigned 32-bit integer values to write.
\param pStream [in] A pointer to an output stream.
*/
void writeUInt32Array(const OdUInt32Array &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of 32-bit integer values to a stream.

\param array [in] An array of 32-bit integer values to write.
\param pStream [in] A pointer to an output stream.
*/
void writeInt32Array(const OdInt32Array &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of 32-bit integer values to a stream.

\param array [in] An array of 32-bit integer values to write.
\param pStream [in] A pointer to an output stream.
\param num [in] A number of elements.
*/
void writeInt32Array(const OdInt32Array &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Writes an array of strings to a stream.

\param array [in] An array of string values to write.
\param pStream [in] A pointer to an output stream.
*/
void writeStringArray(const OdStringArray &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of 3D vectors to a stream.

\param array [in] An array of 3D vectors to write.
\param pStream [in] A pointer to an output stream.
*/
void writeVector3dArray(const OdGeVector3dArray &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of 3D vectors to a stream.

\param array [in] An array of 3D vectors to write.
\param pStream [in] A pointer to an output stream.
\param num [in] A number of elements.
*/
void writeVector3dArray(const OdGeVector3dArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Writes an array of 2D points to a stream.

\param array [in] An array of 2D points to write.
\param pStream [in] A pointer to an output stream.
*/
void writePoint2dArray(const OdGePoint2dArray &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of 2D points to a stream.

\param array [in] An array of 2D points to write.
\param pStream [in] A pointer to an output stream.
\param num [in] A number of elements.
*/
void writePoint2dArray(const OdGePoint2dArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Writes an array of 3D points to a stream.

\param array [in] An array of 3D points to write.
\param pStream [in] A pointer to an output stream.
*/
void writePoint3dArray(const OdGePoint3dArray &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of 3D points to a stream.

\param array [in] An array of 3D points to write.
\param pStream [in] A pointer to an output stream.
\param num [in] A number of elements.
*/
void writePoint3dArray(const OdGePoint3dArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Reads an array of double values from a compressed data stream and converts it into a float values array.
\param array    [out] A reference to an array of float values to store read data.
\param pStream  [in] A pointer to an input compressed data stream.
*/
void readFloatArrayAsDoubleArray(OdFloatArray &array, OdPrcCompressedFiler *pStream);

/** \details
Reads an array of double values from a compressed data stream and converts it into a float values array.
\param array    [out] A reference to an array of float values to store read data.
\param pStream  [in] A pointer to an input compressed data stream.
\param num      [in] A quantity of values to be read from a data stream.
*/
void readFloatArrayAsDoubleArray(OdFloatArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
Writes an array of float values as an array of double values to a compressed data stream .
\param array   [in] A float array to be written .
\param pStream [in] A pointer to an output compressed data stream.
\remarks 
Each element of the input float array is converted into double value before writing to the data stream.
*/
void writeFloatArrayAsDoubleArray(const OdFloatArray &array, OdPrcCompressedFiler *pStream);

/** \details
Writes an array of float values as an array of double values to a compressed data stream .
\param array   [in] A float array to be written.
\param pStream [in] A pointer to an output compressed data stream.
\param num     [in] A quantity of values to be written to a data stream.
\remarks 
Each element of the input float array is converted into double value before writing to the data stream.
*/
void writeFloatArrayAsDoubleArray(const OdFloatArray &array, OdPrcCompressedFiler *pStream, OdUInt32 num);

/** \details
A template function that reads an array of a specified data type from a compressed data stream.
\param array   [out]  A reference to an array to store read data.
\param pStream [in]   A pointer to an input compressed data stream.
*/
template<class T> void readArray(T &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num;

  num = pStream->readUnsignedInteger("ArraySize");
  array.resize(num);
  for (i=0; i<num; ++i)
  {
    array[i].prcIn(pStream);
  }
}

/** \details
A template function that writes an array of a specified data type to a compressed data stream.
\param array   [in] An array to be written.
\param pStream [in] A pointer to an output compressed data stream.
*/
template<class T> void writeArray(T &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num = array.size();

  pStream->writeUnsignedInteger(num, "ArraySize");
  for (i=0; i<num; ++i)
  {
    array[i].prcOut(pStream);
  }
}

/** \details
A template function that reads an array of a specified data type, represented with pointers, to a compressed data stream.
\param array   [in] An array of pointers, which refer to data to be written.
\param pStream [in] A pointer to an output compressed data stream.
*/
template<class T> void readPtrArray(OdArray< OdSmartPtr<T> > &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num;

  num = pStream->readUnsignedInteger("ArraySize");
  array.resize(num);
  for (i = 0; i < num; ++i)
  {
    array[i] = T::createObject();
    array[i]->prcIn(pStream);
  }
}

/** \details
A template function that writes an array of a specified data type, represented with pointers, to a compressed data stream.
\param array   [in] An array of pointers, which refer to data to be written.
\param pStream [in] A pointer to an output compressed data stream.
*/
template<class T> void writePtrArray(OdArray< OdSmartPtr<T> > &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num = array.size();

  pStream->writeUnsignedInteger(num, "ArraySize");
  for (i=0; i<num; ++i)
  {
    array[i]->prcOut(pStream);
  }
}

/** \details
A template function that writes an array of a specified objects, represented with object identifiers, to a compressed data stream.
\param array   [in] An array of object identifiers, which refer to objects to be written.
\param pStream [in] A pointer to an output compressed data stream.
*/
template<class T> void writeIdsArray(const OdPrcObjectIdArray &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num = array.size();

  pStream->writeUnsignedInteger(num, "ArraySize");
  for (i=0; i<num; ++i)
  {
    OdSmartPtr<T> pObj = array[i].safeOpenObject(); // to check that id has proper type.
    pObj->prcOut(pStream);
  }
}

/** \details
A template function that reads an array of objects from a compressed data stream and creates an array of their identifiers.
\param array   [out]  A reference to an array of object identifiers to store read data.
\param pStream [in]   A pointer to an input compressed data stream.
*/
template<class T> void readIdsArray(OdPrcObjectIdArray &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num;

  num = pStream->readUnsignedInteger("ArraySize");
  array.resize(num);
  for (i=0; i<num; ++i)
  {
    OdSmartPtr<T> pObj = T::createObject();
    pObj->prcIn(pStream);
    array[i] = pObj->objectId();
  }
}

/** \details
A template function that reads objects data from a compressed data stream and creates an array of their identifiers.
\param array   [out]  A reference to an array to store read data.
\param pStream [in]   A pointer to an input compressed data stream.
*/
template<class T, class TArr> void readBaseArray(TArr &array, OdPrcCompressedFiler *pStream)
{
  OdUInt32 i, num;

  num = pStream->readUnsignedInteger("ArraySize");
  array.resize(num);
  for (i = 0; i<num; ++i)
  {
    array[i] = T::read(pStream);
  }
}

#endif //_PRCRWFiler_INCLUDED_


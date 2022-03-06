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

#ifndef _ODXDATAITERATOR_INCLUDED_
#define _ODXDATAITERATOR_INCLUDED_

class OdXDataIteratorImpl;
#include "ResBuf.h"
#include "DbBaseDatabase.h"
class OdDbDxfFiler;


/** Iterator that provides access to the extended data attached to an OdDbObject. 
An OdXDataIterator instance allows the user to traverse, read, and edit the 
extended data associated with a specified application.  Extended data for a 
particular application consists of a set of pairs, where each pair contains
a DXF group code, and a data value whose type is dependent on the group code.
An OdXDataIterator maintains a current position within the the list of pairs, 
and provides read/write access to the pair at the current position.
@see OdDbObject::openXData
*/
class TOOLKIT_EXPORT OdXDataIterator : public OdRxObject
{
public:
   ODRX_DECLARE_MEMBERS(OdXDataIterator);
   
   /** Destructor.
   */
   virtual ~OdXDataIterator();
   
   virtual OdResBufPtr readItem(OdDbBaseDatabase* pDb);
   virtual void writeItem(const OdResBuf* pRb, OdDbBaseDatabase* pDb);
   
   /** Resets the current position of this iterator to the beginning of the extended data.
   */
   void start() const;
   
   /** Move the current position to the group code as resType - 1000.  Seek from
   beginning with flag bFromStart
   */
   bool seek(int resType, bool bFromStart = false) const;
   
   /** Search for group code with value equal to string
   */
   bool seek(int resType, const OdChar* value, bool bFromStart = false) const;
   
   /** Returns true if the current position of this iterator does not reference a valid
       extended data pair (either there is no extended data, or the iterator has traversed
       past the end of the extended data).
   */
   bool done() const;
   
   /** Returns true if the current position of this iterator does not reference a valid
       extended data pair (either there is no extended data, or the iterator has traversed
       past the end of the extended data).
   */
   bool atEndOfApp() const;
   
   /** Increments the current position of this iterator to the next data pair.
   */
   void next() const;
   
   /** Returns the group code of the current pair.  The OdDxfCode::_getType() function
   can be used to determine the type of data associated with a group code.
   */
   int  curRestype() const;
   
   /** Returns the string data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Name or OdDxfCode::String.
   */
   OdString getString() const;
   
   /** Returns the bool data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Bool.
   */
   bool     getBool() const;
   
   /** Returns the OdInt8 data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Integer8.
   */
   OdInt8   getInt8() const;
   
   /** Returns the OdInt16 data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Integer16.
   */
   OdInt16  getInt16() const;
   
   /** Returns the OdInt32 data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Integer32.
   */
   OdInt32  getInt32() const;
   
   /** Returns the OdInt64 data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Integer64.
   */
   OdInt64  getInt64() const;

   /** Returns the double data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Double.
   */
   double   getDouble() const;
   
   /** Returns the angle data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Angle.
   */
   double   getAngle() const;
   
   /** Returns the OdGePoint3d data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Point.
   */
   OdGePoint3d& getPoint3d(OdGePoint3d& pt) const;
   
   /** Returns the binary data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::BinaryChunk.
   @param binary (O) Receives a the binary data from the current pair.
   */
   void getBinaryChunk(OdBinaryData& binary) const;
   
   /** Returns the handle data value of the current pair.  This function should be called 
   when the data type of the current pair is OdDxfCode::Handle.
   */
   OdDbHandle getHandle() const;
   
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setString(int gCode, const OdString& val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setBool(int gCode, bool val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setInt8(int gCode, OdInt8 val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setInt16(int gCode, OdInt16 val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setInt32(int gCode, OdInt32 val);

   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setInt64(int gCode, OdInt64 val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setDouble(int gCode, double val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setAngle(int gCode, double val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setPoint3d(int gCode, const OdGePoint3d& val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setBinaryChunk(int gCode, const OdBinaryData& val);
   
   /** Sets the data for the current pair, creating the current pair if one does not already 
   exist.  
   */
   void setHandle(int gCode, const OdDbHandle& val);
   
   /** TBC.
   */
   bool dxfInItem(OdDbDxfFiler* pFiler);

   /** TBC.
   */
   bool dxfOutItem(OdDbDxfFiler* pFiler);


   OdUInt32 position() const;

   void setPosition(OdUInt32 nPosition);

   void cut(OdUInt32 nStartPos, OdUInt32 nEndPos);

protected:
/** Constructor.
   */
   OdXDataIterator(OdXDataIteratorImpl* pIterImpl);
   
   /** Constructor.
   */
   OdXDataIterator();
   friend class OdXDataIteratorImpl;   
   OdXDataIteratorImpl* m_pImpl;
};

typedef OdSmartPtr<OdXDataIterator> OdXDataIteratorPtr;

#endif // _ODXDATAITERATOR_INCLUDED_

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

#ifndef _EX_PRCDUMPER_H_
#define _EX_PRCDUMPER_H_

#include "RxObject.h"

#include "Gi/GiDrawable.h"
#include "RxVariant.h"
#include "PrcFile.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeExtents3d.h"
#include "Ge/GeQuaternion.h"
#include "Gs/GsDefs.h"
#include "CmColorBase.h"
#include "OdBinaryData.h"

class OdExPrcDumper : public OdRxObject
{
public:
  virtual void dumpFieldName( const OdString& fieldName ) = 0;
  virtual void dumpFieldValue( const OdString& fieldName ) = 0;
  virtual void dumpFieldType( const OdString& fieldName ) = 0;

  // output for different types
  inline void writeFieldValue( const OdString& name, const OdString& value );
  inline void writeFieldValue( const OdString& name, OdUInt16 value );
  inline void writeFieldValueHex( const OdString& name, OdUInt16 value );
  inline void writeFieldValue( const OdString& name, OdUInt32 value );
  inline void writeFieldValueHex( const OdString& name, OdUInt32 value );
  inline void writeFieldValue( const OdString& name, double value );
  inline void writeFieldValue( const OdString& name, OdGePoint2d const& value );
  inline void writeFieldValue( const OdString& name, OdGePoint3d const& value );
  inline void writeFieldValue( const OdString& name, OdGeVector3d const& value );
  inline void writeFieldValue( const OdString& name, OdCmEntityColor const& value );
  inline void writeFieldValue( const OdString& name, OdUInt64 value );
  inline void writeFieldValueHex( const OdString& name, OdUInt64 value );
  inline void writeFieldValue( const OdString& name, OdUInt8 value );
  inline void writeFieldValueHex( const OdString& name, OdUInt8 value );
  inline void writeFieldValue( const OdString& name, bool value );
  inline void writeFieldValue( const OdString& name, OdInt16 value );
  inline void writeFieldValue( const OdString& name, OdInt32 value );
  inline void writeFieldValue( const OdString& name, int value );
  inline void writeFieldValue( const OdString& name, OdInt64 value );
  inline void writeFieldValue( const OdString& name, OdGeQuaternion const& value );
  inline void writeFieldValue( const OdString& name, OdGeMatrix2d const& value );
  inline void writeFieldValue( const OdString& name, OdGeMatrix3d const& value );
  inline void writeFieldValue( const OdString& name, OdGsDCRect const& value );
 // inline void writeFieldValue( const OdString& name, OdPrcElementId const& value );
  inline void writeFieldValue( const OdString& name, const OdVariant& value );
  inline void writeFieldValue( const OdString& name, OdGeExtents2d const& value );
  inline void writeFieldValue( const OdString& name, OdGeExtents3d const& value );
  inline void writeFieldValue( const OdString& name, const OdBinaryData& data );
  inline void writeFieldValue( const OdString& name, OdPrcUniqueId value);
  inline void writeFieldValue( const OdString& name, OdPrcObjectId value);
};

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdPrcObjectId value)
{
  dumpFieldName( name );
  dumpFieldValue( value.getHandle().ascii() );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdPrcUniqueId value)
{
  dumpFieldName( name );
  OdString val;
  OdUInt32 id0, id1, id2, id3;
  value.getID(id0, id1, id2, id3);
  val.format( L"%.8X %.8X %.8X %.8X", id0, id1, id2, id3);
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, const OdString& value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%s", value.c_str() );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdUInt16 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%u", OdUInt32( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValueHex( const OdString& name, OdUInt16 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%04X", OdUInt32( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdUInt32 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%u", value );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValueHex( const OdString& name, OdUInt32 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%08X", value );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, double value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%g", value );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGePoint2d const& value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%g; %g", value.x, value.y );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGePoint3d const& value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%g; %g; %g", value.x, value.y, value.z );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGeVector3d const& value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%g; %g; %g", value.x, value.y, value.z );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdCmEntityColor const& value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"R: %u G: %u B: %u",
    unsigned( value.red() ), unsigned( value.green() ), unsigned( value.blue() ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdUInt64 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%I64u", value );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValueHex( const OdString& name, OdUInt64 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%X", value );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdUInt8 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%u", unsigned( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValueHex( const OdString& name, OdUInt8 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%02X", unsigned( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, bool value )
{
  dumpFieldName( name );
  dumpFieldValue( value ? L"true" : L"false" );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdInt16 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%i", int( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdInt32 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%li", int( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, int value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%li", value );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdInt64 value )
{
  dumpFieldName( name );
  OdString val;
  val.format( L"%iI64", int( value ) );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGeQuaternion const& value )
{
  dumpFieldName( name );

  OdString val;
  val.format( L"%g; %g; %g; %g", value.w, value.x, value.y, value.z );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGeMatrix2d const& value )
{
  dumpFieldName( name );

  OdString val;
  val.format( L"%g; %g; %g; %g", value[ 0 ][ 0 ], value[ 1 ][ 0 ], value[ 0 ][ 1 ], value[ 1 ][ 1 ] );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGeMatrix3d const& value )
{
  dumpFieldName( name );

  OdString val;
  val.format( L"%g; %g; %g; %g; %g; %g; %g; %g; %g",
    value( 0, 0 ), value( 1, 0 ), value( 2, 0 ), 
    value( 0, 1 ), value( 1, 1 ), value( 2, 1 ), 
    value( 0, 2 ), value( 1, 2 ), value( 2, 2 ) );
  dumpFieldValue( val );
}


inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdGsDCRect const& value )
{
  dumpFieldName( name );

  OdString val;
  val.format( L"( 0x%X; 0x%X ) - ( 0x%X; 0x%X )\n", value.m_min.x, value.m_min.y, value.m_max.x, value.m_max.y );

  dumpFieldValue( val );
}

/*
inline void OdExPrcDumper::writeFieldValue( const OdString& name, OdPrcElementId const& value )
{
  writeFieldValue(name, value.getHandle().ascii());
}*/

inline void OdExPrcDumper::writeFieldValue( const OdString& name, const OdVariant& val )
{
  switch( val.type() )
  {
  case OdVariant::kBool:
    writeFieldValue( name, val.getBool() );
    break;
  case OdVariant::kInt8:
    writeFieldValue( name, val.getInt8() );
    break;
  case OdVariant::kInt16:
    writeFieldValue( name, val.getInt16() );
    break;
  case OdVariant::kInt32:
    writeFieldValue( name, val.getInt32() );
    break;
  case OdVariant::kInt64:
    writeFieldValue( name, val.getInt64() );
    break;
  case OdVariant::kDouble:
    writeFieldValue( name, val.getDouble() );
    break;
  case OdVariant::kString:
    writeFieldValue( name, val.getString() );
    break;
  case OdVariant::kAnsiString:
    writeFieldValue( name, OdString(val.getAnsiString()) );
    break;
  }
}

inline void OdExPrcDumper::writeFieldValue( OdString const& name, OdGeExtents2d const& value )
{
  dumpFieldName( name );

  OdGePoint2d min = value.minPoint(), max = value.maxPoint();

  OdString val;
  val.format( L"Low point: %g; %g;  High point: %g; %g",
    min.x, min.y,
    max.x, max.y
    );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( OdString const& name, OdGeExtents3d const& value )
{
  dumpFieldName( name );

  OdGePoint3d min = value.minPoint(), max = value.maxPoint();

  OdString val;
  val.format( L"Low point: %g; %g; %g;  High point: %g; %g; %g",
    min.x, min.y, min.z,
    max.x, max.y, max.z
    );
  dumpFieldValue( val );
}

inline void OdExPrcDumper::writeFieldValue( const OdString& name, const OdBinaryData& data )
{
  OdString val, val_i;

  dumpFieldName( name + L" (Size)");
  val.format( L"%d", data.size() );
  dumpFieldValue( val );

  dumpFieldName( name );
  val.empty();
  unsigned outSize = odmin(64, data.size());
  for (unsigned i=0; i<outSize; ++i)
  {
    val_i.format( L"%02X ", (OdUInt32)data[i] );
    val += val_i;
  }
  dumpFieldValue( val );
}

#endif // _EX_PRCDUMPER_H_

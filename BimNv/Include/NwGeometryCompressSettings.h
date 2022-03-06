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

#ifndef __NWGEOMETRYCOMPRESSSETTINGS_H__
#define __NWGEOMETRYCOMPRESSSETTINGS_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"

class OdNwColor;

/** \details
  This class represents geometry compression settings.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryCompressSettings : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryCompressSettings);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwGeometryCompressSettings class.
  */
  OdNwGeometryCompressSettings();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryCompressSettings();

public:

  /** \details
    Sets the geometry precision.
  */
  void setPrecision(double);

  /** \details
    Returns the geometry precision.
    \returns Non-zero positive float if precision is reduced, or 0.0 otherwise.
  */
  double getPrecision() const;

  /** \details
    Sets geometry component compression flags as a bitset.
  */
  void setGeometryCompressedFlags(OdUInt32);
  
  /** \details
    Returns a bitset with flags indicating whether any part of the geometry component is compressed.
  */
  OdUInt32 getGeometryCompressedFlags() const;
  
  /** \details
    Sets the vertex compression flag.
  */
  void setGeometryVertexCompressed(bool);
  
  /** \details
    Checks whether vertexes are compressed.
    \returns true if vertexes are compressed, or false otherwise.
  */
  bool getGeometryVertexCompressed() const;
  
  /** \details
    Sets the normal compression flag.
  */
  void setGeometryNormalCompressed(bool);
  
  /** \details
    Checks whether normals are compressed.
    \returns true if normals are compressed, or false otherwise.
  */
  bool getGeometryNormalCompressed() const;
  
  /** \details
    Sets the color compression flag.
  */
  void setGeometryColorCompressed(bool);
  
  /** \details
    Checks whether colors are compressed.
    \returns true if colors are compressed, or false otherwise.
  */
  bool getGeometryColorCompressed() const;
  
  /** \details
    Sets the texture coordinate compression flag.
  */
  void setGeometryTexCoordCompressed(bool);
  
  /** \details
    Checks whether texture coordinates are compressed.
    \returns true if texture coordinates are compressed, or false otherwise.
  */
  bool getGeometryTexCoordCompressed() const;
  
  /** \details
    Sets the length compression flag.
  */
  void setGeometryLengthsCompressed(bool);
  
  /** \details
    Checks whether lengths are compressed.
    \returns true if lengths are compressed, or false otherwise.
  */
  bool getGeometryLengthsCompressed() const;
  
  /** \details
    Sets the index compression flag.
  */
  void setGeometryIndicesCompressed(bool);
  
  /** \details
    Checks whether indices are compressed.
    \returns true if indices are compressed, or false otherwise.
  */
  bool getGeometryIndicesCompressed() const;

  /** \details
    Sets the flag for normal precision reduction.
  */
  void setNormalsPrecisionReducedFlags(const OdUInt8);
  
  /** \details
    Checks whether the normal precision is reduced.
    \returns true if the normal precision is reduced, or false otherwise.
  */
  bool getNormalsPrecisionReduced() const;
  
  /** \details
    Returns a bitset with normal precision reduction flags.
  */
  OdUInt8 getNormalsPrecisionReducedFlags() const;
  
  /** \details
    Sets the color precision reduction flags.
  */
  void setColorsPrecisionReducedFlags(const OdUInt8);
  
  /** \details
    Checks whether the color precision is reduced.
    \returns true if the color precision is reduced, or false otherwise.
  */
  bool getColorsPrecisionReduced() const;
  
  /** \details
    Returns a bitset with color precision reduction flags.
  */
  OdUInt8 getColorsPrecisionReducedFlags() const;
  
  /** \details
    Sets the texture coordinate precision reduction flags.
  */
  void setTextureCoordinatesPecisionReducedFlags(const OdUInt8);
  
  /** \details
    Checks whether the texture coordinate precision is reduced.
    \returns true if the texture coordinate precision is reduced, or false otherwise.
  */
  bool getTextureCoordinatesPecisionReduced() const;
  
  /** \details
    Returns a bitset with texture coordinate precision reduction flags.
  */
  OdUInt8 getTextureCoordinatesPecisionReducedFlags() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for GeometryCompressSettings object pointers.
*/
typedef OdSmartPtr<OdNwGeometryCompressSettings> OdNwGeometryCompressSettingsPtr;

#endif //__NWGEOMETRYCOMPRESSSETTINGS_H__

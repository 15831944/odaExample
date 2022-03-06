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

#ifndef _ODTV_COMMONDATAACCESS_TREE_FILER_H_INCLUDED_ 
#define _ODTV_COMMONDATAACCESS_TREE_FILER_H_INCLUDED_

#include "Tv.h"
#include "RxModelTreeBaseNode.h"


class OdTvCDATreeFiler : public OdBaseHierarchyTreeFiler
{
public:
  OdTvCDATreeFiler(OdDbDwgFiler* pFiler, OdTvVSFVersion version);

  /** \details
    Reads the boolean value of the current item of this Filer object.

    \returns Returns the boolean value
  */
  virtual bool rdBool();

  /** \details
    Reads the double value of the current item of this Filer object.

    \returns Returns the double value
  */
  virtual double rdDouble();

  /** \details
    Reads the Int8 value of the current item of this Filer object.

    \returns Returns the Int8 value
  */
  virtual OdUInt8 rdInt8();

  /** \details
    Reads the UInt8 value of the current item of this Filer object.

    \returns Returns the UInt8 value
  */
  virtual OdUInt8 rdUInt8();

  /** \details
    Reads the Int16 value of the current item of this Filer object.

    \returns Returns the Int16 value
  */
  virtual OdUInt16 rdInt16();

  /** \details
    Reads the UInt16 value of the current item of this Filer object.

    \returns Returns the UInt16 value
  */
  virtual OdUInt16 rdUInt16();

  /** \details
    Reads the Int32 value of the current item of this Filer object.

    \returns Returns the Int32 value
  */
  virtual OdUInt32 rdInt32();

  /** \details
    Reads the UInt16 value of the current item of this Filer object.

    \returns Returns the UInt16 value
  */
  virtual OdUInt32 rdUInt32();

  /** \details
    Reads the Int64 value of the current item of this Filer object.

    \returns Returns the Int64 value
  */
  virtual OdInt64 rdInt64();

  /** \details
    Reads the UInt64 value of the current item of this Filer object.

    \returns Returns the UInt64 value
  */
  virtual OdInt64 rdUInt64();

  /** \details
    Reads the string value of the current item of this Filer object.

    \returns Returns the string value
  */
  virtual OdString rdString();

  /** \details
    Reads the AnsiString value of the current item of this Filer object.

    \returns Returns the string value
  */
  virtual OdAnsiString rdAnsiString();

  /** \details
    Reads the 2D point value of the current item of this Filer object.

    \returns Returns the 2D point value
  */
  virtual OdGePoint2d rdGePoint2d();

  /** \details
    Reads the 3D point value of the current item of this Filer object.

    \returns Returns the 3D point value
  */
  virtual OdGePoint3d rdGePoint3d();

  /** \details
    Reads the 2D vector value of the current item of this Filer object.

    \returns Returns the 2D vector value
  */
  virtual OdGeVector2d rdGeVector2d();

  /** \details
    Reads the 3D vector value of the current item of this Filer object.

    \returns Returns the 3D vector value
  */
  virtual OdGeVector3d rdGeVector3d();

  /** \details
    Reads the entity color object value of the current item of this Filer object.

    \returns Returns the entity color object value
  */
  virtual OdCmEntityColor rdCmEntityColor();

  /** \details
    Reads the transparency object value of the current item of this Filer object.

    \returns Returns the transparency object value
  */
  virtual OdCmTransparency rdCmTransparency();

  /** \details
    Writes the specified boolean value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrBool(const bool value);

  /** \details
    Writes the specified double value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrDouble(const double value);

  /** \details
    Writes the specified Int8 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrInt8(const OdInt8 value);

  /** \details
    Writes the specified UInt8 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrUInt8(const OdUInt8 value);

  /** \details
    Writes the specified Int16 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrInt16(const OdInt16 value);

  /** \details
    Writes the specified UInt16 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrUInt16(const OdUInt16 value);

  /** \details
    Writes the specified Int32 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrInt32(const OdInt32 value);

  /** \details
    Writes the specified UInt32 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrUInt32(const OdUInt32 value);

  /** \details
    Writes the specified Int64 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrInt64(const OdInt64 value);

  /** \details
    Writes the specified UInt64 value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrUInt64(const OdUInt64 value);

  /** \details
    Writes the specified string value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrString(const OdString& value);

  /** \details
    Writes the specified AnsiString value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrAnsiString(const OdAnsiString& value);

  /** \details
    Writes the specified 2D point value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrGePoint2d(const OdGePoint2d& value);

  /** \details
    Writes the specified 3D point value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrGePoint3d(const OdGePoint3d& value);

  /** \details
    Writes the specified 2D vector value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrGeVector2d(const OdGeVector2d& value);

  /** \details
    Writes the specified 3D vector value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrGeVector3d(const OdGeVector3d& value);

  /** \details
    Writes the specified the entity color object value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrCmEntityColor(const OdCmEntityColor& value);

  /** \details
    Writes the specified the transparency object value to this Filer object.

    \param value [in] Value to write.
  */
  virtual void wrCmTransparency(const OdCmTransparency& value);

  OdDbDwgFiler* getSourceFiler();
  OdTvVSFVersion getTvVersion() const;

private:
  OdDbDwgFiler* m_pFiler;
  OdTvVSFVersion m_version;
};

#endif //_ODTV_COMMONDATAACCESS_TREE_FILER_H_INCLUDED_


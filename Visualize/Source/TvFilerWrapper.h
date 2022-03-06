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

#ifndef ODTV_FILER_WRAPPER_H_INCLUDED_
#define ODTV_FILER_WRAPPER_H_INCLUDED_

#include "TD_PackPush.h"

#include "Tv.h"
#include "TvEntity.h"
#include "TvIObject.h"

#include "DbFiler.h"
#include "DbDatabase.h"
#include "../Core/Source/database/DbFilerController.h"

#include "../TvCore/Include/TvCoreFiler.h"

class ODTV_EXPORT OdTvFilerReferenceCallback
{
public:
  virtual void ownershipReference( const OdTvDbObjectId& value, bool bHard ) = 0;
  virtual void pointerReference( const OdTvDbObjectId& value, bool bHard ) = 0;
};

class ODTV_EXPORT OdTvCoreFilerWrapper : public OdTvDbDwgFiler
{
public:
  ODRX_DECLARE_MEMBERS( OdTvCoreFilerWrapper );
  OdTvCoreFilerWrapper();
  static OdRxObjectPtr createObject( const OdTvCoreFilerPtr pFiler );

  void setTvCoreFiler( OdTvCoreFilerPtr pFiler ) { m_pTvCoreFiler = pFiler; }

  virtual FilerType filerType() const { return m_filerType;  }
  virtual void setFilerType( FilerType type ) { m_filerType = type; }

  virtual OdTvDbDatabase* database() const { return m_pDatabase; }
  virtual void setDatabase( OdTvDbDatabase* pDb ) { m_pDatabase = pDb; }

  virtual bool isPersistentMode() const { return true; }

  virtual OdTvFilerReferenceCallback* setReferencesCallback( OdTvFilerReferenceCallback* pCall )
  {
    OdTvFilerReferenceCallback* pOld = m_pReferenceCall;
    m_pReferenceCall = pCall;
    return pOld;
  }

protected:
  OdTvCoreFilerPtr m_pTvCoreFiler;

  FilerType m_filerType;
  OdTvDbDatabase* m_pDatabase;

  OdTvFilerReferenceCallback* m_pReferenceCall;

public:
  //write methods
    /** \details
    Writes the specified bool value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrBool(
    bool value );

  /** \details
    Writes the specified string value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrString(
    const OdString& value );

  /** \details
    Writes the specified number of bytes to this Filer object.
    \param buffer [in]  array of bytes.
    \param numBytes [in]  Number of bytes.
  */
  virtual void wrBytes(
    const void* buffer,
    OdUInt32 numBytes );

  /** \details
    Writes the specified Int8 value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrInt8(
    OdInt8 value );

  /** \details
    Writes the specified UInt8 value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrUInt8(
    OdUInt8 value );

  /** \details
    Writes the specified Int16 value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrInt16(
    OdInt16 value );

  /** \details
    Writes the specified Int32 value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrInt32(
    OdInt32 value );

  /** \details
    Writes the specified Int64 value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrInt64(
    OdInt64 value );

  /** \details
    Writes the specified double value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrDouble( double value );

  /** \details
    Writes the specified handle value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrDbHandle(
    const OdDbHandle& value );

  /** \details
    Writes the specified SoftOwnershipId value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrSoftOwnershipId(
    const OdTvDbObjectId& value );

  /** \details
    Writes the specified HardOwnershipId value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrHardOwnershipId(
    const OdTvDbObjectId& value );

  /** \details
    Writes the specified SoftPointerId value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrSoftPointerId(
    const OdTvDbObjectId& value );

  /** \details
    Writes the specified HardPointerId value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrHardPointerId(
    const OdTvDbObjectId& value );

  /** \details
    Writes the specified 2D point value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrPoint2d(
    const OdGePoint2d& value );

  /** \details
    Writes the specified 3D point value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrPoint3d(
    const OdGePoint3d& value );

  /** \details
    Writes the specified 2D vector value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrVector2d(
    const OdGeVector2d& value );

  /** \details
    Writes the specified 3D vector value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrVector3d(
    const OdGeVector3d& value );

  /** \details
    Writes the specified 3D scale value to this Filer object.
    \param value [in]  Value.
  */
  virtual void wrScale3d(
    const OdGeScale3d& value );

  //read methods
  /** \details
    Returns the bool value of the current item of this Filer object.
  */
  virtual bool rdBool();

  /** \details
    Returns the string value of the current item of this Filer object.

  */
  virtual OdString rdString();


  /** \details
    Returns the specified number of bytes from this Filer object.
    \param buffer [out]  Receives the bytes.
    \param numBytes [in]  Number of bytes.
  */
  virtual void rdBytes(
    void* buffer,
    OdUInt32 numBytes );


  /** \details
    Returns the Int8 value of the current item of this Filer object.
  */
  virtual OdInt8 rdInt8();

  /** \details
    Returns the UInt8 value of the current item of this Filer object.
  */
  virtual OdUInt8 rdUInt8();

  /** \details
    Returns the Int16 value of the current item of this Filer object.
  */
  virtual OdInt16 rdInt16();

  /** \details
    Returns the Int32 value of the current item of this Filer object.
  */
  virtual OdInt32 rdInt32();

  /** \details
    Returns the Int64 value of the current item of this Filer object.
  */
  virtual OdInt64 rdInt64();

  /** \details
    Returns the double value of the current item of this Filer object.
  */
  virtual double rdDouble();

  /** \details
    Returns the handle value of the current item of this Filer object.
  */
  virtual OdDbHandle rdDbHandle();

  /** \details
    Returns the SoftOwnershipId value of the current item of this Filer object.
  */
  virtual OdTvDbObjectId rdSoftOwnershipId();

  /** \details
    Returns the HardOwnershipId value of the current item of this Filer object.
  */
  virtual OdTvDbObjectId rdHardOwnershipId();

  /** \details
    Returns the HardPointerId value of the current item of this Filer object.
  */
  virtual OdTvDbObjectId rdHardPointerId();

  /** \details
    Returns the SoftPointerId value of the current item of this Filer object.
  */
  virtual OdTvDbObjectId rdSoftPointerId();

  /** \details
    Returns the 2D point value of the current item of this Filer object.
  */
  virtual OdGePoint2d rdPoint2d();

  /** \details
    Returns the 3D point value of the current item of this Filer object.
  */
  virtual OdGePoint3d rdPoint3d();

  /** \details
    Returns the 2D vector value of the current item of this Filer object.
  */
  virtual OdGeVector2d rdVector2d();

  /** \details
    Returns the 3D vector value of the current item of this Filer object.
  */
  virtual OdGeVector3d rdVector3d();

  /** \details
    Returns the scale value of the current item of this Filer object.
  */
  virtual OdGeScale3d rdScale3d();

  //other
  /** \details
    Moves the I/O pointer to the specified location in this Filer object.

    \param offset [in]  Number of bytes.
    \param seekType [in]  Seek type.

    \remarks
    seekType must be one of the following:

    <table>
    Name                    Value       Description.
    OdDb::kSeekFromStart    SEEK_SET    Start of file.
    OdDb::kSeekFromCurrent  SEEK_CUR    Current position of I/O pointer.
    OdDb::kSeekFromEnd      SEEK_END    End of file.
    </table>
  */
  virtual void seek(
    OdInt64 offset,
    OdDb::FilerSeekType seekType );

  /** \details
    Returns the current I/O pointer position of this Filer object.
  */
  virtual OdUInt64 tell() const;
};

typedef OdSmartPtr< OdTvCoreFilerWrapper > OdTvCoreFilerWrapperPtr;

#include "TD_PackPop.h"

#endif

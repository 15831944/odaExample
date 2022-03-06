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

#ifndef _EdBagFiler_h_Included
#define _EdBagFiler_h_Included

#include "DbFiler.h"
#include "ResBuf.h"
#include "Ge/GePoint3d.h"
#include "CmColor.h"
#include "DbFilerImpl.h"

class OdBagFiler : public OdDbCommonDxfFilerImpl
{
  OdResBufPtr   m_pData;      // SmartPointer to the ResBuf chain of this Filer object.
  OdResBufPtr   m_pCurrent;   // SmartPointer to the current ResBuf in the ResBuf chain.
  OdDbDatabase* m_pDb;        // Pointer to the database with which this Filer object is associated.
  bool          m_bAtStart;   // True if and only if we are at the start of this Filer object.
  OdDb::DwgVersion m_Ver;

  /**********************************************************************/
  /* Description:                                                       */
  /* Appends the specified ResBuf to the ResBuf chain.                  */
  /**********************************************************************/
  void appendResBuf( OdResBufPtr rb )
  {
    if ( !m_pCurrent.isNull() )
    {
      m_pCurrent->setNext( rb );
      m_pCurrent = m_pCurrent->next();
    }
    else
    {
      m_pCurrent = rb;
      if ( m_pData.isNull() ) m_pData = m_pCurrent;
    }
  }
public:
  ODRX_DECLARE_MEMBERS(OdBagFiler);
  OdBagFiler();

  virtual OdDbDatabase* database() const;
  OdResBufPtr getCurrentResBuf() const;

  /**********************************************************************/
  /* Description:                                                       */
  /* Initialize this Filer object.                                      */
  /* Arguments:                                                         */
  /* db (I) Pointer to the database with which this Filer object is     */
  /*        associated.                                                 */
  /* resBuf (I) ResBuf to which this Filer object is initialized.       */
  /**********************************************************************/
  void init( OdDbDatabase* db, OdDb::DwgVersion version = OdDb::kDHL_CURRENT, OdResBufPtr resBuf = OdResBufPtr() );

  /**********************************************************************/
  /* Description:                                                       */
  /* Returns the ResBuf chain of this Filer object.                     */
  /**********************************************************************/
  OdResBufPtr getResBuf() const;

  int precision() const;

  virtual FilerType filerType() const;
  virtual OdDb::DwgVersion dwgVersion(
    OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;
  virtual bool includesDefaultValues() const;
  virtual void seek(OdInt64 offset, OdDb::FilerSeekType seekType);

  virtual bool atEOF();
  virtual bool atEndOfObject();
  virtual bool atExtendedData();
  virtual bool atSubclassData(const OdString& subClassName);
  virtual bool atEmbeddedObjectStart();
  virtual void writeXDataStart();

  virtual int nextItem();
  virtual OdResBufPtr nextRb();
  virtual void writeRb(const OdResBuf* pRb);
  virtual void pushBackItem();

  virtual OdUInt64 tell() const ODRX_OVERRIDE;

  virtual void        rdString(OdString &value);
  virtual bool        rdBool();
  virtual OdInt8      rdInt8();
  virtual OdInt16     rdInt16();
  virtual OdInt32     rdInt32();
  virtual OdInt64     rdInt64();
  virtual OdUInt8     rdUInt8();
  virtual OdUInt16    rdUInt16();
  virtual OdUInt32    rdUInt32();
  virtual OdUInt64    rdUInt64();
  virtual OdDbHandle  rdHandle();
  virtual OdDbObjectId rdObjectId();
  virtual double      rdAngle();
  virtual double      rdDouble();
  virtual void        rdPoint2d(OdGePoint2d& value);
  virtual void        rdPoint3d(OdGePoint3d& value);
  virtual void        rdVector2d(OdGeVector2d& value);
  virtual void        rdVector3d(OdGeVector3d& value);
  virtual void        rdScale3d(OdGeScale3d& value);
  virtual void        rdBinaryChunk(OdBinaryData& value);

  virtual void copyItem(OdDbDxfFiler * pSource);

  virtual void wrName(int groupCode, const OdString& value);
  virtual void wrString(int groupCode, const OdString& value);
  virtual void wrBool(int groupCode, bool value);
  virtual void wrInt8(int groupCode, OdInt8 value);
  virtual void wrUInt8(int groupCode, OdUInt8 value);
  virtual void wrInt16(int groupCode, OdInt16 value);
  virtual void wrUInt16(int groupCode, OdUInt16 value);
  virtual void wrInt32(int groupCode, OdInt32 value);
  virtual void wrUInt32(int groupCode, OdUInt32 value);
  virtual void wrInt64(int groupCode, OdInt64 value);
  virtual void wrUInt64(int groupCode, OdUInt64 value);
  virtual void wrHandle(int groupCode, OdDbHandle value);
  virtual void wrObjectId(int groupCode, OdDbObjectId value);
  virtual void wrAngle(int groupCode, double value, int precision = kDfltPrec);
  virtual void wrDouble(int groupCode, double value, int precision = kDfltPrec);
  virtual void wrPoint2d(int groupCode, const OdGePoint2d& value, int precision = kDfltPrec);
  virtual void wrPoint3d(int groupCode, const OdGePoint3d& value, int precision = kDfltPrec);
  virtual void wrVector2d(int groupCode, const OdGeVector2d& value, int precision = kDfltPrec);
  virtual void wrVector3d(int groupCode, const OdGeVector3d& value, int precision = kDfltPrec);
  virtual void wrScale3d(int groupCode, const OdGeScale3d& value, int precision = kDfltPrec);
  virtual void wrBinaryChunk(int groupCode, const OdUInt8* buffer, OdUInt32 numBytes);
};

#endif

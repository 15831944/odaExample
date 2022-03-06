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

#ifndef _ODPROXYSTUFF_INCLUDED_
#define _ODPROXYSTUFF_INCLUDED_

#include "OdBinaryData.h"
#include "IdArrays.h"
#include "ProxyClass.h"
#include "DbDatabase.h"

class OdDbDwgFiler;
class OdRxClass;
class OdDbEntityImpl;


class DBIO_EXPORT OdProxyStuff
{
protected:
  OdUInt16 getItemClassId() const
  {
    return OdUInt16(m_pProxyClass->isDerivedFrom(OdDbEntity::desc()) ? 498 : 499);
  }
  virtual OdDbEntityImpl* getEntityImpl() const { return NULL; }
  virtual OdDbObjectPtr   getObject() const = 0;

  OdRxClass* saveAsClass(OdRxClass* pClass) const;
  friend class OdDbProxyEntity;
  friend class OdDbProxyObject;
  bool cameAsProxy() const { return m_pProxyClass.isNull(); }

  mutable bool  						    m_bSaveInOrigFormat;
public:
  bool isAnEntity() const { return (getEntityImpl()!=NULL); }

  bool  						            m_bOrigDataFormatIsDxf;
  mutable bool  						    m_bWrapper;
  mutable bool  						    m_bDxfZombie;
	OdRxClassPtr                  m_pProxyClass;

  //OdInt32                       m_DrawingFormat;
  OdInt16                       m_DwgVer;
  OdInt32                       m_MaintReleaseVer;

	OdBitBinaryData		            m_BinaryData;
  OdBitBinaryData		            m_StringData;
  OdTypedIdsArray               m_Ids;

  // To define dxf data format (<=R18 or R21) it is enough to verify the m_StringData.getBitSize() value.
  // The first proxy data is a string - groupcode 100 with custom class name.
  bool dxfIsInR18Format() const { return m_StringData.getBitSize() == 0; }
  bool dxfNeedConversion(OdDb::DwgVersion fileVer) const
  {
    return (dxfIsInR18Format() && fileVer > OdDb::vAC18) || (!dxfIsInR18Format() && fileVer <= OdDb::vAC18);
  }
  bool origDataFormatIsDxf() const { return m_bOrigDataFormatIsDxf; }

public:
  OdProxyStuff();

  void setWrapperClass();
  void trackProxyClass(OdDbDatabase* pDb);
  void adjustProxyForSave(OdDbFiler* pFiler);
  bool saveInOrigFormat() const { return m_bSaveInOrigFormat; }
  void setDrawingFormat(OdDb::DwgVersion dwgVer, OdDb::MaintReleaseVer nMaintVer)
  {
		//m_DrawingFormat = ( (nMaintVer << 16) | dwgVer );

    m_DwgVer = (OdInt16)dwgVer;
    m_MaintReleaseVer = nMaintVer;
  }
  OdDb::DwgVersion drawingFormat(OdDb::MaintReleaseVer* pnMaintVer = NULL) const
  {
    /*if(pnMaintVer) *pnMaintVer = OdDb::MaintReleaseVer((m_DrawingFormat >> 16) & 0xFFFF);
    return OdDb::DwgVersion(m_DrawingFormat & 0xFFFF);*/

    if(pnMaintVer) *pnMaintVer = OdDb::MaintReleaseVer(m_MaintReleaseVer);
    return OdDb::DwgVersion(m_DwgVer);
  }
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  OdResult dxfInUnknownObjectFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};

OdResult turnToOriginalObject(OdDbObject* pProxyObj, OdDbFilerController*);
#ifdef ODA_DIAGNOSTICS
void checkForUnknownProxyClass(const OdString& sClass, OdDbObject* pObj, OdDb::DwgVersion ver);
#endif

#endif // _ODPROXYSTUFF_INCLUDED_

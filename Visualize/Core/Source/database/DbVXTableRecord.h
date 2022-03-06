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

#ifndef _ODDBVPORTENTHEADERTABLERECORD_INCLUDED
#define _ODDBVPORTENTHEADERTABLERECORD_INCLUDED

#include "DbSymbolTableRecord.h"
#include "DbDwgClassMap.h"

class OdTvDbVXTableRecord;
typedef OdSmartPtr<OdTvDbVXTableRecord> OdTvDbVXTableRecordPtr;

class TOOLKIT_EXPORT OdTvDbVXTableRecord : public OdTvDbSymbolTableRecord
{
	OdTvDbSoftPointerId m_ViewportEntityId;
	OdTvDbSoftPointerId m_PrevActiveRecordId;
	enum
	{
		kViewportOn = 1
	};
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbVXTableRecord);

  OdTvDbVXTableRecord();

  void setName(const OdString& pName);

	OdTvDbObjectId viewportEntityId() const { assertReadEnabled(); return m_ViewportEntityId; }
  void setViewportEntityId(OdTvDbObjectId id) { assertWriteEnabled(); m_ViewportEntityId = id; }

  bool isViewportOn() const;
  void setViewportOn(bool bVal);

  OdTvDbObjectId prevActiveRecordId() const { assertReadEnabled(); return m_PrevActiveRecordId; }
  void setPrevActiveRecordId(OdTvDbObjectId id) { assertWriteEnabled(); m_PrevActiveRecordId = id; }

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
};



#endif // _ODDBVPORTENTHEADERTABLERECORD_INCLUDED

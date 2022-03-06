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

#ifndef __TNW_GRAPHIC_SCHEMA_BUNDLE_H__
#define __TNW_GRAPHIC_SCHEMA_BUNDLE_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "OdBinaryData.h"

class OdNwGraphicBundleSchema;
typedef OdSmartPtr<OdNwGraphicBundleSchema> OdNwGraphicBundleSchemaPtr;

class NWDBEXPORT OdNwGraphicBundleSchema : public OdNwObject
{
  ODRX_DECLARE_MEMBERS(OdNwGraphicBundleSchema);

protected:
  OdNwGraphicBundleSchema();
public:
  virtual ~OdNwGraphicBundleSchema();

public:
  const OdString& getUID() const;
  const OdString& getType() const;
  OdUInt32 getBufSize() const;
  OdNwGraphicBundleSchemaPtr getParent() const;
  const OdBinaryData& getXmlSchemaBuffer() const;

public:
  void setUID(const OdString& val);
  void setType(const OdString& val);
  void setBufSize(OdUInt32 val);
  void setParent(OdNwGraphicBundleSchemaPtr pParent);
  void setXmlSchemaBuffer(const OdBinaryData& data);

protected:
  OdString m_UID;
  OdString m_type;
  OdUInt32 m_bufSize;
  OdNwGraphicBundleSchemaPtr m_pParent;
  OdBinaryData m_xmlSchemaBuffer;
};

#endif //__TNW_GRAPHIC_SCHEMA_BUNDLE_H__

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


#ifndef _OD_DSSCHEMA_H_INCLUDED_
#define _OD_DSSCHEMA_H_INCLUDED_


#include "DsObject.h"
#include "DsRecord.h"
#include "UInt64Array.h"

namespace OdDs
{
  //----------------------------------------------------------
  //
  // RecordType
  //
  //----------------------------------------------------------
  enum RecordType
  {
    kDsUnknown = -1,
    kDsPreview = 0,
    kDsAsm = 1,

    kDsTypesCount = 2
  };

  //----------------------------------------------------------
  //
  // SchemaProperty
  //
  //----------------------------------------------------------
  class SchemaProperty
  {
  public:
    static OdUInt32 TypeSize[16];

    SchemaProperty()
      : m_DwgDataFlag(0)
      , m_NameIndex(0)
      , m_Type(0)
      , m_CustomTypeSize(0)
      , m_PropUnknown1(0)
      , m_DxfPropFlag(0)
    {}
    SchemaProperty(OdDbDwgFiler* pFiler)
    {
      read(pFiler);
    }
    void read(OdDbDwgFiler* pFiler);
    void write(OdDbDwgFiler* pFiler);

    OdResult dxfIn(OdDbDxfFiler* pFiler);
    void dxfOut(OdDbDxfFiler* pFiler) const;

    OdResult dxfXrecIn(OdDbDxfFiler* pFiler);
    void dxfXrecOut(OdDbDxfFiler* pFiler) const;

    OdUInt32 m_DwgDataFlag;
    OdUInt32 m_NameIndex;
    OdUInt32 m_Type;
    OdUInt32 m_CustomTypeSize;
    OdUInt32 m_PropUnknown1;
    OdUInt32 m_DxfPropFlag;
    OdArray<OdBinaryData> m_propValues;
    SchemaItem m_defValue;
    //
    OdString m_Name;
    OdArray<SchemaAttribute> m_attributes;
  };

  //----------------------------------------------------------
  //
  // SchemaAttributeData
  //
  //----------------------------------------------------------
  class SchemaAttributeData
  {
  public:
    SchemaAttributeData()
      : m_DataSize(8)
      , m_UnknownFlag(1)
      , m_NameIndex(0)
    {}
    SchemaAttributeData(OdUInt32 nameIndex, OdUInt32 dataSize, OdUInt32 flag)
      : m_DataSize(dataSize)
      , m_UnknownFlag(flag)
      , m_NameIndex(nameIndex)
    {
    }
    SchemaAttributeData(OdDbDwgFiler* pFiler)
    {
      m_NameIndex = 0;
      read(pFiler);
    }
    void read(OdDbDwgFiler* pFiler)
    {
      m_DataSize = pFiler->rdInt32(); ODA_ASSERT(m_DataSize==8);
      m_UnknownFlag = pFiler->rdInt32();
    }
    void write(OdDbDwgFiler* pFiler)
    {
      pFiler->wrInt32(m_DataSize);
      pFiler->wrInt32(m_UnknownFlag);
    }
    OdUInt32 m_DataSize;
    OdUInt32 m_UnknownFlag;

    OdUInt32 m_NameIndex;
  };

  //----------------------------------------------------------
  //
  // Schema
  //
  //----------------------------------------------------------
  class Schema : public Object
  {
  public:
    ODRX_DECLARE_MEMBERS(Schema);

    Schema();
    ~Schema();

    // Object overridden
    virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
    virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
    virtual void endLoading();
    virtual OdResult dxfXrecInFields(OdDbDxfFiler* pFiler);
    virtual void dxfXrecOutFields(OdDbDxfFiler* pFiler) const;

    void read(OdDbDwgFiler* pFiler);
    void write(OdDbDwgFiler* pFiler);

    OdUInt32 m_index;
    OdAnsiString m_name;
    OdArray<SchemaProperty> m_properties;
    OdArray<SchemaAttribute> m_attributes;
    OdUInt64Array m_indexes;

    RecordType m_recordType;
  };

  typedef OdSmartPtr<Schema> SchemaPtr;

  //----------------------------------------------------------
  //
  // Schema initialization functions
  //
  //----------------------------------------------------------
  void initializeDsSchema(OdDbDatabase* pDb, OdDbObjectId* pXrecIds = 0);
  void saveDsDecomposeData(OdDbDatabase* pDb);
}

//----------------------------------------------------------
//
// Schema round-trip related strings
//
//----------------------------------------------------------
// TODO: place in StdStrings.h for the next major release (4.0)
#define ACDSDECOMPOSEDATA L"AcDsDecomposeData"
#define ACDSRECORDS L"AcDsRecords"
#define ACDSSCHEMAS L"AcDsSchemas"

#endif // _OD_DSSCHEMA_H_INCLUDED_

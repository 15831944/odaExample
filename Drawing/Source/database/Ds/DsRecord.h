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


#ifndef _OD_DSRECORD_H_INCLUDED_
#define _OD_DSRECORD_H_INCLUDED_


#include "DsObject.h"

namespace OdDs
{
  //----------------------------------------------------------
  //
  // ValueType
  //
  //----------------------------------------------------------
  enum ValueType
  {
    //kVoid       = 0,
    kBool         = 1,
    kWChar        = 2,
    kInt8         = 3,
    kInt16        = 4,
    kInt32        = 5,
    kInt64        = 6,
    kUInt8        = 7,
    kUInt16       = 8,
    kUInt32       = 9,
    kUInt64       = 10,
    kFloat        = 11, // (?) to be verified
    kDouble       = 12,
    kWString      = 13,
    kArray        = 14,
    kBinaryData   = 15
  };

  //----------------------------------------------------------
  //
  // Item - base class
  //
  //----------------------------------------------------------
  class Item
  {
  public:
    Item();

    virtual void dxfIn(
      OdDbDxfFiler* pFiler);
    virtual void dxfOut(
      OdDbDxfFiler* pFiler) const;

    OdString      m_name;
    OdUInt8       m_dsType;
    OdResBufPtr   m_pData;
  };

  //----------------------------------------------------------
  //
  // SchemaItem
  //
  //----------------------------------------------------------
  class SchemaItem : public Item
  {
  public:
    SchemaItem();

    virtual void dxfIn(
      OdDbDxfFiler* pFiler);
    virtual void dxfOut(
      OdDbDxfFiler* pFiler) const;

    void dxfInValue(
      OdDbDxfFiler* pFiler);
    void dxfOutValue(
      OdDbDxfFiler* pFiler) const;

  };

  //----------------------------------------------------------
  //
  // DataItem
  //
  //----------------------------------------------------------
  class DataItem : public Item
  {
  public:
    DataItem();

    virtual void dxfIn(
      OdDbDxfFiler* pFiler);
    virtual void dxfOut(
      OdDbDxfFiler* pFiler) const;

    void dxfInValue(
      OdDbDxfFiler* pFiler);
    void dxfOutValue(
      OdDbDxfFiler* pFiler) const;
  };

  //----------------------------------------------------------
  //
  // Record
  //
  //----------------------------------------------------------
  class Record : public Object
  {
  public:
    ODRX_DECLARE_MEMBERS(Record);

    Record();
    ~Record();

    // Object overridden
    virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);
    virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;
    virtual void endLoading();

    OdUInt32 m_schemaIndex;
    OdArray<DataItem> m_columns;
  };

  typedef OdSmartPtr<Record> RecordPtr;

  //----------------------------------------------------------
  //
  // SchemaAttribute
  // TODO: ? - columns properties
  //
  //----------------------------------------------------------
  class SchemaAttribute
  {
  public:
    SchemaAttribute()
      : m_id(-1)
      , m_schemaIndex(0)
    {}
    ~SchemaAttribute()
    {}

    OdResult dxfIn(OdDbDxfFiler* pFiler);
    void dxfOut(OdDbDxfFiler* pFiler) const;

    OdResult dxfXrecIn(OdDbDxfFiler* pFiler);
    void dxfXrecOut(OdDbDxfFiler* pFiler) const;

    OdInt32 getSchemaIndex() const { return m_schemaIndex; }
    void setSchemaIndex(OdInt32 val) { m_schemaIndex = val; }

  //private:
    OdInt32   m_id;
    OdString  m_idName;
    OdInt32   m_schemaIndex;
    DataItem  m_item;

    OdDbObjectId   m_xrecId;
  };

}

#endif // _OD_DSRECORD_H_INCLUDED_

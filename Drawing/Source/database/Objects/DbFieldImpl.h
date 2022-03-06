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

#ifndef _ODDBFIELDIMPL_INCLUDED_
#define _ODDBFIELDIMPL_INCLUDED_


#include "DbSystemInternals.h"
#include "DbField.h"
#include "Ge/GePoint3d.h"
#include "DbFieldValue.h"
#include "DbObjectImpl.h"
#include "EntityContainer.h"

class OdDbFieldImpl;
struct OdDbFieldContainer : OdObjectContainer
{
  OdDbObjectImpl* m_pParent;
  virtual const OdDbObjectImpl* dbObjectImpl() const ODRX_OVERRIDE { return m_pParent; }
  OdDbFieldPtr getFieldAt(OdUInt32 i, OdDb::OpenMode mode) const;
  void removeField(OdDbField* pField);
  using OdObjectContainer::resize;
  using OdObjectContainer::reserve;
  using OdObjectContainer::append;
  using OdObjectContainer::size;
  using OdObjectContainer::clear;
  using OdObjectContainer::begin;
  using OdObjectContainer::end;
  using OdObjectContainer::const_iterator;
  using OdObjectContainer::isDBROContent;
  using OdObjectContainer::remove;
};

class OdDbFieldImpl : public OdDbObjectImpl
{
  static OdDbFieldImpl* getImpl(const OdDbField *pObj)
  { return (OdDbFieldImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdDbFieldImpl();

  class FieldValuePair
  {
  public:
    OdString     key;
    OdFieldValue val;
    
    FieldValuePair() {}
    FieldValuePair(const OdString& pkey, const OdFieldValue& pval) : key(pkey) , val(pval) { }
  };

  OdString m_evaluatorIDStr;
  OdString m_fieldCodeStr;
  OdDbFieldContainer m_childFields;

  OdArray<OdDbObjectId> m_objectsInFieldCode;
  OdString m_formatStr;

  OdDbField::EvalOption m_evaluationOption;
  OdDbField::FilingOption m_fillingOption;
  OdDbField::State m_fieldStateFlag;
  OdDbField::EvalStatus m_evaluationStatus;
  OdInt32 m_evaluationErrorCode;
  OdString m_evaluationErrorMess;

  OdFieldValue m_data;
  OdString m_strKey;
  OdString m_textStrValue;

  OdArray<FieldValuePair> m_dataSet;

  void addFieldValue(const OdString& key, const OdFieldValue& pval);
  bool getFieldValue(OdInt32 indx, OdString& key, OdFieldValue& pval) const;

  OdFieldValue getData(const OdString& key) const;
  void setData(const OdString& key, const OdFieldValue& val);
  void removeData(const OdString& key);

  OdString getFieldCode(OdDbField* pObj, OdDbField::FieldCodeFlag nFlag);
  void replaceChildCodes(OdString& retString, OdDbField::FieldCodeFlag nFlag);
  void setDataFormat();

  void addChild(OdDbField* child)
  {
    m_childFields.append(m_childFields.appendObject(child));
  }
  void removeChild(OdDbField* child)
  {
    m_childFields.removeField(child);
  }
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void correctTextCoding(OdDbObjectId textStyleId);
  void compile(OdDbField* pThis);
  void initFormatString();
  void dwgOutDataSet(OdDbDwgFiler* pFiler);
private:
  friend class OdDbField;
  friend class OdDbAttributeImpl;
};

OdDbFieldPtr oddbFieldCreator(const OdString sourceFieldCode, OdDbDatabase* pDb);

#endif // _ODDBFIELDIMPL_INCLUDED_

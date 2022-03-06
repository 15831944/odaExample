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

class OdTvDbFieldImpl;
struct OdTvDbFieldContainer : OdTvObjectContainer
{
  OdTvDbObjectImpl* m_pParent;
  virtual const OdTvDbObjectImpl* dbObjectImpl() const ODRX_OVERRIDE { return m_pParent; }
  OdTvDbFieldPtr getFieldAt(OdUInt32 i, OdDb::OpenMode mode) const;
  void removeField(OdTvDbField* pField);
  using OdTvObjectContainer::resize;
  using OdTvObjectContainer::reserve;
  using OdTvObjectContainer::append;
  using OdTvObjectContainer::size;
  using OdTvObjectContainer::clear;
  using OdTvObjectContainer::begin;
  using OdTvObjectContainer::end;
  using OdTvObjectContainer::const_iterator;
  using OdTvObjectContainer::isDBROContent;
  using OdTvObjectContainer::remove;
};

class OdTvDbFieldImpl : public OdTvDbObjectImpl
{
  static OdTvDbFieldImpl* getImpl(const OdTvDbField *pObj)
  { return (OdTvDbFieldImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdTvDbFieldImpl();

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
  OdTvDbFieldContainer m_childFields;

  OdArray<OdTvDbObjectId> m_objectsInFieldCode;
  OdString m_formatStr;

  OdTvDbField::EvalOption m_evaluationOption;
  OdTvDbField::FilingOption m_fillingOption;
  OdTvDbField::State m_fieldStateFlag;
  OdTvDbField::EvalStatus m_evaluationStatus;
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

  OdString getFieldCode(OdTvDbField* pObj, OdTvDbField::FieldCodeFlag nFlag);
  void replaceChildCodes(OdString& retString, OdTvDbField::FieldCodeFlag nFlag);
  void setDataFormat();

  void addChild(OdTvDbField* child)
  {
    m_childFields.append(m_childFields.appendObject(child));
  }
  void removeChild(OdTvDbField* child)
  {
    m_childFields.removeField(child);
  }
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void correctTextCoding(OdTvDbObjectId textStyleId);
  void compile(OdTvDbField* pThis);
  void initFormatString();
  void dwgOutDataSet(OdTvDbDwgFiler* pFiler);
private:
  friend class OdTvDbField;
  friend class OdTvDbAttributeImpl;
};

OdTvDbFieldPtr odtvdbFieldCreator(const OdString sourceFieldCode, OdTvDbDatabase* pDb);

#endif // _ODDBFIELDIMPL_INCLUDED_

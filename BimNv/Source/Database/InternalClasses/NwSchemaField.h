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

#ifndef __NwSchemaFieldFIELD_INCLUDED_
#define __NwSchemaFieldFIELD_INCLUDED_

#include "NwExport.h"
#include "OdString.h"
#define STL_USING_MEMORY
#define STL_USING_VECTOR
#include "OdaSTL.h"

class NWDBEXPORT OdNwSchemaField
{
public:
  OdNwSchemaField();
  virtual ~OdNwSchemaField() {}

public:
  OdString getId() const;
  OdString getDisplayName() const;
  const std::vector<OdString>& getConcepts() const;
  std::vector<OdString>& getConcepts();

public:
  void setId(const OdString& id);
  void setDisplayName(const OdString& name);
  void addConcept(OdString&& concept);

protected:
  OdString m_Id;
  OdString m_DisplayName;
  std::vector<OdString> m_SchemaConcepts;
};

template <class... Args>
class NWDBEXPORT OdNwSchemaValueField : public OdNwSchemaField
{
public:
  OdNwSchemaValueField() = default;
  virtual ~OdNwSchemaValueField() {}
public:
  const std::tuple<Args...>& getValue() const { return m_Value; }
  std::tuple<Args...>& getValue() { return m_Value; }
public:
  void setValue(Args... args) { m_Value = std::make_tuple(std::forward<Args>(args)...); }
protected:
  std::tuple<Args...> m_Value;
};

template <typename T>
class NWDBEXPORT OdNwSchemaValueField<T> : public OdNwSchemaField
{
public:
  OdNwSchemaValueField() = default;
  virtual ~OdNwSchemaValueField() {}
public:
  const T& getValue() const { return m_Value; }
  T& getValue() { return m_Value; }
public:
  void setValue(T&& val) { m_Value = std::move(val); }
protected:
  T m_Value;
};

typedef std::shared_ptr<OdNwSchemaField> OdNwSchemaFieldPtr;

using OdNwSchemaDoubleField = OdNwSchemaValueField<double, OdInt32>;
using OdNwSchemaGuIdField = OdNwSchemaValueField<OdInt32, OdString, OdGUID>;
using OdNwSchemaInt32Field = OdNwSchemaValueField<OdInt32>;
using OdNwSchemaBooleanField = OdNwSchemaValueField<bool>;
using OdNwSchemaStringField = OdNwSchemaValueField<OdString>;
using OdNwSchemaStructField = OdNwSchemaValueField<std::vector<OdNwSchemaFieldPtr> >;

#endif //__NwSchemaFieldFIELD_INCLUDED_

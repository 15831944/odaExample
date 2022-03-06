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

// This file is generated automatically.

#ifndef _DAI_HEADER_FILESCHEMA_AUTO_IMPL_H
#define _DAI_HEADER_FILESCHEMA_AUTO_IMPL_H

#include "daiPubCommon.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with DAI_HEADER express schema definitions.
*/
namespace OdDAI {

class DAI_EXPORT FileSchema : public ApplicationInstance
{
  //DOM-IGNORE-BEGIN
  OD_EXP_HEADER_DECLARE_MEMBERS(OdDAI::FileSchema);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //
  void getSchemaIdentifiers(OdArray<OdAnsiString> &aggregate) const;
  void setSchemaIdentifiers(const OdArray<OdAnsiString> &aggregate);


public:
  virtual OdResult inFields(OdDAI::OdSpfFilerBase* rdFiler);
  virtual OdResult outFields(OdDAI::OdSpfFilerBase* wrFiler);
  virtual bool isKindOf(OdHeaderEntityType entityType) const;
  virtual bool isInstanceOf(OdHeaderEntityType entityType) const;
  virtual OdDAI::Entity* getInstanceType() const;
  virtual OdHeaderEntityType type() const;
  virtual OdRxValue getAttr(const char * attrName) const;
  virtual void unsetAttr(const char * explicitAttrName);
  virtual bool testAttr(const char * explicitAttrName) const;
  virtual bool putAttr(const char * explicitAttrName, const OdRxValue &val);

protected:
  // Fields declaration: 
  OdDAI::OdAnsiStringList m_SchemaIdentifiers; // LIST [1:?] of SchemaName
};
typedef OdSmartPtr<FileSchema> FileSchemaPtr;

} // namespace

#endif // _DAI_HEADER_FILESCHEMA_AUTO_IMPL_H

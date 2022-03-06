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

#ifndef _DAI_HEADER_FILENAME_AUTO_IMPL_H
#define _DAI_HEADER_FILENAME_AUTO_IMPL_H

#include "daiPubCommon.h"
#include "daiAggr/daiArray.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with DAI_HEADER express schema definitions.
*/
namespace OdDAI {

class DAI_EXPORT FileName : public ApplicationInstance
{
  //DOM-IGNORE-BEGIN
  OD_EXP_HEADER_DECLARE_MEMBERS(OdDAI::FileName);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //
  OdAnsiString getName() const;
  void setName(OdAnsiString Name);
  OdAnsiString getTimeStamp() const;
  void setTimeStamp(OdAnsiString TimeStamp);
  void getAuthor(OdArray<OdAnsiString> &aggregate) const;
  void setAuthor(const OdArray<OdAnsiString> &aggregate);
  void getOrganization(OdArray<OdAnsiString> &aggregate) const;
  void setOrganization(const OdArray<OdAnsiString> &aggregate);
  OdAnsiString getPreprocessorVersion() const;
  void setPreprocessorVersion(OdAnsiString PreprocessorVersion);
  OdAnsiString getOriginatingSystem() const;
  void setOriginatingSystem(OdAnsiString OriginatingSystem);
  OdAnsiString getAuthorization() const;
  void setAuthorization(OdAnsiString Authorisation);


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
  OdAnsiString m_Name = OdDAI::Consts::OdStringUnset;
  OdAnsiString m_TimeStamp = OdDAI::Consts::OdStringUnset;
  OdDAI::OdAnsiStringList m_Author; // LIST [0:?] of STRING(256)
  OdDAI::OdAnsiStringList m_Organization; // LIST [0:?] of STRING(256)
  OdAnsiString m_PreprocessorVersion = OdDAI::Consts::OdStringUnset;
  OdAnsiString m_OriginatingSystem = OdDAI::Consts::OdStringUnset;
  OdAnsiString m_Authorization = OdDAI::Consts::OdStringUnset;
};
typedef OdSmartPtr<FileName> FileNamePtr;

} // namespace

#endif // _DAI_HEADER_FILENAME_AUTO_IMPL_H

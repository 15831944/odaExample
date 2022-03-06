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

#ifndef __NW_GRAPHIC_JSON_BUNDLE_IMPL_H__
#define __NW_GRAPHIC_JSON_BUNDLE_IMPL_H__

#include "NwGraphicJsonBundle.h"
#include "OdArray.h"
#include "NwObjectImpl.h"

class OdNwEmbeddedFile;
typedef std::shared_ptr<OdNwEmbeddedFile> OdNwEmbeddedFilePtr;

class OdNwGraphicJsonBundleImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGraphicJsonBundle)
public:
  OdNwGraphicJsonBundleImpl();
  virtual ~OdNwGraphicJsonBundleImpl();
  ODRX_DECLARE_MEMBERS(OdNwGraphicJsonBundleImpl);

public:
  static OdNwGraphicJsonBundleImpl* getImpl(const OdNwGraphicJsonBundle* pNwBck);
  static OdNwGraphicJsonBundleImpl* getImpl(const OdRxObject* pRxBck);

//public implementation's methods
public:
  OdString getJson() const;
  void setJson(OdString json);
  void setFileRef(OdString key, OdString name);
  OdString getFileRef(OdString key) const;

  void setFileEmbedded(const OdString& key, OdNwEmbeddedFilePtr pEmbFile);//not in API
  void setFileEmbedded(const OdString& key, const OdBinaryData& content);
  void setFileEmbedded(const OdString& key, const OdBinaryData& content, const OdString& appName, const OdString& type);//not in API
  OdBinaryData getFileEmbedded(const OdString& key) const;
  OdNwEmbeddedFilePtr getFullFileEmbedded(const OdString& key) const;//not in API

  OdArray<OdString> getFileRefKeys() const;
  OdArray<OdString> getFileEmbeddedKeys() const;

  void setMaterialJson(OdString json);
  OdString getMaterialJson() const;

//not API methods
public:
  inline const std::map<OdString, OdString>&            getFileRefs() const     { return m_mFileRefs; }
  inline const std::map<OdString, OdNwEmbeddedFilePtr>& getFileEmbedded() const { return m_mFileEmbedded; }

protected:
  OdString                                m_sJson;
  OdString                                m_sMaterialJson;
  std::map<OdString, OdString>            m_mFileRefs;
  std::map<OdString, OdNwEmbeddedFilePtr> m_mFileEmbedded;
};

typedef OdSmartPtr<OdNwGraphicJsonBundleImpl> OdNwGraphicJsonBundleImplPtr;

#endif //__NW_GRAPHIC_JSON_BUNDLE_IMPL_H__

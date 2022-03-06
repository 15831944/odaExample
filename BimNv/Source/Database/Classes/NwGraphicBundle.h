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

#ifndef __TNW_GRAPHIC_BUNDLE_H__
#define __TNW_GRAPHIC_BUNDLE_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#define STL_USING_VECTOR
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "NwModelUnits.h"

class OdNwGraphicBundleSchema;
typedef OdSmartPtr<OdNwGraphicBundleSchema> OdNwGraphicBundleSchemaPtr;
class OdNwGraphicProperty;
typedef std::shared_ptr<OdNwGraphicProperty> OdNwGraphicPropertyPtr;
class OdNwGraphicBundle;
typedef OdSmartPtr<OdNwGraphicBundle> OdNwGraphicBundlePtr;
class OdGeMatrix3d;

class NWDBEXPORT OdNwGraphicBundle : public OdNwObject
{
  ODRX_DECLARE_MEMBERS(OdNwGraphicBundle);

protected:
  OdNwGraphicBundle();
public:
  virtual ~OdNwGraphicBundle();

public:
  //VAS: create graphic bundle by GenericSchema
  static OdNwGraphicBundlePtr createGenericBundle();
  //VAS: create graphic bundle by UnifiedBitmapSchema
  static OdNwGraphicBundlePtr createUnifiedBitmapBundle();
  //VAS: create json protein data by graphic bundles with string texture path
  static OdString createJsonBundleByDiffuseTexturePath(const OdString& texturePath, const OdGeMatrix3d& mappingTransform, NwModelUnits::Enum modelUnits);

public:
  const OdString& getLibraryId() const;
  const OdString& getDefinitionId() const;
  OdNwGraphicBundleSchemaPtr getSchema() const;
  const std::vector<OdString>& getKeywords() const;
  const std::vector<OdString>& getCategories() const;
  const std::vector<OdString>& getThumbnailURLs() const;
  OdGUID getGuId() const;
  const OdString& getUIName() const;
  const OdString& getDefaultPreviewId() const;
  const OdString& getDescription() const;

  OdNwGraphicPropertyPtr findProperty(const OdString& propName);

public:
  inline std::vector<OdString>& getKeywords() { return m_vKeyword; }
  inline std::vector<OdString>& getCategories() { return m_vCategory; }
  inline std::vector<OdString>& getThumbnailURLs() { return m_vThumbnailURL; }
  inline std::vector<OdNwGraphicPropertyPtr>& getProperties() { return m_vProperty; }

public:
  void setLibraryId(const OdString& val);
  void setDefinitionId(const OdString& val);
  void setSchema(OdNwGraphicBundleSchemaPtr pSchema);
  void setGuId(const OdGUID& val);
  void setUIName(const OdString& val);
  void setDefaultPreviewId(const OdString& val);
  void setDescription(const OdString& val);

  void addKeyword(OdString&& val);
  void addCategories(OdString&& val);
  void addThumbnailURLs(OdString&& val);
  void addProperty(OdNwGraphicPropertyPtr&& pProperty);

protected:
  OdString m_libraryId;
  OdString m_definitionId;
  OdNwGraphicBundleSchemaPtr m_pSchema;
  std::vector<OdString> m_vKeyword;
  std::vector<OdString> m_vCategory;
  std::vector<OdString> m_vThumbnailURL;
  OdGUID m_GuId;
  OdString m_UIName;
  OdString m_defaultPreviewId;
  OdString m_description;
  std::vector<OdNwGraphicPropertyPtr> m_vProperty;
};

#endif //__TNW_GRAPHIC_BUNDLE_H__

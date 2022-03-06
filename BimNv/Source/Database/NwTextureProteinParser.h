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

#ifndef __NWTEXTUREPROTEINPARSING_INCLUDED__
#define __NWTEXTUREPROTEINPARSING_INCLUDED__

#include "RxObject.h"
#define STL_USING_MAP
#include "OdaSTL.h"
#include "SharedPtr.h"

class OdNwTextureImpl;
class OdNwPropertyImpl;
class OdNwTextureMapper;
class OdNwProperty;
class OdNwColor;

typedef OdSmartPtr<OdNwProperty> OdNwPropertyPtr;
typedef std::pair<OdString, OdNwPropertyPtr> OdPropertiesPair;
class OdNwGraphicJsonBundle;

class OdNwTextureProteinParser
{
public:
  OdNwTextureProteinParser(OdNwTextureImpl* texture, const OdString& texturesDirectory, OdNwGraphicJsonBundle* pJsonBundle);
  OdNwTextureProteinParser(const OdNwTextureProteinParser& other);
  OdNwTextureProteinParser &operator=(const OdNwTextureProteinParser& other);

private:
  void setMapper(OdNwPropertyImpl* pProp, OdNwTextureMapper& textureMapper);

public:
  void operator()(const OdPropertiesPair& cur_prop);

public:
  void setTag(const OdString& tag);

public:
  const OdString& getTag() const;
  const OdString& getType() const;
  const OdString& getFinish() const;
  const OdString& getColorIndex() const;
  OdSharedPtr<OdNwColor> getCustomColor() const;

private:
  OdNwTextureImpl* m_pTexture;
  OdString m_tag;
  OdString m_type;
  OdString m_finish;
  OdString m_colorIndex;
  OdSharedPtr<OdNwColor> m_pCustomColor;
  OdString m_TexturesDirectory;
  OdNwGraphicJsonBundle* m_pJsonBundle;
};

#endif //__NWTEXTUREPROTEINPARSING_INCLUDED__

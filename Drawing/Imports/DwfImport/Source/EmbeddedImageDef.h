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

#ifndef __EMBEDDEDIMAGEDEF_H
#define __EMBEDDEDIMAGEDEF_H


#include "DbRasterImageDef.h"
#include "OdStreamBuf.h"
#include "Gi/GiMaterial.h"

/** \details
  <group OdImport_Classes> 
*/
namespace TD_DWF_IMPORT{
class EmbeddedImageDef;
typedef OdSmartPtr<EmbeddedImageDef> EmbeddedImageDefPtr;

/** \details
  This class implements the image import.
*/
class EmbeddedImageDef : public OdDbRasterImageDef
{
public:
  EmbeddedImageDef();
  ~EmbeddedImageDef();
  static EmbeddedImageDefPtr createObject()
  {
    return EmbeddedImageDefPtr(new EmbeddedImageDef, kOdRxObjAttach);
  }
  void beginSave(OdDbDatabase* pDb, const OdString& pIntendedName);
  void setExtension(const OdString& ext){ _ext = ext; }
  void setData(OdStreamBufPtr& buf){ _data = buf; }
  void setName(const OdString& name){ _name = name; }
  void setTexture(OdGiImageTexturePtr pTexture) { _pTexture = pTexture; }
  OdStreamBufPtr getData(){ return _data; }
private:
  void updateTexturePathOfMatrials(OdDbDatabase* pDb, const OdString& sOldPrefix, const OdString& sNewPrefix);
  OdString _ext;
  OdString _name;
  OdStreamBufPtr _data;
  OdGiImageTexturePtr _pTexture;
};

}
#endif // !defined(__EMBEDDEDIMAGEDEF_H)

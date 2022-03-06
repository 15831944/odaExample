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

#ifndef _NWDATABASEUTILS_INCLUDED_
#define _NWDATABASEUTILS_INCLUDED_

#include "NwDatabaseImpl.h"

class OdNwObjectId;
class OdNwBackgroundElement;
class OdNwClashElement;
class OdNwComponent;
//class OdNwGeometry;
//class OdNwTextFontInfo;
class OdNwMaterial;
class OdNwViewpoint;
class OdNwTexture;
class OdNwModel;
class OdNwProperty;
class OdNwCategory;
class OdNwCommonLight;
class OdNwDataProperty;
class OdNwClashElement;
class OdNwSavedItemsElement;
class OdNwModelItem;
class OdNwClipPlaneSet;
class OdNwRedLine;
class OdNwObject;
class OdNwSavedItem;

namespace NwDatabaseUtils
{
  OdNwObjectId addObject(OdNwDatabaseImpl* pDbImpl, const OdNwObject* pObj);
  OdNwObjectId addBackgroundElement(OdNwDatabaseImpl* pDbImpl, const OdNwBackgroundElement* pBackground);
  OdNwObjectId addSavedItemsElement(OdNwDatabaseImpl* pDbImpl, OdNwSavedItemsElement* pSIElements, const OdNwObjectId& ownerId);
  OdNwObjectId addSavedItem(OdNwDatabaseImpl* pDbImpl, const OdNwSavedItem* pSI, const OdNwObjectId& ownerId);
  OdNwObjectId addModelItem(OdNwDatabaseImpl* pDbImpl, const OdNwModelItem* pNodeImpl, const OdNwObjectId& ownerId);
  OdNwObjectId addComponent(OdNwDatabaseImpl* pDbImpl, const OdNwComponent* pComponent, const OdNwObjectId& ownerId);
  //OdNwObjectId addGeometry(OdNwDatabaseImpl* pDbImpl, const OdNwGeometry* pGeometry, const OdNwObjectId& ownerId);
 // OdNwObjectId addTextFont(OdNwDatabaseImpl* pDbImpl, const OdNwTextFontInfo* pFont, const OdNwObjectId& ownerId);
  OdNwObjectId addMaterial(OdNwDatabaseImpl* pDbImpl, const OdNwMaterial* pMat, const OdNwObjectId& ownerId);
  OdNwObjectId addViewpoint(OdNwDatabaseImpl* pDbImpl, const OdNwViewpoint* pView);
  OdNwObjectId addClipPlaneSet(OdNwDatabaseImpl* pDbImpl, const OdNwClipPlaneSet* pClipPlaneSet);
  OdNwObjectId addTexture(OdNwDatabaseImpl* pDbImpl, const OdNwTexture* pTxt, const OdNwObjectId& ownerId);
  OdNwObjectId addModel(OdNwDatabaseImpl* pDbImpl, const OdNwModel* pModel);
  OdNwObjectId addProperty(OdNwDatabaseImpl* pDbImpl, const OdNwProperty* pProp, const OdNwObjectId& ownerId);
  OdNwObjectId addCategory(OdNwDatabaseImpl* pDbImpl, const OdNwCategory* pCat, const OdNwObjectId& ownerId);
  //OdNwObjectId addColor(OdNwDatabaseImpl* pDbImpl, const OdNwColor* pClr, const OdNwObjectId& ownerId);
  OdNwObjectId addLight(OdNwDatabaseImpl* pDbImpl, const OdNwCommonLight* pLight);
  OdNwObjectId addDataProperty(OdNwDatabaseImpl* pDbImpl, const OdNwDataProperty* pProp, const OdNwObjectId& ownerId);
  OdNwObjectId addRedLine(OdNwDatabaseImpl* pDbImpl, const OdNwRedLine* pRL, const OdNwObjectId& ownerId);
}

#endif // _NWDATABASEUTILS_INCLUDED_

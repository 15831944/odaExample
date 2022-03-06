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

#ifndef _TV_DWGIMPORTNOTIFIER_H_
#define _TV_DWGIMPORTNOTIFIER_H_

#include "TD_PackPush.h"

#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"

class OdTvEmptyNotifier : public ExGsVisualizeDeviceNotifier
{
public:
  //entities
  virtual void entityVectorizationDone(const OdTvEntityId& entityId) {};
  virtual void insertVectorizationDone(const OdTvEntityId& insertId) {};
  virtual void lightVectorizationDone(const OdTvEntityId& lightId) {}

  virtual void entityRemoved(const OdTvEntityId& entityId) {}
  virtual void insertRemoved(const OdTvEntityId& insertId) {}
  virtual void lightRemoved(const OdTvEntityId& insertId) {}

  //view
  virtual void viewCreated(const OdTvGsViewId& viewId) {}
  virtual void viewModified(const OdTvGsViewId& viewId) {}

  //Table records
  virtual void layerCreated(const OdTvLayerId& layerId) {}
  virtual void layerModified(const OdTvLayerId& layerId) {}

  virtual void materialCreated(const OdTvMaterialId& materialId) {}

  virtual void imageCreated(const OdTvRasterImageId& iamgeId) {}

  virtual void blockCreated(const OdTvBlockId& blockId) {};
  virtual void blockVectorizationBegin(const OdTvBlockId& blockId) {};
  virtual void blockVectorizationDone(const OdTvBlockId& blockId) {};

  virtual void linetypeCreated(const OdTvLinetypeId& linetypeId) {}

  virtual void textStyleCreated(const OdTvTextStyleId& textStyleId) {}

  //Models
  virtual void modelCreated(const OdTvModelId& modelId) {};
  virtual void modelActivated(const OdTvModelId& modelId) {};

  //update
  virtual void updateBegins() {}
  virtual void updateEnds() {}

  virtual void viewportEntityCreated(const OdTvEntityId&, const OdGiDrawable*) {}
};

class OdTvDwgImportNotifier : public OdTvEmptyNotifier
{
public:
  virtual void viewportEntityCreated(const OdTvEntityId& entityId, const OdGiDrawable* pDrawable)
  {
    //TODO: implement me
  }

};

#include "TD_PackPop.h"

#endif // _TV_DWGIMPORTNOTIFIER_H_

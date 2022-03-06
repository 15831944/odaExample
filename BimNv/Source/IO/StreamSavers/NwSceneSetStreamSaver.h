  /////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2018, Open Design Alliance (the "Alliance"). 
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
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2019 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#ifndef __NW_SCENESETSTREAMSAVER_H__
#define __NW_SCENESETSTREAMSAVER_H__

#include "NwStreamSaver.h"
#include "NwFormatVersionEx.h"
#include "SharedPtr.h"
#include "TD_PackPush.h"

class OdNwSceneSet;
typedef OdSharedPtr<OdNwSceneSet> OdNwSceneSetPtr;
class OdNwModel;
typedef OdSmartPtr<OdNwModel> OdNwModelPtr;
class OdNwObjectWriterManager;
typedef OdSharedPtr<OdNwObjectWriterManager> OdNwObjectWriterManagerPtr;
class OdNwModelValidData;
typedef OdSharedPtr<OdNwModelValidData> OdNwModelValidDataPtr;
class OdNwCachePlugin;

class OdNwSceneSetStreamSaver : public OdNwStreamSaver
{
public:
  OdNwSceneSetStreamSaver(const OdNwStreamContextPtr& ctx);
  virtual ~OdNwSceneSetStreamSaver();
  virtual OdResult saveToStream();

  void setSceneSet(OdNwSceneSetPtr pSceneSet);
  static void writeModel(OdNwObjectWriterManager* pInflated, OdNwModelPtr pModel);

protected:
  
  static void writeModelValidData(OdNwObjectWriterManager* pObjectWriterMgr, OdNwModelValidDataPtr pValidData);
  static void writeCachePlugin(OdNwObjectWriterManager* pObjectWriterMgr, OdNwCachePlugin* pCachePlugin);

private:
  OdNwSceneSetPtr m_pSceneSet;
  OdNwObjectWriterManagerPtr m_pObjectWriterMgr;
};

typedef std::shared_ptr<OdNwSceneSetStreamSaver> OdNwSceneSetStreamSaverPtr;
typedef std::weak_ptr<OdNwSceneSetStreamSaver> OdNwSceneSetStreamSaverWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_SCENESETSTREAMSAVER_H__

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

#ifndef __OD_ANIMATION_H__
#define __OD_ANIMATION_H__

#include "TvDatabase.h"
#include "NwDatabase.h"
#include "NwColor.h"
#include <functional>
#include <vector>
#include "SavedAnimation/NwSavedAnimElement.h"
#include "SavedAnimation/NwSavedAnimSelectAnim.h"
#include "SavedAnimation/NwSavedAnimSelectKeyFrame.h"

#include "SavedAnimation/NwSavedAnimFolder.h"
#include "SavedAnimation/NwSavedAnimClip.h"
#include "SavedAnimation/NwSavedAnimKeyFrame.h"
#include "SavedAnimation/NwSavedAnimScene.h"
#include "SavedAnimation/NwSavedAnimSceneFolder.h"
#include "SavedAnimation/NwSavedAnimSceneFolder.h"

typedef std::map<OdNwObjectId, std::vector<OdTvEntityId> > mapNwObjId2TvIdsType;

class OdTvNwSavedAnimationEnumerator
{
public:
  OdTvNwSavedAnimationEnumerator(OdNwDatabasePtr pNwDb, OdTvDatabasePtr pTvDb, OdTvModelId modelId);
  ~OdTvNwSavedAnimationEnumerator();
  void feedAnimation();
  void enumSelectedModels();
  mapNwObjId2TvIdsType & getMapNwTv() {
    return m_NwOIds2TvIdsMap;
  }
private:
  void enumAnimSceneFolder (const OdNwSavedAnimSceneFolder * pSceneFolder);
  void enumAnimScene(const OdNwSavedAnimScene * pScene);
  void enumSceneChild(const OdNwSavedItem * pSceneChild);
  bool enumAnimGroup(const OdNwSavedAnimGroup * pAnimGrp);
  bool collectSelectAnim(const OdNwSavedAnimSelectAnim * pSelectAnim);
  bool enumSelectAnim(const OdNwSavedAnimSelectAnim * pSelectAnim);
  void enumAnimation();
  OdNwDatabasePtr m_pNwDb;
  OdTvDatabasePtr m_pTvDb;
  OdTvModelId m_modelId;
  OdTvAnimationContainerPtr m_pContainer;
  OdTvAnimationActionId m_actionId;
  OdTvGsViewId m_newViewId;
  std::function<bool(const OdNwSavedAnimSelectAnim *)> m_selectAnimEnumerator;
  std::function<bool(const OdNwSavedAnimGroup *)> m_animGroupEnumerator;
  OdNwObjectIdArray m_selectedModels;
  mapNwObjId2TvIdsType m_NwOIds2TvIdsMap;
};

#endif

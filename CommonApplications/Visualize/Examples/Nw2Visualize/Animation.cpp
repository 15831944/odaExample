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

#include "OdaCommon.h"
#include "Animation.h"
#include <list>
#include <algorithm>
#include <cmath>
#include <NwModelItem.h>
#include <TvInsert.h>

OdTvNwSavedAnimationEnumerator::OdTvNwSavedAnimationEnumerator(OdNwDatabasePtr pNwDb, OdTvDatabasePtr pTvDb, OdTvModelId modelId)
  : m_pNwDb(pNwDb)
  , m_pTvDb(pTvDb)
  , m_modelId(modelId)
{
}

OdTvNwSavedAnimationEnumerator::~OdTvNwSavedAnimationEnumerator()
{
}

bool OdTvNwSavedAnimationEnumerator::enumAnimGroup(const OdNwSavedAnimGroup * pAnimGrp)
{
  OdTvDevicesIteratorPtr pDevIt = m_pTvDb->getDevicesIterator();
  OdTvGsDevicePtr pDevice = pDevIt->getDevice().openObject(OdTv::kForWrite);
  OdTvGsViewId originalViewId = pDevice->viewAt(0);
  OdTvGsViewPtr pOriginalView = originalViewId.openObject(OdTv::kForWrite);
  OdTvGsViewId newViewId = pDevice->createView(OD_T("SecondView"));
  OdTvGsViewPtr pView = newViewId.openObject(OdTv::kForWrite);
  pView->addModel(m_modelId);
  pDevice->addView(newViewId);
  pView->setView(pOriginalView->position(), pOriginalView->target(), pOriginalView->upVector(), pOriginalView->fieldWidth(), pOriginalView->fieldHeight());
  pView->setBackground(pOriginalView->getBackground());
  pView->setVisualStyle(pOriginalView->getVisualStyle());
  pView->setDefaultLightingColor(pOriginalView->defaultLightingColor());
  pView->setDefaultLightingIntensity(pOriginalView->defaultLightingIntensity());
  pView->enableDefaultLighting(pOriginalView->defaultLightingEnabled(), pOriginalView->defaultLightingType());
  pOriginalView->setViewport(OdTvPoint2d(0., 0.), OdTvPoint2d(0.5, 1.));
  pView->setBorderVisibility(true);
  pOriginalView->setBorderVisibility(true);
  pView->setViewport(OdTvPoint2d(0.5, 0.), OdTvPoint2d(1., 1.));

  OdTvModelPtr pModel = m_modelId.openObject(OdTv::kForWrite);
  OdNwObjectIdArray ObjIdList;

  if (!pAnimGrp || pAnimGrp->getChildren(ObjIdList) != eOk)
  {
    return false;
  }

  auto keyFrameComparFn = [](const OdNwSavedAnimKeyFramePtr& a, const OdNwSavedAnimKeyFramePtr&b)
  {
    return a->getTime() < b->getTime();
  };
  
  std::set<OdNwSavedAnimKeyFramePtr, decltype(keyFrameComparFn)> setKeyFrame(keyFrameComparFn);
  
  for (auto & sceneChildId : ObjIdList)
  {
    OdNwSavedAnimKeyFramePtr pKeyFrame = OdNwSavedAnimKeyFrame::cast(sceneChildId.safeOpenObject());
    setKeyFrame.insert(pKeyFrame);
  }
  
  OdNwSavedAnimKeyFramePtr firstKf = *setKeyFrame.begin();
  OdNwSavedAnimKeyFramePtr lastKf = *setKeyFrame.rbegin();
  double kps = 24;
  double lastKfTime = lastKf->getTime();
  unsigned int kfCount = setKeyFrame.size();
  int totalKfnum = ceil(lastKfTime*kps) + 1;

  OdGeQuaternion camq = firstKf->getCameraRotation();
  OdGeMatrix3d matr = camq.getMatrix();

  ODA_ASSERT(!OdEqual(firstKf->getFocalDistance(), 0));
  OdTvPoint target = firstKf->getCameraPosition() - matr.getCsZAxis() * firstKf->getFocalDistance();

  OdTvVector up = matr.getCsYAxis();
  OdTvPoint position = firstKf->getCameraPosition();

  OdTvEntityId cameraId = pModel->appendCamera(OD_T("AnimatedCamera"));
  OdTvCameraPtr pCamera = cameraId.openObjectAsCamera(OdTv::kForWrite);

  double focalDistance = firstKf->getFocalDistance();
  double verticalAngle = firstKf->getCameraHeightField();
  double horizontAngle = firstKf->getCameraViewAspect()*verticalAngle;
  double fw = 2*tan(verticalAngle/2.0)*focalDistance;
  double fh = fw / firstKf->getCameraViewAspect();

  pCamera->setupCamera(position, target, up);
  pCamera->setViewParameters(fw, fh, true);

  pCamera->setDisplayGlyph(true);
  pCamera->setDisplayTarget(true);
  
  pCamera->setAdjustLensLength(false);
  pCamera->setAutoAdjust(false);

  OdTvAnimationContainerId contId;
  OdTvAnimationContainerPtr pContainer;
  OdTvAnimationActionId positionActionId, targetActionId, fieldsActionId, upActionId;
  OdTvAnimationActionPtr pPositionAction, pTargetAction, pFieldsAction, pUpAction;

  contId = m_pTvDb->createAnimationContainer(pAnimGrp->getDisplayName());
  pContainer = contId.openObject(OdTv::kForWrite);
  
  targetActionId = m_pTvDb->createAnimationAction(OD_T("TargetPositionMoveAction"));
  pTargetAction = targetActionId.openObject(OdTv::kForWrite);
  pTargetAction->setFPS(kps);
  pTargetAction->setNumFrames(totalKfnum);

  positionActionId = m_pTvDb->createAnimationAction(OD_T("CameraPositionMoveAction"));
  pPositionAction = positionActionId.openObject(OdTv::kForWrite);
  pPositionAction->setFPS(kps);
  pPositionAction->setNumFrames(totalKfnum);

  fieldsActionId = m_pTvDb->createAnimationAction(OD_T("CameraFieldScaleAction"));
  pFieldsAction = fieldsActionId.openObject(OdTv::kForWrite);
  pFieldsAction->setFPS(kps);
  pFieldsAction->setNumFrames(totalKfnum);

  upActionId = m_pTvDb->createAnimationAction(OD_T("CameraUpMoveAction"));
  pUpAction = upActionId.openObject(OdTv::kForWrite);
  pUpAction->setFPS(kps);
  pUpAction->setNumFrames(totalKfnum);

  double prevFocalDistance = 0;
  for (OdNwSavedAnimKeyFramePtr kf : setKeyFrame)
  {
    double kfTime = kf->getTime();
    int kftl = ceil(kfTime * kps);

    OdGeQuaternion camq = kf->getCameraRotation();
    OdGeMatrix3d matr = camq.getMatrix();

    double curFocalDistance = kf->getFocalDistance();
    if (OdEqual(curFocalDistance, 0))
    {
      ODA_ASSERT(!OdEqual(prevFocalDistance, 0));
      curFocalDistance = prevFocalDistance;
    }
    else
    {
      prevFocalDistance = curFocalDistance;
    }

    ODA_ASSERT(!OdEqual(curFocalDistance, 0));

    OdTvPoint newTarget = kf->getCameraPosition() - matr.getCsZAxis() * curFocalDistance;
    pTargetAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationX, newTarget.x - target.x, OdTvAnimationAction::kLinear);
    pTargetAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationY, newTarget.y - target.y, OdTvAnimationAction::kLinear);
    pTargetAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationZ, newTarget.z - target.z, OdTvAnimationAction::kLinear);
    
    OdTvPoint newPosition = kf->getCameraPosition();
    pPositionAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationX, newPosition.x - position.x, OdTvAnimationAction::kLinear);
    pPositionAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationY, newPosition.y - position.y, OdTvAnimationAction::kLinear);
    pPositionAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationZ, newPosition.z - position.z, OdTvAnimationAction::kLinear);

    double verticalAngle = kf->getCameraHeightField();
    double horizontAngle = kf->getCameraViewAspect()*verticalAngle;
    double kf_fw = 2 * tan(verticalAngle / 2.0) * curFocalDistance;
    double kf_fh = fw / kf->getCameraViewAspect();

    pFieldsAction->setKeypoint(kftl, OdTvAnimationAction::kScaleX, kf_fw / fw, OdTvAnimationAction::kLinear);
    pFieldsAction->setKeypoint(kftl, OdTvAnimationAction::kScaleY, kf_fh / fh, OdTvAnimationAction::kLinear);

    OdTvVector kf_up = matr.getCsYAxis();

    pUpAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationX, kf_up.x - up.x, OdTvAnimationAction::kLinear);
    pUpAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationY, kf_up.y - up.y, OdTvAnimationAction::kLinear);
    pUpAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationZ, kf_up.z - up.z, OdTvAnimationAction::kLinear);
  }
  {
    OdTvSubItemPath actor;
    actor.entitiesIds().push_back(cameraId);
    actor.geometryDatasIds().push_back(pCamera->targetId());
    pContainer->addAnimation(actor, targetActionId, 0);
  }
  {
    OdTvSubItemPath actor;
    actor.entitiesIds().push_back(cameraId);
    actor.geometryDatasIds().push_back(pCamera->positionId());
    pContainer->addAnimation(actor, positionActionId, 0);
  }
  {
    OdTvSubItemPath actor;
    actor.entitiesIds().push_back(cameraId);
    actor.geometryDatasIds().push_back(pCamera->fieldsId());
    pContainer->addAnimation(actor, fieldsActionId, 0);
  }
  {
    OdTvSubItemPath actor;
    actor.entitiesIds().push_back(cameraId);
    actor.geometryDatasIds().push_back(pCamera->upId());
    pContainer->addAnimation(actor, upActionId, 0);
  }

  pCamera->assignView(newViewId);
  return true;
}

bool OdTvNwSavedAnimationEnumerator::collectSelectAnim(const OdNwSavedAnimSelectAnim * pSelectAnim)
{
  OdNwObjectIdArray ObjIdList;
  ObjIdList = pSelectAnim->getModelItem();
  return true;
}

bool OdTvNwSavedAnimationEnumerator::enumSelectAnim(const OdNwSavedAnimSelectAnim * pSelectAnim)
{
  OdTvResult er = tvOk;
  if (!pSelectAnim)
  {
    return false;
  }
  OdTvDevicesIteratorPtr pDevIt = m_pTvDb->getDevicesIterator();
  OdTvGsDevicePtr pDevice = pDevIt->getDevice().openObject(OdTv::kForWrite);
  OdTvGsViewId originalViewId = pDevice->viewAt(0);
  OdTvGsViewPtr pOriginalView = originalViewId.openObject(OdTv::kForWrite);
  OdNwObjectIdArray ObjIdList;

  if (!pSelectAnim || pSelectAnim->getChildren(ObjIdList) != eOk)
  {
    return false;
  }

  auto keyFrameComparFn = [](const OdNwSavedAnimSelectKeyFramePtr & a, const OdNwSavedAnimSelectKeyFramePtr & b)
  {
    return a->getTime() < b->getTime();
  };

  std::set<OdNwSavedAnimSelectKeyFramePtr, decltype(keyFrameComparFn)> setKeyFrame(keyFrameComparFn);

  for (auto & sceneChildId : ObjIdList)
  {
    OdNwSavedAnimSelectKeyFramePtr pAnimSelectKeyFrame = OdNwSavedAnimSelectKeyFrame::cast(sceneChildId.safeOpenObject());
    setKeyFrame.insert(pAnimSelectKeyFrame);
  }
  OdNwSavedAnimSelectKeyFramePtr firstKf = *setKeyFrame.begin();
  OdNwSavedAnimSelectKeyFramePtr lastKf = *setKeyFrame.rbegin();
  double kps = 24;
  double lastKfTime = lastKf->getTime();
  int totalKfnum = ceil(lastKfTime*kps) + 1;

  OdTvAnimationContainerId contId = m_pTvDb->createAnimationContainer(pSelectAnim->getDisplayName());
  OdTvAnimationContainerPtr pContainer = contId.openObject(OdTv::kForWrite);

  OdTvAnimationActionId translateActionId = m_pTvDb->createAnimationAction(OD_T("TranslateAction") + pSelectAnim->getDisplayName());
  OdTvAnimationActionPtr pTranslateAction = translateActionId.openObject(OdTv::kForWrite);
  pTranslateAction->setFPS(kps);
  pTranslateAction->setNumFrames(totalKfnum);

  OdGePoint3d firstPos;
  OdGeVector3d firstScale(1.,1.,1.);

  OdGePoint3d center = firstKf->getCenter();
  OdGeVector3d transl = firstKf->getTranslation();

  for (OdNwSavedAnimSelectKeyFramePtr kf : setKeyFrame)
  {
    double kfTime = kf->getTime();
    int kftl = ceil(kfTime * kps);

    OdGePoint3d newCenter = kf->getCenter();
    OdGeVector3d newTransl = kf->getTranslation();
    OdGeVector3d scaleVec =  kf->getScaleVector();
    OdGeQuaternion rotationQuat = kf->getRotation();
    pTranslateAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationX, newTransl.x - firstPos.x, OdTvAnimationAction::kLinear);
    pTranslateAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationY, newTransl.y - firstPos.y, OdTvAnimationAction::kLinear);
    pTranslateAction->setKeypoint(kftl, OdTvAnimationAction::kTranslationZ, newTransl.z - firstPos.z, OdTvAnimationAction::kLinear);

    pTranslateAction->setKeypoint(kftl, OdTvAnimationAction::kScaleX, scaleVec.x, OdTvAnimationAction::kLinear);
    pTranslateAction->setKeypoint(kftl, OdTvAnimationAction::kScaleY, scaleVec.y, OdTvAnimationAction::kLinear);
    pTranslateAction->setKeypoint(kftl, OdTvAnimationAction::kScaleZ, scaleVec.z, OdTvAnimationAction::kLinear);
  }

  for (auto & mi : pSelectAnim->getModelItem())
  {
    mapNwObjId2TvIdsType::iterator fit = m_NwOIds2TvIdsMap.find(mi);
    if (fit != m_NwOIds2TvIdsMap.end())
    {
      for (auto & targetEntityId : fit->second)
      {
        OdTvSubItemPath actor;
        OdTvEntityId::EntityTypes ttyp = targetEntityId.getType();
        actor.entitiesIds().push_back(targetEntityId);
        OdTvEntityId::EntityTypes entityType = targetEntityId.getType();
        if (entityType == OdTvEntityId::EntityTypes::kInsert)
        {
          OdTvInsertPtr pTargetEntIns = targetEntityId.openObjectAsInsert(OdTv::kForRead, &er);
          if (er != tvOk)
          {
            continue;
          }
          OdTvEntitiesIteratorPtr pIter = pTargetEntIns->getSubEntitiesIterator();
          if (!pIter.isNull())
          {
            while (!pIter->done())
            {
              OdTvSubItemPath attrActor;
              attrActor.entitiesIds().push_back(pIter->getEntity());
              pContainer->addAnimation(attrActor, translateActionId, 0);
              pIter->step();
            }
          }
        }
        pContainer->addAnimation(actor, translateActionId, 0);
      }
    }
  }
  
  return true;
}

void OdTvNwSavedAnimationEnumerator::enumSceneChild(const OdNwSavedItem * pSceneChild)
{
  if (pSceneChild)
  {
    if (pSceneChild->isKindOf(OdNwSavedAnimSelectAnim::desc()))
    {
      m_selectAnimEnumerator(OdNwSavedAnimSelectAnim::cast(pSceneChild));
    }
    else if (pSceneChild->isKindOf(OdNwSavedAnimFolder::desc()))
    {
    }
    else if (pSceneChild->isKindOf(OdNwSavedAnimClip::desc()))
    {
    }
    else if (pSceneChild->isKindOf(OdNwSavedAnimGroup::desc()))
    {
      m_animGroupEnumerator(OdNwSavedAnimGroup::cast(pSceneChild));
      enumAnimGroup(OdNwSavedAnimGroup::cast(pSceneChild));
    }
  }
};
  
void OdTvNwSavedAnimationEnumerator::enumAnimScene(const OdNwSavedAnimScene * pScene)
{
  OdNwObjectIdArray sceneChildIdList;
  if (pScene && pScene->getChildren(sceneChildIdList) == eOk)
  {
    for (auto & sceneChildId : sceneChildIdList)
    {
      enumSceneChild(OdNwSavedItem::cast(sceneChildId.safeOpenObject()));
    }
  }
};

void OdTvNwSavedAnimationEnumerator::enumAnimSceneFolder (const OdNwSavedAnimSceneFolder * pSceneFolder)
{
  ODA_ASSERT(pSceneFolder);
  OdNwObjectIdArray ObjIdList;;
  pSceneFolder->getChildren(ObjIdList);

  for (auto& item : ObjIdList)
  {
    enumAnimScene(OdNwSavedAnimScene::cast(item.safeOpenObject()));
  };
};

void OdTvNwSavedAnimationEnumerator::enumSelectedModels()
{
  m_selectAnimEnumerator = [this](const OdNwSavedAnimSelectAnim * pSelectAnim) -> bool
  {
    OdNwObjectIdArray ObjIdList;
    if (pSelectAnim) {
      ObjIdList = pSelectAnim->getModelItem();
      for (auto & obj : ObjIdList)
      {
        m_selectedModels.push_back(obj);
        mapNwObjId2TvIdsType::value_type value(obj, {});
        m_NwOIds2TvIdsMap.insert(value);
      }
      return true;
    }
    return false;
  };
  m_animGroupEnumerator = [this](const OdNwSavedAnimGroup * pAnimGrp) -> bool
  {
    return true;
  };
  enumAnimation();
}

void OdTvNwSavedAnimationEnumerator::enumAnimation()
{
  OdNwObjectId savedAnimationElementId = m_pNwDb->getSavedAnimationElementId();
  if (savedAnimationElementId.isNull())
  {
    return;
  }
  OdNwSavedAnimElementPtr pSavedAnimElem = savedAnimationElementId.safeOpenObject();
  OdNwObjectIdArray savedItemIdList;
  if (pSavedAnimElem->getSavedItems(savedItemIdList) == eOk)
  {
    for (auto& item : savedItemIdList)
    {
      OdNwSavedItemPtr pItem = item.safeOpenObject();
      if (!pItem.isNull())
      {
        if (pItem->isKindOf(OdNwSavedAnimScene::desc()))
        {
          enumAnimScene(OdNwSavedAnimScene::cast(pItem));
        }
        else if (pItem->isKindOf(OdNwSavedAnimSceneFolder::desc()))
        {
          enumAnimSceneFolder(OdNwSavedAnimSceneFolder::cast(pItem));
        }
      }
    }
  }
}

void OdTvNwSavedAnimationEnumerator::feedAnimation()
{
  m_selectAnimEnumerator = std::bind(&OdTvNwSavedAnimationEnumerator::enumSelectAnim, this, std::placeholders::_1);
  m_animGroupEnumerator = std::bind(&OdTvNwSavedAnimationEnumerator::enumAnimGroup, this, std::placeholders::_1);
  enumAnimation();
}

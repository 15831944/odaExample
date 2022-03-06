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
#define _USE_MATH_DEFINES

#include "Trackers.h"
#include "Gi/GiWorldDraw.h"
#include <string>
#include <iostream>
#include "Ge/GeLine3d.h"
#include <cmath>
#include "TvGsView.h"
#include "TvGeometryTypifiedData.h"
#include "TvDatabase.h"

void TVCTracker::init(OdTvDatabaseId *dbId)
{
  db_id_ = dbId;
}

void TVCTracker::initDirect()
{

  OdTvDatabasePtr db = db_id_->openObject(OdTv::kForWrite);
  OdTvModelId dir_mdl_ = db->findModel("Direct");

  if (dir_mdl_.isNull())
  {
    OdTvGsViewPtr pView;
    OdTvDevicesIteratorPtr pIt = db_id_->openObject()->getDevicesIterator();
    if (!pIt.isNull())
    {

      OdTvGsViewId vId = pIt->getDevice().openObject()->getActiveView();
      pView = vId.openObject(OdTv::kForWrite);
    }
    dir_mdl_ = db->createModel("Direct", OdTvModel::kDirect, false);
    pView->addModel(dir_mdl_);
  }
  direct_ = dir_mdl_;
}

void SelectionFrame::setValue(const OdGePoint3d &value)
{
  points_[2] = value;
  draw();
}

void SelectionFrame::setStartPoint(const OdGePoint3d &value)
{
  initDirect();

  points_[0] = value;
  points_[2] = value;

  draw(true);
}

void SelectionFrame::draw(bool is_created)
{
  OdTvGsViewPtr avp;
  OdTvDevicesIteratorPtr pIt = db_id_->openObject()->getDevicesIterator();
  if (!pIt.isNull())
  {

    OdTvGsViewId vId = pIt->getDevice().openObject()->getActiveView();
    avp = vId.openObject(OdTv::kForWrite);
  }

  if (avp.isNull())
    return;

  OdGeMatrix3d x = avp->viewingMatrix();
  OdGePoint3d p0 = x * points_[0];
  OdGePoint3d p2 = x * points_[2];

  points_[1].x = p0.x;
  points_[3].x = p2.x;
  points_[1].y = p2.y;
  points_[3].y = p0.y;
  points_[1].z = points_[3].z = p2.z;

  x = avp->eyeToWorldMatrix();
  points_[1].transformBy(x);
  points_[3].transformBy(x);

  if (is_created)
  {
    OdTvModelPtr model = direct_.openObject(OdTv::kForWrite);
    entity_ = model->appendEntity();
    {
      OdTvEntityPtr entity = entity_.openObject(OdTv::kForWrite);
      frame_ = entity->appendPolygon(points_);
      entity->setColor(color_);
    }
  }
  else
  {
    OdTvGeometryDataPtr frame_ptr = frame_.openObject();
    if (frame_ptr.isNull() || frame_ptr->getType() != OdTv::kPolygon)
    {
      return;
    }

    OdTvPolygonDataPtr polygon_ptr = frame_ptr->getAsPolygon();
    if (!polygon_ptr.isNull())
    {
      polygon_ptr->setPoints(points_);
    }
  }
}

SelectionFrame::SelectionFrame()
{
  points_.resize(4);
}

void SelectionFrame::setMode(SelectionFrameMode mode)
{
  mode_ = mode;
  if (mode_ == kFrame)
  {
    color_.setColor(0, 255, 0);
  }
  else
  {
    color_.setColor(0, 0, 255);
  }
}

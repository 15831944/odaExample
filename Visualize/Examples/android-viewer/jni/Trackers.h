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
#pragma once
#define _USE_MATH_DEFINES
#include "OdaCommon.h"
#include "Ed/EdUserIO.h"
#include "Gi/GiDrawableImpl.h"
#include "Ge/GePoint3d.h"
#include "Gi/GiCommonDraw.h"
#include "Gi/GiViewportDraw.h"
#include "RxObjectImpl.h"
#include "AbstractViewPE.h"
#include <vector>
#include "Gi/GiTextStyle.h"
#include "CmColorBase.h"
#include <cmath>
#include "TvGsView.h"

class TVCTracker {
protected:
  OdTvModelId  direct_;
  OdTvEntityId entity_;
  OdTvDatabaseId *db_id_;

public:
  void init(OdTvDatabaseId *dbId);

  void initDirect();

  void clear() {
    if (!direct_.isNull()) {
      direct_.openObject(OdTv::kForWrite)->clearEntities();
    }
  }

  virtual void setValue(const OdGePoint3d &value) {};

  virtual void setStartPoint(const OdGePoint3d &value) {};

  virtual void draw(bool is_created = false) {};
};

enum SelectionFrameMode
{
	kSelect,
	kFrame
};

class SelectionFrame : public TVCTracker {
public:
  SelectionFrame();

	void setMode(SelectionFrameMode mode);

  void setValue(const OdGePoint3d &value);

  void setStartPoint(const OdGePoint3d &value);

  void draw(bool is_created = false);

private:
  OdTvPointArray     points_;
  SelectionFrameMode mode_;
  OdTvGeometryDataId frame_;
  OdTvColorDef       color_;
};

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

#ifndef __NW_SAVEDANIMKEYFRAME_IMPL_H__
#define __NW_SAVEDANIMKEYFRAME_IMPL_H__

#include "NwObjectImpl.h"
#include "NwSavedGroupItemImpl.h"
#include "NwSavedAnimKeyFrame.h"
#include "InternalClasses/NwCamera.h"
class NWDBEXPORT OdNwSavedAnimKeyFrameImpl : public OdNwSavedGroupItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSavedAnimKeyFrame)
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimKeyFrameImpl);
public:
  OdNwSavedAnimKeyFrameImpl();
  virtual ~OdNwSavedAnimKeyFrameImpl();
  static OdNwSavedAnimKeyFrameImpl* getImpl(const OdNwSavedAnimKeyFrame *);
  static OdNwSavedAnimKeyFrameImpl* getImpl(const OdRxObject *);
  void setFocalDistance(double v);
  double getFocalDistance() const;
  void setTime(double v);
  double getTime() const;
  void setInterpolationFlag(bool v);
  bool isInterpolation() const;
  OdNwCamera & getCamera();
  NwViewType::Enum getCameraProjection() const;
  const OdGePoint3d& getCameraPosition() const;
  const OdGeQuaternion& getCameraRotation() const;
  double getCameraViewAspect() const;
  double getCameraHeightField() const;
  double getCameraNear() const;
  double getCameraFar() const;
  double getCameraUpOffsetFactor() const;
  double getCameraRightOffsetFactor() const;
private:
  double m_FocalDistance;
  OdNwCamera m_Camera;
  double m_Time;
  bool m_IsInterpolation;
};

typedef OdSmartPtr<OdNwSavedAnimKeyFrameImpl> OdNwSavedAnimKeyFrameImplPtr;

#endif /* __NW_SAVEDANIMKEYFRAME_IMPL_H__ */

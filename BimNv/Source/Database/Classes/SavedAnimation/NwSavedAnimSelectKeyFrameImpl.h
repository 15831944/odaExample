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

#ifndef __NW_SAVEDANIMSELECTKEYFRAME_IMPL_H__
#define __NW_SAVEDANIMSELECTKEYFRAME_IMPL_H__

#include "NwObjectImpl.h"
#include "NwColor.h"
#include "Ge/GeQuaternion.h"
#include "NwSavedItemImpl.h"
#include "NwSavedAnimSelectKeyFrame.h"

class NWDBEXPORT OdNwSavedAnimSelectKeyFrameImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwSavedAnimSelectKeyFrame)
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimSelectKeyFrameImpl);
public:
  OdNwSavedAnimSelectKeyFrameImpl();
  virtual ~OdNwSavedAnimSelectKeyFrameImpl();
  static OdNwSavedAnimSelectKeyFrameImpl* getImpl(const OdNwSavedAnimSelectKeyFrame *);
  static OdNwSavedAnimSelectKeyFrameImpl* getImpl(const OdRxObject *);
  
  void setScaleVector(const OdGeVector3d& v);
  const OdGeVector3d & getScaleVector() const;
  void setScaleQuaternion(const OdGeQuaternion& q);
  const OdGeQuaternion & getScaleQuaternion() const;
  void setTime(double v);
  double getTime() const;
  void setInterpolationFlag(bool v);
  bool isInterpolation() const;
  void setTranslation(const OdGeVector3d& tr);
  const OdGeVector3d& getTranslation() const;
  void setRotation(const OdGeQuaternion & quat);
  const OdGeQuaternion & getRotation() const;
  void setToolOrientation(const OdGeQuaternion & quat);
  const OdGeQuaternion & getToolOrientation() const;
  void setCenter(const OdGePoint3d & p);
  const OdGePoint3d & getCenter() const;
  void setColor(const OdNwColor & clr);
  const OdNwColor & getColor()  const;
  void setOpacity(double v);
  double getOpacity() const;
  OdUInt32 getSign() const;
  void setSign(OdUInt32 s);
private:
  double m_Time;
  bool m_IsInterpolation;
  OdGeVector3d m_Translation;
  OdGeQuaternion m_Rotation;
  OdGeQuaternion m_ToolOrient;
  OdGePoint3d m_Center;
  OdNwColor m_Color;
  double m_Opacity;
  OdGeVector3d m_ScaleVec;
  OdGeQuaternion m_ScaleQuat;
  OdUInt32 m_Sign;
  
};

typedef OdSmartPtr<OdNwSavedAnimSelectKeyFrameImpl> OdNwSavedAnimSelectKeyFrameImplPtr;

#endif /* __NW_SAVEDANIMSELECTKEYFRAME_IMPL_H__ */

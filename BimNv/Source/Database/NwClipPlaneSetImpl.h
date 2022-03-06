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

#ifndef __NWCLIPPLANESETIMPL_H__
#define __NWCLIPPLANESETIMPL_H__

#include "NwExport.h"
#include "NwObjectImpl.h"
#include "NwClipPlaneSet.h"
#include "NwClipPlaneSetMode.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "Ge/GeExtents3d.h"
#include "Ge/GeQuaternion.h"

class NWDBEXPORT OdNwClipPlaneSetImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwClipPlaneSet)
public:
  OdNwClipPlaneSetImpl();
  virtual ~OdNwClipPlaneSetImpl();
  ODRX_DECLARE_MEMBERS(OdNwClipPlaneSetImpl);

public:
  static OdNwClipPlaneSetImpl* getImpl(const OdNwClipPlaneSet* pNwClipPLane);
  static OdNwClipPlaneSetImpl* getImpl(const OdRxObject* pRxClipPLane);

public:
  inline NwClipPlaneSetMode::Enum getMode() const { return m_mode; }

public:
  const OdGeMatrix3d getTransform() const;
  OdResult getPlanesForActiveMode(OdArray<OdGePlane>& planes) const;
  OdResult getClipPlaneByIndex(OdNwClipPlane& clipPlane, OdUInt32 idx);
  bool isLinked() const;
  OdUInt32 getCurrentPlaneIndex() const;
  const OdGeExtents3d& getRange() const;
  bool isEnabled() const;
  const OdGeExtents3d& getBox() const;
  const OdGeQuaternion& getRotation() const;

public:
  void setClipPlaneByIndex(const OdNwClipPlane& clipPlane, OdUInt32 idx);
  void setIsLinked(bool val);
  void setCurrentPlaneIndex(OdUInt32 index);
  void setRange(OdGeExtents3d&& val);
  void setMode(NwClipPlaneSetMode::Enum val);
  void setIsEnabled(bool val);
  void setBox(OdGeExtents3d&& val);
  void setRotation(OdGeQuaternion&& val);

  void computeBoxTransform();

private:
  std::vector<OdNwClipPlane> m_vClipPlanes;
  bool m_bIsLinked;
  OdUInt32 m_currentPlaneIndex;
  OdGeExtents3d m_range;
  NwClipPlaneSetMode::Enum m_mode;
  bool m_bIsEnabled;
  OdGeExtents3d m_box;
  OdGeQuaternion m_rotation;
  OdGeMatrix3d m_transform;
};



#endif //__NWCLIPPLANESETIMPL_H__

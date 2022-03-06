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

#ifndef __NWREDLINETAG_IMPL_
#define __NWREDLINETAG_IMPL_

#include "Redline/NwRedLineTag.h"
#include "NwRedLineImpl.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeExtents3d.h"

class OdNwRedLineTag;
class OdNwRedLineTagImpl;


class OdNwRedLineTagImpl : public OdNwRedLineImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwRedLineTag)
public:
  ODRX_DECLARE_MEMBERS(OdNwRedLineTagImpl);
  OdNwRedLineTagImpl();
  virtual ~OdNwRedLineTagImpl();

public:
  virtual NwRedLineType::Enum getType() const;
  bool getDirectionFlag() const;
  OdGeVector3d getDirection();
  bool getBoundFlag() const;
  OdGeExtents3d getBound() const;
  OdGeExtents2d getPosition() const;
  OdUInt64 getTagId() const;
  OdUInt64 getCommentId() const;

public:
  void setDirectionFlag(bool val);
  void setDirection(const OdGeVector3d& val);
  void setBoundFlag(bool val);
  void setBound(const OdGeExtents3d& val);
  void setPosition(const OdGeExtents2d& val);
  void setTagId(OdUInt64 val);
  void setCommentId(OdUInt64 val);

public:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwRedLineTagImpl* getImpl(const OdNwRedLineTag* pObj);
  static OdNwRedLineTagImpl* getImpl(const OdRxObject* pObj);

protected:
  bool m_bDirectionFlag;
  OdGeVector3d m_direction;
  bool m_bBoundFlag;
  OdGeExtents3d m_bounds;
  OdGeExtents2d m_position;
  OdUInt64 m_tagId;
  OdUInt64 m_commentId;
};

#endif //__NWREDLINETAG_IMPL_

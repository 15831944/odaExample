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

#ifndef __NWBASETREEITEMIMPL_INCLUDED__
#define __NWBASETREEITEMIMPL_INCLUDED__

#include "NwObjectImpl.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"

class OdNwTreeItemImpl;

class NWDBEXPORT OdNwBaseTreeItemImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwBaseTreeItem)
public:
  OdNwBaseTreeItemImpl();
  virtual ~OdNwBaseTreeItemImpl();
  ODRX_DECLARE_MEMBERS(OdNwBaseTreeItemImpl);

  static OdNwBaseTreeItemImpl* getImpl(const OdNwObject* pNwObject);
  static OdNwBaseTreeItemImpl* getImpl(const OdRxObject* pRxObject);

public:
  inline OdUInt32& getTraversableModifiedFlags() { return m_traversableModifiedFlags; }
  double getTraversableScale() const;
  OdUInt32 getTraversableTris() const;

//traversable modified flags methods:
  inline bool isTraversed() const        { return m_traversableModifiedFlags & 0x200000; }
  inline bool isLeaf() const             { return m_traversableModifiedFlags & 0x400000; }
  inline OdUInt8 getPrimitivies() const { return (m_traversableModifiedFlags & 0x1F0000) >> 16; }
  inline bool isShape() const            { return m_traversableModifiedFlags & 0x800000; }
  inline bool isHideRender() const       { return m_traversableModifiedFlags & 0x1000000; }
  inline bool isForceRender() const      { return m_traversableModifiedFlags & 0x2000000; }
  inline bool hasMultipleParents() const { return m_traversableModifiedFlags & 0x4000000; }
  inline bool isUserOwned() const        { return m_traversableModifiedFlags & 0x8000000; }
  inline bool isIgnoreClip() const       { return m_traversableModifiedFlags & 0x10000000; }
  inline bool isIgnorePick() const       { return m_traversableModifiedFlags & 0x20000000; }
  
public:
  void setTraversableScale(const double& val);
  void setTraversableTris(OdUInt32 val);
  void setPrimitives(OdUInt8 primitives);
  void setHideRender(bool flag);
  void setForceRender(bool flag);

public:
  OdResult addParent(OdNwTreeItemImpl* pParent);
  OdResult removeParent(OdNwTreeItemImpl* pParent);

private:
  //traversable block:
  double                         m_traversableScale;
  OdUInt32                       m_traversableTris;
  OdUInt32                       m_traversableModifiedFlags;
  std::vector<OdNwTreeItemImpl*> m_vParents;
};



#endif //__NWBASETREEITEMIMPL_INCLUDED__

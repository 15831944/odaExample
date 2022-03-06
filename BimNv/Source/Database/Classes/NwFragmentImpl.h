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

#ifndef __NWFRAGMENTIMPL_INCLUDED__
#define __NWFRAGMENTIMPL_INCLUDED__

#include "NwFragment.h"
#include "NwBaseTreeItemImpl.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdNwGraphicAppearance;
typedef OdSmartPtr< OdNwGraphicAppearance> OdNwGraphicAppearancePtr;
class OdNwGraphicGeometryRef;
typedef OdSmartPtr<OdNwGraphicGeometryRef> OdNwGraphicGeometryRefPtr;
class OdNwGeometryStreamLoader;
class OdNwSharedNodesStreamLoader;
class OdNwObjTransform;
typedef OdSmartPtr<OdNwObjTransform> OdNwObjTransformPtr;
class OdNwModelItem;
class OdGeExtents3d;

class NWDBEXPORT OdNwFragmentImpl : public OdNwBaseTreeItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwFragment)
public:
  OdNwFragmentImpl();
  virtual ~OdNwFragmentImpl();
  ODRX_DECLARE_MEMBERS(OdNwFragmentImpl);

public:
  bool draw(OdGiWorldDraw* pWd) const;

public:
  static OdNwFragmentImpl* getImpl(const OdNwFragment* pNwFragment);
  static OdNwFragmentImpl* getImpl(const OdRxObject* pRxFragment);

public:
  //public implementation's methods
  OdGePoint3d getLowBound() const;
  OdGePoint3d getHighBound() const;
  OdGeMatrix3d getTransformation() const;
  // TODO: to deleted start: This block of methods os deprecated
  bool isEllipse() const;
  bool isLineSet() const;
  bool isMesh() const;
  bool isPointSet() const;
  bool isText() const;
  bool isTube() const;
  bool isExternal() const;
  bool checkGeometryType(OdRxClass* pClass) const;

  OdResult setTransformation(const OdGeMatrix3d& trm);

public:
  OdResult updateGeometryIndexFromGeometry();
  void setGeometryIndex(OdUInt32 index);
  OdInt32 getGeometryIndex() const;
  OdNwObjectId getGeometryId() const;
  void setGeometry(const OdNwObjectId& geometryId);

public:
  inline OdUInt32& getFragmentFlags() { return m_fragmentFlags; }
  OdNwGraphicAppearancePtr getOriginalAppearance() const;
  inline bool isAppearanceOverride() const { return !m_pOriginalAppearance.isNull(); }
  OdNwModelItem* getPathLink() const;
  OdNwObjTransformPtr getTransform() const;
  OdNwGraphicGeometryRefPtr getGeometryRef() const;

//fragment flags methods:
  inline bool isSolid() const                     { return m_fragmentFlags & 0x2; }
  inline bool isGeometryUnnormalized() const      { return m_fragmentFlags & 0x4; }
  inline bool isGeometryReversed() const          { return m_fragmentFlags & 0x10; }
  inline bool isTransformReverse() const          { return m_fragmentFlags & 0x20; }  
  inline bool isHighlight() const                 { return m_fragmentFlags & 0x40; }
  inline bool isTransformFragmentInternal() const { return m_fragmentFlags & 0x80; }
  inline bool isTransformItemInternal() const     { return m_fragmentFlags & 0x20000; }
  inline bool isTransformOverride() const         { return m_fragmentFlags & 0x20000000; }

//core shape methods
  inline bool isTransformInternalImplicit() const { return isTransformFragmentInternal() && isTransformItemInternal() && !isTransformOverride(); }
  
public:
  void setGeometryLoader(std::weak_ptr<OdNwGeometryStreamLoader> pGeomLoader);
  void setOriginalAppearance(OdNwGraphicAppearancePtr pAppearance);
  void setGeomRef(OdNwGraphicGeometryRefPtr pGeomRef);
  void setTransform(OdNwObjectPtr pTransform);
  void setPathLink(OdNwModelItem* pRunPathLink);

public:
  void calcBoundingBox(OdGeExtents3d& boundBox) const;

private:
  //fragment block
  OdNwGraphicAppearancePtr  m_pOriginalAppearance;
  OdNwGraphicGeometryRefPtr m_pGeomRef;
  //coreShape block:
  OdNwObjTransformPtr       m_pTransform;
  OdNwModelItem*            m_pPathLink;
  OdUInt32                  m_fragmentFlags;
  mutable OdNwObjectId      m_geometryId;
  // Loaders
  mutable std::weak_ptr<OdNwGeometryStreamLoader>    m_pGeomLoader;
 };

typedef OdSmartPtr<OdNwFragmentImpl> OdNwFragmentImplPtr;

#endif //__NWFRAGMENTIMPL_INCLUDED__

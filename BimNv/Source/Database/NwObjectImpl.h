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

#ifndef _NWOBJECTIMPL_H_
#define _NWOBJECTIMPL_H_

#include "Ge/GeMatrix3d.h"
#include "NwObject.h"
#include "NwObjectContainer.h"
#include "OdBinaryData.h"
#define STL_USING_MAP
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "NwModeType.h"
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) && (GCC_VERSION < 50300)
//VAS: this is fix for incorrect behaivour of gcc before 5.3 version with access to protected static methods
#define ODNW_DECLARE_FRIEND_FOR_IMPL(friendClassName) friend class friendClassName;
#else
#define ODNW_DECLARE_FRIEND_FOR_IMPL(friendClassName)
#endif

namespace NwObjectFlags
{
  enum Enum
  {
    kReadEnabled = 0x1,
    kWriteEnabled = 0x2
  };
}

class OdNwObjectImpl : public OdGiDrawable// : public OdNwObject
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwObject)
protected:
  friend class OdNwDatabase;
  friend class OdNwDatabaseImpl;
  OdNwObjectId m_id;
  OdGsCache* m_pGsNode;
  OdUInt32 m_flags;
  OdRefCounter m_nRefCounter;
  OdNwObject* m_pFacade;

  OdNwObjectImpl();
public:
  virtual ~OdNwObjectImpl();
  ODRX_DECLARE_MEMBERS(OdNwObjectImpl);

  static OdNwObjectImpl* getImpl(const OdNwObject* pNwObj);
  static OdNwObjectImpl* getImpl(const OdRxObject* pRxObj);

  // OdNwObject members:
  virtual OdNwObjectId objectId() const;
  virtual OdDbStub* ownerId() const;
  virtual void addReactor(OdNwObjectReactor* pReactor);
  virtual void removeReactor(OdNwObjectReactor* pReactor);

  // OdGiDrawable members:
  virtual bool isPersistent() const;
  virtual OdDbStub* id() const;
  virtual void setGsNode(OdGsCache* pGsNode);
  virtual OdGsCache* gsNode() const;
  //protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* traits) const override;
  virtual bool subWorldDraw(OdGiWorldDraw* wd) const override;
  virtual void subViewportDraw(OdGiViewportDraw* vd) const override;
  //OdRxObject members:
  void addRef() override;
  long numRefs() const override;
  void release() override;
  void releaseObject();

public:
  inline void setFacade(OdNwObject* pObj) { m_pFacade = pObj; }
protected:
  inline OdNwObject* getFacade() { return m_pFacade; }
  inline const OdNwObject* getFacade() const { return m_pFacade; }

public:
  void setDatabaseDefaults(OdNwDatabase* pDb, bool doSubent);
  virtual void subSetDatabaseDefaults(OdNwDatabase* pDb, bool doSubents);

  //flag setting/getting
public:
  template <OdUInt32 flag>
  inline void setFlagEnabled(bool val) { val ? m_flags |= flag : m_flags &= ~flag; }
  template <OdUInt32 flag>
  inline bool isFlagEnabled() const { return m_flags & flag; }

//open mode part
public:
  NwOpenMode::Enum getOpenMode() const;
  void setOpenMode(NwOpenMode::Enum mode);

public:
  //VAS: this function is need to create correct OdNwObject with pimpl structure, if your OdNwObject has empty pointer to implementation - there is need to use OdRxObjectImpl::createObject instead
  //especialy this creating is important for persistent OdNwObject objects
  template <typename T, class ...Args>
  static typename std::enable_if<std::is_base_of<OdNwObject, T>::value, OdSmartPtr<T> >::type createNwObject(Args... args)
  {
    return OdSmartPtr<T>(static_cast<T*>(new T(args...)), kOdRxObjAttach);
  }
};



class NWDBEXPORT OdNwEntity : public OdNwObjectImpl
{
protected:
  OdNwEntity();
public:
  ODRX_DECLARE_MEMBERS(OdNwEntity);

protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* traits) const;
};

typedef OdSmartPtr<OdNwEntity> OdNwEntityPtr;

class NWDBEXPORT OdNwView : public OdNwObjectImpl
{
protected:
  class OdGsView* m_pGsView;
  OdString m_sName;

  OdNwView();

  virtual DrawableType drawableType() const { return kViewport; }
public:
  ODRX_DECLARE_MEMBERS(OdNwView);
  virtual ~OdNwView() {};

  virtual bool isModelLayout() const = 0;
  virtual bool getThumbnail(OdBinaryData& data) const;

  virtual OdString getName() const;
  void getViewports(OdNwObjectIdArray& idsViewports) const;

  OdGsView* gsView() const;
  void setGsView(OdGsView* pGsView);
};

typedef OdSmartPtr<OdNwView> OdNwViewPtr;

class  OdNwModelView : public OdNwView // for 3d NW_TK_Camera
{
protected:
  friend class OdNwGsLayoutHelper;
  //OdGePoint3d m_ptCameraTarget;
  //OdGeVector3d m_vecCameraDir, m_vecCameraUpVector;
  //double m_withField, m_heightField;
  //bool m_isPerspective;
  //OdGeMatrix3d m_matrix;
  //OdNwObjectContainer m_idsSegments;
  OdNwObjectId m_idViewBackground;
  mutable std::pair<NwModeType::Enum, OdNwObjectId> m_prCurVisStyle;

  OdNwModelView();
public:
  ODRX_DECLARE_MEMBERS(OdNwModelView);

  virtual bool isModelLayout() const;
  virtual bool getThumbnail(OdBinaryData& data) const;

  OdResult addViewBackground(OdNwObjectId objId);

protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* traits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* wd) const;
  virtual void subViewportDraw(OdGiViewportDraw* vd) const;
};

typedef OdSmartPtr<OdNwModelView> OdNwModelViewPtr;

#endif // _NWOBJECTIMPL_H_



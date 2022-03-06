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

// ProxyClassList.h: interface for the OdProxyClassList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODAPROXYCLASSLIST_H__034A5AC9_71CF_4EDB_B461_F16A5D9A083C__INCLUDED_)
#define AFX_ODAPROXYCLASSLIST_H__034A5AC9_71CF_4EDB_B461_F16A5D9A083C__INCLUDED_



#include "OdString.h"
#include "OdList.h"
#include "OdToolKit.h"
#include "RxDictionary.h"
#include "DbEntity.h"

#define M_SetBit2(flags, bit, value) (value ? (flags | bit) : (flags & ~bit))

class OdAcadDxfOutStream;
class OdDbDxfFiler;
class OdProxyClassImpl;

class TOOLKIT_EXPORT OdProxyClass : public OdRxClass
{
protected:
  OdProxyClass(OdProxyClassImpl*);
public:
  OdProxyClass();
  ODRX_DECLARE_MEMBERS(OdProxyClass);
  void copyFrom(const OdRxObject* pObj);

  ~OdProxyClass() {}

  void setDxfName(const OdString& classDxfName);
  void setName(const OdString& className);
  void setAppName(const OdString& appName);
  void setProxyFlags(OdUInt32 value);

  OdUInt16 getItemClassId() const;
  void setItemClassId(OdUInt16 value);
  bool isAnEntity() const;
  void setAnEntity(bool value);

  bool wasAProxy() const;
  void setWasAProxy(bool value);

  OdUInt32 numObjects() const;
  void setNumObjects(OdUInt32 n);

  virtual bool isDerivedFrom(const OdRxClass* pClass) const ODRX_OVERRIDE;
  virtual OdRxObjectPtr create() const ODRX_OVERRIDE;

  void setClassVersion(int DwgVer, int MaintVer);

  bool eraseAllowed() const { return GETBIT(proxyFlags(), 1); }
  bool transformAllowed() const { return GETBIT(proxyFlags(), 2); }
  bool colorChangeAllowed() const { return GETBIT(proxyFlags(), 4); }
  bool layerChangeAllowed() const { return GETBIT(proxyFlags(), 8); }
  bool linetypeChangeAllowed() const { return GETBIT(proxyFlags(), 16); }
  bool linetypeScaleChangeAllowed() const { return GETBIT(proxyFlags(), 32); }
  bool visibilityChangeAllowed() const { return GETBIT(proxyFlags(), 64); }
  bool allOperationsExceptCloningAllowed() const { return (proxyFlags() & 127) == 127; }
  bool cloningAllowed() const { return GETBIT(proxyFlags(), 128); }
  bool allOperationsAllowed() const { return (proxyFlags() & 255) == 255; }
  bool isR13FormatProxy() const { return GETBIT(proxyFlags(), 32768); }

  void setNoOperationsAllowed() { setProxyFlags(0); }
  void setEraseAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 1, value)); }
  void setTransformAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 2, value)); }
  void setColorChangeAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 4, value)); }
  void setLayerChangeAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 8, value)); }
  void setLinetypeChangeAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 16, value)); }
  void setLinetypeScaleChangeAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 32, value)); }
  void setVisibilityChangeAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 64, value)); }
  void setAllOperationsExceptCloningAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 128, value)); }
  void setCloningAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 128, value)); }
  void setAllOperationsAllowed(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 255, value)); }
  void setR13FormatProxy(bool value) { setProxyFlags((OdUInt16)M_SetBit2(proxyFlags(), 32768, value)); }

};

typedef OdSmartPtr<OdProxyClass> OdProxyClassPtr;

inline bool wasAProxy(OdRxClass* pClass)
{
  return (odrxClassDictionary()->getAt(pClass->name()).isNull());
}

inline OdUInt16 getItemClassId(OdRxClass* pClass)
{
  OdProxyClassPtr pProxyClass = OdProxyClass::cast(pClass);
  if(pProxyClass.get())
    return pProxyClass->getItemClassId();
  return OdUInt16(pClass->isDerivedFrom(OdDbEntity::desc()) ? 498 : 499);
}

#endif // !defined(AFX_ODAPROXYCLASSLIST_H__034A5AC9_71CF_4EDB_B461_F16A5D9A083C__INCLUDED_)

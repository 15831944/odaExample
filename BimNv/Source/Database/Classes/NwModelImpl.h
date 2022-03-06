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

#ifndef __NWMODELIMPL_INCLUDED_
#define __NWMODELIMPL_INCLUDED_

#include "NwModel.h"
#include "Ge/GeMatrix3d.h"
#include "NwObjectImpl.h"

class OdNwModelValidData;
typedef OdSharedPtr<OdNwModelValidData> OdNwModelValidDataPtr;
class OdNwCacheXref;
typedef OdSharedPtr<OdNwCacheXref> OdNwCacheXrefPtr;

namespace NwModelChangeFlags
{
  enum Enum
  {
    original = 0,
    units_changed = 1,
    transform_changed = 2,
    unknown_changed = 4
  };
}

class OdNwModelImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwModel)
public:
  OdNwModelImpl();
  virtual ~OdNwModelImpl();
  ODRX_DECLARE_MEMBERS(OdNwModelImpl);

  static OdNwModelImpl* getImpl(const OdNwModel* pNwModel);
  static OdNwModelImpl* getImpl(const OdRxObject* pRxScene);

public:
  OdString getFileName() const;
  OdString getPath() const;
  OdString getSourceName() const;
  OdString getSourceFileName() const;
  OdGUID getSourceGuId() const;
  bool isChange() const;
  OdUInt32 getBitfields3() const;
  OdGeMatrix3d getTransform() const;
  NwModelType::Enum getType() const;
  NwModelUnits::Enum getUnits() const;
  OdUInt32 getUnknownUnits2() const;
  bool getUnitsFlag() const;
  OdGUID getGuId() const;
  OdUInt32 getUnknownEnum() const;
  OdString getUnknownString() const;
  OdGeVector3d getUpVector() const;
  OdGeVector3d getNorthVector() const;
  OdGeVector3d getFrontVector() const;
  OdResult getProperties(std::list<OdNwDataPropertyPtr>& lProperties) const;

  OdNwModelValidDataPtr getModelValidData() const;

public:
  inline OdUInt32& getChangeBitfield() { return m_changeBitfield; }

public:
  void setFileName(const OdString& name);
  void setPath(const OdString& path);
  void setSourceName(const OdString& sourceName);
  void setTransformMatrix(const OdGeMatrix3d& trMtrx);
  void setType(NwModelType::Enum type);
  void setModelUnits(NwModelUnits::Enum units);
  void setAngularUnits(OdUInt32 units);

  void setSourceGUID(const OdGUID& guid);
  void setSourceFileName(const OdString& source);
  void setBitfields1(OdUInt32 bitfields);
  void setBitfields2(OdUInt32 bitfields);
  void setBitfields3(OdUInt32 bitfields);
  void setUnitsFlag(bool flag);
  void setUpVector(const OdGeVector3d& up);
  void setNorthVector(const OdGeVector3d& north);
  void setUnknownEnum(OdUInt32 val);
  void setUnknownString(const OdString& val);

  void setFrontvector(const OdGeVector3d& front);
  void setGUID(const OdGUID& guid);

  void addCacheXref(OdNwCacheXrefPtr pCacheXref);

  void setModelValidData(OdNwModelValidDataPtr pValidData);

public:
  //VAS: implementation public methods
  void setUnits(NwModelUnits::Enum units);
  void setTransform(const OdGeMatrix3d& trMtrx);
  OdResult setSourcePath(const OdString& path);

private:
  OdString m_Name;
  OdString m_Path;
  OdString m_OldName;
  OdUInt32 m_changeBitfield;
  OdGeMatrix3d m_trMtrx;
  NwModelType::Enum m_PluginType;
  NwModelUnits::Enum m_modelUnits;
  OdUInt32 m_AngularUnits;

  OdGUID m_SourceGuId;
  OdString m_SourceFileName;
  OdUInt32 m_bitfields1;
  OdUInt32 m_bitfields2;
  OdUInt32 m_bitfields3;
  bool m_bUnitsFlag;
  OdGeVector3d m_upVector;
  OdGeVector3d m_northVector;
  OdUInt32 m_unknownEnum;
  OdString m_unknownString;
  OdArray<OdNwCacheXrefPtr> m_aCacheXref;
  OdGeVector3d m_frontVector;
  OdGUID m_GuId;
  OdNwModelValidDataPtr m_pModelValidData;
};

typedef OdSmartPtr<OdNwModelImpl> OdNwModelImplPtr;

#endif //__NWMODELIMPL_INCLUDED_

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

#ifndef ODDBDIMDATA_H
#define ODDBDIMDATA_H

#include "TD_PackPush.h"

#include "DbDimension.h"

class OdTvDbDimData;

typedef OdArray<OdTvDbDimData> OdTvDbDimDataArray;
typedef OdArray<OdTvDbDimData*, OdMemoryAllocator<OdTvDbDimData*> > OdTvDbDimDataPtrArray;
typedef OdGeVector3d (*DimDataSetValueFuncPtr) (OdTvDbDimData* pThis,
                                                OdTvDbEntity* pEnt, 
                                                double newValue,
                                                const OdGeVector3d& offset);

typedef OdGeVector3d (*DimDataSetCustomStringFuncPtr) (OdTvDbDimData* pThis,
                                                       OdTvDbEntity* pEnt, 
                                                       const OdString& sCustomString,
                                                       const OdGeVector3d& offset);
/** \details
    This class passes parameters for the getGripPoints and moveGripPoints functions of OdTvDbEntity.
    
    \sa
    TD_Db
   
    <group OdTvDb_Classes>
*/
class OdTvDbDimData
{
public:
  enum DimDataFlags
  {
    kDimEditable           = 0x0001,
    kDimInvisible          = 0x0002,
    kDimFocal              = 0x0004,
    kDimHideIfValueIsZero  = 0x0008,
    kDimEmptyData          = 0x0010,
    kDimResultantLength    = 0x0020,
    kDimDeltaLength        = 0x0040,
    kDimResultantAngle     = 0x0080,
    kDimDeltaAngle         = 0x0100,
    kDimRadius             = 0x0200,
    kDimCustomValue        = 0x0400,
    kDimConstrained        = 0x0800,
    kDimCustomString       = 0x1000
  };

  OdTvDbDimData();

  OdTvDbDimData(OdTvDbDimension* pDim, 
    DimDataSetValueFuncPtr setDimFunc = 0,
    unsigned int bitFlags = 0,
    void* appData = 0,
    DimDataSetCustomStringFuncPtr setCustomStringFunc = 0);

  ~OdTvDbDimData();

  OdTvDbDimData(const OdTvDbDimData&);
  OdTvDbDimData&  operator = (const OdTvDbDimData&);
  OdTvDbDimensionPtr dimension() const;
  void setDimension(OdTvDbDimension* pDim);
  OdTvDbObjectId ownerId() const;
  void setOwnerId(const OdTvDbObjectId& objId);
  unsigned int bitFlags() const;
  void setBitFlags(unsigned int flags);
  bool isDimFocal() const;
  void setDimFocal(bool focal);
  bool isDimEditable() const;
  void setDimEditable(bool editable);
  bool isDimInvisible() const;
  void setDimInvisible(bool invisible);
  bool isDimHideIfValueIsZero() const;
  void setDimHideIfValueIsZero(bool hide);
  void *appData() const;
  void setAppData(void* appData);
  DimDataSetValueFuncPtr dimValueFunc() const;
  void setDimValueFunc(DimDataSetValueFuncPtr funcPtr);
  DimDataSetCustomStringFuncPtr customStringFunc() const;
  void setCustomStringFunc(DimDataSetCustomStringFuncPtr funcPtr);
  bool isDimResultantLength() const;
  void setDimResultantLength(bool bValue);
  bool isDimDeltaLength() const;
  void setDimDeltaLength(bool bValue);
  bool isDimResultantAngle() const;
  void setDimResultantAngle(bool bValue);
  bool isDimDeltaAngle() const;
  void setDimDeltaAngle(bool bValue);
  bool isDimRadius() const;
  void setDimRadius(bool bValue);
  bool isCustomDimValue() const;
  void setCustomDimValue(bool custom);
  bool isConstrained() const;
  void setConstrain(bool bValue);
  bool isCustomString() const;
  void setCustomString(bool bValue);

private:
  OdTvDbDimensionPtr              m_pDim;
  OdTvDbObjectId                  m_ownerId;
  unsigned int                  m_bitFlags;
  void*                         m_pAppData;
  DimDataSetValueFuncPtr        m_pSetDimValueFunc;
  DimDataSetCustomStringFuncPtr m_pSetCustomStringFunc;
};

inline OdTvDbDimData::OdTvDbDimData()
  : m_bitFlags(0)
  , m_pAppData (0)
  , m_pSetDimValueFunc(0)
  , m_pSetCustomStringFunc(0)
{
}

inline
OdTvDbDimData::OdTvDbDimData(OdTvDbDimension* pDim, 
                         DimDataSetValueFuncPtr setValueFunc,
                         unsigned int bitFlags,
                         void* appData,
                         DimDataSetCustomStringFuncPtr setCustomStringFunc)
  : m_pDim(pDim)
  , m_bitFlags(bitFlags)
  , m_pAppData(appData)
  , m_pSetDimValueFunc(setValueFunc)
  , m_pSetCustomStringFunc(setCustomStringFunc)
{
}

inline OdTvDbDimData::~OdTvDbDimData()
{
}

inline OdTvDbDimensionPtr
OdTvDbDimData::dimension() const
{
  return m_pDim;
}

inline void
OdTvDbDimData::setDimension(OdTvDbDimension* pDim)
{
  m_pDim = pDim;
}

inline OdTvDbObjectId
OdTvDbDimData::ownerId() const
{
  return m_ownerId;
}

inline void
OdTvDbDimData::setOwnerId(const OdTvDbObjectId& objId)
{
  m_ownerId = objId;
}

inline unsigned int 
OdTvDbDimData::bitFlags() const
{
  return m_bitFlags;
}

inline void
OdTvDbDimData::setBitFlags(unsigned int flags)
{
  m_bitFlags = flags;
}

inline bool
OdTvDbDimData::isDimFocal() const
{
  return 0 != (m_bitFlags & kDimFocal);
}

inline void
OdTvDbDimData::setDimFocal(bool focal)
{
  if (focal)
    m_bitFlags |= kDimFocal;
  else
    m_bitFlags &= ~kDimFocal;
}

inline bool
OdTvDbDimData::isDimEditable() const
{
  return 0 != (m_bitFlags & kDimEditable);
}

inline void
OdTvDbDimData::setDimEditable(bool editable)
{
  if (editable)
    m_bitFlags |= kDimEditable;
  else
    m_bitFlags &= ~kDimEditable;
}

inline bool
OdTvDbDimData::isDimInvisible() const
{
  return 0 != (m_bitFlags & kDimInvisible);
}

inline void
OdTvDbDimData::setDimInvisible(bool invisible)
{
  if (invisible)
    m_bitFlags |= kDimInvisible;
  else
    m_bitFlags &= ~kDimInvisible;
}

inline bool
OdTvDbDimData::isDimHideIfValueIsZero() const
{
  return 0 != (m_bitFlags & kDimHideIfValueIsZero);
}

inline void
OdTvDbDimData::setDimHideIfValueIsZero(bool hide)
{
  if (hide)
    m_bitFlags |= kDimHideIfValueIsZero;
  else
    m_bitFlags &= ~kDimHideIfValueIsZero;
}

inline bool
OdTvDbDimData::isDimResultantLength() const
{
  return 0 != (m_bitFlags & kDimResultantLength);
}

inline void
OdTvDbDimData::setDimResultantLength(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimResultantLength;
  else
    m_bitFlags &= ~kDimResultantLength;
}

inline bool
OdTvDbDimData::isDimDeltaLength() const
{
  return 0 != (m_bitFlags & kDimDeltaLength);
}

inline void
OdTvDbDimData::setDimDeltaLength(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimDeltaLength;
  else
    m_bitFlags &= ~kDimDeltaLength;
}

inline bool
OdTvDbDimData::isDimResultantAngle() const
{
  return 0 != (m_bitFlags & kDimResultantAngle);
}

inline void
OdTvDbDimData::setDimResultantAngle(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimResultantAngle;
  else
    m_bitFlags &= ~kDimResultantAngle;
}

inline bool
OdTvDbDimData::isDimDeltaAngle() const
{
  return 0 != (m_bitFlags & kDimDeltaAngle);
}

inline void
OdTvDbDimData::setDimDeltaAngle(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimDeltaAngle;
  else
    m_bitFlags &= ~kDimDeltaAngle;
}

inline bool
OdTvDbDimData::isDimRadius() const
{
    return 0 != (m_bitFlags & kDimRadius);
}

inline void
OdTvDbDimData::setDimRadius(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimRadius;
  else
    m_bitFlags &= ~kDimRadius;
}

inline bool
OdTvDbDimData::isCustomDimValue() const
{
  return 0 != (m_bitFlags & kDimCustomValue);
}

inline void
OdTvDbDimData::setCustomDimValue(bool custom)
{
  if (custom)
    m_bitFlags |= kDimCustomValue;
  else
    m_bitFlags &= ~kDimCustomValue;
}

inline bool
OdTvDbDimData::isConstrained() const
{
  return 0 != (m_bitFlags & kDimConstrained);
}

inline void
OdTvDbDimData::setConstrain(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimConstrained;
  else
    m_bitFlags &= ~kDimConstrained;
}

inline bool
OdTvDbDimData::isCustomString() const
{
  return 0 != (m_bitFlags & kDimCustomString);
}

inline void
OdTvDbDimData::setCustomString(bool bValue)
{
  if (bValue)
    m_bitFlags |= kDimCustomString;
  else
    m_bitFlags &= ~kDimCustomString;
}

inline void*
OdTvDbDimData::appData() const
{
  return m_pAppData;
}

inline void
OdTvDbDimData::setAppData(void* appData)
{
  m_pAppData = appData;
}

inline DimDataSetValueFuncPtr
OdTvDbDimData::dimValueFunc() const
{
  return m_pSetDimValueFunc;
}

inline void
OdTvDbDimData::setDimValueFunc(DimDataSetValueFuncPtr funcPtr)
{
  m_pSetDimValueFunc = funcPtr;
}

inline DimDataSetCustomStringFuncPtr
OdTvDbDimData::customStringFunc() const
{
  return m_pSetCustomStringFunc;
}

inline void
OdTvDbDimData::setCustomStringFunc(DimDataSetCustomStringFuncPtr funcPtr)
{
  m_pSetCustomStringFunc = funcPtr;
}

inline OdTvDbDimData& OdTvDbDimData::operator = (const OdTvDbDimData& src)
{
  if (this == &src)
    return *this;
  
  m_pDim = src.dimension()->clone();
  m_ownerId = src.ownerId();
  m_pSetDimValueFunc = src.dimValueFunc();
  m_pSetCustomStringFunc = src.customStringFunc();
  m_bitFlags = src.bitFlags();
  m_pAppData = src.appData();
  return *this;
}

inline OdTvDbDimData::OdTvDbDimData(const OdTvDbDimData& src)
{
  *this = src;
}

#include "TD_PackPop.h"

#endif // ODDBDIMDATA_H

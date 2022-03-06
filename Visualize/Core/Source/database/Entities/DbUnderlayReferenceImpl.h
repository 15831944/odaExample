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


#ifndef __OD_DB_UNDERLAY_REFERENCE_IMPL__
#define __OD_DB_UNDERLAY_REFERENCE_IMPL__

#include "DbUnderlayReference.h"
#include "DbEntityImpl.h"

class OdTvDbUnderlayReferenceImpl : public OdTvDbEntityImpl
{
  OdGeVector3d      m_normal;
  OdGePoint3d       m_position; // in OCS!! (in DWG file it is stored in OCS)
  double            m_rotation;
  OdGeScale3d       m_scale;
  OdTvDbHardPointerId m_defId;
  OdUInt8           m_flags;
  OdGePoint2dArray  m_clip;
  mutable OdGePoint2dArray  m_invertedClip;

  enum Flags
  {
    kIsClipped    = 0x1, // show clipped, use clipping in rendering
    kIsOn         = 0x2,
    kIsMonochrome = 0x4,
    kAdjustForBg  = 0x8,
    kClipInverted = 0x10,

    kDefault = kAdjustForBg | kIsOn | kIsClipped
  };

  const OdGePoint2dArray& invertedClip() const;

  static OdTvDbUnderlayReferenceImpl* getImpl(const OdTvDbUnderlayReference *pObj)
  { return (OdTvDbUnderlayReferenceImpl*)OdTvDbSystemInternals::getImpl(pObj);}

protected:
  OdUInt8 m_contrast, m_fade;

public:
  OdTvDbUnderlayReferenceImpl();

  friend class OdTvDbUnderlayReference;

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  OdResult dxfInFields(OdTvDbDxfFiler* pFiler);  
  void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual bool isRegenTypeSupported(OdGiRegenType regenType) const;
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);
};

class OdTvDbDwfReferenceImpl : public OdTvDbUnderlayReferenceImpl
{
};

class OdTvDbDgnReferenceImpl : public OdTvDbUnderlayReferenceImpl
{
public:
  virtual bool isRegenTypeSupported(OdGiRegenType /*regenType*/) const
  {
    return true;
  }
};

class OdTvDbPdfReferenceImpl : public OdTvDbUnderlayReferenceImpl
{
  OdUInt32 setAttributes(OdGiDrawableTraits* pTraits) const;
public:
  OdTvDbPdfReferenceImpl();

  virtual bool isRegenTypeSupported(OdGiRegenType /*regenType*/) const;
};


class OdTvDbNavisworksReferenceImpl : public OdTvDbEntityImpl
{
  OdUInt16 m_ver;
  OdTvDbHardPointerId m_defId;
  OdGeMatrix3d m_mat;
  double m_InsertionUnitScaleFactor;

  static OdTvDbNavisworksReferenceImpl* getImpl( const OdTvDbNavisworksReference *pObj )
  {
    return (OdTvDbNavisworksReferenceImpl*)OdTvDbSystemInternals::getImpl( pObj );
  }

public:
  OdTvDbNavisworksReferenceImpl();

  friend class OdTvDbNavisworksReference;

  OdResult dwgInFields( OdTvDbDwgFiler* pFiler );
  void dwgOutFields( OdTvDbDwgFiler* pFiler ) const;

  OdResult dxfInFields( OdTvDbDxfFiler* pFiler );
  void dxfOutFields( OdTvDbDxfFiler* pFiler ) const;

};
#endif // __OD_DB_UNDERLAY_REFERENCE_IMPL__

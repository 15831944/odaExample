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

class OdDbUnderlayReferenceImpl : public OdDbEntityImpl
{
  OdGeVector3d      m_normal;
  OdGePoint3d       m_position; // in OCS!! (in DWG file it is stored in OCS)
  double            m_rotation;
  OdGeScale3d       m_scale;
  OdDbHardPointerId m_defId;
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

  static OdDbUnderlayReferenceImpl* getImpl(const OdDbUnderlayReference *pObj)
  { return (OdDbUnderlayReferenceImpl*)OdDbSystemInternals::getImpl(pObj);}

protected:
  OdUInt8 m_contrast, m_fade;

public:
  OdDbUnderlayReferenceImpl();

  friend class OdDbUnderlayReference;

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  OdResult dxfInFields(OdDbDxfFiler* pFiler);  
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  virtual bool isRegenTypeSupported(OdGiRegenType regenType) const;
  virtual void audit(OdDbAuditInfo* pAuditInfo);
};

class OdDbDwfReferenceImpl : public OdDbUnderlayReferenceImpl
{
};

class OdDbDgnReferenceImpl : public OdDbUnderlayReferenceImpl
{
public:
  virtual bool isRegenTypeSupported(OdGiRegenType /*regenType*/) const
  {
    return true;
  }
};

class OdDbPdfReferenceImpl : public OdDbUnderlayReferenceImpl
{
  OdUInt32 setAttributes(OdGiDrawableTraits* pTraits) const;
public:
  OdDbPdfReferenceImpl();

  virtual bool isRegenTypeSupported(OdGiRegenType /*regenType*/) const;
};


class OdDbNavisworksReferenceImpl : public OdDbEntityImpl
{
  OdUInt16 m_ver;
  OdDbHardPointerId m_defId;
  OdGeMatrix3d m_mat;
  double m_InsertionUnitScaleFactor;

  static OdDbNavisworksReferenceImpl* getImpl( const OdDbNavisworksReference *pObj )
  {
    return (OdDbNavisworksReferenceImpl*)OdDbSystemInternals::getImpl( pObj );
  }

public:
  OdDbNavisworksReferenceImpl();

  friend class OdDbNavisworksReference;

  OdResult dwgInFields( OdDbDwgFiler* pFiler );
  void dwgOutFields( OdDbDwgFiler* pFiler ) const;

  OdResult dxfInFields( OdDbDxfFiler* pFiler );
  void dxfOutFields( OdDbDxfFiler* pFiler ) const;

};
#endif // __OD_DB_UNDERLAY_REFERENCE_IMPL__

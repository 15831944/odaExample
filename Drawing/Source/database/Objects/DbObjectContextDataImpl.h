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

#ifndef _ODDBOJECTCONTEXTDATAIMPL_H_INCLUDED_
#define _ODDBOJECTCONTEXTDATAIMPL_H_INCLUDED_

#include "DbObjectContextData.h"
#include "DbMTextImpl.h"
#include "DbBlockReferenceImpl.h"
#include "UInt32Array.h"
#include "DbHatchImpl.h"
#include "DbDimensionImpl.h"
#include "DbAlignedDimensionImpl.h"
#include "Db2LineAngularDimensionImpl.h"
#include "DbDiametricDimensionImpl.h"
#include "DbOrdinateDimensionImpl.h"
#include "DbRadialDimensionImpl.h"
#include "DbRadialDimensionLargeImpl.h"
#include "DbFcfImpl.h"
#include "DbBlockTableRecord.h"

class OdDbMLeaderImpl;

class TOOLKIT_EXPORT OdDbObjectContextDataImpl : public OdDbObjectImpl
{
public:
  OdDbObjectContextDataImpl() : m_nVersion(3), m_bFileToExtensionDictionary(true), m_bModified(false), m_bDefault(false){}
  mutable OdInt16 m_nVersion;
  bool m_bFileToExtensionDictionary; 
  bool m_bModified;
  bool m_bDefault;
  OdDbObjectContextPtr m_pContext;
  static OdDbObjectContextDataImpl* getImpl(const OdDbObjectContextData* pObj)
  { return (OdDbObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdInt16 getOutVersion(OdDbFiler*);
};

class TOOLKIT_EXPORT OdDbAnnotScaleObjectContextDataImpl : public OdDbObjectContextDataImpl
{
public:
  OdDbHardPointerId m_pScale;
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  static OdDbAnnotScaleObjectContextDataImpl* getImpl(const OdDbAnnotScaleObjectContextData* pObj)
  { return (OdDbAnnotScaleObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdDbMTextObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbMTextObjectContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  OdMTextRendererData m_RenderData;
  OdColumnsData m_ColumnsData;
  static OdDbMTextObjectContextDataImpl* getImpl(const OdDbMTextObjectContextData* pObj)
  { return (OdDbMTextObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdDbTextObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbTextObjectContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  static OdDbTextObjectContextDataImpl* getImpl(const OdDbTextObjectContextData* pObj)
  { return (OdDbTextObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbTextObjectContextDataImpl()
    : m_HorizontalMode(0)
    , m_dAngle(0)
  {
  }

  OdUInt16 m_HorizontalMode;
  double m_dAngle;
  OdGePoint2d m_Alignment;
  OdGePoint2d m_Position;

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdDbMTextAttributeObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbMTextAttributeObjectContextDataImpl : public OdDbTextObjectContextDataImpl
{
public:
  static OdDbMTextAttributeObjectContextDataImpl* getImpl(const OdDbMTextAttributeObjectContextData* pObj)
  { return (OdDbMTextAttributeObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbMTextAttributeObjectContextDataImpl()
  {
  }

  OdDbMTextObjectContextDataPtr m_mTextCD;
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
};


//////////////////////////////////////////////////////////////////////////
// OdDbBlkRefObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbBlkRefObjectContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  static OdDbBlkRefObjectContextDataImpl* getImpl(const OdDbBlkRefObjectContextData* pObj)
  { return (OdDbBlkRefObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbBlkRefObjectContextDataImpl()
    : m_dRotation(0.)
  { }

  OdGePoint3d m_positionInEcs;
  double      m_dRotation;
  OdGeScale3d m_ScaleFactors;
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
// OdDbHatchScaleContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbHatchScaleContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  static OdDbHatchScaleContextDataImpl* getImpl(const OdDbHatchScaleContextData* pObj)
  { return (OdDbHatchScaleContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbHatchScaleContextDataImpl()
    : m_dPatternScale(1.)
    , m_bIsCacheValid(false)
    , m_vPatternBaseAngle(OdGeVector3d::kXAxis)
  {
  }

  virtual ~OdDbHatchScaleContextDataImpl()
  {
    clearBoundary();
  }

  OdHatchPattern m_HatchDefLineList;
  double         m_dPatternScale;
  OdGeVector3d   m_vPatternBaseAngle;

  OdDbHatchImpl::LoopList m_LoopsList;

  OdGePoint2dArray m_startPts;
  OdGePoint2dArray m_endPts;
  bool m_bIsCacheValid;

  void clearBoundary();
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
};


//////////////////////////////////////////////////////////////////////////
//  OdDbHatchViewContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbHatchViewContextDataImpl: public OdDbHatchScaleContextDataImpl 
{
public:
  static OdDbHatchViewContextDataImpl* getImpl(const OdDbHatchViewContextData* pObj)
  { return (OdDbHatchViewContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbHatchViewContextDataImpl()
    : m_dAngle(0.)
    , m_bBool(false)
  {
  }

  OdDbSoftPointerId m_VPid;
  OdGeVector3d      m_vTarget;
  double            m_dAngle;
  bool              m_bBool;

  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version) ODRX_OVERRIDE;
  virtual OdResult dwgInContextData(OdDbDwgFiler*) ODRX_OVERRIDE;
  virtual void dwgOutContextData(OdDbDwgFiler*) const ODRX_OVERRIDE;
};


//////////////////////////////////////////////////////////////////////////
// OdDbDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbDimensionObjectContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  static OdDbDimensionObjectContextDataImpl* getImpl(const OdDbDimensionObjectContextData* pObj)
  { return (OdDbDimensionObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbDimensionObjectContextDataImpl()
    : m_Bool1(false)
    , m_bDefTextLocation(false)
    , m_bDimsoxd(false)
    , m_bDimtofl(false)
    , m_bDimtix(false)
    , m_Bool6(false)
    , m_bFlipSecondArrow(false)
    , m_bFlipFirstArrow(false)
    , m_dTextRotation(0.)
    , m_Dimatfit(0)
    , m_Dimtmove(0)
    , m_nFlags(0)
  {
  }
  OdDbBlockTableRecordPtr m_pNDBRDimBlock;
  OdDbHardPointerId       m_BlockRecordId;
  bool        m_Bool1
            , m_bDefTextLocation
            , m_bDimsoxd
            , m_bDimtofl
            , m_bDimtix
            , m_Bool6
            , m_bFlipSecondArrow
            , m_bFlipFirstArrow;
  OdGePoint2d m_TextLocation;
  double      m_dTextRotation;
  OdInt16     m_Dimatfit;
  OdInt16     m_Dimtmove;
  // 1 - m_bDimtofl 1-off
  // 2 - dimsoxd 1-off 
  // 4 - Dimatfit 1-used
  // 8 - Dimtex 1-used
  // 16 - Dimtmove 1-used
  OdUInt8     m_nFlags; 

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDbAlignedDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbAlignedDimensionObjectContextDataImpl : public OdDbDimensionObjectContextDataImpl
{
public:
  static OdDbAlignedDimensionObjectContextDataImpl* getImpl(const OdDbAlignedDimensionObjectContextData* pObj)
  { return (OdDbAlignedDimensionObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbAlignedDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_Point;
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDb2LineAngularDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbAngularDimensionObjectContextDataImpl : public OdDbDimensionObjectContextDataImpl
{
public:
  static OdDbAngularDimensionObjectContextDataImpl* getImpl(const OdDbAngularDimensionObjectContextData* pObj)
  { return (OdDbAngularDimensionObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbAngularDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_Point;
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDbDiametricDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbDiametricDimensionObjectContextDataImpl : public OdDbDimensionObjectContextDataImpl
{
public:
  static OdDbDiametricDimensionObjectContextDataImpl* getImpl(const OdDbDiametricDimensionObjectContextData* pObj)
  { return (OdDbDiametricDimensionObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbDiametricDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_chordPoint, m_farChordPoint;

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDbOrdinateDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbOrdinateDimensionObjectContextDataImpl : public OdDbDimensionObjectContextDataImpl
{
public:
  static OdDbOrdinateDimensionObjectContextDataImpl* getImpl(const OdDbOrdinateDimensionObjectContextData* pObj)
  { return (OdDbOrdinateDimensionObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbOrdinateDimensionObjectContextDataImpl()
  {

  }

  OdGePoint3d m_Origin, m_LeaderEndPoint;
  
  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDbRadialDimensionObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbRadialDimensionObjectContextDataImpl : public OdDbDimensionObjectContextDataImpl
{
public:
  static OdDbRadialDimensionObjectContextDataImpl* getImpl(const OdDbRadialDimensionObjectContextData* pObj)
  { return (OdDbRadialDimensionObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbRadialDimensionObjectContextDataImpl()
  {

  }
  OdGePoint3d m_chordPoint;

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDbRadialDimensionLargeObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbRadialDimensionLargeObjectContextDataImpl: public OdDbRadialDimensionObjectContextDataImpl 
{
public:
  static OdDbRadialDimensionLargeObjectContextDataImpl* getImpl(const OdDbRadialDimensionLargeObjectContextData* pObj)
  { return (OdDbRadialDimensionLargeObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbRadialDimensionLargeObjectContextDataImpl()
  {

  }
  OdGePoint3d m_OverrideCenter, m_JogPoint;

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  virtual void transformBy(const OdGeMatrix3d &mx);
};


//////////////////////////////////////////////////////////////////////////
// OdDbFcfObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbFcfObjectContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  static OdDbFcfObjectContextDataImpl* getImpl(const OdDbFcfObjectContextData* pObj)
  { return (OdDbFcfObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdGePoint3d m_Point;
  OdGeVector3d m_XDir;

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
};

//////////////////////////////////////////////////////////////////////////
// OdDbLeaderObjectContextDataImpl
//////////////////////////////////////////////////////////////////////////

class OdDbLeaderObjectContextDataImpl : public OdDbAnnotScaleObjectContextDataImpl
{
public:
  static OdDbLeaderObjectContextDataImpl* getImpl(const OdDbLeaderObjectContextData* pObj)
  { return (OdDbLeaderObjectContextDataImpl*)OdDbSystemInternals::getImpl(pObj); }

  OdDbLeaderObjectContextDataImpl() : m_HooklineOnXDir(false)
  {
  }

  OdGePoint3dArray  m_Points;
  OdGeVector3d      m_TextOffset;
  OdGeVector3d      m_OffsetToBlkInsPt;
  OdGeVector3d      m_vXDir;
  bool              m_HooklineOnXDir;   // Hook line direction flag

  virtual OdResult dwgInContextData(OdDbDwgFiler*);
  virtual void dwgOutContextData(OdDbDwgFiler*) const;
  friend class OdDbLeader;
};

#endif  // _ODDBOJECTCONTEXTDATAIMPL_H_INCLUDED_

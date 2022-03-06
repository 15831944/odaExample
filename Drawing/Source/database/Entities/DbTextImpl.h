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

#ifndef _ODDBTEXTIMPL_INCLUDED_
#define _ODDBTEXTIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbText.h"
#include "TextStyleRef.h"
#include "DbObjectContextData.h"
#include "DbObjectContextDataManager.h"

class OdDbAttribute;

class OdDbTextImpl : public TextStyleRef<OdDbEntityImpl>,
                     public OdDb2dEntityImpl
{
  static OdDbTextImpl* getImpl(const OdDbText *pObj)
  { return (OdDbTextImpl*)OdDbSystemInternals::getImpl(pObj);}

protected:
  double            m_d_Elevation;
public:
  double            m_dHeight;
  double            m_dAngle;           // << Annot Scale dependent
  double            m_dWidthFactor;
  double            m_dOblique;
  OdGePoint2d       m_position;         // << Annot Scale dependent
  OdGePoint2d       m_alignmentPoint;   // << Annot Scale dependent
public:
  OdString          m_strText;
protected:
  OdUInt32          m_cntStyleChanges;
  OdUInt8           m_GenFlags;
public:
  OdUInt8           m_HorizontalMode;   // << Annot Scale dependent
  OdUInt8           m_VerticalMode;

  enum
  {
    kMirroredInX     = 0x02,
    kMirroredInY     = 0x04,
    kGenerationMask  = 0x06,
    kAlignPtNotValid = 0x80
  };

public:
  virtual const OdString& getString() const { return m_strText; } // It is rewrite in OdDbAttributeDefinitionImpl for internal purpose 
  virtual OdString getTextString() const { return m_strText; }   // It is rewrite in OdDbAttributeImpl for use in public interface textString()
  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

  OdGePoint3d ocsPosition() const
  {
//    OdGePoint3d ocsPosition (m_position);
//    if (m_vNormal != OdGeVector3d::kZAxis)
//      ocsPosition.transformBy(OdGeMatrix3d::worldToPlane(m_vNormal));
//    return ocsPosition;
    return OdGePoint3d(m_position.x, m_position.y, m_d_Elevation);
  }

  OdGePoint3d ocsAlignmentPoint() const
  {
//    if(horizontalMode()==OdDb::kTextLeft && verticalMode()==OdDb::kTextBase)
//      return OdGePoint3d(0., 0., m_dElevation);
//    OdGePoint3d ocsAlignPt (m_AlignmentPoint.x, m_AlignmentPoint.y, m_dElevation);
//    if (m_vNormal != OdGeVector3d::kZAxis)
//      ocsAlignPt.transformBy(OdGeMatrix3d::worldToPlane(m_vNormal));
//    return ocsAlignPt;
    return OdGePoint3d(m_alignmentPoint.x, m_alignmentPoint.y, m_d_Elevation);
  }

  void setOcsPosition(const OdGePoint3d& ocsPos)
  {
//    OdGePoint3d pos = ocsPos;
//    if (m_vNormal != OdGeVector3d::kZAxis)
//      pos.transformBy(OdGeMatrix3d::planeToWorld(m_vNormal));
//    m_Position = (const OdGePoint2d&)pos; m_dElevation = pos.z;
    m_position.set(ocsPos.x, ocsPos.y);
    m_d_Elevation = ocsPos.z;
  }

  void setOcsAlignmentPoint(const OdGePoint3d& ocsPos)
  {
//    OdGePoint3d pos = pt;
//    if ( OdNonZero(pt.x) || OdNonZero(pt.y) &&
//      (m_vNormal != OdGeVector3d::kZAxis) )
//    {
//      pos.transformBy(OdGeMatrix3d::planeToWorld(m_vNormal));
//    }
//    m_AlignmentPoint = (const OdGePoint2d&)pt;
    m_alignmentPoint.set(ocsPos.x, ocsPos.y);
    m_d_Elevation = ocsPos.z;
  }
  OdGePoint3d position(OdDbTextObjectContextDataPtr ctx) const
  {
    OdGePoint2d ecsPos = (ctx.isNull() || ctx->isDefaultContextData()) ? m_position : ctx->positionInEcs();
    OdGePoint3d pos(ecsPos.x, ecsPos.y, m_d_Elevation );
    if (normal() != OdGeVector3d::kZAxis)
    {
      pos.transformBy(OdGeMatrix3d::planeToWorld(normal()));
    }
    return pos;
  }
  virtual void setPosition(OdGePoint3d point, OdDbTextObjectContextDataPtr ctx, bool bAdjust = false)
  {
    if (normal() != OdGeVector3d::kZAxis)
    {
      point.transformBy(OdGeMatrix3d::worldToPlane(normal()));
    }
    if (!ctx.isNull())
    {
      ctx->setPositionInEcs(OdGePoint2d(point.x, point.y));
      if (ctx->isDefaultContextData())
        m_position.set(point.x, point.y);
    }
    else
      m_position.set(point.x, point.y);
    m_d_Elevation = point.z;
  }

  OdGePoint3d alignmentPoint(OdDbTextObjectContextDataPtr ctx) const
  {
    OdGePoint3d pos = (ctx.isNull() || ctx->isDefaultContextData()) ?  OdGePoint3d(m_alignmentPoint.x, m_alignmentPoint.y, m_d_Elevation) 
      : OdGePoint3d(ctx->alignmentPointInEcs().x, ctx->alignmentPointInEcs().y, m_d_Elevation);
    if (normal() != OdGeVector3d::kZAxis)
    {
      pos.transformBy(OdGeMatrix3d::planeToWorld(normal()));
    }
    return pos;
  }

  void setAlignmentPoint(OdGePoint3d point, OdDbTextObjectContextDataPtr ctx)
  {
    if (normal() != OdGeVector3d::kZAxis)
    {
      point.transformBy(OdGeMatrix3d::worldToPlane(normal()));
    }
    if (!ctx.isNull())
    {
      ctx->setAlignmentPointInEcs(OdGePoint2d(point.x, point.y));
      if (ctx->isDefaultContextData())
        m_alignmentPoint.set(point.x, point.y);
    }
    else
      m_alignmentPoint.set(point.x, point.y);
    m_d_Elevation = point.z;
  }

  //bool needAdjustment() const { return GETBIT(m_GenFlags, kAlignPtNotValid); }
  //void setNeedAdjustment(bool val) { SETBIT(m_GenFlags, kAlignPtNotValid, val); }

  OdDb::TextHorzMode horizontalMode() const { return OdDb::TextHorzMode(m_HorizontalMode); }
  OdDb::TextVertMode verticalMode() const { return OdDb::TextVertMode(m_VerticalMode); }
  bool isDefaultAlignment() const
  {
    return ((horizontalMode() == OdDb::kTextLeft && verticalMode() == OdDb::kTextBase)
          || horizontalMode() == OdDb::kTextMid);
  }


  void setGenerationFlags(OdUInt16 flags)
  {
    m_GenFlags &= ~kGenerationMask;
    m_GenFlags |= OdUInt8(flags & kGenerationMask);
  }
  OdUInt16 getGenerationFlags() const { return OdUInt16(kGenerationMask & m_GenFlags); }

  bool isMirroredInX() const { return GETBIT(m_GenFlags, kMirroredInX); }
  void mirrorInX(bool mirror) { SETBIT(m_GenFlags, kMirroredInX, mirror); }

  bool isMirroredInY() const { return GETBIT(m_GenFlags, kMirroredInY); }
  void mirrorInY(bool mirror) { SETBIT(m_GenFlags, kMirroredInY, mirror); }

  OdDbTextImpl();

  void audit(OdDbAuditInfo* pAuditInfo);

  void draw(OdGiGeometry& geom, OdGiCommonDraw* pWd, const OdString& pStr, const OdString& fieldStr = OdString::kEmpty, bool bAnnotative = false, const OdDbText* pText = 0) const;
  void draw1(OdGiGeometry& geom, OdGiCommonDraw* pWd, bool bAnnotative, const OdDbText* pText)const;
  void processFieldDraw(OdGiGeometry& geom, OdGiCommonDraw* pWd, const OdString& pStr, OdGiTextStyle* tp, OdGeVector3d xUnit, OdGePoint3d pos) const;

  virtual void setTextString(const OdString& textString, OdDbText* pThis);

  virtual OdResult transformBy(const OdGeMatrix3d& xform, bool bMirrText, bool b2copy = false, bool bForExplode = false); // transforms by any matrix
#ifndef OD_USING_BUGWARE // To prevent bug in HP compiler with using-statement
  TD_USING(OdDb2dEntityImpl::transformBy);
#endif

  void getBoundingPoints(const OdDbText* pObject, OdGePoint3dArray& array) const;
  void getRawExts(double scale, OdGePoint3d& min, OdGePoint3d& max, double& actHeight, double& actWidth, double& offsetY) const;

  OdAnsiString getAnsiText() const;
  
  virtual void copyFromContextData(OdDbObject* pObj, OdDbObjectContextData*, OdDbObjectContextData*);

  void copyFromAttribute(OdDbAttribute* pAttr);

  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void setRotation(double angle)
  {
    m_dAngle = angle;
    if ( angle > 1.e+16 ) // setRotation ARX  behavior
       m_dAngle = 0.0;
  }
  virtual bool bIsMLineAttribute() { return false; }
  void checkStyleModified(OdDbObject *pObj);

protected:
  void dxfOutTextFieldsData(OdDbDxfFiler* pFiler, const OdDbText* pText);
  virtual void transformAnnotations(OdDbText* pThis, const OdGeMatrix3d& xform, bool mirrText, bool copy);

  friend class OdDbText;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
  friend class OdDbObjectContextTextPE;
  friend class OdDbBlockReference; // for OdDbBlockReference::explodeGeometry
};

#endif // _ODDBTEXTIMPL_INCLUDED_

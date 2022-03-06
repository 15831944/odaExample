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

#ifndef _ODDBATTRIBIMPL_INCLUDED_
#define _ODDBATTRIBIMPL_INCLUDED_

#include "DbTextImpl.h"
#include "Ge/GePoint3d.h"
#include "DbSystemInternals.h"
#include "DbAttribute.h"
#include "DbMTextImpl.h"

class OdTvDbAttributeImpl : public OdTvDbTextImpl
{
  static OdTvDbAttributeImpl* getImpl(const OdTvDbAttribute *pObj)
  { return (OdTvDbAttributeImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  enum AttributeType {
    kSingleLine              = 1,
    kMultiLineAttribute      = 2,
    kMultiLineAttrDefinition = 4
  };

  OdGePoint3d  m_pointFirstMTextFragment;
  OdString m_strTag;
  OdTvDbMTextPtr m_pMText;

  OdInt16  m_FieldLength;
  OdUInt8 m_version;
  OdTvDbObjectId      m_idRegAppTableRec;

  bool m_bValidPoint;

  OdUInt8  m_bAttInvisible : 1;
  OdUInt8  m_bConstant     : 1;
  OdUInt8  m_bVerify       : 1;
  OdUInt8  m_bPreset       : 1;
  OdUInt8  m_bLock         : 1;

public:
  OdTvDbAttributeImpl();

  virtual OdUInt8 assembleFlags() const;
  virtual void disassembleFlags(OdUInt8 f);

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void convertIntoMText(bool val, OdTvDbTextObjectContextDataPtr ctx, OdTvDbObject *pObj);
  void updateMTextAttribute(OdTvDbTextObjectContextDataPtr ctx, OdTvDbObject *pObj);
  virtual void copyFromContextData(OdTvDbObject* pObj, OdTvDbObjectContextData*, OdTvDbObjectContextData*);
  virtual OdResult transformBy(const OdGeMatrix3d& xform, bool bMirrText, bool b2Copy = false, bool bForExplode = false) ODRX_OVERRIDE; // transforms by any matrix
  virtual void setPosition(OdGePoint3d point, OdTvDbTextObjectContextDataPtr ctx, bool bAdjust = false)
  {
    OdTvDbTextImpl::setPosition(point, ctx, bAdjust);
//     OdGeVector3d ydir = OdGeVector3d::kYAxis;
//     ydir.rotateBy(m_dAngle, OdGeVector3d::kZAxis);
//     ydir.transformBy(OdGeMatrix3d::planeToWorld(normal()));
    if (!ctx.isNull())
    {
      OdTvDbMTextAttributeObjectContextDataPtr data(ctx);
      OdTvDbMTextObjectContextDataPtr mctx = data->getMTextObjectContextData();
      if (!mctx.isNull())
      {
        mctx->setLocation(alignmentPoint(ctx));
      }
    }
    if ( !bAdjust && !m_pMText.isNull() && (ctx.isNull() || ctx->isDefaultContextData()))
    {
      ((OdTvDbMTextImpl*)OdTvDbSystemInternals::getImpl(m_pMText))->clearCache();
      ((OdTvDbMTextImpl*)OdTvDbSystemInternals::getImpl(m_pMText))->m_Location = alignmentPoint(ctx);
    }
  }
  void setTextString(const OdString& textString, OdTvDbText* pThis);
  virtual OdString getTextString() const;

  virtual bool bIsMLineAttribute() const
  { 
    return !m_pMText.isNull(); 
  }

  virtual OdUInt8 getTypeAtrribute() const
  {
    if (bIsMLineAttribute())
      return OdTvDbAttributeImpl::kMultiLineAttribute;
    else
      return OdTvDbAttributeImpl::kSingleLine;
  }

protected:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
protected:
  struct MTextEnumParams
  {
    MTextEnumParams(const OdString& tag, OdTvDbObject* o, bool createAttr = true) : m_strTag(tag), m_bPreviousValid(false),m_pObject(o), 
    m_bCreateAttribute(createAttr), m_bAppend(true), m_bFirst(true), m_bTrueType(false)
    {
      if ( createAttr )
        appendAttribute(o);
    }
    void appendAttribute(OdTvDbObjectPtr obj);
    void appendFragment(OdString& s, OdTvDbMTextFragment* f, bool bAppend = true );
    OdArray<OdTvDbObjectPtr> m_Attributes;
    OdStringArray          m_arrTextAttributes;
    bool m_bAppend;
    OdString m_strTag;
    OdTvDbMTextFragment m_pPrevious;
    bool m_bPreviousValid;
    bool m_bCreateAttribute;
    bool m_bFirst;
    bool m_bTrueType;
    OdTvDbObject* m_pObject;
    OdGePoint3d m_firstPoint;
  };
  static int MTextEnum( OdTvDbMTextFragment* f, void * param);
  void decomposeFields(OdTvDbObject *pObj, MTextEnumParams& mp);
  bool m_bEffectivelyAnnotative;
  void setEffectivelyAnnotative(bool v){m_bEffectivelyAnnotative = v;}
  void propagateContextDataToMText();
  void subClose();
  virtual bool isAnnotativeForRendering() const ODRX_OVERRIDE;
  virtual void restoreAnnotativeLayer(OdTvDbObject* pObj, bool addFullContext) ODRX_OVERRIDE;

  friend class OdTvDbAttribute;
  friend class OdTvDbBlockReference;
  friend class OdTvDbBlockReferenceImpl;
  friend void decomposeAnnotativeAttributes(OdTvDbObject* blkRef, OdTvDbObjectContextData* data);
};

#endif // _ODDBATTRIBIMPL_INCLUDED_

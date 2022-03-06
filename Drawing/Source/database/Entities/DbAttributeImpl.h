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

class OdDbAttributeImpl : public OdDbTextImpl
{
  static OdDbAttributeImpl* getImpl(const OdDbAttribute *pObj)
  { return (OdDbAttributeImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  enum AttributeType {
    kSingleLine              = 1,
    kMultiLineAttribute      = 2,
    kMultiLineAttrDefinition = 4
  };

  OdGePoint3d  m_pointFirstMTextFragment;
  OdString m_strTag;
  OdDbMTextPtr m_pMText;

  OdInt16  m_FieldLength;
  OdUInt8 m_version;
  OdDbObjectId      m_idRegAppTableRec;

  bool m_bValidPoint;

  OdUInt8  m_bAttInvisible : 1;
  OdUInt8  m_bConstant     : 1;
  OdUInt8  m_bVerify       : 1;
  OdUInt8  m_bPreset       : 1;
  OdUInt8  m_bLock         : 1;

public:
  OdDbAttributeImpl();

  virtual OdUInt8 assembleFlags() const;
  virtual void disassembleFlags(OdUInt8 f);

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void convertIntoMText(bool val, OdDbTextObjectContextDataPtr ctx, OdDbObject *pObj);
  void updateMTextAttribute(OdDbTextObjectContextDataPtr ctx, OdDbObject *pObj);
  virtual void copyFromContextData(OdDbObject* pObj, OdDbObjectContextData*, OdDbObjectContextData*);
  virtual OdResult transformBy(const OdGeMatrix3d& xform, bool bMirrText, bool b2Copy = false, bool bForExplode = false) ODRX_OVERRIDE; // transforms by any matrix
  virtual void setPosition(OdGePoint3d point, OdDbTextObjectContextDataPtr ctx, bool bAdjust = false)
  {
    OdDbTextImpl::setPosition(point, ctx, bAdjust);
//     OdGeVector3d ydir = OdGeVector3d::kYAxis;
//     ydir.rotateBy(m_dAngle, OdGeVector3d::kZAxis);
//     ydir.transformBy(OdGeMatrix3d::planeToWorld(normal()));
    if (!ctx.isNull())
    {
      OdDbMTextAttributeObjectContextDataPtr data(ctx);
      OdDbMTextObjectContextDataPtr mctx = data->getMTextObjectContextData();
      if (!mctx.isNull())
      {
        mctx->setLocation(alignmentPoint(ctx));
      }
    }
    if ( !bAdjust && !m_pMText.isNull() && (ctx.isNull() || ctx->isDefaultContextData()))
    {
      ((OdDbMTextImpl*)OdDbSystemInternals::getImpl(m_pMText))->clearCache();
      ((OdDbMTextImpl*)OdDbSystemInternals::getImpl(m_pMText))->m_Location = alignmentPoint(ctx);
    }
  }
  void setTextString(const OdString& textString, OdDbText* pThis);
  virtual OdString getTextString() const;

  virtual bool bIsMLineAttribute() const
  { 
    return !m_pMText.isNull(); 
  }

  virtual OdUInt8 getTypeAtrribute() const
  {
    if (bIsMLineAttribute())
      return OdDbAttributeImpl::kMultiLineAttribute;
    else
      return OdDbAttributeImpl::kSingleLine;
  }

protected:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
protected:
  struct MTextEnumParams
  {
    MTextEnumParams(const OdString& tag, OdDbObject* o, bool createAttr = true) : m_strTag(tag), m_bPreviousValid(false),m_pObject(o), 
    m_bCreateAttribute(createAttr), m_bAppend(true), m_bFirst(true), m_bTrueType(false)
    {
      if ( createAttr )
        appendAttribute(o);
    }
    void appendAttribute(OdDbObjectPtr obj);
    void appendFragment(OdString& s, OdDbMTextFragment* f, bool bAppend = true );
    OdArray<OdDbObjectPtr> m_Attributes;
    OdStringArray          m_arrTextAttributes;
    bool m_bAppend;
    OdString m_strTag;
    OdDbMTextFragment m_pPrevious;
    bool m_bPreviousValid;
    bool m_bCreateAttribute;
    bool m_bFirst;
    bool m_bTrueType;
    OdDbObject* m_pObject;
    OdGePoint3d m_firstPoint;
  };
  static int MTextEnum( OdDbMTextFragment* f, void * param);
  void decomposeFields(OdDbObject *pObj, MTextEnumParams& mp);
  bool m_bEffectivelyAnnotative;
  void setEffectivelyAnnotative(bool v){m_bEffectivelyAnnotative = v;}
  void propagateContextDataToMText();
  void subClose();
  virtual bool isAnnotativeForRendering() const ODRX_OVERRIDE;
  virtual void restoreAnnotativeLayer(OdDbObject* pObj, bool addFullContext) ODRX_OVERRIDE;

  friend class OdDbAttribute;
  friend class OdDbBlockReference;
  friend class OdDbBlockReferenceImpl;
  friend void decomposeAnnotativeAttributes(OdDbObject* blkRef, OdDbObjectContextData* data);
};

#endif // _ODDBATTRIBIMPL_INCLUDED_

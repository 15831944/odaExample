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

#ifndef _ODSYSVARAUDITOR_INCLUDED_
#define _ODSYSVARAUDITOR_INCLUDED_

#include "SysVarValidator.h"
#include "DbLayerTableRecord.h"
#include "DbMaterial.h"
#include "DbUCSTableRecord.h"
#include "DbMLeaderStyle.h"
#include "DbVisualStyle.h"

template <class T> class OdSysVarAuditor : public OdSysVarValidator<T>
{
public:
  OdSysVarAuditor(OdDbDatabase* pDb, const OdChar* name, T& val, const T& defVal, OdDbAuditInfo* pAuditInfo, const OdDbObject* pObj = 0)
    : OdSysVarValidator<T>(pDb, name, val)
    , _pAuditInfo(pAuditInfo)
    , _valRef(val)
    , _defVal(defVal)
  {
    if (pObj)
    {
      this->_objName = ::odDbGetObjectName(pObj);
      this->_varName = this->_pDb->appServices()->formatMessage(sidObjProp, this->_name);
    }
    else
    {
      this->_objName = this->_pDb->appServices()->formatMessage(sidDbHeader);
      this->_varName = this->_pDb->appServices()->formatMessage(sidSysVar, this->_name);
    }
  }

  void ValidateNone()
  {
  }
  void ValidateBOOL()
  {
    try
    {
      OdSysVarValidator<T>::ValidateBOOL();
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(this->_defVal ? sidVarDefTrue : sidVarDefFalse));
    }
  }
  void ValidateDouble(double limmin, double limmax)
  {
    try
    {
      OdSysVarValidator<T>::ValidateDouble(limmin, limmax);
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidRangeDouble, limmin, limmax),
        this->_pDb->appServices()->formatMessage(sidVarDefDouble, this->_defVal));
    }
  }
  void ValidateRange(T limmin, T limmax)
  {
    try
    {
      OdSysVarValidator<T>::ValidateRange(limmin, limmax);
    }
    catch (OdError_InvalidSysvarValue&)
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable: 4127)  // conditional expression is constant
#endif
      if (sizeof(T)==sizeof(double))
      {
        fixError(
          this->_pDb->appServices()->formatMessage(sidVarValidRangeDouble, limmin, limmax),
          this->_pDb->appServices()->formatMessage(sidVarDefDouble, this->_defVal));
      }
      else
      {
        fixError(
          this->_pDb->appServices()->formatMessage(sidVarValidRangeInt, limmin, limmax),
          this->_pDb->appServices()->formatMessage(sidVarDefInt, this->_defVal));
      }
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
  }
  void ValidatePositive()
  {
    try
    {
      OdSysVarValidator<T>::ValidatePositive();
    }
    catch (OdError_InvalidSysvarValue&)
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable: 4127)  // conditional expression is constant
#endif
        fixError(this->_pDb->appServices()->formatMessage(sidVarValidZeroPositive),
          this->_pDb->appServices()->formatMessage((sizeof(T) == sizeof(double)) ? sidVarDefDouble : sidVarDefInt, _defVal));
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
  }

  void ValidateNonZero()
  {
    try
    {
      OdSysVarValidator<T>::ValidateNonZero();
    }
    catch (OdError_InvalidSysvarValue&)
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable: 4127)  // conditional expression is constant
#endif
        fixError(this->_pDb->appServices()->formatMessage(sidVarValidNonZero),
          this->_pDb->appServices()->formatMessage((sizeof(T) == sizeof(double)) ? sidVarDefDouble : sidVarDefInt, _defVal));
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
  }

  void ValidatePositiveNonZero()
  {
    try
    {
      OdSysVarValidator<T>::ValidatePositiveNonZero();
    }
    catch (OdError_InvalidSysvarValue&)
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable: 4127)  // conditional expression is constant
#endif
      fixError(this->_pDb->appServices()->formatMessage(sidVarValidPositive),
        this->_pDb->appServices()->formatMessage((sizeof(T) == sizeof(double)) ? sidVarDefDouble : sidVarDefInt, _defVal));
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
  }
  void ValidateTextStyle(bool bNullIdAllowed = false)
  {
    if (bNullIdAllowed && this->_val.isNull())
      return;

    OdString errMsg;
    try
    {
      // additional validation
      OdDbTextStyleTableRecordPtr pStyle = this->_val.safeOpenObject();
      if (pStyle->isShapeFile())
      {
        errMsg = this->_pDb->appServices()->formatMessage(sidIsShapeFile);
      }

      // base validation
      OdSysVarValidator<T>::ValidateTextStyle();
    }
    catch (OdError_InvalidSysvarValue&)
    {
      errMsg = this->_pDb->appServices()->formatMessage(sidIsNotInTable);
    }
    catch (OdError& e)
    {
      errMsg = e.description();
    }

    if (!errMsg.isEmpty())
    {
      if (this->_pAuditInfo->fixErrors())
        this->_defVal = OdDbSymUtil::textStyleStandardId(this->_pDb);
      fixError(errMsg, standardStr);
    }
  }
  void ValidateLayer(bool bNullAllowed = false)
  {
    if (bNullAllowed && this->_val.isNull())
      return;

    try
    {
      OdSysVarValidator<T>::ValidateLayer(bNullAllowed);
      // additional validation
      OdDbLayerTableRecordPtr pRec = this->_val.safeOpenObject();
    }
    catch (OdError&)
    {
      if (this->_pAuditInfo->fixErrors())
        this->_defVal = this->_pDb->getLayerZeroId();
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        layerZeroNameStr);
    }
  }
  void ValidateMaterial()
  {
    try
    {
      OdSysVarValidator<T>::ValidateMaterial();
      // additional validation
      if (!this->_val.isNull())
      {
        OdDbMaterialPtr pMat = this->_val.safeOpenObject();
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidObjPropMaterialByLayer));
    }
  }
  void ValidateLinetype(bool bAllowsNull = false)
  {
    try
    {
      OdSysVarValidator<T>::ValidateLinetype(bAllowsNull);
      // additional validation
      if ( !this->_val.isNull() || !bAllowsNull )
      {
        OdDbLinetypeTableRecordPtr pRec = this->_val.safeOpenObject();
      }
    }
    catch (OdError&)
    {
      if (this->_pAuditInfo->fixErrors())
        this->_defVal = this->_pDb->getLinetypeByLayerId();
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        byLayerNameStr);
    }
  }
  void ValidateDimStyle()
  {
    try
    {
      OdSysVarValidator<T>::ValidateDimStyle();
      // additional validation
      OdDbDimStyleTableRecordPtr pRec = this->_val.safeOpenObject();
    }
    catch (OdError&)
    {
      if (this->_pAuditInfo->fixErrors())
        this->_defVal = OdDbSymUtil::dimStyleStandardId(this->_pDb);
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        OdDbSymUtil::dimStyleStandardName(this->_pDb->getMEASUREMENT()));
    }
  }
  void ValidateUcsRec()
  {
    try
    {
      OdSysVarValidator<T>::ValidateUcsRec();
      // additional validation
      if (!this->_val.isNull())
      {
        OdDbUCSTableRecordPtr pMat = this->_val.safeOpenObject();
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateMLStyle()
  {
    try
    {
      OdSysVarValidator<T>::ValidateMLStyle();
      // additional validation
      OdDbMlineStylePtr pMLStyle = this->_val.safeOpenObject();
    }
    catch (OdError&)
    {
      if (this->_pAuditInfo->fixErrors())
      {
        OdDbDictionaryPtr pDic = this->_pDb->getMLStyleDictionaryId().openObject();
        if (pDic.get())
        {
          OdDbObjectId styleId = pDic->getAt(OdDbSymUtil::MLineStyleStandardName());
          if (styleId.isNull())
          {
            pDic->upgradeOpen();
            styleId = pDic->setAt(
              OdDbSymUtil::MLineStyleStandardName(),
              OdDbUtils::createDefaultMlineStyle(this->_pDb->getLinetypeByLayerId()));
          }
          this->_defVal = styleId;
        }
      }
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        OdDbSymUtil::MLineStyleStandardName());
    }
  }
  void ValidatePSName()
  {
    // Do nothing
    // CEPSNID is audited with CEPSNTYPE in OdDbDatabaseImpl::audit()
  }
  void ValidateDimBlock()
  {
    try
    {
      OdSysVarValidator<T>::ValidateDimBlock();
      // additional validation
      if (!this->_val.isNull())
      {
        OdDbBlockTableRecordPtr pBlock = this->_val.safeOpenObject();
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateDecSep()
  {
  }
  void ValidatePDMODE()
  {
    try
    {
      OdSysVarValidator<T>::ValidatePDMODE();
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefInt, this->_defVal));
    }
  }
# define ODDB_VALIDATE_VALUE_TYPE(Type) \
  OdRxClassPtr cls = odrxClassDictionary()->getAt("AcDb" #Type);\
  OdDbObjectPtr obj = this->_val.safeOpenObject();\
  if(!obj->isKindOf(cls))\
    throw OdError_NotThatKindOfClass(obj->isA(), cls);\
  
  void ValidateTableStyle()
  {
    try
    {
      if (!this->_val.isNull())
      {
        OdSysVarValidator<T>::ValidateTableStyle();
        // additional validation
        ODDB_VALIDATE_VALUE_TYPE(TableStyle);
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateMLeaderStyle()
  {
    try
    {
      if (!this->_val.isNull())
      {
        OdSysVarValidator<T>::ValidateMLeaderStyle();
        // additional validation
        OdDbMLeaderStylePtr pStyle = odrxCastByClassName<OdDbMLeaderStyle>(this->_val.safeOpenObject(), "AcDbMLeaderStyle");
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateViewDetailStyle()
  {
    try
    {
      if (!this->_val.isNull())
      {
        OdSysVarValidator<T>::ValidateViewDetailStyle();
        // additional validation
        ODDB_VALIDATE_VALUE_TYPE(DetailViewStyle);
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateViewSectionStyle()
  {
    try
    {
      if (!this->_val.isNull())
      {
        OdSysVarValidator<T>::ValidateViewSectionStyle();
        // additional validation
        ODDB_VALIDATE_VALUE_TYPE(SectionViewStyle);
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateLineWeight(bool bActValOnly = false)
  {
    try
    {
      OdSysVarValidator<T>::ValidateLineWeight(bActValOnly);
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefInt, this->_defVal));
    }
  }
  void ValidateCmColor()
  {
    try
    {
      OdSysVarValidator<T>::ValidateCmColor();
    }
    catch (OdError_InvalidSysvarValue&)
    {
      OdString strColor = OdDbUnitsFormatter::formatColor(this->_defVal);
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefObj, strColor.c_str()));
    }
  }
  void ValidateEqGr(double r)
  {
    try
    {
      OdSysVarValidator<T>::ValidateEqGr(r);
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidZeroPositive),
        this->_pDb->appServices()->formatMessage(sidVarDefDouble, this->_defVal));
    }
  }
  void ValidateGr(double r)
  {
    try
    {
      OdSysVarValidator<T>::ValidateGr(r);
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidPositive),
        this->_pDb->appServices()->formatMessage(sidVarDefDouble, this->_defVal));
    }
  }
  void ValidateVisualStyle()
  {
    try
    {
      if (!this->_val.isNull())
      {
        OdSysVarValidator<T>::ValidateVisualStyle();
        // additional validation
        OdDbVisualStylePtr pStyle = this->_val.safeOpenObject();
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateLayout()
  {
    try
    {
      OdSysVarValidator<T>::ValidateLayout();
      // additional validation
      if (!this->_val.isNull())
      {
        OdDbLayoutPtr pLayout = this->_val.safeOpenObject();
      }
    }
    catch (OdError&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidVarDefNull));
    }
  }
  void ValidateColor()
  {
    if (!::odDbAuditColor(this->_valRef, this->_pAuditInfo, this->_pDb->appServices()))
    {
      this->_pAuditInfo->printError(this->_objName, this->_varName);
    }
  }

  void ValidateTransparency()
  {
    try
    {
      OdSysVarValidator<T>::ValidateTransparency();
    }
    catch (OdError_InvalidSysvarValue&)
    {
      fixError(
        this->_pDb->appServices()->formatMessage(sidVarValidInvalid),
        this->_pDb->appServices()->formatMessage(sidObjPropColorByLayer));
    }
  }
  void ValidateANNOTATIVEDWG()
  {
    ValidateRange(0, 1);
  }
private:
  void fixError(const OdString& validation, const OdString& defaultValue)
  {
    this->_pAuditInfo->errorsFound(1);
    this->_pAuditInfo->printError(
      this->_objName,
      this->_varName,
      validation,
      defaultValue);
    if (this->_pAuditInfo->fixErrors())
    {
      this->_pAuditInfo->errorsFixed(1);
      this->_valRef = this->_defVal;
    }
  }

  OdDbAuditInfo* _pAuditInfo;
  OdString _objName;
  OdString _varName;
  T& _valRef;
  T _defVal;
};

#endif //#ifndef _ODSYSVARAUDITOR_INCLUDED_

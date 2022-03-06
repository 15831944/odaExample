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

#ifndef _ODSYSVARVALIDATOR_INCLUDED_
#define _ODSYSVARVALIDATOR_INCLUDED_

#include "DbErrorInvalidSysvar.h"
#include "DbDatabaseImpl.h"

// Validator for system variables
template <class T> class OdSysVarValidator
{
protected:
  const OdChar* _name;
  OdTvDbDatabase* _pDb;
  void TvValidateTableRecordId(const OdTvDbObjectId& tableId, bool bNullAllowed = false)
  {
    if (bNullAllowed && _val.isNull())
      return;
    OdTvDbSymbolTablePtr pTable = tableId.safeOpenObject();
    if(!pTable->has(_val))
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
  void TvValidateDictObjectId(const OdTvDbObjectId& dictId)
  {
    OdTvDbDictionaryPtr pDict = dictId.safeOpenObject();
    if(!pDict->has(_val))
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
public:
  T _val;
  OdSysVarValidator(OdTvDbDatabase* pDb, const OdChar* name, const T& val)
    : _name(name)
    , _pDb(pDb)
    , _val( val )
  {
  }

  void TvValidateNone()
  {
  }
  void TvValidateBOOL()
  {
    if ( _val !=true && _val != false )
      throw OdError_TvInvalidSysvarValue( _name, 0, 1 );
  }
  void TvValidateRange(T limmin, T limmax)
  {
    if ( _val < limmin || _val > limmax )
      throw OdError_TvInvalidSysvarValue( _name, limmin, limmax );
  }
  void TvValidateDouble(double limmin, double limmax)
  {
    if ( OdLess(_val, limmin) || OdGreater(_val, limmax ))
      throw OdError_TvInvalidSysvarValue( _name, limmin, limmax );
  }
  void TvValidateTextStyle(bool bNullAllowed = false)
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateTableRecordId(pDb->getTextStyleTableId(), bNullAllowed);
  }
  void TvValidateLayer(bool bNullAllowed = false)
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateTableRecordId(pDb->getLayerTableId(), bNullAllowed);
  }
  void TvValidateMaterial()
  {
    if ( _val.isNull() ) // ByLayer
      return;

    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getMaterialDictionaryId());
  }
  void TvValidateLinetype(bool bAllowsNull = false)
  {
    if ( bAllowsNull && _val.isNull() )
        return;
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateTableRecordId(pDb->getLinetypeTableId());
  }
  void TvValidateDimStyle()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateTableRecordId(pDb->getDimStyleTableId());
  }
  void TvValidateUcsRec()
  {
    if ( _val.isNull() )
      return;

    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateTableRecordId(pDb->getUCSTableId());
  }
  void TvValidateMLStyle()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getMLStyleDictionaryId());
  }
  void TvValidatePSName()
  {
    if ( _val.isNull() )
      return;

    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getPlotStyleNameDictionaryId());
  }
  void TvValidateDimBlock()
  {
    if ( _val.isNull() )
      return;

    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateTableRecordId(pDb->getBlockTableId());
  }
  void TvValidateDecSep()
  {
  }
  void TvValidatePDMODE()
  {
    if ( (unsigned) (_val & ~(32 | 64)) > 4)
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
  void TvValidatePositive()
  {
    if ( _val < 0.0)
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
  void TvValidatePositiveNonZero()
  {
    if ( _val <= 0.0)
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
  void TvValidateNonZero()
  {
    if ( _val == 0.0)
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
  void TvValidateTableStyle()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getTableStyleDictionaryId());
  }
  void TvValidateMLeaderStyle()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getMLeaderStyleDictionaryId());
  }
  void TvValidateViewDetailStyle()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getDetailViewStyleDictionaryId());
  }
  void TvValidateViewSectionStyle()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getSectionViewStyleDictionaryId());
  }
  void TvValidateCmColor()
  {
    if (_val.colorMethod() == OdCmEntityColor::kNone)
      throw OdError_TvInvalidSysvarValue( _name );
  }
  void TvValidateLineWeight(bool bActValOnly = false)
  {
      switch (_val)
      {
      case  /*kLnWt000*/ 0:
      case /*kLnWt005*/  5:
      case /*kLnWt009*/  9:
      case /*kLnWt013*/ 13:
      case /*kLnWt015*/ 15:
      case /*kLnWt018*/ 18:
      case /*kLnWt020*/ 20:
      case /*kLnWt025*/ 25:
      case /*kLnWt030*/ 30:
      case /*kLnWt035*/ 35:
      case /*kLnWt040*/ 40:
      case /*kLnWt050*/ 50:
      case /*kLnWt053*/ 53:
      case /*kLnWt060*/ 60:
      case /*kLnWt070*/ 70:
      case /*kLnWt080*/ 80:
      case /*kLnWt090*/ 90:
      case /*kLnWt100*/100:
      case /*kLnWt106*/106:
      case /*kLnWt120*/120:
      case /*kLnWt140*/140:
      case /*kLnWt158*/158:
      case /*kLnWt200*/200:
      case /*kLnWt211*/211:
        return;
      }
      if (!bActValOnly)
      {
        switch (_val)
        {
        case /*kLnWtByLayer*/-1:
        case /*kLnWtByBlock*/-2:
        case /*kLnWtByLwDefault*/-3:
          return;
        }
      }
      throw OdError_TvInvalidSysvarValue( _name );
  }
  void TvValidateEqGr(double r)
  {
    if(r > _val)
      throw OdError_TvInvalidSysvarValue( _name );
  }
  void TvValidateGr(double r)
  {
    if (r >= _val)
      throw OdError_TvInvalidSysvarValue( _name );
  }
  void TvValidateVisualStyle()
  {
    if ( _val.isNull() )
      return;

    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getVisualStyleDictionaryId());
  }
  void TvValidateLayout()
  {
    OdTvDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_TvInvalidSysvarValue( _name );
    TvValidateDictObjectId(pDb->getLayoutDictionaryId());
  }
  void TvValidateColor()
  {
  }
  void TvValidateMLeaderScale()
  {
    if (_val < 0)
      throw OdError_TvInvalidSysvarValue(_name);
    OdTvDbMLeaderStylePtr mls = odrxCastByClassName<OdTvDbMLeaderStyle>(_pDb->getCMLEADERSTYLE().openObject(), "AcTvDbMLeaderStyle");
    if (!mls.isNull() && mls->annotative())
    {
      if (_val != 0.0) // exact equality
        throw OdError_TvInvalidSysvarValue(_name);
    }
  }

  void TvValidateTransparency()
  {
    if (_val.isInvalid())
    {
      throw OdError_TvInvalidSysvarValue( _name );
    }
  }
  void TvValidateANNOTATIVEDWG()
  {
    if (OdTvDbDatabaseImpl::getImpl(_pDb)->m_nAnnotativeObjectCount > 0)
      throw OdError_TvInvalidSysvarValue(_name);
    TvValidateRange(0, 1);
  }
};

#endif //#ifndef _ODSYSVARVALIDATOR_INCLUDED_


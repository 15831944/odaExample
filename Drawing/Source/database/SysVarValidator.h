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
  OdDbDatabase* _pDb;
  void ValidateTableRecordId(const OdDbObjectId& tableId, bool bNullAllowed = false)
  {
    if (bNullAllowed && _val.isNull())
      return;
    OdDbSymbolTablePtr pTable = tableId.safeOpenObject();
    if(!pTable->has(_val))
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
  void ValidateDictObjectId(const OdDbObjectId& dictId)
  {
    OdDbDictionaryPtr pDict = dictId.safeOpenObject();
    if(!pDict->has(_val))
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
public:
  T _val;
  OdSysVarValidator(OdDbDatabase* pDb, const OdChar* name, const T& val)
    : _name(name)
    , _pDb(pDb)
    , _val( val )
  {
  }

  void ValidateNone()
  {
  }
  void ValidateBOOL()
  {
    if ( _val !=true && _val != false )
      throw OdError_InvalidSysvarValue( _name, 0, 1 );
  }
  void ValidateRange(T limmin, T limmax)
  {
    if ( _val < limmin || _val > limmax )
      throw OdError_InvalidSysvarValue( _name, limmin, limmax );
  }
  void ValidateDouble(double limmin, double limmax)
  {
    if ( OdLess(_val, limmin) || OdGreater(_val, limmax ))
      throw OdError_InvalidSysvarValue( _name, limmin, limmax );
  }
  void ValidateTextStyle(bool bNullAllowed = false)
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateTableRecordId(pDb->getTextStyleTableId(), bNullAllowed);
  }
  void ValidateLayer(bool bNullAllowed = false)
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateTableRecordId(pDb->getLayerTableId(), bNullAllowed);
  }
  void ValidateMaterial()
  {
    if ( _val.isNull() ) // ByLayer
      return;

    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getMaterialDictionaryId());
  }
  void ValidateLinetype(bool bAllowsNull = false)
  {
    if ( bAllowsNull && _val.isNull() )
        return;
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateTableRecordId(pDb->getLinetypeTableId());
  }
  void ValidateDimStyle()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateTableRecordId(pDb->getDimStyleTableId());
  }
  void ValidateUcsRec()
  {
    if ( _val.isNull() )
      return;

    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateTableRecordId(pDb->getUCSTableId());
  }
  void ValidateMLStyle()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getMLStyleDictionaryId());
  }
  void ValidatePSName()
  {
    if ( _val.isNull() )
      return;

    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getPlotStyleNameDictionaryId());
  }
  void ValidateDimBlock()
  {
    if ( _val.isNull() )
      return;

    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateTableRecordId(pDb->getBlockTableId());
  }
  void ValidateDecSep()
  {
  }
  void ValidatePDMODE()
  {
    if ( (unsigned) (_val & ~(32 | 64)) > 4)
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
  void ValidatePositive()
  {
    if ( _val < 0.0)
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
  void ValidatePositiveNonZero()
  {
    if ( _val <= 0.0)
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
  void ValidateNonZero()
  {
    if ( _val == 0.0)
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
  void ValidateTableStyle()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getTableStyleDictionaryId());
  }
  void ValidateMLeaderStyle()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getMLeaderStyleDictionaryId());
  }
  void ValidateViewDetailStyle()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getDetailViewStyleDictionaryId());
  }
  void ValidateViewSectionStyle()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getSectionViewStyleDictionaryId());
  }
  void ValidateCmColor()
  {
    if (_val.colorMethod() == OdCmEntityColor::kNone)
      throw OdError_InvalidSysvarValue( _name );
  }
  void ValidateLineWeight(bool bActValOnly = false)
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
      throw OdError_InvalidSysvarValue( _name );
  }
  void ValidateEqGr(double r)
  {
    if(r > _val)
      throw OdError_InvalidSysvarValue( _name );
  }
  void ValidateGr(double r)
  {
    if (r >= _val)
      throw OdError_InvalidSysvarValue( _name );
  }
  void ValidateVisualStyle()
  {
    if ( _val.isNull() )
      return;

    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getVisualStyleDictionaryId());
  }
  void ValidateLayout()
  {
    OdDbDatabase * pDb = (_pDb != NULL) ? _pDb : _val.database();
    if (pDb == NULL)
      throw OdError_InvalidSysvarValue( _name );
    ValidateDictObjectId(pDb->getLayoutDictionaryId());
  }
  void ValidateColor()
  {
  }
  void ValidateMLeaderScale()
  {
    if (_val < 0)
      throw OdError_InvalidSysvarValue(_name);
    OdDbMLeaderStylePtr mls = odrxCastByClassName<OdDbMLeaderStyle>(_pDb->getCMLEADERSTYLE().openObject(), "AcDbMLeaderStyle");
    if (!mls.isNull() && mls->annotative())
    {
      if (_val != 0.0) // exact equality
        throw OdError_InvalidSysvarValue(_name);
    }
  }

  void ValidateTransparency()
  {
    if (_val.isInvalid())
    {
      throw OdError_InvalidSysvarValue( _name );
    }
  }
  void ValidateANNOTATIVEDWG()
  {
    if (OdDbDatabaseImpl::getImpl(_pDb)->m_nAnnotativeObjectCount > 0)
      throw OdError_InvalidSysvarValue(_name);
    ValidateRange(0, 1);
  }
};

#endif //#ifndef _ODSYSVARVALIDATOR_INCLUDED_


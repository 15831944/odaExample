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

#ifndef _DbBlockParameter_h_Included_
#define _DbBlockParameter_h_Included_

#include "TD_PackPush.h"

#include "DbBlockElement.h"
#include "DbEvalGraph.h"
#include "Ge/GeMatrix3d.h"
#include "DbDynBlockReference.h"

class OdTvDbBlockGrip;
typedef OdSmartPtr<OdTvDbBlockGrip> OdTvDbBlockGripPtr;
typedef OdArray< OdTvDbBlockGripPtr, OdMemoryAllocator<OdTvDbBlockGripPtr> > OdTvDbBlockGripPtrArray;

/** \details

    <group !!RECORDS_tdrawings_apiref>
*/
struct DYNBLOCKS_EXPORT OdTvDbBlkParamPropertyDescriptor
{
  OdTvDbBlkParamPropertyDescriptor();
  OdString m_sName;
  OdString m_sConnection;
  OdTvResBuf::ValueType m_nType;
  bool m_bReadonly;
  bool m_bVisible;
  OdString m_sDescription;
  bool m_bListPresent;
  OdTvDbDynBlockReferenceProperty::UnitsType m_nUnitsType;
  OdTvResBufArray m_pAllowedValues;
};
typedef OdArray< OdTvDbBlkParamPropertyDescriptor > OdTvDbBlkParamPropertyDescriptorArray;

/** \details
    This class represents block parameters in an OdTvDbDatabase instance.

    \sa
    TD_Db

    <group OdTvDb_Classes> 
*/
class DYNBLOCKS_EXPORT OdTvDbBlockParameter : public OdTvDbBlockElement
{
public:
  ODDB_EVAL_DECLARE_MEMBERS(OdTvDbBlockParameter);
  enum ParameterComponent 
  {
    Base,
    End,
    BaseXEndY,
    EndXBaseY,
    InvalidComponent
  };
  //virtual void removedFromGraph( OdTvDbEvalGraph* );
  
  virtual OdString getPropertyConnectionName( const OdString& )const;
  virtual void getPropertyDescription( OdTvDbBlkParamPropertyDescriptorArray& )const;
  virtual OdTvResBufPtr getPropertyValue( const OdString& )const;
  virtual OdTvResBufPtr getPropertyValue( const OdString&, const OdGeMatrix3d& )const;
  
  //virtual void gripErased( ParameterComponent );
  //virtual bool historyRequired() const;
  //static bool isPropertyLabelUnique( OdTvDbEvalGraph*, const OdString &, class OdString* );
  //virtual void getGrips( OdTvDbBlockGripPtrArray&, OdDb::OpenMode );
  //virtual int getNumberOfGrips() const;
  
  virtual ParameterComponent getComponentForGrip( OdTvDbEvalNodeId );
  
  //virtual void removeGrip( ParameterComponent );
  //virtual void resetGrips();
  //virtual void setNumberOfGrips( int );
  
  virtual bool setPropertyValue( const OdString&, const OdTvResBuf* );
  virtual bool setPropertyValue( const OdString&, const OdGeMatrix3d&, const OdTvResBuf* );
  virtual bool chainActions()const;
  virtual void setChainActions( bool );
  virtual bool showProperties()const;
  virtual void setShowProperties( bool );
  OdTvDbEvalNodeId addGrip( ParameterComponent );
};

typedef OdSmartPtr<OdTvDbBlockParameter>OdTvDbBlockParameterPtr;

#include "TD_PackPop.h"

#endif // _DbBlockParameter_h_Included_

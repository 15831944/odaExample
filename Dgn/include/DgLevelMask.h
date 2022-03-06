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
#ifndef __DG_LEVELMASK_H__
#define __DG_LEVELMASK_H__


#include "TD_PackPush.h"

#include "DgElement.h"

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgLevelMask : public OdDgElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgLevelMask);
public:
  enum OdDgLevelStatus
  {
    kLevelStatusUndefined = 0,
    kLevelVisible         = 1,
    kLevelHidden          = 2
  };
public:
  /**
    \remarks 0 - 'Default' level, >=1 - all other levels
  */
  bool getLevelIsVisible( OdUInt32 levelEntryId ) const;
  void setLevelIsVisible( OdUInt32 levelEntryId, bool value );

  OdDgLevelStatus getLevelIsVisible( const OdString& strLevelName, bool bFreezeNewLevels = false ) const;
  OdDgLevelStatus getLevelIsVisible( const OdDgElementId& idLevel, bool bFreezeNewLevels = false) const;
  void setLevelIsVisible( OdUInt32 uEntryId, const OdString& strLevelName, bool bVisible );

  OdUInt16 getViewIndex() const;
  void setViewIndex( OdUInt16 uIndex );

  OdDgElementId getReferenceAttachId() const;
  void          setReferenceAttachId( OdDgElementId idAttach );

  OdUInt64      getReferenceAttachHandleId() const;
  void          setReferenceAttachHandleId( OdUInt64 uRefAttachId );

  OdUInt32 getMaxLevelEntryId() const;  // ATTENTION: 'defaul' level with (64) id can be not taken into account.

  bool getLevelStatus( OdUInt32 uEntryId, OdString& strLevelName, OdDgLevelStatus& uStatus ) const;
};

typedef OdSmartPtr<OdDgLevelMask> OdDgLevelMaskPtr;

/** \details
   
    Corresponding C++ library: TG_Db 

    <group OdDg_Classes>
*/
class TG_EXPORT OdDgReferenceAttachmentLevelMaskGroup : public OdDgElement
{
  ODDG_DECLARE_MEMBERS_INTERNAL(OdDgReferenceAttachmentLevelMaskGroup);
public:
  virtual OdUInt64 getReferenceAttachmentId() const ;
  virtual void     setReferenceAttachmentId( OdUInt64 uId );
  //to support its complexity;
  //indeed, the only sub-element is level mask (to mask some levels by this view)
  void add( OdDgElementPtr pElement );
  OdDgElementIteratorPtr createIterator( bool atBeginning = true, bool skipDeleted = true ) const;
  virtual OdRxObjectPtr clone() const;
};

typedef OdSmartPtr<OdDgReferenceAttachmentLevelMaskGroup> OdDgReferenceAttachmentLevelMaskGroupPtr;

#include "TD_PackPop.h"

#endif // __DG_LEVELMASK_H__

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

#ifndef _EXDIMASSOC_INCLUDED
#define _EXDIMASSOC_INCLUDED


#include "DbEvalWatchers.h"
#include "ExDimAssocPE.h"
#include "DbClass.h"
#include "DbDimAssoc.h"
#include "DbFiler.h"
#include "StaticRxObject.h"
#include "DbTransactionReactor.h"



class OdExDimAssoc : public OdDbDimAssoc
{
public:
  ODDB_PSEUDO_DECLARE_MEMBERS(OdExDimAssoc);
  

  OdExDimAssoc();
  virtual ~OdExDimAssoc() ;

  class TrReactor : OdStaticRxObject<OdDbTransactionReactor>
  {
  public:
    TrReactor ();

    virtual void transactionEnded(OdDbDatabase* pDb);

    void setTransactionLevel(OdExDimAssoc *DimAssoc, const OdDbObject* pObject);

    bool CheckAssociativityInObjectClose(OdDbObjectId objectId);

  private:
    int TransLevel;

    OdDbObjectId DAId;
    OdDbObjectId dimId;
    OdDbObjectId UndoingObjectId;

  }
  TransactionReactor;

  friend class ExDimAssocWatcherPE;
  friend class TrReactor; 

  //void openedForModify(const OdDbObject* pObject);
  /** 
    Description:
    Returns true if all RefPoint has no changes 
    
    Arguments:
    ptPresent (I) Pointer to an array of current states(present or absent) of RefPoint.
    ptVals (I) Pointer to an array of new Points.    
    
  */  
  bool PointRefPositionModified(int *ptPresent, OdGePoint3d *ptVals) const;

  /** 
    Description:
    Returns true if pointRef(index) coordinates has been changed
    
    Arguments:
    index (I) Index of PointRef.    
    point (I) New position of pointRef(index) 
    
  */
  bool PointRefPositionModified(int index, OdGePoint3d &point) const;

  /** 
    Description:
    Returns true if any RefPoint owner is OdDbViewport and customScale() of Viewport has been changed
    
    Arguments:
    newDimlFac (I) New DimlFac value of Dimension.    
    
  */
  bool ViewPortScaleModified(double &newDimlFac) const;

  /**
    Description:
    Returns true if Entity has radius and he has been changed

  */
  bool EntityRadiusModified() const;
  
  void objectClosed(const OdDbObjectId& objectId);

private:

  int ptPresentPrv[kMaxPointRefs];
  OdGePoint3d ptValsPrv[kMaxPointRefs];

  double ViewPortScale;
  double EntityRadius;

  static void CheckForAssociativity(OdDbObjectId DimAssocId);
  
};

typedef OdSmartPtr<OdExDimAssoc> OdExDimAssocPtr;

#endif

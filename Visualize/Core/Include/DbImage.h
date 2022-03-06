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




#ifndef OD_DBIMAGE_H
#define OD_DBIMAGE_H

#include "TD_PackPush.h"

#include "DbEntity.h"

class OdGiSentScanLines;
class OdGiRequestScanLines;

/** \details
    This class is the abstract base class for image entities 
    contained in an OdTvDbDatabase instance.
    
    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbImage : public OdTvDbEntity
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbImage);

  OdTvDbImage();

  /* 
    virtual OdGiSentScanLines* getScanLines(const OdGiRequestScanLines&) const;
    virtual bool freeScanLines(OdGiSentScanLines*) const;    
    virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
    virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
    virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
    virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  */
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbImage object pointers.
*/
typedef OdSmartPtr<OdTvDbImage> OdTvDbImagePtr;

#include "TD_PackPop.h"

#endif  // OD_DBIMAGE_H


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

#ifndef _OD_DB_PROXYENTITYDATA_
#define _OD_DB_PROXYENTITYDATA_

#include "DbObject.h"

class OdTvDbProxyEntityData : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbProxyEntityData);

  OdTvDbProxyEntityData();

	/** Reads in the DWG data for this object.
	    @param pFiler Filer object from which data is read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

	/** Writes out the DWG data for this object.
	    @param pFiler Filer object to which data is written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

	/** Reads in the DXF data for this object.
	    @param pFiler Filer object from which data is read.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

	/** Writes out the DXF data for this object.
	    @param pFiler Filer object to which data is written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** Returns stored matrix
  */
  virtual OdGeMatrix3d getMatrix() const; 

  /** Sets matrix matr to be stored
      @param matr Matrix to be stored
  */
  virtual void setMatrix(const OdGeMatrix3d& matr);

  static void applyTo(OdTvDbEntity* pEnt);
};

typedef OdSmartPtr<OdTvDbProxyEntityData> OdTvDbProxyEntityDataPtr;

#endif

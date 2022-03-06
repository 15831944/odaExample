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


#ifndef _DbSweptSurface_h_Included_
#define _DbSweptSurface_h_Included_

#include "TD_PackPush.h"
#include "DbSurface.h"
#include "DbSweepOptions.h"

/** \details
This class implements a three-dimensional swept surface entity.

\sa
TD_Db

<group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbSweptSurface : public OdTvDbSurface
{
public:
  OdTvDbSweptSurface ();
  ODDB_DECLARE_MEMBERS(OdTvDbSweptSurface);

  /** \details
  Creates a swept surface by sweeping a specified curve, region, or planar surface along a specified path curve.


  \param pSweepEnt    [in] A pointer to the curve, region, or planar surface to be swept.
  \param pPathEnt     [in] A pointer to the curve entity that specifies the sweeping path along which a specified entity should to be swept.
  \param sweepOptions [in] Additional sweep options.
  
  \returns  Returns eOk if a surface was successfully created or eFail for other modelers. 
  If specified sweep information is not valid, returns eInvalidInput.
  Returns eFail if the surface cannot be created.
  
  \remarks 
  Additional parameters, such as a draft angle, can be set through the sweepOptions parameter.
  */
  virtual OdResult createSweptSurface ( OdTvDbEntity* pSweepEnt, OdTvDbEntity* pPathEnt, OdTvDbSweepOptions& sweepOptions, const OdStreamBuf *pSat = 0 );

  /** \details
  Returns the sweep entity that describes the surface.
  */
  OdTvDbEntityPtr getSweepEntity() const;
  
  /** \details
  Returns the sweep path used when the surface was created.
  */
  OdTvDbEntityPtr getPathEntity() const;

  /** \details
  Returns the sweep options applied when the surface was created.
  
  \param sweepOptions [out]  A passed-in parameter for returning the current sweep options object.
  */
  void getSweepOptions ( OdTvDbSweepOptions& sweepOptions ) const;
  
  /** \details
  Sets the new sweep option values for the surface.
  
  \param sweepOptions [in]  New options object to be set.
  
  \remarks
  This method is implemented only for Spatial modeler and returns eNotImplementedYet status
  for other modelers. 
  */
  void setSweepOptions ( const OdTvDbSweepOptions& sweepOptions );

  /** \details
  Returns the length of the path curve entity. 

  \param len [out]  A passed-in parameter for returning the length of the path curve.
  
  \returns Returns eOk if successful or eFail otherwise.
  */
  OdResult getPathLength ( double& len ) const;

  virtual OdResult subTransformBy(
    const OdGeMatrix3d& xfm );

  // OdTvDbObject methods

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  /*virtual OdResult subGetClassID(
    void* pClsid) const;*/

  virtual bool isDependent() const { return false; }
};

typedef OdSmartPtr<OdTvDbSweptSurface> OdTvDbSweptSurfacePtr;

#include "TD_PackPop.h"
#endif //_DbSweptSurface_h_Included_

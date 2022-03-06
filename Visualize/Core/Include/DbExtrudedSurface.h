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


#ifndef _DbExtrudedSurface_h_Included_
#define _DbExtrudedSurface_h_Included_

#include "TD_PackPush.h"
#include "DbSurface.h"
#include "DbSweepOptions.h"

/** \details
    This class implements a three-dimensional extruded surface entity.
    
    \sa
    TD_Db
   
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbExtrudedSurface : public OdTvDbSurface
{
public:
  OdTvDbExtrudedSurface ();
  ODDB_DECLARE_MEMBERS(OdTvDbExtrudedSurface);

  /** \details
    Creates an extruded surface by sweeping a planar curve, region, or planar surface in the direction of the given vector using a distance equal to the length of the vector. 
    	

    \param pSweepEnt      [in] A pointer to the curve, region, or planar surface to be swept.
    \param directionVec 	[in] A vector determining the distance and direction of the sweeping.
    \param sweepOptions		[in] Sweep options.
    \param OdStreamBuf 		[in] A pointer to an output stream buffer.
	
    \returns Returns eOk if successful or an appropriate error code otherwise.
	
	\remarks
    Additional extruding parameters (for example, draft angle) can be specified with the sweepOptions object.
	
    This method is implemented only for Spatial modeler and returns eNotImplementedYet status
    for other modelers. 
  */
  virtual OdResult createExtrudedSurface (OdTvDbEntity* pSweepEnt,
    const OdGeVector3d& directionVec, OdTvDbSweepOptions& sweepOptions, const OdStreamBuf *pSat = 0);

  /** \details
    Returns the sweep entity used to create the extruded surface.
  */
  OdTvDbEntityPtr getSweepEntity () const;

  /** \details
    Returns the extrusion vector.
  */
  OdGeVector3d getSweepVec() const;
  
  /** \details
    Sets the extrusion vector.
	
	\param sweepVec [in] A new extrusion vector.
  */
  void setSweepVec(const OdGeVector3d& sweepVec);

  /** \details
    Returns the extrusion height.
  */
  double getHeight() const;

  /** \details
    Sets the extrusion height.
	
    \param height [in] A new height value.
	
    \remarks
     This method is implemented only for Spatial modeler and returns eNotImplementedYet status 
     for other modelers. 
  */
  void setHeight(double height);

  /** \details
    Returns sweep options.
	
    \param sweepOptions [out] A reference to an OdTvDbSweepOptions object containing sweep option values.
  */
  void getSweepOptions (OdTvDbSweepOptions& sweepOptions) const;

  /** \details
    Sets sweep options.
	
    \param sweepOptions [in] An OdTvDbSweepOptions object containing new option values.
	
    \remarks
    This method is implemented only for Spatial modeler and returns eNotImplementedYet status 
    for other modelers. 
  */
  void setSweepOptions (const OdTvDbSweepOptions& sweepOptions);

  /** \details
    Sets all data that defines the parameters of an extruded surface.
	

	sweepVec 		  [in] A new extrusion vector.
	sweepOptions 	[in] An OdTvDbSweepOptions object containing new option values.
	
	\returns Returns eOk if extrude data is successfully set or an appropriate error code otherwise.
	
  \remarks
	This method is implemented only for Spatial modeler and returns eNotImplementedYet status 
	for other modelers. 
  */
  OdResult setExtrude(const OdGeVector3d& sweepVec,
    const OdTvDbSweepOptions& sweepOptions);

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

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbExtrudedSurface object pointers.
*/
typedef OdSmartPtr<OdTvDbExtrudedSurface> OdTvDbExtrudedSurfacePtr;

#include "TD_PackPop.h"
#endif //_DbExtrudedSurface_h_Included_

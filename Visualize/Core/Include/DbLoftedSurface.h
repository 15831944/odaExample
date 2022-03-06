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


#ifndef _DbLoftedSurface_h_Included_
#define _DbLoftedSurface_h_Included_

#include "TD_PackPush.h"
#include "DbSurface.h"
#include "DbLoftOptions.h"


/** \details
    This class implements a three-dimensional lofted surface entity.
    
    \sa
    TD_Db
   
    <group OdTvDb_Classes>
*/
class DBENT_EXPORT OdTvDbLoftedSurface : public OdTvDbSurface
{
public:
  OdTvDbLoftedSurface ();
  ODDB_DECLARE_MEMBERS(OdTvDbLoftedSurface);

  /** \details
  Creates a lofted surface from the specified curves according to the specified lofting options. 
	
	\param crossSectionCurves 	[in] A new height value.
	\param guideCurves 	        [in] An array of curve entities to be used as cross sections during the lofting process.
	\param pPathCurve 	        [in] A path curve.
	\param loftOptions          [in] A set of loft options.
	\param pSat 				[in] A pointer to an output stream buffer.
	
	\returns Returns eOk if a lofted surface was successfully created or an appropriate error code otherwise.

	\remarks
	All curve entities must be either open or closed. 
	When all curves are closed, this method accepts a point entity as the first and (or) last array element.
    This means that each curve in the guideCurves array must intersect each of the cross-section curves, so the guide curves form a net-like structure with the cross-section curves. 
	The cross-section and guide curves will be allocated on the created surface. 
	If any guide curves are specified, then pPathCurve should be NULL. 
	If pPathCurve is not NULL, then the created surface follows its shape (as close as possible). 
	The path curve does not need to intersect the cross-section curves and does not even need to be near the cross sections. 
	If the pPathCurve parameter is specified (not NULL), then the guideCurves array must be empty. 
  */
  virtual OdResult createLoftedSurface(
    OdTvDbEntityPtrArray& crossSectionCurves,
    OdTvDbEntityPtrArray& guideCurves,
    OdTvDbEntity* pPathCurve, 
    OdTvDbLoftOptions& loftOptions, const OdStreamBuf *pSat = 0);// , const bool byCoedges = false );

                                                               /** \details
                                                               Creates a blend surface from the specified entities according to the specified lofting options.

                                                               \param crossSectionCurves 	[in] A new height value.
                                                               \param guideCurves 	        [in] An array of curve entities to be used as cross sections during the lofting process.
                                                               \param pPathCurve 	        [in] A path curve.
                                                               \param loftOptions          [in] A set of loft options.
                                                               \param pSat 				[in] A pointer to an output stream buffer.

                                                               \returns Returns eOk if a lofted surface was successfully created or an appropriate error code otherwise.

                                                               \remarks
                                                               All curve entities must be either open or closed.
                                                               When all curves are closed, this method accepts a point entity as the first and (or) last array element.
                                                               This means that each curve in the guideCurves array must intersect each of the cross-section curves, so the guide curves form a net-like structure with the cross-section curves.
                                                               The cross-section and guide curves will be allocated on the created surface.
                                                               If any guide curves are specified, then pPathCurve should be NULL.
                                                               If pPathCurve is not NULL, then the created surface follows its shape (as close as possible).
                                                               The path curve does not need to intersect the cross-section curves and does not even need to be near the cross sections.
                                                               If the pPathCurve parameter is specified (not NULL), then the guideCurves array must be empty.
                                                               */
  virtual OdResult createBlendSurface(
    OdTvDbEntityPtrArray& blendedEdges,
    OdTvDbBlendOptions& loftOptions, const OdStreamBuf *pSat = 0);// , const bool byCoedges = false );

  /** \details
    Returns the number of cross section curves.
  */
  int           numCrossSections () const;
  
  /** \details
    Returns a cross section curve with specified index.
	
	\param idx [in]  An index of a cross section.
	
	\remarks
	The index for cross sections is zero-based (i.e., starts with 0). 
  */
  OdTvDbEntityPtr getCrossSection ( int idx ) const;
  
  /** \details
    Returns the number of guide curves used by the surface.
  */
    int           numGuideCurves () const;
  
  /** \details
  Returns a guide curve with specified index.
	
	\param idx [in]  An index of the guide curve.
	
	\remarks
	The index for guide curves is zero-based (i.e., starts with 0). 
  */
  OdTvDbEntityPtr getGuideCurve ( int idx ) const;
  
  /** \details
    Returns the path entity along which the surface is lofting.
  */
  OdTvDbEntityPtr getPathEntity () const;
  
  

  /** \details
  Returns the loft options used to create this surface.
	
	\param loftOptions [out]  An instance of the OdTvDbLoftOptions class passed from the method with the loft option values.
  */
  void          getLoftOptions ( OdTvDbLoftOptions& loftOptions ) const;

  
  /** \details
  Sets new loft option values and recreates the surface. 
	
	\param loftOptions [in]  New loft option values to be set.
	
	\returns Returns eOk if the lofted surface was successfully recreated with new options or an appropriate error code otherwise.
	
  \remarks 
	This method is implemented only for Spatial modeler and returns eNotImplementedYet status 
	for other modelers. 
  */
  OdResult setLoftOptions ( const OdTvDbLoftOptions& loftOptions );

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
    This template class is a specialization of the OdSmartPtr class for OdTvDbLoftedSurfacePtr object pointers.
*/
typedef OdSmartPtr<OdTvDbLoftedSurface> OdTvDbLoftedSurfacePtr;

#include "TD_PackPop.h"
#endif //_DbLoftedSurface_h_Included_
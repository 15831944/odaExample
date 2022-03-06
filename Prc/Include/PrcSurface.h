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

#ifndef _PRCSURFACE_INCLUDED_
#define _PRCSURFACE_INCLUDED_ 
 
#include "PrcUVParameterization.h"
#include "PrcContentSurface.h"
#include "PrcTransformation3d.h"

SMARTPTR(OdPrcSurface);
class OdPrcSurfaceImpl;

/** \details 
<group PRC_Surface_Classes> 

Base class of surfaces.
*/
class PRC_TOOLKIT OdPrcSurface : public OdRxObject
{
protected:
  OdPrcSurface(OdPrcSurfaceImpl *pImpl);
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE_BASE_NOTYPE(OdPrcSurface)
  //DOM-IGNORE-END

  /** \details
  Destroys the surface object.
  */
  virtual ~OdPrcSurface();

  /** \details
  Returns the current matrix of the 3D transformation.
  */
  const OdGeMatrix3d & getGeMatrix3d() const;

  /** \details
  Sets a new value of the surface position in model space.

  \param trans [in] A pointer to a new surface position in model space to set.

  \returns Returns eOk if a new position was successfully set or an appropriate error code in the other case.
  */
  OdResult setTransformation(const OdPrcTransformation3d* trans);

  /** \details
  Returns the current surface position in model space.
  */
  const OdPrcTransformation3d *transformation() const;

  /** \details
  Returns the current surface geometry data.

  \param pGeSurface [out] A pointer to a surface object to store surface geometry data.
  \param tol [in] A topological context.

  \returns Returns eOk if surface geometry data was successfully returned to the calling subroutine or an appropriate error code in the other case.
  */
  OdResult getOdGeSurface(OdGeSurface*& pGeSurface, const OdGeTol& tol = OdGeContext::gTol) const;
  
  /** \details
  Sets new surface data from a surface entity.

  \param geSurface [in] A surface entity to set surface data from.
  \param tol [in] A topological context.

  \returns Returns eOk if surface data was successfully set or an appropriate error code in the other case.
  */
  OdResult setFromOdGeSurface(const OdGeSurface& geSurface, const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Creates new surface data from a OdGeSurface entity.
  
    \param geSurface       [in] OdGeSurface object reference to create from.
    \param pPrcSurface [in/out] Pointer object to which the result will be written.
    \param tol             [in] Tolerance.
    \returns Returns eOk if surface data was successfully set or an appropriate error code in the other case.
  */
  static OdResult createFromOdGeSurface(const OdGeSurface& geSurface, OdPrcSurfacePtr& pPrcSurface, const OdGeTol& tol = OdGeContext::gTol);

  /** \details
  Returns the current uv-parametrization of the surface.
  */
  const OdPrcUVParameterization& uVParameterization() const;
  
  /** \details
  Sets a new parametrization of the surface.

  \param uvparameterization [in] A new uv-parametrization to be set.

  \returns Returns eOk if a new uv-parameterization was successfully applied to the surface or an appropriate error code in the other case.
  */
  OdResult setUVParameterization(const OdPrcUVParameterization& uvparameterization);

  /** \details
  Returns current surface data from a compressed filer stream, creates a surface, and returns a smart pointer to it.

  \param pStream [in] A pointer to a compressed filer stream to read data from.
  */
  static OdPrcSurfacePtr readPtr(OdPrcCompressedFiler *pStream);
  
  /** \details
  Writes surface data to a specified compressed filer stream.

  \param pSurface [in] A pointer to a surface to write data from.

  \param pStream [in] A pointer to a compressed filer stream to write data to.
  */
  static void writePtr(const OdPrcSurface *pSurface, OdPrcCompressedFiler *pStream);
  
  /** \details
  Reads surface array data from a specified compressed filer stream, creates surfaces, and returns an array of smart pointers to the created surfaces.

  \param array [out] A reference to an array of surfaces to fill after reading from a stream.
  \param pStream [in] A pointer to a compressed filer stream to read data from.
  */
  static void readArray(OdPrcSurfacePtrArray &array, OdPrcCompressedFiler *pStream);
  
  /** \details
  Writes an array of surfaces to a specified compressed filer stream.

  \param array [in] An array of surfaces to get surface data from.

  \param pStream [in] A pointer to a compressed filer stream to write data to.
  */
  static void writeArray(const OdPrcSurfacePtrArray &array, OdPrcCompressedFiler *pStream);
  
  /** \details
  Reads surface data from a specified compressed filer stream, creates a surface, and returns a smart pointer to it.

  \param pStream [in] A pointer to a compressed filer stream to read data from.
  */
  static OdPrcSurfacePtr read(OdPrcCompressedFiler *pStream);

  /** \details
  Returns current common data of the surface.
  Common data is returned as a reference to an OdPrcContentSurface object, therefore it can be used to set new data.
  */
  OdPrcContentSurface &contentSurface();

  /** \details
  Returns current common data of the surface.
  */
  const OdPrcContentSurface &contentSurface() const;
};

#endif // _PRCSURFACE_INCLUDED_


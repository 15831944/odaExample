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

#ifndef _PDF2PRCEXPORTPARAMS_INCLUDED_
#define _PDF2PRCEXPORTPARAMS_INCLUDED_

#include "PdfExportDef.h"
#include "Ge/GeMatrix3d.h"
#include "RxSystemServices.h"
#include "RxDictionary.h"
#include "PdfExportParams.h"
#include "Gi/GiSubEntityTraitsData.h"
#include "RxVariantValue.h"
#include "ColorMapping.h"

/** \details
  Represents a list of parameters for exporting PDF data to PRC format.
  <group OdExport_Classes>
*/
struct PDF2PRCExportParams
{
  /** Reserved options. */
  OdRxDictionaryPtr m_extraOptions; 

  /** Compression level values for B-Rep data and tessellation.*/
  OdUInt32 m_compressionLevel;

  /** The transformation matrix. */
  OdGeMatrix3d m_bodyTransformationMatr;

  /** The array of deviations. */
  OdGeDoubleArray m_arrDeviation;

  /** The flag that indicates whether the model is to be exported as a B-Rep. If it is set to false, the model is exported as a mesh. */
  bool m_exportAsBrep;  

  /** An index of the viewport in the destination PDF document to export the model to. */
  OdUInt32 m_viewportIdx;

  /** An index of the view. */
  OdUInt32 m_viewIdx;

  /** A pointer to the effective entity traits object. */
  const OdGiSubEntityTraitsData * m_pTraitsData;

  /** A pointer to the ByBlock traits data. */
  const OdGiSubEntityTraitsData * m_pByBlockTraitsData;

  /** \details
   Creates a new PDF2PRCExportParams instance with default export parameters (default constructor).
 */
  PDF2PRCExportParams()
    : m_compressionLevel(0)
    , m_bodyTransformationMatr()
    , m_exportAsBrep(true)
    , m_viewportIdx(0)
    , m_viewIdx(0)
    , m_pTraitsData(NULL)
    , m_pByBlockTraitsData(NULL)
  {
    m_arrDeviation.resize(5, 0.);
    m_extraOptions = odrxCreateRxDictionary();
    //default palette setup
    OdUInt32 numcolors = 256;
    OdIntPtr ppallete = (OdIntPtr)::odcmAcadDarkPalette();
    m_extraOptions->putAt("Pallet", OdRxVariantValue(ppallete));
    m_extraOptions->putAt("NumColors", OdRxVariantValue(numcolors));
  }

  /** \details
  Sets the PRC data compression level values for B-Rep and tessellation.

  \param compressionLevel       [in] A compression level value to set.
  \param bCompressBrep          [in] A flag value that indicates whether the compression level is being set for B-Rep. If the flag is equal to false, the compression is not used.
  \param bCompressTessellation  [in] A flag that indicates whether the compression level is being set for tessellation. If the flag is equal to false, the compression is not used.
  */
  void setPRCCompression(PDF3D_ENUMS::PRCCompressionLevel compressionLevel, bool bCompressBrep, bool bCompressTessellation)
  {
    if ((!bCompressBrep) && (!bCompressTessellation))
    {
      SETBIT_0(m_compressionLevel, 0x00000004);
      SETBIT_0(m_compressionLevel, 0x00000008);
      return;
    }

    m_compressionLevel = compressionLevel;
    SETBIT(m_compressionLevel, 0x00000004, bCompressBrep);
    SETBIT(m_compressionLevel, 0x00000008, bCompressTessellation);
  }

  /** \details
  Gets the compression flag value for the B-Rep.
  \param compressionLev [out] A placeholder for the compression level used for the B-Rep geometry.
  \returns true if the compression is used for the B-Rep; otherwise, the method returns false.
  */
  bool hasPrcBrepCompression(PDF3D_ENUMS::PRCCompressionLevel &compressionLev) const
  {
    if ((m_compressionLevel & 0x00000004) != 0)
    {
      // apply mask
      compressionLev = (PDF3D_ENUMS::PRCCompressionLevel)(m_compressionLevel & 0x00000003);
      return true;
    }
    return false;
  }

  /** \details
  Gets the tessellation compression flag value.
  \returns true if the compression is used for the tessellation; otherwise, the method returns false.
  */
  bool hasPrcTessellationCompression() const { return ((m_compressionLevel & 0x00000008) != 0); }
};

#endif

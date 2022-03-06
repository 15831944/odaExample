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


///////////////////////////////////////////////////////////////////////////////
//
// STLExport.h - Open Design STL Export definitions
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _STLPARAMS_INCLUDED_
#define _STLPARAMS_INCLUDED_

#include "STLExportDef.h"
#include "Gi/GiDrawable.h"
#include "OdStreamBuf.h"
#include "DbBaseDatabase.h"

/** \details
  <group OdExport_Classes> 
*/
namespace TD_STL_EXPORT
{
  /** \details
  This class implements the STL export parameters.

  <group OdExport_Classes>
  */
  class STLEXPORT_DLL OdStlExportParams
  {
    OdDbBaseDatabase   *m_pDb;
    const OdGiDrawable *m_pEntity;
    OdStreamBuf        *m_pOutStream;
    const ODCOLORREF   *m_pPalette;
    double              m_dDeviation;
    bool                m_bPositiveOctant;
    bool                m_bTextMode;
    bool                m_bCorrectSolid;
    bool                m_bUseColors;
  public:
    /** \details
    Creates a new set of export parameters with default values.
    */
    OdStlExportParams();

    /** \details
    Sets database to be used during the export.

    \param pDb [in]  A new value to be set.
    \returns Reference to the parameters.
    */
    OdStlExportParams &setDatabase(OdDbBaseDatabase &pDb);

    /** \details
    Sets drawable to be exported.

    \param pEntity [in]  A new value to be set.
    \returns Reference to the parameters.
    */
    OdStlExportParams &setEntity(const OdGiDrawable &pEntity);

    /** \details
    Sets output stream to store STL data.

    \param pOutStream [in]  A new value to be set.
    \returns Reference to the parameters.
    */
    OdStlExportParams &setStream(OdStreamBuf &pOutStream);

    /** \details
    Sets deviation value to control geometry quality.

    \param dDeviation [in]  A new value to be set.
    \returns Reference to the parameters.
    */
    OdStlExportParams &setDeviation(double dDeviation);

    /** \details
    Sets octant flag value.

    \param bPositiveOctant [in]  A new value to be set.
    \returns Reference to the parameters.

    \remarks
    If positiveOctant is true and at least one of the obtained triangle points
    has at least one coordinate from the (-inf, 0] interval,
    then all points will be shifted to an octant, where all coordinates
    are positive numbers from the (0.01, +inf) interval.
    */
    OdStlExportParams &setPositiveOctant(bool bPositiveOctant);

    /** \details
    Sets text mode flag. If true, STL will be stored in the text form, otherwise in the binary.

    \param bTextMode [in]  A new value to be set.
    \returns Reference to the parameters.
    */
    OdStlExportParams &setTextMode(bool bTextMode);

    /** \details
    Sets correct solid flag.

    \param bCorrectSolid [in]  A new value to be set.
    \returns Reference to the parameters.

    \remarks
    Exports an element to an STL format stream and checks the element's volume. If the volume is negative, the element will be turned inside out.
    */
    OdStlExportParams &setCorrectSolid(bool bCorrectSolid);

    /** \details
    Sets use colors flag value.

    \param bUseColors [in]  A new value to be set.
    \returns Reference to the parameters.

    \remarks For binary mode only. Stores RGB color information in attribute byte.
    */
    OdStlExportParams &setUseColors(bool bUseColors);

    /** \details
    Sets color palette to be used for indexed colors.

    \param pPalette [in]  A new palette.
    \returns Reference to the parameters.

    \remarks By default indexed colors will be converted to RGB by OdCmEntityColor::lookUpRGB.
    */
    OdStlExportParams &setPalette(const ODCOLORREF* pPalette);

    /** \details
    Retrieves the database.
    \returns The database.
    */
    OdDbBaseDatabase &database() const;

    /** \details
    Retrieves the entity.
    \returns The entity.
    */
    const OdGiDrawable &entity() const;

    /** \details
    Retrieves the output stream.
    \returns The output stream.
    */
    OdStreamBuf &stream() const;

    /** \details
    Retrieves the deviation.
    \returns The deviation.
    */
    double deviation() const;

    /** \details
    Retrieves the positive octant flag.
    \returns The positive octant flag.

    \remarks
    If positiveOctant is true and at least one of the obtained triangle points
    has at least one coordinate from the (-inf, 0] interval,
    then all points will be shifted to an octant, where all coordinates
    are positive numbers from the (0.01, +inf) interval.
    */
    bool positiveOctant() const;

    /** \details
    Retrieves the export mode.
    \returns The export mode.

    \remarks
    If true, STL will be stored in the text form, otherwise in the binary.
    */
    bool textMode() const;

    /** \details
    Retrieves the correct solid flag.
    \returns The correct solid flag.
    \remarks
    Exports an element to an STL format stream and checks the element's volume. If the volume is negative, the element will be turned inside out.
    */
    bool correctSolid() const;

    /** \details
    Retrieves the use colors flag.
    \returns The use colors flag.
    \remarks For binary mode only. Stores RGB color information in attribute byte.
    */
    bool useColors() const;

    /** \details
    Retrieves the color palette.
    \returns The color palette.
    */
    const ODCOLORREF* palette() const;

    /** \details
    Check if parameters are valid or not.
    \returns True if parameters are valid, or false otherwise.
    \remarks Database, entity and stream parameters must be set.
    */
    bool isValid() const;
  };

};

#endif // _STLPARAMS_INCLUDED_


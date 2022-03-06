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

#ifndef _PRCCRVCURVE_INCLUDED_
#define _PRCCRVCURVE_INCLUDED_ 
 
#include "PrcContentCurve.h"
#include "PrcParameterization.h"

SMARTPTR(OdPrcCurve);
class OdPrcCurveImpl;

/** \details 
<group PRC_Curve_Classes>

An abstract class of a curve. 
This class is the base class for various curve classes. 
*/
class PRC_TOOLKIT OdPrcCurve : public OdRxObject
{
protected:
  OdPrcCurve(OdPrcCurveImpl *pImpl);
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_BASE_NOTYPE(OdPrcCurve)
  //DOM-IGNORE-END

  /** \details 
  Destroys the curve object.
  */
  virtual ~OdPrcCurve();

  /** \details
  Reads curve data from a specified input stream, creates a curve, and returns a smart pointer to an OdPrcCurve object.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  
  \returns Returns a smart pointer to an OdPrcCurve object.
  */
  static OdPrcCurvePtr readPtr(OdPrcCompressedFiler *pStream);

  /** \details
  Writes curve data to a specified output stream.

  \param pCRVCurve [in] A smart pointer to an OdPrcCurve object.
  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  */
  static void writePtr(const OdPrcCurve *pCRVCurve, OdPrcCompressedFiler *pStream);

  /** \details
  Reads data from a specified input stream into a curve array.

  \param array [out] A reference to an array of OdPrcCruve smart pointers to read in.
  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  static void readArray(OdPrcCurvePtrArray &array, OdPrcCompressedFiler *pStream);

  /** \details
  Writes data from a curve array to a specified output stream.

  \param array [in] A reference to an array of smart pointers to OdPrcCurve objects.
  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  */
  static void writeArray(const OdPrcCurvePtrArray &array, OdPrcCompressedFiler *pStream);

  /** \details
  Reads curve data from a specified input stream, and creates and returns a curve entity.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  \returns Returns a smart pointer to the created curve.
  */
  static OdPrcCurvePtr read(OdPrcCompressedFiler *pStream);

  /** \details
  Returns the current curve's 3D flag value.
  The flag is equal to true if the curve is a 3D object or is equal to false in the other case.
  */
  virtual bool is3d() const = 0;

  /** \details
  Returns the current parameterization information used for the curve.
  */
  const OdPrcParameterization& parameterization() const;

  /** \details
  Sets new parametrization information to the curve.

  \param param [in] Input definition of parametrization. 
  
  \returns Returns eOk if new parameterization information was successfully applied to the curve or an appropriate error code in the other case.
  */
  OdResult setParameterization(const OdPrcParameterization& param);

  /** \details
  Returns current common curve data for the composite curve.
  Common curve data is returned as a reference to an OdPrcContentCurve object, therefore it can be used to set new common curve data of the composite curve.
  */
  OdPrcContentCurve &contentCurve();

  /** \details
  Returns common curve data for the composite curve.
  */
  const OdPrcContentCurve &contentCurve() const;
};

#endif // _PRCCRVCURVE_INCLUDED_


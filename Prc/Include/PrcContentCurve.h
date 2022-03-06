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

#ifndef _PRCCONTENTCURVE_INCLUDED_
#define _PRCCONTENTCURVE_INCLUDED_ 
 

#include "PrcBaseGeometry.h"
class OdPrcContentCurveImpl;

/** \details 
<group PRC_Curve_Classes>

Class stores additional data of a curve.
*/
class PRC_TOOLKIT OdPrcContentCurve
{
  OdPrcContentCurveImpl *m_pImpl;
  friend class OdPrcSystemInternals;

public:

  /** \details
  Creates an instance of a curve's additional data.
  */
  OdPrcContentCurve(OdPrcContentCurveImpl *pImpl);

  /** \details
  Creates an instance of a curve's additional data.
  */
  ~OdPrcContentCurve();

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE(OdPrcContentCurve)
  //DOM-IGNORE-END

  /** \details
  Returns the current base geometry information.
  The base geometry information is returned as a reference to an OdPrcBaseGeometry object, therefore it can be used to set new geometry data.
  */
  OdPrcBaseGeometry &baseGeometry();
  
  /** \details
  Returns the current base geometry information.
  */
  const OdPrcBaseGeometry &baseGeometry() const;
  
  /** \details
  Sets new information about extending the curve.

  \param value [in] New information to be set.
  */
  void setExtendInfo(OdUInt32 value);
  
  /** \details
  Returns the current information about extending the curve.
  */
  OdUInt32 extendInfo() const;

  /** \details
  The assignment operator for the additional data about the curve.

  \param contentCurve [in] Curve content to be assigned.

  \returns Returns a PRCContentCurve object with new data inside.
  */
  OdPrcContentCurve& operator= (const OdPrcContentCurve &contentCurve);

  /** \details
  Exports the curve content to a .prc file.

  \param pStream [out] An output stream (file stream, memory stream) for writing.

  \param is3d [in] 3D flag. Flag is equal to true if the curve is a 3D curve or is equal to false in the other case.
  */
  void prcOut(OdPrcCompressedFiler *pStream, bool is3d);
  
  /** \details
  Imports the curve content from a .prc file.

  \param pStream [in] An input stream (file stream, memory stream) to read from.
  */
  void prcIn(OdPrcCompressedFiler *pStream);
};

#endif // _PRCCONTENTCURVE_INCLUDED_


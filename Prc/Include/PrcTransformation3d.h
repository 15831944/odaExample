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

#ifndef _PRCTRANSFORMATION3D_INCLUDED_
#define _PRCTRANSFORMATION3D_INCLUDED_ 
 
#include "Ge/GeMatrix3d.h"

/** \details 
<group PRC_Miscellaneous_Classes>

Class represents a 3D transformation defined by a 4x4-sized matrix. 
*/
class PRC_TOOLKIT OdPrcTransformation3d
{
private:
  OdInt8       m_behaviour;
  OdGeMatrix3d m_mat;
  
  OdInt8 calculateBehaviour3d(const OdGeTol& tol = OdGeContext::gTol) const;

protected:

  /** \details
  Sets a new behavior for the 3D transformation.

  \param value [in] An new behavior to be set.
  
  \returns Returns eOk if a new behavior was successfully applied to the 3D transformation entity or an appropriate error code in the other case.
  */
  OdResult setBehaviour(OdInt8 value);

  /** \details
  Returns the current value of the 3D transformation behavior.
  */
  OdInt8 behaviour() const;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE(OdPrcTransformation3d)
  //DOM-IGNORE-END

  /** \details
  Writes cartesian transformation data to a specified output stream.

  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  */
  void writeCartesian3d(OdPrcCompressedFiler *pStream) const;

  /** \details
  Reads cartesian transformation data from a specified input stream.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  void readCartesian3d(OdPrcCompressedFiler *pStream);

  /** \details
  Reads general 3D transformation data from a specified input stream.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  void readGeneral3d(OdPrcCompressedFiler *pStream);

  /** \details
  Writes general 3D transformation data to a specified output stream.

  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  */
  void writeGeneral3d(OdPrcCompressedFiler *pStream) const;

  /** \details
  Reads 3D topological data from a specified input stream.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  */
  void readTopo3d(OdPrcCompressedFiler *pStream);

  /** \details
  Writes 3D topological data to a specified output stream.

  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
  */
  void writeTopo3d(OdPrcCompressedFiler *pStream) const;

  /** \details
  Reads 3D transformation data from a specified input stream, creates a 3D transformation entity, and returns a reference to an OdPrcTransformation3d object.

  \param pStream [in] A pointer to an input stream (file stream, memory stream) to read from.
  \param transformation [in] A reference to an 3D OdPrcTransformation3d object.
  */
  static void readTransformation3d(OdPrcCompressedFiler *pStream, OdPrcTransformation3d &transformation);

  /** \details
  Writes 3D transformation data to a specified output stream.

  \param trnsform [in] A constant reference to a 3D transformation entity.
  \param pStream [in] A pointer to an output stream (file stream, memory stream) to write to.
*/
  static void writeTransformation3d(OdPrcCompressedFiler *pStream, const OdPrcTransformation3d &trnsform);

  /** \details
  Returns the current matrix of the 3D transformation.
  */
  const OdGeMatrix3d &getGeMatrix3d() const;

  /** \details
  Sets a new matrix of the 3D transformation.

  \param geMatrix [in] A new matrix to be set.
  \param tol [in] Tolerance. Default value is equal to OdGeContext::gTol.

  \returns Returns eOk if a new matrix was successfully applied to the 3D transformation entity or an appropriate error code in the other case.
  */
  OdResult set(const OdGeMatrix3d& geMatrix, const OdGeTol& tol = OdGeContext::gTol);

  /** \details
  Assigns transformation 3D data from another OdPrcTransformation3d entity to this object. 

  \param trans [in] A constant reference to a 3D transformation entity for copying. 
  \returns A reference to an OdPrcTransformation3d object.
  */
  OdPrcTransformation3d& operator= (const OdPrcTransformation3d &trans);
};

#endif // _PRCTRANSFORMATION3D_INCLUDED_

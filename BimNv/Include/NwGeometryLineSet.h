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

#ifndef __TNW_GEOMETRYLINESET_H__
#define __TNW_GEOMETRYLINESET_H__

#include "NwGeometry.h"
#include "UInt16Array.h"
#include "Ge/GePoint3dArray.h"

/** Forward declaration of the OdNwVerticesData class. */
class OdNwVerticesData;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwVerticesData object pointers.
*/
typedef OdSmartPtr<OdNwVerticesData> OdNwVerticesDataPtr;

/** \details
  This class represents geometry with the line set type.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwGeometryLineSet : public OdNwGeometry
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwGeometryLineSet);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwGeometryLineSet object.
  */
  OdNwGeometryLineSet();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwGeometryLineSet();
  
  /** \details
    Returns an array with the the number of vertices per line.

    \returns OdArray objects with the the number of vertices per line.
    \remarks
    The method is deprecated. Use getVerticesCountPerLine() method instead.
  */
  OdArray<OdUInt16> getVertexCountPerLine() const;

  /** \details
  Returns an array with the the number of vertices per line.

  \returns OdArray objects with the the number of vertices per line.
  */
  OdUInt16Array getVerticesCountPerLine() const;

  /** \details
    Returns a vertices data object.

    \returns OdNwVerticesDataPtr objects with vertices, normals, colors etc.
  */
  OdNwVerticesDataPtr getVerticesData() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGeometryLineSet object pointers.
*/
typedef OdSmartPtr<OdNwGeometryLineSet> OdNwGeometryLineSetPtr;

#endif //__TNW_GEOMETRYLINESET_H__

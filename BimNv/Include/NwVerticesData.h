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

#ifndef __TNW_VERTICES_DATA_H__
#define __TNW_VERTICES_DATA_H__

#include "RxSystemServices.h"
#include "NwObject.h"
#include "UInt32Array.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeVector3dArray.h"

/** \details
  This class represents object geometry data for vectorization.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwVerticesData : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwVerticesData);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwVerticesData object.
  */
  OdNwVerticesData();
  
  /** \details
    Constructor. Creates a new OdNwVerticesData object.

    \param pImpl [in]  OdNwGeometry implementation object.
  */
  explicit OdNwVerticesData(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwVerticesData();

  /** \details
    Returns an array of vertices.

    \returns Array of vertices.
  */
  OdGePoint3dArray getVertices() const;

  /** \details
  Returns an array of normals.

  \returns Array of normals.
*/
  OdGeVector3dArray getNormals() const;

  /** \details
    Returns an array of texture coordinates.

    \returns Array of texture coordinates.
  */
  OdGePoint2dArray getTexCoords() const;

  /** \details
    Returns an array of colors.

    \returns Array of colors.
  */
  OdUInt32Array getColors() const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwGeometry object pointers.
*/
typedef OdSmartPtr<OdNwVerticesData> OdNwVerticesDataPtr;

#endif //__TNW_VERTICES_DATA_H__

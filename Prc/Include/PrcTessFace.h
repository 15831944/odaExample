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

#ifndef _PRCTESSFACE_INCLUDED_
#define _PRCTESSFACE_INCLUDED_ 
 

#include "PrcArrayRgba.h"
#include "PrcObjectId.h"

/** \details 
<group PRC_Tessellation_Classes> 

Class stores tessellation data for a face.
*/
class PRC_TOOLKIT OdPrcTessFace
{
private:
  OdUInt32Array      m_sizes_wire;
  OdUInt32Array      m_sizes_triangulated;
  OdPrcObjectIdArray m_line_attributes;
  OdPrcArrayRgba     m_ArrayRGBA;
  OdUInt32           m_start_wire;
  OdUInt32           m_used_entities_flag;
  OdUInt32           m_start_triangulated;
  OdUInt32           m_number_of_texture_coordinate_indexes;
  OdUInt32           m_behaviour;
  bool               m_has_vertex_colors;
  bool               m_b_optimised;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcTessFace)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of wire edge indexes.
  The array of wire edge indexes is returned as a reference to an OdUInt32Array object, therefore it can be used to set a new array or modify the existing one.
  */
  OdUInt32Array &sizesWire();
  
  /** \details
  Returns the current array of wire edges indexes.
  */
  const OdUInt32Array &sizesWire() const;
  
  /** \details
  Returns the current array of tessellation data.
  The array of tessellation data is returned as a reference to an OdUInt32Array object, therefore it can be used to set a new array or modify the existing one.
  */
  OdUInt32Array &sizesTriangulated();
  
  /** \details
  Returns the current array of tessellation data.
  */
  const OdUInt32Array &sizesTriangulated() const;
  
  /** \details
  Returns the current array of line styles.
  The array of line styles is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new array or modify the existing one.
  */
  OdPrcObjectIdArray &lineAttributes();
  
  /** \details
  Returns the current array of line styles.
  */
  const OdPrcObjectIdArray &lineAttributes() const;
  
  /** \details
  Returns the current array of color data.
  The array of color data is returned as a reference to an OdPrcArrayRgba object, therefore it can be used to set a new array or modify the existing one.
  */
  OdPrcArrayRgba &arrayRGBA();
  
  /** \details
  Returns the current array of color data.
  */
  const OdPrcArrayRgba &arrayRGBA() const;
  
  /** \details
  Sets a new start wire value.

  \param start_wire [in] A new value of the start wire to be set.
  */
  void setStartWire(OdUInt32 start_wire);
  
  /** \details
  Returns the current start wire value.
  */
  OdUInt32 startWire() const;
  
  /** \details
  Sets a new value of the used entities flag. 
  The used entities flag contains the types of triangulated entities.

  \param used_entities_flag [in] A new value of the flag to be set.
  */
  void setUsedEntitiesFlag(OdUInt32 used_entities_flag);
  
  /** \details
  Returns the current value of the used entities flag.
  The used entities flag contains the types of triangulated entities.
  */
  OdUInt32 usedEntitiesFlag() const;
  
  /** \details
  Sets a new starting index of triangulated entities.

  \param start_triangulated [in] A new starting index to be set.
  */
  void setStartTriangulated(OdUInt32 start_triangulated);
  
  /** \details
  Returns the current starting index of triangulated entities.
  */
  OdUInt32 startTriangulated() const;
  
  /** \details
  Sets a new number of texture coordinate indexes.

  \param number_of_texture_coordinate_indexes [in] A new number of texture coordinate indexes to be set.
  */
  void setNumberOfTextureCoordinateIndexes(OdUInt32 number_of_texture_coordinate_indexes);
  
  /** \details
  Returns the current number of texture coordinate indexes.
  */
  OdUInt32 numberOfTextureCoordinateIndexes() const;
  
  /** \details
  Sets a new graphics behavior value.

  \param behaviour [in] A new graphics behavior value to be set.
  */
  void setBehaviour(OdUInt32 behaviour);
  
  /** \details
  Returns the current graphics behavior value.
  */
  OdUInt32 behaviour() const;
  
  /** \details
  Sets a new value of the direct color storing flag.
  The direct color storing flag indicates whether colors are stored directly in the vertices (true) or not (false).

  \param has_vertex_colors [in] A new flag value to be set.
  */
  void setHasVertexColors(bool has_vertex_colors);
  
  /** \details
  Returns the current value of the direct color storing flag.
  The direct color storing flag indicates whether colors are stored directly in the vertices (true) or not (false).
  */
  bool hasVertexColors() const;
  
  /** \details
  Sets a new value of the optimization flag. 
  The optimization flag indicates whether the entity is optimized (true) or not (false).

  \param b_optimised [in] A new value of the optimization flag to be set.
  */
  void setBOptimised(bool b_optimised);
  
  /** \details
  Returns the current value of the optimization flag. 
  The optimization flag indicates whether the entity is optimized (true) or not (false).
  */
  bool bOptimised() const;
  
  /** \details
  Returns the current PRC type.
  */
  OdUInt32 prcType() const;
};

typedef OdArray<OdPrcTessFace> OdPrcTessFaceArray;

#endif // _PRCTESSFACE_INCLUDED_


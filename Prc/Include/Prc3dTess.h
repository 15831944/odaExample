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

#ifndef _PRC3DTESS_INCLUDED_
#define _PRC3DTESS_INCLUDED_ 
 

#include "PrcBaseTessData.h"
#include "PrcTessFace.h"

/** \details 
<group PRC_Tessellation_Classes> 

Class representing 3D tessellation data for an ordered collection of faces.
*/
class PRC_TOOLKIT OdPrc3dTess : public OdPrcBaseTessData
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TESS(OdPrc3dTess);
  //DOM-IGNORE-END

  /** \details
    Returns the current wire index array.
    Wire index array is returned as a reference to an OdUInt32Array object, therefore it can be used to set a new index array. 
  */
  OdUInt32Array &wireIndex();

  /** \details
    Returns the current wire index array.
  */
  const OdUInt32Array &wireIndex() const;

  /** \details
    Returns the current triangulated index array.
    Triangulated index array is returned as a reference to an OdUInt32Array object, therefore it can be used to set a new index array. 
  */
  OdUInt32Array &triangulatedIndex();

  /** \details
    Returns the current triangulated index array.
  */
  const OdUInt32Array &triangulatedIndex() const;

  /** \details
    Returns the current normal coordinates.
    Normal coordinates are returned as a reference to an OdFloatArray object, therefore it can be used to set new coordinates. 
  */
  OdFloatArray &normalCoordinate();

  /** \details
    Returns the current normal coordinates.
  */
  const OdFloatArray &normalCoordinate() const;

  /** \details
    Returns the current texture coordinates.
    Texture coordinates are returned as a reference to an OdFloatArray object, therefore it can be used to set new coordinates. 
  */
  OdFloatArray &textureCoordinate();
    
  /** \details
    Returns the current texture coordinates.
  */
  const OdFloatArray &textureCoordinate() const;
  
  /** \details
    Returns the current face tessellation data.
    Face tessellation data is returned as a reference to an OdPrcTessFaceArray object, therefore it can be used to set a new face tessellation. 
  */
  OdPrcTessFaceArray &faceTessellation();
  
  /** \details
    Returns the current face tessellation data.
  */
  const OdPrcTessFaceArray &faceTessellation() const;

  /** \details
    Returns the current coordinates.
    Coordinates are returned as a reference to an OdFloatArray object, therefore it can be used to set new coordinates. 
  */
  OdFloatArray &coordinates();

  /** \details
    Returns the current coordinates.
  */
  const OdFloatArray &coordinates() const;
  
  /** \details
    Sets a new value of the normals recalculation flag.

    \param normals_recalculation_flags [in] An integer value of flag.
  */
  void setNormalsRecalculationFlags(OdInt8 normals_recalculation_flags);

  /** \details
    Returns the current value of the normals recalculation flag.
  */
  OdInt8 normalsRecalculationFlags() const;
  
  /** \details
    Sets a new value of the limit angle between two faces.
    
    \param crease_angle [in] A double value of the angle.
  */
  void setCreaseAngle(double crease_angle);

  /** \details
    Returns the current value of the limit angle between two faces.
  */
  double creaseAngle() const;

  /** \details
    Sets a new value of the flag which shows whether the tessellation has faces.
    
    \param has_faces [in] A new value of the flag.
  */
  void setHasFaces(bool has_faces);

  /** \details
    Returns the current value of the flag which shows whether the tessellation has faces.
    If the tessellation has faces, true is returned; in the other case the method returns false.
  */
  bool hasFaces() const;
  
  /** \details
    Sets a new value of the loops flag.
    Loops flag shows whether the tessellation has loops.

    \param has_loops [in] A new value of the flag.
  */
  void setHasLoops(bool has_loops);

  /** \details
    Returns the current value of the loops flag.
    Loops flag shows whether the tessellation has loops.
    If tessellation has loops, true is returned; in the other case the method returns false.
  */
  bool hasLoops() const;

  /** \details
    Sets the current value of the flag which determines whether normals must be recalculated.

    \param must_recalculate_normals [in] A new value of the flag.
  */
  void setMustRecalculateNormals(bool must_recalculate_normals);

  /** \details
    Returns the current value of the flag which determines whether normals must be recalculated.
    If normals must be recalculated, true is returned; in the other case the method returns false.
  */
  bool mustRecalculateNormals() const;

  /** \details
    Sets the current value of the calculation flag.
    Calculation flag determines whether tessellation data was calculated (true) or retrieved from an original CAD application (false).
    \param is_calculated [in] A new value of the flag.
  */
  void setIsCalculated(bool is_calculated);
  
  /** \details
    Returns the current value of the calculation flag.
    Calculation flag determines whether tessellation data was calculated (true) or retrieved from an original CAD application (false).
  */
  bool isCalculated() const;

  /** \details
    Optimizes tessellation data by removing dublicate points, normals, textures, wires.
    Returns true if optimization succeed, false - if not.
    \param dTolerance [in] specifies tolerance of optimization, if dTolerance is 0 (default value) data are taken as is, use it carefuly with other value.
  */
  bool optimize(double dTolerance = 0.);
};

SMARTPTR(OdPrc3dTess);

#endif // _PRC3DTESS_INCLUDED_


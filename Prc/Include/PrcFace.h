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

#ifndef _PRCFACE_INCLUDED_
#define _PRCFACE_INCLUDED_ 
 

#include "PrcTopoItem.h"
#include "PrcBaseTopology.h"
#include "PrcSurface.h"
#include "PrcDomain.h"
#include "PrcTopoItem.h"
#include "PrcLoop.h"
#include "PrcGraphics.h"

/** \details 
<group PRC_Topology_Classes>

Class representing a surface's bounded part which is defined by a surface, 
an optional domain for trimming a face definition, an associated tolerance, 
and a list of loops for delimiting a bounded part.
*/
class PRC_TOOLKIT OdPrcFace : public OdPrcTopoItem
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TOPO(OdPrcFace)
  //DOM-IGNORE-END

  /** \details
  Returns current surface orientation data.
  Surface orientation data is returned as a reference to an Orientation value, therefore it can be used to set new orientation data.
  */
  Orientation &orientationSurfaceWithShell();
  
  /** \details
  Returns current surface orientation data.
  */
  const Orientation &orientationSurfaceWithShell() const;

  /** \details
  Adds a new loop to the face.
  \param pLoop [in] A new loop to be added.
  */
  void addLoop(const OdPrcLoopPtr &pLoop);

  /** \details
  Sets a loop array to the face.
  \param arrLoops [in] A new array of loops to be added.
  */
  void setLoops(const OdPrcLoopPtrArray &arrLoops);
  
  /** \details
  Returns the current array of loops that delimit a part of the face.
  */
  const OdPrcLoopPtrArray &loops() const;
  
  /** \details
  Sets a new domain for trimming the face definition.

  \param pTrimDomain [in] A constant pointer to an OdPrcDomain object to be set as the trimming domain.
  */
  void setSurfaceTrimDomain(const OdPrcDomain *pTrimDomain);
  
  /** \details
  Returns the current domain for trimming the face definition.
  */
  const OdPrcDomain *surfaceTrimDomain() const;
  
  /** \details
  Returns current base surface geometry.
  The base surface geometry is returned as a reference to a smart pointer to an OdPrcSurfacePtr object, therefore it can be used to set new base surface geometry.
  */
  OdPrcSurfacePtr &baseSurface();
  
  /** \details
  Returns the current base surface geometry.
  */
  const OdPrcSurfacePtr &baseSurface() const;
  
  /** \details
  Returns current base topology data.
  The base topology data is returned as a reference to an OdPrcBaseTopology object, therefore it can be used to set new base topology data. 
  */
  OdPrcBaseTopology &baseTopology();
  
  /** \details
  Returns current base topology data.
  */
  const OdPrcBaseTopology &baseTopology() const;
  
  /** \details
  Sets a new tolerance value.
  If the tolerance is 0.0 the topological context tolerance is used.
  \param tolerance [in] The new tolerance value to be set.
  */
  void setTolerance(double tolerance);
  
  /** \details
  Returns the current tolerance value.
  If the tolerance is 0.0 the topological context tolerance must be used.
  */
  double tolerance() const;
  
  /** \details
  Destroys the face object.
  */
  ~OdPrcFace();
  
  /** \details
  Returns the current value of the graphic flag.
  The graphic flag indicates that the face has graphics (if true).
  */
  bool hasGraphics(void) const;
  
  /** \details
  Returns current graphics data.
  */
  const OdPrcGraphics *graphics(void) const;
  /** \details
  Sets a new outer loop index for the face.

  \param nOuterLoopIndex [in] The new outer loop index for the face.
  \returns Returns eOk if new outer loop index was successfully applied to the face or an appropriate error code in the other case.
  */
  OdResult setOuterLoopIndex(OdInt32 nOuterLoopIndex);

  /** \details
  Returns the current outer loop index.
  */
  OdInt32 getOuterLoopIndex() const;
  
  /** \details
  Sets new graphics data to the face.

  \param faceGraphics [in] A pointer to new graphics data to be applied to the face.
  */
  void setGraphics(const OdPrcGraphics *faceGraphics);
   
  /** \details
  Clears current graphics data.
  */
  void clearGraphics(void);
};
SMARTPTR(OdPrcFace);

#endif // _PRCFACE_INCLUDED_


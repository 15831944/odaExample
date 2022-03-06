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
#ifndef BRMESH_H_INCLUDED
#define BRMESH_H_INCLUDED

#include "Br/BrMeshEntity.h"

/** \details
  This class defines the interface base class for meshes.

  \remarks 
  This class is implemented only for Spatial modeler.
  
  \sa
  TD_Br
  
  <group OdBr_Classes>
  */
class ODBR_TOOLKIT_EXPORT OdBrMesh : public OdBrMeshEntity
{
public:
  /** \details
    Virtual destructor.
  */
  virtual ~OdBrMesh();

protected:
  /** \details
    Default constructor. Object of this class can't be instantiated.
  */
  OdBrMesh();
#ifdef OD_ADD_MOVE_CTOR_HAVE_DEF_DEL_FUNC
  //DOM-IGNORE-BEGIN
  OdBrMesh(const OdBrMesh&) = default;
  OdBrMesh& operator=(const OdBrMesh&) = default;
  OdBrMesh(OdBrMesh&&) = default;
  OdBrMesh& operator=(OdBrMesh&&) = default;
  //DOM-IGNORE-END
#endif
};


#endif


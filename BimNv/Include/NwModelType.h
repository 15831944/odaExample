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


#ifndef TNW_MODEL_TYPE_H_
#define TNW_MODEL_TYPE_H_

/** \details
  Type of model that was loaded.

  <group TNW_Namespaces>
*/
namespace NwModelType
{
  enum Enum
  {
    /** Original model is undefined. */
    undefined = 0,
    /** Original model is from a .dwg file. */
    dwg_model,
    /** Original model is a DGN model. */
    dgn_model,
    /** Original model is an Autodesk(R) Revit(R) model. */
    revit_model,
    /** Original model is an Autodesk Navisworks(R) model. */
    nw_model,
    /** Original model is an Autodesk Navisworks model.*/
    nw_13_model,
    /** Original model is a IFC model.*/
    ifc_model,
  };
}
#endif  // TNW_MODEL_TYPE_H_


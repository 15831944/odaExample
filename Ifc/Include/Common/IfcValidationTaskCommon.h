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

#ifndef  _IFC_VALIDATION_TASK_COMMON_H
#define _IFC_VALIDATION_TASK_COMMON_H

#include "OdaCommon.h"

#include "daiValidationTask.h"

class OdIfcFile;

/** \details
Contains declarations related to working with IFC files content.
*/
namespace OdIfc
{
  /** \details
  The ifc struct which contains validation context for instances and extents validations.
  */
  struct OdIfcInstanceValidationContext : OdDAI::OdBaseInstanceValidationContext
  {
    /**A raw pointer to the OdIfcFile class instance.*/
    OdIfcFile* pFile;

    /** \details
    Struct constructor.
    \param _pFile [in] A raw pointer to the <OdIfc::OdIfcFile, OdIfcFile> object which used for validation.
    */
    OdIfcInstanceValidationContext(OdIfcFile* _pFile) :OdDAI::OdBaseInstanceValidationContext(), pFile(_pFile) {}
  };

  /** \details
  The ifc struct which contains validation context for model validations.
  */
  struct OdIfcModelValidationContext : OdDAI::OdBaseModelValidationContext
  {
    /**A raw pointer to the OdIfcFile class instance.*/
    OdIfcFile* pFile;

    /** \details
    Struct constructor.
    \param _pModel [in] A raw pointer to <link OdDAI::Model, Model> object which used for validation.
    \param _pFile  [in] A raw pointer to the <OdIfc::OdIfcFile, OdIfcFile> object which used for validation.
    */
    OdIfcModelValidationContext(OdDAI::Model* _pModel, OdIfcFile* _pFile) :OdDAI::OdBaseModelValidationContext(_pModel), pFile(_pFile) {}
  };
}
#endif // _IFC_VALIDATION_TASK_COMMON_H

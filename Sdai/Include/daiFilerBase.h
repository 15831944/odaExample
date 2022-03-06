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

#ifndef _DAI_FILER_BASE_H_
#define _DAI_FILER_BASE_H_

#include "SharedPtr.h"
#include "RxObject.h"

#include "daiModel.h"
#include "daiApplicationInstance.h"
#include "HandleTree.h"
#include "DbHostAppProgressMeter.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  An abstract class that describes the interface for working with supported files format (as Step Physical File, HDF5, XML).
  Step Physical Files are .ifc/.step/.stp files; XML are represented with .ifcXML, stepX files.
  */
  class DAI_EXPORT FilerBase : public OdRxObject
  {
  protected:
    OdDbHostAppProgressMeter *m_meter;
    Model *m_model;
    SdaiAccessMode m_modeToRestore;

    FilerBase();

    /** \details
    Retrieves an object identifier of the entity instance by its STEP identifier. 
    The enumeration is the same as in the STEP physical file. 
    If there is no object identifier with a specified handle, it will be created.
    \param h [in] A entity identifier.
    \returns An object identifier of the entity instance.
    */
    OdDbStub* checkHandle(const OdDbHandle& h);

    /** \details 
    Calculates inverse attributes after the file loading.
    */
    virtual void calcInverseAttributes();

    /** \details
    Creates a new instance of a specified entity type.
    \param entityTypeName [in] A string that contains the type name of the new entity to be created.
    \param h              [in] An entity handle.
    \returns A smart pointer to the created entity instance.
    \remarks
    If the current schema does not support the specified type, the method returns a NULL smart pointer.
    In this case, the isNull() method of the smart pointer object returns true.
    The created entity instance is not attached to the model.
    */
    ApplicationInstancePtr createEntityInstance(const char *entityTypeName, const OdDbHandle& h);

    /** \details
    Creates a new instance of a specified entity type.
    \param entity [in] An pointer to entity definition to be instantiated.
    \param h      [in] An entity handle.
    \returns A smart pointer to the created entity instance.
    \remarks
    If the current schema does not support the specified type, the method returns a NULL smart pointer.
    In this case, the isNull() method of the smart pointer object returns true.
    The created entity instance is not attached to the model.
    */
    ApplicationInstancePtr createEntityInstance(const OdDAI::Entity *entity, const OdDbHandle& h);

    /** \details
    Retrieves OdHandleTree class for the model.
    \returns A raw pointer to the OdHandleTree object.
    */
    OdHandleTree *getHandleTree();

    /** \details
    The prototype of the internal method for reading the model. It must be re-implemented in derived classes.
    \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error.
    */
    virtual OdResult doReadModel() = 0;
    
    /** \details
    The prototype of the internal method for writing the model. It must be implemented in derived classes.
    \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error.
    */
    virtual OdResult doWriteModel() = 0;

  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(FilerBase);
    //DOM-IGNORE-END

    /** \details
    Reads the Step Physical File data section from a .ifc file into the model.
    \param model [in] A pointer to model.
    \param meter [in] A pointer to progress meter.
    \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error.
    */
    OdResult readModel(Model *model, OdDbHostAppProgressMeter *meter);

    /** \details
    Writes the Step Physical File data section from the model into a .ifc file.
    \param model [in] A pointer to model.
    \param meter [in] A pointer to progress meter.
    \returns eOk if the data was successfully written; otherwise, the method returns an appropriate error.
    */
    OdResult writeModel(Model *model, OdDbHostAppProgressMeter *meter);
  };
} // namespace

#endif // _DAI_FILER_BASE_H_

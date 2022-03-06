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

#ifndef _IFC_CORE_H
#define _IFC_CORE_H

#include <daiModule.h>
#include "daiHostModule.h"

#include "IfcBuildOptions.h"
#include "IfcValueTypes.h"
#include "IfcUtils.h"

class OdIfcHostAppServices;

/** \details
Enumeration for default database content initialization modes.
*/
enum IfcSchema
{
  /**Database content is not initialized (undefined schema).*/
  kScmUndefined = 0,
	/**Default database content has the Ifc2x3 version.*/
  kScmIfc2x3 = 1,
	/**Default database content has the Ifc4 version.*/
  kScmIfc4 = 2,
  /**Default database content has the Ifc4x3 Release Candidate 4 version.*/
  kScmIfc4x3_RC4 = 3
};

/** \details
Defines available modeler types.
*/
enum ModelerType
{
  /**ODA Facet Modeler.*/
  kFacetModeler, 
  /**Spatial ACIS Modeler.*/
  kSpaModeler, 
  /**ODA Brep Modeler.*/
  kBrepModeler, 
  /**Default type of the modeler.*/
  kDefaultModeler = kFacetModeler,
};

/** \details 
Initializes IFC SDK functionality.
\param initCDA             [in] A flag that determines whether Common Data Access (CDA) functionality should be provided for IFC data.
\param initIfcGeomResource [in] A flag that determines whether geometry resources are initialized as well (if equal to true) or not (if equal to false).
\param modelerType         [in] A type of modeler that should be used for geometry creation.
\returns Returns eOk if IFC SDK was successfully initialized; otherwise, the function returns an appropriate error code.
\remarks 
The function checks whether all needed modules are loaded and loads them if they are not. 
If at least one of the necessary modules is not loaded, the function returns the eNullPtr error code.
It the bInitIfcGeomResource parameter value is equal to false, the IFC geometry library is unavailable, 
therefore the model cannot be visualized. In this mode only data management functionality is available.
*/
IFCCORE_EXPORT OdResult odIfcInitialize(bool initCDA = true, bool initIfcGeomResource = true, ModelerType modelerType = kDefaultModeler);

/** \details
Retrieves whether IFC SDK functionality has already been initialized.
\returns true if IFC SDK has already been initialized; otherwise, the function returns false.
*/
IFCCORE_EXPORT bool odIfcIsInitialized();

/** \details 
De-initializes IFC SDK functionality.
\returns Returns eOk if IFC SDK was successfully de-initialized; otherwise, the function returns an appropriate error code.
\remarks 
The function checks whether the needed modules are loaded and decreases the reference counters for them. 
If a reference counter for any appropriate module becomes equal to zero, the function unloads the module.
If no IFC-related modules are loaded, the function returns the eNullPtr error code.
*/
IFCCORE_EXPORT OdResult odIfcUninitialize();

/** \details
Initializes IFC SDK Modeler functionality.
\param modelerType[in] Modeler type which will be used to create geometry.
\returns Returns eOk if IFC SDK Modeler was successfully initialized; otherwise, the function returns an appropriate error code.
*/
IFCCORE_EXPORT OdResult odIfcInitModelerGeometry(ModelerType modelerType = kDefaultModeler);

/**\details 
Retrieves whether the IFC geometry module is loaded and initialized. 
\returns The function returns true if the IFC geometry module is initialized; otherwise, the function returns false.
*/
IFCCORE_EXPORT bool odIfcIsGeomResourceInitialized();

/**\details
Retrieves whether the Common Data Access functionality is initialized for ODA IFC SDK.
\returns The function returns true if the CDA is initialized and can be used for IFC data.
*/
IFCCORE_EXPORT bool odIfcIsCDAInitialized();

/** \details
An abstract class that provides the interface for a module that implements core IFC functionality.
*/
class IFCCORE_EXPORT OdIfcCoreModule : public OdDAIHostModule
{
public:

  /** \details 
  Initializes the core IFC module.
  */
  virtual void initApp();
  
  /** \details 
  De-initializes the core IFC module.
  */
  virtual void uninitApp();

  /** \details 
  Registers a module implements the support of an appropriate IFC schema.
  \param expSchemaModule [in] A raw pointer to a module that supports the work with the schema.
  \returns eOk the module was successfully registered; otherwise, the method returns an appropriate error code.
  */
  OdResult registerSchemaModule(OdExpSchemaModule *expSchemaModule);

  /** \details
  Retrieves whether the Common Data Access interface is available for the core IFC module.
  \returns true if the CDA interface is enabled; otherwise, the method returns false.
  */
  bool isCDAEnabled();
};

/** \details 
A data type that represents a smart pointer to an <link OdIfc::OdIfcCoreModule, OdIfcCoreModule> object.
*/
typedef OdSmartPtr<OdIfcCoreModule> OdIfcCoreModulePtr;

/** \details
Creates a shape representation of a specified GiDrawable entity inside a specified model 
and associates it with a specified representation context.
\param pEnt         [in] A smart pointer to an entity, that should be converted into a shape representation.
\param subContextId [in] An identifier of the sub-context object to which the shape representation should be added.
\param pModel       [in] A smart pointer to an <link OdIfcModel, OdIfcModel> object that represents the current model of the file.
\param shapeId      [out] The object identifier of the created shape representation.
\returns eOk if the shape representation was successfully created; otherwise, the function returns an appropriate error code.
\remarks 
The method sets the value of the created shape representation's identifier and returns it to a calling subroutine.
*/
IFCCORE_EXPORT OdResult getDrawableShapeRepresentation(OdGiDrawablePtr pEnt, 
                                                       const OdDAIObjectId& subContextId, 
                                                       OdDAI::Model *pModel, 
                                                       OdDAIObjectId& shapeId,
                                                       int shapeType);

/** \details
Creates shape representations for each provided GiDrawable entity and returns the array of identifiers for every newly created shape representation to the calling subroutine. 
Every newly created shape representation is assigned to a specified representation context.
\param entities [in] An array of entities, which will be converted in the OdIfcShapeRepresentation object.
\param subContextId [in] An identifier of the sub-context object to which the shape representation will be added.
\param pModel [in] A raw pointer to the instance of the <link , OdIfcModel> class that represents the current model of the file.
\param shapeId [out] A placeholder for the identifier of the created shape representation object.
\returns eOk if the shape representation object was successfully created; otherwise, the function returns an appropriate error code.
\remarks 
The method sets identifier values of created shape representations, adds them into the provided identifiers array, and returns it to a calling subroutine.
*/
IFCCORE_EXPORT OdResult getDrawableShapeRepresentation(const OdArray<OdGiDrawablePtr>& entities,
  const OdDAIObjectId& subContextId,
  OdDAI::Model* pModel,
  OdDAIObjectId& shapeId,
  int shapeType);

//DOM-IGNORE-BEGIN
/**For internal use only.*/
IFCCORE_EXPORT void setIfcFormatter(class OdUnitsFormatter* pFormatter);
/**For internal use only.*/
IFCCORE_EXPORT OdUnitsFormatter* getIfcFormatter();
//DOM-IGNORE-END

#endif // _IFC_CORE_H

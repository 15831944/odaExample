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

#ifndef _IFC_FILE_H
#define _IFC_FILE_H

#include "OdPlatformSettings.h"

#define STL_USING_MAP
#include "OdaSTL.h"

#include "daiStepFile.h"

#include "IfcCore.h"
#include "IfcModel.h"
#include "IfcEntity.h"
#include "IfcModelContext.h"
#include "IfcUnitConverter.h"
#include "IfcGeomModule.h"

class OdIfcHostAppServices;
class OdIfcEntResolver;

/** \details
A class that implements working with an IFC file header and data sections (header and model), 
takes responsibility for the geometry creation and visualization, higher-level features like the access to unit conversions and mapping IfcGuid - OdDAIObjectId.
*/
class IFCCORE_EXPORT OdIfcFile : public OdStepFile
{
public:

  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdIfcFile);
  //DOM-IGNORE-END

  /** \details
  Creates a new IFC file object with default parameters.
  */
  OdIfcFile();

  /** \details 
  Destroys the IFC file object.
  */
  ~OdIfcFile();

  /** \details
  Retrieves the application services object that is associated with the IFC file object.
  \returns Returns a raw pointer to the <link OdIfcHostAppServices, OdIfcHostAppServices> object associated with the file object.
  */
  OdIfcHostAppServices* getAppServices() const;
  
  /** \details
  Sets a new application services object with the IFC file object.
  \param svcs [in] A raw pointer to the <link OdIfcHostAppServices, OdIfcHostAppServices> object to be assigned with the file.
  */
  void setAppServices(OdIfcHostAppServices* svcs);

  /** \details
  Initializes the IFC file object with a specified schema.
  \param schema [in] A schema identifier.
  \returns eOk if the file was successfully initialized; otherwise, the method returns an appropriate error code.
  \remarks 
  If the schema parameter equals the kScmUndefined value, the IFC file object will be created without an underlying <link OdDAI::Model, OdDAI::Model> object.
  */
  OdResult initialize(IfcSchema schema);

  /** \details
  Retrieves the IFC model's root entity.
  \returns The identifier of the root entity of the model.
  \remarks
  Each valid IFC file must have exactly one root entity.
  */
  OdDAIObjectId getProjectId() const;

  /** \details
  Retrieves entity database id by IFC GUID.
  \param ifcGUID [in] An IFC GUID identifier of entity.
  \returns An <link OdDAIObjectId, identifier> of the entity.
  */
  OdDAIObjectId getEntityId(const OdIfcGUID &ifcGUID) const;

  /** \details
  Retrieves the current model context of the file object.
  \returns An instance of the <link OdIfc::OdIfcModelContext, OdIfcModelContext> class.
  */
  OdIfcModelContext getContext() const;

  /** \details
  Sets a new model context for the IFC file object.
  \param context [in] An instance of the <link OdIfc::OdIfcModelContext, OdIfcModelContext> class to be set as the model context object.
  */
  void setContext(const OdIfcModelContext& context);

  /** \details
  Sets a new active view for the IFC file's content.
  \param pActiveView [in] A raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsView.html">OdGsView</exref> object.
  */
  void setActiveView(OdGsView *pActiveView);

  /** \details
  Retrieves the current active view of the IFC file object.
  \returns Returns a raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsView.html">OdGsView</exref> object that represents the currently active view.
  */
  OdGsView *getActiveView() const;

  /** \details
  Composes geometry of entities in the IFC model using the assigned resolver object.
  \sa
  <link OdIfc::OdIfcModel::setResolver@OdIfcEntResolver *, setResolver()> method.
  */
  OdResult composeEntities();

  /** \details
  Unresolve entities in the IFC model.
  \returns eOk if the unresolve was successful; otherwise, the method returns an appropriate error code.
  */
  OdResult unresolveEntities();

  /** \details
  Sets geometrical context selection to build a geometrical representation for selected geometrical contexts.
  Only selected contexts will be composed and drawn.
  \param contexts [in] A set of <link OdDAIObjectId, identifiers of SDAI objects>, which represent the context selection.
  \returns eOk if the new context selection was successfully set; otherwise, the method returns an appropriate error code.
  */
  OdResult setContextSelection(const OdDAIObjectIds &contexts);

  /** \details
  Determines whether an instance of the IfcGeometricRepresentationContext class is selected to build the geometry.
  \param idCtx [in] Object ID of geometric context to test.
  \returns true if an IfcGeometricRepresentationContext object is selected; otherwise, the method returns false.
  */
  bool getContextSelected(const OdDAIObjectId &idCtx) const;

  /** \details
  Retrieves the current geometrical extents of the model.
  \param extents [out] A placeholder for the current geometry extents object to be returned to a calling subroutine.
  \returns eOk if the current extents were successfully returned; otherwise, the method returns an appropriate error code.
  \remarks
  The method returns the model extents only if the model was created by calling the setGeomResource() method.
  The method accepts an instance of the OdGeExtents3d class, fills it with the data about the model's extents and
  returns it to a calling subroutine.
  */
  OdResult getGeomExtents(OdGeExtents3d& extents) const;

  /** \details
  Retrieves the current model's unit converter.
  \returns An instance of the <link OdIfc::OdIfcUnitConverter, OdIfcUnitConverter> class that represents the current model's unit converter.
  */
  OdIfcUnitConverterPtr getUnitConverter();

  /** \details
  Performs an attempt to compose an entity using the specified resolver object.
  \param id [in] An <link OdDAIObjectId, identifier> of an object to compose.
  \returns A smart pointer to the entity with the attached compound object.
  */
  OdIfc::OdIfcEntityPtr get(const OdDAIObjectId &id) const;

  /** \details
  Performs an attempt to compose entities using the specified resolver object.
  \param ids [in] An array of <link OdDAIObjectId, identifiers> of objects to compose.
  \returns eOk if the compose operation was successful; otherwise the method returns an appropriate error code.
  */
  OdResult get(const OdDAIObjectIds &ids) const;

//DOM-IGNORE-BEGIN

  /** \details 
  Sets a new Gs node cache for the drawable.
  \param pGsNode [in] A raw pointer to an <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object.
  */
  virtual void setGsNode(OdGsCache* pGsNode)
  {
    m_gsNode = pGsNode;
  };

  /** \details
  Retrieves the current Gs node object of the entity.
  \returns Returns a raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object associated with the entity.
  */
  virtual OdGsCache* gsNode() const
  {
    return m_gsNode;
  };

  /** \details
  Sets convertible unit from current <OdDAI::Model, Model> class.
  \returns eOk if initialization operation was successful; otherwise the method returns an appropriate error code.
  */
  OdResult initializeUnitConverter();

  using OdStepFile::initialize;

protected:

  /** \details
  Method is called just after file reading has ended, it initializes units converter for loaded model.
  \returns eOk if operation successfully done; otherwise, the method returns an appropriate error code.
  */
  virtual OdResult onReadFileEnd() override;

  /** \details
  Checks if schema with identifier provided is supported by OdIfcFile.
  \param schemaIdentifier [in] A string that contains the schema identifier.
  \returns true if schema is supported by OdIfcFile instance; otherwise returns false.
  \remarks Schema identifier may be empty, or must contain IFC letters.
  */
  virtual OdResult checkSchema(const OdAnsiString &schemaIdentifier) const override;

  /** \details
  Checks if repository contains single model based on IFC schema.
  \param repo [in] A raw pointer to the repository object to be attached to the file object.
  \returns true if repository can be attached to OdIfcFile instance; otherwise returns false.
  */
  virtual OdResult checkRepo(const OdDAI::Repository* repo) const override;


private:

  virtual const char* defaultRepoName() override;

  OdResult setGeomResource();

  /** \details
  Updates collection of IFC GUID entitiy identifiers.
  \returns Returns eOk if the update was successfull; otherwise, the method returns an appropriate error code.
  */
  OdResult collectEntityIds() const;

  OdGsCache *m_gsNode = nullptr;
  OdGsView *m_ActiveView = nullptr;
  OdDAIObjectIds m_selContexts;
  OdIfcUnitConverterPtr m_pConverter;
  OdIfcModelContext m_context;
  OdIfc::OdIfcGeomModulePtr m_pGeom;
  OdIfcEntResolver *m_pEntResolver = nullptr;
  mutable OdDAIObjectId m_ifcProjectId;
  mutable std::map<OdIfcGUID, OdDAIObjectId> m_ifcEntities;

//DOM-IGNORE-END    
};
  
/** \details 
A data type that represents a smart pointer to an <link OdIfcFile, OdIfcFile> object.
*/
typedef OdSmartPtr<OdIfcFile> OdIfcFilePtr;

namespace OdIfc {
  class OdIfcCompound;
  class OdIfcEntity;
}

/** \details
An abstract class that provides an interface for the model's entity resolving functionality.
An entity resolver resolves the underlying application instance data into the corresponding compound object (in most cases) that can later be used and vectorized
or into other objects such as points, matrices, vectors, etc.
\sa
<link ifc_object_model, IFC Object Model>
*/
class IFCCORE_EXPORT OdIfcEntResolver
{
  //DOM-IGNORE-BEGIN
protected:

  OdIfcFile *m_pFile;

  OdArray<OdIfc::OdIfcEntityType> m_composeTypes;

  void assignEntity(OdIfc::OdIfcCompound* compound, OdIfc::OdIfcEntity *inst);
  //DOM-IGNORE-END

public:

  /** \details
  Creates a new entity resolver with default parameters.
  */
  OdIfcEntResolver()
    : m_pFile(nullptr)
  {}

  /** \details
  Destroys the entity resolver object.
  */
  virtual ~OdIfcEntResolver() {};

  /** \details
  Sets a new model to the entity resolver object.
  \param model [in] A raw pointer to the model's content object to be set.
  */
  void setFile(OdIfcFile *file) { m_pFile = file; };

  /** \details
  Sets a set of IfcProduct-base entity types for process into resolver. All other
  type branches will be resolved by default. Empty array allows compose for all IfcProducts.
  */
  void setComposeTypes(const OdArray<OdIfc::OdIfcEntityType> &composeTypes) { m_composeTypes = composeTypes; };

  /** \details
  Resolves the model's entity.
  \param inst     [in] A raw pointer to the entity instance to be resolved.
  \returns true if the entity was successfully resolved; otherwise, the method returns false.
  */
  virtual bool resolve(OdIfc::OdIfcEntity* inst) = 0;
};

#endif // _IFC_CORE_H

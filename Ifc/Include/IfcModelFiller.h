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

#ifndef _IFC_MODEL_FILLER_H
#define _IFC_MODEL_FILLER_H

#include "OdPlatformSettings.h"

#include "IfcModel.h"
#include "IfcEntity.h"

class IFCCORE_EXPORT OdIfcModelFiller
{
protected:

  struct EntityDefinitions
  {
    const OdDAI::Entity* IfcAxis2Placement2D;
    const OdDAI::Entity* IfcAxis2Placement3D;
    const OdDAI::Entity* IfcBuilding;
    const OdDAI::Entity* IfcCartesianPoint;
    const OdDAI::Entity* IfcDirection;
    const OdDAI::Entity* IfcOwnerHistory;
    const OdDAI::Entity* IfcProduct;
    const OdDAI::Entity* IfcProject;
    const OdDAI::Entity* IfcRoot;
    const OdDAI::Entity* IfcSite;
    const OdDAI::Entity* IfcSiUnit;
  };
  EntityDefinitions Entity;
  void initEntities();

protected:

  OdIfcModelPtr m_model;

  OdIfcModelFiller(OdDAI::Model *model)
    : m_model(model)
  {
    initEntities();
  }

  OdIfc::OdIfcEntityPtr m_person;
  OdIfc::OdIfcEntityPtr m_ownerHistory;
  OdIfc::OdIfcEntityPtr m_unitAssignment;
  OdIfc::OdIfcEntityPtr m_project;
  OdIfc::OdIfcEntityPtr m_site;

  //
  // Common entities, must not be changed as their purposes are predefined:
  //
  OdDAIObjectId m_dirX;
  OdDAIObjectId m_dirY;
  OdDAIObjectId m_dirZ;
  OdDAIObjectId m_posOrigin;
  OdDAIObjectId m_identity;

  OdDAIObjectId m_dirX2D;
  OdDAIObjectId m_dirY2D;
  OdDAIObjectId m_posOrigin2D;
  OdDAIObjectId m_identity2D;

  /** \details
  Appends shared (commonly used) geometrical entities as directions aling axis etc.
  */
  void appendSharedInstances();

public:

  /** \details
  Virtual destructor.
  */
  virtual ~OdIfcModelFiller() {};

  /** \details
  Retrieves working IFC model.
  \returns Returns smart pointer to IFC model.
  */
  OdIfcModelPtr model() { return m_model; };

  /** details
  Fills an empty model by predefined set of entities.
  \returns Returns a smart pointer to instantiated IfcProject.
  */
  OdIfc::OdIfcEntityPtr createFromScratch(
    const OdString &organizationName,
    const OdString &applicationDeveloperName,
    const OdString &applicationDeveloperDescription,
    const OdString &applicationFullName,
    const OdString &applicationVersion,
    const OdString &applicationIdentifier
  );

  //
  // Common instances accessors
  //
  const OdDAIObjectId& dirX() const { return m_dirX; };
  const OdDAIObjectId& dirY() const  { return m_dirY; };
  const OdDAIObjectId& dirZ() const  { return m_dirZ; };
  const OdDAIObjectId& origin() const { return m_posOrigin; };
  const OdDAIObjectId& identity() const { return m_identity; };
  
  const OdDAIObjectId& dirX2D() const  { return m_dirX2D; };
  const OdDAIObjectId& dirY2D() const { return m_dirY2D; };
  const OdDAIObjectId& origin2D() const { return m_posOrigin2D; };
  const OdDAIObjectId& identity2D() const { return m_identity2D; };

  OdIfc::OdIfcEntityPtr person() { return m_person; };
  OdIfc::OdIfcEntityPtr ownerHistory() { return m_ownerHistory; };
  OdIfc::OdIfcEntityPtr unitAssignment() { return m_unitAssignment; };
  OdIfc::OdIfcEntityPtr project() { return m_project; };
  OdIfc::OdIfcEntityPtr site() { return m_site; };

  OdIfc::OdIfcEntityPtr createSiUnit(const char *unitType, const char *prefix, const char *name, bool append = false);

  /** \details
  Creates an instance of 3D IfcCartesianPoint within a model.
  */
  OdIfc::OdIfcEntityPtr createCartesianPoint(const OdGePoint3d &p);

  /** \details
  Creates an instance of 2D IfcCartesianPoint within a model.
  */
  OdIfc::OdIfcEntityPtr createCartesianPoint(const OdGePoint2d &p);

  /** \details
  Creates an instance of 3D IfcDirection within a model.
  */
  OdIfc::OdIfcEntityPtr createDirection(const OdGeVector3d &v);

  /** \details
  Creates an instance of 2D IfcDirection within a model.
  */
  OdIfc::OdIfcEntityPtr createDirection(const OdGeVector2d &v);

  OdIfc::OdIfcEntityPtr createAxis2Placement3D(const OdGeMatrix3d &m);

  OdIfc::OdIfcEntityPtr createAxis2Placement2D(const OdGeMatrix2d &m);

  friend class OdIfcFile;
};
typedef OdSharedPtr<OdIfcModelFiller> OdIfcModelFillerPtr;

#endif // _IFC_MODEL_FILLER_H

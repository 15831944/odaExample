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

#include "ExIfcModelFiller.h"
#include "IfcEntity.h"

using namespace OdIfc;

ODRX_NO_CONS_DEFINE_MEMBERS(IfcBuilder, OdRxObject);

bool ExIfcModelFiller::appendId(OdIfc::OdIfcEntity* pInst, OdIfc::OdIfcAttribute attr, OdDAIObjectId id)
{
  if (pInst == NULL)
    return false;

  /* TODO: Fill list!!!
  OdDAI::Aggr *aggr = NULL;
  if (pInst->getAttr(attr) >> aggr)
  {
    if (aggr->type() == OdRxValueType::Desc<OdDAIObjectId>::value())
    {
      if (aggr->isNil())
        aggr->createEmpty();
      if (aggr->aggrType() == aggrTypeSet)
      {
        OdDAI::OdDAIObjectIdSet *set = reinterpret_cast<OdDAI::OdDAIObjectIdSet*>(aggr);
        return set->Add(id);
      }
      else
      if (aggr->aggrType() == aggrTypeList)
      {
        OdDAI::OdDAIObjectIdList *list = reinterpret_cast<OdDAI::OdDAIObjectIdList*>(aggr);
        list->createIterator()->addAfterCurrentMember(id);
        return true;
      }
      else
      {
        ODA_ASSERT_ONCE(0 && "Unsupported aggregate type");
      }
    }
  }*/

  OdDAIObjectIds arrIds;
  if (pInst->getAttr(attr) >> arrIds)
  {
    unsigned int ind;
    if (arrIds.find(id, ind))
      return false;
    arrIds.append(id);
    return pInst->putAttr(attr, arrIds);
  }

  return false;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::addRelAggregates(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Relating object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }
    
  if (pRelated->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("EntityInstance isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pRelAggregates = m_model->createEntityInstance("ifcrelaggregates");
  OdIfc::Utils::assignGlobalId(pRelAggregates);
  pRelAggregates->putAttr(kRelatingObject, OdDAIObjectId(pRelating->id()));
  m_model->appendEntityInstance(pRelAggregates);

  if (pRelated->id() == OdDAIObjectId::kNull)
    m_model->appendEntityInstance(pRelated);

  OdDAIObjectIds relatedObjects;
  relatedObjects.push_back(pRelated->id());
  pRelAggregates->putAttr(kRelatedObjects, relatedObjects);

  m_relAggregates[pRelating] = pRelAggregates;

  return pRelAggregates;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::appendRelAggregates(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Relating object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("EntityInstance isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }
  
  OdIfcEntityPtr pRelAggregates = getRelAggregates(pRelating);
  if (pRelAggregates.isNull())
    return addRelAggregates(pRelating, pRelated);

  if (pRelated->id() == OdDAIObjectId::kNull)
    m_model->appendEntityInstance(pRelated);

  OdDAI::Aggr *idsRelated;
  if (pRelAggregates->getAttr(kRelatedObjects) >> idsRelated)
  {
    if (idsRelated->type() == OdRxValueType::Desc<OdDAIObjectId>::value())
    {
      if (idsRelated->aggrType() == OdDAI::aggrTypeSet)
      {
        if (idsRelated->isNil())
          idsRelated->createEmpty();
        OdDAI::OdDAIObjectIdSet *set = reinterpret_cast<OdDAI::OdDAIObjectIdSet*>(idsRelated);
        set->Add(OdDAIObjectId(pRelated->id()));
      }
      else
      {
        ODA_ASSERT_ONCE(0 && "Unsupported aggr type.");
      }
    }
  }

  /* This is also correct but seems slower!
  OdDAIObjectIds idsRelated;
  if (pRelAggregates->getAttr(kRelatedObjects) >> idsRelated)
  {
    idsRelated.append(OdDAIObjectId(pRelated->id()));
    pRelAggregates->putAttr(kRelatedObjects, idsRelated);
  }*/
  return pRelAggregates;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::getRelAggregates(OdIfc::OdIfcEntityPtr pRelating)
{
  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*>::iterator it = m_relAggregates.find(pRelating);
  if (it == m_relAggregates.end())
    return OdIfc::OdIfcEntityPtr();
  return it->second;
}

//RelatedElements : SET [1:?] OF IfcProduct;
//RelatingStructure: IfcSpatialElement;

OdIfc::OdIfcEntityPtr ExIfcModelFiller::getRelContainedInSpatialStructure(OdIfc::OdIfcEntityPtr pRelating)
{
  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*>::iterator it = m_relContainedInSpatialStructure.find(pRelating);
  if (it == m_relContainedInSpatialStructure.end())
    return OdIfc::OdIfcEntityPtr();
  return it->second;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::addRelNests(OdIfc::OdIfcEntityPtr pRelating, const OdDAIObjectIds &related)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Relating object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (related.isEmpty())
  {
    ODA_ASSERT("Related objects is missing.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelating->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("Relating isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr pNests = m_model->createEntityInstance("ifcrelnests");
  OdIfc::Utils::assignGlobalId(pNests);
  pNests->putAttr("relatingobject", OdDAIObjectId(pRelating->id()));
  pNests->putAttr("relatedobjects", related);
  m_model->appendEntityInstance(pNests);

  return pNests;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::addRelNests(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Relating object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated.isNull())
  {
    ODA_ASSERT("Related objects is missing.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelating->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("Relating isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr pRelNests = m_model->createEntityInstance("ifcrelnests");
  OdIfc::Utils::assignGlobalId(pRelNests);
  pRelNests->putAttr("relatingobject", OdDAIObjectId(pRelating->id()));
  m_model->appendEntityInstance(pRelNests);

  if (pRelated->id() == OdDAIObjectId::kNull)
    m_model->appendEntityInstance(pRelated);

  OdDAIObjectIds relatedObjects;
  relatedObjects.push_back(pRelated->id());
  pRelNests->putAttr("relatedobjects", relatedObjects);

  m_relNests[pRelating] = pRelNests;
  return pRelNests;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::appendRelNests(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Relating object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("EntityInstance isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pRelNests = getRelNests(pRelating);
  if (pRelNests.isNull())
    return addRelNests(pRelating, pRelated);

  if (pRelated->id() == OdDAIObjectId::kNull)
    m_model->appendEntityInstance(pRelated);

  OdDAI::Aggr *idsRelated;
  if (pRelNests->getAttr(kRelatedObjects) >> idsRelated)
  {
    if (idsRelated->type() == OdRxValueType::Desc<OdDAIObjectId>::value())
    {
      if (idsRelated->aggrType() == OdDAI::aggrTypeList)
      {
        if (idsRelated->isNil())
          idsRelated->createEmpty();
        OdDAI::OdDAIObjectIdList *list = reinterpret_cast<OdDAI::OdDAIObjectIdList*>(idsRelated);
        list->addByIndex(list->getMemberCount(), OdDAIObjectId(pRelated->id()));
      }
      else
      {
        ODA_ASSERT_ONCE(0 && "Unsupported aggr type.");
      }
    }
  }

  return pRelNests;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::getRelNests(OdIfc::OdIfcEntityPtr pRelating)
{
  auto it = m_relNests.find(pRelating);
  if (it == m_relNests.end())
    return OdIfc::OdIfcEntityPtr();
  return it->second;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::appendRelContainedInSpatialStructure(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelating->isKindOf(kIfcSpatialElement) == false)
  {
    ODA_ASSERT("Relating isn't a kind of kIfcSpatialElement.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated->isKindOf(kIfcProduct) == false)
  {
    ODA_ASSERT("Related isn't a kind of IfcProduct.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pRelContainedInSpatialStructure = getRelContainedInSpatialStructure(pRelating);// getRelAggregates(pRelating);
  if (pRelContainedInSpatialStructure.isNull())
    return addRelContainedInSpatialStructure(pRelating, pRelated);

  if (!pRelated->id())
    m_model->appendEntityInstance(pRelated);

  OdDAIObjectIds idsRelated;
  if (pRelContainedInSpatialStructure->getAttr(kRelatedElements) >> idsRelated)
  {
    idsRelated.append(OdDAIObjectId(pRelated->id()));
    pRelContainedInSpatialStructure->putAttr(kRelatedElements, idsRelated);
  }
  return pRelContainedInSpatialStructure;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::addRelContainedInSpatialStructure(OdIfc::OdIfcEntityPtr pRelating, OdIfc::OdIfcEntityPtr pRelated)
{
  if (pRelating.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (pRelated->isKindOf(kIfcProduct) == false)
  {
    ODA_ASSERT("Related isn't a kind of IfcProduct.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pRelContainedInSpatialStructure = m_model->createEntityInstance("ifcrelcontainedinspatialstructure");
  OdIfc::Utils::assignGlobalId(pRelContainedInSpatialStructure);
  pRelContainedInSpatialStructure->putAttr(kRelatingStructure, OdDAIObjectId(pRelating->id()));
  m_model->appendEntityInstance(pRelContainedInSpatialStructure);

  if (!pRelated->id())
    m_model->appendEntityInstance(pRelated);

  OdDAIObjectIds relatedObjects;
  relatedObjects.push_back(pRelated->id());
  pRelContainedInSpatialStructure->putAttr(kRelatedElements, relatedObjects);

  m_relContainedInSpatialStructure[pRelating] = pRelContainedInSpatialStructure;

  return pRelContainedInSpatialStructure;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::appendRelDefinesByProperties(OdIfc::OdIfcEntityPtr pRelatingPropertyDefinition, OdIfc::OdIfcEntityPtr relatedObjectDefinition)
{
  if (pRelatingPropertyDefinition.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (relatedObjectDefinition.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (relatedObjectDefinition->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("Related isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pRelDefinesByProperties = getRelDefinesByProperties(pRelatingPropertyDefinition);
  if (pRelDefinesByProperties.isNull())
    return addRelDefinesByProperties(pRelatingPropertyDefinition, relatedObjectDefinition);

  m_model->appendEntityInstance(relatedObjectDefinition);

  OdDAIObjectIds idsRelated;
  if (pRelDefinesByProperties->getAttr(kRelatedObjects) >> idsRelated)
  {
    idsRelated.append(OdDAIObjectId(relatedObjectDefinition->id()));
    pRelDefinesByProperties->putAttr(kRelatedObjects, idsRelated);
  }
  return pRelDefinesByProperties;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::addRelDefinesByProperties(OdIfc::OdIfcEntityPtr pRelatingPropertyDefinition, OdIfc::OdIfcEntityPtr relatedObjectDefinition)
{
  if (pRelatingPropertyDefinition.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (relatedObjectDefinition.isNull())
  {
    ODA_ASSERT("Related object is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (relatedObjectDefinition->isKindOf(kIfcObjectDefinition) == false)
  {
    ODA_ASSERT("Related isn't a kind of IfcObjectDefinition.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pRelDefinesByProperties = m_model->createEntityInstance("ifcreldefinesbyproperties");
  OdIfc::Utils::assignGlobalId(pRelDefinesByProperties);
  pRelDefinesByProperties->putAttr(kRelatingPropertyDefinition, OdDAIObjectId(pRelatingPropertyDefinition->id()));
  m_model->appendEntityInstance(pRelDefinesByProperties);

  if (relatedObjectDefinition->id() == NULL)
    m_model->appendEntityInstance(relatedObjectDefinition);

  OdDAIObjectIds relatedObjects;
  relatedObjects.push_back(relatedObjectDefinition->id());
  pRelDefinesByProperties->putAttr(kRelatedObjects, relatedObjects);

  m_relContainedInSpatialStructure[pRelatingPropertyDefinition] = pRelDefinesByProperties;

  return pRelDefinesByProperties;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::getRelDefinesByProperties(OdIfc::OdIfcEntityPtr pRelatingPropertyDefinition)
{
  std::map<OdIfc::OdIfcEntity*, OdIfc::OdIfcEntity*>::iterator it = m_relDefinesByProperties.find(pRelatingPropertyDefinition);
  if (it == m_relDefinesByProperties.end())
    return OdIfc::OdIfcEntityPtr();
  return it->second;
}

OdIfcEntityPtr ExIfcModelFiller::fromScratch(const OdAnsiString &organizationName, const OdAnsiString &applicationIdentifier, const OdArray<OdIfc::OdIfcEntityPtr> &units)
{
  OdAnsiString strVal;
  OdIfcEntityPtr pInst;

  /////////////////////////////////////////////////////////////////////

  m_person = m_model->createEntityInstance("ifcperson");
  m_person->putAttr("identification", OdAnsiString(""));
  OdDAIObjectId idPerson = m_model->appendEntityInstance(m_person);

  pInst = m_model->createEntityInstance("ifcorganization");
  pInst->putAttr(kName, organizationName);
  OdDAIObjectId idOrganization = m_model->appendEntityInstance(pInst);

  pInst = m_model->createEntityInstance("ifcpersonandorganization");
  pInst->putAttr(kThePerson, idPerson);
  pInst->putAttr(kTheOrganization, idOrganization);
  OdDAIObjectId idPersonAndOrganization = m_model->appendEntityInstance(pInst);

  pInst = m_model->createEntityInstance("ifcorganization");
  pInst->putAttr(kName, OdAnsiString("Open Design Alliance"));
  pInst->putAttr(kDescription, OdAnsiString("SDK Development"));
  OdDAIObjectId idApplicationDeveloper = m_model->appendEntityInstance(pInst);

  OdAnsiString applicationPrefix = "Ex";
  OdAnsiString applicationName = applicationIdentifier;
  if (applicationName.mid(0, applicationPrefix.getLength()) == applicationPrefix)
  {
    applicationName = applicationName.mid(applicationPrefix.getLength());
  }
  pInst = m_model->createEntityInstance("ifcapplication");
  pInst->putAttr("applicationdeveloper", idApplicationDeveloper);
  pInst->putAttr("version", OdAnsiString(TD_SHORT_STRING_VER_S));
  pInst->putAttr("applicationfullname", "ODA IFC SDK example for " + applicationName);
  pInst->putAttr("applicationidentifier", applicationIdentifier);
  OdDAIObjectId idApplication = m_model->appendEntityInstance(pInst);

  m_ownerHistory = m_model->createEntityInstance("ifcownerhistory");
  m_ownerHistory->putAttr(kOwningUser, idPersonAndOrganization);
  m_ownerHistory->putAttr(kOwningApplication, idApplication);
  m_ownerHistory->putAttr(kState, OdAnsiString("READWRITE"));
  strVal = "ADDED";
  m_ownerHistory->putAttr(kChangeAction, strVal);
  m_ownerHistory->putAttr(kCreationDate, 0);
  OdDAIObjectId idOwnerHistory = m_model->appendEntityInstance(m_ownerHistory);

  if (!units.isEmpty())
  {
    OdArray<OdRxValue> idsUnits;
    for (OdArray<OdIfc::OdIfcEntityPtr>::const_iterator it = units.begin(), end = units.end();
      it < end; ++it)
    {
      if ((*it)->id() == NULL)
      {
        m_model->appendEntityInstance(*it);
      }
      idsUnits.append(OdDAIObjectId((*it)->id()));
    }

    m_unitAssignment = m_model->createEntityInstance("ifcunitassignment");
    m_model->appendEntityInstance(m_unitAssignment);
    m_unitAssignment->putAttr(OdIfc::kUnits, idsUnits);
  }

  // IFC file must have exactly one IfcProject
  m_project = m_model->createEntityInstance("ifcproject");
  OdIfc::Utils::assignGlobalId(m_project);
  m_project->putAttr(kOwnerHistory, idOwnerHistory);
  if (m_unitAssignment.get())
    m_project->putAttr(kUnitsInContext, OdDAIObjectId(m_unitAssignment->id()));
  OdDAIObjectId idProject = m_model->appendEntityInstance(m_project);

  // Append IfcSite by default
  m_site = m_model->createEntityInstance("ifcsite");
  OdIfc::Utils::assignGlobalId(m_site);
  OdIfc::OdIfcEntityPtr pRelAggr = addRelAggregates(m_project, m_site); // here m_site becomes appended to model and has own OdDAIObjectId

  appendSharedInstances();
  return m_project;
}

OdDAI::ApplicationInstancePtr ExIfcModelFiller::createRooted(const char *typeName, const char *name, bool append)
{
  OdDAI::EntityPtr entity = m_model->underlyingSchema()->find(typeName);
  if (entity.isNull())
  {
    ODA_ASSERT_ONCE("Can not find a type.");
    return OdDAI::ApplicationInstancePtr();
  }

  if (!entity->instantiable())
  {
    ODA_ASSERT_ONCE("Non-instantiable type.");
    return OdDAI::ApplicationInstancePtr();
  }

  if (!Entity.IfcRoot->isSupertypeOf(entity))
  {
    ODA_ASSERT_ONCE("Not a rooted type.");
    return OdDAI::ApplicationInstancePtr();
  }

  OdDAI::ApplicationInstancePtr rooted = m_model->createEntityInstance(typeName);

  if (rooted.isNull())
    return rooted;

  if (append)
    m_model->appendEntityInstance(rooted);

  OdIfc::Utils::assignGlobalId(OdIfc::OdIfcEntity::cast(rooted));
  if (!m_ownerHistory.isNull())
    rooted->putAttr("ownerhistory", OdDAIObjectId(m_ownerHistory->id()));
  if (name)
    rooted->putAttr("name", name);
  return rooted;
}

//ContextIdentifier: OPTIONAL IfcLabel;
//ContextType: OPTIONAL IfcLabel;
//project.RepresentationContexts

OdIfc::OdIfcEntityPtr ExIfcModelFiller::appendGeometricRepresentationContext(const OdAnsiString &contextIdentifier, const OdAnsiString &contextType, int dim, double precision, OdDAIObjectId idWCS, OdDAIObjectId idTrueNorth)
{
  if (m_project.isNull())
  {
    return OdIfc::OdIfcEntityPtr();
  }

  if (idWCS.isNull())
  {
    if (dim == 3)
    {
      idWCS = m_identity;
    }
    else
    if (dim == 2)
    {
      idWCS = m_identity2D;
    }
  }

  OdIfc::OdIfcEntityPtr pGRC = getGeometricRepresentationContext(contextType);
  if (!pGRC.isNull())
    return pGRC;

  pGRC = m_model->createEntityInstance("ifcgeometricrepresentationcontext");
  if (!contextIdentifier.isEmpty())
    pGRC->putAttr(kContextIdentifier, contextIdentifier);
  pGRC->putAttr(kContextType, contextType);
  pGRC->putAttr(kCoordinateSpaceDimension, dim);
  appendId(m_project, kRepresentationContexts, m_model->appendEntityInstance(pGRC));
  if (!OdDAI::Utils::isUnset(precision))
  {
    pGRC->putAttr(kPrecision, precision);
  }
  pGRC->putAttr(kWorldCoordinateSystem, idWCS);
  m_geometricRepresentationContext[contextType] = pGRC;
  return pGRC;
}

/*OdIfc::OdIfcEntityPtr ExIfcModelFiller::createSiUnit(const char *unitType, const char *prefix, const char *name, bool append)
{
  OdIfc::OdIfcEntityPtr inst = m_model->createEntityInstance("ifcsiunit");

  if (inst->putAttr(OdIfc::kUnitType, unitType) == false ||
      (prefix && inst->putAttr(OdIfc::kPrefix, prefix) == false) ||
      inst->putAttr(OdIfc::kName, name) == false)
    return OdIfc::OdIfcEntityPtr();

  if (append)
    m_model->appendEntityInstance(inst);
  return inst;
}*/

OdIfc::OdIfcEntityPtr ExIfcModelFiller::getGeometricRepresentationContext(const OdAnsiString &contextType)
{
  std::map<OdAnsiString, OdIfc::OdIfcEntity*>::iterator it = m_geometricRepresentationContext.find(contextType);
  if (it != m_geometricRepresentationContext.end())
    return it->second;
  return OdIfc::OdIfcEntityPtr();
}

IfcRepresentationBuilderPtr ExIfcModelFiller::createRepresentationBuilder(OdIfc::OdIfcEntityPtr pInst)
{
  if (pInst.isNull())
  {
    return IfcRepresentationBuilderPtr();
  }
  if (!pInst->isKindOf("ifcproduct"))
  {
    return IfcRepresentationBuilderPtr();
  }

  IfcRepresentationBuilderPtr res = IfcRepresentationBuilder::createObject(this, pInst);
  return res;
}

IfcBridgeBuilderPtr ExIfcModelFiller::appendBridge(const OdAnsiString &name, IfcBridgeBuilder::Type type)
{
  const OdDAI::Entity *pIfcBridge = m_model->getEntityDefinition("ifcbridge");
  if (pIfcBridge == NULL)
  {
    ODA_ASSERT("IfcBridge isn't supported by model schema.");
    return IfcBridgeBuilderPtr();
  }

  if (m_project.isNull() || m_site.isNull())
  {
    ODA_ASSERT("Not enough topology to create Bridge builder.");
    return IfcBridgeBuilderPtr();
  }

  IfcBridgeBuilderPtr res = IfcBridgeBuilder::createObject(this, name, type);
  res->appendIfcBridge();
  return res;
}

IfcAlignmentBuilderPtr ExIfcModelFiller::appendAlignment(const OdAnsiString &name)
{
  const OdDAI::EntityPtr ifcAlignment = m_model->getEntityDefinition("ifcalignment");
  if (ifcAlignment.get() == NULL)
  {
    ODA_ASSERT("IfcAlignment isn't supported by model schema.");
    return IfcAlignmentBuilderPtr();
  }

  if (m_project.isNull() || m_site.isNull())
  {
    ODA_ASSERT("Not enough topology to create Bridge builder.");
    return IfcAlignmentBuilderPtr();
  }

  IfcAlignmentBuilderPtr res = IfcAlignmentBuilder::createObject(this, name);
  res->appendIfcAlignment();
  return res;
}

IfcRailwayBuilderPtr ExIfcModelFiller::appendRailway(const OdAnsiString &name)
{
  const OdDAI::EntityPtr ifcRailway = m_model->getEntityDefinition("ifcrailway");
  if (ifcRailway.get() == NULL)
  {
    ODA_ASSERT("ifcRailway isn't supported by model schema.");
    return IfcRailwayBuilderPtr();
  }

  if (m_project.isNull() || m_site.isNull())
  {
    ODA_ASSERT("Not enough topology to create Bridge builder.");
    return IfcRailwayBuilderPtr();
  }

  IfcRailwayBuilderPtr res = IfcRailwayBuilder::createObject(this, name);
  res->appendIfcRailway();
  return res;
}

IfcPropertySetFillerPtr ExIfcModelFiller::createPropertySet(OdIfc::OdIfcEntityPtr objectDefinition)
{
  if (objectDefinition.isNull())
  {
    ODA_ASSERT("Object definition is null.");
    return IfcPropertySetFillerPtr();
  }
  if (objectDefinition->owningModel() != m_model)
  {
    ODA_ASSERT("Object definition isn in underlying model of filer.");
    return IfcPropertySetFillerPtr();
  }

  IfcPropertySetFillerPtr propertySetFiller = IfcPropertySetFiller::createObject(this, objectDefinition);
  return propertySetFiller;
}

IfcQuantitySetFillerPtr ExIfcModelFiller::createQuantitySet(OdIfc::OdIfcEntityPtr objectDefinition)
{
  if (objectDefinition.isNull())
  {
    ODA_ASSERT("Object definition is null.");
    return IfcQuantitySetFillerPtr();
  }
  if (objectDefinition->owningModel() != m_model)
  {
    ODA_ASSERT("Object definition isn in underlying model of filer.");
    return IfcQuantitySetFillerPtr();
  }

  IfcQuantitySetFillerPtr quantitySetFiller = IfcQuantitySetFiller::createObject(this, objectDefinition);
  return quantitySetFiller;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createCartesianPoint3D(const OdGePoint3d &p)
{
  OdIfc::OdIfcEntityPtr cartesianPoint = m_model->createEntityInstance(Entity.IfcCartesianPoint);

  OdArray<double> coordsOrigin(3);
  coordsOrigin.assign(&p.x, (&p.z) + 1);
  cartesianPoint->putAttr(kCoordinates, coordsOrigin);
  OdDAIObjectId idCartesianPoint = m_model->appendEntityInstance(cartesianPoint);
  return cartesianPoint;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createCartesianPoint2D(const OdGePoint2d &p)
{
  OdIfc::OdIfcEntityPtr cartesianPoint = m_model->createEntityInstance("ifccartesianpoint");

  OdArray<double> coordsOrigin(2);
  coordsOrigin.assign(&p.x, (&p.y) + 1);
  cartesianPoint->putAttr(kCoordinates, coordsOrigin);
  OdDAIObjectId idCartesianPoint = m_model->appendEntityInstance(cartesianPoint);
  return cartesianPoint;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createDirection2D(const OdGeVector2d& d)
{
  OdIfc::OdIfcEntityPtr direction = m_model->createEntityInstance("ifcdirection");

  OdArray<double> coordsOrigin(2);
  coordsOrigin.append(d.x);
  coordsOrigin.append(d.y);
  direction->putAttr(kDirectionRatios, coordsOrigin);
  OdDAIObjectId idCartesianPoint = m_model->appendEntityInstance(direction);
  return direction;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createDirection3D(const OdGeVector3d &d)
{
  OdIfc::OdIfcEntityPtr direction = m_model->createEntityInstance("ifcdirection");

  OdArray<double> coordsOrigin(3);
  coordsOrigin.assign(&d.x, (&d.z) + 1);
  direction->putAttr(kDirectionRatios, coordsOrigin);
  OdDAIObjectId idCartesianPoint = m_model->appendEntityInstance(direction);
  return direction;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createVector(OdIfc::OdIfcEntityPtr pDirection, double magnitude)
{
  OdIfc::OdIfcEntityPtr vector = m_model->createEntityInstance("ifcvector");
  vector->putAttr(kOrientation, OdDAIObjectId(pDirection->id()));
  vector->putAttr(kMagnitude, magnitude);
  OdDAIObjectId idVector = m_model->appendEntityInstance(vector);
  return vector;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createLocalPlacement(OdIfc::OdIfcEntityPtr placementRelTo, OdIfc::OdIfcEntityPtr relativePlacement)
{
  if (relativePlacement.isNull())
  {
    ODA_ASSERT("Relative placement is NULL.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr localPlacement = m_model->createEntityInstance("ifclocalplacement");
  if (!placementRelTo.isNull())
    localPlacement->putAttr("placementrelto", OdDAIObjectId(placementRelTo->id()));
  localPlacement->putAttr("relativeplacement", OdDAIObjectId(relativePlacement->id()));
  m_model->appendEntityInstance(localPlacement);
  return localPlacement;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createSurfaceStyle(const OdAnsiString &name, const OdCmEntityColor &color)
{
  if (name.isEmpty())
  {
    ODA_ASSERT("Empty surface style name.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (!findSurfaceStyle(name).isNull())
  {
    ODA_ASSERT("Surface style with this name is already exists.");
    return OdIfc::OdIfcEntityPtr();
  }

  // Colour RGB
  double r = color.red() / 255.;
  double g = color.green() / 255.;
  double b = color.blue() / 255.;

  OdIfc::OdIfcEntityPtr pColourRGBInst = m_model->createEntityInstance("ifccolourrgb");
  pColourRGBInst->putAttr("red", r);
  pColourRGBInst->putAttr("green", g);
  pColourRGBInst->putAttr("blue", b);
  OdDAIObjectId idColourRGB = m_model->appendEntityInstance(pColourRGBInst);

  // Surface style rendering
  OdIfc::OdIfcEntityPtr pSSRInst = m_model->createEntityInstance("ifcsurfacestylerendering");
  pSSRInst->putAttr("surfacecolour", idColourRGB);
  pSSRInst->putAttr("reflectancemethod", OdAnsiString("NOTDEFINED"));
  m_model->appendEntityInstance(pSSRInst);

  // Surface style
  OdIfc::OdIfcEntityPtr pInst = m_model->createEntityInstance("ifcsurfacestyle");
  pInst->putAttr("name", name);
  pInst->putAttr("side", OdAnsiString("POSITIVE"));
  OdArray<OdRxValue> surfaceStyles;
  surfaceStyles.append(OdDAIObjectId(pSSRInst->id()));
  pInst->putAttr("styles", surfaceStyles);

  m_model->appendEntityInstance(pInst);
  m_surfaceStyles[name] = pInst;
  return pInst;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::findSurfaceStyle(const OdAnsiString &name)
{
  std::map<OdAnsiString, OdIfc::OdIfcEntity*>::iterator it = m_surfaceStyles.find(name);
  if (it == m_surfaceStyles.end())
  {
    return OdIfc::OdIfcEntityPtr();
  }
  return it->second;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createStyledItem(OdIfc::OdIfcEntityPtr item, OdIfc::OdIfcEntityPtr style)
{
  if (item.isNull())
  {
    ODA_ASSERT_ONCE(0 && "Item is null.")
    return OdIfc::OdIfcEntityPtr();
  }
  if (item->id() == nullptr)
  {
    ODA_ASSERT_ONCE(0 && "Item not belongs to model.")
    return OdIfc::OdIfcEntityPtr();
  }
  if (style.isNull())
  {
    ODA_ASSERT_ONCE("Style is null.")
    return OdIfc::OdIfcEntityPtr();
  }
  if (!item->isKindOf(OdIfc::kIfcRepresentationItem))
  {
    ODA_ASSERT_ONCE("Instance type is incorrect for Item.")
    return OdIfc::OdIfcEntityPtr();
  }
  if (!style->isKindOf(OdIfc::kIfcPresentationStyle))
  {
    ODA_ASSERT_ONCE("Instance type is incorrect for Style.")
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr pInst = m_model->createEntityInstance("ifcstyleditem");
  pInst->putAttr("item", OdDAIObjectId(item->id()));
  OdArray<OdRxValue> styles;
  styles.append(OdDAIObjectId(style->id()));
  pInst->putAttr("styles", styles);
  m_model->appendEntityInstance(pInst);
  return pInst;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createShapeRepresentation(const OdAnsiString &contextType, const OdAnsiString &identifier, const OdAnsiString &type)
{
  OdIfc::OdIfcEntityPtr grc = getGeometricRepresentationContext(contextType);
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfc::OdIfcEntityPtr pSR = m_model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));
  pSR->putAttr(OdIfc::kRepresentationIdentifier, identifier);
  pSR->putAttr(OdIfc::kRepresentationType, type);
  return pSR;
}

OdIfc::OdIfcEntityPtr ExIfcModelFiller::createAlignmentSegment(OdDAIObjectId nestedSegmentId)
{
  if (nestedSegmentId.isNull())
  {
    ODA_ASSERT("Nested segment id is missing.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcEntityPtr pSeg = m_model->createEntityInstance("ifcalignmentsegment");
  OdIfc::Utils::assignGlobalId(pSeg);
  pSeg->putAttr("ownerhistory", OdDAIObjectId(ownerHistory()->id()));
  pSeg->putAttr("designparameters", nestedSegmentId);
  m_model->appendEntityInstance(pSeg);

  return pSeg;
}

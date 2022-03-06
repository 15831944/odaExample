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

#ifndef _FILLER_EXTENDER_H
#define _FILLER_EXTENDER_H

#include "ExPrintConsole.h"
#include "IfcCore.h"
#include "IfcEntityTypes.h"
#include "IfcEntity.h"
#include "Ifc2x3/Ifc2x3Entities.h"
#include "Ifc2x3/Ifc2x3SelectTypes.h"
#include "Ifc2x3/Ifc2x3Enum.h"

#include "daiConsts.h"
#include "daiSettings.h"
#include "daiUtils/daiTextEncodeDecode.h"
#include "daiObjectId.h"

#define STL_USING_VECTOR
#include "OdaSTL.h"

namespace OdIfc
{
  namespace Utils
  {

    /*template<class EntityType, OdIfcEntityType entityType>
    inline OdSmartPtr<EntityType> CreateEntity(OdIfcModelPtr model)
    {
      OdSmartPtr<EntityType> entity = model->createEntityInstance(entityType);
      if (entity.isNull()) { throw OdError(eNullEntityPointer); }

      OdDAIObjectId oid = model->appendEntityInstance(entity);
      if (oid.isNull()) { throw OdError(eBrokenHandle); }

      if (entity->isKindOf(kIfcRoot))
        assignGlobalId(entity);

      return entity;
    }*/

    template<class EntityType>
    inline OdSmartPtr<EntityType> CreateEntity(OdIfcModel *model)
    {
      OdSmartPtr<EntityType> inst = EntityType::createObject(model);
      if (inst.isNull()) { throw OdError(eNullEntityPointer); }

      if (inst->isKindOf(kIfcRoot))
        assignGlobalId(inst);

      return inst;
    }


    OdDAIObjectId  createOwnerHistory(OdIfcModel *model)
    {
      // Use static method createObject from entity instance classes
      OdIfc2x3::IfcPersonPtr personData = CreateEntity<OdIfc2x3::IfcPerson>(model);
      OdIfc2x3::IfcOrganizationPtr organizationData = CreateEntity<OdIfc2x3::IfcOrganization>(model);

      const char applicationName[] = "ODA ExIfcModelFiller";

      organizationData->setName(applicationName);

      OdIfc2x3::IfcPersonAndOrganizationPtr personAndOrganizationData = CreateEntity<OdIfc2x3::IfcPersonAndOrganization>(model);
      personAndOrganizationData->setTheOrganization(organizationData->id());
      personAndOrganizationData->setThePerson(personData->id());

      OdIfc2x3::IfcApplicationPtr applicationData = CreateEntity<OdIfc2x3::IfcApplication>(model);
      applicationData->setApplicationDeveloper(organizationData->id());

      const char applicationVersion[] = TD_SHORT_STRING_VER_S;
      applicationData->setVersion(applicationVersion); // provide version current SDK
      applicationData->setApplicationFullName(applicationName);
      applicationData->setApplicationIdentifier(applicationName);

      OdIfc2x3::IfcOwnerHistoryPtr ownerHistoryData = CreateEntity<OdIfc2x3::IfcOwnerHistory>(model);
      ownerHistoryData->setOwningUser(personAndOrganizationData->id());
      ownerHistoryData->setOwningApplication(applicationData->id());
      ownerHistoryData->setChangeAction(OdIfc2x3::kIfcChangeActionEnum_ADDED);
      ownerHistoryData->setLastModifyingUser(personAndOrganizationData->id());
      ownerHistoryData->setLastModifyingApplication(applicationData->id());
      ownerHistoryData->setCreationDate(0);

      return ownerHistoryData->id();
    }

    OdDAIObjectId  createDirection(OdIfcModel *model, double x, double y, double z = OdDAI::Consts::OdNan)
    {
      OdIfc2x3::IfcDirectionPtr direction = CreateEntity<OdIfc2x3::IfcDirection>(model);

      OdArray<double> arrRatios;
      arrRatios.reserve(OdDAI::Utils::isUnset(z) ? 2 : 3);
      arrRatios.append(x);
      arrRatios.append(y);
      if (!OdDAI::Utils::isUnset(z))
        arrRatios.append(z);
      direction->directionRatios().setArray(arrRatios);

      return direction->id();
    }

    OdDAIObjectId  createCartesianPoint(OdIfcModelPtr model, double x, double y, double z = OdDAI::Consts::OdNan)
    {
      OdIfc2x3::IfcCartesianPointPtr cartesianPoint = CreateEntity<OdIfc2x3::IfcCartesianPoint>(model);

      OdArray<double> arrCoords;
      arrCoords.reserve(OdDAI::Utils::isUnset(z) ? 2 : 3);
      arrCoords.append(x);
      arrCoords.append(y);
      if (!OdDAI::Utils::isUnset(z))
        arrCoords.append(z);
      cartesianPoint->coordinates().setArray(arrCoords);

      return cartesianPoint->id();
    }

    OdDAIObjectId  createAxis2Placement3D(OdIfcModelPtr model,
      const OdDAIObjectId& location,
      const OdDAIObjectId& axis,
      const OdDAIObjectId& direction)
    {
      OdIfc2x3::IfcAxis2Placement3DPtr entityData = CreateEntity<OdIfc2x3::IfcAxis2Placement3D>(model);

      entityData->setAxis(axis); 
      entityData->setRefDirection(direction);
      entityData->setLocation(location); 

      return entityData->id();
    }
    
    OdDAIObjectId  createGeometricRepresentationContext(OdIfcModelPtr model,
      char *contextIdentifier,
      char *contextType,
      OdInt16 dimensionsCount,
      double precision,
      const OdDAIObjectId& coordinateSystem,
      const OdDAIObjectId& trueNorth)
    {
      OdIfc2x3::IfcGeometricRepresentationContextPtr repContextData = CreateEntity<OdIfc2x3::IfcGeometricRepresentationContext>(model);

      OdIfc2x3::IfcAxis2Placement   axis2Placement = repContextData->worldCoordinateSystem();
      axis2Placement.select().setHandle(coordinateSystem);

      repContextData->setContextIdentifier(contextIdentifier);
      repContextData->setContextType(contextType);
      
      repContextData->setTrueNorth(trueNorth);
      repContextData->setPrecision(precision);
      repContextData->setCoordinateSpaceDimension(dimensionsCount);

      return repContextData->id();
    }

    OdDAIObjectId  createDimensionalExponents(OdIfcModelPtr model,
      OdInt32 lengthExponent,
      OdInt32 massExponent,
      OdInt32 timeExponent,
      OdInt32 electricCurrentExponent,
      OdInt32 thermodynamicTemperatureExponent,
      OdInt32 amountOfSubstanceExponent,
      OdInt32 luminousIntensityExponent)
    {
      OdIfc2x3::IfcDimensionalExponentsPtr entityData = CreateEntity<OdIfc2x3::IfcDimensionalExponents>(model);

      entityData->setLengthExponent(lengthExponent);
      entityData->setMassExponent(massExponent);
      entityData->setTimeExponent(timeExponent);
      entityData->setElectricCurrentExponent(electricCurrentExponent);
      entityData->setThermodynamicTemperatureExponent(thermodynamicTemperatureExponent);
      entityData->setAmountOfSubstanceExponent(amountOfSubstanceExponent);
      entityData->setLuminousIntensityExponent(luminousIntensityExponent);


      return entityData->id();
    }

    OdDAIObjectId  createSIUnit(OdIfcModelPtr model,
      OdIfc2x3::IfcUnitEnum  unitType,
      OdIfc2x3::IfcSIPrefix  prefix,
      OdIfc2x3::IfcSIUnitName name,
      const OdDAIObjectId &dimensions)
    {
      OdIfc2x3::IfcSIUnitPtr entityData = CreateEntity<OdIfc2x3::IfcSIUnit>(model);

      entityData->setUnitType(unitType);
      entityData->setPrefix(prefix);
      entityData->setName(name);
      if (dimensions)
      {
        entityData->setDimensions(dimensions);
      }

      return entityData->id();
    }

    OdDAIObjectId  createMeasureWithUnit(OdIfcModelPtr model,
      double angleMeasure,
      const OdDAIObjectId& unit)
    {
      OdIfc2x3::IfcMeasureWithUnitPtr entityData = CreateEntity<OdIfc2x3::IfcMeasureWithUnit>(model);

      OdIfc2x3::IfcUnit unitWrapper = entityData->unitComponent();
      unitWrapper.select().setHandle(unit);

      OdIfc2x3::IfcValue valueComponent = entityData->valueComponent();
      valueComponent.setIfcPlaneAngleMeasure(angleMeasure);

      return entityData->id();
    }


    OdDAIObjectId  createConversionBasedUnit(OdIfcModelPtr model,
      const OdString& name,
      const OdDAIObjectId& conversionFactor,
      const OdDAIObjectId& dimensions,
      const OdIfc2x3::IfcUnitEnum& unitType)
    {
      OdIfc2x3::IfcConversionBasedUnitPtr entityData = CreateEntity<OdIfc2x3::IfcConversionBasedUnit>(model);

      OdAnsiString  encodedName;
      if (!OdDAI::Utils::encodeText(name, encodedName, OdDAI::Utils::CodecType::utf8))
      {
        throw OdError(eSyntaxError);
      }

      entityData->setName(encodedName);
      entityData->setConversionFactor(conversionFactor);
      entityData->setDimensions(dimensions);
      entityData->setUnitType(unitType);

      return entityData->id();
    }


    OdDAIObjectId  createUnitAssignment(OdIfcModelPtr model,
      const OdArray<OdDAIObjectId>& unitsCollection)
    {
      OdIfc2x3::IfcUnitAssignmentPtr entityData = CreateEntity<OdIfc2x3::IfcUnitAssignment>(model);

      OdDAIObjectIds::const_iterator nextUnitHandle = unitsCollection.begin();
      
      OdDAI::Set<OdDAI::Select>&  unitsWrapperCollection = entityData->units();
      if (unitsWrapperCollection.empty())
      {
        unitsWrapperCollection.createEmpty();
      }

      for (; nextUnitHandle != unitsCollection.end(); ++nextUnitHandle)
      {
        auto unitWrapper = OdIfc2x3::IfcUnit::createEmptySelect();
        if (unitWrapper.setHandle(*nextUnitHandle))
          unitsWrapperCollection.Add(unitWrapper);
      }

      return entityData->id();
    }

    OdDAIObjectId  createProject(OdIfcModelPtr model,
      const OdString& longName,
      const OdDAIObjectIds& representationContexts,
      const OdDAIObjectId& unitsInContext,
      const OdDAIObjectId& ownerHistory)
    {
      OdIfc2x3::IfcProjectPtr entityData = CreateEntity<OdIfc2x3::IfcProject>(model);

      OdAnsiString  encodedLongName;

      if (!OdDAI::Utils::encodeText(longName, encodedLongName, OdDAI::Utils::CodecType::utf8))
      {
        throw OdError(eSyntaxError);
      }

      entityData->setLongName(encodedLongName);
      entityData->setUnitsInContext(unitsInContext);
      entityData->representationContexts().setArray(representationContexts);
      entityData->setOwnerHistory(ownerHistory);

      return entityData->id();
    }

    OdDAIObjectId  createLocalPlacement(OdIfcModelPtr model,
      const OdDAIObjectId& axis2PlacementRelative,
      const OdDAIObjectId* pPlacementRelatesTo = NULL)
    {
      OdIfc2x3::IfcLocalPlacementPtr entityData = CreateEntity<OdIfc2x3::IfcLocalPlacement>(model);

      OdIfc2x3::IfcAxis2Placement axisPlacement = entityData->relativePlacement();
      axisPlacement.select().setHandle(axis2PlacementRelative);
      
      if (pPlacementRelatesTo)
      {
        entityData->setPlacementRelTo(*pPlacementRelatesTo);
      }

      return entityData->id();
    }

    OdDAIObjectId  createSite(OdIfcModelPtr model,
      const OdDAIObjectId& objectPlacement,
      const OdDAIObjectId& ownerHistory,
      OdIfc2x3::IfcElementCompositionEnum compositionType)
    {
      OdIfc2x3::IfcSitePtr entityData = CreateEntity<OdIfc2x3::IfcSite>(model);
      
      entityData->setObjectPlacement(objectPlacement);
      entityData->setCompositionType(compositionType);
      entityData->setOwnerHistory(ownerHistory);
      entityData->setName("Site");

      return entityData->id();
    }

    OdDAIObjectId  createRelAggregates(OdIfcModelPtr model,
      const OdDAIObjectId& ownerHistory,
      const OdDAIObjectId& relatingObject,
      const OdDAIObjectIds& relatedObjectCollection)
    {
      OdIfc2x3::IfcRelAggregatesPtr entityData = CreateEntity<OdIfc2x3::IfcRelAggregates>(model);

      entityData->setRelatingObject(relatingObject);
      entityData->relatedObjects().setArray(relatedObjectCollection);
      entityData->setOwnerHistory(ownerHistory);

      return entityData->id();
    }

    OdDAIObjectId  createBuilding(OdIfcModelPtr model,
      const OdDAIObjectId& ownerHistory,
      const OdDAIObjectId& objectPlacement,
      OdIfc2x3::IfcElementCompositionEnum compositionType)
    {
      OdIfc2x3::IfcBuildingPtr entityData = CreateEntity<OdIfc2x3::IfcBuilding>(model);

      entityData->setObjectPlacement(objectPlacement);
      entityData->setCompositionType(compositionType);
      entityData->setOwnerHistory(ownerHistory);

      return entityData->id();
    }

    OdDAIObjectId  createBuildingStorey(OdIfcModelPtr model,
      const OdDAIObjectId& ownerHistory,
      const OdDAIObjectId& objectPlacement,
      OdIfc2x3::IfcElementCompositionEnum compositionType)
    {
      OdIfc2x3::IfcBuildingStoreyPtr entityData = CreateEntity<OdIfc2x3::IfcBuildingStorey>(model);

      entityData->setObjectPlacement(objectPlacement);
      entityData->setCompositionType(compositionType);
      entityData->setOwnerHistory(ownerHistory);

      return entityData->id();
    }

    OdDAIObjectId  createBuildingElementProxy(OdIfcModelPtr model,
      const OdDAIObjectId& ownerHistory,
      const OdDAIObjectId* pLocalPlacement = NULL,
      const OdDAIObjectId* pProductDefinitionShape = NULL)
    {
      OdIfc2x3::IfcBuildingElementProxyPtr entityData = CreateEntity<OdIfc2x3::IfcBuildingElementProxy>(model);

      entityData->setOwnerHistory(ownerHistory);

      if (pLocalPlacement)
      {
        entityData->setObjectPlacement(*pLocalPlacement);
      }

      if (pProductDefinitionShape)
      {
        entityData->setRepresentation(*pProductDefinitionShape);
      }

      return entityData->id();
    }

    OdDAIObjectId  createRelContainedInspatialStructure(OdIfcModelPtr model,
      const OdDAIObjectId& ownerHistory,
      const OdDAIObjectIds& relatedElements,
      const OdDAIObjectId& relatingStructure)
    {
      OdIfc2x3::IfcRelContainedInSpatialStructurePtr entityData = CreateEntity<OdIfc2x3::IfcRelContainedInSpatialStructure>(model);

      entityData->setOwnerHistory(ownerHistory);
      entityData->relatedElements().setArray(relatedElements);
      entityData->setRelatingStructure(relatingStructure);

      return entityData->id();
    }

    OdDAIObjectId  createAxis2Placement2D(OdIfcModelPtr model,
      const OdDAIObjectId& location,
      const OdDAIObjectId& direction)
    {
      OdIfc2x3::IfcAxis2Placement2DPtr entityData = CreateEntity<OdIfc2x3::IfcAxis2Placement2D>(model);

      entityData->setRefDirection(direction);
      entityData->setLocation(location);

      return entityData->id();
    }

    OdDAIObjectId  createZShapeProfileDef(OdIfcModelPtr model,
      OdIfc2x3::IfcProfileTypeEnum profileType,
      const OdDAIObjectId& positionPlacement,
      double depth,
      double flangeWidth,
      double webThickness,
      double flangeThickness,
      const double* filletRadius = NULL, 
      const double* edgeRadius = NULL)
    {
      OdIfc2x3::IfcZShapeProfileDefPtr entityData = CreateEntity<OdIfc2x3::IfcZShapeProfileDef>(model);

      entityData->setPosition(positionPlacement);

      entityData->setProfileType(profileType);
      
      entityData->setDepth(depth);
      entityData->setFlangeWidth(flangeWidth);
      entityData->setWebThickness(webThickness);
      entityData->setFlangeThickness(flangeThickness);

      if (filletRadius)
      {
        entityData->setFilletRadius(*filletRadius);
      }

      if (edgeRadius)
      {
        entityData->setEdgeRadius(*edgeRadius);
      }

      return entityData->id();
    }

    OdDAIObjectId  createIShapeProfileDef(OdIfcModelPtr model,
      OdIfc2x3::IfcProfileTypeEnum profileType,
      const OdDAIObjectId& positionPlacement,
      double depth,
      double flangeWidth,
      double webThickness,
      double flangeThickness,
      const double* filletRadius = NULL)
    {
      OdIfc2x3::IfcIShapeProfileDefPtr entityData = CreateEntity<OdIfc2x3::IfcIShapeProfileDef>(model);

      entityData->setPosition(positionPlacement);

      entityData->setProfileType(profileType);

      entityData->setOverallDepth(depth);
      entityData->setOverallWidth(flangeWidth);
      entityData->setWebThickness(webThickness);
      entityData->setFlangeThickness(flangeThickness);

      if (filletRadius)
      {
        entityData->setFilletRadius(*filletRadius);
      }


      return entityData->id();
    }



    OdDAIObjectId  createExtrudedAreaSolid(OdIfcModelPtr model,
      const OdDAIObjectId& shape,
      const OdDAIObjectId& placementPoint,
      const OdDAIObjectId& direction,
      double depth)
    {
      OdIfc2x3::IfcExtrudedAreaSolidPtr entityData = CreateEntity<OdIfc2x3::IfcExtrudedAreaSolid>(model);

      entityData->setDepth(depth);
      entityData->setExtrudedDirection(direction);
      entityData->setSweptArea(shape);
      entityData->setPosition(placementPoint);

      return entityData->id();
    }

    OdDAIObjectId  createShapeRepresentation(OdIfcModelPtr model,
      const OdDAIObjectId& context,
      const char *representationIdentifier,
      const char *representationType,
      const OdArray<OdDAIObjectId>& representationItemsCollection)
    {
      OdIfc2x3::IfcShapeRepresentationPtr entityData = CreateEntity<OdIfc2x3::IfcShapeRepresentation>(model);

      entityData->setContextOfItems(context);
      entityData->setRepresentationIdentifier(representationIdentifier);
      entityData->setRepresentationType(representationType);
      entityData->items().setArray(representationItemsCollection);

      return entityData->id();
    }

    OdDAIObjectId  createProductDefinitionShape(OdIfcModelPtr model,
      const OdArray<OdDAIObjectId>& represntationCollection)
    {
      OdIfc2x3::IfcProductDefinitionShapePtr entityData = CreateEntity<OdIfc2x3::IfcProductDefinitionShape>(model);

      entityData->representations().setArray(represntationCollection);

      return entityData->id();
    }

  }

  namespace Utils 
  {
    template<class TTarget, class TParam>
    class ParamPostSetter
    {
    public:
      ParamPostSetter(OdIfcModelPtr model, const OdDAIObjectId& targetHandle)
        : m_targetHandle(targetHandle)
        , m_wasSettled(false)
        , m_model(model)
      {
      }

      virtual ~ParamPostSetter() 
      {
        ODA_ASSERT(m_wasSettled);
      }

      void Set(const TParam& paramToSet)
      {
        OdSmartPtr<TTarget> entity = m_targetHandle.openObject();

        ODA_ASSERT(!entity.isNull());
        if (!entity.isNull())
        {
          SetParam(*entity, paramToSet);
          m_wasSettled = true;
        }
      }

    private:
      virtual void SetParam(TTarget& target, const TParam& paramToSet) = 0;

    private:
      OdIfcModelPtr m_model;
      OdDAIObjectId m_targetHandle;
      bool  m_wasSettled;
    };

    template <class TTarget>
    class LocalPlacementPostSetter
      : public ParamPostSetter<TTarget, OdDAIObjectId>
    {
    public:
      LocalPlacementPostSetter(OdIfcModelPtr model, const OdDAIObjectId& targetHandle) : ParamPostSetter<TTarget, OdDAIObjectId>(model, targetHandle) {}

    private:
      virtual void SetParam(TTarget& target, const OdDAIObjectId& paramToSet)
      {
        target.setObjectPlacement(paramToSet);
      }
    };

    template <class TTarget>
    class ProductDefinitionShapeSetter
      : public ParamPostSetter<TTarget, OdDAIObjectId>
    {
    public:
      ProductDefinitionShapeSetter(OdIfcModelPtr model, const OdDAIObjectId& targetHandle) : ParamPostSetter<TTarget, OdDAIObjectId>(model, targetHandle) {}

    private:
      virtual void SetParam(TTarget& target, const OdDAIObjectId& paramToSet)
      {
        target.setRepresentation(paramToSet);
      }
    };


  }
}
#endif

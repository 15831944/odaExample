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


using Teigha.Core;
using ODA.Ifc.IFC2X3;
using ODA.Sdai.sdai;
using ODA.Ifc.IfcCore;
using System;
using System.Reflection;
using System.Linq;

namespace OdIfcExamplesLibMgd
{
  public static class OdExIfcModelHelper
  {
    #region Classes

    public abstract class ParamPostSetter<TTarget, TParam>
      where TTarget : class
      where TParam : class
    {
      OdDAI_Model m_model;
      OdDAIObjectId m_targetHandle;
      //bool m_wasSettled;

      public ParamPostSetter(OdDAI_Model model, OdDAIObjectId targetHandle)
      {
        m_targetHandle = targetHandle;
        //m_wasSettled = false;
        m_model = model;
      }

      public void Set(TParam paramToSet)
      {
        TTarget entity = m_targetHandle.openObject() as TTarget;

        if (entity != null)
        {
          SetParam(entity, paramToSet);
          //m_wasSettled = true;
        }
      }

      protected abstract void SetParam(TTarget target, TParam paramToSet);
    };

    public class LocalPlacementPostSetter<TTarget> : ParamPostSetter<TTarget, OdDAIObjectId>
      where TTarget : OdIfc2x3_IfcProduct
    {
      public LocalPlacementPostSetter(OdDAI_Model model, OdDAIObjectId targetHandle) : base(model, targetHandle) { }

      protected override void SetParam(TTarget target, OdDAIObjectId paramToSet)
      {
        target.setObjectPlacement(paramToSet);
      }
    };

    public class ProductDefinitionShapeSetter<TTarget> : ParamPostSetter<TTarget, OdDAIObjectId>
       where TTarget : OdIfc2x3_IfcProduct
    {
      public ProductDefinitionShapeSetter(OdDAI_Model model, OdDAIObjectId targetHandle) : base(model, targetHandle) { }

      protected override void SetParam(TTarget target, OdDAIObjectId paramToSet)
      {
        target.setRepresentation(paramToSet);
      }
    };

    #endregion

    #region Methods

    public static EntityType CreateEntity<EntityType>(OdDAI_Model model)
          where EntityType : OdIfc_OdIfcEntity
    {
      EntityType inst = CreateObject<EntityType>(model);
      if (inst == null) { throw new OdError(OdResult.eNullEntityPointer); }

      if (inst.isKindOf(OdIfc_OdIfcEntityType.kIfcRoot))
        IfcCore_Globals.OdIfc_Utils_assignGlobalId(inst);

      return inst;
    }

    public static EntityType CreateObject<EntityType>(OdRxObject obj)
      where EntityType : OdIfc_OdIfcEntity
    {
      Type type = typeof(EntityType);
      //"createObject"
      var methods = type.GetMethods(System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.FlattenHierarchy)
        .Where(xMethod => xMethod.Name == "createObject").Where(xMethod => xMethod.GetParameters().Length == 1).ToArray();

      MethodInfo method = methods.First();

      return method.Invoke(null, new object[] { obj }) as EntityType;
    }

    public static OdDAIObjectId createOwnerHistory(OdDAI_Model model)
    {
      // Use static method createObject from entity instance classes
      OdIfc2x3_IfcPerson personData = CreateEntity<OdIfc2x3_IfcPerson>(model);
      OdIfc2x3_IfcOrganization organizationData = CreateEntity<OdIfc2x3_IfcOrganization>(model);

      String applicationName = "ODA ExIfcModelFiller";

      organizationData.setName(applicationName);

      OdIfc2x3_IfcPersonAndOrganization personAndOrganizationData = CreateEntity<OdIfc2x3_IfcPersonAndOrganization>(model);
      personAndOrganizationData.setTheOrganization(new OdDAIObjectId(organizationData.id()));
      personAndOrganizationData.setThePerson(new OdDAIObjectId(personData.id()));

      OdIfc2x3_IfcApplication applicationData = CreateEntity<OdIfc2x3_IfcApplication>(model);
      applicationData.setApplicationDeveloper(new OdDAIObjectId(organizationData.id()));

      String applicationVersion = "Empty"/*TD_SHORT_STRING_VER_S*/;
      applicationData.setVersion(applicationVersion); // provide version current SDK
      applicationData.setApplicationFullName(applicationName);
      applicationData.setApplicationIdentifier(applicationName);

      OdIfc2x3_IfcOwnerHistory ownerHistoryData = CreateEntity<OdIfc2x3_IfcOwnerHistory>(model);
      ownerHistoryData.setOwningUser(new OdDAIObjectId(personAndOrganizationData.id()));
      ownerHistoryData.setOwningApplication(new OdDAIObjectId(applicationData.id()));

      ownerHistoryData.setChangeAction(OdIfc2x3_IfcChangeActionEnum.kIfcChangeActionEnum_ADDED);
      ownerHistoryData.setLastModifyingUser(new OdDAIObjectId(personAndOrganizationData.id()));
      ownerHistoryData.setLastModifyingApplication(new OdDAIObjectId(applicationData.id()));
      ownerHistoryData.setCreationDate(0);

      return new OdDAIObjectId(ownerHistoryData.id());
    }

    public static OdDAIObjectId createDirection(OdDAI_Model model, double x, double y, double z = double.NaN)
    {
      OdIfc2x3_IfcDirection direction = CreateEntity<OdIfc2x3_IfcDirection>(model);

      OdDAI_DoubleList arrRatios = new OdDAI_DoubleList();

      direction.directionRatios().addByIndex(0,x);
      direction.directionRatios().addByIndex(1,y);
      if (z != double.NaN)
        direction.directionRatios().addByIndex(2,z);
  
      /*        
      direction->m_directionRatios.m_Coordinates[0] = x;
      direction->m_directionRatios.m_Coordinates[1] = y;
      direction->m_directionRatios.m_Coordinates[2] = z;
      */

      return new OdDAIObjectId(direction.id());
    }

    public static OdDAIObjectId createCartesianPoint(OdDAI_Model model, double x, double y, double z = double.NaN)
    {
      OdIfc2x3_IfcCartesianPoint cartesianPoint = CreateEntity<OdIfc2x3_IfcCartesianPoint>(model);

      OdArray_double_OdObjectsAllocator arrCoords = new OdArray_double_OdObjectsAllocator();
      cartesianPoint.coordinates().addByIndex(0,x);
      cartesianPoint.coordinates().addByIndex(1,y);
      if (z != double.NaN)
        cartesianPoint.coordinates().addByIndex(2, z);      

      /*cartesianPoint->m_Coordinates[0] = x;
      cartesianPoint->m_Coordinates[1] = y;
      cartesianPoint->m_Coordinates[2] = z;*/

      return new OdDAIObjectId(cartesianPoint.id());
    }

    public static OdDAIObjectId createAxis2Placement3D(OdDAI_Model model, OdDAIObjectId location, OdDAIObjectId axis, OdDAIObjectId direction)
    {
      OdIfc2x3_IfcAxis2Placement3D entityData = CreateEntity<OdIfc2x3_IfcAxis2Placement3D>(model);

      entityData.setAxis(axis);
      entityData.setRefDirection(direction);
      entityData.setLocation(location);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createGeometricRepresentationContext(OdDAI_Model model,
      String contextIdentifier,
      String contextType, int dimensionsCount, double precision, OdDAIObjectId coordinateSystem, OdDAIObjectId trueNorth)
    {
      OdIfc2x3_IfcGeometricRepresentationContext repContextData = CreateEntity<OdIfc2x3_IfcGeometricRepresentationContext>(model);

      OdIfc2x3_IfcAxis2Placement axis2Placement = repContextData.worldCoordinateSystem();
      axis2Placement.select().setHandle(coordinateSystem);

      repContextData.setContextIdentifier(contextIdentifier);
      repContextData.setContextType(contextType);

      repContextData.setTrueNorth(trueNorth);
      repContextData.setPrecision(precision);
      repContextData.setCoordinateSpaceDimension(dimensionsCount);

      return new OdDAIObjectId(repContextData.id());
    }

    public static OdDAIObjectId createDimensionalExponents(OdDAI_Model model,
      Int32 lengthExponent,
      Int32 massExponent,
      Int32 timeExponent,
      Int32 electricCurrentExponent,
      Int32 thermodynamicTemperatureExponent,
      Int32 amountOfSubstanceExponent,
      Int32 luminousIntensityExponent)
    {
      OdIfc2x3_IfcDimensionalExponents entityData = CreateEntity<OdIfc2x3_IfcDimensionalExponents>(model);

      entityData.setLengthExponent(lengthExponent);
      entityData.setMassExponent(massExponent);
      entityData.setTimeExponent(timeExponent);
      entityData.setElectricCurrentExponent(electricCurrentExponent);
      entityData.setThermodynamicTemperatureExponent(thermodynamicTemperatureExponent);
      entityData.setAmountOfSubstanceExponent(amountOfSubstanceExponent);
      entityData.setLuminousIntensityExponent(luminousIntensityExponent);


      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createSIUnit(OdDAI_Model model,
      OdIfc2x3_IfcUnitEnum unitType,
      OdIfc2x3_IfcSIPrefix prefix,
      OdIfc2x3_IfcSIUnitName name,
      OdDAIObjectId dimensions)
    {
      OdIfc2x3_IfcSIUnit entityData = CreateEntity<OdIfc2x3_IfcSIUnit>(model);

      entityData.setUnitType(unitType);
      entityData.setPrefix(prefix);
      entityData.setName(name);
      if (dimensions != null)
      {
        entityData.setDimensions(dimensions);
      }

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createMeasureWithUnit(OdDAI_Model model,
      double angleMeasure,
      OdDAIObjectId unit)
    {
      OdIfc2x3_IfcMeasureWithUnit entityData = CreateEntity<OdIfc2x3_IfcMeasureWithUnit>(model);

      OdIfc2x3_IfcUnit unitWrapper = entityData.unitComponent();
      unitWrapper.select().setHandle(unit);

      OdIfc2x3_IfcValue valueComponent = entityData.valueComponent();
      valueComponent.setIfcPlaneAngleMeasure(angleMeasure);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createProject(OdDAI_Model model,
      string longName,
      OdDAI_OdDAIObjectIdSet representationContexts,
      OdDAIObjectId unitsInContext,
      OdDAIObjectId ownerHistory)
    {
      OdIfc2x3_IfcProject entityData = CreateEntity<OdIfc2x3_IfcProject>(model);

      String encodedLongName = "";

      if (!sdai_Globals.OdDAI_Utils_encodeText(longName, ref encodedLongName, OdDAI_Utils_CodecType.utf8))
      {
        throw new OdError(OdResult.eSyntaxError);
      }

      entityData.setLongName(encodedLongName);
      entityData.setUnitsInContext(unitsInContext);

      entityData.representationContexts().Assign(representationContexts);
      entityData.setOwnerHistory(ownerHistory);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createRelAggregates(OdDAI_Model model,
      OdDAIObjectId ownerHistory,
      OdDAIObjectId relatingObject,
      OdDAI_OdDAIObjectIdSet relatedObjectCollection)
    {
      OdIfc2x3_IfcRelAggregates entityData = CreateEntity<OdIfc2x3_IfcRelAggregates>(model);

      entityData.setRelatingObject(relatingObject);
      entityData.relatedObjects().Assign(relatedObjectCollection);
      entityData.setOwnerHistory(ownerHistory);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createConversionBasedUnit(OdDAI_Model model,
      String name,
      OdDAIObjectId conversionFactor,
      OdDAIObjectId dimensions,
      OdIfc2x3_IfcUnitEnum unitType)
    {
      OdIfc2x3_IfcConversionBasedUnit entityData = CreateEntity<OdIfc2x3_IfcConversionBasedUnit>(model);

      String encodedName = "";
      if (!sdai_Globals.OdDAI_Utils_encodeText(name, ref encodedName, OdDAI_Utils_CodecType.utf8))
      {
        throw new OdError(OdResult.eSyntaxError);
      }

      entityData.setName(encodedName);
      entityData.setConversionFactor(conversionFactor);
      entityData.setDimensions(dimensions);
      entityData.setUnitType(unitType);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createBuilding(OdDAI_Model model,
      OdDAIObjectId ownerHistory,
      OdDAIObjectId objectPlacement,
      OdIfc2x3_IfcElementCompositionEnum compositionType)
    {
      OdIfc2x3_IfcBuilding entityData = CreateEntity<OdIfc2x3_IfcBuilding>(model);

      entityData.setObjectPlacement(objectPlacement);
      entityData.setCompositionType(compositionType);
      entityData.setOwnerHistory(ownerHistory);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createRelContainedInspatialStructure(OdDAI_Model model,
      OdDAIObjectId ownerHistory,
      OdDAI_OdDAIObjectIdSet relatedElements,
      OdDAIObjectId relatingStructure)
    {
      OdIfc2x3_IfcRelContainedInSpatialStructure entityData = CreateEntity<OdIfc2x3_IfcRelContainedInSpatialStructure>(model);

      entityData.setOwnerHistory(ownerHistory);
      entityData.relatedElements().Assign(relatedElements);
      entityData.setRelatingStructure(relatingStructure);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createBuildingStorey(OdDAI_Model model,
      OdDAIObjectId ownerHistory,
      OdDAIObjectId objectPlacement,
      OdIfc2x3_IfcElementCompositionEnum compositionType)
    {
      OdIfc2x3_IfcBuildingStorey entityData = CreateEntity<OdIfc2x3_IfcBuildingStorey>(model);

      entityData.setObjectPlacement(objectPlacement);
      entityData.setCompositionType(compositionType);
      entityData.setOwnerHistory(ownerHistory);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createBuildingElementProxy(OdDAI_Model model,
      OdDAIObjectId ownerHistory,
      OdDAIObjectId pLocalPlacement = null,
      OdDAIObjectId pProductDefinitionShape = null)
    {
      OdIfc2x3_IfcBuildingElementProxy entityData = CreateEntity<OdIfc2x3_IfcBuildingElementProxy>(model);

      entityData.setOwnerHistory(ownerHistory);

      if (pLocalPlacement != null)
      {
        entityData.setObjectPlacement(pLocalPlacement);
      }

      if (pProductDefinitionShape != null)
      {
        entityData.setRepresentation(pProductDefinitionShape);
      }

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createShapeRepresentation(OdDAI_Model model,
      OdDAIObjectId context,
      string representationIdentifier,
      string representationType,
      OdDAI_OdDAIObjectIdSet representationItemsCollection)
    {
      OdIfc2x3_IfcShapeRepresentation entityData = CreateEntity<OdIfc2x3_IfcShapeRepresentation>(model);

      entityData.setContextOfItems(context);
      entityData.setRepresentationIdentifier(representationIdentifier);
      entityData.setRepresentationType(representationType);
      entityData.items().Assign(representationItemsCollection);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createUnitAssignment(OdDAI_Model model,
      OdDAIObjectIds unitsCollection)
    {
      OdIfc2x3_IfcUnitAssignment entityData = CreateEntity<OdIfc2x3_IfcUnitAssignment>(model);

      OdDAI_SelectSet unitsWrapperCollection = entityData.units();

      if(unitsWrapperCollection.empty())
      {
        unitsWrapperCollection.createEmpty();
      }

      foreach (var item in unitsCollection)
      {
        OdDAI_Select unitWrapper = OdIfc2x3_IfcUnit.createEmptySelect();
        if (unitWrapper.setHandle(item))
          unitsWrapperCollection.Add(OdRxValueHelper.rxvalue_create(unitWrapper));
      }

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createLocalPlacement(OdDAI_Model model, OdDAIObjectId axis2PlacementRelative, OdDAIObjectId pPlacementRelatesTo = null)
    {
      OdIfc2x3_IfcLocalPlacement entityData = CreateEntity<OdIfc2x3_IfcLocalPlacement>(model);

      OdIfc2x3_IfcAxis2Placement axisPlacement = entityData.relativePlacement();
      axisPlacement.select().setHandle(axis2PlacementRelative);

      if (pPlacementRelatesTo != null)
      {
        entityData.setPlacementRelTo(pPlacementRelatesTo);
      }

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createSite(OdDAI_Model model, OdDAIObjectId objectPlacement, OdDAIObjectId ownerHistory, OdIfc2x3_IfcElementCompositionEnum compositionType)
    {
      OdIfc2x3_IfcSite entityData = CreateEntity<OdIfc2x3_IfcSite>(model);

      entityData.setObjectPlacement(objectPlacement);
      entityData.setCompositionType(compositionType);
      entityData.setOwnerHistory(ownerHistory);
      entityData.setName("Site");

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createAxis2Placement2D(OdDAI_Model model, OdDAIObjectId location, OdDAIObjectId direction)
    {
      OdIfc2x3_IfcAxis2Placement2D entityData = CreateEntity<OdIfc2x3_IfcAxis2Placement2D>(model);

      entityData.setRefDirection(direction);
      entityData.setLocation(location);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createIShapeProfileDef(OdDAI_Model model,
      OdIfc2x3_IfcProfileTypeEnum profileType,
      OdDAIObjectId positionPlacement,
      double depth,
      double flangeWidth,
      double webThickness,
      double flangeThickness,
      double filletRadius = double.NaN)
    {
      OdIfc2x3_IfcIShapeProfileDef entityData = CreateEntity<OdIfc2x3_IfcIShapeProfileDef>(model);

      entityData.setPosition(positionPlacement);

      entityData.setProfileType(profileType);

      entityData.setOverallDepth(depth);
      entityData.setOverallWidth(flangeWidth);
      entityData.setWebThickness(webThickness);
      entityData.setFlangeThickness(flangeThickness);

      if (filletRadius != double.NaN)
      {
        entityData.setFilletRadius(filletRadius);
      }

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createExtrudedAreaSolid(OdDAI_Model model,
      OdDAIObjectId shape,
      OdDAIObjectId placementPoint,
      OdDAIObjectId direction,
      double depth)
    {
      OdIfc2x3_IfcExtrudedAreaSolid entityData = CreateEntity<OdIfc2x3_IfcExtrudedAreaSolid>(model);

      entityData.setDepth(depth);
      entityData.setExtrudedDirection(direction);
      entityData.setSweptArea(shape);
      entityData.setPosition(placementPoint);

      return new OdDAIObjectId(entityData.id());
    }

    public static OdDAIObjectId createProductDefinitionShape(OdDAI_Model model,
      OdDAI_OdDAIObjectIdList represntationCollection)
    {
      OdIfc2x3_IfcProductDefinitionShape entityData = CreateEntity<OdIfc2x3_IfcProductDefinitionShape>(model);

      entityData.representations().Assign(represntationCollection);

      return new OdDAIObjectId(entityData.id());
    }

    #endregion
  }

}
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

#include "IfcPlaneAngleUnitValidationTask.h"
#include "daiSelect.h"
#include "daiSet.h"
#include "daiAggr.h"
#include "daiEntity.h"

#include "daiValidationCommon.h"

using namespace OdIfc;

const std::map<OdAnsiString, std::set<OdAnsiString> > angleAttrsNames = { 
  {"ifcplaneanglemeasure", {} },
  {"ifcpositiveplaneanglemeasure", {} },
  {"ifcmeasurevalue", {"ifcplaneanglemeasure", "ifcpositiveplaneanglemeasure"}},
  {"ifcorientationselect", {"ifcplaneanglemeasure"}},
  {"ifctrimmingselect", {"ifcparametervalue"}}
};

ODRX_VALIDATION_CONS_DEFINE_MEMBERS(PlaneAngleUnitValidationTask, OdDAI::ModelValidationTask, RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PlaneAngleUnitValidationHealer, OdDAI::ModelValidationHealer, RXIMPL_CONSTR);

OdDAI::Logical PlaneAngleUnitValidationTask::validate(OdDAI::OdBaseModelValidationContext* pCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams)
{
  InvalidObjectIdsValidationParams* invalidInstances = new InvalidObjectIdsValidationParams();
  invalidParams = invalidInstances;

  OdDAI::OdDAIObjectIdSet* ifcProjects = pCtx->pModel->getEntityExtent("IfcProject");
  if (ifcProjects->getMemberCount() >= 1)
  {
    OdDAIObjectId ifcProjectId = ifcProjects->getArray().first();
    OdDAI::ApplicationInstancePtr ifcProject = ifcProjectId.getNested();

    OdRxValue unitsInContextRx = ifcProject->getAttr("unitsincontext");

    OdDAIObjectId unitsInContextId;
    //    OdDAI::Select* unitsInContextSelect;
    unitsInContextRx >> unitsInContextId;
    OdDAI::ApplicationInstancePtr unitsInContext = unitsInContextId.getNested();
    OdRxValue units = unitsInContext->getAttr("units");

    OdDAI::Aggr* pAggr;

    units >> pAggr;

    for (auto it = pAggr->createConstIterator(); it->next();)
    {
      OdDAI::Select* select;
      it->getCurrentMember() >> select;
      OdAnsiString name = select->underlyingTypeName();
      if (select->underlyingTypeName() == "ifcnamedunit")
      {
        OdDAIObjectId namedeId;
        select->getHandle(namedeId);

        OdDAI::ApplicationInstancePtr ifcNamedUnit = namedeId.getNested();
        OdRxValue units = ifcNamedUnit->getAttr("unittype");
        OdDAI::Enum* enumeration;
        units >> enumeration;
        OdAnsiString enumerationElementName(enumeration->getTextValue());
        if (enumerationElementName == "PLANEANGLEUNIT")
          return OdDAI::Logical::True;
      }
    }

    invalidInstances->addData(ifcProjectId);

    if (m_healingEnable)
    {
      auto healer = desc()->getX(OdDAI::ModelValidationHealer::desc());
      if (healer)
      {
        OdDAI::ModelValidationHealerPtr validationHealer = OdDAI::ModelValidationHealer::cast(healer);
        if (!validationHealer.isNull())
        {
          validationHealer->heal(pCtx->pModel, invalidInstances);
        }
      }
    }
  }
  return OdDAI::Logical::False;
}

OdAnsiString PlaneAngleUnitValidationTask::description() const
{
  return "PlaneAngleUnit validation";
}

OdDAI::Logical OdIfc::PlaneAngleUnitValidationHealer::heal(OdDAI::Model* model, OdDAI::ValidationTask::InvalidValidationParamsBase* invalidParams)
{
  const OdDAI::SchemaPtr schema = model->underlyingSchema();
  auto entities = schema->entities();
  std::set<OdAnsiString> entityesForCheck;
  for (auto it = entities->newIterator(); it->next();)
  {
    OdDAI::EntityPtr entity = it->object();

    const OdArray<OdDAI::AttributePtr>& attributes = entity->attributes().getArray();
    for (auto attr : attributes)
    {
      OdAnsiString name;
      if (checkAngleAttribute(attr, name))
      {
        entityesForCheck.insert(entity->name());
        break;
      }
    }
  }

  //find angle attr
  for (auto it = model->newIterator(); !it->done(); it->step())
  {
    OdDAI::ApplicationInstancePtr unitsInContext = it->id().openObject();
    OdAnsiString str = unitsInContext->typeName();
    if (entityesForCheck.find(unitsInContext->typeName()) != entityesForCheck.cend())
    {

      OdDAI::EntityPtr entity = unitsInContext->getInstanceType();

      const OdArray<OdDAI::AttributePtr>& attributes = entity->attributes().getArray();
      for (auto attr : attributes)
      {
        OdAnsiString name;
        if (checkAngleAttribute(attr, name))
        {
          if (!unitsInContext->testAttr(attr->name()))
            continue;
          OdDAI::ExplicitAttributePtr explicitAttr = OdDAI::ExplicitAttribute::cast(attr);

          auto attrName = angleAttrsNames.find(name);
          if (attrName->second.empty())
          {
            if (!explicitAttr->domain()->isAggregationType())
              checkRadianAngleFromDouble(unitsInContext->getAttr(attr->name()));

            OdRxValue angleValues = unitsInContext->getAttr(attr->name());
            OdArray<OdRxValue> angleValueArray;
            angleValues >> angleValueArray;
            for (auto value : angleValueArray)
              if (!checkRadianAngleFromDouble(value))
                break;
          }
          else
          {
            if (!explicitAttr->domain()->isAggregationType())
              checkRadianAngleFromSelect(unitsInContext->getAttr(attr->name()), attrName->second);
            else
            {
              OdRxValue angleValues = unitsInContext->getAttr(attr->name());
              OdArray<OdRxValue> angleValueArray;
              angleValues >> angleValueArray;
              for (auto value : angleValueArray)
                if (!checkRadianAngleFromSelect(value, attrName->second))
                  break;
            }
          }
          if (!isRadianAngle)
            break;
        }
      }
      if (!isRadianAngle)
        break;
    }
  }

//set Angle
  OdDAIObjectId siUnitId;

  OdDAI::ApplicationInstancePtr siUnit = model->createEntityInstance("IfcSIUnit");
  siUnit->putAttr("unittype", OdAnsiString("PLANEANGLEUNIT"));
  siUnit->putAttr("name", OdAnsiString("RADIAN"));

  if (isRadianAngle)
  {
    siUnitId = model->appendEntityInstance(siUnit);
  }
  else
  {
    OdDAI::ApplicationInstancePtr conversionBasedUnit = model->createEntityInstance("IfcConversionBasedUnit");
    OdDAI::ApplicationInstancePtr dimensionalExponents = model->createEntityInstance("IfcDimensionalExponents");
    OdDAI::ApplicationInstancePtr measureWithUnit = model->createEntityInstance("IfcMeasureWithUnit");

    OdDAI::Select* valueComponent;
    measureWithUnit->getAttr("valuecomponent") >> valueComponent;
    valueComponent->underlyingTypeName("IfcPlaneAngleMeasure");
    valueComponent->setDouble(sdaiPI / 180.);

    OdDAI::Select* unitComponent;
    measureWithUnit->getAttr("unitcomponent") >> unitComponent;
    unitComponent->underlyingTypeName("IfcNamedUnit");
    unitComponent->setHandle(model->appendEntityInstance(siUnit));

    dimensionalExponents->putAttr("lengthexponent", 0);
    dimensionalExponents->putAttr("massexponent", 0);
    dimensionalExponents->putAttr("timeexponent", 0);
    dimensionalExponents->putAttr("electriccurrentexponent", 0);
    dimensionalExponents->putAttr("thermodynamictemperatureexponent", 0);
    dimensionalExponents->putAttr("amountofsubstanceexponent", 0);
    dimensionalExponents->putAttr("luminousintensityexponent", 0);

    conversionBasedUnit->putAttr("dimensions", model->appendEntityInstance(dimensionalExponents));
    conversionBasedUnit->putAttr("unittype", OdAnsiString("PLANEANGLEUNIT"));
    conversionBasedUnit->putAttr("name", OdAnsiString("DEGREE"));
    conversionBasedUnit->putAttr("conversionfactor", model->appendEntityInstance(measureWithUnit));

    siUnitId = model->appendEntityInstance(conversionBasedUnit);
  }
  
  OdDAI::OdDAIObjectIdSet* ifcProjects = model->getEntityExtent("IfcProject");
  if (ifcProjects->getMemberCount() >= 1)
  {
    OdDAIObjectId ifcProjectId = ifcProjects->getArray().first();
    OdDAI::ApplicationInstancePtr ifcProject = ifcProjectId.getNested();

    OdRxValue unitsInContextRx = ifcProject->getAttr("unitsincontext");

    OdDAIObjectId unitsInContextId;
    //    OdDAI::Select* unitsInContextSelect;
    unitsInContextRx >> unitsInContextId;
    OdDAI::ApplicationInstancePtr unitsInContext = unitsInContextId.getNested();
    OdRxValue units = unitsInContext->getAttr("units");

    OdDAI::Aggr* aggr;
    units >> aggr;
    if (aggr && !aggr->isOrdered())
    {
      OdDAI::AggrUnordered* aggrUnordered = static_cast<OdDAI::AggrUnordered*>(aggr);
      aggrUnordered->Add(OdRxValue(siUnitId));

      return OdDAI::Logical::True;
    }
  }
  return OdDAI::Logical::False;
}

bool PlaneAngleUnitValidationHealer::checkAngleAttribute(OdDAI::Attribute* attr, OdAnsiString& name)
{
  OdDAI::ExplicitAttributePtr explicitAttr = OdDAI::ExplicitAttribute::cast(attr);
  if (!explicitAttr.isNull())
  {
    OdDAI::BaseTypePtr baseType = explicitAttr->domain();
    while (baseType->isAggregationType())
    {
      baseType = baseType->aggregationType()->elementType();
    }
    if (baseType->isNamedType())
    {
      name = baseType->namedType()->name();
      if (angleAttrsNames.find(name) != angleAttrsNames.cend())
      {
        return true;
      }
    }
  }
  return false;
}

bool OdIfc::PlaneAngleUnitValidationHealer::checkRadianAngleFromDouble(const OdRxValue& angle)
{
  double angleDbl;
  angle >> angleDbl;
  if (abs(angleDbl) > 2 * sdaiPI)
  {
    isRadianAngle = false;
    return false;
  }
  return true;
}

bool OdIfc::PlaneAngleUnitValidationHealer::checkRadianAngleFromSelect(const OdRxValue& angle, const std::set<OdAnsiString>& selectNames)
{
  OdDAI::Select* angleSelect;
  angle >> angleSelect;
  if (selectNames.find(angleSelect->underlyingTypeName()) != selectNames.cend())
  {
    double angleDbl;
    angleSelect->getDouble(angleDbl);
    if (abs(angleDbl) > 2 * sdaiPI)
    {
      isRadianAngle = false;
      return false;
    }
  }
  return true;
}

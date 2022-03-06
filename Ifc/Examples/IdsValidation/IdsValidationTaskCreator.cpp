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

#include "IdsValidationTaskCreator.h"
#include "OdIdsIds.h"
//#include "libxml/xmlsave.h"

using namespace OdIds;

ODRX_CONS_DEFINE_MEMBERS(IdsValidationTaskCreator, OdRxObject, RXIMPL_CONSTR);

namespace {
  void setRestruction(const OdXmlRestriction& restruction, IdsValue& idsValue)
  {
    if (!restruction.base.isEmpty())
    {
      if (restruction.base == "xs:integer")
        idsValue.valueType = IdsValue::kInteger;
      else if (restruction.base == "xs:double" || restruction.base == "xs:float")
        idsValue.valueType = IdsValue::kReal;
      else// if (restruction.base == "xs:string")
        idsValue.valueType = IdsValue::kString;
    }
    if (!restruction.minExclusive.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kMinExclusive, restruction.minExclusive });
    }
    if (!restruction.minInclusive.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kMinInclusive, restruction.minInclusive });
    }
    if (!restruction.maxExclusive.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kMaxExclusive,  restruction.maxExclusive });
    }
    if (!restruction.maxInclusive.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kMaxInclusive, restruction.maxInclusive });
    }
    if (!restruction.totalDigits.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kTotalDigits, restruction.totalDigits });
    }
    if (!restruction.fractionDigits.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kFractionDigits, restruction.fractionDigits });
    }
    if (!restruction.length.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kLength, restruction.length });
    }
    if (!restruction.minLength.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kMinLength, restruction.minLength });
    }
    if (!restruction.maxLength.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kMaxLength, restruction.maxLength });
    }
    if (!restruction.enumeration.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kEnumeration, restruction.enumeration });
    }
    if (restruction.whiteSpace != OdXmlRestriction::UNDEFINED)
    {
      idsValue.value.insert({ IdsValue::kWhiteSpace, (int)restruction.whiteSpace });
    }
    if (!restruction.pattern.isEmpty())
    {
      idsValue.value.insert({ IdsValue::kRegExp, restruction.pattern });
    }
  }

  void getIdsIdsValue(OdIdsIdsValue* xmlValue, IdsValue& idsValue)
  {
    if (!xmlValue)
    {
      ODA_ASSERT(!"NULL xmlValue");
      return;
    }
    if (idsValue.value.size() > 0)
      idsValue.value.clear();

    switch (xmlValue->getChoiceType())
    {
    case OdIdsIdsValue::NONE:
      
      break;
    case OdIdsIdsValue::SIMPLEVALUE:
      idsValue.value.insert({ IdsValue::kNone, xmlValue->getRawvalue() });
      break;
    case OdIdsIdsValue::RESTRICTION:
    {
      OdArray<OdXmlRestriction>* restrictions = xmlValue->getRestriction();
      if (restrictions)
      {
        for (const OdXmlRestriction& restriction : *restrictions)
          setRestruction(restriction, idsValue);
      }
      break;
    }
    default:
      break;
    }
  }

/*  template<class T, xmlNodePtr* (T::* getValue)(), bool (T::* getValueRestriction)(OdXmlRestriction&)>
  void getXMLValue(T* xmlElement, IdsValue& idsValue)
  {
    xmlNodePtr* value = (xmlElement->*getValue)();
    if (value)
    {
      xmlNodePtr node = (*value)->children->next;
      OdXmlRestriction restruction;
      if ((xmlElement->*getValueRestriction)(restruction))
      {
        setRestruction(restruction, idsValue);
      }
      else if (node !=nullptr && (xmlStrcmp(node->name, (const xmlChar*)"simpleValue") == 0))
      {
        idsValue.value.insert({ IdsValue::kNone, OdAnsiString((char*)node->children->content) });
      }
      else
      {
        idsValue.value.insert({ IdsValue::kNone, OdAnsiString((char*)(*value)->children->content) });
      }
    }
  }

  template<class T>
  void getXMLSystem(T xmlElement, IdsValue& idsValue)
  {
    xmlNodePtr* value = xmlElement->getSystem();
    xmlNodePtr node = (*value)->children->next;
    if (value)
    {
      OdXmlRestriction restruction;
      if (xmlElement->getSystemRestriction(restruction))
      {
        setRestruction(restruction, idsValue);
      }
      else if (&node && xmlStrcmp(node->name, (const xmlChar*)"simpleValue") == 0)
      {
        idsValue.value.insert({ IdsValue::kNone, OdAnsiString((char*)node->children->content) });
      }
      else
      {
        idsValue.value.insert({ IdsValue::kNone, OdAnsiString((char*)(*value)->children->content) });
      }
    }
  }
  */
  void setFileInfoData(OdIdsInfo* idsFileInfoXml, OdIds::IdsFileInfoPtr& idsFileInfoData)
  {
    if (!idsFileInfoXml)
      return;
    int size = idsFileInfoXml->getNumberOfChoices();
    if (size > 0)
      idsFileInfoData = new OdIds::IdsFileInfo();
    for (int i = 0; i < size; ++i)
    {
      switch (idsFileInfoXml->getChoiceType(i))
      {
      case OdIdsInfo::NONE:
        break;

      case OdIdsInfo::IFCVERSION:
        idsFileInfoData->insert({ "Version", idsFileInfoXml->getIfcversion(i)->getValue() });
        break;
      case OdIdsInfo::DESCRIPTION:
        idsFileInfoData->insert({ "Description", *idsFileInfoXml->getDescription(i) });
        break;
      case OdIdsInfo::AUTHOR:
        idsFileInfoData->insert({ "Author", idsFileInfoXml->getAuthor(i)->getValue() });
        break;
      case OdIdsInfo::COPYRIGHT:
        idsFileInfoData->insert({ "Copyright", *idsFileInfoXml->getCopyright(i) });
        break;
      case OdIdsInfo::VERSION:
        idsFileInfoData->insert({ "Version", *idsFileInfoXml->getVersion(i) });
        break;
      case OdIdsInfo::DATE:
        idsFileInfoData->insert({ "Date", *idsFileInfoXml->getDate(i) });
        break;
      case OdIdsInfo::PURPOSE:
        idsFileInfoData->insert({ "Purpose", *idsFileInfoXml->getPurpose(i) });
        break;
      case OdIdsInfo::MILESTONE:
        idsFileInfoData->insert({ "Milestone", *idsFileInfoXml->getMilestone(i) });
        break;
      default:
        break;
      }
    }
  }

  template<class T>
  void setValidationOptions(T* xmlStruct, IdsOptions* options)
  {
    //Gets entity data
    OdIdsEntityTypePtr entity = xmlStruct->getEntity();
    if (!entity.isNull())
    {
      options->entity = new IdsEntity();
      OdIdsIdsValue* name = entity->getName();
      OdIdsIdsValue* predefinedType = entity->getPredefinedtype();

      getIdsIdsValue(name, options->entity->name);
      getIdsIdsValue(predefinedType, options->entity->predefinedType);
//      getXMLValue<OdIdsEntityType, &OdIdsEntityType::getName, &OdIdsEntityType::getNameRestriction>(entity.get(), options->entity->name);
//      getXMLValue<OdIdsEntityType, &OdIdsEntityType::getPredefinedtype, &OdIdsEntityType::getPredefinedtypeRestriction>(entity.get(), options->entity->predefinedType);
    }

//Gets classification data
    OdIdsClassificationTypePtr classification = xmlStruct->getClassification();
    if (!classification.isNull())
    {
      options->classification = new IdsClassification();
      //        xmlNodePtr* location = classification->getLocation();

      getIdsIdsValue(classification->getValue(), options->classification->value);
      getIdsIdsValue(classification->getSystem(), options->classification->system);
//      getXMLValue<OdIdsClassificationType, &OdIdsClassificationType::getValue, &OdIdsClassificationType::getValueRestriction>(classification, options->classification->value);
//      getXMLValue<OdIdsClassificationType, &OdIdsClassificationType::getSystem, &OdIdsClassificationType::getSystemRestriction>(classification, options->classification->system);

      OdIdsRequirementsTypeClassificationPtr reqClassification = OdIdsRequirementsTypeClassification::cast(classification);
      if (!reqClassification.isNull())
      {
        if (reqClassification->getInstructions())
          options->classification->instructions = *reqClassification->getInstructions();
        OdIdsUse use;
        if (reqClassification->getUse(use))
        {
          OdAnsiString useValue = use.getValue();
          if (useValue == "optional")
            options->classification->use = kOptional;
        }
      }
    }

    //Gets properties data
    const auto& properties = xmlStruct->getProperty();
    for (auto prop : properties)
    {
      //          for (auto prop : *properties)
      //          {

      IdsProperty idsProperty;
      getIdsIdsValue(prop->getName(), idsProperty.name);
      getIdsIdsValue(prop->getPropertyset(), idsProperty.propertySetName);
      getIdsIdsValue(prop->getValue(), idsProperty.value);
//      getXMLValue<OdIdsPropertyType, &OdIdsPropertyType::getName, &OdIdsPropertyType::getNameRestriction>(prop, idsProperty.name);
//      getXMLValue<OdIdsPropertyType, &OdIdsPropertyType::getPropertyset, &OdIdsPropertyType::getPropertysetRestriction>(prop, idsProperty.propertySetName);
      //          if (propertySet)
      //          {
      //            idsProperty.propertySetName = (char*)(*propertySet)->children->content;
      //          }
//      getXMLValue<OdIdsPropertyType, &OdIdsPropertyType::getValue, &OdIdsPropertyType::getValueRestriction>(prop, idsProperty.value);
      //          if (name)
      //          {
      //            idsProperty.name = (char*)(*name)->children->content;
      //          }
      OdIdsPropertyTypeLocation location;
      if (prop->getLocation(location))
      {
        idsProperty.location = location.getValue();
      }

      OdIdsRequirementsTypePropertyPtr reqProp = OdIdsRequirementsTypeProperty::cast(prop);
      if (!reqProp.isNull())
      {
        if (reqProp->getInstructions())
          idsProperty.instructions = *reqProp->getInstructions();
        OdIdsUse use;
        if (reqProp->getUse(use))
        {
          OdAnsiString useValue = use.getValue();
          if (useValue == "optional")
            idsProperty.use = kOptional;
        }
      }
      options->property.push_back(idsProperty);
      //          }
    }

//Gets material data
    OdIdsMaterialTypePtr material = xmlStruct->getMaterial();
    if (!material.isNull())
    {
      options->material = new IdsMaterial();
      getIdsIdsValue(material->getValue(), options->material->value);
//      getXMLValue<OdIdsMaterialType, &OdIdsMaterialType::getValue, &OdIdsMaterialType::getValueRestriction>(material, options->material->value);
      //          (*value)->re
                //        xmlNodePtr* location = classification->getLocation();

      OdIdsRequirementsTypeMaterialPtr reqMaterial = OdIdsRequirementsTypeMaterial::cast(material);
      if (!reqMaterial.isNull())
      {
        if (reqMaterial->getInstructions())
          options->material->instructions = *reqMaterial->getInstructions();
        OdIdsUse use;
        if (reqMaterial->getUse(use))
        {
          OdAnsiString useValue = use.getValue();
          if (useValue == "optional")
            options->material->use = kOptional;
        }
      }
    }
  }
}

std::list<OdDAI::ValidationTaskPtr> IdsValidationTaskCreator::openIdsFile(OdAnsiString fileName)
{
  xmlDocPtr doc = xmlParseFile(fileName);
  if (!doc)
  {
    ODA_FAIL_M("Can't read IDS file " + fileName);
    return std::list<OdDAI::ValidationTaskPtr>();
  }
  OdIdsIdsPtr ids = OdIdsIds::createObject();
  ids->readXml(doc->children);
/*  xmlDocPtr doc2 = xmlNewDoc(0);
  xmlNodePtr root = xmlNewNode(0, (const xmlChar*)"ids");
  xmlDocSetRootElement(doc2, root);
  ids->writeXml(root);
  xmlSaveCtxtPtr ctx = xmlSaveToFilename("W:/save.xml", 0, 1);
  xmlSaveDoc(ctx, doc2);
  xmlSaveFlush(ctx);
  xmlSaveClose(ctx);
  */

  OdIdsInfo* idsFileInfo = ids->getInfo();
  OdIds::IdsFileInfoPtr idsFileInfoData;

  setFileInfoData(idsFileInfo, idsFileInfoData);

  OdIdsSpecificationTypePtrArray specification = ids->getSpecification();

  std::list<OdDAI::ValidationTaskPtr> createdTasks;

  for (auto it : specification)
  {
    OdSharedPtr<IdsOptions> applicabilityData = new IdsOptions;
    OdSharedPtr<IdsOptions> requirementsData = new IdsOptions;

    OdIdsApplicabilityType* applicability = it->getApplicability();

    setValidationOptions(applicability, applicabilityData);

    OdIdsRequirementsType* requirements = it->getRequirements();

    setValidationOptions(requirements, requirementsData);

    OdSharedPtr<IdsSpecificationOptions> idsSpecOptions = new IdsSpecificationOptions;
    it->getName(idsSpecOptions->name);
    idsSpecOptions->fileInfo = idsFileInfoData;
    OdIdsSpecificationTypeNecessity necessity;
    if (it->getNecessity(necessity))
      idsSpecOptions->necessity = (necessity.getValue() == "required") ? 1 : 0;
    
 //   IdsName += " (" + fileName.right(fileName.getLength() - fileName.reverseFind('/') - 1) + ")";
    if (!applicabilityData->entity.isNull() && !applicabilityData->entity->name.value.empty() && applicabilityData->entity->name.value.find(IdsValue::kNone) != applicabilityData->entity->name.value.cend())
    {
      IdsExtentValidationTaskPtr pExtentTask = IdsExtentValidationTask::createObject((OdAnsiString)applicabilityData->entity->name.value.at(IdsValue::kNone).toString());
      pExtentTask->loadData(idsSpecOptions, applicabilityData, requirementsData);
      createdTasks.push_back(pExtentTask);
    }
    else
    {
      IdsInstanceValidationTaskPtr pInstanceTask = IdsInstanceValidationTask::createObject();
      pInstanceTask->loadData(idsSpecOptions, applicabilityData, requirementsData);
      createdTasks.push_back(pInstanceTask);
    }
  }
  xmlFreeDoc(doc);
  return createdTasks;
}

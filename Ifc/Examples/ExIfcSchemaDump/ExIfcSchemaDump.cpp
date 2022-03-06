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
/************************************************************************/
/* This console application make dump of a IFC file.                    */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/* ExIfcSchemaDump <target dump filename> <schema version>              */
/*                                                                      */
/************************************************************************/

#include "OdaCommon.h"
#include "StaticRxObject.h"

#include "daiHeaderSection.h"
#include "daiHeader/daiHeaderEntities.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

ODGI_EXPORT void odgiInitialize();
ODGI_EXPORT void odgiUninitialize();

#include "IfcExamplesCommon.h"
#include "ExIfcHostAppServices.h"

#include "IfcCore.h"
#include "daiEntity.h"
#include "daiSimpleTypes.h"
#include "daiArrayType.h"
#include "daiBagType.h"
#include "daiListType.h"
#include "daiSetType.h"

#define STL_USING_MAP
#include "OdaSTL.h"

//
// Define module map for statically linked modules:
//
#ifndef _TOOLKIT_IN_DLL_
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
  ODRX_BEGIN_STATIC_MODULE_MAP()                 
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)
  ODRX_END_STATIC_MODULE_MAP()
#endif

FILE* DumpStream;

OdString getBaseTypeName(const OdDAI::BaseTypePtr& baseType);

OdString getSimpleTypeName(const OdDAI::SimpleTypePtr& pSimpleType)
{
  OdString res;
  if (!OdDAI::BinaryType::cast(pSimpleType).isNull())
  {
    OdDAI::BinaryTypePtr pType = OdDAI::BinaryType::cast(pSimpleType);
    return L"BINARY" + (pType->width() != OdDAI::Consts::OdIntUnset ? res.format(L"(%d)", pType->width()) : res) + (pType->fixedWidth() ? L" FIXED" : L"");
  }
  if (!OdDAI::BooleanType::cast(pSimpleType).isNull())
  {
    return L"BOOLEAN";
  }
  if (!OdDAI::IntegerType::cast(pSimpleType).isNull())
  {
    return L"INTEGER";
  }
  if (!OdDAI::LogicalType::cast(pSimpleType).isNull())
  {
    return L"LOGICAL";
  }
  if (!OdDAI::NumberType::cast(pSimpleType).isNull())
  {
    return L"NUMBER";
  }
  if (!OdDAI::RealType::cast(pSimpleType).isNull())
  {
    OdDAI::RealTypePtr pType = OdDAI::RealType::cast(pSimpleType);
    return L"REAL"+(pType->precision() != OdDAI::Consts::OdIntUnset ? res.format(L"(%d)", pType->precision()) : res);
  }
  if (!OdDAI::StringType::cast(pSimpleType).isNull())
  {
    OdDAI::StringTypePtr pType = OdDAI::StringType::cast(pSimpleType);
    return L"STRING" + (pType->width() != OdDAI::Consts::OdIntUnset ? res.format(L"(%d)", pType->width()) : res) + (pType->fixedWidth() ? L" FIXED" : L"");
  }
  if (pSimpleType.isNull())
  {
    return L"UNDEFINED";
  }
  return L"TODO";
}

OdString getBound(const OdDAI::BoundPtr& pBound)
{
  OdString res;
  if (!OdDAI::IntegerBound::cast(pBound).isNull())
  {
    return res.format(L"%d", OdDAI::IntegerBound::cast(pBound)->boundValue());
  }
  return L"?";
}

OdString getAggregationTypeName(const OdDAI::AggregationTypePtr& pAggregationType)
{
  OdString res;
  OdDAI::BoundPtr lowerBound;
  OdDAI::BoundPtr upperBound;
  if (!OdDAI::ArrayType::cast(pAggregationType).isNull())
  {
    OdDAI::ArrayTypePtr pType = OdDAI::ArrayType::cast(pAggregationType);
    lowerBound = pType->lowerBound();
    upperBound = pType->upperBound();
    res = L"ARRAY";
  } 
  else if (!OdDAI::VariableSizeAggregationType::cast(pAggregationType).isNull())
  {
    OdDAI::VariableSizeAggregationTypePtr pVariableSizeAggregationType = OdDAI::VariableSizeAggregationType::cast(pAggregationType);
    lowerBound = pVariableSizeAggregationType->lowerBound();
    upperBound = pVariableSizeAggregationType->upperBound();
    if (!OdDAI::BagType::cast(pVariableSizeAggregationType).isNull())
    {
      res = L"BAG";
    }
    else if (!OdDAI::ListType::cast(pVariableSizeAggregationType).isNull())
    {
      res = L"LIST";
    }
    else if (!OdDAI::SetType::cast(pVariableSizeAggregationType).isNull())
    {
      res = L"SET";
    }    
  }
  else
  {
    return L"UNDEFINED";
  }
  return res + (!lowerBound.isNull() ?
    L" [" + getBound(lowerBound) + L":" + getBound(upperBound) + L"]" : 
    OdString()) + 
    L" OF " + getBaseTypeName(pAggregationType->elementType());
}

void addListElement(const char* elem, bool isFirst, OdString& res, const char* ind = "  ")
{
  res += "\n";
  res += ind;
  if (isFirst == false)
  {
    res += L",";
  }
  else
  {
    res += L"(";
  }
  res += elem;
}

OdString getEnumerationTypeName(const OdDAI::EnumerationTypePtr& pEnumarationType)
{
  OdString res = L"ENUMERATION OF";

  const OdArray<OdAnsiString> elements = pEnumarationType->elements().getArray();
  for (const auto &it : elements)
  {
    addListElement(it.c_str(), &it == &elements.at(0), res);
  }
  res += L")";
  return res;
}

OdString getSelectTypeName(const OdDAI::SelectTypePtr& pSelectType)
{
  OdString res = L"SELECT";
  for (OdDAI::NamedTypeSet::const_iterator it = pSelectType->selections().begin(), end = pSelectType->selections().end(); it != end; it++)
  {
    addListElement((*it)->originalName(), it == pSelectType->selections().begin(), res);
  }
  res += L")";
  return res;
}

OdString getConstructedTypeName(const OdDAI::ConstructedTypePtr& pConstructedType)
{
  if (pConstructedType->isEnumerationType())
  {
    return getEnumerationTypeName(pConstructedType->enumerationType());
  }
  else if (pConstructedType->isSelectType())
  {
    return getSelectTypeName(pConstructedType->selectType());
  }
  return L"UNDEFINED";
}

OdString getDefinedTypeName(const OdDAI::DefinedTypePtr& pDefinedType)
{
  if (pDefinedType->domain()->isSimpleType())
  {
    return getSimpleTypeName(pDefinedType->domain()->simpleType());
  }
  else if (pDefinedType->domain()->isAggregationType())
  {
    return getAggregationTypeName(pDefinedType->domain()->aggregationType());
  }
  else if (pDefinedType->domain()->isDefinedType())
  {
    return pDefinedType->domain()->definedType()->originalName();
  }
  else if (pDefinedType->domain()->isConstructedType())
  {
    return getConstructedTypeName(pDefinedType->domain()->constructedType());
  }
  return L"UNDEFINED";
}

OdString getBaseTypeName(const OdDAI::BaseTypePtr& baseType)
{
  if (baseType->isSimpleType())
  {
    return getSimpleTypeName(baseType->simpleType());
  }
  if (baseType->isNamedType())
  {
    return baseType->namedType()->originalName();
  }
  if (baseType->isAggregationType())
  {
    return getAggregationTypeName(baseType->aggregationType());
  }
  return L"UNDEFINED";
}

void dumpTypes(const OdDAI::DefinedTypeSet& types)
{
  for (OdUInt32 id = 0; id < types->numEntries(); id++)
  {
    OdDAI::DefinedTypePtr pDefinedType = types->getAt(types->keyAt(id));
    if (pDefinedType->domain()->isSimpleType())
    {
      if (pDefinedType->originalName() == "BOOLEAN" ||
        pDefinedType->originalName() == "LOGICAL" ||
        pDefinedType->originalName() == "REAL" ||
        pDefinedType->originalName() == "NUMBER" ||
        pDefinedType->originalName() == "INTEGER" ||
        pDefinedType->originalName() == "STRING" ||
        pDefinedType->originalName() == "BINARY")
      continue;
    }
    fwprintf(DumpStream, L"TYPE %hs = %s;\n", pDefinedType->originalName().c_str(), getDefinedTypeName(pDefinedType).c_str());
    fwprintf(DumpStream, L"END_TYPE;\n\n");
  }
}

void collectSubtypes(const OdDAI::EntitySet& entities, std::map<OdString, std::list<OdDAI::Entity*> >& subtypes)
{
  for (OdUInt32 id = 0; id < entities->numEntries(); id++)
  {
    OdDAI::EntityPtr pEntity = entities->getAt(entities->keyAt(id));
    for (OdDAI::ConstIteratorPtr it = pEntity->supertypes().createConstIterator(); it->next();)
    {
      OdDAI::Entity* pSupertype;
      it->getCurrentMember() >> pSupertype;
      std::map<OdString, std::list<OdDAI::Entity*> >::iterator subtype = subtypes.find(pSupertype->originalName());
      if (subtype == subtypes.end())
      {
        std::pair<OdString, std::list<OdDAI::Entity*> > value;
        value.first = pSupertype->originalName();
        subtype = subtypes.insert(value).first;
      }
      subtype->second.push_back(pEntity);
    }
  }
}

void dumpSubtypes(const OdDAI::EntityPtr& pEntity, const std::map<OdString, std::list<OdDAI::Entity*> >& subtypes)
{
  std::map<OdString, std::list<OdDAI::Entity*> >::const_iterator entitySubtypes = subtypes.find(pEntity->originalName());
  if (entitySubtypes != subtypes.end())
  {
    fwprintf(DumpStream, L"\n SUPERTYPE OF (ONEOF");
    OdString list;
    for (std::list<OdDAI::Entity*>::const_iterator it = entitySubtypes->second.begin(), end = entitySubtypes->second.end(); it != end; it++)
    {
      addListElement((*it)->originalName(), it == entitySubtypes->second.begin(), list, "    ");
    }
    fwprintf(DumpStream, L"%s))", list.c_str());
  }
}

void dumpSupertypes(const OdDAI::List<OdDAI::Entity*>& supertypes)
{
  for (OdDAI::ConstIteratorPtr it = supertypes.createConstIterator(); it->next();)
  {
    OdDAI::Entity* pSupertype;
    it->getCurrentMember() >> pSupertype;
    fwprintf(DumpStream, L"\n SUBTYPE OF (%hs)", pSupertype->originalName().c_str());
  }
}

void dumpExplicitAttributes(const OdDAI::AttributeSet& attributes)
{
  for (OdDAI::ConstIteratorPtr it = attributes.createConstIterator(); it->next();)
  {
    OdDAI::AttributePtr pAttr;
    it->getCurrentMember() >> pAttr;
    const OdDAI::ExplicitAttribute* pExplicit = dynamic_cast<const OdDAI::ExplicitAttribute*>(pAttr.get());
    if (pExplicit != NULL)
    {
      fwprintf(DumpStream, L"    %hs : %s%s;\n", 
        pExplicit->originalName().c_str(), 
        (pExplicit->optional() ? L"OPTIONAL " : L""), 
        getBaseTypeName(pExplicit->domain()).c_str());
    }
  }
}

void dumpInverseAttributes(const OdDAI::AttributeSet& attributes)
{
  bool hasInverse = false;
  for (OdDAI::ConstIteratorPtr it = attributes.createConstIterator(); it->next();)
  {
    OdDAI::AttributePtr pAttr;
    it->getCurrentMember() >> pAttr;
    const OdDAI::InverseAttribute* pInverse = dynamic_cast<const OdDAI::InverseAttribute*>(pAttr.get());
    if (pInverse != NULL)
    {
      if (hasInverse == false)
      {
        fwprintf(DumpStream, L" INVERSE\n");
        hasInverse = true;
      }
      fwprintf(DumpStream, L"    %hs : ", pInverse->originalName().c_str());
      if (pInverse->minCardinality() != OdDAI::Consts::OdIntUnset)
      {
        fwprintf(DumpStream, L"%s [%d:", pInverse->duplicates() ? L"BAG" : L"SET", pInverse->minCardinality());
        if (pInverse->maxCardinality() != OdDAI::Consts::OdIntUnset)
        {
          fwprintf(DumpStream, L"%d] OF ", pInverse->maxCardinality());
        }
        else
        {
          fwprintf(DumpStream, L"?] OF ");
        }
      }
      fwprintf(DumpStream, L"%hs FOR %hs;\n", 
        pInverse->domain()->originalName().c_str(), 
        pInverse->invertedAttr()->originalName().c_str());
    }
  }
}

void dumpDerivedAttributes(const OdDAI::AttributeSet& attributes)
{
  bool hasDerived = false;
  for (OdDAI::ConstIteratorPtr it = attributes.createConstIterator(); it->next();)
  {
    OdDAI::AttributePtr pAttr;
    it->getCurrentMember() >> pAttr;
    const OdDAI::DerivedAttribute* pDerived = dynamic_cast<const OdDAI::DerivedAttribute*>(pAttr.get());
    if (pDerived != NULL)
    {
      if (hasDerived == false)
      {
        fwprintf(DumpStream, L" DERIVE\n");
        hasDerived = true;
      }
      auto pRedeclaring = pDerived->redeclaring();
      if (!pRedeclaring.isNull())
      {
        const OdDAI::Attribute* pRedeclaringAttr = NULL;
        if (pRedeclaring->isExplicitAttribute())
        {
          pRedeclaringAttr = pRedeclaring->explicitAttribute();
        }
        else if (pRedeclaring->isDerivedAttribute())
        {
          pRedeclaringAttr = pRedeclaring->derivedAttribute();
        }
        if (pRedeclaringAttr)
        {
          fwprintf(DumpStream, L"    SELF\\%hs.%hs",
            pRedeclaringAttr->entityDef()->originalName().c_str(),
            pRedeclaringAttr->originalName().c_str());
        }
      }
      else
      {
        fwprintf(DumpStream, L"    %hs", pDerived->originalName().c_str());
      }
      fwprintf(DumpStream, L" : %s", getBaseTypeName(pDerived->domain()).c_str());
      fwprintf(DumpStream, L" := %hs;\n", pDerived->expression().c_str());
    }
  }
}

void dumpWhereRules(const OdDAI::WhereRuleList& whereRules)
{
  if (whereRules.empty())
  {
    return;
  }
  fwprintf(DumpStream, L" WHERE\n");
  for (OdDAI::ConstIteratorPtr it = whereRules.createConstIterator(); it->next();)
  {
    OdDAI::WhereRulePtr pWhereRule;
    it->getCurrentMember() >> pWhereRule;
    if (!pWhereRule.isNull())
    {
      fwprintf(DumpStream, L"    %hs : %hs;\n", pWhereRule->originalLabel().c_str(), pWhereRule->expression().c_str());
    }
  }
}

void dumpEntities(const OdDAI::EntitySet& entities)
{
  std::map<OdString, std::list<OdDAI::Entity*> > subtypes;
  collectSubtypes(entities, subtypes);

  for (OdUInt32 id = 0; id < entities->numEntries(); id++)
  {
    OdDAI::EntityPtr pEntity = entities->getAt(entities->keyAt(id));

    fwprintf(DumpStream, L"ENTITY %hs", pEntity->originalName().c_str());
    dumpSubtypes(pEntity, subtypes);
    dumpSupertypes(pEntity->supertypes());
    fwprintf(DumpStream, L";\n");

    const OdDAI::AttributeSet& attributes = pEntity->attributes();
    dumpExplicitAttributes(attributes);
    dumpDerivedAttributes(attributes);
    dumpInverseAttributes(attributes);

    dumpWhereRules(pEntity->whereRules());
    
    fwprintf(DumpStream, L"END_ENTITY;\n\n");
  }
}

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{

  /**********************************************************************/
  /* Command line parameters description                                */
  /**********************************************************************/
  if(argc != 3)
  {
    odPrintConsoleString(L"\nExIfcSchemaDump sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: ExIfcSchemaDump <target dump filename> <schema version>\n");
    odPrintConsoleString(L"\tsupported schema versions: Ifc2x3, Ifc4\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    return 1;
  }

  OdString wDump = argv[1]; 
  OdString wSchemaName = argv[2];
  OdAnsiString schemaName(wSchemaName, CP_UTF_8);

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  DumpStream = fopen(wDump, "w");
  if(!DumpStream)
  {
    odPrintConsoleString(L"\nThe file %ls has not been opened\n", wDump.c_str());
    return 1;
  }
 
  // create a service
  OdStaticRxObject< MyServices > svcs;

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false/* No geometry calculation needed */);

  try
  {
    OdDAI::SchemaPtr pSchema = oddaiGetSchema(schemaName);
    if (!pSchema.isNull())
    {
      fwprintf(DumpStream, L"SCHEMA %hs;\n\n", pSchema->name().c_str());

      dumpTypes(pSchema->types());
      dumpEntities(pSchema->entities());

      fwprintf(DumpStream, L"END_SCHEMA;");

      fclose(DumpStream);
    }
    else
    {
      fwprintf(DumpStream, L"Schema %hs is unsupported yet.\n\n", schemaName.c_str());
    }
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\nError: %ls\n", e.description().c_str());
  }
  catch (...)
  {
    odPrintConsoleString(L"\nUnknown Error.\n");
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize Runtime Extension environment                         */
  /**********************************************************************/
  odDbRootUninitialize();
  ::odrxUninitialize();

  return 0;
}

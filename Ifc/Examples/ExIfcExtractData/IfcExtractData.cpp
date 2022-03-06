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

// ODA SDK includes
#include <OdaCommon.h>
#include <StaticRxObject.h>
#include <RxDynamicModule.h>

// System includes
#include <iostream>
#include <cstdlib>

// SDAI includes
#include <daiHeaderSection.h>
#include <daiHeader/daiHeaderEntities.h>
#include <daiHeader/FileSchemaAutoImpl.h>

// IFC SDK includes
#include <IfcCore.h>
#include <IfcExamplesCommon.h>

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

enum AppResult
{
	arOk = 0,
	arIncorrectUsage,
	arFileOpenError,
	arEmptySectionHeader,
	arUnsupportedSchema,
	arEmptyModel,
	arOdError,
	arUnexpectedError
};

unsigned int inverse_aggregates = 0;
unsigned int empty_inverse_aggregates = 0;

void dumpEntity(OdIfc::OdIfcEntity *inst, OdDAI::Entity *entityDef)
{
  if (inst == nullptr)
    return;

  /* OdDAIObjectId instId = inst->id();
  if (instId.getHandle() == (OdUInt64)10)
  {
    throw OdError("Just stop");
  } */

  const OdDAI::List<OdDAI::Entity*>& superEntities = entityDef->supertypes();
  OdDAI::ConstIteratorPtr it_super = superEntities.createConstIterator();
  for (; it_super->next();)
  {
    OdDAI::Entity* pEntity;
    it_super->getCurrentMember() >> pEntity;
    dumpEntity(inst, pEntity);
  }

  OdString entName = entityDef->name();
  OdString strAbstract = entityDef->instantiable() ? L"INSTANTIABLE" : L"ABSTRACT";
  odPrintConsoleString(L"\t%s %s\n", strAbstract.c_str(), entName.c_str());
  for (OdDAI::ConstIteratorPtr it = entityDef->attributes().createConstIterator(); it->next();)
  { 

    OdDAI::AttributePtr pAttr;
    it->getCurrentMember() >> pAttr;

    OdString strAttrType = OD_T("UNKNOWN");
    OdDAI::ExplicitAttributePtr pExplicit = OdDAI::ExplicitAttribute::cast(pAttr);
    if (!pExplicit.isNull())
    {
      strAttrType = OD_T("EXPLICIT");
    }

    OdDAI::InverseAttributePtr pInverse = OdDAI::InverseAttribute::cast(pAttr);
    if (!pInverse.isNull())
    {
      strAttrType = OD_T("INVERSE");
    }

    OdDAI::DerivedAttributePtr pDerived = OdDAI::DerivedAttribute::cast(pAttr);
    if (!pDerived.isNull())
    {
      strAttrType = OD_T("DERIVED");
    }

    const OdAnsiString &attrName = pAttr->name();
    odPrintConsoleString(L"\t\t%s .%hs", strAttrType.c_str(), attrName.c_str());


// #define _DUMP_DERIVED_ATTRIBUTES
#ifndef _DUMP_DERIVED_ATTRIBUTES
    if (!pDerived.isNull())
    {
      odPrintConsoleString(L" = <Coming Soon>\n");
      continue;
    }
#endif

    OdRxValue val;
#ifndef _DUMP_DERIVED_ATTRIBUTES
    val = inst->getAttr(attrName);
#else
    val = pDerived.isNull() ? inst->getAttr(attrName) : inst->getDerivedAttr(attrName);
#endif

    bool unset = false;
    const OdRxValueType &vt = val.type();

    if (vt == OdRxValueType::Desc<OdDAIObjectId>::value())
    {
      OdDAIObjectId idVal;
      if (val >> idVal)
      {
        unset = OdDAI::Utils::isUnset(idVal);
        if (!unset)
        {
          OdUInt64 int64 = idVal.getHandle();
          odPrintConsoleString(L" = #%d", int64);
        }
      }
    }
    else
    if (vt == OdRxValueType::Desc<OdIfcGUID>::value())
    {
      OdIfcGUID guidVal;
      if (val >> guidVal)
      {
        unset = OdDAI::Utils::isUnset(guidVal);
        if (!unset)
        {
          odPrintConsoleString(L" = '%s'", OdString(guidVal).c_str());
        }
      }
    }
    else
    if (vt == OdRxValueType::Desc<int>::value())
    {
      int intVal;
      if (val >> intVal)
      {
        unset = OdDAI::Utils::isUnset(intVal);
        if (!unset)
          odPrintConsoleString(L" = %i", intVal);
      }
    }
    else
    if (vt == OdRxValueType::Desc<double>::value())
    {
      double dblVal;
      if (val >> dblVal)
      {
        unset = OdDAI::Utils::isUnset(dblVal);
        if (!unset)
          odPrintConsoleString(L" = %.6f", dblVal);
      }
    }
    else
    if (vt == OdRxValueType::Desc<const char *>::value())
    {
      const char *strVal;
      if (val >> strVal)
      {
        unset = OdDAI::Utils::isUnset(strVal);
        if (!unset)
        {
          OdString strW = strVal;
          odPrintConsoleString(L" = '%hs'", strW.c_str());
        }
      }
    }
    else
    if (vt.isEnum())
    {
      const char *strVal = nullptr;
      if (val >> strVal)
      {
        unset = (strVal == nullptr);
        if (!unset)
        {
          odPrintConsoleString(L" = .%hs.", strVal);
        }
      }

      // or:

      //OdDAI::EnumValueInfo enumVal;
      //if (val >> enumVal)
      //{
      //  unset = (enumVal.value == NULL);
      //  if (!unset)
      //  {
      //    odPrintConsoleString(L" = .%hs.", enumVal.value);
      //  }
      //}
    }
    else
    if (vt.isSelect())
    {
      OdTCKind selectKind;
      if (val >> selectKind)
      {
        unset = (selectKind == tkNull);
        if (!unset)
        {
          OdString typePath = val.typePath();
          odPrintConsoleString(L" = %s(", typePath.c_str());

          switch (selectKind)
          {
            case tkObjectId: // An object identifier's value.
            {
              OdDAIObjectId idVal;
              if (val >> idVal)
              {
                OdUInt64 int64;
                int64 = idVal.getHandle();
                odPrintConsoleString(L"#%d", int64);
              }
              break;
            }
            case tkLong: // An unsigned 32-bit integer value.
            {
              int intVal;
              if (val >> intVal)
                odPrintConsoleString(L"%i", intVal);
              break;
            }
            case tkBoolean: // A boolean value.
            {
              bool boolVal;
              if (val >> boolVal)
              {
                OdString strBool;
                strBool = boolVal ? "true" : "false";
                odPrintConsoleString(L"%s", strBool.c_str());
              }
              break;
            }
            case tkDouble: // A double value.
            {
              double dVal;
              if (val >> dVal)
                odPrintConsoleString(L"%.6f", dVal);
              break;
            }
            case tkBinary: // A binary value.
            case tkLogical: // A logical value.
              break;
            case tkString:
            {
              OdAnsiString strVal;
              if (val >> strVal)
              {
                OdString wcsVal = strVal;
                odPrintConsoleString(L"'%s'", wcsVal.c_str());
              }
              break;
            }
            case tkSequence:
            {
              odPrintConsoleString(L"TODO: kSequence not implemented yet");
              break;
            }
            default:
              odPrintConsoleString(L"Not implemented yet.");
          }
          odPrintConsoleString(L")");
        }
      }
    }
    else
    //if (vt == OdRxValueType::Desc<OdDAIObjectIds>::value()
    //  || vt == OdRxValueType::Desc<OdDAI::Aggr<OdDAIObjectId>* >::value())
    if (vt.isAggregate())
    {
      OdDAI::Aggr *aggr = NULL;
      if (val >> aggr)
      {
        unset = aggr->isNil();
        if (!unset)
        {
          odPrintConsoleString(L" = ");

          OdDAI::AggrType aggrType = aggr->aggrType();
          switch (aggrType)
          {
          case OdDAI::aggrTypeArray:
            odPrintConsoleString(L"ARRAY");
            break;
          case OdDAI::aggrTypeBag:
            odPrintConsoleString(L"BAG");
            break;
          case OdDAI::aggrTypeList:
            odPrintConsoleString(L"LIST");
            break;
          case OdDAI::aggrTypeSet:
            odPrintConsoleString(L"SET");
            break;
          }

          odPrintConsoleString(L"[");
          OdDAI::IteratorPtr iterator = aggr->createIterator();
          for (iterator->beginning(); iterator->next();)
          {
            OdRxValue val = iterator->getCurrentMember();
            OdString strVal = val.toString();
            odPrintConsoleString(L" %s ", strVal.c_str());
          }
          odPrintConsoleString(L"]");
        }
      }
    }
    else
    {
      //
      // Deprecated: OdArray instead of Aggregate
      //
      OdDAIObjectIds idsVal;
      if (val >> idsVal)
      {
        ++inverse_aggregates;
        unset = (idsVal.size() == 0);
        if (!unset)
        {
          OdUInt64 int64;
          int64 = idsVal[0].getHandle();
          odPrintConsoleString(L" = (#%d", int64);
          for (unsigned int i = 1; i < idsVal.size(); ++i)
          {
            int64 = idsVal[i].getHandle();
            odPrintConsoleString(L", #%d", int64);
          }
          odPrintConsoleString(L")");
        }
        else
          ++empty_inverse_aggregates;
      }
    }

    if (unset)
      odPrintConsoleString(L" = UNSET");

    odPrintConsoleString(L"\n");
  }
}

int dumpFile(OdIfcHostAppServices &svcs, const OdString fileName)
{
  odPrintConsoleString(L"\nDump %s.\n", fileName.c_str());

  OdIfcFilePtr pFile = svcs.createDatabase();
  OdResult res = pFile->readFile(fileName);

  if (res == eOk)
  {
    odPrintConsoleString(L"\nFile opened successfully.\n");
  }
  else
  {
    odPrintConsoleString(L"\nFile open error. Press any key to finish...");
    getchar();
    return arFileOpenError;
  }

  OdDAI::OdHeaderSectionPtr headerSection = pFile->getHeaderSection();

  if (headerSection.isNull())
  {
    odPrintConsoleString(L"\nError getting header section from the %s file! Press any key to finish...");
    getchar();
    return arEmptySectionHeader;
  }

  OdSmartPtr<OdDAI::FileSchema> pFileSchema = headerSection->getEntityByType(OdDAI::kFileSchema);

  OdAnsiStringArray schemaIdentifiers;
  pFileSchema->getSchemaIdentifiers(schemaIdentifiers);
  //or: pFileSchema->getAttr("schema_identifiers") >> schemaIdentifiers;
  OdString schemaName = schemaIdentifiers[0];
  if (!schemaName.iCompare("IFC2X3") && !schemaName.iCompare("IFC4"))
  {
    odPrintConsoleString(L"\nUnsupported file schema: %s! Press any key to finish...", schemaName.c_str());
    getchar();
    return arUnsupportedSchema;
  }

  OdIfcModelPtr pModel = pFile->getModel();

  if (pModel.isNull())
  {
    odPrintConsoleString(L"\nAn unexpected error occurred while opening the IFC file! Press any key to finish...");
    getchar();
    return arEmptyModel;
  }

  odPrintConsoleString(L"Model entities (schema name is \"%s\"): \n", schemaName.c_str());

  OdDAI::InstanceIteratorPtr it = pModel->newIterator();
  OdIfc::OdIfcEntityPtr pInst;

  unsigned int entIdx;
  for (entIdx = 0; !it->done(); it->step(), ++entIdx)
  {
    // Opens an instance
    pInst = it->id().openObject();

    if (!pInst.isNull())
    {
      OdUInt64 id;
      pInst->getAttr("_id") >> id;
      OdString typeNameW = pInst->typeName();
      OdDAI::EntityPtr pEntityDef = pInst->getInstanceType();

      odPrintConsoleString(L"Entity %d: \n", entIdx);
      odPrintConsoleString(L"\tEntity handle (corresponds to the STEP-id) = %d\n", id);
      odPrintConsoleString(L"\tEntity type name = %s (enum = %d)\n", typeNameW.c_str(), pInst->type());
      dumpEntity(pInst, pEntityDef);

      if (pInst->isKindOf("ifcroot"))
        odPrintConsoleString(L"\tDerived from IfcRoot!\n");
    }
  }

  odPrintConsoleString(L"Found entities: %d\n", entIdx);
  odPrintConsoleString(L"Inverse aggregates: %d\n", inverse_aggregates);
  odPrintConsoleString(L"Empty inverse aggregates: %d\n", empty_inverse_aggregates);

  //Finalize the process, OdIfcFile and underlying header section and Model will be released.

  return arOk;
}

#ifndef _TOOLKIT_IN_DLL_
  INIT_IFC_STATIC_MODULES_NO_GEOM;
#endif

int main(int argc, char* argv[])
{
	setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  OdStaticRxObject< MyServices > svcs; // In current documentation <> together
                                       // with inner code is empty as it looks as html tag

	odrxInitialize(&svcs);

	odDbRootInitialize();

	odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  OdArray<int> intArr;
  int arrSize = sizeof(intArr);
  int arrBufSize = sizeof(OdArrayBuffer);

	odPrintConsoleString(L"\nIFC SDK Extract Data Application. Copyright (c) 2022, Open Design Alliance\n");
	odPrintConsoleString(L"\nExIfcExtractData application developed using %ls ver %ls", svcs.product().c_str(), svcs.versionString().c_str());

	if (argc != 2)
	{
		odPrintConsoleString(L"\n\nusage: ExIfcExtractData ");
		odPrintConsoleString(L"\n a full path to the input IFC file\n Press any key to finish...");
		getchar();
		return arIncorrectUsage;
	}

#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  int result = arOk;

	try
	{
		OdString ifcFileName(argv[1]);
    result = dumpFile(svcs, ifcFileName);
	}
	catch (OdError& e)
	{
		odPrintConsoleString(L"\nError occurred: %ls! Press any key to finish...", e.description().c_str());
		result = arOdError;
	}
	catch (...)
	{
		odPrintConsoleString(L"\n\nUnexpected error.");
    result = arUnexpectedError;
	}

	odIfcUninitialize();
	odDbRootUninitialize();
	::odrxUninitialize();

	return result;
}

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

#include <iostream>
#include "ExIfcTutorial_02.h"
#include "IfcModel.h"
#include "RxValue.h"

using namespace OdIfc;
using namespace OdDAI;

int Tutorial_02(int argc, wchar_t* argv[], const MyServices &svcs)
{
  OdString ifcFileName(argv[2]);

  OdIfcFilePtr pFile = svcs.createDatabase();
  OdResult res = pFile->readFile(ifcFileName);

  if (res == eOk)
  {
    odPrintConsoleString(L"\nFile opened successfully.\n");
  }
  else
  {
    odPrintConsoleString(L"\nFile open error. Press any key to finish...");
    getchar();
    return res;
  }

  odPrintConsoleString(L"\nRetreiving property information");

  OdIfcModelPtr pModel = pFile->getModel();
  OdDAIObjectIdSet* products = pModel->getEntityExtent("ifcproduct");

  IteratorPtr pIt = products->createIterator();
  pIt->beginning();
  while (pIt->next())
  {
    OdDAIObjectId id;
    if (!(pIt->getCurrentMember() >> id))
      return eInvalidInput;

    if (OdResult res = dumpProduct(id))
      return res;
  }
  odPrintConsoleString(L"\nProcess finished\n");
  return eOk;
}

OdResult dumpProduct(const OdDAIObjectId& id)
{
  OdString templ("\n");
  OdIfcEntityPtr pEntity = id.openObject();
  if (pEntity.isNull())
    return eNullPtr;

  OdString entName = pEntity->getInstanceType()->name();
  entName.makeUpper();

  OdString productName;
  pEntity->getAttr("name") >> productName;

  OdString res;
  res = templ + entName;
  if (!productName.isEmpty())
  {
    res += " : ";
    res += productName;
  }

  odPrintConsoleString(res);

  OdDAIObjectIds invIsDefinedBy;
  if (pEntity->getAttr("isdefinedby") >> invIsDefinedBy)
  {
    OdDAIObjectIds::iterator pIt, pEnd = invIsDefinedBy.end();
    for (pIt = invIsDefinedBy.begin(); pIt != pEnd; ++pIt)
    {
      if (!pIt->isNull())
      {
        OdIfcEntityPtr relDefinedByProperties = pIt->openObject();
        if (relDefinedByProperties.isNull())
          return eNullPtr;

        OdDAIObjectId relatingPropertyDefinition;
        if (relDefinedByProperties->getAttr("relatingpropertydefinition") >> relatingPropertyDefinition)
        {
          if (!relatingPropertyDefinition.isNull())
          {
            if (OdResult res = dumpPropertySet(relatingPropertyDefinition))
              return res;
          }
        }
      }
    }
  }

  OdDAIObjectIds invIsTypedBy;
  if (pEntity->getAttr("istypedby") >> invIsTypedBy)
  {
    OdDAIObjectIds::iterator pIt, pEnd = invIsTypedBy.end();
    for (pIt = invIsTypedBy.begin(); pIt != pEnd; ++pIt)
    {
      if (!pIt->isNull())
      {
        OdIfcEntityPtr pRelType = pIt->openObject();
        if (pRelType.isNull())
          return eNullPtr;

        OdDAIObjectId typeId;
        if (pRelType->getAttr("relatingtype") >> typeId)
        {
          if (!typeId.isNull())
          {
            OdIfcEntityPtr pType = typeId.openObject();
            if (pType.isNull())
              return eNullPtr;

            OdDAIObjectIds propertySets;
            if (pType->getAttr("haspropertysets") >> propertySets)
            {
              OdDAIObjectIds::iterator pPropIt, pPropEnd = propertySets.end();
              for (pPropIt = propertySets.begin(); pPropIt != pPropEnd; ++pPropIt)
              {
                if (!pPropIt->isNull())
                {
                  if (OdResult res = dumpPropertySet(*pPropIt))
                    return res;
                }
              }
            }
          }
        }
      }
    }
  }

  return eOk;
}

OdResult dumpPropertySet(const OdDAIObjectId& relatingPropertyDefinition)
{
  OdString templ("\n--");
  OdIfcEntityPtr pIfcPropertySet = relatingPropertyDefinition.openObject();
  if (pIfcPropertySet.isNull())
    return eNullPtr;

  OdString setName = pIfcPropertySet->getInstanceType()->name();
  setName.makeUpper();

  OdString propertyName;
  pIfcPropertySet->getAttr("name") >> propertyName;

  OdString res = templ + setName;
  if (!propertyName.isEmpty())
  {
    res += " : ";
    res += propertyName;
  }
  odPrintConsoleString(res);

  OdDAIObjectIds props;
  if (pIfcPropertySet->getAttr("hasproperties") >> props)
  {
    OdDAIObjectIds::iterator pIt, pEnd = props.end();
    for (pIt = props.begin(); pIt != pEnd; ++pIt)
    {
      if (!pIt->isNull())
      {
        if (OdResult res = dumpProperty(*pIt))
          return res;
      }
    }
  }
  return eOk;
}

OdResult dumpProperty(const OdDAIObjectId& propertyId)
{
  OdIfcEntityPtr pProperty = propertyId.openObject();
  if (pProperty.isNull())
    return eNullPtr;

  OdString propertyName = pProperty->getInstanceType()->name();
  propertyName.makeUpper();

  OdString templ("\n----");
  OdString propName;
  pProperty->getAttr("name") >> propName;

  OdString res = templ + propertyName;
  if (!propName.isEmpty())
  {
    res += " : ";
    res += propName;
  }

  OdRxValue propVal = pProperty->getAttr("nominalvalue");
  if (!propVal.isEmpty() && propVal.type().isSelect())
  {
    OdString typeValue = propVal.typePath();
    typeValue.makeUpper();

    OdTCKind kind;
    propVal >> kind;
    OdAnsiString sVal;
    switch (kind)
    {
    case tkString:
      if (propVal >> sVal)
        sVal.format("(\"%s\")", sVal);
      break;
    case tkLong:
    {
      int iVal;
      if (propVal >> iVal)
        sVal.format("(%d)", iVal);
      break;
    }
    case tkLogical:
    {
      Logical lVal;
      if (propVal >> lVal)
        sVal.format("(%s)", (OdAnsiString)lVal);
      break;
    }
    case tkDouble:
    {
      double dVal;
      if (propVal >> dVal)
        sVal.format("(%f)", dVal);
      break;
    }
    case tkBoolean:
    {
      Boolean bVal;
      if (propVal >> bVal)
        sVal.format("(%s)", bVal.toStr());
      break;
    }
    default:
      return eNotImplemented;
    }

    if (!sVal.isEmpty())
    {
      res += "=";
      res += typeValue;
      res += sVal.c_str();
    }
  }

  odPrintConsoleString(res);

  return eOk;
}

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
#include "ExPrintConsole.h"
#include "IfcCore.h"
#include "IfcEntityTypes.h"
#include "daiSchema.h"
#include "daiHeaderSection.h"
#include "daiHeader/daiHeaderEntities.h"
#include "daiUtils/daiUnset.h"
#include "daiUtils/daiCustomCompare.h"
#include "OdDbStub.h"

#ifndef _MODEL_COMPARE_H
#define _MODEL_COMPARE_H

template<class HeaderEntity, OdDAI::OdHeaderEntityType HeaderSectionType>
bool HeaderEntitiesCompare(OdDAI::OdHeaderSectionPtr&  headerSectionLeft, OdDAI::OdHeaderSectionPtr&  headerSectionRight)
{
  if (headerSectionLeft.isNull() || headerSectionRight.isNull())
  {
    odPrintConsoleString(L"\nHeader section is null.");
    return false;
  }

  OdDAI::ApplicationInstancePtr  entityLeft = headerSectionLeft->getEntityByType(HeaderSectionType);
  OdDAI::ApplicationInstancePtr  entityRight = headerSectionRight->getEntityByType(HeaderSectionType);

  if (entityLeft.isNull() || entityRight.isNull())
  {
    odPrintConsoleString(L"\nHeader entity is null.");
    return false;
  }

  HeaderEntity* left = dynamic_cast<HeaderEntity*> (entityLeft.get());
  HeaderEntity* right = dynamic_cast<HeaderEntity*> (entityRight.get());

  return (*left == *right);
}

static bool CompareHeaders(OdDAI::OdHeaderSectionPtr  headerSectionLeft, OdDAI::OdHeaderSectionPtr  headerSectionRight)
{
  return HeaderEntitiesCompare<OdDAI::FileDescription, OdDAI::kFileDescription>(headerSectionLeft, headerSectionRight) &&
  HeaderEntitiesCompare<OdDAI::FileName, OdDAI::kFileName>(headerSectionLeft, headerSectionRight) &&
  HeaderEntitiesCompare<OdDAI::FileSchema, OdDAI::kFileSchema>(headerSectionLeft, headerSectionRight);
}

static bool getEntityAttributes(
  OdAnsiString entityTypeName,
  OdDAI::SchemaPtr schema,
  OdDAI::AttributeSet& attributes)
{
  OdDAI::EntityPtr pEntityDef = schema->find(entityTypeName);
  if (pEntityDef.isNull())
  {
    odPrintConsoleString(L"\nCan't fint entity definition at schema.");
    return false;
  }

  OdDAI::EntityList  entityDefCollection;
  schema->getSuperEntityCollection(pEntityDef, entityDefCollection);
  entityDefCollection.push_back(pEntityDef);

  for (OdDAI::EntityList::iterator itEnt = entityDefCollection.begin(), endEnt = entityDefCollection.end();
    itEnt != endEnt; ++itEnt)
  {
    for (OdDAI::ConstIteratorPtr itAttr = (*itEnt)->attributes().createConstIterator(); itAttr->next();)
    {
      OdDAI::AttributePtr pAttr;
      itAttr->getCurrentMember() >> pAttr;
      attributes.putByIndex(attributes.getMemberCount(), pAttr);
    }
  }

  return true;
}

static bool CompareModels(OdIfcModelPtr modelLeft, OdIfcModelPtr modelRight)
{
  if (modelLeft.isNull() || modelRight.isNull())
  {
    odPrintConsoleString(L"\nInvalid model parameters.");
    return false;
  }

  OdDAI::InstanceIteratorPtr leftIterator = modelLeft->newIterator();
  OdDAI::InstanceIteratorPtr rightIterator = modelRight->newIterator();

  while (!leftIterator->done())
  {
    OdIfc::OdIfcEntityPtr leftEntity = leftIterator->id().openObject();
    if (rightIterator->done())
    {
      odPrintConsoleString(L"\nCan not seek to the next entity in right: %lu.", (OdUInt64)leftIterator->id().getHandle());
      return false;
    }

    OdDAIObjectId id = leftIterator->id();
    OdDbHandle currentHandle = id.getHandle();

    OdIfc::OdIfcEntityPtr rightEntity = rightIterator->id().openObject();
    if (rightEntity.isNull() || leftEntity.isNull())
    {
      odPrintConsoleString(L"\nIterator error.");
      return false;
    }

    if (rightEntity->comparedTo(leftEntity.get()) != OdRx::Ordering::kEqual)
    {
      odPrintConsoleString(L"[ are not equal ] ");
      odPrintConsoleString(L"  right - %hs(%lu) ", rightEntity->typeName().c_str(), (OdUInt64)rightEntity->id()->getHandle());
      odPrintConsoleString(L"  left - %hs(%lu) \r\n", leftEntity->typeName().c_str(), (OdUInt64)leftEntity->id()->getHandle());
      break;
    }

//#define _MODEL_COMPARE_BREAKPOINT_HANDLE
#ifdef _MODEL_COMPARE_BREAKPOINT_HANDLE
    if (currentHandle == (OdUInt64)97)
    {
      int breakpoint = 1;
    }
#endif

    rightIterator->step();
    leftIterator->step();
  }

  if (!rightIterator->done())
  {
    odPrintConsoleString(L"\nRight file differs of left.");
    return false;
  }

  return true;
}

#endif

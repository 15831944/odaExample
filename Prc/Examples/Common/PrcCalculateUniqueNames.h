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

#ifndef _PRCCALCULATEUNIQUENAMES_INCLUDED_
#define _PRCCALCULATEUNIQUENAMES_INCLUDED_ 
/** { Secret } */

#include "PrcCommon.h"
#include "PrcFile.h"

void traverseTree(OdPrcProductOccurrencePtr productOccurrence, OdStack<OdPrcProductOccurrencePtr> &stackPO)
{
  OdString name = productOccurrence->name().name();
  int count = productOccurrence->referencesOfProductOccurrence().getSonProductOccurrences().size();
  for (int idx = 0; idx < count; ++idx)
  {
    // - child.traverse
    OdPrcObjectPtr objPO = productOccurrence->referencesOfProductOccurrence().getSonProductOccurrences()[idx].openObject();
    OdPrcProductOccurrencePtr pPO = (OdPrcProductOccurrence *) objPO.get(); ODA_ASSERT(!pPO.isNull());
    OdString name1 = pPO->name().name();
    traverseTree(pPO, stackPO);
  }

  const OdPrcPartDefinition *pPartDef = productOccurrence->getPartDefinition();
  if(pPartDef)
  {
    const OdPrcObjectIdArray &rItemArr = pPartDef->representationItem();
    if(0 != rItemArr.size())
      stackPO.push(productOccurrence);
  }
}

OdStringArray CalculateUniqueNames(const OdPrcFilePtr &pPrcFile)
{
  OdStringArray arrOutStr;
  if (!pPrcFile.isNull())
  {
    const OdPrcObjectIdArray &roots = pPrcFile->modelFileData().getStartRootOccurrences();
    OdUInt32 countRoots = roots.size();
    for (OdUInt32 idx = 0; idx < countRoots; idx++)
    {
      OdPrcProductOccurrencePtr rootProductOccurrence = pPrcFile->modelFileData().getStartRootOccurrences()[idx].safeOpenObject();
      if (!rootProductOccurrence.isNull())
      {
        OdStack<OdPrcProductOccurrencePtr> stackPO;
        traverseTree(rootProductOccurrence, stackPO);
        while(!stackPO.empty())
        {
          if (stackPO.top())
          {
            OdPrcProductOccurrencePtr &pTopPO = *stackPO.top();
            if (!pTopPO.isNull())
            {
              arrOutStr.push_back(pTopPO->calculateUniqueName(NULL));
            }
          }
          stackPO.pop();
        }
      }
    }
  }
  return arrOutStr;
}

#endif // _PRCCALCULATEUNIQUENAMES_INCLUDED_


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

#include "PrcCommon.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcBrepModel.h"
#include "PrcPolyBrepModel.h"
#include "PrcBrepData.h"
#include "PrcWireCurve.h"
#include "PrcPointSet.h"
#include "PrcSingleWireBody.h"
#include "PrcWireEdge.h"
#include "PrcExportContext.h"
#include "PrcExport.h"

OdPrcFilePtr createFileModel()
{
  // create prc
  OdPrcFilePtr pFile = OdPrcFile::createObject();

  pFile->setVersions(8137, 8137);
  pFile->fileStructureId() = OdPrcUniqueId::generateUID();

  // init model file data section
  pFile->modelFileData().unit().setUnitFromCADFile(true);
  pFile->modelFileData().unit().setUnit(1); // 1 mm

  // create file structures section
  addNewFileStructure(*pFile);

  return pFile;
}

OdPrcTopoContextPtr createTopoContext(OdPrcFileStructure & newStructure)
{
  OdPrcTopoContextPtr newTopoContext = OdPrcTopoContext::createObject();
  newTopoContext->setBehaviour(6);
  newTopoContext->setGranularity(1e-8);
  newTopoContext->setTolerance(1e-6);
  newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().push_back(newTopoContext);
  return newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
}

OdPrcFilePtr createTopologyCommon()
{
  OdPrcFilePtr pFile = createFileModel();
  OdPrcFileStructurePtr pFS = pFile->fileStructures().last();

  // create root product occurrence
  OdPrcProductOccurrencePtr newProductOccurrence = OdPrcProductOccurrence::createObject();
  pFS->addObject(newProductOccurrence);

  pFS->fileStructureTree().internalData().setRootProductOccurrence(newProductOccurrence->objectId());
  pFile->modelFileData().addStartRootOccurrence(*newProductOccurrence);

  return pFile;
}

OdPrcFileStructurePtr addNewFileStructure(OdPrcFile & file)
{
  // create file structures section
  OdPrcFileStructurePtr newStructure = OdPrcFileStructure::createObject();
  file.fileStructures().append(newStructure);
  newStructure->fileStructureId() = OdPrcUniqueId::generateUID();
  file.addFileStructure(*newStructure);

  // create file structure globals section
  OdPrcFileStructureGlobals& fileStructureGlobals = newStructure->fileStructureGlobals();
  fileStructureGlobals.setTessellationChordHeightRatio(2000);
  fileStructureGlobals.setTessellationAngleDegree(40);

  // file structure header section
  newStructure->setVersions(8137, 8137);

  return newStructure;
}

OdPrcProductOccurrencePtr createProductOccurrence(OdPrcFileStructure & FSt, OdPrcProductOccurrence & parentPO)
{
  OdPrcProductOccurrencePtr newProductOccurrence = OdPrcProductOccurrence::createObject();
  FSt.addObject(newProductOccurrence);
  parentPO.referencesOfProductOccurrence().getSonProductOccurrences().push_back(newProductOccurrence->objectId());
  return newProductOccurrence;
}

OdPrcPartDefinitionPtr createPartDefinition(OdPrcFileStructure & FSt, OdPrcProductOccurrence & PO)
{
  // part definition section
  OdPrcPartDefinitionPtr newDefinition = OdPrcPartDefinition::createObject();
  FSt.addObject(newDefinition);
  FSt.fileStructureTree().partDefinition().push_back(newDefinition->objectId());
  PO.referencesOfProductOccurrence().setCorrespondingPartDefinition(newDefinition->objectId());
  return newDefinition;
}

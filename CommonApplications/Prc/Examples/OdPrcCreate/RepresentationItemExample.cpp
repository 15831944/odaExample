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

#include "PrcFile.h"
#include "PrcUniqueId.h"
#include "PrcModelFileData.h"
#include "PrcFileStructure.h"
#include "PrcRepresentationItem.h"
#include "PrcPolyWire.h"
#include "Prc3dWireTess.h"
#include "PrcDirection.h"
#include "PrcPointSet.h"
#include "PrcCoordinateSystem.h"
#include "PrcPolyBrepModel.h"
#include "Prc3dTess.h"
#include "PrcSet.h"
#include "OdPrcCreateStart.h"
#include "Ge/GeExtents3d.h"
#include "PrcCreateTopologyHelper.h"

OdPrcRepresentationItemPtr CreatePolyWire(OdPrcFileStructure &newStructure)
{
  OdPrcPolyWirePtr polyWire = OdPrcPolyWire::createObject();
  OdPrc3dWireTessPtr mTess = OdPrc3dWireTess::createObject();
  OdFloatArray arr;
  arr.push_back(0.0);
  arr.push_back(2.0);
  arr.push_back(0.0);
  arr.push_back(2.0);
  arr.push_back(4.0);
  arr.push_back(0.0);
  arr.push_back(4.0);
  arr.push_back(2.0);
  arr.push_back(0.0);
  arr.push_back(2.0);
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(2.0);
  arr.push_back(0.0);

  arr.push_back(1.0);
  arr.push_back(1.0);
  arr.push_back(0.0);
  arr.push_back(1.0);
  arr.push_back(3.0);
  arr.push_back(0.0);
  arr.push_back(3.0);
  arr.push_back(3.0);
  arr.push_back(0.0);
  arr.push_back(3.0);
  arr.push_back(1.0);
  arr.push_back(0.0);
  arr.push_back(1.0);
  arr.push_back(1.0);
  arr.push_back(0.0);

  mTess->coordinates() = arr;

  mTess->wireIndexes().push_back(arr.size()/(3*2)); // in array we have number of points = size()/3 but we also have 2 polyWire
  for (OdUInt32 i = 0; i < arr.size()/(3*2); ++i)
  {
    mTess->wireIndexes().push_back(i*3);
  }

  mTess->wireIndexes().push_back(arr.size()/(3*2));
  for (OdUInt32 i = arr.size()/(3*2); i < 2*arr.size()/(3*2); ++i)
  {
    mTess->wireIndexes().push_back(i*3);
  }

  polyWire->tessellation() = mTess;

  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
  return polyWire;
}

OdPrcRepresentationItemPtr CreatePointSets(OdPrcFileStructure& newStructure, double radius = 30, OdGePoint3d position = OdGePoint3d::kOrigin)
{
  OdPrcSetPtr set = OdPrcSet::createObject();

  OdPrcPointSetPtr pointSetBlue = OdPrcPointSet::createObject();
  pointSetBlue->styleId() = OdPrcCategory1LineStyle::createByColor(23. / 255., 32. / 255., 137. / 255., newStructure);
  OdPrcCategory1LineStylePtr lineStyle = pointSetBlue->styleId().openObject(kForWrite);
  lineStyle->setLineWidth(5);
  pointSetBlue->setBehaviourBitField(PRC_GRAPHICS_Show);
  newStructure.addObject(pointSetBlue);
  set->representationItem().push_back(pointSetBlue->objectId());


  OdPrcPointSetPtr pointSetRed = OdPrcPointSet::createObject();
  pointSetRed->styleId() = OdPrcCategory1LineStyle::createByColor(255. / 255., 50. / 255., 8. / 255., newStructure);
  lineStyle = pointSetRed->styleId().openObject(kForWrite);
  lineStyle->setLineWidth(5);
  pointSetRed->setBehaviourBitField(PRC_GRAPHICS_Show);
  newStructure.addObject(pointSetRed);
  set->representationItem().push_back(pointSetRed->objectId());

  OdPrcPointSetPtr pointSetWhite = OdPrcPointSet::createObject();
  pointSetWhite->styleId() = OdPrcCategory1LineStyle::createByColor(249. / 255., 249. / 255., 249. / 255., newStructure);
  lineStyle = pointSetWhite->styleId().openObject(kForWrite);
  lineStyle->setLineWidth(5);
  pointSetWhite->setBehaviourBitField(PRC_GRAPHICS_Show);
  newStructure.addObject(pointSetWhite);
  set->representationItem().push_back(pointSetWhite->objectId());

  for (int j = 0; j < 180; ++j)
  {
    for (int i = 0; i < 360; ++i)
    {
      double theta = i * OdaPI / 180.;
      double phi = j * OdaPI / 180.;

      OdGePoint3d pt;

      pt.x = radius * sin(phi) * cos(theta);
      pt.y = radius * sin(phi) * sin(theta);
      pt.z = radius * cos(phi);

      OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
      OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);

      OdGeMatrix3d xEyeToWorld;
      OdGeVector3d yVector = defUpVec;
      yVector.normalize();
      OdGeVector3d zVector = (defCamPos - OdGePoint3d::kOrigin).normalize();
      OdGeVector3d xVector = yVector.crossProduct(zVector);
      xEyeToWorld.setCoordSystem(OdGePoint3d::kOrigin, xVector, yVector, zVector);

      pt.transformBy(xEyeToWorld);

      pt += position.asVector();


      if ((j > 40 && j < 140))
      {
        if (i < 160 || i > 200)
        {
          pointSetBlue->point().push_back(pt);
        }
        else
        {
          if ((i > 162 && i < 179) || (i > 181 && i < 198))
          {
            pointSetRed->point().push_back(pt);
          }
          else
          {
            pointSetWhite->point().push_back(pt);
          }
        }
      }
      else
      {
        pointSetWhite->point().push_back(pt);
      }
    }
  }

  return set;
}

OdPrcRepresentationItemPtr CreatePolyBrepModel(OdPrcFileStructure &newStructure)
{
  OdPrcPolyBrepModelPtr polyBrep = OdPrcPolyBrepModel::createObject();

  OdPrcCategory1LineStylePtr style = OdPrcCategory1LineStyle::createObject();
  newStructure.addObject(style);
  style->setLineWidth(10);
  newStructure.fileStructureGlobals().category1LineStyles().push_back(style->objectId());
  polyBrep->styleId() = style->objectId();
  polyBrep->setBehaviourBitField(PRC_GRAPHICS_Show);

  OdPrc3dTessPtr mTess = createTess<OdPrc3dTess>(newStructure, *polyBrep);
  OdFloatArray arr;
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(2.0);
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(2.0);
  arr.push_back(2.0);
  arr.push_back(0.0);
  arr.push_back(4.0);
  arr.push_back(2.0);
  arr.push_back(0.0);

  mTess->coordinates() = arr;
  mTess->setMustRecalculateNormals(true);
  mTess->triangulatedIndex().push_back(0);
  mTess->triangulatedIndex().push_back(3);
  mTess->triangulatedIndex().push_back(6);
  mTess->triangulatedIndex().push_back(6);
  mTess->triangulatedIndex().push_back(9);
  mTess->triangulatedIndex().push_back(3);
  OdPrcTessFace face;
  face.setUsedEntitiesFlag(2);
  face.sizesTriangulated().push_back(2);
  mTess->faceTessellation().push_back(face);

  return polyBrep;
}


// OdPrcRepresentationItemPtr CreateDirection(OdPrcFileStructure &newStructure)
// {
//   OdPrcDirectionPtr direction = OdPrcDirection::createObject();
// 
//   OdGeVector3d vect(1,0,0);
//   direction->direction() = vect;
//   direction->setHasOrigin(true);
//   OdGePoint3d orig(1,1,1);
//   direction->origin() = orig;
// 
//   OdPrcCategory1LineStylePtr style = OdPrcCategory1LineStyle::createObject();
//   newStructure.addObject(style);
//   style->setLineWidth(10);
//   newStructure.fileStructureGlobals().category1LineStyles().push_back(style->objectId());
//   direction->styleId() = style->objectId();
// 
//   return direction;
// }
 
// OdPrcRepresentationItemPtr CreateCoordinateSystem(/*OdPrcFileStructure &newStructure*/)
// {
//   OdPrcCoordinateSystemPtr coordSystem = OdPrcCoordinateSystem::createObject();
// 
//   coordSystem->axisSet()->set(OdGeMatrix3d().setCoordSystem(OdGePoint3d(1,1,1), OdGeVector3d(1,0,0),OdGeVector3d(0,1,0),OdGeVector3d(0,0,1)));
// 
//   return coordSystem;
// }

OdPrcRepresentationItemPtr CreateSet(OdPrcFileStructure &newStructure)
{
  OdPrcSetPtr set = OdPrcSet::createObject();
  OdPrcRepresentationItemPtr rI = CreatePolyWire(newStructure);
  newStructure.addObject(rI);
  set->representationItem().push_back(rI->objectId());

  rI = CreatePointSets(newStructure, 2, OdGePoint3d(2.5, 2.5, 2.5));
  newStructure.addObject(rI);
  set->representationItem().push_back(rI->objectId());

  rI = CreatePolyBrepModel(newStructure);
  newStructure.addObject(rI);
  set->representationItem().push_back(rI->objectId());

  return set;
}

OdPrcRepresentationItemPtr Create3dPolyWireWithFlags(OdPrcFileStructure &newStructure)
{
  OdPrcPolyWirePtr polyWire = OdPrcPolyWire::createObject();
  OdPrc3dWireTessPtr mTess = OdPrc3dWireTess::createObject();
  OdFloatArray arr;
  arr.push_back(-3.0); //1 point
  arr.push_back(-3.0);
  arr.push_back(0.0);
  arr.push_back(-1.0); //2 point
  arr.push_back(-3.0);
  arr.push_back(0.0);
  arr.push_back(-2.0); //3 point
  arr.push_back(-1.0);
  arr.push_back(0.0);
  arr.push_back(-1.0); //4 point
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(1.0); //5 point
  arr.push_back(0.0);
  arr.push_back(0.0);
  arr.push_back(2.0); //6 point
  arr.push_back(-1.0);
  arr.push_back(0.0);
  arr.push_back(1.0); //7 point
  arr.push_back(-3.0);
  arr.push_back(0.0);
  arr.push_back(3.0); //8 point
  arr.push_back(-3.0);
  arr.push_back(0.0);
  mTess->coordinates() = arr;

  mTess->wireIndexes().push_back(3+PRC_3DWIRETESSDATA_IsClosing);
  mTess->wireIndexes().push_back(0);
  mTess->wireIndexes().push_back(3);
  mTess->wireIndexes().push_back(6);
  mTess->wireIndexes().push_back(2+PRC_3DWIRETESSDATA_IsContinuous);
  mTess->wireIndexes().push_back(9);
  mTess->wireIndexes().push_back(12);
  mTess->wireIndexes().push_back(4+PRC_3DWIRETESSDATA_IsContinuous);
  mTess->wireIndexes().push_back(15);
  mTess->wireIndexes().push_back(18);
  mTess->wireIndexes().push_back(21);
  mTess->wireIndexes().push_back(15);

  mTess->arrayRGBA().colors().push_back(255);//1 wire color
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);//2 wire color
  mTess->arrayRGBA().colors().push_back(255);
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);//3 wire color (can't see)
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);

  mTess->arrayRGBA().colors().push_back(0);//Closing wire color
  mTess->arrayRGBA().colors().push_back(255);
  mTess->arrayRGBA().colors().push_back(255);

  mTess->arrayRGBA().colors().push_back(255);//Continuous wire color
  mTess->arrayRGBA().colors().push_back(255);
  mTess->arrayRGBA().colors().push_back(0);

  mTess->arrayRGBA().colors().push_back(0);//4 wire color
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(255);
  mTess->arrayRGBA().colors().push_back(0);//5 wire color (can't see)
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);

  mTess->arrayRGBA().colors().push_back(255);//Continuous wire color
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(255);

  mTess->arrayRGBA().colors().push_back(255);//6 wire color
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);//7 wire color
  mTess->arrayRGBA().colors().push_back(255);
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);//8 wire color
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(255);
  mTess->arrayRGBA().colors().push_back(0);//9 wire color (can't see)
  mTess->arrayRGBA().colors().push_back(0);
  mTess->arrayRGBA().colors().push_back(0);

  polyWire->tessellation() = mTess;

  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
  return polyWire;
}

OdPrcProductOccurrencePtr CreateTopologyCommonForRI(OdPrcFilePtr &pFile, OdGeExtents3d &extents, OdPrcRepresentationItemPtr rI, OdPrcName name)
{
  OdPrcFileStructurePtr newStructure = pFile->fileStructures().last();

  // product occurrence section
  OdPrcProductOccurrencePtr newProductOccurrence = OdPrcProductOccurrence::createObject();
  newStructure->addObject(newProductOccurrence);

  // part definition section
  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(*newStructure, *newProductOccurrence);

  rI->name() = name;
  newStructure->addObject(rI);

  newDefinition->representationItem().push_back(rI->objectId());

  // file structure geometry section
  createTopoContext(*newStructure);

  // bounding box
  newDefinition->boundingBox().box() = extents;

  newStructure->fileStructureGlobals().colors().append()->set(0, 1, 0);

  return newProductOccurrence;
}

// main
void representationItemExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // common
  OdPrcName name;
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());

  OdPrcProductOccurrencePtr rootOccurrence = pFile->modelFileData().getStartRootOccurrences().last().openObject(kForWrite);
  OdPrcObjectIdArray &son_occurrences = rootOccurrence->referencesOfProductOccurrence().getSonProductOccurrences();

  OdPrcProductOccurrencePtr newProductOccurrence;
  switch (mode)
  {
    case kRepresentationItemPolyWire:
      name.setName(L"RepresentationItemPolyWire");  
      newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePolyWire(newStructure), name);
      break;
    case kRepresentationItemPointSet:
      name.setName(L"RepresentationItemPointSet");  
      newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePointSets(newStructure), name);
      break;
    case kRepresentationItemPolyBrepModel:
      name.setName(L"RepresentationItemPolyBrepModel");  
      newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePolyBrepModel(newStructure), name);
      break;
//     case kRepresentationItemDirection:
//       name.setName(L"RepresentationItemDirection");  
//       newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreateDirection(newStructure), name);
//       break;
//     case kRepresentationItemCoordinateSystem:
//       name.setName(L"RepresentationItemCoordinateSystem");  
//       newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreateCoordinateSystem(/*newStructure*/), name);
//       break;
    case kRepresentationItemSet:
      name.setName(L"RepresentationItemSet");  
      newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreateSet(newStructure), name);
      break;
    case kWireTessWithFlags:
      name.setName(L"3dWireTess with flags");  
      newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, Create3dPolyWireWithFlags(newStructure), name);
      break;
    default:
      ODA_ASSERT(false);
  }

  son_occurrences.push_back(newProductOccurrence->objectId());

  // export prc
  pFile->writeFile(pPrcStream);
}

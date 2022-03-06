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
#include "PrcPolyBrepModel.h"
#include "Prc3dTess.h"
#include "PrcMaterialGeneric.h"
#include "PrcPicture.h"
#include "PrcTextureApplication.h"
#include "OdPrcCreateStart.h"
#include "Ge/GeExtents3d.h"
#include "PrcCreateTopologyHelper.h"

OdPrcProductOccurrencePtr CreateTopologyCommonForRI(OdPrcFilePtr &pFile, OdGeExtents3d &extents, OdPrcRepresentationItemPtr rI, OdPrcName name);

OdPrcRepresentationItemPtr CreatePolyBrepModelTextured(OdPrcFileStructure &newStructure)
{
  OdPrcPolyBrepModelPtr polyBrep = OdPrcPolyBrepModel::createObject();

  //adding color
  OdPrcRgbColor color;
  color.set(0,0,1);
  newStructure.fileStructureGlobals().colors().push_back(color);
  color.set(0,1,0);
  newStructure.fileStructureGlobals().colors().push_back(color);
  color.set(1,0,0);
  newStructure.fileStructureGlobals().colors().push_back(color);

  //adding picture data to UBlock
  OdPrcUncompressedFiles unFile;
  OdBinaryData bit;
  bit.push_back(255);
  bit.push_back(0);
  bit.push_back(0);

  bit.push_back(0);
  bit.push_back(255);
  bit.push_back(0);

  bit.push_back(0);
  bit.push_back(0);
  bit.push_back(255);

  unFile.fileContents().push_back(bit);
  newStructure.uncompressedFiles() = unFile;

  //adding picture
  OdPrcPicturePtr picture = OdPrcPicture::createObject();
  picture->setFormat(2); //format = 2 -> RGB triplet picture
  picture->setPixelHeight(3);
  picture->setPixelWidth(1);

  picture->setUncompressedFileIndex(0);
  newStructure.fileStructureGlobals().pictures().push_back(picture);

  //adding textureDefinition
  OdPrcTextureDefinitionPtr texture = OdPrcTextureDefinition::createObject();
  newStructure.addObject(texture);
  texture->picture() = picture;
  texture->setTextureDimension(2); //must be 2
  OdPrcTextureMappingType tex_type;
  tex_type.eMappingType() = KEPRCTextureMappingType_Stored;
  texture->textureMappingType() = tex_type;
  
  texture->setTextureMappingAttributes(1);
  texture->textureMappingAttributesIntensities().push_back(1);
  texture->textureMappingAttributesComponents().push_back(8);
  texture->setTextureFunction(KEPRCTextureFunction_Unknown);
  texture->setTextureWrappingModeS(KEPRCTextureWrappingMode_Unknown);
  texture->setTextureWrappingModeT(KEPRCTextureWrappingMode_Unknown);
  newStructure.fileStructureGlobals().textureDefinitions().push_back(texture->objectId());

  //adding material
  OdPrcMaterialGenericPtr material = OdPrcMaterialGeneric::createObject();
  material->setAmbient(0);
  material->setAmbientAlpha(1);
  material->setDiffuse(2);
  material->setDiffuseAlpha(1);
  material->setEmissive(1);
  material->setEmissiveAlpha(1);
  material->setSpecular(0);
  material->setSpecularAlpha(0.2);
  material->setShininess(0);
  newStructure.addObject(material);
  newStructure.fileStructureGlobals().materials().push_back(material->objectId());

  //adding textureApplication (combine textureDefinition & material)
  OdPrcTextureApplicationPtr textureApp = OdPrcTextureApplication::createObject();
  newStructure.addObject(textureApp);
  textureApp->setMaterialGenericID(material->objectId());
  textureApp->setTextureDefinitionID(texture->objectId());

  //create style with textureApplication
  OdPrcObjectId newStyleId = OdPrcCategory1LineStyle::createByMaterial(textureApp->objectId(), newStructure);
  polyBrep->styleId() = newStyleId;
  polyBrep->setBehaviourBitField(PRC_GRAPHICS_Show);

  //crete tesselation for polyBrepModel
  OdPrc3dTessPtr mTess = createTess<OdPrc3dTess>(newStructure, *polyBrep);
  OdFloatArray arr;
  arr.push_back(-1);
  arr.push_back(-0.5);
  arr.push_back(0.0);

  arr.push_back(1);
  arr.push_back(-0.5);
  arr.push_back(0.0);

  arr.push_back(1);
  arr.push_back(0.5);
  arr.push_back(0.0);

  arr.push_back(-1);
  arr.push_back(0.5);
  arr.push_back(0.0);

  mTess->coordinates() = arr;
  mTess->setMustRecalculateNormals(true);
  mTess->triangulatedIndex().push_back(0);
  mTess->triangulatedIndex().push_back(0);
  mTess->triangulatedIndex().push_back(2);
  mTess->triangulatedIndex().push_back(3);
  mTess->triangulatedIndex().push_back(4);
  mTess->triangulatedIndex().push_back(6);
  mTess->triangulatedIndex().push_back(4);
  mTess->triangulatedIndex().push_back(6);
  mTess->triangulatedIndex().push_back(6);
  mTess->triangulatedIndex().push_back(9);
  mTess->triangulatedIndex().push_back(0);
  mTess->triangulatedIndex().push_back(0);

  OdPrcTessFace face;
  face.setUsedEntitiesFlag(PRC_FACETESSDATA_TriangleTextured);
  face.sizesTriangulated().push_back(2);
  face.setNumberOfTextureCoordinateIndexes(1);
  face.setBehaviour(1);

  mTess->faceTessellation().push_back(face);
  mTess->textureCoordinate().push_back(0);
  mTess->textureCoordinate().push_back(0);
  mTess->textureCoordinate().push_back(1);
  mTess->textureCoordinate().push_back(0);
  mTess->textureCoordinate().push_back(1);
  mTess->textureCoordinate().push_back(1);
  mTess->textureCoordinate().push_back(0);
  mTess->textureCoordinate().push_back(1);

  return polyBrep;
}


// main
void tessObjectTextureExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
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
    case kTessObjectTexture:
      name.setName(L"PolyBrepModelWithTexture");  
      newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePolyBrepModelTextured(newStructure), name);
      break;
    default:
      ODA_ASSERT(false);
  }

  son_occurrences.push_back(newProductOccurrence->objectId());

  // export prc
  pFile->writeFile(pPrcStream);
}


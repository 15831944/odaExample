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
#include "RxObject.h"
#include "DbHostAppServices.h"
#include "AppServices/PrcHostAppServices.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcCreateMeshHelper.h"
#include "Prc3dTess.h"
#include "PrcPolyBrepModel.h"
#include "PrcMaterial.h"
#include "PrcMaterialGeneric.h"
#include "PrcTextureApplication.h"
#include "PrcTextureDefinition.h"
#include "RxVariantValue.h"
#include "RxDictionary.h"
#include "RxSystemServices.h"
#include "RxRasterServices.h"
#include "RxVariantValue.h"
#include "DynamicLinker.h"
#include "MemoryStream.h"
#include "ExPrintConsole.h"
#include "PrcExport.h"
#include "PdfExportService.h"
#include "PrcExportContext.h"

void addSimpleTriangle(TriangleInfoPtrArray &mesh,
                double nx, double ny, double nz,
                double p1x, double p1y, double p1z,
                double p2x, double p2y, double p2z,
                double p3x, double p3y, double p3z,
                OdUInt8 r, OdUInt8 g, OdUInt8 b)
{
  TriangleInfoPtr ptmp = new TriangleInfo();
  TriangleInfo &tmp = *(TriangleInfo*)ptmp.get();

  tmp.vtx_normal[0].x = nx;
  tmp.vtx_normal[0].y = ny;
  tmp.vtx_normal[0].z = nz;

  tmp.vtx_normal[1].x = nx;
  tmp.vtx_normal[1].y = ny;
  tmp.vtx_normal[1].z = nz;

  tmp.vtx_normal[2].x = nx;
  tmp.vtx_normal[2].y = ny;
  tmp.vtx_normal[2].z = nz;

  tmp.p1.x = p1x;
  tmp.p1.y = p1y;
  tmp.p1.z = p1z;

  tmp.p2.x = p2x;
  tmp.p2.y = p2y;
  tmp.p2.z = p2z;

  tmp.p3.x = p3x;
  tmp.p3.y = p3y;
  tmp.p3.z = p3z;

  tmp.color.setRGB(r,g,b);
  mesh.push_back(ptmp);
}

// main
//#1: all bodies into one prc tess
void createTessExampleSingleTess (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // setup
  TriangleInfoPtrArray mesh;

  // start add objects to prc file (as tessellation)
  OdUInt32 countOfObjects = 1000;
  OdUInt32 objectsPerRow = 10;
  OdUInt32 dx = 2;
  OdUInt32 dy = 2;
  OdUInt32 shift_x = 0; // distance between boxes
  OdUInt32 shift_y = 0;
  for (OdUInt32 idx = 0; idx < (countOfObjects/objectsPerRow); ++idx)
  {
  for (OdUInt32 j = 0; j < objectsPerRow; ++j)
  {
    // - fill the tess representation of the body
    addSimpleTriangle(mesh, 0,0,-1, 0+shift_x,0+shift_y,0, 1+shift_x,1+shift_y,0, 1+shift_x,0+shift_y,0, 255,0,0);
    addSimpleTriangle(mesh, 0,0,-1, 1+shift_x,1+shift_y,0, 0+shift_x,0+shift_y,0, 0+shift_x,1+shift_y,0, 128,0,0);
                            
    addSimpleTriangle(mesh, 0,0,1, 1+shift_x,0+shift_y,1, 1+shift_x,1+shift_y,1, 0+shift_x,0+shift_y,1, 0,255,0);
    addSimpleTriangle(mesh, 0,0,1, 0+shift_x,1+shift_y,1, 0+shift_x,0+shift_y,1, 1+shift_x,1+shift_y,1, 0,128,0);
                            
    addSimpleTriangle(mesh, 0,1,0, 0+shift_x,1+shift_y,0, 1+shift_x,1+shift_y,1, 1+shift_x,1+shift_y,0, 0,0,255);
    addSimpleTriangle(mesh, 0,1,0, 1+shift_x,1+shift_y,1, 0+shift_x,1+shift_y,0, 0+shift_x,1+shift_y,1, 0,0,128);
                            
    addSimpleTriangle(mesh, 0,-1,0, 1+shift_x,0+shift_y,0, 1+shift_x,0+shift_y,1, 0+shift_x,0+shift_y,0, 255,255,0);
    addSimpleTriangle(mesh, 0,-1,0, 0+shift_x,0+shift_y,1, 0+shift_x,0+shift_y,0, 1+shift_x,0+shift_y,1, 128,128,0);
                            
    addSimpleTriangle(mesh, 1,0,0, 1+shift_x,1+shift_y,1, 1+shift_x,0+shift_y,0, 1+shift_x,1+shift_y,0, 0,255,255);
    addSimpleTriangle(mesh, 1,0,0, 1+shift_x,0+shift_y,0, 1+shift_x,1+shift_y,1, 1+shift_x,0+shift_y,1, 0,128,128);
                            
    addSimpleTriangle(mesh, -1,0,0, 0+shift_x,0+shift_y,0, 0+shift_x,1+shift_y,1, 0+shift_x,1+shift_y,0, 255,0,255);
    addSimpleTriangle(mesh, -1,0,0, 0+shift_x,1+shift_y,1, 0+shift_x,0+shift_y,0, 0+shift_x,0+shift_y,1, 128,0,128);

    shift_x = (shift_x + dx);
  }
    
  shift_y += dy;
  shift_x = 0;
  }

  // load module
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName, true);
  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();

  // write data into stream
  PDF2PRCExportParams params;
  params.m_exportAsBrep = false;
  OdRxObjectPtr pContext = pExportIFace->createPrcExportContext(NULL);
  OdResult res = exportMeshToPrc(mesh, pContext);
  if (res != eOk)
  {
    throw res;
  }
  res = pExportIFace->serialize(pPrcStream, pContext, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
}


//#2: each body to its own prc tess
void createTessExampleMultiTess (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName);

  // setup
  // - prc file
  OdPrcFilePtr newFile = createTopologyCommon();
  
  // create model topology for tessellation
  OdPrcFileStructure &newStructure = *newFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(newStructure, *pRootPO);

  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();
  OdPrcExportContextPtr pContext = pExportIFace->createPrcExportContext(NULL);

  // start add objects to prc file (as tessellation)
  OdUInt32 countOfObjects = 1000;
  OdUInt32 objectsPerRow = 10;
  OdUInt32 dx = 2;
  OdUInt32 dy = 2;
  OdUInt32 shift_x = 0; // distance between boxes
  OdUInt32 shift_y = 0;
  for (OdUInt32 idx = 0; idx < (countOfObjects/objectsPerRow); ++idx)
  {
    for (OdUInt32 j = 0; j < objectsPerRow; ++j)
    {
      TriangleInfoPtrArray mesh;
      // - fill the tess representation of the body
      addSimpleTriangle(mesh, 0,0,-1, 0+shift_x,0+shift_y,0, 1+shift_x,1+shift_y,0, 1+shift_x,0+shift_y,0, 255,0,0);
      addSimpleTriangle(mesh, 0,0,-1, 1+shift_x,1+shift_y,0, 0+shift_x,0+shift_y,0, 0+shift_x,1+shift_y,0, 128,0,0);

      addSimpleTriangle(mesh, 0,0,1, 1+shift_x,0+shift_y,1, 1+shift_x,1+shift_y,1, 0+shift_x,0+shift_y,1, 0,255,0);
      addSimpleTriangle(mesh, 0,0,1, 0+shift_x,1+shift_y,1, 0+shift_x,0+shift_y,1, 1+shift_x,1+shift_y,1, 0,128,0);

      addSimpleTriangle(mesh, 0,1,0, 0+shift_x,1+shift_y,0, 1+shift_x,1+shift_y,1, 1+shift_x,1+shift_y,0, 0,0,255);
      addSimpleTriangle(mesh, 0,1,0, 1+shift_x,1+shift_y,1, 0+shift_x,1+shift_y,0, 0+shift_x,1+shift_y,1, 0,0,128);

      addSimpleTriangle(mesh, 0,-1,0, 1+shift_x,0+shift_y,0, 1+shift_x,0+shift_y,1, 0+shift_x,0+shift_y,0, 255,255,0);
      addSimpleTriangle(mesh, 0,-1,0, 0+shift_x,0+shift_y,1, 0+shift_x,0+shift_y,0, 1+shift_x,0+shift_y,1, 128,128,0);

      addSimpleTriangle(mesh, 1,0,0, 1+shift_x,1+shift_y,1, 1+shift_x,0+shift_y,0, 1+shift_x,1+shift_y,0, 0,255,255);
      addSimpleTriangle(mesh, 1,0,0, 1+shift_x,0+shift_y,0, 1+shift_x,1+shift_y,1, 1+shift_x,0+shift_y,1, 0,128,128);

      addSimpleTriangle(mesh, -1,0,0, 0+shift_x,0+shift_y,0, 0+shift_x,1+shift_y,1, 0+shift_x,1+shift_y,0, 255,0,255);
      addSimpleTriangle(mesh, -1,0,0, 0+shift_x,1+shift_y,1, 0+shift_x,0+shift_y,0, 0+shift_x,0+shift_y,1, 128,0,128);

      shift_x = (shift_x + dx);

      OdPrcPolyBrepModelPtr newPolyBrep = createRI<OdPrcPolyBrepModel>(newStructure, *pPD);

      // - write tess into prc file
      fillTessellation(newStructure, mesh, *pContext);
      newPolyBrep->tessellation() = newStructure.fileStructureTessellation().tessellations().last();

      // - bounding box
      OdGeExtents3d extents;
      meshExtents(mesh, extents);
      pPD->boundingBox().box() = extents;
    }

    shift_y += dy;
    shift_x = 0;
  }

  // write file
  try
  {
    OdPrcFileSettings pSettings = OdPrcFileSettings();
    newFile->writeFile(pPrcStream, &pSettings);
  }
  catch(OdError &e)
  {
    throw e.code();
  }
  catch(...)
  {
    throw eExtendedError;
  }
}

//#3 textured tess
static void add_with_texture(TriangleInfoPtrArray &mesh,
  double nx, double ny, double nz,
  double p1x, double p1y, double p1z,
  double p2x, double p2y, double p2z,
  double p3x, double p3y, double p3z,
  double t1x, double t1y,
  double t2x, double t2y,
  double t3x, double t3y
  )
{
  TriangleInfoPtr ptmp = new TriangleInfoTextured();
  TriangleInfoTextured &tmp = *(TriangleInfoTextured*)ptmp.get();

  tmp.vtx_normal[0].x = nx;
  tmp.vtx_normal[0].y = ny;
  tmp.vtx_normal[0].z = nz;

  tmp.vtx_normal[1].x = nx;
  tmp.vtx_normal[1].y = ny;
  tmp.vtx_normal[1].z = nz;

  tmp.vtx_normal[2].x = nx;
  tmp.vtx_normal[2].y = ny;
  tmp.vtx_normal[2].z = nz;

  tmp.p1.x = p1x;
  tmp.p1.y = p1y;
  tmp.p1.z = p1z;

  tmp.p2.x = p2x;
  tmp.p2.y = p2y;
  tmp.p2.z = p2z;

  tmp.p3.x = p3x;
  tmp.p3.y = p3y;
  tmp.p3.z = p3z;

  tmp.texCoords[0].x = t1x;
  tmp.texCoords[0].y = t1y;
  tmp.texCoords[1].x = t2x;
  tmp.texCoords[1].y = t2y;
  tmp.texCoords[2].x = t3x;
  tmp.texCoords[2].y = t3y;

  mesh.push_back(ptmp);
}

OdString correctPath(const OdString& filePath)
{
  OdRxSystemServices* pSs = odrxSystemServices();
  if (pSs)
  {
    OdString validPath = filePath;
    if (pSs->accessFile(validPath, Oda::kFileRead))
      return validPath; // Found path as is.
#if defined(ODA_WINDOWS)
    validPath.insert(0, "Prc\\Examples\\OdPrcCreate\\");
#else
    validPath.insert(0, "Prc/Examples/OdPrcCreate/");
#endif
    if (pSs->accessFile(validPath, Oda::kFileRead))
      return validPath;
    for (OdUInt32 i = 0; i < 6; i++)
    {
#if defined(ODA_WINDOWS)
      validPath.insert(0, "..\\");
#else
      validPath.insert(0, "../");
#endif
      if (pSs->accessFile(validPath, Oda::kFileRead))
        return validPath;
    }
  }
  return OdString::kEmpty; // not found
}

void tessExampleTextured(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName);

  // setup
  // - prc file
  OdPrcFilePtr newFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *newFile->fileStructures().last();

  // create mesh
  TriangleInfoPtrArray mesh;
  add_with_texture(mesh, 0, 0, -1,   0, 0, 0,  1, 1, 0,  1, 0, 0,       1, 0,  0, 1,  0, 0);
  add_with_texture(mesh, 0, 0, -1,   1, 1, 0,  0, 0, 0,  0, 1, 0,       0, 1,  1, 0,  1, 1);
                         
  add_with_texture(mesh, 0, 0, 1,    1, 0, 1, 1, 1, 1, 0, 0, 1,       0, 0,  1, 0,  0, 1);
  add_with_texture(mesh, 0, 0, 1,    0, 1, 1, 0, 0, 1, 1, 1, 1,       1, 1,  0, 1,  1, 0);
                         
  add_with_texture(mesh, 0, 1, 0,    0, 1, 0,  1, 1, 1,  1, 1, 0,       0, 1,  1, 0,  1, 1);
  add_with_texture(mesh, 0, 1, 0,    1, 1, 1,  0, 1, 0,  0, 1, 1,       1, 0,  0, 1,  0, 0);
                         
  add_with_texture(mesh, 0, -1, 0,   1, 0, 0, 1, 0, 1, 0, 0, 0,       0, 0,  1, 0,  0, 1);
  add_with_texture(mesh, 0, -1, 0,   0, 0, 1, 0, 0, 0, 1, 0, 1,       1, 1,  0, 1,  1, 0);
                         
  add_with_texture(mesh, 1, 0, 0,    1, 1, 1,  1, 0, 0,  1, 1, 0,       1, 1,  0, 0,  1, 0);
  add_with_texture(mesh, 1, 0, 0,    1, 0, 0,  1, 1, 1,  1, 0, 1,       0, 0,  1, 1,  0, 1);
                         
  add_with_texture(mesh, -1, 0, 0,   0, 0, 0,  0, 1, 1,  0, 1, 0,       0, 0,  1, 1,  1, 0);
  add_with_texture(mesh, -1, 0, 0,   0, 1, 1,  0, 0, 0,  0, 0, 1,       1, 1,  0, 0,  0, 1);
  
  // create material line style
  OdPrcObjectId materialLineStyleID;
  {
    // - material generic
    OdPrcMaterialGenericPtr pMat = OdPrcMaterialGeneric::createObject();
    newStructure.addObject(pMat);
    // - - set material params
    OdPrcRgbColorArray &colorArr = newStructure.fileStructureGlobals().colors();
    colorArr.append()->set(1, 1, 1); // this colors are used as parameters of material
    colorArr.append()->set(0, 0, 0);
    pMat->setAmbient(0); // index of color in color array is set here
    pMat->setDiffuse(0);
    pMat->setEmissive(1);
    pMat->setSpecular(0);
    pMat->setShininess(0.85f); // regular params here and below
    pMat->setAmbientAlpha(1);
    pMat->setDiffuseAlpha(1);
    pMat->setEmissiveAlpha(1);
    pMat->setSpecularAlpha(1);
    newStructure.fileStructureGlobals().materials().push_back(pMat->id());

    // - texture definition
    OdPrcTextureDefinitionPtr pTextureDef = OdPrcTextureDefinition::createObject();
    newStructure.addObject(pTextureDef);
    newStructure.fileStructureGlobals().textureDefinitions().push_back(pTextureDef->id());
    // - - set texture definition
    OdDbBaseDatabase* pDb = ((OdPrcObjectId)pTextureDef->id()).database();
    OdString textureName = pPrcHost.findFile("dbgtexture.png", pDb, OdDbBaseHostAppServices::kTextureMapFile); // set path to texture picture here
    if (textureName.isEmpty())
    {
      textureName = correctPath("dbgtexture.png");
      if (textureName.isEmpty())
      {
        // you should make sure that the path you defined ("dbgtexture.png") to the picture is valid and the picture is on the disk.
        // please copy "dbgtexture.png" from "Examples\OdPrcCreate" to a folder from the support path.
        odPrintConsoleString(L"\nPicture for texture not found!!!\nPlease copy \"dbgtexture.png\" from \"Examples\\OdPrcCreate\" to a folder from the support path.");
        throw OdError(eInvalidInput);
      }
    }
    OdPrcPicturePtr pPicture = OdPrcPicture::createByImage(textureName, newStructure);
    if (pPicture.isNull())
    {
      throw OdError(eInvalidInput);
    }
    // - - texture dimension
    pTextureDef->setTextureDimension(2); // 1 and 3 are possible values, but they are not used in prc standard now
    // - - texture mapping type
    pTextureDef->textureMappingType().eMappingType() = /*KEPRCTextureMappingType_Unknown;*/ KEPRCTextureMappingType_Stored;
    // - - texture mapping attributes
    pTextureDef->setTextureMappingAttributes(PRC_TEXTURE_MAPPING_DIFFUSE); // only PRC_TEXTURE_MAPPING_DIFFUSE, PRC_TEXTURE_MAPPING_SPHERICAL_REFLECTION and PRC_TEXTURE_MAPPING_CUBICAL_REFLECTION are currently supported by PRC
    pTextureDef->textureMappingAttributesIntensities().push_back(1.0f);
    pTextureDef->textureMappingAttributesComponents().push_back(PRC_TEXTURE_MAPPING_COMPONENTS_RGB);
    // - - texture function
    pTextureDef->setTextureFunction(KEPRCTextureFunction_Modulate); // NOTE! Contradicting documentation data!
    // - - blend
    pTextureDef->setBlendSrcRgb(KEPRCTextureBlendParameter_Unknown);
    pTextureDef->setBlendSrcAlpha(KEPRCTextureBlendParameter_Unknown);
    // - - texture applying mode
    pTextureDef->setTextureApplyingMode(PRC_TEXTURE_APPLYING_MODE_NONE /*PRC_TEXTURE_APPLYING_MODE_LIGHTING*/);
    // - - texture wrapping mode
    pTextureDef->setTextureWrappingModeS(KEPRCTextureWrappingMode_Repeat);
    pTextureDef->setTextureWrappingModeT(KEPRCTextureWrappingMode_Repeat);
    // - - texture transformation
    pTextureDef->removeTextureTransformation();
    pTextureDef->picture() = pPicture;

    // - texture application
    OdPrcTextureApplicationPtr pTextureApp = OdPrcTextureApplication::createObject();
    newStructure.addObject(pTextureApp);
    pTextureApp->setTextureDefinitionID(pTextureDef->id());
    pTextureApp->setMaterialGenericID(pMat->id());

    // material line style
    materialLineStyleID = OdPrcCategory1LineStyle::createByMaterial(pTextureApp->id(), newStructure); // add line style to prc file;
  }
  // open line style by this id and set transparency there
  // ...

  // create poly brep topology
  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(newStructure, *pRootPO);
  OdPrcPolyBrepModelPtr newBrep = createRI<OdPrcPolyBrepModel>(newStructure, *pPD);

  // set material for this poly brep
  newBrep->styleId() = materialLineStyleID;
  newBrep->setBehaviourBitField(PRC_GRAPHICS_Show);

  // create prc tessellation and set it for this poly brep
  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();
  OdPrcExportContextPtr pContext = pExportIFace->createPrcExportContext(NULL);
  newBrep->tessellation() = fillTessellation(newStructure, mesh, *pContext);

  // write file
  try
  {
    OdPrcFileSettings pSettings = OdPrcFileSettings();
    newFile->writeFile(pPrcStream, &pSettings);
  }
  catch (OdError &e)
  {
    throw e.code();
  }
  catch (...)
  {
    throw eExtendedError;
  }
}

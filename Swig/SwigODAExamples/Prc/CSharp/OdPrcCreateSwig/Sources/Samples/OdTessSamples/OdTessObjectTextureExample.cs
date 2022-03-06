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
using OdPrcCreateSwigMgd.Samples.OdRepresentationItemSamples;
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdTessSamples
{
  public class OdTessExample_TessObjectTexture : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Textured polyBrepModel textured example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // common
      OdPrcName name = new OdPrcName();
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(0, 0, 0));
      extents.addPoint(new OdGePoint3d(1, 1, 1));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      OdPrcObjectIdArray getStartRootOccurrences = pFile.modelFileData().getStartRootOccurrences();
      OdPrcProductOccurrence rootOccurrence = getStartRootOccurrences[getStartRootOccurrences.Count - 1].openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcObjectIdArray son_occurrences = rootOccurrence.referencesOfProductOccurrence().getSonProductOccurrences();

      OdPrcProductOccurrence newProductOccurrence = null;
      switch (mode)
      {
        case OdPrcCreateSwigMgd_ExampleModes.TessObjectTexture:
          name.setName("PolyBrepModelWithTexture");
          newProductOccurrence = OdRepresentationItemExample.CreateTopologyCommonForRI(pFile, extents, CreatePolyBrepModelTextured(newStructure), name);
          break;
        default:
          OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
          break;
      }

      son_occurrences.Add(newProductOccurrence.objectId());

      // export prc
      pFile.writeFile(pPrcStream);
    }

    OdPrcRepresentationItem CreatePolyBrepModelTextured(OdPrcFileStructure newStructure)
    {
      OdPrcPolyBrepModel polyBrep = OdPrcPolyBrepModel.createObject();

      //adding color
      OdPrcRgbColor color = new OdPrcRgbColor();
      color.set(0, 0, 1);
      newStructure.fileStructureGlobals().colors().Add(color);
      color.set(0, 1, 0);
      newStructure.fileStructureGlobals().colors().Add(color);
      color.set(1, 0, 0);
      newStructure.fileStructureGlobals().colors().Add(color);

      //adding picture data to UBlock
      OdPrcUncompressedFiles unFile = new OdPrcUncompressedFiles();
      OdBinaryData bit = new OdBinaryData();
      bit.Add(255);
      bit.Add(0);
      bit.Add(0);

      bit.Add(0);
      bit.Add(255);
      bit.Add(0);

      bit.Add(0);
      bit.Add(0);
      bit.Add(255);

      unFile.fileContents().Add(bit);
      newStructure.setuncompressedFiles(unFile);

      //adding picture
      OdPrcPicture picture = OdPrcPicture.createObject();
      picture.setFormat(2); //format = 2 . RGB triplet picture
      picture.setPixelHeight(3);
      picture.setPixelWidth(1);

      picture.setUncompressedFileIndex(0);
      newStructure.fileStructureGlobals().pictures().Add(picture);

      //adding textureDefinition
      OdPrcTextureDefinition texture = OdPrcTextureDefinition.createObject();
      newStructure.addObject(texture);
      texture.setpicture(picture);
      texture.setTextureDimension(2); //must be 2
      OdPrcTextureMappingType tex_type = new OdPrcTextureMappingType();
      tex_type.seteMappingType(EPRCTextureMappingType.KEPRCTextureMappingType_Stored);
      texture.settextureMappingType(tex_type);

      texture.setTextureMappingAttributes(1);
      texture.textureMappingAttributesIntensities().Add(1);
      texture.textureMappingAttributesComponents().Add((char)8);
      texture.setTextureFunction((uint)EPRCTextureFunction.KEPRCTextureFunction_Unknown);
      texture.setTextureWrappingModeS((uint)EPRCTextureWrappingMode.KEPRCTextureWrappingMode_Unknown);
      texture.setTextureWrappingModeT((uint)EPRCTextureWrappingMode.KEPRCTextureWrappingMode_Unknown);
      newStructure.fileStructureGlobals().textureDefinitions().Add(texture.objectId());

      //adding material
      OdPrcMaterialGeneric material = OdPrcMaterialGeneric.createObject();
      material.setAmbient( new OdPrcColorIndex(0));
      material.setAmbientAlpha(1);
      material.setDiffuse(new OdPrcColorIndex(2));
      material.setDiffuseAlpha(1);
      material.setEmissive(new OdPrcColorIndex(1));
      material.setEmissiveAlpha(1);
      material.setSpecular(new OdPrcColorIndex(0));
      material.setSpecularAlpha(0.2);
      material.setShininess(0);
      newStructure.addObject(material);
      newStructure.fileStructureGlobals().materials().Add(material.objectId());

      //adding textureApplication (combine textureDefinition  material)
      OdPrcTextureApplication textureApp = OdPrcTextureApplication.createObject();
      newStructure.addObject(textureApp);
      textureApp.setMaterialGenericID(material.objectId());
      textureApp.setTextureDefinitionID(texture.objectId());

      //create style with textureApplication
      OdPrcObjectId newStyleId = OdPrcCategory1LineStyle.createByMaterial(textureApp.objectId(), newStructure);
      polyBrep.setstyleId(newStyleId);
      polyBrep.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_Show);

      //crete tesselation for polyBrepModel
      OdPrc3dTess mTess = OdPrcCreateTopologyHelper.createTess<OdPrc3dTess>(newStructure, polyBrep);
      OdFloatArray arr = new OdFloatArray();
      arr.Add((float)-1);
      arr.Add((float)-0.5);
      arr.Add((float)0.0);

      arr.Add((float)1);
      arr.Add((float)-0.5);
      arr.Add((float)0.0);

      arr.Add((float)1);
      arr.Add((float)0.5);
      arr.Add((float)0.0);

      arr.Add((float)-1);
      arr.Add((float)0.5);
      arr.Add((float)0.0);

      mTess.setcoordinates(arr);
      mTess.setMustRecalculateNormals(true);
      mTess.triangulatedIndex().Add(0);
      mTess.triangulatedIndex().Add(0);
      mTess.triangulatedIndex().Add(2);
      mTess.triangulatedIndex().Add(3);
      mTess.triangulatedIndex().Add(4);
      mTess.triangulatedIndex().Add(6);
      mTess.triangulatedIndex().Add(4);
      mTess.triangulatedIndex().Add(6);
      mTess.triangulatedIndex().Add(6);
      mTess.triangulatedIndex().Add(9);
      mTess.triangulatedIndex().Add(0);
      mTess.triangulatedIndex().Add(0);

      OdPrcTessFace face = new OdPrcTessFace();
      face.setUsedEntitiesFlag(PRC_Globals.PRC_FACETESSDATA_TriangleTextured);
      face.sizesTriangulated().Add(2);
      face.setNumberOfTextureCoordinateIndexes(1);
      face.setBehaviour(1);

      mTess.faceTessellation().Add(face);
      mTess.textureCoordinate().Add(0);
      mTess.textureCoordinate().Add(0);
      mTess.textureCoordinate().Add(1);
      mTess.textureCoordinate().Add(0);
      mTess.textureCoordinate().Add(1);
      mTess.textureCoordinate().Add(1);
      mTess.textureCoordinate().Add(0);
      mTess.textureCoordinate().Add(1);

      return polyBrep;
    }
  }
}

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
using System;
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdTessSamples
{
  public class OdTessExample_TessExample3 : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Textured box example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport");

      // setup
      // - prc file
      OdPrcFile newFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = newFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      // create mesh
      TriangleInfoPtrArray mesh = new TriangleInfoPtrArray();
      add_with_texture(mesh, 0, 0, -1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0);
      add_with_texture(mesh, 0, 0, -1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1);

      add_with_texture(mesh, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1);
      add_with_texture(mesh, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0);

      add_with_texture(mesh, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1);
      add_with_texture(mesh, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0);

      add_with_texture(mesh, 0, -1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1);
      add_with_texture(mesh, 0, -1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0);

      add_with_texture(mesh, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0);
      add_with_texture(mesh, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1);

      add_with_texture(mesh, -1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0);
      add_with_texture(mesh, -1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1);

      // create material line style
      OdPrcObjectId materialLineStyleID;
      {
        // - material generic
        OdPrcMaterialGeneric pMat = OdPrcMaterialGeneric.createObject();
        newStructure.addObject(pMat);
        // - - set material params
        OdPrcRgbColorArray colorArr = newStructure.fileStructureGlobals().colors();
        OdPrcRgbColor c1 = new OdPrcRgbColor(1, 1, 1);
        OdPrcRgbColor c2 = new OdPrcRgbColor(0, 0, 0);
        colorArr.Add(c1); // this colors are used as parameters of material
        colorArr.Add(c2);
        pMat.setAmbient(new OdPrcColorIndex(0)); // index of color in color array is set here
        pMat.setDiffuse(new OdPrcColorIndex(0));
        pMat.setEmissive(new OdPrcColorIndex(1));
        pMat.setSpecular(new OdPrcColorIndex(0));
        pMat.setShininess(0.85f); // regular params here and below
        pMat.setAmbientAlpha(1);
        pMat.setDiffuseAlpha(1);
        pMat.setEmissiveAlpha(1);
        pMat.setSpecularAlpha(1);
        newStructure.fileStructureGlobals().materials().Add(new OdPrcObjectId(pMat.id()));

        // - texture definition
        OdPrcTextureDefinition pTextureDef = OdPrcTextureDefinition.createObject();
        newStructure.addObject(pTextureDef);
        newStructure.fileStructureGlobals().textureDefinitions().Add(new OdPrcObjectId(pTextureDef.id()));
        // - - set texture definition
        OdDbDatabase pDb = (new OdPrcObjectId(pTextureDef.id())).database() as OdDbDatabase;
        String textureName = pPrcHost.findFile("dbgtexture.png", pDb, OdDbBaseHostAppServices.FindFileHint.kTextureMapFile); // set path to texture picture here
        if (String.IsNullOrEmpty(textureName))
        {
          textureName = correctPath("dbgtexture.png");
          if (String.IsNullOrEmpty(textureName))
          {
            // you should make sure that the path you defined ("dbgtexture.png") to the picture is valid and the picture is on the disk.
            // please copy "dbgtexture.png" from "Examples\OdPrcCreate" to a folder from the support path.
            Console.WriteLine("\nPicture for texture not found!!!\nPlease copy \"dbgtexture.png\" from \"Examples\\OdPrcCreate\" to a folder from the support path.");
            throw new OdError(OdResult.eInvalidInput);
          }
        }
        OdPrcPicture pPicture = OdPrcPicture.createByImage(textureName, newStructure);
        if (pPicture == null)
        {
          throw new OdError(OdResult.eInvalidInput);
        }
        // - - texture dimension
        pTextureDef.setTextureDimension(2); // 1 and 3 are possible values, but they are not used in prc standard now
                                            // - - texture mapping type
        pTextureDef.textureMappingType().seteMappingType(/*KEPRCTextureMappingType_Unknown;*/ EPRCTextureMappingType.KEPRCTextureMappingType_Stored);
        // - - texture mapping attributes
        pTextureDef.setTextureMappingAttributes(PRC_Globals.PRC_TEXTURE_MAPPING_DIFFUSE); // only PRC_TEXTURE_MAPPING_DIFFUSE, PRC_TEXTURE_MAPPING_SPHERICAL_REFLECTION and PRC_TEXTURE_MAPPING_CUBICAL_REFLECTION are currently supported by PRC
        pTextureDef.textureMappingAttributesIntensities().Add(1.0f);
        pTextureDef.textureMappingAttributesComponents().Add((char)PRC_Globals.PRC_TEXTURE_MAPPING_COMPONENTS_RGB);
        // - - texture function
        pTextureDef.setTextureFunction((uint)EPRCTextureFunction.KEPRCTextureFunction_Modulate); // NOTE! Contradicting documentation data!
                                                                                                 // - - blend
        pTextureDef.setBlendSrcRgb((uint)EPRCTextureBlendParameter.KEPRCTextureBlendParameter_Unknown);
        pTextureDef.setBlendSrcAlpha((uint)EPRCTextureBlendParameter.KEPRCTextureBlendParameter_Unknown);
        // - - texture applying mode
        pTextureDef.setTextureApplyingMode(PRC_Globals.PRC_TEXTURE_APPLYING_MODE_NONE /*PRC_TEXTURE_APPLYING_MODE_LIGHTING*/);
        // - - texture wrapping mode
        pTextureDef.setTextureWrappingModeS((uint)EPRCTextureWrappingMode.KEPRCTextureWrappingMode_Repeat);
        pTextureDef.setTextureWrappingModeT((uint)EPRCTextureWrappingMode.KEPRCTextureWrappingMode_Repeat);
        // - - texture transformation
        pTextureDef.removeTextureTransformation();
        pTextureDef.setpicture(pPicture);

        // - texture application
        OdPrcTextureApplication pTextureApp = OdPrcTextureApplication.createObject();
        newStructure.addObject(pTextureApp);
        pTextureApp.setTextureDefinitionID(new OdPrcObjectId(pTextureDef.id()));
        pTextureApp.setMaterialGenericID(new OdPrcObjectId(pMat.id()));

        // material line style
        materialLineStyleID = OdPrcCategory1LineStyle.createByMaterial(new OdPrcObjectId(pTextureApp.id()), newStructure); // add line style to prc file;
      }
      // open line style by this id and set transparency there
      // ...

      // create poly brep topology
      OdPrcProductOccurrence pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, pRootPO);
      OdPrcPolyBrepModel newBrep = OdPrcCreateTopologyHelper.createRI<OdPrcPolyBrepModel>(newStructure, pPD);

      // set material for this poly brep
      newBrep.setstyleId(materialLineStyleID);
      newBrep.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_Show);

      // create prc tessellation and set it for this poly brep
      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();
      OdPrcExportContext pContext = pExportIFace.createPrcExportContext(null) as OdPrcExportContext;
      newBrep.settessellation(OdPrcCreateTopologyHelper.fillTessellation(newStructure, mesh, pContext));

      // write file
      try
      {
        OdPrcFileSettings pSettings = new OdPrcFileSettings();
        newFile.writeFile(pPrcStream, pSettings);
      }
      catch (OdError e)
      {
        throw e;
      }
      catch (Exception)
      {
        throw new OdError(OdResult.eExtendedError);
      }
    }

    private static void add_with_texture(TriangleInfoPtrArray mesh,
        double nx, double ny, double nz,
        double p1x, double p1y, double p1z,
        double p2x, double p2y, double p2z,
        double p3x, double p3y, double p3z,
        double t1x, double t1y,
        double t2x, double t2y,
        double t3x, double t3y)
    {
      TriangleInfoTextured tmp = new TriangleInfoTextured();

      var v1 = new OdGeVector3d(nx, ny, nz);
      var v2 = new OdGeVector3d(nx, ny, nz);
      var v3 = new OdGeVector3d(nx, ny, nz);
      GC.SuppressFinalize(v1);
      GC.SuppressFinalize(v2);
      GC.SuppressFinalize(v3);
      tmp.Set_vtx_normal(v1, v2, v3);

      tmp.p1.x = (float)p1x;
      tmp.p1.y = (float)p1y;
      tmp.p1.z = (float)p1z;

      tmp.p2.x = (float)p2x;
      tmp.p2.y = (float)p2y;
      tmp.p2.z = (float)p2z;

      tmp.p3.x = (float)p3x;
      tmp.p3.y = (float)p3y;
      tmp.p3.z = (float)p3z;

      var p1 = new OdGePoint2d(t1x, t1y);
      var p2 = new OdGePoint2d(t2x, t2y);
      var p3 = new OdGePoint2d(t3x, t3y);
      GC.SuppressFinalize(p1);
      GC.SuppressFinalize(p2);
      GC.SuppressFinalize(p3);
      tmp.SetTexCoords(p1, p2, p3);

      GC.SuppressFinalize(tmp);
      mesh.Add(tmp);
    }

    private static String correctPath(String filePath)
    {
      unchecked
      {
        OdRxSystemServices pSs = Globals.odrxSystemServices();
        if (pSs != null)
        {
          String validPath = filePath;
          if (pSs.accessFile(validPath, (int)FileAccessMode.kFileRead))
            return validPath; // Found path as is.

          validPath.Insert(0, @"Prc/Examples/OdPrcCreate/");

          if (pSs.accessFile(validPath, (int)FileAccessMode.kFileRead))
            return validPath;

          for (int i = 0; i < 6; i++)
          {
            validPath.Insert(0, "../");
            if (pSs.accessFile(validPath, (int)FileAccessMode.kFileRead))
              return validPath;
          }
        }
      }
      return String.Empty; // not found
    }
  }
}

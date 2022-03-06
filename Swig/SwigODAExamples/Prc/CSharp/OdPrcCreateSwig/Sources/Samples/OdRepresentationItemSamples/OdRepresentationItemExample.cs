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
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdRepresentationItemSamples
{

  public class OdRepresentationItemExample_RepresentationItemPolyWire : OdRepresentationItemExample
  {
    public override string Description
    {
      get
      {
        return "Representation item polyWire example";
      }
    }
  }

  public class OdRepresentationItemExample_RepresentationItemPointSet : OdRepresentationItemExample
  {
    public override string Description
    {
      get
      {
        return "Representation item pointSet example";
      }
    }
  }

  public class OdRepresentationItemExample_RepresentationItemPolyBrepModel : OdRepresentationItemExample
  {
    public override string Description
    {
      get
      {
        return "Representation item polyBrepModel example";
      }
    }
  }

  public class OdRepresentationItemExample_RepresentationItemSet : OdRepresentationItemExample
  {
    public override string Description
    {
      get
      {
        return "Representation item with all RI type example";
      }
    }
  }

  public class OdRepresentationItemExample_WireTessWithFlags : OdRepresentationItemExample
  {
    public override string Description
    {
      get
      {
        return "3d polywire with flags";
      }
    }
  }

  public abstract class OdRepresentationItemExample : OdPrcCreateExample
  {
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

      OdPrcProductOccurrence newProductOccurrence = OdPrcProductOccurrence.createObject();
      switch (mode)
      {
        case OdPrcCreateSwigMgd_ExampleModes.RepresentationItemPolyWire:
          name.setName("RepresentationItemPolyWire");
          newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePolyWire(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.RepresentationItemPointSet:
          name.setName("RepresentationItemPointSet");
          newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePointSet(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.RepresentationItemPolyBrepModel:
          name.setName("RepresentationItemPolyBrepModel");
          newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreatePolyBrepModel(newStructure), name);
          break;
        //     case OdPrcCreateSwigMgd_ExampleModes.RepresentationItemDirection:
        //       name.setName("RepresentationItemDirection");  
        //       newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreateDirection(newStructure), name);
        //       break;
        //     case OdPrcCreateSwigMgd_ExampleModes.RepresentationItemCoordinateSystem:
        //       name.setName("RepresentationItemCoordinateSystem");  
        //       newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreateCoordinateSystem(/*newStructure*/), name);
        //       break;
        case OdPrcCreateSwigMgd_ExampleModes.RepresentationItemSet:
          name.setName("RepresentationItemSet");
          newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, CreateSet(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.WireTessWithFlags:
          name.setName("3dWireTess with flags");
          newProductOccurrence = CreateTopologyCommonForRI(pFile, extents, Create3dPolyWireWithFlags(newStructure), name);
          break;
        default:
          OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
          break;
      }

      son_occurrences.Add(newProductOccurrence.objectId());

      // export prc
      pFile.writeFile(pPrcStream);
    }
    public static OdPrcRepresentationItem CreatePolyWire(OdPrcFileStructure newStructure)
    {
      OdPrcPolyWire polyWire = OdPrcPolyWire.createObject();
      OdPrc3dWireTess mTess = OdPrc3dWireTess.createObject();
      OdFloatArray arr = new OdFloatArray();
      arr.Add((float)0.0);
      arr.Add((float)2.0);
      arr.Add((float)0.0);
      arr.Add((float)2.0);
      arr.Add((float)4.0);
      arr.Add((float)0.0);
      arr.Add((float)4.0);
      arr.Add((float)2.0);
      arr.Add((float)0.0);
      arr.Add((float)2.0);
      arr.Add((float)0.0);
      arr.Add((float)0.0);
      arr.Add((float)0.0);
      arr.Add((float)2.0);
      arr.Add((float)0.0);

      arr.Add((float)1.0);
      arr.Add((float)1.0);
      arr.Add((float)0.0);
      arr.Add((float)1.0);
      arr.Add((float)3.0);
      arr.Add((float)0.0);
      arr.Add((float)3.0);
      arr.Add((float)3.0);
      arr.Add((float)0.0);
      arr.Add((float)3.0);
      arr.Add((float)1.0);
      arr.Add((float)0.0);
      arr.Add((float)1.0);
      arr.Add((float)1.0);
      arr.Add((float)0.0);

      mTess.setcoordinates(arr);

      mTess.wireIndexes().Add((uint)(arr.Count / (3 * 2))); // in array we have number of points = size()/3 but we also have 2 polyWire
      for (int i = 0; i < arr.Count / (3 * 2); ++i)
      {
        mTess.wireIndexes().Add((uint)i * 3);
      }

      mTess.wireIndexes().Add((uint)(arr.Count / (3 * 2)));
      for (int i = arr.Count / (3 * 2); i < 2 * arr.Count / (3 * 2); ++i)
      {
        mTess.wireIndexes().Add((uint)(i * 3));
      }

      polyWire.settessellation(mTess);

      newStructure.fileStructureTessellation().tessellations().Add(mTess);
      return polyWire;
    }

    public static OdPrcRepresentationItem CreatePointSet(OdPrcFileStructure newStructure)
    {
      OdPrcPointSet pointSet = OdPrcPointSet.createObject();
      pointSet.point().Add(new OdGePoint3d(0.0, 0.0, 0.0));
      pointSet.point().Add(new OdGePoint3d(1.0, 1.0, 1.0));

      OdPrcCategory1LineStyle style = OdPrcCategory1LineStyle.createObject();
      newStructure.addObject(style);
      style.setLineWidth(10);
      newStructure.fileStructureGlobals().category1LineStyles().Add(style.objectId());
      pointSet.setstyleId(style.objectId());
      pointSet.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_Show);

      return pointSet;
    }

    public static OdPrcRepresentationItem CreatePolyBrepModel(OdPrcFileStructure newStructure)
    {
      OdPrcPolyBrepModel polyBrep = OdPrcPolyBrepModel.createObject();

      OdPrcCategory1LineStyle style = OdPrcCategory1LineStyle.createObject();
      newStructure.addObject(style);
      style.setLineWidth(10);
      newStructure.fileStructureGlobals().category1LineStyles().Add(style.objectId());
      polyBrep.setstyleId(style.objectId());
      polyBrep.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_Show);

      OdPrc3dTess mTess = OdPrcCreateTopologyHelper.createTess<OdPrc3dTess>(newStructure, polyBrep);
      OdFloatArray arr = new OdFloatArray();
      arr.Add((uint)0.0);
      arr.Add((uint)0.0);
      arr.Add((uint)0.0);
      arr.Add((uint)2.0);
      arr.Add((uint)0.0);
      arr.Add((uint)0.0);
      arr.Add((uint)2.0);
      arr.Add((uint)2.0);
      arr.Add((uint)0.0);
      arr.Add((uint)4.0);
      arr.Add((uint)2.0);
      arr.Add((uint)0.0);

      mTess.setcoordinates(arr);
      mTess.setMustRecalculateNormals(true);
      mTess.triangulatedIndex().Add(0);
      mTess.triangulatedIndex().Add(3);
      mTess.triangulatedIndex().Add(6);
      mTess.triangulatedIndex().Add(6);
      mTess.triangulatedIndex().Add(9);
      mTess.triangulatedIndex().Add(3);
      OdPrcTessFace face = new OdPrcTessFace();
      face.setUsedEntitiesFlag(2);
      face.sizesTriangulated().Add(2);
      mTess.faceTessellation().Add(face);

      return polyBrep;
    }

    //OdPrcRepresentationItem CreateDirection(OdPrcFileStructure newStructure)
    //{
    //  OdPrcDirection direction = OdPrcDirection.createObject();
    //
    //  OdGeVector3d vect = new OdGeVector3d (1,0,0);
    //  direction.setdirection(vect);
    //  direction.setHasOrigin(true);
    //  OdGePoint3d orig = new OdGePoint3d(1,1,1);
    //  direction.setorigin(orig);
    //
    //  OdPrcCategory1LineStyle style = OdPrcCategory1LineStyle.createObject();
    //  newStructure.addObject(style);
    //  style.setLineWidth(10);
    //  newStructure.fileStructureGlobals().category1LineStyles().Add(style.objectId());
    //  direction.setstyleId(style.objectId());
    //
    //  return direction;
    //}
    //
    //OdPrcRepresentationItem CreateCoordinateSystem(/*OdPrcFileStructure newStructure*/)
    //{
    //  OdPrcCoordinateSystem coordSystem = OdPrcCoordinateSystem.createObject();
    //
    //  coordSystem.axisSet().set( new OdGeMatrix3d().setCoordSystem( new OdGePoint3d(1,1,1), new OdGeVector3d(1,0,0), new OdGeVector3d(0,1,0), new OdGeVector3d(0,0,1)));
    //
    //  return coordSystem;
    //}

    public static OdPrcRepresentationItem CreateSet(OdPrcFileStructure newStructure)
    {
      OdPrcSet set = OdPrcSet.createObject();
      OdPrcRepresentationItem rI = CreatePolyWire(newStructure);
      newStructure.addObject(rI);
      set.representationItem().Add(rI.objectId());

      rI = CreatePointSet(newStructure);
      newStructure.addObject(rI);
      set.representationItem().Add(rI.objectId());

      rI = CreatePolyBrepModel(newStructure);
      newStructure.addObject(rI);
      set.representationItem().Add(rI.objectId());

      return set;
    }

    public static OdPrcRepresentationItem Create3dPolyWireWithFlags(OdPrcFileStructure newStructure)
    {
      OdPrcPolyWire polyWire = OdPrcPolyWire.createObject();
      OdPrc3dWireTess mTess = OdPrc3dWireTess.createObject();
      OdFloatArray arr = new OdFloatArray();
      arr.Add((float)-3.0); //1 point
      arr.Add((float)-3.0);
      arr.Add((float)0.0);
      arr.Add((float)-1.0); //2 point
      arr.Add((float)-3.0);
      arr.Add((float)0.0);
      arr.Add((float)-2.0); //3 point
      arr.Add((float)-1.0);
      arr.Add((float)0.0);
      arr.Add((float)-1.0); //4 point
      arr.Add((float)0.0);
      arr.Add((float)0.0);
      arr.Add((float)1.0); //5 point
      arr.Add((float)0.0);
      arr.Add((float)0.0);
      arr.Add((float)2.0); //6 point
      arr.Add((float)-1.0);
      arr.Add((float)0.0);
      arr.Add((float)1.0); //7 point
      arr.Add((float)-3.0);
      arr.Add((float)0.0);
      arr.Add((float)3.0); //8 point
      arr.Add((float)-3.0);
      arr.Add((float)0.0);
      mTess.setcoordinates(arr);

      mTess.wireIndexes().Add(3 + PRC_Globals.PRC_3DWIRETESSDATA_IsClosing);
      mTess.wireIndexes().Add(0);
      mTess.wireIndexes().Add(3);
      mTess.wireIndexes().Add(6);
      mTess.wireIndexes().Add(2 + PRC_Globals.PRC_3DWIRETESSDATA_IsContinuous);
      mTess.wireIndexes().Add(9);
      mTess.wireIndexes().Add(12);
      mTess.wireIndexes().Add(4 + PRC_Globals.PRC_3DWIRETESSDATA_IsContinuous);
      mTess.wireIndexes().Add(15);
      mTess.wireIndexes().Add(18);
      mTess.wireIndexes().Add(21);
      mTess.wireIndexes().Add(15);

      mTess.arrayRGBA().colors().Add(255);//1 wire color
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);//2 wire color
      mTess.arrayRGBA().colors().Add(255);
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);//3 wire color (can't see)
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);

      mTess.arrayRGBA().colors().Add(0);//Closing wire color
      mTess.arrayRGBA().colors().Add(255);
      mTess.arrayRGBA().colors().Add(255);

      mTess.arrayRGBA().colors().Add(255);//Continuous wire color
      mTess.arrayRGBA().colors().Add(255);
      mTess.arrayRGBA().colors().Add(0);

      mTess.arrayRGBA().colors().Add(0);//4 wire color
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(255);
      mTess.arrayRGBA().colors().Add(0);//5 wire color (can't see)
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);

      mTess.arrayRGBA().colors().Add(255);//Continuous wire color
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(255);

      mTess.arrayRGBA().colors().Add(255);//6 wire color
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);//7 wire color
      mTess.arrayRGBA().colors().Add(255);
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);//8 wire color
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(255);
      mTess.arrayRGBA().colors().Add(0);//9 wire color (can't see)
      mTess.arrayRGBA().colors().Add(0);
      mTess.arrayRGBA().colors().Add(0);

      polyWire.settessellation(mTess);

      newStructure.fileStructureTessellation().tessellations().Add(mTess);
      return polyWire;
    }

    public static OdPrcProductOccurrence CreateTopologyCommonForRI(OdPrcFile pFile, OdGeExtents3d extents, OdPrcRepresentationItem rI, OdPrcName name)
    {
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      // product occurrence section
      OdPrcProductOccurrence newProductOccurrence = OdPrcProductOccurrence.createObject();
      newStructure.addObject(newProductOccurrence);

      // part definition section
      OdPrcPartDefinition newDefinition = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, newProductOccurrence);

      rI.setname(name);
      newStructure.addObject(rI);

      newDefinition.representationItem().Add(rI.objectId());

      // file structure geometry section
      OdPrcCreateTopologyHelper.createTopoContext(newStructure);

      // bounding box
      newDefinition.boundingBox().setbox(extents);

      OdPrcRgbColorArray colors = newStructure.fileStructureGlobals().colors();
      OdPrcRgbColor color = new OdPrcRgbColor(0, 1, 0);
      colors.Add(color);

      return newProductOccurrence;
    }
  }
}

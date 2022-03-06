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
using System.Collections.Generic;
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdComplexSamples
{

  public class OdComplexExample_CloneConnexesFromComplexExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Example with cloning Connexes from complex example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create new file
      OdPrcFile pNewFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pNewFile.fileStructures();
      OdPrcFileStructure pNewStructure = fileStructures[fileStructures.Count - 1];
      OdPrcProductOccurrence pRootPO = pNewStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(pNewStructure, pRootPO);
      OdPrcTopoContext newTopoContext = OdPrcCreateTopologyHelper.createTopoContext(pNewStructure);

      {
        //OdPrcFile pFile = pHostApp.readFile(pHostApp.findFile(L"D:/1.prc"));
        OdPrcFile pFile = OdComplexExample_CreateComplexExample.CreateComplexModels(); // create prc with all brep examples

        OdPrcFileStructurePtrArray arrFs = pFile.fileStructures();
        for (int i = 0; i < arrFs.Count; ++i)
        {
          OdPrcFileStructure pFs = arrFs[i];
          OdPrcFileStructureExactGeometry exactGeom = pFs.fileStructureGeometry().fileStructureExactGeometry();
          OdPrcTopoContextPtrArray arrCB = exactGeom.topologicalContext();
          for (int j = 0; j < arrCB.Count; ++j)
          {
            OdPrcObjectIdArray arrBody = arrCB[j].bodies();
            for (int k = 0; k < arrBody.Count; ++k)
            {
              OdPrcBrepData pBD = arrBody[k].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForRead,false) as OdPrcBrepData;

              OdGeExtents3d extents = pBD.boundingBox().box();
              OdPrcRepresentationItem pNewRepItem = OdPrcCreateTopologyHelper.createRI<OdPrcBrepModel>(pNewStructure, pPD);
              pPD.boundingBox().setbox(extents);
              OdPrcBrepData pNewBD = OdPrcCreateTopologyHelper.createBody<OdPrcBrepData>(pNewStructure, newTopoContext, pNewRepItem);
              pNewBD.boundingBox().setbox(extents);
              pNewBD.contentBody().setBoundingBoxBehaviour(2);

              pNewRepItem.name().setName(String.Format("BrepData without graphics[{0}]", newTopoContext.bodies().Count));

              OdPrcConnexPtrArray arrConnex = pBD.connex();
              for (int t = 0; t < arrConnex.Count; ++t)
              {
                OdPrcCloneMap cloneMap = new OdPrcCloneMap();
                cloneMap.pTargetDatabase = pNewStructure;
                OdRxObject pNewConnex;
                prcWblockCloneObject(out pNewConnex, arrConnex[t], cloneMap);
                pNewBD.addConnex(pNewConnex as OdPrcConnex); // all into one brepData
              }
            }
          }
        }
      }

      pNewFile.writeFile(pPrcStream);
    }

    public class OdPrcCloneMap
    {
      public OdRxObject2OdRxObjectMap mapOld2New = new OdRxObject2OdRxObjectMap();
      public OdPrcFileStructure pTargetDatabase = null;
      //OdPrcFileStructure pInputDatabase;
    };

    public static void prcWblockCloneObject(out OdRxObject pNewObj, OdRxObject pObj, OdPrcCloneMap mapOld2New)
    {
      if (pObj.isKindOf(OdPrcConnex.desc()))
      {
        OdPrcConnex pConnex;
        copyPrcConnex(out pConnex, pObj as OdPrcConnex, mapOld2New);
        pNewObj = pConnex;
      }
      else
      {
        pNewObj = null;
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }
    }

    public static void copyPrcConnex(out OdPrcConnex pNewConnex, OdPrcConnex pConnex, OdPrcCloneMap mapOld2New)
    {
      if (pConnex == null)
      {
        pNewConnex = null;
        return;
      }

      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pConnex, out v_value))
      {
        pNewConnex = v_value as OdPrcConnex;
        return;
      }
      pNewConnex = OdPrcConnex.createObject();
      mapOld2New.mapOld2New[pConnex] = pNewConnex;
      copyPrcBaseTopology(pNewConnex.baseTopology(), pConnex.baseTopology());

      OdPrcShellPtrArray arrShells = pConnex.shells();
      for (int i = 0; i < arrShells.Count; ++i)
      {
        OdPrcShell pNewShell;
        copyPrcShell(out pNewShell, arrShells[i], mapOld2New);
        pNewConnex.addShell(pNewShell);
      }
    }

    public static void copyPrcBaseTopology(OdPrcBaseTopology pNewBaseTopology, OdPrcBaseTopology pBaseTopology)
    {
      pNewBaseTopology.setname(pBaseTopology.name());
      pNewBaseTopology.setattributeData(pBaseTopology.attributeData());
      pNewBaseTopology.setIdentifier(pBaseTopology.identifier());
      pNewBaseTopology.setBaseInformation(pBaseTopology.baseInformation());
    }

    public static void copyPrcShell(out OdPrcShell pNewShell, OdPrcShell pShell, OdPrcCloneMap mapOld2New)
    {
      if (pShell == null)
      {
        pNewShell = null;
        return;
      }

      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pShell, out v_value))
      {
        pNewShell = v_value as OdPrcShell;
        return;
      }
      pNewShell = OdPrcShell.createObject();
      mapOld2New.mapOld2New[pShell] = pNewShell;
      copyPrcBaseTopology(pNewShell.baseTopology(), pShell.baseTopology());
      pNewShell.setShellIsClosed(pShell.shellIsClosed());

      OdPrcFacePtrArray arrFaces = pShell.faces();
      for (int i = 0; i < arrFaces.Count; ++i)
      {
        OdPrcFace pNewFace;
        copyPrcFace(out pNewFace, arrFaces[i], mapOld2New);
        pNewShell.addFace(pNewFace);
      }
    }

    public static void copyPrcFace(out OdPrcFace pNewFace, OdPrcFace pFace, OdPrcCloneMap mapOld2New)
    {
      if (pFace == null)
      {
        pNewFace = null;
        return;
      }

      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pFace, out v_value))
      {
        pNewFace = v_value as OdPrcFace;
        return;
      }
      pNewFace = OdPrcFace.createObject();
      mapOld2New.mapOld2New[pFace] = pNewFace;
      copyPrcBaseTopology(pNewFace.baseTopology(), pFace.baseTopology());
      OdPrcSurface surface;
      copyPrcSurface(out surface, pFace.baseSurface(), mapOld2New);
      pNewFace.setbaseSurface(surface);
      pNewFace.setSurfaceTrimDomain(pFace.surfaceTrimDomain());
      pNewFace.setTolerance(pFace.tolerance());

      OdPrcLoopPtrArray arrLoops = pFace.loops();
      for (int i = 0; i < arrLoops.Count; ++i)
      {
        OdPrcLoop pNewLoop;
        copyPrcLoop(out pNewLoop, arrLoops[i], mapOld2New);
        pNewFace.addLoop(pNewLoop);
      }

      pNewFace.setOuterLoopIndex(pFace.getOuterLoopIndex());
      pNewFace.setorientationSurfaceWithShell(pFace.getorientationSurfaceWithShell());

      //OdPrcGraphics *m_face_graphics; TODO: not fully implemented, only line styles with color can be copied
      /*if (pFace.hasGraphics())
      {
        OdPrcGraphics newGraphics;
        copyPrcGraphics(newGraphics, *pFace.graphics(), mapOld2New);
        pNewFace.setGraphics(&newGraphics);
      }*/
    }

    public static void copyPrcSurface(out OdPrcSurface pNewSurface, OdPrcSurface pSurface, OdPrcCloneMap mapOld2New)
    {
      pNewSurface = null;
      if (pSurface == null)
      {
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pSurface, out v_value))
      {
        pNewSurface = v_value as OdPrcSurface;
        return;
      }

      if (pSurface.isKindOf(OdPrcBlend01Surface.desc()))
      {
        pNewSurface = OdPrcBlend01Surface.createObject();
        OdPrcBlend01Surface pNewPrcBlend01Surface = pNewSurface as OdPrcBlend01Surface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcBlend01Surface pPrcBlend01Surface = pSurface as OdPrcBlend01Surface;
        pNewPrcBlend01Surface.setTransformation(pPrcBlend01Surface.transformation());

        OdPrcCurve pNewCenterCurve;
        copyPrcCurve(out pNewCenterCurve, pPrcBlend01Surface.centerCurve(), mapOld2New);
        pNewPrcBlend01Surface.setCenterCurve(pNewCenterCurve);

        OdPrcCurve pNewOriginCurve;
        copyPrcCurve(out pNewOriginCurve, pPrcBlend01Surface.originCurve(), mapOld2New);
        pNewPrcBlend01Surface.setOriginCurve(pNewOriginCurve);

        OdPrcCurve pNewTangentCurve;
        copyPrcCurve(out pNewTangentCurve, pPrcBlend01Surface.tangentCurve(), mapOld2New);
        pNewPrcBlend01Surface.setTangentCurve(pNewTangentCurve);
      }
      else if (pSurface.isKindOf(OdPrcBlend02Surface.desc()))
      {
        pNewSurface = OdPrcBlend02Surface.createObject();
        OdPrcBlend02Surface pNewPrcBlend02Surface = pNewSurface as OdPrcBlend02Surface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcBlend02Surface pPrcBlend02Surface = pSurface as OdPrcBlend02Surface;
        pNewPrcBlend02Surface.setTransformation(pPrcBlend02Surface.transformation());

        OdPrcSurface cliffSupportingSurface0;
        OdPrcSurface cliffSupportingSurface1;
        copyPrcSurface(out cliffSupportingSurface0, pPrcBlend02Surface.cliffSupportingSurface0(), mapOld2New);
        copyPrcSurface(out cliffSupportingSurface1, pPrcBlend02Surface.cliffSupportingSurface1(), mapOld2New);
        pNewPrcBlend02Surface.setcliffSupportingSurface0(cliffSupportingSurface0);
        pNewPrcBlend02Surface.setcliffSupportingSurface1(cliffSupportingSurface1);

        OdPrcCurve boundCurve0;
        OdPrcCurve boundCurve1;
        OdPrcSurface boundSurface0;
        OdPrcSurface boundSurface1;
        copyPrcCurve(out boundCurve0, pPrcBlend02Surface.boundCurve0(), mapOld2New);
        copyPrcCurve(out boundCurve1, pPrcBlend02Surface.boundCurve1(), mapOld2New);
        copyPrcSurface(out boundSurface0, pPrcBlend02Surface.boundSurface0(), mapOld2New);
        copyPrcSurface(out boundSurface1, pPrcBlend02Surface.boundSurface1(), mapOld2New);

        pNewPrcBlend02Surface.setboundCurve0(boundCurve0);
        pNewPrcBlend02Surface.setboundCurve1(boundCurve1);
        pNewPrcBlend02Surface.setboundSurface0(boundSurface0);
        pNewPrcBlend02Surface.setboundSurface1(boundSurface0);

        pNewPrcBlend02Surface.setRadius0(pPrcBlend02Surface.radius0());
        pNewPrcBlend02Surface.setRadius1(pPrcBlend02Surface.radius1());

        pNewPrcBlend02Surface.setBoundSurfaceSens0(pPrcBlend02Surface.boundSurfaceSens0());
        pNewPrcBlend02Surface.setBoundSurfaceSens1(pPrcBlend02Surface.boundSurfaceSens1());
        pNewPrcBlend02Surface.setCenterCurveSens(pPrcBlend02Surface.centerCurveSens());

        OdPrcCurve pNewCenterCurve;
        copyPrcCurve(out pNewCenterCurve, pPrcBlend02Surface.centerCurve(), mapOld2New);
        pNewPrcBlend02Surface.setCenterCurve(pNewCenterCurve);

        pNewPrcBlend02Surface.setParameterizationType(pPrcBlend02Surface.parameterizationType());
      }
      else if (pSurface.isKindOf(OdPrcBlend03Surface.desc()))
      {
        pNewSurface = OdPrcBlend03Surface.createObject();
        OdPrcBlend03Surface pNewPrcBlend03Surface = pNewSurface as OdPrcBlend03Surface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcBlend03Surface pPrcBlend03Surface = pSurface as OdPrcBlend03Surface;
        pNewPrcBlend03Surface.setTransformation(pPrcBlend03Surface.transformation());
        pNewPrcBlend03Surface.setsecondDerivatives(pPrcBlend03Surface.secondDerivatives());
        pNewPrcBlend03Surface.settangent(pPrcBlend03Surface.tangent());
        pNewPrcBlend03Surface.setposition(pPrcBlend03Surface.position());
        pNewPrcBlend03Surface.setmultiplicities(pPrcBlend03Surface.multiplicities());
        pNewPrcBlend03Surface.setrail2SecondDerivatives(pPrcBlend03Surface.rail2SecondDerivatives());
        pNewPrcBlend03Surface.setrail2DerivativesV(pPrcBlend03Surface.rail2DerivativesV());
        pNewPrcBlend03Surface.setrail2AnglesV(pPrcBlend03Surface.rail2AnglesV());
        pNewPrcBlend03Surface.setparameters(pPrcBlend03Surface.parameters());
        pNewPrcBlend03Surface.setTrimVMax(pPrcBlend03Surface.trimVMax());
        pNewPrcBlend03Surface.setTrimVMin(pPrcBlend03Surface.trimVMin());
        pNewPrcBlend03Surface.setRail2ParameterV(pPrcBlend03Surface.rail2ParameterV());

        //int               m_reserved_int; TODO!
        //int               m_reserved_int4;
      }
      else if (pSurface.isKindOf(OdPrcCone.desc()))
      {
        pNewSurface = OdPrcCone.createObject();
        OdPrcCone pNewPrcCone = pNewSurface as OdPrcCone;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcCone pPrcCone = pSurface as OdPrcCone;

        pNewPrcCone.setTransformation(pPrcCone.transformation());
        pNewPrcCone.setSemiAngle(pPrcCone.semiAngle());
        pNewPrcCone.setBottomRadius(pPrcCone.bottomRadius());
      }
      else if (pSurface.isKindOf(OdPrcCylinder.desc()))
      {
        pNewSurface = OdPrcCylinder.createObject();
        OdPrcCylinder pNewPrcCylinder = pNewSurface as OdPrcCylinder;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcCylinder pPrcCylinder = pSurface as OdPrcCylinder;
        pNewPrcCylinder.setTransformation(pPrcCylinder.transformation());
        pNewPrcCylinder.setRadius(pPrcCylinder.radius());
      }
      else if (pSurface.isKindOf(OdPrcCylindricalSurface.desc()))
      {
        pNewSurface = OdPrcCylindricalSurface.createObject();
        OdPrcCylindricalSurface pNewPrcCylindricalSurface = pNewSurface as OdPrcCylindricalSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcCylindricalSurface pPrcCylindricalSurface = pSurface as OdPrcCylindricalSurface;
        pNewPrcCylindricalSurface.setTransformation(pPrcCylindricalSurface.transformation());
        pNewPrcCylindricalSurface.setTolerance(pPrcCylindricalSurface.tolerance());

        OdPrcSurface pNewBaseSurface;
        copyPrcSurface(out pNewBaseSurface, pPrcCylindricalSurface.baseSurface(), mapOld2New);
        pNewPrcCylindricalSurface.setBaseSurface(pNewBaseSurface);

        //OdGeExtents3d         m_baseSurfExt_cache; TODO!
      }
      else if (pSurface.isKindOf(OdPrcExtrusionSurface.desc()))
      {
        pNewSurface = OdPrcExtrusionSurface.createObject();
        OdPrcExtrusionSurface pNewPrcExtrusionSurface = pNewSurface as OdPrcExtrusionSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcExtrusionSurface pPrcExtrusionSurface = pSurface as OdPrcExtrusionSurface;
        pNewPrcExtrusionSurface.setTransformation(pPrcExtrusionSurface.transformation());
        pNewPrcExtrusionSurface.setsweepVector(pPrcExtrusionSurface.sweepVector());

        OdPrcCurve pNewBaseCurve;
        copyPrcCurve(out pNewBaseCurve, pPrcExtrusionSurface.baseCurve(), mapOld2New);
        pNewPrcExtrusionSurface.setBaseCurve(pNewBaseCurve);
      }
      else if (pSurface.isKindOf(OdPrcFromCurvesSurface.desc()))
      {
        pNewSurface = OdPrcFromCurvesSurface.createObject();
        OdPrcFromCurvesSurface pNewPrcFromCurvesSurface = pNewSurface as OdPrcFromCurvesSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcFromCurvesSurface pPrcFromCurvesSurface = pSurface as OdPrcFromCurvesSurface;
        pNewPrcFromCurvesSurface.setTransformation(pPrcFromCurvesSurface.transformation());
        pNewPrcFromCurvesSurface.setorigin(pPrcFromCurvesSurface.origin());

        OdPrcCurve firstCurve;
        OdPrcCurve secondCurve;
        copyPrcCurve(out firstCurve, pPrcFromCurvesSurface.firstCurve(), mapOld2New);
        copyPrcCurve(out secondCurve, pPrcFromCurvesSurface.secondCurve(), mapOld2New);
        pNewPrcFromCurvesSurface.setfirstCurve(firstCurve);
        pNewPrcFromCurvesSurface.setsecondCurve(secondCurve);
      }
      else if (pSurface.isKindOf(OdPrcNurbsSurface.desc()))
      {
        pNewSurface = OdPrcNurbsSurface.createObject();
        OdPrcNurbsSurface pNewPrcNurbsSurface = pNewSurface as OdPrcNurbsSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcNurbsSurface pPrcNurbsSurface = pSurface as OdPrcNurbsSurface;
        pNewPrcNurbsSurface.setKnotType(pPrcNurbsSurface.knotType());
        pNewPrcNurbsSurface.setSurfaceForm(pPrcNurbsSurface.surfaceForm());

        //OdGeSurface _pSurface = null;
        //pPrcNurbsSurface.getOdGeSurface(_pSurface);
        //pNewPrcNurbsSurface.setFromOdGeSurface(_pSurface);
        //delete pSurface;
        ////OdGeNurbSurface     m_nurbSurface;
        ////bool                m_bNurbInitialized; //TODO!
      }
      else if (pSurface.isKindOf(OdPrcOffsetSurface.desc()))
      {
        pNewSurface = OdPrcOffsetSurface.createObject();
        OdPrcOffsetSurface pNewPrcOffsetSurface = pNewSurface as OdPrcOffsetSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcOffsetSurface pPrcOffsetSurface = pSurface as OdPrcOffsetSurface;
        pNewPrcOffsetSurface.setTransformation(pPrcOffsetSurface.transformation());
        pNewPrcOffsetSurface.setOffsetDistance(pPrcOffsetSurface.offsetDistance());

        OdPrcSurface pNewBaseSurface;
        copyPrcSurface(out pNewBaseSurface, pPrcOffsetSurface.baseSurface(), mapOld2New);
        pNewPrcOffsetSurface.setBaseSurface(pNewBaseSurface);
      }
      else if (pSurface.isKindOf(OdPrcPlane.desc()))
      {
        pNewSurface = OdPrcPlane.createObject();
        OdPrcPlane pNewPrcPlane = pNewSurface as OdPrcPlane;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcPlane pPrcPlane = pSurface as OdPrcPlane;
        pNewPrcPlane.setTransformation(pPrcPlane.transformation());
      }
      else if (pSurface.isKindOf(OdPrcRevolutionSurface.desc()))
      {
        pNewSurface = OdPrcRevolutionSurface.createObject();
        OdPrcRevolutionSurface pNewPrcRevolutionSurface = pNewSurface as OdPrcRevolutionSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcRevolutionSurface pPrcRevolutionSurface = pSurface as OdPrcRevolutionSurface;

        pNewPrcRevolutionSurface.setTransformation(pPrcRevolutionSurface.transformation());
        pNewPrcRevolutionSurface.setx(pPrcRevolutionSurface.getx());
        pNewPrcRevolutionSurface.sety(pPrcRevolutionSurface.y());
        pNewPrcRevolutionSurface.setorigin(pPrcRevolutionSurface.origin());
        pNewPrcRevolutionSurface.setTolerance(pPrcRevolutionSurface.tolerance());

        OdPrcCurve pNewBaseCurve;
        copyPrcCurve(out pNewBaseCurve, pPrcRevolutionSurface.baseCurve(), mapOld2New);
        pNewPrcRevolutionSurface.setBaseCurve(pNewBaseCurve);
      }
      else if (pSurface.isKindOf(OdPrcRuledSurface.desc()))
      {
        pNewSurface = OdPrcRuledSurface.createObject();
        OdPrcRuledSurface pNewPrcRuledSurface = pNewSurface as OdPrcRuledSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcRuledSurface pPrcRuledSurface = pSurface as OdPrcRuledSurface;
        pNewPrcRuledSurface.setTransformation(pPrcRuledSurface.transformation());

        OdPrcCurve firstCurve;
        OdPrcCurve secondCurve;
        copyPrcCurve(out firstCurve, pPrcRuledSurface.firstCurve(), mapOld2New);
        copyPrcCurve(out secondCurve, pPrcRuledSurface.secondCurve(), mapOld2New);
        pNewPrcRuledSurface.setfirstCurve(firstCurve);
        pNewPrcRuledSurface.setsecondCurve(secondCurve);
      }
      else if (pSurface.isKindOf(OdPrcSphere.desc()))
      {
        pNewSurface = OdPrcSphere.createObject();
        OdPrcSphere pNewPrcSphere = pNewSurface as OdPrcSphere;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcSphere pPrcSphere = pSurface as OdPrcSphere;
        pNewPrcSphere.setTransformation(pPrcSphere.transformation());
        pNewPrcSphere.setRadius(pPrcSphere.radius());
      }
      else if (pSurface.isKindOf(OdPrcTorus.desc()))
      {
        pNewSurface = OdPrcTorus.createObject();
        OdPrcTorus pNewPrcTorus = pNewSurface as OdPrcTorus;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcTorus pPrcTorus = pSurface as OdPrcTorus;
        pNewPrcTorus.setTransformation(pPrcTorus.transformation());
        pNewPrcTorus.setMinorRadius(pPrcTorus.minorRadius());
        pNewPrcTorus.setMajorRadius(pPrcTorus.majorRadius());
      }
      else if (pSurface.isKindOf(OdPrcTransformedSurface.desc()))
      {
        pNewSurface = OdPrcTransformedSurface.createObject();
        OdPrcTransformedSurface pNewPrcTransformedSurface = pNewSurface as OdPrcTransformedSurface;
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcTransformedSurface pPrcTransformedSurface = pSurface as OdPrcTransformedSurface;
        pNewPrcTransformedSurface.setTransformation(pPrcTransformedSurface.transformation());

        OdPrcMath3d mathTransformation;
        copyPrcMath3d(out mathTransformation, pPrcTransformedSurface.mathTransformation(), mapOld2New);
        pNewPrcTransformedSurface.setmathTransformation(mathTransformation);

        OdPrcSurface pNewBaseSurface;
        copyPrcSurface(out pNewBaseSurface, pPrcTransformedSurface.baseSurface(), mapOld2New);
        pNewPrcTransformedSurface.setBaseSurface(pNewBaseSurface);
      }
      /*else if (pSurface.isKindOf(OdPrcBlend04.desc()))
      {
        OdPrcBlend04 pNewPrcBlend04 = pNewSurface = OdPrcBlend04.createObject();
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcBlend04 pPrcBlend04 = pSurface;
        // This type is currently not supported and is reserved for future use.
        ODA_ASSERT(0);
      }
      else if (pSurface.isKindOf(OdPrcPipe.desc()))
      {
        OdPrcPipe pNewPrcPipe = pNewSurface = OdPrcPipe.createObject();
        mapOld2New.mapOld2New[pSurface] = pNewSurface;
        OdPrcPipe pPrcPipe = pSurface;
        // This surface type is currently not supported and reserved for future use.
        ODA_ASSERT(0);
      }*/
      else
      {
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }

      pNewSurface.setUVParameterization(pSurface.uVParameterization());
      copyPrcContentSurface(pNewSurface.contentSurface(), pSurface.contentSurface());
    }

    public static void copyPrcMath3d(out OdPrcMath3d pNewMath3d, OdPrcMath3d pMath3d, OdPrcCloneMap mapOld2New)
    {
      pNewMath3d = null;
      if (pMath3d == null)
      {
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pMath3d, out v_value))
      {
        pNewMath3d = v_value as OdPrcMath3d;
        return;
      }
      if (pMath3d.isKindOf(OdPrcMath3dLinear.desc()))
      {
        pNewMath3d = OdPrcMath3dLinear.createObject();
        OdPrcMath3dLinear pNewPrcMath3dLinear = pNewMath3d as OdPrcMath3dLinear;
        mapOld2New.mapOld2New[pMath3d] = pNewMath3d;
        OdPrcMath3dLinear pPrcMath3dLinear = pMath3d as OdPrcMath3dLinear;
        pNewPrcMath3dLinear.setmat(pPrcMath3dLinear.mat());
      }
      else if (pMath3d.isKindOf(OdPrcMath3dNonLinear.desc()))
      {
        pNewMath3d = OdPrcMath3dNonLinear.createObject();
        OdPrcMath3dNonLinear pNewPrcMath3dNonLinear = pNewMath3d as OdPrcMath3dNonLinear;
        mapOld2New.mapOld2New[pMath3d] = pNewMath3d;
        OdPrcMath3dNonLinear pPrcMath3dNonLinear = pMath3d as OdPrcMath3dNonLinear;
        pNewPrcMath3dNonLinear.setD2(pPrcMath3dNonLinear.d2());

        OdPrcMath3d pLeftTransformation;
        copyPrcMath3d(out pLeftTransformation, pPrcMath3dNonLinear.leftTransformation(), mapOld2New);
        pNewPrcMath3dNonLinear.setLeftTransformation(pLeftTransformation as OdPrcMath3dLinear);

        OdPrcMath3d pRightTransformation;
        copyPrcMath3d(out pRightTransformation, pPrcMath3dNonLinear.rightTransformation(), mapOld2New);
        pNewPrcMath3dNonLinear.setRightTransformation(pRightTransformation as OdPrcMath3dLinear);
      }
      else
      {
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }
    }

    public static void copyPrcContentSurface(OdPrcContentSurface newContentSurface, OdPrcContentSurface contentSurface)
    {
      copyPrcBaseGeometry(newContentSurface.baseGeometry(), contentSurface.baseGeometry());
      newContentSurface.set_extendInfo(contentSurface.extendInfo());
    }

    public static void copyPrcBaseGeometry(OdPrcBaseGeometry newBaseGeometry, OdPrcBaseGeometry baseGeometry)
    {
      if (baseGeometry.hasBaseInformation())
      {
        newBaseGeometry.setBaseInformation(true);
        newBaseGeometry.setattributeData(baseGeometry.attributeData());
        newBaseGeometry.setname(baseGeometry.name());
        newBaseGeometry.setIdentifier(baseGeometry.identifier());
      }
      else
      {
        newBaseGeometry.setBaseInformation(false);
      }
    }

    public static void copyPrcEdge(out OdPrcEdge pNewEdge, OdPrcEdge pEdge, OdPrcCloneMap mapOld2New)
    {
      if (pEdge == null)
      {
        pNewEdge = null;
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pEdge, out v_value))
      {
        pNewEdge = v_value as OdPrcEdge;
        return;
      }
      pNewEdge = OdPrcEdge.createObject();
      mapOld2New.mapOld2New[pEdge] = pNewEdge;

      OdPrcContentWireEdge newContentWireEdge = pNewEdge.contentWireEdge();
      OdPrcContentWireEdge contentWireEdge = pEdge.contentWireEdge();

      copyPrcBaseTopology(newContentWireEdge.baseTopology(), contentWireEdge.baseTopology());
      newContentWireEdge.setTrimInterval(contentWireEdge.trimInterval());

      OdPrcCurve newContentWireEdge_curve;
      copyPrcCurve(out newContentWireEdge_curve, contentWireEdge.getcurve(), mapOld2New);
      newContentWireEdge.setcurve(newContentWireEdge_curve);

      OdPrcTopoItem pVertexStart, pVertexEnd;
      copyPrcVertex(out pVertexStart, pEdge.vertexStart(), mapOld2New);
      pNewEdge.setStartVertex(pVertexStart);
      copyPrcVertex(out pVertexEnd, pEdge.vertexEnd(), mapOld2New);
      pNewEdge.setEndVertex(pVertexEnd);
      pNewEdge.setTolerance(pEdge.tolerance());
    }

    public static void copyPrcVertex(out OdPrcTopoItem pNewVertex, OdPrcTopoItem pVertex, OdPrcCloneMap mapOld2New)
    {
      pNewVertex = null;
      if (pVertex == null)
      {
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pVertex, out v_value))
      {
        pNewVertex = v_value as OdPrcTopoItem;
        return;
      }

      if (pVertex.isKindOf(OdPrcUniqueVertex.desc()))
      {
        pNewVertex = OdPrcUniqueVertex.createObject();
        OdPrcUniqueVertex pNewVertexStart = pNewVertex as OdPrcUniqueVertex;
        mapOld2New.mapOld2New[pVertex] = pNewVertex;
        OdPrcUniqueVertex pVertexUnique = pVertex as OdPrcUniqueVertex;
        copyPrcBaseTopology(pNewVertexStart.baseTopology(), pVertexUnique.baseTopology());
        pNewVertexStart.setpoint(pVertexUnique.point());
        pNewVertexStart.setHaveTolerance(pVertexUnique.haveTolerance());
        pNewVertexStart.setTolerance(pVertexUnique.tolerance());
      }
      else if (pVertex.isKindOf(OdPrcMultipleVertex.desc()))
      {
        pNewVertex = OdPrcMultipleVertex.createObject();
        OdPrcMultipleVertex pNewVertexStart = pNewVertex as OdPrcMultipleVertex;
        mapOld2New.mapOld2New[pVertex] = pNewVertex;
        OdPrcMultipleVertex pVertexMultiple = pVertex as OdPrcMultipleVertex;
        copyPrcBaseTopology(pNewVertexStart.baseTopology(), pVertexMultiple.baseTopology());
        pNewVertexStart.setpoints(pVertexMultiple.points());
      }
      else
      {
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }
    }

    public static void copyPrcCoEdge(out OdPrcCoEdge pNewCoEdge, OdPrcCoEdge pCoEdge, OdPrcCloneMap mapOld2New)
    {
      if (pCoEdge == null)
      {
        pNewCoEdge = null;
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pCoEdge, out v_value))
      {
        pNewCoEdge = v_value as OdPrcCoEdge;
        return;
      }
      pNewCoEdge = OdPrcCoEdge.createObject();
      mapOld2New.mapOld2New[pCoEdge] = pNewCoEdge;
      copyPrcBaseTopology(pNewCoEdge.baseTopology(), pCoEdge.baseTopology());
      OdPrcEdge pEdge;
      copyPrcEdge(out pEdge, pCoEdge.edge(), mapOld2New);
      pNewCoEdge.setEdge(pEdge);

      OdPrcCurve curveUV;
      copyPrcCurve(out curveUV, pCoEdge.curveUV(), mapOld2New);
      pNewCoEdge.setcurveUV(curveUV);

      pNewCoEdge.setOrientationWithLoop(pCoEdge.orientationWithLoop());
      pNewCoEdge.setOrientationUvWithLoop(pCoEdge.orientationUvWithLoop());

      OdPrcCoEdge pNewNeighCoEdge;
      copyPrcCoEdge(out pNewNeighCoEdge, pCoEdge.neighCoEdge(), mapOld2New);
      pNewCoEdge.setNeighCoEdge(pNewNeighCoEdge);
    }

    public static void copyPrcCurve(out OdPrcCurve pNewCurve, OdPrcCurve pCurve, OdPrcCloneMap mapOld2New)
    {
      pNewCurve = null;
      if (pCurve == null)
      {
        return;
      }

      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pCurve, out v_value))
      {
        pNewCurve = v_value as OdPrcCurve;
        return;
      }

      if (pCurve.isKindOf(OdPrc2dCurveOnSurfaceCurve3d.desc()))
      {
        pNewCurve = OdPrc2dCurveOnSurfaceCurve3d.createObject();
        OdPrc2dCurveOnSurfaceCurve3d pNewPrc2dCurveOnSurfaceCurve3d = pNewCurve as OdPrc2dCurveOnSurfaceCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrc2dCurveOnSurfaceCurve3d pPrc2dCurveOnSurfaceCurve3d = pCurve as OdPrc2dCurveOnSurfaceCurve3d;
        pNewPrc2dCurveOnSurfaceCurve3d.setTolerance(pPrc2dCurveOnSurfaceCurve3d.tolerance());

        OdPrcCurve pNewUvCurve;
        copyPrcCurve(out pNewUvCurve, pPrc2dCurveOnSurfaceCurve3d.curveUV(), mapOld2New);
        pNewPrc2dCurveOnSurfaceCurve3d.setCurveUV(pNewUvCurve);

        OdPrcSurface pNewBaseSurface;
        copyPrcSurface(out pNewBaseSurface, pPrc2dCurveOnSurfaceCurve3d.baseSurface(), mapOld2New);
        pNewPrc2dCurveOnSurfaceCurve3d.setBaseSurface(pNewBaseSurface);
      }
      else if (pCurve.isKindOf(OdPrcBlend02Boundary3d.desc()))
      {
        pNewCurve = OdPrcBlend02Boundary3d.createObject();
        OdPrcBlend02Boundary3d pNewPrcBlend02Boundary3d = pNewCurve as OdPrcBlend02Boundary3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcBlend02Boundary3d pPrcBlend02Boundary3d = pCurve as OdPrcBlend02Boundary3d;

        pNewPrcBlend02Boundary3d.setTransformation(pPrcBlend02Boundary3d.transformation());
        pNewPrcBlend02Boundary3d.setendLimitPoint(pPrcBlend02Boundary3d.endLimitPoint());
        pNewPrcBlend02Boundary3d.setstartLimitPoint(pPrcBlend02Boundary3d.startLimitPoint());

        pNewPrcBlend02Boundary3d.setcrossingPointPositions(pPrcBlend02Boundary3d.crossingPointPositions());
        pNewPrcBlend02Boundary3d.setBaseScale(pPrcBlend02Boundary3d.baseScale());
        pNewPrcBlend02Boundary3d.setBaseParameter(pPrcBlend02Boundary3d.baseParameter());
        pNewPrcBlend02Boundary3d.setAngularError(pPrcBlend02Boundary3d.angularError());
        pNewPrcBlend02Boundary3d.setChordalError(pPrcBlend02Boundary3d.chordalError());
        pNewPrcBlend02Boundary3d.setIntersectionCurveSens(pPrcBlend02Boundary3d.intersectionCurveSens());
        pNewPrcBlend02Boundary3d.setIntersectionOrder(pPrcBlend02Boundary3d.intersectionOrder());
        pNewPrcBlend02Boundary3d.setBoundingSurfaceSens(pPrcBlend02Boundary3d.boundingSurfaceSens());

        OdPrcSurface pNewBlendSurface;
        copyPrcSurface(out pNewBlendSurface, pPrcBlend02Boundary3d.blend(), mapOld2New);
        pNewPrcBlend02Boundary3d.setBlend(pNewBlendSurface as OdPrcBlend02Surface);

        pNewPrcBlend02Boundary3d.setBound(pPrcBlend02Boundary3d.bound());

        OdPrcSurface pNewBoundingSurface;
        copyPrcSurface(out pNewBoundingSurface, pPrcBlend02Boundary3d.boundingSurface(), mapOld2New);
        pNewPrcBlend02Boundary3d.setBoundingSurface(pNewBoundingSurface);

        pNewPrcBlend02Boundary3d.setStartLimitType(pNewPrcBlend02Boundary3d.startLimitType());
        pNewPrcBlend02Boundary3d.setEndLimitType(pNewPrcBlend02Boundary3d.endLimitType());
      }
      else if (pCurve.isKindOf(OdPrcCircle2d.desc()))
      {
        pNewCurve = OdPrcCircle2d.createObject();
        OdPrcCircle2d pNewPrcCircle2d = pNewCurve as OdPrcCircle2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcCircle2d pPrcCircle2d = pCurve as OdPrcCircle2d;

        pNewPrcCircle2d.setTransformation(pPrcCircle2d.transformation());
        pNewPrcCircle2d.setRadius(pPrcCircle2d.radius());
      }
      else if (pCurve.isKindOf(OdPrcCircle3d.desc()))
      {
        pNewCurve = OdPrcCircle3d.createObject();
        OdPrcCircle3d pNewPrcCircle3d = pNewCurve as OdPrcCircle3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcCircle3d pPrcCircle3d = pCurve as OdPrcCircle3d;
        pNewPrcCircle3d.setTransformation(pPrcCircle3d.transformation());
        pNewPrcCircle3d.setRadius(pPrcCircle3d.radius());
      }
      else if (pCurve.isKindOf(OdPrcCompositeCurve2d.desc()))
      {
        pNewCurve = OdPrcCompositeCurve2d.createObject();
        OdPrcCompositeCurve2d pNewPrcCompositeCurve2d = pNewCurve as OdPrcCompositeCurve2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcCompositeCurve2d pPrcCompositeCurve2d = pCurve as OdPrcCompositeCurve2d;
        pNewPrcCompositeCurve2d.setTransformation(pPrcCompositeCurve2d.transformation());
        pNewPrcCompositeCurve2d.setIsClosed(pPrcCompositeCurve2d.isClosed());

        OdPrcCurvePtrArray arrNewBaseCurve = new OdPrcCurvePtrArray();
        arrNewBaseCurve.resize((uint)pPrcCompositeCurve2d.baseCurve().Count);
        for (int i = 0; i < pPrcCompositeCurve2d.baseCurve().Count; ++i)
        {
          OdPrcCurve tmp_curve;
          copyPrcCurve(out tmp_curve, pPrcCompositeCurve2d.baseCurve()[i], mapOld2New);
          arrNewBaseCurve[i] = tmp_curve;
        }
        pNewPrcCompositeCurve2d.setbaseCurve(arrNewBaseCurve);
        pNewPrcCompositeCurve2d.setbaseSense(pPrcCompositeCurve2d.baseSense());
      }
      else if (pCurve.isKindOf(OdPrcCompositeCurve3d.desc()))
      {
        pNewCurve = OdPrcCompositeCurve3d.createObject();
        OdPrcCompositeCurve3d pNewPrcCompositeCurve3d = pNewCurve as OdPrcCompositeCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcCompositeCurve3d pPrcCompositeCurve3d = pCurve as OdPrcCompositeCurve3d;

        pNewPrcCompositeCurve3d.setTransformation(pPrcCompositeCurve3d.transformation());
        pNewPrcCompositeCurve3d.setIsClosed(pPrcCompositeCurve3d.isClosed());

        OdPrcCurvePtrArray arrNewBaseCurve = new OdPrcCurvePtrArray();
        arrNewBaseCurve.resize((uint)pPrcCompositeCurve3d.baseCurve().Count);
        for (int i = 0; i < pPrcCompositeCurve3d.baseCurve().Count; ++i)
        {
          OdPrcCurve tmp_curve;
          copyPrcCurve(out tmp_curve, pPrcCompositeCurve3d.baseCurve()[i], mapOld2New);
          arrNewBaseCurve[i] = tmp_curve;
        }
        pNewPrcCompositeCurve3d.setbaseCurve(arrNewBaseCurve);
        pNewPrcCompositeCurve3d.setbaseSense(pPrcCompositeCurve3d.baseSense());
      }
      else if (pCurve.isKindOf(OdPrcEllipse2d.desc()))
      {
        pNewCurve = OdPrcEllipse2d.createObject();
        OdPrcEllipse2d pNewPrcEllipse2d = pNewCurve as OdPrcEllipse2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcEllipse2d pPrcEllipse2d = pCurve as OdPrcEllipse2d;
        pNewPrcEllipse2d.setTransformation(pPrcEllipse2d.transformation());
        pNewPrcEllipse2d.setRadiusAtXAxis(pPrcEllipse2d.radiusAtXAxis());
        pNewPrcEllipse2d.setRadiusAtYAxis(pPrcEllipse2d.radiusAtYAxis());
      }
      else if (pCurve.isKindOf(OdPrcEllipse3d.desc()))
      {
        pNewCurve = OdPrcEllipse3d.createObject();
        OdPrcEllipse3d pNewPrcEllipse3d = pNewCurve as OdPrcEllipse3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcEllipse3d pPrcEllipse3d = pCurve as OdPrcEllipse3d;
        pNewPrcEllipse3d.setTransformation(pPrcEllipse3d.transformation());
        pNewPrcEllipse3d.setRadiusAtXAxis(pPrcEllipse3d.radiusAtXAxis());
        pNewPrcEllipse3d.setRadiusAtYAxis(pPrcEllipse3d.radiusAtYAxis());
      }
      else if (pCurve.isKindOf(OdPrcEquationCurve2d.desc()))
      {
        pNewCurve = OdPrcEquationCurve2d.createObject();
        OdPrcEquationCurve2d pNewPrcEquationCurve2d = pNewCurve as OdPrcEquationCurve2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcEquationCurve2d pPrcEquationCurve2d = pCurve as OdPrcEquationCurve2d;
        pNewPrcEquationCurve2d.setTransformation(pPrcEquationCurve2d.transformation());

        OdPrcMath1d pNewFunctionX;
        copyPrcMath1d(out pNewFunctionX, pPrcEquationCurve2d.functionX(), mapOld2New);
        pNewPrcEquationCurve2d.setFunctionX(pNewFunctionX);

        OdPrcMath1d pNewFunctionY;
        copyPrcMath1d(out pNewFunctionY, pPrcEquationCurve2d.functionY(), mapOld2New);
        pNewPrcEquationCurve2d.setFunctionY(pNewFunctionY);
      }
      else if (pCurve.isKindOf(OdPrcEquationCurve3d.desc()))
      {
        pNewCurve = OdPrcEquationCurve3d.createObject();
        OdPrcEquationCurve3d pNewPrcEquationCurve3d = pNewCurve as OdPrcEquationCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcEquationCurve3d pPrcEquationCurve3d = pCurve as OdPrcEquationCurve3d;
        pNewPrcEquationCurve3d.setTransformation(pPrcEquationCurve3d.transformation());

        OdPrcMath1d pNewFunctionX;
        copyPrcMath1d(out pNewFunctionX, pPrcEquationCurve3d.functionX(), mapOld2New);
        pNewPrcEquationCurve3d.setFunctionX(pNewFunctionX);

        OdPrcMath1d pNewFunctionY;
        copyPrcMath1d(out pNewFunctionY, pPrcEquationCurve3d.functionY(), mapOld2New);
        pNewPrcEquationCurve3d.setFunctionY(pNewFunctionY);

        OdPrcMath1d pNewFunctionZ;
        copyPrcMath1d(out pNewFunctionZ, pPrcEquationCurve3d.functionZ(), mapOld2New);
        pNewPrcEquationCurve3d.setFunctionZ(pNewFunctionZ);
      }
      else if (pCurve.isKindOf(OdPrcHelixType0Curve.desc()))
      {
        pNewCurve = OdPrcHelixType0Curve.createObject();
        OdPrcHelixType0Curve pNewPrcHelixType0Curve = pNewCurve as OdPrcHelixType0Curve;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcHelixType0Curve pPrcHelixType0Curve = pCurve as OdPrcHelixType0Curve;
        pNewPrcHelixType0Curve.setTransformation(pPrcHelixType0Curve.transformation());
        pNewPrcHelixType0Curve.setdirection(pPrcHelixType0Curve.direction());
        pNewPrcHelixType0Curve.setorigin(pPrcHelixType0Curve.origin());
        pNewPrcHelixType0Curve.setstart(pPrcHelixType0Curve.start());
        pNewPrcHelixType0Curve.setRadiusEvolution(pPrcHelixType0Curve.radiusEvolution());
        pNewPrcHelixType0Curve.setPitch(pPrcHelixType0Curve.pitch());
        pNewPrcHelixType0Curve.setTrigonometricOrientation(pPrcHelixType0Curve.trigonometricOrientation());
      }
      else if (pCurve.isKindOf(OdPrcHelixType1Curve.desc()))
      {
        pNewCurve = OdPrcHelixType1Curve.createObject();
        OdPrcHelixType1Curve pNewPrcHelixType1Curve = pNewCurve as OdPrcHelixType1Curve;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcHelixType1Curve pPrcHelixType1Curve = pCurve as OdPrcHelixType1Curve;

        pNewPrcHelixType1Curve.setTransformation(pPrcHelixType1Curve.transformation());
        pNewPrcHelixType1Curve.setstart(pPrcHelixType1Curve.start());
        pNewPrcHelixType1Curve.setTrigonometricOrientation(pPrcHelixType1Curve.trigonometricOrientation());
        pNewPrcHelixType1Curve.setUnitZ(pPrcHelixType1Curve.unitZ());
        pNewPrcHelixType1Curve.setUnitU(pPrcHelixType1Curve.unitU());

        OdPrcMath1d pNewRadiusLaw;
        copyPrcMath1d(out pNewRadiusLaw, pPrcHelixType1Curve.radiusLaw(), mapOld2New);
        pNewPrcHelixType1Curve.setRadiusLaw(pNewRadiusLaw);

        OdPrcMath1d pNewZLaw;
        copyPrcMath1d(out pNewZLaw, pPrcHelixType1Curve.zLaw(), mapOld2New);
        pNewPrcHelixType1Curve.setZLaw(pNewZLaw);

        OdPrcMath1d pNewThetaLaw;
        copyPrcMath1d(out pNewThetaLaw, pPrcHelixType1Curve.thetaLaw(), mapOld2New);
        pNewPrcHelixType1Curve.setThetaLaw(pNewThetaLaw);
      }
      else if (pCurve.isKindOf(OdPrcHyperbola2d.desc()))
      {
        pNewCurve = OdPrcHyperbola2d.createObject();
        OdPrcHyperbola2d pNewPrcHyperbola2d = pNewCurve as OdPrcHyperbola2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcHyperbola2d pPrcHyperbola2d = pCurve as OdPrcHyperbola2d;
        pNewPrcHyperbola2d.setTransformation(pPrcHyperbola2d.transformation());
        pNewPrcHyperbola2d.setSemiImageAxis(pPrcHyperbola2d.semiImageAxis());
        pNewPrcHyperbola2d.setSemiAxis(pPrcHyperbola2d.semiAxis());
        pNewPrcHyperbola2d.setParameterizationType(pPrcHyperbola2d.parameterizationType());
      }
      else if (pCurve.isKindOf(OdPrcHyperbola3d.desc()))
      {
        pNewCurve = OdPrcHyperbola3d.createObject();
        OdPrcHyperbola3d pNewPrcHyperbola3d = pNewCurve as OdPrcHyperbola3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcHyperbola3d pPrcHyperbola3d = pCurve as OdPrcHyperbola3d;
        pNewPrcHyperbola3d.setTransformation(pPrcHyperbola3d.transformation());
        pNewPrcHyperbola3d.setSemiImageAxis(pPrcHyperbola3d.semiImageAxis());
        pNewPrcHyperbola3d.setSemiAxis(pPrcHyperbola3d.semiAxis());
        pNewPrcHyperbola3d.setParameterizationType(pPrcHyperbola3d.parameterizationType());
      }
      else if (pCurve.isKindOf(OdPrcIntersectionCurve3d.desc()))
      {
        pNewCurve = OdPrcIntersectionCurve3d.createObject();
        OdPrcIntersectionCurve3d pNewPrcIntersectionCurve3d = pNewCurve as OdPrcIntersectionCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcIntersectionCurve3d pPrcIntersectionCurve3d = pCurve as OdPrcIntersectionCurve3d;
        pNewPrcIntersectionCurve3d.setTransformation(pPrcIntersectionCurve3d.transformation());
        pNewPrcIntersectionCurve3d.setendLimitPoint(pPrcIntersectionCurve3d.endLimitPoint());
        pNewPrcIntersectionCurve3d.setstartLimitPoint(pPrcIntersectionCurve3d.startLimitPoint());
        pNewPrcIntersectionCurve3d.setcrossingPointsCrvIntersection(pPrcIntersectionCurve3d.crossingPointsCrvIntersection());
        pNewPrcIntersectionCurve3d.setAngularError(pPrcIntersectionCurve3d.angularError());
        pNewPrcIntersectionCurve3d.setChordalError(pPrcIntersectionCurve3d.chordalError());
        pNewPrcIntersectionCurve3d.setParameterizationDefinitionRespected(pPrcIntersectionCurve3d.parameterizationDefinitionRespected());
        pNewPrcIntersectionCurve3d.setIntersectionSense(pPrcIntersectionCurve3d.intersectionSense());

        pNewPrcIntersectionCurve3d.setSurface1Sense(pPrcIntersectionCurve3d.surface1Sense());
        pNewPrcIntersectionCurve3d.setSurface2Sense(pPrcIntersectionCurve3d.surface2Sense());

        OdPrcSurface pNewSurface1;
        copyPrcSurface(out pNewSurface1, pPrcIntersectionCurve3d.surface1(), mapOld2New);
        pNewPrcIntersectionCurve3d.setSurface1(pNewSurface1);

        OdPrcSurface pNewSurface2;
        copyPrcSurface(out pNewSurface2, pPrcIntersectionCurve3d.surface2(), mapOld2New);
        pNewPrcIntersectionCurve3d.setSurface2(pNewSurface2);

        pNewPrcIntersectionCurve3d.setStartLimitType(pPrcIntersectionCurve3d.startLimitType());
        pNewPrcIntersectionCurve3d.setEndLimitType(pPrcIntersectionCurve3d.endLimitType());
      }
      else if (pCurve.isKindOf(OdPrcLine2d.desc()))
      {
        pNewCurve = OdPrcLine2d.createObject();
        OdPrcLine2d pNewPrcLine2d = pNewCurve as OdPrcLine2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcLine2d pPrcLine2d = pCurve as OdPrcLine2d;
        pNewPrcLine2d.setTransformation(pPrcLine2d.transformation());
      }
      else if (pCurve.isKindOf(OdPrcLine3d.desc()))
      {
        pNewCurve = OdPrcLine3d.createObject();
        OdPrcLine3d pNewPrcLine3d = pNewCurve as OdPrcLine3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcLine3d pPrcLine3d = pCurve as OdPrcLine3d;
        pNewPrcLine3d.setTransformation(pPrcLine3d.transformation());
      }
      else if (pCurve.isKindOf(OdPrcNurbsCurve2d.desc()))
      {
        pNewCurve = OdPrcNurbsCurve2d.createObject();
        OdPrcNurbsCurve2d pNewPrcNurbsCurve2d = pNewCurve as OdPrcNurbsCurve2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcNurbsCurve2d pPrcNurbsCurve2d = pCurve as OdPrcNurbsCurve2d;

        OdGeCurve2d pCurve2d = null;
        pPrcNurbsCurve2d.getOdGeCurve(pCurve2d);
        pNewPrcNurbsCurve2d.setFromOdGeCurve(pCurve2d);
      }
      else if (pCurve.isKindOf(OdPrcNurbsCurve3d.desc()))
      {
        pNewCurve = OdPrcNurbsCurve3d.createObject();
        OdPrcNurbsCurve3d pNewPrcNurbsCurve3d = pNewCurve as OdPrcNurbsCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcNurbsCurve3d pPrcNurbsCurve3d = pCurve as OdPrcNurbsCurve3d;
        OdGeCurve3d pCurve3d = null;
        pPrcNurbsCurve3d.getOdGeCurve(pCurve3d);
        pNewPrcNurbsCurve3d.setFromOdGeCurve(pCurve3d);
      }
      else if (pCurve.isKindOf(OdPrcOffsetCurve3d.desc()))
      {
        pNewCurve = OdPrcOffsetCurve3d.createObject();
        OdPrcOffsetCurve3d pNewPrcOffsetCurve3d = pNewCurve as OdPrcOffsetCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcOffsetCurve3d pPrcOffsetCurve3d = pCurve as OdPrcOffsetCurve3d;
        pNewPrcOffsetCurve3d.setOffsetDistance(pPrcOffsetCurve3d.offsetDistance());

        copyPrcCurve(out pNewCurve, pPrcOffsetCurve3d.baseCurve(), mapOld2New);
        pNewPrcOffsetCurve3d.setBaseCurve(pNewCurve);
        pNewPrcOffsetCurve3d.setOffsetPlaneNormal(pPrcOffsetCurve3d.offsetPlaneNormal());
      }
      else if (pCurve.isKindOf(OdPrcParabola2d.desc()))
      {
        pNewCurve = OdPrcParabola2d.createObject();
        OdPrcParabola2d pNewPrcParabola2d = pNewCurve as OdPrcParabola2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcParabola2d pPrcParabola2d = pCurve as OdPrcParabola2d;
        pNewPrcParabola2d.setTransformation(pPrcParabola2d.transformation());
        pNewPrcParabola2d.setParameterizationType(pPrcParabola2d.parameterizationType());
        pNewPrcParabola2d.setFocalLength(pPrcParabola2d.focalLength());
      }
      else if (pCurve.isKindOf(OdPrcParabola3d.desc()))
      {
        pNewCurve = OdPrcParabola3d.createObject();
        OdPrcParabola3d pNewPrcParabola3d = pNewCurve as OdPrcParabola3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcParabola3d pPrcParabola3d = pCurve as OdPrcParabola3d;
        pNewPrcParabola3d.setTransformation(pPrcParabola3d.transformation());
        pNewPrcParabola3d.setParameterizationType(pPrcParabola3d.parameterizationType());
        pNewPrcParabola3d.setFocalLength(pPrcParabola3d.focalLength());
      }
      else if (pCurve.isKindOf(OdPrcPolyLine2d.desc()))
      {
        pNewCurve = OdPrcPolyLine2d.createObject();
        OdPrcPolyLine2d pNewPrcPolyLine2d = pNewCurve as OdPrcPolyLine2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcPolyLine2d pPrcPolyLine2d = pCurve as OdPrcPolyLine2d;
        pNewPrcPolyLine2d.setTransformation(pPrcPolyLine2d.transformation());
        pNewPrcPolyLine2d.setPoints(pPrcPolyLine2d.points());
      }
      else if (pCurve.isKindOf(OdPrcPolyLine3d.desc()))
      {
        pNewCurve = OdPrcPolyLine3d.createObject();
        OdPrcPolyLine3d pNewPrcPolyLine3d = pNewCurve as OdPrcPolyLine3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcPolyLine3d pPrcPolyLine3d = pCurve as OdPrcPolyLine3d;
        pNewPrcPolyLine3d.setTransformation(pPrcPolyLine3d.transformation());
        pNewPrcPolyLine3d.setPoints(pPrcPolyLine3d.points());
      }
      else if (pCurve.isKindOf(OdPrcTransformedCurve2d.desc()))
      {
        pNewCurve = OdPrcTransformedCurve2d.createObject();
        OdPrcTransformedCurve2d pNewPrcTransformedCurve2d = pNewCurve as OdPrcTransformedCurve2d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcTransformedCurve2d pPrcTransformedCurve2d = pCurve as OdPrcTransformedCurve2d;
        pNewPrcTransformedCurve2d.setTransformation(pPrcTransformedCurve2d.transformation());
        OdPrcCurve pNewBaseCurve;
        copyPrcCurve(out pNewBaseCurve, pPrcTransformedCurve2d.baseCurve(), mapOld2New);
        pNewPrcTransformedCurve2d.setBaseCurve(pNewBaseCurve);
        OdPrcMath3d mathTransformation;
        copyPrcMath3d(out mathTransformation, pPrcTransformedCurve2d.mathTransformation(), mapOld2New);
        pNewPrcTransformedCurve2d.setmathTransformation(mathTransformation);
      }
      else if (pCurve.isKindOf(OdPrcTransformedCurve3d.desc()))
      {
        pNewCurve = OdPrcTransformedCurve3d.createObject();
        OdPrcTransformedCurve3d pNewPrcTransformedCurve3d = pNewCurve as OdPrcTransformedCurve3d;
        mapOld2New.mapOld2New[pCurve] = pNewCurve;
        OdPrcTransformedCurve3d pPrcTransformedCurve3d = pCurve as OdPrcTransformedCurve3d;
        pNewPrcTransformedCurve3d.setTransformation(pPrcTransformedCurve3d.transformation());
        OdPrcCurve pNewBaseCurve;
        copyPrcCurve(out pNewBaseCurve, pPrcTransformedCurve3d.baseCurve(), mapOld2New);
        pNewPrcTransformedCurve3d.setBaseCurve(pNewBaseCurve);
        OdPrcMath3d mathTransformation;
        copyPrcMath3d(out mathTransformation, pPrcTransformedCurve3d.mathTransformation(), mapOld2New);
        pNewPrcTransformedCurve3d.setmathTransformation(mathTransformation);
      }
      else
      {
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }
      pNewCurve.setParameterization(pCurve.parameterization());
      copyPrcContentCurve(pNewCurve.contentCurve(), pCurve.contentCurve());
    }

    public static void copyPrcContentCurve(OdPrcContentCurve newContentCurve, OdPrcContentCurve contentCurve)
    {
      copyPrcBaseGeometry(newContentCurve.baseGeometry(), contentCurve.baseGeometry());
      newContentCurve.setExtendInfo(contentCurve.extendInfo());
    }

    public static void copyPrcMath1d(out OdPrcMath1d pNewMath1d, OdPrcMath1d pMath1d, OdPrcCloneMap mapOld2New)
    {
      pNewMath1d = null;
      if (pMath1d == null)
      {
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pMath1d, out v_value))
      {
        pNewMath1d = v_value as OdPrcMath1d;
        return;
      }
      if (pMath1d.isKindOf(OdPrcMath1dArcTanCos.desc()))
      {
        pNewMath1d = OdPrcMath1dArcTanCos.createObject();
        OdPrcMath1dArcTanCos pNewPrcMath1dArcTanCos = pNewMath1d as OdPrcMath1dArcTanCos;
        mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
        OdPrcMath1dArcTanCos pPrcMath1dArcTanCos = pMath1d as OdPrcMath1dArcTanCos;
        pPrcMath1dArcTanCos.setPhase(pPrcMath1dArcTanCos.phase());
        pPrcMath1dArcTanCos.setFrequency(pPrcMath1dArcTanCos.frequency());
        pPrcMath1dArcTanCos.setA(pPrcMath1dArcTanCos.a());
        pPrcMath1dArcTanCos.setAmplitude(pPrcMath1dArcTanCos.amplitude());
      }
      else if (pMath1d.isKindOf(OdPrcMath1dCombination.desc()))
      {
        pNewMath1d = OdPrcMath1dCombination.createObject();
        OdPrcMath1dCombination pNewPrcMath1dCombination = pNewMath1d as OdPrcMath1dCombination;
        mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
        OdPrcMath1dCombination pPrcMath1dCombination = pMath1d as OdPrcMath1dCombination;
        pNewPrcMath1dCombination.combinationFunctions().resize((uint)pPrcMath1dCombination.combinationFunctions().Count);
        for (int i = 0; i < pPrcMath1dCombination.combinationFunctions().Count; ++i)
        {
          pNewPrcMath1dCombination.combinationFunctions()[i].setCoefficient(pPrcMath1dCombination.combinationFunctions()[i].getCoefficient());
          OdPrcMath1d function;
          copyPrcMath1d(out function, pPrcMath1dCombination.combinationFunctions()[i].function(), mapOld2New);
          pNewPrcMath1dCombination.combinationFunctions()[i].setfunction(function);
        }
      }
      else if (pMath1d.isKindOf(OdPrcMath1dFraction.desc()))
      {
        pNewMath1d = OdPrcMath1dFraction.createObject();
        OdPrcMath1dFraction pNewPrcMath1dFraction = pNewMath1d as OdPrcMath1dFraction;
        mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
        OdPrcMath1dFraction pPrcMath1dFraction = pMath1d as OdPrcMath1dFraction;

        OdPrcMath1d pNewNumerator;
        copyPrcMath1d(out pNewNumerator, pPrcMath1dFraction.numerator(), mapOld2New);
        pNewPrcMath1dFraction.setNumerator(pNewNumerator);

        OdPrcMath1d pNewDenominator;
        copyPrcMath1d(out pNewDenominator, pPrcMath1dFraction.denominator(), mapOld2New);
        pNewPrcMath1dFraction.setNumerator(pNewDenominator);
      }
      else if (pMath1d.isKindOf(OdPrcMath1dPolynom.desc()))
      {
        pNewMath1d = OdPrcMath1dPolynom.createObject();
        OdPrcMath1dPolynom pNewPrcMath1dPolynom = pNewMath1d as OdPrcMath1dPolynom;
        mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
        OdPrcMath1dPolynom pPrcMath1dPolynom = pMath1d as OdPrcMath1dPolynom;
        pNewPrcMath1dPolynom.setcoefficient(pPrcMath1dPolynom.coefficient());
      }
      else if (pMath1d.isKindOf(OdPrcMath1dTrigonometric.desc()))
      {
        pNewMath1d = OdPrcMath1dTrigonometric.createObject();
        OdPrcMath1dTrigonometric pNewPrcMath1dTrigonometric = pNewMath1d as OdPrcMath1dTrigonometric;
        mapOld2New.mapOld2New[pMath1d] = pNewMath1d;
        OdPrcMath1dTrigonometric pPrcMath1dTrigonometric = pMath1d as OdPrcMath1dTrigonometric;
        pNewPrcMath1dTrigonometric.setDcOffset(pPrcMath1dTrigonometric.dcOffset());
        pNewPrcMath1dTrigonometric.setFrequency(pPrcMath1dTrigonometric.frequency());
        pNewPrcMath1dTrigonometric.setPhase(pPrcMath1dTrigonometric.phase());
        pNewPrcMath1dTrigonometric.setAmplitude(pPrcMath1dTrigonometric.amplitude());
      }
      else
      {
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }
    }

    public static void copyPrcLoop(out OdPrcLoop pNewLoop, OdPrcLoop pLoop, OdPrcCloneMap mapOld2New)
    {
      if (pLoop == null)
      {
        pNewLoop = null;
        return;
      }
      OdRxObject v_value;
      if (mapOld2New.mapOld2New.TryGetValue(pLoop, out v_value))
      {
        pNewLoop = v_value as OdPrcLoop;
        return;
      }
      pNewLoop = OdPrcLoop.createObject();
      mapOld2New.mapOld2New[pLoop] = pNewLoop;
      copyPrcBaseTopology(pNewLoop.baseTopology(), pLoop.baseTopology());
      pNewLoop.setOrientationWithSurface(pLoop.orientationWithSurface());

      OdPrcCoEdgePtrArray arrCoEdge = pLoop.coedges();
      for (int i = 0; i < arrCoEdge.Count; ++i)
      {
        OdPrcCoEdge pNewCoEdge;
        copyPrcCoEdge(out pNewCoEdge, arrCoEdge[i], mapOld2New);
        pNewLoop.addCoEdge(pNewCoEdge);
      }
    }
  }
}

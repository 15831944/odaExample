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

namespace OdPrcCreateSwigMgd.Samples
{
  public class PrcFaceKey
  {
    public uint m_face_index;
    public TriangleInfo.TriangleType m_type;
    public OdDbStub m_materialID;
    public OdCmEntityColor m_color;
    public byte m_alpha;
    public PrcFaceKey(uint face_index,
      TriangleInfo.TriangleType type,
      OdDbStub materialID,
      OdCmEntityColor color,
      byte alpha)
    {
      m_face_index = face_index;
      m_type = type;
      m_materialID = materialID;
      m_color = color;
      m_alpha = alpha;
    }

    public override bool Equals(object obj)
    {
      PrcFaceKey key = obj as PrcFaceKey;
      return key != null &&
             m_face_index == key.m_face_index &&
             m_type == key.m_type &&
             EqualityComparer<IntPtr>.Default.Equals(OdDbStub.getCPtr(m_materialID).Handle, OdDbStub.getCPtr(key.m_materialID).Handle) &&
             EqualityComparer<OdCmEntityColor>.Default.Equals(m_color, key.m_color) &&
             m_alpha == key.m_alpha;
    }

    public override int GetHashCode()
    {
      var hashCode = -324788028;
      hashCode = hashCode * -1521134295 + m_face_index.GetHashCode();
      hashCode = hashCode * -1521134295 + m_type.GetHashCode();
      hashCode = hashCode * -1521134295 + OdDbStub.getCPtr(m_materialID).Handle.GetHashCode();
      hashCode = hashCode * -1521134295 + m_color.color().GetHashCode();
      hashCode = hashCode * -1521134295 + m_alpha.GetHashCode();
      return hashCode;
    }
  }

  public static class OdPrcCreateTopologyHelper
  {

    public static TType createTess<TType>(OdPrcFileStructure FSt, OdPrcRepresentationItem RI)
       where TType : OdPrcBaseTessData
    {
      TType pTess = typeof(TType).GetMethod("createObject", System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public).Invoke(null, Array.Empty<Object>()) as TType;
      FSt.fileStructureTessellation().tessellations().Add(pTess);
      RI.settessellation(pTess);
      return pTess;
    }

    public static TType createRI<TType>(OdPrcFileStructure FSt, OdPrcPartDefinition PD)
      where TType : OdPrcRepresentationItem
    {
      TType pRI = typeof(TType).GetMethod("createObject", System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public).Invoke(null, Array.Empty<Object>()) as TType;
      FSt.addObject(pRI);
      PD.representationItem().Add(pRI.objectId());
      return pRI;
    }

    public static TType createBody<TType>(OdPrcFileStructure FSt, OdPrcTopoContext TC, OdPrcRepresentationItem RI)
       where TType : OdPrcBody
    {
      TType pBody = typeof(TType).GetMethod("createObject", System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public).Invoke(null, Array.Empty<Object>()) as TType;
      FSt.addObject(pBody);
      TC.bodies().Add(pBody.objectId());
      RI.setReferenceToBody(pBody);
      return pBody;
    }

    public static OdPrcProductOccurrence createProductOccurrence(OdPrcFileStructure FSt, OdPrcProductOccurrence parentPO)
    {
      OdPrcProductOccurrence newProductOccurrence = OdPrcProductOccurrence.createObject();
      FSt.addObject(newProductOccurrence);
      parentPO.referencesOfProductOccurrence().getSonProductOccurrences().Add(newProductOccurrence.objectId());
      return newProductOccurrence;
    }

    public static OdPrcTopoContext createTopoContext(OdPrcFileStructure newStructure)
    {
      OdPrcTopoContext newTopoContext = OdPrcTopoContext.createObject();
      newTopoContext.setBehaviour(6);
      newTopoContext.setGranularity(1e-8);
      newTopoContext.setTolerance(1e-6);
      newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().Add(newTopoContext);
      OdPrcTopoContextPtrArray topologicalContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
      return topologicalContext[topologicalContext.Count - 1];
    }

    public static OdPrcPartDefinition createPartDefinition(OdPrcFileStructure FSt, OdPrcProductOccurrence PO)
    {
      // part definition section
      OdPrcPartDefinition newDefinition = OdPrcPartDefinition.createObject();
      FSt.addObject(newDefinition);
      FSt.fileStructureTree().partDefinition().Add(newDefinition.objectId());
      PO.referencesOfProductOccurrence().setCorrespondingPartDefinition(newDefinition.objectId());
      return newDefinition;
    }

    public static OdPrcFileStructure addNewFileStructure(OdPrcFile file)
    {
      // create file structures section
      OdPrcFileStructure newStructure = OdPrcFileStructure.createObject();
      file.fileStructures().Add(newStructure);
      newStructure.setfileStructureId(OdPrcUniqueId.generateUID());
      file.addFileStructure(newStructure);

      // create file structure globals section
      OdPrcFileStructureGlobals fileStructureGlobals = newStructure.fileStructureGlobals();
      fileStructureGlobals.setTessellationChordHeightRatio(2000);
      fileStructureGlobals.setTessellationAngleDegree(40);

      // file structure header section
      newStructure.setVersions(8137, 8137);

      return newStructure;
    }

    public static OdPrcFile createFileModel()
    {
      // create prc
      OdPrcFile pFile = OdPrcFile.createObject();

      pFile.setVersions(8137, 8137);
      pFile.setfileStructureId(OdPrcUniqueId.generateUID());

      // init model file data section
      pFile.modelFileData().unit().setUnitFromCADFile(true);
      pFile.modelFileData().unit().setUnit(1); // 1 mm

      // create file structures section
      addNewFileStructure(pFile);

      return pFile;
    }

    public static OdPrcFile createTopologyCommon()
    {
      OdPrcFile pFile = createFileModel();

      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();

      OdPrcFileStructure pFS = fileStructures[fileStructures.Count - 1];

      // create root product occurrence
      OdPrcProductOccurrence newProductOccurrence = OdPrcProductOccurrence.createObject();
      pFS.addObject(newProductOccurrence);

      pFS.fileStructureTree().internalData().setRootProductOccurrence(newProductOccurrence.objectId());
      pFile.modelFileData().addStartRootOccurrence(newProductOccurrence);

      return pFile;
    }

    public static void addColorToBaseWithGraphics(OdPrcFileStructure curFileStructure, OdPrcProductOccurrence pBaseWithGraphics, double r, double g, double b)
    {
      OdPrcObjectId newLineStyleId = OdPrcCategory1LineStyle.createByColor(r, g, b, curFileStructure);

      // Attribute
      pBaseWithGraphics.setstyleId(newLineStyleId);
      pBaseWithGraphics.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_Show);
    }

    public class edgeStruct
    {
      public OdPrcEdge pEdge;
      public int startIndx;
      public int endIndx;
    };

    public static OdResult fillBrepDataByVertex(OdPrcBrepData pBrepData, OdGePoint3dArray vertexList, OdUInt32Array2d vertexOrder)
    {
      List<edgeStruct> arrEdges = new List<edgeStruct>();

      int cntFaces = vertexOrder.Count;

      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      pBrepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        for (int i = 0; i < cntFaces; i++)
        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");
          }

          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);

          //add loop
          OdPrcLoop curLoop = OdPrcLoop.createObject();
          pCurFace.addLoop(curLoop);
          int cntEdges = vertexOrder[i].Count;
          if (cntEdges < 3)
          {
            //"Wrong edge count"
            OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
            return OdResult.eInvalidInput;
          }
          for (int j = 0; j < cntEdges; j++)
          {
            uint startIndx = vertexOrder[i][j] - 1;
            uint endIndx = j + 1 < cntEdges ? vertexOrder[i][j + 1] - 1 : vertexOrder[i][0] - 1;
            curLoop.addCoEdge(getCoEdge(arrEdges, (int)startIndx, (int)endIndx, vertexList));
            curLoop.setOrientationWithSurface((sbyte)Orientation.kSame);
          }

          // calculate plane
          OdGePoint3d pnt1 = vertexList[(int)vertexOrder[i][0] - 1];
          OdGePoint3d pnt2 = vertexList[(int)vertexOrder[i][1] - 1];
          OdGePoint3d pnt3 = vertexList[(int)vertexOrder[i][2] - 1];
          OdGeVector3d vec1 = pnt2 - pnt1;
          OdGeVector3d vec2 = pnt3 - pnt2;
          OdGeVector3d vrNormal = vec1.crossProduct(vec2);
          vrNormal.normalize();
          OdGePlane gePlane = new OdGePlane(pnt1, vrNormal);

          OdGeInterval intU = new OdGeInterval(-12345.0, 12345.0);
          OdGeInterval intV = new OdGeInterval(-12345.0, 12345.0);
          gePlane.setEnvelope(intU, intV);

          pPrcPlane.setFromOdGeSurface(gePlane);
          pCurFace.setbaseSurface(pPrcPlane);
        }

        //pCurShell.setShellIsClosed(true); // flag shellIsClosed is entered automatically in the method updateIsClosedFlag in OdPrcBrepModel
      }

      return OdResult.eOk;
    }

    public static OdPrcCoEdge getCoEdge(List<edgeStruct> arrEdges, int startIndx, int endIndx, OdGePoint3dArray vertexList)
    {
      OdPrcCoEdge curCoEdge = OdPrcCoEdge.createObject();

      for (int i = 0; i < arrEdges.Count; i++)
      {
        if (arrEdges[i].startIndx == startIndx && arrEdges[i].endIndx == endIndx)
        {
          curCoEdge.setEdge(arrEdges[i].pEdge);
          curCoEdge.setOrientationWithLoop((sbyte)Orientation.kSame);
          return curCoEdge;
        }
        else if (arrEdges[i].startIndx == endIndx && arrEdges[i].endIndx == startIndx)
        {
          curCoEdge.setEdge(arrEdges[i].pEdge);
          curCoEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);
          return curCoEdge;
        }
      }

      OdGeLineSeg3d geLine = new OdGeLineSeg3d(vertexList[startIndx], vertexList[endIndx]);
      OdPrcLine3d line = OdPrcLine3d.createObject();
      line.setFromOdGeCurve(geLine);

      OdPrcEdge curEdge = OdPrcEdge.createObject();
      curEdge.contentWireEdge().setcurve(line);
      OdPrcUniqueVertex startP = OdPrcUniqueVertex.createObject();
      OdPrcUniqueVertex endP = OdPrcUniqueVertex.createObject();
      startP.setpoint(vertexList[startIndx]);
      endP.setpoint(vertexList[endIndx]);
      curEdge.setStartVertex(startP);
      curEdge.setEndVertex(endP);

      curCoEdge.setEdge(curEdge);
      curCoEdge.setOrientationWithLoop((sbyte)Orientation.kSame);

      edgeStruct newEdgeInArr = new edgeStruct();
      newEdgeInArr.pEdge = curEdge;
      newEdgeInArr.startIndx = startIndx;
      newEdgeInArr.endIndx = endIndx;
      arrEdges.Add(newEdgeInArr);

      return curCoEdge;
    }

    public static void addSimpleTriangle(TriangleInfoPtrArray mesh,
      double nx, double ny, double nz,
      double p1x, double p1y, double p1z,
      double p2x, double p2y, double p2z,
      double p3x, double p3y, double p3z,
      Byte r, Byte g, Byte b)
    {
      TriangleInfo tmp = new TriangleInfo();

      OdGeVector3d v0 = new OdGeVector3d(nx, ny, nz);
      OdGeVector3d v1 = new OdGeVector3d(nx, ny, nz);
      OdGeVector3d v2 = new OdGeVector3d(nx, ny, nz);
      GC.SuppressFinalize(v0);
      GC.SuppressFinalize(v1);
      GC.SuppressFinalize(v2);
      tmp.Set_vtx_normal(v0, v1, v2);

      tmp.p1.x = (float)p1x;
      tmp.p1.y = (float)p1y;
      tmp.p1.z = (float)p1z;

      tmp.p2.x = (float)p2x;
      tmp.p2.y = (float)p2y;
      tmp.p2.z = (float)p2z;

      tmp.p3.x = (float)p3x;
      tmp.p3.y = (float)p3y;
      tmp.p3.z = (float)p3z;

      tmp.color.setRGB(r, g, b);
      GC.SuppressFinalize(tmp);
      mesh.Add(tmp);
    }

    public static void meshExtents(TriangleInfoPtrArray mesh, out OdGeExtents3d extents)
    {
      extents = new OdGeExtents3d();
      int count = mesh.Count;
      for (int idx = 0; idx < count; idx++)
      {
        TriangleInfo pT = mesh[idx];
        extents.addPoint(new OdGePoint3d(pT.p1.x, pT.p1.y, pT.p1.z));
        extents.addPoint(new OdGePoint3d(pT.p2.x, pT.p2.y, pT.p2.z));
        extents.addPoint(new OdGePoint3d(pT.p3.x, pT.p3.y, pT.p3.z));
      }
    }

    public static TriangleInfo CopyTriangleInfo(TriangleInfo from)
    {
      TriangleInfo tmp = from;
      OdGeVector3d v0 = new OdGeVector3d(), v1 = new OdGeVector3d(), v2 = new OdGeVector3d();
      tmp.Get_vtx_normal(v0, v1, v2);
      GC.SuppressFinalize(v0);
      GC.SuppressFinalize(v1);
      GC.SuppressFinalize(v2);
      TriangleInfo triangleInfo = new TriangleInfo();
      triangleInfo.Set_vtx_normal(v0, v1, v2);
      triangleInfo.alpha = tmp.alpha;
      triangleInfo.color = tmp.color;
      triangleInfo.faceIdx = tmp.faceIdx;
      triangleInfo.materialID = tmp.materialID;
      triangleInfo.p1 = tmp.p1;
      triangleInfo.p2 = tmp.p2;
      triangleInfo.p3 = tmp.p3;
      GC.SuppressFinalize(triangleInfo);
      return triangleInfo;
    }

    public static OdPrc3dTess fillTessellation(OdPrcFileStructure newStructure, TriangleInfoPtrArray mesh, OdPrcExportContext prcContext)
    {
      // general tess section
      OdPrcFileStructureTessellation tess = newStructure.fileStructureTessellation();
      OdPrcBaseTessDataPtrArray tessData = tess.tessellations();
      OdPrc3dTess tess3d = OdPrc3dTess.createObject();
      tess3d.setIsCalculated(true);
      tess3d.setHasFaces(true);
      tess3d.setHasLoops(false);
      tess3d.setMustRecalculateNormals(false);
      tessData.Add(tess3d);
      OdFloatArray coordinates = tess3d.coordinates();
      coordinates.Capacity = (mesh.Count * 9);
      OdFloatArray normal_coordinate = tess3d.normalCoordinate();
      normal_coordinate.Capacity = (mesh.Count * 9);
      OdUInt32Array triangulated_index = tess3d.triangulatedIndex();
      triangulated_index.Capacity = (mesh.Count * 9);
      OdFloatArray texture_coordinates = tess3d.textureCoordinate();
      texture_coordinates.Capacity = (mesh.Count * 6);

      // group Triangles by Faces and materials
      Dictionary<PrcFaceKey, TriangleInfoPtrArray> arrFaces = new Dictionary<PrcFaceKey, TriangleInfoPtrArray>();
      for (int idx = 0; idx < mesh.Count; ++idx)
      {
        TriangleInfo triangleInfo = CopyTriangleInfo(mesh[idx]);
        TriangleInfoPtrArray arr = new TriangleInfoPtrArray();
        arr.Add(triangleInfo);

        PrcFaceKey key = new PrcFaceKey(triangleInfo.faceIdx, triangleInfo.getTriangleType(), triangleInfo.materialID, triangleInfo.color, triangleInfo.alpha);

        arrFaces.Add(key, arr);
      }

      uint uStartTriangulated = 0;
      tess3d.faceTessellation().Capacity = (arrFaces.Count);

      foreach (var item in arrFaces)
      {
        PrcFaceKey prcFaceKey = item.Key;
        TriangleInfoPtrArray arrTriangleInfo = item.Value;

        OdPrcTessFace curFace = new OdPrcTessFace();
        curFace.setStartTriangulated(uStartTriangulated);
        curFace.setBehaviour(1);
        curFace.sizesTriangulated().Add((uint)arrTriangleInfo.Count);

        if (prcFaceKey.m_type == TriangleInfo.TriangleType.kTriangleColored)
        {
          curFace.setUsedEntitiesFlag(PRC_Globals.PRC_FACETESSDATA_Triangle);
          curFace.setHasVertexColors(true);
          curFace.arrayRGBA().colors().Capacity = (arrTriangleInfo.Count * 9);
          for (int i = 0; i < arrTriangleInfo.Count; ++i)
          {
            TriangleInfoColoredPoints pTriangle = new TriangleInfoColoredPoints(TriangleInfoColoredPoints.getCPtr(arrTriangleInfo[i]).Handle, false);

            //points
            int _nCoordIndex = coordinates.Count;
            coordinates.Add(pTriangle.p1.x); coordinates.Add(pTriangle.p1.y); coordinates.Add(pTriangle.p1.z);
            coordinates.Add(pTriangle.p2.x); coordinates.Add(pTriangle.p2.y); coordinates.Add(pTriangle.p2.z);
            coordinates.Add(pTriangle.p3.x); coordinates.Add(pTriangle.p3.y); coordinates.Add(pTriangle.p3.z);

            // normals
            int _nNormalIndex = normal_coordinate.Count;

            OdGeVector3d v1 = new OdGeVector3d(), v2 = new OdGeVector3d(), v3 = new OdGeVector3d();
            pTriangle.Get_vtx_normal(v1, v2, v3);
            normal_coordinate.Add((float)v1.x); normal_coordinate.Add((float)v1.y); normal_coordinate.Add((float)v1.z);
            normal_coordinate.Add((float)v2.x); normal_coordinate.Add((float)v2.y); normal_coordinate.Add((float)v2.z);
            normal_coordinate.Add((float)v3.x); normal_coordinate.Add((float)v3.y); normal_coordinate.Add((float)v3.z);

            // triangulated indices
            triangulated_index.Add((uint)_nNormalIndex);
            triangulated_index.Add((uint)_nCoordIndex);
            triangulated_index.Add((uint)_nNormalIndex + 3);
            triangulated_index.Add((uint)_nCoordIndex + 3);
            triangulated_index.Add((uint)_nNormalIndex + 6);
            triangulated_index.Add((uint)_nCoordIndex + 6);

            byte red_v1, red_v2, red_v3;
            pTriangle.GetRed(out red_v1, out red_v2, out red_v3);

            byte green_v1, green_v2, green_v3;
            pTriangle.GetRed(out green_v1, out green_v2, out green_v3);

            byte blue_v1, blue_v2, blue_v3;
            pTriangle.GetRed(out blue_v1, out blue_v2, out blue_v3);

            curFace.arrayRGBA().colors().Add(red_v1);
            curFace.arrayRGBA().colors().Add(green_v1);
            curFace.arrayRGBA().colors().Add(blue_v1);

            curFace.arrayRGBA().colors().Add(red_v2);
            curFace.arrayRGBA().colors().Add(green_v2);
            curFace.arrayRGBA().colors().Add(blue_v2);

            curFace.arrayRGBA().colors().Add(red_v3);
            curFace.arrayRGBA().colors().Add(green_v3);
            curFace.arrayRGBA().colors().Add(blue_v3);

          }
          uStartTriangulated += (uint)arrTriangleInfo.Count * 6;
        }
        else if (prcFaceKey.m_type == TriangleInfo.TriangleType.kTriangleTextured)
        {
          curFace.setUsedEntitiesFlag(PRC_Globals.PRC_FACETESSDATA_TriangleTextured);
          curFace.setNumberOfTextureCoordinateIndexes(1);
          for (int i = 0; i < arrTriangleInfo.Count; ++i)
          {
            TriangleInfoTextured _pTriangle = new TriangleInfoTextured(TriangleInfoTextured.getCPtr(arrTriangleInfo[i]).Handle, false);

            // normals
            OdGeVector3d v1 = new OdGeVector3d(), v2 = new OdGeVector3d(), v3 = new OdGeVector3d();
            _pTriangle.Get_vtx_normal(v1, v2, v3);
            int _nNormalIndex = normal_coordinate.Count;
            normal_coordinate.Add((float)v1.x); normal_coordinate.Add((float)v1.y); normal_coordinate.Add((float)v1.z);
            normal_coordinate.Add((float)v2.x); normal_coordinate.Add((float)v2.y); normal_coordinate.Add((float)v2.z);
            normal_coordinate.Add((float)v3.x); normal_coordinate.Add((float)v3.y); normal_coordinate.Add((float)v3.z);

            // texture coordinates
            int nTexCoordIndex = texture_coordinates.Count;
            OdGePoint2d p_v1 = new OdGePoint2d(), p_v2 = new OdGePoint2d(), p_v3 = new OdGePoint2d();
            _pTriangle.GetTexCoords(p_v1, p_v2, p_v3);
            texture_coordinates.Add((float)p_v1.x); texture_coordinates.Add((float)p_v1.y);
            texture_coordinates.Add((float)p_v2.x); texture_coordinates.Add((float)p_v2.y);
            texture_coordinates.Add((float)p_v3.x); texture_coordinates.Add((float)p_v3.y);

            //points
            int _nCoordIndex = coordinates.Count;
            coordinates.Add(_pTriangle.p1.x); coordinates.Add(_pTriangle.p1.y); coordinates.Add(_pTriangle.p1.z);
            coordinates.Add(_pTriangle.p2.x); coordinates.Add(_pTriangle.p2.y); coordinates.Add(_pTriangle.p2.z);
            coordinates.Add(_pTriangle.p3.x); coordinates.Add(_pTriangle.p3.y); coordinates.Add(_pTriangle.p3.z);

            // triangulated indices
            triangulated_index.Add((uint)_nNormalIndex);
            triangulated_index.Add((uint)nTexCoordIndex);
            triangulated_index.Add((uint)_nCoordIndex);
            triangulated_index.Add((uint)_nNormalIndex + 3);
            triangulated_index.Add((uint)nTexCoordIndex + 2);
            triangulated_index.Add((uint)_nCoordIndex + 3);
            triangulated_index.Add((uint)_nNormalIndex + 6);
            triangulated_index.Add((uint)nTexCoordIndex + 4);
            triangulated_index.Add((uint)_nCoordIndex + 6);
          }

          //material
          OdPrcObjectId lineStyleID = new OdPrcObjectId();
          TriangleInfoTextured pTriangle = new TriangleInfoTextured(TriangleInfoTextured.getCPtr(arrTriangleInfo[0]).Handle, false);
          if (pTriangle.materialLineStyleID != null)
          {
            lineStyleID = new OdPrcObjectId(pTriangle.materialLineStyleID);
          }
          if (lineStyleID.isNull())
          {
            if (pTriangle.materialID != null)
            {
              DrawingMaterialNode matNode = new DrawingMaterialNode();
              matNode.pMaterial = pTriangle.materialID;
              matNode.drawingColor = pTriangle.color;
              matNode.transparency.setAlpha(pTriangle.alpha);
              lineStyleID = prcContext.getLineStyleID(matNode, newStructure);
            }
            else
            {
              DrawingColorNode colorNode = new DrawingColorNode();
              colorNode.drawingColor = pTriangle.color;
              colorNode.transparency.setAlpha(pTriangle.alpha);
              lineStyleID = prcContext.getLineStyleID(colorNode, newStructure);
            }
          }
          if (!lineStyleID.isNull())
          {
            curFace.lineAttributes().Add(lineStyleID);
          }

          uStartTriangulated += (uint)arrTriangleInfo.Count * 9;
        }
        else if (prcFaceKey.m_type == TriangleInfo.TriangleType.kTriangle)
        {
          curFace.setUsedEntitiesFlag(PRC_Globals.PRC_FACETESSDATA_Triangle);
          for (int i = 0; i < arrTriangleInfo.Count; ++i)
          {
            TriangleInfoColoredPoints _pTriangle = new TriangleInfoColoredPoints(TriangleInfoColoredPoints.getCPtr(arrTriangleInfo[i]).Handle, false);

            //points
            int nCoordIndex = coordinates.Count;
            coordinates.Add(_pTriangle.p1.x); coordinates.Add(_pTriangle.p1.y); coordinates.Add(_pTriangle.p1.z);
            coordinates.Add(_pTriangle.p2.x); coordinates.Add(_pTriangle.p2.y); coordinates.Add(_pTriangle.p2.z);
            coordinates.Add(_pTriangle.p3.x); coordinates.Add(_pTriangle.p3.y); coordinates.Add(_pTriangle.p3.z);

            // normals
            int nNormalIndex = normal_coordinate.Count;
            OdGeVector3d v1 = new OdGeVector3d(), v2 = new OdGeVector3d(), v3 = new OdGeVector3d();
            _pTriangle.Get_vtx_normal(v1, v2, v3);
            normal_coordinate.Add((float)v1.x); normal_coordinate.Add((float)v1.y); normal_coordinate.Add((float)v1.z);
            normal_coordinate.Add((float)v2.x); normal_coordinate.Add((float)v2.y); normal_coordinate.Add((float)v2.z);
            normal_coordinate.Add((float)v3.x); normal_coordinate.Add((float)v3.y); normal_coordinate.Add((float)v3.z);

            // triangulated indices
            triangulated_index.Add((uint)nNormalIndex);
            triangulated_index.Add((uint)nCoordIndex);
            triangulated_index.Add((uint)nNormalIndex + 3);
            triangulated_index.Add((uint)nCoordIndex + 3);
            triangulated_index.Add((uint)nNormalIndex + 6);
            triangulated_index.Add((uint)nCoordIndex + 6);
          }

          //material
          OdPrcObjectId lineStyleID = new OdPrcObjectId();
          TriangleInfo pTriangle = arrTriangleInfo[0];

          if (pTriangle.materialID != null)
          {
            DrawingMaterialNode matNode = new DrawingMaterialNode();
            matNode.pMaterial = pTriangle.materialID;
            matNode.drawingColor = pTriangle.color;
            matNode.transparency.setAlpha(pTriangle.alpha);
            lineStyleID = prcContext.getLineStyleID(matNode, newStructure);
          }
          else
          {
            DrawingColorNode colorNode = new DrawingColorNode();
            colorNode.drawingColor = pTriangle.color;
            colorNode.transparency.setAlpha(pTriangle.alpha);
            lineStyleID = prcContext.getLineStyleID(colorNode, newStructure);
          }
          if (!lineStyleID.isNull())
          {
            curFace.lineAttributes().Add(lineStyleID);
          }

          uStartTriangulated += (uint)arrTriangleInfo.Count * 6;
        }
        else
          throw new OdError(OdResult.eInvalidInput);

        tess3d.faceTessellation().Add(curFace);
      }

      //remove duplicate data
      tess3d.optimize();
      return tess3d;
    }

  }
}

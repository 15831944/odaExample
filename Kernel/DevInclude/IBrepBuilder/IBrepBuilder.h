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

#ifndef _IBB_INCLUDED_
#define _IBB_INCLUDED_

#include "OdDbStub.h"
#include "RxObject.h"
#include "Ge/Ge.h"

class OdGeCurve3d;
class OdGeSurface;

class OdIBrepBuilder
{
public:
  virtual ~OdIBrepBuilder() {};

  //Returns type of output geometry 
  virtual BrepType getType() = 0;

  // Add a co-edge associated to a previously added edge. 
  // A co-edge represents the use of an edge on one of the edge's faces.
  virtual BRepBuilderGeometryId addCoedge(const BRepBuilderGeometryId& loopId, const BRepBuilderGeometryId& edgeId, bool isCoedgeReversed = false, const OdGeCurve2d* pParCur = NULL) = 0;
  // Add a new edge to the geometry being built.
  virtual BRepBuilderGeometryId addEdge(const OdGeCurve3d* pCurveForEdge) = 0;
  // Add a new edge to the geometry being built.
  virtual BRepBuilderGeometryId addEdge(const OdGeCurve3d* pCurveForEdge, const BRepBuilderGeometryId& vertex1Id, const BRepBuilderGeometryId& vertex2Id) = 0;
  // Add a new vertex to the geometry being built.
  virtual BRepBuilderGeometryId addVertex(const OdGePoint3d& point) = 0;
  // Creates an empty face in the geometry being built.
  virtual BRepBuilderGeometryId addFace(const OdGeSurface* pSurf, bool isFaceReversed, const BRepBuilderGeometryId& shellId = OdBrepBuilder::kDefaultShellId) = 0;
  // Creates an empty loop in a given face of the geometry being built.
  virtual BRepBuilderGeometryId addLoop(const BRepBuilderGeometryId& faceId) = 0;
  // Creates a shell.
  virtual BRepBuilderGeometryId addShell(const BRepBuilderGeometryId& complexId) = 0;
  // Creates a complex - upper topology element with gives shell
  virtual BRepBuilderGeometryId addComplex() = 0;
  // Set tag value (it is used for faces, edges and vertices)
  // Use setTag just after addFace, addEdge and addVertex calls.
  virtual void setTag(const BRepBuilderGeometryId& id, OdUInt32 tag) = 0;

  //Allow BRepBuilder to remove problematic faces (e.g., due to inaccurate edge geometry). 
  //If this option is enabled and BRepBuilder removes some faces, 
  //the output geometry's type will be OpenShell regardless of the expected type specified when the BRepBuilder was created.
  virtual void allowRemovalOfProblematicFaces() = 0;
 
  //A validator function that checks the state of this BRepBuilder object.Returns true if this BRepBuilder object is accepting b - rep data, false otherwise.
  virtual bool canAddGeometry() = 0;

  //Indicates that the caller has finished defining the given complex.
  virtual void finishComplex(const BRepBuilderGeometryId& complexId) = 0;

  //Indicates that the caller has finished defining the given shell
  virtual void finishShell(const BRepBuilderGeometryId& shellId) = 0;

  //Indicates that the caller has finished defining the given face.
  virtual void finishFace(const BRepBuilderGeometryId& faceId) = 0;

  //Indicates that the caller has finished defining the given loop.
  virtual void finishLoop(const BRepBuilderGeometryId& loopId) = 0;
  
  //Get the Geometry object built by this BRepBuilder. This will clear the built Geometry stored in the BRepBuilder.
  //This function will throw if this BRepBuilder hasn't completed building the b-rep. Use IsResultAvailable() to verify that this BRepBuilder contains a valid result.
  virtual OdRxObjectPtr getResult() = 0;

  //A validator function that checks whether the surface object is of type supported as face surface by BRepBuilder.
  virtual  bool isPermittedSurfaceType(const OdGeSurface* pSurf) = 0;

  //A validator function that checks the state of this BRepBuilder object. Returns true if this BRepBuilder object has successfully built a b-rep.
  virtual bool isResultAvailable() = 0;


  //A validator function that checks whether the edge id corresponds to an edge previously added to this BRepBuilder object.
  virtual bool isValidEdgeId(const BRepBuilderGeometryId& edgeId) = 0;

  //A validator function that checks whether the complex id corresponds to a complex previously added to this BRepBuilder object.
  virtual bool isValidComplexId(const BRepBuilderGeometryId& complexId) = 0;

  //A validator function that checks whether the shell id corresponds to a shell previously added to this BRepBuilder object.
  virtual bool isValidShellId(const BRepBuilderGeometryId& shellId) = 0;

  //A validator function that checks whether the face id corresponds to a face previously added to this BRepBuilder object.
  virtual bool isValidFaceId(const BRepBuilderGeometryId& faceId) = 0;

  //A validator function that checks whether the loop id corresponds to a loop previously added to this BRepBuilder object.
  virtual bool isValidLoopId(const BRepBuilderGeometryId& loopId) = 0;


  //Returns 'true' if BRepBuilder removed some problematic faces from the output geometry, 'false' if not.
  //If allowRemovalOfProblematicFaces was not called to enable removal of problematic faces, this function will return 'false'. Note that if some faces were removed,
  //the output geometry's type will be OpenShell regardless of the expected type that was specified when the BRepBuilder was created.
  virtual bool removedSomeFaces() = 0;

  //Make BRepBuilder allow edges that it would normally disallow as being too short for geometry.
  virtual void setAllowShortEdges() = 0;

  //Sets flag from BrEntityFlags on an entity.
  virtual void setFlag(const BRepBuilderGeometryId &id, OdUInt32 flag, bool enable) = 0;

  //Sets material id to a face.
  virtual void setFacesMaterial(const BRepBuilderGeometryId& faceId, OdDbStub& materialId) = 0;
  //Sets material mapping
  virtual OdResult setFaceMaterialMapping(const BRepBuilderGeometryId& faceId,
    const OdGiMapper& materialMapper) = 0;

  //Sets edge color
  virtual OdResult setEdgeColor(const BRepBuilderGeometryId& edgeId, const OdCmEntityColor& edgeColor) = 0;

  //Sets face color
  virtual OdResult setFaceColor(const BRepBuilderGeometryId& faceId, const OdCmEntityColor& faceColor) = 0;

  //Complete construction of the geometry. The geometry will be validated and, if valid, stored in this Builder.
  virtual OdRxObjectPtr finish() = 0;

  //Enable/disable validation in BRepBuilder
  virtual void enableValidator(bool bEnable = true) = 0;

  //Returns errors found during validation
  virtual const ValidationErrors* getValidationErrors() const = 0;

};

#endif //_IBB_INCLUDED_

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

#ifndef _ODTV_ENTITYGEOMETRYSHELL_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRYSHELL_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "Int32Array.h"
#include "UInt32Array.h"
#include "UInt8Array.h"
#include "DoubleArray.h"

#include "TvTraitsDef.h"
#include "TvMaterial.h"
#include "TvMaterialsTraits.h"

/** \details
  This is an interface class for an OdTvShellData object.
  \sa
  <link tv_geometry_shells, Work with Shells>
*/ 
class ODTV_EXPORT OdTvShellData : public OdTvIObject
{
public:

  /** \details
    Types of geometry.
  */
  enum FaceCulling
  {
    kInherited = 0, // Inherits from the device property ("Discard back faces").
    kOn = 1,        // Enable culling.
    kOff = 2        // Disable culling.
  };

  /** \details
    Sets the geometry data of the shell.
    
    \param verticesArray  [in] A vertex array of the shell.
    \param faces          [in] A face array of the shell.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(const OdTvPointArray& verticesArray, const OdInt32Array& faces) = 0;

  /** \details
    Sets the geometry data of the shell.
    
    \param nVertices    [in] A quantity of shell vertexes.
    \param vertices     [in] A pointer to the array of points that represent the vertexes of the shell.
    \param faceListSize [in] A size of the face data list for the shell.
    \param faces        [in] A pointer to the array of face data that represents the faces of the shell.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(OdInt32 nVertices, const OdTvPoint* vertices, OdInt32 faceListSize, const OdInt32* faces ) = 0;

  /** \details
    Gets the geometry data of the shell.
    
    \param verticesArray  [out] A placeholder for the array of shell vertexes.
    \param faces          [out] A placeholder for the array of shell faces.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the parameter values were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdTvPointArray& verticesArray, OdInt32Array& faces) const = 0;

  /** \details
    Sets whether to take lighting into account.
    
    \param bDisable [in] A bool value that instructs whether to disable lighting calculations (set to true) or not (set to false). 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_lights, Work with Lights>
  */
  virtual OdTvResult setDisableLighting(bool bDisable) = 0;

  /** \details
    Returns whether to take lighting into account. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of bool type that shows if lighting calculations are disabled (set to true) or not (set to false).
    \remarks
    If the method successfully returns a bool value, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_lights, Work with Lights>
  */
  virtual bool getDisableLighting(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the mode of back face culling. The default value is kInherited.
    
    \param val [in] A value that determines a mode of back face culling.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBackFaceCulling(FaceCulling val) = 0;

  /** \details
    Returns the mode of back face culling.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of the FaceCulling enumerated type that contains a mode of back face culling.
    \remarks
    If the method successfully returns a FaceCulling value, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual FaceCulling getBackFaceCulling(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the selectable property for the faces of the shell. The selectable property determines whether the faces of the shell can be selected.
    
    \param bSelectable [in] A boolean value that is equal to true if the faces can be selected; otherwise it should be equal to false.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new value of the selectable property for the shell faces is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesSelectable(bool bSelectable) = 0;

  /** \details
    Retrieves current value of the selectable property for the faces of the shell. 
    Selectable property determines whether the faces of the shell can be selected.
    
    \param bIsInherited [out] A placeholder for a value of the flag that determines whether the selectability property is inherited.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the faces of the shell can be selected; otherwise the method returns false.
    \remarks
    The method stores true in the bIsInherited parameter if the selectable property value is inherited from the parent entity (sub-entity).
    If the rc parameter is not null and the current value of the selectable property is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getFacesSelectable(bool* bIsInherited = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the selectable property for the edges of the shell. 
    The selectable property determines whether the edges of the shell can be selected.
    
    \param bSelectable [in] A boolean value that is equal to true if the edges can be selected; otherwise it should be equal to false.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new value of the selectable property for the shell edges is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesSelectable(bool bSelectable) = 0;

  /** \details
    Retrieves current value of the selectable property for the edges of the shell. 
    Selectable property determines whether the edges of the shell can be selected.
    
    \param bIsInherited [out] A placeholder for a value of the flag that determines whether the selectability property is inherited.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the edges of the shell can be selected; otherwise the method returns false.
    \remarks
    The method stores true in the bIsInherited parameter if the selectable property value is inherited from the parent entity (sub-entity).
    If the rc parameter is not null and the current value of the selectable property is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getEdgesSelectable(bool* bIsInherited = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the number of faces in the shell.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdUInt32 type that contains the number of shell faces.
    \remarks
    If the method successfully returns an OdUInt32 value, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getFacesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the number of edges in the shell.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdUInt32 type that contains the number of shell edges.
    \remarks
    If the method successfully returns an OdUInt32 value, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getEdgesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the number of vertices in the shell.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdUInt32 type that contains the number of shell vertices.
    \remarks
    If the method successfully returns an OdUInt32 value, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getVerticesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the number of triangles in the shell.
    
    \param uncountedFaces [out] A quantity of new uncounted triangles.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value of OdUInt32 type that contains the number of shell triangles.
    \remarks
    If the method successfully returns an OdUInt32 value, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getTrianglesCount(OdUInt32& uncountedFaces, OdTvResult* rc = NULL) const = 0;

  /** \details
    Replaces vertices of the shell starting with startPos.
    
    \param startPos       [in] A start position from which replacement is applied.
    \param verticesArray  [in] A pointer to an array of <link OdTvPoint, OdTvPoint> objects that represent the new vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaRange(OdUInt32 startPos, const OdTvPointArray& verticesArray) = 0;

  /** \details
    Replaces vertices of the shell starting with startPos.
    
    \param startPos  [in] A start position from which replacement is applied.
    \param nVertices [in] A quantity of new vertexes.
    \param vertices  [in] A pointer to an array of new vertices.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaRange(OdUInt32 startPos, OdUInt32 nVertices, const OdTvPoint* vertices) = 0;

  /** \details
    Replaces the vertexes of the shell according to a vertex list. The list of vertexes is defined with a set of vertex position objects.
    
    \param indVertices    [in] An array of vertex positions to be replaced.
    \param verticesArray  [in] An array of <link OdTvPoint, OdTvPoint> objects that represent the new vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaList(const OdInt32Array& indVertices, const OdTvPointArray& verticesArray) = 0;

  /** \details
    Replaces the vertexes of the shell according to a vertex list. The list of vertexes is defined with a set of vertex position objects.
    
    \param nVertices      [in] A quantity of vertexes to be replaced.
    \param indVertices    [in] A pointer to an array of vertex positions to be replaced.
    \param vertices       [in] A pointer to an array of <link OdTvPoint, OdTvPoint> objects that represent the new vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaList(OdUInt32 nVertices, const OdUInt32* indVertices, const OdTvPoint* vertices) = 0;

  /** \details
    Replaces faces of the shell starting with startFace.
    
    \param startFace  [in] A position of the face from which replacement is applied.
    \param faces      [in] A pointer to an array of <link OdTvPoint, OdTvPoint> objects that represent faces to be replaced with.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell faces were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editFacesViaRange(OdUInt32 startFace, const OdInt32Array& faces) = 0;

  /** \details
    Replaces faces of the shell starting with startFace.
    
    \param startFace    [in] A position of the face from which replacement is applied.
    \param faceListSize [in] A quantity of faces to be replaced.
    \param faces        [in] A pointer to an array of new face data.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell faces were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editFacesViaRange(OdUInt32 startFace, OdUInt32 faceListSize, const OdInt32* faces) = 0;

  /** \details
    Replaces the faces of the shell according to a list of faces.
    
    \param indFaces [in] An array of faces to be replaced.
    \param faces    [in] An array of new faces.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell faces were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editFacesViaList(const OdUInt32Array& indFaces, const OdInt32Array& faces) = 0;

  /** \details
    Replaces faces defined by 'indFaces' of the shell.
    
    \param nFaces       [in] A number of faces to be replaced.
    \param indFaces     [in] A pointer to an array of face data to be replaced.
    \param faceListSize [in] A quantity of faces to be replaced.
    \param faces        [in] A pointer to an array of new face data.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified shell faces were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editFacesViaList(OdUInt32 nFaces, const OdUInt32* indFaces, OdUInt32 faceListSize, const OdInt32* faces) = 0;

  /** \details
    Sets colors for a list of shell vertexes.
    
    \param nCount       [in] A quantity of vertexes for setting the color.
    \param indVertices  [in] A pointer to an array of vertex indexes.
    \param colors       [in] A pointer to an array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified shell vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors) = 0;
  
  /** \details
    Sets colors for a list of shell vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param colors       [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified shell vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDefArray& colors) = 0;
  
  /** \details
    Sets a color for a list of shell vertexes.
    
    \param nCount       [in] A quantity of vertexes for setting the color.
    \param indVertices  [in] A pointer to an array of vertex indexes.
    \param color        [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified shell vertexes was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets a color for a list of shell vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param color        [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified shell vertexes was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets a color for a range of shell vertexes.
    
    \param indStart [in] A starting index of the vertex to be set with color.
    \param nCount   [in] A quantity of vertexes to be set with color.
    \param color    [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified shell vertexes was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets a color for a range of shell vertexes.
    
    \param indStart [in] A starting index of the vertex to be set with color.
    \param colors   [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified shell vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, const OdTvRGBColorDefArray& colors) = 0;
  
  /** \details
    Sets a color for a range of shell vertexes.
    
    \param indStart [in] A starting index of the vertex to be set with color.
    \param nCount   [in] A quantity of vertexes to be set with color.
    \param colors   [in] A pointer to an array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified shell vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors) = 0;
  
  /** \details
    Retrieves colors for a range of shell vertexes.
    
    \param indStart [in] A starting index of the range.
    \param nCount   [in] A quantity of vertexes in the range.
    \param colors   [out] A placeholder for an array of color definitions to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified shell vertexes were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves colors for a range of shell vertexes.
    
    \param indVertices [in] An array of shell vertex indexes.
    \param colors      [out] A placeholder for an array of color definitions to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified shell vertexes were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getVertexColorsViaList(const OdInt32Array& indVertices, OdTvRGBColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves the color for a specified shell vertex.
    
    \param ind [in] A shell vertex index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvRGBColorDef, OdTvRGBColorDef> class that represents the color information.
    \remarks
    If the rc parameter is not null and the color data was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Vertex orientation management.
  */
  
  /** \details
    Sets a new vertex orientation value for the shell.
    
    \param orientation [in] A vertex orientation value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If a new vertex orientation was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexOrientation(OdTv::OrientationType orientation) = 0;
  
  /** \details
    Retrieves the current vertex orientation of the shell.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the vertex orientation.
    \remarks
    If the rc parameter is not null and the orientation type value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTv::OrientationType getVertexOrientation(OdTvResult* rc = NULL) const = 0;

  /**
  Vertex normals management.
  */
  
  /** \details
    Sets normal vectors for a list of shell vertexes.
    
    \param nCount      [in] A quantity of vertexes in the list.
    \param indVertices [in] An array of vertex indexes represented with a pointer to the first array element.
    \param vectors     [in] A array of normal vectors represented with a pointer to a first vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector* vectors) = 0;
  
  /** \details
    Sets normal vectors for a list of shell vertexes.
    
    \param indVertices [in] An array of vertex indexes.
    \param vectors     [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normal vectors for a list of shell vertexes.
    
    \param nCount      [in] A quantity of vertexes in the list.
    \param indVertices [in] An array of vertex indexes represented with a pointer to the first array element.
    \param vector      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normal vectors for a list of shell vertexes.
    
    \param indVertices [in] An array of vertex indexes.
    \param vector      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVector& vector) = 0;

  /** \details
    Sets normal vectors for a range of shell vertexes.
    
    \param indStart [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount   [in] A quantity of vertexes in the range from the start position.
    \param vector   [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normal vectors for a range of shell vertexes.
    
    \param indStart     [in] An index of the shell vertex array that represents the start position of the range.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normal vectors for a range of shell vertexes.
    
    \param indStart [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount   [in] A quantity of vertexes in the range from the start position.
    \param vectors  [in] An array of normal vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors) = 0;

  /** \details
    Retrieves normal vectors for a range of shell vertexes.
    
    \param indStart     [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves normal vectors for a list of shell vertexes.
    
    \param indVertices [in] An array of vertex indexes.
    \param vectors     [out] A placeholder for the array of normal vectors to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexNormalsViaList(const OdInt32Array& indVertices, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves the normal vector for a specified shell vertex.
    
    \param ind      [in] A shell vertex index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the <link OdTvVector, OdTvVector> class that contains normal vector information.
    \remarks
    If the rc parameter is not null and the normal vector object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Vertex mapping coordinates management.
  */
  
  /** \details
    Sets mapping coordinates for a list of shell vertices.
    
    \param nCount        [in] A quantity of vertices.
    \param indVertices   [in] An array of vertex indexes represented with a pointer to the first array element.
    \param mappingCoords [in] An array of UV mapping coordinates represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a list of shell vertices.
    
    \param indVertices   [in] An array of vertex indexes.
    \param mappingCoords [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2dArray& mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a list of shell vertices.
    
    \param nCount       [in] A quantity of vertices.
    \param indVertices  [in] An array of vertex indexes represented with a pointer to the first array element.
    \param mappingCoord [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord) = 0;
  
  /** \details
    Sets mapping coordinates for a list of shell vertices.
    
    \param indVertices  [in] An array of vertex indexes.
    \param mappingCoord [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2d& mappingCoord) = 0;

  /** \details
    Sets mapping coordinates for a range of shell vertexes.
    
    \param indStart       [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount         [in] A quantity of vertexes in the range from the start position.
    \param mappingCoords  [in] An array of UV mapping coordinates represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a range of shell vertexes.
    
    \param indStart       [in] An index of the shell vertex array that represents the start position of the range.
    \param mappingCoords  [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, const OdTvPoint2dArray& mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a range of shell vertexes.
    
    \param indStart     [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param mappingCoord [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord) = 0;

  /** \details
    Retrieves mapping coordinates for a range of shell vertexes.
    
    \param indStart       [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount         [in] A quantity of vertexes in the range from the start position.
    \param mappingCoords  [out] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved mapping coordinates are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const = 0;
  
  /** \details
    Retrieves mapping coordinates for a list of shell vertexes.
    
    \param indVert        [in] An array of indexes of the shell vertexes.
    \param mappingCoords  [out] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved mapping coordinates are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indVert, OdTvPoint2dArray& mappingCoords) const = 0;
  
  /** \details
    Retrieves mapping coordinates for a specified shell vertex.
    
    \param ind    [in] A shell vertex index.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the <link OdTvVector, OdTvVector> class that contains normal vector information.
    \remarks
    If the retrieved mapping coordinates are successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  //**************************************************************************************
  // Group of the methods for managing the properties of faces
  //**************************************************************************************

  /**
  Face color management.
  */
  
  /** \details
    Sets colors for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param colors     [in] An array of color definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors) = 0;
  
  /** \details
    Sets colors for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param colors     [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets colors for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets a color for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDef& color) = 0;

  /** \details
    Sets a color for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets colors for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param colors     [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets colors for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param colors     [in] An array of color definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors) = 0;

  /** \details
    Retrieves color definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param colors     [out] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved color definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves color definition objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param colors     [out] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved color definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getFaceColorsViaList(const OdInt32Array& indFaces, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves a color definition object for a specified face of the shell.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvColorDef class that contains color definition information.
    \remarks
    If the retrieved color definition object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face normal management.
  */
  
  /** \details
    Sets normals for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param vectors    [in] An array of normal vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normals are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector* vectors) = 0;
  
  /** \details
    Sets normals for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param vectors    [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normals are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(const OdInt32Array& indFaces, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normals for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param vector     [in] A normal vector object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normals for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param vector     [in] A normal vector object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(const OdInt32Array& indFaces, const OdTvVector& vector) = 0;

  /** \details
    Sets a normal vector for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param vector     [in] A normal vector object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normals for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param vectors    [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normals are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normals for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param vectors    [in] An array of normal vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normals are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors) = 0;

  /** \details
    Retrieves normal vectors for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param vectors    [out] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves normal vectors for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param vectors    [out] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceNormalsViaList(const OdInt32Array& indFaces, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves a color definition object for a specified shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the <link OdTvVector, OdTvVector> class that contains normal vector information.
    \remarks
    If the retrieved normal vector is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvVector getFaceNormal(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face visibility management.
  */
  
  /** \details
    Sets visibility data for a list of shell faces.
    
    \param nCount         [in] A quantity of faces.
    \param indFaces       [in] An array of face indexes represented with a pointer to the first array element.
    \param visibilities   [in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef* visibilities) = 0;
  
  /** \details
    Sets visibility data for a list of shell faces.
    
    \param indFaces       [in] An array of face indexes represented with a pointer to the first array element.
    \param visibilities   [in] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(const OdInt32Array& indFaces, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets visibility data for a list of shell faces.
    
    \param nCount       [in] A quantity of faces.
    \param indFaces     [in] An array of face indexes represented with a pointer to the first array element.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef& visibility) = 0;
  
  /** \details
    Sets visibility data for a list of shell faces.
    
    \param indFaces     [in] An array of face indexes represented with a pointer to the first array element.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(const OdInt32Array& indFaces, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets visibility data for a range of shell faces.
    
    \param indStart     [in] An index of the shell face array that represents the start position of the range.
    \param nCount       [in] A quantity of faces in the range from the start position.
    \param visibilities [in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities) = 0;
  
  /** \details
    Sets visibility data for a range of shell faces.
    
    \param indStart     [in] An index of the shell face array that represents the start position of the range.
    \param visibilities [in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets visibility data for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param visibility [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Retrieves visibility data for a range of shell faces.
    
    \param indStart     [in] An index of the shell face array that represents the start position of the range.
    \param nCount       [in] A quantity of faces in the range from the start position.
    \param visibilities [out] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved visibility data objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves visibility data for a list of shell faces.
    
    \param indFaces     [in] An array of face indexes.
    \param visibilities [out] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved visibility data objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceVisibilitiesViaList(const OdInt32Array& indFaces, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves visibility data for a specified shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVisibilityDef class that contains information about object visibility (visible or invisible).
    \remarks
    If the retrieved visibility data object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvVisibilityDef getFaceVisibility(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face layer management.
  */
  
  /** \details
    Sets layers for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param layers     [in] An array of layer objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef* layers) = 0;
  
  /** \details
    Sets layers for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param layers     [in] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(const OdInt32Array& indFaces, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets a layer for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param layer      [in] A layer object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef& layer) = 0;
  
  /** \details
    Sets layers for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param layer      [in] A layer object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(const OdInt32Array& indFaces, const OdTvLayerDef& layer) = 0;

  /** \details
    Sets layers for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param layers     [in] An array of layer objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers) = 0;
  
  /** \details
    Sets layers for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param layers     [in] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets layers for a range of shell faces.
    
    \param indStart [in] An index of the shell face array that represents the start position of the range.
    \param nCount   [in] A quantity of faces in the range from the start position.
    \param layer    [in] A layer object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer) = 0;

  /** \details
    Retrieves layer objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param layers     [out] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved layer objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves layer objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param layers     [out] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved layer objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getFaceLayersViaList(const OdInt32Array& indFaces, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves layer objects for a specified shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvLayerDef class that contains layer data.
    \remarks
    If the retrieved layer object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getFaceLayer(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face transparency management.
  */
  
  /** \details
    Sets transparency data for a list of shell faces.
    
    \param nCount       [in] A quantity of faces.
    \param indFaces     [in] An array of face indexes represented with a pointer to the first array element.
    \param transparencies [in] An array of transparency data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef* transparencies) = 0;
  
  /** \details
    Sets transparency data for a list of shell faces.
    
    \param indFaces       [in] An array of face indexes represented with a pointer to the first array element.
    \param transparencies [in] An array of transparency data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(const OdInt32Array& indFaces, const OdTvTransparencyDefArray& transparencies) = 0;
  
  /** \details
    Sets transparency data for a list of shell faces.
    
    \param nCount         [in] A quantity of faces.
    \param indFaces       [in] An array of face indexes represented with a pointer to the first array element.
    \param transparency   [in] A transparency data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef& transparency) = 0;
  
  /** \details
    Sets transparency data for a list of shell faces.
    
    \param indFaces       [in] An array of face indexes represented with a pointer to the first array element.
    \param transparency   [in] A transparency data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(const OdInt32Array& indFaces, const OdTvTransparencyDef& transparency) = 0;

  /** \details
    Sets transparency data for a range of shell faces.
    
    \param indStart       [in] An index of the shell face array that represents the start position of the range.
    \param nCount         [in] A quantity of faces in the range from the start position.
    \param transparencies [in] An array of transparency data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef* transparencies) = 0;
  
  /** \details
    Sets transparency data for a range of shell faces.
    
    \param indStart       [in] An index of the shell face array that represents the start position of the range.
    \param transparencies [in] An array of transparency data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, const OdTvTransparencyDefArray& transparencies) = 0;
  
  /** \details
    Sets transparency data for a range of shell faces.
    
    \param indStart     [in] An index of the shell face array that represents the start position of the range.
    \param nCount       [in] A quantity of faces in the range from the start position.
    \param transparency [in] A transparency data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified transparency data object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef& transparency) = 0;

  /** \details
    Retrieves transparency data for a range of shell faces.
    
    \param indStart       [in] An index of the shell face array that represents the start position of the range.
    \param nCount         [in] A quantity of faces in the range from the start position.
    \param transparencies [out] An array of transparency data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved transparency data objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, OdTvTransparencyDefArray& transparencies) const = 0;
  
  /** \details
    Retrieves transparency data for a list of shell faces.
    
    \param indFaces       [in] An array of face indexes.
    \param transparencies [out] An array of transparency data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved transparency data objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceTransparencyViaList(const OdInt32Array& indFaces, OdTvTransparencyDefArray& transparencies) const = 0;
  
  /** \details
    Retrieves transparency data for a specified face of the shell.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvTransparencyDef class that contains transparency data.
    \remarks
    If the retrieved transparency data object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvTransparencyDef getFaceTransparency(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face material management.
  */
  
  /** \details
    Sets material definition objects for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param materials  [in] An array of material definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials) = 0;
  
  /** \details
    Sets material definition objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param materials  [in] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDefArray& materials) = 0;
  
  /** \details
    Sets material definition objects for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param material   [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material) = 0;
  
  /** \details
    Sets material definition objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param material   [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDef& material) = 0;

  /** \details
    Sets material definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param materials  [in] An array of material definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials) = 0;
  
  /** \details
    Sets material definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param materials  [in] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, const OdTvMaterialDefArray& materials) = 0;
  
  /** \details
    Sets material definition object for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param material   [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material) = 0;

  /** \details
    Retrieves material definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param materials  [out] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved material definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials) const = 0;
  
  /** \details
    Retrieves material definition objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param materials  [out] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved material definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult getFaceMaterialsViaList(const OdInt32Array& indFaces, OdTvMaterialDefArray& materials) const = 0;
  
  /** \details
    Retrieves material definition objects for a specified shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvMaterialDef class that contains information about material.
    \remarks
    If the retrieved material definition object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face mapper management.
  */
  
  /** \details
    Sets mapping definition objects for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param mappers    [in] An array of mapper definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef* mappers) = 0;
  
  /** \details
    Sets mapper definition objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param mappers    [in] An array of mapper definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(const OdInt32Array& indFaces, const OdTvMapperDefArray& mappers) = 0;
  
  /** \details
    Sets a mapper definition for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param mapper     [in] A mapper definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef& mapper) = 0;
  
  /** \details
    Sets a mapper definition object for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param mapper     [in] A mapper definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(const OdInt32Array& indFaces, const OdTvMapperDef& mapper) = 0;

  /** \details
    Sets mapper definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param mappers    [in] An array of mapper definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef* mappers) = 0;
  
  /** \details
    Sets mapper definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param mappers    [in] An array of mapper definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, const OdTvMapperDefArray& mappers) = 0;
  
  /** \details
    Sets a mapper definition object for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param mapper     [in] A mapper definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef& mapper) = 0;

  /** \details
    Sets a mapper definition object for all shell faces.
    
    \param mapper   [in] A mapper definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapper definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMapper(const OdTvMapperDef& mapper) = 0;

  /** \details
    Retrieves mapper definition objects for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param mappers    [out] An array of mapper definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved mapper definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult getFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMapperDefArray& mappers) const = 0;
  
  /** \details
    Retrieves mapper definition objects for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param mappers    [out] An array of mapper definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved mapper definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult getFaceMappersViaList(const OdInt32Array& indFaces, OdTvMapperDefArray& mappers) const = 0;
  
  /** \details
    Retrieves a mapper definition object for a specified shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvMapperDef class that contains data about texture mapping to a specific 3D geometry.
    \remarks
    If the retrieved mapper definition object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvMapperDef getFaceMapper(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /**
  Face fill origin management.
  */
  
  /** \details
    Defines origin points of hatch pattern fills for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param origins    [in] An array of origin points represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvPoint2d* origins) = 0;

  /** \details
    Defines origin points of hatch pattern fills for a list of shell faces.
    
    \param indFaces [in] An array of face indexes.
    \param origins  [in] An array of origin points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaList(const OdInt32Array& indFaces, const OdTvPoint2dArray& origins) = 0;

  /** \details
    Defines an origin point of hatch pattern fills for a list of shell faces.
    
    \param nCount   [in] A quantity of faces.
    \param indFaces [in] An array of face indexes represented with a pointer to the first array element.
    \param origin   [in] An origin point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvPoint2d& origin) = 0;

  /** \details
    Defines an origin point of hatch pattern fills for a list of shell faces.
    
    \param indFaces [in] An array of face indexes.
    \param origin   [in] An origin point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaList(const OdInt32Array& indFaces, const OdTvPoint2d& origin) = 0;

  /** \details
    Defines origin points of hatch pattern fills for a range of shell faces.
    
    \param indStart [in] An index of the shell face array that represents the start position of the range.
    \param nCount   [in] A quantity of faces in the range from the start position.
    \param origins  [in] An array of origin points represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* origins) = 0;
  
  /** \details
    Defines origin points of hatch pattern fills for a range of shell faces.
    
    \param indStart [in] An index of the shell face array that represents the start position of the range.
    \param origins  [in] An array of origin points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin points are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaRange(OdInt32 indStart, const OdTvPoint2dArray& origins) = 0;
  
  /** \details
    Defines an origin point of hatch pattern fills for a range of shell faces.
    
    \param indStart [in] An index of the shell face array that represents the start position of the range.
    \param nCount   [in] A quantity of faces in the range from the start position.
    \param origin   [in] An origin point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOriginsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& origin) = 0;

  /** \details
    Defines an origin point of hatch pattern fills for all faces.
    
    \param origin [in] An origin point.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified origin point is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillOrigin(const OdTvPoint2d& origin) = 0;

  /** \details
    Retrieves origin points for a range of shell faces.
    
    \param indStart [in] An index of the shell face array that represents the start position of the range.
    \param nCount   [in] A quantity of faces in the range from the start position.
    \param origins  [out] An array of origin points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved origin points are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult getFaceFillOriginsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& origins) const = 0;
  
  /** \details
    Retrieves origin points for a list of shell faces.
    
    \param indexes [in] An array of face indexes.
    \param origins [out] An array of origin points.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved origin points are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult getFaceFillOriginsViaList(const OdInt32Array& indexes, OdTvPoint2dArray& origins) const = 0;
  
  /** \details
    Retrieves an origin point for a specified shell face.
    
    \param ind [in] A shell face index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint2d class that represents a point in two-dimensional space.
    \remarks
    If the retrieved origin point is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvPoint2d getFaceFillOrigin(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Defines vectors of hatch pattern fills for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param directions [in] An array of two-dimensional vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vectors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector2d* directions) = 0;
  
  /** \details
    Defines vectors of hatch pattern fills for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param directions [in] An array of two-dimensional vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vectors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaList(const OdInt32Array& indFaces, const OdTvVector2dArray& directions) = 0;
  
  /** \details
    Defines a vector of hatch pattern fills for a list of shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param direction  [in] A two-dimensional vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector2d& direction) = 0;
  
  /** \details
    Defines a vector of hatch pattern fills for a list of shell faces.
    
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param direction  [in] A two-dimensional vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaList(const OdInt32Array& indFaces, const OdTvVector2d& direction) = 0;

  /** \details
    Defines vectors of hatch pattern fills for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param directions [in] An array of two-dimensional vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vectors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector2d* directions) = 0;
  
  /** \details
    Defines vectors of hatch pattern fills for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param directions [in] An array of two-dimensional vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vectors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaRange(OdInt32 indStart, const OdTvVector2dArray& directions) = 0;
  
  /** \details
    Defines a vector of hatch pattern fills for a range of shell faces.
    
    \param indStart  [in] An index of the shell face array that represents the start position of the range.
    \param nCount    [in] A quantity of faces in the range from the start position.
    \param direction [in] A two-dimensional vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vector is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirectionsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector2d& direction) = 0;

  /** \details
    Defines a vector of hatch pattern fills for all shell faces.
    
    \param direction [in] A two-dimensional vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified vectors are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setFaceFillDirection(const OdTvVector2d& direction) = 0;

  /** \details
    Retrieves fill vectors for a range of shell faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param directions [out] An array of two-dimensional vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved vectors are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult getFaceFillDirectionsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVector2dArray& directions) const = 0;
  
  /** \details
    Retrieves fill vectors for a list of shell faces.
    
    \param indexes    [in]  An array of face indexes.
    \param directions [out] An array of two-dimensional vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved vectors are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult getFaceFillDirectionsViaList(const OdInt32Array& indexes, OdTvVector2dArray& directions) const = 0;
  
  /** \details
    Retrieves a fill vector for a specified shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector2d class that represents a vector in two-dimensional space.
    \remarks
    If the retrieved vector is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvVector2d getFaceFillDirection(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets color data for a list of shell edges.
    
    \param nCount     [in] A quantity of edges.
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param colors     [in] An array of color definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef* colors) = 0;
  
  /** \details
    Sets color data for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param colors     [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(const OdInt32Array& indEdges, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets color data for a list of shell edges.
    
    \param nCount     [in] A quantity of edges.
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets color data for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(const OdInt32Array& indEdges, const OdTvColorDef& color) = 0;

  /** \details
    Sets color data for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets color data for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param colors     [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition objects are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets color data for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param colors     [in] An array of color definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color definition object is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors) = 0;

  /** \details
    Retrieves color data for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes.
    \param colors     [out] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved color definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getEdgeColorsViaList(const OdInt32Array& indEdges, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves color data for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param colors     [out] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved color definition objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves color data object for a specified shell edge.
    
    \param ind  [in] A shell edge index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvColorDef class that contains color definition information.
    \remarks
    If the retrieved color definition object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getEdgeColor(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;


  /** \details
    Sets visibility data for a list of shell edges.
    
    \param nCount         [in] A quantity of edges.
    \param indEdges       [in] An array of edge indexes represented with a pointer to the first array element.
    \param visibilities   [in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities) = 0;
  
  /** \details
    Sets visibility data for a list of shell edges.
    
    \param indEdges       [in] An array of edge indexes represented with a pointer to the first array element.
    \param visibilities   [in] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets visibility data for a list of shell edges.
    
    \param nCount       [in] A quantity of edges.
    \param indEdges     [in] An array of edge indexes represented with a pointer to the first array element.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility) = 0;
  
  /** \details
    Sets visibility data for a list of shell edges.
    
    \param indEdges     [in] An array of edge indexes.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets visibility data for a range of shell edges.
    
    \param indStart     [in] An index of the shell edge array that represents the start position of the range.
    \param nCount       [in] A quantity of edges in the range from the start position.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility) = 0;
  
  /** \details
    Sets visibility data for a range of shell edges.
    
    \param indStart      [in] An index of the shell edge array that represents the start position of the range.
    \param visibilities  [in] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets visibility data for a range of shell edges.
    
    \param indStart     [in] An index of the shell edge array that represents the start position of the range.
    \param nCount       [in] A quantity of edges in the range from the start position.
    \param visibilities [in] An array of visibility data objects represented with a pointer to the first array element..
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities) = 0;

  /** \details
    Retrieves visibility data for a list of shell edges.
    
    \param indEdges     [in] An array of edge indexes.
    \param visibilities [out] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved visibility data objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indEdges, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves visibility data for a range of shell edges.
    
    \param indStart     [in] An index of the shell edge array that represents the start position of the range.
    \param nCount       [in] A quantity of edges in the range from the start position.
    \param visibilities [out] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved visibility data objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves visibility data object for a specified shell edge.
    \param ind  [in] A shell edge index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVisibilityDef class that contains information about object visibility.
    \remarks
    If the retrieved visibility data object is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;

  
  /** \details
    Sets the linetypes for a list of shell edges.
    
    \param nCount     [in] A quantity of edges.
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param linetypes  [in] An array of linetype objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified linetypes are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef* linetypes) = 0;
  
  /** \details
    Sets the linetypes for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param linetypes  [in] An array of linetype objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified linetypes are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(const OdInt32Array& indEdges, const OdTvLinetypeDefArray& linetypes) = 0;
  
  /** \details
    Sets the linetype for a list of shell edges.
    
    \param nCount     [in] A quantity of edges.
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param linetype   [in] A linetype object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified linetype is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef& linetype) = 0;
  
  /** \details
    Sets the linetype for a list of shell edges.
    
    \param indEdges [in] An array of edge indexes represented with a pointer to the first array element.
    \param linetype [in] A linetype object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified linetypes are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(const OdInt32Array& indEdges, const OdTvLinetypeDef& linetype) = 0;

  /** \details
    Sets the linetype for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param linetype   [in] A linetype object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the linetype is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef& linetype) = 0;
  
  /** \details
    Sets the linetypes for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param linetypes  [in] An array of linetype objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the linetypes are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, const OdTvLinetypeDefArray& linetypes) = 0;
  
  /** \details
    Sets the linetypes for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param linetypes  [in] An array of linetype objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the linetypes are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef* linetypes) = 0;

  /** \details
    Retrieves linetypes for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes.
    \param linetypes  [out] An array of linetype objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved linetype objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult getEdgeLinetypesViaList(const OdInt32Array& indEdges, OdTvLinetypeDefArray& linetypes) const = 0;
  
  /** \details
    Retrieves linetypes for a range of shell edges.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param linetypes  [out] An array of linetype objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved linetype objects are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult getEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLinetypeDefArray& linetypes) const = 0;
  
  /** \details
    Retrieves a linetype for a specified shell edge.
    
    \param ind  [in] A shell edge index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvLinetypeDef class that contains the linetype definition data.
    \remarks
    If the retrieved linetype is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeDef getEdgeLinetype(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;


  /** \details
    Sets layers for a list of shell edges.
    
    \param nCount     [in] A quantity of edges.
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param layers     [in] An array of layer objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layers are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef* layers) = 0;
  
  /** \details
    Sets layers for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes.
    \param layers     [in] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layers are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(const OdInt32Array& indEdges, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets a layer for a list of shell edges.
    
    \param nCount     [in] A quantity of edges.
    \param indEdges   [in] An array of edge indexes represented with a pointer to the first array element.
    \param layer      [in] A layer object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef& layer) = 0;
  
  /** \details
    Sets a layer for a list of shell edges.
    
    \param indEdges   [in] An array of edge indexes.
    \param layer      [in] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layers are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(const OdInt32Array& indEdges, const OdTvLayerDef& layer) = 0;

  /** \details
    Sets a layer for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param layer      [in] A layer object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layer is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer) = 0;
  
  /** \details
    Sets layers for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param layers     [in] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layers are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets layers for a range of shell edges.
    
    \param indStart   [in] An index of the shell edge array that represents the start position of the range.
    \param nCount     [in] A quantity of edges in the range from the start position.
    \param layers     [in] An array of layer objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified layers are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers) = 0;

  /** \details
    Retrieves layer objects for a list of shell edges.
    
    \param indEdges   [in] An array of face indexes.
    \param layers     [out] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved layers are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getEdgeLayersViaList(const OdInt32Array& indEdges, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves layer objects for a range of shell edges.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param layers     [out] An array of layer objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved layers are successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves a layer object for a specified shell edge.
    
    \param ind  [in] A shell edge index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvLayerDef class that contains layer data.
    \remarks
    If the retrieved layer is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getEdgeLayer(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a hatch pattern for the shell object.
    
    \param def   [in] An instance of OdTvHatchPatternDef that represents a definition for a hatch pattern.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the hatch pattern is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setHatchPattern(const OdTvHatchPatternDef& def) = 0;
  
  /** \details
    Retrieves a hatch pattern object for the shell object.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvHatchPatternDef class that represents a definition for a hatch pattern.
    \remarks
    If the hatch pattern is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvHatchPatternDef getHatchPattern(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that the shell should be filled in 2D rendering mode or visual styles
    
    \param bNeedFill  [in] Flag which indicates that it is need to fill shell in the 2D rendering modes or visual styles
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the 2D filling flag is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setNeedFillIn2D(bool bNeedFill) = 0;

  /** \details
    Retrieves a hatch pattern object for the shell object.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if shell should be filled in 2D rendering modes or visual styles
    \remarks
    If the 2D filling flag is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getNeedFillIn2D(OdTvResult* rc = NULL) const = 0;

  /** \details
    Marks edges as 'silhouette' edges.
    
    \param indEdges   [in] An array of edge's indexes which should be marked as 'silhouettes'.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the edges is successfully marked, the method returns tvOk; otherwise it returns an appropriate error code.
    'Silhouettes' edges processed in a special way in some cases. Such edges used mostly for compatibility with some 
    ODA-based databases.
  */
  virtual OdTvResult setIndexesOfSilhouetteEdges(const OdInt32Array& indEdges) = 0;

  /** \details
    Retrieves indexes of the edges which are marked as 'silhouettes'
    
    \param indEdges   [out] An array of edges indexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved array is successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getIndexesOfSilhouetteEdges(OdInt32Array& indEdges) const = 0;

  /** \details
    Sets that it is need to show shell vertices for the shell object.
    
    \param bShow         [in] Flag which indicates that it is need to show shell vertices.
    \param verticesSize  [in] A vertices size which will be used for the vertices visualization.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If vertices visibility is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShowVertices(bool bShow, OdInt32 verticesSize = 5) = 0;

  /** \details
    Returns true if shell vertices are visible. Also returns a vertices size which is used for the vertices visualization.
    
    \param verticesSize  [out] A vertices size which will be used for the vertices visualization.
    \param rc            [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if shell vertices are visible, false otherwise.
    \remarks
    If the vertices visibility is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getShowVertices(OdInt32& verticesSize, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that only shell vertices should be visualized for this shell object.
    
    \param bShowOnly         [in] Flag which indicates that only shell vertices should be visualized.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If flag is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    This method will have no effect if the show vertices flag is set to false.
  */
  virtual OdTvResult setShowOnlyVertices(bool bShowOnly) = 0;

  /** \details
    Returns true if only shell vertices should be visualized for this shell object.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if only shell vertices should be visualized, false otherwise.
    \remarks
    If the show only flag was successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getShowOnlyVertices(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets overriding of the vertices color. If bOverride flag is true, color will be applied to the shell vertices. Otherwise, color from attributes will be applied.
    
    \param bOverride   [in] Flag if need apply shell vertices color.
    \param color       [in] Color of vertices.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified override vertices color flag and color are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    This method will have no effect if the show vertices flag is set to false.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setOverrideVerticesColor(bool bOverride, const OdTvRGBColorDef& color) = 0;

  /** \details
    Get vertices color and override vertices color flag.
    
    \param bOverride   [out] Override vertices color flag.
    \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns vertices color.
    \remarks
    If the retrieved color and flag are successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvRGBColorDef getOverrideVerticesColor(bool& bOverride, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that it is need to show shell normals for the shell object.
    
    \param bShow         [in] Flag which indicates that it is need to show shell normals.
    \param normalsLength [in] A lines length which will be used for the normals visualization.
    \param normalsColor  [in] A lines color which will be used for the normals visualization. If this parameter is default, color will be taken from shell color.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normalsLength is 0., the lines length will be calculated automatically on the basis of the shell extents' size
    If the normalsColor is 'default', the lines color will be the same as the color of normal's source (face or vertex)
    If normals visibility is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShowNormals(bool bShow, double normalsLength = 0., const OdTvRGBColorDef& normalsColor = OdTvRGBColorDef()) = 0;

  /** \details
    Returns true if shell normals are visible. Also returns a normals size and color which is used for the normals visualization.
    
    \param normalsLength  [out] A normal length which is used for the normals visualization.
    \param normalsColor   [out] A lines color which is used for the normals visualization.
    \param rc             [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if shell normals are visible, false otherwise.
    \remarks
    If the normals visibility is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getShowNormals(double& normalsLength, OdTvRGBColorDef& normalsColor, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that it is need to show shell sharp edges for the shell object.
    
    \param bShow         [in] Flag which indicates that it is need to show shell sharp edges.
    \param edgesWidth    [in] A lines lineweight which will be used for the sharp edges visualization.
    \param edgesColor    [in] A lines color which will be used for the sharp edges visualization.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the edgesColor is 'default', the lines color will be taken from shell color
    If sharp edges visibility is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShowSharpEdges(bool bShow, OdUInt8 edgesWidth = 5, const OdTvRGBColorDef& edgesColor = OdTvRGBColorDef()) = 0;

  /** \details
    Returns true if shell sharp edges are visible.
    
    \param rc            [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \param edgesWidth    [out] A lineweight which is used for the sharp edges visualization.
    \param edgesColor    [out] A lines color which is used for the sharp edges visualization.
    \returns Returns true if shell sharp edges are visible, false otherwise.
    \remarks
    If the sharp edges visibility is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getShowSharpEdges(OdUInt8& edgesWidth, OdTvRGBColorDef& edgesColor, OdTvResult* rc = NULL) const = 0;

  /** \details
    Specifies whether to use spatial tree for selection.
    
    \param bUseSpatialTreeForSelection [in] A flag that determines whether to use spatial tree for selection.
    \param nVerticesLimit              [in] A value that determines the minimum count of vertices for which to use a spatial tree. Valid only if 'bUseSpatialTreeForSelection' is set to true. Should be greater than or equal to 1000.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If flag is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection, OdUInt32 nVerticesLimit = 50000) = 0;

  /** \details
    Checks whether spatial tree is used for selection. This method also receives the minimum count of vertices for which to use a spatial tree if spatial tree is used.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns 0 spatial tree should not be used; otherwise returns the minimum count of vertices for which to use a spatial tree.
    \remarks
    If the rc parameter is not null and the result is returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getUseSpatialTreeForSelection(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the shell geometry type and is used for storing and passing references to the shell object.
*/
typedef OdTvSmartPtr<OdTvShellData> OdTvShellDataPtr;

#endif // _ODTV_ENTITYGEOMETRYSHELL_H_INCLUDED_


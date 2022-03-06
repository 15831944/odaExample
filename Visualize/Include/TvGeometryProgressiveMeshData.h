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

#ifndef _ODTV_ENTITYGEOMETRYPROGRESSIVEMESH_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRYPROGRESSIVEMESH_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"

/** \details
  This is an interface class for an OdTvProgressiveMesh custom interpolator.
  \sa
  <link tv_geometry_progressive_mesh, Work with Progressive Mesh>
*/
class OdTvCustomInterpolation
{
public:
  /** \details
    Calculates function value f( x ) with conditions: f( minX ) = minY, f( maxX ) = maxY.
    
    \param minX [in] Minimum x value.
    \param minY [in] Y value corresponding to the minimum x value.
    \param maxX [in] Maximum x value.
    \param maxY [in] Y value corresponding to the maximum x value.
    \param x [in] X value for obtaining f( x ).
    \returns Returns Y value corresponding to the x value: y = f( x ).
  */
  virtual OdUInt32 interpolate( OdUInt32 minX, OdUInt32 minY, OdUInt32 maxX, OdUInt32 maxY, OdUInt32 x ) const = 0;
};

/** \details
  This is an interface class for an OdTvProgressiveMeshData object.
  \sa
  <link tv_geometry_progressive_mesh, Work with Progressive Mesh>
*/ 
class OdTvProgressiveMeshData : public OdTvIObject
{
public:
  /** \details
    Enumerates automatic level of details selection type.
  */
  enum LODAutoSelectType
  {
    kAutoLOD_None,                  //No auto select
    kAutoLOD_SqrInterpolation,      //Square interpolation
    kAutoLOD_SqrtInterpolation,     //Square root interpolation
    kAutoLOD_CustomInterpolation    //Custom interpolation using OdTvCustomInterpolation
  };
  /** \details
    Gets the geometry data of progressive mesh on current LOD if progressive mesh was generated. Otherwise gets the geometry data of initial shell.
    
    \param verticesArray  [out] A placeholder for the array of shell vertexes.
    \param faces          [out] A placeholder for the array of shell faces.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the parameter values were successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdTvPointArray& verticesArray, OdInt32Array& faces) const = 0;

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
    Sets normal vectors for a list of initial shell vertexes.
    
    \param indVertices [in] An array of vertex indexes.
    \param vectors     [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVectorArray& vectors) = 0;

  /** \details
    Sets normal vectors for a list of initial shell vertexes.
    
    \param nCount      [in] A quantity of vertexes in the list.
    \param indVertices [in] An array of vertex indexes represented with a pointer to the first array element.
    \param vector      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector) = 0;

  /** \details
    Sets normal vectors for a list of initial shell vertexes.
    
    \param indVertices [in] An array of vertex indexes.
    \param vector      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVector& vector) = 0;

  /** \details
    Sets normal vectors for a range of initial shell vertexes.
    
    \param indStart [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount   [in] A quantity of vertexes in the range from the start position.
    \param vector   [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector) = 0;

  /** \details
    Sets normal vectors for a range of initial shell vertexes.
    
    \param indStart     [in] An index of the shell vertex array that represents the start position of the range.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors) = 0;

  /** \details
    Sets normal vectors for a range of initial shell vertexes.
    
    \param indStart [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount   [in] A quantity of vertexes in the range from the start position.
    \param vectors  [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors) = 0;

  /** \details
    Retrieves normal vectors for a range of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves normal vectors for a range of initial shell data.
    
    \param indStart     [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors were successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const = 0;

  /** \details
    Retrieves normal vectors for a list of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves normal vectors for a list of initial shell data.
    
    \param indVertices [in] An array of vertex indexes.
    \param vectors     [out] A placeholder for the array of normal vectors to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors were successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexNormalsViaList(const OdInt32Array& indVertices, OdTvVectorArray& vectors) const = 0;

  /** \details
    Retrieves the normal vector for a specified progressive mesh vertex on current LOD if progressive mesh was generated. Otherwise retrieves the normal vector for a specified initial shell vertex.
    
    \param ind      [in] A shell vertex index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the <link OdTvVector, OdTvVector> class that contains normal vector information.
    \remarks
    If the rc parameter is not null and the normal vector object was returned successfully, the rc parameter accepts the tvOk value for progressive mesh data and tvWarning for initial shell data; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets colors for a list of initial shell vertexes.
    
    \param nCount       [in] A quantity of vertexes for setting the color.
    \param indVertices  [in] A pointer to an array of vertex indexes.
    \param colors       [in] A pointer to an array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified shell vertexes were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors) = 0;

  /** \details
    Sets colors for a list of initial shell vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param colors       [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified shell vertexes were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDefArray& colors) = 0;

  /** \details
    Sets a color for a list of initial shell vertexes.
    
    \param nCount       [in] A quantity of vertexes for setting the color.
    \param indVertices  [in] A pointer to an array of vertex indexes.
    \param color        [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified shell vertexes was successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color) = 0;

  /** \details
    Sets a color for a list of initial shell vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param color        [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified initial shell vertexes was successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDef& color) = 0;

  /** \details
    Sets a color for a range of initial shell vertexes.
    
    \param indStart [in] A starting index of the vertex to be set with color.
    \param nCount   [in] A quantity of vertexes to be set with color.
    \param color    [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified initial shell vertexes was successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color) = 0;

  /** \details
    Sets a color for a range of initial shell vertexes.
    
    \param indStart [in] A starting index of the vertex to be set with color.
    \param colors   [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified initial shell vertexes were successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, const OdTvRGBColorDefArray& colors) = 0;

  /** \details
    Sets a color for a range of initial shell vertexes.
    
    \param indStart [in] A starting index of the vertex to be set with color.
    \param nCount   [in] A quantity of vertexes to be set with color.
    \param colors   [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified initial shell vertexes was successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors) = 0;

  /** \details
    Retrieves colors for a range of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves colors for a range of initial shell data.
    
    \param indStart [in] A starting index of the range.
    \param nCount   [in] A quantity of vertexes in the range.
    \param colors   [out] A placeholder for an array of color definitions to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified shell vertexes were successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const = 0;

  /** \details
    Retrieves colors for a list of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves colors for a list of of initial shell data.
    
    \param indVertices [in] An array of shell vertex indexes.
    \param colors      [out] A placeholder for an array of color definitions to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified shell vertexes were successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getVertexColorsViaList(const OdInt32Array& indVertices, OdTvRGBColorDefArray& colors) const = 0;

  /** \details
    Retrieves the color for a specified progressive mesh vertex on current LOD if progressive mesh was generated. Otherwise retrieves the color for a specified initial shell vertex.
    
    \param ind [in] A shell vertex index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvRGBColorDef, OdTvRGBColorDef> class that represents the color information.
    \remarks
    If the rc parameter is not null and the color data was returned successfully, the rc parameter accepts the tvOk value for progressive mesh data and tvWarning for initial shell data; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets mapping coordinates for a list of initial shell vertices.
    
    \param nCount        [in] A quantity of vertices.
    \param indVertices   [in] An array of vertex indexes represented with a pointer to the first array element.
    \param mappingCoords [in] An array of UV mapping coordinates represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a list of initial shell vertices.
    
    \param indVertices   [in] An array of vertex indexes.
    \param mappingCoords [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2dArray& mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a list of initial shell vertices.
    
    \param nCount       [in] A quantity of vertices.
    \param indVertices  [in] An array of vertex indexes represented with a pointer to the first array element.
    \param mappingCoord [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord) = 0;
  
  /** \details
    Sets mapping coordinates for a list of initial shell vertices.
    
    \param indVertices  [in] An array of vertex indexes.
    \param mappingCoord [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2d& mappingCoord) = 0;

  /** \details
    Sets mapping coordinates for a range of initial shell vertexes.
    
    \param indStart       [in] An index of the initial shell vertex array that represents the start position of the range.
    \param nCount         [in] A quantity of vertexes in the range from the start position.
    \param mappingCoords  [in] An array of UV mapping coordinates represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange( OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords ) = 0;

  /** \details
    Sets mapping coordinates for a range of initial shell vertexes.
    
    \param indStart       [in] An index of the initial shell vertex array that represents the start position of the range.
    \param mappingCoords  [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, const OdTvPoint2dArray& mappingCoords) = 0;
  
  /** \details
    Sets mapping coordinates for a range of initial shell vertexes.
    
    \param indStart     [in] An index of the initial shell vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param mappingCoord [in] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mapping coordinates are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord) = 0;

  /** \details
    Retrieves mapping coordinates for a range of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves mapping coordinates for a range of initial shell data.
    
    \param indStart       [in] An index of the shell vertex array that represents the start position of the range.
    \param nCount         [in] A quantity of vertexes in the range from the start position.
    \param mappingCoords  [out] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved mapping coordinates are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const = 0;

  /** \details
    Retrieves mapping coordinates for a list of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves mapping coordinates for a list of initial shell data.
    
    \param indVert        [in] An array of indexes of the shell vertexes.
    \param mappingCoords  [out] An array of UV mapping coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved mapping coordinates are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indVert, OdTvPoint2dArray& mappingCoords) const = 0;

  /** \details
    Retrieves mapping coordinates for a specified progressive mesh vertex on current LOD if progressive mesh was generated. Otherwise retrieves mapping coordinates for a specified initial shell vertex.
    
    \param ind    [in] A shell vertex index.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the <link OdTvVector, OdTvVector> class that contains normal vector information.
    \remarks
    If the retrieved mapping coordinates are successfully returned, the rc parameter is set to tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets colors for a list of initial shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param colors     [in] An array of color definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors) = 0;

  /** \details
    Sets colors for a list of initial shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param colors     [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDefArray& colors) = 0;

  /** \details
    Sets colors for a list of initial shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color) = 0;

  /** \details
    Sets a color for a list of initial shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDef& color) = 0;

  /** \details
    Sets a color for a range of initial shell faces.
    
    \param indStart   [in] An index of the initial shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param color      [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color) = 0;

  /** \details
    Sets colors for a range of initial shell faces.
    
    \param indStart   [in] An index of the initial shell face array that represents the start position of the range.
    \param colors     [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified colors are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors) = 0;

  /** \details
    Sets a color for a range of initial shell faces.
    
    \param indStart   [in] An index of the initial shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param colors     [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified color is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors) = 0;

  /** \details
    Retrieves color definition objects for a range of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves color definition objects for a range of initial shell data.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param colors     [out] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved color definition objects are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const = 0;

  /** \details
    Retrieves color definition objects for a list of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves color definition objects for a list of initial shell data.
    
    \param indFaces   [in] An array of face indexes.
    \param colors     [out] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved color definition objects are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getFaceColorsViaList(const OdInt32Array& indFaces, OdTvColorDefArray& colors) const = 0;

  /** \details
    Retrieves a color definition object for a specified face of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves a color definition object for a specified face of initial shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvColorDef class that contains color definition information.
    \remarks
    If the retrieved color definition object is successfully returned, the rc parameter is set to tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets material definition objects for a list of initial shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param materials  [in] An array of material definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials) = 0;

  /** \details
    Sets material definition objects for a list of initial shell faces.
    
    \param indFaces   [in] An array of face indexes.
    \param materials  [in] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDefArray& materials) = 0;

  /** \details
    Sets material definition objects for a list of initial shell faces.
    
    \param nCount     [in] A quantity of faces.
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param material   [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition object is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material) = 0;

  /** \details
    Sets material definition objects for a list of initial shell faces.
    
    \param indFaces   [in] An array of face indexes represented with a pointer to the first array element.
    \param material   [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition object is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDef& material) = 0;

  /** \details
    Sets material definition objects for a range of initial shell faces.
    
    \param indStart   [in] An index of the initial shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param materials  [in] An array of material definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials) = 0;

  /** \details
    Sets material definition objects for a range of initial shell faces.
    
    \param indStart   [in] An index of the initial shell face array that represents the start position of the range.
    \param materials  [in] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition objects are successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, const OdTvMaterialDefArray& materials) = 0;

  /** \details
    Sets material definition object for a range of initial shell faces.
    
    \param indStart   [in] An index of the initial shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param material   [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified material definition object is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material) = 0;

  /** \details
    Retrieves material definition objects for a range of progressive mesh faces on current LOD if progressive mesh was generated. Otherwise retrieves material definition objects for a range of initial shell data faces.
    
    \param indStart   [in] An index of the shell face array that represents the start position of the range.
    \param nCount     [in] A quantity of faces in the range from the start position.
    \param materials  [out] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved material definition objects are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials) const = 0;

  /** \details
    Retrieves material definition objects for a list of progressive mesh faces on current LOD if progressive mesh was generated. Otherwise retrieves material definition objects for a list of initial shell data faces.
    
    \param indFaces   [in] An array of face indexes.
    \param materials  [out] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved material definition objects are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult getFaceMaterialsViaList(const OdInt32Array& indFaces, OdTvMaterialDefArray& materials) const = 0;

  /** \details
    Retrieves material definition objects for a specified face of progressive mesh on current LOD if progressive mesh was generated. Otherwise retrieves material definition objects for a specified face of initial shell face.
    
    \param ind  [in] A shell face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvMaterialDef class that contains information about material.
    \remarks
    If the retrieved material definition object is successfully returned, the rc parameter is set to tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it holds an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets visibility data for a list of initial shell edges.
    
    \param nCount       [in] A quantity of edges.
    \param indEdges     [in] An array of edge indexes represented with a pointer to the first array element.
    \param visibilities [in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities) = 0;

  /** \details
    Sets visibility data for a list of initial shell edges.
    
    \param indEdges       [in] An array of edge indexes represented with a pointer to the first array element.
    \param visibilities   [in] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDefArray& visibilities) = 0;

  /** \details
    Sets visibility data for a list of initial shell edges.
    
    \param nCount       [in] A quantity of edges.
    \param indEdges     [in] An array of edge indexes represented with a pointer to the first array element.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets visibility data for a list of initial shell edges.
  
    \param indEdges     [in] An array of edge indexes.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets visibility data for a range of initial shell edges.
    
    \param indStart     [in] An index of the initial shell edge array that represents the start position of the range.
    \param nCount       [in] A quantity of edges in the range from the start position.
    \param visibility   [in] A visibility data object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets visibility data for a range of initial shell edges.
    
    \param indStart      [in] An index of the initial shell edge array that represents the start position of the range.
    \param visibilities  [in] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities) = 0;

  /** \details
    Sets visibility data for a range of initial shell edges.
    
    \param indStart     [in] An index of the initial shell edge array that represents the start position of the range.
    \param nCount       [in] A quantity of edges in the range from the start position.
    \param visibilities [in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified visibility data is successfully set, the method returns tvOk; if progressive mesh is already generated it returns tvWarning; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities) = 0;

  /** \details
    Retrieves visibility data for a list of progressive mesh edges on current LOD if progressive mesh was generated. Otherwise retrieves visibility data for a list of initial shell data edges.
    
    \param indEdges     [in] An array of edge indexes.
    \param visibilities [out] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved visibility data objects are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indEdges, OdTvVisibilityDefArray& visibilities) const = 0;

  /** \details
    Retrieves visibility data for a range of progressive mesh edges on current LOD if progressive mesh was generated. 
    Otherwise retrieves visibility data for a range of initial shell data edges.
    
    \param indStart     [in] An index of the shell edge array that represents the start position of the range.
    \param nCount       [in] A quantity of edges in the range from the start position.
    \param visibilities [out] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved visibility data objects are successfully returned, the method returns tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const = 0;

  /** \details
    Retrieves visibility data object for a specified edge of progressive mesh on current LOD if progressive mesh was generated. 
    Otherwise retrieves visibility data object for a specified edge of initial shell edge.
    
    \param ind  [in] A shell edge index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVisibilityDef class that contains information about object visibility.
    \remarks
    If the retrieved visibility data object is successfully returned, the rc parameter is set to tvOk for progressive mesh data and tvWarning for initial shell data; otherwise it holds an appropriate error code.
  */
  virtual OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Builds progressive mesh.
    
    \param nMinPoints   [in] Required vertex number in resulting simplified mesh.
    \param nMinFaces    [in] Required faces number in resulting simplified mesh.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If both input parameters are zero, initial shell will be simplified until it is possible.
    If the initial shell is not completely appropriate for progressive mesh generation and the instance of OdTvProgressiveMeshReactor is specified, generation will be aborted if 
    OdTvProgressiveMeshGenerator::onInitialShellProcessingWarning() returns false. If reactor is not specified mesh will be generated regardless of the warnings.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult buildProgressiveMesh( OdUInt32 nMinPoints = 0, OdUInt32 nMinFaces = 0 ) = 0;
  
  /** \details
    Retrieves a number of level of details.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdUInt32 numLODs( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves a current level of details.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdUInt32 currentLOD( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Switch progressive mesh to the specified level of detail
    
    \param lod  [in] Required level of detail
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult setLOD( OdUInt32 lod ) = 0;
  
  /** \details
    Retrieves a number of faces on current level of details.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdUInt32 numFaces( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves a number of vertices on current level of details.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdUInt32 numVertices( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Returns true if and only if progressive mesh should ignore face normals while draw.
    
    \remarks
    Progressive mesh always have face normals, even if no normals were specified.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual bool getIgnoreFaceNormals( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies should progressive mesh ignore face normals while draw.
    
    \remarks
    Progressive mesh always have face normals, even if no normals were specified.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult setIgnoreFaceNormals( bool bIgnore ) = 0;
  
  /** \details
    Checks whether the progressive mesh is successfully build from input data. 
    
    \returns
    true if the the progressive mesh is successfully build from input data, false otherwise.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual bool isProgressiveMeshGenerated( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies how progressive mesh automatically selects level of details while drawn.
    
    \param autoSelectType [in] Level of details automatic select type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult setAutoLODSelection( LODAutoSelectType autoSelectType ) = 0;
  
  /** \details
    Returns Level of details automatic select type.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual LODAutoSelectType getAutoLODSelection( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Returns Level of details automatic select interpolation thresholds.
    
    \param nMin   [out] Minimum interpolation threshold.
    \param nMax   [out] Maximum interpolation threshold.
    \returns A value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult getAutoLODSelectInterpolationThresholds( OdUInt32& nMin, OdUInt32& nMax ) const = 0;
  
  /** \details
    Specifies Level of details automatic select interpolation thresholds.
    \param nMin   [in] Minimum interpolation threshold.
    \param nMax   [in] Maximum interpolation threshold.
    \returns A value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult setAutoLODSelectInterpolationThresholds( OdUInt32 nMin, OdUInt32 nMax ) = 0;
  
  /** \details
    Specifies interpolation callback for kAutoLOD_CustomInterpolation.
    
    \param pInterpolation [in] Pointer to the instance of OdTvCustomInterpolation.
    \returns A value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    Since custom interpolator instance cannot be saved while OdTvProgressiveMeshData with specified OdTvCustomInterpolation is being saved,
    OdTvCustomInterpolation::interpolate will be called for each value in interval [ getAutoLODSelectMinInterpolationThreshold(); getAutoLODSelectMaxInterpolationThreshold() ].
    After the read operation the array-based interpolation will be used until new instance of OdTvCustomInterpolation is specified via the setAutoLODCustomInterpolation() method.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvResult setAutoLODCustomInterpolation( OdTvCustomInterpolation* pInterpolation ) = 0;
  
  /** \details
    Returns interpolation callback for kAutoLOD_CustomInterpolation.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Pointer to the instance of OdTvCustomInterpolation.
    \sa
    <link tv_geometry_progressive_mesh, Use Progressive Meshes in Visualize SDK>
  */
  virtual OdTvCustomInterpolation* getAutoLODCustomInterpolation( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether progressive mesh is in partial mode or not.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if and only if progressive mesh is in partial mode; otherwise returns false.
    \remarks If progressive mesh is not generated, return code will be tvWarning.
  */
  virtual bool isInPartialMode( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Loads all unloaded progressive mesh data and ends partial mode.
    
    \returns A value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks If progressive mesh is not generated or is not in partial mode, result will be tvWarning.
  */
  virtual OdTvResult endPartialMode() = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the progressive mesh geometry type and is used for storing and passing references to the progressive mesh object.
*/
typedef OdTvSmartPtr<OdTvProgressiveMeshData> OdTvProgressiveMeshDataPtr;

#endif // _ODTV_ENTITYGEOMETRYPROGRESSIVEMESH_H_INCLUDED_


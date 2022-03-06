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

#ifndef _ODTV_ENTITYGEOMETRYMESH_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRYMESH_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "Int32Array.h"
#include "UInt32Array.h"
#include "UInt8Array.h"
#include "DoubleArray.h"
#include "TvTraitsDef.h"

/** \details
  Structure for storing vertex positions of the mesh.
*/
class OdTvVertexPos
{
public:
  /** \details
    Creates a new vertex position object with default parameters.
  */
  OdTvVertexPos() : m_row(0), m_column(0) {}
  
  /** \details
    Creates a new vertex position object with specified parameters.
    
    \param row    [in] A mesh row count.
    \param column [in] A mesh column count.
  */
  OdTvVertexPos(OdUInt32 row, OdUInt32 column) : m_row(row), m_column(column) {}
  
  /** \details
    Destroys the vertex position object.
  */
  virtual ~OdTvVertexPos() {};

  /** \details
    Retrieves the current row count from the mesh.
    
    \returns Returns the row count of the mesh.
  */
  OdUInt32 getRow() const { return m_row; }
  
  /** \details
    Retrieves the current column count from the mesh.
    
    \returns Returns the column count of the mesh.
  */
  OdUInt32 getColumn() const { return m_column; }

//DOM-IGNORE-BEGIN
private:
  OdUInt32 m_row;
  OdUInt32 m_column;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of mesh vertex positions.
*/
typedef OdVector<OdTvVertexPos, OdMemoryAllocator<OdTvVertexPos> >  OdTvVertexPosArray;


/** \details
  This is an interface class for manipulating Visualize mesh data.
  \sa
  <link tv_geometry_meshes, Work with Meshes>
*/
class ODTV_EXPORT OdTvMeshData : public OdTvIObject
{
public:


  /** \details
    Sets the mesh geometry parameters.
    
    \param nRows          [in] A new value of the mesh row count.
    \param nColumns       [in] A new value of the mesh column count.
    \param verticesArray  [in] A vertex array of the mesh.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mesh parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray) = 0;

  /** \details
    Sets the mesh geometry parameters.
    
    \param nRows      [in] A quantity of mesh rows.
    \param nColumns   [in] A quantity of mesh columns.
    \param nVertices  [in] A quantity of mesh vertexes.
    \param vertices   [in] A pointer to the array of points that represent the vertexes of the mesh.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mesh parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setParam(OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices) = 0;

  /** \details
    Retrieves the current mesh geometry parameters.
    
    \param nRows          [out] A placeholder for the quantity of mesh rows.
    \param nColumns       [out] A placeholder for the quantity of mesh columns.
    \param verticesArray  [out] A placeholder for the array of mesh vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the parameter values were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getParam(OdUInt32& nRows, OdUInt32& nColumns, OdTvPointArray& verticesArray) = 0;

  /** \details
    Retrieves the current quantity of mesh vertexes.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of mesh vertexes.
    \remarks
    If the rc parameter is not null and the quantity of mesh vertexes was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getVerticesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current quantity of mesh faces.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of mesh faces.
    \remarks
    If the rc parameter is not null and the quantity of mesh faces was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getFacesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current quantity of mesh edges.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of mesh edges.
    \remarks
    If the rc parameter is not null and the quantity of mesh edges was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getEdgesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current quantity of mesh rows.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of mesh rows.
    \remarks
    If the rc parameter is not null and the quantity of mesh rows was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getRowsCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current quantity of mesh columns.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the quantity of mesh columns.
    \remarks
    If the rc parameter is not null and the quantity of mesh columns was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 getColumnsCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the selectable property for the faces of the mesh. The selectable property determines whether the faces of the mesh can be selected.
    
    \param bSelectable [in] A boolean value that is equal to true if the faces can be selected; otherwise it should be equal to false.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new value of the selectable property for the mesh faces is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFacesSelectable(bool bSelectable) = 0;

  /** \details
    Retrieves current value of the selectable property for the faces of the mesh. Selectable property determines whether the faces of the mesh can be selected.
    
    \param bIsInherited [out] A placeholder for a value of the flag that determines whether the selectability property is inherited.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the faces of the mesh can be selected; otherwise the method returns false.
    \remarks
    The method stores true in the bIsInherited parameter if the selectable property value is inherited from the parent entity (sub-entity).
    If the rc parameter is not null and the current value of the selectable property is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getFacesSelectable(bool* bIsInherited = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the selectable property for the edges of the mesh. The selectable property determines whether the edges of the mesh can be selected.
    
    \param bSelectable [in] A boolean value that is equal to true if the edges can be selected; otherwise it should be equal to false.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new value of the selectable property for the mesh edges is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesSelectable(bool bSelectable) = 0;

  /** \details
    Retrieves current value of the selectable property for the edges of the mesh. Selectable property determines whether the edges of the mesh can be selected.
    
    \param bIsInherited [out] A placeholder for a value of the flag that determines whether the selectability property is inherited.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the edges of the mesh can be selected; otherwise the method returns false.
    \remarks
    The method stores true in the bIsInherited parameter if the selectable property value is inherited from the parent entity (sub-entity).
    If the rc parameter is not null and the current value of the selectable property is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getEdgesSelectable(bool* bIsInherited = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Replaces the vertexes of the mesh starting at a specified position.
    
    \param startRow       [in] A starting row position.
    \param startColumn    [in] A starting column position.
    \param nRows          [in] A quantity of rows to be replaced.
    \param nColumns       [in] A quantity of columns to be replaced.
    \param verticesArray  [in] An array of points that represent vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mesh vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaRange(OdUInt32 startRow, OdUInt32 startColumn, OdUInt32 nRows, OdUInt32 nColumns, const OdTvPointArray& verticesArray) = 0;

  /** \details
    Replaces the vertexes of the mesh starting at a specified position.
    
    \param startRow       [in] A starting row position.
    \param startColumn    [in] A starting column position.
    \param nRows          [in] A quantity of rows to be replaced.
    \param nColumns       [in] A quantity of columns to be replaced.
    \param nVertices      [in] A quantity of vertexes to be replaced.
    \param vertices       [in] A pointer to an array of <link OdTvPoint, OdTvPoint> objects that represent vertexes for replacement.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mesh vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaRange(OdUInt32 startRow, OdUInt32 startColumn, OdUInt32 nRows, OdUInt32 nColumns, OdUInt32 nVertices, const OdTvPoint* vertices) = 0;

  /** \details
    Replaces the vertexes of the mesh with a specified vertex list. The list of vertexes is defined with a set of vertex position objects.
    
    \param indVertices    [in] An array of vertex positions for replacement.
    \param verticesArray  [in] A pointer to an array of <link OdTvPoint, OdTvPoint> objects that represent the new vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mesh vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaList(const OdTvVertexPosArray& indVertices, const OdTvPointArray& verticesArray) = 0;

  /** \details
    Replaces the vertexes of the mesh with a specified vertex list. The list of vertexes is defined with a set of vertex position objects.
    
    \param nVertices   [in] A quantity of vertexes for replacement.
    \param indVertices [in] A pointer to an array of vertex positions for replacement.
    \param vertices    [in] A pointer to an array of <link OdTvPoint, OdTvPoint> objects that represent the new vertexes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified mesh vertexes were successfully replaced, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult editVerticesViaList(OdUInt32 nVertices, const OdTvVertexPos* indVertices, const OdTvPoint* vertices) = 0;

  /** \details
    Sets colors for a list of mesh vertexes.
    
    \param nCount       [in] A quantity of vertexes to set colors for.
    \param indVertices  [in] A pointer to an array of vertex indexes.
    \param colors       [in] A pointer to an array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified mesh vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef* colors) = 0;
  
  /** \details
    Sets colors for a list of mesh vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param colors       [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the colors for specified mesh vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDefArray& colors) = 0;
  
  /** \details
    Sets a color for a list of mesh vertexes.
    
    \param nCount       [in] A quantity of vertexes to set the color for.
    \param indVertices  [in] A pointer to an array of vertex indexes.
    \param color        [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified mesh vertexes was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets a color for a list of mesh vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param color        [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified mesh vertexes was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaList(const OdInt32Array& indVertices, const OdTvRGBColorDef& color) = 0;

  /** \details
    Sets a color for a range of mesh vertexes.
    
    \param indStart [in] A starting index for replacement.
    \param nCount   [in] A quantity of vertexes for replacement.
    \param color    [in] A color definition to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color for specified mesh vertexes was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef& color) = 0;
  
  /** \details
    Sets colors for a range of mesh vertexes.
    
    \param indStart [in] A starting index for replacement.
    \param colors   [in] An array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified mesh vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, const OdTvRGBColorDefArray& colors) = 0;
  
  /** \details
    Sets colors for a range of mesh vertexes.
    
    \param indStart [in] A starting index for replacement.
    \param nCount   [in] A quantity of vertexes for replacement.
    \param colors   [in] A pointer to an array of color definitions to be applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified mesh vertexes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvRGBColorDef* colors) = 0;
  
  
  /** \details
    Retrieves colors for a range of mesh vertexes.
    
    \param indStart [in] A starting index of the range.
    \param nCount   [in] A quantity of vertexes in the range.
    \param colors   [out] A placeholder for an array of color definitions to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified mesh vertexes were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getVertexColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvRGBColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves colors for a range of mesh vertexes.
    
    \param indVertices [in] An array of mesh vertex indexes.
    \param colors       [out] A placeholder for an array of color definitions to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors for specified mesh vertexes were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getVertexColorsViaList(const OdInt32Array& indVertices, OdTvRGBColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves the color for a specified mesh vertex.
    
    \param ind [in] A mesh vertex index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the instance of the <link OdTvRGBColorDef, OdTvRGBColorDef> class that represents the color information.
    \remarks
    If the rc parameter is not null and the color data was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvRGBColorDef getVertexColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new vertex orientation value for the mesh.
    
    \param orientation [in] A vertex orientation value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If a new vertex orientation was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexOrientation(OdTv::OrientationType orientation) = 0;
  
  /** \details
    Retrieves the current vertex orientation of the mesh.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the vertex orientation.
    \remarks
    If the rc parameter is not null and the orientation type value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTv::OrientationType getVertexOrientation(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets normal vectors for a list of mesh vertexes.
    
    \param nCount       [in] A quantity of vertexes in the list.
    \param indVertices  [in] An array of vertex indexes represented with a pointer to the first array element.
    \param vectors      [in] An array of normal vectors represented with a pointer to a first vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector* vectors) = 0;
  
  /** \details
    Sets normal vectors for a list of mesh vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normal vectors for a list of mesh vertexes.
    
    \param nCount       [in] A quantity of vertexes in the list.
    \param indVertices  [in] An array of vertex indexes represented with a pointer to the first array element.
    \param vector       [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normal vectors for a list of mesh vertexes.
    
    \param indVertices  [in] An array of vertex indexes.
    \param vector       [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaList(const OdInt32Array& indVertices, const OdTvVector& vector) = 0;

  /** \details
    Sets normal vectors for a range of mesh vertexes.
    
    \param indStart     [in] An index of the mesh vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param vector       [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normal vectors for a range of mesh vertexes.
    
    \param indStart     [in] An index of the mesh vertex array that represents the start position of the range.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normal vectors for a range of mesh vertexes.
    
    \param indStart     [in] An index of the mesh vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param vectors      [in] An array of normal vectors represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors) = 0;

  /** \details
    Retrieves normal vectors for a range of mesh vertexes.
    
    \param indStart     [in] An index of the mesh vertex array that represents the start position of the range.
    \param nCount       [in] A quantity of vertexes in the range from the start position.
    \param vectors      [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves normal vectors for a list of mesh vertexes.
    
    \param indVertices [in] An array of vertex indexes.
    \param vectors     [out] A placeholder for the array of normal vectors to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the retrieved normal vectors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexNormalsViaList(const OdInt32Array& indVertices, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves the normal vector for a specified mesh vertex.
    
    \param ind      [in] A mesh vertex index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the <link OdTvVector, OdTvVector> class that contains normal vector information.
    \remarks
    If the rc parameter is not null and the normal vector object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getVertexNormal(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets texture coordinates for a mesh vertex list.
    
    \param nCount         [in] A quantity of mesh vertexes.
    \param indVertices    [in] A pointer to an array of mesh vertex indexes.
    \param mappingCoords  [in] A pointer to an array of two-dimensional points that represent texture coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinates were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d* mappingCoords) = 0;
  
  /** \details
    Sets texture coordinates for a mesh vertex list.
    
    \param indVertices   [in] An array of mesh vertex indexes.
    \param mappingCoords [in] An array of two-dimensional points that represent texture coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinates were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2dArray& mappingCoords) = 0;
  
  /** \details
    Sets a texture coordinate for a mesh vertex list.
    
    \param nCount        [in] A quantity of mesh vertexes.
    \param indVertices   [in] A pointer to an array of mesh vertex indexes.
    \param mappingCoord  [in] A two-dimensional point that represents a texture coordinate.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinate was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(OdInt32 nCount, const OdInt32* indVertices, const OdTvPoint2d& mappingCoord) = 0;
  
  /** \details
    Sets a texture coordinate for a mesh vertex list.
    
    \param indVertices   [in] An array of mesh vertex indexes.
    \param mappingCoord  [in] A two-dimensional point that represents a texture coordinate.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinate was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaList(const OdInt32Array indVertices, const OdTvPoint2d& mappingCoord) = 0;

  /** \details
    Sets texture coordinates for a specified range of mesh vertexes.
    
    \param indStart [in] A starting index of mesh vertexes.
    \param nCount   [in] A quantity of mesh vertexes to be set with texture coordinates.
    \param mappingCoords [in] A pointer to an array of two-dimensional points that represent texture coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinates were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d* mappingCoords) = 0;

  /** \details
    Sets texture coordinates for a specified range of mesh vertexes.
    
    \param indStart       [in] A starting index of mesh vertexes.
    \param nCount         [in] A quantity of mesh vertexes to be set with texture coordinates.
    \param mappingCoords  [in] A pointer to an array of two-dimensional points that represent texture coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinates were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, const OdTvPoint2dArray& mappingCoords) = 0;
  
  /** \details
    Sets a texture coordinate for a specified range of mesh vertexes.
    
    \param indStart     [in] A starting index of mesh vertexes.
    \param nCount       [in] A quantity of mesh vertexes to be set with texture coordinates.
    \param mappingCoord [in] A two-dimensional point that represents a texture coordinate.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinate was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvPoint2d& mappingCoord) = 0;

  /** \details
    Retrieves texture coordinates for a specified range of mesh vertexes.
    
    \param indStart       [in] A starting index of the mesh vertex range.
    \param nCount         [in] A quantity of mesh vertexes included in the range.
    \param mappingCoords  [out] A placeholder for a two-dimensional point array that represents texture coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinates were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexMappingCoordsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvPoint2dArray& mappingCoords) const = 0;
  
  /** \details
    Retrieves texture coordinates for a specified range of mesh vertexes.
    
    \param indVert       [in] An array of vertex indexes that are included in the range.
    \param mappingCoords [out] A placeholder for a two-dimensional point array that represents texture coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the texture coordinates were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexMappingCoordsViaList(const OdInt32Array& indVert, OdTvPoint2dArray& mappingCoords) const = 0;
  
  /** \details
    Retrieves the texture coordinate for a specified mesh vertex.
    
    \param ind [in] A vertex index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a two-dimensional point that represents the texture coordinate.
    \remarks
    If the rc parameter is not null and the texture coordinate was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPoint2d getVertexMappingCoord(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  //**************************************************************************************
  // Group of the methods for managing the properties of the faces
  //**************************************************************************************

  /** \details
    Sets colors for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param colors   [in] A pointer to an array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If face colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef* colors) = 0;
  
  /** \details
    Sets colors for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param colors   [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets a color for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param color    [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets a color for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param color    [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaList(const OdInt32Array& indFaces, const OdTvColorDef& color) = 0;

  /** \details
    Sets a color for a specified range of mesh faces.
    
    \param indStart [in] A starting index of mesh faces.
    \param nCount   [in] A quantity of mesh faces to be updated with a new color.
    \param color  [in] A color definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets a color for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param colors   [in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    The quantity of faces to be updated with new colors is defined with the color definition array size.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets colors for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces to be updated with new colors.
    \param colors   [in] A pointer to an array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors) = 0;

  /** \details
    Retrieves colors for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces included in the range.
    \param colors [out] A placeholder for a color definition array to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getFaceColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves colors for a specified range of mesh faces.
    
    \param indFaces [in] An array of face indexes that are included in the range.
    \param colors   [out] A placeholder for a color definition array to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getFaceColorsViaList(const OdInt32Array& indFaces, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves the color for a specified mesh face.
    
    \param ind [in] A face index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a color definition object that determines the specified face's color.
    \remarks
    If the rc parameter is not null and the color was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getFaceColor(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets normal vectors for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param vectors  [in] A pointer to an array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector* vectors) = 0;
  
  /** \details
    Sets normal vectors for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param vectors  [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(const OdInt32Array& indFaces, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets a normal vector for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param vector   [in] A normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVector& vector) = 0;
  
  /** \details
    Sets a normal vector for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param vector   [in] A normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaList(const OdInt32Array& indFaces, const OdTvVector& vector) = 0;

  /** \details
    Sets a normal vector for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces to be updated with a new normal vector.
    \param vector   [in] A normal vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal vector was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector& vector) = 0;
  
  /** \details
    Sets normal vectors for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param vectors  [in] An array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    The quantity of faces to be updated with new normal vectors is determined with the vector array's size.
  */
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, const OdTvVectorArray& vectors) = 0;
  
  /** \details
    Sets normal vectors for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces to be updated with new normal vectors.
    \param vectors  [in] A pointer to an array of normal vectors.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normal vectors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVector* vectors) = 0;

  /** \details
    Retrieves normal vectors for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces included in the range.
    \param vectors  [out] A placeholder for an array of normal vectors to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normal vectors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceNormalsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves normal vectors for a specified range of mesh faces.
    
    \param indFaces [in] An array of face indexes that are included in the range.
    \param vectors  [out] A placeholder for an array of normal vectors to be returned to a calling subroutine.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If normal vectors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceNormalsViaList(const OdInt32Array& indFaces, OdTvVectorArray& vectors) const = 0;
  
  /** \details
    Retrieves the normal vector for a specified mesh face.
    
    \param ind [in] A face index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a normal vector.
    \remarks
    If the rc parameter is not null and the normal vector was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getFaceNormal(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets visibility parameters for a list of mesh faces.
    
    \param nCount         [in] A quantity of mesh faces.
    \param indFaces       [in] A pointer to an array of mesh face indexes.
    \param visibilities   [in] A pointer to an array of visibility parameter definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef* visibilities) = 0;
  
  /** \details
    Sets visibility parameters for a list of mesh faces.
    
    \param indFaces     [in] An array of mesh face indexes.
    \param visibilities [in] An array of visibility parameter definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(const OdInt32Array& indFaces, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets a visibility definition for a list of mesh faces.
    
    \param nCount     [in] A quantity of mesh faces.
    \param indFaces   [in] A pointer to an array of mesh face indexes.
    \param visibility [in] A visibility parameter definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility parameter definition was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvVisibilityDef& visibility) = 0;
  
  /** \details
    Sets a visibility definition for a list of mesh faces.
    
    \param indFaces   [in] An array of mesh face indexes.
    \param visibility [in] A visibility parameter definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility parameter definition was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaList(const OdInt32Array& indFaces, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets visibility parameters for a specified range of mesh faces.
    
    \param indStart     [in] A starting index of the mesh face range.
    \param nCount       [in] A quantity of mesh faces to be updated with visibility parameters.
    \param visibilities [in] A pointer to an array of visibility parameter definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities) = 0;
  
  /** \details
    Sets visibility parameters for a specified range of mesh faces.
    
    \param indStart     [in] A starting index of the mesh face range.
    \param visibilities [in] An array of visibility parameter definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets a visibility definition for a specified range of mesh faces.
    
    \param indStart   [in] A starting index of the mesh face range.
    \param nCount     [in] A quantity of mesh faces to be updated with visibility parameters.
    \param visibility [in] A visibility parameter definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility definition was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Retrieves visibility parameters for a specified range of mesh faces.
    
    \param indStart     [in] A starting index of the mesh faces range.
    \param nCount       [in] A quantity of mesh faces included in the range.
    \param visibilities [out] A placeholder for an array that represents visibility parameters.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves visibility parameters for a specified range of mesh faces.
    
    \param indFaces     [in] An array of face indexes that are included in the range.
    \param visibilities [out] A placeholder for an array of visibility parameter definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceVisibilitiesViaList(const OdInt32Array& indFaces, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves the visibility definition for a specified mesh face.
    
    \param ind  [in] A face index.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an object that contains visibility parameters.
    \remarks
    If the rc parameter is not null and the visibility parameters object was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVisibilityDef getFaceVisibility(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets layers for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param layers   [in] A pointer to an array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef* layers) = 0;
  
  /** \details
    Sets layers for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param layers   [in] An array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(const OdInt32Array& indFaces, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets a layer for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param layer    [in] A layer definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvLayerDef& layer) = 0;
  
  /** \details
    Sets a layer for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param layer    [in] A layer definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaList(const OdInt32Array& indFaces, const OdTvLayerDef& layer) = 0;

  /** \details
    Sets layers for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces to be set with layers.
    \param layers [in] A pointer to an array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers) = 0;
  
  /** \details
    Sets layers for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param layers   [in] An array of layers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets a layer for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces.
    \param layer    [in] A layer definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer) = 0;

  /** \details
    Retrieves layers for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces.
    \param layers   [out] A placeholder for the array of layers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getFaceLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves layers for a specified range of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param layers   [out] A placeholder for the array of layers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getFaceLayersViaList(const OdInt32Array& indFaces, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves the layer for a specified mesh face.
    
    \param ind [in] A face index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a layer definition object.
    \remarks
    If the rc parameter is not null and the layer was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getFaceLayer(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets transparency parameters for a list of mesh faces.
    
    \param nCount         [in] A quantity of mesh faces.
    \param indFaces       [in] A pointer to an array of mesh face indexes.
    \param transparencies [in] A pointer to an array of transparency definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If transparency parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef* transparencies) = 0;
  
  /** \details
    Sets transparency parameters for a list of mesh faces.
    
    \param indFaces       [in] An array of mesh face indexes.
    \param transparencies [in] An array of transparency definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If transparency parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(const OdInt32Array& indFaces, const OdTvTransparencyDefArray& transparencies) = 0;
  
  /** \details
    Sets a transparency for a list of mesh faces.
    
    \param nCount       [in] A quantity of mesh faces.
    \param indFaces     [in] A pointer to an array of mesh face indexes.
    \param transparency [in] A transparency definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the transparency was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvTransparencyDef& transparency) = 0;
  
  /** \details
    Sets a transparency for a list of mesh vertexes.
    
    \param indFaces     [in] An array of mesh face indexes.
    \param transparency [in] A transparency definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the transparency was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaList(const OdInt32Array& indFaces, const OdTvTransparencyDef& transparency) = 0;

  /** \details
    Sets transparency parameters for a specified range of mesh faces.
    
    \param indStart       [in] A starting index of the mesh face range.
    \param nCount         [in] A quantity of mesh faces to be updated with new transparency parameters.
    \param transparencies [in] A pointer to an array of transparency definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If transparency parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef* transparencies) = 0;
  
  /** \details
    Sets transparency parameters for a specified range of mesh faces.
    
    \param indStart       [in] A starting index of the mesh face range.
    \param transparencies [in] An array of transparency definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If transparency parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, const OdTvTransparencyDefArray& transparencies) = 0;
  
  /** \details
    Sets a transparency for a specified range of mesh faces.
    
    \param indStart     [in] A starting index of the mesh face range.
    \param nCount       [in] A quantity of mesh faces to be set with the transparency.
    \param transparency [in] A transparency definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the transparency was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvTransparencyDef& transparency) = 0;

  /** \details
    Retrieves transparency parameters for a specified range of mesh faces.
    
    \param indStart       [in] A starting index of the mesh face range.
    \param nCount         [in] A quantity of mesh faces included in the range.
    \param transparencies [out] A placeholder for an array of transparency definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If transparency parameters were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceTransparencyViaRange(OdInt32 indStart, OdInt32 nCount, OdTvTransparencyDefArray& transparencies) const = 0;
  
  /** \details
    Retrieves transparency parameters for a specified range of mesh faces.
    
    \param indFaces       [in] An array of face indexes that are included in the range.
    \param transparencies [out] A placeholder for an array of transparency definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If transparency parameters were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFaceTransparencyViaList(const OdInt32Array& indFaces, OdTvTransparencyDefArray& transparencies) const = 0;
  
  /** \details
    Retrieves the transparency for a specified mesh face.
    
    \param ind [in] A face index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a transparency definition object.
    \remarks
    If the rc parameter is not null and the transparency value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvTransparencyDef getFaceTransparency(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets materials for a list of mesh faces.
    
    \param nCount    [in] A quantity of mesh faces.
    \param indFaces  [in] A pointer to an array of mesh face indexes.
    \param materials [in] A pointer to an array of materials definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If materials were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef* materials) = 0;
  
  /** \details
    Sets materials for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param materials [in] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If materials were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDefArray& materials) = 0;
  
  /** \details
    Sets a material for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param material [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the material was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMaterialDef& material) = 0;
  
  /** \details
    Sets a material for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param material  [in] A material definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the material was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaList(const OdInt32Array& indFaces, const OdTvMaterialDef& material) = 0;

  /** \details
    Sets materials for a specified range of mesh faces.
    
    \param indStart   [in] A starting index of the mesh face range.
    \param nCount     [in] A quantity of mesh faces to be updated with a new material.
    \param materials  [in] A pointer to an array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If materials were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef* materials) = 0;
  
  /** \details
    Sets materials for a specified range of mesh faces.
    
    \param indStart   [in] A starting index of the mesh face range.
    \param materials  [in] An array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the materials were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, const OdTvMaterialDefArray& materials) = 0;
  
  /** \details
    Sets a material for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces to be updated with a new material.
    \param material [in] A material definition object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the material was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult setFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMaterialDef& material) = 0;

  /** \details
    Retrieves materials for a specified range of mesh faces.
    
    \param indStart  [in] A starting index of the mesh face range.
    \param nCount    [in] A quantity of mesh faces included in the range.
    \param materials [out] A placeholder for an array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If materials were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult getFaceMaterialsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMaterialDefArray& materials) const = 0;
  
  /** \details
    Retrieves materials for a specified range of mesh faces.
    
    \param indFaces  [in] An array of face indexes that are included in the range.
    \param materials [out] A placeholder for an array of material definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If materials were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvResult getFaceMaterialsViaList(const OdInt32Array& indFaces, OdTvMaterialDefArray& materials) const = 0;
  
  /** \details
    Retrieves the material for a specified mesh face.
    
    \param ind [in] A face index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a material definition object.
    \remarks
    If the rc parameter is not null and the material was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials, Work with Materials>
  */
  virtual OdTvMaterialDef getFaceMaterial(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets mappers for a list of mesh faces.
    
    \param nCount    [in] A quantity of mesh faces.
    \param indFaces  [in] A pointer to an array of mesh face indexes.
    \param mappers   [in] A pointer to an array of mapper definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If mappers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef* mappers) = 0;
  
  /** \details
    Sets mappers for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param mappers  [in] An array of mapper definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If mappers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(const OdInt32Array& indFaces, const OdTvMapperDefArray& mappers) = 0;
  
  /** \details
    Sets a mapper for a list of mesh faces.
    
    \param nCount   [in] A quantity of mesh faces.
    \param indFaces [in] A pointer to an array of mesh face indexes.
    \param mapper [in] A mapper definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the mapper was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(OdInt32 nCount, const OdInt32* indFaces, const OdTvMapperDef& mapper) = 0;
  
  /** \details
    Sets a mapper for a list of mesh faces.
    
    \param indFaces [in] An array of mesh face indexes.
    \param mapper   [in] A mapper definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the mapper was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaList(const OdInt32Array& indFaces, const OdTvMapperDef& mapper) = 0;

  /** \details
    Sets mappers for a specified range of mesh faces.
    
    \param indStart   [in] A starting index of the mesh face range.
    \param nCount     [in] A quantity of mesh faces to be updated with a new mapper.
    \param mappers    [in] A pointer to an array of mapper definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If mappers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef* mappers) = 0;
  
  /** \details
    Sets mappers for a specified range of mesh faces.
    
    \param indStart   [in] A starting index of the mesh face range.
    \param mappers    [in] An array of mapper definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If mappers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, const OdTvMapperDefArray& mappers) = 0;
  
  /** \details
    Sets a mapper for a specified range of mesh faces.
    
    \param indStart [in] A starting index of the mesh face range.
    \param nCount   [in] A quantity of mesh faces to be updated with a new mapper.
    \param mapper   [in] A mapper definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the mapper was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvMapperDef& mapper) = 0;

  /** \details
    Sets a mapper for all mesh faces.
    
    \param mapper   [in] A mapper definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the mapper was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult setFaceMapper(const OdTvMapperDef& mapper) = 0;
  
  /** \details
    Retrieves mappers for a specified range of mesh faces.
    
    \param indStart  [in] A starting index of the mesh faces range.
    \param nCount    [in] A quantity of mesh faces included in the range.
    \param mappers   [out] A placeholder for an array of mapper definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If mappers were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult getFaceMappersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvMapperDefArray& mappers) const = 0;
  
  /** \details
    Retrieves mappers for a specified range of mesh faces.
    
    \param indFaces  [in] An array of face indexes that are included in the range.
    \param mappers   [out] A placeholder for an array of mapper definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If mappers were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvResult getFaceMappersViaList(const OdInt32Array& indFaces, OdTvMapperDefArray& mappers) const = 0;
  
  /** \details
    Retrieves the mapper for a specified mesh face.
    
    \param ind [in] A face index.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a mapper definition object.
    \remarks
    If the rc parameter is not null and the mapper was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
  */
  virtual OdTvMapperDef getFaceMapper(OdInt32 ind, OdTvResult* rc = NULL) const = 0;

  //**************************************************************************************
  // Group of the methods for managing the properties of the edges
  //**************************************************************************************

  /** \details
    Sets colors for a list of mesh edges.
    
    \param nCount   [in] A quantity of mesh edges.
    \param indEdges [in] A pointer to an array of mesh edge indexes.
    \param colors   [in] A pointer to an array of color definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef* colors) = 0;
  
  /** \details
    Sets colors for a list of mesh edges.
    
    \param indEdges [in] An array of mesh edge indexes.
    \param colors   [in] An array of color definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(const OdInt32Array& indEdges, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets a color for a list of mesh edges.
    
    \param nCount   [in] A quantity of mesh edges.
    \param indEdges [in] A pointer to an array of mesh edge indexes.
    \param color [in] A color definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets a color for a list of mesh edges.
    
    \param indEdges [in] An array of mesh edge indexes.
    \param color    [in] A color definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaList(const OdInt32Array& indEdges, const OdTvColorDef& color) = 0;

  /** \details
    Sets a color for a specified range of mesh edges.
    
    \param indStart   [in] A starting index of the mesh edge range.
    \param nCount     [in] A quantity of mesh edges to be updated with a new color.
    \param color      [in] A color definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef& color) = 0;
  
  /** \details
    Sets colors for a specified range of mesh edges.
    
    \param indStart   [in] A starting index of the mesh edge range.
    \param colors     [in] An array of color definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, const OdTvColorDefArray& colors) = 0;
  
  /** \details
    Sets colors for a specified range of mesh edges.
    
    \param indStart [in] A starting index of the mesh edge range.
    \param nCount   [in] A quantity of mesh edges to be updated with a new color.
    \param colors   [in] A pointer to an array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult setEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvColorDef* colors) = 0;

  /** \details
    Retrieves colors for a specified range of mesh edges.
    
    \param indEdges  [in] An array of edge indexes that are included in the range.
    \param colors    [out] A placeholder for an array of color definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getEdgeColorsViaList(const OdInt32Array& indEdges, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves colors for a specified range of mesh edges.
    
    \param indStart  [in] A starting index of the mesh edges range.
    \param nCount    [in] A quantity of mesh edges included in the range.
    \param colors    [out] A placeholder for an array of color definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If colors were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvResult getEdgeColorsViaRange(OdInt32 indStart, OdInt32 nCount, OdTvColorDefArray& colors) const = 0;
  
  /** \details
    Retrieves the color for a specified mesh edge.
    
    \param ind [in] An edge index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a color definition object.
    \remarks
    If the rc parameter is not null and the color was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_colors, Work with Colors>
  */
  virtual OdTvColorDef getEdgeColor(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets visibility parameters for a list of mesh edges.
    
    \param nCount       [in] A quantity of mesh edges.
    \param indEdges     [in] A pointer to an array of mesh edge indexes.
    \param visibilities [in] A pointer to an array of visibility definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef* visibilities) = 0;
  
  /** \details
    Sets visibility parameters for a list of mesh edges.
    
    \param indEdges     [in] An array of mesh edge indexes.
    \param visibilities [in] An array of visibility definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets a visibility for a list of mesh edges.
    
    \param nCount     [in] A quantity of mesh edges.
    \param indEdges   [in] A pointer to an array of mesh edge indexes.
    \param visibility [in] A visibility definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvVisibilityDef& visibility) = 0;
  
  /** \details
    Sets a visibility for a list of mesh edges.
    
    \param indEdges   [in] An array of mesh edge indexes.
    \param visibility [in] A visibility definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaList(const OdInt32Array& indEdges, const OdTvVisibilityDef& visibility) = 0;

  /** \details
    Sets a visibility for a specified range of mesh edges.
    
    \param indStart   [in] A starting index of the mesh edge range.
    \param nCount     [in] A quantity of mesh edges to be updated with a new visibility value.
    \param visibility [in] A of visibility definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef& visibility) = 0;
  
  /** \details
    Sets visibility parameters for a specified range of mesh edges.
    
    \param indStart     [in] A starting index of the mesh edge range.
    \param visibilities [in] An array of visibility definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, const OdTvVisibilityDefArray& visibilities) = 0;
  
  /** \details
    Sets visibility parameters for a specified range of mesh edges.
    \param indStart     [in] A starting index of the mesh edge range.
    \param nCount       [in] A quantity of mesh edges to be updated with a new visibility value.
    \param visibilities [in] An array of visibility definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvVisibilityDef* visibilities) = 0;

  /** \details
    Retrieves visibility parameters for a specified range of mesh edges.
    
    \param indEdges  [in] An array of edge indexes that are included in the range.
    \param visibilities [out] A placeholder for an array of visibility definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgeVisibilitiesViaList(const OdInt32Array& indEdges, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves visibility parameters for a specified range of mesh edges.
    
    \param indStart     [in] A starting index of the mesh edges range.
    \param nCount       [in] A quantity of mesh edges included in the range.
    \param visibilities [out] A placeholder for an array of visibility definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If visibility parameters were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgeVisibilitiesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvVisibilityDefArray& visibilities) const = 0;
  
  /** \details
    Retrieves the visibility for a specified mesh edge.
    
    \param ind [in] An edge index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a visibility definition object.
    \remarks
    If the rc parameter is not null and the visibility value was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVisibilityDef getEdgeVisibility(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;


  /** \details
    Sets linetypes for a list of mesh edges.
    
    \param nCount    [in] A quantity of mesh edges.
    \param indEdges  [in] A pointer to an array of mesh edge indexes.
    \param linetypes [in] A pointer to an array of linetype definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If linetypes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef* linetypes) = 0;
  
  /** \details
    Sets linetypes for a list of mesh edges.
    
    \param indEdges  [in] An array of mesh edge indexes.
    \param linetypes [in] An array of linetype definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If linetypes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(const OdInt32Array& indEdges, const OdTvLinetypeDefArray& linetypes) = 0;
  
  /** \details
    Sets a linetype for a list of mesh edges.
    
    \param nCount   [in] A quantity of mesh edges.
    \param indEdges [in] A pointer to an array of mesh edge indexes.
    \param linetype [in] A linetype definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the linetype was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLinetypeDef& linetype) = 0;
  
  /** \details
    Sets a linetype for a list of mesh edges.
    
    \param indEdges [in] An array of mesh edge indexes.
    \param linetype [in] A linetype definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the linetype was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaList(const OdInt32Array& indEdges, const OdTvLinetypeDef& linetype) = 0;

  /** \details
    Sets a linetype for a specified range of mesh edges.
    
    \param indStart [in] A starting index of the mesh edge range.
    \param nCount   [in] A quantity of mesh edges to be updated with a new linetype.
    \param linetype [in] A linetype definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the linetype was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef& linetype) = 0;
  
  /** \details
    Sets linetypes for a specified range of mesh edges.
    
    \param indStart   [in] A starting index of the mesh edge range.
    \param linetypes [in] An array of linetype definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If linetypes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, const OdTvLinetypeDefArray& linetypes) = 0;
  
  /** \details
    Sets linetypes for a specified range of mesh edges.
    
    \param indStart  [in] A starting index of the mesh edge range.
    \param nCount    [in] A quantity of mesh edges to be updated with a new linetype.
    \param linetypes [in] A pointer to an array of linetype definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If linetypes were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult setEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLinetypeDef* linetypes) = 0;

  /** \details
    Retrieves linetypes for a specified range of mesh edges.
    
    \param indEdges  [in] An array of edge indexes that are included in the range.
    \param linetypes [out] A placeholder for an array of linetype definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If linetypes were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult getEdgeLinetypesViaList(const OdInt32Array& indEdges, OdTvLinetypeDefArray& linetypes) const = 0;
  
  /** \details
    Retrieves linetypes for a specified range of mesh edges.
    
    \param indStart  [in] A starting index of the mesh edge range.
    \param nCount    [in] A quantity of mesh edges included in the range.
    \param linetypes [out] A placeholder for an array of linetype definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If linetypes were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvResult getEdgeLinetypesViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLinetypeDefArray& linetypes) const = 0;
  
  /** \details
    Retrieves the linetype for a specified mesh edge.
    
    \param ind [in] An edge index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a linetype definition object.
    \remarks
    If the rc parameter is not null and the linetype was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_linetypes, Work with Linetypes>
  */
  virtual OdTvLinetypeDef getEdgeLinetype(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets layers for a list of mesh edges.
    
    \param nCount    [in] A quantity of mesh edges.
    \param indEdges  [in] A pointer to an array of mesh edge indexes.
    \param layers    [in] A pointer to an array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef* layers) = 0;
  
  /** \details
    Sets layers for a list of mesh edges.
    \param indEdges  [in] An array of mesh edge indexes.
    \param layers    [in] An array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(const OdInt32Array& indEdges, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets a layer for a list of mesh edges.
    \param nCount   [in] A quantity of mesh edges.
    \param indEdges [in] A pointer to an array of mesh edge indexes.
    \param layer    [in] A layer definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(OdInt32 nCount, const OdInt32* indEdges, const OdTvLayerDef& layer) = 0;
  
  /** \details
    Sets a layer for a list of mesh edges.
    
    \param indEdges [in] An array of mesh edge indexes.
    \param layer [in] A layer definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaList(const OdInt32Array& indEdges, const OdTvLayerDef& layer) = 0;

  /** \details
    Sets a layer for a specified range of mesh edges.
    
    \param indStart [in] A starting index of the mesh edge range.
    \param nCount   [in] A quantity of mesh edges to be updated with a new layer.
    \param layer    [in] A layer definition.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the layer was successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef& layer) = 0;
  
  /** \details
    Sets layers for a specified range of mesh edges.
    
    \param indStart   [in] A starting index of the mesh edge range.
    \param layers     [in] An array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, const OdTvLayerDefArray& layers) = 0;
  
  /** \details
    Sets layers for a specified range of mesh edges.
    
    \param indStart  [in] A starting index of the mesh edge range.
    \param nCount    [in] A quantity of mesh edges to be updated with a new layer.
    \param layers    [in] A pointer to an array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult setEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, const OdTvLayerDef* layers) = 0;

  /** \details
    Retrieves layers for a specified range of mesh edges.
    
    \param indEdges  [in] An array of edge indexes that are included in the range.
    \param layers    [out] A placeholder for an array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getEdgeLayersViaList(const OdInt32Array& indEdges, OdTvLayerDefArray& layers) const = 0;

  /** \details
    Retrieves layers for a specified range of mesh edges.
    
    \param indStart  [in] A starting index of the mesh edge range.
    \param nCount    [in] A quantity of mesh edges included in the range.
    \param layers    [out] A placeholder for an array of layer definitions.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If layers were successfully returned, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult getEdgeLayersViaRange(OdInt32 indStart, OdInt32 nCount, OdTvLayerDefArray& layers) const = 0;
  
  /** \details
    Retrieves the layer for a specified mesh edge.
    
    \param ind [in] An edge index.
    \param rc  [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a layer definition object.
    \remarks
    If the rc parameter is not null and the layer was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerDef getEdgeLayer(OdUInt32 ind, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that it is need to show mesh vertices for the mesh object.
    
    \param bShow         [in] Flag which indicates that it is need to show mesh vertices.
    \param verticesSize  [in] A vertices size which will be used for the vertices visualization.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If vertices visibility is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShowVertices(bool bShow, OdInt32 verticesSize = 5) = 0;

  /** \details
    Returns true if mesh vertices are visible. Also returns a vertices size which is used for the vertices visualization.
    
    \param verticesSize  [out] A vertices size which will be used for the vertices visualization.
    \param rc            [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if mesh vertices are visible, false otherwise.
    \remarks
    If the vertices visibility is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getShowVertices(OdInt32& verticesSize, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that only mesh vertices should be visualized for this mesh object.
    
    \param bShowOnly         [in] Flag which indicates that only mesh vertices should be visualized.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If flag is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    This method will have no effect if the show vertices flag is set to false.
  */
  virtual OdTvResult setShowOnlyVertices(bool bShowOnly) = 0;

  /** \details
    Returns true if only mesh vertices should be visualized for this mesh object.
    
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if only mesh vertices should be visualized, false otherwise.
    \remarks
    If the show only flag was successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getShowOnlyVertices(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets overriding of the vertices color. If bOverride flag is true, color will be applied to the mesh vertices. Otherwise, color from attributes will be applied.
    
    \param bOverride   [in] Flag if need apply mesh vertices color.
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
  A data type that represents a smart pointer to an instance of the mesh geometry type and is used for storing and passing references to the mesh object.
*/
typedef OdTvSmartPtr<OdTvMeshData> OdTvMeshDataPtr;

#endif // _ODTV_ENTITYGEOMETRYMESH_H_INCLUDED_

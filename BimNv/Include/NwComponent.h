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

#ifndef __TNW_COMPONENT_H__
#define __TNW_COMPONENT_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwTriangleIndexes.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GeVector3dArray.h"

class OdNwColor;
class OdGiRasterImage;
class OdGeMatrix3d;

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdGiRasterImage object pointers.
*/
typedef OdSmartPtr<OdGiRasterImage> OdGiRasterImagePtr;

/** \details
  This class represents a geometry component within the model hierarchy.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwComponent : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwComponent);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new OdNwComponent object.
  */
  OdNwComponent();

public:

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwComponent();

  /** \details
    Returns an array with fragments of this geometry component.

    \param aFragments [out] OdArray with object IDs of fragments of the geometry component.

    \returns eOk if successful, or an appropriate error code if not.
  */
  OdResult getFragments(OdNwObjectIdArray& aFragments) const;

  /** \details
    Indicates whether the component is hidden within the model hierarchy.

    \returns True if the component is hidden, or returns false if not.
  */
  bool isHidden() const;

  /** \details
    Returns bitfields with the primitives used to define this geometry component.

    \returns OdUInt8 value for bitfields with geometry primitives.

    \remarks
    The bitfields must contain the following bits:

    <table>
    Name                           Value   Description
    NwPrimitiveTypes::NONE         0x00    No primitives.
    NwPrimitiveTypes::TRIANGLES    0x01    Has triangle primitives.
    NwPrimitiveTypes::LINES        0x02    Has line primitives.
    NwPrimitiveTypes::POINTS       0x04    Has point primitives.
    NwPrimitiveTypes::SNAPPOINTS   0x08    Has snap point primitives.
    NwPrimitiveTypes::TEXT         0x10    Has text primitives.
    NwPrimitiveTypes::SOLID        0x20    Has solid primitives.
    </table>
  */
  OdUInt8 getPrimitives() const;

  /** \details
    Returns the object ID of the material of this component.

    \returns Object ID of the OdNwMaterial object with the material of this
    component. If the component does not have a material, the returned object ID
    is empty.
  */
  OdNwObjectId getMaterialId() const;

  /** \details
    Returns the object ID of the original material of this component, without
    override processing.

    \returns Object ID of the OdNwMaterial object with the original material of
    this component. If the component does not have a material, the returned
    object ID is empty.
  */
  OdNwObjectId getOriginalMaterialId() const;

  /** \details
    Returns the current (visible) transparency for this geometry component.

    \param val [out] Transparency value.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getTransparency(float& val) const;

  /** \details
    Returns the low bound of this geometry component in world space.

    \param lb [out] OdGePoint3d object with the low bound of this geometry component.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getLowBound(OdGePoint3d& lb) const;

  /** \details
    Returns the high bound of this geometry component in world space.

    \param hb [out] OdGePoint3d object with the high bound of this geometry component.

    \returns eOk if the operation is successful, or an appropriate error code
    otherwise.
  */
  OdResult getHighBound(OdGePoint3d& hb) const;

  /** \details
    Returns the number of fragments this geometry is divided into.

    \returns Number of fragments.
  */
  OdUInt32 getFragmentCount() const;

  /** \details
    Returns the object ID of the fragment with the geometry of this component.

    \param index [in] Value of the fragment's index in the component's fragment array.

    \returns Object ID of the OdNwFragment object with the fragment (by index)
    with the geometry of this component. If there is no fragment with this
    index, the returned object ID is empty.
  */
  OdNwObjectId findFragmentGeometry(OdUInt32 index) const;

  /** \details
    Adds a new fragment with given geometry to this component.

    \param geometryId [in] OdNwObjectId of the OdNwGeometry object with given geometry.
    \param pResult   [out] Pointer to the OdResult object with the error code.

    \returns Object ID of the new OdNwFragment object.
  */
  OdNwObjectId addFragmentGeometry(const OdNwObjectId& geometryId, OdResult* pResult = NULL);

  /** \details
    Adds a new fragment with the given circle geometry to this component.

    \param center   [in] Center of the circle.
    \param radius   [in] Radius of the circle.
    \param normal   [in] Normal of the circle.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns Object ID of the new OdNwFragment object.
  */
  OdNwObjectId addFragmentGeometryCircle(const OdGePoint3d& center, double radius, const OdGeVector3d& normal, OdResult* pResult = NULL);

  /** \details
    Adds a new fragment with the given polyline geometry to this component.

    \param points   [in] Array of 3D points.
    \param pResult [out] Pointer to the OdResult object with the error code.

    \returns Object ID of the new OdNwFragment object.
  */
  OdNwObjectId addFragmentGeometryPolyline(const OdGePoint3dArray& points, OdResult* pResult = NULL);

  /** \details
    Adds a new fragment with the given shell geometry to this component.

    \param pVertexList [in] Array with 3D points.
    \param pNormalList [in] Array with normals.
    \param pFaceList   [in] Array of vertex indices for each triangle.
    \param pResult    [out] Pointer to the OdResult object with the error code.

    \returns Object ID of the new OdNwFragment object.

    \remarks
    Arrays of vertices and normals must have the same size.
  */
  OdNwObjectId addFragmentGeometryShell(const OdGePoint3dArray& pVertexList, const OdGeVector3dArray& pNormalList, const OdArray<OdNwTriangleIndexes>& pFaceList, OdResult* pResult = NULL);

  /** \details
    Adds a new fragment with the given snap point geometry to this component.

    \param point    [in] Snap point 3D point.
    \param pResult [out] Pointer to the OdResult object with an error code.

    \returns Object ID of the new OdNwFragment object.
  */
  OdNwObjectId addFragmentGeometrySnapPoint(const OdGePoint3d& point, OdResult* pResult = NULL);

  /** \details
    Sets the material for the component.

    \param matId [in] Constant reference to the OdNwObjectId object with OdNwMaterial's derrived object.

    \returns eOk if the material is set to the component successfully, or an
    appropriate error code otherwise.
  */
  OdResult setMaterial(const OdNwObjectId& matId);

  /** \details
    Sets the ambient color of the component's material.

    \param clr [in] OdNwColor object with the color value.

    \returns eOk if the color is set to the material successfully, or an
    appropriate error code otherwise.
  */
  OdResult setAmbient(const OdNwColor& clr);

  /** \details
    Sets the diffuse color of the component's material.

    \param clr [in] OdNwColor object with the color value.

    \returns eOk if the color is set to the material successfully, or an
    appropriate error code otherwise.
  */
  OdResult setDiffuse(const OdNwColor& clr);

  /** \details
    Sets the specular color of the component's material.

    \param clr [in] OdNwColor object with the color value.

    \returns eOk if the color is set to the material successfully, or an
    appropriate error code otherwise.
  */
  OdResult setSpecular(const OdNwColor& clr);

  /** \details
    Sets the emissive color of the component's material.

    \param clr [in] OdNwColor object with the color value.

    \returns eOk if the color is set to the material successfully, or an
    appropriate error code otherwise.
  */
  OdResult setEmissive(const OdNwColor& clr);

  /** \details
    Sets the shininess value of the component's material.

    \param val [in] Shininess value.

    \returns eOk if the shininess is set to the material successfully, or an
    appropriate error code otherwise.
  */
  OdResult setShininess(float val);

  /** \details
    Sets the transparency value of the component's material.

    \param val [in] Transparency value.

    \returns eOk if the transparency is set to the material successfully, or an
    appropriate error code otherwise.
  */
  OdResult setTransparency(float val);

  /** \details
    Sets the internal texture data of the component's material.

    \param txtPath [in] A string value with the texture path.
    \param pTxtImage [in] A smart pointer to the OdGiRasterImage object with the texture.
    \param pMappingTransform [in] A pointer to an OdGeMatrix3d object with the texture mapping transformation.

    \returns eOk if the texture data is set to the material successfully, or an
    appropriate error code otherwise.

    \remarks
    The texture mapping transformation can contain:
      x scale value in the [0][0] element,
      y scale value in the [1][1] element,
      x offset value in the [0][3] element,
      y offset value in the [1][3] element.
    If the getMaterialId() method is called and returns an object ID with an OdNwTexture object and then the setInternalTexture() method is called, the returned object ID becomes invalid and the getMaterialId() method must be called again for correct behavior.
  */
  OdResult setInternalTexture(const OdString& txtPath, OdGiRasterImagePtr pTxtImage, const OdGeMatrix3d* pMappingTransform = NULL);

  /** \details
    Sets the external texture data of the component's material.

    \param txtPath [in] A string value with the texture path.
    \param pMappingTransform [in] A pointer to the OdGeMatrix3d object with the texture mapping transformation.

    \returns eOk if the texture data is set to the material successfully, or an
    appropriate error code otherwise.

    \remarks
    The texture mapping transformation can contain:
      x scale value in the [0][0] element,
      y scale value in the [1][1] element,
      x offset value in the [0][3] element,
      y offset value in the [1][3] element.
    If the getMaterialId() method is called and returns an object ID with an OdNwTexture object and after the setExternalTexture() method is called, the returned object ID becomes invalid and the getMaterialId() method must be called again for correct behavior.
  */
  OdResult setExternalTexture(const OdString& txtPath, const OdGeMatrix3d* pMappingTransform = NULL);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwComponent object pointers.
*/
typedef OdSmartPtr<OdNwComponent> OdNwComponentPtr;

#endif //__TNW_COMPONENT_H__

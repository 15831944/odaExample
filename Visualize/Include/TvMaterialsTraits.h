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

#ifndef _ODTV_MATERIALTRAITS_H_INCLUDED_
#define _ODTV_MATERIALTRAITS_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvTraitsDef.h"
#include "Tv.h"
#include "TvRasterImage.h"

/** \details
  The base interface class that implements mapping functionality for Visualize SDK textures.
  \sa
  <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
*/
class ODTV_EXPORT OdTvTextureMapper
{
public:

  /** \details
    Mapper's tiling methods.
  */
  enum Tiling
  {
    kInheritTiling = 0, // Inherits tiling from the current material's mapper.
    kTile = 1,          // Repeats a map along the image axes.
    kCrop = 2,          // Crops a map outside of the (0.0, 1.0) intervals at the image axes.
    kClamp = 3,         // Clamps (stretches) a map inside the (0.0, 1.0) intervals at the image axes.
    kMirror = 4         // Mirrors the material map at every integer boundary.
  };

  /** \details 
    Creates a new texture mapper object with default parameters. 
  */
  OdTvTextureMapper()
    : m_uTiling(kTile)
    , m_vTiling(kTile)
  {
  }

  /** \details 
    Creates a new texture mapper object as a copy of an existing object (copy constructor). 
    
    \param mapper [in] An original object.
  */
  OdTvTextureMapper(const OdTvTextureMapper& mapper);
  
  /** \details 
    The assignment operator for a texture mapper object. 
    
    \param mapper [in] A right hand operand of the assignment operation.
    \returns Returns the reference to the texture mapper modified after the assignment operation.
  */
  OdTvTextureMapper& operator=(const OdTvTextureMapper& mapper);
  
  /** \details 
    The equal operator that compares two texture mapper objects. 
    
    \param mapper [in] Another texture mapper object to be compared with.
    \returns Returns true if the texture mapper objects are equal; otherwise the method returns false.
  */
  bool operator==(const OdTvTextureMapper& mapper) const;
  
  /** \details 
    The non-equal operator for two texture mapper objects. 
    
    \param mapper [in] Another texture mapper object to be compared with.
    \returns Returns true if the texture mapper objects are not equal; otherwise the method returns false.
  */
  bool operator!=(const OdTvTextureMapper& mapper) const;

  /** \details
    Sets a new type of X-axis tiling for the texture mapper object.
    
    \param tiling [in] A new tiling type to be set.
  */
  void setUTiling(Tiling tiling);

  /** \details
    Sets a new type of Y-axis tiling for the texture mapper object.
    
    \param tiling [in] A new tiling type to be set.
  */
  void setVTiling(Tiling tiling);

  /** \details
    Retrieves the current type of X-axis tiling for the texture mapper object.
    
    \returns Returns the current type of X-axis tiling.
  */
  Tiling uTiling() const;

  /** \details
    Retrieves the current type of Y-axis tiling for the texture mapper object.
    
    \returns Returns the current type of Y-axis tiling.
  */
  Tiling vTiling() const;

  /** \details
    Retrieves the current transformation matrix for the texture mapper object.
    
    \returns Returns the current transformation matrix represented with an <link OdTvMatrix, OdTvMatrix> object.
  */
  const OdTvMatrix& transform() const;

  /** \details
    Applies a new transformation matrix to the texture mapper object.
    
    \param tm [in] An <link OdTvMatrix, OdTvMatrix> object that represents a new transformation matrix to be set.
  */
  void setTransform(const OdTvMatrix &tm);

  /** \details
    Sets a new texture sample size.
    
    \param dWidth   [in] A new width value to be set; corresponds to the U-value.
    \param dHeight  [in] A new height value to be set; corresponds to the V-value.
  */
  void setSampleSize(double dWidth, double dHeight);

  /** \details
    Sets new texture offsets for the mapper object.
    
    \param u [in] A new offset value along the X-axis to be set.
    \param v [in] A new offset value along the Y-axis to be set.
  */
  void setOffset(double u, double v);

  /** \details
    Sets a new rotation angle. The method rotates the texture around the U-axis and V-axis.
    
    \param dAngle [in] A new rotation angle value to be set.
  */
  void setRotation(double dAngle);

//DOM-IGNORE-BEGIN
private:
  Tiling        m_uTiling;
  Tiling        m_vTiling;
  OdTvMatrix    m_transform;
//DOM-IGNORE-END
};

/** \details
  The base interface class for color management of Visualize SDK material entities.
  \sa
  <link tv_working_with_attributes_materials_color, Work with Color Properties of Materials>
*/
class ODTV_EXPORT OdTvMaterialColor
{
public:

  /** \details
    Creates a new material color object.
  */
  OdTvMaterialColor();
  
  /** \details
    Creates a new material color object with parameters defined in a specified <link OdTvColorDef, color definition> object.
    
    \param overrideColor [in] A color definition object. 
  */
  OdTvMaterialColor(const OdTvColorDef& overrideColor);

  /** \details
    Coloring methods used by the <link OdTvMaterialColor::setMethod@Method, setMethod()> and <link OdTvMaterialColor::getMethod@OdTvResult*@const, getMethod()> methods.
  */
  enum Method
  {
    kInherit = 0, // Uses the current drawing color.
    kOverride = 1 // Uses the color set with the <link OdTvMaterialColor::setColor@OdTvColorDef &, setColor()> method.
  };

  /** \details
    Sets a new color method for the material color object.
    
    \param method [in] A new color method to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new color method was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMethod(Method method);

  /** \details
    Retrieves the current color method used for the material color object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current <link OdTvMaterialColor::Method, color method>.
    \remarks 
    If the rc parameter is not null and the current color method was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual Method getMethod(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new color factor value for the material color object.
    
    \param dFactor [in] A new color factor value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new color factor value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFactor(double dFactor);

  /** \details
    Retrieves the current color factor value used for the material color object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current color factor represented with a double value.
    \remarks 
    If the rc parameter is not null and the current color factor value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getFactor(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new color for the material color object.
    
    \param color [in] A <link OdTvColorDef, color definition> object that represents a new color to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setColor(const OdTvColorDef &color);

  /** \details
    Retrieves the current color used for the material color object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvColorDef, color definition> object that represents the current color.
    \remarks 
    If the rc parameter is not null and the current color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvColorDef getColor(OdTvResult* rc = NULL) const;

  /** \details 
    The equal operator for two material color objects.
    
    \param other [in] Another material color object to be compared with this color material object.
    \returns Returns true if the material color objects are equal; otherwise the method returns false.
  */
  bool operator ==(const OdTvMaterialColor &other) const
  {
    return (m_method == other.m_method) &&
      (m_factor == other.m_factor) &&
      (m_color == other.m_color);
  }

  /** \details 
    The non-equal operator for two material color objects.
    
    \param other [in] Another material color object to be compared with this color material object.
    \returns Returns true if the material color objects are not equal; otherwise the method returns false.
  */
  bool operator != (const OdTvMaterialColor &other) const
  {
    return (m_method != other.m_method) ||
      (m_factor != other.m_factor) ||
      (m_color != other.m_color);
  }

//DOM-IGNORE-BEGIN
private:
  Method          m_method;
  double          m_factor;
  OdTvColorDef    m_color;
//DOM-IGNORE-END
};

/** \details
  A data type that represents a smart pointer to an <link OdTvMaterialColor, OdTvMaterialColor> object.
*/
typedef OdSmartPtr<OdTvMaterialColor> OdTvMaterialColorPtr;

/** \details
  The base interface class that implements handling a map of Visualize SDK material entities.
  \sa
  <link tv_working_with_attributes_materials_mapping, Overview of Mapping Properties>
*/
class ODTV_EXPORT OdTvMaterialMap
{
public:

  /** \details 
    Creates a new material map object.
  */
  OdTvMaterialMap();

  /** \details
    Types of the material map source (file or raster image).
  */
  enum SourceType
  {
    kUnknown = -1,  // An unknown source.
    kFile = 0,      // A file.
    kRaster = 1     // A raster image.
  };

  /** \details
    Retrieves the current source type for the material map.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a value of the <link OdTvMaterialMap::SourceType, SourceType> enumeration that represents the current source type.
    \remarks 
    If the rc parameter is not null and the source type value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual SourceType getSourceType(OdTvResult* rc = NULL) const;

  /** \details
    Sets a new source filename for the material map object.
    
    \param sFilename [in] A string that contains the source filename to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new source filename was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSourceFileName(const OdString& sFilename);

  /** \details
    Retrieves the current source filename for the material map object.
    
    \returns Returns a string that contains the current source filename.
  */
  virtual OdString getSourceFileName() const;

  /** \details
    Sets a new raster image as a source of the material map object.
    
    \param rasterImageId [in] An identifier of the <link OdTvRasterImage, Visualize SDK raster image> object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new source raster image object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSourceRasterImage(OdTvRasterImageId rasterImageId);

  /** \details
    Retrieves the current source raster image object for the material map object.
    
    \returns Returns an identifier of the current source <link OdTvRasterImage, raster image> object.
  */
  virtual OdTvRasterImageId getSourceRasterImage() const;

  /** \details
    Sets a new blend factor value for the material map object.
    
    \param dBlendFactor [in] A new blend factor value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new blend factor value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */ 
  virtual OdTvResult setBlendFactor(double dBlendFactor);

  /** \details
    Retrieves current blend factor value for the material map object.
    
    \returns Returns current blend factor value.
  */
  virtual double getBlendFactor() const;

  /** \details
    Sets a new <link OdTvTextureMapper, material mapper> object for the material map object.
    
    \param pMapper [in] A new <link OdTvTextureMapper, material mapper> object to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new <link OdTvTextureMapper, material mapper> object was successfully set, the method returns tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMapper(const OdTvTextureMapper& pMapper);

  /** \details
    Retrieves the current <link OdTvTextureMapper, material mapper> object for the material map object.
    
    \returns Returns the current <link OdTvTextureMapper, material mapper> object.
  */
  virtual OdTvTextureMapper getMapper() const;

//DOM-IGNORE-BEGIN
private:
  SourceType        m_source;
  OdString          m_fileName;
  OdTvRasterImageId m_rasterImageId;
  double            m_blendFactor;
  OdTvTextureMapper m_mapper;
//DOM-IGNORE-END
};

/** \details
  A data type that represents a smart pointer to an <link OdTvMaterialMap, OdTvMaterialMap> object.
*/
typedef OdSmartPtr<OdTvMaterialMap> OdTvMaterialMapPtr;

#include "TD_PackPop.h"

#endif // _ODTV_MATERIALTRAITS_H_INCLUDED_

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

#ifndef _PRCMARKUPTESSBUF_INCLUDED_
#define _PRCMARKUPTESSBUF_INCLUDED_ 
 

#include "PrcPicturePattern.h"
#include "PrcMarkupTessBufBase.h"

/** \details 
<group PRC_Markup_Classes> 
Class stores information about a three-dimensional point. Coordinates of the point are represented in float format.
*/
class OdPrcFloatPoint
{
public:

  /** \details 
  Created a new float three-dimensional point with default coordinates (0.0, 0.0, 0.0).
  */
  OdPrcFloatPoint() 
    : x (0.0), y (0.0), z (0.0)
  {
  }

  /** \details 
  Created a new float three-dimensional point with specified coordinates.
  \param xx [in] An X-axis coordinate of the point.
  \param yy [in] An Y-axis coordinate of the point.
  \param zz [in] An Z-axis coordinate of the point.
  */
  OdPrcFloatPoint(
    float xx, 
    float yy, 
    float zz)
    : x (xx), y (yy), z (zz)
  {
  }

  /** \details 
  Sets new coordinates for the float three-dimensional point.
  \param xx [in] An X-axis coordinate of the point.
  \param yy [in] An Y-axis coordinate of the point.
  \param zz [in] An Z-axis coordinate of the point.
  \returns Returns a reference to the point with new coodinates.
  */
  OdPrcFloatPoint& set(
    double xx, 
    double yy, 
    double zz)
  {
    x = xx;
    y = yy;
    z = zz;
    return *this;
  }
  float x; // X-coordinate
  float y; // Y-coordinate
  float z; // Z-coordinate
};

/** \details
  A data type that represents an array of float three-dimensional points.
*/
typedef OdArray<OdPrcFloatPoint, OdMemoryAllocator<OdPrcFloatPoint> > OdPrcFloatPointArray;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for a block of tessellation entities.  
*/
class PRC_TOOLKIT OdPrcMarkupTessBufBlock : public OdPrcMarkupTessBuf
{
private:
  OdPrcMarkupTessBufPtr m_pNextInBlock;   // Smart pointer to another instance in a block for attaching in a sequence

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufBlock);
  //DOM-IGNORE-END
  
  /** \details
      Destroys the markup tessellation block buffer. 
  */
  virtual ~OdPrcMarkupTessBufBlock();

  /** \details
    Returns a smart-pointer to the next entity in the block. 
  */
  OdPrcMarkupTessBufPtr nextInBlock() const;

  /** \details
    Sets a new entity next in the tessellation block buffer. 

    \param pMkpTessBuf [in] A pointer to the new markup tessellation entity next in the block. 

    \returns Returns a smart pointer to the new tessellation buffer next in the block. 
  */
  OdPrcMarkupTessBufPtr setNextInBlock(OdPrcMarkupTessBuf* pMkpTessBuf);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufBlock object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufBlock> OdPrcMarkupTessBufBlockPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for a polyline.  
*/
class PRC_TOOLKIT OdPrcMarkupTessBufPolyline : public OdPrcMarkupTessBuf
{
private:
  OdPrcFloatPointArray m_Points;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufPolyline);
  //DOM-IGNORE-END

  /** \details
    Returns the polyline points. 
  */
  const OdPrcFloatPointArray &getPoints() const;

  /** \details
    Sets a new array of polyline points. 

    \param points [in] A new array of points. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPoints(const OdPrcFloatPointArray &points);

  /** \details
    Sets a new array of polyline points. 

    \param points     [in] A new array of points represented as a heap pointer. 
    \param numPoints  [in] Quantity of points in the specified array. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPoints(const OdPrcFloatPoint *points, OdUInt32 numPoints);

  /** \details
    Sets a new array of polyline points. 

    \param points     [in] A new array of points represented as a float array. 
    \param numPoints  [in] Quantity of points in the specified array. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPoints(const float *points, OdUInt32 numPoints);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufPolyline object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufPolyline> OdPrcMarkupTessBufPolylinePtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for a matrix.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufMatrix : public OdPrcMarkupTessBufBlock
{
private:
  OdGeMatrix3d m_Matr;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufMatrix);
  //DOM-IGNORE-END

  /** \details
    Returns the current markup tessellation matrix. 
  */
  const OdGeMatrix3d &getMatrix() const;

  /** \details
    Sets a new markup tessellation matrix. 

    \param matr [in] A new matrix to be set as a tessellation buffer. 
  */
  void setMatrix(const OdGeMatrix3d &matr);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufMatrix object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufMatrix> OdPrcMarkupTessBufMatrixPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for triangles.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufTriangles : public OdPrcMarkupTessBuf
{
private:
  OdPrcFloatPointArray m_Points;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufTriangles);
  //DOM-IGNORE-END

  /** \details
    Returns the current tessellation triangles as an OdPrcFloatPointArray object. 
  */
  const OdPrcFloatPointArray &getTriangles() const;

  /** \details
    Sets new tessellation triangles. 

    \param points [in] A 3D point array that represents tessellation triangles. 

    \returns Returns eOk if new triangles have been successfully set. 
  */
  OdResult setTriangles(const OdPrcFloatPointArray &points);

  /** \details
    Sets new tessellation triangles. 

    \param points     [in] A 3D point array that represents tessellation triangles. 
    \param numPoints  [in] Quantity of triangle points. 

    \returns Returns eOk if new triangles have been successfully set. 
  */
  OdResult setTriangles(const OdPrcFloatPoint *points, OdUInt32 numPoints);

  /** \details
    Sets new tessellation triangle points. 

    \param points     [in] A float array that represents tessellation triangle points. 
    \param numPoints  [in] Quantity of triangle points. 

    \returns Returns eOk if new triangles have been successfully set. 
  */
  OdResult setTriangles(const float *points, OdUInt32 numPoints);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufTriangles object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufTriangles> OdPrcMarkupTessBufTrianglesPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for frames.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufFrame : public OdPrcMarkupTessBufBlock
{
private:
  OdPrcFloatPoint m_Position;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufFrame);
  //DOM-IGNORE-END

  /** \details
    Returns the current tessellation frame position. 
  */
  const OdPrcFloatPoint &getPosition() const;

  /** \details
    Sets a new tessellation frame position. 

    \param pos [in] A 3D point that specifies a new tessellation frame's position. 
  */
  void setPosition(const OdPrcFloatPoint &pos);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufFrame object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufFrame> OdPrcMarkupTessBufFramePtr;

/** \details
<group PRC_Markup_Classes>

Class implements a markup tessellation buffer for face view mode.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufFaceView : public OdPrcMarkupTessBufBlock
{
private:
  OdPrcFloatPoint m_Position;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufFaceView);
  //DOM-IGNORE-END

  /** \details
  Returns the current tessellation position.
  */
  const OdPrcFloatPoint &getPosition() const;

  /** \details
  Sets a new tessellation position.

  \param pos [in] A 3D point that specifies a new tessellation position.
  */
  void setPosition(const OdPrcFloatPoint &pos);
};

/** \details
A specialization of the OdSmartPtr class for OdPrcMarkupTessBufFaceView object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufFaceView> OdPrcMarkupTessBufFaceViewPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for fixed sized entities in blocks.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufFixedSize : public OdPrcMarkupTessBufBlock
{
private:
  OdPrcFloatPoint m_Position;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufFixedSize);
  //DOM-IGNORE-END

  /** \details
    Returns the current position of a tessellation fixed sized entity. 
  */
  const OdPrcFloatPoint &getPosition() const;

  /** \details
    Sets a new position of a tessellation fixed sized entity. 
    \param pos [in] A 3D point that specifies a new position. 
  */
  void setPosition(const OdPrcFloatPoint &pos);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufFixedSize object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufFixedSize> OdPrcMarkupTessBufFixedSizePtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for symbols.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufSymbol : public OdPrcMarkupTessBuf
{
private:
  OdPrcFloatPoint        m_Position;
  OdPrcPicturePatternPtr m_pPicPattern;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufSymbol);
  //DOM-IGNORE-END

  /** \details
    Returns the current tessellation symbol position. 
  */
  const OdPrcFloatPoint &getPosition() const;

  /** \details
    Sets a new position of a tessellation symbol. 
    \param pos [in] A 3D point that specifies a new position. 
  */
  void setPosition(const OdPrcFloatPoint &pos);

  /** \details
    Returns the current picture pattern for the tessellation symbol. 
  */
  const OdPrcPicturePatternPtr &getPicPattern() const;

  /** \details
    Sets a new picture pattern of the tessellation symbol. 
    \param pPicPattern [in] A reference to a pointer to an OdPrcPicturePattern object to be set as a new picture pattern. 

    \returns Returns eOk if a new picture pattern has been successfully set. 
  */
  OdResult setPicPattern(const OdPrcPicturePatternPtr &pPicPattern);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufSymbol object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufSymbol> OdPrcMarkupTessBufSymbolPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for cylinders.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufCylinder : public OdPrcMarkupTessBuf
{
private:
  float m_BaseRadius;
  float m_TopRadius;
  float m_Height;

protected:
  OdPrcMarkupTessBufCylinder();

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufCylinder);
  //DOM-IGNORE-END

  /** \details 
    Returns the current value of the tessellation cylinder's base radius. 
  */
  float getBaseRadius() const;

  /** \details 
    Returns the current value of the tessellation cylinder's top radius. 
  */
  float getTopRadius() const;

  /** \details 
    Returns the current value of the tessellation cylinder's height.
  */
  float getHeight() const;

  /** \details 
    Sets a new tessellation cylinder. 
    \param baseRadius [in] A base radius of a new tessellation cylinder.
    \param topRadius  [in] A top radius of a new tessellation cylinder.
    \param height     [in] A height of a new tessellation cylinder.

    \returns Returns eOk if a new tessellation cylinder has been successfully added to the buffer. 
  */
  OdResult setCylinder(float baseRadius, float topRadius, float height);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufCylinder object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufCylinder> OdPrcMarkupTessBufCylinderPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for colors.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufColor : public OdPrcMarkupTessBuf
{
private:
  OdPrcRgbColor m_Color;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufColor);
  //DOM-IGNORE-END

  /** \details 
    Returns the current markup tessellation color. 
  */
  const OdPrcRgbColor &getColor() const;

  /** \details 
    Sets a new markup tessellation color. 
    \param color [in] A new markup tessellation color. 
  */
  void setColor(const OdPrcRgbColor &color);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufColor object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufColor> OdPrcMarkupTessBufColorPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for fonts.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufFont : public OdPrcMarkupTessBuf
{
private:
  OdPrcFontKeysSameFont m_Font;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufFont);
  //DOM-IGNORE-END

  /** \details 
    Returns the current markup tessellation font from the buffer. 
  */
  const OdPrcFontKeysSameFont &getFont() const;

  /** \details 
    Sets a new markup tessellation font to the buffer. 
    \param font [in] A new markup tessellation font. 

    \returns Returns eOk if a new font has been successfully added to the tessellation buffer. 
  */
  OdResult setFont(const OdPrcFontKeysSameFont &font);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufFont object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufFont> OdPrcMarkupTessBufFontPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for text.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufText : public OdPrcMarkupTessBuf
{
private:
  float   m_Width;
  float   m_Height;
  OdString m_Text;

protected:
  OdPrcMarkupTessBufText();

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufText);
  //DOM-IGNORE-END

  /** \details 
    Returns the current value of the text width. 
  */
  float getWidth() const;

  /** \details 
    Returns the current value of the text height. 
  */
  float getHeight() const;

  /** \details 
    Returns the current tessellation text. 
  */
  const OdString &getText() const;

  /** \details 
    Sets a new markup tessellation text and its width and height.
    \param text   [in] A new markup tessellation text. 
    \param width  [in] A new markup tessellation text width. 
    \param height [in] A new markup tessellation text height. 

    \returns Returns eOk if new text and its parameters have been successfully set. 
  */
  OdResult setText(const OdString &text, float width, float height);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufText object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufText> OdPrcMarkupTessBufTextPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for point sets.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufPoints : public OdPrcMarkupTessBuf
{
private:
  OdPrcFloatPointArray m_Points;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufPoints);
  //DOM-IGNORE-END

  /** \details 
    Returns the current array of 3D points from the markup tessellation buffer. 
  */
  const OdPrcFloatPointArray &getPoints() const;

  /** \details 
    Sets a new markup tessellation point array.
    \param points [in] A new markup tessellation 3D point array. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPoints(const OdPrcFloatPointArray &points);

  /** \details 
    Sets a new markup tessellation point array.
    \param points     [in] A new markup tessellation 3D point array. 
    \param numPoints  [in] Quantity of points in a new array. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPoints(const OdPrcFloatPoint *points, OdUInt32 numPoints);

  /** \details 
    Sets a new markup tessellation point array.
    \param points     [in] A new markup tessellation point array represented as a float array. 
    \param numPoints  [in] Quantity of points in a new array. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPoints(const float *points, OdUInt32 numPoints);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufPoints object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufPoints> OdPrcMarkupTessBufPointsPtr;

/** \details
  <group PRC_Markup_Classes> 

  Class implements a markup tessellation buffer for polygons.
*/
class PRC_TOOLKIT OdPrcMarkupTessBufPolygon : public OdPrcMarkupTessBuf
{
private:
  OdPrcFloatPointArray m_Points;

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBufPolygon);
  //DOM-IGNORE-END

  /** \details 
    Returns the current polygon as an array of 3D points. 
  */
  const OdPrcFloatPointArray &getPolygon() const;

  /** \details 
    Sets a new markup tessellation polygon.
    \param points     [in] A new markup tessellation polygon represented as a 3D points array. 

    \returns Returns eOk if a new polygon has been successfully set.
  */
  OdResult setPolygon(const OdPrcFloatPointArray &points);

  /** \details 
    Sets a new markup tessellation polygon.
    \param points     [in] A new markup tessellation polygon represented as a 3D points array. 
    \param numPoints  [in] Quantity of points in a new polygon. 

    \returns Returns eOk if a new point array has been successfully set. 
  */
  OdResult setPolygon(const OdPrcFloatPoint *points, OdUInt32 numPoints);

  /** \details 
    Sets a new markup tessellation polygon.
    \param points     [in] A new markup tessellation polygon represented as a float array. 
    \param numPoints  [in] Quantity of points in a new polygon. 

    \returns Returns eOk if a new polygon has been successfully set. 
  */
  OdResult setPolygon(const float *points, OdUInt32 numPoints);
};

/** \details
  A specialization of the OdSmartPtr class for OdPrcMarkupTessBufPolygon object pointers.
*/
typedef OdSmartPtr<OdPrcMarkupTessBufPolygon> OdPrcMarkupTessBufPolygonPtr;

#endif // _PRCMARKUPTESSBUF_INCLUDED_


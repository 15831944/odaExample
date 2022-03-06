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

#ifndef _PDF_2D_EXPORT_GS_CACHE_RECORDS_INCLUDED_
#define _PDF_2D_EXPORT_GS_CACHE_RECORDS_INCLUDED_

#if _MSC_VER > 1000
#pragma once 
#endif // _MSC_VER > 1000

#include "OdPlatform.h"

#include "Gi/GiMetafiler.h"
#include "Pdf2dExportDevice.h"
//////////////////////////////////////////////////////////////////////

/** \details
  Contains declarations for 2D PDF Export.
  <group OdExport_Classes> 
*/
namespace TD_PDF_2D_EXPORT {

  class PDF2dExportView;
  
  /** \details 
  A structure that stores information about a raster image.
  */
  struct ImageData
  {
    /** The origin point of the image.*/
    OdGePoint3d m_origin;
    /** The u-vector of the image.*/
    OdGeVector3d m_uVec;
    /** The v-vector of the image.*/
    OdGeVector3d m_vVec;
    /** A smart pointer to the raster image object.*/
    OdGiRasterImagePtr m_pImage;
  };
  
  /** \details 
  A data type definition that represents a one-dimensional array (vector) of images data.
  */
  typedef OdVector<ImageData> ImageArray;

  /** \details 
  A class that implements record for a color bitmap DPI.
  */
  class RecColorBitmapDPI: public OdGiGeometryMetafile::Record
  {
  public:
    /** \details 
    Creates a new instance of the color bitmap DPI record object.
    \param value [in] A DPI value to be recorded.
    */
    RecColorBitmapDPI(OdUInt16 value): m_value(value) {}
    
    /** \details 
    Sets the DPI value for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }

    //DOM-IGNORE-BEGIN
  private:
    OdUInt16 m_value;
    //DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of a polygon fill rule in a metafile.
  */
  class RecFillRule : public OdGiGeometryMetafile::Record
  {
  public:
    /** \details 
    Creates a new instance of the fill rule recording object.
    \param fillRule [in] An instance of the PDF2dExportGeometry::PolygonFillRules value that represents polygon fill rules.
    */
    RecFillRule(PDF2dExportGeometry::PolygonFillRules fillRule)
      : m_fillRule(fillRule)
    {}
    
    /** \details 
    Sets the polygon fill rule for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }

//DOM-IGNORE-BEGIN
  private:
    PDF2dExportGeometry::PolygonFillRules m_fillRule;
//DOM-IGNORE-END
  };

  /** \details 
  A class that implements recording of a hidden text in a metafile.
  */
  class RecHiddenText : public OdGiGeometryMetafile::Record
  {
  public:
    /** \details 
    Creates a new instance of the hidden text recording object.
    \param bOn [in] A flag that determines whether the text is hidden (if equals to true) or not (if equals to false).
    */
    RecHiddenText(bool bOn)
      : m_hidden(bOn)
    {}

    /** \details 
    Sets the hidden text for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;

    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }

  //DOM-IGNORE-BEGIN
  private:
    bool m_hidden;
  //DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of a contour fill rule in a metafile.
  */
  class RecFillContour : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the fill rule recording object.
    */
    RecFillContour() {}
    
    /** \details 
    Sets the contour fill rule for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }
  };

  /** \details
  A class that implements recording of a drawing contour fill rule in a metafile.
  */
  class RecDrawingContour : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the drawing contour fill rule recording object.
    \param bStart [in] A flag value that determines the start flag.
    */
    RecDrawingContour(bool bStart) : m_bStart(bStart) {}
    
    /** \details 
    Sets the drawing contour fill rule for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }

    /** \details 
      Requests the start flag.
      \return true if contour redrawing is started; otherwise, the method returns false.
      \remarks 
      For internal (debugging) purposes only. Do not use it in your applications.
    */
    bool isStart() const { return m_bStart; } 
    
//DOM-IGNORE-BEGIN
  private:
    bool m_bStart;
//DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of a hatch drawing mode in a metafile.
  */
  class RecHatchDrawingMode : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the hatch drawing mode recording object.
    \param bMode [in] A flag value that determines the mode flag.
    */
    RecHatchDrawingMode(bool bMode) : m_bMode(bMode) {}
    
    /** \details 
    Sets the hatch drawing mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }
    
//DOM-IGNORE-BEGIN
  private:
    bool m_bMode;
//DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of a viewport clip command in a metafile.
  */  
  class RecEnableClipper : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the viewport clipping mode recording object.
    \param bEnable [in] A flag value that determines whether the viewport clipping is enabled (true) or not (false).
    */
    RecEnableClipper(bool bEnable) : m_bEnable(bEnable) {}
    
    /** \details 
    Sets the viewport clipping mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }
    
//DOM-IGNORE-BEGIN
  private:
    bool m_bEnable;
//DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of a disable color merge command in a metafile.
  */
  class RecDisableColorMerge : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the disable color merge command recording object.
    */
    RecDisableColorMerge() {};
    
    /** \details 
    Sets the disable color merge record mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }
  };

  /** \details
  A structure that stores and operates hyperlink data.
  */
  struct HyperlinkData
  {
    /** \details
    Creates a new hyperlink data instance with default parameters.
    */
    HyperlinkData() :
      m_bInternal(false), m_page(-1) {}
    
    /** \details
    Creates a new hyperlink data instance with specified parameters.
    \param link      [in] A string that contains the link address.
    \param bInternal [in] A flag that defines whether the hyperlink is internal (if equals true) or not (if equals false).
    \param layer     [in] A string that contains the name of the layer.
    \param pageIndex [in] An index of the page (for internal links).
    */
    HyperlinkData(const OdString& link, bool bInternal, const OdString& layer, OdInt32 pageIndex) :
      m_link(link), m_bInternal(bInternal), m_layer(layer), m_page(pageIndex) {}
      
    /** \details
    Creates a new hyperlink data instance as a copy of another existing hyperlink data object.
    \param o [in] Another hyperlink data object to copy.
    */
    HyperlinkData(const HyperlinkData& o) : m_link(o.m_link), m_bInternal(o.m_bInternal), m_layer(o.m_layer), m_page(o.m_page) {}

    /**A hyperlink address.*/
    OdString m_link;

    /**A name of the layer that contains the hyperlink.*/
    OdString m_layer;

    /**An index of the page in resulting pdf (for internal links).*/
    OdInt32 m_page;

    /**A flag that defines whether the hyperlink is internal (if equals true) or not (if equals false).*/
    bool m_bInternal;

    /** \details 
      Requests the size of the hyperlink data object in bytes.
      \return An unsigned 64-bit integer value that contains the size of hyperlink data in bytes.
    */
    OdUInt64 size() const
    {
      return (OdUInt64)sizeof(*this) + (OdUInt64)((m_link.getLength() + 1) * sizeof(OdChar)) + (OdUInt64)((m_layer.getLength() + 1) * sizeof(OdChar));
    }
  };

  /** \details
  A class that implements recording of a hyperlink data to a metafile.
  */
  class RecHyperlink : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the hyperlink data recording object.
    \param data [in] A hyperlink data object to record.
    */
    RecHyperlink(const HyperlinkData& data) : m_data(data) {}
    
    /** \details 
    Sets the hyperlink record mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;

    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const
    {
      return Record::recordSize() + m_data.size();
    }
    
  //DOM-IGNORE-BEGIN
  private:
    const HyperlinkData m_data;
  //DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of a text annotation to a metafile.
  */
  class RecTextAnnot : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the text annotation recording object.
    \param text  [in] A string that contains the annotation text.
    \param layer [in] A string that contains the name of the text annotation's layer.
    */
    RecTextAnnot(const OdString& text, const OdString& layer) :
      OdGiGeometryMetafile::Record(), m_text(text), m_layer(layer) {}
      
    /** \details 
    Sets the text annotation record mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
    /** \details 
    Retrieves the record size. 
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const
    {
      return Record::recordSize() + (OdUInt64)((m_text.getLength() + 1)*sizeof(OdChar)) + (OdUInt64)((m_layer.getLength() + 1) * sizeof(OdChar));
    }

  //DOM-IGNORE-BEGIN
  private:
    OdString m_text;
    OdString m_layer;
  //DOM-IGNORE-END
  };

  /** \details
  A class that implements a record for a hatch, that is represented as a bitmap, to a metafile.
  */
  class RecHatchAsBitmap : public OdGiGeometryMetafile::Record
  {
  public:
  
    /** \details 
    Creates a new instance of the hatch record object.
    \param nbVertex     [in] A number of vertices.
    \param pVertexList  [in] A raw pointer to an array of verticies.
    \param faceListSize [in] A size of the faces list.
    \param pFaceList    [in] A raw pointer to the indexes of verticies that form faces.
    \param pEdgeData    [in] A raw pointer to edges data.
    \param pFaceData    [in] A raw pointer to the faces data.
    \param pVertexData  [in] A raw pointer to the verticies data.
    */
    RecHatchAsBitmap(OdInt32 nbVertex,
      const OdGePoint3d* pVertexList,
      OdInt32 faceListSize,
      const OdInt32* pFaceList,
      const OdGiEdgeData* pEdgeData,
      const OdGiFaceData* pFaceData,
      const OdGiVertexData* pVertexData) :
      OdGiGeometryMetafile::Record(), m_shell(nbVertex,
        pVertexList, faceListSize, pFaceList,
        pEdgeData, pFaceData, pVertexData), m_bImageCreated(false) {}

    /** \details
    Sets the hatch record mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;

    /** \details
    Retrieves the record size.
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }
    
    /** \details 
      Creates an image for a conveyor context.
      \param extents [in] An image extents object.
      \param vect    [in] An export view to use for the image creation.
    */
    void createImage(const OdGeExtents3d& extents, PDF2dExportView& vect) const;

    //DOM-IGNORE-BEGIN
  private:
    OdGiShell m_shell;
    mutable ImageArray m_images;
    mutable bool m_bImageCreated;
    //DOM-IGNORE-END
  };

  /** \details
  A class that implements record for a drawing device context data.
  */
  class RecOwnerDrawDc: public OdGiGeometryMetafile::Record
  {
  public:
    /** \details 
    Creates a new instance of the drawing device context data record object.
    \param org            [in] An origin point of the device context.
    \param u              [in] A u-vector object.
    \param v              [in] A v-vector object.
    \param pDrawable      [in] A raw pointer to the self-drawable object.
    \param bDcAligned     [in] A device context alingment flag value.
    \param bAllowClipping [in] A flag value that determines whether the clipping is allowed (true) or not (false).
    */
    RecOwnerDrawDc(const OdGePoint3d& org,
      const OdGeVector3d& u,
      const OdGeVector3d& v,
      const OdGiSelfGdiDrawable* pDrawable,
      bool bDcAligned,
      bool bAllowClipping):
      OdGiGeometryMetafile::Record(), m_origin(org), m_u(u), m_v(v),
        m_pDrawable(pDrawable), m_bDcAligned(bDcAligned),
        m_bAllowClipping(bAllowClipping), m_bImageCached(false){}

    /** \details
    Sets the device context record mode for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;

    /** \details
    Retrieves the record size.
    \returns A 64-bit unsigned integer value that contains the record size in bytes.
    */
    virtual OdUInt64 recordSize() const { return (OdUInt64)sizeof(*this); }

    //DOM-IGNORE-BEGIN
  private:
    OdGePoint3d m_origin;
    OdGeVector3d m_u, m_v;
    OdSmartPtr<OdGiSelfGdiDrawable> m_pDrawable;
    bool m_bDcAligned;
    bool m_bAllowClipping;
    mutable bool m_bImageCached;
    mutable ImageData m_img;
    //DOM-IGNORE-END
  };

  /** \details
  A class that implements recording of an obscured color to a metafile.
  */
  class RecTraitsObscuredColor : public OdGiGeometryMetafile::Record
  {
  public:
    /** \details
    Creates a new instance of metafile record with a specified color.
    \param clr [in] A color for the metafile record object.
    */
    RecTraitsObscuredColor(const OdCmEntityColor& clr) : m_clr(clr) {}

    /** \details
    Sets the obscured color for the specified geometry and conveyor context.
    \param pGeom [in] A raw pointer to the geometry.
    \param pCtx  [in] A raw pointer to the conveyor context object.
    */
    void play(OdGiConveyorGeometry* pGeom, OdGiConveyorContext* pCtx) const ODRX_OVERRIDE;
    
//DOM-IGNORE-BEGIN
  protected:
    const OdCmEntityColor m_clr;
//DOM-IGNORE-END
  };

}
#endif // #ifndef _PDF_2D_EXPORT_GS_CACHE_RECORDS_INCLUDED_

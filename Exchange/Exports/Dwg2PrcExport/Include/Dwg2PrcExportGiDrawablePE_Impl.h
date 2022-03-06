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



#ifndef _PDF_EXPORT_GIDRAWABLE_PE_IMPL_INCLUDED_
#define _PDF_EXPORT_GIDRAWABLE_PE_IMPL_INCLUDED_

#include "PdfExportGiDrawablePE.h"
#include "DbEntity.h"
#include "PrcBaseExportGiDrawablePE_Default.h"

// forward declaration
class OdBrBrep;

/** \details 
A protocol extension class that implements the functionality for exporting a layer table record to a PDF layer.

<group PRC_Export_Import_Classes>
*/
class PdfExportLayerPE_LayerTableRecord : public PdfExportLayerPE
{
  ODRX_DECLARE_MEMBERS(PdfExportLayerPE_LayerTableRecord);

  /** \details 
  Retrieves the current color used for exporting a layer to PDF format.
  \param pObj [in] A raw pointer to the layer table record to export.
  \returns Returns an OdCmEntityColor object that contains information about the currently used color.
  */
  virtual OdCmEntityColor getColor(const OdRxObject *pObj) const;
  
  /** \details 
  Retrieves the current material used for exporting a layer to PDF format.
  \param pObj [in] A raw pointer to the layer table record to export.
  \returns Returns a raw pointer to an OdDbStub object that contains information about the currently used material.
  */
  virtual OdDbStub * getMaterial(const OdRxObject *pObj) const;
  
  /** \details 
  Retrieves the current transparency level for exporting a layer to PDF format.
  \param pObj [in] A raw pointer to the layer table record to export.
  \returns Returns an OdCmTransparency object that contains information about the current transparency level.
  */
  virtual OdCmTransparency getTransparency(const OdRxObject *pObj) const;
};

/** \details 
A protocol extension class that implements the PDF export of a Gi drawable entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Entity : public PdfExportGiDrawablePE_Default
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Entity);
  //DOM-IGNORE-END

  /** \details 
  Retrieves the current color used for exporting a Gi drawable entity to PDF format.
  \param pDrawable [in] A raw pointer to the Gi drawable entity to export.
  \returns Returns an OdCmEntityColor object that contains information about the currently used color.
  */
  virtual OdCmEntityColor getColor(const OdGiDrawable *pDrawable) const;
  
  /** \details 
  Retrieves the current material used for exporting a Gi drawable entity to PDF format.
  \param pDrawable [in] A raw pointer to the Gi drawable entity to export.
  \returns Returns a raw pointer to an OdDbStub object that contains information about the currently used material.
  */
  virtual OdDbStub * getMaterial(const OdGiDrawable *pDrawable) const;
  
  /** \details 
  Retrieves the current transparency level for exporting a Gi drawable entity to PDF format.
  \param pDrawable [in] A raw pointer to the Gi drawable entity to export.
  \returns Returns an OdCmTransparency object that contains information about the current transparency level.
  */
  virtual OdCmTransparency getTransparency(const OdGiDrawable *pDrawable) const;
};

/** \details 
An abstract protocol extension class that implements a common interface for PDF export of B-Rep objects.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Solid_IFace : public PdfExportGiDrawablePE_Entity
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Solid_IFace);
  //DOM-IGNORE-END

  /** \details
  Exports a specified B-Rep object to PRC format.
  \param pDrawable     [in] A raw pointer to the B-Rep entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param context       [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the B-Rep entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC (const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *context
    ) const;

  /**
  Retrieves B-Rep object from a specified drawable entity.
  \param pDrawable [in] A raw pointer to the drawable entity.
  \param brep      [out] A placeholder for a B-Rep object.
  \remarks
  The method fills the passed OdBrBrep object and returns it to a calling subroutine.
  */
  virtual void GetBrep (const OdGiDrawable *pDrawable, OdBrBrep &brep) const = 0;
};

/** \details 
A protocol extension class that implements PDF export of a 3D solid entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_3dSolid : public PdfExportGiDrawablePE_Solid_IFace
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_3dSolid);
  //DOM-IGNORE-END

  /**
  Retrieves B-Rep object from a specified 3D solid entity.
  \param pDrawable [in] A raw pointer to the 3D solid entity.
  \param brep      [out] A placeholder for a B-Rep object.
  \remarks
  The method fills the passed OdBrBrep object and returns it to a calling subroutine.
  */
  virtual void GetBrep (const OdGiDrawable *pDrawable, OdBrBrep &brep) const;
};

/** \details 
A protocol extension class that implements PDF export of a region entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Region : public PdfExportGiDrawablePE_Solid_IFace
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Region);
  //DOM-IGNORE-END

  /**
  Retrieves B-Rep object from a specified region entity.
  \param pDrawable [in] A raw pointer to the region entity.
  \param brep      [out] A placeholder for a B-Rep object.
  \remarks
  The method fills the passed OdBrBrep object and returns it to a calling subroutine.
  */
  virtual void GetBrep (const OdGiDrawable *pDrawable, OdBrBrep &brep) const;
};

/** \details 
A protocol extension class that implements PDF export of a surface entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Surface : public PdfExportGiDrawablePE_Solid_IFace
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Surface);
  //DOM-IGNORE-END

  /**
  Retrieves B-Rep object from a specified surface entity.
  \param pDrawable [in] A raw pointer to the surface entity.
  \param brep      [out] A placeholder for a B-Rep object.
  \remarks
  The method fills the passed OdBrBrep object and returns it to a calling subroutine.
  */
  virtual void GetBrep(const OdGiDrawable *pDrawable, OdBrBrep &brep) const;
};

/** \details 
A protocol extension class that implements PDF export of a body entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Body : public PdfExportGiDrawablePE_Solid_IFace
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Body);
  //DOM-IGNORE-END

  /**
  Retrieves B-Rep object from a specified body entity.
  \param pDrawable [in] A raw pointer to the body entity.
  \param brep      [out] A placeholder for a B-Rep object.
  \remarks
  The method fills the passed OdBrBrep object and returns it to a calling subroutine.
  */
  virtual void GetBrep (const OdGiDrawable *pDrawable, OdBrBrep &brep) const;
};

/** \details 
A protocol extension class that implements PDF export of a curve entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Curve : public PdfExportGiDrawablePE_Entity
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Curve);
  //DOM-IGNORE-END

  /** \details 
  Exports a specified line object to PRC format.
  \param pDrawable     [in] A raw pointer to the line entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param pContext      [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the line entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *pContext
    ) const;
};

/** \details 
A protocol extension class that implements PDF export of a line entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Line : public PdfExportGiDrawablePE_Curve
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Line);
  //DOM-IGNORE-END

  /** \details 
  Exports a specified line object to PRC format.
  \param pDrawable     [in] A raw pointer to the line entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param pContext      [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the line entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *pContext
    ) const;
};

/** \details 
A protocol extension class that implements PDF export of a circle entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Circle : public PdfExportGiDrawablePE_Curve
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Circle);
  //DOM-IGNORE-END

  /** \details
  Exports a specified circle object to PRC format.
  \param pDrawable     [in] A raw pointer to the circle entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param pContext      [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the circle entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *pContext
    ) const;
};

/** \details 
A protocol extension class that implements PDF export of a circleArc entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Arc : public PdfExportGiDrawablePE_Curve
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Arc);
  //DOM-IGNORE-END

  /** \details
  Exports a specified circle object to PRC format.
  \param pDrawable     [in] A raw pointer to the circle entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param pContext      [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the circle entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *pContext
    ) const;
};

/** \details 
A protocol extension class that implements PDF export of a polyline entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_Polyline : public PdfExportGiDrawablePE_Curve
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_Polyline);
  //DOM-IGNORE-END

  /** \details
  Exports a specified polyline object to PRC format.
  \param pDrawable     [in] A raw pointer to the polyline entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param pContext      [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the polyline entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *pContext
    ) const;
};

/** \details 
A protocol extension class that implements PDF export of a polyline entity.

<group PRC_Export_Import_Classes>
*/
class PdfExportGiDrawablePE_2dPolyline : public PdfExportGiDrawablePE_Curve
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(PdfExportGiDrawablePE_2dPolyline);
  //DOM-IGNORE-END

  /** \details
  Exports a specified polyline object to PRC format.
  \param pDrawable     [in] A raw pointer to the polyline entity to export.
  \param pPdfPrcParams [in] A raw pointer to an object that contains the set of export parameters.
  \param pContext      [in] A raw pointer to an object that contains the drawable context.
  \returns eOk if the polyline entity was successfully exported to PRC format; otherwise the method returns false.
  */
  virtual OdResult drawableToPRC(const OdGiDrawable *pDrawable,
    const PDF2PRCExportParams *pPdfPrcParams,
    OdRxObject *pContext
    ) const;
};

#endif

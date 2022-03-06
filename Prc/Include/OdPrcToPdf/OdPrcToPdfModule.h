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

#ifndef _PRCTOPDF_DEFINED_
#define _PRCTOPDF_DEFINED_

#include "PrcToPdfExportDef.h"
#include "RxModule.h"
#include "Ge/GeExtents3d.h"
#include "Ge/GeMatrix3d.h"
#include "Gs/GsPageParams.h"
#include "Pdf/Pdf3dEnums.h"

class OdPrcHostAppServices;

/** \details
Contains declarations for PRC to PDF conversion. 
*/
namespace PrcToPdf
{
  /** \details
  Enumerates camera conversion modes.
  */
  enum ConversionMode
  {
    defaultMode = 0,  //Default mode.
    cameraLeftMode,   //Camera from the left.
    cameraRightMode,  //Camera from the right.
    cameraTopMode,    //Camera from the top.
    cameraBottomMode, //Camera from the bottom.
    cameraFrontMode,  //Front camera mode.
    //DOM-IGNORE-BEGIN
    LAST,             //For internal use.
    //DOM-IGNORE-END
  };

  /** \details
  <group PRC_Export_Import_Classes>
  The structure that represents conversion parameters for exporting a PRC file content to a PDF file.
  */
  struct ConversionParams
  {
    bool isDefault;         //Flag which shows whether default conversion parameters are used.
    ConversionMode mode;    //Conversion mode.
    double modelScale;      //Scale for the model.
    double cameraZ;         //Camera shift for Z-axis.
    bool bExtentsMode;      //Flag which shows whether extents mode is used.
    OdGeExtents3d extents;  //Extents which are used if flag bExtentsMode is switched on.

    /** \details
    Creates a conversion parameters set by default: extents mode is false, model scale is equal to 0.0, shift for camera along Z-axis.
    */
    ConversionParams() : isDefault (true), bExtentsMode(false), mode (defaultMode), modelScale (0.1), cameraZ (0.0) {}
  };
}

/** \details 
<group PRC_Export_Import_Classes>

Class representing functions for writing PRC data to an output .pdf file. 
*/
class PRCTOPDF_TOOLKIT OdPrcToPdfModule : public OdRxModule
{
public:

  /** \details
  Initializes an application.
  */
  virtual void initApp();
  
  /** \details
  Uninitializes an application.
  */
  virtual void uninitApp();
  
  /** \details
  Writes PRC data to a specified output stream.
  \param pServices  [out] A placeholder for a host services object.
  \param pPrcStream [in] A smart pointer to an input stream with PRC data.
  \param pPrcStream [in] A smart pointer to an output stream (.prc file) to write to.
  \param pPdfStream [in] A smart pointer to an output stream (.pdf file) to write to.
  
  \returns Returns eOk if PRC data was successfully written to a specified output stream or an appropriate error code in the other case.
  */
  virtual OdResult prcToPdf(OdPrcHostAppServices &pServices, OdStreamBufPtr pPrcStream, OdStreamBufPtr pPdfStream);
  
  /** \details
  Writes PRC data to a specified output stream.
  \param pServices  [out] A placeholder for a host services object.
  \param pPrcStream [in] A smart pointer to an input stream with PRC data.
  \param pPdfStream [in] A smart pointer to an output stream (.pdf file) to write to.
  \param pdfParams [in] Graphic parameters of a page.
  \param prcBoundingBox [in] A bounding box.
  
  \returns Returns eOk if PRC data was successfully written to a specified output stream or an appropriate error code in the other case.
  */
  virtual OdResult prcToPdf(OdPrcHostAppServices &pServices, OdStreamBufPtr pPrcStream, OdStreamBufPtr pPdfStream, const OdGsPageParams &pdfParams, const OdGeExtents3d &prcBoundingBox);
  
  /** \details
  Writes PRC data to a specified output stream.
  \param pServices  [out] A placeholder for a host services object.
  \param pPrcStream [in] A smart pointer to an input stream with PRC data.
  \param pPdfStream [in] A smart pointer to an output stream (.pdf file) to write to.
  \param pdfParams  [in] Graphic parameters of a page.
  \param C2W        [in] A matrix which determines the camera position within the world coordinate system.
  \param CO         [in] A distance between the camera and the center of rotation. 
  \param OS         [in] A scale value.
  \param rendMode   [in] A rendering mode value.

  \returns Returns eOk if PRC data was successfully written to a specified output stream or an appropriate error code in the other case.
  */  
  virtual OdResult prcToPdf(OdPrcHostAppServices &pServices, OdStreamBufPtr pPrcStream, OdStreamBufPtr pPdfStream, const OdGsPageParams &pdfParams, const OdGeMatrix3d &C2W, double CO, double OS, PDF3D_ENUMS::PRCRenderingMode rendMode = PDF3D_ENUMS::kDefaultMode);

  /** \details
  Writes PRC data to a specified output stream.
  \param pServices  [out] A placeholder for a host services object.
  \param pPrcStream [in] A smart pointer to an input stream with PRC data.
  \param pPdfStream [in] A smart pointer to an output stream (PDF file) to write to.
  \param params [in] Conversion parameters.
  
  \returns Returns eOk if PRC data was successfully written to a specified output stream or an appropriate error code in the other case.
  */
  virtual OdResult prcToPdf(OdPrcHostAppServices &pServices, OdStreamBufPtr pPrcStream, OdStreamBufPtr pPdfStream, const PrcToPdf::ConversionParams &params);
};

SMARTPTR(OdPrcToPdfModule);

#endif //_PRCTOPDF_DEFINED_


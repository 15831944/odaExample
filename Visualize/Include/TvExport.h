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

#ifndef _ODTV_EXPORT_H_INCLUDED_
#define _ODTV_EXPORT_H_INCLUDED_

#include "RxModule.h"
#include "SharedPtr.h"

#include "TD_PackPush.h"
#include "TvDatabase.h"


/** \details
  This class implements the base Visualize SDK export parameters.
*/
class ODTV_EXPORT OdTvBaseExportParams
{
public:

  /** \details
    Creates a new set of export parameters with default values.
  */
  OdTvBaseExportParams(){};

  /** \details
    Destroys the set of export parameters.
  */
  virtual ~OdTvBaseExportParams() {}

  /** \details
    Sets a new file path for the export output.
    
    \param filePath [in] A string that contains the output file path.
  */
  void setFilePath(const OdString& filePath) { m_strFilePath = filePath; }

  /** \details
    Retrieves the file path for export output.
    
    \returns Returns the output file full path.
  */
  OdString getFilePath() const { return m_strFilePath; }

//DOM-IGNORE-BEGIN
protected:
  // common properties
  OdString  m_strFilePath;            // File path for export with right extension
//DOM-IGNORE-END
};


/** \details
  This class implements the Visualize SDK parameters for exporting to PDF (2D or 3D) format.
  \sa
  <link tv_export_params_pdf, Work with .pdf Export Parameters>
*/
class ODTV_EXPORT OdTvPdfExportParams : public OdTvBaseExportParams
{
public:

  /** \details
    Devices for the bitmap generation
  */
  enum Device
  {
    kOpenGL     = 0,    // OpenGL ES2 device.
    kOpenGLES2  = 1,    // OpenGL device.
    kBitmap     = 2     // Bitmap device.
  };

  /** \details
    Templates for publish to PDF
  */
  enum PublishTemplate
  {
    kDefault        = 0,  // Default template
    kOpenIfcViewer  = 1   // Customized template designed for using in OpenIFCViewer
  };

  /** \details
    Creates a new set of PDF export parameters with default values.
  */
  OdTvPdfExportParams() : m_bIs3DPdf(false)
    , m_backgroundColor(ODRGB(255, 255, 255)), m_bZoomToExtents(true), m_deviceForBitmap(kOpenGLES2), m_publishTemplate(kDefault) { }

  /** \details
    Destroys the set of PDF export parameters.
  */
  virtual ~OdTvPdfExportParams() {}

  /** \details
    Sets the new value of the 3D PDF export flag. The 3D flag value determines whether 3D PDF export should be performed.
    
    \param bIs3DPdf [in] A new value of the 3D PDF export flag.
  */
  void set3DPdf(bool bIs3DPdf) 
  { 
    m_bIs3DPdf = bIs3DPdf; 
  }

  /** \details
    Retrieves the current value of the 3D PDF export flag.
    
    \return The method returns true if the drawing should be exported to the 3D PDF format, otherwise returns false.
  */
  bool is3DPdf() const 
  { 
    return m_bIs3DPdf; 
  }

  /** \details
    Sets the new value of background color.
    
    \param backgroundColor [in] Background color value.
  */
  void setBackgroundColor(ODCOLORREF backgroundColor)
  {
    m_backgroundColor = backgroundColor;
  }

  /** \details
    Retrieves the current value of background color.
    
    \return Background color value as ODCOLORREF.
  */
  ODCOLORREF getBackgroundColor() const
  {
    return m_backgroundColor;
  }

  /** \details
    Sets devices to export.
    
    \param devices [in] Array of strings that contains names of devices to export.
  */
  void setDevices(OdStringArray devices)
  {
    m_devices = devices;
  }

  /** \details
    Retrieves reference to array of devices for export.
    
    \returns Array of strings that contains names of devices to export.
  */
  OdStringArray& getDevices()
  {
    return m_devices;
  }

  /** \details
    Retrieves array of devices for export.
    
    \returns Array of strings that contains names of devices to export.
  */
  OdStringArray getDevices() const
  {
    return m_devices;
  }

  /** \details
    Sets paper sizes of devices to export.
    
    \param paperSizes [in] Array that consists of paper width and height values.
    \remarks
    Width and height are written consistently: for i device width is in 2*i position and height is on 2*i+1 position.
  */
  void setPaperSizes(OdDoubleArray paperSizes)
  {
    m_paperSizes = paperSizes;
  }

  /** \details
    Retrieves reference to array of paper sizes of devices for export.
    
    \remarks
    Width and height are written consistently: for i device width is in 2*i position and height is on 2*i+1 position.
  */
  OdDoubleArray& getPaperSizes()
  {
    return m_paperSizes;
  }

  /** \details
    Retrieves array of paper sizes of devices for export.
    
    \returns
    Array of values of paper width and height values.
    \remarks
    Width and height are written consistently: for i device width is in 2*i position and height is on 2*i+1 position.
  */
  OdDoubleArray getPaperSizes() const
  {
    return m_paperSizes;
  }

  /** \details
    Sets the new flag if need zoom to extents.
    
    \param bVal [in] Zoom to extents flag.
  */
  void setZoomToExtents(bool bVal)
  {
    m_bZoomToExtents = bVal;
  }

  /** \details
    Retrieves flag that indicates whether it is needed zoom to extents.
  
    \returns
    true if it is needed zoom to extents, false otherwise.
  */
  bool getZoomToExtents() const
  {
    return m_bZoomToExtents;
  }

  /** \details
    Sets the device for the bitmap generation.
  
    \param device          [in] Device which should be used for the bitmap generation.
  */
  void setDeviceForBitmap(Device device)
  {
    m_deviceForBitmap = device;
  }

  /** \details
    Retrieves the device for the bitmap generation.
  
    \returns the device which will be used for the bitmap generation.
  */
  Device getDeviceForBitmap() const
  {
    return m_deviceForBitmap;
  }

  /** \details
    Sets the template for the publish to PDF.
  
    \param publishTemplate          [in] Template which should be used for the publish to PDF.
  */
  void setPublishTemplate(PublishTemplate publishTemplate)
  {
    m_publishTemplate = publishTemplate;
  }

  /** \details
    Retrieves the template for the publish to PDF.
  
    \returns the template which will be used for the publish to PDF.
  */
  PublishTemplate getPublishTemplate() const
  {
    return m_publishTemplate;
  }

//DOM-IGNORE-BEGIN
protected:
  bool                        m_bIs3DPdf;           // Flag indicates what action should be performed: export to 2D PDF or publish to 3D PDF
  ODCOLORREF                  m_backgroundColor;    // Background color. Default: white.
  OdStringArray               m_devices;            // Devices to export
  OdDoubleArray               m_paperSizes;         // Paper sizes
  bool                        m_bZoomToExtents;     // Need zoom to extents
  Device                      m_deviceForBitmap;    // Device for bitmap generation
  PublishTemplate             m_publishTemplate;    // Template for publish to PDF
//DOM-IGNORE-END
};

/** \details
This class implements the Visualize SDK parameters for exporting to .dwg.
\sa
<link tv_export_params_dwg, Work with .pdf Export Parameters>
*/
class ODTV_EXPORT OdTvDwgExportParams : public OdTvBaseExportParams
{
public:

  /** \details
    Creates a new set of export parameters.
  */
  OdTvDwgExportParams() : m_bConvertNurbsToSpline(false) { }

  /** \details
    Destroys the set of export parameters.
  */
  virtual ~OdTvDwgExportParams() {}

  /** \details
    Sets a new view to export for the 'view + model' export mode.
    
    \param viewId [in] Identifier of a view to export.
    \remarks
    Deprecated: use the device export mode instead.
    Also, set model to OdTvDwgExportParams if you use the 'view + model' export mode.
  */
  void setView(OdTvGsViewId viewId) { m_viewId = viewId; }

  /** \details
    Retrieves the view for the export operation.
    
    \returns Returns the identifier of the view to export.
  */
  OdTvGsViewId getView() const { return m_viewId; }

  /** \details
    Sets a new model to export for the 'view + model' export mode.
    
    \param modelId [in] Identifier of a model to export.
    \remarks
    Deprecated: use the device export mode instead.
    Also, set view to OdTvDwgExportParams if you use the 'view + model' export mode.
  */
  void setModel(OdTvModelId modelId) { m_modelId = modelId; }

  /** \details
    Retrieves the model for the export operation.
    
    \returns Returns the identifier of the model to export.
  */
  OdTvModelId getModel() const { return m_modelId; }

  /** \details
    Sets a new device to export for device export mode.
    
    \param deviceId [in] Identifier of a device to export.
    \remarks
    You don't need to specify identifiers of a model and view in the device export mode.
  */
  void setDevice(OdTvGsDeviceId deviceId) { m_deviceId = deviceId; }

  /** \details
    Retrieves the device identifier for the export operation.
    
    \returns Returns the identifier of the device to export.
  */
  OdTvGsDeviceId getDevice() const { return m_deviceId; }

  /** \details
    Sets the convert to spline value.
    
    \param bValue [in] An value for convert nurbs to spline.
  */
  void setConvertNurbsToSpline(bool bValue) { m_bConvertNurbsToSpline = bValue; }

  /** \details
    Retrieves the convert nurbs to spline value.
    
    \returns Returns the convert nurbs to spline value.
  */
  bool getConvertNurbsToSpline() const { return m_bConvertNurbsToSpline; }

//DOM-IGNORE-BEGIN
protected:
  OdTvGsViewId m_viewId;
  OdTvModelId m_modelId;
  OdTvGsDeviceId m_deviceId;
  bool m_bConvertNurbsToSpline;
//DOM-IGNORE-END
};

/** \details
  This class implements the Visualize SDK parameters for exporting to .xml or .tgs.
*/
class ODTV_EXPORT OdTvXmlExportParams : public OdTvBaseExportParams
{
public:

  /** \details
    Creates a new set of export parameters.
  */
  OdTvXmlExportParams() : m_bComposite(true), m_bBinary(false) { }

  /** \details
    Destroys the set of export parameters.
  */
  virtual ~OdTvXmlExportParams() {}

  /** \details
    Sets a device for export.
    
    \param deviceId [in] An export device's identifier.
  */
  void setDevice(OdTvGsDeviceId deviceId) { m_deviceId = deviceId; }

  /** \details
    Retrieves the device for the export operation.
    
    \returns Returns the identifier of the device to export.
  */
  OdTvGsDeviceId getDevice() const { return m_deviceId; }

  /** \details
    Sets the new value of the binary flag. The binary flag value determines whether the export to the binary XML (TGS) should be performed.
    
    \param bIsBinary [in] A new value of the binary flag.
  */
  void setIsBinary(bool bIsBinary) { m_bBinary = bIsBinary; }

  /** \details
    Retrieves the current value of the binary flag.
    
    \return The method returns true if the data should be exported to the binary XML (TGS), otherwise returns false.
  */
  bool getIsBinary() const { return m_bBinary; }

  /** \details
    Sets the new value of the composite flag. The composite flag value determines whether the composite metafiles should be exported.
    
    \param bIsComposite [in] A new value of the composite flag.
  */
  void setIsComposite(bool bIsComposite) { m_bComposite = bIsComposite; }

  /** \details
    Retrieves the current value of the composite flag.
    
    \return The method returns true if the composite metafiles should be exported, otherwise returns false.
  */
  bool getIsComposite() const { return m_bComposite; }

  //DOM-IGNORE-BEGIN
protected:
  OdTvGsDeviceId m_deviceId;
  bool m_bBinary;
  bool m_bComposite;
  //DOM-IGNORE-END
};

/** \details
  This class provides the common interface for the export operations.
*/
class ODTV_EXPORT OdTvVisualizeExport
{
public:

  /** \details
    Creates an instance of the Visualize SDK export functionality.
  */
  OdTvVisualizeExport() {};

  /** \details
    Destroys an instance of the Visualize SDK export functionality.
  */
  virtual ~OdTvVisualizeExport() {}

  /** \details
    Retrieves the set of export process properties.
    
    \returns Returns a smart pointer to the instance of the OdRxDictionary object that encapsulates export process properties.
  */
  virtual OdRxDictionaryPtr properties() = 0;

  /** \details
    Exports the Visualize database to the specified file.
  
    \param tvDbId   [in]  A Visualize database to export.
    \param fileName [in]  A full path to the output file.
    \returns Returns the result of the export operation represented with an <link OdTvResult, OdTvResult> value.
  */
  virtual OdTvResult exportTo(const OdTvDatabaseId& tvDbId, const OdString& fileName) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvVisualizeExport, OdTvVisualizeExport> object.
*/
typedef OdSharedPtr<OdTvVisualizeExport> OdTvVisualizeExportPtr;


/** \details
  This class provides an interface for the module that exports data from a Visualize database.
*/
class ODTV_EXPORT OdTvVisualizeExportModule : public OdRxModule
{
public:

  /** \details
    Returns the object that exports a Visualize database to a specified file.
    \returns Returns a smart pointer to an <link OdTvVisualizeExport, OdTvVisualizeExport> object that implements the export functionality.
  */
  virtual OdTvVisualizeExportPtr getVisualizeExporter() const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvVisualizeExportModule, OdTvVisualizeExportModule> object.
*/
typedef OdSmartPtr<OdTvVisualizeExportModule> OdTvVisualizeExportModulePtr;

/** \details
  A data type that represents a pointer to the export callback function for Visualize SDK.
*/
typedef void(*OdTvExportCallbackFunction)(OdTvVisualizeExport*);

#include "TD_PackPop.h"

#endif // _ODTV_EXPORT_H_INCLUDED_

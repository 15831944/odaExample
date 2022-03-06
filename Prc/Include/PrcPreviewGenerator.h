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

#ifndef _PRCPREVIEWGENERATOR_INCLUDED_
#define _PRCPREVIEWGENERATOR_INCLUDED_
 

#include "Gs/Gs.h"
#include "Gi/GiRasterImageArray.h"

class OdPrcPreviewGeneratorImpl;

/** \details
Contains declarations for preview generator functionality. 
*/
namespace PrcPreviewGenerator
{
  /** \details
  Enumerates view's camera position values (view types).
  */
  enum ViewType
  {
    kDefault = 0, //Default mode.
    kFront,       //Front camera mode.
    kBack,        //Back camera mode.
    kTop,         //Camera from the top.
    kBottom,      //Camera from the bottom.
    kRight,       //Camera from the right.
    kLeft         //Camera from the left.
  };
}

/** \details
The class implements creating preview images for views, which exist in a PRC file.
<group PRC_Base_Classes>
*/
class PRC_TOOLKIT OdPrcPreviewGenerator : public OdRxObject
{
public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE_BASE(OdPrcPreviewGenerator)
  //DOM-IGNORE-END

  /** \details
  Destroys the preview images generator.
  */
  virtual ~OdPrcPreviewGenerator();

  /** \details
  Initializes the preview images generator with the content of a specified PRC file.
  \param pPRCFile [in] A smart pointer to a PRC file that should be used for the initialization.
  \returns eOk if the initialization was successful; otherwise, the method returns an appropriate error code.
  */
  OdResult init(OdPrcFilePtr pPRCFile);

  /** \details
  Retrieves the current PRC file associated with the preview images generator.
  \returns Returns a pointer to an OdPrcFile object that represent PRC file content. 
  */
  OdPrcFile *getPRCFile() const;

  /** \details 
    Sets parameters of a camera for the preview images generator.

    \param ptCameraPos    [in] A three-dimensional point that determines the camera position.
    \param ptCameraTarget [in] A three-dimensional point that determines the camera target.
    \param vrCameraUp     [in] A three-dimensional vector that determines the camera's vertical moving.
    \param dCameraWidth   [in] A width of the camera.
    \param dCameraHeight  [in] A height of the camera.
    \param bPerspective   [in] A flag value that determines whether camera is in perspective (if true) of in parallel (if false) mode.

    \returns Returns the eOk value if the new camera was successfully set or an appropriate error code in the other case.
  */
  OdResult setCamera(const OdGePoint3d &ptCameraPos, const OdGePoint3d &ptCameraTarget, const OdGeVector3d &vrCameraUp, double dCameraWidth = 1., double dCameraHeight = 1., bool bPerspective = false);

  /** \details 
    Retrieves the camera's parameters for the preview images generator.

    \param ptCameraPos    [out] A placeholder for a three-dimensional point that determines the camera position.
    \param ptCameraTarget [out] A placeholder for a three-dimensional point that determines the camera target.
    \param vrCameraUp     [out] A placeholder for a three-dimensional vector that determines the camera's vertical moving.
    \param dCameraWidth   [out] A placeholder for the camera width value.
    \param dCameraHeight  [out] A placeholder for the camera height value.
    \param bPerspective   [out] A A placeholder for the camera's perspective flag value.

    \returns Returns the eOk value if the camera's parameters were successfully returned, otherwise the method returns an appropriate error code.
  */
  OdResult getCamera(OdGePoint3d &ptCameraPos, OdGePoint3d &ptCameraTarget, OdGeVector3d &vrCameraUp, double &dCameraWidth, double &dCameraHeight, bool &bPerspective) const;

  /** \details 
    Sets the width and height of the bitmap preview image.

    \param width  [in] A new value of the bitmap width to be set.
    \param height [in] A new value of the bitmap height to be set.

    \returns Returns the eOk value if new width and height values were successfully set, otherwise the method returns an appropriate error code.
  */
  OdResult setBitmapSize(long width, long height);

  /** \details 
    Retrieves current width and height values of the bitmap preview image.

    \param width  [out] A placeholder for the bitmap width value.
    \param height [out] A placeholder for the bitmap height value.

    \returns Returns the eOk value if current bitmap width and height values were successfully returned, otherwise the method returns an appropriate error code.
  */
  OdResult getBitmapSize(long &width, long &height) const;

  /** \details 
    Sets the preview images render mode.

    \param rMode [in] A new value of the render mode.

    \returns Returns the eOk value if the new render mode value was successfully set, otherwise the method returns an appropriate error code.
  */
  OdResult setRenderMode(OdGsView::RenderMode rMode);

  /** \details 
    Retrieves the current render mode value that is used for preview images.

    \param rMode  [out] A placeholder for the render mode value.

    \returns Returns the eOk value if the current render mode value was successfully returned, otherwise the method returns an appropriate error code.
  */
  OdResult getRenderMode(OdGsView::RenderMode &rMode) const;

  /** \details 
    Sets the background color for preview images.

    \param backgroundColor [in] A new value of the background color.

    \returns Returns the eOk value if the new background color value was successfully set, otherwise the method returns an appropriate error code.
  */
  OdResult setBackground(ODCOLORREF backgroundColor);

  /** \details 
    Retrieves the current background color that is used for preview images.

    \param backgroundColor  [out] A placeholder for the current background color value.

    \returns Returns the eOk value if the current background color value was successfully returned, otherwise the method returns an appropriate error code.
  */
  OdResult getBackground(ODCOLORREF &backgroundColor) const;

  /** \details 
    Sets the default color for preview images.

    \param defColor [in] A new value of the default color.

    \returns Returns the eOk value if the new default color value was successfully set, otherwise the method returns an appropriate error code.
    
    \remarks
    The default color is used when a PRC entity does not have a color setting.
  */
  OdResult setDefaultColor(ODCOLORREF defColor);

  /** \details 
    Retrieves the current default color that is used for preview images.

    \param defColor  [out] A placeholder for the current default color value.

    \returns Returns the eOk value if the current default color value was successfully returned, otherwise the method returns an appropriate error code.
    
    \remarks
    The default color is used when a PRC entity does not have a color setting.
  */
  OdResult getDefaultColor(ODCOLORREF &defColor) const;

  /** \details 
    Generates a raster preview image for the current view.

    \param pOutPreview    [out] A smart pointer to an OdGiRasterImage object that represents generated preview image.
    \param bZoomToExtents [in] A flag value that determines whether the generated image should be zoomed to extents.

    \returns Returns the eOk value if the preview image was successfully generated, otherwise the method returns an appropriate error code.
  */
  OdResult generate(OdGiRasterImagePtr &pOutPreview, bool bZoomToExtents = true);

  /** \details 
    Generates a raster preview image for the specified view type (camera position).

    \param viewType [in] A view type for generation of a preview image.
    \param pResult  [in] A pointer to an OdResult value that contains the result of generating operation.

    \returns Returns a smart pointer to an OdGiRasterImage object that contains the generated preview image. 
    \remarks 
    If the pResult parameter is set when calling the method (value of the pointer is not equal to NULL), the method stores the result of generation operation in it. 
    If the generation was successful, the method stores the eOk value, otherwise it stores an appropriate error code. 
  */
  OdGiRasterImagePtr generateByView(PrcPreviewGenerator::ViewType viewType, OdResult *pResult = NULL);

  /** \details 
    Generates raster preview image for each view that exists in the PRC file associated with the generator.

    \param arrRasImg [out] An array of smart pointers to preview images, which should be created as the result of the generation process.

    \returns Returns the eOk value if the preview images were successfully generated, otherwise the method returns an appropriate error code.
  */
  OdResult generatePreviewSet(OdGiRasterImagePtrArray &arrRasImg);
};

/** \details
  A data type that represents a smart pointer to a preview generator object.
*/
SMARTPTR(OdPrcPreviewGenerator);

#endif // _PRCPREVIEWGENERATOR_INCLUDED_


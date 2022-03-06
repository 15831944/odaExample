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


///////////////////////////////////////////////////////////////////////////////
//
// PdfPublish2dGeometryLayer.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_2DGEOM_LAYER_INCLUDED_
#define _PDF_PUBLISH_2DGEOM_LAYER_INCLUDED_

#include "PdfPublishCommon.h"
#include "PdfPublishBaseObject.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements the layer object for the two-dimensional geometry in .pdf documents created with Publish SDK.
  PDF layers can be used when adding objects to Od2dGeometryBlock as well as to Od2dGeometryReference, OdImage and OdText 
  objects which can be added to the document page. 
*/
class PDFPUBLISH_TOOLKIT Od2dGeometryLayer : public OdObject
{
protected:
  //DOM-IGNORE-BEGIN
  Od2dGeometryLayer();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(Od2dGeometryLayer);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END

  /** \details
    Destroys the layer object.
  */
  virtual ~Od2dGeometryLayer();

  /** \details
    Sets the layer name.
    \param name [in] A name value.
    \remarks
    The name is mandatory and must be unique among the document object names.
  */
  void setName(const OdString& name);

  /** \details
    Sets the visibility flag of the layer.

    \param state [in] A visibility flag value. Specify true to allow objects belonging to the layer to be visible when the document is opened. Otherwise false.
  */
  void setVisible(const bool state);

  /** \details
    Sets the locked flag of the layer.

    \param state [out] A locked flag value. Specify true to not allow the visibility of the layer to be changed when viewing the document. Otherwise false.
  */
  void setLocked(const bool state);

  /** \details
    Gets the layer name.
    
    \param name [out] A placeholder for the layer name.
    \remarks
    The method fills a passed string object and returns it to a calling subroutine.
  */
  void getName(OdString& name) const;

  /** \details
    Gets the current value of the visibility flag of the layer.
    
    \param state [out] A placeholder for the visibility flag value.
    \remarks
    The method fills a passed boolean value and returns it to a calling subroutine.
  */
  void getVisible(bool& state) const;

  /** \details
    Gets the current value of the locked flag of the layer.
    
    \param state [out] A placeholder for the locked flag value.
    \remarks
    The method fills a passed boolean value and returns it to a calling subroutine.
  */
  void getLocked(bool& state) const;
};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::Od2dGeometryLayer, Od2dGeometryLayer> object.
*/
SMARTPTR(Od2dGeometryLayer);

}
#endif // _PDF_PUBLISH_2DGEOM_LAYER_INCLUDED_


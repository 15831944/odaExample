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




#ifndef _ODDBVIEWTABLERECORD_INCLUDED
#define _ODDBVIEWTABLERECORD_INCLUDED

#include "TD_PackPush.h"

#include "DbAbstractViewTableRecord.h"
#include "DbAnnotationScale.h"
#include "DbObject.h"
#include "DwgDeclareMembers.h"

/** \details
    This class represents View records in the OdTvDbViewTable in an OdTvDbDatabase instance.

    \sa
    TD_Db
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbViewTableRecord : public OdTvDbAbstractViewTableRecord
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbViewTableRecord);

  OdTvDbViewTableRecord();

  /** \details
    Returns true if and only if this View is a Paper Space view (DXF 70, bit 0x01).
  */
  bool isPaperspaceView() const;
  
  /** \details
    Controls if this View is a Paper Space view (DXF 70, bit 0x01).
    
    \param pspaceView [in]  True for Paper Space, false for Model space.
  */
  void setIsPaperspaceView(
    bool pspaceView);
  
  /** \details
    Returns true if and only if there is a UCS associated with this View.
  */
  bool isUcsAssociatedToView() const;
  /** \details
    Disassociates any UCS associated with this View.
  */
  void disassociateUcsFromView();

  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

  virtual OdResult dxfInFields_R12(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields_R12(
    OdTvDbDxfFiler* pFiler) const;

  /*virtual OdResult subGetClassID(
    void* pClsid) const;*/

  // new in 2005
  
  /** \details
    Returns the name of the category of this View.
  */
  OdString getCategoryName() const;

  /** \details
    Sets the name of the category of this View.
    \param categoryName [in]  Category name.
  */
  void setCategoryName(
    const OdString& categoryName);

  /** \details
    Returns the name of the layer state of this View.
  */
  OdString getLayerState() const;
  /** \details
    Sets the name of the layer state of this View.
    \param layerStateName [in]  Layer State name.
  */
  void setLayerState(
    const OdString& layerStateName);

  /** \details
    Returns the Object ID of the OdTvDbLayout of this View.
  */
  OdTvDbObjectId getLayout() const;

  /** \details
    Sets the Object ID of the Layout of this View.
    \param layoutId [in]  Layout ID.
  */
  void setLayout(
    OdTvDbObjectId layoutId);

  /** \details
    Returns true if and only if this View is associated with a Paper Space Viewport.
  */
  bool isViewAssociatedToViewport() const;
  
  /** \details
    Controls if this View is associated with a Viewport.
    \param viewAssociated [in]  Controls association.
  */
  void setViewAssociatedToViewport (
    bool viewAssociated);

  /** \details
    Returns the thumbnail information for this view.
    
    \param pThumbnail [out]  Receives a pointer to the thumbnail.
    
    \remarks
    Thumbnail information consists of a packed BITMAPINFO structure 
    immediately followed in memory by the thumbnail data.
  */
  void getThumbnail (
    OdBinaryData* pThumbnail) const;
  /** \details
    Sets the thumbnail information for this view.
    
    \param pThumbnail [in]  Pointer to the thumbnail.

    \remarks
    Thumbnail information consists of a packed BITMAPINFO structure 
    immediately followed in memory by the thumbnail data.
  */
  void setThumbnail(
    const OdBinaryData* pThumbnail);

  //  void setParametersFromViewport(OdTvDbObjectId objId);
  
  // new R21 methods
  
  bool isCameraPlottable () const;
  void setIsCameraPlottable(bool plottable);

  OdTvDbObjectId camera() const;
  void setCamera(const OdTvDbObjectId &cameraId);

  virtual void subClose();

  virtual void subSwapIdWith(
    const OdTvDbObjectId& otherId,
    bool swapXdata = false,
    bool swapExtDict = false);

  // Live Section

  OdTvDbObjectId liveSection() const;
  void setLiveSection(const OdTvDbObjectId& liveSectionId);

  OdResult setAnnotationScale(const OdTvDbAnnotationScale* pScaleObj);
  OdTvDbAnnotationScalePtr annotationScale() const;
};

/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbViewTableRecord object pointers.
*/
typedef OdSmartPtr<OdTvDbViewTableRecord> OdTvDbViewTableRecordPtr;

#include "TD_PackPop.h"

#endif // _ODDBVIEWTABLERECORD_INCLUDED


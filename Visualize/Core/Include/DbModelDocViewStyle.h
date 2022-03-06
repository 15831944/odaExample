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

#ifndef OD_MODELDOCVIEWSTYLE_H
#define OD_MODELDOCVIEWSTYLE_H

#include "TD_PackPush.h"
#include "DbObject.h"

/** \details

    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes> 
*/
class ODRX_ABSTRACT DBENT_EXPORT OdTvDbModelDocViewStyle : public OdTvDbObject
{
protected:
  // Default constructor is protected since OdTvDbModelDocViewStyle is an abstract class.
  OdTvDbModelDocViewStyle();

public:
  ODDB_DECLARE_MEMBERS(OdTvDbModelDocViewStyle);

  /** \details
    Defines the attachment point for the model documentation view label text. 
  */
  enum AttachmentPoint {
    kAboveView    = 0,  // Label text is attached above the view.   
    kBelowView    = 1,  // Label text is attached below the view.
  };

  /** \details
    Defines the alignment for the model documentation view label text. 
  */
  enum TextAlignment {
    kTextAlignmentLeft   = 0, // Left alignment is used for the view label text.
    kTextAlignmentCenter = 1, // Center alignment is used for the view label text.
    kTextAlignmentRight  = 2, // Right alignment is used for the view label text.
  };

  // Default destructor.
  virtual ~OdTvDbModelDocViewStyle() = 0;

  /** \details
    Returns the name of this OdTvDbModelDocViewStyle object.
  */
  virtual OdString getName() const;

  /** \details
    Sets the name of this OdTvDbModelDocViewStyle object.

    \param name [in]  Name.
  */
  virtual void setName(const OdString& name);

  /** \details
    Returns the description of this view style.
  */
  virtual OdString description() const;

  /** \details
    Sets the description of this view style.
    
    \param description [in]  Description.
  */
  virtual void setDescription(const OdString& description);

  /** \details
    Sets defaults values for the properties of this view style.
  */
  virtual void setDatabaseDefaults(OdTvDbDatabase* pDb);

  /** \details
    Includes this view style object in a OdTvDbDatabase object.
    
    \param pDb [in]  Pointer of the database to receive the OdTvDbModelDocViewStyle object.
    \param styleName [in]  Name of the view style.
    
    \returns
    Returns the OdTvDbObjectID of the newly added OdTvDbModelDocViewStyle object.
  */
  virtual OdTvDbObjectId postViewStyleToDb(OdTvDbDatabase* pDb, 
                                         const OdString& styleName) = 0;

  /** \details
    Specifies whether properties were changed. 
	
	\returns
    True if properties were changed; returns false otherwise.
  */
  bool isModifiedForRecompute() const;

  /** \details
    Returns the default view name based on the specified index.

    \param index [in]  Index of default name.
  */
  OdString defaultViewName(int index) const;

  /** \details
    Checks whether a label name is valid.

    \param name [in]  Label name to check.

    \returns
    True if the specified name is a valid string.
  */
  bool isViewNameValid(const OdString& name) const;

  ///** \details
  //  Calculates a view label's position.
  //
  //  \param offsetVector [out] Offset (vector) of the view label.
  //  \param textAlignment [out] Text alignment of the view label.
  //  \param attachment [in] Use with the offset argument to specify label position.
  //  \param offset [in] Use with the attachment argument to specify label position. 
  //  \param minPt [in] Point located in the lower left corner of the view's bounding box. 
  //  \param maxPt [in] Point located in the upper right corner of the view's bounding box. 
  //
  //  \returns
  //  Position of the view label.
  //*/
  //static OdGePoint3d calculateViewLabelPosition(OdGeVector2d& offsetVector,
  //                                              OdTvDbMText::AttachmentPoint& textAlignment,
  //                                              OdTvDbModelDocViewStyle::AttachmentPoint attachment,
  //                                              double offset,
  //                                              const OdGePoint3d& minPt,
  //                                              const OdGePoint3d& maxPt);

  ///** \details
  //  Sets the position of a view label.
  //  
  //  \param pMText [in] Pointer to MText object to be positioned as a label.
  //  \param attachment [in] Use with the offset argument to specify label position. 
  //  \param offset [in] Use with the attachment argument to specify label position.
  //  \param minPt [in] Point located in the lower left corner of the view's bounding box.
  //  \param maxPt [in] Point located in the upper right corner of the view's bounding box. 
  //  
  //  \returns
  //  Position of the view label.
  //*/
  //static OdGeVector2d setViewLabelPosition(OdTvDbMText* pMText,
  //                                         OdTvDbModelDocViewStyle::AttachmentPoint attachment,
  //                                         double offset,
  //                                         const OdGePoint3d& minPt,
  //                                         const OdGePoint3d& maxPt);

  ///** \details
  //  Updates the position of a view label.
  //
  //  \param pMText [in] Pointer to MText object to be positioned as a label.
  //  \param attachment [in] Specifies whether the label is attached. 
  //  \param minPt [in] Point located in the lower left corner of the view's bounding box.
  //  \param maxPt [in] Point located in the upper right corner of the view's bounding box. 
  //
  //  \returns
  //  Position of the view label.
  //*/
  //static OdGeVector2d updateViewLabelPosition(OdTvDbMText* pMText,
  //                                            OdTvDbModelDocViewStyle::AttachmentPoint attachment,
  //                                            const OdGePoint3d& minPt,
  //                                            const OdGePoint3d& maxPt);

  OdString getDisplayName() const;
  OdResult setDispayName( const OdString& name );
  bool canRename() const;
  OdResult setCanRename(bool canRename);

protected:
  // OdTvDbObject overridden functions
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  enum
  {
    kCanRename = 1
  };

//protected:
//  // For internal use only
//  virtual OdTvDbObjectPtr subDeepClone(OdTvDbObject* pOwner,
//                                     OdTvDbIdMapping& idMap, bool isPrimary = true) const;
//  virtual OdTvDbObjectPtr subWblockClone(OdTvDbObject* pOwner,
//                                       OdTvDbIdMapping& idMap, bool isPrimary = true) const;
//private:
//    friend class OdTvDbModelDocViewStyleImp;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbModelDocViewStyle object pointers.
*/
typedef OdSmartPtr<OdTvDbModelDocViewStyle> OdTvDbModelDocViewStylePtr;

#include "TD_PackPop.h"

#endif // OD_MODELDOCVIEWSTYLE_H
